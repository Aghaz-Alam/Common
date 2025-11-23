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