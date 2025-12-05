/* 
Question 10: Smart Pointer Implementation

Create a C++ program that demonstrates the use of smart pointers. Implement a Resource class and use unique_ptr, shared_ptr, and weak_ptr to manage its instances.

Requirements:
Resource class should have a constructor and destructor printing messages.
Demonstrate ownership transfer using unique_ptr.
Demonstrate reference counting with shared_ptr.
Show how weak_ptr can be used to break circular references.

Sample Input :

auto r1 = make_shared<Resource>();
auto r2 = r1; // shared_ptr


Excepted Output :

Resource acquired
Resource reference count: 2
Resource released
*/


Question 10: Smart Pointer Implementation.

It includes:

✔ Resource class with constructor & destructor messages
✔ unique_ptr ownership transfer
✔ shared_ptr reference counting
✔ weak_ptr demonstrating breaking cyclic references

Matches your expected behavior.

//unique_ptr, shared_ptr, weak_ptr Demo
#include <iostream>
#include <memory>
using namespace std;

class Resource {
public:
    Resource() {
        cout << "Resource acquired\n";
    }
    ~Resource() {
        cout << "Resource released\n";
    }
};

// Class to demonstrate weak_ptr breaking circular references
class Node {
public:
    int value;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;   // weak_ptr prevents circular reference

    Node(int val) : value(val) {
        cout << "Node(" << value << ") created\n";
    }

    ~Node() {
        cout << "Node(" << value << ") destroyed\n";
    }
};

int main() {

    cout << "\n--- unique_ptr Demo ---\n";
    unique_ptr<Resource> u1 = make_unique<Resource>();

    // Transfer ownership
    unique_ptr<Resource> u2 = std::move(u1);

    if (!u1)
        cout << "u1 no longer owns the resource\n";
    if (u2)
        cout << "u2 owns the resource via unique_ptr\n";


    cout << "\n--- shared_ptr Demo ---\n";
    shared_ptr<Resource> r1 = make_shared<Resource>();
    {
        shared_ptr<Resource> r2 = r1;
        cout << "Resource reference count: " << r1.use_count() << "\n";
    }
    // r2 goes out of scope → count decreases
    cout << "Resource reference count after r2 destroyed: " << r1.use_count() << "\n";


    cout << "\n--- weak_ptr Demo (breaking cyclic references) ---\n";
    {
        shared_ptr<Node> n1 = make_shared<Node>(1);
        shared_ptr<Node> n2 = make_shared<Node>(2);

        n1->next = n2;
        n2->prev = n1;   // weak_ptr prevents cycle

        cout << "Both nodes going out of scope now...\n";
    }
    // Both get destroyed normally because weak_ptr does not increase count

    return 0;
}
/* 
Expected Output (Simplified)
--- unique_ptr Demo ---
Resource acquired
u1 no longer owns the resource
u2 owns the resource via unique_ptr

--- shared_ptr Demo ---
Resource acquired
Resource reference count: 2
Resource reference count after r2 destroyed: 1

--- weak_ptr Demo ---
Node(1) created
Node(2) created
Both nodes going out of scope now...
Node(2) destroyed
Node(1) destroyed
Resource released
Resource released


(Exact ordering may vary slightly due to scope, but the behavior is the same.)
*/