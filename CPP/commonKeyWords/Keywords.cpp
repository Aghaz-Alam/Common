✅ C++11 – New / Advanced Keywords
1. auto (reworked) — type inference
2. nullptr — null pointer literal
3. constexpr — compile-time evaluation
4. decltype — deduce expression type
5. thread_local — thread-local storage duration
6. static_assert — compile-time assertion
7. override — checks virtual override
8. final — prevents overriding / inheritance
9. noexcept — function that cannot throw
10. alignas — specify memory alignment
11. alignof — get type alignment
12. char16_t / char32_t — UTF-16, UTF-32 chars
13. enum class (new scoped enums)
14. using (enhanced, alias declarations)
15. decltype(auto) (C++14 refinement began in C++11 grammar)



/* ---------------------------------------------------------- */
1. auto — Type Inference (reworked in C++11)
Automatically deduces type from initializer.

//Program
#include <iostream>
int main() {
    auto x = 10;           // int
    auto y = 3.14;         // double
    auto s = "Hello";      // const char*

    std::cout << x << "\n" << y << "\n" << s << "\n";
}
/* 
Output
10
3.14
Hello
*/



2. nullptr — null pointer literal
Replaces NULL (which was an integer).

//Program
#include <iostream>
void func(int*) { std::cout << "int* called\n"; }
void func(double*) { std::cout << "double* called\n"; }
int main() {
    func(nullptr);   // resolves to int* or double*? → null pointer type → matches both? No → ambiguous resolved properly
}
/* 
Output
int* called

(Exact overload resolution depends; this one prefers the first overload.)
*/



3. constexpr — Compile-time evaluation
Functions/variables that can be evaluated at compile-time.

//Program
#include <iostream>
constexpr int square(int x) { 
    return x * x; 
}
int main() {
    constexpr int v = square(5);  // compile-time
    std::cout << v << "\n";
}
/* 
Output
25
*/


4. decltype — Get type from expression
Extracts type of an expression without evaluating it.

//Program
#include <iostream>
int main() {
    int x = 10;
    decltype(x) y = 20;   // y is int

    std::cout << x + y << "\n";
}
/* 
Output
30
*/


5. thread_local — Thread-local variable
Each thread gets its own copy.

//Program
#include <iostream>
#include <thread>
thread_local int counter = 0;
void work() {
    counter++;
    std::cout << "Counter in thread: " << counter << "\n";
}
int main() {
    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();
}
/* 
Output (order may vary)
Counter in thread: 1
Counter in thread: 1

Each thread has its own counter.
*/


6. static_assert — Compile-time checks
Compiler error if condition is false.

//Program
#include <iostream>
static_assert(sizeof(int) == 4, "int must be 4 bytes");
int main() {
    std::cout << "Program ran\n";
}
/* 
Output
Program ran

(If condition failed → compile-time error)
*/



7. override — Ensures method overrides base class virtual
Prevents mistakes by checking override correctness.

//Program
#include <iostream>
struct Base {
    virtual void show() { std::cout << "Base\n"; }
};
struct Derived : Base {
    void show() override { std::cout << "Derived\n"; }
};
int main() {
    Derived d;
    d.show();
}
/* 
Output
Derived
*/


8. final — Prevents overriding / inheritance
//Program
#include <iostream>
struct Base {
    virtual void fun() final { std::cout << "Base final\n"; }
};
struct Derived : Base {
    // void fun() override {}   // ERROR: cannot override final function
};
int main() {
    Base b;
    b.fun();
}
/* 
Output
Base final
*/



9. noexcept — Function guaranteed not to throw
Better performance and exception safety.

//Program
#include <iostream>
void safe() noexcept {
    std::cout << "Noexcept function\n";
}
int main() {
    std::cout << std::boolalpha << noexcept(safe()) << "\n";
    safe();
}
/* 
Output
true
Noexcept function
*/



10. alignas — Force alignment
//Program
#include <iostream>
struct alignas(32) Data {
    int x;
};
int main() {
    std::cout << alignof(Data) << "\n";
}
/* 
Output
32
*/



11. alignof — Query alignment requirement
//Program
#include <iostream>
struct Test { 
    double d; 
    int x; 
};
int main() {
    std::cout << alignof(Test) << "\n";
}
/* 
Output
(On typical platforms)
8
*/



12. char16_t / char32_t — UTF-16 & UTF-32 characters
//Program
#include <iostream>
int main() {
    char16_t u16 = u'A';
    char32_t u32 = U'😊';

    std::cout << sizeof(u16) << "\n" << sizeof(u32) << "\n";
}
/* 
Output
2
4
*/



13. enum class — Strongly typed enums
//Program
#include <iostream>
enum class Color { Red, Green, Blue };
int main() {
    Color c = Color::Green;

    if (c == Color::Green)
        std::cout << "Green\n";
}
/* 
Output
Green
*/



14. using — Type alias (replacement of typedef)
//Program
#include <iostream>
using uint = unsigned int;
using Pair = std::pair<int,int>;
int main() {
    uint x = 20;
    Pair p = {1, 2};

    std::cout << x << " " << p.first << "," << p.second;
}
/* 
Output
20 1,2
*/



15. decltype(auto) (C++14 refinement)
Returns exact type (value, reference, const ref).

//Program
#include <iostream>
int x = 100;
decltype(auto) get() {
    return (x);     // returns int&
}
int main() {
    int& r = get();
    r = 200;

    std::cout << x << "\n";
}
/* 
Output
200
*/
/* ---------------------------------------------------------- */


/* ========================================================================================================================================= */
✅ C++14 – Important Additions
(C++14 added few keywords; mostly extensions.)

16. constexpr extended — more complete compile-time functions
(not a new keyword but heavily expanded)

17. decltype(auto) — return type deduction
(C++14 but considered part of advanced keyword system)

18. auto for function return type deduction
(not a keyword but a major semantic extension)
No new dedicated keywords were added in C++14.


/* ----------------------------------------------------------- */
✅ 16. Extended constexpr (C++14)
In C++11: constexpr functions had many restrictions — no loops, no conditionals, no mutable variables.

In C++14:
✔ Loops allowed
✔ Local non-const variables allowed
✔ Multiple statements allowed
✔ if, switch, etc. allowed

//Program: C++14 constexpr with loop
#include <iostream>
constexpr int sum_upto(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++) {
        s += i;                 // Allowed only from C++14
    }
    return s;
}
int main() {
    constexpr int x = sum_upto(5);  // compile-time
    std::cout << x << "\n";
}
/* 
Output
15
*/


✅ 17. decltype(auto) — exact return type deduction (C++14)
Deduce type including reference & const-ness.
If expression is an lvalue, return type = reference
If expression is an rvalue, return type = value

//Program: decltype(auto) preserving reference
#include <iostream>
int value = 10;
decltype(auto) get_ref() {
    return (value);   // parentheses → lvalue → returns int&
}
int main() {
    int& r = get_ref();  
    r = 20;

    std::cout << value << "\n";
}
/* 
Output
20

Meaning:
decltype(auto) preserved return type as reference, so modifying r modified value.
*/




✅ 18. auto return type deduction for functions (C++14)
C++14 allows:
auto func() {
    return expression;  // compiler deduces return type
}


C++11 required trailing return type (auto func() -> int).
//Program: auto return type
#include <iostream>
auto add(int a, int b) {
    return a + b;    // deduced as int
}
auto pi() {
    return 3.1415;   // deduced as double
}
int main() {
    std::cout << add(2, 3) << "\n";
    std::cout << pi() << "\n";
}
/* 
Output
5
3.1415
*/
/* ----------------------------------------------------------- */


/* ========================================================================================================================================= */
✅ C++17 – New / Advanced Keywords / Contextual Keywords
19. if constexpr — compile-time conditional
(not new keyword, but constexpr used as a special conditional keyword)

20. inline variables
(existing keyword but new meaning)

21. noexcept became part of function type
(keyword redefined)

22. typename allowed in more contexts
23. namespace inline
(keyword used in a new semantic way)
No new core keywords were added in C++17.


/* ---------------------------------------------------------- */
✅ 19. if constexpr — Compile-time Conditional
C++11/14: You had constexpr, but you could not remove invalid branches.
C++17: if constexpr removes unused branch at compile time.

//Program: Compile-time branching
#include <iostream>
#include <type_traits>
template <typename T>
void printType(const T& value) {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Integral: " << value << "\n";
    } else {
        std::cout << "Non-integral: " << value << "\n";
    }
}
int main() {
    printType(10);      // integral
    printType(3.14);    // non-integral
}
/* 
Output
Integral: 10
Non-integral: 3.14
*/


✅ 20. Inline Variables (C++17)
Before C++17:
Global variables in headers caused multiple-definition linker errors.

C++17:
inline variables allow single definition shared across translation units.

//Program: inline variable
#include <iostream>
struct Config {
    inline static int version = 17;   // New in C++17
};
int main() {
    std::cout << Config::version << "\n";
}
/* 
Output
17
*/



✅ 21. noexcept as part of function type (C++17)
In C++17, this is valid:

void(*fp)() noexcept;
Meaning: function pointer type includes noexcept.

//Program: noexcept function type
#include <iostream>
void safe() noexcept { std::cout << "safe\n"; }
void unsafe()        { std::cout << "unsafe\n"; }
int main() {
    void(*fp)() noexcept = safe;  // OK
    fp();                         // calls safe

    // void(*fp2)() noexcept = unsafe; // ERROR: type mismatch

    std::cout << std::boolalpha << noexcept(safe()) << "\n";
}
/* 
Output
safe
true
*/


✅ 22. typename allowed in more contexts (C++17)
C++17 permits typename in templates inside non-dependent contexts.

//Program: typename allowed in template template-argument
#include <iostream>
#include <vector>
template <typename T>
void show() {
    typename std::vector<T>::value_type x = T();  // allowed in C++17
    std::cout << x << "\n";
}
int main() {
    show<int>();     // prints default int → 0
}
/* 
Output
0
*/



✅ 23. Inline Namespaces — expanded semantics in C++17
What is it?
Mark a namespace as "inline"
Its members behave as if they are in the parent namespace
Useful for versioning

//Program: inline namespace versioning
#include <iostream>
namespace Lib {
    inline namespace v2 {     // preferred version
        void hello() { std::cout << "Hello from v2\n"; }
    }
    namespace v1 {
        void hello() { std::cout << "Hello from v1\n"; }
    }
}
int main() {
    Lib::hello();      // calls v2::hello due to inline namespace
    Lib::v1::hello();  // old version
}
/* 
Output
Hello from v2
Hello from v1
*/
/* ---------------------------------------------------------- */


/* ========================================================================================================================================= */
✅ C++20 – New / Advanced Keywords
24. consteval — Immediate functions
25. constinit — Must initialize at compile-time
26. co_await — Coroutine await expression
27. co_yield — Coroutine generator yield
28. co_return — Coroutine return value
29. requires — Concepts
30. concept — Define constraints
31. typename (expanded use in constraints)
32. import — Modules
33. export — Module interface (revived from C++)
34. module — Module declaration


/* -------------------------------------------------------- */
✅ 24. consteval — Immediate Functions
A consteval function must be evaluated at compile time, not runtime.

//Program
#include <iostream>
consteval int square(int x) {
    return x * x;
}
int main() {
    constexpr int a = square(5);   // OK
    std::cout << a << "\n";
}
/* 
Output
25
*/


✅ 25. constinit — Must initialize at compile-time
Guarantees static storage variables are initialized at compile time,
BUT unlike constexpr, the value does not need to be constant after initialization.
//Program
#include <iostream>
constinit int value = 100;   // must be initialized with constant expression
int main() {
    std::cout << value << "\n";
}
/* 
Output
100
 */

🌀 C++20 COROUTINE KEYWORDS (co_await, co_yield, co_return)
To demonstrate them simply, we use a minimal coroutine generator.

✅ 26. co_await — Await an Awaitable
//Program: simple future
#include <iostream>
#include <coroutine>
struct Awaiter {
    bool await_ready() const noexcept { return true; }
    void await_suspend(std::coroutine_handle<>) const noexcept {}
    int await_resume() const noexcept { return 42; }
};
struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() noexcept {}
        void unhandled_exception() {}
    };
};
Task foo() {
    int val = co_await Awaiter(); 
    std::cout << val << "\n";
}
int main() {
    foo();
}
/* 
Output
42
*/



✅ 27. co_yield — Produces a value (generator)
//Program: generator
#include <iostream>
#include <coroutine>
template<typename T>
struct Generator {
    struct promise_type {
        T current;
        Generator get_return_object() {
            return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always yield_value(T v) { current = v; return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
    };

    std::coroutine_handle<promise_type> h;

    ~Generator() { if (h) h.destroy(); }

    bool next() {
        if (!h.done()) { h.resume(); }
        return !h.done();
    }
    T value() const { return h.promise().current; }
};
Generator<int> numbers() {
    co_yield 1;
    co_yield 2;
    co_yield 3;
}
int main() {
    auto g = numbers();
    while (g.next()) {
        std::cout << g.value() << "\n";
    }
}
/* 
Output
1
2
3
*/


✅ 28. co_return — Return value from coroutine
//Program
#include <iostream>
#include <coroutine>
struct Task {
    struct promise_type {
        int value;
        Task get_return_object() { return Task{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_value(int v) noexcept { value = v; }
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> h;
};
Task compute() {
    co_return 99;
}
int main() {
    Task t = compute();
    std::cout << t.h.promise().value << "\n";
    t.h.destroy();
}
/* 
Output
99
*/


✅ 29. requires — Constraint expression for templates
//Program
#include <iostream>
#include <type_traits
template<typename T>
requires std::is_integral_v<T>
T add(T a, T b) {
    return a + b;
}
int main() {
    std::cout << add(5, 6) << "\n";

    // add(1.2, 2.3);  // ERROR: double does not satisfy requires
}
/* 
Output
11
*/



✅ 30. concept — Define constraints
//Program
#include <iostream>
#include <concepts>
template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;
Number auto square(Number auto x) {
    return x * x;
}
int main() {
    std::cout << square(5) << "\n";
    std::cout << square(2.5) << "\n";
}
/* 
Output
25
6.25
*/



✅ 31. typename in constraints
C++20 allows typename inside constrained template parameters.

//Program
#include <iostream>
#include <vector>
#include <concepts>
template<typename T>
requires requires { typename T::value_type; } 
void show(T container) {
    std::cout << "Has value_type\n";
}
int main() {
    std::vector<int> v;
    show(v);
}
/* 
Output
Has value_type
*/


📦 MODULE KEYWORDS (export, import, module)
These require two files.

✅ 32–34. module, export, import — C++20 Modules
File 1: math.mpp
export module math;
export int add(int a, int b) {
    return a + b;
}

File 2: main.cpp
import math;
#include <iostream>
int main() {
    std::cout << add(3, 4) << "\n";
}
/* 
Output
7
*/

Explanation:
module math; → declares a module
export → exposes functions to other files
import math; → uses module instead of #include
/* ------------------------------------------------------- */
/* ========================================================================================================================================== */