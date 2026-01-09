// gTest Parameterized without Class
/*
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
/* 
Output:
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from EvenParamTest/0, where TypeParam = int
[ RUN      ] EvenParamTest/0.CheckEvenOdd/0
[       OK ] EvenParamTest/0.CheckEvenOdd/0 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/1
[       OK ] EvenParamTest/0.CheckEvenOdd/1 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/2
[       OK ] EvenParamTest/0.CheckEvenOdd/2 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/3
[       OK ] EvenParamTest/0.CheckEvenOdd/3 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/4
[       OK ] EvenParamTest/0.CheckEvenOdd/4 (0 ms)
[----------] 5 tests from EvenParamTest/0 (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.   

g++ TEST_P.cpp -lgtest -lgtest_main -lpthread -o gTestParameterized && ./gTestParameterized
*/






//gTest Parameterized With Class
#include <gtest/gtest.h>
#include <iostream>
using namespace std;
class Sample {
private:
    int value;
public:
    void SetValue(int v) { value = v; }
    int getValue() const { return value; }
    bool isEven() const { return (value % 2 == 0); }    
};  
// Test Parameterized Fixture
class EvenParamTest : public ::testing::TestWithParam<int> {
protected:
    Sample sample;
};
// SAME test logic, different inputs
TEST_P(EvenParamTest, CheckEvenOdd) {
    int val = GetParam();
    sample.SetValue(val);       
    if (val % 2 == 0)
        EXPECT_TRUE(sample.isEven());
    else
        EXPECT_FALSE(sample.isEven());
}
// Input values ---//MACRO
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
/* 
Output:
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from EvenParamTest/0, where TypeParam = int
[ RUN      ] EvenParamTest/0.CheckEvenOdd/0
[       OK ] EvenParamTest/0.CheckEvenOdd/0 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/1
[       OK ] EvenParamTest/0.CheckEvenOdd/1 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/2
[       OK ] EvenParamTest/0.CheckEvenOdd/2 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/3
[       OK ] EvenParamTest/0.CheckEvenOdd/3 (0 ms)
[ RUN      ] EvenParamTest/0.CheckEvenOdd/4
[       OK ] EvenParamTest/0.CheckEvenOdd/4 (0 ms)
[----------] 5 tests from EvenParamTest/0 (0 ms total)  

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests.           

g++ TEST_P.cpp -lgtest -lgtest_main -lpthread -o gTestParameterizedWithClass && ./gTestParameterizedWithClass
*/




