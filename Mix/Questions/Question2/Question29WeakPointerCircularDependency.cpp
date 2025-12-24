/* 
29. Weak Pointer Circular Dependency

Demonstrate a circular reference problem between Parent and Child classes using shared_ptr.
Resolve it using weak_ptr to prevent memory leaks.
*/


#include <iostream>
#include <memory>
using namespace std;

// ====================== BAD VERSION (LEAKS) ======================
class Child; // forward declaration

class Parent {
public:
    shared_ptr<Child> child; // shared_ptr → causes circular dependency

    Parent() { cout << "Parent created\n"; }
    ~Parent() { cout << "Parent destroyed\n"; }
};

class Child {
public:
    shared_ptr<Parent> parent; // shared_ptr back to parent → leak!

    Child() { cout << "Child created\n"; }
    ~Child() { cout << "Child destroyed\n"; }
};

void circularLeakDemo() {
    auto p = make_shared<Parent>();
    auto c = make_shared<Child>();

    p->child = c;
    c->parent = p;

    cout << "Exiting circularLeakDemo...\n";
    // p and c go out of scope here BUT
    // shared_ptr reference count never becomes 0 → memory leak
}



// ====================== FIXED VERSION (NO LEAK) ======================
class Child2; // forward declared

class Parent2 {
public:
    shared_ptr<Child2> child;

    Parent2() { cout << "Parent2 created\n"; }
    ~Parent2() { cout << "Parent2 destroyed\n"; }
};

class Child2 {
public:
    weak_ptr<Parent2> parent; // weak_ptr FIXES cycle

    Child2() { cout << "Child2 created\n"; }
    ~Child2() { cout << "Child2 destroyed\n"; }
};

void weakPtrSolutionDemo() {
    auto p = make_shared<Parent2>();
    auto c = make_shared<Child2>();

    p->child = c;
    c->parent = p; // weak_ptr → does not increase ref count

    cout << "Exiting weakPtrSolutionDemo...\n";
    // Both objects are properly destroyed.
}



// ====================== MAIN ======================
int main() {
    cout << "\n--- Demonstrating Circular Leak (shared_ptr) ---\n";
    circularLeakDemo();  // Parent/Child destructors will NOT run

    cout << "\n--- Demonstrating Fixed Version (weak_ptr) ---\n";
    weakPtrSolutionDemo();  // Parent2/Child2 destructors WILL run

    return 0;
}
/* 
Explanation
❌ 1. Circular Dependency Leak
Parent has shared_ptr<Child>
Child has shared_ptr<Parent>

Both objects hold strong references to each other.
Parent Ref Count: 1 → from main + 1 from Child = 2
Child Ref Count: 1 → from main + 1 from Parent = 2


When they go out of scope:
Each still has a ref count of 1
Neither is destroyed
Destructor messages never print → memory leak

✔️ 2. Fix using weak_ptr
The fix:
Child2 has weak_ptr<Parent2>

weak_ptr:
Does NOT increase reference count
Does NOT participate in ownership
Breaks the cycle

Ref counts become:
Parent2 Ref Count: 1
Child2 Ref Count: 1

Both drop to 0 naturally → destructors run.

🎯 Output (Expected)
--- Demonstrating Circular Leak (shared_ptr) ---
Parent created
Child created
Exiting circularLeakDemo...

--- Demonstrating Fixed Version (weak_ptr) ---
Parent2 created
Child2 created
Exiting weakPtrSolutionDemo...
Parent2 destroyed
Child2 destroyed

(Notice how Parent/Child destructors do not run in the first case.)
*/