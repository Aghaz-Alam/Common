Exception handling - custom exceptions, checked and unchecked exceptions ( autosar cpp guidelines)

Exception Handling in C++: Custom Exceptions, Checked and Unchecked Exceptions (According to AUTOSAR C++ Guidelines)
In C++, exception handling is typically done using try, catch, and throw keywords. Exception handling allows the program to handle errors gracefully, 
ensuring that the application can respond to issues without crashing.

When following AUTOSAR C++ guidelines, particularly in embedded systems development, there are specific practices for exception handling 
to make sure that software is safe, robust, and meets real-time requirements. These guidelines emphasize custom exceptions, checked exceptions, and unchecked exceptions.



Overview of Exception Handling Concepts
Custom Exceptions: These are exceptions that are defined by the user, often to handle domain-specific errors.

Checked Exceptions: These are exceptions that must be declared and handled by the function signature. 
C++ does not have checked exceptions in the same way as Java, but you can use noexcept and throw specifications to enforce some constraints.

Unchecked Exceptions: These are exceptions that are not declared or checked at compile time, and the program can throw any type of exception.




C++ Version Differences and Exception Handling
Let us go over the version-wise usage of exception handling in C++11, C++14, and C++17 with a focus on the guidelines provided by 
AUTOSAR (which emphasizes safety and predictability).





1. C++11: Exception Handling (Custom Exceptions, Checked and Unchecked Exceptions)
C++11 introduced a new noexcept specifier and improved exception handling with better support for lambda expressions. 
However, C++ does not have true "checked" exceptions (like Java), and all exceptions are unchecked by default.


In C++11, you define custom exceptions by inheriting from std::exception or other base exception classes.

Custom Exceptions in C++11
#include <iostream>
#include <exception>
using namespace std;
// Custom exception class
class MyCustomException : public std::exception {
  public:
    const char* what() const noexcept override {
        return "My Custom Exception occurred!";
    }
};

void testException() {
    throw MyCustomException();
}

int main() {
    try {
        testException();
    } catch (const MyCustomException& ex) {
        std::cout << "Caught exception: " << ex.what() << std::endl;
    }
  return 0;
}



Noexcept and Exception Specifiers (C++11)
C++11 introduced the noexcept specifier that is used to indicate whether a function may throw exceptions.

void safeFunction() noexcept {
    // No exceptions allowed
}
void riskyFunction() {
    throw std::runtime_error("An error occurred!");
}
int main() {
    safeFunction();  // Compiles because it is noexcept
    riskyFunction(); // Throws exception
  return 0;
}


noexcept: Marks a function as not throwing exceptions.
noexcept(false): Marks a function as potentially throwing exceptions.

AUTOSAR Guidelines for C++11
No dynamic exception handling in critical functions. You should avoid exceptions for functions that are part of a real-time critical path.
Custom exceptions: Recommended for defining error states, but avoid exceptions in high-performance code paths.
Unchecked exceptions: In AUTOSAR, unchecked exceptions are discouraged in time-critical systems.



2. C++14: Enhancements in Exception Handling
In C++14, exception handling remains the same as in C++11, but there were some improvements to the lambda and type traits that 
can be used in conjunction with exceptions.



Custom Exceptions with Lambdas in C++14
While custom exceptions do not change significantly, you can use lambdas to simplify exception handling when throwing or catching exceptions.

#include <iostream>
#include <exception>

class MyCustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "My Custom Exception occurred!";
    }
};

int main() {
    auto safeLambda = []() {
        throw MyCustomException();
    };

    try {
        safeLambda();
    } catch (const MyCustomException& ex) {
        std::cout << "Caught exception: " << ex.what() << std::endl;
    }

    return 0;
}


In C++14, exception handling still follows the same principles. However, it provides better support for lambda expressions as function objects, 
allowing for more flexible exception handling.



Noexcept in C++14
C++14 builds on noexcept and provides more expressive ways to apply it to functions, including when using lambdas:

#include <iostream>
int add(int a, int b) noexcept {
    return a + b;
}
int main() {
    // safe to call add() as it is marked noexcept
    std::cout << add(1, 2) << std::endl;
   return 0;
}



AUTOSAR Guidelines for C++14
As with C++11, exceptions in time-sensitive or safety-critical systems are discouraged.
If exceptions must be used, they should be checked in the higher-level layers, and critical low-level code should avoid throwing exceptions.
No throwing across APIs in time-critical functions.





3. C++17: Further Enhancements to Exception Handling
C++17 builds on previous versions and introduces std::any, std::optional, and std::variant which can be used for 
exception handling when you do not want to throw exceptions directly. 

It also refines the noexcept specifier for better type inference.



Custom Exception with Inheritance in C++17
In C++17, the general pattern for defining custom exceptions does not change, 
but you may use noexcept more rigorously to indicate functions that would not throw exceptions.

#include <iostream>
#include <exception>
using namespace std;
class MyCustomException : public std::exception {
  public:
    const char* what() const noexcept override {
        return "My Custom Exception occurred!";
    }
};
void functionThatThrows() noexcept(false) {  // Explicitly states it can throw exceptions
    throw MyCustomException();
}
int main() {
    try {
        functionThatThrows();
    } catch (const MyCustomException& ex) {
        std::cout << "Caught exception: " << ex.what() << std::endl;
    }

  return 0;
}




noexcept in C++17
In C++17, the noexcept specifier can be inferred automatically by the compiler when using lambdas or functions. 
This means you do not need to explicitly state noexcept if the compiler can deduce it.

auto func = []() noexcept {
    // Code that does not throw exceptions
};
void anotherFunction() noexcept(false) {
    throw std::runtime_error("Error!");
}
int main() {
    func();  // No exceptions
    anotherFunction();  // Throws exception
    return 0;
}



AUTOSAR Guidelines for C++17
No exception handling in performance-critical or real-time contexts.
Custom exceptions can be used but should not be thrown in high-priority or real-time code.
noexcept should be used to clearly communicate whether a function can throw exceptions or not.
Avoid any dynamic memory allocation or heap-based exceptions in embedded systems (they are typically not used in AUTOSAR-based environments).





Checked vs. Unchecked Exceptions (C++11, C++14, C++17)
Checked Exceptions in C++
C++ does not have checked exceptions as in Java. However, you can enforce that certain functions must or must not throw exceptions by using:
noexcept: A function marked noexcept is guaranteed not to throw exceptions.
throw() or noexcept(false): A function that explicitly throws exceptions can be marked with noexcept(false).




Unchecked Exceptions in C++
In C++11, C++14, and C++17, exceptions are unchecked by default. You can throw any type of object, including objects that don’t derive from std::exception.

void throwUncheckedException() {
    throw 42;  // Unchecked exception
}


AUTOSAR Guidelines:
Unchecked exceptions (throwing any object) are not recommended in real-time, embedded systems because they can be unpredictable.
It is best to define custom exceptions derived from std::exception to provide consistent exception handling.

Conclusion:
C++11: Introduced noexcept, and custom exceptions, but the concept of checked exceptions does not exist in C++. 
It is up to the developer to ensure that functions that are part of real-time or performance-critical paths do not throw exceptions.
C++14: Enhanced exception handling with lambdas and provided additional tools for exception-free function signatures (noexcept).
C++17: Further refined exception handling, especially in terms of using noexcept and lambda functions. It also made it easier to work with exception-safe code using better type inference and functional programming patterns.


AUTOSAR C++ Guidelines:
Exception handling is discouraged in time-critical or safety-critical systems.
Custom exceptions are acceptable but should be used with caution.
Use **noexcept