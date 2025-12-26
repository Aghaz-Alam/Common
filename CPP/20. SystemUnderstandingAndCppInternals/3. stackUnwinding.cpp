Stack Unwinding
Unwinding means:
✔ Destructor of every local object is called
✔ Scope exits one by one
✔ Until a matching catch() is found
✔ If not found → program terminates

What is Stack Unwinding?
Stack unwinding is the process of cleaning up the stack when an exception is thrown.

✔ Detailed Explanation
When you throw, C++:
Stops normal execution
Searches for a matching catch
Unwinds the call stack
Calls destructors of all local objects
Jumps to the catch block
If no match → calls std::terminate()




✔ Example Demonstrating Stack Unwinding
#include <iostream>
using namespace std;
struct A {
    A()  { cout << "A constructed\n"; }
    ~A() { cout << "A destroyed\n"; }
};
void f2() {
    A a2;
    throw runtime_error("error!");
}
void f1() {
    A a1;
    f2();
}
int main() {
    try {
        f1();
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << "\n";
    }
}
/* 
Output:
A constructed   (from f1)
A constructed   (from f2)
A destroyed     (from f2)
A destroyed     (from f1)
Caught: error!
*/

Notice:
Even though the exception originated in f2(), destructors of objects in both f2() and f1() are executed before the catch block.



Stack Unwinding — Step-by-Step Diagram
Assume this call sequence:
main → f1 → f2 → f3

Inside f3:
throw Error();

Stack before throw:
+-----------------------+
| f3 stack frame        |
| local variables       |
+-----------------------+
| f2 stack frame        |
| locals                |
+-----------------------+
| f1 stack frame        |
| locals                |
+-----------------------+
| main stack frame      |
+-----------------------+

Unwinding process:
Step 1 — f3 frame destroyed
Destructor of f3 locals called.

Step 2 — f2 frame destroyed
Destructor of f2 locals called.

Step 3 — f1 frame destroyed
Destructor of f1 locals called.

Step 4 — main has try/catch
Exception caught here.



✔ What happens during stack unwinding?
Destructors run
Stack frames pop
Unwinder checks for handlers
Jump to catch block

✔ What if a destructor throws during unwinding?
Program terminates.

✔ Does stack unwinding use recursion?
No—handled by unwinder engine (libunwind, Windows SEH).

✔ Does stack trace work during unwinding?
Yes—if captured at throw time.




✅ Example 1: Multiple Local Objects in Each Function
Shows how each functions local objects are destroyed during unwinding.

#include <iostream>
#include <stdexcept>
using namespace std;
struct X {
    string name;
    X(string n) : name(n) { cout << "Construct " << name << "\n"; }
    ~X() { cout << "Destroy " << name << "\n"; }
};
void f3() {
    X x3("x3");
    throw runtime_error("Boom in f3");
}
void f2() {
    X x2("x2");
    f3();
}
void f1() {
    X x1("x1");
    f2();
}
int main() {
    try {
        f1();
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
   return 0;
}
/* 
Output
Construct x1
Construct x2
Construct x3
Destroy x3      ← unwinding starts
Destroy x2
Destroy x1
Caught: Boom in f3
*/



✅ Example 2: Stack Unwinding with Smart Pointers
Destructor of unique_ptr runs during unwinding.

#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;
struct Test {
    Test() { cout << "Test created\n"; }
    ~Test() { cout << "Test destroyed\n"; }
};
void g() {
    unique_ptr<Test> ptr(new Test());
    throw runtime_error("Error in g()");
}
void f() {
    unique_ptr<Test> ptr(new Test());
    g();
}
int main() {
    try {
        f();
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
}
/* 
Output
Test created  (from f)
Test created  (from g)
Test destroyed (from g)
Test destroyed (from f)
Caught: Error in g()
*/


✅ Example 3: Stack Unwinding with Inheritance
Destructor order is still honored.

#include <iostream>
#include <stdexcept>
using namespace std;
struct Base {
    Base()  { cout << "Base constructed\n"; }
    ~Base() { cout << "Base destroyed\n"; }
};
struct Derived : Base {
    Derived()  { cout << "Derived constructed\n"; }
    ~Derived() { cout << "Derived destroyed\n"; }
};
void fun() {
    Derived d;
    throw runtime_error("Error!");
}
int main() {
    try {
        fun();
    }
    catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
}
/* 
Output
Base constructed
Derived constructed
Derived destroyed   ← child first
Base destroyed      ← parent next
Caught: Error!
*/


✅ Example 4: Unwinding through Multiple Try–Catch Blocks
Demonstrates rethrowing and continuing unwinding.

#include <iostream>
#include <stdexcept>
using namespace std;
struct Obj {
    string n;
    Obj(string n) : n(n) { cout << "Create " << n << "\n"; }
    ~Obj() { cout << "Destroy " << n << "\n"; }
};
void f3() {
    Obj o("o3");
    throw runtime_error("f3 failed");
}
void f2() {
    Obj o("o2");
    try {
        f3();
    }
    catch(...) {
        cout << "f2 caught but rethrowing\n";
        throw;
    }
}
void f1() {
    Obj o("o1");
    f2();
}
int main() {
    try {
        f1();
    }
    catch(const exception& e) {
        cout << "Main caught: " << e.what() << endl;
    }
}
/* 
Output
Create o1
Create o2
Create o3
Destroy o3
f2 caught but rethrowing
Destroy o2
Destroy o1
Main caught: f3 failed
*/



✅ Example 5: Stack Unwinding in Constructors (Partially Constructed Objects)
Only fully constructed subobjects are destroyed.

#include <iostream>
#include <stdexcept>
using namespace std;
struct A {
    A() { cout << "A constructed\n"; }
    ~A(){ cout << "A destroyed\n"; }
};
struct B {
    B() { cout << "B constructed\n"; }
    ~B(){ cout << "B destroyed\n"; }
};
struct C {
    A a;     // constructed first
    C() {
        cout << "C constructor\n";
        throw runtime_error("Failure in C");
    }
    ~C() { cout << "C destroyed\n"; }
};
int main() {
    try {
        C c;
    }
    catch(...) {
        cout << "Error caught\n";
    }
}
/* 
Output
A constructed
C constructor
A destroyed      ← only subobject constructed
Error caught


Notice:
B is never constructed → so never destroyed.
C’s destructor does NOT run because the object never fully constructed.
*/