//safe_div_test.cpp

#include <gtest/gtest.h>
#include "safe_div.hpp"

TEST(DivideTest, DiesOnZero) {
    EXPECT_DEATH(divide(10, 0), "");
}



//g++ safe_div_test.cpp safe_div.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest




/* 
safe_div.hpp
safe_div.cpp
safe_div_test.cpp
*/