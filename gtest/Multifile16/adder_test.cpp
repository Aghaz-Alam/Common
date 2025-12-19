//adder_test.cpp

#include <gtest/gtest.h>
#include "adder.hpp"

TEST(AdderTest, AddNumbers) {
    Adder a;
    EXPECT_EQ(a.add(5, 5), 10);
}

TEST(AdderTest, AddNegative) {
    Adder a;
    EXPECT_EQ(a.add(-2, 3), 1);
}
