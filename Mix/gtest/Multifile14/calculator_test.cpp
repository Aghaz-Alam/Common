//calculator_test.cpp


#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalcTest, Compute) {
    Calculator c;
    EXPECT_EQ(c.compute(), 5);
}



//g++ calculator_test.cpp calculator.cpp adder_test.cpp adder.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest


/* 
adder.hpp
adder.cpp
calculator.hpp
calculator.cpp
calculator_test.cpp
adder_test.cpp
*/