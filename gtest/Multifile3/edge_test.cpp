#include <gtest/gtest.h>
#include "add.hpp"

TEST(AddTest, Zero) {
    EXPECT_EQ(add(0, 0), 0);
}


//g++ add_test.cpp edge_test.cpp add.cpp -lgtest -lgtest_main -lpthread -o gTest
//./gTest




//g++ add_test.cpp edge_test.cpp add.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest
