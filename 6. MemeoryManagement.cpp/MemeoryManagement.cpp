memeory management
- smart pointers and their implementations
- how they internaly work ?





Memory Management with Smart Pointers in C++
Smart pointers are a critical feature in C++ (introduced in C++11) that help manage dynamically allocated memory automatically, 
avoiding common issues like memory leaks and dangling pointers. 

They use RAII (Resource Acquisition Is Initialization) to ensure that memory is freed when no longer in use.



There are several types of smart pointers:
std::unique_ptr: A smart pointer that owns a dynamically allocated object and ensures that no other smart pointer can share ownership. 
It cannot be copied, but can be moved.


std::shared_ptr: A smart pointer that allows multiple pointers to share ownership of an object. 
The object is destroyed when the last shared_ptr pointing to it is destroyed or reset.



std::weak_ptr: A non-owning reference to an object managed by std::shared_ptr. 
It does not affect the reference count, thus avoiding circular references.




How Smart Pointers Internally Work:
1. std::unique_ptr
A std::unique_ptr is implemented as a wrapper around a raw pointer. 
It ensures that only one unique_ptr exists at a time that points to a resource. 
When the unique_ptr goes out of scope, it automatically deletes the associated object.


Internally, a std::unique_ptr might look like this:
#include <iostream>
using namespace std;
class MyClass {
  public:
    MyClass() {
        cout << "MyClass Constructor\n";
    }

    ~MyClass() {
        cout << "MyClass Destructor\n";
    }

    void greet() {
        cout << "Hello from MyClass!\n";
    }
};

class UniquePtr {
  private:
    MyClass* ptr;  // Raw pointer

  public:
    // Constructor: Initializes with a raw pointer, default is nullptr
    explicit UniquePtr(MyClass* p = nullptr) : ptr(p) {}

    // Destructor: Automatically deletes the managed object
    ~UniquePtr() {
        delete ptr;
    }

    // Move constructor: Transfers ownership from another UniquePtr
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;  // Make the other UniquePtr null to avoid double-deletion
    }

    // Move assignment operator: Transfers ownership from another UniquePtr
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;  // Deletes current object
            ptr = other.ptr;  // Takes ownership
            other.ptr = nullptr;  // Make the other UniquePtr null
        }
        return *this;
    }

    // Accessor: Allows access to the managed object through the pointer
    MyClass* operator->() {
        return ptr;
    }

    // Dereference operator: Allows dereferencing of the managed object
    MyClass& operator*() {
        return *ptr;
    }

    // Prevent copy constructor (no copying allowed)
    UniquePtr(const UniquePtr&) = delete;

    // Prevent copy assignment operator (no copying allowed)
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Accessor for the raw pointer (no ownership transfer)
    MyClass* get() const {
        return ptr;
    }

    // Releases ownership of the managed object (does not delete it)
    MyClass* release() {
        MyClass* temp = ptr;
        ptr = nullptr;  // Null out the pointer, so it won't be deleted when going out of scope
        return temp;
    }

    // Resets the managed object (deletes the old one and takes ownership of the new one)
    void reset(MyClass* newPtr = nullptr) {
        delete ptr;  // Delete the old object
        ptr = newPtr;  // Take ownership of the new object
    }

    // Check if the UniquePtr is managing a non-null object
    bool isNull() const {
        return ptr == nullptr;
    }
};

int main() {
    // Create a UniquePtr to a MyClass object
    UniquePtr ptr1(new MyClass());
    ptr1->greet();  // Access MyClass' method via unique_ptr

    // Move ownership of ptr1 to ptr2
    UniquePtr ptr2 = move(ptr1);
    cout << "ptr1 isNull: " << ptr1.isNull() << "\n";  // Should be true
    ptr2->greet();  // Access MyClass' method via ptr2

    // Reset ptr2 with a new object
    ptr2.reset(new MyClass());
    ptr2->greet();  // Access the method of the new object

    // Release ownership of the managed object
    MyClass* rawPtr = ptr2.release();  // Now rawPtr is the owner
    cout << "ptr2 isNull: " << ptr2.isNull() << "\n";  // Should be true

    delete rawPtr;  // Manually delete the object, since UniquePtr no longer owns it

    return 0;
}
/*
MyClass Constructor
Hello from MyClass!
ptr1 isNull: 1
Hello from MyClass!
MyClass Constructor
MyClass Destructor
Hello from MyClass!
ptr2 isNull: 1
MyClass Destructor
*/








2. std::shared_ptr

A std::shared_ptr uses reference counting to manage an objects lifetime. 
Internally, it typically uses a control block to store the reference count, 
which keeps track of how many shared_ptrs are pointing to the same object. 

When the last shared_ptr goes out of scope, the object is deleted.
#include <iostream>
#include <atomic>
#include <memory> // For std::cout and std::endl
using namespace std;
template <typename T>
class SharedPtr {
  private:
    T* ptr;
    atomic<int>* ref_count;  // Atomic reference count for thread safety

  public:
    // Constructor: Initializes with a raw pointer, reference count is 1
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(new std::atomic<int>(1)) {}

    // Destructor: Releases the resource when ref_count reaches 0
    ~SharedPtr() {
        release();
    }

    // Copy constructor: Increments the reference count
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    // Copy assignment: Handles the release of old resource and increments ref_count
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    // Release the resource if ref_count reaches 0
    void release() {
        if (--(*ref_count) == 0) {
            delete ptr;         // Delete the managed object
            delete ref_count;   // Delete the reference count object
        }
    }

    // Accessor: Allows access to the managed object via the pointer
    T* operator->() { return ptr; }

    // Dereference operator: Allows dereferencing of the managed object
    T& operator*() { return *ptr; }

    // Get the reference count for testing purposes
    int use_count() const {
        return *ref_count;
    }
};

class MyClass {
public:
    MyClass() {
        cout << "MyClass Constructor\n";
    }

    ~MyClass() {
        cout << "MyClass Destructor\n";
    }

    void greet() {
        cout << "Hello from MyClass!\n";
    }
};

int main() {
    // Create a SharedPtr to a MyClass object
    SharedPtr<MyClass> ptr1(new MyClass());
    ptr1->greet();  // Access MyClass' method via shared_ptr

    cout << "Use count after ptr1 creation: " << ptr1.use_count() << "\n";  // Should be 1

    // Create another SharedPtr (ptr2) pointing to the same object
    SharedPtr<MyClass> ptr2 = ptr1;
    cout << "Use count after ptr2 creation: " << ptr1.use_count() << "\n";  // Should be 2

    ptr2->greet();  // Access MyClass' method via ptr2

    // Create another SharedPtr (ptr3) via assignment
    SharedPtr<MyClass> ptr3;
    ptr3 = ptr2;
    cout << "Use count after ptr3 assignment: " << ptr1.use_count() << "\n";  // Should be 3

    ptr3->greet();  // Access MyClass' method via ptr3

    // At this point, ptr1, ptr2, and ptr3 all share ownership of the same MyClass instance.

    return 0;
}
/*
MyClass Constructor
Hello from MyClass!
Use count after ptr1 creation: 1
Use count after ptr2 creation: 2
Hello from MyClass!
Use count after ptr3 assignment: 3
Hello from MyClass!
MyClass Destructor
*/


In this simplified implementation:
The ref_count is incremented in the copy constructor and copy assignment operator to track shared ownership.
The object is deleted only when the reference count reaches zero.




#include <iostream>   // For std::cout and std::endl
#include <atomic>
#include <memory> 
using namespace std;

class MyClass {
public:
    MyClass() {
        cout << "MyClass Constructor\n";
    }

    ~MyClass() {
        cout << "MyClass Destructor\n";
    }

    void greet() {
        cout << "Hello from MyClass!\n";
    }
};

class SharedPtr {
private:
    MyClass* ptr;
    atomic<int>* ref_count;  // Atomic reference count for thread safety

public:
    // Constructor: Initializes with a raw pointer, reference count is 1
    explicit SharedPtr(MyClass* p = nullptr) : ptr(p), ref_count(new atomic<int>(1)) {}

    // Default constructor (removed in this case as it's not necessary)
    // SharedPtr() : ptr(nullptr), ref_count(new atomic<int>(0)) {}

    // Destructor: Releases the resource when ref_count reaches 0
    ~SharedPtr() {
        release();
    }

    // Copy constructor: Increments the reference count
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    // Copy assignment: Handles the release of old resource and increments ref_count
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    // Release the resource if ref_count reaches 0
    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;         // Delete the managed object
            delete ref_count;   // Delete the reference count object
        }
    }

    // Accessor: Allows access to the managed object via the pointer
    MyClass* operator->() { return ptr; }

    // Dereference operator: Allows dereferencing of the managed object
    MyClass& operator*() { return *ptr; }

    // Get the reference count for testing purposes
    int use_count() const {
        return *ref_count;
    }
};

int main() {
    // Create a SharedPtr to a MyClass object
    SharedPtr ptr1(new MyClass());
    ptr1->greet();  // Access MyClass' method via shared_ptr

    cout << "Use count after ptr1 creation: " << ptr1.use_count() << "\n";  // Should be 1

    // Create another SharedPtr (ptr2) pointing to the same object
    SharedPtr ptr2 = ptr1;
    cout << "Use count after ptr2 creation: " << ptr1.use_count() << "\n";  // Should be 2

    ptr2->greet();  // Access MyClass' method via ptr2

    // Create another SharedPtr (ptr3) via assignment
    SharedPtr ptr3;
    ptr3 = ptr2;
    cout << "Use count after ptr3 assignment: " << ptr1.use_count() << "\n";  // Should be 3

    ptr3->greet();  // Access MyClass' method via ptr3

    // At this point, ptr1, ptr2, and ptr3 all share ownership of the same MyClass instance.

    return 0;
}
/*
MyClass Constructor
Hello from MyClass!
Use count after ptr1 creation: 1
Use count after ptr2 creation: 2
Hello from MyClass!
Use count after ptr3 assignment: 3
Hello from MyClass!
MyClass Destructor
*/




3. std::weak_ptr

A std::weak_ptr does not affect the reference count of the managed object. 
It is used to avoid circular references. It can be "converted" to a std::shared_ptr using lock(), 
which safely checks if the object is still alive (i.e., if any shared_ptr still exists).

#include <iostream>
#include <memory> // For std::shared_ptr, std::weak_ptr, etc.
using namespace std;

template <typename T>
class WeakPtr {
  private:
    weak_ptr<T> ptr;  // std::weak_ptr is used to avoid circular references

  public:
    explicit WeakPtr(shared_ptr<T> p = nullptr) : ptr(p) {}

    // Convert weak_ptr to shared_ptr (if the object is still alive)
    shared_ptr<T> lock() const {
        return ptr.lock();  // Returns a shared_ptr if the object is still alive, nullptr otherwise
    }

    // Optional: Check if the managed object is still alive
    bool expired() const {
        return ptr.expired();
    }
};

class MyClass {
  public:
    MyClass() {
        cout << "MyClass Constructor\n";
    }

    ~MyClass() {
        cout << "MyClass Destructor\n";
    }

    void greet() const {
        cout << "Hello from MyClass!\n";
    }
};

int main() {
    // Create a shared_ptr to manage a MyClass object
    shared_ptr<MyClass> sharedPtr1 = make_shared<MyClass>();

    // Create a weak_ptr that doesn't affect the reference count
    WeakPtr<MyClass> weakPtr1(sharedPtr1);

    // Use the shared_ptr to access the object
    sharedPtr1->greet();  // Output: "Hello from MyClass!"

    // Lock the weak_ptr to get a shared_ptr and use it
    shared_ptr<MyClass> lockedPtr = weakPtr1.lock();
    if (lockedPtr) {
        lockedPtr->greet();  // Output: "Hello from MyClass!"
    } else {
        cout << "Object is expired.\n";
    }

    // Now, let's reset the original shared_ptr
    sharedPtr1.reset();

    // Try to lock again after sharedPtr1 is reset
    lockedPtr = weakPtr1.lock();
    if (lockedPtr) {
        lockedPtr->greet();  // This won't run, because the object has been destroyed
    } else {
        cout << "Object is expired.\n";  // Output: "Object is expired."
    }

    return 0;
}
/*
MyClass Constructor
Hello from MyClass!
Hello from MyClass!
Hello from MyClass!
MyClass Destructor
*/






#include <iostream>
#include <memory> // For std::shared_ptr, std::weak_ptr, etc.

using namespace std;

class MyClass {  // Declare MyClass first
public:
    MyClass() {
        cout << "MyClass Constructor\n";
    }

    ~MyClass() {
        cout << "MyClass Destructor\n";
    }

    void greet() const {
        cout << "Hello from MyClass!\n";
    }
};

class WeakPtr {
private:
    weak_ptr<MyClass> ptr;  // Use weak_ptr of MyClass

public:
    // Constructor: Accept a shared_ptr, which is converted to a weak_ptr
    explicit WeakPtr(shared_ptr<MyClass> p = nullptr) : ptr(p) {}

    // Convert weak_ptr to shared_ptr (if the object is still alive)
    shared_ptr<MyClass> lock() const {
        return ptr.lock();  // Returns a shared_ptr if the object is still alive, nullptr otherwise
    }

    // Optional: Check if the managed object is still alive
    bool expired() const {
        return ptr.expired();
    }
};

int main() {
    // Create a shared_ptr to manage a MyClass object
    shared_ptr<MyClass> sharedPtr1 = make_shared<MyClass>();

    // Create a weak_ptr that doesn't affect the reference count
    WeakPtr weakPtr1(sharedPtr1);

    // Use the shared_ptr to access the object
    sharedPtr1->greet();  // Output: "Hello from MyClass!"

    // Lock the weak_ptr to get a shared_ptr and use it
    shared_ptr<MyClass> lockedPtr = weakPtr1.lock();
    if (lockedPtr) {
        lockedPtr->greet();  // Output: "Hello from MyClass!"
    } else {
        cout << "Object is expired.\n";
    }

    // Now, let's reset the original shared_ptr
    sharedPtr1.reset();

    // Try to lock again after sharedPtr1 is reset
    lockedPtr = weakPtr1.lock();
    if (lockedPtr) {
        lockedPtr->greet();  // This won't run, because the object has been destroyed
    } else {
        cout << "Object is expired.\n";  // Output: "Object is expired."
    }

    return 0;
}
/*
MyClass Constructor
Hello from MyClass!
Hello from MyClass!
Hello from MyClass!
MyClass Destructor
*/









Full Example with std::unique_ptr, std::shared_ptr, and std::weak_ptr:
#include <iostream>
#include <memory>
#include <vector>
#include <atomic>

// Unique Pointer Example
void uniquePtrExample() {
    std::cout << "Unique Pointer Example:\n";
    std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);
    std::cout << "Value from unique pointer: " << *uniquePtr << std::endl;

    // Transfer ownership
    std::unique_ptr<int> anotherPtr = std::move(uniquePtr);
    if (uniquePtr == nullptr) {
        std::cout << "uniquePtr is now null after move." << std::endl;
    }
    std::cout << "Value from anotherPtr: " << *anotherPtr << std::endl;
}

// Shared Pointer Example
void sharedPtrExample() {
    std::cout << "\nShared Pointer Example:\n";
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(100);
    std::shared_ptr<int> sharedPtr2 = sharedPtr1;  // Shared ownership

    std::cout << "Shared Pointer 1: " << *sharedPtr1 << std::endl;
    std::cout << "Shared Pointer 2: " << *sharedPtr2 << std::endl;

    std::cout << "Reference count: " << sharedPtr1.use_count() << std::endl;  // Reference count is 2

    sharedPtr1.reset();  // Release sharedPtr1
    std::cout << "After reset, reference count: " << sharedPtr2.use_count() << std::endl;  // Reference count is 1
}

// Weak Pointer Example
void weakPtrExample() {
    std::cout << "\nWeak Pointer Example:\n";
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(200);
    std::weak_ptr<int> weakPtr = sharedPtr;  // Weak reference

    std::cout << "Weak pointer created.\n";
    
    // Check if the weak pointer is valid
    if (auto tempPtr = weakPtr.lock()) {
        std::cout << "Weak Pointer is valid, value: " << *tempPtr << std::endl;
    } else {
        std::cout << "Weak pointer is expired.\n";
    }

    sharedPtr.reset();  // Reset sharedPtr, which destroys the object

    // After reset, weakPtr should be expired
    if (auto tempPtr = weakPtr.lock()) {
        std::cout << "Weak Pointer is valid, value: " << *tempPtr << std::endl;
    } else {
        std::cout << "Weak pointer is expired.\n";
    }
}

int main() {
    uniquePtrExample();
    sharedPtrExample();
    weakPtrExample();

    return 0;
}
/*
Unique Pointer Example:
Value from unique pointer: 42
uniquePtr is now null after move.
Value from anotherPtr: 42

Shared Pointer Example:
Shared Pointer 1: 100
Shared Pointer 2: 100
Reference count: 2
After reset, reference count: 1

Weak Pointer Example:
Weak pointer created.
Weak Pointer is valid, value: 200
Weak pointer is expired.
*/

Explanation of Code:
Unique Pointer Example (std::unique_ptr):
std::unique_ptr<int> uniquePtr = std::make_unique<int>(42); creates a unique_ptr that owns an integer.
Ownership is transferred using std::move to anotherPtr, and uniquePtr becomes nullptr.



Shared Pointer Example (std::shared_ptr):
std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(100); creates a shared_ptr that owns an integer.
sharedPtr2 is a copy of sharedPtr1, meaning both share ownership of the integer.
The reference count can be accessed via use_count(), and when sharedPtr1 is reset, the object is still accessible via sharedPtr2.



Weak Pointer Example (std::weak_ptr):
A std::weak_ptr is created from a std::shared_ptr to avoid circular references. It doesn’t increase the reference count.
weakPtr.lock() attempts to "promote" the weak_ptr to a shared_ptr (if the object is still alive).
After sharedPtr is reset, the weak_ptr is considered expired.



Key Takeaways:
std::unique_ptr is used for exclusive ownership. It automatically deletes the object when it goes out of scope.
std::shared_ptr allows shared ownership of an object, and the object is deleted only when the last shared_ptr goes out of scope.
std::weak_ptr is used to avoid circular references with std::shared_ptr and does not affect the reference count of the object.
















In C++ std::shared_ptr, the control block is an internal structure allocated once 
per managed object.
Although implementations differ, it always contains approximately four essential 
pieces of information.

the four components of the shared_ptr control block:
--> Managed object pointer
--> Strong count
--> Weak count
--> Deleter + Allocator

Most explanations say the control block stores four things:
1. Pointer to the managed object
--> Actually stored inside the control block (for make_shared) or 
    separately (if constructed from raw pointer), but logically part of what 
    the control block manages.

2. Strong reference count (use count)
--> Number of active shared_ptr instances.

3. Weak reference count
--> Number of active weak_ptr instances
--> Also includes +1 while strong count > 0 (implementation detail).

4. Deleter and Allocator (type-erased)
--> The custom deleter function used to destroy the object.
--> Optionally a custom allocator for deallocating the control block itself.


#include <iostream>
#include <memory>

struct MyObject {
    MyObject()  { std::cout << "MyObject constructed\n"; }
    ~MyObject() { std::cout << "MyObject destroyed\n"; }
};

// Custom deleter to show control block stores it
struct MyDeleter {
    void operator()(MyObject* p) const {
        std::cout << "[Custom Deleter] Destroying MyObject\n";
        delete p;
    }
};

int main() {
    std::cout << "Creating shared_ptr...\n";

    // Create shared_ptr with custom deleter
    std::shared_ptr<MyObject> sp1(new MyObject, MyDeleter());

    // Control block: strong=1, weak=0  
    std::cout << "sp1.use_count() = " << sp1.use_count() << "\n";

    {
        // Creating another shared_ptr from sp1 increases strong count
        std::shared_ptr<MyObject> sp2 = sp1;
        std::cout << "After creating sp2, use_count = "
                  << sp1.use_count() << "\n";

        // Creating weak_ptr increases weak count
        std::weak_ptr<MyObject> wp = sp1;
        std::cout << "Created weak_ptr.\n";
        std::cout << "sp1.use_count() (strong count) = "
                  << sp1.use_count() << "\n";
        std::cout << "wp.use_count() (still strong count) = "
                  << wp.use_count() << "\n";

        // Weak count is not directly accessible, but wp exists
        std::cout << "wp.expired() = " << std::boolalpha
                  << wp.expired() << "\n";
    }

    // At this point, sp2 & wp are out of scope:
    // strong count decreased to 1
    std::cout << "After sp2 & wp destroyed, use_count = "
              << sp1.use_count() << "\n";

    std::cout << "Resetting last shared_ptr...\n";
    sp1.reset();  // Now the managed object should be destroyed

    std::cout << "Program end.\n";
}
/*
Creating shared_ptr...
MyObject constructed
sp1.use_count() = 1
After creating sp2, use_count = 2
Created weak_ptr.
sp1.use_count() (strong count) = 2
wp.use_count() (still strong count) = 2
wp.expired() = false
After sp2 & wp destroyed, use_count = 1
Resetting last shared_ptr...
[Custom Deleter] Destroying MyObject
MyObject destroyed
Program end.
*/


Explanation of the Four Control-Block Components Using the Program
1. Managed Object Pointer
Inside the control block, the shared_ptr stores:
--> pointer to MyObject

When we do:
std::shared_ptr<MyObject> sp1(new MyObject, MyDeleter());


memory layout (conceptually):
+------------------+
|  Control block   |
|  - ptr to object |
|  - strong count  |
|  - weak count    |
|  - deleter       |
+------------------+
          |
          v
 +-------------------+
 |   MyObject        |
 +-------------------+

2. Strong Count (use count)
Whenever you copy a shared_ptr, the control block increments
the strong count:

std::shared_ptr<MyObject> sp2 = sp1;

Output:
After creating sp2, use_count = 2

The object is destroyed only when strong count → 0.



3. Weak Count
Weak pointers do NOT increase the strong count.
But they do increase the weak reference count inside the 
control block.

std::weak_ptr<MyObject> wp = sp1;
Weak count is internal; we check state via:

wp.expired()
Later, when strong count drops to 0, 
the object is destroyed but the control block 
stays alive as long as weak_count > 0.




4. Deleter + Allocator
We provide a custom deleter:

struct MyDeleter {
    void operator()(MyObject* p) const {
        std::cout << "[Custom Deleter] Destroying MyObject\n";
        delete p;
    }
};


The control block stores this deleter, so it knows how to delete the object.

When the last shared_ptr is destroyed:

sp1.reset();


Output:
[Custom Deleter] Destroying MyObject
This proves the deleter lives inside the control block.







In C++ smart pointers, a std::shared_ptr maintains:
--> ref count (use_count) → number of shared_ptr objects owning the same resource
--> weak count → number of weak_ptr observing the same resource (but not owning it)

When the ref count = 1 and weak count = 1:
--> One shared_ptr owns the object
--> One weak_ptr refers to it (but does NOT extend its lifetime)


Below is a simple program demonstrating this.
✅ Example Program: shared_ptr and weak_ptr reference counts
#include <iostream>
#include <memory>
using namespace std;
int main() {

    // Create shared_ptr (ref count becomes 1)
    shared_ptr<int> sp = make_shared<int>(10);

    cout << "After creating shared_ptr:\n";
    cout << "use_count = " << sp.use_count() << endl;  // 1

    // Create weak_ptr from shared_ptr
    weak_ptr<int> wp = sp;

    cout << "\nAfter creating weak_ptr:\n";
    cout << "shared_ptr use_count = " << sp.use_count() << endl; // still 1
    cout << "weak_ptr expired? = " << (wp.expired() ? "yes" : "no") << endl;

    // Demonstrate locking weak_ptr
    if (auto temp = wp.lock()) {
        cout << "\nweak_ptr.lock() succeeded, value = " << *temp << endl;
        cout << "use_count (temp increases count temporarily) = " << temp.use_count() << endl;
    }

    // Reset shared_ptr (ref count becomes 0 → object deleted)
    sp.reset();

    cout << "\nAfter resetting shared_ptr:\n";
    cout << "shared_ptr use_count = " << sp.use_count() << endl;  // 0
    cout << "weak_ptr expired? = " << (wp.expired() ? "yes" : "no") << endl;

    return 0;
}

Explanation
✔ Step 1: Create shared_ptr
shared_ptr<int> sp = make_shared<int>(10);
--> ref count = 1
--> weak count = 0

✔ Step 2: Create weak_ptr
weak_ptr<int> wp = sp;
--> ref count = 1 (still one owner)
--> weak count = 1
This matches your case:
👉 ref count = 1, weak count = 1

✔ Step 3: weak_ptr.lock()
auto temp = wp.lock();
--> Creates a temporary shared_ptr
--> ref count increases to 2 temporarily
--> When temp goes out of scope → back to 1

✔ Step 4: Reset the shared_ptr
sp.reset();
--> ref count becomes 0, object is destroyed
--> weak_ptr sees expired resource → expired() = true










