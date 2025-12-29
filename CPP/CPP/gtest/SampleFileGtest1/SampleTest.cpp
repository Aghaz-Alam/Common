//SampleTest.cpp

#include "gtest/gtest.h"

int add(int a, int b) {
    return a + b;
}

TEST(AdditionTest, HandlesPositiveNumbers) {
    EXPECT_EQ(5, add(2, 3));
}

TEST(AdditionTest, HandlesNegativeNumbers) {
    EXPECT_EQ(-5, add(-2, -3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
   return 0;
}




//g++ SampleTest.cpp -lgtest -lgtest_main -lpthread -o SampleTest && ./SampleTest