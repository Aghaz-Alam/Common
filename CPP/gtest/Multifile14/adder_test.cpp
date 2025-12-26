//adder_test.cpp

#include <gtest/gtest.h>
#include "adder.hpp"

TEST(AdderTest, Add) {
    Adder a;
    EXPECT_EQ(a.add(3, 4), 7);
}


//g++ calculator_test.cpp calculator.cpp adder_test.cpp adder.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest