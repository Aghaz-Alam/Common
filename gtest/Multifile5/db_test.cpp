//db_test.cpp

#include <gtest/gtest.h>
#include "db.hpp"

class DatabaseTest : public ::testing::Test {
protected:
    Database db;

    void SetUp() override {
        db.connect();
    }
};

TEST_F(DatabaseTest, ConnectionEstablished) {
    EXPECT_TRUE(db.isConnected());
}


//g++ db_test.cpp db.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest
