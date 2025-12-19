//calculator.hpp

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <gtest/gtest_prod.h>

class Calculator {
private:
    int add(int a, int b);

    FRIEND_TEST(CalcPrivateTest, Add);
};

#endif
