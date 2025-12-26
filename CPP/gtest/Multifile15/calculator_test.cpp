//calculator_test.cpp


#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalculatorTest, ComputeSum) {
    Calculator c;

    // We DO NOT test add() directly
    // We test observable behavior
    EXPECT_EQ(c.computeSum(), 10);
}



//g++ calculator_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest


//g++ -std=c++17 calculator_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest

/* 
calculator.hpp
calculator.cpp
calculator_test.cpp



Private Logic Tested Indirectly (Simple Case)
Problem: Calculator has private add() logic used internally.
*/