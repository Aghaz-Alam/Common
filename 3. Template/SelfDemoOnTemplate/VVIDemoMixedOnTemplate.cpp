Normal template usage

// c++11-decltype
#include <iostream>
using namespace std;
template <typename T1, typename T2>
auto Add(T1 x, T2 y) -> decltype(x + y) {
    return x + y;
}
int main() {
    cout << "Addition of 3 and 7.5f is: " << Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << Add(3.5, 7) << endl;
    cout << "Addition of 'A' and 'E' is: " << Add(char('A'), char('E')) << endl;  //A=65, B=69   ===A+B=65+69=134
    cout << "Addition of Hello and World is: " << Add(string("Hello "), string("World!")) << endl; //Hello World
    
   return 0;
}
/* DemoNormalTemplate
Output:
Addition of 3 and 7.5f is: 10.5
Addition of 3.5f and 7.5 is: 11
Addition of 3.5 and 7 is: 10.5
Addition of 'A' and 'E' is: 134
Addition of Hello and World is: Hello World!
*/


// c++14-auto-return-type
#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
auto Add(T1 x, T2 y) {
    return x + y;   // C++14 deduces return type automatically
}

int main() {
    cout << "Addition of 3 and 7.5f is: " << Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << Add(3.5, 7) << endl;

    cout << "Addition of 'A' and 'E' is: " << Add(char('A'), char('E')) << endl;  // 65 + 69 = 134

    cout << "Addition of Hello and World is: " << Add(string("Hello "), string("World!")) << endl;

    return 0;
}
/*
Addition of 3 and 7.5f is: 10.5
Addition of 3.5f and 7.5 is: 11
Addition of 3.5 and 7 is: 10.5
Addition of 'A' and 'E' is: 134
Addition of Hello and World is: Hello World!
*/





// Variadic Templates  c++11 And C++14 same
#include <iostream>
using namespace std;
// Base case
void print() {
    cout << "Empty Function! " << endl;
}

// Variadic template function: processes one argument and recursively calls itself
template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first<< endl;
    print(rest...); // Pack expansion: calls print with the remaining arguments
}

int main() {
    print(1, 2.5, "Hello", 'A'); 
}
/*
Output;
1
2.5
Hello
A
Empty Function! 
*/



//C++17
#include <iostream>
using namespace std;
template <typename... Args>
void print(Args... args) {
    // Print each argument followed by newline
    ((cout << args << endl), ...);

    cout << "Empty Function!" << endl;
}

int main() {
    print(1, 2.5, "Hello", 'A');
}
/*
1
2.5
Hello
A
Empty Function!
*/



// Variadic Templates - C++11 / C++14
#include <iostream>
using namespace std;
// Base case
int add() {
    cout << "Empty Function!" << endl;
    return 0;
}
// Variadic template recursive function
template <typename T, typename... Args>
int add(T first, Args... rest) {
    return first + add(rest...);
}

int main() {
    cout << add(1, 2, 3, 4, 5) << endl;
}
/*
Output;
Empty Function! 
15
*/


// Variadic Templates - C++17 (Fold Expression)
#include <iostream>
using namespace std;
// Variadic add using fold expression
template <typename... Args>
int add(Args... args) {
    cout << "Empty Function!" << endl;   // mimic your original behavior
    return (args + ...);                 // C++17 fold expression
}
int main() {
    cout << add(1, 2, 3, 4, 5) << endl;
}
/*
Empty Function!
15
*/




//C++14 Mixed sum
#include <iostream>
using namespace std;
// 1. Base case: non-template function to stop the recursion (handles the empty pack)
int Sum() {
    return 0;
}

// 2. Recursive case: template function to process one argument and recurse
template<typename T, typename... Args>
int Sum(T first, Args... rest) {
    // The recursive call with a reduced parameter pack
    return first + Sum(rest...);
}
int main() {
    // The compiler generates instantiations for Sum(1, 2, 3), 
    // then Sum(2, 3), then Sum(3), and finally Sum()
    int total1 = Sum(1, 2, 3, 4, 5); 
    cout << "Sum is: " << total1 << endl; // Output: Sum is: 15

    // Works with different types (implicit conversion to int return type)
    int total2 = Sum(1, 2.5, 3);
    cout << "Mixed Sum is: " << total2 << endl; // Output: Mixed Sum is: 6 (due to int return type)

    return 0;
}
/*
Sum is: 15
Mixed Sum is: 6
*/



//Mixed sum C++17
#include <iostream>
using namespace std;

// C++17 fold-expression based Sum()
template <typename... Args>
auto Sum(Args... args) {
    return (args + ...);   // Fold expression (right fold)
}

int main() {
    int total1 = Sum(1, 2, 3, 4, 5);
    cout << "Sum is: " << total1 << endl;  // 15

    // Now returns double, no truncation!
    auto total2 = Sum(1, 2.5, 3);
    cout << "Mixed Sum is: " << total2 << endl;  // 6.5

    return 0;
}
/*
Sum is: 15
Mixed Sum is: 6.5
*/


//C++ 11/14/17
1. Full Template Specialization
In full specialization, We provide an entirely separate implementation for a specific type or class template.
#include <iostream>
using namespace std;

// Primary template
template <typename T>
void print(T value) {
    cout << "Generic template: " << value << endl;
}

// Full specialization for int
template <>
void print<int>(int value) {
    cout << "Specialized template for int: " << value << endl;
}

int main() {
    print(3.14);  // Uses the generic template
    print(42);    // Uses the specialized template for int
    return 0;
}
/*
Generic template: 3.14
Specialized template for int: 42
*/


//C++11/14/17 same with return value
#include <iostream>
using namespace std;

// Primary template
template <typename T>
T print(T value) {
    cout << "Generic template: " << value << endl;
    return value;     // Return the same value
}

// Full specialization for int
template <>
int print<int>(int value) {
    cout << "Specialized template for int: " << value << endl;
    return value * 2;   // Just an example: return modified value
}

int main() {
    double d = print(3.14);   // Uses generic version
    int n     = print(42);    // Uses specialized version

    cout << "Returned (generic): " << d << endl;
    cout << "Returned (specialized int): " << n << endl;

    return 0;
}

/*
Generic template: 3.14
Specialized template for int: 42
Returned (generic): 3.14
Returned (specialized int): 84
*/


2. Partial Template Specialization
In partial specialization, you define a specialized version of the template that works for a subset of types. 
For example, you might want to specialize a template for pointer types or reference types.

#include <iostream>
using namespace std;

// Primary template
template <typename T>
void print(T value) {
    cout << "Generic template: " << value << endl;
}

// Partial specialization for pointer types
template <typename T>
void print(T* value) {
    cout << "Specialized template for pointer: " << *value << endl;
}
int main() {
    int x = 10;
    print(x);          // Uses the generic template
    print(&x);         // Uses the specialized template for pointers
    return 0;
}
/*
Generic template: 10
Specialized template for pointer: 10
*/


3. Template Specialization with Multiple Parameters

You can also specialize a template when it has multiple parameters. 
For example, you can specialize a template when one of its parameters is a certain type.


include <iostream>
using namespace std;

// Generic template with two parameters
template <typename T, typename U>
void print(T value1, U value2) {
    cout << "Generic template: " << value1 << ", " << value2 << endl;
}

// Overload for int as the first parameter
template <typename U>
void print(int value1, U value2) {
    cout << "Specialized template for int as first parameter: " << value1 << ", " << value2 << endl;
}

int main() {
    print(5, 3.14);     // Uses the overload for int
    print("Hello", 42); // Uses the generic template
    return 0;
}
/*
Specialized template for int as first parameter: 5, 3.14
Generic template: Hello, 42
*/






3. SFINAE C++11
Sometimes, you may want to specialize templates based on certain conditions like whether a type is integral or 
floating-point. 
This is often achieved using SFINAE (Substitution Failure Is Not An Error) along with std::enable_if or type traits.


#include <iostream>
#include <type_traits>
using namespace std;

// Function template enabled only for arithmetic types
template <typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
add(T a, T b) {
    cout << "Arithmetic add() called\n";
    return a + b;
}

// Overload for non-arithmetic types (optional)
template <typename T>
typename enable_if<!is_arithmetic<T>::value, T>::type
add(T a, T b) {
    cout << "Non-arithmetic add() called\n";
    return a + b; // Just for demonstration
}

int main() {
    cout << add(10, 20) << endl;          // OK: int → arithmetic
    cout << add(2.5, 3.7) << endl;        // OK: double → arithmetic
    cout << add(2.5f, 5.7f) << endl;      // OK: float → arithmetic

    // Example non-arithmetic type
    string x = "Hello ", y = "World";
    cout << add(x, y) << endl;            // Non-arithmetic version called

    return 0;
}
/*
Arithmetic add() called
30
Arithmetic add() called
6.2
Arithmetic add() called
8.2
Non-arithmetic add() called
Hello World
*/

//C++14
#include <iostream>
#include <type_traits>
using namespace std;

// Function enabled only for arithmetic types
template <typename T>
enable_if_t<is_arithmetic<T>::value, T>
add(T a, T b) {
    cout << "Arithmetic add() called\n";
    return a + b;
}

// Function enabled only for non-arithmetic types (e.g., string)
template <typename T>
enable_if_t<!is_arithmetic<T>::value, T>
add(T a, T b) {
    cout << "Non-arithmetic add() called\n";
    return a + b; // works if operator+ is defined
}

int main() {
    cout << add(10, 20) << endl;        // int → arithmetic
    cout << add(2.5, 3.7) << endl;      // double → arithmetic
    cout << add(2.5f, 5.7f) << endl;    // float → arithmetic

    string x = "Hello ", y = "World";
    cout << add(x, y) << endl;          // string → non-arithmetic

    return 0;
}
/*
Arithmetic add() called
30
Arithmetic add() called
6.2
Arithmetic add() called
8.2
Non-arithmetic add() called
Hello World
*/



//Metaprogramming
Metaprogramming (C++11)
C++11 formalized many metaprogramming techniques and improved their syntax and usability. 

Key features included:
constexpr: Allowed functions and variables to be evaluated at compile time, providing a more readable 
and efficient alternative to complex template recursion for simple calculations.

<type_traits> library: Standardized tools for type manipulation and introspection, 
which are the backbone of modern C++ metaprogramming.


Example: Compile-time calculation using constexpr:
#include <iostream>
using namespace std;
// C++11 constexpr factorial (recursive)
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}
int main() {
    constexpr int f5 = factorial(5); // compile-time evaluation
    cout << "Factorial of 5: " << f5 << endl;
}
/*
Factorial of 5: 120
*/



Metaprogramming C++14
C++14 significantly eased the implementation of metaprograms by relaxing the constraints on constexpr functions.

A. Relaxed constexpr:
In C++11, constexpr functions were limited to a single return statement 
(often using the ternary operator for logic/recursion). 

C++14 allowed constexpr functions to contain:
->Local variable declarations
->if and switch statements
->Loops (for, while, do-while)

This allowed compile-time computation to be written in a style very close to normal runtime C++ code, 
almost entirely replacing complex template recursion for many numeric tasks.

#include <iostream>
using namespace std;
constexpr int factorial(int n) {
    if(n<=1) return 1;   // base case
    
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}
int main() {
    constexpr int f5 = factorial(5); // compile-time evaluation
    cout << "Factorial of 5: " << f5 << endl;
}
/*
Factorial of 5: 120
*/

