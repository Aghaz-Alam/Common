//gTestWithTestFixture.cpp   with class
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

struct MyClassTest: public testing::Test{
    MyClass *mc;
    void SetUp(){                      //S(1st letter) must be capital letter in test fixture class method name
        cout<<"Alive!"<<endl;
        mc = new MyClass(100);
    }
    void TearDown(){                  //T(1st letter) must be capital letter in test fixture class method name
        cout<<"Dead!"<<endl;
        delete mc;
    }
};

TEST_F(MyClassTest, Increment_by_5){
      //Act
    mc->Increment(5);

     //Assert
     ASSERT_EQ(mc->getValue(), 105);

}

TEST_F(MyClassTest, Increment_by_10){
     //Act
    mc->Increment(10);

     //Assert
     ASSERT_EQ(mc->getValue(), 110);

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
   return 0;
}
/*

g++ gTestWithTestFixture.cpp -lgtest -lgtest_main -lpthread -o gTestWithTestFixture && ./gTestWithTestFixture
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from MyClassTest
[ RUN      ] MyClassTest.Increment_by_5
Alive!
Dead!
[       OK ] MyClassTest.Increment_by_5 (0 ms)
[ RUN      ] MyClassTest.Increment_by_10
Alive!
Dead!
[       OK ] MyClassTest.Increment_by_10 (0 ms)
[----------] 2 tests from MyClassTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.

*/