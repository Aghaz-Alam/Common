PART 1 — RAW POINTERS (Theory + Internals)

What is a Raw Pointer?
A raw pointer is a variable that stores the memory address of another object.

int* p = new int(10);
delete p;

Problems with Raw Pointers:
❌ Memory leaks
❌ Double deletion
❌ Dangling pointers
❌ Hard ownership tracking
❌ Manual delete required


PART 2 — SMART POINTERS (Theory)
Smart pointers automate memory management.
| Smart Pointer  | Ownership              | Key Use              |
| -------------- | ---------------------- | -------------------- |
| **unique_ptr** | Exclusive              | RAII, resource owner |
| **shared_ptr** | Shared reference count | Shared ownership     |
| **weak_ptr**   | Non-owning reference   | Break cycles         |

PART 3 — INTERNAL IMPLEMENTATION OF SMART POINTERS (Short)

1) unique_ptr Internals
Holds raw pointer
Destructor calls delete
Copying deleted; move transfers pointer

Pseudo-structure:
template<class T>
class UniquePtr {
    T* ptr;
  public:
    ~UniquePtr() { delete ptr; }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) noexcept {
        ptr = other.ptr; other.ptr = nullptr;
    }
};

2) shared_ptr Internals
Holds pointer + control block
Control block stores:
strong count
weak count
Deletes pointer when strong count == 0
Deletes control block when weak count == 0

Pseudo-structure:
struct ControlBlock {
    int strong;
    int weak;
};

template<typename T>
class SharedPtr {
    T* ptr;
    ControlBlock* ctrl;
};

3) weak_ptr Internals
Only increases weak count
Does NOT delete memory
Can check if pointer is expired



PART 4 — CODING CHALLENGES (with full code + output)
✅ Challenge 1 — Raw Pointer: Memory Leak Demonstration
#include <iostream>
using namespace std;

void leak() {
    int* p = new int(10);
    cout << *p << endl;
    // forgot delete -> leak
}
int main() {
    leak();
}
/* 
Output
10

Explanation: Memory is never freed → memory leak.
*/


✅ Challenge 2 — Fix Leak with delete
#include <iostream>
using namespace std;
void fixed() {
    int* p = new int(20);
    cout << *p << endl;
    delete p;
}
int main() {
    fixed();
}
/* 
Output
20
*/


✅ Challenge 3 — Dangling Pointer Issue
#include <iostream>
using namespace std;

int main() {
    int* p = new int(5);
    delete p;
    cout << "Dangling pointer value = " << p << endl; // Not safe
}
/* 
Output (sample)
Dangling pointer value = 0x55c9fea...
*/



//UNIQUE_PTR CHALLENGES (4–8)
✅ Challenge 4 — Basic unique_ptr usage
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> p = make_unique<int>(50);
    cout << *p << endl;
}
/* 
Output
50
*/


✅ Challenge 5 — unique_ptr Move Semantics
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> p1 = make_unique<int>(99);
    unique_ptr<int> p2 = move(p1);

    cout << (p1 == nullptr ? "p1 empty" : "p1 not empty") << endl;
    cout << *p2 << endl;
}
/* 
Output
p1 empty
99
*/


✅ Challenge 6 — Custom Deleter for unique_ptr
#include <iostream>
#include <memory>
using namespace std;
struct FreeDeleter {
    void operator()(int* p) {
        cout << "FreeDeleter called\n";
        delete p;
    }
};
int main() {
    unique_ptr<int, FreeDeleter> p(new int(10));
    cout << *p << endl;
}
/* 
Output
10
FreeDeleter called
*/


//shared_ptr CHALLENGES (9–14)
✅ Challenge 7 — shared_ptr Ref Counting
#include <iostream>
#include <memory>
using namespace std;
int main() {
    shared_ptr<int> a = make_shared<int>(10);
    shared_ptr<int> b = a;

    cout << a.use_count() << endl; // 2
    cout << b.use_count() << endl;
}
/* 
Output
2
2
*/


✅ Challenge 8 — shared_ptr Automatic Cleanup
#include <iostream>
#include <memory>
using namespace std;
struct X {
    ~X() { cout << "X destroyed\n"; }
};
int main() {
    {
        shared_ptr<X> p = make_shared<X>();
    }
}
/* 
Output
X destroyed
*/


weak_ptr CHALLENGES (15–18)
✅ Challenge 9 — weak_ptr detecting expiration
#include <iostream>
#include <memory>
using namespace std;
int main() {
    weak_ptr<int> wp;

    {
        shared_ptr<int> sp = make_shared<int>(100);
        wp = sp;
        cout << "Expired? " << wp.expired() << endl;
    }

    cout << "Expired after scope? " << wp.expired() << endl;
}
/* 
Output
Expired? 0
Expired after scope? 1
*/

INTERNAL SMART POINTER IMPLEMENTATION CHALLENGES (19–20)
✅ Challenge 10 — Implement a minimal unique_ptr
#include <iostream>
using namespace std;
template<typename T>
class UniquePtr {
    T* ptr;
  public:
    UniquePtr(T* p=nullptr) : ptr(p) {}
    ~UniquePtr() { delete ptr; }

    UniquePtr(UniquePtr&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    T& operator*() { return *ptr; }
};
int main() {
    UniquePtr<int> p(new int(77));
    cout << *p << endl;
}
/* 
Output
77
*/


✅ Challenge 11 — Implement a mini shared_ptr
#include <iostream>
using namespace std;
template<class T>
class SharedPtr {
    T* ptr;
    int* count;

  public:
    SharedPtr(T* p=nullptr)
        : ptr(p), count(new int(1)) {}

    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), count(other.count) {
        ++(*count);
    }

    ~SharedPtr() {
        if (--(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

    int use_count() const { return *count; }
    T& operator*() { return *ptr; }
};
int main() {
    SharedPtr<int> a(new int(5));
    SharedPtr<int> b = a;

    cout << a.use_count() << endl;
    cout << *b << endl;
}
/* 
Output
2
5
*/





















1) Implement make_unique (for single object)
// 1_make_unique.cpp
#include <iostream>
#include <memory>
using namespace std;
// basic make_unique for single object (C++14 already provides one)
template<typename T, typename... Args>
unique_ptr<T> my_make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
struct X {
    int v;
    X(int n):v(n){ cout<<"X ctor "<<v<<"\n"; }
    ~X(){ cout<<"X dtor "<<v<<"\n"; }
};
int main(){
    auto p = my_make_unique<X>(123);
    cout<<"X.v = "<<p->v<<"\n";
}
/* 
Sample Output
X ctor 123
X.v = 123
X dtor 123

Explanation: my_make_unique wraps new into unique_ptr with perfect forwarding. (Production code: use std::make_unique.)
*/



2) Implement weak_ptr internal behavior (simple SharedPtr + WeakPtr control block)
// 2_shared_weak_simple.cpp
#include <iostream>
using namespace std;
// Minimal control block
struct ControlBlock {
    int strong = 1;
    int weak = 0;
    ControlBlock() = default;
};

template<typename T>
struct SharedPtr;

template<typename T>
struct WeakPtr;

template<typename T>
struct SharedPtr {
    T* ptr = nullptr;
    ControlBlock* ctrl = nullptr;

    SharedPtr(): ptr(nullptr), ctrl(nullptr) {}
    explicit SharedPtr(T* p): ptr(p), ctrl(new ControlBlock()) {}

    // copy
    SharedPtr(const SharedPtr& o) : ptr(o.ptr), ctrl(o.ctrl) {
        if (ctrl) ++ctrl->strong;
    }
    // move
    SharedPtr(SharedPtr&& o) noexcept : ptr(o.ptr), ctrl(o.ctrl) { o.ptr = nullptr; o.ctrl = nullptr; }

    ~SharedPtr() {
        release();
    }

    void release() {
        if (!ctrl) return;
        if (--ctrl->strong == 0) {
            delete ptr;
            ptr = nullptr;
            if (ctrl->weak == 0) {
                delete ctrl;
                ctrl = nullptr;
            }
        }
    }

    int use_count() const { return ctrl ? ctrl->strong : 0; }

    friend struct WeakPtr<T>;
};
template<typename T>
struct WeakPtr {
    T* ptr = nullptr;
    ControlBlock* ctrl = nullptr;

    WeakPtr() = default;
    WeakPtr(const SharedPtr<T>& sp) : ptr(sp.ptr), ctrl(sp.ctrl) {
        if (ctrl) ++ctrl->weak;
    }
    ~WeakPtr() {
        if (!ctrl) return;
        if (--ctrl->weak == 0 && ctrl->strong == 0) delete ctrl;
    }

    SharedPtr<T> lock() const {
        if (!ctrl || ctrl->strong == 0) return SharedPtr<T>();
        // create new SharedPtr that increases strong count
        SharedPtr<T> sp;
        sp.ptr = ptr;
        sp.ctrl = ctrl;
        ++sp.ctrl->strong;
        return sp;
    }

    bool expired() const { return !ctrl || ctrl->strong == 0; }
};
int main(){
    SharedPtr<int> sp(new int(42));
    cout<<"sp.use_count() = "<<sp.use_count()<<"\n";
    WeakPtr<int> wp(sp);
    cout<<"wp.expired() = "<<wp.expired()<<"\n";

    {
        auto sp2 = wp.lock();
        cout<<"locked count = "<<sp2.use_count()<<"\n";
    }
    cout<<"sp.use_count() after lock scope = "<<sp.use_count()<<"\n";
}
/* 
Sample Output
sp.use_count() = 1
wp.expired() = 0
locked count = 2
sp.use_count() after lock scope = 1

Explanation: This shows the core idea: a separate control block holds strong/weak counts; WeakPtr::lock() increments strong count if object alive. (This is a simplified single-threaded model.)
*/




3) Circular reference problem with shared_ptr (leak demonstration)
// 3_circular_sharedptr_leak.cpp
#include <iostream>
#include <memory>
using namespace std;
struct B; // forward
struct A {
    shared_ptr<B> bptr;
    ~A(){ cout<<"A destroyed\n"; }
};
struct B {
    shared_ptr<A> aptr;
    ~B(){ cout<<"B destroyed\n"; }
};
int main(){
    {
        auto a = make_shared<A>();
        auto b = make_shared<B>();
        a->bptr = b;
        b->aptr = a;
        // both a and b point to each other -> reference cycle
    }
    cout<<"exited scope\n";
}
/* 
Sample Output
exited scope

Explanation: Destructors not printed: A and B remain allocated because shared_ptr reference counts never drop to zero due to the cycle (memory leak). 
OS will reclaim memory at process exit but destructors were never invoked.
*/



4) Fix circular reference with weak_ptr
// 4_circular_fixed_weakptr.cpp
#include <iostream>
#include <memory>
using namespace std;
struct B;
struct A {
    shared_ptr<B> bptr;
    ~A(){ cout<<"A destroyed\n"; }
};
struct B {
    weak_ptr<A> aptr; // weak -> breaks cycle
    ~B(){ cout<<"B destroyed\n"; }
};
int main(){
    {
        auto a = make_shared<A>();
        auto b = make_shared<B>();
        a->bptr = b;
        b->aptr = a; // weak_ptr does not increase strong count
    }
    cout<<"exited scope\n";
}
/* 
Sample Output
B destroyed
A destroyed
exited scope

Explanation: Using weak_ptr breaks the ownership cycle; when the scope ends, shared_ptr counts hit zero and destructors run.
 */



5) unique_ptr with custom deleter storing state
// 5_unique_with_state_deleter.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Deleter {
    int* counter; // external state
    Deleter(int* c): counter(c) {}
    void operator()(int* p) const {
        cout<<"Deleting pointer and incrementing counter\n";
        delete p;
        if (counter) ++(*counter);
    }
};

int main(){
    int delCount = 0;
    {
        unique_ptr<int, Deleter> p(new int(7), Deleter(&delCount));
        cout<<"value = "<<*p<<"\n";
    } // custom deleter runs here
    cout<<"delCount = "<<delCount<<"\n";
}
/* 
Sample Output
value = 7
Deleting pointer and incrementing counter
delCount = 1

Explanation: Custom deleter can capture/hold state (here via pointer to external counter). unique_ptr stores the deleter object and calls it on destruction.
*/


6) shared_ptr aliasing constructor (share control block but point to subobject)
// 6_shared_ptr_aliasing.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Big {
    int a;
    int b;
    Big(int x,int y):a(x),b(y){ cout<<"Big ctor\n"; }
    ~Big(){ cout<<"Big dtor\n"; }
};
int main(){
    // owner holds whole Big; aliasing shared_ptr points to member b but shares ownership
    auto owner = make_shared<Big>(1,2);
    // alias: shared_ptr<int> that keeps owner alive but points to &owner->b
    shared_ptr<int> alias(owner, &owner->b);
    cout<<"alias points to "<<*alias<<"\n";
    cout<<"owner use_count = "<<owner.use_count() << " alias use_count = "<<alias.use_count()<<"\n";
}
/* 
Sample Output
Big ctor
alias points to 2
owner use_count = 2 alias use_count = 2
Big dtor


Explanation: Alias constructor shared_ptr<T>(shared_ptr<U> const& r, T* ptr) creates a shared_ptr that shares ownership of rs control block but points to a different pointer. 
When both owner and alias destruct, object is destroyed once.
*/



7) Intrusive reference counting implementation
// 7_intrusive_ptr.cpp
#include <iostream>
using namespace std;

// Intrusive base: store refcount in object
struct IntrusiveBase {
    int refcount = 0;
    void add_ref(){ ++refcount; }
    void release_ref(){ if(--refcount==0) delete this; }
protected:
    virtual ~IntrusiveBase(){ cout<<"IntrusiveBase destroyed\n"; }
};

struct Obj : IntrusiveBase {
    int v;
    Obj(int x):v(x){ cout<<"Obj ctor\n"; }
    ~Obj(){ cout<<"Obj dtor\n"; }
};

template<typename T>
struct IntrusivePtr {
    T* p = nullptr;
    IntrusivePtr(T* ptr = nullptr): p(ptr){ if(p) p->add_ref(); }
    IntrusivePtr(const IntrusivePtr& o): p(o.p){ if(p) p->add_ref(); }
    IntrusivePtr& operator=(const IntrusivePtr& o){
        if (o.p) o.p->add_ref();
        if (p) p->release_ref();
        p = o.p;
        return *this;
    }
    ~IntrusivePtr(){ if(p) p->release_ref(); }
    T* operator->() const { return p; }
};

int main(){
    IntrusivePtr<Obj> a(new Obj(100));
    {
        IntrusivePtr<Obj> b = a;
        cout<<"inside block v="<<b->v<<"\n";
    }
    cout<<"exiting\n";
}


Sample Output

Obj ctor
inside block v=100
Obj dtor
IntrusiveBase destroyed
exiting


Explanation: The object itself tracks references; IntrusivePtr calls add_ref/release_ref. No external control block needed. Useful for performance-sensitive settings.

8) Smart pointer for arrays (UniqueArray)
// 8_unique_array.cpp
#include <iostream>
using namespace std;

template<typename T>
class UniqueArray {
    T* ptr;
public:
    explicit UniqueArray(T* p = nullptr): ptr(p) {}
    ~UniqueArray(){ delete[] ptr; }
    UniqueArray(const UniqueArray&) = delete;
    UniqueArray(UniqueArray&& o) noexcept : ptr(o.ptr) { o.ptr=nullptr; }
    UniqueArray& operator=(UniqueArray&& o){ if(this!=&o){ delete[] ptr; ptr=o.ptr; o.ptr=nullptr; } return *this; }
    T& operator[](size_t i){ return ptr[i]; }
    T* get(){ return ptr; }
};

int main(){
    UniqueArray<int> a(new int[5]{1,2,3,4,5});
    cout<<a[2]<<"\n";
}


Sample Output

3


Explanation: UniqueArray manages new[]/delete[]. Standard std::unique_ptr<T[]> exists, but this shows custom behavior.

9) Memory pool + unique_ptr (return-to-pool via custom deleter)
// 9_pool_with_unique.cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Pool {
    vector<char> buffer;
    vector<void*> free_list;
    size_t obj_size;
    Pool(size_t objSize, size_t count): buffer(objSize*count), obj_size(objSize) {
        for(size_t i=0;i<count;++i) free_list.push_back(buffer.data() + i*objSize);
    }
    void* allocate() {
        if(free_list.empty()) return nullptr;
        void* p = free_list.back(); free_list.pop_back(); return p;
    }
    void deallocate(void* p) { free_list.push_back(p); }
};

struct PoolDeleter {
    Pool* pool;
    PoolDeleter(Pool* p=nullptr): pool(p) {}
    void operator()(int* p) const {
        if(pool) pool->deallocate((void*)p);
    }
};

int main(){
    Pool pool(sizeof(int), 3);
    // create unique_ptr that uses pool-deleter
    auto make_from_pool = [&](int val){
        void* raw = pool.allocate();
        if(!raw) return unique_ptr<int,PoolDeleter>(nullptr, PoolDeleter(&pool));
        int* ip = new(raw) int(val); // placement-new
        return unique_ptr<int,PoolDeleter>(ip, PoolDeleter(&pool));
    };

    auto p1 = make_from_pool(10);
    auto p2 = make_from_pool(20);
    cout<<*p1<<" "<<*p2<<"\n";
    // p1 and p2 go out of scope -> returned to pool
}


Sample Output

10 20


Explanation: Pool provides raw storage; unique_ptr with custom deleter returns memory to pool instead of calling delete. Placement-new required; destructors omitted for trivial int.

10) Smart pointer toggle between unique and shared ownership (convert unique_ptr → shared_ptr)
// 10_unique_to_shared.cpp
#include <iostream>
#include <memory>
using namespace std;

struct X { X(int v):v(v){ cout<<"X ctor\n"; } ~X(){ cout<<"X dtor\n"; } int v; };

int main(){
    unique_ptr<X> up = make_unique<X>(7);
    // convert ownership to shared_ptr (std provides constructor)
    shared_ptr<X> sp = std::move(up); // takes ownership, up becomes empty
    cout<<"use_count after move = "<<sp.use_count()<<"\n";

    // convert shared_ptr back into unique_ptr is NOT directly possible safely.
    // But you can if use_count == 1: release() via sp.get() then reset sp (not recommended),
    // Proper approach: only move unique->shared; not reversible without caution.
}


Sample Output

X ctor
use_count after move = 1
X dtor


Explanation: std::shared_ptr has a constructor that takes unique_ptr<T>&& and transfers ownership into a control block. After move, unique_ptr is empty and shared_ptr has use_count() == 1. Converting back to unique_ptr is not generally supported safely.