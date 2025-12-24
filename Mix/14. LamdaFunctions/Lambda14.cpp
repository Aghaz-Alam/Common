4. Lambda Function in C++14

C++14 improved lambdas:
Generic Lambdas: auto parameters
Return type deduction automatic
/*--------------------------------------------
✅ Complete Program: C++14 Lambda Improvements
#include <iostream>
#include <string>
int main() {
    // 1️⃣ Generic Lambda — can take parameters of *any* type
    auto add = [](auto a, auto b) {
        return a + b;  // Works for int, double, string, etc.
    };

    std::cout << "add(3, 4) = " << add(3, 4) << std::endl;             // int + int
    std::cout << "add(2.5, 3.1) = " << add(2.5, 3.1) << std::endl;     // double + double
    std::cout << "add(std::string, std::string) = " 
              << add(std::string("Hello "), std::string("World")) 
              << std::endl;                                            // string + string

    // 2️⃣ Automatic Return Type Deduction
    // No need for explicit -> return_type
    auto divide = [](auto a, auto b) {
        // Return type is automatically deduced from the expression (double)
        return a / b;
    };

    std::cout << "divide(10, 2) = " << divide(10, 2) << std::endl;       // int / int
    std::cout << "divide(7.5, 2.5) = " << divide(7.5, 2.5) << std::endl; // double / double

    return 0;
}

Explanation:
✅ 1. Generic Lambdas
Introduced in C++14.
auto in parameter lists makes the lambda type-generic, like a template function.
The compiler deduces parameter types automatically.

✅ 2. Automatic Return Type Deduction
In C++11, if the return type wasn’t obvious, you had to write:
[](int a, int b) -> double { return (a + b) / 2.0; }
In C++14, the compiler deduces the return type automatically, even for complex expressions.

Expected Output:
add(3, 4) = 7
add(2.5, 3.1) = 5.6
add(std::string, std::string) = Hello World
divide(10, 2) = 5
divide(7.5, 2.5) = 3
--------------------------------------------*/
Example:
auto add = [](auto a, auto b) { return a + b; };
std::cout << add(3, 4) << std::endl;   // 7
std::cout << add(3.5, 2.1) << std::endl; // 5.6
/*--------------------------------------------
✅ Complete Program: Generic Lambda in C++14
#include <iostream>
int main() {
    // Generic lambda — can take parameters of any type
    auto add = [](auto a, auto b) {
        return a + b;
    };

    std::cout << "add(3, 4) = " << add(3, 4) << std::endl;       // int + int
    std::cout << "add(3.5, 2.1) = " << add(3.5, 2.1) << std::endl; // double + double
    std::cout << "add(10, 2.5) = " << add(10, 2.5) << std::endl;   // int + double

  return 0;
}

Explanation:
In C++14, lambdas can have auto parameters, making them implicitly templated.
This means the same lambda can work for int, double, float, etc., without having to manually define templates.
The return type is automatically deduced by the compiler.

Expected Output:
add(3, 4) = 7
add(3.5, 2.1) = 5.6
add(10, 2.5) = 12.5
--------------------------------------------*/

Can now modify captured variables inside the lambda using [x] mutable.

int x = 10;
auto f = [x]() mutable { x += 5; return x; };
std::cout << f(); // 15
std::cout << x;   // 10 (original x unchanged)

/*--------------------------------------------
✅ Complete Program: Mutable Lambda (C++14 Example)
#include <iostream>
int main() {
    int x = 10;

    // 'mutable' allows modifying a variable captured by value inside the lambda
    auto f = [x]() mutable { 
        x += 5;         // modifies the *copy* of x
        return x; 
    };

    std::cout << "f() returns: " << f() << std::endl;  // 15
    std::cout << "Original x after calling f(): " << x << std::endl; // still 10

    // Call again — since x was captured by value, a new copy is used each time f is created
    auto g = [x]() mutable {
        x *= 2;
        return x;
    };

    std::cout << "g() returns: " << g() << std::endl;  // 20
    std::cout << "Original x remains: " << x << std::endl; // still 10

  return 0;
}

Explanation:
[x] → captures x by value (a copy).
mutable → allows modification of that captured copy inside the lambda.
The original variable (x in the outer scope) remains unchanged.
Without mutable, this line:
x += 5;


would cause a compiler error, because captured-by-value 
variables are normally read-only inside lambdas.

Expected Output:
f() returns: 15
Original x after calling f(): 10
g() returns: 20
Original x remains: 10
--------------------------------------------*/





1. Lambda Function in C++14
A lambda function is an anonymous function that you can define inline. 
In C++14, lambdas can do more than in C++11 (like generic lambdas).

Syntax:
[ captures ] ( parameters ) -> return_type { body }

Example:
#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    // Lambda to print numbers
    auto print = [](int n) { std::cout << n << " "; };
    for (auto n : nums) {
        print(n);
    }
    std::cout << std::endl;

  return 0;
}

Explanation:
[ ] → capture clause
(int n) → parameter list
{ std::cout << n << " "; } → function body



2. Generic Lambda (C++14 feature)
C++14 allows generic lambdas using auto in parameter types. 
This lets you write lambdas that work with multiple types.

Example:
#include <iostream>
int main() {
    auto add = [](auto a, auto b) { return a + b; };
    std::cout << add(2, 3) << std::endl;       // 5 (int)
    std::cout << add(2.5, 3.7) << std::endl;   // 6.2 (double)
  return 0;
}

Explanation:
auto a, auto b → generic parameters
Works like a template function for lambdas


3. Generalized Lambda Capture (C++14 feature)
C++14 allows you to initialize variables directly in the capture clause. 
This is called generalized lambda capture (or init-capture).

Example:
#include <iostream>
int main() {
    int x = 5;
    // Capture x by value and also create a new variable y in the lambda
    auto lambda = [x, y = x + 10]() { 
        std::cout << "x = " << x << ", y = " << y << std::endl; 
    };
    lambda(); // Output: x = 5, y = 15
  return 0;
}

Explanation:
y = x + 10 creates a new variable y inside the lambda
Can also capture by move: [p = std::move(ptr)]

4. constexpr Lambda (C++17+, partially in C++14 as constexpr functions)
In C++14, lambdas can be constexpr if all operations inside are 
constexpr compatible. 
This allows the lambda to be evaluated at compile-time.

Example:
#include <iostream>
int main() {
    constexpr auto square = [](int n) { return n * n; };
    std::cout << square(5) << std::endl; // 25
  return 0;
}

Explanation:
constexpr allows compile-time evaluation
C++14 adds more relaxed rules compared to C++11

5. Capture by Constant Reference
You can capture variables by reference and mark them as const 
to prevent modification.

Example:
#include <iostream>
int main() {
    int x = 10;
    auto lambda = [&x]() { 
        std::cout << "x = " << x << std::endl; 
        // x = x + 5; // Error if lambda parameter is const
    };
    lambda(); // x = 10
  return 0;
}

Or explicitly as const reference in init-capture (C++14):
auto lambda = [cx = x]() { std::cout << cx << std::endl; };

Explanation:
&x → capture by reference
Can use const int &cx = x in generalized capture to avoid modification

✅ Summary Table
| Feature              | Example                              | Notes                            |
| -------------------- | ------------------------------------ | -------------------------------- |
| Lambda               | `[](int n){}`                        | Basic anonymous function         |
| Generic Lambda       | `[](auto a, auto b){ return a+b; }`  | Template-like lambda             |
| Generalized Capture  | `[y = x+10](){}`                     | Init variables in lambda capture |
| `constexpr` Lambda   | `constexpr [](int n){ return n*n; }` | Compile-time evaluation          |
| Capture by Const Ref | `[&x]() {}`                          | Access without modification      |
