what are deleters , how deleters can be used in templates.
✅ What Are Deleters in C++?
A deleter is a callable (function, function object, lambda) used by smart pointers (especially std::unique_ptr) 
to destroy the managed object when the smart pointer goes out of scope.

🔑 Why deleters?
Because:
Different resources need different cleanup logic
Delete may not be enough (FILE*, mutexes, OS handles, etc.)
Deleters let you extend smart pointers beyond memory (RAII)

✅ Standard Smart Pointer + Deleter
unique_ptr syntax
std::unique_ptr<T, Deleter>

Where:
T = type being managed
Deleter = type of custom deleter (function object, lambda, etc.)

Example:
std::unique_ptr<FILE, decltype(&fclose)> fp(fopen("a.txt", "r"), &fclose);

1️⃣ Function Pointer Deleter
void myDelete(int* p) {
    cout << "Deleting pointer\n";
    delete p;
}
int main() {
    std::unique_ptr<int, void(*)(int*)> ptr(new int(10), myDelete);
}

2️⃣ Functor (Function Object) Deleter
Very common for generic / template scenarios
struct IntDeleter {
    void operator()(int* p) const {
        cout << "Functor deleter\n";
        delete p;
    }
};
std::unique_ptr<int, IntDeleter> ptr(new int(10));

3️⃣ Lambda Deleter
auto del = [](int* p){
    cout << "Lambda deleter\n";
    delete p;
};

std::unique_ptr<int, decltype(del)> ptr(new int(10), del);

⭐ Why Use a Deleter?
| Use case                  | Example                 |
| ------------------------- | ----------------------- |
| Free array memory         | custom delete[]         |
| Close files               | `fclose` on `FILE*`     |
| Release socket            | close()                 |
| Free custom API objects   | `myAPI_Destroy(handle)` |
| Debug/log memory releases | logging deleter         |
| Allocate using malloc     | free()                  |

⚡ Custom Deleters with Templates
Now the real power:
Templates + custom deleters = fully generic resource management

4️⃣ Template Function Accepting Deleter
template <typename T, typename D>
void processResource(std::unique_ptr<T, D> ptr) {
    // use ptr
}

Usage:
auto del = [](int* p){ delete p; };
std::unique_ptr<int, decltype(del)> p(new int(5), del);
processResource(std::move(p));

5️⃣ Generic Resource Wrapper (RAII) Using Template Deleter
This is how std::unique_ptr is actually designed internally:

template <typename T, typename Deleter>
class Resource {
    T* ptr;
    Deleter del;
  public:
    Resource(T* p, Deleter d) : ptr(p), del(d) {}
    ~Resource() { 
        del(ptr); 
    }
    T* get() { return ptr; }
};

Usage:
struct FCloseDeleter {
    void operator()(FILE* f) const { fclose(f); }
};

int main() {
    Resource<FILE, FCloseDeleter> file(fopen("a.txt","r"), FCloseDeleter());
}

6️⃣ Template Helper to Make Unique Pointer with Custom Deleter
template <typename T, typename D, typename... Args>
std::unique_ptr<T, D> make_unique_custom(D deleter, Args&&... args) {
    return std::unique_ptr<T, D>(new T(std::forward<Args>(args)...), deleter);
}


Usage:
auto deleter = [](int* p){
    cout << "Deleting custom\n";
    delete p;
};
auto ptr = make_unique_custom<int>(deleter, 100);

7️⃣ Type-Erased Deleter Using std::function
Good when you want run-time polymorphic deleters.
std::unique_ptr<int, std::function<void(int*)>> ptr(
    new int(10),
    [](int* p){ cout << "Deleting\n"; delete p; }
);

⭐ Advanced: Deleters affect unique_ptr size
✔ Deleter as empty functor = no size increase (EBO optimization)
struct EmptyDel { void operator()(int* p) const { delete p; } };
std::unique_ptr<int, EmptyDel> ptr;  // same size as raw pointer!
Because the deleter is stateless → gets optimized away.

📌 Summary
✔ Deleters define how smart pointers destroy the resource
✔ They can be:
Functions
Functors
Lambdas
std::function (type-erased)

✔ Deleters + templates =
Generic resource management
Custom RAII wrappers
Highly reusable C++ code





⭐ 1. Default Deleters
Every smart pointer has a default deleter:
✔ std::unique_ptr<T>
Deletes using delete.
If managing an array (unique_ptr<T[]>), uses delete[].
✔ std::shared_ptr<T>
Uses delete (unless constructed with custom deleter).

Example:
unique_ptr<int> up(new int(10));      // delete
unique_ptr<int[]> upArr(new int[10]); // delete[]

⭐ 2. Custom Deleters in unique_ptr
Syntax:
unique_ptr<T, Deleter> ptr;
The deleter affects:
How the resource is destroyed
The type size of the unique_ptr
(because the deleter type is part of it)

📌 Example 1 — Custom Functor Deleter
Functor:
struct FileCloser {
    void operator()(FILE* f) const {
        if (f) fclose(f);
    }
};
Usage:
unique_ptr<FILE, FileCloser> fp(fopen("data.txt", "r"));
Now when fp goes out of scope → file closes automatically.



📌 Example 2 — Lambda Deleter
auto deleter = [](int* p){
    cout << "Deleting int\n";
    delete p;
};
unique_ptr<int, decltype(deleter)> p(new int(5), deleter);



📌 Example 3 — Using free() Instead of delete
Useful when memory is allocated via malloc.
unique_ptr<int, decltype(&free)> p(
    (int*)malloc(sizeof(int)),
    free
);



⭐ 3. Custom Deleters in shared_ptr
Unlike unique_ptr, the deleter type does NOT affect the type of shared_ptr.
Why?
Because:
shared_ptr<T> stores the deleter inside the control block
It has type-erased

📌 Example:
shared_ptr<int> p(
    new int(10),
    [](int* ptr){
        cout << "Custom delete\n";
        delete ptr;
    }
);

⭐ 4. Array Deleters
Using unique_ptr<T[]>
unique_ptr<int[]> arr(new int[20]);  // automatically uses delete[]
Using custom array deleter:
unique_ptr<int, void(*)(int*)> arr(
    new int[10],
    [](int* p){ delete[] p; }
);



⭐ 5. Using Deleters for Non-Memory Resources
Smart pointers can manage ANY resource, not only heap memory.

Device handles
Mutex unlockers
File descriptors
Network sockets
📌 Example — Managing fopen Resource
auto fileCloser = [](FILE* f){ if(f) fclose(f); };
unique_ptr<FILE, decltype(fileCloser)> file(
    fopen("my.txt", "r"), fileCloser
);
📌 Example — Managing Mutex with RAII
unique_ptr<mutex, function<void(mutex*)>> lock(
    &m,
    [](mutex* m){ m->unlock(); }
);

m.lock();
// critical section

⭐ 6. Stateless Deleters = Zero-Cost
If a custom deleter is empty (sizeof(deleter)=1), the compiler may optimize it away.
Example:
struct NoopDeleter {
    void operator()(int*) const {}
};

unique_ptr<int, NoopDeleter> has the same size as raw pointer.



⭐ 7. Why Use Custom Deleters?
| Use Case                       | Example                           |
| ------------------------------ | --------------------------------- |
| Non-memory resources           | FILE*, sockets, mutex, DB handles |
| Different allocation mechanism | malloc/free, fopen/fclose         |
| Debugging memory               | print on delete                   |
| Avoiding delete[] mistakes     | unique_ptr<T[]>                   |




⭐ 8. Practical Examples
✔ Example: Shared_ptr with Custom Deleter to Close Socket
struct SocketCloser {
    void operator()(int* sock) const {
        close(*sock);
        delete sock;
    }
};
shared_ptr<int> sock(new int(fd), SocketCloser());
✔ Example: Array Managed by Shared_ptr
shared_ptr<int> arr(
    new int[10],
    [](int* p){ delete[] p; }
);



⭐ 9. Deleters and Performance
unique_ptr
Deleter type is part of the pointer type.
Can make the pointer bigger (if deleter carries state).

shared_ptr
Deleter stored in control block.
Does not affect type size.

⭐ 10. Summary
| Pointer Type | Deleter              | Affects Type? | Stored in         |
| ------------ | -------------------- | ------------- | ----------------- |
| `unique_ptr` | compile-time deleter | YES           | inside unique_ptr |
| `shared_ptr` | run-time deleter     | NO            | control block     |
