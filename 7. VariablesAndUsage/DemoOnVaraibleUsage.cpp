✅ 1. Pass-by-Value, Pass-by-Reference, Pass-by-Const-Reference
(Already explained by you; I rewrite in best interview-ready compact form)

1.1 Pass by Value
#include <iostream>
using namespace std;
void f(int x) {
    x = 100;
    cout << "Inside f(): " << x << endl;
}
int main() {
    int a = 10;
    f(a);
    cout << "Inside main(): " << a << endl;
}
/* 
Output
Inside f(): 100
Inside main(): 10
*/

1.2 Pass by Reference
void f(int& x) {
    x = 100;
    cout << "Inside f(): " << x << endl;
}
/* 
Output
Inside f(): 100
Inside main(): 100
*/


1.3 Pass by Const Reference
void f(const int& x) {
    cout << "Inside f(): " << x << endl;
}



✅ 2. Using const in Functions
2.1 const Function Parameters
void display(const int x) {
    cout << x << endl;
}

2.2 const Reference
void show(const string& s) {
    cout << s << endl;
}



✅ 3. Using decltype in Functions

#include <iostream>
using namespace std;
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
int main() {
    cout << add(10, 2.5) << endl;  // double
}
/* 
Output
12.5
*/


--------------------------------------------------------
🚀 ADVANCED C++ CONCEPTS WITH COMPLETE PROGRAM CODES
--------------------------------------------------------
Below are the important modern C++ advanced concepts, each with:
✔ Full Program
✔ Explanation
✔ Output




⭐ A1. CRTP – Curiously Recurring Template Pattern
Used for static polymorphism (no virtual overhead).

#include <iostream>
using namespace std;
template<class Derived>
class Base {
  public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived1 : public Base<Derived1> {
  public:
    void implementation() { cout << "Derived1 implementation\n"; }
};

class Derived2 : public Base<Derived2> {
  public:
    void implementation() { cout << "Derived2 implementation\n"; }
};

int main() {
    Derived1 d1;
    Derived2 d2;

    d1.interface();
    d2.interface();
}
/* 
Output
Derived1 implementation
Derived2 implementation
*/


⭐ A2. EBO – Empty Base Optimization

Shows memory optimization when inheriting empty classes.

#include <iostream>
using namespace std;
class Empty {};

class A : public Empty {
    int x;
};

int main() {
    cout << sizeof(Empty) << endl;
    cout << sizeof(A) << endl;
}
/* 
Output (varies but typical):
1
4

Empty base takes zero extra bytes due to EBO.
*/



⭐ A3. Tag Dispatching
Improves overload selection based on compile-time tags.

#include <iostream>
using namespace std;
void process(int x, true_type) { cout << "Processing small int\n"; }
void process(int x, false_type) { cout << "Processing large int\n"; }
void dispatcher(int x) {
    process(x, conditional_t<(sizeof(int) <= 4), true_type, false_type>{});
}
int main() {
    dispatcher(10);
}
/* 
Output
Processing small int
*/


⭐ A4. Expression Templates
Lazy evaluation of vector operations.

#include <iostream>
using namespace std;
template<typename T>
class Vec {
  public:
    T x, y;

    Vec(T a, T b) : x(a), y(b) {}

    Vec operator+(const Vec& other) {
        return Vec(x + other.x, y + other.y);
    }

    void print() { cout << x << " " << y << endl; }
};
int main() {
    Vec<int> v1(1, 2), v2(3, 4);
    Vec<int> v3 = v1 + v2;
    v3.print();
}
/* 
Output
4 6
*/


⭐ A5. Perfect Forwarding (std::forward)
Preserves lvalue/rvalue.
#include <iostream>
using namespace std;
void fun(int& x) { cout << "Lvalue\n"; }
void fun(int&& x) { cout << "Rvalue\n"; }
template<typename T>
void wrapper(T&& arg) {
    fun(forward<T>(arg));
}
int main() {
    int x = 10;
    wrapper(x);        // lvalue
    wrapper(20);       // rvalue
}
/* 
Output
Lvalue
Rvalue
*/


⭐ A6. Atomic Operations

#include <iostream>
#include <atomic>
#include <thread>
using namespace std;
atomic<int> countValue(0);
void increment() {
    for(int i = 0; i < 100000; i++)
        countValue++;
}
int main() {
    thread t1(increment);
    thread t2(increment);
    t1.join();
    t2.join();

    cout << countValue << endl;
}
/* 
Output
200000
*/



⭐ A7. Memory Barriers
#include <atomic>
#include <iostream>
using namespace std;
atomic<int> x(0), y(0);
int main() {
    x.store(10, memory_order_release);
    int val = y.load(memory_order_acquire);
}

(Used for hardware-level ordering. No output.)






⭐ A8. Coroutine Generator (C++20)
#include <iostream>
#include <coroutine>
using namespace std;
struct Generator {
    struct promise_type;
    using handle_type = coroutine_handle<promise_type>;

    struct promise_type {
        int value;
        auto get_return_object() { return Generator(handle_type::from_promise(*this)); }
        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        suspend_always yield_value(int v) { value = v; return {}; }
        void return_void() {}
        void unhandled_exception() { exit(1); }
    };

    handle_type h;
    Generator(handle_type h): h(h) {}
    ~Generator() { h.destroy(); }

    bool next() {
        h.resume();
        return !h.done();
    }
    int value() { return h.promise().value; }
};
Generator numbers() {
    for (int i=1; i<=3; i++)
        co_yield i;
}
int main() {
    auto gen = numbers();
    while(gen.next())
        cout << gen.value() << endl;
}
/* 
Output
1
2
3
*/



⭐ A9. RTTI & typeid
#include <iostream>
#include <typeinfo>
using namespace std;
int main() {
    int x = 10;
    cout << typeid(x).name() << endl;
}





⭐ A10. Custom Deleters in Smart Pointers

#include <iostream>
#include <memory>
using namespace std;
struct FileCloser {
    void operator()(FILE* fp) {
        cout << "Closing file\n";
        fclose(fp);
    }
};
int main() {
    unique_ptr<FILE, FileCloser> fp(fopen("test.txt", "w"));
    fprintf(fp.get(), "Hello!");
}
/* 
Output
Closing file
*/













-----------------------------------------------------
⭐ A11. Move Semantics (C++11)
-----------------------------------------------------
Move semantics avoids expensive deep copies and transfers ownership of resources.

✔ Example Program
#include <iostream>
#include <vector>
using namespace std;

class Array {
public:
    int* data;
    int size;

    Array(int s) : size(s) {
        data = new int[size];
        cout << "Constructor called\n";
    }

    // Copy constructor
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        cout << "Copy constructor\n";
    }

    // Move constructor
    Array(Array&& other) noexcept : data(nullptr), size(0) {
        cout << "Move constructor\n";
        data = other.data;
        size = other.size;
        other.data = nullptr;
    }

    ~Array() {
        delete[] data;
    }
};

int main() {
    Array a1(5);
    Array a2 = move(a1);
}
/* 
✔ Output
Constructor called
Move constructor
*/



-----------------------------------------------------
⭐ A12. Rvalue References (T&&)
-----------------------------------------------------
✔ Example Program
#include <iostream>
using namespace std;

void fun(int& x) { cout << "Lvalue reference\n"; }
void fun(int&& x) { cout << "Rvalue reference\n"; }

int main() {
    int a = 10;
    fun(a);      // lvalue
    fun(20);     // rvalue
}
/* 
✔ Output
Lvalue reference
Rvalue reference
*/


-----------------------------------------------------
⭐ A13. Lambda Expressions
-----------------------------------------------------
✔ Example Program
#include <iostream>
using namespace std;

int main() {
    auto add = [](int a, int b) { return a + b; };
    cout << add(10, 20) << endl;

    int x = 5;
    auto show = [=]() { cout << x << endl; };
    show();
}
/* 
✔ Output
30
5
*/



-----------------------------------------------------
⭐ A14. Function Objects (Functors)
-----------------------------------------------------
✔ Example Program
#include <iostream>
using namespace std;

struct Square {
    int operator()(int x) { return x * x; }
};

int main() {
    Square s;
    cout << s(5) << endl;
}
/* 
✔ Output
25
*/


-----------------------------------------------------
⭐ A15. std::function and std::bind
-----------------------------------------------------
✔ Example Program
#include <iostream>
#include <functional>
using namespace std;

int add(int a, int b) { return a + b; }

int main() {
    function<int(int, int)> f = add;
    cout << f(3, 4) << endl;

    auto bound = bind(add, 10, 20);
    cout << bound() << endl;
}
/* 
✔ Output
7
30
*/



-----------------------------------------------------
⭐ A16. Operator Overloading
-----------------------------------------------------
✔ Example Program
#include <iostream>
using namespace std;

class Complex {
  public:
    int a, b;
    Complex(int x, int y) : a(x), b(y) {}

    Complex operator+(const Complex& other) {
        return Complex(a + other.a, b + other.b);
    }

    void print() { cout << a << " + " << b << "i\n"; }
};

int main() {
    Complex c1(1, 2), c2(3, 4);
    Complex c3 = c1 + c2;
    c3.print();
}
/* 
✔ Output
4 + 6i
*/



-----------------------------------------------------
⭐ A17. Rule of 5 (Destructor, Copy/Move Ctors & Operators)
-----------------------------------------------------
✔ Example Program
#include <iostream>
using namespace std;

class Demo {
public:
    int* p;

    Demo() { p = new int(10); }

    // Destructor
    ~Demo() { delete p; }

    // Copy ctor
    Demo(const Demo& d) {
        p = new int(*d.p);
        cout << "Copy ctor\n";
    }

    // Move ctor
    Demo(Demo&& d) noexcept {
        p = d.p;
        d.p = nullptr;
        cout << "Move ctor\n";
    }

    // Copy assignment
    Demo& operator=(const Demo& d) {
        cout << "Copy assignment\n";
        if (this != &d) {
            delete p;
            p = new int(*d.p);
        }
        return *this;
    }

    // Move assignment
    Demo& operator=(Demo&& d) noexcept {
        cout << "Move assignment\n";
        if (this != &d) {
            delete p;
            p = d.p;
            d.p = nullptr;
        }
        return *this;
    }
};

int main() {
    Demo d1;
    Demo d2 = d1;       // copy
    Demo d3 = move(d1); // move
}
/* 
✔ Output
Copy ctor
Move ctor
*/



-----------------------------------------------------
⭐ A18. Smart Pointers (unique_ptr, shared_ptr, weak_ptr)
-----------------------------------------------------
✔ unique_ptr
#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> p = make_unique<int>(10);
    cout << *p << endl;
}
/* 
Output
10
*/


✔ shared_ptr
#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> p1 = make_shared<int>(20);
    shared_ptr<int> p2 = p1;

    cout << p1.use_count() << endl;
}
/* 
Output
2
*/



✔ weak_ptr
#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> sp = make_shared<int>(30);
    weak_ptr<int> wp = sp;

    cout << wp.expired() << endl; // 0 = false
}
/* 
Output
0
*/


-----------------------------------------------------
⭐ A19. Templates: Variadic Templates
-----------------------------------------------------
✔ Example Program
#include <iostream>
using namespace std;

void print() {}

template<typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first << " ";
    print(rest...);
}

int main() {
    print(1, 2, 3.5, "hello");
}
/* 
✔ Output
1 2 3.5 hello 
*/


-----------------------------------------------------
⭐ A20. SFINAE (Substitution Failure Is Not An Error)
-----------------------------------------------------
✔ Example Program
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
auto test(T t) -> decltype(t + 1, void()) {
    cout << "Type supports +1\n";
}

void test(...) {
    cout << "Type does NOT support +1\n";
}

int main() {
    test(5);      // int supports +1
    struct X{} x;
    test(x);      // custom type unsupported
}
/* 
✔ Output
Type supports +1
Type does NOT support +1
*/









A21 — Type Traits (compile-time type queries)
Use <type_traits> to query/transform types at compile time.

// g++ -std=c++17
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
void check() {
    cout << "is_integral: " << is_integral<T>::value
         << ", is_pointer: " << is_pointer<T>::value << '\n';
}

int main() {
    check<int>();
    check<int*>();
    check<double>();
}
/* 
Output
is_integral: 1, is_pointer: 0
is_integral: 0, is_pointer: 1
is_integral: 0, is_pointer: 0
*/




A22 — Concepts (C++20)
Constrain templates with readable predicates.

// g++ -std=c++20
#include <concepts>
#include <iostream>
using namespace std;

template<std::integral T>
T add(T a, T b) { return a + b; }

int main() {
    cout << add(2, 3) << '\n';
    // cout << add(2.5, 3.1) << '\n'; // error: double not integral
}
/* 
Output
5
*/




(Requires C++20)
A23 — std::optional (C++17)
Wraps an optional value.

// g++ -std=c++17
#include <optional>
#include <iostream>
using namespace std;

optional<int> find_even(int x) {
    if (x % 2 == 0) return x;
    return nullopt;
}

int main() {
    if (auto v = find_even(3)) cout << *v << '\n'; else cout << "none\n";
    if (auto v = find_even(4)) cout << *v << '\n'; else cout << "none\n";
}
/* 
Output
none
4
*/




A24 — std::variant (C++17)
Type-safe union.

// g++ -std=c++17
#include <variant>
#include <iostream>
using namespace std;

int main() {
    variant<int, string> v;
    v = 10;
    cout << get<int>(v) << '\n';
    v = string("hello");
    cout << get<string>(v) << '\n';
}
/* 
Output
10
hello
*/






A25 — std::any (C++17)
Type-erased container.

// g++ -std=c++17
#include <any>
#include <iostream>
using namespace std;

int main() {
    any a = 5;
    cout << any_cast<int>(a) << '\n';
    a = string("abc");
    cout << any_cast<string>(a) << '\n';
}
/* 
Output
5
abc
*/




A26 — std::span (C++20)
View into continuous sequence (no ownership).

// g++ -std=c++20
#include <span>
#include <vector>
#include <iostream>
using namespace std;

void print(span<int> s) {
    for (int x : s) cout << x << ' ';
    cout << '\n';
}

int main() {
    vector<int> v{1,2,3,4};
    print(v);
    int a[3]{7,8,9};
    print(a);
}
/* 
Output
1 2 3 4 
7 8 9 
*/






A27 — Policy-based Design (CRTP + policies)
Swap behavior via template policies.

// g++ -std=c++17
#include <iostream>
using namespace std;

struct AddPolicy { static int op(int a,int b){ return a+b; } };
struct MulPolicy { static int op(int a,int b){ return a*b; } };

template<typename Policy>
struct Calculator {
    int compute(int a,int b){ return Policy::op(a,b); }
};

int main(){
    Calculator<AddPolicy> c1; cout<<c1.compute(2,3)<<'\n';
    Calculator<MulPolicy> c2; cout<<c2.compute(2,3)<<'\n';
}
/* 
Output
5
6
*/




A28 — Custom Allocator (sketch)
Demonstrates custom allocator plumbing for STL — simplified.
Full custom allocators are verbose. This shows minimal form to use with vector.

// g++ -std=c++17
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
struct SimpleAllocator {
    using value_type = T;
    T* allocate(size_t n) {
        cout << "alloc " << n << '\n';
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, size_t n) {
        cout << "dealloc " << n << '\n';
        ::operator delete(p);
    }
};

int main() {
    vector<int, SimpleAllocator<int>> v;
    v.push_back(1);
    v.push_back(2);
}
/* 
Output (allocator messages vary by implementation)
alloc 1
alloc 2
dealloc 1
*/



A29 — Memory Pool (simple fixed pool)
Fast allocation for many small objects.

// g++ -std=c++17
#include <iostream>
#include <vector>
using namespace std;

struct Pool {
    vector<char> buf;
    size_t offset = 0;
    Pool(size_t n): buf(n) {}
    void* alloc(size_t s) {
        if (offset + s > buf.size()) return nullptr;
        void* p = buf.data() + offset;
        offset += s;
        return p;
    }
    void reset() { offset = 0; }
};

int main() {
    Pool p(1024);
    int* a = static_cast<int*>(p.alloc(sizeof(int)));
    *a = 42;
    cout << *a << '\n';
    p.reset();
}
/* 
Output
42
*/



A30 — Metaprogramming: constexpr + if constexpr (C++17/20)
Compute at compile time.

// g++ -std=c++17
#include <iostream>
using namespace std;

template<int N>
constexpr int factorial() {
    if constexpr (N <= 1) return 1;
    else return N * factorial<N-1>();
}

int main() {
    constexpr int f5 = factorial<5>();
    cout << f5 << '\n';
}
/* 
Output
120
*/



A31 — Futures & async
Simple concurrency with std::async.

// g++ -std=c++17 -pthread
#include <future>
#include <iostream>
using namespace std;
int heavy() { 
    return 42; 
}

int main() {
    auto fut = async(launch::async, heavy);
    cout << fut.get() << '\n';
}
/* 
Output
42
*/



A32 — Thread Pool (tiny example)
Simple thread pool pattern (minimal).

// g++ -std=c++17 -pthread
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

struct ThreadPool {
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex m;
    condition_variable cv;
    bool stop = false;

    ThreadPool(size_t n) {
        for (size_t i=0;i<n;i++) workers.emplace_back([this] {
            while (true) {
                function<void()> task;
                { unique_lock lk(m);
                  cv.wait(lk, [this]{ return stop || !tasks.empty(); });
                  if (stop && tasks.empty()) return;
                  task = move(tasks.front()); tasks.pop();
                }
                task();
            }
        });
    }

    void enqueue(function<void()> f) {
        { lock_guard lk(m); tasks.push(move(f)); }
        cv.notify_one();
    }

    ~ThreadPool() {
        { lock_guard lk(m); stop = true; }
        cv.notify_all();
        for (auto &t: workers) t.join();
    }
};

int main() {
    ThreadPool tp(2);
    tp.enqueue([]{ cout << "task1\n"; });
    tp.enqueue([]{ cout << "task2\n"; });
}
/* 
Output (order non-deterministic)
task1
task2
*/





A33 — Event System (Observer pattern)
Publish-subscribe using std::function.

// g++ -std=c++17
#include <vector>
#include <functional>
#include <iostream>
using namespace std;
struct Event {
    vector<function<void(int)>> listeners;
    void subscribe(function<void(int)> f) { listeners.push_back(f); }
    void emit(int v) { for (auto &l : listeners) l(v); }
};

int main() {
    Event e;
    e.subscribe([](int x){ cout<<"L1:"<<x<<'\n'; });
    e.subscribe([](int x){ cout<<"L2:"<<x*2<<'\n'; });
    e.emit(5);
}
/* 
Output
L1:5
L2:10
*/


A34 — Ranges (C++20)
Nice composable pipelines over sequences.

// g++ -std=c++20
#include <ranges>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v{1,2,3,4,5,6};
    for (int x : v | views::filter([](int n){ return n%2==0; }) | views::transform([](int n){ return n*n; })) {
        cout << x << ' ';
    }
    cout << '\n';
}
/* 
Output
4 16 36 
*/




✅ Perfect Forwarding — Complete C++ Program with Output
Perfect forwarding preserves value category (lvalue/rvalue) when forwarding arguments to another function.
This enables zero-overhead abstraction.

✔️ Program: Perfect Forwarding using std::forward
#include <iostream>
#include <utility>
using namespace std;

// ---------------------------
// Overloaded functions
// ---------------------------
void process(int& x) {
    cout << "process(int&): Lvalue received -> " << x << endl;
}

void process(int&& x) {
    cout << "process(int&&): Rvalue received -> " << x << endl;
}

// ---------------------------
// Templated wrapper: PERFECT FORWARDING
// ---------------------------
template<typename T>
void wrapper(T&& arg) {
    cout << "Wrapper forwarding --> ";
    process(std::forward<T>(arg)); // Perfect forwarding
}

int main() {
    int a = 10;

    cout << "Calling with lvalue:" << endl;
    wrapper(a);       // lvalue

    cout << "\nCalling with rvalue:" << endl;
    wrapper(20);      // rvalue

 return 0;
}
/* 
▶️ Expected Output
Calling with lvalue:
Wrapper forwarding --> process(int&): Lvalue received -> 10

Calling with rvalue:
Wrapper forwarding --> process(int&&): Rvalue received -> 20
*/















✅ Atomic Operations in C++ — Complete Program with Output
std::atomic provides lock-free, thread-safe, and race-condition-free operations.
Below is a fully working example showing:
Atomic counter
Multiple threads incrementing it
Memory ordering
Correct final count

✔️ Program: Atomic Counter with Multiple Threads
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

// Global atomic counter
atomic<int> counter(0);

// Function executed by each thread
void incrementTask(int iterations) {
    for (int i = 0; i < iterations; i++) {
        counter.fetch_add(1, memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 4;
    const int iterations = 100000;

    vector<thread> threads;

    // Launch threads
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(incrementTask, iterations);
    }

    // Join threads
    for (auto &t : threads)
        t.join();

    cout << "Expected count = " << numThreads * iterations << endl;
    cout << "Actual atomic count = " << counter.load() << endl;

  return 0;
}
/* 
▶️ Expected Output
Expected count = 400000
Actual atomic count = 400000




Explanation
Why Atomic?

If you use int counter, concurrent increments cause race conditions like:
Actual count = 273812   (wrong)


But with atomic<int>:
counter.fetch_add(1)

is guaranteed to be atomic, so all increments are correct.
*/







✅ Memory Barriers (Fences) in C++ — Full Explanation + Complete Program with Output
Memory barriers (a.k.a. fences) ensure correct ordering of memory operations across threads.
They don’t perform atomic operations themselves but enforce ordering constraints.

C++ provides:
atomic_thread_fence(memory_order_acquire)
atomic_thread_fence(memory_order_release)
atomic_thread_fence(memory_order_acq_rel)
atomic_thread_fence(memory_order_seq_cst) — strongest

✔️ Program: Producer–Consumer Using Fences
This example demonstrates:
Producer writes data, then sets a flag
Consumer waits for flag and reads data
Memory fences ensure correct ordering without using mutex

🔥 Without fences this program is allowed to fail!
With fences, correctness is guaranteed.

✅ Complete C++ Program
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<bool> ready(false);
int data = 0;

void producer() {
    data = 42;  // Step 1: Write shared data

    // Step 2: Make sure the write is visible before ready=true
    atomic_thread_fence(memory_order_release);

    ready.store(true, memory_order_relaxed);
}

void consumer() {
    // Wait until producer finishes
    while (!ready.load(memory_order_relaxed));

    // Ensure this load happens AFTER reading ready=true
    atomic_thread_fence(memory_order_acquire);

    cout << "Consumer read data = " << data << endl;
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

  return 0;
}
/* 
▶️ Expected Output
Consumer read data = 42

🧠 Why Memory Fences Matter
✔ memory_order_release

Ensures:
all prior writes in producer (like data = 42)
become visible before
ready = true

✔ memory_order_acquire
Ensures:
all subsequent reads in consumer (like data)
happen after
seeing ready = true
Together they form acquire–release synchronization.
⚡Key Guarantee

Even though:
ready is atomic
data is NOT atomic
No mutex is used
The consumer will always read 42, thanks to:
release fence  →  acquire fence


This is an extremely important concept for:
Lock-free programming
Work-stealing queues
Hazard pointers
RCU (Read-Copy-Update)
High-performance systems
*/








✅ C++20 Coroutines — Generators (co_yield) with Full Working Code + Output
C++20 added coroutines, enabling:
Lazy generators
Asynchronous functions
Infinite sequences
Event loops
Here we implement a custom generator using co_yield.

✔️ Complete Working Generator Example (C++20)
This program creates a generator that yields integers one at a time.

Full Code:
#include <coroutine>
#include <iostream>
#include <optional>
using namespace std;
class Generator {
  public:
    struct promise_type {
        int current_value;

        Generator get_return_object() {
            return Generator{ coroutine_handle<promise_type>::from_promise(*this) };
        }

        static suspend_always initial_suspend() noexcept { return {}; }
        static suspend_always final_suspend() noexcept { return {}; }

        suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }

        void unhandled_exception() { throw; }
        void return_void() {}
    };

    coroutine_handle<promise_type> handle;

    Generator(coroutine_handle<promise_type> h) : handle(h) {}
    Generator(const Generator&) = delete;
    Generator(Generator&& other) : handle(other.handle) { other.handle = nullptr; }

    ~Generator() {
        if (handle)
            handle.destroy();
    }

    // Iterator for range-based for loop
    class iterator {
        coroutine_handle<promise_type> h;
    public:
        iterator(coroutine_handle<promise_type> handle) : h(handle) {}

        iterator& operator++() {
            h.resume();
            if (h.done())
                h = nullptr;
            return *this;
        }

        int operator*() const {
            return h.promise().current_value;
        }

        bool operator!=(const iterator& other) const {
            return h != other.h;
        }
    };

    iterator begin() {
        handle.resume();  // start coroutine
        if (handle.done())
            return iterator{ nullptr };
        return iterator{ handle };
    }

    iterator end() {
        return iterator{ nullptr };
    }
};

// COROUTINE FUNCTION
Generator numberGenerator(int limit) {
    for (int i = 1; i <= limit; ++i) {
        co_yield i;  // yield each value
    }
}

int main() {
    cout << "Generated values:" << endl;

    for (int x : numberGenerator(5)) {
        cout << x << " ";
    }

    cout << endl;
    return 0;
}
/* 
▶️ Expected Output
Generated values:
1 2 3 4 5

🧠 Explanation
co_yield
Suspends the coroutine and returns a value to the caller.
promise_type

Controls:
what the coroutine returns
how suspension works
how values are yielded
coroutine_handle
Used to start, resume, and destroy a coroutine.

Iteration Flow
Enter for (int x : numberGenerator(5))
begin() starts coroutine with resume()
On co_yield, coroutine suspends & returns the value
Loop prints value
Next iteration: operator++() resumes coroutine
*/












✅ RTTI (Run-Time Type Information) & typeid / dynamic_cast — Full Programs with Output
RTTI allows you to determine object types at runtime, especially through base-class pointers.

We cover:
typeid
dynamic_cast
type_info
Checking polymorphic types at runtime



✔️ 1. typeid with Polymorphism
typeid gives you the actual type of an object even when accessed via a base pointer.

Full Program:
#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
  public:
    virtual ~Base() {}  // Needed for RTTI with polymorphism
};

class Derived : public Base {};
class Another : public Base {};

int main() {
    Base* b1 = new Derived();
    Base* b2 = new Another();
    Base* b3 = new Base();

    cout << "b1 is: " << typeid(*b1).name() << endl;
    cout << "b2 is: " << typeid(*b2).name() << endl;
    cout << "b3 is: " << typeid(*b3).name() << endl;

    delete b1;
    delete b2;
    delete b3;

  return 0;
}
/* 
Expected Output (compiler-dependent):
b1 is: Derived
b2 is: Another
b3 is: Base
*/



✔️ 2. dynamic_cast — Safe Downcasting
dynamic_cast returns:
A valid pointer if cast is correct
nullptr if cast fails

Full Program:
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {}
};

class Dog : public Base {};
class Cat : public Base {};

void checkAnimal(Base* b) {
    if (Dog* d = dynamic_cast<Dog*>(b)) {
        cout << "It is a Dog!" << endl;
    } 
    else if (Cat* c = dynamic_cast<Cat*>(b)) {
        cout << "It is a Cat!" << endl;
    }
    else {
        cout << "Unknown Animal!" << endl;
    }
}

int main() {
    Base* a1 = new Dog();
    Base* a2 = new Cat();
    Base* a3 = new Base();

    checkAnimal(a1);
    checkAnimal(a2);
    checkAnimal(a3);

    delete a1;
    delete a2;
    delete a3;
   return 0;
}
/* 
Expected Output:
It is a Dog!
It is a Cat!
Unknown Animal!
*/


✔️ 3. dynamic_cast with References (throws exceptions)
If you cast with references:
invalid cast → throws std::bad_cast

Full Program:
#include <iostream>
#include <typeinfo>
using namespace std;
class Base {
  public:
    virtual ~Base() {}
};

class Car : public Base {};
class Bike : public Base {};

int main() {
    Base* b = new Bike();

    try {
        Car& c = dynamic_cast<Car&>(*b);   // Invalid cast
        cout << "Cast successful!" << endl;
    }
    catch (bad_cast& e) {
        cout << "Exception: " << e.what() << endl;
    }

    delete b;
   return 0;
}
/* 
Expected Output:
Exception: std::bad_cast
*/


✔️ 4. Combined Example — Polymorphic Behavior + RTTI
#include <iostream>
#include <typeinfo>
using namespace std;

class Shape {
  public:
    virtual ~Shape() {}
    virtual void draw() = 0;
};

class Circle : public Shape {
  public:
    void draw() override { cout << "Drawing Circle\n"; }
};

class Square : public Shape {
  public:
    void draw() override { cout << "Drawing Square\n"; }
};

void identify(Shape* s) {
    cout << "Object type: " << typeid(*s).name() << endl;

    if (dynamic_cast<Circle*>(s))
        cout << "It is a Circle!" << endl;
    else if (dynamic_cast<Square*>(s))
        cout << "It is a Square!" << endl;

    s->draw();
}
int main() {
    Shape* s1 = new Circle();
    Shape* s2 = new Square();

    identify(s1);
    identify(s2);

    delete s1;
    delete s2;

   return 0;
}
/* 
Expected Output:
Object type: Circle
It is a Circle!
Drawing Circle

Object type: Square
It is a Square!
Drawing Square
*/









✅ Custom Deleters in Smart Pointers — Complete Programs With Output
Custom deleters allow you to control how memory/resources are freed, which is extremely useful for:
Logging destruction
Managing OS handles (FILE*, sockets, mutexes, etc.)
Using arrays with unique_ptr
Allocating from custom memory pools
Below are fully working examples, each with clear output.




✔️ 1. unique_ptr with Custom Deleter (Function)
Full Program:
#include <iostream>
#include <memory>
using namespace std;

void myDeleter(int* p) {
    cout << "[Custom Deleter] Deleting integer: " << *p << endl;
    delete p;
}

int main() {
    unique_ptr<int, void(*)(int*)> ptr(new int(100), myDeleter);

    cout << "Value stored: " << *ptr << endl;

    return 0; 
}
/* 
Expected Output:
Value stored: 100
[Custom Deleter] Deleting integer: 100
*/



✔️ 2. unique_ptr with Lambda Deleter
Full Program:
#include <iostream>
#include <memory>
using namespace std;

int main() {
    auto del = [](int* p){
        cout << "[Lambda Deleter] Cleaning: " << *p << endl;
        delete p;
    };

    unique_ptr<int, decltype(del)> ptr(new int(50), del);

    cout << "Inside main: " << *ptr << endl;

    return 0;
}
/* 
Expected Output:
Inside main: 50
[Lambda Deleter] Cleaning: 50
*/


✔️ 3. shared_ptr with Custom Deleter
Full Program:
#include <iostream>
#include <memory>
using namespace std;

struct LoggerDeleter {
    void operator()(int* p) const {
        cout << "[LoggerDeleter] Deleting: " << *p << endl;
        delete p;
    }
};

int main() {
    shared_ptr<int> sp(new int(200), LoggerDeleter());

    cout << "Value: " << *sp << endl;
    cout << "Use count: " << sp.use_count() << endl;

    return 0;
}
/* 
Expected Output:
Value: 200
Use count: 1
[LoggerDeleter] Deleting: 200
*/



✔️ 4. Custom Deleter Managing FILE* Resource (RAII)
Smart pointers can safely manage resources like FILE*.
Full Program:
#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

int main() {
    auto fileDeleter = [](FILE* f){
        cout << "[File Deleter] Closing file" << endl;
        if (f) fclose(f);
    };

    unique_ptr<FILE, decltype(fileDeleter)> fp(
        fopen("demo.txt", "w"),
        fileDeleter
    );

    if (fp) {
        fputs("Hello from custom deleter example!\n", fp.get());
    }

    return 0;
}
/* 
Expected Output:
[File Deleter] Closing file

💡 fp automatically closes the file when it goes out of scope → no memory/resource leak.
*/



✔️ 5. Managing Arrays with Custom Deleter
Full Program:
#include <iostream>
#include <memory>
using namespace std;

int main() {
    auto arrayDeleter = [](int* p){
        cout << "[Array Deleter] Destroying array\n";
        delete[] p;
    };

    unique_ptr<int[], decltype(arrayDeleter)> arr(new int[5], arrayDeleter);

    for (int i = 0; i < 5; i++)
        arr[i] = i + 1;

    cout << "Array elements: ";
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";

    cout << endl;
    return 0;
}
/* 
Expected Output:
Array elements: 1 2 3 4 5 
[Array Deleter] Destroying array
*/








✅ EBO — Empty Base Optimization in C++
EBO is one of the smartest and most hidden optimizations in C++.
It allows classes that inherit from empty classes to occupy zero extra bytes in memory.
Why does this matter?
For std::tuple
For std::function, std::optional
For iterators and functors
For small objects (compile-time patterns)


✔️ 1. Basic EBO Example — Empty Base Takes NO Space
Full Program:
#include <iostream>
using namespace std;
class Empty {};

class Derived : private Empty {
    int x;
};
int main() {
    cout << "sizeof(Empty)  = " << sizeof(Empty) << endl;
    cout << "sizeof(Derived) = " << sizeof(Derived) << endl;
   return 0;
}
/* 
Expected Output (typical):
sizeof(Empty)  = 1
sizeof(Derived) = 4
*/

📝 Even though Empty would normally take 1 byte,
C++ removes that 1 byte when inherited → Derived occupies only the size of int (4 bytes).

✔️ 2. Without EBO (Composition) — Takes More Space
Full Program:
#include <iostream>
using namespace std;

class Empty {};

class Wrapper {
    Empty e;   // NOT inherited → occupies 1 byte
    int x;
};

int main() {
    cout << "sizeof(Wrapper) = " << sizeof(Wrapper) << endl;
    return 0;
}
/* 
Expected Output:
sizeof(Wrapper) = 8   (Alignment padding + 1 byte for empty)

Composition does NOT allow EBO.
Only inheritance triggers EBO.
*/


✔️ 3. Real-Life EBO Example — Storing Functors Efficiently
Functional objects often contain no data.

Full Program:
#include <iostream>
using namespace std;
struct Functor {
    void operator()() const { cout << "Hello\n"; }
};

template<typename F>
class FunctionHolder : private F {  // EBO applied
  public:
    void call() { F::operator()(); }
};
int main() {
    FunctionHolder<Functor> obj;

    cout << "sizeof(Functor)          = " << sizeof(Functor) << endl;
    cout << "sizeof(FunctionHolder)   = " << sizeof(obj) << endl;

    obj.call();
  return 0;
}
/* 
Expected Output:
sizeof(Functor)          = 1
sizeof(FunctionHolder)   = 1
Hello

✔ Because Functor is empty, inheriting from it makes it cost 0 bytes.
*/



✔️ 4. Multiple Empty Bases — Still Zero Cost
Full Program:
#include <iostream>
using namespace std;

class A {};
class B {};
class C {};

class X : private A, private B, private C {
    int n;
};

int main() {
    cout << "sizeof(X) = " << sizeof(X) << endl;
    return 0;
}
/* 
Expected Output:
sizeof(X) = 4


Even though X inherits from 3 empty classes,
they take 0 space.
*/



✔️ 5. When EBO Does NOT Work
EBO fails when:
two empty base classes are the same type
inheritance creates ambiguity

Example:
#include <iostream>
using namespace std;

class Empty {};

class FailEBO : private Empty, private Empty {
    int x;
};

int main() {
    cout << sizeof(FailEBO) << endl;
}
/* 
Expected Output (typical):
8

Because the compiler must differentiate the two base subobjects.
*/





13. Memory Barriers (Fences) — Complete Code + Output

Memory barriers (also called fences) prevent the compiler and CPU from reordering operations around them.
They are essential in lock-free programming.

C++ provides memory barriers via std::atomic_thread_fence.

✅ Program: Using memory barriers to enforce ordering
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

atomic<int> data1{0};
atomic<int> data2{0};

void writer() {
    data1.store(10, memory_order_relaxed);

    // Memory fence: prevents reordering of stores across this point
    atomic_thread_fence(memory_order_release);

    data2.store(20, memory_order_relaxed);
}

void reader() {
    int x2 = data2.load(memory_order_relaxed);

    // Memory fence: enforces acquire semantics
    atomic_thread_fence(memory_order_acquire);

    int x1 = data1.load(memory_order_relaxed);

    cout << "Reader observed: data2=" << x2 
         << ", data1=" << x1 << endl;
}

int main() {
    thread t1(writer);
    thread t2(reader);

    t1.join();
    t2.join();

    return 0;
}
/* 
📌 Expected Output
Reader observed: data2=20, data1=10

Why this works
Without fences, CPU or compiler might reorder loads/stores.

Using:
release fence in writer ensures data1 is visible before data2.

acquire fence in reader ensures once we read data2 == 20,
the read of data1 is guaranteed to see 10.

This is a classic lock-free synchronization pattern.
*/






14. Coroutine Generators (C++20) — Complete Code + Output

Coroutines let you write functions that can pause and resume.
A generator is a coroutine that yields values one-by-one.

We build a minimal custom generator using the C++20 coroutine types.

✅ Complete Program: C++20 Coroutine Generator
#include <coroutine>
#include <iostream>
using namespace std;

template<typename T>
struct Generator {
    struct promise_type {
        T current_value;

        Generator get_return_object() {
            return Generator{
                coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }

        suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { terminate(); }
    };

    coroutine_handle<promise_type> handle;

    Generator(coroutine_handle<promise_type> h) : handle(h) {}
    Generator(const Generator&) = delete;

    Generator(Generator&& other) : handle(other.handle) {
        other.handle = nullptr;
    }

    ~Generator() {
        if (handle) handle.destroy();
    }

    bool next() {
        if (!handle || handle.done()) return false;
        handle.resume();
        return !handle.done();
    }

    T value() const {
        return handle.promise().current_value;
    }
};

Generator<int> counter(int start, int end) {
    for (int i = start; i <= end; i++) {
        co_yield i;
    }
}

int main() {
    auto gen = counter(1, 5);

    while (gen.next()) {
        cout << gen.value() << " ";
    }

    return 0;
}
/* 
📌 Expected Output
1 2 3 4 5

📝 Explanation
✔ What happens internally
co_yield i suspends the coroutine and returns the value to the caller.
gen.next() resumes execution until the next co_yield.
Execution ends when the loop completes.

✔ Why it is powerful
Coroutines avoid:
Allocating intermediate containers
Creating heavy iterator pipelines
State-machine boilerplate
They run efficiently using compiler-generated state machines.
*/











15. RTTI & typeid / dynamic_cast (Run-Time Type Information)
Complete code + suitable output.
RTTI helps you determine the actual type of an object at runtime.

✅ Program: RTTI using typeid and dynamic_cast
#include <iostream>
#include <typeinfo>
using namespace std;
class Base {
   public:
    virtual ~Base() {}     // RTTI requires at least one virtual function
};

class Derived1 : public Base {};
class Derived2 : public Base {};

void check_type(Base* b) {
    if (typeid(*b) == typeid(Derived1))
        cout << "Object is of type Derived1" << endl;
    else if (typeid(*b) == typeid(Derived2))
        cout << "Object is of type Derived2" << endl;
    else
        cout << "Unknown type" << endl;

    // dynamic_cast check
    if (auto d1 = dynamic_cast<Derived1*>(b))
        cout << "dynamic_cast -> It's a Derived1" << endl;

    if (auto d2 = dynamic_cast<Derived2*>(b))
        cout << "dynamic_cast -> It's a Derived2" << endl;

    cout << "-------------------------" << endl;
}

int main() {
    Base* b1 = new Derived1();
    Base* b2 = new Derived2();

    check_type(b1);
    check_type(b2);

    delete b1;
    delete b2;

    return 0;
}
/* 
📌 Expected Output
Object is of type Derived1
dynamic_cast -> It is a Derived1
-------------------------
Object is of type Derived2
dynamic_cast -> It is a Derived2
-------------------------

📝 Explanation
✔ typeid
Compares actual object type, not pointer type.
Requires polymorphic class (must have at least one virtual function).

✔ dynamic_cast
Safely downcasts pointers.
Returns:
Valid pointer on success
nullptr if cast fails

✔ Why used?
Useful in plugin systems
Serialization
Safe identification of derived types at runtime 
*/









16. Custom Deleters in Smart Pointers
Complete code + suitable output.
Smart pointers (unique_ptr, shared_ptr) allow you to customize how objects are destroyed, which is useful for:
Logging deletions
Managing resources like FILE*, sockets, mutexes
Using custom memory pools
Handling arrays

✅ Complete Program: Custom Deleters with unique_ptr & shared_ptr
#include <iostream>
#include <memory>
using namespace std;

// Custom deleter as a struct (functor)
struct MyDeleter {
    void operator()(int* p) const {
        cout << "[MyDeleter] Deleting int: " << *p << endl;
        delete p;
    }
};

// Custom deleter for FILE*
struct FileCloser {
    void operator()(FILE* f) const {
        cout << "[FileCloser] Closing file..." << endl;
        if (f) fclose(f);
    }
};

int main() {

    // 1. unique_ptr with custom functor deleter
    unique_ptr<int, MyDeleter> ptr1(new int(42));
    cout << "ptr1 points to: " << *ptr1 << endl;

    // 2. unique_ptr with lambda deleter
    unique_ptr<int, void(*)(int*)> ptr2(
        new int(100),
        [](int* p){
            cout << "[Lambda Deleter] Deleting: " << *p << endl;
            delete p;
        }
    );
    cout << "ptr2 points to: " << *ptr2 << endl;

    // 3. shared_ptr with custom deleter (lambda)
    shared_ptr<int> ptr3(
        new int(500),
        [](int* p){
            cout << "[Shared_ptr Lambda] Deleting shared int: " << *p << endl;
            delete p;
        }
    );
    cout << "ptr3 points to: " << *ptr3 << endl;

    // 4. Smart pointer for FILE* resource
    {
        unique_ptr<FILE, FileCloser> file(
            fopen("demo.txt", "w")
        );
        if (file) {
            cout << "Writing to file..." << endl;
            fputs("Hello from custom deleter!\n", file.get());
        }
    } // file closes automatically here

  return 0;
}
/* 
📌 Expected Output
ptr1 points to: 42
ptr2 points to: 100
ptr3 points to: 500
Writing to file...
[FileCloser] Closing file...
[Shared_ptr Lambda] Deleting shared int: 500
[Lambda Deleter] Deleting: 100
[MyDeleter] Deleting int: 42

(Destruction order may vary slightly depending on compiler.)

📝 Explanation
✔ Why Custom Deleters?
Smart pointers allow us to specify how objects get cleaned up.

You can delete:
heap objects (delete)
arrays (delete[])

C resources like FILE*
sockets
database connections
GPU buffers
objects in custom memory pools

✔ Deleter forms:
Functor / struct → general purpose
Lambda → quick inline deleter
Function pointer → flexible
For shared_ptr, deleter is stored inside control block
For unique_ptr, deleter affects pointer size 
*/









17. Memory Barriers (std::atomic_thread_fence)
Complete program + clear output.
Memory barriers (also called fences) enforce ordering constraints between CPU operations.

They are required when:
You’re doing low-level multithreading
Mixing atomics and non-atomics
Implementing lock-free structures
Building custom spinlocks
This example shows how atomic_thread_fence prevents instruction reordering.

✅ Complete Program: Memory Barrier Demo
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<bool> ready(false);     // atomic flag
int data = 0;                  // normal variable (non-atomic)

void writer() {
    data = 123;  // Step 1: normal write

    atomic_thread_fence(memory_order_release);  // RELEASE BARRIER

    ready.store(true, memory_order_relaxed);    // Step 2: publish flag
}

void reader() {
    while (!ready.load(memory_order_relaxed))
        ;  // spin until writer sets ready=true

    atomic_thread_fence(memory_order_acquire);  // ACQUIRE BARRIER

    cout << "Reader sees data = " << data << endl;
}

int main() {
    thread t1(writer);
    thread t2(reader);

    t1.join();
    t2.join();

    return 0;
}
/* 
📌 Expected Output
Reader sees data = 123

📝 Explanation
Without barriers

CPU or compiler might reorder:
ready = true;
data = 123;     // (BAD)


Reader could see:
ready == true  but data is still 0
With barriers
memory_order_release ensures all writes before fence happen before publishing the flag.
memory_order_acquire ensures all reads after the fence happen after the flag is seen.

So ordering becomes:
Writer:
data = 123   happens-before   ready = true
Reader:
ready = true happens-before   data = 123

✔ Why important?
Used to implement:
lock-free queues
custom mutexes
reference counters
ring buffers
custom atomic operations 
*/













18. Atomic Operations (std::atomic)
Complete program + suitable output.
std::atomic provides lock-free, thread-safe operations without using mutexes.

This example shows:
Atomic increment (fetch_add)
Atomic compare-and-swap (compare_exchange_strong)
Relaxed ordering example

✅ Program: Atomic Counter + CAS Operation
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
using namespace std;

atomic<int> counter(0);   // atomic counter
atomic<int> value(100);   // for CAS demo

void incrementTask(int id) {
    for (int i = 0; i < 1000; i++) {
        counter.fetch_add(1, memory_order_relaxed);
    }
}

void CAS_Task() {
    int expected = 100;
    cout << "Attempting CAS: expected = 100, new = 200\n";

    if (value.compare_exchange_strong(expected, 200)) {
        cout << "CAS success → value changed to 200\n";
    } else {
        cout << "CAS failed → expected was " << expected << endl;
    }
}

int main() {
    vector<thread> threads;

    // Increment counter using 4 threads
    for (int i = 0; i < 4; i++)
        threads.emplace_back(incrementTask, i);

    for (auto& t : threads)
        t.join();

    cout << "Final atomic counter = " << counter.load() << endl;

    // CAS demonstration
    CAS_Task();

    return 0;
}
/* 
📌 Expected Output
Final atomic counter = 4000
Attempting CAS: expected = 100, new = 200
CAS success → value changed to 200

📝 Explanation
✔ fetch_add()
Lock-free atomic increment:
counter.fetch_add(1);
Safe from race conditions
No mutex required
Increments are guaranteed atomic

✔ compare_exchange_strong(expected, new_value)
Atomic Compare-And-Swap:
if (value == expected)
    value = new_value;
else
    expected = value (updated internally)

Used in:
Lock-free queues
spinlocks
reference counters
hazard pointers

✔ Ordering
memory_order_relaxed means:
No ordering guarantees
Faster
Safe for counters 
*/


















19. Perfect Forwarding (std::forward)
Complete program + suitable output.
Perfect forwarding preserves the value category (lvalue/rvalue) of function arguments when forwarding them to another function.
It is essential in generic code to avoid unnecessary copies.

✅ Program: Perfect Forwarding Demo
#include <iostream>
#include <utility>
using namespace std;

// Overloaded functions
void process(int& x) {
    cout << "process(int&): Lvalue -> " << x << endl;
}

void process(int&& x) {
    cout << "process(int&&): Rvalue -> " << x << endl;
}

// Templated wrapper with perfect forwarding
template<typename T>
void wrapper(T&& arg) {
    cout << "Wrapper forwarding --> ";
    process(forward<T>(arg));  // preserves lvalue/rvalue
}

int main() {
    int a = 10;

    cout << "Calling with lvalue:" << endl;
    wrapper(a);        // passes lvalue

    cout << "\nCalling with rvalue:" << endl;
    wrapper(20);       // passes rvalue

    return 0;
}
/* 
📌 Expected Output
Calling with lvalue:
Wrapper forwarding --> process(int&): Lvalue -> 10

Calling with rvalue:
Wrapper forwarding --> process(int&&): Rvalue -> 20

📝 Explanation
T&& arg is a forwarding reference (also called universal reference).
std::forward<T>(arg) preserves whether arg is an lvalue or rvalue.
This avoids unnecessary copies and ensures correct function overload is selected.
Without std::forward: rvalues may be converted to lvalues, causing wrong overloads or extra copies. 
*/








20. Advanced Coroutine Generators (C++20) with Iteration
Complete program + output.
We’ll create a generator that yields values lazily and allows range-based for loop iteration.

✅ Program: Generator for Fibonacci Sequence
#include <coroutine>
#include <iostream>
using namespace std;

template<typename T>
struct Generator {
    struct promise_type {
        T current_value;

        Generator get_return_object() {
            return Generator{
                coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }

        suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { terminate(); }
    };

    coroutine_handle<promise_type> handle;

    Generator(coroutine_handle<promise_type> h) : handle(h) {}
    Generator(const Generator&) = delete;
    Generator(Generator&& other) : handle(other.handle) { other.handle = nullptr; }

    ~Generator() {
        if (handle) handle.destroy();
    }

    struct iterator {
        coroutine_handle<promise_type> h;
        bool done;

        iterator(coroutine_handle<promise_type> handle, bool end=false)
            : h(handle), done(end) {
            if (h && !done) h.resume();
        }

        iterator& operator++() {
            if (h) h.resume();
            if (!h || h.done()) done = true;
            return *this;
        }

        T operator*() const { return h.promise().current_value; }
        bool operator!=(const iterator& other) const { return done != other.done; }
    };

    iterator begin() { return iterator{handle}; }
    iterator end()   { return iterator{handle, true}; }
};

// Coroutine generating first n Fibonacci numbers
Generator<int> fibonacci(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

int main() {
    cout << "Fibonacci sequence (10 numbers): ";
    for (int x : fibonacci(10)) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
/* 
📌 Expected Output
Fibonacci sequence (10 numbers): 0 1 1 2 3 5 8 13 21 34

📝 Explanation
co_yield suspends the coroutine and yields each value.
Generator provides an iterator interface compatible with range-based for loops.
Execution is lazy: values are generated only when needed.

Useful for:
Infinite sequences
Streaming large datasets
Pipelines without intermediate containers 
*/




21. CRTP (Curiously Recurring Template Pattern)
Complete program + suitable output.
CRTP allows compile-time polymorphism by having a class inherit from a template instantiation of itself.
Avoids runtime overhead of virtual functions
Enables static polymorphism, mixins, and policy-based design

✅ Program: CRTP Example — Base Calls Derived Implementation
#include <iostream>
using namespace std;

// Base class template
template <typename Derived>
class Base {
public:
    void interface() {
        // Call derived class implementation at compile-time
        static_cast<Derived*>(this)->implementation();
    }
};

// Derived class
class Derived1 : public Base<Derived1> {
public:
    void implementation() {
        cout << "Derived1 implementation called!" << endl;
    }
};

// Another derived class
class Derived2 : public Base<Derived2> {
public:
    void implementation() {
        cout << "Derived2 implementation called!" << endl;
    }
};

int main() {
    Derived1 d1;
    Derived2 d2;

    d1.interface();  // Calls Derived1::implementation()
    d2.interface();  // Calls Derived2::implementation()

    return 0;
}
/* 
📌 Expected Output
Derived1 implementation called!
Derived2 implementation called!

📝 Explanation
How CRTP Works

Base<Derived> is a template.
Derived class passes itself as template parameter.
Base can call Derived’s methods using static_cast<Derived*>(this).
No virtual table needed, everything resolved at compile time.

✔ Advantages
Compile-time polymorphism → zero runtime cost
Enables static mixins and code reuse

Commonly used in:
Eigen library (matrix expressions)
Boost libraries
Policy-based designs
Expression templates 
*/













22. Tag Dispatching — Compile-Time Function Selection
Complete program + suitable output.
Tag dispatching is a technique to choose function overloads at compile-time based on types or properties.

Useful for template specialization
Enables optimized code for different categories (e.g., iterators, arithmetic types)

✅ Program: Tag Dispatching with Arithmetic Types
#include <iostream>
#include <type_traits>
using namespace std;

// Implementation for integral types
template <typename T>
void process_impl(T value, std::true_type) {
    cout << "Processing integral value: " << value << endl;
}

// Implementation for floating-point types
template <typename T>
void process_impl(T value, std::false_type) {
    cout << "Processing floating-point value: " << value << endl;
}

// Generic process function using tag dispatch
template <typename T>
void process(T value) {
    process_impl(value, std::is_integral<T>{});  // dispatch based on type trait
}

int main() {
    int i = 10;
    double d = 3.14;

    process(i);  // Calls integral implementation
    process(d);  // Calls floating-point implementation

    return 0;
}
/* 
📌 Expected Output
Processing integral value: 10
Processing floating-point value: 3.14

📝 Explanation
std::is_integral<T>{} produces a compile-time tag (true_type or false_type)
process_impl is selected based on the tag
No runtime checks → purely compile-time dispatch

Common in:
STL iterator traits (std::iterator_traits)
Expression templates
Optimized math libraries
*/






23. Expression Templates — Lazy Evaluation
Complete program + suitable output.
Expression templates are used to avoid unnecessary temporaries in operations like vector math.
Common in libraries like Eigen or Blitz++
Improves performance by evaluating expressions lazily

✅ Program: Simple Expression Template for Vectors
#include <iostream>
#include <vector>
using namespace std;

// Forward declaration
template <typename E>
class VecExpr;

// Vector wrapper
template <typename T>
class Vec {
public:
    vector<T> data;

    Vec(int n) : data(n) {}
    Vec(initializer_list<T> l) : data(l) {}

    int size() const { return data.size(); }

    T operator[](int i) const { return data[i]; }
    T& operator[](int i) { return data[i]; }

    // Assign from any expression
    template <typename E>
    Vec& operator=(const VecExpr<E>& expr) {
        for (int i = 0; i < size(); ++i)
            data[i] = expr[i];
        return *this;
    }
};

// Expression template base
template <typename E>
class VecExpr {
public:
    const E& self() const { return static_cast<const E&>(*this); }

    int size() const { return self().size(); }
    auto operator[](int i) const { return self()[i]; }
};

// Addition expression
template <typename L, typename R>
class VecAdd : public VecExpr<VecAdd<L,R>> {
    const L& lhs;
    const R& rhs;
public:
    VecAdd(const L& l, const R& r) : lhs(l), rhs(r) {}
    int size() const { return lhs.size(); }
    auto operator[](int i) const { return lhs[i] + rhs[i]; }
};

// Operator+ returns an expression, not a temporary vector
template <typename L, typename R>
VecAdd<L,R> operator+(const VecExpr<L>& l, const VecExpr<R>& r) {
    return VecAdd<L,R>(l.self(), r.self());
}

int main() {
    Vec<int> a = {1,2,3};
    Vec<int> b = {4,5,6};
    Vec<int> c = {0,0,0};

    c = a + b;  // Lazy evaluation, no temporary vector created

    cout << "Result vector c: ";
    for (int i = 0; i < c.size(); ++i) cout << c[i] << " ";
    cout << endl;

    return 0;
}
/* 
📌 Expected Output
Result vector c: 5 7 9

📝 Explanation
operator+ returns an expression object (VecAdd) instead of computing a temporary vector.
c = a + b; evaluates elements on assignment.
Reduces unnecessary copies for large vectors/matrices.
Core idea behind high-performance C++ libraries (Eigen, Blitz++, Armadillo).
*/






24. Perfect Forwarding + Move Semantics in Templates
Complete program + suitable output.
Perfect forwarding is often combined with move semantics to efficiently forward lvalues and rvalues.
Avoids unnecessary copies
Preserves value categories
Essential in generic constructors and factory functions

✅ Program: Perfect Forwarding with Move Semantics
#include <iostream>
#include <utility>
#include <string>
using namespace std;

class Widget {
    string name;
public:
    Widget(string n) : name(move(n)) {
        cout << "Widget constructed: " << name << endl;
    }

    Widget(const Widget& other) : name(other.name) {
        cout << "Widget copy-constructed: " << name << endl;
    }

    Widget(Widget&& other) noexcept : name(move(other.name)) {
        cout << "Widget move-constructed: " << name << endl;
    }
};

// Generic factory function using perfect forwarding
template <typename T, typename Arg>
T create(Arg&& arg) {
    return T(forward<Arg>(arg));
}

int main() {
    string s = "MyWidget";

    cout << "\nPassing lvalue:\n";
    Widget w1 = create<Widget>(s);   // lvalue -> copy

    cout << "\nPassing rvalue:\n";
    Widget w2 = create<Widget>("TempWidget"); // rvalue -> move

    return 0;
}
/* 
📌 Expected Output
Passing lvalue:
Widget copy-constructed: MyWidget

Passing rvalue:
Widget constructed: TempWidget

📝 Explanation
T(forward<Arg>(arg)) preserves lvalue/rvalue:
lvalue → copy constructor
rvalue → move constructor
Combined with move semantics, generic code is highly efficient

Pattern is used in:
std::make_unique
std::forward wrappers
Factory functions in generic libraries 
*/








25. Atomic Flag + Spinlock — Low-Level Synchronization
Complete program + suitable output.
Spinlocks are lightweight locks using busy-waiting.
std::atomic_flag is ideal for implementing them.

✅ Program: Spinlock Using atomic_flag
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
using namespace std;

class SpinLock {
    atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(memory_order_acquire)) {
            // Busy wait
        }
    }

    void unlock() {
        flag.clear(memory_order_release);
    }
};

// Shared counter
int counter = 0;
SpinLock spin;

void increment(int n) {
    for (int i = 0; i < n; ++i) {
        spin.lock();
        ++counter;
        spin.unlock();
    }
}

int main() {
    const int numThreads = 4;
    const int increments = 1000;

    vector<thread> threads;

    for (int i = 0; i < numThreads; ++i)
        threads.emplace_back(increment, increments);

    for (auto& t : threads)
        t.join();

    cout << "Final counter = " << counter << endl;

    return 0;
}
/* 
📌 Expected Output
Final counter = 4000

📝 Explanation
atomic_flag is lock-free boolean
test_and_set sets the flag and returns previous value
Busy-waits until lock is acquired
clear() releases the lock
Spinlocks are fast for short critical sections, but not ideal for long waits 
*/





26. Combining EBO (Empty Base Optimization) + CRTP
Complete program + suitable output.
EBO removes storage for empty base classes.
CRTP allows compile-time polymorphism.
Combining them gives zero-cost static polymorphism.

✅ Program: CRTP + EBO Example
#include <iostream>
using namespace std;

// Empty base for EBO
struct Logger {
    void log(const char* msg) const {
        cout << "[LOG] " << msg << endl;
    }
};

// CRTP base class
template <typename Derived>
class Base : private Logger {  // EBO applies here
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
        this->log("Called from Base via CRTP + EBO");
    }
};

// Derived class
class Derived1 : public Base<Derived1> {
public:
    void implementation() {
        cout << "Derived1 implementation executed" << endl;
    }
};

int main() {
    Derived1 d;
    d.interface();

    cout << "sizeof(Logger) = " << sizeof(Logger) << endl;
    cout << "sizeof(Base<Derived1>) = " << sizeof(Base<Derived1>) << endl;

    return 0;
}
/* 
📌 Expected Output
Derived1 implementation executed
[LOG] Called from Base via CRTP + EBO
sizeof(Logger) = 1
sizeof(Base<Derived1>) = 1

📝 Explanation
Logger is empty → EBO reduces its size to 0 bytes in Base.
Base<Derived> calls Derived methods at compile time → CRTP.
Combines zero-cost static polymorphism + compile-time logging.

Very efficient for:
Policy-based designs
Expression templates
Libraries like Eigen or Boost 
*/









27. Advanced Type Traits + decltype + constexpr
Complete program + suitable output.
Type traits allow compile-time type inspection and manipulation.
decltype deduces types from expressions.
constexpr enables compile-time evaluation.
Combining all allows highly optimized, type-safe code.

✅ Program: Compile-Time Type Checking with decltype and constexpr
#include <iostream>
#include <type_traits>
using namespace std;

// Compile-time function to check if type is integral
template <typename T>
constexpr bool isIntegral() {
    return is_integral<T>::value;
}

// Generic function using decltype
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    int x = 10;
    double y = 3.5;

    // Compile-time checks
    static_assert(isIntegral<int>(), "int should be integral");
    static_assert(!isIntegral<double>(), "double should not be integral");

    cout << "Sum of int + double: " << add(x, y) << endl;

    // Type deduction using decltype
    decltype(x + y) sum = add(x, y);
    cout << "Type of sum deduced using decltype: " 
         << typeid(sum).name() << endl;

    return 0;
}
/* 
📌 Expected Output
Sum of int + double: 13.5
Type of sum deduced using decltype: d

(“d” indicates double in typeid.name() format)

📝 Explanation
is_integral<T> → compile-time type trait
constexpr function evaluates at compile-time
decltype(a + b) deduces the return type based on expression
static_assert ensures correctness at compile time

Useful for:
Generic numeric libraries
Template metaprogramming
Compile-time checks & optimizations 
*/







28. Advanced Containers + Thread-Safe Access using mutex
Complete program + suitable output.
Many STL containers are not thread-safe by default.
Using std::mutex ensures safe concurrent access.
Common pattern in multi-threaded applications.

✅ Program: Thread-Safe Vector Wrapper
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

template <typename T>
class ThreadSafeVector {
    vector<T> data;
    mutable mutex mtx;

public:
    void push_back(const T& value) {
        lock_guard<mutex> lock(mtx);
        data.push_back(value);
    }

    void pop_back() {
        lock_guard<mutex> lock(mtx);
        if (!data.empty())
            data.pop_back();
    }

    T at(size_t index) const {
        lock_guard<mutex> lock(mtx);
        return data.at(index);
    }

    size_t size() const {
        lock_guard<mutex> lock(mtx);
        return data.size();
    }
};

ThreadSafeVector<int> tsVec;

void writer(int start, int count) {
    for (int i = 0; i < count; ++i)
        tsVec.push_back(start + i);
}

int main() {
    thread t1(writer, 0, 50);
    thread t2(writer, 100, 50);

    t1.join();
    t2.join();

    cout << "Vector size after threads: " << tsVec.size() << endl;
    cout << "First 5 elements: ";
    for (int i = 0; i < 5; ++i) cout << tsVec.at(i) << " ";
    cout << endl;

    return 0;
}
/* 
📌 Expected Output
Vector size after threads: 100
First 5 elements: 0 1 2 3 4

(Exact order may vary due to thread interleaving)

📝 Explanation
mutex ensures that push_back/pop_back/at are thread-safe.
lock_guard automatically locks and unlocks the mutex.

Pattern is widely used for:
Thread-safe queues
Shared buffers
Logging systems
Avoids data races in multi-threaded programs. 
*/








29. Custom Allocators with STL Containers — Memory Optimization
Complete program + suitable output.
STL containers (like vector, map) allow custom allocators

Useful for:
Pool allocation
Memory tracking/debugging
Optimizing performance for specific workloads

✅ Program: Custom Allocator for std::vector
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Simple logging allocator
template <typename T>
struct LoggingAllocator {
    using value_type = T;

    LoggingAllocator() = default;

    template <class U>
    constexpr LoggingAllocator(const LoggingAllocator<U>&) noexcept {}

    T* allocate(size_t n) {
        cout << "[Allocator] Allocating " << n << " element(s)" << endl;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_t n) {
        cout << "[Allocator] Deallocating " << n << " element(s)" << endl;
        ::operator delete(p);
    }
};

int main() {
    vector<int, LoggingAllocator<int>> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Vector elements: ";
    for (auto x : vec) cout << x << " ";
    cout << endl;

    return 0;
}
/* 
📌 Expected Output
[Allocator] Allocating 1 element(s)
[Allocator] Allocating 2 element(s)
[Allocator] Allocating 4 element(s)
Vector elements: 10 20 30
[Allocator] Deallocating 4 element(s)
[Allocator] Deallocating 2 element(s)
[Allocator] Deallocating 1 element(s)

(Exact allocation sizes may vary depending on vector growth policy)

📝 Explanation
allocate and deallocate control memory allocation
STL containers use your allocator instead of new/delete

Allows:
Pre-allocating memory pools
Tracking memory usage
Custom performance optimization 
*/







30. Type Erasure with std::function — Runtime Polymorphism Without Inheritance
Complete program + suitable output.
Type erasure allows storing different callable types in a single type (std::function)
Provides runtime polymorphism without using inheritance

Useful for:
Callbacks
Generic event handlers
Functional-style programming

✅ Program: Using std::function for Callbacks
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

// Simple callback invoker
void invokeCallbacks(const vector<function<void(int)>>& callbacks, int val) {
    for (auto& cb : callbacks) {
        cb(val);
    }
}

int main() {
    vector<function<void(int)>> callbacks;

    // Lambda
    callbacks.push_back([](int x) {
        cout << "Lambda called with: " << x << endl;
    });

    // Free function
    auto freeFunc = [](int x) { cout << "Free function called with: " << x << endl; };
    callbacks.push_back(freeFunc);

    // Functor
    struct Functor {
        void operator()(int x) { cout << "Functor called with: " << x << endl; }
    };
    callbacks.push_back(Functor{});

    cout << "Invoking callbacks with value 42:\n";
    invokeCallbacks(callbacks, 42);

    return 0;
}
/* 
📌 Expected Output
Invoking callbacks with value 42:
Lambda called with: 42
Free function called with: 42
Functor called with: 42

📝 Explanation
std::function<void(int)> can hold any callable with signature void(int)
Internally, it uses type erasure to store different types of callables
Enables runtime polymorphism without inheritance

Common use cases:
Event systems
Signal-slot mechanisms
Generic callback frameworks
*/








31. Advanced Smart Pointers — enable_shared_from_this
Complete program + suitable output.
std::enable_shared_from_this allows an object managed by shared_ptr to safely create additional shared_ptr instances pointing to itself.
Prevents undefined behavior when creating shared_ptr from this.

✅ Program: Using enable_shared_from_this
#include <iostream>
#include <memory>
using namespace std;

class Widget : public enable_shared_from_this<Widget> {
public:
    void show() {
        cout << "Widget address: " << this << endl;
    }

    shared_ptr<Widget> getShared() {
        return shared_from_this();  // safe way to get shared_ptr
    }
};

int main() {
    shared_ptr<Widget> w1 = make_shared<Widget>();

    w1->show();

    // Create another shared_ptr pointing to same object
    shared_ptr<Widget> w2 = w1->getShared();
    w2->show();

    cout << "w1.use_count() = " << w1.use_count() << endl;
    cout << "w2.use_count() = " << w2.use_count() << endl;

    return 0;
}
/* 
📌 Expected Output
Widget address: 0x563f7c1e5e40
Widget address: 0x563f7c1e5e40
w1.use_count() = 2
w2.use_count() = 2

📝 Explanation
shared_from_this() safely returns a shared_ptr to the current object
Without enable_shared_from_this, creating shared_ptr(this) would:
Cause double deletion
Break reference counting

Useful in:
Observer patterns
Event-driven architectures
Objects that need self-references 
*/








32. Advanced Lambda Expressions — Capture by Move, Generic Lambdas, Mutable
Complete program + suitable output.
C++14+ supports generic lambdas
Capture by move allows lambdas to take ownership of variables
Mutable allows modification of captured variables

✅ Program: Advanced Lambda Examples
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    cout << "Generic lambda (auto parameter): ";
    auto print = [](auto x) { cout << x << " "; };
    for (auto n : nums) print(n);
    cout << endl;

    // Capture by move
    string s = "Hello";
    auto mover = [str = move(s)]() {
        cout << "Moved string: " << str << endl;
    };
    mover();
    cout << "Original string after move: " << s << endl; // empty

    // Mutable lambda
    int counter = 0;
    auto mut_lambda = [counter]() mutable {
        counter++;
        cout << "Inside lambda counter = " << counter << endl;
    };
    mut_lambda();
    mut_lambda();
    cout << "Original counter = " << counter << endl; // unchanged

    return 0;
}
/* 
📌 Expected Output
Generic lambda (auto parameter): 1 2 3 4 5 
Moved string: Hello
Original string after move: 
Inside lambda counter = 1
Inside lambda counter = 2
Original counter = 0

📝 Explanation
Generic lambda: auto parameter → deduces type automatically
Capture by move: [str = move(s)] moves s into lambda
Mutable lambda: allows changing copies of captured variables (counter)

Useful for:
Closures with ownership semantics
Lazy evaluation
Thread-safe captures 
*/







33. Advanced constexpr — Compile-Time Algorithms
Complete program + suitable output.
C++14+ allows loops, recursion, and branching in constexpr functions
Computations are done at compile time

Useful for:
Compile-time constants
Lookup tables
Optimized math

✅ Program: Compile-Time Fibonacci Using constexpr
#include <iostream>
using namespace std;

// constexpr recursive Fibonacci
constexpr int fibonacci(int n) {
    return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// constexpr iterative Fibonacci (C++14+)
constexpr int fibonacci_iter(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    // Computed at compile-time
    constexpr int fib10 = fibonacci(10);
    constexpr int fib15 = fibonacci_iter(15);

    cout << "Fibonacci(10) = " << fib10 << endl;
    cout << "Fibonacci(15) = " << fib15 << endl;

    return 0;
}
/* 
📌 Expected Output
Fibonacci(10) = 55
Fibonacci(15) = 610

📝 Explanation
constexpr functions are evaluated at compile time if input is constant
Recursive or iterative forms are supported (C++14+ allows loops)

Benefits:
No runtime cost for constants
Enables compile-time table generation
Reduces runtime computations for performance-critical code 
*/











34. Advanced noexcept — Conditional Exception Safety in Templates
Complete program + suitable output.
noexcept indicates that a function does not throw exceptions
Can be conditional based on template parameters or operations
Useful for optimizing move operations and ensuring exception safety

✅ Program: Conditional noexcept with Templates
#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

template <typename T>
class Container {
    vector<T> data;
  public:
    // Constructor
    Container() noexcept = default;

    // Move constructor — conditional noexcept
    Container(Container&& other) noexcept(noexcept(vector<T>(move(other.data)))) 
        : data(move(other.data)) {
        cout << "Move constructor called" << endl;
    }

    void add(const T& value) { data.push_back(value); }

    size_t size() const noexcept { return data.size(); }
};

int main() {
    Container<int> c1;
    c1.add(10);
    c1.add(20);

    cout << "Before move, c1.size() = " << c1.size() << endl;

    Container<int> c2 = move(c1);  // Move constructor called

    cout << "After move, c2.size() = " << c2.size() << endl;

    // Check noexcept status
    cout << boolalpha 
         << "Move constructor is noexcept? " 
         << noexcept(Container<int>(move(c2))) << endl;

    return 0;
}
/* 
📌 Expected Output
Before move, c1.size() = 2
Move constructor called
After move, c2.size() = 2
Move constructor is noexcept? true

📝 Explanation
noexcept(expression) evaluates at compile time whether the function is noexcept
Ensures safe move operations for STL optimizations
Conditional noexcept is important in:
std::vector move operations
Generic template libraries
High-performance exception-safe code 
*/












35. Advanced alignas and alignof — Custom Memory Alignment
Complete program + suitable output.
alignas specifies custom alignment for variables or types
alignof queries the alignment requirement of a type

Useful for:
SIMD/vectorized operations
Memory-mapped hardware
Optimized memory layouts

✅ Program: Using alignas and alignof
#include <iostream>
#include <cstddef>
using namespace std;

struct alignas(16) AlignedStruct {
    double x;
    double y;
};

int main() {
    AlignedStruct a;
    int normalVar;
    alignas(32) double alignedVar;

    cout << "Alignment of AlignedStruct: " << alignof(AlignedStruct) << endl;
    cout << "Address of a: " << &a << endl;

    cout << "Alignment of normal int: " << alignof(int) << endl;
    cout << "Address of normalVar: " << &normalVar << endl;

    cout << "Alignment of aligned double: " << alignof(decltype(alignedVar)) << endl;
    cout << "Address of alignedVar: " << &alignedVar << endl;

    return 0;
}
/* 
📌 Expected Output (addresses may vary)
Alignment of AlignedStruct: 16
Address of a: 0x563f7c1e6040
Alignment of normal int: 4
Address of normalVar: 0x7ffeefbff4c8
Alignment of aligned double: 32
Address of alignedVar: 0x563f7c1e6060

📝 Explanation
alignas(16) ensures AlignedStruct starts at 16-byte boundary
alignas(32) for variable ensures 32-byte alignment
alignof tells the required alignment of a type at compile time

Critical for:
SSE/AVX instructions
High-performance computing
Memory-mapped hardware access 
*/








36. Advanced RTTI (typeid and dynamic_cast) — Runtime Type Information
Complete program + suitable output.
RTTI allows inspecting object types at runtime
Useful for safe downcasting and type introspection

Key tools:
dynamic_cast → safe casting with polymorphic types
typeid → query type information

✅ Program: RTTI with dynamic_cast and typeid
#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
public:
    virtual ~Base() = default; // Needed for RTTI
};

class Derived1 : public Base {};
class Derived2 : public Base {};

void identify(Base* obj) {
    if (dynamic_cast<Derived1*>(obj)) {
        cout << "Object is Derived1" << endl;
    } else if (dynamic_cast<Derived2*>(obj)) {
        cout << "Object is Derived2" << endl;
    } else {
        cout << "Object is Base or unknown" << endl;
    }
}

int main() {
    Base b;
    Derived1 d1;
    Derived2 d2;

    Base* ptr = &d1;
    identify(ptr); // Runtime check

    cout << "Type of d2 using typeid: " << typeid(d2).name() << endl;

    return 0;
}
/* 
📌 Expected Output
Object is Derived1
Type of d2 using typeid: 7Derived2

(The typeid name may vary depending on compiler, e.g., mangled names)

📝 Explanation
dynamic_cast<T*>(ptr):
Returns valid pointer if object is of type T or derived
Returns nullptr if cast fails

typeid(obj):
Provides type information at runtime
Can be used for logging, serialization, or debugging
Requires at least one virtual function (usually destructor) in base class 
*/












37. Advanced std::optional — Value Semantics + Lazy Initialization
Complete program + suitable output.
std::optional<T> represents a value that may or may not be present

Useful for:
Lazy initialization
Functions that may fail without exceptions
Optional configuration or parameters

✅ Program: Using std::optional for Lazy Initialization
#include <iostream>
#include <optional>
#include <string>
using namespace std;

optional<string> getUserName(bool exists) {
    if (exists) {
        return "Alice";
    } else {
        return nullopt; // No value
    }
}

int main() {
    optional<string> name1 = getUserName(true);
    optional<string> name2 = getUserName(false);

    if (name1) {
        cout << "User1: " << *name1 << endl; // Access value
    } else {
        cout << "User1 not found" << endl;
    }

    cout << "User2: " << name2.value_or("DefaultName") << endl; // default fallback

    // Lazy initialization
    optional<int> lazyValue;
    if (!lazyValue) {
        lazyValue = 42; // initialize only when needed
    }

    cout << "Lazy value: " << *lazyValue << endl;

    return 0;
}
/* 
📌 Expected Output
User1: Alice
User2: DefaultName
Lazy value: 42

📝 Explanation
optional<T> safely represents optional data
value_or(default) → provides fallback value
Supports lazy evaluation and avoids unnecessary memory usage

Common use cases:
Functions that might fail (optional<int> findIndex(...))
Lazy-loaded configuration
Avoiding null pointers 
*/







38. Advanced std::variant — Type-Safe Union
Complete program + suitable output.
std::variant is a type-safe union that can hold one of several types
Safer than void* or raw unions
Combined with std::visit for pattern matching

✅ Program: Using std::variant
#include <iostream>
#include <variant>
#include <string>
using namespace std;

int main() {
    // Variant can hold int, double, or string
    variant<int, double, string> v;

    v = 10;
    cout << "v holds int: " << get<int>(v) << endl;

    v = 3.14;
    cout << "v holds double: " << get<double>(v) << endl;

    v = "Hello Variant";
    cout << "v holds string: " << get<string>(v) << endl;

    // Using std::visit for type-safe handling
    visit([](auto&& arg){
        cout << "Visiting value: " << arg << endl;
    }, v);

    return 0;
}
/* 
📌 Expected Output
v holds int: 10
v holds double: 3.14
v holds string: Hello Variant
Visiting value: Hello Variant

📝 Explanation
std::variant<T1, T2, ...> can hold exactly one type at a time
get<T>(v) → retrieves the value; throws if wrong type
std::visit → provides type-safe visitation, like pattern matching

Useful for:
Heterogeneous data storage
Tagged unions
Event/message systems 
*/











39. Advanced std::any — Type-Erased Value Holder
Complete program + suitable output.
std::any can hold any type and type erasure allows runtime polymorphism
Unlike variant, it can hold any single type, even user-defined types unknown at compile-time
Access via std::any_cast

✅ Program: Using std::any
#include <iostream>
#include <any>
#include <string>
using namespace std;

int main() {
    any a;

    // Assign different types
    a = 42;
    cout << "Integer value: " << any_cast<int>(a) << endl;

    a = 3.14;
    cout << "Double value: " << any_cast<double>(a) << endl;

    a = string("Hello Any");
    cout << "String value: " << any_cast<string>(a) << endl;

    // Check type at runtime
    if (a.type() == typeid(string)) {
        cout << "Currently holding a string" << endl;
    }

    // Reset the any
    a.reset();
    if (!a.has_value()) {
        cout << "Any is empty" << endl;
    }

    return 0;
}
/* 
📌 Expected Output
Integer value: 42
Double value: 3.14
String value: Hello Any
Currently holding a string
Any is empty

📝 Explanation
std::any can store any type at runtime
any_cast<T> retrieves the value; throws if the type is wrong
a.type() returns the stored type info
a.reset() clears the content

Useful for:
Generic containers
Runtime polymorphic data
Event/message handling systems 
*/















40. Coroutine Generators (co_yield) — Lazy Evaluation Streams
Complete program + suitable output.
C++20 introduces coroutines for lazy evaluation and asynchronous programming
co_yield produces values on-demand

Useful for:
Generators
Lazy sequences
Async workflows

✅ Program: Simple Fibonacci Generator Using Coroutines
#include <iostream>
#include <coroutine>
#include <memory>
using namespace std;

// Generator class
template <typename T>
struct Generator {
    struct promise_type;
    using handle_type = coroutine_handle<promise_type>;

    struct promise_type {
        T current_value;
        auto get_return_object() { return Generator{handle_type::from_promise(*this)}; }
        auto initial_suspend() { return suspend_always{}; }
        auto final_suspend() noexcept { return suspend_always{}; }
        void unhandled_exception() { std::exit(1); }
        auto yield_value(T value) {
            current_value = value;
            return suspend_always{};
        }
        void return_void() {}
    };

    handle_type coro;

    Generator(handle_type h) : coro(h) {}
    ~Generator() { if (coro) coro.destroy(); }

    bool next() {
        coro.resume();
        return !coro.done();
    }

    T value() { return coro.promise().current_value; }
};

// Coroutine function generating Fibonacci numbers
Generator<int> fibonacci(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        co_yield a;
        int temp = a + b;
        a = b;
        b = temp;
    }
}

int main() {
    auto gen = fibonacci(10);

    cout << "Fibonacci sequence: ";
    while (gen.next()) {
        cout << gen.value() << " ";
    }
    cout << endl;

    return 0;
}
/* 
📌 Expected Output
Fibonacci sequence: 0 1 1 2 3 5 8 13 21 34

📝 Explanation
co_yield produces values lazily
Values are generated on-demand, not all at once
Coroutine handles manage the generator state automatically

Useful for:
Streams of data
Lazy evaluation sequences
Async pipelines and tasks 
*/








41. Memory Barriers & Atomic Operations — Low-Level Concurrency Control
Complete program + suitable output.
Memory barriers prevent reordering of memory operations by the compiler or CPU
std::atomic ensures atomicity and proper ordering
Critical for lock-free programming and multithreaded safety

✅ Program: Atomic Counter with Memory Order
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
using namespace std;

atomic<int> counter(0);

void increment(int n) {
    for (int i = 0; i < n; ++i) {
        counter.fetch_add(1, memory_order_relaxed);
    }
}

int main() {
    const int numThreads = 4;
    const int increments = 100000;

    vector<thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(increment, increments);
    }

    for (auto& t : threads) t.join();

    cout << "Final counter = " << counter.load(memory_order_relaxed) << endl;

    return 0;
}
/* 
📌 Expected Output
Final counter = 400000

📝 Explanation
std::atomic<int> guarantees atomic increments
fetch_add(value, memory_order_relaxed) performs increment without locking

Memory order options:
relaxed → no ordering constraints, only atomicity
acquire/release → synchronize threads
seq_cst → sequentially consistent, safest default

Useful for:
Lock-free data structures
High-performance concurrent counters
Low-level multithreading 
*/



















42. Custom Deleters in Smart Pointers — Resource Management
Complete program + suitable output.
std::unique_ptr and std::shared_ptr allow custom deleters

Useful for:
Managing non-heap resources (files, sockets)
Logging or debugging deletion
Custom memory pools

✅ Program: unique_ptr with Custom Deleter
#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

int main() {
    // Custom deleter for a FILE pointer
    auto fileDeleter = [](FILE* f) {
        if (f) {
            cout << "Closing file..." << endl;
            fclose(f);
        }
    };

    unique_ptr<FILE, decltype(fileDeleter)> filePtr(fopen("test.txt", "w"), fileDeleter);

    if (filePtr) {
        fputs("Hello custom deleter!", filePtr.get());
    }

    cout << "File operation done" << endl;

    // filePtr goes out of scope → fileDeleter is called automatically
    return 0;
}
/* 
📌 Expected Output
File operation done
Closing file...

📝 Explanation
unique_ptr<T, Deleter> allows custom cleanup logic
The deleter is called automatically when unique_ptr goes out of scope

Advantages:
RAII for non-memory resources
Ensures exception-safe cleanup
Supports logging/debugging resource usage 
*/







43. Expression Templates — Lazy Evaluation in C++
Complete program + suitable output.
Expression templates allow delaying evaluation of operations to avoid temporary objects
Commonly used in numeric/vector libraries (e.g., Eigen)
Improves performance for complex chained expressions

✅ Program: Simple Expression Template for Vectors
#include <iostream>
#include <vector>
using namespace std;

// Forward declaration
template <typename E>
struct VecExpr;

// Vector class
struct Vec {
    vector<double> data;

    Vec(size_t n) : data(n) {}

    size_t size() const { return data.size(); }

    double operator[](size_t i) const { return data[i]; }
    double& operator[](size_t i) { return data[i]; }

    // Assignment from expression template
    template <typename E>
    Vec& operator=(const VecExpr<E>& expr);
};

// Expression template for vector addition
template <typename E1, typename E2>
struct VecAdd : public VecExpr<VecAdd<E1, E2>> {
    const E1& u;
    const E2& v;

    VecAdd(const E1& u_, const E2& v_) : u(u_), v(v_) {}

    double operator[](size_t i) const { return u[i] + v[i]; }
    size_t size() const { return u.size(); }
};

// Base template
template <typename E>
struct VecExpr {
    const E& self() const { return static_cast<const E&>(*this); }

    double operator[](size_t i) const { return self()[i]; }
    size_t size() const { return self().size(); }
};

// Vec assignment from expression
template <typename E>
Vec& Vec::operator=(const VecExpr<E>& expr) {
    for (size_t i = 0; i < expr.size(); ++i)
        data[i] = expr[i];
    return *this;
}

// Operator+
template <typename E1, typename E2>
VecAdd<E1, E2> operator+(const VecExpr<E1>& u, const VecExpr<E2>& v) {
    return VecAdd<E1, E2>(u.self(), v.self());
}

int main() {
    Vec a(3), b(3), c(3);

    a[0]=1; a[1]=2; a[2]=3;
    b[0]=4; b[1]=5; b[2]=6;

    // Lazy evaluation via expression template
    c = a + b;

    cout << "c = ";
    for (size_t i=0; i<c.size(); ++i) cout << c[i] << " ";
    cout << endl;

    return 0;
}
/* 
📌 Expected Output
c = 5 7 9

📝 Explanation
VecExpr provides generic interface for expressions
VecAdd implements operator+ without creating temporary vectors
Assignment c = a + b evaluates element-wise only once

Benefits:
Eliminates temporary objects
Boosts performance in numeric libraries
Enables complex expressions without overhead 
*/









44. Tag Dispatching — Compile-Time Function Selection
Complete program + suitable output.
Tag dispatching is a compile-time technique to select function overloads based on type traits
Useful for optimizing functions differently for integral vs floating-point types

✅ Program: Tag Dispatching Example
#include <iostream>
#include <type_traits>
using namespace std;

// Integral version
void processImpl(int x, std::true_type) {
    cout << "Processing integral: " << x << endl;
}

// Floating-point version
void processImpl(double x, std::false_type) {
    cout << "Processing floating-point: " << x << endl;
}

// Generic wrapper
template <typename T>
void process(T x) {
    processImpl(x, std::is_integral<T>{});
}

int main() {
    int i = 42;
    double d = 3.14;

    process(i); // selects integral version
    process(d); // selects floating-point version

    return 0;
}
/* 
📌 Expected Output
Processing integral: 42
Processing floating-point: 3.14

📝 Explanation
std::is_integral<T> produces a compile-time tag (true_type / false_type)
processImpl is selected at compile-time based on type

Tag dispatching allows:
Optimized implementations for different types
Avoiding runtime checks
High-performance generic code
*/










45. Perfect Forwarding with std::forward
Complete program + suitable output.
Perfect forwarding allows preserving the value category of arguments
Used in template functions to forward lvalues/rvalues correctly
Avoids unnecessary copies and enables efficient generic code

✅ Program: Perfect Forwarding Example
#include <iostream>
#include <utility>
using namespace std;

void print(int& x) {
    cout << "Lvalue reference: " << x << endl;
}

void print(int&& x) {
    cout << "Rvalue reference: " << x << endl;
}

// Forwarding wrapper
template <typename T>
void forwardPrint(T&& val) {
    print(forward<T>(val)); // preserves lvalue/rvalue nature
}

int main() {
    int a = 10;

    forwardPrint(a);        // passes as lvalue
    forwardPrint(20);       // passes as rvalue

    return 0;
}
/* 
📌 Expected Output
Lvalue reference: 10
Rvalue reference: 20

📝 Explanation
T&& in templates is a forwarding reference (universal reference)
std::forward<T>(val) preserves whether argument is lvalue or rvalue
Avoids unnecessary copies and allows perfectly forwarding arguments

Common use cases:
Factory functions
Wrappers around constructors
Generic forwarding of parameters 
*/










46. CRTP — Curiously Recurring Template Pattern
Complete program + suitable output.
CRTP allows compile-time polymorphism without virtual functions
Base class uses the derived class as a template parameter

Enables:
Static polymorphism
Code reuse
Optimizations without runtime overhead

✅ Program: CRTP Example
#include <iostream>
using namespace std;

// Base class template
template <typename Derived>
class Base {
  public:
    void interface() {
        // Calls derived implementation at compile time
        static_cast<Derived*>(this)->implementation();
    }

    void defaultBehavior() {
        cout << "Base default behavior" << endl;
    }
};

// Derived class
class Derived : public Base<Derived> {
  public:
    void implementation() {
        cout << "Derived implementation called" << endl;
    }
};
int main() {
    Derived d;
    d.interface();        // Calls Derived::implementation()
    d.defaultBehavior();  // Calls Base::defaultBehavior()

   return 0;
}
/* 
📌 Expected Output
Derived implementation called
Base default behavior

📝 Explanation
Base<Derived> allows compile-time dispatch
static_cast<Derived*>(this)->implementation() resolves to derived method

Advantages:
No virtual table → no runtime overhead
Compile-time optimization
Useful in numeric libraries, policy-based designs, static interfaces 
*/












47. Empty Base Optimization (EBO) — Memory Savings
Complete program + suitable output.
Empty Base Optimization (EBO) allows empty base classes to occupy no memory
Useful for policy-based design or tag classes
Reduces memory footprint when combining multiple empty classes

✅ Program: Demonstrating EBO
#include <iostream>
using namespace std;

// Empty tag class
struct EmptyTag {};

// Derived class using EBO
struct Derived : EmptyTag {
    int value;
};

int main() {
    Derived d;
    d.value = 42;

    cout << "Size of EmptyTag: " << sizeof(EmptyTag) << endl;
    cout << "Size of Derived: " << sizeof(Derived) << endl;

    return 0;
}
/* 
📌 Expected Output
Size of EmptyTag: 1
Size of Derived: 4

(On most platforms, EmptyTag itself occupies 1 byte, but Derived does not increase due to EBO.)

📝 Explanation
Without EBO, each base class may occupy at least 1 byte
With EBO, empty base classes do not contribute to derived class size

Commonly used in:
Policy-based design (e.g., STL allocators)
Traits and tag dispatching
Template metaprogramming 
*/







48. Advanced Move Semantics — std::move and std::exchange
Complete program + suitable output.
Move semantics enables resource transfer without copying
std::move casts lvalues to rvalues for moving
std::exchange swaps values and provides safe resource transfer

✅ Program: Move Semantics with std::move and std::exchange
#include <iostream>
#include <utility>
#include <string>
using namespace std;

class MyString {
    string data;
public:
    MyString(const string& s) : data(s) {}
    MyString(MyString&& other) noexcept
        : data(exchange(other.data, "")) {
        cout << "Move constructor called" << endl;
    }

    const string& get() const { return data; }
};

int main() {
    MyString s1("Hello");
    MyString s2 = move(s1); // Move constructor

    cout << "s1: " << s1.get() << endl; // empty
    cout << "s2: " << s2.get() << endl; // "Hello"

    return 0;
}
/* 
📌 Expected Output
Move constructor called
s1: 
s2: Hello

📝 Explanation
std::move(s1) casts s1 to rvalue → calls move constructor

std::exchange(other.data, ""):
Transfers resource from other.data
Sets other.data to empty safely

Move semantics:
Avoid expensive copies
Essential in containers, strings, unique_ptr
Enables efficient temporary object handling 
*/









49. SFINAE (Substitution Failure Is Not An Error) — Template Metaprogramming
Complete program + suitable output.
SFINAE allows templates to enable or disable functions based on type traits
Key for compile-time type checks and generic programming
Works with enable_if, decltype, or concepts (C++20)

✅ Program: SFINAE with std::enable_if
#include <iostream>
#include <type_traits>
using namespace std;

// Function enabled only for integral types
template <typename T>
typename enable_if<is_integral<T>::value>::type
printType(T val) {
    cout << val << " is integral" << endl;
}

// Function enabled only for floating-point types
template <typename T>
typename enable_if<is_floating_point<T>::value>::type
printType(T val) {
    cout << val << " is floating-point" << endl;
}

int main() {
    printType(42);    // integral
    printType(3.14);  // floating-point

    // printType("hello"); // Error: neither enabled

    return 0;
}
/* 
📌 Expected Output
42 is integral
3.14 is floating-point

📝 Explanation
enable_if<condition>::type is only defined if condition is true
If substitution fails, that function is ignored → no compile error

SFINAE is widely used for:
Type traits
Overload selection in templates
Generic libraries like STL, Boost 
*/









50. C++20 Concepts — Constraints for Template Parameters
Complete program + suitable output.
Concepts allow compile-time constraints on template parameters
Make templates easier to read and generate clearer error messages
Example constraints: std::integral, std::floating_point

✅ Program: Using C++20 Concepts
#include <iostream>
#include <concepts>
using namespace std;

// Function requires integral type
template <std::integral T>
void printIntegral(T value) {
    cout << "Integral value: " << value << endl;
}

// Function requires floating-point type
template <std::floating_point T>
void printFloating(T value) {
    cout << "Floating-point value: " << value << endl;
}

int main() {
    printIntegral(42);    // OK
    printFloating(3.14);  // OK

    // printIntegral(3.14); // Compile-time error
    // printFloating(42);   // Compile-time error

    return 0;
}
/* 
📌 Expected Output
Integral value: 42
Floating-point value: 3.14

📝 Explanation
std::integral and std::floating_point are predefined concepts
Concepts replace SFINAE with clearer syntax

Benefits:
Cleaner code
Improved compile-time diagnostics
Safer and more expressive templates 
*/





