//adder_test.cpp


#include <gtest/gtest.h>
#include "adder.hpp"

template<typename T>
class AdderTest : public ::testing::Test {};

using MyTypes = ::testing::Types<int, double>;

TYPED_TEST_SUITE(AdderTest, MyTypes);

TYPED_TEST(AdderTest, WorksForTypes) {
    Adder<TypeParam> a;
    EXPECT_EQ(a.add(2, 3), 5);
}



//g++ adder_test.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest




/* 
adder.hpp
adder_test.cpp
*/