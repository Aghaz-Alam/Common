1. Basic Lambda Example
#include<iostream>
using namespace std;
int main(){
   auto f = []() {
      cout << "Hello from lambda!" << endl;
   };

   f();   // call lambda
  return 0;
}
/*
Hello from lambda!
*/




2. Lambda With Parameters
#include<iostream>
using namespace std;
int main(){
  auto add = [](int a, int b) {
    return a + b;
   };
   cout << add(5, 6);   // 11
  return 0;
}
/*
11
*/




3. Lambda with Return Type: Useful when return type is not obvious.

#include<iostream>
using namespace std;
int main(){
    auto divide = [](double a, double b) -> double {
      return a / b;
    };
    cout<<divide(1.2, 2.0)<<endl;
  return 0;
}
/*
0.6
*/


//std::function is a viabale replacement of auto
#include<iostream>
#include <functional>
using namespace std;
int main(){
    std::function divide = [](double a, double b) -> double {
      return a / b;
    };
    cout<<divide(1.2, 2.0)<<endl;
  return 0;
}
/*
0.6
*/



4. Lambda Capture List: The capture list controls which outside variables are accessible.

//Capture by Value
#include<iostream>
using namespace std;
int main(){
    int x = 10;
    auto f = [x]() {
      cout << x << endl;   // prints copied value (10)
    };
   
    f();                   // CALL THE LAMBDA
  return 0;
}
/*/
10
*/

//Capture by Reference
#include<iostream>
using namespace std;
int main(){
    int x = 10;
    auto f = [&x]() {
         x = 20;  // modifies original x
    };
   
    cout<<x<<endl;
    f();                   // CALL THE LAMBDA
    cout<<x<<endl;
  return 0;
}
/*
10
20
*/

//Capture All by Value [=]
//auto f = [=]() { cout << x << y; };

//global variable
#include <iostream>
using namespace std;
int x = 10;
int y = 20;
int main() {
    auto f = [=]() {
        cout << x << " " << y << endl;
    };

    f();

    return 0;
}
/*
10 20
*/



//local variable
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int y = 20;
    auto f = [=]() {
        cout << x << " " << y << endl;
    };

    f();

    return 0;
}
/*
10 20
*/





//Capture All by Reference [&]
//auto f = [&]() { x++; y++; };


//with Global variable
#include <iostream>
using namespace std;
int x = 10;
int y = 20;
int main() {
    auto f = [&]() { x++; y++; };
    
    cout<<x<<" "<<y<<endl;
    f();
    cout<<x<<" "<<y<<endl;
    return 0;
}
/*
10 20
11 21
*/

//with local variables
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int y = 20;
    auto f = [&]() { x++; y++; };
    
    cout<<x<<" "<<y<<endl;
    f();
    cout<<x<<" "<<y<<endl;
    return 0;
}
/*
10 20
11 21
*/



5. Using Lambda with Thread: We can pass a lambda directly to a thread:

#include <iostream>
#include <thread>
using namespace std;

int main() {
    thread t([](int x, int y){
        cout << "Lambda sum = " << x + y << endl;
    }, 5, 6);

    t.join();
}
/* 
Output:

Lambda sum = 11
*/


6. Lambda in Algorithms (Modern C++)
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4};

    for_each(v.begin(), v.end(), [](int x){
        cout << x << " ";
    });
  return 0;
}
/* 
Output:
1 2 3 4 
*/



7. Mutable Lambdas: Allows modification of captured-by-value variables inside the lambda.

#include <iostream>
using namespace std;
int main() {
    int x = 10;
    auto f = [x]() mutable {
         x = 20;   // allowed because of mutable
         cout << x<<endl;
    };

    f(); // 20
    cout << x<<endl; // still 10 (outside unchanged)
  return 0;
}
/* 
20
10
*/





1. What Is a Lambda Expression in C++?
---> A lambda expression is an anonymous function — a function without a name — used for short, inline operations.
---> Introduced in C++11, improved in C++14/17/20.

/* ------------------------------------------ */
2. Basic Syntax
[capture](parameters) -> return_type {
    //body
};

Meaning of Each Part:
| Part            | Purpose                                         |
| --------------- | ----------------------------------------------- |
| **capture**     | Variables from outside to use inside the lambda |
| **parameters**  | Function parameters                             |
| **return_type** | Usually optional (auto deduced)                 |
| **body**        | Function code                                   |

Example:
auto sum = [](int a, int b) { return a + b; };
cout << sum(3, 4);   // 7




/* -------------------------------------------- */
3. Using a Lambda Immediately
cout << [](int x){ return x * x; } (5); //This is called an immediately invoked lambda expression.

Output:
25



/* ------------------------------------------- */
4. Capture List Explained (Most Important)
---> The capture list defines how variables outside the lambda are accessed inside it.

4.1 Capture Nothing
[](){ cout << "Hello"; }();

4.2 Capture by Value
int x = 10;
auto lam = [x]() { cout << x; };

✔ Creates a copy of x
Changes outside do not affect the copy.


4.3 Capture by Reference
int x = 10;
auto fun = [&x]() { x++; };
fun();
cout << x;  // 11

✔ Modifies the original value
✔ Dangerous if capturing temporary variables


4.4 Capture All by Value
auto lam = [=]() { cout << x << y; };

4.5 Capture All by Reference
auto lam = [&]() { x++; y++; };

4.6 Mixed Captures
auto lam = [x, &y]() { cout << x << y; };


/* --------------------------------------------------------------------------------------------------------- */
5. Mutable Lambdas
---> By default, value-captured variables are const inside the lambda.
---> You can modify the captured value using mutable.
int x = 10;
auto fun = [x]() mutable { x++; cout << x; };
fun();  // 11
cout << x; // 10

✔ Inside the lambda: x modified
✔ Outside: original x unchanged

/* --------------------------------------------------------------------------------------------------------- */
6. Return Type Deduction
C++11
---> Must specify return type if multiple return statements with different types.
auto f = [](int x) -> double {
    if(x > 0) return x;
    return 0.5;
};

C++14+
---> Return type automatically deduced.
---> In C++14, lambdas can deduce the return type automatically, just like a function using auto.

✔ The rule:
All return statements must deduce to the same type.
(Otherwise, the compiler gives an error.)

✔ The compiler deduces the return type by:
Looking at all return statements
Computing a common type
Using that as the final return type



Example 1 — Works in C++14
auto f = [](int x) {
    if (x > 0) return x;     // int
    return 0;                // int
};

Compiler logic:
First return: int
Second return: int
Common type = int

✔ Valid.
✔ Return type deduced as int.



Example 2 — This works in C++14 but NOT in C++11
auto f = [](int x) {
    if (x > 0) return x;     // int
    return 0.5;              // double
};

How C++14 deduces this:
Return 1: int
Return 2: double
Common type = double
(using usual arithmetic conversions)
✔ Allowed in C++14
❌ Not allowed in C++11


❗ Why C++11 cannot do this?
---> Because in C++11, lambda return type deduction follows template trailing-return-type deduction rules which only deduce from one return statement.

So in C++11:
auto f = [] (int x) { 
    if(x > 0) return x; 
    return 0.5; 
};

Compiler error:
---> error: inconsistent deduced return types ‘int’ and ‘double’


Why?
---> Because C++11 cannot inspect all return statements.
---> It only looks at the first return and fixes the return type.

So it sees:
if (x>0) return x;   // int

→ return type assumed: int
---> But later you return 0.5 → mismatch → error.

C++14 Fix: "deduced return type from all return paths"
C++14 changed the rule:
---> Lambdas with auto return types behave like normal functions with auto return type.

Meaning:
C++14:
---> Compiler considers every return statement → deduces a single common return type.


C++14 Deduction Mechanism (behind the scenes)
For this:
auto f = [](int x) {
    if (x > 0) return x;     // int
    return 0.5;              // double
};

Compiler does:
decltype(true ? int{} : double{})  →  double
This is the conditional operator rules, producing the common type.


/* --------------------------------------------------------------------------------------------------------- */
7. Lambdas with STL Algorithms (Most Useful)
Example: sort with custom comparator
vector<int> v = {5, 3, 9, 1};

sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;    // descending
});

Example: count_if
int countEven = count_if(v.begin(), v.end(),
                         [](int x){ return x % 2 == 0; });




/* ----------------------------------------------------------------------------------------------------- */
8. Lambda as Function Objects (Functors)

A lambda is compiled as an unnamed class with:

Operator () overloaded

Captured variables stored as data members

Visualization:
auto f = [x](int y){ return x + y; };


Compiler generates something like:

class __Lambda_1 {
    int x;
public:
    int operator()(int y) const {
        return x + y;
    }
};


f is an object of this class.



/* ------------------------------------------------------------------------------------------------------- */
9. Generic Lambdas (C++14)

Use auto in parameters:

auto add = [](auto a, auto b) {
    return a + b;
};

cout << add(2, 3);       // 5
cout << add(2.5, 3.5);   // 6.0



/* ------------------------------------------------------------------------------------------------------- */
10. Lambda Capture of this

Inside a class:

class A {
public:
    int x = 5;
    void show() {
        auto lam = [this]() { cout << x; };
        lam();
    }
};



/* ----------------------------------------------------------------------------------------------------- */
11. C++20: Lambda Templates
auto func = []<typename T>(T x) {
    return x * x;
};

cout << func(10);     // 100



/* ----------------------------------------------------------------------------------------------------- */
Q1: What is the difference between capture-by-value and capture-by-reference?
| By Value                          | By Reference                |
| --------------------------------- | --------------------------- |
| Copies variables                  | Uses original variables     |
| Safe                              | Risky (dangling references) |
| Does not reflect external changes | Reflects changes            |



Q2: Why do we need mutable in lambdas?
Because value-captured variables are const by default.



Q3: Can a lambda outlive the variables it captures?
✔ Yes, if captured by value
❌ No, if captured by reference and the referenced object is destroyed


Q4: What is the type of a lambda?
A unique, compiler-generated closure type.
You cannot write its type directly.

/* --------------------------------------------------------------------------------------------------------- */