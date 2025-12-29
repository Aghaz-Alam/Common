//counter_test.cpp

#include <gtest/gtest.h>
#include "counter.hpp"

TEST(CounterTest, First) {
    counter = 0;
    increment();
    EXPECT_EQ(counter, 1);
}

TEST(CounterTest, Second) {
    counter = 0;
    increment();
    EXPECT_EQ(counter, 1);
}


//g++ counter_test.cpp  counter.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest



/* 
counter.hpp
counter.cpp
counter_test.cpp
*/