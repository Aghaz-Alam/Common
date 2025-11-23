//Sample_Test.cpp

// #include <gtest/gtest.h>
// #include "Math_Functions.h" // Use quotes for your local header

// // No need for a custom main if you link with libgtest_main.a
// // Remove the main function from this file.

// TEST(AdditionTest, Addition) {
//     EXPECT_EQ(5, Add(2, 3));
// }

// TEST(AdditionTest, Multiplication) {
//     EXPECT_EQ(6, Multiply(2, 3));
// }



// //dell@dell-Latitude-5420:~/Music/App4$ g++ Sample_Test.cpp Math_Functions.cpp -o Sample_Test -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main -lpthread
// //dell@dell-Latitude-5420:~/Music/App4$ ./Sample_Test














//test fixture
#include <gtest/gtest.h>
#include "Math_Functions.h" // Assuming this header declares Add() and Multiply()

// 1. Define the test fixture class
class MathFunctionsTest : public ::testing::Test {
  protected:
    // Declare objects or variables to be used by all tests
    int num1;
    int num2;

    // SetUp() is called immediately before each test is run
    void SetUp() override {
        num1 = 2;
        num2 = 3;
    }

    // TearDown() is called immediately after each test finishes
    // void TearDown() override {
    //     // Optional cleanup code
    // }
};

// 2. Use TEST_F() to write tests that share the fixture data/methods
TEST_F(MathFunctionsTest, Addition) {
    // Access fixture members directly
    EXPECT_EQ(5, Add(num1, num2));
}

TEST_F(MathFunctionsTest, Multiplication) {
    // Access fixture members directly
    EXPECT_EQ(6, Multiply(num1, num2));
}

// Note: No need for a custom main() if you link with gtest_main library









/*
1. The Fixture Class (Deriving from ::testing::Test)
You define a C++ class that inherits publicly from the base class ::testing::Test. 
This inheritance gives your class access to GTest's internal mechanisms.


class DatabaseTest : public ::testing::Test {
    // ... members and methods go here ...
};





2. Shared Data Members
Any data or objects that all tests in the suite need access to should be declared as members of this class. 
It is conventional to place these in the protected section to allow access by derived test functions while maintaining encapsulation.


class DatabaseTest : public ::testing::Test {
  protected:
    // Shared resource handle
    DatabaseConnection* db_conn;
    // ... other shared variables ...
};




3. Setup and Teardown Methods
Google Test provides two special member functions that the test runner automatically calls:
Method	                    Timing	P                           urpose
void SetUp() override	    Before each individual TEST_F.	    Initializes shared resources, sets initial states.
void TearDown() override	After each individual TEST_F.	    Cleans up resources, frees memory, closes connections.

These methods ensure that every single test function operates on a fresh instance of the fixture class.

lass DatabaseTest : public ::testing::Test {
  protected:
    DatabaseConnection* db_conn;

    void SetUp() override {
        // Connect to the actual database before *each* test starts
        db_conn = new DatabaseConnection("test_db");
        db_conn->connect();
    }

    void TearDown() override {
        // Disconnect and clean up after *each* test finishes
        db_conn->disconnect();
        delete db_conn;
    }
};



4. The TEST_F() Macro
Instead of using the standard TEST() macro, you use TEST_F() to associate a test with a 
specific fixture class.

TEST_F(DatabaseTest, CanConnect) {
    // We can access db_conn directly here
    ASSERT_TRUE(db_conn->isConnected());
}

TEST_F(DatabaseTest, CanQuery) {
    // This test gets its *own* fresh connection via SetUp()
    ASSERT_EQ(db_conn->query("SELECT COUNT(*) FROM users;"), 10);
}

Execution Flow in Detail
When you run your test executable, Google Test orchestrates the following sequence for a suite with two TEST_F tests:
Step	A                   ction	Description
Test 1 Execution		
1	new DatabaseTest()	    GTest instantiates a fresh object of your fixture class.
2	SetUp()	                Calls the setup function defined in your fixture.
3	TEST_F(..., CanConnect)	Executes the first test function body.
4	TearDown()	            Calls the teardown function.
5	delete DatabaseTest()	Destroys the first instance.


Test 2 Execution		
6	new DatabaseTest()	    GTest instantiates a second, fresh object.
7	SetUp()	                Calls setup again (ensuring a clean state).
8	TEST_F(..., CanQuery)	Executes the second test function body.
9	TearDown()	            Calls teardown again.
10	delete DatabaseTest()	Destroys the second instance.

This execution model guarantees strong test isolation; 
if the first test modified the database connection object in some unexpected way, 
that modification is immediately discarded before the second test runs.




Alternative Setup/Teardown Methods
While SetUp() and TearDown() are standard, you can also use the class constructor and 
destructor for initialization and cleanup, respectively:

class MyFixture : public ::testing::Test {
  protected:
    MyFixture() {
        // Constructor equivalent to SetUp() for simple initialization
    }

    ~MyFixture() override {
        // Destructor equivalent to TearDown() for simple cleanup
    }
    // ... SetUp() and TearDown() are still available for more complex scenarios
};

*/