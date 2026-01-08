// TEST_P.cpp
#include <gtest/gtest.h>

// SAME function
int isEven(int n) {
    return (n % 2 == 0);
}

// Parameterized Fixture
class EvenParamTest : public ::testing::TestWithParam<int> {
};

// SAME test logic, different inputs
TEST_P(EvenParamTest, CheckEvenOdd) {
    int value = GetParam();

    if (value % 2 == 0)
        EXPECT_TRUE(isEven(value));
    else
        EXPECT_FALSE(isEven(value));
}

// Input values
INSTANTIATE_TEST_SUITE_P(
    EvenOddTests,
    EvenParamTest,
    ::testing::Values(2, 3, 4, 5, 10)
);

// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

