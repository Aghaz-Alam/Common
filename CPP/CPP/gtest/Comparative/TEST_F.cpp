
//without member
#include <gtest/gtest.h>
// Function under test
int isEven(int n) {
    return (n % 2 == 0);
}
// Test Fixture (NO parameters)
class EvenTestNoMember : public ::testing::Test {
};
// Fixed tests
TEST_F(EvenTestNoMember, EvenNumber) {
    EXPECT_TRUE(isEven(4));
}
TEST_F(EvenTestNoMember, OddNumber) {
    EXPECT_FALSE(isEven(5));
}
// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   


/* 
//with public member
#include <gtest/gtest.h>
// Function under test
int isEven(int n) {
    return (n % 2 == 0);
}
// Test Fixture (NO parameters)
class EvenTestPublic : public ::testing::Test {
public:
    int value;
};
// Fixed tests
TEST_F(EvenTestPublic, EvenNumber) {
    value = 4;
    EXPECT_TRUE(isEven(value));
}   
TEST_F(EvenTestPublic, OddNumber) {
    value = 5;
    EXPECT_FALSE(isEven(value));
}
// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

 */



/* 
//with protected member
#include <gtest/gtest.h>
// Function under test
int isEven(int n) {
    return (n % 2 == 0);
}

// Test Fixture (NO parameters)
class EvenTest : public ::testing::Test {
protected:
    int value;
};

// Fixed tests
TEST_F(EvenTest, EvenNumber) {
    value = 4;
    EXPECT_TRUE(isEven(value));
}

TEST_F(EvenTest, OddNumber) {
    value = 5;
    EXPECT_FALSE(isEven(value));
}

// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

 */

/* 
 //with private member
#include <gtest/gtest.h>
// Function under test
int isEven(int n) {
    return (n % 2 == 0);
}
// Test Fixture (NO parameters)
class EvenTestPrivate : public ::testing::Test {
private:
    int value;
protected:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
};          
// Fixed tests
TEST_F(EvenTestPrivate, EvenNumber) {
    setValue(4);
    EXPECT_TRUE(isEven(getValue()));
}   
TEST_F(EvenTestPrivate, OddNumber) {
    setValue(5);
    EXPECT_FALSE(isEven(getValue()));
}
// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   

 */
