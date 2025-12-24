✅ Advanced Exception Handling in Modern C++ (C++11 → C++20)
Includes:
✔ noexcept (specifier & operator)
✔ noexcept(true/false)
✔ conditional noexcept
✔ rethrowing exceptions
✔ nested exceptions (C++11)
✔ std::exception_ptr, std::current_exception, std::rethrow_exception
✔ std::make_exception_ptr
✔ custom exception classes
✔ deriving from std::exception
✔ override what()
✔ throwing in constructors
✔ exception safety guarantees
✔ RAII + exceptions
✔ noexcept in move constructor
✔ std::bad_alloc, std::bad_cast, std::bad_exception
✔ catching multiple exception types
✔ noexcept on lambdas (C++14)
✔ noexcept function types (C++17)
✔ std::uncaught_exceptions (C++17)
✔ exception handling in coroutines (C++20)
✔ exception propagation in threads using exception_ptr



⭐ 1. noexcept Specifier (C++11)
#include <iostream>
void f() noexcept {
    std::cout << "Function declared noexcept\n";
}
int main() {
    f();
}








⭐ 2. noexcept Operator (C++11)
#include <iostream>
int g() { return 10; }
int h() noexcept { return 20; }
int main() {
    std::cout << std::boolalpha;
    std::cout << "Is g() noexcept? " << noexcept(g()) << "\n";
    std::cout << "Is h() noexcept? " << noexcept(h()) << "\n";
}






⭐ 3. Conditional noexcept (C++11)
#include <iostream>
#include <type_traits>
template<typename T>
void func(T) noexcept(std::is_integral<T>::value) {
    std::cout << "Called func\n";
}
int main() {
    std::cout << std::boolalpha;
    std::cout << noexcept(func(10)) << "\n";     // true
    std::cout << noexcept(func(1.5)) << "\n";    // false
}






⭐ 4. Custom Exception Class (C++11)
#include <iostream>
#include <exception>
class MyError : public std::exception {
  public:
    const char* what() const noexcept override {
        return "MyError occurred!";
    }
};
int main() {
    try {
        throw MyError();
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}






⭐ 5. Throwing in Constructor (C++11)
#include <iostream>
#include <stdexcept>
class Demo {
  public:
    Demo() {
        throw std::runtime_error("Constructor failed!");
    }
};
int main() {
    try {
        Demo d;
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}





⭐ 6. Rethrowing Exceptions (C++11)
#include <iostream>
#include <stdexcept>
void f() {
    try {
        throw std::runtime_error("Error inside f");
    } catch (...) {
        std::cout << "Caught in f, rethrowing...\n";
        throw;  // rethrow
    }
}
int main() {
    try {
        f();
    } catch (const std::exception& e) {
        std::cout << "Caught in main: " << e.what() << "\n";
    }
}





⭐ 7. Nested Exceptions (C++11)
#include <iostream>
#include <exception>
void inner() {
    throw std::runtime_error("Inner failure");
}
void outer() {
    try {
        inner();
    } catch (...) {
        std::throw_with_nested(std::runtime_error("Outer failure"));
    }
}
void printNested(const std::exception& e) {
    std::cout << "Exception: " << e.what() << "\n";
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& nested) {
        printNested(nested);
    } catch (...) {}
}
int main() {
    try {
        outer();
    } catch (const std::exception& e) {
        printNested(e);
    }
}





⭐ 8. Using std::exception_ptr (C++11)
#include <iostream>
#include <exception>
std::exception_ptr eptr;
void thrower() {
    try {
        throw std::runtime_error("Captured exception");
    } catch (...) {
        eptr = std::current_exception();
    }
}
int main() {
    thrower();
    try {
        std::rethrow_exception(eptr);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}






⭐ 9. std::make_exception_ptr (C++11)
#include <iostream>
#include <exception>
int main() {
    std::exception_ptr ep = std::make_exception_ptr(std::runtime_error("made error"));

    try {
        std::rethrow_exception(ep);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}







⭐ 10. Exception Safety + RAII (C++11)
#include <iostream>
class File {
  public:
    File()  { std::cout << "Open file\n"; }
    ~File() { std::cout << "Close file\n"; }
};
int main() {
    try {
        File f;
        throw std::runtime_error("Something failed");
    } catch (...) {
        std::cout << "Exception caught\n";
    }
}






⭐ 11. noexcept Move Constructor (C++11)
#include <iostream>
#include <vector>
class A {
  public:
    A() {}
    A(A&&) noexcept { std::cout << "noexcept move\n"; }
};
int main() {
    std::vector<A> v;
    v.emplace_back();
    v.emplace_back(); // optimized because move is noexcept
}






⭐ 12. std::bad_alloc, std::bad_cast, std::bad_exception
#include <iostream>
#include <vector>
#include <typeinfo>
int main() {
    try {
        std::vector<int> big(1000000000000ULL); // may throw bad_alloc
    } catch (const std::bad_alloc& e) {
        std::cout << "bad_alloc\n";
    }

    try {
        throw std::bad_cast();
    } catch (const std::bad_cast&) {
        std::cout << "bad_cast\n";
    }
}







⭐ 13. noexcept Lambdas (C++14)
#include <iostream>
int main() {
    auto fn = []() noexcept { return 10; };
    std::cout << noexcept(fn()) << "\n";
}







⭐ 14. noexcept Function Types (C++17)
#include <iostream>
#include <type_traits>
void f() noexcept {}
void g() {}
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_nothrow_invocable<decltype(f)>::value << "\n";
    std::cout << std::is_nothrow_invocable<decltype(g)>::value << "\n";
}







⭐ 15. std::uncaught_exceptions (C++17)
#include <iostream>
#include <exception>
class Tracker {
  public:
    ~Tracker() {
        std::cout << "Uncaught exceptions: "
                  << std::uncaught_exceptions() << "\n";
    }
};
int main() {
    try {
        Tracker t;
        throw 1;
    } catch (...) {}
}






⭐ 16. Exception Propagation in Threads (C++11)
#include <iostream>
#include <thread>
#include <exception>
std::exception_ptr eptr;
void worker() {
    try {
        throw std::runtime_error("Error in thread");
    } catch (...) {
        eptr = std::current_exception();
    }
}
int main() {
    std::thread t(worker);
    t.join();

    try {
        if (eptr) std::rethrow_exception(eptr);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}






⭐ 17. C++20 Coroutines & Exceptions
#include <iostream>
#include <coroutine>
#include <exception>
struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() { 
            std::cout << "Coroutine exception handled\n";
        }
        void return_void() {}
    };
};
Task f() {
    throw std::runtime_error("Coroutine failed");
    co_return;
}
int main() {
    f();
}




Advanced Topics (Part–2)

✔ exception rethrowing with custom context
✔ exception translation
✔ exception neutrality
✔ catching by value, reference, base, derived
✔ noexcept + templates advanced
✔ strong/weak/no-throw exception guarantees (detailed coded examples)
✔ stack unwinding demonstration
✔ destructor exceptions (why dangerous & solutions)
✔ std::unexpected / bad_exception (legacy but important)
✔ terminate handlers
✔ custom terminate()
✔ set_unexpected (C++17 removed but shown for history)
✔ noexcept(false) explicitly
✔ polymorphic vs non-polymorphic exceptions
✔ noexcept and templates SFINAE
✔ exception safe smart pointers
✔ exception-safe swap()
✔ exception in initializer list
✔ exceptions in overloaded operators
✔ exceptions in move operations
✔ exceptions in thread pools with packaged_task + future
✔ C++20: exceptions in modules
✔ C++20: exceptions with concepts

⭐ 18. Exception Translation (Wrap Low-Level Errors into High-Level Ones)
#include <iostream>
#include <stdexcept>

void lowLevel() {
    throw std::runtime_error("Disk read error");
}

void highLevel() {
    try {
        lowLevel();
    } catch (const std::exception& e) {
        throw std::logic_error(std::string("High-level error: ") + e.what());
    }
}

int main() {
    try {
        highLevel();
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 19. Exception Neutrality (Template Functions that Don’t Hide Exceptions)
#include <iostream>
#include <stdexcept>

template<typename F>
void wrapper(F f) {
    try {
        f();
    } catch (...) {
        std::cout << "Wrapper rethrows...\n";
        throw;     // neutral, doesn't swallow
    }
}

int main() {
    try {
        wrapper([] { throw std::runtime_error("Error"); });
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 20. Catching by Value / Reference / Base / Derived
#include <iostream>
#include <exception>

class Base : public std::exception {
public:
    const char* what() const noexcept override { return "Base"; }
};

class Derived : public Base {
public:
    const char* what() const noexcept override { return "Derived"; }
};

int main() {
    try {
        throw Derived();
    }
    catch (Derived& d) { std::cout << "Caught Derived: " << d.what() << "\n"; }
    catch (Base& b)    { std::cout << "Caught Base: " << b.what() << "\n"; }
    catch (...)        { std::cout << "Caught Something\n"; }
}

⭐ 21. noexcept(false) explicitly
#include <iostream>

void foo() noexcept(false) {
    throw std::runtime_error("Explicit noexcept(false)");
}

int main() {
    try {
        foo();
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 22. Stack Unwinding Demonstration
#include <iostream>

struct A {
    A() { std::cout << "A constructed\n"; }
    ~A() { std::cout << "A destroyed\n"; }
};

void f() {
    A a;
    throw std::runtime_error("Error!");
}

int main() {
    try {
        f();
    } catch (...) {
        std::cout << "Caught exception\n";
    }
}

⭐ 23. Exceptions in Destructors (Danger & Solution)

✔ Wrong (throws from destructor → terminate)
✔ Correct (log then swallow)

#include <iostream>
#include <exception>

class Bad {
public:
    ~Bad() {
        throw std::runtime_error("Error in destructor!");
    }
};

class Good {
public:
    ~Good() noexcept {
        try {
            throw std::runtime_error("Error in destructor!");
        } catch (...) {
            std::cout << "Safe: destructor absorbed exception\n";
        }
    }
};

int main() {
    try {
        Bad b; // destructor called during stack unwinding → terminate
        throw 1;
    } catch (...) {
        std::cout << "Exception caught but program will terminate due to Bad\n";
    }

    // Good destructor avoids terminate()
    Good g;
}


⚠ The Bad example will call terminate — this is intended educationally.

⭐ 24. Custom terminate() Handler
#include <iostream>
#include <exception>

void myTerminate() {
    std::cout << "Custom terminate called!\n";
    std::abort();
}

int main() {
    std::set_terminate(myTerminate);

    std::cout << "About to call terminate...\n";
    std::terminate();
}

⭐ 25. noexcept + Templates SFINAE (Advanced)
#include <iostream>
#include <type_traits>

template<typename T>
void process(T) noexcept(std::is_nothrow_copy_constructible<T>::value) {
    std::cout << "Processing...\n";
}

int main() {
    std::cout << noexcept(process(10)) << "\n";
    std::cout << noexcept(process(std::string("ABC"))) << "\n";
}

⭐ 26. Strong Exception Guarantee (Commit/Rollback Pattern)
#include <iostream>
#include <vector>

void pushStrong(std::vector<int>& v, int x) {
    std::vector<int> temp = v;  // strong guarantee via copy
    temp.push_back(x);          // may throw
    v = std::move(temp);        // commit only if no throw
}

int main() {
    std::vector<int> v = {1,2,3};
    pushStrong(v, 4);
    for (int n : v) std::cout << n << " ";
}

⭐ 27. Weak Exception Guarantee Example
#include <iostream>
#include <vector>

void weakAdd(std::vector<int>& v, int x) {
    v.push_back(x); // If reallocation throws, vector may be unchanged or partially modified
}

int main() {
    std::vector<int> v = {1,2,3};
    weakAdd(v, 4);
    for (int n : v) std::cout << n << " ";
}

⭐ 28. No-Throw Guarantee Example
#include <iostream>

void safe() noexcept {
    std::cout << "Guaranteed no throw\n";
}

int main() {
    safe();
}

⭐ 29. Exception-Safe swap (Commit/Rollback)
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
void safeSwap(T& a, T& b) {
    T temp = a;   // may throw
    a = b;        // may throw
    b = temp;     // may throw
}

int main() {
    int a=1, b=2;
    safeSwap(a,b);
    std::cout << a << " " << b;
}

⭐ 30. Exception During Operator Overload
#include <iostream>

class X {
public:
    int val;
    X(int v) : val(v) {}

    X operator+(const X& other) {
        if (other.val == 0)
            throw std::runtime_error("Zero error");
        return X(val + other.val);
    }
};

int main() {
    try {
        X a(10), b(0);
        X c = a + b;
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 31. Exception in Initializer List
#include <iostream>
#include <stdexcept>

class A {
public:
    A() { throw std::runtime_error("Init list failed"); }
};

class B {
    A a;
public:
    B() try : a() {
        std::cout << "This never prints\n";
    } catch (...) {
        std::cout << "Caught constructor exception\n";
    }
};

int main() {
    B b;
}

⭐ 32. Exception-Safe Smart Pointers
#include <iostream>
#include <memory>

void risky() {
    throw std::runtime_error("Boom");
}

int main() {
    try {
        std::unique_ptr<int> p(new int(10));
        risky();
    } catch (...) {
        std::cout << "Unique_ptr cleaned up automatically\n";
    }
}

⭐ 33. Exceptions with std::future, std::promise, packaged_task
#include <iostream>
#include <future>
#include <stdexcept>

int work() {
    throw std::runtime_error("Thread exception");
}

int main() {
    std::packaged_task<int()> task(work);
    std::future<int> fut = task.get_future();
    task();  // run

    try {
        fut.get();
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 34. C++20 Concepts + Exceptions
#include <iostream>
#include <concepts>

template<std::integral T>
T safeDivide(T a, T b) {
    if (b == 0) throw std::runtime_error("Divide by zero");
    return a / b;
}

int main() {
    try {
        std::cout << safeDivide(10, 0);
    } catch(const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 35. C++20 Modules + Exceptions (Simplified)
File: mymodule.ixx
export module mymodule;
export int f() {
    throw std::runtime_error("Module exception");
}

File: main.cpp
import mymodule;
#include <iostream>
#include <exception>

int main() {
    try {
        f();
    } catch(const std::exception& e) {
        std::cout << e.what();
    }
}



PART-3 CONTENTS

✔ exception handling inside STL algorithms
✔ exception handling with move-only objects
✔ exception handling with allocators
✔ exception-handling with std::variant
✔ exception-handling with std::optional
✔ exception-handling with std::any
✔ exception specification vs noexcept
✔ type erasure & exception relaying
✔ exception tracing (manual stack trace)
✔ exception safety in node-based containers
✔ new/delete exception guarantees
✔ exception in signal handlers
✔ exception in multi-level inheritance
✔ exception polymorphism dispatching
✔ exception throttling (coalescing exceptions)
✔ conditional rethrowing
✔ exceptions with constexpr (C++20 constraints)
✔ exceptions in fold expressions (C++17)
✔ exceptions in parallel algorithms
✔ exceptions with std::ranges
✔ exceptions in custom memory pools
✔ allocator propagation + exceptions
✔ compile-time exceptions using static_assert

Each program is standalone, has a main(), and compiles individually.

⭐ 36. Exceptions inside std::sort / algorithms
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

int main() {
    std::vector<int> v = {1,0,3,4};

    try {
        std::sort(v.begin(), v.end(),
            [](int a, int b) {
                if (a == 0 || b == 0)
                    throw std::runtime_error("Zero encountered");
                return a < b;
            }
        );
    } catch (const std::exception& e) {
        std::cout << "Sort failed: " << e.what();
    }
}

⭐ 37. Exception with Move-Only Types
#include <iostream>
#include <memory>
#include <vector>

class MoveOnly {
public:
    MoveOnly() = default;
    MoveOnly(MoveOnly&&) {
        throw std::runtime_error("Move failed!");
    }
    MoveOnly& operator=(MoveOnly&&) = delete;
};

int main() {
    try {
        std::vector<MoveOnly> v;
        v.emplace_back(); // works
        v.push_back(MoveOnly()); // move throws
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 38. Exception Safety of Allocators
#include <iostream>
#include <memory>
#include <vector>

struct BadAlloc : std::allocator<int> {
    int* allocate(std::size_t n) {
        throw std::runtime_error("Custom allocator failed");
    }
};

int main() {
    try {
        std::vector<int, BadAlloc> v;
        v.push_back(10);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 39. std::variant and Exceptions
#include <iostream>
#include <variant>

int main() {
    std::variant<int, std::string> v = "hello";

    try {
        std::get<int>(v);  // throws
    } catch (const std::bad_variant_access& e) {
        std::cout << e.what();
    }
}

⭐ 40. std::optional Value Access Exception
#include <iostream>
#include <optional>

int main() {
    std::optional<int> o;

    try {
        std::cout << o.value(); // throws
    } catch (const std::bad_optional_access& e) {
        std::cout << e.what();
    }
}

⭐ 41. std::any Bad Cast Exception
#include <iostream>
#include <any>

int main() {
    std::any a = 10;

    try {
        std::cout << std::any_cast<std::string>(a);
    } catch (const std::bad_any_cast& e) {
        std::cout << e.what();
    }
}

⭐ 42. Exception Specification vs final noexcept
#include <iostream>
#include <exception>

// deprecated exception specification
void legacy() throw(int) { throw 5; }

// modern C++: noexcept
void modern() noexcept(false) { throw 10; }

int main() {
    try { legacy(); }
    catch (...) { std::cout << "Legacy thrown\n"; }

    try { modern(); }
    catch (...) { std::cout << "Modern thrown\n"; }
}

⭐ 43. Type Erasure + Exception Relay
#include <iostream>
#include <functional>

void execute(std::function<void()> f) {
    try {
        f();
    } catch (...) {
        std::cout << "Exception relayed through type erasure\n";
        throw;
    }
}

int main() {
    try {
        execute([] { throw std::runtime_error("Boom!"); });
    } catch (...) {
        std::cout << "Caught in main";
    }
}

⭐ 44. Manual Stack Trace (Simple Trace Log)
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> trace;

void f3() {
    trace.push_back("f3");
    throw std::runtime_error("Fail f3");
}

void f2() {
    trace.push_back("f2");
    f3();
}

void f1() {
    trace.push_back("f1");
    f2();
}

int main() {
    try {
        f1();
    } catch (...) {
        std::cout << "Trace:\n";
        for (auto& s : trace) std::cout << s << "\n";
    }
}

⭐ 45. Exception Safety in Node-Based Containers
#include <iostream>
#include <set>
#include <stdexcept>

struct BadComp {
    bool operator()(int a, int b) const {
        if (a == 2 || b == 2)
            throw std::runtime_error("Comparator failed");
        return a < b;
    }
};

int main() {
    try {
        std::set<int, BadComp> s;
        s.insert(1);
        s.insert(2); // comparator throws
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 46. new/delete & Exception Guarantees
#include <iostream>
#include <new>

int main() {
    try {
        size_t huge = (size_t)-1;
        int* p = new int[huge]; // throws bad_alloc
        delete[] p;
    } catch (const std::bad_alloc&) {
        std::cout << "bad_alloc caught\n";
    }
}

⭐ 47. Exceptions in Signal Handlers — ERROR Example

✔ Demonstrates that C++ exceptions may NOT be thrown safely.

#include <csignal>
#include <iostream>
#include <stdexcept>

void handler(int) {
    std::cout << "Signal caught, do NOT throw exceptions here!\n";
    // throw std::runtime_error("unsafe"); // Undefined behaviour!
}

int main() {
    signal(SIGINT, handler);
    std::cout << "Press Ctrl+C\n";
    while (true);
}

⭐ 48. Multi-Level Inheritance Exception Dispatching
#include <iostream>

struct A : std::exception { const char* what() const noexcept override { return "A"; } };
struct B : A { const char* what() const noexcept override { return "B"; } };
struct C : B { const char* what() const noexcept override { return "C"; } };

int main() {
    try { throw C(); }
    catch (C& c) { std::cout << c.what(); }
    catch (B& b) { std::cout << b.what(); }
    catch (A& a) { std::cout << a.what(); }
}

⭐ 49. Exception Throttling (Coalescing Exceptions)
#include <iostream>
#include <stdexcept>

int failedCount = 0;

void mightFail(bool bad) {
    if (bad) {
        if (++failedCount < 3)
            throw std::runtime_error("Temporary error");
        throw std::runtime_error("Serious error");
    }
}

int main() {
    for (int i=0; i<5; i++) {
        try { mightFail(true); }
        catch (const std::exception& e) {
            std::cout << "Caught: " << e.what() << "\n";
        }
    }
}

⭐ 50. Conditional Rethrow
#include <iostream>
#include <stdexcept>

void f() {
    try {
        throw std::runtime_error("Low error");
    } catch (...) {
        std::cout << "Logging low error\n";
        throw;      // conditional rethrow
    }
}

int main() {
    try { f(); }
    catch (...) { std::cout << "Caught again"; }
}

⭐ 51. Exceptions with constexpr (C++20)

❌ Exceptions are NOT allowed in constexpr execution.
✔ But allowed when not evaluated at compile time.

#include <iostream>
#include <stdexcept>

constexpr int safeDiv(int a, int b) {
    if (b == 0) throw std::runtime_error("zero"); // valid at runtime only
    return a / b;
}

int main() {
    try {
        std::cout << safeDiv(10,0);
    } catch (...) {
        std::cout << "runtime exception allowed\n";
    }
}

⭐ 52. Exception in Fold Expressions (C++17)
#include <iostream>

template<typename... Args>
void risky(Args... args) {
    (..., (args == 0 ? throw std::runtime_error("Zero") : void()));
}

int main() {
    try {
        risky(1,2,0,4);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 53. Exceptions in Parallel Algorithms (C++17)
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <stdexcept>

int main() {
    std::vector<int> v = {1,2,3,0,5};

    try {
        std::for_each(std::execution::par, v.begin(), v.end(),
            [](int x){
                if (x == 0) throw std::runtime_error("Zero found");
            }
        );
    } catch(const std::exception& e) {
        std::cout << "Parallel exception: " << e.what();
    }
}

⭐ 54. Exceptions with std::ranges (C++20)
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v={1,2,0,4};

    try {
        auto r = v | std::views::transform([](int x){
            if (x == 0) throw std::runtime_error("Bad value");
            return x*2;
        });

        for (auto x : r) std::cout << x << " ";
    } catch(const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 55. Exceptions in Custom Memory Pools
#include <iostream>
#include <stdexcept>

class Pool {
public:
    void* alloc() {
        throw std::runtime_error("Pool exhausted");
    }
};

int main() {
    Pool p;
    try {
        p.alloc();
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}

⭐ 56. Allocator Propagation Rules + Exceptions
#include <iostream>
#include <vector>
#include <memory>

struct MyAlloc : std::allocator<int> {
    using propagate_on_container_copy_assignment = std::true_type;
};

int main() {
    try {
        std::vector<int,MyAlloc> v1 = {1,2,3};
        std::vector<int,MyAlloc> v2;

        v2 = v1; // may propagate allocator → may throw
    } catch (...) {
        std::cout << "Exception during allocator propagation";
    }
}

⭐ 57. Compile-Time Exceptions via static_assert
#include <type_traits>

constexpr int f(int x) {
    static_assert(sizeof(int)==4, "int must be 4 bytes");
    return x;
}

int main() {
    return f(10);
}




Part-4 Contents (quick list)

Exception class hierarchy with RTTI-friendly dispatch

Exception-based finite state machine (clear control flow)

Custom scope guard / stack-unwinder for resource rollback

Enriching exceptions with contextual data (translation + nested)

Hybrid error-code + exception pattern (best of both worlds)

Crash-safe logging when throwing (writes before unwind)

High-performance “zero-cost” style: Expected<T,E> (lightweight)

Deep dive: coroutine exception propagation & unhandled_exception

Safe signal handling: defer exception to main loop (correct pattern)

Exception tracer: capture chain + timestamps + minimal backtrace-like info

Exception translation middleware for boundary layers (API → domain)

Building an exception-safe plugin loader (dynamic boundary example)

1) Exception class hierarchy with RTTI dispatch

Demonstrates rich hierarchy + std::rethrow_if_nested usage.

#include <iostream>
#include <exception>
#include <string>

struct AppError : std::exception {
    std::string msg;
    AppError(std::string s): msg(std::move(s)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

struct IOError : AppError { using AppError::AppError; };
struct NetworkError : AppError { using AppError::AppError; };
struct ProtocolError : NetworkError { using NetworkError::NetworkError; };

void handle() {
    try {
        throw ProtocolError("Bad protocol version");
    } catch (...) {
        // demonstrate RTTI-style dispatch
        try { std::rethrow_if_nested(std::current_exception()); } catch(...) {}
        throw; // propagate to caller for a higher-level handler
    }
}

int main() {
    try {
        handle();
    } catch (const ProtocolError& e) {
        std::cout << "ProtocolError: " << e.what() << "\n";
    } catch (const NetworkError& e) {
        std::cout << "NetworkError: " << e.what() << "\n";
    } catch (const AppError& e) {
        std::cout << "AppError: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "std::exception: " << e.what() << "\n";
    }
}

2) Exception-based Finite State Machine (FSM)

Use exceptions for control transfer in a complex state transition sequence.

#include <iostream>
#include <stdexcept>

struct StopState : std::exception {};
struct RetryState : std::exception {};

void stateC() {
    std::cout << "stateC: fatal -> stop\n";
    throw StopState();
}

void stateB() {
    std::cout << "stateB: transient -> retry\n";
    throw RetryState();
}

void runFSM() {
    int attempts = 0;
    while (true) {
        try {
            std::cout << "enter stateA\n";
            // stateA code...
            stateB();
            stateC();
        } catch (const RetryState&) {
            if (++attempts > 3) throw std::runtime_error("Too many retries");
            std::cout << "retrying...\n";
        } catch (const StopState&) {
            std::cout << "stop requested\n";
            break;
        }
    }
}

int main() {
    try { runFSM(); }
    catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
}

3) Custom scope guard / stack-unwinder (commit/rollback)

A tiny ScopeGuard that guarantees rollback on exception.

#include <iostream>
#include <functional>

class ScopeGuard {
    std::function<void()> undo_;
    bool dismissed_ = false;
public:
    ScopeGuard(std::function<void()> f): undo_(std::move(f)) {}
    ~ScopeGuard() noexcept {
        if (!dismissed_) {
            try { undo_(); } catch(...) { /* swallow */ }
        }
    }
    void dismiss() noexcept { dismissed_ = true; }
};

void transactionalOp(bool fail) {
    std::cout << "start transaction\n";
    int resource = 42;
    ScopeGuard rollback([&]{ std::cout << "rolled back resource=" << resource << "\n"; });
    if (fail) throw std::runtime_error("operation failed");
    // commit
    rollback.dismiss();
    std::cout << "committed\n";
}

int main() {
    try { transactionalOp(true); } catch (const std::exception& e) { std::cout << e.what() << "\n"; }
    try { transactionalOp(false); } catch (...) {}
}

4) Enriching exceptions with context (nested + translation)

Attach context at boundaries without losing original cause.

#include <iostream>
#include <stdexcept>
#include <exception>

void lowLevel() {
    throw std::runtime_error("I/O timeout");
}

void boundary() {
    try {
        lowLevel();
    } catch (...) {
        std::throw_with_nested(std::runtime_error("Failed reading config (boundary)"));
    }
}

void printNested(const std::exception& e, int level = 0) {
    for (int i=0;i<level;++i) std::cout << "  ";
    std::cout << "-> " << e.what() << "\n";
    try { std::rethrow_if_nested(e); }
    catch(const std::exception& nested) { printNested(nested, level+1); }
    catch(...) {}
}

int main() {
    try { boundary(); }
    catch(const std::exception& e) { printNested(e); }
}

5) Hybrid: return std::error_code for hot loops, throw for APIs

Pattern: low-overhead hot paths return error codes; boundary layer throws.

#include <iostream>
#include <system_error>

std::error_code computeFast(int x, int& out) noexcept {
    if (x == 0) return std::make_error_code(std::errc::invalid_argument);
    out = 100 / x;
    return {};
}

int compute(int x) {
    int result;
    if (auto ec = computeFast(x, result)) {
        throw std::system_error(ec, "compute failed");
    }
    return result;
}

int main() {
    try { std::cout << compute(0) << "\n"; }
    catch (const std::system_error& e) { std::cout << e.what() << "\n"; }
}

6) Crash-safe logging before throwing

Ensure essential data is persisted before stack unwinding begins.

#include <iostream>
#include <fstream>
#include <stdexcept>

void crashSafeLog(const std::string& msg) {
    std::ofstream out("critical.log", std::ios::app | std::ios::binary);
    if (out) {
        out << msg << std::endl;
        out.flush(); // try to force write
    }
}

void doWork() {
    crashSafeLog("About to throw: important state XYZ");
    throw std::runtime_error("critical failure");
}

int main() {
    try { doWork(); }
    catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
        std::cout << "Check critical.log for pre-crash record\n";
    }
}

7) Lightweight Expected<T,E> (zero-allocation style)

Minimal Expected type to avoid exceptions for hot paths, while still expressive.

#include <iostream>
#include <variant>
#include <string>

template<typename T, typename E>
class Expected {
    std::variant<T,E> v;
public:
    Expected(T t): v(std::move(t)) {}
    Expected(E e): v(std::move(e)) {}
    bool ok() const { return std::holds_alternative<T>(v); }
    T& value() { return std::get<T>(v); }
    E& error() { return std::get<E>(v); }
};

Expected<int, std::string> parseInt(const std::string& s) {
    try { return std::stoi(s); } catch(...) { return std::string("bad int"); }
}

int main() {
    auto r = parseInt("42");
    if (r.ok()) std::cout << "value=" << r.value() << "\n"; else std::cout << "err=" << r.error() << "\n";
    auto r2 = parseInt("nope");
    if (!r2.ok()) std::cout << "err=" << r2.error() << "\n";
}

8) Coroutines: unhandled_exception and propagating exception state

Shows how a coroutine promise can capture exceptions and rethrow later.

#include <iostream>
#include <coroutine>
#include <exception>

struct Task {
    struct promise_type {
        std::exception_ptr eptr;
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() noexcept { eptr = std::current_exception(); }
        void return_void() {}
    };
};

Task failingCoroutine() {
    throw std::runtime_error("coroutine error");
    co_return;
}

int main() {
    try {
        auto t = failingCoroutine();
        // In real frameworks you'd store promise and check eptr later.
        // For demo, the exception invokes unhandled_exception at coroutine time.
        std::cout << "Coroutine invoked\n";
    } catch(const std::exception& e) {
        std::cout << "Caught at call site (if rethrown): " << e.what() << "\n";
    }
    std::cout << "Program continues; coroutines need explicit promise handling to rethrow.\n";
}

9) Safe signal handling: mark & rethrow in main loop (recommended)

Do not throw in a signal handler — set an atomic flag and act later.

#include <atomic>
#include <csignal>
#include <iostream>
#include <thread>
#include <chrono>

std::atomic<bool> sigflag{false};

void handler(int) { sigflag.store(true); }

int main() {
    std::signal(SIGINT, handler);
    std::cout << "Running — press Ctrl+C to trigger\n";
    for (int i=0;i<30;i++) {
        if (sigflag.load()) {
            // safe to throw from main loop
            try { throw std::runtime_error("Deferred signal handling"); }
            catch (const std::exception& e) { std::cout << "Handled: " << e.what() << "\n"; break; }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

10) Exception tracer: capture chain + timestamps

Collect context across layers and print a retrace when handling.

#include <iostream>
#include <exception>
#include <chrono>
#include <sstream>

struct TraceError : std::exception {
    std::string msg;
    std::string time;
    std::exception_ptr nested;
    TraceError(std::string m, std::exception_ptr n = {}): msg(std::move(m)), nested(n) {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        time = std::string(std::ctime(&t));
        if (!time.empty() && time.back()=='\n') time.pop_back();
    }
    const char* what() const noexcept override { return msg.c_str(); }
};

void printTrace(const TraceError& e, int level=0) {
    for(int i=0;i<level;++i) std::cout<<"  ";
    std::cout << "[" << e.time << "] " << e.what() << "\n";
    if (e.nested) {
        try { std::rethrow_exception(e.nested); }
        catch(const TraceError& ne) { printTrace(ne, level+1); }
        catch(const std::exception& se) { for(int i=0;i<=level;++i) std::cout<<"  "; std::cout<< "caused by: "<< se.what() <<"\n"; }
    }
}

void low() { throw std::runtime_error("disk IO"); }
void mid() {
    try { low(); } catch(...) { std::throw_with_nested(TraceError("mid layer", std::current_exception())); }
}
void top() {
    try { mid(); } catch(...) { std::throw_with_nested(TraceError("top layer", std::current_exception())); }
}

int main() {
    try { top(); } catch(const TraceError& e) { printTrace(e); }
    catch(const std::exception& e) { std::cout << "Other: " << e.what() << "\n"; }
}

11) Exception translation middleware (API boundary)

Wrap low-level exceptions into API-defined domain errors.

#include <iostream>
#include <stdexcept>

struct DomainError : std::runtime_error {
    DomainError(const std::string& m): std::runtime_error(m) {}
};

void systemLayer() { throw std::runtime_error("posix: ENOENT"); }

void apiBoundary() {
    try {
        systemLayer();
    } catch (const std::runtime_error& e) {
        // translate to domain error
        throw DomainError(std::string("ResourceMissing: ") + e.what());
    }
}

int main() {
    try { apiBoundary(); }
    catch (const DomainError& d) { std::cout << "Domain error: " << d.what() << "\n"; }
}

12) Exception-safe plugin loader (boundary + cleanup)

Simulates loading plugins and ensures partial init is undone on failure.

#include <iostream>
#include <vector>
#include <stdexcept>

struct Plugin {
    std::string name;
    Plugin(std::string n): name(std::move(n)) { std::cout << "init " << name << "\n"; }
    ~Plugin() noexcept { std::cout << "shutdown " << name << "\n"; }
};

void loadAll(const std::vector<std::string>& names) {
    std::vector<Plugin> loaded;
    for (auto& n : names) {
        // constructing Plugin may throw (simulate)
        if (n == "bad") throw std::runtime_error("plugin corrupt");
        loaded.emplace_back(n);
    }
    std::cout << "all plugins loaded\n";
}

int main() {
    try { loadAll({"alpha","beta","bad","gamma"}); }
    catch (const std::exception& e) { std::cout << "Load failed: " << e.what() << "\n"; }
    std::cout << "Main continues; previously loaded plugins cleaned up by RAII\n";
}
