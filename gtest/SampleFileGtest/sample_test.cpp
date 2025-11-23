// sample_test.cpp
#include <gtest/gtest.h>

TEST(MathTest, TwoPlusTwoEqualsFour) {
    EXPECT_EQ(2 + 2, 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  return 0;
}



//g++ sample_test.cpp -lgtest -lgtest_main -lpthread -o sample_test && ./sample_test   ==success
//g++ sample_test.cpp -lgtest -lgtest_main -lpthread -o sample_test ./sample_test      ==Compile time error


//g++ -std=c++17 sample_test.cpp -lgtest -lgtest_main -lpthread -o sample_test && ./sample_test
//g++ -std=c++20 sample_test.cpp -lgtest -lgtest_main -lpthread -o sample_test && ./sample_test

