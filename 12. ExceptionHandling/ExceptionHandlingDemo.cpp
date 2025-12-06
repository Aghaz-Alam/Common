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
