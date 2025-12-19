//calculator_test.cpp

#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalcTest, Compute) {
    Calculator c;
    EXPECT_EQ(c.compute(), 5);
}





//g++ calculator_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest
