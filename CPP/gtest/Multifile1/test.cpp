#include <gtest/gtest.h>
#include "add.hpp"

TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(10, 20), 30);
}

TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(add(-10, -20), -30);
}


//g++ test.cpp add.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest



/* 
add.hpp
add.cpp
test.cpp
*/