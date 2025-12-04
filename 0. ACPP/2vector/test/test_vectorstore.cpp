#include "vectorstore.h"
#include <gtest/gtest.h>

// ---------- Tests ----------

TEST(VectorStoreTest, SetAndGet) {
    VectorStore<int> v;
    v.set(0, 42);
    EXPECT_EQ(v.get(0), 42);
}

TEST(VectorStoreTest, ResizeOnSet) {
    VectorStore<int> v;
    v.set(5, 99);  // forces resize
    EXPECT_EQ(v.size(), 6);
    EXPECT_EQ(v.get(5), 99);
}

TEST(VectorStoreTest, Remove) {
    VectorStore<int> v;
    v.set(0, 10);
    v.set(1, 20);
    v.remove(0);
    EXPECT_EQ(v.get(0), 20);
}

TEST(VectorStoreTest, Exists) {
    VectorStore<int> v;
    v.set(2, 50);
    EXPECT_TRUE(v.exists(2));
    EXPECT_FALSE(v.exists(10));
}

TEST(VectorStoreTest, Clear) {
    VectorStore<int> v;
    v.set(0, 1);
    v.clear();
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorStoreTest, OutOfRangeGet) {
    VectorStore<int> v;
    EXPECT_THROW(v.get(10), std::out_of_range);
}

// ---------- Main ----------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//g++ test_vectorstore.cpp -lgtest -lpthread -o test_vectorstore ./test_vectorstore

/* 
Output:
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from VectorStoreTest
[ RUN      ] VectorStoreTest.SetAndGet
[       OK ] VectorStoreTest.SetAndGet (0 ms)
[ RUN      ] VectorStoreTest.ResizeOnSet
[       OK ] VectorStoreTest.ResizeOnSet (0 ms)
[ RUN      ] VectorStoreTest.Remove
[       OK ] VectorStoreTest.Remove (0 ms)
[ RUN      ] VectorStoreTest.Exists
[       OK ] VectorStoreTest.Exists (0 ms)
[ RUN      ] VectorStoreTest.Clear
[       OK ] VectorStoreTest.Clear (0 ms)
[ RUN      ] VectorStoreTest.OutOfRangeGet
[       OK ] VectorStoreTest.OutOfRangeGet (0 ms)
[----------] 6 tests from VectorStoreTest (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 6 tests.

*/