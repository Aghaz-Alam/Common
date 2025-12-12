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
        if (type == "truck") return new Truck();
        else return new Ship();
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