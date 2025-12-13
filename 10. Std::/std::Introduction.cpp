
This document lists the **most important and commonly-used `std::` facilities introduced from C++11 through C++20**, 
grouped by standard version.

> ⚠️ Note: The C++ standard introduces **hundreds** of names each version. 
This is a **practical, interview + systems-level curated list**, not an ISO index dump.

Each entry includes:
* What it is / why it exists
* Minimal working example
* `main()`
* Output

---

# 🔵 C++11 (Modern C++ begins)
## 1. std::move
Forces move semantics (casts to rvalue).
```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> a = {1,2,3};
    vector<int> b = move(a);
    cout << "a size=" << a.size() << " b size=" << b.size();
}
/* 
**Output**
a size=0 b size=3
*/

## 2. std::forward
Preserves lvalue/rvalue category in templates.

#include <iostream>
using namespace std;
void f(int& ) { 
    cout << "lvalue"; 
}
void f(int&&) { 
    cout << "rvalue"; 
}

template<typename T>
void wrapper(T&& x) {
    f(forward<T>(x));
}

int main() {
    int a = 10;
    wrapper(a);
    cout << " ";
    wrapper(20);
}
/* 
**Output**
lvalue rvalue
*/

## 3. std::bind
Binds arguments to a callable.

#include <iostream>
#include <functional>
using namespace std;
int add(int a, int b) { 
    return a + b; 
}
int main() {
    auto add5 = bind(add, 5, placeholders::_1);
    cout << add5(3);
}
/* 
**Output**
8
*/

## 4. std::function
Type-erased callable wrapper.

#include <iostream>
#include <functional>
using namespace std;
int main() {
    function<int(int,int)> fn = [](int a,int b){return a+b;};
    cout << fn(2,3);
}
/* 
**Output**
5
*/


## 5. std::enable_if / std::enable_if_t
Compile-time SFINAE constraints.

#include <iostream>
#include <type_traits>
using namespace std;
template<typename T>
enable_if_t<is_integral<T>::value> print(T v) {
    cout << "Integral: " << v;
}
int main() {
    print(10);
}
/* 
**Output**
Integral: 10
*/


## 6. std::unique_ptr / std::shared_ptr
Smart pointers.

#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> p = make_unique<int>(42);
    cout << *p;
}
/* 
**Output**
42
*/


## 7. std::thread
Portable threading.

#include <iostream>
#include <thread>
using namespace std;
void work() { 
    cout << "Hello from thread"; 
}
int main() {
    thread t(work);
    t.join();
}
/* 
**Output**
Hello from thread
*/



# 🟢 C++14
## 8. std::make_unique
Safer unique_ptr creation.

#include <memory>
#include <iostream>
using namespace std;
int main() {
    auto p = make_unique<int>(7);
    cout << *p;
}

**Output**
7




# 🟡 C++17
## 9. std::optional
Represents optional value.

#include <iostream>
#include <optional>
using namespace std;
optional<int> get(bool ok) {
    if(ok) return 10;
    return nullopt;
}
int main() {
    auto v = get(true);
    cout << v.value();
}
/* 
**Output**
10
*/


## 10. std::variant
Type-safe union.

#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<int,string> v = "hello";
    cout << get<string>(v);
}
/* 
**Output**
hello
*/


## 11. std::any
Holds any type (runtime).

#include <iostream>
#include <any>
using namespace std;
int main() {
    any a = 5;
    cout << any_cast<int>(a);
}
/* 
**Output**
5
*/


## 12. std::launder
Fixes pointer aliasing after placement new.

#include <new>
#include <iostream>
using namespace std;
struct A { 
    int x; 
};
int main() {
    alignas(A) char buf[sizeof(A)];
    A* p = new(buf) A{10};
    cout << launder(p)->x;
}

**Output**
10




# 🔴 C++20
## 13. std::span
Non-owning view (pointer + size).

#include <iostream>
#include <span>
using namespace std;
void print(span<int> s) {
    for(int x: s) cout << x << " ";
}
int main() {
    int a[] = {1,2,3};
    print(a);
}
/* 
**Output**
1 2 3
*/



## 14. std::jthread
RAII thread with stop token.

#include <iostream>
#include <thread>
using namespace std;
int main() {
    jthread t([]{ cout << "auto-joined"; });
}
/* 
**Output**
auto-joined
*/



## 15. std::stop_token
Cooperative thread cancellation.

#include <iostream>
#include <thread>
using namespace std;
int main() {
    jthread t([](stop_token st){
        if(!st.stop_requested()) cout << "running";
    });
}
/* 
**Output**
running
*/



# ✅ Final takeaway
* **C++11**: language + threading + smart pointers
* **C++14**: usability fixes
* **C++17**: sum types, optionality, safety
* **C++20**: views, cancellation, ranges foundation


🔵 C++11 — language + threading + smart pointers
Demonstrates

Language: auto, lambda

Threading: std::thread

Smart pointer: std::unique_ptr

// C++11
#include <iostream>
#include <thread>
#include <memory>
using namespace std;

int main() {
    // Language feature: auto + lambda
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << "Lambda result: " << add(2, 3) << endl;

    // Smart pointer
    unique_ptr<int> ptr = make_unique<int>(42);
    cout << "unique_ptr value: " << *ptr << endl;

    // Threading
    thread t([] {
        cout << "Hello from thread" << endl;
    });

    t.join();  // mandatory in C++11

    return 0;
}

Output
Lambda result: 5
unique_ptr value: 42
Hello from thread

🟢 C++14 — usability fixes
Demonstrates

auto return type

Generic lambda

std::make_unique (C++14 addition)

// C++14
#include <iostream>
#include <memory>
using namespace std;

// auto return type (C++14)
auto multiply(int a, int b) {
    return a * b;
}

int main() {
    // Generic lambda
    auto printer = [](auto x) {
        cout << x << endl;
    };

    printer(multiply(3, 4));

    auto p = make_unique<string>("C++14 usability");
    printer(*p);

    return 0;
}

Output
12
C++14 usability

🟡 C++17 — sum types, optionality, safety
Demonstrates

std::optional → optionality

std::variant → sum type

if constexpr → compile-time safety

// C++17
#include <iostream>
#include <optional>
#include <variant>
#include <type_traits>
using namespace std;

optional<int> divide(int a, int b) {
    if (b == 0) return nullopt;
    return a / b;
}

template<typename T>
void printType(T v) {
    if constexpr (is_integral_v<T>)
        cout << "Integral: " << v << endl;
    else
        cout << "Non-integral" << endl;
}

int main() {
    // Optional
    auto r = divide(10, 2);
    if (r) cout << "Result: " << *r << endl;

    // Variant (sum type)
    variant<int, string> v = "C++17 variant";
    cout << get<string>(v) << endl;

    // Compile-time safety
    printType(100);

    return 0;
}

Output
Result: 5
C++17 variant
Integral: 100

🔴 C++20 — views, cancellation, ranges foundation
Demonstrates

std::span → view (pointer + size)

std::jthread → cancellation + RAII

std::ranges → algorithm foundation

// C++20
#include <iostream>
#include <span>
#include <thread>
#include <ranges>
#include <vector>
using namespace std;

void print(span<int> s) {
    for (int x : s)
        cout << x << " ";
    cout << endl;
}

int main() {
    // View: span
    int arr[] = {1, 2, 3, 4, 5};
    print(arr);

    // Cancellation + RAII thread
    jthread t([](stop_token st) {
        if (!st.stop_requested())
            cout << "jthread running" << endl;
    });

    // Ranges foundation
    vector<int> v = {1,2,3,4,5};
    auto even = v | views::filter([](int x){ return x % 2 == 0; });

    for (int x : even)
        cout << x << " ";
    cout << endl;

    return 0;
}

Output
1 2 3 4 5
jthread running
2 4

✅ Final mental model (now with code proof)
| Standard | What it *really* changed       | Seen in code                 |
| -------- | ------------------------------ | ---------------------------- |
| C++11    | Core language + concurrency    | lambda, thread, unique_ptr   |
| C++14    | Removed friction               | generic lambda, make_unique  |
| C++17    | Expressiveness + safety        | optional, variant, constexpr |
| C++20    | Views + structured concurrency | span, jthread, ranges        |




/* ====================================================================================== */

# 1️⃣ ISO-STYLE INDEX DUMP (CURATED BUT EXTENSIVE)
> Note: The real ISO index is thousands of names. Below is the **complete practical index** engineers are expected to know.

## 🔵 C++11

### Language / Utilities

* std::move — cast to rvalue
* std::forward — preserve value category
* std::declval — fake rvalue for type traits
* std::initializer_list — brace-init support
* std::nullptr_t — type-safe null
* std::result_of — callable return type (deprecated later)

/* ----------------------------------------------------- */
1️⃣ std::move — cast to rvalue
Program:
// std_move.cpp
#include <iostream>
#include <utility>
using namespace std;
void consume(int&& x) {
    cout << "Consumed rvalue: " << x << endl;
}
int main() {
    int a = 10;
    consume(std::move(a));   // lvalue → rvalue cast
    return 0;
}
/* 
Output
Consumed rvalue: 10
*/


2️⃣ std::forward — preserve value category
Program:
// std_forward.cpp
#include <iostream>
#include <utility>
using namespace std;

void detect(int&)  { 
    cout << "lvalue\n"; 
}
void detect(int&&) { 
    cout << "rvalue\n"; 
}

template<typename T>
void wrapper(T&& x) {
    detect(std::forward<T>(x));
}
int main() {
    int a = 5;
    wrapper(a);     // lvalue preserved
    wrapper(20);    // rvalue preserved
   return 0;
}
/* 
Output
lvalue
rvalue
*/



3️⃣ std::declval — fake rvalue for type traits
Program:
// std_declval.cpp
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;
struct A {
    double foo(int) { 
        return 3.14; 
    }
};
int main() {
    using Ret =
        decltype(declval<A>().foo(1));

    cout << boolalpha << is_same<Ret, double>::value << endl;
    return 0;
}
/* 
Output
true

📌 Key point:
declval<T>() is never executed — it exists only for type deduction.
*/



4️⃣ std::initializer_list — brace initialization
Program:
// std_initializer_list.cpp
#include <iostream>
#include <initializer_list>
using namespace std;
void print(initializer_list<int> list) {
    for (int x : list){
        cout << x << " ";
    }
    cout << endl;
}
int main() {
    print({1, 2, 3, 4});
  return 0;
}
/* 
Output
1 2 3 4
*/



5️⃣ std::nullptr_t — type-safe null
Program:
// std_nullptr_t.cpp
#include <iostream>
#include <cstddef>
using namespace std;
void func(int*) {
    cout << "int* overload\n";
}
void func(nullptr_t) {
    cout << "nullptr_t overload\n";
}
int main() {
    func(nullptr);   // unambiguous
  return 0;
}
/* 
Output
nullptr_t overload

📌 Fixes classic C ambiguity of NULL / 0.
*/



6️⃣ std::result_of — callable return type (C++11)
Program:
// std_result_of.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int main() {
    result_of<decltype(add)&(int,int)>::type r = add(2, 3);
    cout << r << endl;
    return 0;
}
/* 
Output
5

⚠️ Note
std::result_of is deprecated in C++17, replaced by:
std::invoke_result_t<F, Args...>
*/
/* ----------------------------------------------------- */
#include <iostream>
#include <type_traits>
#include <utility>
#include <initializer_list>
using namespace std;

/*---------------------------------------------------------
  1) std::move — cast to rvalue
---------------------------------------------------------*/
void take(int&& x) {
    cout << "take(int&&): " << x << endl;
}

/*---------------------------------------------------------
  2) std::forward — preserve value category
---------------------------------------------------------*/
void detect(int& )  { cout << "lvalue detected" << endl; }
void detect(int&& ) { cout << "rvalue detected" << endl; }

template<typename T>
void forward_wrapper(T&& x) {
    detect(std::forward<T>(x));
}

/*---------------------------------------------------------
  3) std::declval — fake rvalue for type traits
---------------------------------------------------------*/
struct Foo {
    double bar(int) { return 3.14; }
};

/*---------------------------------------------------------
  4) std::initializer_list — brace-init support
---------------------------------------------------------*/
void print_list(initializer_list<int> list) {
    for (int x : list)
        cout << x << " ";
    cout << endl;
}

/*---------------------------------------------------------
  5) std::nullptr_t — type-safe null
---------------------------------------------------------*/
void ptr_fn(int*) {
    cout << "pointer overload" << endl;
}

void ptr_fn(nullptr_t) {
    cout << "nullptr_t overload" << endl;
}

/*---------------------------------------------------------
  6) std::result_of — callable return type
---------------------------------------------------------*/
int add(int a, int b) {
    return a + b;
}

int main() {

    cout << "1) std::move\n";
    int a = 10;
    take(std::move(a));   // cast lvalue to rvalue

    cout << "\n2) std::forward\n";
    int x = 5;
    forward_wrapper(x);     // lvalue preserved
    forward_wrapper(20);    // rvalue preserved

    cout << "\n3) std::declval\n";
    // Ask: what is the return type of Foo::bar(int)?
    using ReturnType =
        result_of<decltype(&Foo::bar)(Foo, int)>::type;

    cout << "Return type of Foo::bar is double? "
         << is_same<ReturnType, double>::value << endl;

    cout << "\n4) std::initializer_list\n";
    print_list({1, 2, 3, 4});

    cout << "\n5) std::nullptr_t\n";
    ptr_fn(nullptr);   // unambiguous, type-safe null

    cout << "\n6) std::result_of\n";
    result_of<decltype(add)&(int, int)>::type r = add(2, 3);
    cout << "add(2,3) = " << r << endl;

    return 0;
}
/* 
Output:
1) std::move
take(int&&): 10

2) std::forward
lvalue detected
rvalue detected

3) std::declval
Return type of Foo::bar is double? 1

4) std::initializer_list
1 2 3 4

5) std::nullptr_t
nullptr_t overload

6) std::result_of
add(2,3) = 5
*/
/* ====================================================================================== */

### Type Traits

* std::is_same, is_integral, is_class, is_trivial
* std::enable_if
* std::conditional
* std::remove_reference / const / volatile
* std::add_lvalue_reference / rvalue_reference
/* ---------------------------------------- */
1️⃣ std::is_same, std::is_integral, std::is_class, std::is_trivial
Program:
// type_traits_basic.cpp
#include <iostream>
#include <type_traits>
using namespace std;

struct A {};
struct B { int x; };

int main() {
    cout << boolalpha;
    cout << "is_same<int, int>: " << is_same<int, int>::value << endl;
    cout << "is_integral<int>: " << is_integral<int>::value << endl;
    cout << "is_class<A>: " << is_class<A>::value << endl;
    cout << "is_trivial<B>: " << is_trivial<B>::value << endl;
   return 0;
}
/* 
Output
is_same<int, int>: true
is_integral<int>: true
is_class<A>: true
is_trivial<B>: true
*/




2️⃣ std::enable_if — SFINAE constraint
Program:
// enable_if.cpp
#include <iostream>
#include <type_traits>
using namespace std;
template<typename T>
typename enable_if<is_integral<T>::value>::type
print(T v) {
    cout << "Integral: " << v << endl;
}
int main() {
    print(10);
    // print(3.14); // ❌ compile-time error if uncommented
   return 0;
}
/* 
Output
Integral: 10

📌 Key idea: Function exists only if condition is true.
*/



3️⃣ std::conditional — compile-time if/else
Program:
// conditional.cpp
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    using SelectedType = conditional<true, int, double>::type;
    SelectedType x = 42;
    cout << x << endl;
   return 0;
}
/* 
Output
42

📌 Used heavily in templates and allocators.
*/



4️⃣ std::remove_reference
Program:
// remove_reference.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << boolalpha;

    cout << is_same<remove_reference<int&>::type, int>::value << endl;

   return 0;
}
/* 
Output
true
*/



5️⃣ std::remove_const / std::remove_volatile
Program
// remove_cv.cpp
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << boolalpha;

    cout << is_same<remove_const<const int>::type, int>::value << endl;
    cout << is_same< remove_volatile<volatile int>::type, int >::value << endl;

    return 0;
}
/* 
Output
true
true

📌 CV-removal is foundational for forwarding & traits.
*/



6️⃣ std::add_lvalue_reference / std::add_rvalue_reference
Program
// add_reference.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << boolalpha;
    cout << is_same<add_lvalue_reference<int>::type, int&>::value << endl;
    cout << is_same<add_rvalue_reference<int>::type, int&&>::value << endl;
  return 0;
}
/* 
Output
true
true
*/
/* ====================================================================================== */
### Smart Pointers

* std::unique_ptr
* std::shared_ptr
* std::weak_ptr
* std::default_delete

/* ------------------------ */
1️⃣ std::unique_ptr — exclusive ownership
Program
// unique_ptr.cpp
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> p = make_unique<int>(42);

    cout << "Value: " << *p << endl;

    unique_ptr<int> q = move(p);   // transfer ownership

    cout << "p is null? " << boolalpha << (p == nullptr) << endl;
    cout << "q value: " << *q << endl;

    return 0;
}
/* 
Output
Value: 42
p is null? true
q value: 42
*/



2️⃣ std::shared_ptr — shared ownership
Program:
// shared_ptr.cpp
#include <iostream>
#include <memory>
using namespace std;
int main() {
    shared_ptr<int> p1 = make_shared<int>(100);
    shared_ptr<int> p2 = p1;   // increase ref count

    cout << "p1 value: " << *p1 << endl;
    cout << "use_count: " << p1.use_count() << endl;

    return 0;
}
/* 
Output
p1 value: 100
use_count: 2

📌 Note: use_count() is for debugging only.
*/




3️⃣ std::weak_ptr — break cyclic ownership
Program:
// weak_ptr.cpp
#include <iostream>
#include <memory>
using namespace std;
int main() {
    shared_ptr<int> sp = make_shared<int>(200);
    weak_ptr<int> wp = sp;   // non-owning observer

    cout << "expired? " << boolalpha << wp.expired() << endl;

    if (auto locked = wp.lock()) {
        cout << "Locked value: " << *locked << endl;
    }

    sp.reset();   // destroy object

    cout << "expired after reset? " << wp.expired() << endl;

    return 0;
}
/* 
Output
expired? false
Locked value: 200
expired after reset? true
*/



4️⃣ std::default_delete — default deleter policy
Program:
// default_delete.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Resource {
    ~Resource() {
        cout << "Resource destroyed" << endl;
    }
};
int main() {
    unique_ptr<Resource, default_delete<Resource>> p(
        new Resource()
    );

    cout << "Using resource" << endl;

    return 0;   // default_delete calls delete
}
/* 
Output
Using resource
Resource destroyed
*/



🧠 Mental model (important)
unique_ptr
Stack            Heap
unique_ptr ───▶  Object

✔ One owner
✔ No refcount
✔ MISRA-friendly




shared_ptr
Stack        Heap
shared_ptr ─▶ control block ─▶ object

⚠️ Atomic refcount
⚠️ Non-deterministic destruction




weak_ptr
weak_ptr ──┐
           ├──▶ control block ─▶ object
shared_ptr ┘

✔ Breaks cycles
✔ No ownership




default_delete
-->Policy object
-->Calls delete or delete[]
-->Can be replaced with custom deleter

/* ====================================================================================== */
### Functional

* std::function
* std::bind
* std::mem_fn
* std::reference_wrapper

/* ------------------------------ */
1️⃣ std::function — type-erased callable
Program:
// function.cpp
#include <iostream>
#include <functional>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int main() {
    function<int(int,int)> f = add;
    cout << f(2, 3) << endl;
    return 0;
}
/* 
Output
5

📌 Stores any callable with a fixed signature.
*/



2️⃣ std::bind — bind arguments to callable
Program
// bind.cpp
#include <iostream>
#include <functional>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    auto add10 = bind(add, 10, placeholders::_1);
    cout << add10(5) << endl;
    return 0;
}
/* 
Output
15

⚠️ Interview note: Prefer lambdas in modern C++.
*/




3️⃣ std::mem_fn — wrap member functions
Program:
// mem_fn.cpp
#include <iostream>
#include <functional>
using namespace std;
struct Printer {
    void print(int x) const {
        cout << x << endl;
    }
};
int main() {
    Printer p;

    auto fn = mem_fn(&Printer::print);
    fn(p, 42);     // calls p.print(42)

    return 0;
}
/* 
Output
42

📌 Useful when passing member functions to algorithms.
*/





4️⃣ std::reference_wrapper — reference semantics in value contexts
Program:
// reference_wrapper.cpp
#include <iostream>
#include <functional>
using namespace std;
void increment(int& x) {
    x++;
}
int main() {
    int a = 10;

    reference_wrapper<int> ref = a;
    increment(ref);   // behaves like int&

    cout << a << endl;
    return 0;
}
/* 
Output
11

📌 Enables references inside STL containers.
 */


/* ====================================================================================== */
### Concurrency

* std::thread
* std::mutex, recursive_mutex
* std::lock_guard, unique_lock
* std::condition_variable
* std::atomic<T>
* std::future, std::promise
* std::async

/* -------------------------- */

1️⃣ std::thread — basic threading
Program
// thread.cpp
#include <iostream>
#include <thread>
using namespace std;
void work() {
    cout << "Hello from thread\n";
}
int main() {
    thread t(work);
    t.join();   // wait for completion
    cout << "Main done\n";
    return 0;
}
/* 
Output
Hello from thread
Main done
*/




2️⃣ std::mutex and std::recursive_mutex
Program
// mutex.cpp
#include <iostream>
#include <mutex>
using namespace std;
recursive_mutex mtx;
int counter = 0;
void increment(int depth) {
    if (depth == 0) return;
    lock_guard<recursive_mutex> lock(mtx);
    counter++;
    increment(depth - 1);
}
int main() {
    increment(3);
    cout << "Counter: " << counter << endl;
    return 0;
}
/* 
Output
Counter: 3

📌 recursive_mutex allows the same thread to lock multiple times.
*/




3️⃣ std::lock_guard vs std::unique_lock
Program
// lock_guard_unique_lock.cpp
#include <iostream>
#include <mutex>
using namespace std;
mutex m;
int main() {
    {
        lock_guard<mutex> lg(m);
        cout << "lock_guard locked\n";
    } // auto unlock

    unique_lock<mutex> ul(m);
    cout << "unique_lock locked\n";
    ul.unlock();
    cout << "unique_lock unlocked\n";

    return 0;
}
/* 
Output
lock_guard locked
unique_lock locked
unique_lock unlocked
*/







4️⃣ std::condition_variable — thread signaling
Program:
// condition_variable.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
mutex m;
condition_variable cv;
bool ready = false;
void worker() {
    unique_lock<mutex> lk(m);
    cv.wait(lk, [] { return ready; });
    cout << "Worker proceeding\n";
}
int main() {
    thread t(worker);

    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lg(m);
        ready = true;
    }
    cv.notify_one();

    t.join();
    return 0;
}
/* 
Output
Worker proceeding
*/





5️⃣ std::atomic<T> — lock-free synchronization
Program:
// atomic.cpp
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
atomic<int> counter(0);
void increment() {
    for (int i = 0; i < 1000; ++i)
        counter++;
}
int main() {
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Counter: " << counter << endl;
    return 0;
}
/* 
Output
Counter: 2000

📌 No mutex needed → lock-free.
*/





6️⃣ std::future and std::promise — value passing
Program:
// future_promise.cpp
#include <iostream>
#include <thread>
#include <future>
using namespace std;
void producer(promise<int> p) {
    p.set_value(42);
}
int main() {
    promise<int> p;
    future<int> f = p.get_future();

    thread t(producer, move(p));
    cout << "Received: " << f.get() << endl;

    t.join();
    return 0;
}
/* 
Output
Received: 42
*/






7️⃣ std::async — task-based concurrency
Program:
// async.cpp
#include <iostream>
#include <future>
using namespace std;
int compute() {
    return 10 + 20;
}
int main() {
    future<int> f = async(launch::async, compute);
    cout << "Result: " << f.get() << endl;
    return 0;
}
/* 
Output
Result: 30

📌 Execution policy:
launch::async → new thread
launch::deferred → lazy execution
*/


/* ====================================================================================== */
### Containers

* std::array
* std::forward_list
* std::unordered_map / unordered_set

/* ------------------------------ */
1️⃣ std::array — fixed-size, stack-allocated container
Program
// array.cpp
#include <iostream>
#include <array>
using namespace std;
int main() {
    array<int, 5> arr = {1, 2, 3, 4, 5};

    cout << "Size: " << arr.size() << endl;
    cout << "Elements: ";

    for (int x : arr)
        cout << x << " ";

    cout << endl;
    return 0;
}
/* 
Output
Size: 5
Elements: 1 2 3 4 5

📌 Key points
No heap allocation
STL-compatible
MISRA-friendly
*/



2️⃣ std::forward_list — singly linked list
Program
// forward_list.cpp
#include <iostream>
#include <forward_list>
using namespace std;

int main() {
    forward_list<int> fl = {10, 20, 30};

    fl.push_front(5);
    fl.pop_front();

    cout << "Elements: ";
    for (int x : fl)
        cout << x << " ";

    cout << endl;
    return 0;
}
/* 
Output
Elements: 10 20 30

📌 Key points
No size() (O(n))
Fast push_front
Lower memory than list
*/



3️⃣ std::unordered_map — hash map
Program
// unordered_map.cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> um;

    um["apple"] = 3;
    um["banana"] = 5;

    cout << "apple count: " << um["apple"] << endl;
    cout << "banana count: " << um["banana"] << endl;

    return 0;
}
/* 
Output
apple count: 3
banana count: 5

📌 Average O(1), worst-case O(n).
*/



4️⃣ std::unordered_set — hash set
Program
// unordered_set.cpp
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> us = {1, 2, 3};

    us.insert(4);
    us.insert(2);   // duplicate ignored

    cout << "Elements: ";
    for (int x : us)
        cout << x << " ";

    cout << endl;
    return 0;
}
/* 
Output
Elements: 1 2 3 4

⚠️ Order is not guaranteed.
*/


/* ====================================================================================== */

## 🟢 C++14

* std::make_unique
* std::exchange
* std::integer_sequence / index_sequence
* std::quoted


/* ----------------------------------- */

1️⃣ std::make_unique — safe unique_ptr creation
Program:
// make_unique.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Foo {
    Foo(int x) { cout << "Foo(" << x << ")\n"; }
};
int main() {
    auto ptr = make_unique<Foo>(42);
    cout << "Object owned\n";
  return 0;
}
/* 
Output
Foo(42)
Object owned

📌 Prevents memory leaks during construction.
*/



2️⃣ std::exchange — replace and return old value
Program:
// exchange.cpp
#include <iostream>
#include <utility>
using namespace std;
int main() {
    int x = 10;
    int old = exchange(x, 20);

    cout << "Old: " << old << endl;
    cout << "New: " << x << endl;
  return 0;
}
/* 
Output
Old: 10
New: 20

📌 Very useful in move constructors.
*/



3️⃣ std::integer_sequence / std::index_sequence
Program:
// integer_sequence.cpp
#include <iostream>
#include <utility>
using namespace std;
template <size_t... I>
void print(index_sequence<I...>) {
    ((cout << I << " "), ...);
    cout << endl;
}
int main() {
    print(make_index_sequence<5>{});
  return 0;
}
/* 
Output
0 1 2 3 4

📌 Compile-time index generation.
*/




4️⃣ std::quoted — safe quoted I/O
Program:
// quoted.cpp
#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    string s = "hello world";

    cout << quoted(s) << endl;

    string input;
    cin >> quoted(input);
    cout << input << endl;

  return 0;
}
/* 
Example Run
Input
"good morning"

Output
"hello world"
good morning

📌 Handles spaces and quotes correctly.
*/


/* ====================================================================================== */

Type trait aliases:

* std::enable_if_t
* std::conditional_t
* std::remove_reference_t


/* -------------------------- */

1️⃣ std::enable_if_t — SFINAE made readable
Program:
// enable_if_t.cpp
#include <iostream>
#include <type_traits>
using namespace std;
template <typename T>
enable_if_t<is_integral<T>::value>
print(T value) {
    cout << "Integral: " << value << endl;
}
int main() {
    print(10);      // OK
    // print(3.14); // ❌ compile-time error
  return 0;
}
/* 
Output
Integral: 10

📌 Cleaner alias for typename enable_if<...>::type.
*/



2️⃣ std::conditional_t — compile-time type selection
Program:
// conditional_t.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    conditional_t<(sizeof(int) > 2), int, short> value = 100;
    cout << value << endl;
  return 0;
}
/* 
Output
100

📌 Selects a type without runtime cost.
*/



3️⃣ std::remove_reference_t — strip references
Program:
// remove_reference_t.cpp
#include <iostream>
#include <type_traits>
using namespace std;
template <typename T>
void printType(T) {
    using Base = remove_reference_t<T>;
    cout << is_reference<T>::value << " "
         << is_reference<Base>::value << endl;
}
int main() {
    int x = 10;
    printType<int&>(x);
  return 0;
}
/* 
Output
1 0

📌 Commonly used in perfect forwarding internals.
*/

/* ====================================================================================== */

## 🟡 C++17

### Vocabulary Types

* std::optional
* std::variant
* std::any
* std::monostate

/* ------------------------ */

1️⃣ std::optional — value may or may not exist
Program:
// optional.cpp
#include <iostream>
#include <optional>
using namespace std;
optional<int> divide(int a, int b) {
    if (b == 0) return nullopt;
    return a / b;
}
int main() {
    auto r1 = divide(10, 2);
    auto r2 = divide(10, 0);

    if (r1)
        cout << *r1 << endl;
    if (!r2)
        cout << "No value" << endl;

  return 0;
}
/* 
Output
5
No value

📌 Eliminates magic return values.
*/


2️⃣ std::variant — type-safe union
Program
// variant.cpp
#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<int, double> v;

    v = 10;
    cout << get<int>(v) << endl;

    v = 3.14;
    cout << get<double>(v) << endl;

  return 0;
}
/* 
Output
10
3.14

📌 Safer replacement for union.
*/





3️⃣ std::any — store any type
Program
// any.cpp
#include <iostream>
#include <any>
using namespace std;
int main() {
    any a = 10;
    cout << any_cast<int>(a) << endl;

    a = string("hello");
    cout << any_cast<string>(a) << endl;

   return 0;
}
/* 
Output
10
hello

📌 Runtime type-erased storage.
*/





4️⃣ std::monostate — empty variant state
Program
// monostate.cpp
#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<monostate, int> v;

    if (holds_alternative<monostate>(v))
        cout << "Empty state" << endl;

    v = 42;
    cout << get<int>(v) << endl;

   return 0;
}
/* 
Output
Empty state
42

📌 Represents a meaningful “no-value” inside variant.
*/

/* ====================================================================================== */

### Utilities

* std::launder
* std::clamp
* std::size, std::data, std::empty
* std::apply
* std::invoke

/* -------------------------------- */

1️⃣ std::launder — pointer to new object at same storage
Used in low-level memory / placement-new scenarios

Program
// launder.cpp
#include <iostream>
#include <new>
using namespace std;
struct A {
    int x;
};
int main() {
    alignas(A) unsigned char buffer[sizeof(A)];

    A* p = new (buffer) A{10};
    cout << p->x << endl;

    p->~A();
    new (buffer) A{20};

    A* q = std::launder(reinterpret_cast<A*>(buffer));
    cout << q->x << endl;

    return 0;
}
/* 
Output
10
20

📌 Prevents undefined behavior after object lifetime restarts.
*/




2️⃣ std::clamp — constrain value to range
Program
// clamp.cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int x = 15;

    cout << clamp(x, 0, 10) << endl;
    cout << clamp(-5, 0, 10) << endl;

    return 0;
}
/* 
Output
10
0

📌 Safer than manual if checks.
*/




3️⃣ std::size — container size (generic)
Program
// size.cpp
#include <iostream>
#include <iterator>
using namespace std;
int main() {
    int arr[] = {1, 2, 3, 4};

    cout << size(arr) << endl;
  return 0;
}
/* 
Output
4

📌 Works for arrays and containers.
*/



4️⃣ std::data / std::empty
Program:
// data_empty.cpp
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3};

    cout << *data(v) << endl;
    cout << empty(v) << endl;

   return 0;
}
/* 
Output
1
0

📌 Uniform access to container internals.
*/



5️⃣ std::apply — unpack tuple into callable
Program
// apply.cpp
#include <iostream>
#include <tuple>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int main() {
    auto t = make_tuple(2, 3);
    cout << apply(add, t) << endl;
    return 0;
}
/* 
Output
5

📌 Compile-time tuple expansion.
*/



6️⃣ std::invoke — unified callable invocation
Program:
// invoke.cpp
#include <iostream>
#include <functional>
using namespace std;
struct Foo {
    int value() const { return 42; }
};
int main() {
    Foo f;

    cout << invoke(&Foo::value, f) << endl;
    cout << invoke([](int x) { return x * 2; }, 5) << endl;

    return 0;
}
/* 
Output
42
10

📌 Works for:
functions
lambdas
member functions
member data
*/


/* ====================================================================================== */

### Filesystem

* std::filesystem::path
* std::filesystem::exists, file_size

/* ------------------------------- */

1️⃣ std::filesystem::path — portable path abstraction
Program
// path.cpp
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
int main() {
    fs::path p = "example_dir/file.txt";

    cout << "Path: " << p << endl;
    cout << "Filename: " << p.filename() << endl;
    cout << "Parent path: " << p.parent_path() << endl;

  return 0;
}
/* 
Output
Path: example_dir/file.txt
Filename: file.txt
Parent path: example_dir


📌 fs::path handles:
/ vs \
concatenation
filename / extension extraction
*/



2️⃣ std::filesystem::exists and std::filesystem::file_size
Program
// exists_file_size.cpp
#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;
int main() {
    fs::path p = "test.txt";

    // create a file
    ofstream ofs(p);
    ofs << "Hello";
    ofs.close();

    if (fs::exists(p)) {
        cout << "File exists\n";
        cout << "File size: " << fs::file_size(p) << " bytes\n";
    }

    fs::remove(p); // cleanup
    return 0;
}
/* 
Output
File exists
File size: 5 bytes


📌 file_size works only for regular files
📌 Throws exception if file does not exist (unless using error_code overload)
*/



/* ====================================================================================== */

### Type Traits
* std::is_same_v, is_integral_v, etc.

/* ------------------------------------ */

1️⃣ std::is_same_v — check if two types are identical
Program
// is_same_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << is_same_v<int, int> << endl;
    cout << is_same_v<int, double> << endl;
    return 0;
}
/* 
Output
1
0

📌 Compile-time type equality check.
*/



2️⃣ std::is_integral_v — integral type check
Program:
// is_integral_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << is_integral_v<int> << endl;
    cout << is_integral_v<float> << endl;
    return 0;
}
/* 
Output
1
0

📌 True for int, char, bool, etc.
*/


3️⃣ std::is_floating_point_v
Program:
// is_floating_point_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << is_floating_point_v<double> << endl;
    cout << is_floating_point_v<int> << endl;
    return 0;
}
/* 
Output
1
0
*/


4️⃣ std::is_class_v — class/struct detection
Program:
// is_class_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;
struct Foo {};
enum Bar { A, B };
int main() {
    cout << is_class_v<Foo> << endl;
    cout << is_class_v<Bar> << endl;
    return 0;
}
/* 
Output
1
0

📌 True for class and struct, false for enums.
*/



5️⃣ std::is_pointer_v
Program:
// is_pointer_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << is_pointer_v<int*> << endl;
    cout << is_pointer_v<int> << endl;
    return 0;
}
/* 
Output
1
0
*/



6️⃣ std::is_reference_v
Program:
// is_reference_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << is_reference_v<int&> << endl;
    cout << is_reference_v<int> << endl;
    return 0;
}
/* 
Output
1
0
*/


7️⃣ std::is_const_v
Program:
// is_const_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << is_const_v<const int> << endl;
    cout << is_const_v<int> << endl;
    return 0;
}
/* 
Output
1
0
*/



8️⃣ std::is_trivial_v
Program:
// is_trivial_v.cpp
#include <iostream>
#include <type_traits>
using namespace std;
struct A {
    int x;
};
struct B {
    B() {}
};
int main() {
    cout << is_trivial_v<A> << endl;
    cout << is_trivial_v<B> << endl;
    return 0;
}
/* 
Output
1
0
*/



/* ====================================================================================== */

## 🔴 C++20

### Views / Ranges

* std::span
* std::ranges::sort, find
* std::views::filter, transform, take, drop

/* ------------------------------------- */

1️⃣ std::span — non-owning view (pointer + size)
// span.cpp
#include <iostream>
#include <span>
using namespace std;
void print(span<const int> s) {
    for (int x : s) cout << x << " ";
    cout << endl;
}
int main() {
    int arr[] = {1, 2, 3, 4};
    print(arr);          // array
    print(span{arr, 2}); // subspan
  return 0;
}
/* 
Output
1 2 3 4
1 2
*/


2️⃣ std::ranges::sort — range-aware sort
// ranges_sort.cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;
int main() {
    vector<int> v = {4, 1, 3, 2};
    ranges::sort(v);

    for (int x : v) cout << x << " ";
    cout << endl;
   return 0;
}
/* 
Output
1 2 3 4
*/


3️⃣ std::ranges::find — range-aware find
// ranges_find.cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;
int main() {
    vector<int> v = {10, 20, 30};

    auto it = ranges::find(v, 20);
    if (it != v.end())
        cout << "Found: " << *it << endl;

    return 0;
}
/* 
Output
Found: 20
*/



4️⃣ std::views::filter — lazy filtering
// views_filter.cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    auto even = v | views::filter([](int x){ return x % 2 == 0; });

    for (int x : even) cout << x << " ";
    cout << endl;
  return 0;
}
/* 
Output
2 4
*/



5️⃣ std::views::transform — lazy mapping
// views_transform.cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3};

    auto squares = v | views::transform([](int x){ return x * x; });

    for (int x : squares) cout << x << " ";
    cout << endl;
  return 0;
}
/* 
Output
1 4 9
*/



6️⃣ std::views::take — take first N elements
// views_take.cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    for (int x : v | views::take(3))
        cout << x << " ";
    cout << endl;

  return 0;
}
/* 
Output
1 2 3
*/


7️⃣ std::views::drop — skip first N elements
// views_drop.cpp
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    for (int x : v | views::drop(2))
        cout << x << " ";
    cout << endl;

  return 0;
}
/* 
Output
3 4 5
*/

/* ====================================================================================== */

### Concurrency

* std::jthread
* std::stop_token
* std::stop_source
* std::latch
* std::barrier

/* ----------------------- */

1️⃣ std::jthread — RAII thread with auto-join
Program
// jthread.cpp
#include <iostream>
#include <thread>
using namespace std;
void work() {
    cout << "Working in jthread\n";
}
int main() {
    jthread t(work);   // auto-joined on scope exit
    cout << "Main exiting\n";
  return 0;
}
/* 
Output
Working in jthread
Main exiting

📌 No need to call join() or detach().
*/




2️⃣ std::stop_token — cooperative cancellation
Program
// stop_token.cpp
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
void worker(stop_token st) {
    while (!st.stop_requested()) {
        cout << "Running...\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        break; // keep output deterministic
    }
    cout << "Stopped\n";
}
int main() {
    jthread t(worker);
    t.request_stop();   // signal stop
  return 0;
}
/* 
Output
Running...
Stopped

📌 Cancellation is cooperative, not forced.
*/



3️⃣ std::stop_source — explicit stop control
Program
// stop_source.cpp
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
void task(stop_token st) {
    if (st.stop_requested())
        cout << "Already stopped\n";
    else
        cout << "Running task\n";
}
int main() {
    stop_source src;
    stop_token tok = src.get_token();

    src.request_stop();   // request cancellation
    task(tok);

 return 0;
}
/* 
Output
Already stopped

📌 Allows external ownership of cancellation state.
*/




4️⃣ std::latch — one-time thread synchronization
Program
// latch.cpp
#include <iostream>
#include <thread>
#include <latch>
using namespace std;
int main() {
    latch done(2);

    auto worker = [&](int id) {
        cout << "Worker " << id << " done\n";
        done.count_down();
    };

    jthread t1(worker, 1);
    jthread t2(worker, 2);

    done.wait();   // wait until both finish
    cout << "All workers completed\n";

   return 0;
}
/* 
Output
Worker 1 done
Worker 2 done
All workers completed

📌 Latch cannot be reset.
*/



5️⃣ std::barrier — reusable synchronization point
Program:
// barrier.cpp
#include <iostream>
#include <thread>
#include <barrier>
using namespace std;
barrier sync_point(2, [] {
    cout << "Phase completed\n";
});
void worker(int id) {
    cout << "Worker " << id << " reached barrier\n";
    sync_point.arrive_and_wait();
}
int main() {
    jthread t1(worker, 1);
    jthread t2(worker, 2);
  return 0;
}
/* 
Output
Worker 1 reached barrier
Worker 2 reached barrier
Phase completed

📌 Barrier resets automatically after each phase.
*/



/* ====================================================================================== */

### Utilities

* std::bit_cast
* std::ssize
* std::endian
* std::type_identity

/* ---------------------------- */

1️⃣ std::bit_cast — safe bit-level reinterpretation

Requires trivially copyable types of the same size

Program
// bit_cast.cpp
#include <iostream>
#include <bit>
#include <cstdint>
using namespace std;

int main() {
    float f = 1.0f;
    uint32_t bits = bit_cast<uint32_t>(f);

    cout << "Float: " << f << endl;
    cout << "Bits : " << bits << endl;

    return 0;
}

Output
Float: 1
Bits : 1065353216


📌 Replaces reinterpret_cast + UB
📌 Compile-time checked

2️⃣ std::ssize — signed size of container/array
Program
// ssize.cpp
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};

    auto n = ssize(v);
    cout << n << endl;

    return 0;
}

Output
3


📌 Returns ptrdiff_t
📌 Prevents signed/unsigned comparison bugs

3️⃣ std::endian — byte order detection
Program
// endian.cpp
#include <iostream>
#include <bit>
using namespace std;

int main() {
    if constexpr (endian::native == endian::little)
        cout << "Little endian\n";
    else if constexpr (endian::native == endian::big)
        cout << "Big endian\n";
    else
        cout << "Mixed endian\n";

  return 0;
}
/* 
Output (most systems)
Little endian

📌 Compile-time constant
📌 Critical for networking / serialization
*/



4️⃣ std::type_identity — prevent type deduction
Program
// type_identity.cpp
#include <iostream>
#include <type_traits>
using namespace std;
template <typename T>
void print(type_identity_t<T> value) {
    cout << value << endl;
}
int main() {
    print<int>(42);
  return 0;
}
/* 
Output
42

📌 Used to block template argument deduction
📌 Important in TMP and overload control
*/
/* ====================================================================================== */

# 2️⃣ MEMORY MODEL DIAGRAMS (CORE UTILITIES)

## std::unique_ptr

```
Stack                  Heap
┌────────────┐         ┌──────────┐
│ unique_ptr │ ─────▶  │   int    │
│  (owns)    │         └──────────┘
└────────────┘
```

✔ Single owner
✔ Deterministic destruction

/* ----------------------- */

std::unique_ptr — single ownership, deterministic destruction
Program
// unique_ptr_demo.cpp
#include <iostream>
#include <memory>
using namespace std;

struct Resource {
    Resource() {
        cout << "Resource acquired\n";
    }
    ~Resource() {
        cout << "Resource released\n";
    }
};

int main() {
    cout << "Entering scope\n";

    {
        unique_ptr<Resource> ptr = make_unique<Resource>();
        cout << "Using resource\n";
    } // ptr goes out of scope → destructor called

    cout << "Exited scope\n";
    return 0;
}

Output
Entering scope
Resource acquired
Using resource
Resource released
Exited scope

🧠 Memory model (what actually happens)
Stack                            Heap
┌────────────────┐              ┌────────────────┐
│ unique_ptr ptr │ ───────────▶ │ Resource object│
│ (owns pointer) │              │                │
└────────────────┘              └────────────────┘
         │
         └─ destructor deletes heap object

✔ Why std::unique_ptr exists
| Property           | Explanation                  |
| ------------------ | ---------------------------- |
| **Single owner**   | Cannot be copied             |
| **Move-only**      | Ownership can be transferred |
| **RAII**           | Automatic cleanup            |
| **Zero overhead**  | Same size as raw pointer     |
| **Exception safe** | No leaks                     |

❌ What is NOT allowed (compile-time error)
unique_ptr<int> a = make_unique<int>(10);
unique_ptr<int> b = a;  // ❌ copy not allowed

✔ This prevents double delete bugs.

🔁 Ownership transfer (move semantics)
unique_ptr<int> a = make_unique<int>(10);
unique_ptr<int> b = move(a); // ownership moved

After move:
a == nullptr
b owns the object




/* ====================================================================================== */

## std::shared_ptr / weak_ptr

```
Stack        Heap (control block)
┌──────┐     ┌──────────────┐
│ sp   │ ──▶ │ refcount = 2 │ ──▶ object
└──────┘     │ weak = 1     │
             └──────────────┘
```

⚠️ Atomic refcount
⚠️ Heap control block

---
/* ------------------------------------ */

1️⃣ std::shared_ptr — shared ownership (refcounted)
Program
// shared_ptr_demo.cpp
#include <iostream>
#include <memory>
using namespace std;

struct Resource {
    Resource()  { cout << "Resource acquired\n"; }
    ~Resource() { cout << "Resource released\n"; }
};

int main() {
    cout << "Creating sp1\n";
    shared_ptr<Resource> sp1 = make_shared<Resource>();

    cout << "sp1 use_count: " << sp1.use_count() << endl;

    {
        cout << "Creating sp2 (shared owner)\n";
        shared_ptr<Resource> sp2 = sp1;

        cout << "sp1 use_count: " << sp1.use_count() << endl;
        cout << "sp2 use_count: " << sp2.use_count() << endl;
    } // sp2 destroyed

    cout << "After sp2 scope\n";
    cout << "sp1 use_count: " << sp1.use_count() << endl;

    cout << "Leaving main\n";
    return 0;
}

Output
Creating sp1
Resource acquired
sp1 use_count: 1
Creating sp2 (shared owner)
sp1 use_count: 2
sp2 use_count: 2
After sp2 scope
sp1 use_count: 1
Leaving main
Resource released

Memory model (shared_ptr)
Stack                 Heap (control block)              Heap (object)
┌──────┐              ┌──────────────────┐             ┌──────────┐
│ sp1  │ ──────────▶  │ strong = 1        │ ─────────▶ │ Resource │
└──────┘              │ weak   = 0        │             └──────────┘
       ┌──────┐       └──────────────────┘
       │ sp2  │ ─────▶ strong = 2
       └──────┘

2️⃣ std::weak_ptr — non-owning observer
Program
// weak_ptr_demo.cpp
#include <iostream>
#include <memory>
using namespace std;

struct Resource {
    Resource()  { cout << "Resource acquired\n"; }
    ~Resource() { cout << "Resource released\n"; }
};

int main() {
    weak_ptr<Resource> wp;

    {
        shared_ptr<Resource> sp = make_shared<Resource>();
        wp = sp;

        cout << "sp use_count: " << sp.use_count() << endl;
        cout << "wp expired: " << wp.expired() << endl;

        if (auto locked = wp.lock()) {
            cout << "Accessing resource\n";
        }
    } // last shared_ptr destroyed

    cout << "After shared_ptr scope\n";
    cout << "wp expired: " << wp.expired() << endl;

    if (!wp.lock())
        cout << "Cannot access resource\n";

    return 0;
}

Output
Resource acquired
sp use_count: 1
wp expired: 0
Accessing resource
Resource released
After shared_ptr scope
wp expired: 1
Cannot access resource

Memory model (weak_ptr)
Stack                 Heap (control block)              Heap (object)
┌──────┐              ┌──────────────────┐             ┌──────────┐
│ wp   │ ──────────▶  │ strong = 0        │   X──────▶ │ destroyed│
└──────┘              │ weak   = 1        │             └──────────┘
                      └──────────────────┘

⚠️ Important characteristics (interview gold)



/* ====================================================================================== */

## std::span

```
Stack only (non-owning)
┌──────────────┐
│ ptr ───────▶ │ data[]
│ size = N     │
└──────────────┘
```

✔ No allocation
✔ Lifetime NOT extended

---
/* -------------------------------- */

std::span — non-owning view (pointer + size)
Program
// span_demo.cpp
#include <iostream>
#include <span>
using namespace std;

void print(span<const int> s) {
    cout << "Span size: " << s.size() << endl;
    for (int x : s)
        cout << x << " ";
    cout << endl;
}
int main() {
    int data[] = {1, 2, 3, 4};
    cout << "Creating span\n";
    span<int> s(data);      // ptr + size only

    print(s);

    cout << "Modifying through span\n";
    s[0] = 99;

    print(s);

    cout << "Original array reflects change\n";
    for (int x : data)
        cout << x << " ";
    cout << endl;
   return 0;
}
/* 
Output
Creating span
Span size: 4
1 2 3 4
Modifying through span
Span size: 4
99 2 3 4
Original array reflects change
99 2 3 4
*/

🧠 Memory model (exactly as you drew)
Stack only
┌──────────────────┐
│ span s           │
│ ├─ ptr ─────────▶│ data[] (elsewhere)
│ └─ size = 4      │
└──────────────────┘

span does not own
span does not allocate
span does not delete

⚠️ Lifetime rule (VERY IMPORTANT)
span<int> s;{
    int arr[] = {1, 2, 3};
    s = arr;     // ❌ dangling after scope
} // arr destroyed
// s is now INVALID

✔ Compiler will NOT warn you
✔ This is a logic error, not UB until used


/* ====================================================================================== */

## std::optional

```
Stack
┌──────────────┐
│ engaged flag │
│ storage T    │
└──────────────┘
```

✔ No heap
✔ Explicit absence

---
/* ------------------------ */

std::optional — value + engaged flag (stack-only)
Program:
// optional_demo.cpp
#include <iostream>
#include <optional>
using namespace std;
struct Data {
    int x;
    Data(int v) : x(v) {
        cout << "Data(" << x << ") constructed\n";
    }
    ~Data() {
        cout << "Data(" << x << ") destroyed\n";
    }
};
optional<Data> makeData(bool create) {
    if (create)
        return Data{42};   // engaged
    return nullopt;        // disengaged
}
int main() {
    cout << "Creating optional with value\n";
    optional<Data> a = makeData(true);

    if (a)
        cout << "Value: " << a->x << endl;

    cout << "Resetting optional\n";
    a.reset();   // destroys contained object

    cout << "Creating empty optional\n";
    optional<Data> b = makeData(false);

    cout << "b engaged: " << b.has_value() << endl;
   return 0;
}
/* 
Output
Creating optional with value
Data(42) constructed
Value: 42
Resetting optional
Data(42) destroyed
Creating empty optional
b engaged: 0
*/


🧠 Memory model (exactly as you drew)
Stack
┌────────────────────┐
│ optional<Data>     │
│ ├─ engaged flag    │
│ └─ inline storage  │
└────────────────────┘

Storage is inline
No allocation
Destructor runs on reset() or scope exit

/* ====================================================================================== */

## std::variant

```
Stack
┌────────────────────┐
│ active index       │
│ union storage max  │
└────────────────────┘
```

✔ Type-safe union
✔ One active alternative

---
/* -------------------- */

std::variant — tagged union (index + storage)
Program:
// variant_demo.cpp
#include <iostream>
#include <variant>
#include <string>
using namespace std;
int main() {
    variant<int, double, string> v;

    cout << "Assign int\n";
    v = 10;
    cout << "index: " << v.index() << endl;
    cout << "int value: " << get<int>(v) << endl;

    cout << "\nAssign double\n";
    v = 3.14;
    cout << "index: " << v.index() << endl;
    cout << "double value: " << get<double>(v) << endl;

    cout << "\nAssign string\n";
    v = string("hello");
    cout << "index: " << v.index() << endl;
    cout << "string value: " << get<string>(v) << endl;

   return 0;
}
/* 
Output
Assign int
index: 0
int value: 10

Assign double
index: 1
double value: 3.14

Assign string
index: 2
string value: hello
*/


🧠 Memory model (exactly as you drew)
Stack:
┌────────────────────────┐
│ variant<int,double,str>│
│ ├─ active index        │
│ └─ union storage       │  ← max(sizeof(int),
│                         │     sizeof(double),
│                         │     sizeof(string))
└────────────────────────┘

Only one alternative is alive
Previous one is destroyed automatically
Storage is inline

✔ Type safety guarantee
get<double>(v);  // ❌ throws std::bad_variant_access if wrong type

Use safe access:
if (holds_alternative<double>(v)) {
    cout << get<double>(v);
}
✔ Visiting (recommended idiom)
visit([](auto&& x) {
    cout << x << endl;
}, v);



/* ====================================================================================== */

## std::forward (perfect forwarding)

```
Caller      Template param     forward<T>
------------------------------------------
int a;      T = int&           lvalue
f(a)

f(10)       T = int            rvalue
```

---
/* -------------------------------- */

std::forward — preserve value category (perfect forwarding)
Program
// forward_demo.cpp
#include <iostream>
#include <utility>
using namespace std;

// Overloads to detect value category
void sink(int& x) {
    cout << "sink(int&)  → lvalue\n";
}

void sink(int&& x) {
    cout << "sink(int&&) → rvalue\n";
}

// Forwarding reference
template <typename T>
void f(T&& x) {
    cout << "Inside f: forwarding\n";
    sink(forward<T>(x));   // PERFECT forwarding
}

int main() {
    int a = 10;

    cout << "Calling f(a)\n";
    f(a);      // lvalue

    cout << "\nCalling f(10)\n";
    f(10);     // rvalue

    return 0;
}
/* 
Output
Calling f(a)
Inside f: forwarding
sink(int&)  → lvalue

Calling f(10)
Inside f: forwarding
sink(int&&) → rvalue
*/


🧠 Memory / Type deduction model (matches your table)
Caller        T deduced       Parameter type     forward<T>(x)
----------------------------------------------------------------
int a;        T = int&        T&& → int&         lvalue
f(a)

f(10)         T = int         T&& → int&&        rvalue

❌ What happens WITHOUT std::forward
sink(x);   // ❌ ALWAYS lvalue inside f

Because:
Named variables are always lvalues
Even if their type is T&&


/* ====================================================================================== */


# 3️⃣ INTERVIEW QUESTIONS (WITH ANSWERS)

## std::move vs std::forward

Q: Why not always use std::move?
A: move destroys value category. forward preserves caller intent.

---
/* -------------------------------- */

1️⃣ std::move — unconditionally cast to rvalue
Destroys value category

Program:
// move_demo.cpp
#include <iostream>
#include <utility>
using namespace std;
void sink(int& x) {
    cout << "sink(int&)  → lvalue\n";
}
void sink(int&& x) {
    cout << "sink(int&&) → rvalue\n";
}
template <typename T>
void f(T&& x) {
    cout << "Inside f: using std::move\n";
    sink(move(x));   // ALWAYS rvalue
}
int main() {
    int a = 10;

    cout << "Calling f(a)\n";
    f(a);      // ❌ lvalue becomes rvalue

    cout << "\nCalling f(10)\n";
    f(10);     // rvalue stays rvalue

   return 0;
}
/* 
Output
Calling f(a)
Inside f: using std::move
sink(int&&) → rvalue

Calling f(10)
Inside f: using std::move
sink(int&&) → rvalue

Key observation:
a was an lvalue
std::move(a) forces rvalue
Caller intent is destroyed
*/





2️⃣ std::forward — conditional cast
Preserves caller intent

Program:
// forward_vs_move_demo.cpp
#include <iostream>
#include <utility>
using namespace std;

void sink(int& x) {
    cout << "sink(int&)  → lvalue\n";
}

void sink(int&& x) {
    cout << "sink(int&&) → rvalue\n";
}

template <typename T>
void f(T&& x) {
    cout << "Inside f: using std::forward\n";
    sink(forward<T>(x));   // PERFECT forwarding
}
int main() {
    int a = 10;

    cout << "Calling f(a)\n";
    f(a);      // lvalue preserved

    cout << "\nCalling f(10)\n";
    f(10);     // rvalue preserved

   return 0;
}
/* 
Output
Calling f(a)
Inside f: using std::forward
sink(int&)  → lvalue

Calling f(10)
Inside f: using std::forward
sink(int&&) → rvalue
*/




/* ====================================================================================== */
## std::span vs pointer + size

Q: Why introduce span?
A: Pointer loses size → buffer overflow bugs.

---
/* ------------------------------------- */

1️⃣ Raw pointer + size — size can be lost (bug-prone)
Program
// pointer_size_bug.cpp
#include <iostream>
using namespace std;

void print(int* p) {
    // ❌ Size information LOST
    cout << "Printing 5 elements (assumed): ";
    for (int i = 0; i < 5; ++i) {   // BUG if array smaller
        cout << p[i] << " ";
    }
    cout << endl;
}
int main() {
    int arr[3] = {1, 2, 3};

    print(arr);   // No way to know size here
   return 0;
}
/* 
Output (undefined behavior — sample)
Printing 5 elements (assumed): 1 2 3 32767 0

⚠️ Bug source: pointer has no size info

Memory model (raw pointer)
Stack
┌────────┐
│ int* p │ ─────────▶ data[]
└────────┘
(no size info)
*/




2️⃣ std::span — pointer + size bundled (safe view)
Program:
// span_safe.cpp
#include <iostream>
#include <span>
using namespace std;
void print(span<const int> s) {
    cout << "Printing " << s.size() << " elements: ";
    for (int x : s)
        cout << x << " ";
    cout << endl;
}
int main() {
    int arr[3] = {1, 2, 3};

    print(arr);   // size known automatically
  return 0;
}
/* 
Output
Printing 3 elements: 1 2 3

Memory model (std::span)
Stack
┌────────────────┐
│ span<int>      │
│ ├─ ptr ───────▶│ data[]
│ └─ size = 3    │
└────────────────┘
*/

/* ====================================================================================== */
## std::variant vs union

Q: Why variant?
A: union is unsafe, no active member tracking.

---
/* ----------------------------------------- */

1️⃣ union — unsafe, no active member tracking
Program
// union_bug.cpp
#include <iostream>
using namespace std;

union U {
    int i;
    double d;
};

int main() {
    U u;
    u.i = 10;

    cout << "Assigned int\n";
    cout << "Reading int: " << u.i << endl;

    cout << "Reading double (WRONG): " << u.d << endl;  // ❌ UB
    return 0;
}

Output (undefined behavior — sample)
Assigned int
Reading int: 10
Reading double (WRONG): 4.94066e-324


⚠️ Bug source: no record of active member

Memory model (union)
Stack
┌──────────────┐
│ union U      │
│ raw storage  │  ← reused blindly
└──────────────┘
(no active tag)

2️⃣ std::variant — safe tagged union
Program:
// variant_safe.cpp
#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<int, double> v;

    v = 10;
    cout << "Assigned int\n";
    cout << "index: " << v.index() << endl;
    cout << "int: " << get<int>(v) << endl;

    // Safe check
    if (holds_alternative<double>(v))
        cout << get<double>(v) << endl;
    else
        cout << "double not active\n";

  return 0;
}
/* 
Output
Assigned int
index: 0
int: 10
double not active

Memory model (std::variant)
Stack
┌────────────────────┐
│ variant<int,double>│
│ ├─ active index    │
│ └─ union storage   │
└────────────────────┘
*/

/* ====================================================================================== */
## std::optional vs pointer

Q: Why optional instead of nullptr?
A: No heap, explicit state, value semantics.

---
/* ------------------------------------- */

1️⃣ Nullable pointer — implicit state, heap/lifetime issues
Program:
// pointer_nullable.cpp
#include <iostream>
using namespace std;
int* makeValue(bool create) {
    if (create)
        return new int(42);   // heap allocation
    return nullptr;          // implicit absence
}
int main() {
    int* p = makeValue(true);

    if (p) {
        cout << "Value: " << *p << endl;
        delete p;   // manual lifetime
    }

    int* q = makeValue(false);
    if (q == nullptr)
        cout << "q is null\n";

  return 0;
}
/* 
Output
Value: 42
q is null

Memory model (pointer)
Stack              Heap
┌────────┐         ┌──────┐
│ int* p │ ─────▶  │ int  │
└────────┘         └──────┘
(null = no object)
*/



2️⃣ std::optional — explicit absence, no heap
Program:
// optional_value.cpp
#include <iostream>
#include <optional>
using namespace std;
optional<int> makeValue(bool create) {
    if (create)
        return 42;        // inline value
    return nullopt;      // explicit absence
}
int main() {
    auto a = makeValue(true);
    if (a)
        cout << "Value: " << *a << endl;

    auto b = makeValue(false);
    cout << "b engaged: " << b.has_value() << endl;

   return 0;
}
/* 
Output
Value: 42
b engaged: 0

Memory model (std::optional)
Stack
┌────────────────┐
│ optional<int>  │
│ ├─ engaged flag│
│ └─ int value   │
└────────────────┘
*/

/* ====================================================================================== */
## std::shared_ptr pitfalls

Q: Why discouraged in embedded?
A: Atomic refcount, heap control block, nondeterministic lifetime.

---
/* --------------------------------- */

1️⃣ Atomic reference counting (hidden cost)
Program:
// shared_ptr_atomic.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Data {
    ~Data() { cout << "Data destroyed\n"; }
};
void pass(shared_ptr<Data> p) {
    cout << "Inside function, use_count = " << p.use_count() << endl;
}
int main() {
    shared_ptr<Data> sp = make_shared<Data>();

    cout << "Initial use_count = " << sp.use_count() << endl;

    pass(sp);   // ❗ atomic increment/decrement

    cout << "After call, use_count = " << sp.use_count() << endl;
  return 0;
}
/* 
Output
Initial use_count = 1
Inside function, use_count = 2
After call, use_count = 1
Data destroyed

⚠️ Embedded issue
Every copy → atomic inc/dec
Expensive on MCUs
Hidden cost in APIs
*/




2️⃣ Heap control block (extra allocation)
Program:
// shared_ptr_heap.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Obj {
    Obj()  { cout << "Obj constructed\n"; }
    ~Obj() { cout << "Obj destroyed\n"; }
};
int main() {
    cout << "Using new + shared_ptr\n";
    shared_ptr<Obj> p1(new Obj);

    cout << "Using make_shared\n";
    shared_ptr<Obj> p2 = make_shared<Obj>();

  return 0;
}
/* 
Output
Using new + shared_ptr
Obj constructed
Using make_shared
Obj constructed
Obj destroyed
Obj destroyed

⚠️ Embedded issue
new Obj + shared_ptr → 2 heap allocations
make_shared → 1 combined heap allocation
Still heap → fragmentation risk
*/



3️⃣ Non-deterministic destruction timing
Program:
// shared_ptr_lifetime.cpp
#include <iostream>
#include <memory>
using namespace std;
struct Sensor {
    ~Sensor() { cout << "Sensor destroyed\n"; }
};
int main() {
    shared_ptr<Sensor> s1 = make_shared<Sensor>();

    {
        shared_ptr<Sensor> s2 = s1;
        cout << "Inside scope\n";
    } // s2 destroyed, object still alive

    cout << "Leaving main\n";
  return 0;
}
/* 
Output
Inside scope
Leaving main
Sensor destroyed

⚠️ Embedded issue
Destruction depends on last owner
Hard to predict timing
Breaks real-time guarantees

🧠 Memory model (shared_ptr)
Stack             Heap (control block)        Heap (object)
┌──────┐          ┌──────────────────┐       ┌──────────┐
│ sp   │ ──────▶  │ atomic refcount  │ ───▶  │ object   │
└──────┘          │ weak count       │       └──────────┘
                  └──────────────────┘
*/




/* ====================================================================================== */
# 4️⃣ MISRA-SAFE VS NON-SAFE UTILITIES

## ✅ Generally MISRA-Friendly

* std::array
* std::span (C++20)
* std::optional
* std::variant
* std::unique_ptr
* std::lock_guard
* std::bit_cast

/* ------------------------------------ */

✅ std::array — fixed-size, stack, deterministic
Code:
#include <iostream>
#include <array>
using namespace std;
int main() {
    array<int, 3> a = {1, 2, 3};

    for (int x : a)
        cout << x << " ";
    cout << endl;
}
/* 
Output
1 2 3

✔ No heap
✔ Compile-time size
✔ MISRA-friendly
*/




✅ std::span (C++20) — non-owning view
Code:
#include <iostream>
#include <span>
using namespace std;
void print(span<const int> s) {
    for (int x : s)
        cout << x << " ";
    cout << endl;
}
int main() {
    int data[] = {4, 5, 6};
    print(data);
}
/* 
Output
4 5 6

✔ No allocation
✔ Explicit size
⚠ Lifetime responsibility on caller
*/




✅ std::optional — explicit absence, stack-only
Code:
#include <iostream>
#include <optional>
using namespace std;
optional<int> read(bool ok) {
    if (ok) return 10;
    return nullopt;
}
int main() {
    auto v = read(true);
    if (v)
        cout << *v << endl;
}
/* 
Output
10

✔ No heap
✔ Deterministic
✔ Better than nullable pointers
*/





✅ std::variant — type-safe union
Code
#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<int, float> v = 3;

    if (holds_alternative<int>(v))
        cout << get<int>(v) << endl;
}
/* 
Output
3

✔ Stack storage
✔ Active alternative tracked
✔ Safer than union
*/




✅ std::unique_ptr — single ownership
Code
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> p(new int(7));
    cout << *p << endl;
}
/* 
Output
7

✔ Deterministic destruction
✔ No refcount
⚠ Heap allowed but controlled
*/




✅ std::lock_guard — RAII mutex lock
Code
#include <iostream>
#include <mutex>
using namespace std;
mutex m;
int counter = 0;
int main() {
    {
        lock_guard<mutex> lock(m);
        counter++;
    } // unlocked deterministically

    cout << counter << endl;
}
/* 
Output
1

✔ No heap
✔ No deadlock risk
✔ Preferred over manual lock/unlock
*/




✅ std::bit_cast (C++20) — safe bit reinterpretation
Code
#include <iostream>
#include <bit>
#include <cstdint>
using namespace std;
int main() {
    uint32_t u = 0x3F800000; // IEEE float 1.0
    float f = bit_cast<float>(u);

    cout << f << endl;
}
/* 
Output
1
✔ No UB
✔ No aliasing violation
✔ MISRA-approved replacement for reinterpret_cast
*/





/* ====================================================================================== */
## ⚠️ Restricted / Discouraged

* std::shared_ptr (refcount, heap)
* std::function (type erasure, heap)
* std::bind (hard to analyze)
* std::any (runtime type errors)
* std::thread (use RTOS primitives)
* std::async (unspecified scheduling)

## ❌ Usually Forbidden

* new / delete
* malloc / free
* unbounded recursion
* RTTI / exceptions (project-dependent)

---
/* ------------------------------------ */

🔶 RESTRICTED / DISCOURAGED UTILITIES
⚠️ std::shared_ptr — atomic refcount + heap
Code
#include <iostream>
#include <memory>
using namespace std;

struct Obj {
    ~Obj() { cout << "Obj destroyed\n"; }
};
void f(shared_ptr<Obj> p) {
    cout << "use_count inside f: " << p.use_count() << endl;
}
int main() {
    shared_ptr<Obj> sp = make_shared<Obj>();
    cout << "use_count before: " << sp.use_count() << endl;

    f(sp);   // atomic refcount inc/dec

    cout << "use_count after: " << sp.use_count() << endl;
}
/* 
Output
use_count before: 1
use_count inside f: 2
use_count after: 1
Obj destroyed

❌ Atomic operations
❌ Heap control block
❌ Non-deterministic destruction
*/




⚠️ std::function — type erasure, possible heap
Code
#include <iostream>
#include <functional>
using namespace std;
void foo(int x) {
    cout << "foo: " << x << endl;
}
int main() {
    function<void(int)> f = foo;  // type erased
    f(10);
}
/* 
Output
foo: 10

❌ Hidden virtual dispatch
❌ Often heap allocates
❌ Hard to analyze statically
*/





⚠️ std::bind — unreadable, analyzer-hostile
Code
#include <iostream>
#include <functional>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int main() {
    auto f = bind(add, _2, _1);   // confusing
    cout << f(2, 1) << endl;
}
/* 
Output
3

❌ Argument order hidden
❌ Hard to review
❌ Prefer lambdas
*/





⚠️ std::any — runtime type errors
Code
#include <iostream>
#include <any>
using namespace std;
int main() {
    any a = 10;

    try {
        cout << any_cast<double>(a) << endl;  // runtime error
    } catch (...) {
        cout << "Bad any_cast\n";
    }
}
/* 
Output
Bad any_cast

❌ No compile-time safety
❌ Exceptions required
❌ Runtime failure
*/




⚠️ std::thread — OS threads, non-RT
Code
#include <iostream>
#include <thread>
using namespace std;
void task() {
    cout << "Thread running\n";
}
int main() {
    thread t(task);
    t.join();
}
/* 
Output
Thread running

❌ Uses OS scheduler
❌ No priority control
❌ RTOS primitives preferred
*/





⚠️ std::async — unspecified scheduling
Code
#include <iostream>
#include <future>
using namespace std;
int work() {
    cout << "Working\n";
    return 42;
}
int main() {
    auto f = async(work);   // thread? deferred? unknown
    cout << f.get() << endl;
}
/* 
Output
Working
42
*/

❌ Execution policy unclear
❌ Hidden thread creation
❌ Non-deterministic

🔴 USUALLY FORBIDDEN (MISRA)
❌ new / delete — manual heap
Code
#include <iostream>
using namespace std;
int main() {
    int* p = new int(5);
    cout << *p << endl;
    delete p;
}
/* 
Output
5

❌ Heap fragmentation
❌ Lifetime errors
❌ Use stack / static / RAII
*/





❌ malloc / free — no constructors
Code
#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    int* p = (int*)malloc(sizeof(int));
    *p = 7;
    cout << *p << endl;
    free(p);
}
/* 
Output
7

❌ No constructors/destructors
❌ Type unsafe
❌ Forbidden in C++
*/






❌ Unbounded recursion — stack overflow
Code
#include <iostream>
using namespace std;
void recurse() {
    recurse();   // no bound
}
int main() {
    recurse();
}
/* 
Output
(stack overflow / crash)

❌ No termination guarantee
❌ Stack exhaustion
*/






❌ RTTI / Exceptions (project-dependent)
RTTI Example
#include <iostream>
#include <typeinfo>
using namespace std;
struct Base { virtual ~Base(){} };
struct Derived : Base {};
int main() {
    Base* b = new Derived;
    cout << typeid(*b).name() << endl;
    delete b;
}
/* 
❌ RTTI overhead
❌ Breaks predictability
*/





//Exception Example
#include <iostream>
using namespace std;
int main() {
    try {
        throw 1;
    } catch (...) {
        cout << "Exception caught\n";
    }
}
/* 
Output
Exception caught

❌ Stack unwinding
❌ Hidden control flow
❌ Often disabled in embedded
*/


/* ====================================================================================== */


