Macros usage

✅ 1. What Are Macros in C++?
Macros are preprocessor directives that run before compilation, performing text substitution.
They are handled by the C++ preprocessor (cpp), not the compiler.

✅ 2. List of All Possible Macro Usages in C++
Here is a complete and exhaustive list of ways macros are used.

A) Object-like Macros (Simple substitution)
#define PI 3.14159
#define MAX_SIZE 100

B) Function-like Macros
#define SQUARE(x) ((x) * (x))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

C) Conditional Compilation
Used to compile or skip blocks of code.
#ifdef DEBUG
    cout << "Debug mode\n";
#endif


Common:
#ifdef
#ifndef
#if
#elif
#else
#endif

D) File Include Guards
To avoid multiple inclusion of headers:
#ifndef MY_HEADER_H
#define MY_HEADER_H
// code...
#endif

E) #include macro replacement
Preprocessor includes another file:
#include <iostream>
#include "myfile.h"

F) #undef (To remove a previously defined macro)
#undef MAX

G) Stringizing (#) and Token-pasting (##) Macros
1️⃣ Stringizing
#define TO_STRING(x) #x
cout << TO_STRING(Hello); // "Hello"

2️⃣ Token pasting
#define CONCAT(a,b) a##b
int xy = 10;
cout << CONCAT(x,y); // xy → 10

H) Variadic Macros
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)

I) Predefined Built-in Macros
| Macro         | Meaning               |
| ------------- | --------------------- |
| `__LINE__`    | Current line number   |
| `__FILE__`    | Current file name     |
| `__func__`    | Current function name |
| `__DATE__`    | Compilation date      |
| `__TIME__`    | Compilation time      |
| `__cplusplus` | C++ standard version  |

Example:
cout << "Compiled on: " << __DATE__ << " " << __TIME__;

J) Pragmas (Compiler instructions via macros)
Example:
#pragma once

(Alternative to include guards)

K) Macro-generated code (X-Macros technique)
Used to generate repetitive code in one place.

#define COLORS \
X(Red) \
X(Green) \
X(Blue)

L) OS or Platform Specific Compilation
#ifdef _WIN32
   // Windows code
#elif __linux__
   // Linux code
#endif

✅ 3. Pros of Using Macros in C++
✔ 1. No runtime overhead
Macros are replaced before compilation, so they are extremely fast.

✔ 2. Useful for conditional compilation
Enable platform-specific code.

✔ 3. Useful for debugging/logging
Macros like:
#define LOG(x) cout << x << endl

✔ 4. Avoid repetitive code
Function-like macros, X-Macros, code generation.

✔ 5. Can use in C (compatibility reasons)
Macros are required when writing C/C++ compatible libraries.

❌ 4. Cons of Using Macros
✘ 1. No type safety
#define SQUARE(x) x*x     // SQUARE(1+2) → 1+2*1+2 (wrong)

✘ 2. Hard to debug
Debugger cannot step into macros easily.

✘ 3. Replaced blindly
The preprocessor does text substitution, causing:
Unexpected precedence issues
Hard-to-find bugs

✘ 4. Namespace pollution
Macros don’t obey C++ scope rules.

✘ 5. Harder to maintain
Especially complex nested macros.

✘ 6. Prefer constexpr, inline, templates
Modern C++ has better alternatives.

✅ 5. Do We Really Need Macros in Modern C++?
Alternatives now exist:
| Macro usage        | Modern C++ alternative        |
| ------------------ | ----------------------------- |
| `#define PI 3.14`  | `constexpr double PI = 3.14;` |
| `#define MAX(a,b)` | `std::max(a,b)`               |
| include guards     | `#pragma once`                |
| debug logs         | inline logging functions      |
| version checks     | if constexpr + build system   |

But macros are still needed for:

✔ Conditional compilation (OS/platform dependent)
✔ Header include guards (#pragma once)
✔ Debug enabling/disabling
✔ Interfacing with C libraries
✔ Compile-time generation (X-macros)
✔ Platform configuration flags
✔ Metaprogramming in low-level systems

✅ 6. Real-life Use Cases of Macros in C++

Here are the actual real-world scenarios where companies (Google, LLVM, Linux Kernel) use macros:

1️⃣ Logging systems
#ifdef DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

2️⃣ Platform-specific code
#ifdef _WIN32
   Sleep(1000);
#else
   sleep(1);
#endif

3️⃣ Compile-time configuration
Used in embedded systems, drivers, kernels.
#define USE_DMA 1
#if USE_DMA
   // DMA-based transfer
#else
   // CPU-based transfer
#endif

4️⃣ Include Guards
Every header file uses this.
#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H
// code...
#endif

5️⃣ Assertions & Debugging
#define ASSERT(x) if(!(x)) abort();

6️⃣ X-Macros for repeated code generation
Example: list of error codes in one place.
#define ERROR_LIST  \
X(FileNotFound)     \
X(AccessDenied)     \
X(OutOfMemory)

enum ErrorCode {
#define X(code) code,
    ERROR_LIST
#undef X
};


This avoids duplication.
7️⃣ Wrapping C APIs
Used when writing C++ libraries that interface with C libraries.

8️⃣ Performance sensitive flags
Used in game engines and embedded systems:
#define FAST_MATH

9️⃣ Variadic logging macros
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__);

🎯 Summary Answer (For Interview)
Macros in C++ are used for:
Symbolic constants
Function-like macros
Conditional compilation
Debugging/logging
Include guards
Variadic macros
X-macros
Token pasting / Stringizing
Platform/OS dependent code
Interfacing with C libraries


They are powerful but dangerous:
No type safety
Hard to debug
Cause unexpected bugs
Should be replaced with constexpr, inline, templates when possible

Still necessary for:
Low-level systems
OS-specific compilation
Compile-time feature toggles
Integrating legacy C code
Code generation techniques










/* ================================================== */

✅ A) Object-like Macros
✔ Example: Simple substitution
#include <iostream>
#define PI 3.14159
#define MAX_SIZE 100
int main() {
    std::cout << "PI = " << PI << "\n";
    std::cout << "MAX_SIZE = " << MAX_SIZE << "\n";
}
/* 
Output
PI = 3.14159
MAX_SIZE = 100
*/



✅ B) Function-like Macros
✔ Example: SQUARE, MAX

#include <iostream>
#define SQUARE(x) ((x) * (x))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
int main() {
    std::cout << "SQUARE(5) = " << SQUARE(5) << "\n";
    std::cout << "MAX(10, 20) = " << MAX(10,20) << "\n";
}
/* 
Output
SQUARE(5) = 25
MAX(10, 20) = 20
*/




✅ C) Conditional Compilation

#include <iostream>
#define DEBUG   // Try commenting this out
int main() {
#ifdef DEBUG
    std::cout << "Debug mode ON\n";
#else
    std::cout << "Debug mode OFF\n";
#endif
}
/* 
Output (DEBUG defined)
Debug mode ON
*/




✅ D) Include Guards

//header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H
void hello();
#endif

//header.cpp
#include <iostream>
#include "header.h"
void hello() { 
   std::cout << "Hello from header!\n"; 
}

//main.cpp
#include "header.h"
#include "header.h"  // included twice but guarded
int main() {
    hello();
}
/* 
Output
Hello from header!
*/




✅ E) #include (macro replacement)

#include <iostream>
#include <cmath>     // example of include
int main() {
    std::cout << "sqrt(16) = " << sqrt(16) << "\n";
}
/* 
Output
sqrt(16) = 4
*/



✅ F) #undef Example

#include <iostream>
#define VALUE 10
int main() {
    std::cout << VALUE << "\n";
    #undef VALUE
    #define VALUE 20
    std::cout << VALUE << "\n";
}
/* 
Output
10
20
*/


✅ G1) Stringizing (#)

#include <iostream>
#define TO_STRING(x) #x
int main() {
    std::cout << TO_STRING(Hello World) << std::endl;
    std::cout << TO_STRING(12345)<< std::endl;
    std::cout << TO_STRING(10 + 20 * 3)<< std::endl;
}
/* 
Output
"Hello World"
"12345"
"10 + 20 * 3"
*/


#include <iostream>
#define N 10
#define S(x) #x
int main() {
    std::cout << S(Hello World) << std::endl;
    std::cout << S(12345)<< std::endl;
    std::cout << S(10 + 20 * 3)<< std::endl;
}
/* 
Output
"Hello World"
"12345"
"10 + 20 * 3"
*/


#include <iostream>
#define DEBUG_VAR(x) std::cout << #x " = " << x << "\n"
int main() {
    int myValue = 42;
    double pi = 3.14;

    DEBUG_VAR(myValue);
    DEBUG_VAR(pi);
}
/* 
Output
myValue = 42
pi = 3.14
*/





#include <iostream>
#define DEBUG_VAR(x) std::cout << #x " = " << x << "\n"
int main() {

    int myValue = 42;
    double pi = 3.14;

    // ---------- Call 1 ----------
    DEBUG_VAR(myValue);

    /*
        Expansion step-by-step:
        #x  → "myValue"
        So the macro expands to:
        std::cout << "myValue" " = " << myValue << "\n";

        Adjacent string literals merge:
        "myValue" " = "  →  "myValue = "

        Final expanded line:
        std::cout << "myValue = " << myValue << "\n";
    */


    // ---------- Call 2 ----------
    DEBUG_VAR(pi);

    /*
        Expansion step-by-step:
        #x  → "pi"

        Macro becomes:
        std::cout << "pi" " = " << pi << "\n";

        Merge adjacent literals:
        "pi" " = "  → "pi = "

        Final expanded line:
        std::cout << "pi = " << pi << "\n";
    */

    return 0;
}
/* 
Output
myValue = 42
pi = 3.14
*/





✅ G2) Token Pasting (##)

#include <iostream>
#define CONCAT(a,b) a##b
int main() {
    int xy = 50;
    std::cout << CONCAT(x,y) << "\n";   // becomes xy
  return 0;
}
/* 
Output
50
*/



//Creating Unique Variable Names (auto-generated)
#include <iostream>
// two-step expansion so __LINE__ expands before concatenation
#define PASTE(a, b) a##b
#define EXPAND(a, b) PASTE(a, b)
#define UNIQUE_VAR(base) EXPAND(base, __LINE__)

int main() {

    int UNIQUE_VAR(temp) = 10;  
    int UNIQUE_VAR(temp) = 20;   

    // Print actual generated variables
    std::cout << temp497 << " " << temp498 << "\n";
  return 0;
}
/* 
Output
10 20
*/




//Building Function Names Dynamically
#include <iostream>
void func1() { std::cout << "func1\n"; }
void func2() { std::cout << "func2\n"; }

#define CALL_FUNC(n) func##n()

int main() {
    CALL_FUNC(1);   // expands to func1()
    CALL_FUNC(2);   // expands to func2()
}
/* 
Output
func1
func2
*/





//Building Struct/Class Names
#include <iostream>
struct Point2D { int x=2; };
struct Point3D { int x=3; };

#define SELECT_POINT(d) Point##d

int main() {
    SELECT_POINT(2D) p1;  // becomes Point2D
    SELECT_POINT(3D) p2;  // becomes Point3D

    std::cout << p1.x << " " << p2.x << "\n";
}
/* 
Output
2 3
*/






//Creating Enum Names Dynamically
#include <iostream>
enum ErrorCode {
    ERR_None,
    ERR_FileNotFound,
    ERR_AccessDenied
};
#define ERR_NAME(e) ERR_##e
int main() {
    ErrorCode e = ERR_NAME(FileNotFound); // becomes ERR_FileNotFound
    std::cout << e << "\n";
}
/* 
Output
1
*/








//X-Macros with Token Pasting
#include <iostream>
#define COLORS \
    X(Red)     \
    X(Green)   \
    X(Blue)

#define MAKE_ENUM(name) COLOR_##name,
enum Color {
    #define X(n) MAKE_ENUM(n)
    COLORS
    #undef X
};
int main() {
    std::cout << COLOR_Red << " " << COLOR_Blue << "\n";
}
/* 
Output
0 2
*/




//Creating Getter/Setter Methods Automatically
#include <iostream>
#define GEN_GETTER(var) get_##var() { return var; }

class Test {
  public:
    int value = 5;
    int GEN_GETTER(value); // becomes get_value()
};
int main() {
    Test t;
    std::cout << t.get_value() << "\n";
}

/* 
Output
5
*/





//Concatenating Macro Arguments with Prefix/Suffix
#include <iostream>
#define ADD_PREFIX(x) pre_##x
#define ADD_SUFFIX(x) x##_post

int main() {
    int pre_num = 11;
    int num_post = 22;

    std::cout << ADD_PREFIX(num) << " " << ADD_SUFFIX(num) << "\n";
}
/* 
Output
11 22
*/





//Generating Test Case Names / Logging Keys
#include <iostream>
#define TEST(name) void test_##name()
TEST(alpha) { std::cout << "alpha\n"; }
TEST(beta)  { std::cout << "beta\n"; }
int main() {
    test_alpha();
    test_beta();
}
/* 
Output
alpha
beta
*/

//Generating Template Specializations Automatically
#include <iostream>
template<int N>
void func() { std::cout << "generic\n"; }

template<>
void func<10>() { std::cout << "ten\n"; }

#define CALL(N) func<N>()
int main() {
    CALL(10);
    CALL(20);
}
/* 
Output
ten
generic
*/






✅ H) Variadic Macros

#include <cstdio>
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)
int main() {
    LOG("x=%d, y=%d\n", 10, 20);
}
/* 
Output
x=10, y=20
*/




✅ I) Predefined Macros

#include <iostream>
void test() {
    std::cout << "File: " << __FILE__ << "\n";
    std::cout << "Line: " << __LINE__ << "\n";
    std::cout << "Function: " << __func__ << "\n";
    std::cout << "Date: " << __DATE__ << "\n";
    std::cout << "Time: " << __TIME__ << "\n";
}
int main() {
    test();
}
/* 
Output (example)
File: main.cpp
Line: 6
Function: test
Date: Dec 07 2025
Time: 09:42:10
*/


✅ J) Pragmas (example: #pragma once)
//myheader.h
#pragma once
#include <iostream>
inline void hello() { std::cout << "Hello using pragma once\n"; }

//main.cpp
#include "myheader.h"
#include "myheader.h"
int main() {
    hello();
}
/* 
Output
Hello using pragma once
*/




✅ K) X-Macros (code generation)

#include <iostream>
#define COLORS   \
X(Red)          \
X(Green)        \
X(Blue)

enum Color {
#define X(c) c,
    COLORS
#undef X
};
int main() {
    Color c = Green;
    std::cout << "Enum Value = " << c << "\n";
}
/* 
Output
Enum Value = 1
*/




✅ L) OS / Platform Specific Compilation

#include <iostream>
int main() {
#ifdef _WIN32
    std::cout << "Running on Windows\n";
#elif __linux__
    std::cout << "Running on Linux\n";
#elif __APPLE__
    std::cout << "Running on macOS\n";
#else
    std::cout << "Unknown OS\n";
#endif
}
/* 
Output (example Linux)
Running on Linux
⭐ Real-life Use Cases Examples
*/



1️⃣ Logging System (real-world)

#include <iostream>
#define DEBUG
#ifdef DEBUG
#define LOG(x) std::cout << "[LOG] " << x << "\n"
#else
#define LOG(x)
#endif
int main() {
    LOG("Program started");
    LOG("Value = " << 42);
}
/* 
Output
[LOG] Program started
[LOG] Value = 42
*/


2️⃣ Compile-time Configuration

#include <iostream>
#define USE_FAST 1
int main() {
#if USE_FAST
    std::cout << "Fast mode enabled\n";
#else
    std::cout << "Normal mode enabled\n";
#endif
}
/* 
Output
Fast mode enabled
*/



3️⃣ Assertions

#include <iostream>
#include <cstdlib>
#define ASSERT(x) if(!(x)) { \
    std::cout << "Assertion Failed: " #x "\n"; \
    std::abort(); \
}
int main() {
    ASSERT(5 > 2);
    std::cout << "Program OK\n";
}
/* 
Output
Program OK
*/



4️⃣ Wrapping C APIs

#include <cstdio>
#define C_LOG(msg) puts(msg)
int main() {
    C_LOG("Hello from C API macro");
}
/* 
Output
Hello from C API macro
*/



5️⃣ Variadic Macro (Advanced Logging)

#include <cstdio>
#define LOGF(tag, fmt, ...) \                         //This \ (backslash) macro continues on the next line. Treat both lines as one single macro definition.
    printf("[%s] " fmt "\n", tag, __VA_ARGS__)

int main() {
    LOGF("INFO", "Value = %d", 10);
}
/* 
Output
[INFO] Value = 10


//OR
#define LOGF(tag, fmt, ...) printf("[%s] " fmt "\n", tag, __VA_ARGS__)

*/