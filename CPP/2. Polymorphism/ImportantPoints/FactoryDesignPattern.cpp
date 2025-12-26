//Factory Pattern (Object Creation using Polymorphism)
/* 
Used when:
Object creation logic must be abstracted.
Return objects via base pointer.
*/
//Code:
#include <iostream>
using namespace std;
class Transport {
  public:
    virtual void deliver() = 0;
    virtual ~Transport() {}
};
class Truck : public Transport {
  public:
    void deliver() override { cout << "Deliver by Truck\n"; }
};
class Ship : public Transport {
  public:
    void deliver() override { cout << "Deliver by Ship\n"; }
};
// Factory
class TransportFactory {
  public:
    static Transport* create(string type) {
        if (type == "truck") {
          return new Truck();
        }
        else {
          return new Ship();
        }
    }
};
int main() {
    Transport* t = TransportFactory::create("truck");
    t->deliver();
    delete t;
}
/*
Output:
Deliver by Truck
*/




//Mayer's Singleton thread safe 
#include<iostream>
#include<thread>
using namespace std;
class Test{
    Test()=default;
    
   public:
     Test(const Test&)=delete;
     Test& operator=(const Test&)=delete;
     
     static Test& create(){
         static Test Instance;
         
         return Instance;
     }
     void display(){
         cout<<"Thread safe Singleton class!"<<endl;
     }
};
int main(){
    Test& t1 = Test::create();
    Test& t2 = Test::create();
    
    cout<<((&t1 == &t2) ? "Same Instance!" : "Different Instance!")<<endl;
    
    thread t([]{
        Test::create().display();
    });
    
    t.join();
  return 0;
}
/*
Same Instance!
Thread safe Singleton class!
*/