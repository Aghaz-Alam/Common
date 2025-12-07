1. Gtest, coverity
2. Usage of git , gerrit
3. static, dyn libs, executables.
4. Debugging - gdb, using tools like addr2line, nm, readelf etc
5. Given a program identify what UT can be written, what all does it cover ( boundary conditions etc)




1. GTest & Coverity
Google Test (GTest)
Purpose: Unit testing C++ code. It allows checking if individual functions behave as expected.

Example: Testing a simple math function.
// math_functions.h
#pragma once
int add(int a, int b) {
    return a + b;
}
int divide(int a, int b) {
    if(b == 0) throw std::invalid_argument("Divide by zero");
    return a / b;
}

// test_math.cpp
#include <gtest/gtest.h>
#include "math_functions.h"
// Test add function
TEST(MathTest, AddTest) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

// Test divide function
TEST(MathTest, DivideTest) {
    EXPECT_EQ(divide(10, 2), 5);
    EXPECT_THROW(divide(5, 0), std::invalid_argument);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Output (when running ./test_math):

[ RUN      ] MathTest.AddTest
[       OK ] MathTest.AddTest
[ RUN      ] MathTest.DivideTest
[       OK ] MathTest.DivideTest
[==========] 2 tests ran. 0 failed.
*/

✅ Explanation:
EXPECT_EQ checks expected vs actual.
EXPECT_THROW checks exception.
Covers normal and boundary cases (divide by zero).






Coverity
Purpose: Static code analysis tool. Detects bugs, memory leaks, and undefined behaviors without running the program.

Example of a bug detected by Coverity:
#include <iostream>
void buggyFunction() {
    int* ptr = new int[5];
    ptr[10] = 42; // Out-of-bounds write
    delete[] ptr;
}
int main() {
    buggyFunction();
    return 0;
}
/* 
Coverity will report:
CID 12345: Out-of-bounds access (BUFFER_OVERFLOW)
ptr[10] access is out of bounds of allocated memory (5 elements)
*/

✅ Explanation:
Coverity is for static analysis.
Catches issues like memory leaks, null pointer dereference, uninitialized variables, buffer overflows.







2. Usage of Git & Gerrit
Git
Purpose: Version control.

Example Commands:
git init                  # Initialize repo
git add .                 # Stage files
git commit -m "Initial"   # Commit files
git log                   # View history
git checkout -b feature   # Create a new branch
git merge feature         # Merge feature branch


✅ Explanation:
Keeps track of changes.
Supports branching, merging, and collaboration.

Gerrit
Purpose: Code review tool on top of Git.

Workflow:
Make changes in a branch.
Push to Gerrit for review:
    git push origin HEAD:refs/for/master
Reviewer comments → approve or reject.
Once approved → merged into main branch.

✅ Explanation:
Ensures peer review before merging code.
Works well with CI/CD pipelines.




3. Static Libraries, Dynamic Libraries, Executables
Static Library (.a / .lib)
Compiled at link-time.
Included in executable → no dependency at runtime.

// mylib.h
#pragma once
int square(int x);

// mylib.cpp
#include "mylib.h"
int square(int x) { return x * x; }

// main.cpp
#include <iostream>
#include "mylib.h"
int main() {
    std::cout << "Square of 5: " << square(5) << "\n";
}

Commands:
g++ -c mylib.cpp
ar rcs libmylib.a mylib.o
g++ main.cpp -L. -lmylib -o main
./main
/* 
Output:
Square of 5: 25
*/


Dynamic Library (.so / .dll)
Linked at runtime.
Smaller executable, can update library without recompiling.
   g++ -fPIC -shared -o libmylib.so mylib.cpp
   g++ main.cpp -L. -lmylib -Wl,-rpath=. -o main
   ./main

/* 
Output: Same as static library.
*/

Executable
Final runnable program (main in examples).
Can link static or dynamic libraries.




4. Debugging Tools (gdb, addr2line, nm, readelf)
gdb (Debugger)
g++ -g main.cpp -o main
gdb ./main


Commands inside gdb:
break main       # Set breakpoint
run              # Run program
next             # Step over
print x          # Print variable
backtrace        # Show call stack

addr2line
Maps addresses to source code lines.

./main
# Segmentation fault at 0x400abc
addr2line -e main 0x400abc

nm
Lists symbols (functions/variables) in object/executable.
nm main

readelf
Reads ELF file headers (Linux).
readelf -h main
readelf -s main

✅ Explanation:
Together, these tools help debug crashes, inspect binaries, and analyze symbols.





5. Writing Unit Tests (UT)
Given a program:
int factorial(int n) {
    if(n < 0) throw std::invalid_argument("Negative!");
    if(n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

Unit Tests to Cover:
TEST(FactorialTest, PositiveNumbers) {
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(1), 1);
}
TEST(FactorialTest, Zero) {
    EXPECT_EQ(factorial(0), 1);
}
TEST(FactorialTest, NegativeNumber) {
    EXPECT_THROW(factorial(-1), std::invalid_argument);
}


✅ Coverage:
Boundary conditions: 0, 1
Normal conditions: 5, 10
Exceptional conditions: negative numbers

✅ Summary Table
| Topic        | Purpose                  | Example                                |
| ------------ | ------------------------ | -------------------------------------- |
| GTest        | Unit testing             | `EXPECT_EQ(add(2,3),5)`                |
| Coverity     | Static analysis          | Out-of-bounds detection                |
| Git/Gerrit   | Version control & review | `git push origin HEAD:refs/for/master` |
| Libraries    | Code reuse               | `.a` static, `.so` dynamic             |
| Debugging    | Debug & analyze          | `gdb`, `addr2line`, `nm`, `readelf`    |
| Unit Testing | Functional coverage      | Boundary, normal, exception cases      |
