//gTestWithoutTestFixture.cpp   with class
#include<iostream>
#include<gtest/gtest.h>
using namespace std;
class MyClass{
      int value;
    public:
      MyClass(int val): value(val){}
      void Increment(int x){
        value += x;
      }  
      int getValue(){
        return value;
      }
};

TEST(TestName, Increment_by_5){
    //Arrange:
    MyClass mc(100);
    
    //Act
    mc.Increment(5);

     //Assert
     ASSERT_EQ(mc.getValue(), 105);

}

TEST(TestName, Increment_by_10){
    //Arrange:
    MyClass mc(100);
    
    //Act
    mc.Increment(10);

     //Assert
     ASSERT_EQ(mc.getValue(), 110);

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
   return 0;
}
/*

g++ gTestWithoutTestFixture.cpp -lgtest -lgtest_main -lpthread -o gTestWithoutTestFixture && ./gTestWithoutTestFixture
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