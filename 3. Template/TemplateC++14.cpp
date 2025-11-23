Templates
- Normal template usage
- template specialization
- SFINAE
- metaprogramming



A. Template Variables (Since C++ 14)
A template variable is a variable that can work with any type specified when the variable is used, 
similar to how we use templates for functions or classes.

C++14 introduced variable templates, allowing a variable declaration to be templated. 
The compiler instantiates a unique variable for each type used.


In C++, a template variable is a variable that is defined using template syntax to allow the type of the variable to be specified at compile time. 
This enables the variable to work with any type, and the type is determined when the template is instantiated.

C++ templates are typically used for functions or classes, but since C++14, it has become possible to create template variables as well. 
A template variable allows you to define a variable that is dependent on a template type.

Syntax of Template Variables:
A template variable is defined with the template keyword, similar to a template function or template class. 
The general form of a template variable is:

template <typename T>
T variable = T();  // A template variable initialized with default value of type T


This declares a template variable variable of type T, and it is initialized with the default constructor of type T. 
The type T will be deduced when the template is instantiated.



/ A template variable 'threshold' that can be accessed for any type T
template <typename T>
constexpr T threshold = 0.5;

int main() {
    double d = threshold<double>; // threshold<double> instance = 0.5
    float f = threshold<float>;   // threshold<float> instance = 0.5f

    // We can also specialize it:
    template <>
    constexpr int threshold<int> = 10;
    int i = threshold<int>; // i becomes 10
}



#include <iostream>
using namespace std;
template <typename T>
T pi = T(3.14159);  // template variable with a default value (of type T)

int main() {
    // Using the template variable with float type
    std::cout << "Pi as float: " << pi<float> << std::endl;

    // Using the template variable with double type
    std::cout << "Pi as double: " << pi<double> << std::endl;

    // Using the template variable with int type (rounded to nearest integer)
    std::cout << "Pi as int: " << pi<int> << std::endl;

    return 0;
}


C++14 introduced the concept of template variables, allowing the definition of variables 
that are templated over one or more types or non-type parameters. 

The compiler generates a unique instance of the variable for each different type or value used to instantiate it.
This is especially useful for creating type-specific constants or configuration values.

Example: A template variable for Pi
#include <iostream>
#include <iomanip>

// A template variable 'pi' that yields a different value/type depending on T
template <typename T>
constexpr T pi = T{3.1415926535897932385};

int main() {
    // Instantiates pi<double>
    double pi_d = pi<double>;
    
    // Instantiates pi<float>
    float pi_f = pi<float>;

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "Pi as double: " << pi_d << std::endl;
    std::cout << "Pi as float:  " << pi_f << std::endl;
    
  return 0;
}


B. Default Arguments for Function Templates //Default Template Arguments
Like normal parameters, we can also specify default type arguments to templates. 

Default template arguments allow specifying a default type for a template parameter 
if the user does not explicitly provide one. 

This makes template usage more concise when a common default type exists.
This feature applies to class, function (since C++11 for functions, 
though type deduction often made it unnecessary), and variable templates.

Example: Class Template with a default type argument

#include <iostream>
#include <vector>
#include <string>

// The second template parameter 'Allocator' defaults to std::allocator<T>
template <typename T, typename Allocator = std::allocator<T>>
class MyContainer {
public:
    void display_type() {
        std::cout << "Container holds type: " 
                  << typeid(T).name() 
                  << std::endl;
        // The allocator type is inferred as the default unless specified
    }
};

int main() {
    // Usage 1: Uses the default std::allocator<int>
    MyContainer<int> c1; 
    c1.display_type();

    // Usage 2: Explicitly specifying the type works too
    // Note: For std::vector this looks slightly different, but the concept is the same.
    
    // Example of a default template argument in the standard library: std::vector
    // std::vector<T, Allocator = std::allocator<T>>
    std::vector<int> v1; // Uses default allocator

    return 0;
}


//Default Arguments for Function Templates
While C++11 allowed type deduction to handle most cases, 
C++14 explicitly allowed default type arguments for function templates, mirroring the syntax of class templates.

/ If T is not specified when calling the function, it defaults to double
template <typename T = double>
T get_default_value() {
    return T{};
}

int main() {
    double d = get_default_value();       // Uses T = double
    int i = get_default_value<int>();     // Uses T = int
}



C. Generic Lambdas
C++11 introduced lambdas, but their parameter types had to be explicitly defined. 
C++14 allowed the use of the auto keyword in the lambda parameter list, 
effectively making the lambda a function template. 

This feature blurred the line between templates and runtime constructs. 
C++14 allowed using auto as a type specifier for lambda parameters, essentially creating a function template 
behind the scenes.

Example: Generic Lambdas
// C++11: need explicit types
auto sum_c11 = [](int x, int y) { return x + y; };

// C++14: generic parameters using auto
auto sum_c14 = [](auto x, auto y) { return x + y; };

// The C++14 lambda works for any types that support the '+' operator:
std::cout << sum_c14(1, 2) << std::endl;         // T is int, U is int
std::cout << sum_c14(1.5, 2.5) << std::endl;     // T is double, U is double
std::cout << sum_c14(std::string("a"), "b") << std::endl; // Works with string types




//Example: Generic Lambdas
// This lambda is effectively a template function 'operator()(auto x, auto y)'
auto add = [](auto x, auto y) {
    return x + y;
};

int main() {
    std::cout << add(1, 2) << std::endl;         // T/U are int
    std::cout << add(1.5, 2.5) << std::endl;     // T/U are double
}





2. Template Specialization C++14
C++14 did not fundamentally change how specialization works, but the introduction of template variables 
extended where specialization could be applied (as shown in the threshold<int> example above). 

The core mechanics of explicit and partial specialization remained the same as C++11.





3. SFINAE C++14
C++14 leveraged the robust <type_traits> library introduced in C++11 but made SFINAE usage cleaner by 
introducing variable templates for traits.
Instead of writing std::is_integral<T>::value everywhere, C++14 added the _v aliases:


#include <type_traits>
#include <iostream>

// C++11 style SFINAE using enable_if
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_if_integral(T val) {
    std::cout << val << " is an integral." << std::endl;
}

// C++14 introduced aliases to simplify accessing the ::value member:
// std::is_integral_v<T> is the C++14 way of writing std::is_integral<T>::value

template <typename T>
typename std::enable_if_t<std::is_floating_point_v<T>, void>
print_if_floating(T val) {
    std::cout << val << " is a float point number." << std::endl;
}

int main() {
    print_if_integral(10);
    print_if_floating(1.5);
    // print_if_integral(1.5); // Fails compilation as expected via SFINAE
}



4. Metaprogramming C++14
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

C++11 Style (Template Recursion or single expression constexpr):
// Classic C++11 template metaprogramming for Factorial
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};
template <>
struct Factorial<0> {
    static const int value = 1;
};


C++14 Style (Relaxed constexpr function):
// C++14 style: much more readable, behaves like a normal function but runs at compile time
constexpr long long factorial(int n) {
    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

int main() {
    // Both C++11 and C++14 methods result in compile-time constants
    constexpr long long f5_tmpl = Factorial<5>::value; // C++11 style
    constexpr long long f5_cxpr = factorial(5);       // C++14 style
}


//Relaxed constexpr Restrictions
While not exclusively a template feature, the relaxation of constexpr functions had 
a major impact on template metaprogramming. 

C++14 constexpr functions could contain multiple statements, local variables, if-switch statements, 
and loops (like for, range-based for, while), making compile-time computations much easier 
to write and read than the complex template recursion required in C++11. 

This made it simpler to use constexpr functions in contexts where template-based metaprogramming 
was previously necessary.





B. Generalized Lambda Captures (Init Captures)
While generic, this feature (also called "init capture") allows the closure object created by a lambda 
to hold members initialized with arbitrary expressions. 

This is used in advanced scenarios to store complex state within generic, templated algorithms.

//Generalized Lambda Captures (Init Capture)
C++14 enabled initialization of captured variables with arbitrary expressions in the lambda's capture clause. 
This allows for capturing by move (using std::move) and defining new members in the lambda's closure type 
that do not correspond to existing local variables. 

Example:
#include <memory>
#include <iostream>

std::unique_ptr<int> create_ptr(int value) {
    return std::make_unique<int>(value);
}

int main() {
    // Capture a move-only type into the lambda using init capture
    auto lambda = [ptr = create_ptr(10)]() {
        std::cout << "Value in captured ptr: " << *ptr << std::endl;
    };

    lambda();
    // ptr is moved into the lambda's scope, so it's not usable outside (conceptually)
}



Binary Literals and Digit Separators (Minor)
C++14 introduced binary literals (e.g., 0b101) and digit separators (e.g., 1'000'000). 
These are minor language features but can be useful within non-type template parameters 
to improve readability of large integer values used in templates. 









std::integer_sequence (Library Feature)
The standard library added the std::integer_sequence class template and related aliases 
(std::index_sequence), a powerful tool for working with parameter packs in variadic templates. 

It is commonly used to unpack tuples or apply a function to a variable number of arguments by generating 
a sequence of compile-time indices. 

Example (Conceptual use in parameter pack unpacking):
#include <utility> // for std::integer_sequence, std::index_sequence

template<typename T, T... Ints>
void print_sequence(std::integer_sequence<T, Ints...>) {
    // Unpacks the compile-time sequence into a runtime print statement
    (std::cout << ... << Ints) << std::endl; 
}

int main() {
    // Creates a sequence 0, 1, 2, 3
    print_sequence(std::make_index_sequence<4>{}); 
}




All the provided code snippets are already valid in C++14. 
The examples focus on core template features introduced in C++98, C++11, or features that are backward compatible.

C++14 introduced minor relaxations to the constexpr rules and generic lambdas, 
but did not invalidate the existing template syntax used in your examples.

The code provided can be compiled as is, typically by using the flag -std=c++14 with your compiler 
(e.g., g++ yourfile.cpp -std=c++14).

Here is the exact code you provided, which works perfectly fine under the C++14 standard:


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
The following code works in C++11 and C++14. 
Note that the C++17 printFold example is commented out as it requires C++17 features.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//a. Function Template Recursion
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

//b. Class Template Specialization
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

//c. Using Initializer Lists
// Helper function to process each element in the initializer list
template<typename T>
void process(T t) {
    cout << t << endl;
}

// Variadic template function using an initializer list trick (works C++11/14)
template <typename... Args>
void printList(Args... args) {
    cout << "Printing using initializer list:" << endl;

    // Create a dummy array where each element initialization calls the 'process' helper function
    int dummy[] = {0, (process(args), 0)...};

    (void)dummy; // Suppress unused variable warning
}

// C++17 introduces "fold expressions", which are much cleaner for this purpose:
// template <typename... Args>
// void printFold(Args... args) {
//     cout << "Printing using C++17 fold expression:" << endl;
//     ((cout << args << endl), ...);
// }

int main() {
    cout << "--- Function Recursion ---" << endl;
    print(1, 2.5, "Hello", 'A'); 

    cout << "\n--- Class Template Specialization ---" << endl;
    Tuple<int, double, string, char> myTuple(10, 5.5, "Tuple Example", 'C');
    cout << "Printing Tuple elements:" << endl;
    myTuple.print();

    cout << "\n--- Using Initializer Lists ---" << endl;
    printList(1, 2.5, "Hello", 'A');
    // printFold(1, 2.5, "Hello", 'A'); // Requires C++17
    
    return 0;
}



