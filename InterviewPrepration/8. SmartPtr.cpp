difference between shared and unique ptr
| Feature         | `unique_ptr`               | `shared_ptr`                       |
| --------------- | -------------------------- | ---------------------------------- |
| Ownership       | Exclusive                  | Shared                             |
| Copying         | ❌ Not allowed              | ✔ Allowed                          |
| Moving          | ✔ Allowed                  | NA (shared copies increase count)  |
| Reference Count | ❌ None                     | ✔ Yes                              |
| Overhead        | Very low                   | Higher (control block, atomic ops) |
| Use cases       | Resource with single owner | Multiple owners required           |


✅ What is a Smart Pointer?
---> A smart pointer in C++ is a class template (in <memory>) that manages a raw pointer automatically.
It handles:
---> Automatic memory release
---> Ownership semantics
---> Avoiding memory leaks
---> Avoiding dangling pointers
---> Smart pointers use RAII → memory is freed when the smart pointer goes out of scope.


✅ 7. Advantages of Smart Pointers
✔️ Automatic memory management
✔️ Prevent memory leaks
✔️ Prevent double delete
✔️ Exception-safe
✔️ Easy ownership semantics
✔️ Better with STL containers
✔️ No need to manually call delete
✔️ Smart Pointer Example

#include <memory>
using namespace std;
int main() {
    unique_ptr<int> up = make_unique<int>(10);      // exclusive owner
    shared_ptr<int> sp1 = make_shared<int>(20);     // reference counted
    shared_ptr<int> sp2 = sp1;                      // count = 2
}


✅ Why do we use Smart Pointers?
---> They solve common raw-pointer problems:

✔ Memory leaks
---> If you forget to delete memory → leak.
---> Smart pointers call delete automatically.

✔ Exception safety
---> Even if an exception occurs, destructors run → memory gets freed.

✔ Clear ownership
---> You can define who owns the object (unique/shared).

✔ Prevent double delete
---> Smart pointers ensure the object is deleted only once.

✅ Types of Smart Pointers
1. unique_ptr
---> Exclusive ownership.
---> Only one owner at a time.
---> Cannot be copied.
---> Can be moved.

2. shared_ptr
---> Shared ownership.
---> Maintains reference count (use_count()).
---> Object destroyed when count becomes 0.

3. weak_ptr
---> Non-owning reference.
---> Used to break circular references.

✅ Difference between unique_ptr and shared_ptr
| Feature         | `unique_ptr`               | `shared_ptr`                       |
| --------------- | -------------------------- | ---------------------------------- |
| Ownership       | Exclusive                  | Shared                             |
| Copying         | ❌ Not allowed              | ✔ Allowed                          |
| Moving          | ✔ Allowed                  | NA (shared copies increase count)  |
| Reference Count | ❌ None                     | ✔ Yes                              |
| Overhead        | Very low                   | Higher (control block, atomic ops) |
| Use cases       | Resource with single owner | Multiple owners required           |

Example:
unique_ptr<A> p1(new A);
// unique_ptr<A> p2 = p1;  // ❌ compile error
unique_ptr<A> p2 = std::move(p1);  // ✔ transfer ownership

shared_ptr<A> s1(new A);
shared_ptr<A> s2 = s1;  // ✔ both share the object



❗ What is Circular Reference? (Shared Pointer Problem)
Problem:
If two objects hold shared_ptr to each other → reference count never becomes zero.

➡ Memory leak occurs.
Example:
struct B;
struct A {
    shared_ptr<B> bptr;
};
struct B {
    shared_ptr<A> aptr;
};


Both objects keep each other alive → never destroyed.

✅ How to Overcome Circular Reference?
Use weak_ptr on at least one side.

Why?
weak_ptr does not increase reference count
It observes the object without owning it

Fixed Example:
struct B;
struct A {
    shared_ptr<B> bptr;
};
struct B {
    weak_ptr<A> aptr;  // FIX: use weak_ptr
};




Now destruction works properly.

#include <iostream>
#include <memory>
using namespace std;
struct Sample;   // Forward declaration
struct Test {
    shared_ptr<Sample> sptr;   // Test points to Sample
    Test()  { cout << "Test constructed\n"; }
    ~Test() { cout << "Test destroyed\n"; }
};
struct Sample {
    weak_ptr<Test> tptr;    // Sample weakly points to Test
    Sample()  { cout << "Sample constructed\n"; }
    ~Sample() { cout << "Sample destroyed\n"; }
};
int main() {
    {
        shared_ptr<Test> t = make_shared<Test>();
        shared_ptr<Sample> s = make_shared<Sample>();

        t->sptr = s;     // shared ownership
        s->tptr = t;     // weak ownership (prevents circular reference)

        cout << "use_count of Test : " << t.use_count() << endl;     // 1
        cout << "use_count of Sample : " << s.use_count() << endl;   // 1
    }

    cout << "End of scope\n";
    return 0;
}




what types of smart pointers.
how shared pointer is implemented.

⭐ 1. Types of Smart Pointers in C++ (C++11+)
C++ provides three core smart pointers in <memory>:

✅ 1) std::unique_ptr<T>
Exclusive ownership (only one pointer can own the object)
Cannot be copied, only moved
Fastest smart pointer (no reference counting)
Automatically deletes the object when it goes out of scope

Example:
auto p = std::make_unique<int>(10);

✅ 2) std::shared_ptr<T>
Shared (multiple) ownership
Uses a reference-counted control block
Deletes the object when last shared_ptr is destroyed
Slight overhead due to atomic reference count

Example:
auto p1 = std::make_shared<int>(10);
auto p2 = p1;   // count++

✅ 3) std::weak_ptr<T>
Non-owning pointer that refers to an object managed by shared_ptr
Does not increase the reference count
Used to break cyclic references

Example:
std::shared_ptr<int> p = std::make_shared<int>(10);
std::weak_ptr<int> w = p;     // no ownership

⭐ 2. How std::shared_ptr Works Internally
When you write:
auto sp = std::make_shared<int>(10);

The runtime allocates:
🔹 A — The Object
(int) 10
🔹 B — Control Block (Important!)

Contains:
+---------------------------+
| Reference count (strong)  |
| Weak count (weak_ptr)     |
| Pointer to object         |
| Deleter (function pointer)|
+---------------------------+


For example:
shared_count = 1
weak_count = 0
ptr = 0x1234
deleter = default_delete

📌 Control Block Example Diagram
  sp1 ----+
          |
          V
   +--------------+       +---------------------+
   | shared_ptr   |       |      Control Block  |
   |--------------|       |---------------------|
   | ptr -> 0xAA  | ----> | strong_count = 2    |
   | cb  -> 0xCC  |       | weak_count   = 1    |
   +--------------+       | deleter            |
                          +---------------------+
                                       |
                                       V
                                   [int object]

⭐ Reference Counting Rules
| Operation          | strong_count | weak_count |
| ------------------ | ------------ | ---------- |
| copy shared_ptr    | +1           | same       |
| destroy shared_ptr | −1           | same       |
| construct weak_ptr | same         | +1         |
| destroy weak_ptr   | same         | −1         |


⭐ When the object is deleted?
When strong_count becomes 0:
delete managed object


When both strong_count AND weak_count become 0:
delete control block

Weak pointers do NOT keep the object alive.


⭐ 3. Thread Safety
shared_ptr reference counters use atomic operations, so:
✔ Multiple threads can copy/move shared_ptr safely
✔ Access to the managed object itself is not thread-safe

⭐ 4. Why make_shared is better?
auto p = std::make_shared<int>(10);
Allocates one memory block (object + control block) → faster, safer.

Whereas:
std::shared_ptr<int> p(new int(10));
Allocates two blocks → slower, exceptions → dangerous.

⭐ 5. Minimal Implementation of SharedPtr<T>
This is a simplified, educational version:

#include <iostream>
using namespace std;
template <typename T>
class SharedPtr {
    T* ptr;
    size_t* refCount;
  public:
    SharedPtr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}
    // Copy constructor
    SharedPtr(const SharedPtr& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        ++(*refCount);
    }
    // Assignment operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();

            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }
    void release() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }
    ~SharedPtr() {
        release();
    }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    size_t use_count() const { return *refCount; }
};
int main() {
    SharedPtr<int> p1(new int(10));
    cout << p1.use_count() << endl; // 1
    {
        SharedPtr<int> p2 = p1;
        cout << p1.use_count() << endl; // 2
    }
    cout << p1.use_count() << endl; // back to 1
  return 0;
}
/* 
1
2
1
*/

✔ Very close to how real shared_ptr works
✔ Does not implement weak_ptr or control block → kept simple for clarity

⭐ Final Summary
| Smart Pointer | Ownership    | Use Case                             |
| ------------- | ------------ | ------------------------------------ |
| `unique_ptr`  | exclusive    | RAII, resource acquisition, fast     |
| `shared_ptr`  | shared       | shared ownership, reference counting |
| `weak_ptr`    | no ownership | avoid cyclic references, cache       |
