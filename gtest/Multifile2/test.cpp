#include <gtest/gtest.h>
#include "add.hpp"

TEST(AddTest, Basic) {
    ASSERT_EQ(add(3, 4), 7);
}
