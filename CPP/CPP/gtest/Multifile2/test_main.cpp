#include <gtest/gtest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



//g++ test.cpp test_main.cpp add.cpp -lgtest -lpthread -o gTest && ./gTest



/* 
add.hpp
add.cpp
test.cpp
test_main.cpp
*/