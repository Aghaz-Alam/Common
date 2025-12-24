explain std move. how std move is implemented underneath.

✅ What std::move Actually Does
std::move does NOT move anything.

It only performs a cast:
---> It casts an object to an rvalue (specifically, an xvalue),
---> which allows move constructors / move assignment operators to be invoked.

✔️ std::move → “treat this object as a temporary; you are allowed to steal from it.”
✅ Official Implementation of std::move
The real implementation (from <utility>) is basically:

template <class T>
constexpr remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<remove_reference_t<T>&&>(t);
}

That’s all.
Key points:
--> T&& in a template is universal reference (a.k.a forwarding reference),
--> remove_reference_t<T> ensures that if T is int&, the cast becomes int&&,
--> static_cast<T&&> returns an rvalue reference.

/* ----------------------------------- */
#include <iostream>
#include <type_traits>   // for std::remove_reference_t

// ===============================
// 1. Custom implementation of move
// ===============================
namespace my {

template <class T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(t);
}

} // namespace my

// ===============================
// 2. A class that logs copy/move
// ===============================
struct A {
    A() { std::cout << "A: Default constructor\n"; }
    A(const A&) { std::cout << "A: Copy constructor\n"; }
    A(A&&) noexcept { std::cout << "A: Move constructor\n"; }
};

// ===============================
// 3. Test code
// ===============================
int main() {
    A a;                 // Default constructor
    std::cout << "----\n";

    A b = my::move(a);   // Should call Move constructor
    std::cout << "----\n";

    A c = a;             // Copy constructor (lvalue)
    std::cout << "----\n";

    return 0;
}
/*
A: Default constructor
----
A: Move constructor
----
A: Copy constructor
----
*/
/* ----------------------------------- */

Why std::move Needs remove_reference_t?
Consider:
int a = 10;
int& ref = a;
std::move(ref);   // What should this cast to?


Without removing reference:
T deduces to int&
meaning T&& becomes int& && → collapses to int&
static_cast<int&>(ref) would produce an lvalue, NOT an rvalue.

That’s wrong.
With remove_reference_t<T>:
remove_reference_t<int&> → int
cast becomes static_cast<int&&>(ref) → this is an rvalue.

/* ----------------------------------------- */
#include <iostream>
#include <type_traits>

// ------------------------------------------------------
// 1. Wrong implementation (NO remove_reference_t)
// ------------------------------------------------------
namespace wrong {

template <class T>
constexpr T&& move(T&& t) noexcept {    // ❌ WRONG
    return static_cast<T&&>(t);         // does NOT remove reference
}

}  // namespace wrong

// ------------------------------------------------------
// 2. Correct implementation (WITH remove_reference_t)
// ------------------------------------------------------
namespace correct {

template <class T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept {   // ✔️ CORRECT
    return static_cast<std::remove_reference_t<T>&&>(t);
}

}  // namespace correct


// ------------------------------------------------------
// Helpers to print value-category
// ------------------------------------------------------
template <typename T>
void print_value_category(const T&) {
    std::cout << "Expression is an LVALUE\n";
}

template <typename T>
void print_value_category(T&&, 
    typename std::enable_if<!std::is_lvalue_reference<T>::value>::type* = nullptr)
{
    std::cout << "Expression is an RVALUE\n";
}


// ------------------------------------------------------
// 3. Test program
// ------------------------------------------------------
int main() {
    int a = 10;
    int& ref = a;

    std::cout << "=== Using WRONG move (no remove_reference_t) ===\n";
    auto&& w = wrong::move(ref);   // returns int&  (still an lvalue!)
    print_value_category(w);       // prints: LVALUE

    std::cout << "\n=== Using CORRECT move (with remove_reference_t) ===\n";
    auto&& c = correct::move(ref); // returns int&& (rvalue)
    print_value_category(std::move(c));  // prints: RVALUE

    return 0;
}
/*
=== Using WRONG move (no remove_reference_t) ===
Expression is an LVALUE

=== Using CORRECT move (with remove_reference_t) ===
Expression is an RVALUE
*/
/* ----------------------------------------- */


What Happens After std::move(x)?
Calling:
std::string s1 = "hello";
std::string s2 = std::move(s1);

Steps:
std::move(s1) → casts s1 to std::string&& (xvalue)
This makes overload resolution choose:
string(string&&) noexcept   // move constructor
Move constructor steals the internal buffer, e.g.:
s2._ptr = s1._ptr;
s1._ptr = nullptr;     // leave s1 valid but unspecified

/* ------------------------------------------ */
#include <iostream>
#include <string>
#include <cstring>   // <-- REQUIRED for strlen, memcpy

struct MyString {
    char* data;

    // Default constructor
    MyString() : data(nullptr) {
        std::cout << "Default constructor\n";
    }

    // Construct from C-string
    MyString(const char* s) {
        std::cout << "Construct from const char*\n";
        size_t len = std::strlen(s) + 1;   // OK now
        data = new char[len];
        std::memcpy(data, s, len);         // OK now
    }

    // Copy constructor
    MyString(const MyString& other) {
        std::cout << "Copy constructor\n";
        if (other.data) {
            size_t len = std::strlen(other.data) + 1;
            data = new char[len];
            std::memcpy(data, other.data, len);
        } else {
            data = nullptr;
        }
    }

    // Move constructor
    MyString(MyString&& other) noexcept {
        std::cout << "Move constructor\n";
        data = other.data;     // steal
        other.data = nullptr;  // leave valid but unspecified
    }

    // Destructor
    ~MyString() {
        std::cout << "Destructor\n";
        delete[] data;
    }
};

int main() {
    std::cout << "=== Creating s1 ===\n";
    MyString s1("hello");

    std::cout << "Address of s1.data = " << static_cast<void*>(s1.data) << "\n\n";

    std::cout << "=== Moving s1 into s2 ===\n";
    MyString s2 = std::move(s1);

    std::cout << "Address of s2.data = " << static_cast<void*>(s2.data) << "\n";
    std::cout << "Address of s1.data after move = " << static_cast<void*>(s1.data) << "\n\n";

    if (s1.data == nullptr)
        std::cout << "s1 is now in a moved-from state (data == nullptr)\n";
    else
        std::cout << "s1 still has data: " << s1.data << "\n";

    return 0;
}
/*
=== Creating s1 ===
Construct from const char*
Address of s1.data = 0x245166c0

=== Moving s1 into s2 ===
Move constructor
Address of s2.data = 0x245166c0
Address of s1.data after move = 0

s1 is now in a moved-from state (data == nullptr)
Destructor
Destructor
*/
/* ------------------------------------------ */



✔️ std::move vs. Actual Move Construction
Remember:
❌ std::move does NOT move
✔️ Move constructors / move assignments perform movement
Practical Example (with prints)
#include <iostream>
#include <utility>
class A {
  public:
    A() { 
        std::cout << "Default\n"; 
    }
    A(const A&) { 
        std::cout << "Copy\n"; 
    }
    A(A&&) noexcept { 
        std::cout << "Move\n"; 
    }
};
int main() {
    A a;
    A b = std::move(a);  // prints Move
   return 0;
}

Output:
Default
Move

Because std::move(a) converts a into an rvalue.




When NOT to use std::move
❌ Don’t move from a variable if you still need it:
std::string s = "hello";
foo(std::move(s));     // OK
std::cout << s;        // UB? No. But unspecified.

❌ Don’t move a local when returning (C++17+)
return std::move(x);   // BAD: prevents NRVO
return x;              // GOOD: NRVO + move fallback

/* 1. When NOT to use std::move--------------------------------------------- */
❌ Why you should NOT use std::move if you still need the variable afterward.
It shows that the moved-from object is valid but unspecified, meaning you can read it safely, but its contents are not guaranteed.

#include <iostream>
#include <string>
using namespace std;
void foo(std::string s) {
    cout << "Inside foo, received: " << s <<endl;
}
int main() {
    string s = "hello";
    cout << "Before move: s = " << s << endl;
    foo(move(s));  // move from s into foo() parameter
    cout << "After move: s = \"" << s << "\" (valid but unspecified)"<<endl;
  return 0;
}
/*
Before move: s = hello
Inside foo, received: hello
After move: s = "" (valid but unspecified)  
*/

✅ What This Demonstrates
✔ Before move:
s = "hello"

✔ Move happens inside foo(std::string)
std::move(s) casts s to an rvalue

Move constructor of std::string transfers the internal buffer
s becomes “moved-from” (still valid, but unspecified)

✔ After move:
s = ""   // usually empty, but not guaranteed
The program prints whatever state the implementation leaves inside s.


/* 2. When NOT to use std::move--------------------------------------------- */

❌ Returning std::move(x) prevents NRVO (Bad)
✔ Returning x allows NRVO (Good)
You will clearly see when the move constructor is called and when NRVO eliminates all copies/moves.

#include <iostream>
#include <string>
using namespace std;
class Demo {
  public:
    string msg;
    Demo(const string& m) : msg(m) {
        cout << "Constructor\n";
    }
    Demo(const Demo& other) : msg(other.msg) {
        cout << "Copy constructor\n";
    }
    Demo(Demo&& other) noexcept : msg(std::move(other.msg)) {
        cout << "Move constructor\n";
    }
    ~Demo() {
        cout << "Destructor\n";
    }
};
// ----------------------------------
// BAD: Using std::move blocks NRVO
// ----------------------------------
Demo make_bad() {
    cout << "\n--- make_bad() ---\n";
    Demo d("Returning with std::move");
   return std::move(d);   // BAD: Forces move; NRVO disabled
}
// ----------------------------------
// GOOD: Let NRVO happen
// ----------------------------------
Demo make_good() {
    cout << "\n--- make_good() ---\n";
    Demo d("Returning without std::move");
   return d;     // GOOD: NRVO (no copy/move)
}
int main() {
    cout << "\n=== Calling make_good (NRVO) ===\n";
    Demo g = make_good();   // No move constructor called

    cout << "\n=== Calling make_bad (Forced move) ===\n";
    Demo b = make_bad();    // Move constructor is called

    cout << "\nProgram finished\n";
  return 0;
}
/*
=== Calling make_good (NRVO) ===

--- make_good() ---
Constructor

=== Calling make_bad (Forced move) ===

--- make_bad() ---
Constructor
Move constructor
Destructor

Program finished
Destructor
Destructor
*/

💡 What You Will See in Output
✔ make_good() — NRVO happens
Constructor
(no copy or move constructor message)

❌ make_bad() — NRVO is blocked
Constructor
Move constructor   <-- printed because std::move forces a move

📌 Why is return x; better?
return x;

Compiler performs NRVO → constructs directly in the caller’s variable
Zero copies
Zero moves

return std::move(x);
Forces object to be treated as rvalue
Compiler is NOT allowed to apply NRVO
Must call move constructor


/* --------------------------------------------- */
#include <iostream>
#include <string>
using namespace std;
class Demo {
  public:
    string msg;
    Demo(const string& m) : msg(m) {
        cout << "Constructor\n";
    }
    Demo(const Demo& other) : msg(other.msg) {
        cout << "Copy constructor\n";
    }
    Demo(Demo&& other) noexcept : msg(std::move(other.msg)) {
        cout << "Move constructor\n";
    }
    ~Demo() {
      cout << "Destructor\n";
    }
};
// -------------------------------
// Example 1:
// Moving from a variable and using it afterwards
// -------------------------------
void use_after_move() {
    cout << "\n=== Example 1: Using object after std::move ===\n";
    string s = "hello";
    cout << "Original s = " << s << "\n";
    string t = move(s);  // move from s
    cout << "After move, t = " << t << "\n";

    cout << "After move, s = \"" << s << "\" (valid but unspecified)\n";
}
// -------------------------------
// Example 2:
// NRVO vs std::move in return
// -------------------------------
// GOOD: No std::move → NRVO happens
Demo make_demo_good() {
    cout << "\n--- make_demo_good() ---\n";
    Demo d("NRVO example");
    return d;   // NRVO (no move, no copy)
}
// BAD: std::move(x) prevents NRVO
Demo make_demo_bad() {
    cout << "\n--- make_demo_bad() ---\n";
    Demo d("Forced move example");
    return move(d);   // Forces move, NRVO blocked
}
// -------------------------------
// MAIN
// -------------------------------
int main() {
    use_after_move();

    cout << "\n=== Example 2: NRVO vs std::move ===\n";

    cout << "\nCalling make_demo_good (NRVO expected):\n";
    Demo g = make_demo_good();   // No move constructor called

    cout << "\nCalling make_demo_bad (move forced):\n";
    Demo b = make_demo_bad();    // Move constructor called

    cout << "\nProgram end\n";
  return 0;
}
/*

=== Example 1: Using object after std::move ===
Original s = hello
After move, t = hello
After move, s = "" (valid but unspecified)

=== Example 2: NRVO vs std::move ===

Calling make_demo_good (NRVO expected):

--- make_demo_good() ---
Constructor

Calling make_demo_bad (move forced):

--- make_demo_bad() ---
Constructor
Move constructor
Destructor

Program end
Destructor
Destructor
*/
/* ---------------------------------------------- */

Inside the Compiler: Value Categories
Lvalue → named objects
Rvalue → temporary objects
Xvalue → “eXpiring” values (rvalue with identity)

std::move(x) creates an xvalue.
This affects overload resolution:
void f(const A&);  // 1
void f(A&&);       // 2

A a;
f(a);              // calls (1)
f(std::move(a));   // calls (2)



/* ---------------------------------- */
The complete runnable C++ program demonstrating:
lvalue, rvalue, xvalue
how std::move(x) creates an xvalue
how overload resolution chooses the correct function



#include <iostream>
#include <utility>   // for std::move
using namespace std;
class A {
   public:
    A() { 
        cout << "A constructed"<<endl;
    }
    A(const A&) { 
        cout << "A copy-constructed"<<endl;
    }
    A(A&&) noexcept {
        cout << "A move-constructed"<<endl;
    }
};
void f(const A&) {
    cout << "f(const A&) called (lvalue overload)"<<endl;
}
void f(A&&) {
    cout << "f(A&&) called (rvalue/xvalue overload)"<<endl;
}
int main() {
    A a;      // 'a' is an lvalue (has a name)

    cout << "\nCalling f(a): "<<endl;
    f(a);     // lvalue → calls f(const A&)

    cout << "\nCalling f(std::move(a)): "<<endl;
    f(std::move(a));   // xvalue → calls f(A&&)

    cout << "\nCalling f(A()): "<<endl;
    f(A());   // temporary → rvalue → calls f(A&&)

   return 0;
}
/*
A constructed

Calling f(a): 
f(const A&) called (lvalue overload)

Calling f(std::move(a)): 
f(A&&) called (rvalue/xvalue overload)

Calling f(A()): 
A constructed
f(A&&) called (rvalue/xvalue overload)
*/

/* ---------------------------------------------------------------------------------- */
NRVO = Named Return Value Optimization

NRVO is a compiler optimization in C++ where the compiler constructs the return object directly in the caller’s space, 
avoiding unnecessary copies or moves.

🔍 Meaning
Named Return Value Optimization
= An optimization where a named variable (like x) inside a function is constructed directly into the return value of the caller.

🔧 Example Without NRVO (conceptually)
MyType f() {
    MyType x;   // x created here
    return x;   // copy or move x
}

Normally, returning x would require:
Construct x
Copy/move x into the caller
/* ---------------------------------- */

This demonstrates:
Object constructed inside the function
Returned object is copied or moved to caller
No NRVO optimization (conceptually)

#include <iostream>
using namespace std;
struct MyType {
    MyType() {
        cout << "MyType constructed\n";
    }
    MyType(const MyType&) {
        cout << "MyType copy-constructed\n";
    }
    MyType(MyType&&) noexcept {
        cout << "MyType move-constructed\n";
    }
    ~MyType() {
        cout << "MyType destroyed\n";
    }
};
MyType f() {
    MyType x;                // Constructed here
    cout << "Returning x (no NRVO conceptually)\n";
   return x;                 // Must copy or move x
}
int main() {
    cout << "Calling f()...\n";
    MyType obj = f();         // Copy or move from returned value
  return 0;
}
/*
Calling f()...
MyType constructed
Returning x (no NRVO conceptually)
MyType destroyed
*/


/* --------------------------------- */
✔️ With NRVO
The compiler instead does:
Construct x directly in the return object, eliminating copy/move entirely.
No constructor call for copying/moving happens.

/* --------------------------------- */
the complete program that demonstrates NRVO (Named Return Value Optimization).

With NRVO:
The compiler constructs the return value directly in the caller’s storage.
NO copy constructor
NO move constructor
Only the default constructor is called.

To force the compiler to actually show NRVO behavior, this program is written normally.
(If compiled with optimizations on, NRVO will almost always occur.)

/* --------------------------------- */
#include <iostream>
using namespace std;
class MyType {
   public:
    MyType() {
        cout << "MyType constructed\n";
    }
    MyType(const MyType&) {
        cout << "MyType copy-constructed\n";
    }
    MyType(MyType&&) noexcept {
        cout << "MyType move-constructed\n";
    }
    ~MyType() {
        cout << "MyType destroyed\n";
    }
};
MyType f() {
    MyType x;   // Constructed here
    cout << "Returning x (NRVO expected)\n";
  return x;   // With NRVO: NO copy/move
}
int main() {
    cout << "Calling f()...\n";
    MyType obj = f();   // NRVO: x constructed directly into obj
  return 0;
}
/*
Calling f()...
MyType constructed
Returning x (NRVO expected)
MyType destroyed



Notice:
No copy-constructed
No move-constructed

Only:
construction of the final object
destruction at program end
Because NRVO elided (removed) the extra temporary object.
*/

/* --------------------------------- */

🟢 Why “DON’T use std::move(x)” when returning a local?
Because:
return std::move(x);   // BAD

tells the compiler:
Use move semantics, do not optimize this!
So NRVO becomes impossible, and the move constructor is forced.

✔️ Correct (NRVO allowed)
return x;   // NRVO happens, no move needed


/* ------------------------------ */
A complete C++ program that demonstrates exactly what this rule means:
Returning x → NRVO happens → NO move constructor called.
Returning std::move(x) → NRVO blocked → move constructor is forced.
This will help you visualize why you should NOT write return std::move(x).


#include <iostream>
using namespace std;
class MyType {
  public:
    MyType() {
        cout << "MyType constructed\n";
    }
    MyType(const MyType&) {
        cout << "MyType copy-constructed\n";
    }
    MyType(MyType&&) noexcept {
        cout << "MyType move-constructed\n";
    }
    ~MyType() {
        cout << "MyType destroyed\n";
    }
};
// ------------------------------------------
// Case 1: NRVO happens (good)
// ------------------------------------------
MyType good() {
    MyType x;              // local object
    cout << "Returning x (NRVO allowed)\n";
   return x;              // NRVO — no move, no copy
}
// ------------------------------------------
// Case 2: std::move blocks NRVO (bad)
// ------------------------------------------
MyType bad() {
    MyType x;              // local object
    cout << "Returning std::move(x) (NRVO disabled)\n";
   return std::move(x);   // forces move constructor → BAD
}
int main() {
    cout << "=== Calling good() ===\n";
    MyType a = good();     // NRVO, no move
    cout << "\n=== Calling bad() ===\n";
    MyType b = bad();      // Move constructor called
  return 0;
}
/*
=== Calling good() ===
MyType constructed
Returning x (NRVO allowed)

=== Calling bad() ===
MyType constructed
Returning std::move(x) (NRVO disabled)
MyType move-constructed
MyType destroyed
MyType destroyed
MyType destroyed
*/