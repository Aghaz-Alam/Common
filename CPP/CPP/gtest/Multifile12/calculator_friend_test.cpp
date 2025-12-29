//calculator_friend_test.cpp


#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalcPrivateTest, Add) {
    Calculator c;
    EXPECT_EQ(c.add(3, 4), 7);
}



//g++ calculator_friend_test.cpp calculator.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest




/* 
calculator.hpp
calculator.cpp
calculator_private_test.cpp
*/