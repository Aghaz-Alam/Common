Default Arguments in C++:
-->A default argument is a value provided for a parameter in a function declaration that is automatically assigned by the compiler 
   if no value is provided for those parameters in function.
-->Default arguments must be present on the right side only. 
-->Once a default argument is provided, all the arguments to its right must also be defaults.
-->It is recommended to specify them in function declaration (usually in the header).

#include <iostream>
using namespace std;
void fun(int a = 10, int b=20, int c=30){
    cout << a+b+c << endl;
}
int main(){
    // Uses default argument
    fun();

    // Uses passed value
    fun(2);
    fun(2,3);
    fun(3,5,6);

  return 0;
}
/*
60
52
35
14
*/



/* ==================================================================================================================================================== */

Rules to Follow
There are some important rules and best practices to keep in mind when using default arguments in C++:

1. Default Values Should be Specified in Function Declarations
The default values for parameters should be specified in the function declaration (or prototype). 
If a function is declared and defined separately, the default values must be in the declaration, not in definition.

// Declaration with default argument
void func(int x = 10);

// Definition without default argument
void func(int x){
    cout << "Value: " << x << endl;
}


/* --------------------------------- */
#include <iostream>
using namespace std;

// Function declaration (prototype)
// ✔ Default value specified here
void func(int x = 10);

// Function definition
// ✔ No default value here
void func(int x) {
    cout << "Value: " << x << endl;
}

int main() {
    func();     // uses default value → 10
    func(25);   // uses provided value → 25
    return 0;
}
/* 
Value: 10
Value: 25
*/

/* ==================================================================================================================================================== */


2. Default Arguments Cannot Be Modified
Once default arguments are defined in the declaration, they cannot be modified in the function definition. 
If you try to change the default value in the definition, it will result in a compilation error.

// Declaration
void f(int a = 10);

// This definintion will throw and error
void f(int a = 222){
    // statements
}

/* ------------------------- */
#include <iostream>
using namespace std;

// Function declaration (default argument here)
void f(int a = 10);

// Function definition (NO default argument here)
void f(int a) {
    cout << "a = " << a << endl;
}

int main() {
    f();        // uses default value → 10
    f(50);      // uses provided value → 50
    return 0;
}
/* 
a = 10
a = 50
*/

/* ==================================================================================================================================================== */

3. Default Arguments Must Be Provided from Right to Left
In a function with multiple parameters, default values must be provided from the rightmost parameter to the left. 
It means that if a parameter has a default argument, all parameters to its right must also have default values.

// Valid
void func(int x, int y = 20);

// Invalid, as `y` does not have a default value
void func(int x = 10, int y);

/* ----------------------------------- */
#include <iostream>
using namespace std;

// ✔ Valid: default provided from rightmost parameter
void func(int x, int y = 20) {
    cout << "x = " << x << ", y = " << y << endl;
}

int main() {
    func(5);        // x = 5, y = 20
    func(5, 10);    // x = 5, y = 10
    return 0;
}
/* 
x = 5, y = 20
x = 5, y = 10
*/
/* ==================================================================================================================================================== */

4. Ambiguity in Function Overloading
If a function containing default arguments is overloaded, then we need to make sure it is not ambiguous to the compiler, otherwise it will throw an error.

// Valid
void f(int a = 10, int b = 20);

// Will throw error as the signature is same
void f(int a = 22, int b = 2);

// Will also throw error
void f(int a);

// Will also throw an error
void f(int a, b)



✔️ Option 1: Single function with default arguments (BEST PRACTICE)
#include <iostream>
using namespace std;
void f(int a = 10, int b = 20) {
    cout << "a = " << a << ", b = " << b << endl;
}
int main() {
    f();        // a = 10, b = 20
    f(5);       // a = 5,  b = 20
    f(5, 7);    // a = 5,  b = 7
}





✔️ Option 2: Overloading WITHOUT default arguments
#include <iostream>
using namespace std;
void f(int a) {
    cout << "f(int): a = " << a << endl;
}
void f(int a, int b) {
    cout << "f(int, int): a = " << a << ", b = " << b << endl;
}
int main() {
    f(5);        // calls f(int)
    f(5, 10);    // calls f(int, int)
}

✔ No ambiguity
✔ Clear overload resolution




✔️ Option 3: Combine overloading + defaults (RULED & SAFE)
Only ONE overload may use default arguments.

#include <iostream>
using namespace std;
void f(int a, int b = 20) {
    cout << "a = " << a << ", b = " << b << endl;
}

int main() {
    f(5);        // a = 5, b = 20
    f(5, 8);     // a = 5, b = 8
}
