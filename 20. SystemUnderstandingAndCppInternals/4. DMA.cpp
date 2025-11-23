what concepts in c++ can be used for better memeory management

✅ C++ Concepts for Better Memory Management
1. RAII (Resource Acquisition Is Initialization)
Core principle of C++ memory safety.
Objects acquire resources in constructors and release in destructors automatically.

Examples of RAII-managed resources:
Memory → std::unique_ptr, std::shared_ptr
File handles → std::ifstream, std::ofstream
Mutex locks → std::lock_guard, std::unique_lock
Threads → std::jthread

Why it is useful?
✔ No manual delete, fclose, unlock, etc.
✔ Exception-safe → cleanup on stack unwinding.


/* -------------------------------------------------- */
#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <mutex>
using namespace std;
//===============================================
// Example Class to show RAII for dynamic memory
//===============================================
class Resource {
  public:
    Resource()  { cout << "Resource acquired\n"; }
    ~Resource() { cout << "Resource released\n"; }
    void use()  { cout << "Using resource\n"; }
};

// Global mutex for demonstration
mutex mtx;

//===============================================
// Worker function for std::jthread
//===============================================
void worker() {
    lock_guard<mutex> lock(mtx);  // RAII → mutex automatically unlocked
    cout << "Worker thread executing (mutex locked)\n";
}

//===============================================
// Main demonstrating RAII for all resources
//===============================================
int main() {
    try {
        cout << "=== RAII: Smart Pointer (Memory) ===\n";
        {
            unique_ptr<Resource> res = make_unique<Resource>();
            res->use();
        }
        // Destructor of Resource automatically called here


        cout << "\n=== RAII: File Handling ===\n";
        {
            ifstream file("example.txt");   // file opened
            if (!file.is_open())
                cout << "File not found (but RAII still works)\n";
            // file automatically closed when leaving scope
        }


        cout << "\n=== RAII: Mutex Lock ===\n";
        {
            lock_guard<mutex> lock(mtx);   // locks mutex
            cout << "Inside critical section\n";
            // mutex automatically unlocked here
        }


        cout << "\n=== RAII: jthread (auto-join) ===\n";
        {
            jthread t(worker);  // thread starts immediately
            // No need to call t.join()
            // jthread auto-joins in its destructor
        }


        cout << "\n=== Exception Safety Demonstration ===\n";
        {
            unique_ptr<Resource> res2 = make_unique<Resource>();
            cout << "About to throw exception...\n";
            throw runtime_error("Some error occurred!");
            // res2 is still automatically destroyed even after throw
        }
    }
    catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\n=== End of Program ===\n";
    return 0;
}
/*
=== RAII: Smart Pointer (Memory) ===
Resource acquired
Using resource
Resource released

=== RAII: File Handling ===
File not found (but RAII still works)

=== RAII: Mutex Lock ===
Inside critical section

=== RAII: jthread (auto-join) ===
Worker thread executing (mutex locked)

=== Exception Safety Demonstration ===
Resource acquired
About to throw exception...
Resource released
Caught exception: Some error occurred!

=== End of Program ===
*/
/* -------------------------------------------------- */


2. Smart Pointers
Smart pointers automatically manage dynamic memory.

2.1 std::unique_ptr
Exclusive ownership
Zero overhead
Best for performance
auto p = std::make_unique<int>(10);

2.2 std::shared_ptr
Reference counting
Shared ownership
Automatically destructs when last reference goes away

2.3 std::weak_ptr
Non-owning pointer
Prevents circular reference memory leaks in shared_ptr.



/* ------------------------------------------ */
#include <iostream>
#include <memory>
using namespace std;
//----------------------------------------------
// Class to observe construction & destruction
//----------------------------------------------
class A {
   public:
    A()  { cout << "A constructed\n"; }
    ~A() { cout << "A destroyed\n"; }
};
class B {
   public:
    shared_ptr<A> a_ptr;     // Strong owning pointer
    B()  { cout << "B constructed\n"; }
    ~B() { cout << "B destroyed\n"; }
};
class C {
   public:
    weak_ptr<A> a_ptr;       // Weak (non-owning) pointer
    C()  { cout << "C constructed\n"; }
    ~C() { cout << "C destroyed\n"; }
};
int main() {
    cout << "=== unique_ptr Example ===\n";
    {
        unique_ptr<int> up = make_unique<int>(42);
        cout << "unique_ptr value = " << *up << "\n";
    } // up goes out of scope → automatically destroyed


    cout << "\n=== shared_ptr Example ===\n";
    {
        shared_ptr<A> sp1 = make_shared<A>();
        {
            shared_ptr<A> sp2 = sp1;   // shared ownership
            cout << "shared_ptr use_count = " << sp1.use_count() << "\n";
        } // sp2 destroyed → count decreases
        cout << "shared_ptr use_count = " << sp1.use_count() << "\n";
    } // last shared_ptr destroyed → A is destroyed


    cout << "\n=== weak_ptr Example (Avoid Circular Reference) ===\n";
    {
        shared_ptr<A> a = make_shared<A>();

        B b;
        b.a_ptr = a; // strong reference

        C c;
        c.a_ptr = a; // weak reference

        cout << "use_count (shared_ptr) = " << a.use_count() << "\n";

        if (!c.a_ptr.expired()) {
            cout << "weak_ptr locked → A is still alive\n";
        }
    } 
    // A destroyed here → no circular reference and no memory leak

    cout << "\n=== End of main ===\n";
    return 0;
}
/*
=== unique_ptr Example ===
unique_ptr value = 42

=== shared_ptr Example ===
A constructed
shared_ptr use_count = 2
shared_ptr use_count = 1
A destroyed

=== weak_ptr Example (Avoid Circular Reference) ===
A constructed
B constructed
C constructed
use_count (shared_ptr) = 2
weak_ptr locked → A is still alive
C destroyed
B destroyed
A destroyed

=== End of main ===
*/
/* ----------------------------------------- */


3. Move Semantics (C++11+)
Reduces unnecessary copies → prevents temporary-object overhead.
T(T&&) → move constructor
operator=(T&&) → move assignment
std::move() → cast to rvalue

Useful for:
Avoiding deep copies
Containers like vector reallocations
Optimizing large objects


/* ----------------------------------------- */
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Buffer {
private:
    size_t size;
    int* data;    // raw resource to show copy vs move

public:
    // Constructor
    Buffer(size_t s) : size(s), data(new int[s]) {
        cout << "Constructor: Allocated " << size << " ints\n";
    }

    // Destructor
    ~Buffer() {
        delete[] data;
        cout << "Destructor: Freed " << size << " ints\n";
    }

    // Copy Constructor (deep copy)
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        memcpy(data, other.data, size * sizeof(int));
        cout << "Copy Constructor: Deep copied " << size << " ints\n";
    }

    // Copy Assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;  // free old
            size = other.size;
            data = new int[size];
            memcpy(data, other.data, size * sizeof(int));
            cout << "Copy Assignment: Deep copied " << size << " ints\n";
        }
        return *this;
    }

    // Move Constructor
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
        cout << "Move Constructor: Took ownership\n";
    }

    // Move Assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;  // free old memory

            size = other.size;
            data = other.data;

            other.size = 0;
            other.data = nullptr;

            cout << "Move Assignment: Took ownership\n";
        }
        return *this;
    }
};

int main() {

    cout << "=== Move Constructor Example ===\n";
    {
        Buffer b1(10);
        Buffer b2 = std::move(b1);   // invokes move constructor
    }


    cout << "\n=== Move Assignment Example ===\n";
    {
        Buffer b3(20);
        Buffer b4(5);

        b4 = std::move(b3);  // invokes move assignment
    }


    cout << "\n=== Vector Reallocation using Move ===\n";
    {
        vector<Buffer> vec;
        vec.reserve(3);   // avoid copy on reallocation

        cout << "-- pushing element 1 --\n";
        vec.push_back(Buffer(10));   // temporary → moved

        cout << "-- pushing element 2 --\n";
        vec.push_back(Buffer(20));   // temporary → moved

        cout << "-- pushing element 3 --\n";
        vec.push_back(Buffer(30));   // temporary → moved
    }

    cout << "\n=== End of Program ===\n";
    return 0;
}
/*
=== Move Constructor Example ===
Constructor: Allocated 10 ints
Move Constructor: Took ownership
Destructor: Freed 10 ints
Destructor: Freed 0 ints

=== Move Assignment Example ===
Constructor: Allocated 20 ints
Constructor: Allocated 5 ints
Move Assignment: Took ownership
Destructor: Freed 20 ints
Destructor: Freed 0 ints

=== Vector Reallocation using Move ===
-- pushing element 1 --
Constructor: Allocated 10 ints
Move Constructor: Took ownership
Destructor: Freed 0 ints
-- pushing element 2 --
Constructor: Allocated 20 ints
Move Constructor: Took ownership
Destructor: Freed 0 ints
-- pushing element 3 --
Constructor: Allocated 30 ints
Move Constructor: Took ownership
Destructor: Freed 0 ints
Destructor: Freed 10 ints
Destructor: Freed 20 ints
Destructor: Freed 30 ints

=== End of Program ===
*/
/* ----------------------------------------- */

4. Memory-aware Standard Containers
Always prefer STL containers over raw pointers.

Examples:
std::vector → dynamic array
std::deque → double-ended fast insertion
std::list → linked list
std::array → static array
std::string → dynamic char array

Why containers help:
✔ Handle allocation/deallocation
✔ Exception safe
✔ Fast & optimized internally
✔ Avoid raw memory bugs


/* ----------------------------------------- */
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <string>

using namespace std;

struct Demo {
    Demo()  { cout << "Demo constructed\n"; }
    ~Demo() { cout << "Demo destroyed\n"; }
};

int main() {

    cout << "=== std::vector (Dynamic Array) ===\n";
    {
        vector<int> v;
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);

        cout << "vector contents: ";
        for (int x : v) cout << x << " ";
        cout << "\n";
    }
    // v goes out of scope → memory automatically freed


    cout << "\n=== std::deque (Double-ended Queue) ===\n";
    {
        deque<int> dq;
        dq.push_front(1);
        dq.push_back(2);
        dq.push_front(3);

        cout << "deque contents: ";
        for (int x : dq) cout << x << " ";
        cout << "\n";
    }
    // deque frees memory automatically


    cout << "\n=== std::list (Doubly Linked List) ===\n";
    {
        list<int> lst = { 10, 20, 30 };
        lst.push_back(40);

        cout << "list contents: ";
        for (int x : lst) cout << x << " ";
        cout << "\n";
    }


    cout << "\n=== std::array (Static Array, stack-allocated) ===\n";
    {
        array<int, 4> arr = { 5, 10, 15, 20 };

        cout << "array contents: ";
        for (int x : arr) cout << x << " ";
        cout << "\n";
    }


    cout << "\n=== std::string (Dynamic char array) ===\n";
    {
        string s = "Hello";
        s += " World";  // automatic reallocation

        cout << "string: " << s << "\n";
        cout << "length = " << s.size() << "\n";
    }


    cout << "\n=== Container with Objects (Auto Memory Management) ===\n";
    {
        vector<Demo> vec;
        vec.emplace_back();  // automatic construction/destruction
        vec.emplace_back();
    }
    // All objects destroyed automatically!


    cout << "\n=== End of Program ===\n";
    return 0;
}
/*
=== std::vector (Dynamic Array) ===
vector contents: 10 20 30 

=== std::deque (Double-ended Queue) ===
deque contents: 3 1 2 

=== std::list (Doubly Linked List) ===
list contents: 10 20 30 40 

=== std::array (Static Array, stack-allocated) ===
array contents: 5 10 15 20 

=== std::string (Dynamic char array) ===
string: Hello World
length = 11

=== Container with Objects (Auto Memory Management) ===
Demo constructed
Demo constructed
Demo destroyed
Demo destroyed
Demo destroyed

=== End of Program ===
*/
/* ---------------------------------------- */

5. Allocators
For custom memory allocation strategies.

Examples:
Pool allocators
Monotonic buffers
Custom arena allocators

Used in:
Game engines
High-frequency trading systems
Systems with strict memory budgets

Example:
std::vector<int, MyPoolAllocator<int>> v;


/* ------------------------------------------- */
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// ===========================================================
//            SIMPLE FIXED-SIZE MEMORY POOL
// ===========================================================
class MemoryPool {
private:
    static const size_t POOL_SIZE = 1024;     // bytes
    char pool[POOL_SIZE];
    size_t offset = 0;

public:
    void* allocate(size_t bytes) {
        if (offset + bytes > POOL_SIZE) {
            throw bad_alloc();
        }
        void* ptr = pool + offset;
        offset += bytes;

        cout << "[Pool] Allocated " << bytes 
             << " bytes at offset " << offset << "\n";
        return ptr;
    }

    void deallocate(void* p, size_t bytes) {
        // Pool allocator usually does nothing
        cout << "[Pool] Deallocate " << bytes << " bytes (no-op)\n";
    }
};

static MemoryPool globalPool;   // global pool used by allocator


// ===========================================================
//         CUSTOM ALLOCATOR THAT USES MEMORY POOL
// ===========================================================
template <typename T>
class MyPoolAllocator {
public:
    using value_type = T;

    MyPoolAllocator() = default;

    template <class U>
    MyPoolAllocator(const MyPoolAllocator<U>&) {}

    T* allocate(size_t n) {
        cout << "[Allocator] Request " << n * sizeof(T) << " bytes\n";
        return static_cast<T*>(globalPool.allocate(n * sizeof(T)));
    }

    void deallocate(T* p, size_t n) {
        globalPool.deallocate(p, n * sizeof(T));
    }
};


template <class T, class U>
bool operator==(const MyPoolAllocator<T>&, const MyPoolAllocator<U>&) { return true; }

template <class T, class U>
bool operator!=(const MyPoolAllocator<T>&, const MyPoolAllocator<U>&) { return false; }


// ===========================================================
//                             MAIN
// ===========================================================
int main() {

    cout << "=== Using std::vector with Custom Pool Allocator ===\n";

    vector<int, MyPoolAllocator<int>> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "\nElements: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";

    cout << "\n=== End of Program ===\n";
    return 0;
}
/*
=== Using std::vector with Custom Pool Allocator ===
[Allocator] Request 4 bytes
[Pool] Allocated 4 bytes at offset 4
[Allocator] Request 8 bytes
[Pool] Allocated 8 bytes at offset 12
[Pool] Deallocate 4 bytes (no-op)
[Allocator] Request 16 bytes
[Pool] Allocated 16 bytes at offset 28
[Pool] Deallocate 8 bytes (no-op)

Elements: 10 20 30 

=== End of Program ===
[Pool] Deallocate 16 bytes (no-op)
*/
/* ------------------------------------------- */

6. Placement new
Allows constructing an object in pre-allocated memory.
char buffer[sizeof(MyClass)];
MyClass* obj = new (buffer) MyClass();

Useful for:
Embedded systems
Memory pools
Avoiding heap fragmentation


/* ----------------------------------------- */
#include <iostream>
#include <new>     // for placement new
using namespace std;

class MyClass {
public:
    int x;
    MyClass(int val) : x(val) {
        cout << "MyClass constructed with x = " << x << "\n";
    }
    ~MyClass() {
        cout << "MyClass destroyed with x = " << x << "\n";
    }
};

int main() {

    // 1. Raw buffer with enough space
    alignas(MyClass) char buffer[sizeof(MyClass)];

    cout << "Buffer allocated on stack (" << sizeof(buffer) 
         << " bytes)\n";

    // 2. Construct object using placement new
    MyClass* obj = new (buffer) MyClass(42);

    cout << "Object constructed in buffer, address = " 
         << static_cast<void*>(buffer) << "\n";

    cout << "obj->x = " << obj->x << "\n";

    // 3. Manually call destructor
    obj->~MyClass();

    cout << "End of program\n";

    return 0;
}
/*
Buffer allocated on stack (4 bytes)
MyClass constructed with x = 42
Object constructed in buffer, address = 0x7ffc6ae81b54
obj->x = 42
MyClass destroyed with x = 42
End of program
*/
/* ----------------------------------------- */
7. Custom Deleters
Used with unique_ptr or shared_ptr to manage non-memory resources.
auto fileCloser = [](FILE* f){ fclose(f); };
std::unique_ptr<FILE, decltype(fileCloser)> fp(fopen("a.txt", "r"), fileCloser);


Use cases:
✔ Sockets
✔ Files
✔ Handles
✔ Mapped memory

/* ----------------------------------------- */
#include <iostream>
#include <memory>
#include <cstdio>
#include <cstring>  // <-- FIX
using namespace std;

// Simulated Socket resource
struct Socket {
    int id;
    Socket(int id) : id(id) {
        cout << "[Socket] Opened socket id = " << id << "\n";
    }
    ~Socket() {
        cout << "[Socket] Destructor should NOT run (managed by custom deleter)\n";
    }
};

// Custom deleter for FILE*
auto fileCloser = [](FILE* f) {
    if (f) {
        cout << "[File] Closing file\n";
        fclose(f);
    }
};

// Custom deleter for Socket*
struct SocketCloser {
    void operator()(Socket* s) const {
        if (s) {
            cout << "[Socket] Closing socket id = " << s->id << "\n";
            delete s;
        }
    }
};

// Custom deleter for raw buffer
struct BufferDeleter {
    void operator()(char* buf) const {
        cout << "[Buffer] Releasing memory buffer\n";
        delete[] buf;
    }
};

int main() {

    cout << "=== Custom Deleter Example ===\n\n";

    // 1. File using unique_ptr + custom deleter
    {
        unique_ptr<FILE, decltype(fileCloser)> fp(
            fopen("example.txt", "w"),
            fileCloser
        );

        if (fp) {
            cout << "[File] Writing to file\n";
            fprintf(fp.get(), "Hello, custom deleter!\n");
        }
    }   // auto-close file


    cout << "\n";


    // 2. Socket using unique_ptr + custom deleter
    {
        unique_ptr<Socket, SocketCloser> sock(
            new Socket(101)
        );

        cout << "[Socket] Using socket id = " << sock->id << "\n";
    }   // custom deleter closes socket


    cout << "\n";


    // 3. Raw buffer using shared_ptr + custom deleter
    {
        shared_ptr<char> buffer(
            new char[32],
            BufferDeleter()
        );

        cout << "[Buffer] Writing to buffer\n";
        strcpy(buffer.get(), "Custom deleter buffer test");

        cout << "[Buffer] Buffer contains: " << buffer.get() << "\n";
    }   // custom deleter frees buffer


    cout << "\n=== End of Program ===\n";

    return 0;
}
/*
=== Custom Deleter Example ===


[Socket] Opened socket id = 101
[Socket] Using socket id = 101
[Socket] Closing socket id = 101
[Socket] Destructor should NOT run (managed by custom deleter)

[Buffer] Writing to buffer
[Buffer] Buffer contains: Custom deleter buffer test
[Buffer] Releasing memory buffer

=== End of Program ===
*/
/* ----------------------------------------- */



8. std::optional
Avoids unnecessary dynamic allocations.
Instead of doing:
MyClass* ptr = nullptr;


Use:
std::optional<MyClass> opt;
Stores object inline → no heap allocation.


/* ----------------------------------------- */
#include <iostream>
#include <optional>
#include <string>
using namespace std;

class MyClass {
public:
    string name;

    MyClass(string n) : name(n) {
        cout << "MyClass constructed: " << name << "\n";
    }

    ~MyClass() {
        cout << "MyClass destroyed: " << name << "\n";
    }

    void hello() const {
        cout << "Hello from " << name << "\n";
    }
};

int main() {

    cout << "=== std::optional Example ===\n\n";

    // 1. Create an empty optional
    std::optional<MyClass> opt;
    cout << "Optional initially empty: " << boolalpha << !opt.has_value() << "\n\n";


    // 2. Construct object inline (no heap allocation)
    cout << "Emplacing object...\n";
    opt.emplace("InlineObject");   // Construct MyClass inside the optional

    if (opt) {
        opt->hello();
    }
    cout << "\n";


    // 3. Reset destroys the object
    cout << "Resetting optional...\n";
    opt.reset();  // Calls MyClass destructor

    cout << "Optional has value? " << opt.has_value() << "\n\n";


    // 4. Reassign with a new object
    cout << "Assigning a new object...\n";
    opt = MyClass("NewObject");  // Temporary moved into optional

    if (opt) {
        opt->hello();
    }

    cout << "\n=== End of Program ===\n";
    return 0;
}
/*
=== std::optional Example ===

Optional initially empty: true

Emplacing object...
MyClass constructed: InlineObject
Hello from InlineObject

Resetting optional...
MyClass destroyed: InlineObject
Optional has value? false

Assigning a new object...
MyClass constructed: NewObject
MyClass destroyed: NewObject
Hello from NewObject

=== End of Program ===
MyClass destroyed: NewObject
*/
/* ----------------------------------------- */

9. std::variant
Type-safe union.
Replaces raw unions with safe memory handling and zero leaks.


/* ----------------------------------------- */
#include <iostream>
#include <variant>
#include <string>
using namespace std;

// A visitor for std::visit
struct Printer {
    void operator()(int value) const {
        cout << "Variant holds int: " << value << "\n";
    }
    void operator()(double value) const {
        cout << "Variant holds double: " << value << "\n";
    }
    void operator()(const string& value) const {
        cout << "Variant holds string: " << value << "\n";
    }
};

int main() {

    cout << "=== std::variant Example ===\n\n";

    // Variant that can hold int, double, or string
    std::variant<int, double, std::string> v;

    // 1. Assign an int
    v = 42;
    cout << "Assigned int.\n";

    // Check type
    if (holds_alternative<int>(v)) {
        cout << "Current value: " << get<int>(v) << "\n\n";
    }

    // 2. Assign a double
    v = 3.14;
    cout << "Assigned double.\n";

    if (auto p = get_if<double>(&v)) {
        cout << "Current value: " << *p << "\n\n";
    }

    // 3. Assign a string
    v = std::string("Hello Variant");
    cout << "Assigned string.\n";

    // Using std::visit for type-safe handling
    std::visit(Printer{}, v);
    cout << "\n";

    // 4. Reassign int again
    v = 100;
    cout << "Reassigned int.\n";
    std::visit(Printer{}, v);
    cout << "\n";

    cout << "=== End of Program ===\n";
    return 0;
}
/*
=== std::variant Example ===

Assigned int.
Current value: 42

Assigned double.
Current value: 3.14

Assigned string.
Variant holds string: Hello Variant

Reassigned int.
Variant holds int: 100

=== End of Program ===
*/
/* ----------------------------------------- */



10. Memory Alignment / alignas, std::aligned_alloc
Better performance on SIMD, GPU, or hardware-aligned data.
alignas(32) float arr[8];

/* ----------------------------------------- */
#include <iostream>
#include <cstdlib>      // std::aligned_alloc, std::free
#include <cstddef>      // std::size_t
#include <cstdint>      // uintptr_t  <-- FIX
using namespace std;

// A struct aligned to 32 bytes (useful for SIMD)
struct alignas(32) Vec4 {
    float x, y, z, w;
};

int main() {

    cout << "=== Memory Alignment Example ===\n\n";

    // 1. Compile-time aligned array
    alignas(32) float arr[8];  // 32-byte aligned

    cout << "Address of aligned array: " << static_cast<void*>(arr) << "\n";
    cout << "Is arr 32-byte aligned? "
         << boolalpha << ((reinterpret_cast<uintptr_t>(arr) % 32) == 0)
         << "\n\n";


    // 2. Compile-time aligned struct
    Vec4 v{1, 2, 3, 4};

    cout << "Address of aligned Vec4:  " << &v << "\n";
    cout << "Is Vec4 32-byte aligned? "
         << boolalpha << ((reinterpret_cast<uintptr_t>(&v) % 32) == 0)
         << "\n\n";


    // 3. Runtime-aligned allocation
    size_t alignment = 64;       // 64-byte alignment
    size_t sizeBytes = 64;       // 64 bytes

    void* ptr = std::aligned_alloc(alignment, sizeBytes);

    if (!ptr) {
        cout << "Allocation failed!\n";
        return 1;
    }

    cout << "Address of aligned_alloc ptr: " << ptr << "\n";
    cout << "Is ptr 64-byte aligned? "
         << boolalpha << ((reinterpret_cast<uintptr_t>(ptr) % 64) == 0)
         << "\n\n";

    // Use aligned memory
    float* data = reinterpret_cast<float*>(ptr);
    for (int i = 0; i < 8; i++)
        data[i] = i * 10;

    cout << "Data stored in aligned memory: ";
    for (int i = 0; i < 8; i++)
        cout << data[i] << " ";
    cout << "\n\n";

    // Free aligned memory
    std::free(ptr);

    cout << "=== End of Program ===\n";
    return 0;
}
/*
=== Memory Alignment Example ===

Address of aligned array: 0x7fff620949a0
Is arr 32-byte aligned? true

Address of aligned Vec4:  0x7fff62094980
Is Vec4 32-byte aligned? true

Address of aligned_alloc ptr: 0x288c56c0
Is ptr 64-byte aligned? true

Data stored in aligned memory: 0 10 20 30 40 50 60 70 

=== End of Program ===
*/
/* ----------------------------------------- */


11. std::pmr (Polymorphic Memory Resources) — C++17/20
Advanced memory resource abstraction.

Examples:
pmr::monotonic_buffer_resource
pmr::unsynchronized_pool_resource

Allows:
✔ Custom arenas
✔ Faster transient allocations
✔ Controlling allocation per-container

/* ----------------------------------------- */
#include <iostream>
#include <memory_resource>   // pmr::memory_resource
#include <vector>
#include <string>
using namespace std;

// Logging resource to display allocations
struct LoggingResource : std::pmr::memory_resource {
    std::pmr::memory_resource* upstream;

    LoggingResource(std::pmr::memory_resource* u = std::pmr::get_default_resource())
        : upstream(u) {}

protected:
    // Called on every allocation
    void* do_allocate(size_t bytes, size_t alignment) override {
        cout << "[LoggingResource] Allocate " << bytes
             << " bytes (align " << alignment << ")\n";
        return upstream->allocate(bytes, alignment);
    }

    // Called on every deallocation
    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        cout << "[LoggingResource] Deallocate " << bytes
             << " bytes (align " << alignment << ")\n";
        upstream->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(const memory_resource& other) const noexcept override {
        return this == &other;
    }
};

int main() {

    cout << "=== std::pmr Example ===\n\n";

    // 1. Buffer for monotonic allocator
    std::byte buffer[1024];

    // 2. Monotonic buffer resource (fast arena allocator)
    std::pmr::monotonic_buffer_resource mono(buffer, sizeof(buffer));

    // 3. Wrap it with logging resource to observe allocations
    LoggingResource loggingResource(&mono);

    // 4. pmr::vector using custom allocator
    std::pmr::vector<std::pmr::string> names(&loggingResource);

    cout << "\n--- Adding strings into pmr::vector ---\n";
    names.emplace_back("Alice");
    names.emplace_back("Bob");
    names.emplace_back("Charlie");

    cout << "\nElements: ";
    for (auto& s : names) cout << s << " ";
    cout << "\n";

    cout << "\n--- pmr::unsynchronized_pool_resource Example ---\n";

    // 5. Pool resource (very fast for small allocations)
    std::pmr::unsynchronized_pool_resource pool;

    std::pmr::vector<int> poolVec(&pool);
    for (int i = 0; i < 10; i++)
        poolVec.push_back(i * 10);

    cout << "Pool vector: ";
    for (auto v : poolVec) cout << v << " ";
    cout << "\n\n";

    cout << "=== End of Program ===\n";
    return 0;
}
/* 
=== std::pmr Example ===

--- Adding strings into pmr::vector ---
[LoggingResource] Allocate 32 bytes (align 8)
[LoggingResource] Allocate 8 bytes (align 1)
[LoggingResource] Allocate 32 bytes (align 8)
[LoggingResource] Allocate 16 bytes (align 1)
[LoggingResource] Allocate 32 bytes (align 8)
[LoggingResource] Allocate 24 bytes (align 1)

Elements: Alice Bob Charlie 

--- pmr::unsynchronized_pool_resource Example ---
Pool vector: 0 10 20 30 40 50 60 70 80 90 

=== End of Program ===

*/
/* ----------------------------------------- */



12. Avoiding Raw Pointers
General rule:
❌ Avoid
new/delete  
malloc/free  
raw owning pointers  

✔ Prefer
unique_ptr  
shared_ptr  
vector  
string  

/* ----------------------------------------- */
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

// A simple class to demonstrate ownership
struct Demo {
    int x;
    Demo(int v) : x(v) {
        cout << "Demo(" << x << ") constructed.\n";
    }
    ~Demo() {
        cout << "Demo(" << x << ") destroyed.\n";
    }
};

int main() {

    cout << "\n===== ❌ Avoid Using Raw new/delete =====\n";
    {
        // BAD: raw owning pointer
        Demo* ptr = new Demo(10);

        cout << "Value: " << ptr->x << "\n";

        delete ptr;  // must remember manually → dangerous
    }

    cout << "\n===== ✔ Prefer unique_ptr (Exclusive Ownership) =====\n";
    {
        // Good: Automatically freed when going out of scope
        unique_ptr<Demo> up = make_unique<Demo>(20);

        cout << "Value: " << up->x << "\n";

        // No delete needed!
    }

    cout << "\n===== ✔ Prefer shared_ptr (Shared Ownership) =====\n";
    {
        shared_ptr<Demo> sp1 = make_shared<Demo>(30);
        {
            shared_ptr<Demo> sp2 = sp1;  // shared ownership

            cout << "Shared use count: " << sp1.use_count() << "\n";
        }
        cout << "Use count after inner scope: " << sp1.use_count() << "\n";

        // Automatically cleaned when last reference is gone
    }

    cout << "\n===== ✔ Prefer vector over new[] =====\n";
    {
        // BAD:
        // int* arr = new int[5];
        // delete[] arr;

        // GOOD: automatically manages memory
        vector<int> arr = {1, 2, 3, 4, 5};

        for (int x : arr) cout << x << " ";
        cout << "\n";
    }

    cout << "\n===== ✔ Prefer std::string over char* =====\n";
    {
        // BAD:
        // char* name = strdup("hello");

        // GOOD:
        string name = "hello modern C++";

        cout << name << "\n";
    }

    cout << "\n===== ✔ Prefer smart pointers inside classes =====\n";
    {
        struct Node {
            int value;
            unique_ptr<Node> next;

            Node(int v) : value(v) {}
        };

        auto head = make_unique<Node>(1);
        head->next = make_unique<Node>(2);

        cout << "Node1: " << head->value << "\n";
        cout << "Node2: " << head->next->value << "\n";
    }

    cout << "\n===== ALL DONE CLEANLY WITHOUT delete! =====\n";
}
/*

===== ❌ Avoid Using Raw new/delete =====
Demo(10) constructed.
Value: 10
Demo(10) destroyed.

===== ✔ Prefer unique_ptr (Exclusive Ownership) =====
Demo(20) constructed.
Value: 20
Demo(20) destroyed.

===== ✔ Prefer shared_ptr (Shared Ownership) =====
Demo(30) constructed.
Shared use count: 2
Use count after inner scope: 1
Demo(30) destroyed.

===== ✔ Prefer vector over new[] =====
1 2 3 4 5 

===== ✔ Prefer std::string over char* =====
hello modern C++

===== ✔ Prefer smart pointers inside classes =====
Node1: 1
Node2: 2

===== ALL DONE CLEANLY WITHOUT delete! =====
*/
/* ----------------------------------------- */


13. Static Analysis Tools
Use tools to detect leaks:
Valgrind
AddressSanitizer (ASan)
Clang-tidy
Visual Studio static analyzer

Catches:
✔ Memory leaks
✔ Buffer overflows
✔ Use-after-free
✔ Double delete

/* ----------------------------------------- */
#include <iostream>
using namespace std;

// Helper function to print reports
void show_report(const string& title, const string& detail) {
    cout << "\n===== " << title << " =====\n";
    cout << detail << "\n";
}

int main() {
    cout << "=== Memory Error Demonstrator (SAFE VERSION) ===\n";

    // ----------------------------------------------------------
    // 1) Simulated Use-After-Free
    // ----------------------------------------------------------
    {
        int* p = new int(100);
        delete p;

        // ❌ Do NOT dereference (unsafe)
        show_report(
            "Use-After-Free Detected",
            "Pointer 'p' was used after being freed.\n"
            "Memory analyzer would show: heap-use-after-free"
        );
    }

    // ----------------------------------------------------------
    // 2) Simulated Double Free
    // ----------------------------------------------------------
    {
        int* q = new int(55);
        delete q;

        // ❌ Do NOT delete q again (unsafe)
        show_report(
            "Double Free Detected",
            "Pointer 'q' was freed twice.\n"
            "Memory analyzer would show: double-free or corruption"
        );
    }

    // ----------------------------------------------------------
    // 3) Simulated Out-of-Bounds Access
    // ----------------------------------------------------------
    {
        int arr[5] = {1, 2, 3, 4, 5};

        // ❌ Do NOT write arr[5] (unsafe)
        show_report(
            "Out-of-Bounds Write Detected",
            "Attempted write past array boundary (index 5).\n"
            "Memory analyzer would show: heap-buffer-overflow"
        );
    }

    // ----------------------------------------------------------
    // 4) Simulated Memory Leak
    // ----------------------------------------------------------
    {
        int* leak = new int(777);

        // ❌ Intentionally not deleting it
        show_report(
            "Memory Leak Detected",
            "Allocated pointer 'leak' was not deleted.\n"
            "Memory analyzer would show: memory leak"
        );
    }

    cout << "\n=== Program finished successfully (no crashes). ===\n";

    return 0;
}
/*
=== Memory Error Demonstrator (SAFE VERSION) ===

===== Use-After-Free Detected =====
Pointer 'p' was used after being freed.
Memory analyzer would show: heap-use-after-free

===== Double Free Detected =====
Pointer 'q' was freed twice.
Memory analyzer would show: double-free or corruption

===== Out-of-Bounds Write Detected =====
Attempted write past array boundary (index 5).
Memory analyzer would show: heap-buffer-overflow

===== Memory Leak Detected =====
Allocated pointer 'leak' was not deleted.
Memory analyzer would show: memory leak

=== Program finished successfully (no crashes). ===
*/
/* ----------------------------------------- */

✔ Summary Table
| Concept         | Helps With           | Recommended For           |
| --------------- | -------------------- | ------------------------- |
| RAII            | Automatic cleanup    | Everywhere                |
| Smart Pointers  | Auto memory delete   | 99% of dynamic memory     |
| Move Semantics  | Avoid copies         | Performance-critical code |
| STL Containers  | Safe memory mgmt     | All storage needs         |
| Allocators      | Custom allocation    | Game engines, low latency |
| Placement new   | Manual control       | Embedded, pools           |
| Custom Deleters | Non-memory resources | Files, sockets            |
| std::optional   | Avoid heap           | Optional values           |
| std::variant    | Type-safe union      | Replacing unions          |
| pmr             | High-performance     | Advanced systems          |
| Tools (ASan)    | Leak detection       | Debugging stage           |
/* ----------------------------------------- */
#include <iostream>
#include <memory>
#include <variant>
#include <optional>
#include <vector>
#include <string>
#include <new>
#include <cstdio>
#include <memory_resource>

using namespace std;

void print_header(const string& title) {
    cout << "\n=====================================\n";
    cout << title << "\n";
    cout << "=====================================\n";
}

// 1) RAII example - file wrapper
class FileRAII {
public:
    FileRAII(const char* name) {
        file = fopen(name, "w");
        cout << "File opened using RAII\n";
    }
    ~FileRAII() {
        if (file) {
            fclose(file);
            cout << "File closed automatically by RAII\n";
        }
    }
private:
    FILE* file = nullptr;
};

// 2) Smart pointer demo
void smart_pointer_demo() {
    auto ptr = make_unique<int>(42);
    cout << "Unique_ptr holds: " << *ptr << "\n";
}

// 3) Move semantics demo
class Big {
public:
    int* data;
    Big() : data(new int[1000]) { cout << "Constructed\n"; }
    // move ctor
    Big(Big&& other) noexcept : data(other.data) {
        other.data = nullptr;
        cout << "Moved (constructor)\n";
    }
    // destructor prints only if it owns the data (so moved-from won't print)
    ~Big() {
        if (data) {
            delete[] data;
            cout << "Destroyed\n";
        }
    }
};

// 4) STL container demo
void stl_container_demo() {
    vector<int> v = {1,2,3};
    v.push_back(4);
    cout << "Vector elements: ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}

// 5) Simple pool (manual allocate to get two 4-byte allocations)
struct SimplePool {
    char buffer[256];
    size_t offset = 0;
    void* allocate(size_t n) {
        void* p = buffer + offset;
        offset += n;
        cout << "Pool allocated " << n << " bytes\n";
        return p;
    }
} pool;

// 6) Placement new demo
class MyClass {
public:
    int x;
    MyClass(int v) : x(v) { cout << "MyClass constructed: " << x << "\n"; }
    ~MyClass() { cout << "MyClass destroyed\n"; }
};

// 7) Custom deleter demo
void custom_deleter_demo() {
    auto deleter = [](FILE* f){
        if (f) {
            fclose(f);
            cout << "File closed by custom deleter\n";
        }
    };
    {
        unique_ptr<FILE, decltype(deleter)> fp(fopen("test_custom_del.txt", "w"), deleter);
        cout << "File opened with custom deleter\n";
        // fp goes out of scope here -> custom deleter runs
    }
}

// 8) optional demo
optional<int> getOptional(bool flag) {
    if (flag) return 10;
    return nullopt;
}

// 9) variant demo
variant<int, string> getVariant(int id) {
    if (id == 1) return 42;
    return string("Hello Variant");
}

// 10) pmr demo
void pmr_demo() {
    static char buff[512];
    pmr::monotonic_buffer_resource resource(buff, sizeof(buff));
    pmr::vector<int> v(&resource);
    v.push_back(10);
    v.push_back(20);
    cout << "PMR vector: ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}

// 11) static analysis simulated output
void show_asan_demo() {
    cout << "ASan/Valgrind would detect:\n";
    cout << "- buffer overflows\n";
    cout << "- use-after-free\n";
    cout << "- memory leaks\n";
    cout << "- double frees\n";
}

int main() {
    // 1) RAII
    print_header("1) RAII - Automatic Resource Management");
    {
        FileRAII fr("raii_demo.txt");
    }

    // 2) Smart Pointers
    print_header("2) Smart Pointers");
    smart_pointer_demo();

    // 3) Move Semantics (scope so destructor runs here)
    print_header("3) Move Semantics");
    {
        Big a;
        Big b = std::move(a);
        // when this scope ends, only 'b' owns data -> one "Destroyed"
    }

    // 4) STL Containers
    print_header("4) STL Containers");
    stl_container_demo();

    // 5) Custom Allocator (manual pool allocations to control messages)
    print_header("5) Custom Allocator (Simple Pool)");
    {
        // allocate two ints manually -> each 4 bytes
        int* p1 = static_cast<int*>(pool.allocate(sizeof(int)));
        *p1 = 10;
        int* p2 = static_cast<int*>(pool.allocate(sizeof(int)));
        *p2 = 20;
        (void)p1; (void)p2; // silence unused warnings
    }

    // 6) Placement new
    print_header("6) Placement new");
    {
        alignas(MyClass) char buffer[sizeof(MyClass)];
        MyClass* obj = new(buffer) MyClass(99);
        obj->~MyClass();
    }

    // 7) Custom deleters
    print_header("7) Custom Deleters");
    custom_deleter_demo();

    // 8) std::optional
    print_header("8) std::optional");
    {
        auto opt = getOptional(true);
        if (opt) cout << "Optional value: " << *opt << "\n";
    }

    // 9) std::variant
    print_header("9) std::variant");
    {
        auto var = getVariant(2);
        if (holds_alternative<string>(var))
            cout << "Variant holds string: " << get<string>(var) << "\n";
    }

    // 10) pmr
    print_header("10) Polymorphic Memory Resources (pmr)");
    pmr_demo();

    // 11) Tools
    print_header("11) Static Analysis Tools (Simulated)");
    show_asan_demo();

    return 0;
}
/*
=====================================
1) RAII - Automatic Resource Management
=====================================
File opened using RAII

=====================================
2) Smart Pointers
=====================================
Unique_ptr holds: 42

=====================================
3) Move Semantics
=====================================
Constructed
Moved (constructor)
Destroyed

=====================================
4) STL Containers
=====================================
Vector elements: 1 2 3 4 

=====================================
5) Custom Allocator (Simple Pool)
=====================================
Pool allocated 4 bytes
Pool allocated 4 bytes

=====================================
6) Placement new
=====================================
MyClass constructed: 99
MyClass destroyed

=====================================
7) Custom Deleters
=====================================
File opened with custom deleter

=====================================
8) std::optional
=====================================
Optional value: 10

=====================================
9) std::variant
=====================================
Variant holds string: Hello Variant

=====================================
10) Polymorphic Memory Resources (pmr)
=====================================
PMR vector: 10 20 

=====================================
11) Static Analysis Tools (Simulated)
=====================================
ASan/Valgrind would detect:
- buffer overflows
- use-after-free
- memory leaks
- double frees
*/
/* ----------------------------------------- */





1. When the memory will be allocated on heap , what type of memery
2. have you used debugger, ? how are you using ? example scenario
3. what is call stack and what it contains ?
4. say more about dynamic allocation
5. risk with dynamic memoery allocation 


/* ---------------------------------------- */
1. When the memory will be allocated on heap , what type of memery
--> When memory is allocated on the heap, it is called dynamic memory (or free-store memory in C++ terminology).

Here is the clean breakdown:
✅ What type of memory is allocated on the heap?
✔ Dynamic Memory
--> When you allocate memory at runtime using:
new
make_unique
make_shared
malloc

…the memory is taken from the heap (also called dynamic storage area).


Memory Types in a C++ Program
A C++ program has several memory regions:
| Memory Region                         | Stores                             | Allocated By                | Lifetime          |
| ------------------------------------- | ---------------------------------- | --------------------------- | ----------------- |
| **Stack**                             | local variables, function calls    | automatic                   | end of scope      |
| **Heap**                              | dynamically allocated memory       | new / delete, malloc / free | until delete/free |
| **Data Segment (Global/Static area)** | global variables, static variables | compiler                    | entire program    |
| **Text/Code Segment**                 | program instructions               | compiler                    | entire program    |



Heap (Dynamic Memory)
✔ Allocates memory at runtime

Example:
int* p = new int(10);

Here:
p (the pointer) lives on the stack
integer value 10 lives on the heap

✔ Must be manually released
delete p;
Or use smart pointers:
auto ptr = make_unique<int>(10); // auto-delete


Why Do We Use the Heap?
To allocate large memory
To allocate memory that must outlive a function call
To create objects when size is not known at compile time
For dynamic data structures (linked list, tree, graph)

Example (Heap Allocation)
#include <iostream>
using namespace std;
int main() {
    int* p = new int(55);   // memory allocated on heap
    cout << *p << endl;
    delete p;               // free memory
  return 0;
}
/* ------------------------------------------- */

2. Have you used debugger, ? how are you using ? example scenario
Yes — using a debugger is a basic and essential skill in C++.
Let me explain how a debugger works, how you use it, and give you a full example scenario using the most commonly used debugger:

What is a Debugger?
A debugger (like gdb, Visual Studio Debugger, CLion Debugger, VSCode debugger) lets you:
Pause program execution
Inspect variable values
Step line-by-line
Set breakpoints
Watch memory
Find segmentation faults
Reverse execution (in some IDEs)

🧰 Common Debuggers
| Platform       | Debugger                                      |
| -------------- | --------------------------------------------- |
| Linux / Mac    | **GDB** (GNU Debugger)                        |
| Windows        | **Visual Studio Debugger**                    |
| Cross-platform | CLion Debugger                                |
| VS Code        | C++ Extension Debugger (uses `gdb` or `lldb`) |

Debugger Example Scenario (Using GDB)

Let’s take a buggy C++ program.

❌ Buggy Program (common mistake)
#include <iostream>
using namespace std;

int main() {
    int arr[3] = {10, 20, 30};

    for (int i = 0; i <= 3; i++) {  // BUG: loop goes out of bounds
        cout << arr[i] << endl;
    }

    return 0;
}

This program will print garbage or crash after 30 because we accessed arr[3] (invalid index).


🪲 Step-by-Step: How to Debug Using GDB (Linux/VS Code)
1. Compile with debugging symbols
g++ -g main.cpp -o myprog
-g enables debugging info.

2. Run the program inside GDB
gdb ./myprog

3. Set a breakpoint
(gdb) break main

4. Start the program
(gdb) run

5. Step line by line
(gdb) next
Or enter n repeatedly.

6. Watch variable values
Example:
(gdb) print i
$1 = 0

(gdb) print arr[i]
$2 = 10


As you keep stepping:
(gdb) print i
$3 = 3
(gdb) print arr[i]
$4 = <Error or garbage>

Now you see the bug clearly:
i became 3, and arr[3] is invalid.


Debugger Helps You Understand
The loop ran one step too far
Out-of-bounds access caused memory corruption
Without a debugger, this bug is very hard to see



Debugger Example Using Visual Studio (Windows)
Place a breakpoint (red dot) on the loop line.
Press F5 (Start Debugging).

Use:
F10 = Step Over
F11 = Step Into

Open Watch Window:
Add i
Add arr[i]
On last iteration, you see i = 3 and arr[i] = garbage.



Another Example: Debugging a Segmentation Fault

Buggy Code:
int* p = nullptr;
cout << *p << endl;  // crash

Using debugger:
(gdb) run
Program received SIGSEGV
(gdb) backtrace
#0 main at main.cpp:5

Debugger shows the exact line of crash.


⭐ Why Debuggers are Useful
✔ Find segmentation faults
✔ Detect memory corruption
✔ Step through logic flow
✔ Examine heap/stack variables
✔ View assembly (if needed)
✔ Watch smart pointers / RAII objects


/* -------------------------------------- */
3. what is call stack and what it contains ?
The call stack is one of the most important concepts in C++ program execution.
It tells how functions call each other and where local variables are stored.
Let’s break it down clearly.

🧱 What is the Call Stack in C++?
The call stack is a region of memory used for:
Function calls
Local variables
Return addresses
Function parameters
Saved registers
Stack frames (activation records)
Every time a function is called, a new frame is pushed onto the stack.
When the function returns, its frame is popped off.

📦 What a Call Stack Contains
Each function call creates a stack frame.
A stack frame contains:
| Item                             | Meaning                                |
| -------------------------------- | -------------------------------------- |
| **Function parameters**          | Arguments passed to function           |
| **Local variables**              | Variables defined inside the function  |
| **Return address**               | Location to return after function ends |
| **Saved registers**              | CPU state saved during call            |
| **Stack pointer & base pointer** | Used to access variables               |
| **Temporary values**             | Result of expressions                  |

Visual Diagram of Call Stack
Example C++ code:
void C() {
    int c = 30;
}
void B() {
    int b = 20;
    C();
}
void A() {
    int a = 10;
    B();
}
int main() {
    A();
}


Call Stack grows downward:
Top of Stack  ↓ (new frames added)

+---------------------+
| Frame of function C |
| - local: c          |
| - return address    |
+---------------------+
| Frame of function B |
| - local: b          |
| - return address    |
+---------------------+
| Frame of function A |
| - local: a          |
| - return address    |
+---------------------+
| Frame of main       |
| - maybe local vars  |
| - return address    |
+---------------------+
Bottom of Stack ↑ (old frames)

🧠 Call Stack Key Points
✔ Stack grows downward
Each function call pushes a new frame.

✔ Stack shrinks upward
When function returns → frame popped.

✔ Fast allocation
Stack allocation is extremely fast (just pointer movement).

✔ Automatic lifetime
Objects on stack are automatically destroyed when the function ends.

Example:
void foo() {
    int x = 5;  // on stack
}               // x is destroyed automatically

⚠️ Common Stack Problems
❌ Stack overflow

Happens with deep recursion:
void f() {
    f(); // infinite recursion → stack overflow
}

❌ Returning address of a local variable
Local variables vanish after function returns:
int* bad() {
    int x = 10;
    return &x; // ❌ dangling pointer
}

📌 What does NOT go on the stack?
These go on heap, not stack:
--> new-allocated objects
--> make_unique, make_shared objects
--> global variables
--> static variables
--> dynamically allocated arrays
--> objects with dynamic lifetime

Example:
int* p = new int(5);  // heap

⭐ Summary
✔ The call stack handles:
--> Function calls
--> Parameters
--> Return addresses
--> Local variables
--> Saved CPU state

✔ Fast and automatic memory
--> Stack variables disappear automatically when the function returns.

/* --------------------------------------- */
4. say more about dynamic allocation
✅ Dynamic Allocation in C++ (Explained Fully)

Dynamic allocation means:
You request memory at runtime from the heap using new, and release it using delete.
This allows you to create objects whose size or lifetime is not known at compile time.

📌 1. Where is dynamically allocated memory stored?
✔️ Heap / Free Store
A large memory region managed by the runtime.
Memory is allocated in blocks via new, new[], malloc(), or allocators.
Memory persists until you explicitly free it (or smart pointers free it automatically).

📌 2. How to allocate memory dynamically
✔️ Allocate single variable:
int* p = new int(10);

✔️ Allocate array:
int* arr = new int[5];

✔️ Allocate object:
class A {};
A* obj = new A();

📌 3. How to free dynamic memory
✔️ Delete single object:
delete p;

✔️ Delete array:
delete[] arr;


⚠️ Never mix:
new with free()
malloc() with delete
new[] with delete

📌 4. Why do we use dynamic allocation?
✔️ (A) Unknown size at runtime
int n;
cin >> n;
int* arr = new int[n];

✔️ (B) Lifetime control
Object can outlive the scope:
Node* createNode() {
    return new Node();   // returned and still alive
}

✔️ (C) Large objects
Big arrays cannot be placed on stack (limited size).
int* hugeArray = new int[1000000];

📌 5. Problems with manual dynamic allocation

❌ Memory leaks
Forgot to delete.

❌ Dangling pointers
Using memory after deletion.

❌ Double delete
Calling delete twice.

❌ No automatic cleanup
Harder to maintain.

📌 6. Smart Pointers — Modern C++ fix
✔️ Use instead of raw new:
auto ptr = make_unique<int>(10);
auto ptr2 = make_shared<MyClass>();

Smart pointers automatically delete memory → no leaks, no dangling pointers.

📌 7. Example: Raw new (manual)
int* p = new int(42);
cout << *p;
delete p;   // MUST
p = nullptr;

📌 8. Example: Smart Pointer (recommended)
auto p = make_unique<int>(42);
cout << *p;    // automatic cleanup when p goes out of scope

📌 9. Memory layout summary
+-----------------------------+
| Code / Text Segment         |
+-----------------------------+
| Global / Static Segment     |
+-----------------------------+
| Heap (dynamic memory)       |
+-----------------------------+
| Stack (functions, locals)   |
+-----------------------------+

Stack → automatic variables, function calls
Heap → dynamic allocation (new, smart pointers)

📌 10. When should you use dynamic allocation?
✔ When object size unknown at compile time
✔ When object must outlive the scope
✔ When cutting-edge data structures (trees, linked lists)
✔ When using modern smart pointers

❌ Avoid raw new unless writing low-level code.
/* --------------------------------------- */
5. risk with dynamic memoery allocation 

Dynamic memory allocation is powerful, but it also introduces serious risks in C++ when not handled correctly.
Here is a complete list of all major risks, with examples.

⚠️ Risks with Dynamic Memory Allocation in C++
Dynamic memory (allocated using new, new[], malloc(), or smart pointers) lives on the heap, and managing it incorrectly can lead to bugs that are often hard to detect.

1. Memory Leaks
You allocate memory but never free it.

❌ Example:
int* p = new int(5);
// forgot delete p;

📌 Result:
Memory stays allocated forever
Eventually heap fills → slowdown or crash

2. Dangling Pointer
Pointer still exists after memory is freed.

❌ Example:
int* p = new int(10);
delete p;
cout << *p;   // undefined behavior

📌 Result:
Program may crash
May print garbage
Hardest bugs to debug

3. Double Free (Double Delete)
Deleting the same memory twice.

❌ Example:
int* p = new int(10);
delete p;
delete p;  // CRASH

📌 Result:
Heap corruption
Random crashes later in program

4. Mismatched Allocation / Deallocation
Using delete for memory allocated with new[], or free() with new.

❌ Example:
int* arr = new int[5];
delete arr;  // WRONG → should be delete[]

📌 Result:
Heap corruption
Memory corruption
Very difficult to track down

5. Out-of-Bounds Access
Writing or reading outside allocated memory.

❌ Example:
int* arr = new int[3];
arr[3] = 10;  // out of bounds

📌 Result:
Corrupts heap
Corrupts other variables
May not crash immediately → dangerous

6. Uninitialized Memory
Using memory before initializing it.

❌ Example:
int* p = new int;  
cout << *p;  // reading uninitialized memory

📌 Result:
Garbage value
Undefined behavior

7. Memory Fragmentation
Repeated new and delete cause scattered memory blocks.

📌 Result:
Program becomes slow
Heap becomes fragmented
Allocation may fail even if memory is available

8. Performance Overhead
Heap allocation is slow compared to stack allocation.

Why?
Heap must search for a suitable free block
Thread-safe allocator adds locking
Complex allocator metadata

9. Exception Safety Issues
If exception occurs after new, memory leak happens.

❌ Example:
int* p = new int(10);
foo();       // throws exception
delete p;    // NEVER reached → leak

✔️ Fix with smart pointers:
auto p = make_unique<int>(10);  // automatically cleaned
foo(); // OK

10. Smart Pointer Misuse
Even smart pointers can be misused.

❌ Circular reference (shared_ptr)
struct A { shared_ptr<A> self; };

📌 Result:
Both objects keep each other alive → memory leak
Fix: use weak_ptr

11. Race Conditions in Multi-threaded Programs
Dynamic memory shared between threads can lead to:
double delete
use-after-free
corrupt heap
/* -------------------------------------- */