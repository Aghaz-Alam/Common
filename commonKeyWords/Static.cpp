
Static: 
The static keyword in C++ can be used in various contexts, with some changes in how it is applied across different versions (C++11, C++14, C++17). 
It can be used with variables, functions, and other parts of the C++ language. 
Here's a detailed explanation of its usage across C++11, C++14, and C++17.

1. Static Variables
   In C++, static variables are those that retain their value across function calls, 
   and their scope is limited to the block in which they are defined.


   C++11 and later
   The static keyword defines a variable that persists for the lifetime of the program, but its scope is limited to the function or block 
   in which it is declared.



//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
void staticVarExample() {
    static int count = 0; // Static variable
    count++;
    cout << "Count: " << count << endl;
}
int main() {
    for (int i = 0; i < 5; i++) {
        staticVarExample();
    }
    return 0;
}
/* 
Output:

Count: 1
Count: 2
Count: 3
Count: 4
Count: 5

In this example, count is a static variable that retains its value across function calls.
*/



2. Static Functions
   Static functions are functions that can only be called from within the same translation unit (file). 
   They are not visible outside the file where they are defined.

   C++11 and later
   A static function has internal linkage, meaning it is not visible outside the file. 
   This can be useful for limiting the scope of utility functions.


//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
static void printMessage() {
    cout << "This function is static and can only be called in this file.\n";
}
int main() {
    printMessage();  // This works because printMessage is in the same file
   return 0;
}
/* 
This function is static and can only be called in this file.


The printMessage function can only be called in this file because it is declared as static.
*/




3. Static Member Variables in Classes
   Static member variables are variables that are shared across all instances of a class. 
   They are not tied to any specific object of the class but rather to the class itself.

   C++11 and later
   In C++11 and beyond, static member variables can be defined inside the class, but they must be initialized outside the class.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
class MyClass {
  public:
    static int count;  // Static member variable

    MyClass() {
        count++;  // Increment count when an object is created
    }

    static void showCount() {
        cout << "Count: " << count << endl;
    }
};
// Definition of the static member outside the class
int MyClass::count = 0;

int main() {
    MyClass obj1;
    MyClass obj2;
    MyClass::showCount();  // Access static method
  return 0;
}
/* 
Output:
Count: 2

The static member variable count is shared across all instances of MyClass. Every time a new object is created, the count is incremented.
*/




4. Static Member Functions in Classes
   Static member functions can be called without creating an object of the class. 
   They can only access static member variables and cannot access instance-specific data.

   C++11 and later
   Static member functions are typically used when the function operates only on static data members.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
class MyClass {
  public:
    static int count;
    static void showCount() {
        cout << "Count: " << count << endl;
    }
};
int MyClass::count = 0;

int main() {
    MyClass::count = 5;
    MyClass::showCount();
  return 0;
}
/* 
Output:
Count: 5
*/


5. Static Local Variables in Classes (C++11 and later)
   A static local variable in a class can be used inside a member function or a method. 
   This can be particularly useful for ensuring that certain values are retained across function calls without making them global.

   C++11 and later
   This is similar to static local variables in non-class functions.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
class MyClass {
  public:
    void countObjects() {
        static int count = 0;  // Static variable inside method
        count++;
        cout << "Object count: " << count << endl;
    }
};
int main() {
    MyClass obj1, obj2, obj3;
    obj1.countObjects();
    obj2.countObjects();
    obj3.countObjects();
   return 0;
}
/* 
Output:

Object count: 1
Object count: 2
Object count: 3

Even though the countObjects() method is called multiple times, the static variable count retains its value across calls.
*/



6. Static Assertion (C++11 and later)
   The static_assert keyword is used for compile-time assertions. 
   It checks whether a condition is true during compilation, and if not, the program will fail to compile with a specified error message.

   C++11 and later
   The static_assert can be used to perform compile-time checks.

//Example (C++11, C++14, C++17):

#include <iostream>
using namespace std;
int main() {
    static_assert(sizeof(int) == 4, "Integers must be 4 bytes");
    cout << "Static assertion passed!" << endl;
    return 0;
}
/* 
Static assertion passed!

If the size of int is not 4 bytes, the compiler will issue an error message: "Integers must be 4 bytes."
*/



7. Static Class Templates (C++17 and later)
   C++17 introduced support for static class members in template classes. 
   This can be useful when you need a class template with static data members or functions.

   C++17
   In C++17, class templates can have static members, and you can instantiate them with different template arguments.


//Example (C++17):
#include <iostream>
using namespace std;
template <typename T>
class MyClass {
  public:
    static int count;  // Static member variable
    MyClass() {
        count++;  // Increment count when an object is created
    }
    static void showCount() {
        std::cout << "Count for type " << typeid(T).name() << ": " << count << std::endl;
    }
};
// Define static member for different template types
template <typename T> int MyClass<T>::count = 0;
int main() {
    MyClass<int> obj1, obj2;
    MyClass<double> obj3;

    MyClass<int>::showCount();    // Output for int
    MyClass<double>::showCount(); // Output for double

   return 0;
}
/* 
Output:

Count for type i: 2
Count for type d: 1
*/



8. Static Linkage for Functions (C++11 and later)
   In addition to static functions in classes, you can define functions with static linkage at the global scope. 
   This restricts the visibility of the function to the current translation unit (source file).

   C++11 and later
   This can be useful to avoid symbol collisions when multiple source files include the same header file.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
static void helperFunction() {
    cout << "This is a static helper function." << ndl;
}
int main() {
    helperFunction();
    return 0;
}

Summary of static usage:
Static variables: Retain their value between function calls (C++11 and later).
Static functions: Have internal linkage, only accessible within the same translation unit (C++11 and later).
Static member variables: Shared across all instances of a class (C++11 and later).
Static member functions: Operate only on static member data and do not require an object to be called (C++11 and later).
Static assertions: Used for compile-time checks (C++11 and later).
Static class templates: In C++17, allows for static members in template classes.
Static linkage for global functions: Restricts visibility to the current translation unit (C++11 and later).