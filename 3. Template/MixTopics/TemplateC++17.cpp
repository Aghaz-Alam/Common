Templates C++17 in detailed 
- Normal template usage C++17 
- template specialization C++17 
- SFINAE C++17
- metaprogramming C++17

Another Use Case: SFINAE with Template Variables (C++17+)
While introduced in C++14, template variables became widely used with the C++17 adoption of variable templates for standard type traits, like std::is_integral_v<T> (which is equivalent to std::is_integral<T>::value).


C++17's primary improvement to everyday template usage was Class Template Argument Deduction (CTAD). 

Class Template Argument Deduction (CTAD)
Before C++17, you had to explicitly specify template arguments when constructing a class instance, 
even if the compiler could easily deduce them from the constructor arguments. 
C++17 fixed this, matching the behavior function templates have always had. 





//Before C++17
#include <iostream>
#include <vector>
#include <map>
#include <utility> // Required for std::pair and std::make_pair

int main() {
    // --- C++11/C++14 Valid Code ---

    // 1. Explicit Template Arguments (Mandatory for class construction):
    // We must write <int, double> here.
    std::pair<int, double> p1(1, 3.14);
    
    // We must write <int> here.
    std::vector<int> v1 = {1, 2, 3, 4};
    
    // We must write <std::string, int> here.
    std::map<std::string, int> m1;

    std::cout << "Explicit Declaration (C++11/14 Style):" << std::endl;
    std::cout << "p1 type: std::pair<int, double>, value: (" << p1.first << ", " << p1.second << ")" << std::endl;
    std::cout << "v1 size: " << v1.size() << std::endl;

    
    // 2. Using Helper Functions (The common workaround for C++11/14):
    // Helper functions can deduce their template arguments automatically.
    // std::make_pair() returns an std::pair object, allowing us to initialize p2.
    auto p2 = std::make_pair(1, 3.14); 
    // The compiler deduces p2 is of type std::pair<int, double> without explicit <int, double> usage here.

    std::cout << "\nUsing make_pair helper function (C++11/14 workaround):" << std::endl;
    std::cout << "p2 value: (" << p2.first << ", " << p2.second << ")" << std::endl;

    return 0;
}




//Complete Program Demonstrating CTAD
#include <iostream>
#include <vector>
#include <map>
#include <utility> // For std::pair

int main() {
    // --- Code that compiles in C++11/14/17 ---

    // Function templates have always allowed deduction:
    std::make_pair(1, 3.14); // Compiler deduces std::pair<int, double>
    
    // Class template instances required explicit arguments before C++17:
    std::pair<int, double> p1(1, 3.14);
    std::vector<int> v1 = {1, 2, 3, 4};
    std::map<std::string, int> m1;


    std::cout << "C++14 style explicit declaration:" << std::endl;
    std::cout << "p1 type: std::pair<int, double>" << std::endl;
    std::cout << "v1 type: std::vector<int>" << std::endl;

    std::cout << "\n--------------------------\n\n";


    // --- C++17 ONLY Code (Requires C++17 compiler flag) ---

    std::cout << "C++17 style with Class Template Argument Deduction (CTAD):" << std::endl;

    // The compiler automatically deduces the types from the constructor arguments
    std::pair p2(1, 3.14); 
    // ^^^ Compiler internally generates std::pair<int, double> p2(1, 3.14);

    std::vector v2 = {1, 2, 3, 4};
    // ^^^ Compiler internally generates std::vector<int> v2 = { ... };

    std::map m2 = {{"apple", 1}, {"banana", 2}};
    // ^^^ Compiler internally generates std::map<const char*, int> m2 = { ... };

    std::cout << "p2 value: (" << p2.first << ", " << p2.second << ")" << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;
    std::cout << "m2 size: " << m2.size() << std::endl;

    return 0;
}






//C++17
Example:
#include <vector>
#include <map>
int main() {
    // C++14 and earlier required explicit template arguments:
    std::pair<int, double> p1(1, 3.14);
    std::vector<int> v1 = {1, 2, 3};

    // C++17 allows deduction from constructor arguments:
    std::pair p2(1, 3.14); // Compiler deduces std::pair<int, double>
    std::map m1 = {{"key", "value"}}; // Compiler deduces std::map<const char*, const char*>

    // This makes standard library usage cleaner:
    std::vector v2 = {1, 2, 3}; // Compiler deduces std::vector<int>
}









Fold Expressions in C++ 17
Fold expressions in C++17 are a powerful feature that allows you to reduce or "fold" 
a parameter pack over a binary operator. 

They were introduced to simplify code that operates on variadic templates and make it more concise and readable.

Syntax
Fold expressions have the following syntax forms:

Types of Fold Expression
Fold expressions come in four types:

1. Unary Right Fold:
(pack op ...)

2. Unary Left Fold:
(... op pack)

3. Binary Right Fold:
(pack op ... op init)

4. Binary Left Fold:
(init op ... op pack)

In a binary fold expression, both operators op must be the same.

Examples:
1. Unary Left Fold Example
// C++ program to illustrate unary leftfold expression
#include <iostream>
using namespace std;
template <typename... Args> bool all(Args... args){
    return (... && args);
}

int main(){
    bool b = all(true, true, true, false);
    cout << "Result: " << boolalpha << b << endl;
    return 0;
}
/*
Output

Result: false
In this example, all function checks if all the arguments are true by performing a unary right fold 
with the logical AND operator &&.
*/



2. Binary Right Fold Example

#include <iostream>
template<typename... Args>
int sum(Args&&... args){
    return (args + ...); // Performs a binary right fold with addition
}

int main(){
    int result = sum(1, 2, 3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
/* 
Output

Result: 10
Here, the sum function calculates the sum of all its arguments using a binary left fold with the addition operator +. 
*/



3. Unary Left Fold with Empty Pack Example

#include <iostream>
template<typename... Args>
bool any(Args... args) {
    return (... || args);
}
int main() {
    bool b = any(false, false, false);
    std::cout << "Result: " << std::boolalpha << b << std::endl;
    return 0;
}
/* 
Output

Result: false
This example demonstrates a unary left fold with an empty pack. The result is false, as the logical OR operator || returns false for an empty pack.
*/



4. Binary Left Fold with Parentheses Example

#include <iostream>
using namespace std;

template <typename... Args>
int multiply_and_add(Args... args)
{
    return (1 * ... * args); // Error: operator with
                             // precedence below cast
}

int main()
{
    int result = multiply_and_add(1, 2, 3, 4);
    cout << "Result: " << result;
    return 0;
}
In this case, we encounter an error because the binary left-fold expression lacks parentheses around the operator *. To fix this, we need to add parentheses to ensure the correct operator precedence:


#include <iostream>

template<typename... Args>
int multiply_and_add(Args... args)
{
    return (1 * ... * (args)); // Corrected with parentheses
}

int main()
{
    int result = multiply_and_add(1, 2, 3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
/* 
Output

Result: 24
Ensure that you correctly parenthesize operators when necessary, especially in binary left-fold expressions.
 */


Example 1: Summing Numbers
This is the most common use case, drastically simplifying recursive sum functions.

#include <iostream>
#include <string>

// Unary left fold with the '+' operator
template <typename... Args>
auto sum(Args... args) {
    // Expands to: ( (arg1 + arg2) + ... + argN )
    return (args + ...);
}

int main() {
    // Works with integers:
    int total_int = sum(1, 2, 3, 4, 5); // 15
    std::cout << "Integer sum: " << total_int << std::endl;

    // Works with strings (concatenation):
    // Note: The types must be compatible with the '+' operator.
    std::string s1 = "Hello, ";
    std::string s2 = "World";
    std::string combined_string = sum(s1, s2, "!");
    std::cout << "String concatenation: " << combined_string << std::endl;
}





Example 2: Logical Operations (All/Any True)
Fold expressions are excellent for applying logical operators (&&, ||).
#include <iostream>

// Check if all arguments are true using the logical AND operator (&&)
template <typename... Args>
constexpr bool all_true(Args... args) {
    // Unary left fold: ( (arg1 && arg2) && ... )
    return (args && ...);
}

int main() {
    bool result1 = all_true(true, true, true);       // true
    bool result2 = all_true(true, false, true);      // false
    
    std::cout << "Result 1 (all true): " << std::boolalpha << result1 << std::endl;
    std::cout << "Result 2 (mixed): " << std::boolalpha << result2 << std::endl;
}




Example 3: Function Invocation and Printing
A particularly powerful use case involves the comma operator ( operator,). You can use a fold expression to execute a function or operation on every element in the pack in sequence.

#include <iostream>
#include <vector>

template <typename T>
void print(T t) {
    std::cout << t << std::endl;
}

// Unary right fold with the comma operator
template <typename... Args>
void print_all(Args... args) {
    // Expands to: ( print(arg1), print(arg2), ..., print(argN) )
    // The cast to 'void' prevents the compiler from complaining about the result 
    // of the comma operator not being used in the context of the fold.
    (print(args), ...); 
}

int main() {
    print_all("Hello", 123, 4.5, "World");
    
    // Example using binary fold with comma for structured insertion into a vector:
    std::vector<int> v;
    auto insert_to_vec = [&](int i){ v.push_back(i); };

    (insert_to_vec(1), insert_to_vec(2), insert_to_vec(3), ...); // This syntax is complex for simple vector pushes, 
                                                               // but shows how a generic operation can be folded.
}