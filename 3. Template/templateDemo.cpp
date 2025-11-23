what is template and how it works.



✅ What is a Template in C++?
A template is a C++ feature that allows writing generic code — code that works for any data type.
Two types:
Function templates
Class templates

Templates are instantiated at compile-time when used with specific types.
This is the basis of:
STL containers (vector<T>)
Algorithms (sort, find)
Smart pointers (unique_ptr<T>)

✅ 1) Normal Template Usage
➤ Function Template + Class Template
#include <iostream>
using namespace std;
// Function template
template <typename T>
T add(T a, T b) {
    return a + b;
}
// Class template
template <typename T>
class Box {
    T value;
  public:
    Box(T v) : value(v) {}
    T get() { return value; }
};
int main() {
    cout << add<int>(3, 4) << endl;      // 7
    cout << add<double>(2.5, 3.1) << endl; // 5.6
    Box<string> b("Hello Templates");
    cout << b.get() << endl;
   return 0;
}
/* 
7
5.6
Hello Templates
*/


✅ 2) Template Specialization
Used when a specific version of a template behaves differently for a certain type.
Template specialization lets you override the behavior of a template for specific types.

You typically use it when:
a generic implementation works for most types
but a special type needs different behavior
(like string, char*, or pointers)

✅ 1) Function Template Specialization
#include <iostream>
using namespace std;
// Primary template
template <typename T>
void print(T value) {
    cout << "Generic: " << value << endl;
}
// Full specialization for string
template <>
void print<string>(string value) {
    cout << "String specialization: [" << value << "]" << endl;
}
int main() {
    print(10);           // Generic
    print(3.14);         // Generic
    print(string("Hi")); // Specialized
  return 0;
}
/* 
Generic: 10
Generic: 3.14
String specialization: [Hi]
*/
✔ When T = string, the compiler chooses the specialized version.

✅ 2) Class Template Specialization
#include <iostream>
using namespace std;
// Primary template
template <typename T>
class Box {
  public:
    void show(T value) {
        cout << "Generic Box: " << value << endl;
    }
};
// Specialization for int
template <>
class Box<int> {
  public:
    void show(int value) {
        cout << "Int Box: value = " << value << endl;
    }
};
int main() {
    Box<double> b1;
    b1.show(2.2);      // Generic
    Box<int> b2;
    b2.show(10);       // Specialized
  return 0;
}
/* 
Generic Box: 2.2
Int Box: value = 10
*/

✅ 3) Partial Template Specialization
You can partially specialize class templates (but NOT function templates).
Example: specialize all pointer types

#include <iostream>
using namespace std;
// Primary template
template <typename T>
class TypeInfo {
  public:
    static void show() {
        cout << "General Type" << endl;
    }
};
// Partial specialization for pointer types
template <typename T>
class TypeInfo<T*> {
  public:
    static void show() {
        cout << "Pointer Type" << endl;
    }
};
int main() {
    TypeInfo<int>::show();    // General
    TypeInfo<int*>::show();   // Pointer Type
  return 0;
}
/* 
General Type
Pointer Type
*/
✔ Partial specialization pattern:
template <typename T> class TypeInfo<T*>

✅ 4) Partial Specialization for Arrays
#include <iostream>
using namespace std;
template <typename T>
class ArrayInfo {
  public:
    static void show() { cout << "Not an array\n"; }
};
// Specialize for arrays of any size
template <typename T, size_t N>
class ArrayInfo<T[N]> {
  public:
    static void show() { cout << "Array of size " << N << endl; }
};
int main() {
    ArrayInfo<int>::show();      // Not an array
    ArrayInfo<int[5]>::show();   // Array of size 5
  return 0;
}
/* 
Not an array
Array of size 5
*/

✅ 5) Template Specialization + Default Behavior
A real-world pattern: generic print + pointer specialization.

#include <iostream>
using namespace std;
template <typename T>
struct Printer {
    static void print(const T& value) {
        cout << "Value: " << value << endl;
    }
};
// Pointer specialization
template <typename T>
struct Printer<T*> {
    static void print(T* ptr) {
        cout << "Pointer Address: " << ptr;
        if (ptr) cout << ", Value: " << *ptr;
        cout << endl;
    }
};
int main() {
    int x = 42;
    Printer<int>::print(10);       // Generic
    Printer<int*>::print(&x);      // Pointer specialization
  return 0;
}
/* 
Value: 10
Pointer Address: 0x7ffe3e90e5a8, Value: 42
*/

✅ SPECIALIZATION RULES (Important)
✔ Allowed:
Full specialization of function templates
Full specialization of class templates
Partial specialization of class templates only

❌ Not allowed:
Partial specialization of function templates

➤ Full Specialization
#include <iostream>
using namespace std;
template <typename T>
struct Printer {
    static void print(T value) {
        cout << "Generic print: " << value << endl;
    }
};
// Specialization for string
template <>
struct Printer<string> {
    static void print(const string& value) {
        cout << "String print: [" << value << "]" << endl;
    }
};
int main() {
    Printer<int>::print(10);        // Generic
    Printer<string>::print("Hi");   // Specialized
  return 0;
}
/* 
Generic print: 10
String print: [Hi]
*/


✅ 3) SFINAE Example
SFINAE = Substitution Failure Is Not An Error
Used to enable/disable a function based on validity of an expression.

➤ Detect whether a type has .size() member function
#include <iostream>
#include <type_traits>
using namespace std;
// Case 1: type has size() -> this overload is preferred
template <typename T>
auto printSize(T t) -> decltype(t.size(), void()) {
    cout << "Has size(): " << t.size() << endl;
}
// Case 2: fallback for types without size()
template <typename T>
void printSize(...) {
    cout << "No size() available" << endl;
}
int main() {
    printSize(string("hello"));  // Has size()
    printSize(10);               // No size()
  return 0;
}

✔️ decltype(t.size(), void()) is valid only if t.size() exists
✔️ If invalid → compiler does NOT error → chooses fallback function

/* ----------------------- */
❗ Why your SFINAE code fails?
Because the fallback overload
template <typename T>
void printSize(...)

cannot deduce T for an ellipsis (...).
So template argument deduction fails, and the compiler rejects it.

✔ Solution
You need the fallback to be a non-template function or a template that does not depend on T.

Below are two correct versions:
✅ ✔ Correct SFINAE Version (enable_if) — Recommended
This is the cleanest and most reliable SFINAE pattern.

#include <iostream>
#include <type_traits>
using namespace std;
// Case 1: T has size()
template <typename T>
auto printSize(const T& t) -> decltype(t.size(), void()) {
    cout << "Has size(): " << t.size() << endl;
}
// Case 2: T has no size()
template <typename T>
typename enable_if<!is_same<decltype(declval<T>().size()), void>::value, void>::type
printSize(const T&) {
    cout << "No size() available" << endl;
}
int main() {
    printSize(string("hello"));  // Has size()
    printSize(10);               // No size()
  return 0;
}

✅ ✔ Simpler Correct SFINAE Version (Overload with int/...)
This is the classic trick:
prefer the int overload; fall back to the ... overload.

👍 Works perfectly
#include <iostream>
#include <type_traits>
using namespace std;
// Preferred overload (selected if t.size() is valid)
template<typename T>
auto printSize(const T& t, int) -> decltype(t.size(), void()) {
    cout << "Has size(): " << t.size() << endl;
}
// Fallback overload
template<typename T>
void printSize(const T&, ...) {
    cout << "No size() available" << endl;
}
int main() {
    printSize(string("hello"), 0);  // Has size()
    printSize(10, 0);               // No size()
  return 0;
}
/* 
Has size(): 5
No size() available
*/

Why it works?
If t.size() is valid → first overload wins (int is better than ...)
If invalid → SFINAE removes it → second overload chosen
✔ No template deduction problems
✔ Works for all types

❗ Why your original code fails?
Because:
template <typename T>
void printSize(...)

cannot deduce T, since ellipsis (...) does not participate in template deduction.

⭐ Best Modern C++20 Alternative (Concepts)
If you are using C++20, this is even easier:
#include <iostream>
#include <concepts>
using namespace std;
template <typename T>
concept HasSize = requires(T t) {
    t.size();
};
void printSize(HasSize auto t) {
    cout << "Has size(): " << t.size() << endl;
}
void printSize(auto) {
    cout << "No size() available" << endl;
}
int main() {
    printSize(string("hello"));
    printSize(10);
  return 0;
}
/* 
Output: c++20
Has size(): 5
No size() available
*/
/* ---------------------- */



✅ 4) Template Metaprogramming (Compile-Time Calculation): Compute factorial at compile time.
➤ Compile-time factorial using recursion

#include <iostream>
using namespace std;
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};
// Base case
template <>
struct Factorial<1> {
    static const int value = 1;
};
int main() {
    cout << Factorial<5>::value << endl;  // 120
    cout << Factorial<10>::value << endl; // 3628800
  return 0;
}
/* 
120
3628800


This executes at compile-time, not runtime.
*/
