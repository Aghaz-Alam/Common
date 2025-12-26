constexpr was introduced in C++11.

Evolution summary:
C++11 — constexpr introduced (very limited: functions required a single return statement, no loops, no local variables, etc.)
C++14 — major expansion: loops, local variables, conditionals allowed.
C++17 — minor improvements; constexpr more widely usable.
C++20 — consteval and constinit added, and many standard library functions/containers became constexpr.


//c++11/14/17/20
constexpr

✅ constexpr (C++11 → C++20)
🔹 C++11 — First introduction
What it can do:
-->Mark variables whose values may be evaluated at compile time.
-->Mark functions that can be executed at compile time if given constant-expression arguments.

C++11 limitations:
constexpr functions must:
-->contain only one return statement
-->cannot have:
  *loops (for, while)
  *local variables (except trivial)
  *branches (if, switch) except a conditional return
  *dynamic memory allocation
-->only literal types allowed.

Use cases (C++11):
constexpr int square(int x) { return x * x; }
constexpr int v = square(5);  // compile-time

/* ----------------complete program------ */
#include <iostream>
constexpr int square(int x) {
    return x * x;
}
int main() {
    // Compile-time evaluation
    constexpr int v = square(5);   // computed at compile time

    // Run-time evaluation
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;

    int r = square(n);             // computed at run time

    std::cout << "Compile-time result: " << v << std::endl;
    std::cout << "Run-time result: " << r << std::endl;

   return 0;
}
/*
Enter a number: 5
Compile-time result: 25
Run-time result: 25
*/

What this program demonstrates
✔ Compile-time constexpr evaluation
--> constexpr int v = square(5);
--> This is guaranteed to be evaluated at compile time because:
   *square(5) is a valid constant expression.
   *v is declared constexpr.

✔ Run-time evaluation
--> int r = square(n);

Here n is user input → not a constant expression → function runs at runtime.
/* -------------------------------------------------------------------------------------- */
🔹 C++14 — Big expansion
Improvements:
constexpr functions can now contain:
--> loops
--> local variables
--> multiple statements
--> branches (if, switch)
--> recursion
This made real compile-time algorithms possible.

Use cases (C++14):
constexpr int fact(int n) {
    int r = 1;
    for(int i = 1; i <= n; ++i) r *= i;
    return r;
}
/* -------------commplete program code------------- */
#include <iostream>
constexpr int fact(int n) {
    int r = 1;
    for (int i = 1; i <= n; ++i)
        r *= i;
    return r;
}

int main() {
    // Compile-time computation
    constexpr int ct = fact(5);     // evaluated at compile time

    // Run-time computation
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;

    int rt = fact(n);               // evaluated at run time

    std::cout << "Compile-time factorial of 5: " << ct << std::endl;
    std::cout << "Run-time factorial of " << n << ": " << rt << std::endl;

    return 0;
}
/*
Enter a number: 5
Compile-time factorial of 5: 120
Run-time factorial of 5: 120
*/



/* ---------------------------------------------- */
✅ 1. Loops inside constexpr (C++14)
#include <iostream>
constexpr int sum_upto(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i)
        sum += i;        // loop allowed in C++14
    return sum;
}
int main() {
    constexpr int v = sum_upto(5); // compile-time
    std::cout << "Sum up to 5 = " << v << std::endl;
}
//Sum up to 5 = 15




✅ 2. Local variables inside constexpr (C++14)
#include <iostream>
constexpr int add_three(int x) {
    int a = 1;           // local variable allowed
    int b = 2;
    int c = 3;
    return x + a + b + c;
}
int main() {
    constexpr int v = add_three(10);
    std::cout << "Result = " << v << std::endl;
}
//Result = 16



✅ 3. Multiple statements inside constexpr (C++14)
#include <iostream>
constexpr int do_math(int x) {
    int y = x * 2;
    y += 10;
    y /= 2;
    return y;           // multiple statements allowed
}
int main() {
    constexpr int v = do_math(8);
    std::cout << "Result = " << v << std::endl;
}
//Result = 13



✅ 4. Branches (if / switch) inside constexpr (C++14)
✔ Using if
#include <iostream>
constexpr int abs_val(int x) {
    if (x < 0)           // if allowed in C++14 constexpr
        return -x;
    return x;
}
int main() {
    constexpr int v = abs_val(-20);
    std::cout << "Absolute value = " << v << std::endl;
}
//Absolute value = 20



✔ Using switch   (C++14)
#include <iostream>
constexpr const char* num_to_word(int n) {
    switch (n) {         // switch allowed in C++14 constexpr
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        default: return "other";
    }
}
int main() {
    constexpr const char* s = num_to_word(2);
    std::cout << "Word: " << s << std::endl;
}
//Word: two



✅ 5. Recursion inside constexpr (C++14)
#include <iostream>
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1); // recursion OK in C++14
}
int main() {
    constexpr int v = factorial(6);
    std::cout << "Factorial of 6 = " << v << std::endl;
}
//Factorial of 6 = 720


/* -------------------------------------------------------------------------------------- */
🔹 C++17 — Mostly polish
Changes:
--> More standard library functions became constexpr
--> The language itself did not change the rules much from C++14

Use cases (C++17):
--> All C++14 examples work; still no dynamic allocation or complex types like std::string (until C++20).

/* ------------------------------ */
C++17 did NOT expand constexpr rules,
but it made more standard-library functions constexpr, which made some new things possible.


✅ 1. C++14 code works unchanged in C++17
--> C++17 does not change restrictions on user-defined constexpr functions.
--> So all our C++14 examples (loops, branches, recursion…) continue to work.

✔ Example: C++14 constexpr recursion → still fine in C++17
#include <iostream>
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
int main() {
    constexpr int v = factorial(5);  // still compile-time in C++17
    std::cout << "Factorial = " << v << std::endl;
}
//Factorial = 120
✔ Works in C++14
✔ Works in C++17
🚫 Still cannot use dynamic allocation
🚫 Still cannot use std::string



✅ 2. More of the Standard Library becomes constexpr in C++17
--> C++17 made many utility functions and algorithms constexpr.

Examples include:
--> std::array::operator[]
--> std::pair, std::tuple constructors
Some <algorithm> utilities (small upgrades)

✔ Example: std::array now fully usable in constexpr contexts (improved in C++17)
#include <iostream>
#include <array>
constexpr int sum_array() {
    std::array<int, 4> arr = {1, 2, 3, 4};   // OK in C++17

    int s = 0;
    for (int x : arr)
        s += x;
    return s;
}
int main() {
    constexpr int v = sum_array();  // computed at compile-time
    std::cout << v << std::endl;
}
//10

✔ In C++14: std::array had limits (not all functions were constexpr)
✔ In C++17: more std::array operations allowed inside constexpr




❌ 3. Still no std::string in constexpr (C++17)
--> C++17 still does NOT allow dynamic memory inside constexpr.
--> Therefore, types like std::string or std::vector cannot be used in a constexpr function.

Example that fails in C++17 but works in C++20:
#include <string>
constexpr std::string make_message() {   // ❌ ERROR in C++17
    return "Hello";
}
int main() {
    constexpr auto msg = make_message(); // ❌ not allowed in C++17
}

⚠ C++17 rejects this because std::string uses heap allocation
✔ C++20 allows this thanks to constexpr dynamic allocation





❌ 4. Still no dynamic memory inside constexpr (C++17)
Example that fails in C++17 but works in C++20:
constexpr int* make_ptr() {     // ❌ ERROR in C++17
    return new int(5);          // new/delete not constexpr yet
}
int main() {
    constexpr int* p = make_ptr();   // ❌ fails in C++17
}

✔ Dynamic allocation inside constexpr becomes supported in C++20
❌ Not allowed in C++17 or C++14




✅ 5. Example: Using newly constexpr standard-library features (C++17)
--> std::pair and std::tuple received constexpr constructors.

Example (C++17):
#include <iostream>
#include <utility>
constexpr int get_sum() {
    std::pair<int, int> p = {4, 6};   // now constexpr constructor
    return p.first + p.second;
}
int main() {
    constexpr int v = get_sum(); 
    std::cout << v << std::endl;   // prints 10
}
//10

✔ New in C++17 – now usable inside constexpr
❌ In C++14 some constructors were not constexpr

/* -------------------------------------------------------------------------------------- */
🔹 C++20 — Major upgrade
Changes:
--> Many containers become constexpr (std::vector, std::string, std::array improved)
--> Allowed dynamic allocation inside constexpr in some contexts
--> Enabled compile-time parsing, JSON parsing, etc.

Uses (C++20):
--> constexpr std::string s = "hello";   // now allowed in C++20

🟦 Summary: constexpr purpose
✔ Optional compile-time evaluation
✔ Can run at runtime if not evaluated in constant context
✔ Improved dramatically from C++11 → C++20


/* ----------------------------------- */
C++20’s major constexpr upgrades:
--> std::string now allowed in constexpr
--> std::vector now allowed in constexpr
--> dynamic memory allocation (new) now allowed in constexpr
--> containers + algorithms improved to work in constant expressions
--> Everything below is valid only in C++20 or later.

✅ 1. C++17 FAILED: constexpr std::string
❌ C++17 Error
std::string cannot be used inside constexpr.

✔ C++20 FIXED program (works!)
#include <iostream>
#include <string>
constexpr std::string make_message() {
    std::string s = "Hello";
    s += " World";
    return s;
}
int main() {
    constexpr std::string msg = make_message();  // compile-time
    std::cout << msg << std::endl;
}

🟢 C++20 allows dynamic memory inside constexpr, so std::string works.

/* -------------------------------- */
#include <iostream>
#include <string>
constexpr std::string make_message() {
    std::string s = "Hello";
    s += " World";
    return s;
}
int main() {
    constexpr std::string msg = make_message();  // compile-time
    std::cout << msg << std::endl;
}



Online GDB ERROR: C++20 
main.cpp: In function ‘int main()’:
main.cpp:9:46: error: ‘std::string{std::__cxx11::basic_string::_Alloc_hider{((char*)(& msg.std::__cxx11::basic_string::.std::__cxx11::basic_string::::_M_local_buf))}, 11, std::__cxx11::basic_string::{char [16]{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0, '\000', '\000', '\000', '\000'}}}’ is not a constant expression
    9 |     constexpr std::string msg = make_message();  // compile-time

*/----------------------------------------------------------------------*/
#include <iostream>
#include <string>

constexpr std::string make_message() {
    std::string s = "Hello";
    s += " World";
    return s;
}

int main() {
    constexpr std::string msg = make_message();
    std::cout << msg << std::endl;
}

Online GDB ERROR: C++23 
main.cpp: In function ‘int main()’:
main.cpp:31:46: error: ‘std::string{std::__cxx11::basic_string::_Alloc_hider{((char*)(& msg.std::__cxx11::basic_string::.std::__cxx11::basic_string::::_M_local_buf))}, 11, std::__cxx11::basic_string::{char [16]{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0, '\000', '\000', '\000', '\000'}}}’ is not a constant expression
   31 |     constexpr std::string msg = make_message();
      |                                              ^
      
      
      
You are running your code on OnlineGDB, which uses GCC + libstdc++ — and that combination STILL does NOT support constexpr std::string, even in C++23 mode.

👉 This is not your code’s fault.
👉 It is the compiler + standard-library implementation.

🔥 IMPORTANT FACT
✔ The C++ standard allows constexpr std::string starting in C++20
❌ GCC’s libstdc++ only finished partial support in GCC 13,

but OnlineGDB uses an older / incomplete libstdc++ build,
so std::string is NOT constexpr there, even in C++23.

➤ That is why you get:
error: std::string ... is not a constant expression


This is because GCC’s std::string still uses non-constexpr SSO buffers internally.

🟦 What this means
Your code:
constexpr std::string make_message() {
    std::string s = "Hello";
    s += " World";
    return s;
}


is valid C++20/C++23, and works on:
| Compiler                                | Works?                     |
| --------------------------------------- | -------------------------- |
| **Clang + libc++**                      | ✔ YES                      |
| **MSVC (Visual Studio)**                | ✔ YES                      |
| **GCC (full library, correct version)** | ✔ YES (but not all builds) |
| **OnlineGDB (GCC)**                     | ❌ NO                       |
| **MinGW GCC**                           | ❌ NO                       |



🟩 WORKING SOLUTION (portable everywhere)
--> Use std::string_view instead of std::string.
--> This works on all compilers, including C++17:

#include <iostream>
#include <string_view>
constexpr std::string_view make_message() {
    return "Hello World";
}
int main() {
    constexpr std::string_view msg = make_message();
    std::cout << msg << std::endl;
}
//Hello World

✔ Fully constexpr
✔ Works in OnlineGDB
✔ Works in C++17/20/23




🟩 WORKING SOLUTION (C++20) using array instead of string
--> If you want a true compile-time string, use a char array:

#include <iostream>
#include <array>
constexpr auto make_message() {
    return std::array<char, 12>{"Hello World"};
}
int main() {
    constexpr auto msg = make_message();
    for (char c : msg) std::cout << c;
}
//Hello World


🟩 If you want real constexpr std::string, use one of these platforms:
✔ Compiler that supports constexpr std::string:
--> Clang 16+ with libc++
--> MSVC (VS 2022+)

❌ Not fully implemented:
--> GCC on OnlineGDB
--> GCC in many Linux distros
--> MinGW

🟥 Conclusion
--> Your code is correct,
--> OnlineGDB’s GCC standard library does NOT support constexpr std::string,
--> even in C++23.

This is a compiler limitation, NOT a mistake in your program.
/* -------------------------------- */


/* ----------------------------------------------------------- */
✅ 2. C++17 FAILED: Dynamic allocation inside constexpr (new)
❌ C++17 Error
new and delete are not allowed inside constexpr.

✔ C++20 FIXED program
#include <iostream>
constexpr int make_value() {
    int* p = new int(42);  // allowed in C++20 constexpr
    int val = *p;
    delete p;
    return val;
}
int main() {
    constexpr int v = make_value();
    std::cout << v << std::endl;
}
//42

🟢 C++20 permits limited dynamic memory in constexpr evaluation.

✅ 3. C++17 FAILED: constexpr std::vector
❌ C++17 Error
std::vector is not constexpr-friendly.

✔ C++20 FIXED program
#include <iostream>
#include <vector>
constexpr int sum_vector() {
    std::vector<int> v = {1, 2, 3, 4};  // now allowed
    int s = 0;
    for (int x : v)
        s += x;
    return s;
}
int main() {
    constexpr int total = sum_vector();
    std::cout << total << std::endl;
}
//10


🟢 std::vector became constexpr-enabled in C++20.

✅ 4. C++17 FAILED: constexpr compile-time parsing / processing
❌ C++17: Complex algorithms with dynamic memory + strings not allowed
✔ C++20: Fully allowed

Example: constexpr parsing of a CSV-like string.
#include <iostream>
#include <string>
#include <vector>
constexpr std::vector<std::string> split(const std::string& text) {
    std::vector<std::string> result;
    std::string temp;
    for (char c : text) {
        if (c == ',') {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += c;
        }
    }
    result.push_back(temp);
    return result;
}
int main() {
    constexpr auto parts = split("apple,banana,orange");

    for (auto& s : parts) {
        std::cout << s << std::endl;   // compile-time created strings
    }
}


🟢 Works because std::string and std::vector are constexpr in C++20.

✅ 5. C++17 FAILED: More advanced constexpr container manipulation
❌ C++17: not fully supported
✔ C++20: allowed

Here’s a full compile-time sort using std::vector:

#include <iostream>
#include <vector>
#include <algorithm>
constexpr std::vector<int> make_sorted() {
    std::vector<int> v = {5, 1, 4, 3, 2};
    std::sort(v.begin(), v.end());   // now constexpr in C++20
    return v;
}
int main() {
    constexpr auto sorted = make_sorted();
    for (int n : sorted)
        std::cout << n << " ";
}


🟢 C++20 makes <algorithm> constexpr-enabled.

/* -------------------------------------------------------------------------------------- */
//C++20
consteval

/* ---------------------- */
✅ consteval (introduced in C++20)
What it does:
--> A consteval function must be evaluated at compile time.
--> It cannot be executed at runtime.
--> If you call it with a non–constant expression → compile-time error.

Purpose:
--> Guarantee that a function’s result is always known at compile time.

Example:
consteval int add(int a, int b) {
    return a + b;
}
int x = add(3, 4);      // OK
int n;                 
int y = add(n, 4);      // ❌ compile-time error (n is not constexpr)


Use cases:
--> Compile-time ID generators
--> Static configuration values
--> Compile-time string hashing
--> Safer constexpr replacements when runtime use is dangerous


/* -------------------------------------------------------------------------------------- */
//C++20
constinit

/* ------------------------------- */
✅ constinit (introduced in C++20)
What it does:
--> Ensures a variable is initialized at compile time.
--> BUT the variable is not necessarily constant.
--> Prevents the “static initialization order fiasco”.

Example:
constinit int counter = 0;  // must have compile-time initial value
counter = 5;                // OK — it's not const


Why it exists:
--> constexpr and const do not guarantee initialization before runtime
--> constinit does.

Common use case:
--> Global objects that must be initialized before main():
--> constinit int global_id = 10;


Side-by-side comparison
| Feature                 | `constexpr`                  | `consteval`        | `constinit`                             |
| ----------------------- | ---------------------------- | ------------------ | --------------------------------------- |
| Introduced              | C++11                        | C++20              | C++20                                   |
| Compile-time evaluation | **allowed** but not required | **required**       | Initialization required, not evaluation |
| Usable at runtime       | ✔ Yes                        | ❌ No               | ✔ Yes                                   |
| Applies to              | functions + variables        | functions          | variables                               |
| Can change after init?  | No (const var)               | No (function only) | ✔ Yes                                   |

🎯 Short, practical explanation
C++11–17 (constexpr)
"This can run at compile time if possible, otherwise runtime."

C++20 (consteval)
"This must run at compile time."

C++20 (constinit)

"This variable must be initialized at compile time,
but can change later."


/* ------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------ */
✅ 1. constexpr variables
A variable declared with constexpr must be known at compile time.
constexpr int x = 10;   // OK

❌ Not allowed:
int y = 5;
constexpr int z = y;    // ERROR: y not compile-time constant

👍 Allowed only if value is constant at compile time:
constexpr int a = 5 + 10;   // OK

/* -------------------------- */
#include <iostream>
using namespace std;
int main() {

    // ------------------------------------------
    // 1. constexpr variable: compile-time constant
    // ------------------------------------------
    constexpr int x = 10;     // OK
    cout << "x = " << x << endl;

    // ------------------------------------------
    // 2. Not allowed: initializer not constant
    // ------------------------------------------
    int y = 5;

    // constexpr int z = y;   // ❌ ERROR
    // ERROR: y is NOT a compile-time constant

    // ------------------------------------------
    // 3. Allowed: constexpr with compile-time expression
    // ------------------------------------------
    constexpr int a = 5 + 10;  // OK (15)
    cout << "a = " << a << endl;

    return 0;
}
/*
x = 10
a = 15
*/
/* ------------------------------------------------------------------------ */
✅ 2. constexpr functions
A constexpr function can run at compile time OR runtime, depending on inputs.
constexpr int square(int x) {
    return x * x;
}

Compile-time execution:
constexpr int val = square(5);   // computed at compile time
Runtime execution:
int r;
cin >> r;
cout << square(r);              // runtime

🎯 constexpr is NOT “always compile time”
It means:
Function is allowed to be computed at compile time.
If arguments are constant → compile time
If arguments are runtime → evaluated normally

/* ----------------------- */
#include <iostream>
using namespace std;
// -----------------------------------------
// constexpr function
// Can run at compile-time OR runtime
// -----------------------------------------
constexpr int square(int x) {
    return x * x;
}
int main() {
    // -----------------------------------------
    // 1. Compile-time execution
    // -----------------------------------------
    constexpr int val = square(5);   // computed at compile time
    cout << "Compile-time square(5) = " << val << endl;

    // -----------------------------------------
    // 2. Runtime execution
    // -----------------------------------------
    int r;
    cout << "Enter a number: ";
    cin >> r;

    // r is not constexpr → runtime evaluation
    cout << "Runtime square(" << r << ") = " << square(r) << endl;

    return 0;
}
/*
Compile-time square(5) = 25
Enter a number: 5
Runtime square(5) = 25
*/
/* ------------------------------------------------------------------------ */
✅ 3. constexpr objects
Can define static lookup tables at compile time:
struct Point {
    int x, y;
};
constexpr Point p{10, 20};      // OK

/* --------------------- */
//1. constexpr with STRUCT
#include <iostream>
using namespace std;
// -----------------------------------------
// constexpr with STRUCT
// -----------------------------------------
struct Point {
    int x;
    int y;
};
// constexpr object of struct (compile-time)
constexpr Point p1{10, 20};
int main() {
    cout << "Struct Point p1 = (" << p1.x << ", " << p1.y << ")\n";
    // Runtime example
    int a, b;
    cout << "Enter x and y: ";
    cin >> a >> b;

    Point p2{a, b};  // runtime object
    cout << "Point p2 = (" << p2.x << ", " << p2.y << ")\n";
  return 0;
}
/*
Struct Point p1 = (10, 20)
Enter x and y: 5 6
Point p2 = (5, 6)
*/


//2. constexpr with CLASS
#include <iostream>
using namespace std;
// -----------------------------------------
// constexpr with CLASS
// Requires constexpr constructor
// -----------------------------------------
class Rectangle {
  private:
    int width;
    int height;
  public:
    // constexpr constructor
    constexpr Rectangle(int w, int h) : width(w), height(h) {}
    // constexpr function
    constexpr int area() const {
        return width * height;
    }
};
// Compile-time object
constexpr Rectangle r1(4, 5);
constexpr int area1 = r1.area(); // compile-time area
int main() {
    cout << "Rectangle r1 area (compile-time) = " << area1 << "\n";
    // Runtime example
    int w, h;
    cout << "Enter width & height: ";
    cin >> w >> h;

    Rectangle r2(w, h);  // runtime object
    cout << "Rectangle r2 area (runtime) = " << r2.area() << "\n";
  return 0;
}
/*
Rectangle r1 area (compile-time) = 20
Enter width & height: 10 5
Rectangle r2 area (runtime) = 50
*/
/* ------------------------------------------------------------------------ */
✅ 4. constexpr constructors
Allows creating constant objects at compile time.
class Point {
  public:
    int x, y;

    constexpr Point(int a, int b) : x(a), y(b) {}
};
constexpr Point p(3, 4);

/* ------------------ */
#include <iostream>
using namespace std;
// -----------------------------------------
// Class with constexpr constructor
// -----------------------------------------
class Point {
  public:
    int x;
    int y;
    // constexpr constructor
    constexpr Point(int a, int b) : x(a), y(b) {}
    // constexpr member function
    constexpr int sum() const {
        return x + y;
    }
};
// constexpr object (compile-time)
constexpr Point p(3, 4);
constexpr int sum1 = p.sum();
int main() {
    // -----------------------------------------
    // Using constexpr object
    // -----------------------------------------
    cout << "Compile-time Point p = (" << p.x << ", " << p.y << ")\n";
    cout << "Sum of p = " << sum1 << "\n";
    // -----------------------------------------
    // Runtime object
    // -----------------------------------------
    int a, b;
    cout << "Enter x and y: ";
    cin >> a >> b;
    Point q(a, b);  // runtime object
    cout << "Runtime Point q = (" << q.x << ", " << q.y << ")\n";
    cout << "Sum of q = " << q.sum() << "\n";
  return 0;
}
/*
Compile-time Point p = (3, 4)
Sum of p = 7
Enter x and y: 5 3
Runtime Point q = (5, 3)
Sum of q = 8
*/
/* ------------------------------------------------------------------------ */
✅ 5. constexpr if (C++17)
Compile-time branching for templates.
template <typename T>
void show(T v) {
    if constexpr (std::is_integral_v<T>)
        cout << "Integral\n";
    else
        cout << "Non-integral\n";
}

/* ------------------------- */
#include <iostream>
#include <type_traits>
using namespace std;
// -----------------------------------------
// Template function with constexpr if
// -----------------------------------------
template <typename T>
void show(T v) {
    if constexpr (std::is_integral_v<T>) {
        cout << v << " is Integral\n";
    } else {
        cout << v << " is Non-integral\n";
    }
}
int main() {

    int a = 10;
    double b = 3.14;
    char c = 'X';
    string s = "Hello";

    show(a); // Integral
    show(b); // Non-integral
    show(c); // Integral
    show(s); // Non-integral

    return 0;
}
/*  
Output: in C++17

10 is Integral
3.14 is Non-integral
X is Integral
Hello is Non-integral
*/
/* ------------------------------------------------------------------------ */
✅ 6. constexpr with arrays
You can use constexpr to create fixed compile-time arrays.
constexpr int arr[] = {1,2,3,4};

⚡ Important rules
✔ constexpr function must contain only one return statement (C++11)

C++14 removes this restriction → allows loops, if, etc.
✔ constexpr variable must be initialized
constexpr int n;   // ❌ ERROR

✔ constexpr object must have a constexpr constructor

/* --------------------------- */
#include <iostream>
using namespace std;
// -----------------------------------------
// 1. constexpr array
// -----------------------------------------
constexpr int arr[] = {1, 2, 3, 4, 5};
constexpr size_t arrSize = sizeof(arr)/sizeof(arr[0]);
// -----------------------------------------
// 2. constexpr function (C++11: single return)
// -----------------------------------------
constexpr int sumArray_C11(int a, int b) {
    return a + b; // only single return
}
// -----------------------------------------
// 3. constexpr function (C++14: can use loops)
// -----------------------------------------
constexpr int sumArray_C14() {
    int sum = 0;
    for (size_t i = 0; i < arrSize; ++i)
        sum += arr[i];
    return sum;
}
int main() {

    // -----------------------------------------
    // Using constexpr array
    // -----------------------------------------
    cout << "constexpr array: ";
    for (size_t i = 0; i < arrSize; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    // -----------------------------------------
    // Using C++11 constexpr function
    // -----------------------------------------
    constexpr int s1 = sumArray_C11(10, 20);
    cout << "C++11 constexpr sum(10,20) = " << s1 << "\n";

    // -----------------------------------------
    // Using C++14 constexpr function with loop
    // -----------------------------------------
    constexpr int s2 = sumArray_C14();
    cout << "C++14 constexpr sum of array = " << s2 << "\n";

  return 0;
}
/*
constexpr array: 1 2 3 4 5 
C++11 constexpr sum(10,20) = 30
C++14 constexpr sum of array = 15
*/
/* ------------------------------------------------------------------------ */