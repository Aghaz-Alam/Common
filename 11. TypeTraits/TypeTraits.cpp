type traits



Type Traits in C++11, C++14, and C++17

Type traits are a collection of templates that allow you to query and manipulate types at compile time. 
They are typically defined in the <type_traits> header. 
Type traits are extremely useful in generic programming, where you often need to make decisions based on the properties of types.

Let us go over the type traits in C++11, C++14, and C++17, and see the features available in each version, with examples for each.


1. Type Traits in C++11
C++11 introduced the core set of type traits. It provides several templates to inspect, transform, or manipulate types at compile time. 
The most commonly used type traits in C++11 are in the <type_traits> header.


Commonly Used Type Traits in C++11
std::is_integral<T>: Checks if T is an integral type (like int, char, short, etc.).
std::is_floating_point<T>: Checks if T is a floating-point type (float, double, long double).
std::is_pointer<T>: Checks if T is a pointer type.
std::is_same<T, U>: Checks if two types T and U are the same.
std::remove_reference<T>: Removes references from type T.


Example: Basic Usage in C++11
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << boolalpha;

    cout << "is_integral<int>: " << std::is_integral<int>::value << endl;
    cout << "is_integral<double>: " << std::is_integral<double>::value << endl;

    cout << "is_pointer<int*>: " << std::is_pointer<int*>::value << endl;
    cout << "is_pointer<int>: " << std::is_pointer<int>::value << endl;

    cout << "is_same<int, int>: " << std::is_same<int, int>::value << endl;
    cout << "is_same<int, double>: " << std::is_same<int, double>::value << endl;

  return 0;
}
/* 
Output:
is_integral<int>: true
is_integral<double>: false
is_pointer<int*>: true
is_pointer<int>: false
is_same<int, int>: true
is_same<int, double>: false
*/










2. Type Traits in C++14
C++14 builds upon C++11 by adding new type traits and refining the existing ones. 
However, the majority of the type traits available in C++11 remain the same in C++14.


New Type Traits Introduced in C++14:
std::is_convertible<T, U> (Enhanced for class types): 
This checks if type T is convertible to type U (refined to work with class types and pointers more effectively).

std::is_trivially_copyable<T>: Checks if a type T is trivially copyable (i.e., a type that can be copied via memcpy).
std::make_signed<T> / std::make_unsigned<T>: Convert integer types to their signed/unsigned variants.
std::aligned_storage<sizeof(T), alignof(T)>: This is used to allocate memory with custom alignment.


Example: New Type Traits in C++14
#include <iostream>
#include <type_traits>
using namespace std;
struct Base {
    virtual ~Base() {}
};

struct Derived : public Base {};

int main() {
    // C++14 - is_convertible
    std::cout << "is_convertible<Derived*, Base*>: " << std::is_convertible<Derived*, Base*>::value << std::endl;
    std::cout << "is_convertible<Base*, Derived*>: " << std::is_convertible<Base*, Derived*>::value << std::endl;

    // C++14 - is_trivially_copyable
    std::cout << "is_trivially_copyable<int>: " << std::is_trivially_copyable<int>::value << std::endl;
    std::cout << "is_trivially_copyable<std::string>: " << std::is_trivially_copyable<std::string>::value << std::endl;

  return 0;
}
/* 
Output:
is_convertible<Derived*, Base*>: true
is_convertible<Base*, Derived*>: false
is_trivially_copyable<int>: true
is_trivially_copyable<std::string>: false
*/







3. Type Traits in C++17
C++17 introduces several enhancements to the existing type traits and adds new type traits for more fine-grained type manipulation.

New Type Traits Introduced in C++17:
std::is_nothrow_invocable<T, Args...>: Checks whether a function or callable T can be invoked with arguments of type Args... without 
throwing exceptions.
std::is_invocable<T, Args...>: Checks whether T is callable with arguments of type Args....
std::is_trivially_constructible<T>: Checks if T can be constructed trivially (e.g., no user-defined constructor).
std::is_default_constructible<T>: Checks if T is default-constructible (i.e., it can be created with a default constructor).
std::is_copy_constructible<T> / std::is_move_constructible<T>: Checks if T is copy or move constructible.

Example: New Type Traits in C++17
#include <iostream>
#include <type_traits>
#include <functional> // for std::function
using namespace std;
// Function to check noexcept behavior
void foo() noexcept {
    // Nothing
}
void bar() {
    // This function throws an exception
    throw std::runtime_error("Error");
}
int main() {
    // C++17 - is_nothrow_invocable
    std::cout << "is_nothrow_invocable<void()>: " << std::is_nothrow_invocable<void()>::value << std::endl;
    std::cout << "is_nothrow_invocable<decltype(foo)>: " << std::is_nothrow_invocable<decltype(foo)>::value << std::endl;
    std::cout << "is_nothrow_invocable<decltype(bar)>: " << std::is_nothrow_invocable<decltype(bar)>::value << std::endl;

    // C++17 - is_invocable
    std::cout << "is_invocable<std::function<void()>>: " << std::is_invocable<std::function<void()>>::value << std::endl;

    // C++17 - is_trivially_constructible
    std::cout << "is_trivially_constructible<int>: " << std::is_trivially_constructible<int>::value << std::endl;

    // C++17 - is_copy_constructible
    std::cout << "is_copy_constructible<std::string>: " << std::is_copy_constructible<std::string>::value << std::endl;

  return 0;
}
/* 
Output:
is_nothrow_invocable<void()>: true
is_nothrow_invocable<decltype(foo)>: true
is_nothrow_invocable<decltype(bar)>: false
is_invocable<std::function<void()>>: true
is_trivially_constructible<int>: true
is_copy_constructible<std::string>: true
*/