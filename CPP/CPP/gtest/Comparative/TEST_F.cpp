
//without member, gtest fixture with no member variables, with function
/*
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
Output:
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestNoMember
[ RUN      ] EvenTestNoMember.EvenNumber
[       OK ] EvenTestNoMember.EvenNumber (0 ms)
[ RUN      ] EvenTestNoMember.OddNumber
[       OK ] EvenTestNoMember.OddNumber (0 ms)
[----------] 2 tests from EvenTestNoMember (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.


g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithFunc && ./gTestWithFunc
*/








//without member, gtest fixture with no member variables, with class method
/*
#include <gtest/gtest.h>
// Function under test
// Test Fixture (NO parameters) 
class EvenTestNoMember : public ::testing::Test {
public:
    static bool isEven(int n) {
        return (n % 2 == 0);
    }
};

TEST_F(EvenTestNoMember, EvenNumber) {
    EXPECT_TRUE(isEven(4));
}

TEST_F(EvenTestNoMember, OddNumber) {
    EXPECT_FALSE(isEven(5));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   
/* 
Output: 
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestNoMember
[ RUN      ] EvenTestNoMember.EvenNumber
[       OK ] EvenTestNoMember.EvenNumber (0 ms)
[ RUN      ] EvenTestNoMember.OddNumber
[       OK ] EvenTestNoMember.OddNumber (0 ms)
[----------] 2 tests from EvenTestNoMember (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
*/



//without member, gtest fixture with no member variables, with class method
/*
#include <gtest/gtest.h>
#include <iostream>
class EvenTest{
public:
    static bool isEven(int n) {
        return (n % 2 == 0);
    }
};
// Test Fixture (NO parameters)
class EvenTestNoMember : public ::testing::Test {
};
// Fixed tests
TEST_F(EvenTestNoMember, EvenNumber) {
    EXPECT_TRUE(EvenTest::isEven(4));
}       
TEST_F(EvenTestNoMember, OddNumber) {
    EXPECT_FALSE(EvenTest::isEven(5));
}
// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   
/* 
Output: 
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestNoMember
[ RUN      ] EvenTestNoMember.EvenNumber
[       OK ] EvenTestNoMember.EvenNumber (0 ms)
[ RUN      ] EvenTestNoMember.OddNumber
[       OK ] EvenTestNoMember.OddNumber (0 ms)
[----------] 2 tests from EvenTestNoMember (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithClassMethod && ./gTestWithClassMethod
*/



//without member, gtest fixture with no member variables, with class method and object
/*
#include <gtest/gtest.h>
#include <iostream>

class Sample {
public:
    bool fun(int n) {
        std::cout << n << std::endl;
        return (n % 2 == 0);
    }
};

class TestNoMember : public ::testing::Test {
protected:
    Sample s;
};

TEST_F(TestNoMember, ENumber) {
    int val = 4;
    EXPECT_TRUE(s.fun(val));
}

TEST_F(TestNoMember, ONumber) {
    int val = 5;
    EXPECT_FALSE(s.fun(val));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Output: 
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from TestNoMember
[ RUN      ] TestNoMember.ENumber
4
[       OK ] TestNoMember.ENumber (0 ms)
[ RUN      ] TestNoMember.ONumber
5
[       OK ] TestNoMember.ONumber (0 ms)
[----------] 2 tests from TestNoMember (0 ms total) 

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.       

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestNoMemberWithClass1 && ./gTestNoMemberWithClass1

*/










//with public member
/* 
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
/* 
Output:
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestPublic
[ RUN      ] EvenTestPublic.EvenNumber
[       OK ] EvenTestPublic.EvenNumber (0 ms)
[ RUN      ] EvenTestPublic.OddNumber
[       OK ] EvenTestPublic.OddNumber (0 ms)
[----------] 2 tests from EvenTestPublic (0 ms total)   
[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.   

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithPublicMember1 && ./gTestWithPublicMember1

 */









//with protected member
/* 
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
/* 
Output:
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTest
[ RUN      ] EvenTest.EvenNumber
[       OK ] EvenTest.EvenNumber (0 ms)
[ RUN      ] EvenTest.OddNumber
[       OK ] EvenTest.OddNumber (0 ms)
[----------] 2 tests from EvenTest (0 ms total) 
[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.   

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithProtectedMember2 && ./gTestWithProtectedMember2

 */


//with private member
/* 
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
/* 
Output:
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestPrivate
[ RUN      ] EvenTestPrivate.EvenNumber
[       OK ] EvenTestPrivate.EvenNumber (0 ms)
[ RUN      ] EvenTestPrivate.OddNumber
[       OK ] EvenTestPrivate.OddNumber (0 ms)
[----------] 2 tests from EvenTestPrivate (0 ms total)          
[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.   

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithPrivateMember3 && ./gTestWithPrivateMember3


 */




 //with private member
/* 
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

class Sample {
private:
    int value;

public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
    bool isEven() const { return (value % 2 == 0); }
};

// Test Fixture
class EvenTestPrivate : public ::testing::Test {
protected:
    Sample sample;
};

// Tests
TEST_F(EvenTestPrivate, EvenNumber) {
    sample.setValue(4);
    EXPECT_TRUE(sample.isEven());
}

TEST_F(EvenTestPrivate, OddNumber) {
    sample.setValue(5);
    EXPECT_FALSE(sample.isEven());
}

// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* 
Output:


[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestPrivate
[ RUN      ] EvenTestPrivate.EvenNumber
[       OK ] EvenTestPrivate.EvenNumber (0 ms)
[ RUN      ] EvenTestPrivate.OddNumber
[       OK ] EvenTestPrivate.OddNumber (0 ms)
[----------] 2 tests from EvenTestPrivate (0 ms total)          
[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.   

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithPrivateMember4 && ./gTestWithPrivateMember4

 */








 //with private member
/* 
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

class Sample {
private:
    int value;

public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
    bool isEven() const { return (value % 2 == 0); }
};

// Test Fixture
class EvenTestPrivate : public ::testing::Test {
private:
    Sample sample;
public:
    Sample& getSample() { return sample; }  

};
// Tests
TEST_F(EvenTestPrivate, EvenNumber) {
    getSample().setValue(4);
    EXPECT_TRUE(getSample().isEven());
}
TEST_F(EvenTestPrivate, OddNumber) {
    getSample().setValue(5);
    EXPECT_FALSE(getSample().isEven());
}
// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Output:
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestPrivate
[ RUN      ] EvenTestPrivate.EvenNumber
[       OK ] EvenTestPrivate.EvenNumber (0 ms)
[ RUN      ] EvenTestPrivate.OddNumber
[       OK ] EvenTestPrivate.OddNumber (0 ms)
[----------] 2 tests from EvenTestPrivate (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.  

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithPrivateMember5 && ./gTestWithPrivateMember5
*/





//with private member
/* 
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

class Sample {
private:
    int value{0};   // ✅ initialized

public:
    void setValue(int v) { value = v; }   // ✅ added
    bool isEven() const { return (value % 2 == 0); }
};

// Test Fixture
class EvenTestPrivate : public ::testing::Test {
protected:
    Sample sample;

    Sample& getSample() { return sample; }  // optional helper
};

// Tests
TEST_F(EvenTestPrivate, EvenNumber) {
    getSample().setValue(4);
    EXPECT_TRUE(getSample().isEven());
}

TEST_F(EvenTestPrivate, OddNumber) {
    getSample().setValue(5);
    EXPECT_FALSE(getSample().isEven());
}

// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* 
Output:
[----------] Global test environment set-up.
[----------] 2 tests from EvenTestPrivate
[ RUN      ] EvenTestPrivate.EvenNumber
[       OK ] EvenTestPrivate.EvenNumber (0 ms)
[ RUN      ] EvenTestPrivate.OddNumber
[       OK ] EvenTestPrivate.OddNumber (0 ms)
[----------] 2 tests from EvenTestPrivate (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.  

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestWithPrivateMember6 && ./gTestWithPrivateMember6
*/







//Password Example with TEST_F with validation
/*
#include <gtest/gtest.h>
#include <iostream>
using namespace std;
class PassWord {
private:
    string password;    
public:
    void setPassword(const string& pwd) { 
        password = pwd; 
    }
    bool isStrong() const {
        return password.length() >= 8;
    }
};  
// Test Fixture
class PasswordTest : public ::testing::Test {
protected:
    PassWord pwd;       
    PassWord& getPwd() { 
        return pwd; 
    }  
};
// Tests
TEST_F(PasswordTest, StrongPassword) {
    getPwd().setPassword("AghazAlam123");
    EXPECT_TRUE(getPwd().isStrong());
}   
TEST_F(PasswordTest, WeakPassword) {
    getPwd().setPassword("weak");
    EXPECT_FALSE(getPwd().isStrong());
}
// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Output:
[----------] Global test environment set-up.
[----------] 2 tests from PasswordTest
[ RUN      ] PasswordTest.StrongPassword
[       OK ] PasswordTest.StrongPassword (0 ms)     
[ RUN      ] PasswordTest.WeakPassword
[       OK ] PasswordTest.WeakPassword (0 ms)
[----------] 2 tests from PasswordTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.   

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestPassword && ./gTestPassword
*/















//Password Example with TEST_F without validation
/*
#include<gtest/gtest.h>
#include<iostream>
using namespace std;
class PassWord {
private:
    string password;    
public:
    void setPassword(const string& pwd) { 
        password = pwd; 
    }
};
// Test Fixture
class PasswordTest : public ::testing::Test {
protected:
    PassWord pwd;       
    PassWord& getPwd() { 
        return pwd; 
    }  
};
// Tests
TEST_F(PasswordTest, SetPassword) {
    getPwd().setPassword("AghazAlam123");
    EXPECT_TRUE(true);          

}   
// main
int main(int argc, char **argv) {           
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Output: 
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from PasswordTest
[ RUN      ] PasswordTest.SetPassword
[       OK ] PasswordTest.SetPassword (0 ms)
[----------] 1 test from PasswordTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test. 

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestPasswordSet && ./gTestPasswordSet
*/


















//Password Example with TEST_F with printing
//*
#include <gtest/gtest.h>
#include <string>

using namespace std;

class PassWord {
private:
    string password;

public:
    void setPassword(const string& pwd) {
        password = pwd;
    }

    string getPassword() const {
        return password;
    }

    string printPassword() const {
        return "Password: " + password;
    }
};

// Test Fixture
class PasswordTest : public ::testing::Test {
protected:
    PassWord pwd;
};

// Test case
TEST_F(PasswordTest, SetPassword) {
    pwd.setPassword("AghazAlam123");

    EXPECT_EQ(pwd.getPassword(), "AghazAlam123");
    EXPECT_EQ(pwd.printPassword(), "Password: AghazAlam123");
}

// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/* 
Output: 
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from PasswordTest
[ RUN      ] PasswordTest.SetPassword
[       OK ] PasswordTest.SetPassword (0 ms)
[----------] 1 test from PasswordTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.

g++ TEST_F.cpp -lgtest -lgtest_main -lpthread -o gTestPasswordSet1 && ./gTestPasswordSet1
*/

