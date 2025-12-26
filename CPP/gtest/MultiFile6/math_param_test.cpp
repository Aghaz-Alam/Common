//math_param_test.cpp

#include <gtest/gtest.h>
#include "math.hpp"

class SquareTest : public ::testing::TestWithParam<int> {};

TEST_P(SquareTest, WorksForMultipleInputs) {
    int val = GetParam();
    EXPECT_EQ(square(val), val * val);
}

INSTANTIATE_TEST_SUITE_P(
    SquareValues,
    SquareTest,
    ::testing::Values(-2, -1, 0, 2, 5)
);



//g++ math_param_test.cpp math.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest




/* 
math.hpp
math.cpp
math_param_test.cpp
*/