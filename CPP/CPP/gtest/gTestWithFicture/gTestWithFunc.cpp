
//gTestWithFunc.cpp
#include<iostream>
#include<gtest/gtest.h>
using namespace std;
TEST(TestName, Increment_by_5){
    //Arrange
    int value = 100;
    int increment = 5;

    //Act
    value +=increment;

    //Assert
    ASSERT_EQ(value, 105);
}

TEST(TestName, Increment_by_10){
    //Arrange
    int value = 100;
    int increment = 10;

    //Act
    value +=increment;

    //Assert
    ASSERT_EQ(value, 110);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
   return 0;
}

/*
g++ gTestWithFunc.cpp -lgtest -lgtest_main -lpthread -o gTestWithFunc && ./gTestWithFunc

[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from TestName
[ RUN      ] TestName.Increment_by_5
[       OK ] TestName.Increment_by_5 (0 ms)
[ RUN      ] TestName.Increment_by_10
[       OK ] TestName.Increment_by_10 (0 ms)
[----------] 2 tests from TestName (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
*/