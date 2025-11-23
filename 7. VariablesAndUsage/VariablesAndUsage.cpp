Variables and usage
- using pass by value, pass by reference, const
- using const, decltype other directives at functions




1. Pass by Value vs. Pass by Reference
Pass by Value:
When you pass a variable by value, the function gets a copy of the variable. 
Any modifications to the variable inside the function do not affect the original variable outside the function.

Example of Pass by Value:
#include <iostream>
using namespace std;
void passByValue(int x) {
    x = 10;  // Modifies the copy of the variable
    cout << "Inside passByValue: " << x << endl;
}
int main() {
    int a = 5;
    passByValue(a);
    cout << "In main: " << a << endl;  // Original 'a' remains unchanged
  return 0;
}
/* 
Output:

Inside passByValue: 10
In main: 5

In this case, a in main is not affected by the modification inside passByValue.
*/



Pass by Reference:
When you pass a variable by reference, the function operates on the original variable. 
Any changes made to the variable inside the function will reflect on the variable outside the function.

Example of Pass by Reference:
#include <iostream>
using namespace std;
void passByReference(int& x) {
    x = 10;  // Modifies the original variable
    cout << "Inside passByReference: " << x << endl;
}
int main() {
    int a = 5;
    passByReference(a);
    cout << "In main: " << a << endl;  // 'a' is modified
  return 0;
}
/* 
Output:

Inside passByReference: 10
In main: 10


In this case, a in main is modified because the function receives a reference to it.
*/



Pass by Reference with Const:
You can pass a reference to a variable without allowing modifications inside the function by using const. 
This is useful when you want to avoid copying large objects (like containers or complex classes), 
but still ensure the function doesn’t modify the object.

Example of Pass by Reference with const:
#include <iostream>
using namespace std;
void passByConstReference(const int& x) {
    // x = 10;  // This would cause a compile-time error
    cout << "Inside passByConstReference: " << x << endl;
}
int main() {
    int a = 5;
    passByConstReference(a);
    cout << "In main: " << a << endl;  // 'a' is not modified
  return 0;
}
/* 
Output:

Inside passByConstReference: 5
In main: 5

const int& x ensures that x cannot be modified inside the function, but the original a remains unchanged in main.
*/



2. decltype Directive in Functions
The decltype keyword in C++ is used to query the type of an expression at compile time. 
This can be useful when you want to deduce the type of a variable or an expression without explicitly specifying it.

Example of decltype:
#include <iostream>
using namespace std;
template<typename T>
void printType(T&& val) {
    // deducing type of val using decltype
    decltype(val) value = val;
    cout << "The value is: " << value << endl;
}
int main() {
    int x = 10;
    double y = 5.5;

    printType(x);  // The type is deduced as int
    printType(y);  // The type is deduced as double

  return 0;
}
/* 
Output:

The value is: 10
The value is: 5.5

Here, decltype allows the function printType to deduce the type of val automatically, making it generic and type-safe.
*/



3. Using const in Function Parameters
Using const in function parameters can help ensure that certain arguments cannot be modified inside the function, which can be important for:
Ensuring the integrity of data.
Allowing the compiler to optimize performance by guaranteeing that arguments will not be changed.

Example of const in Function Parameters:
#include <iostream>
using namespace std;
void printValue(const int x) {
    // x = 10;  // Error! Cannot modify a 'const' parameter
    cout << "The value is: " << x << endl;
}

int main() {
    int a = 5;
    printValue(a);
    cout << "In main: " << a << endl;  // 'a' is not modified
  return 0;
}
/* 
Output:

The value is: 5
In main: 5
*/



4. Using const with References
If you want to prevent modifications to a reference while avoiding a copy (for performance reasons), 
you can use a constant reference (const T&).

Example of const Reference:
#include <iostream>
using namespace std;
void printValue(const int& x) {
    // x = 10;  // Error! Cannot modify a 'const' reference
    cout << "The value is: " << x << endl;
}
int main() {
    int a = 10;
    printValue(a);  // Pass by const reference, no copy is made
    cout << "In main: " << a << endl;  // 'a' remains unchanged
  return 0;
}
/* 
Output:

The value is: 10
In main: 10

The const ensures that x cannot be changed inside the function, but no unnecessary copying happens (since it is passed by reference).
*/



5. Function Overloading with const
You can overload functions to differentiate based on whether the argument is const or not.

Example of Overloading with const:
#include <iostream>
using namespace std;
void printValue(int x) {
    cout << "Non-const version: " << x << endl;
}

void printValue(const int x) {
    cout << "Const version: " << x << endl;
}

int main() {
    int a = 10;
    const int b = 20;

    printValue(a);  // Calls non-const version
    printValue(b);  // Calls const version

  return 0;
}
/* 
Output:

Non-const version: 10
Const version: 20
*/

Summary of Key Concepts:
Pass by Value: Creates a copy of the variable. Any changes inside the function do not affect the original variable.
Pass by Reference: Passes the address of the variable, so changes inside the function affect the original variable.
const: Ensures a variable cannot be modified, either in function parameters or within the function body.
decltype: Used to deduce the type of an expression at compile-time. Useful for templates or when you don’t want to explicitly specify a type.
const References: Prevents modifications to a variable passed by reference while avoiding the overhead of copying the variable.