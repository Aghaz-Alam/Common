//SharedPtr<T> Implementation
#include <iostream>
#include <utility>
#include <functional>
using namespace std;
template <typename T>
class SharedPtr {
  private:
    T* ptr;                     // raw managed pointer
    size_t* refCount;           // pointer to shared reference counter
    std::function<void(T*)> deleter; // custom deleter

    void release() {
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                // Delete managed object
                if (ptr){
                    deleter(ptr);
                }
                delete refCount;   // delete counter
            }
        }
        ptr = nullptr;
        refCount = nullptr;
    }

  public:
    // --- Constructors ---
    SharedPtr(): ptr(nullptr), refCount(nullptr), deleter([](T* p) { delete p; }) {}

    explicit SharedPtr(T* p): ptr(p), refCount(new size_t(1)),  deleter([](T* p) { delete p; }) {}

    SharedPtr(T* p, std::function<void(T*)> d): ptr(p), refCount(new size_t(1)), deleter(d) {}

    // --- Copy Constructor ---
    SharedPtr(const SharedPtr& other): ptr(other.ptr), refCount(other.refCount), deleter(other.deleter) {
        if (refCount)
            (*refCount)++;
    }

    // --- Move Constructor ---
    SharedPtr(SharedPtr&& other) noexcept: ptr(other.ptr), refCount(other.refCount), deleter(std::move(other.deleter)) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    // --- Copy Assignment ---
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();  // release current

            ptr = other.ptr;
            refCount = other.refCount;
            deleter = other.deleter;

            if (refCount)
                (*refCount)++;
        }
        return *this;
    }

    // --- Move Assignment ---
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();

            ptr = other.ptr;
            refCount = other.refCount;
            deleter = std::move(other.deleter);

            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    // --- Destructor ---
    ~SharedPtr() {
        release();
    }

    // --- Operators ---
    T& operator*() const { 
        return *ptr; 
    }
    
    T* operator->() const { 
        return ptr; 
    }
    
    T* get() const { 
        return ptr; 
    }

    // --- Utilities ---
    size_t use_count() const {
        return refCount ? *refCount : 0;
    }

    explicit operator bool() const { 
        return ptr != nullptr; 
    }

    void reset(T* p = nullptr) {
        release();  // drop old object
        if (p) {
            ptr = p;
            refCount = new size_t(1);
        } else {
            ptr = nullptr;
            refCount = nullptr;
        }
    }
};

int main() {
    SharedPtr<int> sp1(new int(10));
    cout << *sp1 << "\n";            // 10
    cout << sp1.use_count() << "\n"; // 1

    {
        SharedPtr<int> sp2 = sp1;
        cout << sp2.use_count() << "\n"; // 2
    }

    // sp2 destroyed → count becomes 1
    cout << sp1.use_count() << "\n";     // 1

    sp1.reset();
    cout << sp1.use_count() << "\n";     // 0
}
/*
10
1
2
1
0
*/



/* ------------------------------------- */
✅ Line-by-line Explanation
Header + Using
#include <iostream>
#include <utility>
#include <functional>
using namespace std;

iostream → needed for printing in main.
utility → needed for std::move in move constructor/assignment.
functional → needed for std::function (custom deleter).
using namespace std → to avoid writing std:: everywhere.


🌟 SharedPtr Class
template <typename T>
class SharedPtr {
Template so it can store any type T (int, string, custom class…).


🎯 Private Members
private:
    T* ptr;                     

ptr → raw pointer to the managed object.
    
    size_t* refCount;
refCount → dynamically allocated counter shared among copies.
Stored as pointer so multiple SharedPtr share one counter (same memory).

    std::function<void(T*)> deleter;
deleter → function object storing the deletion strategy
(default = delete, but user can pass a custom deleter).


🔥 release(): Core cleanup logic
void release() {

Called when:
object goes out of scope (destructor)
reset()
assignment overwrites old pointer


    if (refCount) {
Only work if the object actually owns a counter.

        (*refCount)--;
Decrease strong reference count.

        if (*refCount == 0) {
If no more SharedPtr objects refer to ptr, delete it.

            if (ptr){
                deleter(ptr);
            }
Call custom deleter → usually delete ptr.

            delete refCount;   // delete counter
Free memory of the counter.
    }


End of refCount block.
    ptr = nullptr;
    refCount = nullptr;
}
Nullify internal pointers so object becomes empty (use_count() == 0).


🏗 Constructors
✔ Default Constructor
SharedPtr(): ptr(nullptr), refCount(nullptr),
             deleter([](T* p) { delete p; }) {}

Creates an empty shared pointer:
ptr = nullptr
refCount = nullptr
default deleter is a lambda: delete p.

✔ Constructor with raw pointer
explicit SharedPtr(T* p): ptr(p), refCount(new size_t(1)), deleter([](T* p) { delete p; }) {}
Takes ownership of p.
Initializes reference counter to 1.
Default deleter = delete.


✔ Constructor with custom deleter
SharedPtr(T* p, std::function<void(T*)> d): ptr(p), refCount(new size_t(1)), deleter(d) {}

Allows:
SharedPtr<File> sp(f, fclose);


📌 Copy Constructor
SharedPtr(const SharedPtr& other): ptr(other.ptr), refCount(other.refCount), deleter(other.deleter) {

Copies raw pointer.
Shares counter.
Copies deleter.

    if (refCount)
        (*refCount)++;
}
Increase reference count.


🚚 Move Constructor
SharedPtr(SharedPtr&& other) noexcept: ptr(other.ptr), refCount(other.refCount), deleter(std::move(other.deleter)) {

Move semantics:
Steal pointer, counter, deleter from other.
    other.ptr = nullptr;
    other.refCount = nullptr;
}
Make other empty; prevents double deletion.


🔁 Copy Assignment
SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {

Self-assignment check.
        release();  // release current

Clean up previous owned object.
        ptr = other.ptr;
        refCount = other.refCount;
        deleter = other.deleter;

Copy new pointer data.
        if (refCount)
            (*refCount)++;
    }
return *this;
}

Increase counter.

🚚 Move Assignment
SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        release();  // release current
        ptr = other.ptr;
        refCount = other.refCount;
        deleter = std::move(other.deleter);

Move from other.
        other.ptr = nullptr;
        other.refCount = nullptr;
    }
    return *this;
}

Make other empty.
⚰ Destructor
~SharedPtr() {
    release();
}

Automatically decrease reference count and delete if needed.

🎮 Operators
T& operator*() const { return *ptr; }

Dereference *sp.
T* operator->() const { return ptr; }

Member access sp->x.
T* get() const { return ptr; }

Get raw pointer without modifying reference count.

📊 Utilities
size_t use_count() const {
    return refCount ? *refCount : 0;
}

If counter exists → return strong count.
Otherwise, return 0.
explicit operator bool() const { return ptr != nullptr; }

Allows:
if(sp) { ... }

🔄 reset()
void reset(T* p = nullptr) {
    release();  // drop old object

Release old pointer.
    if (p) {
        ptr = p;
        refCount = new size_t(1);
    } else {
        ptr = nullptr;
        refCount = nullptr;
    }
}

If new pointer provided:
take ownership
Else:
become empty

🧪 Main Function
int main() {
    SharedPtr<int> sp1(new int(10));

Creates shared pointer holding value 10.
    cout << *sp1 << "\n";            // 10

Dereference prints 10.
    cout << sp1.use_count() << "\n"; // 1

Only sp1 owns the object → count = 1.
{
    SharedPtr<int> sp2 = sp1;

Copy → count becomes 2.
    cout << sp2.use_count() << "\n"; // 2
}

sp2 goes out of scope → count -= 1 → becomes 1.
cout << sp1.use_count() << "\n"; // 1
sp1.reset();

Deletes counter and managed object.
cout << sp1.use_count() << "\n"; // 0

sp1 no longer owns anything.

🎉 Output
10
1
2
1
0
/* ------------------------------------ */