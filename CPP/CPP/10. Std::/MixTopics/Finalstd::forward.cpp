//Perfect forwarding preserves value category

#include<iostream>
#include<utility>
using namespace std;
void fun(int& x){
    cout <<"lvalue: "<< x <<endl;
}
void fun(int&& x){
    cout <<"rvalue: "<< x <<endl;
}

template<typename T>
void test(T&& x){
    fun(forward<T>(x));
}

int main(){
    int x =10;
    test(x);
    test(20);
  return 0;
}
/* 
lvalue: 10
rvalue: 20
*/


/* ===================================================== */
#include<iostream>
#include<utility>
using namespace std;
void fun(int& x){
    cout<<"lvalue:"<<x<<endl;
}

void fun(int&& x){
    cout<<"rvalue:"<<x<<endl;
}

/* 
template<typename T>
void test(T&& x){
    fun(forward<T>(x));
}
*/

template<typename... Args>
void test(Args&&... args) {
    (fun(forward<Args>(args)), ...); // fold expression
}


int main(){
    int x =10;
    test(x);
    test(20);
  return 0;
}
/* 
lvalue:10
rvalue:20
 */

/* ====================================================== */
#include<iostream>
#include<utility>
using namespace std;
void fun(int& a){
    cout<<a<<endl;
}
void fun(int&& a){
    cout<<a<<endl;
}
template<typename... Args>
void test(Args&&... args){
    (fun(std::forward<Args>(args)), ...);     //line 1- Fold expression, Calls fun() once per argument

    fun(std::forward<Args>(args)...);         //line 2- Pack expansion in function call, Calls fun() once with ALL arguments together
}
int main(){
    test(10);

    int a=20;
    test(a);
}
/* 
10
10
20
20
*/


1️⃣ Line-1 Explained (Fold Expression)
(fun(std::forward<Args>(args)), ...);

This expands like:
fun(std::forward<Arg1>(arg1));
fun(std::forward<Arg2>(arg2));
fun(std::forward<Arg3>(arg3));
...

Key Properties
✔ Calls fun separately for each argument
✔ Each argument keeps its value category
✔ Works for any number of arguments
✔ Very commonly used in logging, printing, validation, etc.

2️⃣ Line-2 Explained (Parameter Pack Expansion)
fun(std::forward<Args>(args)...);

This expands like:
fun(arg1, arg2, arg3, ...);

🚨 Important
This only works if fun() accepts that many parameters.
Your fun() is:
void fun(int&);
void fun(int&&);


It accepts only ONE argument, so:
test(10) → OK
test(a) → OK
test(1, 2) → ❌ compile error

🔥 Why Output Looks Same in Your Example
You are calling:
test(10);   // single argument
test(a);    // single argument


So both lines effectively do:
fun(10);
fun(10);

and

fun(a);
fun(a);

Hence same output.





🚀 HOW TO CLEARLY DISTINGUISH LINE-1 vs LINE-2
✅ Case 1: Multiple Arguments (Line-1 Works, Line-2 Fails)
Complete Program
#include<iostream>
#include<utility>
using namespace std;
void fun(int& a){
    cout << "lvalue ref: " << a << endl;
}
void fun(int&& a){
    cout << "rvalue ref: " << a << endl;
}
template<typename... Args>
void test(Args&&... args){
    cout << "Line 1 output:" << endl;
    (fun(std::forward<Args>(args)), ...);

    cout << "Line 2 output:" << endl;
    // fun(std::forward<Args>(args)...); // ❌ ERROR
}
int main(){
    int x = 10;
    test(x, 20, 30);
}

Output
Line 1 output:
lvalue ref: 10
rvalue ref: 20
rvalue ref: 30

❌ Line-2 error
error: no matching function for call to ‘fun(int&, int, int)’
📌 This is the clearest distinction






✅ Case 2: Modify fun() to Accept Multiple Args (Line-2 Works)
Complete Program
#include<iostream>
#include<utility>
using namespace std;
template<typename... T>
void fun(T&&... t){
    cout << "fun called with " << sizeof...(t) << " arguments: ";
    ((cout << t << " "), ...);
    cout << endl;
}
template<typename... Args>
void test(Args&&... args){
    cout << "Line 1:" << endl;
    (fun(std::forward<Args>(args)), ...);

    cout << "Line 2:" << endl;
    fun(std::forward<Args>(args)...);
}
int main(){
    int a = 10;
    test(a, 20, 30);
}
 
Output
Line 1:
fun called with 1 arguments: 10 
fun called with 1 arguments: 20 
fun called with 1 arguments: 30 
Line 2:
fun called with 3 arguments: 10 20 30 



🧠 Mental Model (Very Important)
Line-1
“Apply this function to each argument individually”

Line-2
“Forward all arguments together as a single call”



🧪 Interview-Ready Summary
| Feature             | Line-1                        | Line-2                          |
| ------------------- | ----------------------------- | ------------------------------- |
| Technique           | Fold expression               | Pack expansion                  |
| Calls               | Multiple calls                | Single call                     |
| Argument handling   | One at a time                 | All together                    |
| Supports multi-args | ✅                             | ❌ (unless function supports it) |
| Use cases           | Logging, printing, validation | Perfect forwarding APIs         |
| Evaluation          | Left-to-right guaranteed      | Depends on function             |


⭐ Real-World Use
✔ Line-1 → cout, logging, assertion, visiting
✔ Line-2 → emplace_back, forwarding constructors, wrappers

 */

//Fold expression, Calls fun() once per argument
#include<iostream>
#include<utility>
using namespace std;
void fun(int& a){
    cout<<a<<endl;
}
void fun(int&& a){
    cout<<a<<endl;
}
template<typename... Args>
void test(Args&&... args){
    (fun(std::forward<Args>(args)), ...);     //line 1- Fold expression, Calls fun() once per argument

    //fun(std::forward<Args>(args)...);         //line 2- Pack expansion in function call, Calls fun() once with ALL arguments together
}
int main(){
    int a=20;
    test(a);

    test(10, a, 30);

    
}
/* 
20
10
20
20
*/


//Fold expression + Pack expansion
#include<iostream>
#include<utility>
using namespace std;
template<typename... T>
void fun(T&&... a){
    ((cout << a << " "), ...);
    cout<<endl;
}
template<typename... Args>
void test(Args&&... args){
    (fun(std::forward<Args>(args)), ...);     //line 1- Fold expression, Calls fun() once per argument

    fun(std::forward<Args>(args)...);         //line 2- Pack expansion in function call, Calls fun() once with ALL arguments together
}
int main(){
    int a=20;
    test(a);

    test(10, a, 30);

    
}
/* 
20 
20 
10 
20 
30 
10 20 30 
 */




 /* ==================================================== */

 #include <iostream>
#include <utility>
#include <type_traits>
using namespace std;
template<typename T>
void fun(T&& x) {
    if constexpr (std::is_lvalue_reference_v<T>) {
        cout << "lvalue: " << x << endl;
    } else {
        cout << "rvalue: " << x << endl;
    }
}

template<typename... Args>
void test(Args&&... args) {
    (fun(std::forward<Args>(args)), ...);
}

int main() {
    int x = 10;
    test(x);
    test(20);
    //test(x, 30, 40, x);

    return 0;
}
/* 
lvalue: 10
rvalue: 20
 */





/* ===================================================== */
// ch03_forwarding_preserve.cpp
#include <iostream>
#include <utility>
using namespace std;
void g(int&) { 
    cout << "g(int&)\n"; 
}
void g(int&&) { 
    cout << "g(int&&)\n"; 
}

template<typename T>
void wrap(T&& x) { 
    g(std::forward<T>(x)); 
}
int main() {
    int a = 1;
    wrap(a);
    wrap(2);
}
/* 
Output
g(int&)
g(int&&)
*/

Why: std::forward<T> forwards lvalues as lvalues and rvalues as rvalues.
Why std::forward<T> preserves value category

Goal:
When writing a template, don’t change whether the caller passed an lvalue or an rvalue.
The problem templates introduce:
Without templates (easy case)
void f(int& x);   // lvalue only
void f(int&& x);  // rvalue only


The caller’s intent is preserved automatically.
With templates (the trap)
template<typename T>
void wrapper(T&& x) {
    f(x);   // ❌ always an lvalue
}


🚨 Even if the caller passes an rvalue, x is a named variable, therefore an lvalue.
wrapper(10);   // rvalue passed
// inside wrapper: x is an lvalue

This breaks move semantics and overload resolution.
Why this happens (core rule)
Any named object is an lvalue, regardless of its type.

Even:
int&& r = 10;
r;    // lvalue!

So templates lose value category information unless we recover it.


Enter std::forward<T>
std::forward<T>(x)

What it does
If T is an lvalue reference, returns an lvalue
If T is a non-reference, returns an rvalue

Hence:
lvalues stay lvalues, rvalues stay rvalues


Why T matters (reference collapsing)
Case 1: Caller passes lvalue
int a = 5;
wrapper(a);

Type deduction:
T = int&
T&& → int& && → int&   (reference collapsing)

So:
std::forward<int&>(x)  // returns lvalue


Case 2: Caller passes rvalue
wrapper(10);

Type deduction:
T = int
T&& → int&&

So:
std::forward<int>(x)   // returns rvalue




How std::forward is implemented (simplified)
template<class T>
constexpr T&& forward(std::remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}




The magic is static_cast<T&&>.
Why std::move is NOT enough
f(std::move(x));  // ❌ always rvalue

That destroys the caller’s intent.
| Tool              | Behavior                   |
| ----------------- | -------------------------- |
| `std::move`       | Force rvalue               |
| `std::forward<T>` | Preserve original category |




The real reason std::forward exists
Templates must:
-->Accept anything
-->Forward exactly what they received
This is called perfect forwarding.

template<class T>
void wrapper(T&& arg) {
    f(std::forward<T>(arg));   // ✅ perfect forwarding
}

Without std::forward, C++ move semantics cannot work generically.




Visual summary
Caller          Template param     std::forward result
------------------------------------------------------
lvalue          T = U&             lvalue
rvalue          T = U              rvalue



Why this design is necessary (not accidental)
If C++ didn’t behave this way:
-->Overload resolution would be ambiguous
-->Move semantics would silently fail
-->Templates would break encapsulation
-->Performance would degrade

std::forward is the bridge between:
-->Compile-time type deduction
-->Runtime value category



One-line takeaway
Templates erase value category — std::forward<T> restores it using type deduction + reference collapsing.












