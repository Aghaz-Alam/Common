Friend functions
- class , function
- mutual friendship?


In C++, friendship is not mutual (or reciprocal) by default; it is a one-way grant of access. 

If a class declares a function or another class as a friend, only the friend gains access to the private and protected members of the class that made the declaration. The class granting friendship does not automatically get access to the friend's private members.


To achieve mutual friendship between a class and a function (or between two classes), you must explicitly declare the friendship in both directions within their respective definitions. 


Mutual Friendship: Class and Function
To have mutual friendship between a ClassA and a functionB, you must:

Declare functionB as a friend inside ClassA.

Ensure functionB has a way to access private members of ClassA, 
typically by taking an object of ClassA as an argument.

(If functionB is a member of another class, say ClassB, then ClassA's definition would appear in 
ClassB and functionB's definition might access ClassA's private members). 



Here is a simplified example of a global function and a class having a "mutual friendship" 
where each operates on the other (though the function only operates on the class, 
the principle of bidirectional declaration is for class-to-class):



#include <iostream>
// Forward declaration of ClassA is needed because functionB is declared first
class ClassA; 
// Declaration of the global function
void functionB(ClassA& objA);
class ClassA {
  private:
    int dataA = 10;
    // Declare the global function as a friend
    friend void functionB(ClassA& objA); 
};
// Definition of the global function, which now has access to ClassA's private members
void functionB(ClassA& objA) {
    std::cout << "functionB accessing ClassA's dataA: " << objA.dataA << std::endl;
    // functionB doesn't have private members to be accessed, so the 
    // "mutuality" is purely about declaration permissions.
}
int main() {
    ClassA objA;
    functionB(objA);
   return 0;
}
/* 
In this scenario, ClassA explicitly grants access to functionB. 
Since a standalone function doesn't have "private" members that a class would need to access, 
the "mutuality" is simply the declaration in the class.
*/

Mutual Friendship: Two Classes
For two classes, say ClassA and ClassB, to have mutual friendship:
1. ClassA must declare ClassB as a friend within its definition.
2. ClassB must declare ClassA as a friend within its definition.
3. Forward declarations and careful ordering of function definitions using the scope resolution operator (::) 
are required to avoid compilation errors. 

In essence, friendship is a unilateral contract in C++. 
The entity granting access (friend declaration within its body) is the one in control. 
To make it mutual, both sides must explicitly agree by using the friend keyword in their own declarations.










Note: VVI
A friend function in C++ is a function that is granted access to the private and protected members of a class. 
The very definition of a friend function relies on the existence of a class whose members it can access. 


Therefore, it is impossible to write a program that uses a friend function in C++ "without using a class". 
The friend keyword has no meaning or use case outside of a class definition. 



                                  A SIMPLE PROGRAM
                                           |
                                           |
                                           |
                                           
//A simple C++ program that uses a regular function (not a friend function) or just demonstrates basic C++ syntax, here is an example:
#include <iostream>
// A simple function that takes two integers and returns their sum
int add(int a, int b) {
    return a + b;
}
int main() {
    int num1 = 5;
    int num2 = 10;

    // Calling the 'add' function
    int sum = add(num1, num2);

    std::cout << "The sum of " << num1 << " and " << num2 << " is: " << sum << std::endl;

 return 0;
}



                      A SIMPLE PROGRAM CONVERTED TO CLASS OBJECT
                                           |
                                           |
                                           |               
Option 1: The add function as a method using member variables
In this version, the numbers are stored inside the class instance (Calculator), 
and the add() method operates on these stored values.

#include <iostream>
class Calculator {
  private:
    int num1;
    int num2;

  public:
    // A constructor to initialize the member variables
    Calculator(int a, int b) {
        num1 = a;
        num2 = b;
    }

    // The 'add' function converted into a public member method
    int add() {
        return num1 + num2;
    }
};

int main() {
    // Create an instance (object) of the Calculator class
    Calculator calc(5, 10);

    // Call the 'add' member function using the object
    int sum = calc.add();

    std::cout << "The sum is: " << sum << std::endl;

  return 0;
}



                      A SIMPLE PROGRAM CONVERTED TO CLASS OBJECT
                                           |
                                           |
                                           |   
Option 2: The add function as a method accepting parameters
In this version, the class provides the structure, but the data is still passed to the add method, 
similar to how the original global function worked.

#include <iostream>
class Calculator {
  public:
    // The 'add' function as a public member method
    // It accepts parameters, just like the original global function
    int add(int a, int b) {
        return a + b;
    }
};
int main() {
    int num1 = 5;
    int num2 = 10;

    // Create an instance (object) of the Calculator class
    Calculator calc;

    // Call the 'add' member function using the object and pass arguments
    int sum = calc.add(num1, num2);

    std::cout << "The sum of " << num1 << " and " << num2 << " is: " << sum << std::endl;

 return 0;
}



                      BASIC CLASS OBJECT METHOD CONVERTED TO FRIEND 
                                           |
                                           |
                                           |   

Option 1: Using a friend function to access private member variables
In this version, the calculation is performed by a standalone, non-member function named add, 
which is explicitly granted friend access by the Calculator class to read its private num1 and num2 members.

#include <iostream>
// Forward declaration of the Calculator class is needed
// so the 'add' prototype below it knows what 'Calculator' refers to.
class Calculator;

// Prototype of the friend function (must be defined outside the class)
int add(Calculator calc_obj);

class Calculator {
  private:
    int num1 = 5;
    int num2 = 10;

// Declare the external 'add' function as a friend of this class
   friend int add(Calculator calc_obj);

   public:
    // A simple public display function
    void display_numbers() {
        std::cout << "Numbers are: " << num1 << " and " << num2 << std::endl;
    }
};

// Definition of the friend function:
// It takes a Calculator object and accesses its PRIVATE members directly.
int add(Calculator calc_obj) {
    // This is valid because 'add' is a friend of 'Calculator'
    return calc_obj.num1 + calc_obj.num2;
}

int main() {
    Calculator calc;

    // Call the independent friend function, passing the object as an argument
    int sum = add(calc);

    calc.display_numbers();
    std::cout << "The sum calculated by the friend function is: " << sum << std::endl;

   return 0;
}



Option 2: Using a friend function to perform the operation with passed parameters
This version mimics the original structure more closely. The numbers are defined in main, 
and the independent add function takes them as parameters.

The use of a friend keyword is technically unnecessary here unless you want the add function to 
use private class members while it calculates the sum of the external inputs (which is a slightly unusual 
design pattern, but demonstrates the syntax).

The example below shows a class DataHolder that uses a friend function to set its private data 
using the parameters passed into the function.

#include <iostream>
class DataHolder {
  private:
    int stored_sum;
    // The main point is that the friend function can access 'stored_sum'

  public:
    // Declare the external function 'calculateAndStore' as a friend
    friend void calculateAndStore(DataHolder& dh, int a, int b);

    void display_stored_sum() {
        std::cout << "Stored Sum in DataHolder class: " << stored_sum << std::endl;
    }
};

// Definition of the friend function:
// It modifies the private members of the DataHolder object it receives by reference.
void calculateAndStore(DataHolder& dh, int a, int b) {
    // Accessing private member 'stored_sum' is allowed because it's a friend
    dh.stored_sum = a + b;
    std::cout << "Friend function calculated sum (" << a << "+" << b << ") and stored it privately." << std::endl;
}

int main() {
    int num1 = 5;
    int num2 = 10;
    DataHolder my_data;

    // Call the friend function to operate on the my_data object
    calculateAndStore(my_data, num1, num2);

    // Verify the private data was set correctly
    my_data.display_stored_sum();

  return 0;
}





Example: Testing a Private Member Function
Here is a program broken into two files: the production code header, and the test implementation file.

1. Production Code (MyClass.h)
This is the header file for the class you want to test. 
You must include the GTest production header and use the FRIEND_TEST macro inside the class definition, typically in the private section. 


// MyClass.h
#ifndef MYCLASS_H
#define MYCLASS_H
#include "gtest/gtest_prod.h" // Defines the FRIEND_TEST macro
class MyClass {
 private:
    int private_value = 10;

    // A private helper function we want to test
    int add_private_values(int b) {
        return private_value + b;
    }

    // Declare the specific Google Test as a friend
    FRIEND_TEST(MyClassTest, CanAccessPrivateMethod);
    FRIEND_TEST(MyClassTest, CanAccessPrivateVariable);

  public:
    // Public function that uses the private functionality
    int add_public(int b) {
        return add_private_values(b);
    }
};

#endif // MYCLASS_H




2. Test Implementation (MyClass_test.cc)
This file contains your GTest test cases. 
The tests can now directly call private members of MyClass because of the FRIEND_TEST declarations in the header.

// MyClass_test.cc
#include "MyClass.h"
#include "gtest/gtest.h"
// Define a test case named "MyClassTest"
TEST(MyClassTest, CanAccessPrivateMethod) {
    MyClass obj;
    int result = obj.add_private_values(5); // Directly calling a private method
    EXPECT_EQ(result, 15);
}

// Another test case accessing a private member variable
TEST(MyClassTest, CanAccessPrivateVariable) {
    MyClass obj;
    obj.private_value = 50; // Directly modifying a private variable
    EXPECT_EQ(obj.private_value, 50);
    EXPECT_EQ(obj.add_public(1), 51);
}