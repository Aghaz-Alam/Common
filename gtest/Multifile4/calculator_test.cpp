//calculator_test.cpp

#include <gtest/gtest.h>
#include "calculator.hpp"

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
};

TEST_F(CalculatorTest, Add) {
    EXPECT_EQ(calc.add(5, 5), 10);
}



//g++ calculator_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest
//./gTest



//g++ calculator_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest
