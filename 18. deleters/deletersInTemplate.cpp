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