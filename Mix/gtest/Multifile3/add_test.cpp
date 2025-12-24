#include <gtest/gtest.h>
#include "add.hpp"

TEST(AddTest, Normal) {
    EXPECT_EQ(add(2, 3), 5);
}
