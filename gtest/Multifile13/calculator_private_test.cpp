//calculator_private_test.cpp


#include <gtest/gtest.h>
#include "calculator.hpp"

class CalculatorTestHelper {
public:
    static int callAdd(Calculator& c, int a, int b) {
        return c.add(a, b);
    }
};

TEST(CalcPrivateTest, Add) {
    Calculator c;
    EXPECT_EQ(CalculatorTestHelper::callAdd(c, 1, 2), 3);
}



//g++ calculator_private_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest




/* 
calculator.hpp
calculator.cpp
calculator_private_test.cpp
*/