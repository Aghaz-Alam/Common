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












