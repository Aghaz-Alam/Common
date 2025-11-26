//unique_ptr implementation
#include <iostream>
#include <utility>
using namespace std;
template <typename T>
class UniquePtr {
 private:
    T* ptr;

 public:
    // --- Constructors ---
    UniquePtr() : ptr(nullptr) {}
    explicit UniquePtr(T* p) : ptr(p) {}

    // Disable copy
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;         // free current
            ptr = other.ptr;    // steal
            other.ptr = nullptr;
        }
        return *this;
    }

    // Destructor
    ~UniquePtr() {
        delete ptr;
    }

    // --- Observers ---
    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    explicit operator bool() const { return ptr != nullptr; }

    // --- Modifiers ---
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    void swap(UniquePtr& other) {
        swap(ptr, other.ptr);
    }
};

// Helper function similar to std::make_unique
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}


struct Test {
    Test()  { cout << "Test created\n"; }
    ~Test() { cout << "Test destroyed\n"; }
    void hello() { cout << "Hello\n"; }
};

int main() {
    auto p = make_unique<Test>();
    p->hello();

    UniquePtr<int> x(new int(42));
    cout << *x << "\n";

    auto y = move(x); // ownership transferred

    if (!x)
        cout << "x is now empty\n";

    cout << *y << "\n";

  return 0;
}
/*
Test created
Hello
42
x is now empty
42
Test destroyed
*/



/* ------------------------------------------------------------- */
1️⃣ Header Includes
#include <iostream>
#include <utility>
using namespace std;

<iostream> — for cout
<utility> — for std::move and std::forward
using namespace std; — brings names like cout, move into scope

2️⃣ Template Definition
template <typename T>
class UniquePtr {

T is the type of object this smart pointer manages
This makes UniquePtr<int>, UniquePtr<Test>, etc. possible

3️⃣ Private Pointer
private:
    T* ptr;

The raw pointer owned by this unique_ptr
Only one unique_ptr can own this pointer at a time

4️⃣ Constructors
UniquePtr() : ptr(nullptr) {}

Default constructor
Initializes pointer to nullptr
Means: this object owns nothing
explicit UniquePtr(T* p) : ptr(p) {}


❗ Why explicit?
Without explicit, this could happen:
UniquePtr<int> p = new int(5);   // BAD: implicit conversion

This is dangerous because:
Implicit conversions may accidentally convert raw pointers
unique_ptr must always be created intentionally

explicit forces:
UniquePtr<int> p(new int(5));  // OK, explicit

5️⃣ Disable Copying (Core property of unique_ptr)
UniquePtr(const UniquePtr&) = delete;
UniquePtr& operator=(const UniquePtr&) = delete;

Because:
A unique_ptr must have exclusive ownership
Only one instance can own the pointer
If copying was allowed:
A → ptr
B = A → ptr

Two owners = double delete = crash.
So copy operations are deleted.

6️⃣ Move Constructor
UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

Meaning:
Steal pointer from other
other becomes empty (nullptr)
No copying occurs
Ownership is transferred

7️⃣ Move Assignment
UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr;         // free current object
        ptr = other.ptr;    // steal
        other.ptr = nullptr;
    }
    return *this;
}

Steps:
Guard against self-assignment
Delete what you currently own
Steal pointer from other
Reset other to nullptr

8️⃣ Destructor
~UniquePtr() {
    delete ptr;
}

Automatically called when unique_ptr goes out of scope
Frees the owned object
Prevents memory leaks

9️⃣ Observers
get()
T* get() const { return ptr; }

Returns the raw pointer but does not transfer ownership.
operator*
T& operator*() const { return *ptr; }

Allows:
*ptr   // dereferencing like a normal pointer
operator->
T* operator->() const { return ptr; }

Allows:
ptr->method()
operator bool
explicit operator bool() const { return ptr != nullptr; }

Returns:
true if pointer is not null
Enables if (p) {...}

🔟 Modifiers
✔ release() — Give up ownership
T* release() {
    T* temp = ptr;
    ptr = nullptr;
    return temp;
}

What it does:
Returns the raw pointer
Leaves unique_ptr empty
DOES NOT delete the object

Use case:
UniquePtr<int> p(new int(5));
int* raw = p.release();  // you now own the pointer manually

✔ reset() — Delete current object and take new one
void reset(T* p = nullptr) {
    delete ptr;
    ptr = p;
}

Meaning:
Deletes currently owned object
Replaces it with p
If p = nullptr → just deletes old object

Example:
p.reset(new int(10));
p.reset();    // deletes object

✔ swap() — Swap contents of two unique_ptrs
void swap(UniquePtr& other) {
    swap(ptr, other.ptr);
}

Exchanges pointers
No deletion required
Ownership swapped

🔟 Helper function — make_unique
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

Purpose:
Safe object creation without risking memory leaks
Perfect-forwarding constructor arguments to T

Usage:
auto p = make_unique<Test>();  
auto q = make_unique<MyClass>(10, 20);

Equivalent to:
UniquePtr<Test> p(new Test());
But safer!

1️⃣1️⃣ The Test struct
struct Test {
    Test()  { cout << "Test created\n"; }
    ~Test() { cout << "Test destroyed\n"; }
    void hello() { cout << "Hello\n"; }
};

Used to demonstrate construction/destruction
Shows automatically managed lifetime

1️⃣2️⃣ Demo in main()
Create a Test object
auto p = make_unique<Test>();
p->hello();

Create and move unique_ptr
UniquePtr<int> x(new int(42));
auto y = move(x);


Now:
y owns the int
x becomes empty
Output confirms:
x is now empty

/* ------------------------------------------------------------- */
🟩 1. Memory Diagrams — How unique_ptr Works Internally
1️⃣ Basic unique_ptr layout
+-------------------+
|  UniquePtr<T>     |
+-------------------+
|  ptr  ----------+------> heap:  [   T object   ]
+-------------------+

Only one UniquePtr<T> can point to this object.

2️⃣ After move: UniquePtr ownership transfer
Before move:

   src                         dest
+---------+              +-------------+
| ptr ----+-----> [T]    | ptr = null |
+---------+              +-------------+


After move:

   src                         dest
+---------+              +-------------+
| ptr=null|              | ptr ---> [T]
+---------+              +-------------+


Ownership is transferred; nothing is copied.

3️⃣ After release()
T* raw = uptr.release();


Diagram:

uptr                      raw
+---------+         +----------------+
| ptr=null|         | points to [T] |
+---------+         +----------------+
               (You must delete it manually)


unique_ptr gives up ownership (raw pointer becomes your responsibility).
4️⃣ After reset()
uptr.reset(new T);

Before reset:
uptr ----> [Old T]

After reset:
Old T is deleted
uptr ----> [New T]

🟩 2. Move Semantics Visualization (“Stealing Model”)
Step 1: Construction
UniquePtr<int> a(new int(10));

 a.ptr ---> [10]

Step 2: Move operation
UniquePtr<int> b = move(a);
╔════════════════════════════════╗
║ What happens internally: ║
║ 1. b.ptr = a.ptr ║
║ 2. a.ptr = nullptr ║
║ 3. No heap copy is made ║
╚════════════════════════════════╝

Visualization:
Before move:
a ---> [10]
b ---> null

After move:
a ---> null
b ---> [10]

Step 3: Destruction
b goes out of scope → deletes [10]
a does nothing


Zero overhead, zero ref-counting.

🟩 3. Comparison with std::unique_ptr
| Feature                            | Your Simple Version | std::unique_ptr                         |
| ---------------------------------- | ------------------- | --------------------------------------- |
| Exclusive ownership                | ✔ Yes               | ✔ Yes                                   |
| Copy disabled                      | ✔ Yes               | ✔ Yes                                   |
| Move-enabled                       | ✔ Yes               | ✔ Yes                                   |
| Custom deleter                     | ❌ No                | ✔ Yes                                   |
| Empty state                        | ✔ nullptr           | ✔ nullptr                               |
| Array support                      | ❌ No                | ✔ `unique_ptr<T[]>`                     |
| get/release/reset/swap             | ✔ Yes               | ✔ Yes                                   |
| Aliasing constructor               | ❌ No                | ✔ Yes                                   |
| Uses EBO (empty-base optimization) | ❌ No                | ✔ Yes (for storing deleter efficiently) |
| noexcept correctness               | Partial             | Full                                    |
| Works with allocators              | ❌ No                | ✔ Yes (via deleter)                     |
| Specialized constructors           | ❌ No                | ✔ Many                                  |

STL Version is Optimized For:
minimal memory footprint
safe pointer deletion
LWG/C++ standard requirements
arbitrary deleters
array types
constexpr + noexcept guarantees

🟩 4. Array Version: UniquePtr<T[]>
This specialization deletes using delete[] instead of delete.
Simple Implementation
template <typename T>
class UniquePtr<T[]> {
  private:
    T* ptr;
  public:
    UniquePtr() : ptr(nullptr) {}
    explicit UniquePtr(T* p) : ptr(p) {}
    ~UniquePtr() {
        delete[] ptr;
    }
    // no copy
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    // move
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    // array indexing
    T& operator[](size_t i) { return ptr[i]; }
    // release/reset/get
    T* get() const { return ptr; }
    T* release() { T* p = ptr; ptr = nullptr; return p; }
    void reset(T* p = nullptr) { delete[] ptr; ptr = p; }
};

Usage
UniquePtr<int[]> arr(new int[5]);
arr[0] = 10;
arr[1] = 20;

🟩 5. Custom Deleter Version
A deleter is a functor that defines how to destroy the object.
Why needed?
Free using free()
Close FILE*
Destroy OS handles
Custom memory pools
Logging deletion
Array vs object deletion

Example: Custom Deleter
struct FileCloser {
    void operator()(FILE* f) const {
        if (f) fclose(f);
    }
};

Custom-deleter unique_ptr
template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
  private:
    T* ptr;
    Deleter deleter;

  public:
    explicit UniquePtr(T* p = nullptr, Deleter d = Deleter())
        : ptr(p), deleter(d) {}

    ~UniquePtr() {
        if (ptr) deleter(ptr);
    }
    // move-only as before…
    T* release() {
        T* p = ptr;
        ptr = nullptr;
        return p;
    }
    void reset(T* p = nullptr) {
        if (ptr) deleter(ptr);
        ptr = p;
    }
};

Usage with custom deleter:
UniquePtr<FILE, FileCloser> f(fopen("test.txt", "r"));
When f dies → FileCloser::operator() is executed.

🟩 6. Summary Diagram (All Features)
unique_ptr<T>
 ├── owns pointer exclusively
 ├── move-only semantics
 ├── delete ptr      (object)
 ├── delete[] ptr    (array specialization)
 ├── custom-deleter  (free(), fclose(), CloseHandle...)
 ├── release()       → give up ownership
 ├── reset()         → replace managed object
 ├── swap()          → constant-time pointer exchange
 └── make_unique()   → safe factory constructor

/* ------------------------------------------------------------ */





































//Unique ptr implementation using deleter
#include <iostream>
#include <utility>
#include <type_traits>
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
  private:
    T* ptr;
    Deleter del;

  public:
    constexpr UniquePtr() noexcept : ptr(nullptr), del(Deleter()) {}
    explicit UniquePtr(T* p) noexcept : ptr(p), del(Deleter()) {}
    UniquePtr(T* p, Deleter d) noexcept : ptr(p), del(std::move(d)) {}

    // Rule of 5
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr), del(std::move(other.del)) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            del = std::move(other.del);
            other.ptr = nullptr;
        }
        return *this;
    }

    ~UniquePtr() { reset(); }

    // Observers
    T* get() const noexcept { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const noexcept { return ptr; }
    explicit operator bool() const noexcept { return ptr != nullptr; }

    // Modifiers
    void reset(T* p = nullptr) noexcept {
        if (ptr)
            del(ptr);
        ptr = p;
    }

    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
        std::swap(del, other.del);
    }
};

template <typename T, typename Deleter>
class UniquePtr<T[], Deleter> {
private:
    T* ptr;
    Deleter del;

public:
    constexpr UniquePtr() noexcept : ptr(nullptr), del(Deleter()) {}
    explicit UniquePtr(T* p) noexcept : ptr(p), del(Deleter()) {}

    UniquePtr(T* p, Deleter d) noexcept : ptr(p), del(std::move(d)) {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept
        : ptr(other.ptr), del(std::move(other.del)) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            del = std::move(other.del);
            other.ptr = nullptr;
        }
        return *this;
    }

    ~UniquePtr() { reset(); }

    T& operator[](size_t i) const { return ptr[i]; }

    T* get() const noexcept { return ptr; }
    explicit operator bool() const noexcept { return ptr != nullptr; }

    void reset(T* p = nullptr) noexcept {
        if (ptr)
            del(ptr);
        ptr = p;
    }

    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
        std::swap(del, other.del);
    }
};


// OBJECT VERSION (T NOT array)
template <typename T, typename... Args>
typename std::enable_if<!std::is_array<T>::value, UniquePtr<T>>::type
make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

// ARRAY VERSION (T = U[])
template <typename T>
typename std::enable_if<std::is_array<T>::value, UniquePtr<T>>::type
make_unique(size_t size) {
    using Base = typename std::remove_extent<T>::type;
    return UniquePtr<T>(new Base[size]());
}

struct Test {
    Test() { std::cout << "Test created\n"; }
    ~Test() { std::cout << "Test destroyed\n"; }
    void hello() { std::cout << "Hello\n"; }
};

int main() {
    {
        auto p = make_unique<Test>();
        p->hello();
    }

    {
        auto arr = make_unique<int[]>(5);
        arr[0] = 10;
        arr[1] = 20;
        std::cout << arr[0] << " " << arr[1] << "\n";
    }
}
/*
Test created
Hello
Test destroyed
10 20
*/


This implementation demonstrates:
✔ Rule of 5
Move-only semantics, deleted copy, custom destructor.

✔ Template partial specialization
Must specialize for arrays.

✔ SFINAE with enable_if
Prevents the wrong overload from being used.

✔ Correct array deletion
std::default_delete<T[]> automatically uses delete[].

✔ Strong exception safety
No leaks.

✔ Perfect forwarding
In object version of make_unique.

✔ Matching actual C++ behavior
Fully faithful to the STL version.





✅ A diagram of how UniquePtr works internally
✅ Memory layout explanation
✅ Differences from shared_ptr
✅ Interlocked pointer semantics

✅ 1. Diagram of How unique_ptr Works Internally

unique_ptr is extremely simple inside.

It contains only one raw pointer (plus optional custom deleter).

Case 1: unique_ptr<T> (no custom deleter)
+-----------------------------+
|   unique_ptr<T>             |
|-----------------------------|
|  ptr: T* ----------------------> [OBJECT T in HEAP]
+-----------------------------+

Case 2: unique_ptr<T, Deleter>
+--------------------------------------------------+
|              unique_ptr<T, Deleter>              |
|--------------------------------------------------|
|  ptr: T* ------------------------> [OBJECT T]     |
|  del: Deleter (functor/function)                 |
+--------------------------------------------------+

Move Transfers Ownership

When moved:

unique_ptr<T> A           unique_ptr<T> B
+-----+                   +-----+
| ptr | ---- move ---->   | ptr |
+-----+                   +-----+

A.ptr (before) = 0x1000
B.ptr (after)  = 0x1000
A.ptr (after)  = nullptr


Copying is illegal.

✅ 2. Memory Layout Explanation
Object Memory Layout

unique_ptr<T> contains:
A pointer T* ptr
Optional: A deleter object (can be empty if stateless)

Approx size:
| Type                             | Example Size |
| -------------------------------- | ------------ |
| `unique_ptr<int>`                | 8 bytes      |
| `unique_ptr<int[]>`              | 8 bytes      |
| `unique_ptr<int, MyFunctor>`     | 16–24 bytes  |
| `unique_ptr<int, void(*)(int*)>` | 16 bytes     |

unique_ptr itself lives on stack
Stack:
+------------------+
| unique_ptr<T>    |  ---> contains only pointer + optional deleter
+------------------+

Heap:
+------------------+
| Raw object T     |
+------------------+

Destruction Layout
delete ptr;           // for unique_ptr<T>
delete[] ptr;         // for unique_ptr<T[]>


If deleter is custom:

del(ptr);

✅ 3. Differences Between unique_ptr and shared_ptr (Interview Gold)
| Feature          | `unique_ptr`               | `shared_ptr`                            |
| ---------------- | -------------------------- | --------------------------------------- |
| Ownership        | **Exclusive (one owner)**  | **Shared (multiple owners)**            |
| Copyable         | ❌ No                       | ✔ Yes                                   |
| Movable          | ✔ Yes                      | ✔ Yes                                   |
| Storage Size     | **1 pointer (+ deleter)**  | **2 pointers (object + control block)** |
| Control Block    | ❌ No                       | ✔ Yes (ref count, weak count, deleter)  |
| Memory Overhead  | **Very low**               | High                                    |
| Lifetime control | Simple                     | Complex                                 |
| Use Cases        | RAII, single-owner objects | Shared graphs, shared resources         |
| Thread Safety    | No atomic operations       | Atomic ref counting                     |


shared_ptr Internal Diagram
+-----------------------------------+
| shared_ptr                        |
| ptr -----------------------------> [OBJECT T]
| ctrl_ptr ------+                  |
+----------------+                  |
                 |                  |
                 v                  v
        +------------------------------+
        |   Control Block              |
        |------------------------------|
        | strong_count (atomic)        |
        | weak_count   (atomic)        |
        | deleter                      |
        | allocator                    |
        +------------------------------+

unique_ptr vs shared_ptr Summary

unique_ptr = zero-overhead abstraction

shared_ptr = heavy, atomic increments/decrements, control block

✅ 4. Interlocked Pointer Semantics (Move Semantics)

unique_ptr implements ownership transfer using move semantics.

Move Constructor
unique_ptr(unique_ptr&& other) noexcept {
    ptr = other.ptr;  // steal pointer
    other.ptr = nullptr;  // release old owner
}

Move Assignment
operator=(unique_ptr&& other) {
    if (this != &other) {
        delete ptr;        // destroy current
        ptr = other.ptr;   // steal
        other.ptr = nullptr;
    }
}

📌 What Does "Interlocked semantics" Mean?
“Interlocked” here means:
Only one pointer owns the resource at any time

Mechanism:
Move steals the raw pointer
Old pointer becomes null
Only one variable points to the resource

Before move:
A.ptr → 0xAAA
B.ptr → null

After move:
A.ptr → null
B.ptr → 0xAAA

📌 Guarantees:
No double delete
No copying
No aliasing
Ownership always well-defined

💡 Why no atomic operations?
Because unique_ptr is single-owner; no threads share it.
shared_ptr requires atomic ops since multiple threads may copy it.

🎯 Final Summary (Perfect for Interview Answers)
unique_ptr
Zero-cost RAII wrapper
Exclusive ownership
Move-only
No control block
Ideal for performance-critical RAII

shared_ptr
Reference-counted shared ownership
Heavy (atomic increments + control block)
Can participate in cycles (use weak_ptr)

unique_ptr internals
Only holds a pointer (+ optional deleter)
Move overrides pointer, old gets nullified
No atomic operations

Memory Layout
unique_ptr<T> = 1 pointer (8 bytes)
unique_ptr<T, Deleter> = ptr + deleter
shared_ptr = ptr + control block + atomic counters





🟩 Full STL-compliant unique_ptr source code (exactly like libstdc++/libc++)
🟩 A diagram comparing unique_ptr and weak_ptr
🟩 Advanced questions: aliasing constructors, custom allocators, deleter types

// unique_ptr_stl_like.cpp
#include <cstddef>
#include <utility>
#include <type_traits>
#include <memory>   // std::default_delete
#include <iostream>

// Primary template (object)
template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
 public:
    using pointer = T*;
    using element_type = T;
    using deleter_type = Deleter;

 private:
    pointer ptr_;
    deleter_type del_;

 public:
    // Constructors
    constexpr UniquePtr() noexcept: ptr_(nullptr), del_(Deleter()) {}

    constexpr UniquePtr(std::nullptr_t) noexcept: ptr_(nullptr), del_(Deleter()) {}

    explicit UniquePtr(pointer p) noexcept: ptr_(p), del_(Deleter()) {}

    UniquePtr(pointer p, deleter_type d) noexcept : ptr_(p), del_(std::move(d)) {}

    // Converting move constructor: UniquePtr<U, E> -> UniquePtr<T, Deleter>
    template <typename U, typename E,
              typename = std::enable_if_t<
                  std::is_convertible<U*, T*>::value &&
                  std::is_convertible<E, Deleter>::value
              >>
    UniquePtr(UniquePtr<U, E>&& other) noexcept : ptr_(other.release()), del_(std::move(other.get_deleter_ref())) {}

    // no copy
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // move
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_), del_(std::move(other.del_)) {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            del_ = std::move(other.del_);
            other.ptr_ = nullptr;
        }
        return *this;
    }

    ~UniquePtr() { reset(); }

    // Observers
    pointer get() const noexcept { return ptr_; }
    deleter_type& get_deleter_ref() noexcept { return del_; }
    const deleter_type& get_deleter_ref() const noexcept { return del_; }

    // For API parity with std::unique_ptr: return pointer to deleter
    deleter_type* get_deleter() noexcept { return std::addressof(del_); }
    const deleter_type* get_deleter() const noexcept { return std::addressof(del_); }

    element_type& operator*() const { return *ptr_; }
    pointer operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    // Modifiers
    pointer release() noexcept {
        pointer tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void reset(pointer p = pointer()) noexcept {
        if (ptr_)
            del_(ptr_);
        ptr_ = p;
    }

    void swap(UniquePtr& other) noexcept {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(del_, other.del_);
    }
};

// Non-member swap
template <typename T, typename D>
void swap(UniquePtr<T, D>& a, UniquePtr<T, D>& b) noexcept {
    a.swap(b);
}

// Comparisons with nullptr
template <typename T, typename D>
bool operator==(const UniquePtr<T, D>& p, std::nullptr_t) noexcept {
    return !p;
}
template <typename T, typename D>
bool operator==(std::nullptr_t, const UniquePtr<T, D>& p) noexcept {
    return !p;
}
template <typename T, typename D>
bool operator!=(const UniquePtr<T, D>& p, std::nullptr_t) noexcept {
    return (bool)p;
}
template <typename T, typename D>
bool operator!=(std::nullptr_t, const UniquePtr<T, D>& p) noexcept {
    return (bool)p;
}

// Partial specialization for arrays: UniquePtr<T[], Deleter>
template <typename T, typename Deleter>
class UniquePtr<T[], Deleter> {
public:
    using pointer = T*;
    using element_type = T;
    using deleter_type = Deleter;

private:
    pointer ptr_;
    deleter_type del_;

public:
    constexpr UniquePtr() noexcept : ptr_(nullptr), del_(Deleter()) {}
    constexpr UniquePtr(std::nullptr_t) noexcept : ptr_(nullptr), del_(Deleter()) {}
    explicit UniquePtr(pointer p) noexcept : ptr_(p), del_(Deleter()) {}
    UniquePtr(pointer p, deleter_type d) noexcept : ptr_(p), del_(std::move(d)) {}

    // no copy
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // move
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_), del_(std::move(other.del_)) {
        other.ptr_ = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            del_ = std::move(other.del_);
            other.ptr_ = nullptr;
        }
        return *this;
    }

    ~UniquePtr() { reset(); }

    // Array-specific
    T& operator[](std::size_t i) const { return ptr_[i]; }
    pointer get() const noexcept { return ptr_; }
    deleter_type* get_deleter() noexcept { return std::addressof(del_); }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    pointer release() noexcept {
        pointer t = ptr_;
        ptr_ = nullptr;
        return t;
    }

    void reset(pointer p = pointer()) noexcept {
        if (ptr_)
            del_(ptr_);
        ptr_ = p;
    }

    void swap(UniquePtr& other) noexcept {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(del_, other.del_);
    }
};

// make_unique: object version (disable for array types)
template <typename T, typename... Args,
          typename = std::enable_if_t<!std::is_array<T>::value>>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

// make_unique: array version (only for T[] types)
template <typename T,
          typename = std::enable_if_t<std::is_array<T>::value>>
UniquePtr<T> make_unique(std::size_t n) {
    using U = std::remove_extent_t<T>;
    return UniquePtr<T>(new U[n]());
}

/* ---------------------------
   Demo
   --------------------------- */
struct Test {
    Test() { std::cout << "Test created\n"; }
    ~Test() { std::cout << "Test destroyed\n"; }
    void hello() const { std::cout << "Hello\n"; }
};

int main() {
    {
        auto p = make_unique<Test>();
        p->hello();
    }

    {
        auto arr = make_unique<int[]>(3);
        arr[0] = 1;
        arr[1] = 2;
        arr[2] = 3;
        std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';
    }
}
/*
Test created
Hello
Test destroyed
1 2 3

*/


Diagram: unique_ptr vs weak_ptr (and where shared_ptr fits)
Use this diagram in interviews — it’s succinct and clarifies ownership relationships.

                    +---------------------------+
                    |   unique_ptr<T> (stack)   |
                    |---------------------------|
                    |  ptr_  ----------+        |
                    |                |         |
                    +----------------|---------+
                                     |
                                     v
                           [Heap] ----+-----> Object T (unique owner)
                                     |
                                     + (only one owner; no control block)

--------------------------------------------------------------
shared_ptr/weak_ptr relationship (control-block model)
--------------------------------------------------------------

shared_ptr<T> A             shared_ptr<T> B            weak_ptr<T> W
+------------+              +------------+             +-----------+
| ptr ------ |--------------| ptr ------ |-------------| ptr -> ctrl block
| ctrl ptr --|--+       +---| ctrl ptr --|---+         | (no ownership)
+------------+  |       |   +------------+   |         +-----------+
                |       |                    |
                |       v                    |
         +---------------------------+       |
         |   control block (heap)    |<------+
         |---------------------------|
         | strong_count (atomic)     |
         | weak_count (atomic)       |
         | pointer -> Object T       |
         | deleter & allocator info  |
         +---------------------------+

- shared_ptr increments strong_count when copied; decrements on destruction.
- When strong_count reaches 0, object is destroyed via deleter.
- weak_ptr observes the control block and can be promoted to shared_ptr if strong_count>0.
- unique_ptr does NOT use a control block; it is exclusive-owner and has no weak_ptr concept.

