//secret_test.cpp


#include <gtest/gtest.h>
#include "secret.hpp"

TEST(SecretTest, HiddenLogic) {
    Secret s;
    EXPECT_EQ(s.hidden(5), 50);
}


//g++ secret_test.cpp secret.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest



/* 
secret.hpp
secret.cpp
secret_test.cpp
*/