5. Lambda Function in C++17

C++17 introduced:
Capture by Move: [x = std::move(y)]
Structured Bindings inside lambdas
constexpr lambdas

Example:
auto f = [v = std::move(vec)](){ return v.size(); };

Useful when you want the lambda to take ownership of variables.

/*--------------------------------------------
✅ Complete Program: C++17 Lambda Improvements
#include <iostream>
#include <vector>
#include <tuple>
#include <utility>  // for std::move
int main() {
    std::cout << "=== Capture by Move ===" << std::endl;
    // 1️⃣ Capture by Move: [x = std::move(y)]
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // Move vec into the lambda so it takes ownership
    auto f = [v = std::move(vec)]() {
        return v.size();
    };
    std::cout << "Size of moved vector inside lambda: " << f() << std::endl;
    std::cout << "Original vector size after move: " << vec.size() << std::endl;  // 0 (moved-from)
    std::cout << "\n=== Structured Bindings Inside Lambda ===" << std::endl;

    // 2️⃣ Structured Bindings inside Lambda
    auto printPair = [](const std::pair<int, std::string>& p) {
        auto [id, name] = p; // structured binding in C++17
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    };
    std::pair<int, std::string> person = {101, "Alice"};
    printPair(person);
    std::cout << "\n=== constexpr Lambda ===" << std::endl;

    // 3️⃣ constexpr Lambda
    constexpr auto square = [](int n) {
        return n * n;
    };
    // Can be evaluated at compile time
    constexpr int result = square(5);
    std::cout << "square(5) = " << result << std::endl;

   return 0;
}

Explanation of Key Features
✅ 1. Capture by Move [x = std::move(y)]

Introduced in C++17.
Lets a lambda take ownership of a movable resource (e.g., std::vector, std::unique_ptr).
Without it, only copy or reference capture was possible.
auto f = [v = std::move(vec)]() { return v.size(); };

✅ 2. Structured Bindings inside Lambdas
Allows unpacking tuples/pairs easily within lambda bodies.
Example:
auto [id, name] = p;

Cleaner and more expressive than using .first and .second.

✅ 3. constexpr Lambdas
Lambdas can now be marked as constexpr.
Allows compile-time evaluation if all arguments are constant expressions.
constexpr auto square = [](int n) { return n * n; };
constexpr int result = square(5);  // computed at compile time

Expected Output
=== Capture by Move ===
Size of moved vector inside lambda: 5
Original vector size after move: 0

=== Structured Bindings Inside Lambda ===
ID: 101, Name: Alice

=== constexpr Lambda ===
square(5) = 25
--------------------------------------------*/




1. Lambda Function in C++17
Basic lambda syntax remains the same as in C++14:

#include <iostream>
int main() {
    auto greet = [](const std::string& name) {
        std::cout << "Hello, " << name << "!\n";
    };

    greet("Alice"); // Output: Hello, Alice!
  return 0;
}


Notes for C++17:
Lambdas in C++17 support auto return type deduction automatically, 
so you often don’t need -> type.

Can use lambdas in constexpr contexts if compatible.

2. Generic Lambda (C++14+)
C++17 inherits generic lambdas from C++14. 
Using auto in parameters allows template-like behavior:

#include <iostream>
int main() {
    auto multiply = [](auto a, auto b) { return a * b; };
    std::cout << multiply(3, 4) << "\n";    // 12
    std::cout << multiply(2.5, 1.5) << "\n"; // 3.75
  return 0;
}


C++17 improvement:
Can now have auto parameters with constexpr lambdas and 
structured bindings in lambda parameters.

3. Generalized Lambda Capture (C++14+)
C++17 keeps init-capture but adds * and && captures more naturally.

#include <iostream>
#include <memory>
int main() {
    int x = 5;
    auto ptr = std::make_unique<int>(10);

    auto lambda = [x, y = x + 2, uptr = std::move(ptr)]() {
        std::cout << "x = " << x << ", y = " << y << ", *uptr = " << *uptr << "\n";
    };

    lambda(); // Output: x=5, y=7, *uptr=10
  return 0;
}


Notes:
You can now easily move resources into lambdas (uptr = std::move(ptr))
Works for both C++14 and C++17, but C++17 improves type deduction 
and constexpr interaction.

4. constexpr Lambda (C++17 feature enhancement)
C++17 lifts most C++14 constexpr restrictions, 
allowing more lambdas to be evaluated at compile-time.

#include <iostream>
int main() {
    constexpr auto square = [](int n) { return n * n; };
    constexpr int val = square(5); // Compile-time
    std::cout << val << "\n";      // Output: 25
  return 0;
}


C++17 Notes:
Lambdas can now be used in constexpr contexts with more complex 
logic, including loops and branches.

Before C++17, constexpr lambdas were very limited.

5. Capture by Constant Reference
Capturing variables by const reference prevents modification 
inside the lambda.

#include <iostream>
int main() {
    int x = 42;

    auto lambda = [&x]() { 
        std::cout << "x = " << x << "\n"; 
        // x = 50; // Error if we intend to keep x constant
    };

    lambda(); // Output: x = 42

    // Or with generalized capture
    auto lambda2 = [cx = x]() { std::cout << "cx = " << cx << "\n"; };

    lambda2(); // Output: cx = 42
  return 0;
}


C++17 Notes:
Works the same as C++14
You can combine constexpr lambdas with captures by constant 
reference for compile-time safe access.

✅ Summary Table for C++17 Lambdas
| Feature              | Example                              | C++17 Notes                                    |
| -------------------- | ------------------------------------ | ---------------------------------------------- |
| Lambda               | `[](int n){}`                        | Auto return type deduction                     |
| Generic Lambda       | `[](auto a, auto b){ return a+b; }`  | Can be constexpr, structured binding in params |
| Generalized Capture  | `[y = x+10, p = std::move(ptr)](){}` | Move captures and better type deduction        |
| `constexpr` Lambda   | `constexpr [](int n){ return n*n; }` | More complex logic allowed                     |
| Capture by Const Ref | `[&x]() {}` or `[cx = x](){}`        | Safe read-only access, works with constexpr    |
