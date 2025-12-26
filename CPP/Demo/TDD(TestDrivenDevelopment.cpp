1️⃣ What is TDD?
TDD (Test-Driven Development) is a software development approach where you:
Write a test first that specifies the behavior you want.
Write the minimal code to pass that test.
Refactor the code while keeping the test passing.
Key idea: “Red → Green → Refactor”
Red: Write a failing test (test fails).
Green: Write code to pass the test.
Refactor: Improve code without breaking the test.
This ensures your code is always tested, correct, and maintainable.

2️⃣ Example in C++
We’ll write a simple Calculator class that adds and multiplies numbers.
We’ll use Google Test (gtest) framework — the most popular C++ testing framework.

Step 1: Write the failing test (Red)
#include <gtest/gtest.h>
#include "Calculator.h"  // We'll create this later
TEST(CalculatorTest, AddTest) {
    Calculator calc;
    EXPECT_EQ(calc.add(2, 3), 5);
    EXPECT_EQ(calc.add(-1, 1), 0);
}
TEST(CalculatorTest, MultiplyTest) {
    Calculator calc;
    EXPECT_EQ(calc.multiply(2, 3), 6);
    EXPECT_EQ(calc.multiply(-2, 3), -6);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

This fails initially because Calculator doesn’t exist yet.

Step 2: Write minimal code to pass the test (Green)
Create Calculator.h:

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
  public:
    int add(int a, int b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }
};
#endif


Now, running the test:

$ ./test_calculator
[ RUN      ] CalculatorTest.AddTest
[       OK ] CalculatorTest.AddTest (0 ms)
[ RUN      ] CalculatorTest.MultiplyTest
[       OK ] CalculatorTest.MultiplyTest (0 ms)


✅ All tests pass.

Step 3: Refactor if needed

If we wanted, we could later improve Calculator (e.g., support floating points) without breaking existing tests, because tests ensure correctness.

3️⃣ Advantages of TDD

Ensures code correctness from day one.

Forces modular, testable design.

Reduces bugs in production.

Makes refactoring safe.