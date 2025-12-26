pragma✅ 1. #pragma once (Header-include guard)
Status: Widely supported (non-standard but universal)
Purpose: Ensures the file is included only once.

File: header.h
#pragma once
#include <iostream>
void hello() {
    std::cout << "Hello from header!\n";
}

File: main.cpp
#include "header.h"
#include "header.h"     // Included twice but works once

int main() {
    hello();
}
/* 
Output
Hello from header!
*/



✅ 2. #pragma pack (Control struct padding)
Status: Supported in GCC/Clang/MSVC
Purpose: Change alignment of struct members.

//Program
#include <iostream>
#pragma pack(push, 1)   // Align to 1 byte
struct A {
    char c;
    int i;
};
#pragma pack(pop)
struct B {
    char c;
    int i;
};
int main() {
    std::cout << "sizeof(A) = " << sizeof(A) << "\n";
    std::cout << "sizeof(B) = " << sizeof(B) << "\n";
}
/* 
Output (GCC/Clang/MSVC)
sizeof(A) = 5
sizeof(B) = 8
*/


✅ 3. #pragma message (Compile-time messages)

Status: GCC/Clang: #warning / #pragma message
MSVC: fully supports #pragma message

Program
#pragma message("Compiling this file...")

#include <iostream>
int main() {
    std::cout << "Program running...\n";
}
/* 
Compile output (NOT runtime)
Compiling this file...

Program Output:
Program running...
*/



✅ 4. GCC/Clang: #pragma GCC diagnostic (Enable/disable warnings)
Program
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
int test() {
    int unused = 5;     // Warning suppressed
    return 1;
}
#pragma GCC diagnostic pop

int main() {
    std::cout << "Warnings controlled.\n";
}
/* 
Output
Warnings controlled.


Compiler warnings change depending on flags.
 */


✅ 5. MSVC: #pragma warning (Similar to GCC diagnostic)
Program (MSVC)
#include <iostream>
#pragma warning(push)
#pragma warning(disable:4101)  // Disable unused variable warning

int main() {
    int x;  // Normally triggers warning
    std::cout << "MSVC warning disabled.\n";
}
#pragma warning(pop)
/* 
Output
MSVC warning disabled.
*/



✅ 6. GCC: #pragma GCC optimize (Enable optimizations for a function/file)
Program (GCC-only)
#include <iostream>
#pragma GCC optimize("O3")
int fast_function(int x) {
    return x * x;
}

int main() {
    std::cout << fast_function(10) << "\n";
}
/* 
Output
100

(Optimization affects performance, not output.)
*/


✅ 7. #pragma region / #pragma endregion (Code folding)
MSVC + some IDEs (Visual Studio, CLion supports folding)

#include <iostream>
#pragma region Printing
void print() {
    std::cout << "Inside region\n";
}
#pragma endregion

int main() {
    print();
}
/* 
Output
Inside region
*/




✅ 8. #pragma STDC (Rare but Standard C Pragmas)
Pragmas include:
#pragma STDC FENV_ACCESS
#pragma STDC FP_CONTRACT
#pragma STDC CX_LIMITED_RANGE


Example: (may or may not be supported by your compiler)
#pragma STDC FP_CONTRACT ON
#include <iostream>
int main() {
    float a = 1.5f, b = 2.5f;
    float c = a * b;
    std::cout << c << "\n";
}
/* 
Output
3.75

Compiler behavior regarding FP contraction may differ.
*/






✅ 9. OpenMP #pragma omp (Parallelization)
Supported by GCC/Clang/MSVC when enabling OpenMP (-fopenmp)

Program
#include <iostream>
#include <omp.h>
int main() {
    #pragma omp parallel
    {
        std::cout << "Thread " << omp_get_thread_num() << "\n";
    }
}
/* 
Example Output (varies)
Thread 0
Thread 1
Thread 2
Thread 3
*/









✅ 10. #pragma comment(lib, ...) (MSVC only)
Program (Windows/MSVC)
#pragma comment(lib, "user32.lib")
#include <iostream>

int main() {
    std::cout << "Linked with user32.lib\n";
}
/* 
Output
Linked with user32.lib
*/