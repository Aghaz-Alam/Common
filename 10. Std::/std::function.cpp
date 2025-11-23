//std::function
std::function in C++ (C++11, C++14, C++17)
std::function is a general-purpose polymorphic function wrapper introduced in C++11 that can store any callable object 
(like function pointers, lambdas, bind expressions, or other function objects). 

It provides a convenient way to store, pass, and invoke functions, making it very useful for cases where you need to pass around function callbacks, 
delegate functionality, or store functions in containers.





1. std::function in C++11
std::function was introduced in C++11, and in this version, it is primarily used to wrap function pointers, 
functors (function objects), or lambda expressions.

//Basic Usage
#include <iostream>
#include <functional>  // For std::function
using namespace std;
// A simple function
int add(int a, int b) {
    return a + b;
}
int main() {
    // Create a std::function object to hold a function pointer
    std::function<int(int, int)> func = add;

    // Call the function through std::function
    std::cout << "Result: " << func(5, 3) << std::endl;  // Output: Result: 8

  return 0;
}

Explanation:
std::function<int(int, int)> can store any function or callable object that takes two int arguments and returns an int.
In this case, it stores the function pointer add and allows it to be called through the std::function object func.





2. std::function in C++14
In C++14, std::function remains the same as in C++11. However, with C++14, there are improvements to lambda expressions 
(such as generalized lambda captures) and other language features, which can enhance how you use std::function.

Example: Using Lambda Expressions
#include <iostream>
#include <functional>  // For std::function
int main() {
    // A lambda function
    auto multiply = [](int a, int b) { return a * b; };

    // Using std::function to store the lambda
    std::function<int(int, int)> func = multiply;

    // Call the lambda function through std::function
    std::cout << "Multiplication Result: " << func(4, 5) << std::endl;  // Output: Multiplication Result: 20

  return 0;
}

Explanation:
In C++14, lambda expressions are more powerful, and std::function can store them just as it can store normal function pointers.
The lambda multiply is passed to std::function, which can then be invoked using func().






3. std::function in C++17
In C++17, the usage of std::function remains mostly the same as in C++11 and C++14, but C++17 introduced new features that complement std::function:
Inline variable definitions: Allows for cleaner initialization of std::function objects.
Improved lambdas: Lambdas with template parameters (generic lambdas) were introduced in C++17, which can further be stored in std::function.

Example: Storing Generic Lambdas in std::function (C++17)
#include <iostream>
#include <functional>  // For std::function
using namespace std;
int main() {
    // A generic lambda (C++17 feature)
    auto add = [](auto a, auto b) { return a + b; };

    // Storing the lambda in std::function
    std::function<int(int, int)> func = add;

    // Call the lambda through std::function
    std::cout << "Add result: " << func(2, 3) << std::endl;  // Output: Add result: 5

    // Now, using a different type
    std::function<double(double, double)> func_double = add;
    std::cout << "Add result (double): " << func_double(2.5, 3.5) << std::endl;  // Output: Add result (double): 6

  return 0;
}

Explanation:
C++17 allows us to create generic lambdas, which can take parameters of any type (auto keyword).
This lambda can be stored in a std::function of a specific signature (e.g., std::function<int(int, int)>), even though it is 
a generic lambda that can work with different types of arguments.

This makes std::function even more powerful, as it can store lambdas that are more flexible and capable of handling multiple argument types.







4. Additional std::function Use Cases
Function Wrapping: You can use std::function to wrap functions, lambdas, or functors and pass them around in the code.
Callbacks: std::function is commonly used in callback-based systems, where you pass a function (or lambda) to another function for deferred execution.
Event Handling: It is useful for handling events in GUI applications or any context where a function might need to be triggered later based on some condition.

Advanced Example: Using std::function with Callbacks
#include <iostream>
#include <functional>  // For std::function
using namespace std;
// A function that takes a callback
void perform_action(std::function<void()> action) {
    // Perform the action (callback)
    action();
}
int main() {
    // Define a simple callback (lambda)
    auto callback = []() { std::cout << "Callback function executed!" << std::endl; };

    // Pass the callback to a function
    perform_action(callback);

    return 0;
}

Explanation:
std::function<void()> is used to store a callable that takes no parameters and returns void.
The function perform_action takes a callback and invokes it within the function body.
This allows you to pass functions, lambdas, or other callable types to functions as arguments, providing flexibility in how you handle actions or events.





Key Points About std::function
Type-Erased Function Object: std::function is type-erased, meaning it can hold any callable object 
(function pointer, lambda, functor, etc.) as long as the signature matches.

Signature: When using std::function, you define the signature of the function (e.g., std::function<int(int, int)>), 
which enforces the type consistency for the callable object.

Copyable and Callable: std::function objects are copyable, and once you assign a callable to it, you can invoke it like a normal function.

Performance Considerations: Since std::function uses type erasure, there may be a slight overhead in terms of performance compared to 
using regular function pointers or direct lambda calls. However, this trade-off is often acceptable due to the flexibility it provides.

Null State: A std::function object can be in a "null" state, which means it doesn’t hold any callable object. You can check this 
state by comparing the object to nullptr.

std::function<void()> func;
if (!func) {
    std::cout << "No function assigned!" << std::endl;
}



Summary of std::function Usage Across C++ Versions
C++11: Introduced std::function as a way to store and invoke callable objects. 
It allows for flexible use of function pointers, lambdas, and functors.

C++14: No major changes to std::function, but improvements in lambda expressions (e.g., generalized lambda captures) 
make it easier to work with callable objects in more complex scenarios.

C++17: std::function continues to be useful, with the addition of generic lambdas and improved lambda syntax making it even more versatile. 
Lambdas with auto parameters can be stored in std::function with greater ease.