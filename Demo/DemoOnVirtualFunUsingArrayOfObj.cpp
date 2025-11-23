✔️ Corrected & Complete Code (Polymorphic Example)
#include <iostream>
using namespace std;
class Base {
  public:
    virtual void fun() {
        cout << "Base fun\n";
    }
    virtual ~Base() { 
        cout << "Base destroyed\n"; 
    }
};
class Derived : public Base {
  public:
    void fun() override {
        cout << "Derived fun\n";
    }
    ~Derived() {
        cout << "Derived destroyed\n";
    }
};
int main() {
    Derived d;
    // array of Base pointers
    Base** b = new Base*[2];
    for (int i = 0; i < 2; i++) {
        b[i] = &d;   // Pointing to same derived object
    }
    for (int i = 0; i < 2; i++) {
        b[i]->fun();   // Calls Derived fun
    }
    delete [] b;  // deleting pointer array (not the objects)

   return 0;
}

What this code does:
d is a single Derived object.
b is an array of 2 pointers (Base*).
Both entries in the array point to the same Derived instance.
b[i]->fun() correctly dispatches to Derived::fun().
delete [] b; only deletes the array of pointers (not the objects they point to).




✔️ If you want each element to be a separate Derived object
Here is the version where each element is dynamically created:
int main() {
    Base** b = new Base*[2];
    for (int i = 0; i < 2; i++) {
        b[i] = new Derived();
    }
    for (int i = 0; i < 2; i++) {
        b[i]->fun();
    }
    for (int i = 0; i < 2; i++) {
        delete b[i];   // deletes Derived, then Base
    }
    delete [] b;       // deletes pointer array
}



