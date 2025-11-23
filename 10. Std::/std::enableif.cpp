1. std::enable_if in C++11
In C++11, std::enable_if is used to conditionally enable a function or class template based on a type trait or expression. 
The std::enable_if works by using the SFINAE (Substitution Failure Is Not An Error) principle, 
where if the condition fails, the template instantiation is discarded.

Example: std::enable_if to enable a function only for integral types
#include <iostream>
#include <type_traits> // For std::enable_if, std::is_integral
using namespace std;
// Function template for integral types only
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}
int main() {
    std::cout << "Sum of 5 and 3 (int): " << add(5, 3) << std::endl; // Works (integral type)

    // std::cout << "Sum of 5.5 and 3.3 (double): " << add(5.5, 3.3) << std::endl; // Error (not an integral type)
    
  return 0;
}

Explanation:
std::enable_if<std::is_integral<T>::value, T>::type enables the add function only for integral types (int, char, etc.). 
If you try to call add with a non-integral type like double, it will cause a compilation error because 
the function is not enabled for floating-point types.






2. std::enable_if in C++14
In C++14, std::enable_if is essentially the same as in C++11. However, C++14 brings improvements like generalized lambda expressions, 
which can be combined with std::enable_if to create even more powerful and expressive code.

Example: std::enable_if with a lambda expression
In C++14, we can use lambda expressions along with std::enable_if. The std::enable_if usage remains the same, 
but we can use lambdas in places where we might want to perform type-checking or type manipulation.
#include <iostream>
#include <type_traits> // For std::enable_if, std::is_integral
using namespace std;
// Function template with a lambda to check for integral types
template <typename T>
auto add(T a, T b) -> typename std::enable_if<std::is_integral<T>::value, T>::type {
    return a + b;
}
int main() {
    std::cout << "Sum of 5 and 3 (int): " << add(5, 3) << std::endl; // Works (integral type)
    
    // std::cout << "Sum of 5.5 and 3.3 (double): " << add(5.5, 3.3) << std::endl; // Error (not an integral type)

  return 0;
}

Explanation:
In this case, the code is very similar to C++11, but the lambda syntax in the return type (auto) makes the code more concise and readable.








3. std::enable_if in C++17
In C++17, std::enable_if remains largely unchanged from C++11 and C++14, but there are a few enhancements to the language that 
can make using std::enable_if more convenient and expressive:


Example: std::enable_if with if constexpr (new in C++17)
In C++17, the if constexpr feature was introduced, which allows for compile-time conditional logic. 
This makes it easier to write generic code that behaves differently depending on whether certain conditions are met, 
without the need for std::enable_if in many cases. However, std::enable_if is still very useful when you need to restrict 
templates or perform SFINAE-based logic.

Here is how std::enable_if can still be useful when combined with if constexpr:
#include <iostream>
#include <type_traits>  // For std::enable_if, std::is_integral
using namespace std;
// Function template for integral types using if constexpr (new in C++17)
template <typename T>
auto add(T a, T b) {
    if constexpr (std::is_integral<T>::value) {
        return a + b;  // For integral types, add them
    } else {
        return T(0);  // For non-integral types, return 0 (this code is not even compiled if T is integral)
    }
}
int main() {
    std::cout << "Sum of 5 and 3 (int): " << add(5, 3) << std::endl; // Works (integral type)
    std::cout << "Sum of 5.5 and 3.3 (double): " << add(5.5, 3.3) << std::endl;  // Works (non-integral type)

    return 0;
}

Explanation:
In this code, the if constexpr is used to determine at compile-time whether the type T is integral or not.
For integral types, the add function performs the addition.
For non-integral types, it returns a default-constructed value (0 for non-integral types). 
The code inside the else branch is not compiled for integral types, thanks to if constexpr.


While if constexpr can often replace std::enable_if in C++17 and later, std::enable_if is still useful in cases where 
we need to specialize types or control the availability of functions based on more complex conditions.


Key Differences in C++ Versions
C++11: std::enable_if is available and is used to conditionally enable template functions based on type traits or expressions. 
You manually enable or disable functions by adding typename std::enable_if<condition>::type as the return type.


C++14: The functionality of std::enable_if remains the same as in C++11. However, C++14 allows for more concise code, 
especially with generalized lambda captures, though this does not directly affect std::enable_if. 

The basic usage is unchanged.

C++17: std::enable_if continues to be used as in C++11 and C++14, but with the introduction of if constexpr, 
you can often replace it with simpler, more readable code that is easier to maintain. However, std::enable_if remains useful for 
SFINAE-based template specialization and advanced metaprogramming.



Full Example: std::enable_if in C++11, C++14, and C++17
#include <iostream>
#include <type_traits>  // For std::enable_if, std::is_integral

// C++11 / C++14: Using std::enable_if with function templates
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

// C++17: Using std::enable_if with if constexpr (more readable code)
template <typename T>
auto add_with_if_constexpr(T a, T b) {
    if constexpr (std::is_integral<T>::value) {
        return a + b;
    } else {
        return T(0);  // For non-integral types, return default-constructed value
    }
}

int main() {
    std::cout << "C++11 / C++14 (std::enable_if): " << add(5, 3) << std::endl;  // Works
    // std::cout << "C++11 / C++14 (std::enable_if): " << add(5.5, 3.3) << std::endl;  // Compile-time error

    std::cout << "C++17 (if constexpr): " << add_with_if_constexpr(5, 3) << std::endl;  // Works
    std::cout << "C++17 (if constexpr): " << add_with_if_constexpr(5.5, 3.3) << std::endl;  // Works, returns 0

    return 0;
}


Summary
C++11: std::enable_if is used to control function/template specialization based on type conditions (e.g., std::is_integral<T>).
C++14: Same as C++11, but with more powerful lambda expressions and generalized lambda captures.
C++17: Continues to use

