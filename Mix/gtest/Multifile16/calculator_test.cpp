//calculator_test.cpp

#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalculatorTest, Compute) {
    Calculator c;
    EXPECT_EQ(c.compute(), 10);
}



//g++ adder_test.cpp calculator_test.cpp adder.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest
