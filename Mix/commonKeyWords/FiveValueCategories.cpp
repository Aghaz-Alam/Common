The 5 Value Categories
C++ expressions fall into:
               expression
                    |
        --------------------------------
        |                              |
     glvalue                        rvalue
        |                              |
   -----------                   -----------
   |         |                   |         |
 lvalue    xvalue               prvalue   (none)


 The five categories are:
lvalue
xvalue
prvalue
glvalue (generalized lvalue)
rvalue





1️⃣ lvalue (Locator Value)
Definition:
An lvalue:
-->Has a name
-->Refers to a persistent object
-->Has a memory location
-->Can appear on the left-hand side of =

✔ Examples
int x = 10;
x = 20;          // x is lvalue

int& ref = x;    // ref is lvalue


struct S { int a; };
S s;
s.a = 5;         // s.a is lvalue



✔ lvalue references
int& r = x;      // OK

❌ Not allowed
int& r = 10;     // ERROR (10 is not lvalue)

🧠 Mental model
“I can point to it, name it, and modify it.”






2️⃣ prvalue (Pure rvalue)
📌 Definition
A prvalue:
-->Is a temporary
-->Has no identity
-->Usually disappears after the expression
-->Cannot be assigned to

✔ Examples
10              // literal → prvalue
x + y           // result → prvalue
int(5)          // prvalue

struct S {};
S();            // prvalue

✔ rvalue references
int&& r = 10;   // OK

❌ Not allowed
int& r = 10;    // ERROR

🧠 Mental model
“A temporary value that exists just to be used.”










3️⃣ xvalue (eXpiring value)
📌 Definition
An xvalue:
-->Refers to an object about to be destroyed
-->Has identity (unlike prvalue)
-->Can be moved from

✔ Examples
std::move(x)    // xvalue

struct S { };
S make();

S&& r = make();  // make() materializes then becomes xvalue

std::vector<int> v;
std::vector<int>&& rv = std::move(v);

Why std::move?
std::move(x)    // DOES NOT move
                // Just casts x to xvalue

🧠 Mental model
“A named object, but the compiler is allowed to steal its resources.”







4️⃣ glvalue (Generalized lvalue)
📌 Definition
A glvalue:
-->Has identity
-->Refers to a specific object
-->Can be either lvalue or xvalue

✔ Examples
x              // lvalue → glvalue
std::move(x)   // xvalue → glvalue

❌ prvalue is NOT glvalue
10             // prvalue → NOT glvalue

🧠 Mental model
“I can identify which object this refers to.”





5️⃣ rvalue (Right value)
📌 Definition
An rvalue:
-->Temporary or expiring
-->Can bind to T&&

Includes:
-->prvalue
-->xvalue

✔ Examples
10              // prvalue → rvalue
x + y           // prvalue → rvalue
std::move(x)    // xvalue  → rvalue

❌ lvalue is not rvalue
int x;
int&& r = x;    // ERROR

🧠 Mental model
“This value can be consumed it.






⚡ Why These Categories Exist
They enable:
-->Move semantics
-->Perfect forwarding
-->Efficient STL containers
-->Overload resolution

Example:
void foo(const string& s);  // copy
void foo(string&& s);       // move

string a = "hello";
foo(a);            // lvalue → copy
foo("world");      // prvalue → move
foo(std::move(a)); // xvalue → move







1️⃣ decltype behavior for each value category
🔹 Core rules of decltype

For an expression e:
| Expression form                         | `decltype(e)`        |
| --------------------------------------- | -------------------- |
| **unparenthesized id-expression** (`x`) | declared type of `x` |
| **lvalue expression**                   | `T&`                 |
| **xvalue expression**                   | `T&&`                |
| **prvalue expression**                  | `T`                  |



Program 1: decltype with lvalue, xvalue, prvalue
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    int x = 10;

    decltype(x) a = 1;        // int
    decltype((x)) b = x;     // int&  (because (x) is lvalue)
    decltype(x + 5) c = 20;  // int   (prvalue)
    decltype(std::move(x)) d = 30; // int&& (xvalue)

    cout << boolalpha;
    cout << is_same<decltype(a), int>::value << endl;
    cout << is_same<decltype(b), int&>::value << endl;
    cout << is_same<decltype(c), int>::value << endl;
    cout << is_same<decltype(d), int&&>::value << endl;

    return 0;
}
/* 
🖨 Output
true
true
true
true

🔑 Key interview trap
decltype(x)   // int
decltype((x)) // int&
*/






2️⃣ Why T&& is sometimes lvalue
🔹 Rule
Named rvalue references are lvalues


🔸 Program 2: Named T&& is lvalue
#include <iostream>
using namespace std;

void foo(int& x) {
    cout << "lvalue reference\n";
}

void foo(int&& x) {
    cout << "rvalue reference\n";
}

int main() {
    int&& r = 10;

    foo(r);            // r is lvalue!
    foo(std::move(r)); // r cast to xvalue

    return 0;
}
/* 
🖨 Output
lvalue reference
rvalue reference

🧠 Explanation
int&& r = 10;

r has type int&&
but r is a named variable
all named variables are lvalues
🔑 Interview quote
“Type is rvalue reference, but expression is lvalue.”
*/





3️⃣ Value categories in function return
🔹 Rules (C++11 → C++17)
| Return expression              | Value category |
| ------------------------------ | -------------- |
| `return x;` where `x` is local | **prvalue**    |
| `return T{}`                   | prvalue        |
| `return std::move(x);`         | xvalue         |
| Function returning `T&`        | lvalue         |
| Function returning `T&&`       | xvalue         |




Program 3A: Returning by value (prvalue)
#include <iostream>
using namespace std;

int make() {
    return 10;
}

int main() {
    int&& r = make();  // prvalue binds to rvalue ref
    cout << r << endl;
    return 0;
}
/* 
🖨 Output
10
 */



🔸 Program 3B: Returning lvalue reference
#include <iostream>
using namespace std;

int& getRef() {
    static int x = 100;
    return x;
}

int main() {
    int& r = getRef();
    r += 10;
    cout << getRef() << endl;
    return 0;
}
/* 
🖨 Output
110
 */




🔸 Program 3C: Returning rvalue reference (xvalue)
#include <iostream>
using namespace std;
int&& getRRef() {
    static int x = 50;
    return std::move(x);
}
int main() {
    int&& r = getRRef();
    cout << r << endl;
    return 0;
}
/* 
🖨 Output
50

⚠ Dangerous in real code – lifetime confusion.
 */




4️⃣ Interview-style tricky questions (with programs)
❓ Q1: Why does this fail?
int& r = 10;

✔ Reason
10 is prvalue
lvalue reference cannot bind to prvalue





❓ Q2: What is the value category of x + y?
#include <iostream>
using namespace std;

int main() {
    int x = 2, y = 3;
    decltype(x + y) z = 5;
    cout << z << endl;
    return 0;
}
/* 
🖨 Output
5

✔ x + y → prvalue
 */



❓ Q3: Why does this call copy, not move?
#include <iostream>
using namespace std;

void foo(int& ) {
    cout << "copy\n";
}

void foo(int&& ) {
    cout << "move\n";
}

int main() {
    int x = 10;
    int&& r = std::move(x);

    foo(r); // ❗
    return 0;
}
/* 
🖨 Output
copy

✔ Because r is lvalue
 */



❓ Q4: Perfect forwarding trap
#include <iostream>
using namespace std;
template<typename T>
void wrapper(T&& arg) {
    foo(arg);              // always lvalue
    foo(std::forward<T>(arg)); // perfect forwarding
}
void foo(int& ) {
    cout << "lvalue\n";
}
void foo(int&& ) {
    cout << "rvalue\n";
}
int main() {
    wrapper(10);
    return 0;
}
/* 
🖨 Output
lvalue
rvalue
 */
























