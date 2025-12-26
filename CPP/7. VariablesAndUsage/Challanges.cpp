✅ Challenge 1 — Pass-by-value vs Pass-by-reference performance + effect
#include <iostream>
#include <vector>
using namespace std;
int sum_by_value(vector<int> v) {        // COPY
    return v[0] + v[1];
}
int sum_by_ref(const vector<int>& v) {   // NO COPY
    return v[0] + v[1];
}
int main() {
    vector<int> v = {10, 20};

    cout << "By Value sum  = " << sum_by_value(v) << "\n";
    cout << "By Ref sum    = " << sum_by_ref(v) << "\n";
}
/* 
Output
By Value sum  = 30
By Ref sum    = 30

Explanation
Pass-by-value copies entire vector → expensive.
Pass-by-reference-to-const avoids copying → efficient.
*/


✅ Challenge 2 — Modify using pass-by-reference
#include <iostream>
using namespace std;

void increment(int& x) { x++; }

int main() {
    int a = 5;
    increment(a);
    cout << "a = " << a << "\n";
}
/* 
Output
a = 6
*/


✅ Challenge 3 — const reference prevents modification
#include <iostream>
using namespace std;
void show(const int& x) {
    cout << "x = " << x << "\n";
    // x++;  // ❌ Compile error
}
int main() {
    int a = 10;
    show(a);
}
/* 
Output
x = 10
*/


✅ Challenge 4 — Return type deduction using decltype
#include <iostream>
using namespace std;
int x = 100;
double y = 3.14;
// return type is deduced from expression type
auto compute() -> decltype(x + y) {
    return x + y;
}
int main() {
    cout << compute() << "\n";
}
/* 
Output
103.14
*/



✅ Challenge 5 — Function overloading with const vs non-const reference
#include <iostream>
using namespace std;
void print(int& x) {
    cout << "non-const ref\n";
}
void print(const int& x) {
    cout << "const ref\n";
}
int main() {
    int a = 10;
    const int b = 20;

    print(a);  // non-const
    print(b);  // const

    print(30); // temporary → const-ref overload
}
/* 
Output
non-const ref
const ref
const ref
*/


✅ Challenge 6 — Perfect forwarding (universal reference + decltype)
#include <iostream>
#include <utility>
using namespace std;
template<typename T>
void wrapper(T&& val) {
    cout << "Type: " << (is_lvalue_reference<T>::value ? "Lvalue" : "Rvalue") << "\n";
}
int main() {
    int a = 10;
    wrapper(a);     // lvalue
    wrapper(50);    // rvalue
}
/* 
Output
Type: Lvalue
Type: Rvalue
*/


✅ Challenge 7 — Using decltype(auto) return type
#include <iostream>
using namespace std;
int& get_ref(int& x) { return x; }
decltype(auto) identity(int& x) {   // returns int&
    return get_ref(x);
}
int main() {
    int a = 5;
    identity(a) = 99;
    cout << a << "\n";
}
/* 
Output
99
*/


✅ Challenge 8 — constexpr + const correctness
#include <iostream>
using namespace std;
constexpr int square(int x) {
    return x * x;
}
int main() {
    constexpr int a = square(10);
    cout << a << "\n";
}
/* 
Output
100
*/


✅ Challenge 9 — Using const pointer vs pointer-to-const
#include <iostream>
using namespace std;
int main() {
    int a = 10, b = 20;

    const int* ptr1 = &a;   // ptr1 points to const int
    // *ptr1 = 30;  ❌ error

    int* const ptr2 = &a;   // const pointer
    *ptr2 = 40;             // valid
    // ptr2 = &b;   ❌ cannot reassign

    cout << *ptr1 << " " << *ptr2 << "\n";
}
/* 
Output
10 40
*/




✅ Challenge 10 — decltype on variables, expressions, functions
#include <iostream>
using namespace std;
int func() { return 5; }
int main() {
    int a = 10;
    double d = 3.5;

    decltype(a) x = 100;       // int
    decltype(d + a) y = 12.5;  // double (expression type)

    decltype(func()) z = 50;   // int

    cout << x << " " << y << " " << z << "\n";
}
/* 
Output
100 12.5 50
*/








Challenge 1 — Reference collapsing rules (T& & vs T&& &)
// ch01_ref_collapsing.cpp
#include <iostream>
using namespace std;

template<typename T>
void f(T&&) { cout << "f(T&&) called\n"; }

int main() {
    int x = 1;
    f(x);          // T = int& -> f(int& &&) -> f(int&)
    f(std::move(x)); // T = int -> f(int&&)
}


Output

f(T&&) called
f(T&&) called


Explanation: Template T&& is a forwarding reference. When passed an lvalue x, T deduces to int& and reference-collapsing yields int&. With std::move(x) it deduces int so we get int&&. Concept: reference collapsing / universal refs.

Challenge 2 — Perfect forwarding preserves value category
// ch02_forwarding.cpp
#include <iostream>
#include <utility>
using namespace std;

void g(int&){ cout<<"g(int&)\n"; }
void g(int&&){ cout<<"g(int&&)\n"; }

template<typename T>
void wrapper(T&& t) { g(std::forward<T>(t)); }

int main(){
    int a=0;
    wrapper(a);          // calls g(int&)
    wrapper(5);          // calls g(int&&)
}


Output

g(int&)
g(int&&)


Explanation: std::forward<T> forwards exact category. Without forward, rvalue would become lvalue in some contexts.

Challenge 3 — decltype on lvalue vs prvalue vs xvalue
// ch03_decltype_categories.cpp
#include <iostream>
using namespace std;

int foo() { return 5; }

int main(){
    int a = 0;
    decltype(a) x = a;                // int
    decltype((a)) y = a;              // int& (note extra parentheses)
    decltype(foo()) z = foo();        // int (prvalue)
    cout << typeid(x).name() << " " << typeid(y).name() << " " << typeid(z).name() << "\n";
    cout << x << " " << y << " " << z << "\n";
}


Output (type names implementation-defined, values deterministic)

i i i
0 0 5


Explanation: decltype(expr) yields reference type for lvalue expressions ((a)), plain type for prvalues. Important trick: decltype((a)) gives T&.

Challenge 4 — decltype(auto) return preserves reference
// ch04_decltype_auto_return.cpp
#include <iostream>
using namespace std;

int& get_ref(int& x){ return x; }
decltype(auto) identity(int& x){ return get_ref(x); }

int main(){
    int a=10;
    identity(a) = 20; 
    cout << a << "\n";
}


Output

20


Explanation: decltype(auto) deduces the exact return type including references; here it becomes int&, so assignment modifies a.

Challenge 5 — Const-correctness: overload resolution (const vs non-const)
// ch05_const_overload.cpp
#include <iostream>
using namespace std;

void f(int&){ cout<<"non-const\n"; }
void f(const int&){ cout<<"const\n"; }

int main(){
    int a=1;
    const int b=2;
    f(a);    // non-const
    f(b);    // const
    f(3);    // const (prvalue binds to const&)
}


Output

non-const
const
const


Explanation: Overload resolution chooses non-const for non-const lvalues; temporaries and const lvalues bind to const &.

Challenge 6 — auto&& as universal reference and template-free forwarding
// ch06_auto_forward.cpp
#include <iostream>
#include <type_traits>
using namespace std;

int main(){
    int x=1;
    auto&& a = x;            // lvalue -> a is int&
    auto&& b = 2;            // prvalue -> b is int&&
    cout << is_lvalue_reference<decltype(a)>::value << " " 
         << is_rvalue_reference<decltype(b)>::value << "\n";
}


Output

1 1


Explanation: auto&& deduces to an lvalue-ref for lvalues and rvalue-ref for prvalues. Useful for generic code without templates.

Challenge 7 — const member function vs non-const (overloading)
// ch07_const_member.cpp
#include <iostream>
using namespace std;

struct S {
    void show() { cout<<"non-const\n"; }
    void show() const { cout<<"const\n"; }
};

int main(){
    S s;
    const S cs;
    s.show();   // non-const
    cs.show();  // const
}


Output

non-const
const


Explanation: const qualifier on member functions affects overload resolution based on object constness.

Challenge 8 — mutable permits modification in const functions
// ch08_mutable.cpp
#include <iostream>
using namespace std;

struct Counter {
    mutable int cnt = 0;
    void mark() const { ++cnt; }
};

int main(){
    const Counter c;
    c.mark();
    cout << c.cnt << "\n";
}


Output

1


Explanation: mutable allows modification even in const objects (useful for caching/logging inside logical-const methods).

Challenge 9 — const_cast to call non-const method (safe only if underlying object non-const)
// ch09_const_cast.cpp
#include <iostream>
using namespace std;

struct X { void inc(){ ++v; } int v=0; };

void call_nonconst(const X& x){
    X& nx = const_cast<X&>(x);
    nx.inc();
}

int main(){
    X x;
    call_nonconst(x);
    cout << x.v << "\n";
}


Output

1


Explanation: const_cast removes constness — safe only when original object is non-const. Undefined behavior if original truly const.

Challenge 10 — noexcept specification and noexcept(expr)
// ch10_noexcept.cpp
#include <iostream>
#include <utility>
using namespace std;

void may_throw() noexcept(false) {}
void never() noexcept(true) {}

template<typename T>
void wrapper(T&& t) noexcept(noexcept(t())) {
    cout << "wrapper noexcept = " << noexcept(t()) << "\n";
    t();
}

int main(){
    wrapper([](){ never(); });       // true
    wrapper([](){ may_throw(); });   // false
}


Output

wrapper noexcept = 1
wrapper noexcept = 0


Explanation: noexcept(expr) can be used to compute whether a function is noexcept; propagate property with templates.

Challenge 11 — Return type SFINAE with decltype trailing return
// ch11_sfinae_decltype.cpp
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
auto add_if_possible(T a, T b) -> decltype(a + b) {
    return a + b;
}

int main(){
    cout << add_if_possible(1,2) << "\n";
    cout << add_if_possible(1.5, 2.5) << "\n";
}
/* 
Output
3
4

Explanation: Trailing decltype deduces return type; SFINAE can be combined to disable for non-addable types.
*/



Challenge 12 — Forwarding arrays vs pointers (decay issue)
// ch12_array_decay.cpp
#include <iostream>
using namespace std;

template<typename T>
void print_size(T&& t){
    cout << sizeof(t) << "\n";
}

int main(){
    int arr[10];
    print_size(arr);           // T deduces to int(&)[10], no decay for template reference
    print_size(std::move(arr)); // still reference to array (rvalue ref to array)
    int* p = arr;
    print_size(p);             // pointer size
}
/* 
Output (sizes platform-dependent; typical 40 for 10 ints on 4-byte ints? actually sizeof(arr) 
when T is reference type is size of array type when used in sizeof of parameter? 
Here sizeof(t) where t is reference to array gives size of array type)

40
40
8

Explanation: Passing arr to a template by forwarding reference preserves array type (no decay) — handy when you need length at compile/run time.
*/



Challenge 13 — std::reference_wrapper to store references in containers
// ch13_ref_wrapper.cpp
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main(){
    int a=1,b=2;
    vector<reference_wrapper<int>> v;
    v.push_back(ref(a));
    v.push_back(ref(b));
    v[0].get() = 10;
    cout << a << " " << b << "\n";
}
/* 
Output
10 2

Explanation: Containers cannot hold raw references; use std::reference_wrapper to store references in containers.
*/



Challenge 14 — Function template with decltype(auto) and perfect forwarding of return
// ch14_forwarding_return.cpp
#include <iostream>
#include <utility>
using namespace std;
int& foo(int& x){ return x; }
template<typename F, typename... Args>
decltype(auto) call(F&& f, Args&&... args){
    return std::forward<F>(f)(std::forward<Args>(args)...);
}
int main(){
    int a=5;
    call(foo, a) = 99;
    cout << a << "\n";
}
/* 
Output
99

Explanation: decltype(auto) preserves function return category; assignment modifies original.
*/



Challenge 15 — constexpr variable and functions (C++17)
// ch15_constexpr_var.cpp
#include <iostream>
using namespace std;
constexpr int square(int x){ return x*x; }
constexpr int v = square(7);
int main(){
    cout << v << "\n";
}
/* 
Output
49

Explanation: constexpr variables computed at compile time and can be used where constant expressions required.
*/



Challenge 16 — Structured bindings and auto&/const auto& usage
// ch16_struct_bindings.cpp
#include <iostream>
#include <tuple>
using namespace std;

int main(){
    tuple<int,int> t{1,2};
    auto& [x,y] = t;
    x = 10;
    cout << get<0>(t) << " " << get<1>(t) << "\n";

    const auto& [c1,c2] = t;
    cout << c1 << " " << c2 << "\n";
}
/* 
Output
10 2
10 2

Explanation: Structured bindings can bind by reference; const auto& enforces constness.
*/


Challenge 17 — auto return type deduction + reference collapsing pitfalls
// ch17_auto_return_ref.cpp
#include <iostream>
using namespace std;

int& get_static(){ static int v=1; return v; }

auto bad() { return get_static(); }        // returns int (prvalue copy) if not decltype(auto)
decltype(auto) good() { return get_static(); } // returns int&

int main(){
    bad() = 5;    // modifies temporary -> no effect on static
    cout << get_static() << "\n"; // still 1
    good() = 7;
    cout << get_static() << "\n"; // now 7
}
/* 
Output
1
7

Explanation: auto return copies; decltype(auto) preserves reference. Important when returning static or member references.
*/



Challenge 18 — Overload resolution with std::initializer_list and auto
// ch18_init_list.cpp
#include <iostream>
#include <initializer_list>
using namespace std;

void f(std::initializer_list<int>) { cout << "init_list\n"; }
template<typename T>
void f(T) { cout << "template\n"; }

int main(){
    f({1,2,3});    // prefers initializer_list overload
    f(10);         // template
}
/* 
Output
init_list
template

Explanation: Braced-init-list prefers initializer_list overload; affects overload choices.
*/




Challenge 19 — volatile usage demo (simple)
// ch19_volatile.cpp
#include <iostream>
using namespace std;
volatile int flag = 0;
int main(){
    flag = 1;
    if(flag) cout << "flag set\n";
    else cout << "flag not set\n";
}
/* 
Output
flag set

Explanation: volatile tells the compiler variable might change unexpectedly (hardware/threads/ISR). 
It prevents certain optimizations; use sparingly.
*/


Challenge 20 — Perfect forwarding with overload set selection (value vs container)
// ch20_overload_forwarding.cpp
#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

void process_value(int x){ cout<<"value: "<<x<<"\n"; }
template<typename C> void process_value(const C& c){ cout<<"container size: "<<c.size()<<"\n"; }

template<typename T>
void accept(T&& t){
    process_value(std::forward<T>(t));
}
int main(){
    int v = 42;
    vector<int> vec{1,2,3};
    accept(v);   // picks value overload
    accept(vec); // picks container overload
}
/* 
Output
value: 42
container size: 3

Explanation: Overload resolution picks best match after forwarding; 
keep in mind forwarding preserves cv/ref qualifiers so overload set can differentiate containers vs scalars.
*/




