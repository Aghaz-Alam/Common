/*1. Mocking without Deriving from a Class

In gMock, you can mock interfaces or pure virtual classes without needing to derive a new mock manually; 
you just define a mock class using MOCK_METHOD.
*/
//Example
//* 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

// Interface
class Calculator {
  public:
    virtual ~Calculator() = default;
    virtual int Add(int a, int b) = 0;
};

// Mock class (no manual derivation required)
class MockCalculator : public Calculator {
  public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
};

TEST(MockWithoutDeriveTest, AddFunction) {
    MockCalculator mock;
    EXPECT_CALL(mock, Add(3, 4)).WillOnce(Return(7));

    EXPECT_EQ(mock.Add(3, 4), 7);
}

/*
Explanation:
We don’t manually override or derive anything beyond declaring the mock with MOCK_METHOD.
EXPECT_CALL defines behavior directly.
 */


/* 
2. Invoking Original and Other Implementations
You can delegate a mock method to call the real implementation or another instance’s implementation using Invoke.
*/

//Example 
//* 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Invoke;

// Real class
class Math {
  public:
    virtual ~Math() = default;
    virtual int Multiply(int a, int b) { return a * b; }
};

// Mock class
class MockMath : public Math {
  public:
    MOCK_METHOD(int, Multiply, (int a, int b), (override));
};

TEST(InvokeOriginalTest, CallsRealMultiply) {
    MockMath mock;

    // Delegate to real implementation
    ON_CALL(mock, Multiply).WillByDefault(Invoke(&mock, &Math::Multiply));

    EXPECT_EQ(mock.Multiply(3, 5), 15);
}

/*
Explanation:
Invoke(&mock, &Math::Multiply) calls the real Multiply even though it’s mocked.
This allows partial mocking.
 */



 /* 
 3. Setting Default Actions
ON_CALL lets you define default behavior for mock methods, which will be used unless overridden by EXPECT_CALL.
 */


 //Example
//* 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

// Interface
class Network {
  public:
    virtual ~Network() = default;
    virtual bool Connect() = 0;
};

// Mock class
class MockNetwork : public Network {
  public:
    MOCK_METHOD(bool, Connect, (), (override));
};

TEST(DefaultActionTest, UsesDefaultAction) {
    MockNetwork mock;

    // Default action
    ON_CALL(mock, Connect).WillByDefault(Return(true));

    // Even without EXPECT_CALL, it works
    EXPECT_TRUE(mock.Connect());

    // You can still override
    EXPECT_CALL(mock, Connect).WillOnce(Return(false));
    EXPECT_FALSE(mock.Connect());
}

/*
xplanation:
ON_CALL defines default behavior.
EXPECT_CALL overrides for specific test cases.
 */





/*  4. Performing Multiple Actions

You can perform multiple actions in sequence using DoAll() — e.g., 
set a variable, print, and then return a value. */

//Example
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

// Interface
class Service {
  public:
    virtual ~Service() = default;
    virtual bool GetData(int id, std::string& out) = 0;
};

// Mock
class MockService : public Service {
  public:
    MOCK_METHOD(bool, GetData, (int id, std::string& out), (override));
};

TEST(MultipleActionsTest, PerformsSeveralActions) {
    MockService mock;
    std::string output;

    EXPECT_CALL(mock, GetData(_, _))
        .WillOnce(DoAll(
            SetArgReferee<1>("Mocked Data"), // set output arg
            Return(true)                     // return value
        ));

    EXPECT_TRUE(mock.GetData(1, output));
    EXPECT_EQ(output, "Mocked Data");
}
/*
Explanation:
DoAll executes multiple actions in sequence.
Here it sets an argument and then returns a value.
*/

