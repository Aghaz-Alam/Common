// sim_protocols.cpp
// Compile: g++ -std=c++17 sim_protocols.cpp -O2 -o sim_protocols && ./sim_protocols

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// -----------------------------
// Utility helpers
// -----------------------------
string hexify(const vector<uint8_t>& d) {
    std::ostringstream os; os << std::hex << std::setfill('0');
    for (auto b : d) os << std::setw(2) << (int)b << ' ';
    return os.str();
}
template <typename T>
string to_hex(T v) {
    std::ostringstream os; os << "0x" << std::hex << v;
    return os.str();
}

// -----------------------------
// SimBus
// -----------------------------
class SimBus {
  public:
    using Callback = function<void(const string&, const string&, const vector<uint8_t>&)>;
    void registerNode(const string& name, Callback cb) {
        lock_guard<mutex> lg(m_);
        nodes_[name] = cb;
    }
    void broadcast(const string& src, const string& proto, const vector<uint8_t>& payload) {
        lock_guard<mutex> lg(m_);
        for (auto& n : nodes_) {
            if (n.first != src) n.second(src, proto, payload);
        }
    }
    void sendTo(const string& src, const string& dst,
                const string& proto, const vector<uint8_t>& payload) {
        lock_guard<mutex> lg(m_);
        if (nodes_.count(dst)) nodes_[dst](src, proto, payload);
    }

  private:
    mutex m_;
    map<string, Callback> nodes_;
};
static SimBus gBus;

// -----------------------------
// CAN
// -----------------------------
namespace CAN {
struct Frame { uint32_t id; vector<uint8_t> data; bool extended=false, fd=false; };

class Node {
  public:
    Node(const string& name) : name_(name) {
        gBus.registerNode(name_, [this](auto& s, auto& p, auto& raw){
            if (p=="CAN") onRaw(s,raw);
        });
    }
    void setCallback(function<void(const Frame&, const string&)> cb){ cb_=cb; }

    void send(const Frame& f) {
        vector<uint8_t> raw;
        raw.push_back((f.id>>24)&255);
        raw.push_back((f.id>>16)&255);
        raw.push_back((f.id>>8)&255);
        raw.push_back((f.id)&255);
        raw.push_back((f.extended?1:0)|(f.fd?2:0));
        raw.push_back(f.data.size());
        raw.insert(raw.end(), f.data.begin(), f.data.end());
        gBus.broadcast(name_,"CAN",raw);
        cout<<"["<<name_<<"][CAN TX] ID="<<to_hex(f.id)<<" data="<<hexify(f.data)<<"\n";
    }

  private:
    void onRaw(const string& src, const vector<uint8_t>& raw) {
        if (raw.size()<6) return;
        Frame f;
        f.id = (raw[0]<<24)|(raw[1]<<16)|(raw[2]<<8)|raw[3];
        size_t len = raw[5];
        if (raw.size()>=6+len) f.data.assign(raw.begin()+6,raw.begin()+6+len);
        if (cb_) cb_(f,src);
    }
    string name_;
    function<void(const Frame&,const string&)> cb_;
};
}

// -----------------------------
// LIN
// -----------------------------
namespace LIN {
struct Frame { uint8_t pid; vector<uint8_t> data; };

class Master {
  public:
    Master(const string& n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&raw){ if(p=="LIN") onResp(s,raw); });
    }
    void request(const string& slave, uint8_t pid){
        gBus.sendTo(name_,slave,"LIN",{pid});
        cout<<"["<<name_<<"][LIN] Request PID="<<(int)pid<<" -> "<<slave<<"\n";
    }
  private:
    void onResp(const string& src,const vector<uint8_t>&raw){
        if(raw.empty())return;
        uint8_t pid=raw[0];
        vector<uint8_t> d(raw.begin()+1, raw.end());
        cout<<"["<<name_<<"][LIN RX] from "<<src<<" PID="<<(int)pid<<" data="<<hexify(d)<<"\n";
    }
    string name_;
};

class Slave {
  public:
    Slave(const string&n,uint8_t pid,vector<uint8_t>reply):name_(n),pid_(pid),reply_(reply){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&raw){ if(p=="LIN") onReq(s,raw); });
    }
  private:
    void onReq(const string&src,const vector<uint8_t>&raw){
        if(raw.empty())return;
        if(raw[0]==pid_){
            vector<uint8_t> out = {pid_};
            out.insert(out.end(), reply_.begin(), reply_.end());
            gBus.sendTo(name_,src,"LIN",out);
            cout<<"["<<name_<<"][LIN TX] PID="<<(int)pid_<<" data="<<hexify(reply_)<<"\n";
        }
    }
    string name_; uint8_t pid_; vector<uint8_t> reply_;
};
}

// -----------------------------
// FlexRay
// -----------------------------
namespace FlexRay {
class Controller {
  public:
    Controller(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="FlexRay") onRaw(s,r); });
    }
    void send(uint16_t slot, const vector<uint8_t>& payload){
        vector<uint8_t> raw = {(uint8_t)(slot>>8),(uint8_t)slot,(uint8_t)payload.size()};
        raw.insert(raw.end(),payload.begin(),payload.end());
        gBus.broadcast(name_,"FlexRay",raw);
        cout<<"["<<name_<<"][FlexRay TX] slot="<<slot<<" data="<<hexify(payload)<<"\n";
    }
  private:
    void onRaw(const string&src,const vector<uint8_t>&r){
        if(r.size()<3)return;
        uint16_t slot=(r[0]<<8)|r[1];
        uint8_t len=r[2];
        vector<uint8_t> p(r.begin()+3,r.begin()+3+len);
        cout<<"["<<name_<<"][FlexRay RX] from "<<src<<" slot="<<slot<<" data="<<hexify(p)<<"\n";
    }
    string name_;
};
}

// -----------------------------
// DoIP
// -----------------------------
namespace DoIP {
vector<uint8_t> pack(const string&s,const vector<uint8_t>&p){
    vector<uint8_t>r={uint8_t(s.size())};
    r.insert(r.end(),s.begin(),s.end());
    r.insert(r.end(),p.begin(),p.end());
    return r;
}

pair<string,vector<uint8_t>> unpack(const vector<uint8_t>&raw){
    if(raw.empty())return{"",{}}; size_t n=raw[0];
    string s(raw.begin()+1,raw.begin()+1+n);
    vector<uint8_t>d(raw.begin()+1+n,raw.end());
    return{s,d};
}

class Node {
  public:
    Node(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="ETH") onRx(s,r); });
    }
    void send(const string&dst,const string&svc,const vector<uint8_t>&payload){
        gBus.sendTo(name_,dst,"ETH",pack(svc,payload));
        cout<<"["<<name_<<"][DoIP TX] to="<<dst<<" svc="<<svc<<"\n";
    }
  private:
    void onRx(const string&src,const vector<uint8_t>&raw){
        auto [svc,p]=unpack(raw);
        cout<<"["<<name_<<"][DoIP RX] from "<<src<<" svc="<<svc<<" data="<<hexify(p)<<"\n";
    }
    string name_;
};
}

// -----------------------------
// UDS
// -----------------------------
namespace UDS {
enum SID:uint8_t { ReadDataByIdentifier=0x22, ECUReset=0x11 };

class Server {
  public:
    Server(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="ETH") onReq(s,r); });
    }
  private:
    void onReq(const string&src,const vector<uint8_t>&raw){
        if(raw.empty())return;
        uint8_t sid=raw[0];

        if(sid==ReadDataByIdentifier && raw.size()>=3){
            uint16_t did=(raw[1]<<8)|raw[2];
            if(did==0xF190){
                vector<uint8_t> resp={sid+0x40,0xF1,0x90};
                string vin="SIMVIN123456";
                resp.insert(resp.end(),vin.begin(),vin.end());
                gBus.sendTo(name_,src,"ETH",resp);
                return;
            }
        }

        if(sid==ECUReset){
            vector<uint8_t> r={sid+0x40,0x01};
            gBus.sendTo(name_,src,"ETH",r);
            return;
        }

        gBus.sendTo(name_,src,"ETH",{0x7F,sid,0x11});
    }

    string name_;
};

class Client {
  public:
    Client(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="ETH") onRx(s,r); });
    }
    void readVIN(const string&srv){
        gBus.sendTo(name_,srv,"ETH",{ReadDataByIdentifier,0xF1,0x90});
    }
    void reset(const string&srv){
        gBus.sendTo(name_,srv,"ETH",{ECUReset,0x01});
    }
  private:
    void onRx(const string&src,const vector<uint8_t>&r){
        if(r.empty())return;
        if(r[0]==ReadDataByIdentifier+0x40){
            string vin(r.begin()+3,r.end());
            cout<<"["<<name_<<"][UDS RX] VIN="<<vin<<"\n";
        } else if(r[0]==ECUReset+0x40){
            cout<<"["<<name_<<"][UDS RX] ECU Reset OK\n";
        }
    }
    string name_;
};
}

// -----------------------------
// OBD
// -----------------------------
namespace OBD {
class Gateway {
  public:
    Gateway(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="CAN") onReq(s,r); });
    }
  private:
    void onReq(const string&src,const vector<uint8_t>&r){
        if(r.size()<2)return;
        uint8_t pid=r[1];
        if(pid==0x0C){ // RPM
            int rpm=3000;
            int val=rpm*4;
            gBus.sendTo(name_,src,"CAN",{0x41,pid, (uint8_t)(val>>8),(uint8_t)val});
        } else if(pid==0x0D){
            gBus.sendTo(name_,src,"CAN",{0x41,pid,88});
        }
    }
    string name_;
};

class Client {
  public:
    Client(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="CAN") onResp(s,r); });
    }
    void reqRPM(const string&gw){ gBus.sendTo(name_,gw,"CAN",{0x01,0x0C}); }
    void reqSpeed(const string&gw){ gBus.sendTo(name_,gw,"CAN",{0x01,0x0D}); }
  private:
    void onResp(const string&src,const vector<uint8_t>&r){
        if(r.size()<3)return;
        if(r[1]==0x0C)
            cout<<"["<<name_<<"][OBD RX] RPM="<<(((r[2]<<8)|r[3])/4)<<"\n";
        else if(r[1]==0x0D)
            cout<<"["<<name_<<"][OBD RX] SPEED="<<(int)r[2]<<"\n";
    }
    string name_;
};
}

// -----------------------------
// SOME/IP
// -----------------------------
namespace SOMEIP {
class Service {
  public:
    Service(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="SOMEIP") onReq(s,r); });
    }
    void setHandler(function<vector<uint8_t>(const vector<uint8_t>&)>h){handler_=h;}
  private:
    void onReq(const string&src,const vector<uint8_t>&r){
        auto resp=handler_(r);
        gBus.sendTo(name_,src,"SOMEIP",resp);
    }
    string name_;
    function<vector<uint8_t>(const vector<uint8_t>&)> handler_;
};

class Client {
  public:
    Client(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="SOMEIP") onResp(s,r); });
    }
    void call(const string&srv,const vector<uint8_t>&p){
        gBus.sendTo(name_,srv,"SOMEIP",p);
    }
  private:
    void onResp(const string&src,const vector<uint8_t>&r){
        cout<<"["<<name_<<"][SOME/IP RX] "<<hexify(r)<<"\n";
    }
    string name_;
};
}

// -----------------------------
// XCP
// -----------------------------
namespace XCP {
class Slave {
  public:
    Slave(const string&n):name_(n){
        mem.resize(256);
        iota(mem.begin(),mem.end(),0);
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="XCP") onReq(s,r); });
    }
  private:
    void onReq(const string&src,const vector<uint8_t>&r){
        if(r.size()<9)return;
        uint32_t addr=(r[1]<<24)|(r[2]<<16)|(r[3]<<8)|r[4];
        uint32_t len =(r[5]<<24)|(r[6]<<16)|(r[7]<<8)|r[8];
        vector<uint8_t> out(mem.begin()+addr, mem.begin()+addr+len);
        gBus.sendTo(name_,src,"XCP",out);
    }
    string name_; vector<uint8_t> mem;
};

class Master {
  public:
    Master(const string&n):name_(n){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){ if(p=="XCP") onResp(s,r); });
    }
    void read(const string&slave,uint32_t addr,uint32_t len){
        vector<uint8_t>req={0x22,(uint8_t)(addr>>24),(uint8_t)(addr>>16),
        (uint8_t)(addr>>8),(uint8_t)addr,(uint8_t)(len>>24),(uint8_t)(len>>16),
        (uint8_t)(len>>8),(uint8_t)len};
        gBus.sendTo(name_,slave,"XCP",req);
    }
  private:
    void onResp(const string&,const vector<uint8_t>&r){
        cout<<"["<<name_<<"][XCP RX] "<<hexify(r)<<"\n";
    }
    string name_;
};
}

// -----------------------------
// SPI / I2C / UART
// -----------------------------
namespace Peripheral {
class SPIdev {
  public:
    SPIdev(const string&n,uint8_t v):name_(n),val(v){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){if(p=="SPI")onCmd(s,r);});
    }
    void onCmd(const string&src,const vector<uint8_t>&r){
        if(r.size() && r[0]==0x01)
            gBus.sendTo(name_,src,"SPI",{val});
    }
  private:
    string name_; uint8_t val;
};

class I2Cdev {
  public:
    I2Cdev(const string&n,uint8_t v):name_(n){
        regs={v};
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){if(p=="I2C")onCmd(s,r);});
    }
    void onCmd(const string&src,const vector<uint8_t>&r){
        uint8_t reg=r[0];
        uint8_t v = (reg<regs.size()?regs[reg]:0xFF);
        gBus.sendTo(name_,src,"I2C",{v});
    }
  private:
    string name_; vector<uint8_t> regs;
};

class UARTdev {
  public:
    UARTdev(const string&n,string g):name_(n),msg(g){
        gBus.registerNode(name_,[this](auto&s,auto&p,auto&r){if(p=="UART")onCmd(s,r);});
    }
    void onCmd(const string&src,const vector<uint8_t>&r){
        string s(r.begin(),r.end());
        if(s=="HELLO"){
            vector<uint8_t> out(msg.begin(),msg.end());
            gBus.sendTo(name_,src,"UART",out);
        }
    }
  private:
    string name_, msg;
};
}

// -----------------------------
// MAIN
// -----------------------------
int main() {
    cout << "=== Simulated Automotive Protocols Demo ===\n\n";

    // CAN
    CAN::Node eng("ECU_Engine");
    CAN::Node abs("ECU_ABS");
    abs.setCallback([](auto&f,auto&s){
        cout<<"[ABS][CAN RX] from "<<s<<" data="<<hexify(f.data)<<"\n";
    });
    eng.send({0x100,{0x0F,0xA0}});

    cout<<"\n";

    // LIN
    LIN::Master lm("LIN_Master");
    LIN::Slave ld("Door_Slave",5,{0xAB,0xCD});
    lm.request("Door_Slave",5);

    cout<<"\n";

    // FlexRay
    FlexRay::Controller frA("FR_A");
    FlexRay::Controller frB("FR_B");
    frA.send(2,{0x11,0x22});

    cout<<"\n";

    // DoIP + UDS
    UDS::Server udsS("UDS_Server");
    UDS::Client udsC("UDS_Client");
    udsC.readVIN("UDS_Server");
    udsC.reset("UDS_Server");

    cout<<"\n";

    // OBD
    OBD::Gateway gw("OBD_GW");
    OBD::Client obc("Tester");
    obc.reqRPM("OBD_GW");
    obc.reqSpeed("OBD_GW");

    cout<<"\n";

    // SOME/IP
    SOMEIP::Service sTemp("TempService");
    sTemp.setHandler([](auto&){ return vector<uint8_t>{0x55}; });
    SOMEIP::Client cTemp("TempClient");
    cTemp.call("TempService",{0x01});

    cout<<"\n";

    // XCP
    XCP::Slave xs("XCP_Slave");
    XCP::Master xm("XCP_Master");
    xm.read("XCP_Slave",10,5);

    cout<<"\n";

    // Peripherals
    Peripheral::SPIdev sp("SPI_Sensor",42);
    Peripheral::I2Cdev i2("I2C_Temp",99);
    Peripheral::UARTdev ua("UART_Greet","WELCOME!");

    // simulate calls
    gBus.sendTo("Tester","SPI_Sensor","SPI",{0x01});
    gBus.sendTo("Tester","I2C_Temp","I2C",{0x00});
    gBus.sendTo("Tester","UART_Greet","UART",{'H','E','L','L','O'});

    cout << "\n=== END ===\n";
    return 0;
}
/* 
=== Simulated Automotive Protocols Demo ===

[ECU_Engine][CAN TX]  ID=0x100 data=f a0
[ECU_ABS][CAN RX] from ECU_Engine ID=0x0 data=0 

=== End of Simulation ===
*/