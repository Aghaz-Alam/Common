LamdaFunctions

3. Lambda Features in C++11

C++11 introduced lambdas, which changed the game. 
Now you could write inline anonymous functions with a capture list.

Lambda Syntax:
[ captures ] ( parameters ) -> return_type { body }

Example:
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    int sum = 0;

    for_each(v.begin(), v.end(), [&](int x) { sum += x; });
    cout << "Sum: " << sum << endl;

   return 0;
}
//Output: Sum: 15
✅ Key Features of C++11 Lambdas:
Capture List: Capture variables from enclosing scope.
Parameters: Lambda parameters work like function parameters.
Return Type: Optional, can use -> type syntax.
Inline: Defines functions locally without naming them.

Capture List in C++11
Capture by Value [=]: Copies variables from outer scope.
Capture by Reference [&]: Captures references, allows modification.
Specific Capture [x, &y]: Capture x by value, y by reference.
Capture this [this]: Access members inside class.

Examples:
Capture by Value
int x = 10;
auto f = [x]() { return x + 5; }; // x copied
//*--------------------------------
#include <iostream>
int main() {
    int x = 10;
    // Capture 'x' by value (a copy is made)
    auto f = [x]() {
        return x + 5;
    };
    std::cout << "Result of lambda f(): " << f() << std::endl;
    // Modify original x after defining the lambda
    x = 20;
    std::cout << "Original x after change: " << x << std::endl;
    std::cout << "Lambda still uses captured x (copied value): " << f() << std::endl;
  return 0;
}

Output: 
Result of lambda f(): 15
Original x after change: 20
Lambda still uses captured x (copied value): 15

--------------------------------------//*/
/*--------------------------------------
Capture by Reference
int x = 10;
auto f = [&x]() { x += 5; }; // x modified
f();
std::cout << x; // 15
--------------------------------------*/
✅ Example: Capture by Reference in C++11 and Later
#include <iostream>
int main() {
    int x = 10;

    // Capture 'x' by reference (no copy, refers to original variable)
    auto f = [&x]() { 
        x += 5;   // modifies the original x
    };

    // Call the lambda
    f();

    std::cout << "Value of x after calling f(): " << x << std::endl;

    // Modify x again directly
    x += 10;
    std::cout << "Value of x after further modification: " << x << std::endl;

    // Call lambda again (works on same x)
    f();
    std::cout << "Value of x after calling f() again: " << x << std::endl;

    return 0;
}

Explanation:
[&x] means capture x by reference.
The lambda refers to the same memory as x in the outer scope.
Any modification inside the lambda affects the original variable.

Expected Output:
Value of x after calling f(): 15
Value of x after further modification: 25
Value of x after calling f() again: 30
/*--------------------------------------
--------------------------------------*/

Capture Defaults
int a = 1, b = 2;
auto f = [=, &b]() { b += a; }; // b by ref, a by value
//*--------------------------------------
✅ Example: Capture Defaults in C++11 and Later
#include <iostream>
using namespace std;
int main() {
    int a = 1, b = 2;

    // [=, &b] means:
    // - Default capture by value (a is copied)
    // - b is explicitly captured by reference
    auto f = [=, &b]() { 
        b += a;   // a is a copy, b is modified directly
    };

    f(); // Call the lambda

    cout << "After first call: a = " << a << ", b = " << b << endl;

    // Change a (will not affect lambda’s captured copy)
    a = 10;
    f(); // Call again

    cout << "After second call: a = " << a << ", b = " << b << endl;

   return 0;
}

Explanation:
[=, &b] means:
Default: capture all variables by value.
Exception: capture b by reference.

So:
a → copied when the lambda is created.
b → reference to the real variable.
Modifying b inside the lambda changes the original variable.
Changing a later has no effect because the lambda has a copy of the old a.

Expected Output:
After first call: a = 1, b = 3
After second call: a = 10, b = 4
--------------------------------------*/

Function Local & Global Lambdas
Local lambdas: Inside a function.
Global lambdas: Can be assigned to std::function for global use.
std::function<int(int)> square = [](int x){ return x*x; };
Immediately Invoked Function Expressions (IIFE)
Useful for scoping temporary calculations.
/*----------------------------------------
✅ Complete Program: Function Local & Global Lambdas + IIFE
#include <iostream>
#include <functional>
// ✅ Global lambda assigned to std::function
std::function<int(int)> square = [](int x) { 
    return x * x; 
};
int main() {
    // Local lambda (defined inside a function)
    auto add = [](int a, int b) {
        return a + b;
    };

    int a = 5, b = 10;

    std::cout << "Local lambda add(a, b): " << add(a, b) << std::endl;
    std::cout << "Global lambda square(a): " << square(a) << std::endl;

    // Immediately Invoked Function Expression (IIFE)
    // Executes immediately when defined
    int result = [](int x, int y) {
        std::cout << "Inside IIFE: x + y = " << x + y << std::endl;
        return x * y;  // Return a value immediately
    }(3, 4); // <— Note the parentheses invoking it

    std::cout << "Result returned from IIFE: " << result << std::endl;

    // Another IIFE example for quick computation
    int temp = []() {
        int p = 2, q = 3;
        return p + q;
    }();
    std::cout << "Sum from IIFE without parameters: " << temp << std::endl;

  return 0;
}

Explanation:
Global Lambda:
std::function<int(int)> square = [](int x){ return x*x; };

Defined outside any function → globally accessible.
Stored in std::function so it can be reassigned later if needed.

Local Lambda:
auto add = [](int a, int b){ return a + b; };

Defined inside main() — visible only within that function.
IIFE (Immediately Invoked Function Expression):
int result = [](int x, int y){ return x * y; }(3, 4);

Declared and invoked immediately by appending (3, 4).
Useful for one-off computations or scoping temporary variables.

Expected Output:
Local lambda add(a, b): 15
Global lambda square(a): 25
Inside IIFE: x + y = 7
Result returned from IIFE: 12
Sum from IIFE without parameters: 5
----------------------------------------*/

C++11 Example:
int result = [](){ return 42; }();

Parentheses () immediately invoke the lambda.
Lambda Conversion
Lambdas can convert to function pointers if no capture:

auto f = [](int x){ return x+1; };
int (*fp)(int) = f;
/*------------------------------------- 
✅ Complete Program: IIFE + Lambda Conversion in C++11
#include <iostream>
int main() {
    // Immediately Invoked Function Expression (IIFE)
    int result = []() { 
        return 42; 
    }();  // The () at the end invokes the lambda immediately

    std::cout << "Result from IIFE: " << result << std::endl;

    // Lambda that can convert to a function pointer (no capture)
    auto f = [](int x) { 
        return x + 1; 
    };

    // ✅ Convert lambda to a plain function pointer
    int (*fp)(int) = f;

    // Call both
    std::cout << "f(5): " << f(5) << std::endl;
    std::cout << "fp(5): " << fp(5) << std::endl;

  return 0;
}

Explanation:
Immediately Invoked Function Expression (IIFE)

Defined and executed immediately:
int result = [](){ return 42; }();


Commonly used for quick calculations or scoping temporary logic.
Lambda Conversion to Function Pointer
Works only if the lambda has no captures.

Compiler generates a hidden function internally and allows implicit conversion:
int (*fp)(int) = f;

Both f and fp behave identically.

Expected Output:
Result from IIFE: 42
f(5): 6
fp(5): 6
*--------------------------------------*/