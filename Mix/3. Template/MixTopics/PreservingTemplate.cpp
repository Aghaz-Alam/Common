Preserving a template type in C++ usually means ensuring that a function or class 
keeps the exact type a caller provides—including references, const-qualifiers, 
and value categories—without unwanted decay or deduction changes.

Below are the correct and idiomatic ways to preserve template types depending on 
the situation.
/* ----------------------------------------------------------------------- */
✅ 1. Use auto&& with std::forward (Perfect Forwarding)
Use this when writing forwarding helpers or wrapper functions.

template <typename T>
void wrapper(T&& value) {
    helper(std::forward<T>(value));
}


T&& in a template context is a forwarding reference.
It preserves:
lvalue vs rvalue
const / volatile
references

/* ------------------------------------- */
#include <iostream>
#include <utility>

// The function we will forward to
void helper(int& x) {
    std::cout << "helper(int&): lvalue\n";
}

void helper(const int& x) {
    std::cout << "helper(const int&): const lvalue\n";
}

void helper(int&& x) {
    std::cout << "helper(int&&): rvalue\n";
}

// Forwarding wrapper
template <typename T>
void wrapper(T&& value) {
    // Perfectly forward the value to helper()
    helper(std::forward<T>(value));
}

int main() {
    int a = 10;
    const int b = 20;

    wrapper(a);        // lvalue → helper(int&)
    wrapper(b);        // const lvalue → helper(const int&)
    wrapper(30);       // rvalue → helper(int&&)

    int&& r = 40;
    wrapper(std::move(r));  // xvalue → helper(int&&)

    return 0;
}
/*
helper(int&): lvalue
helper(const int&): const lvalue
helper(int&&): rvalue
helper(int&&): rvalue
*/
/* ----------------------------------- */
#include <iostream>
#include <utility>

void helper(auto&& v) {
    std::cout << "Type preserved!\n";
}

template <typename T>
void wrapper(T&& value) {
    helper(std::forward<T>(value));
}

int main() {
    int x = 5;
    wrapper(x);
    wrapper(42);
}
/* 
Output: C++20

Type preserved!
Type preserved!
*/


/* ----------------------------- */

#include <iostream>
#include <utility>

// simple name instead of 'helper'
void printType(auto&& v) {
    std::cout << "Type preserved!\n";
}

// simple name instead of 'wrapper'
template <typename T>
void forwardValue(T&& value) {
    printType(std::forward<T>(value));
}

int main() {
    int x = 5;

    forwardValue(x);   // lvalue
    forwardValue(42);  // rvalue
}
/*
Type preserved!
Type preserved!
*/

/* ----------------------------------------------------------------------- */

✅ 2. Use const T& to preserve type without copying
If you don’t need perfect forwarding, but want to avoid decaying:

template <typename T>
void printType(const T& value) {
    std::cout << typeid(T).name() << "\n";
}

This keeps the template parameter exactly as passed (except you strip value category).


/* ------------------------------- */
#include <iostream>
#include <typeinfo> // for typeid

// Function to print the type of the parameter
template <typename T>
void printType(const T& value) {
    std::cout << "Type: " << typeid(T).name() << "\n";
}

int main() {
    int a = 10;
    const int b = 20;
    int arr[3] = {1, 2, 3};

    printType(a);    // int
    printType(b);    // const int
    printType(arr);  // int[3] → decays to int* if not const T&

    return 0;
}
/*
Type: i
Type: i
Type: A3_i
*/

/* ----------------------------------------------------------------------- */
✅ 3. Avoid type-decay by not using plain auto
This is wrong if you want to preserve qualifiers:
auto x = expr;    // ❌ const, reference, and arrays decay

Use:
auto& x = expr;        // preserves reference
const auto& x = expr;  // preserves const + reference
auto&& x = expr;       // preserves everything (universal ref)


/* -------------------------------- */
#include <iostream>
#include <type_traits>

int main() {
    const int a = 10;
    int b = 20;
    int arr[3] = {1, 2, 3};

    // ❌ Plain auto decays types
    auto x = a;      // const removed, becomes int
    auto y = arr;    // array decays to int*

    std::cout << "x type (auto): " << typeid(x).name() << "\n";
    std::cout << "y type (auto): " << typeid(y).name() << "\n";

    // ✅ Preserve reference
    auto& ref_b = b;           // lvalue reference
    const auto& cref_a = a;    // const lvalue reference
    auto&& uni_arr = arr;      // preserves array type

    std::cout << "ref_b type (auto&): " << typeid(ref_b).name() << "\n";
    std::cout << "cref_a type (const auto&): " << typeid(cref_a).name() << "\n";
    std::cout << "uni_arr type (auto&&): " << typeid(uni_arr).name() << "\n";

    // Modify through reference
    ref_b = 30;
    std::cout << "Modified b via ref_b: " << b << "\n";

    return 0;
}
/*
x type (auto): i
y type (auto): Pi
ref_b type (auto&): i
cref_a type (const auto&): i
uni_arr type (auto&&): A3_i
Modified b via ref_b: 30
*/

/* ----------------------------------------------------------------------- */
✅ 4. If you want to capture a type, use type_identity (C++20)
Sometimes template argument deduction interferes with preservation.
You can force the type to be preserved:

template <typename T>
void foo(std::type_identity_t<T> value);

This prevents template parameter substitution from altering the type.

/* ---------------------------- */
#include <iostream>
#include <type_traits> // for std::type_identity
#include <typeinfo>

template <typename T>
void foo(std::type_identity_t<T> value) {
    std::cout << "Type preserved: " << typeid(T).name() << "\n";
}

int main() {
    int x = 42;
    const int y = 10;
    int arr[3] = {1, 2, 3};

    foo<int>(x);       // T = int
    foo<const int>(y); // T = const int
    foo<decltype(arr)>(arr); // T = int[3], array preserved

  return 0;
}

/*
Output: C++20

Type preserved: i
Type preserved: i
Type preserved: A3_i
*/


/* ----------------------------------------------------------------------- */
✅ 5. To store the type for later use, use a template parameter or alias
template <typename T>
struct Holder {
    using type = T;  // preserves exactly the type
};


/* ------------------------------- */
#include <iostream>
#include <type_traits>

// Template that stores a type
template <typename T>
struct Holder {
    using type = T;  // preserves exactly the type
};

// Example usage
int main() {
    // Store the type int
    Holder<int>::type a = 42;

    // Store the type double
    Holder<double>::type b = 3.14;

    // Check types at compile-time
    static_assert(std::is_same_v<decltype(a), int>, "a should be int");
    static_assert(std::is_same_v<decltype(b), double>, "b should be double");

    std::cout << "a = " << a << ", b = " << b << std::endl;

    return 0;
}


/*
Output: C++20
a = 42, b = 3.14
*/

/* ----------------------------------------------------------------------- */
✅ 6. Return type preservation
If you want a function to return exactly the type of the expression:
template <typename F, typename... Args>
decltype(auto) call(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

decltype(auto) ensures:
references preserved
const preserved
returns exactly what the inner call returned

Full Example: Correct Template Type Preservation
#include <utility>
template <typename T>
void process(T&& t) {
    // T is preserved perfectly
    using Preserved = T;

    // Pass the value onward without losing its type
    forwardToSomething(std::forward<T>(t));
}


/* ------------------------- */
#include <iostream>
#include <utility>
#include <string>

// A simple function to forward the value
template <typename T>
void forwardToSomething(T&& value) {
    // Print type info at runtime (just to demonstrate)
    if constexpr (std::is_lvalue_reference_v<T>)
        std::cout << "Forwarded an lvalue: ";
    else
        std::cout << "Forwarded an rvalue: ";

    std::cout << value << std::endl;
}

// Function that perfectly preserves the type of its argument
template <typename T>
void process(T&& t) {
    using Preserved = T; // type preserved

    // Forward without losing lvalue/rvalue or const qualifiers
    forwardToSomething(std::forward<T>(t));
}

// Generic call function that preserves return type
template <typename F, typename... Args>
decltype(auto) call(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

// Example functions
int getValue() { return 42; }
int& getRef(int& x) { return x; }

int main() {
    int x = 10;

    std::cout << "Testing process with lvalue:\n";
    process(x);  // forwards as lvalue

    std::cout << "Testing process with rvalue:\n";
    process(20); // forwards as rvalue

    std::cout << "\nTesting call with function returning value:\n";
    int result = call(getValue);
    std::cout << "Result = " << result << std::endl;

    std::cout << "\nTesting call with function returning reference:\n";
    int& refResult = call(getRef, x);
    refResult = 99; // modifies original x
    std::cout << "x after modification = " << x << std::endl;

    return 0;
}



/*
Testing process with lvalue:
Forwarded an lvalue: 10
Testing process with rvalue:
Forwarded an rvalue: 20

Testing call with function returning value:
Result = 42

Testing call with function returning reference:
x after modification = 99
*/

/* ----------------------------------------------------------------------- */





Tag dispatching in C++ is a technique that uses types (usually empty structs) 
to select between different function overloads at compile time. 

It’s widely used in template metaprogramming to choose the optimal implementation 
based on type traits, iterator categories, or other compile-time information.



✅ What is Tag Dispatching?
--> Tag dispatching is a pattern where:
--> You define tag types that represent different behaviors.
--> You write overloaded functions that take these tag types.
--> A wrapper function deduces a tag at compile time (via traits) and forwards it
    to the correct overload.
--> This avoids if constexpr (older C++), runtime branching, or SFINAE-heavy code.



Simple Example: dispatch based on whether type is integral
Step 1: define tag types
struct integral_tag {};
struct non_integral_tag {};

Step 2: implement overloads
void process_impl(int x, integral_tag) {
    std::cout << "Integral version: " << x << "\n";
}

template<typename T>
void process_impl(T x, non_integral_tag) {
    std::cout << "Non-integral version: " << x << "\n";
}

Step 3: wrapper selects the tag using a trait
template<typename T>
void process(T x) {
    using tag = std::conditional_t<
        std::is_integral_v<T>,
        integral_tag,
        non_integral_tag
    >;

    process_impl(x, tag{});
}

Usage
process(5);     // Integral version
process(3.14);  // Non-integral version




Classic Example: Iterator Category Dispatching (from the STL)
Standard iterators have categories:
std::random_access_iterator_tag
std::bidirectional_iterator_tag
std::forward_iterator_tag
etc.

This allows algorithms like advance() to choose efficient code.
Overloads for iterator categories:
template<typename Iter>
void my_advance_impl(Iter& it, int n, std::random_access_iterator_tag) {
    it += n;  // optimal
}
template<typename Iter>
void my_advance_impl(Iter& it, int n, std::input_iterator_tag) {
    while (n-- > 0) ++it;  // generic
}


Wrapper that dispatches
template<typename Iter>
void my_advance(Iter& it, int n) {
    using category = typename std::iterator_traits<Iter>::iterator_category;
    my_advance_impl(it, n, category{});
}


Why Use Tag Dispatching?
✔ Compile-time dispatch (zero overhead)
✔ Cleaner than SFINAE-heavy techniques
✔ Works even before C++17 (before if constexpr)
✔ Used by STL for iterators, algorithms, traits-based optimizations


When to Use
--> Optimizing behaviour based on iterator category
--> Customizing algorithms based on type traits
--> Choosing between different code paths depending on whether types are trivially 
    copyable, integral, POD, etc.
--> Implementing generic algorithms where some types have better implementations


Modern Alternative: if constexpr (C++17+)
In many cases:
if constexpr (std::is_integral_v<T>) {
    ...
} else {
    ...
}

…but tag dispatching is still useful when:
Overloading is more natural than branching
You want to control ADL

Working in pre-C++17 codebases
Optimizing standard-library-like algorithms

/* --------------------- */
#include <iostream>
#include <type_traits>

// -----------------------------------------------------
// 1. Define tag types
// -----------------------------------------------------
struct integral_tag {};
struct non_integral_tag {};

// -----------------------------------------------------
// 2. Overloaded implementations selected by tag
// -----------------------------------------------------
void process_impl(int x, integral_tag) {
    std::cout << "Integral implementation: x * 2 = " << (x * 2) << "\n";
}

template<typename T>
void process_impl(T x, non_integral_tag) {
    std::cout << "Non-integral implementation: x / 2 = " << (x / 2) << "\n";
}

// -----------------------------------------------------
// 3. Wrapper: deduces the correct tag via type traits
// -----------------------------------------------------
template<typename T>
void process(T x) {
    using tag = std::conditional_t<
        std::is_integral_v<T>,
        integral_tag,
        non_integral_tag
    >;

    process_impl(x, tag{});
}

// -----------------------------------------------------
// 4. Demo
// -----------------------------------------------------
int main() {
    process(10);      // uses integral_tag overload
    process(3.14);    // uses non_integral_tag overload

    long long a = 42;
    process(a);       // still integral_tag

    float f = 9.5f;
    process(f);       // non_integral_tag

    return 0;
}
/*
Integral implementation: x * 2 = 20
Non-integral implementation: x / 2 = 1.57
Integral implementation: x * 2 = 84
Non-integral implementation: x / 2 = 4.75
*/
/* --------------------- */



/* ---------------------------------------------------------------- */
✅ 1. STL-style iterator tag dispatching (std::advance-like)

File: iterator_tag_dispatch.cpp

#include <iostream>
#include <iterator>
#include <vector>
#include <list>

//-----------------------------------------------
// Overloads for random-access iterators
//-----------------------------------------------
template<typename Iter>
void my_advance_impl(Iter& it, int n, std::random_access_iterator_tag) {
    std::cout << "[random-access] fast advance\n";
    it += n;
}

//-----------------------------------------------
// Overloads for input/forward/bidirectional iterators
//-----------------------------------------------
template<typename Iter>
void my_advance_impl(Iter& it, int n, std::input_iterator_tag) {
    std::cout << "[input/forward] slow advance\n";
    while (n-- > 0) ++it;
}

//-----------------------------------------------
// Dispatcher
//-----------------------------------------------
template<typename Iter>
void my_advance(Iter& it, int n) {
    using category = typename std::iterator_traits<Iter>::iterator_category;
    my_advance_impl(it, n, category{});
}

//-----------------------------------------------
int main() {
    std::vector<int> v{10,20,30,40};
    auto it1 = v.begin();
    my_advance(it1, 2);
    std::cout << "vector iterator now at: " << *it1 << "\n\n";

    std::list<int> lst{1,2,3,4};
    auto it2 = lst.begin();
    my_advance(it2, 2);
    std::cout << "list iterator now at: " << *it2 << "\n";
}
/*
[random-access] fast advance
vector iterator now at: 30

[input/forward] slow advance
list iterator now at: 3
*/



/* ------------------------------------------------ */
✅ 2. Tag dispatching with std::true_type / std::false_type

File: true_false_tag_dispatch.cpp

#include <iostream>
#include <type_traits>

void handle_impl(int x, std::true_type) {
    std::cout << "[true_type] integral: x*3 = " << x * 3 << "\n";
}

template<class T>
void handle_impl(T x, std::false_type) {
    std::cout << "[false_type] non-integral: x/3 = " << x / 3 << "\n";
}

template<class T>
void handle(T x) {
    handle_impl(x, std::is_integral<T>{});
}

int main() {
    handle(9);
    handle(3.0);
}
/* 
[true_type] integral: x*3 = 27
[false_type] non-integral: x/3 = 1
*/


/* ------------------------------------------------ */
✅ 3. Modern if constexpr comparison (C++17+)

File: if_constexpr_comparison.cpp

#include <iostream>
#include <type_traits>

template<class T>
void process(T x) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "[if constexpr] integral: x+1=" << x + 1 << "\n";
    } else {
        std::cout << "[if constexpr] non-integral: x-1=" << x - 1 << "\n";
    }
}

int main() {
    process(5);
    process(3.14);
}
/* 
[if constexpr] integral: x+1=6
[if constexpr] non-integral: x-1=2.14



Note:
This accomplishes the same idea as tag dispatching but without needing 
external tag types or overloads.
*/






/* ------------------------------------------------ */
✅ 4. Real-world tag dispatching: optimized memory operations

Uses tag dispatching to choose between fast memcpy for trivially copyable types 
and a loop copy for complex types.

File: tag_dispatch_memcopy.cpp

#include <iostream>
#include <cstring>
#include <type_traits>

//-----------------------------------------------------------
// Fast path: trivially copyable → use memcpy
//-----------------------------------------------------------
template<class T>
void copy_impl(T* dst, const T* src, size_t n, std::true_type) {
    std::cout << "[fast memcpy]\n";
    std::memcpy(dst, src, n * sizeof(T));
}

//-----------------------------------------------------------
// Slow path: non-trivial → copy using constructor/assignment
//-----------------------------------------------------------
template<class T>
void copy_impl(T* dst, const T* src, size_t n, std::false_type) {
    std::cout << "[slow element-by-element copy]\n";
    for (size_t i = 0; i < n; ++i)
        dst[i] = src[i];
}

//-----------------------------------------------------------
// Dispatcher: chooses fast or slow at compile time
//-----------------------------------------------------------
template<class T>
void optimized_copy(T* dst, const T* src, size_t n) {
    copy_impl(dst, src, n, std::is_trivially_copyable<T>{});
}

//-----------------------------------------------------------
struct NonTrivial {
    int x;
    NonTrivial(int v=0) : x(v) {}
};

int main() {
    // Trivial type — fast memcpy
    int a[5] = {1,2,3,4,5};
    int b[5];
    optimized_copy(b, a, 5);

    // Non-trivial type — slow loop copy
    NonTrivial na[3] = {1,2,3};
    NonTrivial nb[3];
    optimized_copy(nb, na, 3);

    return 0;
}
/* 
[fast memcpy]
[fast memcpy]
*/