#include <iostream>        // For standard I/O operations
#include <vector>          // Included for demonstration (not strictly needed)
#include <gtest/gtest.h>   // Google Test framework
#include <gmock/gmock.h>   // Google Mock framework

// --- Namespace Usings ---
using namespace std;              // Using the standard C++ namespace
using ::testing::AtLeast;         // For specifying minimum call expectations
using ::testing::Return;          // For defining mock return values
using ::testing::_;               // Wildcard matcher for mock function arguments

// ============================================================================
//                         Base Class Definition
// ============================================================================
class DataBaseConnect {
  public:
    // Virtual function for login, simulates database login behavior
    virtual bool login(string username, string password) { 
        return true; 
    }

    // Virtual function for logout, simulates database logout behavior
    virtual bool logout(string username) { 
        return true; 
    }

    // Virtual function for fetching records from DB, returns dummy -1
    virtual int fetchRecord() { 
        return -1; 
    }

    // Virtual function for a second login mechanism (used in Program 1 & 2)
    virtual bool login2(string username, string password) {
        return true;
    }
};

// ============================================================================
//                         Mock Class Definition
// ============================================================================
// This mock class simulates the behavior of DataBaseConnect using Google Mock.
class MockDB : public DataBaseConnect {
  public:
    // Mock the fetchRecord() method with no parameters, returning int
    MOCK_METHOD0(fetchRecord, int());

    // Mock the login() method with 2 parameters: username and password
    MOCK_METHOD2(login, bool(string username, string password));

    // Mock the logout() method with 1 parameter: username
    MOCK_METHOD1(logout, bool(string username));

    // Mock the login2() method with 2 parameters: username and password
    MOCK_METHOD2(login2, bool(string username, string password));
};

// ============================================================================
//                         Class Under Test
// ============================================================================
// MyDatabase class depends on DataBaseConnect (Dependency Injection)
class MyDatabase {
    DataBaseConnect &dbc;   // Reference to a DataBaseConnect (can be real or mock)
  public:
    // Constructor initializes dbc reference
    MyDatabase(DataBaseConnect &_dbc) : dbc(_dbc) {}

    // Init() function simulates connecting to a database and checking credentials
    int Init(string username, string password) {
        
        // // Case 1: First login attempt
            if (dbc.login(username, password) != true) {
                // Second attempt if first fails
                if (dbc.login(username, password) != true) {
                    cout << "DB FAILURE 2nd TIME" << endl; // Output message for failure
                    return -1; // Return -1 if login failed twice
                } else {
                    cout << "DB SUCCESS" << endl; // Output message for success
                    return 1; // Return 1 for success
                }
            } else {
                // If login succeeds first time, use secondary login (login2)
                return dbc.login2(username, password);
            }

        // Case 2: directly call login2
        return dbc.login2(username, password);
    }
};

// ============================================================================
//                         Google Test Unit Test
// ============================================================================
// This test checks that MyDatabase::Init() works correctly with mock DB calls
TEST(MyDBTest, LoginTest) {
    // Arrange: Create mock DB and MyDatabase object using dependency injection
    MockDB mdb;
    MyDatabase db(mdb);

    // Expect the login() function to be called at least once
    EXPECT_CALL(mdb, login(_, _))
        .Times(AtLeast(1))           // Must be called one or more times
        .WillRepeatedly(Return(true)); // Always return true for login()

    // Expect the login2() function to return true when called
    EXPECT_CALL(mdb, login2(_, _))
        .WillRepeatedly(Return(true)); // Always return true for login2()

    // Act: Call Init() with test credentials
    int retValue = db.Init("Terminator", "I'll be Back");

    // Assert: Check that Init() returned success (1)
    EXPECT_EQ(retValue, 1);
}

// ============================================================================
//                         Main Entry Point
// ============================================================================
// This main function runs all Google Tests in the file
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Initialize Google Test framework
    return RUN_ALL_TESTS();                  // Run all tests and return results
}
/*



//g++ gMock.cpp -lgtest -lgtest_main -lpthread -o gMock && ./gMock


//g++ gMock.cpp -std=c++17 -lgtest -lgmock -pthread -o gMock && ./gMock

*/