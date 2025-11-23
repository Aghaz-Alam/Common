Templates
- Normal template usage
- template specialization
- SFINAE (Substitution Failure Is Not An Error)
- metaprogramming


-Normal template usage
==>C++ template is a powerful tool for creating generic classes or functions. 
==>This allows us to write code that works for any data type without rewriting it for each type.

Key feature of templates :
-Avoid code duplication by allowing one function or class to work with multiple data types, mainly allowing generic functions and classes.
-Provide type safety, unlike using void* pointers or macros.
-Can be specialized for specific data types when needed.
-Form the basis of STL containers and algorithms like vector, map, and sort.

(A) Function Templates
#include <iostream>
using namespace std;
template <typename T> 
T myMax(T x, T y){
    return (x > y) ? x : y;
}

int main(){
    cout << "Max of 3 and 7 is: " << myMax<int>(3, 7) << endl;
    cout << "Max of 3.5 and 7.5 is :" << myMax<double>(3.5, 7.5) << endl;
    cout << "Max of 'g' and 'e' is: " << myMax<char>('g', 'e') << endl;  
  return 0;
}

(B) Class Templates
#include <iostream>
using namespace std;

template <typename T>
class Pair {
  public:
    T first, second;

    Pair(T x, T y): first(x), second(y){ }

    T getMax() {
        return (first > second) ? first : second;
    }
};

int main() {
    // Create a Pair object for integers
    Pair<int> intPair(10, 20);
    cout << "Max of int pair: " << intPair.getMax() << endl;

    // Create a Pair object for doubles
    Pair<double> doublePair(3.5, 7.5);
    cout << "Max of double pair: " << doublePair.getMax() << endl;

    return 0;
}


(C) Variadic Templates

//a. Function Template Recursion
//*
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


//*
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

//b. Class Template Specialization
#include <iostream>
#include <string>
using namespace std;

// Primary template: General definition for a variadic template class (e.g., a simple Tuple)
template <typename... Args>
class Tuple; // Declaration only; actual implementation uses partial specialization below

// Partial specialization for the case when at least one argument exists
template <typename Head, typename... Tail>
class Tuple<Head, Tail...> {
  public:
    Head head;
    Tuple<Tail...> tail; // The rest of the tuple

    Tuple(Head h, Tail... t) : head(h), tail(t...) {
        // Constructor initializes the current head and the rest of the tail tuple
    }

    void print() {
        cout << "Head: " << head << endl;
        tail.print(); // Recursively call print on the rest of the tuple
    }
};

// Explicit specialization for the base case (when no arguments are left)
template <>
class Tuple<> {
  public:
    void print() {
        cout << "End of Tuple." << endl;
    }
};

int main() {
    // Create a Tuple instance with different data types
    Tuple<int, double, string, char> myTuple(10, 5.5, "Tuple Example", 'C');

    cout << "Printing Tuple elements:" << endl;
    myTuple.print();

    return 0;
}



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

#include <iostream>
using namespace std;

// Primary template with two parameters
template <typename T, typename U>
void print(T value1, U value2) {
    cout << "Generic template: " << value1 << ", " << value2 << endl;
}

// Partial specialization when the first parameter is int
template <typename U>
void print<int, U>(int value1, U value2) {   // ❌ Invalid in C++
    cout << "Specialized template for int as first parameter: " << value1 << ", " << value2 << endl;
}

int main() {
    print(5, 3.14);     // Uses the specialized template for int as the first parameter
    print("Hello", 42); // Uses the generic template
    return 0;
}
/*
Specialized template for int as first parameter: 5, 3.14
Generic template: Hello, 42
*/


//Corrected Program is 
#include <iostream>
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



4. SFINAE and Template Specialization

Sometimes, you may want to specialize templates based on certain conditions like whether a type is integral or 
floating-point. 
This is often achieved using SFINAE (Substitution Failure Is Not An Error) along with std::enable_if or type traits.

#include <iostream>
#include <type_traits>
using namespace std;

// Primary template (only enabled for non-integral and non-floating-point types)
template <typename T>
typename std::enable_if<!std::is_integral<T>::value && !std::is_floating_point<T>::value>::type
print(T value) {
    cout << "Generic template: " << value << endl;
}

// Specialization for integral types (like int, char)
template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print(T value) {
    cout << "Specialized for integral type: " << value << endl;
}

// Specialization for floating-point types (like float, double)
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type
print(T value) {
    cout << "Specialized for floating-point type: " << value << endl;
}

int main() {
    print(42);         // Uses the specialization for integral type
    print(3.14);       // Uses the specialization for floating-point type
    print("Hello");    // Uses the generic template
    return 0;
}
/*
Specialized for integral type: 42
Specialized for floating-point type: 3.14
Generic template: Hello
*/




//c. Using Initializer Lists
#include <iostream>
#include <vector>
using namespace std;

// Helper function to process each element in the initializer list
template<typename T>
void process(T t) {
    cout << t << endl;
}

// Variadic template function using an initializer list trick
template <typename... Args>
void printList(Args... args) {
    cout << "Printing using initializer list:" << endl;

    // Create a dummy array where each element initialization calls the 'process' helper function
    // The comma operator ensures each call to 'process(args)' is executed in order.
    int dummy[] = {0, (process(args), 0)...};

    // Suppress unused variable warning if needed, the array is only for side effects
    (void)dummy;
}

// C++17 introduces "fold expressions", which are much cleaner for this purpose:
template <typename... Args>
void printFold(Args... args) {
    cout << "Printing using C++17 fold expression:" << endl;
    // (process(args), ...); // This would also work in C++17
    // For simple printing to cout:
    ((cout << args << endl), ...);
}

int main() {
    printList(1, 2.5, "Hello", 'A');
    cout << endl;
    // C++17 required for the next call
    // printFold(1, 2.5, "Hello", 'A');

    return 0;
}





//2. Alias Templates
a. Simple Pointer Alias
A common, simple use case is creating an alias for a pointer to any type: 
template<typename T>
using ptr = T*;

int main() {
    ptr<int> x;  // Same as int* x
    ptr<double> y; // Same as double* y
}


/* -------------------------------------- */
#include <iostream>

template<typename T>
using ptr = T*;

int main() {
    // Using the alias template to declare pointers
    ptr<int> x = new int;       // Same as int* x = new int;
    ptr<double> y = new double; // Same as double* y = new double;

    // Assign values
    *x = 42;
    *y = 3.14;

    // Print values
    std::cout << "x = " << *x << std::endl;
    std::cout << "y = " << *y << std::endl;

    // Free allocated memory
    delete x;
    delete y;

    return 0;
}
/*
x = 42
y = 3.14
*/
/* -------------------------------------- */


b. Simplifying Complex Template Types
Alias templates are extremely useful for shortening verbose, nested template names, which improves code readability. 
This is frequently seen in the standard library.

Output

Result: 24
Ensure that you correctly parenthesize operators when necessary, especially in binary left-fold expressions.


/* ------------------- */
#include <iostream>
#include <tuple>

// Alias template to simplify a tuple type
template<typename... Ts>
using MyTuple = std::tuple<Ts...>;

// Function to multiply all arguments using a binary left-fold
template<typename... Ts>
int multiply(Ts... args) {
    return (... * args);  // left fold: (((args1 * args2) * args3) * ...)
}

int main() {
    // Using the alias template for a tuple
    MyTuple<int, int, int> t = std::make_tuple(2, 3, 4);

    // Multiply all elements in the tuple
    int result = std::apply([](auto... elems) { return multiply(elems...); }, t);

    std::cout << "Result: " << result << std::endl;  // Output: Result: 24

    return 0;
}
/*
Result: 24
*/
/* ------------------- */


// Original complex type
std::map<std::string, std::vector<std::string>> myMap;

// Using an alias template to create a more readable name
template<typename T1, typename T2>
using MapAlias = std::map<T1, std::vector<T2>>; //

int main() {
    MapAlias<std::string, std::string> map1; // Cleaner declaration
    MapAlias<int, float> map2;               // Easily change underlying types
}

/* ----------------- */
#include <iostream>
#include <map>
#include <vector>
#include <string>

// Alias template to simplify the complex map type
template<typename T1, typename T2>
using MapAlias = std::map<T1, std::vector<T2>>;

int main() {
    // Using the alias template for easier map declaration
    MapAlias<std::string, std::string> map1; 
    MapAlias<int, float> map2;               

    // Insert elements into map1
    map1["fruits"].push_back("apple");
    map1["fruits"].push_back("banana");
    map1["colors"].push_back("red");
    map1["colors"].push_back("blue");

    // Insert elements into map2
    map2[1].push_back(1.1f);
    map2[1].push_back(1.2f);
    map2[2].push_back(2.5f);

    // Print contents of map1
    std::cout << "Contents of map1:" << std::endl;
    for (const auto& [key, vec] : map1) {
        std::cout << key << ": ";
        for (const auto& val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Print contents of map2
    std::cout << "\nContents of map2:" << std::endl;
    for (const auto& [key, vec] : map2) {
        std::cout << key << ": ";
        for (const auto& val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
/*
Contents of map1:
colors: red blue 
fruits: apple banana 

Contents of map2:
1: 1.1 1.2 
2: 2.5 
*/
/* ----------------- */

c. Partially Bound Templates
They allow for fixing some template parameters while leaving others open. 
This lets you create a specific "family" of types from a more generic one. 
template <typename T, int Lines, int Cols>
class Matrix { /* ... */ };

// Alias template for a "Square Matrix" of any type T
// Lines and Cols are bound to be equal
template <typename T, int Dim>
using SquareMatrix = Matrix<T, Dim, Dim>; //

// Alias template for a "Vector" (1 column) of any type T
template <typename T, int Dim>
using Vector = Matrix<T, Dim, 1>; //

int main() {
    Matrix<int, 5, 3> ma;
    SquareMatrix<double, 4> sq; // A 4x4 matrix of doubles
    Vector<char, 5> vec;        // A 5x1 matrix (vector) of chars
}

/* --------------------- */
#include <iostream>
#include <array>

// Generic Matrix template
template <typename T, int Lines, int Cols>
class Matrix {
public:
    std::array<std::array<T, Cols>, Lines> data;

    // Constructor to initialize all elements to a default value
    Matrix(T initValue = T()) {
        for (int i = 0; i < Lines; ++i)
            for (int j = 0; j < Cols; ++j)
                data[i][j] = initValue;
    }

    // Function to print matrix dimensions
    void printDimensions() const {
        std::cout << "Matrix dimensions: " << Lines << "x" << Cols << std::endl;
    }
};

// Alias template for a Square Matrix (Lines == Cols)
template <typename T, int Dim>
using SquareMatrix = Matrix<T, Dim, Dim>;

// Alias template for a Vector (Cols == 1)
template <typename T, int Dim>
using Vector = Matrix<T, Dim, 1>;

int main() {
    Matrix<int, 5, 3> ma;       // 5x3 matrix of ints
    SquareMatrix<double, 4> sq; // 4x4 matrix of doubles
    Vector<char, 5> vec;        // 5x1 matrix (vector) of chars

    // Print dimensions
    ma.printDimensions();  // Output: 5x3
    sq.printDimensions();  // Output: 4x4
    vec.printDimensions(); // Output: 5x1

    return 0;
}
/*
Matrix dimensions: 5x3
Matrix dimensions: 4x4
Matrix dimensions: 5x1
*/
/* --------------------- */





4. Accessing Nested Types (Modern Type Traits)
Alias templates are fundamental to modern C++ type traits.
They are used to create the convenient _t aliases (e.g., std::vector<T>::value_type becomes std::vector<T>::value_type_t). 

#include <iostream>
#include <type_traits>

// Before alias templates, accessing a nested type was complex within templates:
template <typename T>
void print_value_type_old() {
    typename T::value_type value;
    // ...
}
// In C++11, std::is_same_v uses alias templates internally.
// A simpler example:
template <typename T>
using remove_const_t = typename std::remove_const<T>::type; //

int main() {
    // remove_const_t<const int> is an alias for 'int'
    remove_const_t<const int> myInt = 10;
    std::cout << std::is_same_v<int, decltype(myInt)> << std::endl; // Output: 1 (true)
}

//3. Default Template Arguments for Function Templates
a. Basic Default Argument
If the user does not specify <int> or <double>, the compiler automatically assumes the default type provided 
(int in this case).

#include <iostream>
#include <string>
#include <typeinfo>

// Default template argument T is int
template <typename T = int>
void display(T value = T()) {  // Default value allows calling display() with no arguments
    std::cout << "Value: " << value  << ", Type: " << typeid(T).name() << std::endl;
}

int main() {
    // 1. Explicitly specify type
    display<double>(12.34); // T is double

    // 2. Rely on argument deduction
    display("hello");       // T is const char* (deduced)

    // 3. Use the default template argument
    display();              // T is int (default), value is 0

    return 0;
}
/*
Value: 12.34, Type: d
Value: hello, Type: PKc
Value: 0, Type: i
*/


b. Defaulting when Deduction Fails 
One of the primary uses of this feature is to provide a fallback type when template argument deduction is not possible 
(e.g., when there are no function arguments, as in the display() call above), or when you want to override standard 
deduction rules with a specific default behavior. 

#include <iostream>

template <typename ReturnType = int, typename ArgType = ReturnType>
ReturnType add(ArgType a, ArgType b) {
    return static_cast<ReturnType>(a + b);
}

int main() {
    // Explicitly specify ReturnType as double, ArgType defaults to double
    std::cout << "Result 1: " << add<double>(10.5, 20.3) << std::endl;

    // Use defaults: ReturnType is int, ArgType is int (deduced)
    // Deduction for ArgType happens first based on arguments (10, 20),
    // but this example shows chaining defaults: ArgType defaults to whatever ReturnType is.
    std::cout << "Result 2: " << add(10, 20) << std::endl;

    // Explicitly set ReturnType to float. ArgType uses its default (float).
    std::cout << "Result 3: " << add<float>(1.5f, 2.5f) << std::endl;
}
/*
Result 1: 30.8
Result 2: 30
Result 3: 4

Note: 
Important Rule: Argument Deduction Still Preferred
If the compiler can successfully deduce the template argument from the function call arguments, 
it will use the deduced type even if a default template argument is provided. 
The default is only used when deduction is impossible or when the template argument list is explicitly used (e.g., myFunc<>('a')).
*/






//4. Explicit Template Instantiation and extern Templates


Explicit Template Instantiation
->By default, C++ uses the "inclusion model" for templates. 
->The compiler generates an entire function or class definition every time it encounters a use of that template in a new translation unit (a .cpp file). 
->This leads to code bloat and slow compilation times in large projects.
->Explicit instantiation allows you to manually instruct the compiler to generate the concrete implementation of a template only once, in a single specific source file.

How it works:
You place the explicit instantiation definition in one source file (.cpp) using the template keyword without any parameters.


File: storage.h (Header file)
// storage.h
template <typename T>
void processValue(T value) {
    // Complex implementation defined here
    std::cout << "Processing: " << value << std::endl;
}

// Declaration of explicit instantiation (optional, but good practice)
// This tells other files NOT to generate this code.
extern template void processValue<int>(int);


File: storage.cpp (Implementation file)
// storage.cpp
#include "storage.h"
#include <iostream>

// Explicit instantiation definition:
// Generate the actual machine code for processValue<int> ONLY here.
template void processValue<int>(int);

// We might generate other types here too if needed:
// template void processValue<double>(double);



File: main.cpp (Usage file)
// main.cpp
#include "storage.h"

int main() {
    // This call uses the function generated in storage.cpp.
    // The compiler in this file does not generate new machine code.
    processValue<int>(100);

    // This is fine, but if we don't have an explicit instantiation for char,
    // this file will generate its own version for char.
    processValue<char>('A');
}


/*
Note:
Extern Templates (C++11)
C++11 standardized and improved the use of the extern keyword specifically for templates. This is a crucial feature used in conjunction with explicit instantiation.
The extern template declaration tells the compiler: "Do not generate the machine code for this specific template instantiation in the current translation unit; I promise it will be defined elsewhere (via an explicit instantiation definition)."
How extern templates fix the problem:
When you use the inclusion model, every .cpp file has a copy of the template code. The linker is responsible for merging these identical copies. This is wasteful.
The extern template declaration prevents the compiler from emitting the duplicate code entirely, significantly speeding up compilation and reducing object file sizes.
In the example above, the line extern template void processValue<int>(int); in storage.h serves this exact purpose. When main.cpp includes storage.h, the compiler sees the extern declaration and avoids generating redundant code, relying solely on the version generated in storage.cpp.
*/






//5. Generalized Constant Expressions (constexpr) in Templates

Generalized Constant Expressions, introduced with the constexpr keyword in C++11, 
allow functions to be evaluated at compile time if they are called with compile-time constant arguments. 

When constexpr is used within templates, it allows the behavior of the template to be determined and 
optimized during compilation, leading to more efficient code and enabling operations within contexts that 
require compile-time constants (like array sizes or template arguments). 


The Role of constexpr in C++11
The primary purpose of constexpr is to move computation from runtime to compile time. In C++11, 
a function marked constexpr must be very simple (essentially a single return statement, 
with limitations on loops and if statements that were relaxed in C++14). 
c

onstexpr in Function Templates 
When applied to a function template, constexpr indicates that any instantiation of that template is a 
constant expression function, provided the arguments allow it. 
This allows the compiler to calculate values used within template logic during the compilation phase: 



#include <iostream>

// A constexpr function template to calculate the power of a number
template <typename T>
constexpr T power(T base, int exp) {
    // In C++11, this requires recursion because loops aren't allowed in constexpr functions
    return (exp == 0) ? 1 : base * power(base, exp - 1);
}

int main() {
    // 1. Runtime usage (like a normal function call)
    int exp_val = 3;
    std::cout << "Runtime: " << power(2.0, exp_val) << std::endl;

    // 2. Compile-time usage (the result is a constant expression)
    // The compiler calculates 2^5 = 32 at compile time
    constexpr int compile_time_result = power(2, 5);

    // Using the result in a context requiring a compile-time constant:
    int myArray[compile_time_result]; // Array size must be a constant expression
    std::cout << "Array size: " << sizeof(myArray) / sizeof(int) << std::endl;
}



constexpr in Class Templates (Constructors and Member Functions) 
You can mark constructors and member functions of class templates as constexpr, 
allowing instantiation of template objects to be done at compile time. 

#include <iostream>
template <typename T>
class Point {
public:
    T x, y;

    // Constexpr constructor (C++11: must have an empty body)
    constexpr Point(T x_val, T y_val) : x(x_val), y(y_val) {}

    // Constexpr member function
    constexpr T get_x() const {
        return x;
    }
};

int main() {
    // Create a Point instance at compile time
    constexpr Point<int> p(10, 20);

    // We can use the constexpr member function in a constant context
    constexpr int x_coord = p.get_x();

    // Use the compile-time result for array size
    int data[x_coord];
    std::cout << "Data array size: " << sizeof(data) / sizeof(int) << std::endl;
}

/* 
Note:
Summary of constexpr in Templates in C++11
Compile-time efficiency: Moves computations into the compilation phase, making the final executable faster.

Enables constant contexts: Allows results from template functions to be used where only compile-time constants are permitted (like defining array dimensions).

Strict C++11 rules: In C++11, constexpr functions had tight restrictions (single return statement, no loops or local if statements), often requiring recursion to achieve iterative tasks. These rules were significantly relaxed in C++14
*/


//6. Support for Local and Unnamed Types as Template Arguments

C++11 significantly improved template capabilities by expanding the types that could be used as template arguments. 
Specifically, it introduced support for using local types and unnamed types with templates, 
which were previously disallowed by the C++ standard. 

a. Local Types as Template Arguments
A local type is a class or struct defined inside a function or a block scope. 

Before C++11:
The following code was illegal:

template <typename T>
void someFunction(T arg) { /* ... */ }

void test_old() {
    struct LocalStruct { int x; };
    LocalStruct ls;
    // Error: Cannot use a local type as a template argument
    // someFunction(ls);
}


In C++11 and later:
This restriction was lifted. The compiler can now successfully deduce or accept local types as template arguments.

#include <iostream>
template <typename T>
void process(T arg) {
    std::cout << "Processing a local type." << std::endl;
}

void test_cxx11() {
    // Define a struct within a function scope (local type)
    struct LocalData {
        int id;
        float value;
    };

    LocalData ld = {1, 2.5f};

    // This is now perfectly valid C++11 code:
    process(ld);
    process<LocalData>(ld); // Explicit use also works
}

int main() {
    test_cxx11();
    return 0;
}




b. Unnamed Types as Template Arguments 
An unnamed type is a type that does not have an explicit identifier (name). 
The most common unnamed types are anonymous unions and classes/structs defined directly within 
a typedef declaration without an intermediate tag. 

Before C++11:
The standard did not guarantee support for these types in template contexts. 


In C++11 and later:
Support for these types was added. This mostly affects C-style codebases using specific typedef patterns, 
as modern C++ style generally avoids unnamed types except for anonymous unions. 


#include <iostream>
template <typename T>
void handleType(T value) {
    std::cout << "Handling an unnamed type." << std::endl;
}

int main() {
    // An unnamed struct used within a typedef (a common C pattern)
    typedef struct {
        int data;
        char flag;
    } UnnamedStructType; // The type itself has no tag name, only the typedef alias

    UnnamedStructType my_var = {10, 'Y'};

    // This is now valid C++11 code:
    handleType(my_var);
    handleType<UnnamedStructType>(my_var);
    
    return 0;
}

/*
Note:
Summary of the C++11 change:
The relaxation of rules for local and unnamed types streamlined the use of templates, 
making generic programming more flexible and allowing template functions to seamlessly 
integrate with types defined anywhere in the codebase, regardless of scope or naming convention. 

The primary intent was to allow template argument deduction (auto equivalent for templates) 
to work without encountering "hard errors" just because a type was defined locally.
*/














SFINAE (C++11)
C++11 standardized and simplified SFINAE usage through the <type_traits> header, 
which provided a vast library of templates for inspecting type properties at compile time
(e.g., std::is_integral, std::enable_if, std::void_t). 

This made SFINAE much more accessible and less error-prone.
Example using std::enable_if from <type_traits>:

#include <type_traits>

// Enable this template function only for arithmetic types
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
add_five(T value) {
    return value + 5;
}

// Usage:
int a = add_five(10);     // Valid
// int b = add_five("hello"); // Fails to compile due to SFINAE

The std::enable_if technique removes the add_five function from the overload set when T is not an arithmetic type.



Example 1: Function overloading with SFINAE
We can conditionally enable a function for certain types using std::enable_if. 
Here's a simple example that adds two numbers, but only if the types are integral types (like int, long, etc.).

#include <iostream>
#include <type_traits>

// Enable only for integral types (int, char, etc.)
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

// Enable only for floating-point types (float, double)
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2) << std::endl;          // Calls the integral version
    std::cout << add(1.5, 2.5) << std::endl;      // Calls the floating-point version
    // std::cout << add("string", "test");       // Compile error because strings are not handled
}
/*
3
4
*/



Metaprogramming (C++11)
C++11 formalized many metaprogramming techniques and improved their syntax and usability. 

Key features included:
constexpr: Allowed functions and variables to be evaluated at compile time, providing a more readable 
and efficient alternative to complex template recursion for simple calculations.

<type_traits> library: Standardized tools for type manipulation and introspection, 
which are the backbone of modern C++ metaprogramming.


Example: Compile-time calculation using constexpr:
constexpr int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}

// Usage:
int arr[factorial(5)]; // Array size is calculated at compile time (120)


#include <iostream>
using namespace std;
// C++11 introduced 'constexpr' functions which can be evaluated at compile time
constexpr int factorial(int n) {
    // The conditional operator (ternary) is used to perform recursion within a single expression
    return (n == 0) ? 1 : n * factorial(n - 1);
}

int main() {
    // Usage 1: Compile-time array size declaration (requires a constant expression)
    // The value of factorial(5) is computed by the compiler as 120.
    int arr[factorial(5)]; 
    
    cout << "Factorial of 5 calculated at compile time: " << sizeof(arr) / sizeof(arr[0]) << " elements long." << endl;

    // Usage 2: Storing the result in a constexpr variable
    constexpr int fact_10 = factorial(10);
    cout << "Factorial of 10 calculated at compile time: " << fact_10 << endl;

    // Usage 3: Calling the constexpr function at runtime (behaves like a normal function)
    int runtime_val = 5;
    cout << "Factorial of 5 calculated at runtime: " << factorial(runtime_val) << endl;

    return 0;
}