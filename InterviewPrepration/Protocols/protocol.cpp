#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>
#include <vector>

using namespace std;

// ==============================
//       CAN Message
// ==============================
struct CANMessage {
    uint32_t id;
    vector<uint8_t> data;
};

// ==============================
//         CAN BUS
// ==============================
class CANBus {
private:
    queue<CANMessage> msgQueue;
    mutex mtx;
    condition_variable cv;

public:
    // Send a message into the bus
    void send(const CANMessage &msg) {
        {
            lock_guard<mutex> lock(mtx);
            msgQueue.push(msg);
        }
        cv.notify_one();
    }

    // Non-blocking receive with timeout
    bool receive(CANMessage &msg) {
        unique_lock<mutex> lock(mtx);
        if (cv.wait_for(lock, chrono::milliseconds(50)) == cv_status::timeout)
            return false;

        msg = msgQueue.front();
        msgQueue.pop();
        return true;
    }
};

// ==============================
//          ECU Base
// ==============================
class ECU {
protected:
    string name;
    CANBus &bus;
    thread worker;
    atomic<bool> running{false};

public:
    ECU(const string &n, CANBus &b) : name(n), bus(b) {}
    virtual ~ECU() { stop(); }

    virtual void onReceive(const CANMessage &msg) = 0;
    virtual void onStart() {}

    void start() {
        running = true;
        onStart();

        worker = thread([this] {
            while (running) {
                CANMessage msg;
                if (bus.receive(msg)) {
                    onReceive(msg);
                } else {
                    // no data, avoid busy wait
                    this_thread::sleep_for(chrono::milliseconds(10));
                }
            }
        });
    }

    void stop() {
        if (!running) return;
        running = false;
        bus.send({0, {0}});     // wake-up message
        if (worker.joinable()) worker.join();
    }
};

// ==============================
//        Engine ECU
// ==============================
class EngineECU : public ECU {
public:
    EngineECU(CANBus &b) : ECU("ECU_Engine", b) {}

    void onStart() override {
        // Send initial engine message
        CANMessage msg{0x100, {0x0F, 0xA0}};
        bus.send(msg);

        cout << "[" << name << "][CAN TX]  ID=0x"
             << hex << msg.id << " data="
             << hex << (int)msg.data[0] << " "
             << hex << (int)msg.data[1] << dec << endl;
    }

    void onReceive(const CANMessage &msg) override {
        // Engine does not process messages in this simple demo
    }
};

// ==============================
//          ABS ECU
// ==============================
class ABSECU : public ECU {
public:
    ABSECU(CANBus &b) : ECU("ECU_ABS", b) {}

    void onReceive(const CANMessage &msg) override {
        cout << "[" << name << "][CAN RX] from ECU_Engine "
             << "ID=0x" << hex << msg.id << " data=";

        for (auto d : msg.data)
            cout << hex << (int)d << " ";

        cout << dec << endl;
    }
};

// ==============================
//          MAIN
// ==============================
int main() {
    cout << "=== Simulated Automotive Protocols Demo ===\n\n";

    CANBus bus;

    EngineECU engine(bus);
    ABSECU abs(bus);

    engine.start();
    abs.start();

    this_thread::sleep_for(chrono::seconds(1));

    engine.stop();
    abs.stop();

    cout << "\n=== End of Simulation ===\n";
    return 0;
}
/* 
=== Simulated Automotive Protocols Demo ===

[ECU_Engine][CAN TX]  ID=0x100 data=f a0
[ECU_ABS][CAN RX] from ECU_Engine ID=0x0 data=0 

=== End of Simulation ===
*/