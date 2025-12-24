//Challenge 1 — Basic class template + type deduction
#include <iostream>
using namespace std;
template<typename T>
class Box {
  public:
    T value;
    Box(T v) : value(v) {}
};

int main() {
    Box<int> a(10);
    Box<double> b(3.14);

    cout << a.value << " " << b.value << "\n";
}
/* 
✅ Output
10 3.14

Explanation
Box<int> and Box<double> generate two different classes at compile time.
*/


//Challenge 2 — Template function + automatic type deduction
#include <iostream>
using namespace std;

template<typename T>
T add(T a, T b) { return a + b; }

int main() {
    cout << add(5, 6) << "\n";         // T = int
    cout << add(2.2, 3.3) << "\n";     // T = double
}
/* 
Output
11
5.5
*/


//Challenge 3 — Full specialization
#include <iostream>
using namespace std;
template<typename T>
struct Printer {
    static void print(const T& x) { cout << "Generic: " << x << "\n"; }
};
template<>
struct Printer<string> {
    static void print(const string& x) { cout << "String specialization: " << x << "\n"; }
};
int main() {
    Printer<int>::print(10);
    Printer<string>::print("Hello");
}
/* 
Output
Generic: 10
String specialization: Hello
*/


//Challenge 4 — Partial specialization
#include <iostream>
using namespace std;
template<typename T>
struct TypeSize {
    static void print() { cout << "Size: " << sizeof(T) << "\n"; }
};
// partial specialization for pointer types
template<typename T>
struct TypeSize<T*> {
    static void print() { cout << "Pointer size: " << sizeof(T*) << "\n"; }
};
int main() {
    TypeSize<int>::print();
    TypeSize<int*>::print();
}
/* 
Output
Size: 4 or 8 (platform dependent)
Pointer size: 8 (on 64-bit)
*/

//Challenge 5 — SFINAE: enable_if on function
#include <type_traits>
#include <iostream>
using namespace std;
// only for integral types
template<typename T>
typename enable_if<is_integral<T>::value, T>::type
process(T x) {
    return x * 2;
}
// only for floating types
template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type
process(T x) {
    return x / 2;
}
int main() {
    cout << process(10) << "\n";     // integral version
    cout << process(3.2) << "\n";    // float version
}
/* 
Output
20
1.6
*/


//Challenge 6 — SFINAE: detect presence of member function
#include <iostream>
#include <type_traits>
using namespace std;
class A { public: void foo() {} };
class B {};
template<typename T>
class has_foo {
    typedef char Yes;
    typedef long No;

    template<typename U>
    static Yes test( decltype(&U::foo) );

    template<typename U>
    static No test(...);
  public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(Yes);
};
int main() {
    cout << has_foo<A>::value << "\n";
    cout << has_foo<B>::value << "\n";
}
/* 
Output
1
0
*/


//Challenge 7 — Compile-time factorial (metaprogramming recursion)
#include <iostream>
using namespace std;
template<int N>
struct Fact {
    static const int value = N * Fact<N-1>::value;
};
template<>
struct Fact<0> {
    static const int value = 1;
};
int main() {
    cout << Fact<5>::value << "\n";   // compile-time
}
/* 
Output
120
*/


//Challenge 8 — Template + Inheritance
#include <iostream>
using namespace std;
template<typename T>
class Base {
  public:
    void show() { cout << "Base<T>: " << sizeof(T) << "\n"; }
};
class Derived : public Base<int> {};
int main() {
    Derived d;
    d.show();
}
/* 
Output
Base<T>: 4
*/


//Challenge 9 — Template class storing different types
#include <iostream>
using namespace std;
template<typename A, typename B>
class Pair {
  public:
    A first;
    B second;

    Pair(A a, B b) : first(a), second(b) {}
};
int main() {
    Pair<int, string> p(10, "Hello");
    cout << p.first << " " << p.second;
}
/* 
Output
10 Hello
*/


//Challenge 10 — Template function overload priority
#include <iostream>
using namespace std;
void fun(int) { cout << "Normal int\n"; }
template<typename T>
void fun(T) { cout << "Template\n"; }
int main() {
    fun(10);      // normal wins over template
    fun(3.2);     // template version
}
/* 
Output
Normal int
Template
*/

//Challenge 11 — Template constructor behavior
#include <iostream>
using namespace std;
class X {
  public:
    template<typename T>
    X(T x) {
        cout << "Template ctor: " << x << "\n";
    }

    X(int x) {
        cout << "Normal ctor\n";
    }
};
int main() {
    X a(5);      // calls normal constructor
    X b(5.5);    // calls template constructor
}
/* 
Output
Normal ctor
Template ctor: 5.5
*/

//Challenge 12 — Template alias
#include <iostream>
using namespace std;
template<typename T>
using Vec = T*;
int main() {
    Vec<int> p = new int(20);
    cout << *p << "\n";
    delete p;
}
/* 
Output
20
*/


//Challenge 13 — CRTP (Static Polymorphism)
#include <iostream>
using namespace std;
template<typename Derived>
class Base {
  public:
    void interface() {
        static_cast<Derived*>(this)->impl();
    }
};
class Child : public Base<Child> {
  public:
    void impl() { cout << "Child::impl\n"; }
};
int main() {
    Child c;
    c.interface();
}
/* 
Output
Child::impl
*/


//Challenge 14 — Template inside template
#include <iostream>
using namespace std;
template<typename T>
class Wrapper {
  public:
    template<typename U>
    U convert(const T& x) {
        return static_cast<U>(x);
    }
};
int main() {
    Wrapper<int> w;
    cout << w.convert<double>(5);
}
/* 
Output
5
*/


//Challenge 15 — Template recursion printing tuple
#include <iostream>
#include <tuple>
using namespace std;
template<size_t I, typename... Ts>
struct Printer {
    static void print(const tuple<Ts...>& t) {
        cout << get<I>(t) << " ";
        Printer<I+1, Ts...>::print(t);
    }
};
template<typename... Ts>
struct Printer<sizeof...(Ts), Ts...> {
    static void print(const tuple<Ts...>&) {}
};
int main() {
    auto t = make_tuple(1, 2.5, "hi");
    Printer<0, int, double, const char*>::print(t);
}
/* 
Output
1 2.5 hi 
*/


//Challenge 16 — Detect type using decltype + template
#include <iostream>
using namespace std;
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
int main() {
    cout << add(5, 2.5) << "\n";  // double
}
/* 
Output
7.5
*/


//Challenge 17 — Template static members
#include <iostream>
using namespace std;
template<typename T>
struct Counter {
    static int count;
};
template<typename T>
int Counter<T>::count = 0;
int main() {
    Counter<int>::count++;
    Counter<double>::count += 2;

    cout << Counter<int>::count << " " 
         << Counter<double>::count << "\n";
}
/* 
Output
1 2
*/


//Challenge 18 — Template default parameters
#include <iostream>
using namespace std;
template<typename T = int>
class Box {
  public:
    T x = 5;
};
int main() {
    Box<> a;          // T = int
    Box<double> b;    

    cout << a.x << " " << b.x << "\n";
}
/* 
Output
5 5
*/


//Challenge 19 — Variadic template summation
#include <iostream>
using namespace std;
int sum() { return 0; }
template<typename T, typename... Rest>
int sum(T first, Rest... rest) {
    return first + sum(rest...);
}
int main() {
    cout << sum(1,2,3,4,5) << "\n";
}
/* 
Output
15
*/



//Challenge 20 — Creating objects from template + detecting their type
#include <iostream>
#include <typeinfo>
using namespace std;
template<typename T>
class Creator {
  public:
    static T create() { return T(); }
};
int main() {
    auto obj = Creator<double>::create();
    cout << "Type: " << typeid(obj).name() << "\n";
    cout << obj << "\n";
}
/* 
Output (implementation-dependent)
Type: d
0
*/




1) Concept: Addable — require types that support +
// ch01_addable_concept.cpp
#include <concepts>
#include <iostream>
using namespace std;

template<typename T>
concept Addable = requires(T a, T b) { { a + b }; };

template<Addable T>
T add(T a, T b) { return a + b; }

int main(){
    cout << add(2,3) << "\n";        // OK
    cout << add(2.5, 3.5) << "\n";   // OK
    // struct S{}; add(S{}, S{});   // compile error if uncommented
}
/* 
Output
5
6

Why: simple concept that constraints templates to types supporting operator+.
*/



2) Constrained overload resolution (use concepts to prefer one overload)
// ch02_overload_concepts.cpp
#include <concepts>
#include <iostream>
using namespace std;

template<typename T>
concept Integral = std::is_integral_v<T>;

void print(Integral auto x) { cout << "Integral: " << x << "\n"; }
void print(auto x)          { cout << "Generic: " << x << "\n"; }

int main(){
    print(10);    // Integral overload
    print(3.14);  // generic overload
}
/* 
Output
Integral: 10
Generic: 3.14

Why: concepts let you control overload priority cleanly.
*/


3) Fold-expression to compute product of arguments (variadic)
// ch03_fold_product.cpp
#include <iostream>
using namespace std;
template<typename... Ts>
constexpr auto product(Ts... xs) {
    return (xs * ... * 1);
}
int main(){
    cout << product(2,3,4) << "\n";   // 24
    cout << product(5) << "\n";       // 5
}
/* 
Output
24
5

Why: fold expression over * with identity 1.
*/


4) Logical fold-expression (all_of / any_of)
// ch04_fold_logical.cpp
#include <iostream>
using namespace std;

template<typename... Bools>
constexpr bool all(Bools... bs) { return (bs && ...); }

template<typename... Bools>
constexpr bool any(Bools... bs) { return (bs || ...); }

int main(){
    cout << all(true, true, false) << " " << any(false,false,true) << "\n";
}
/* 
Output
0 1
*/


5) void_t + detection idiom (modern is_detected) via TMP
// ch05_is_detected.cpp
#include <type_traits>
#include <iostream>
using namespace std;

template <class, template<class> class, class = void>
struct is_detected : std::false_type {};

template <class T, template<class> class Op>
struct is_detected<T, Op, std::void_t<Op<T>>> : std::true_type {};

// Op: detect member `size_type` (just as example)
template<class T> using has_size_type_t = typename T::size_type;

struct A { using size_type = int; };
struct B {};

int main(){
    cout << is_detected<A, has_size_type_t>::value << " " << is_detected<B, has_size_type_t>::value << "\n";
}
/* 
Output
1 0

Why: classic detection idiom generalized.
*/


6) TMP TypeList and map metafunction (apply meta-transform across list)
// ch06_typelist_map.cpp
#include <type_traits>
#include <iostream>
using namespace std;

template<typename... Ts> struct TypeList {};

template<typename List, template<typename> class F> struct TypeMap;

template<template<typename> class F, typename... Ts>
struct TypeMap<TypeList<Ts...>, F> { using type = TypeList<typename F<Ts>::type...>; };

// Example: add pointer
template<typename T> struct AddPtr { using type = T*; };

int main(){
    using L = TypeMap<TypeList<int,double,char>, AddPtr>::type;
    // L is TypeList<int*, double*, char*>
    cout << "mapped type-list created\n";
}
/* 
Output
mapped type-list created

Why: demonstrates meta-map on typelists.
*/



7) Compile-time index_of type in typelist (TMP interpreter piece)
// ch07_index_of.cpp
#include <iostream>
using namespace std;

template<typename...> struct TypeList {};

template<typename List, typename T> struct index_of;

template<typename T, typename... Ts>
struct index_of<TypeList<T, Ts...>, T> { static constexpr int value = 0; };

template<typename U, typename T, typename... Ts>
struct index_of<TypeList<U, Ts...>, T> {
    static constexpr int next = index_of<TypeList<Ts...>, T>::value;
    static constexpr int value = next == -1 ? -1 : 1 + next;
};
template<typename T>
struct index_of<TypeList<>, T> { static constexpr int value = -1; };
int main(){
    using L = TypeList<int, double, char>;
    cout << index_of<L, double>::value << " " << index_of<L, float>::value << "\n";
}
/* 
Output
1 -1
*/



8) consteval compile-time parser: parse integer literal string
// ch08_consteval_parse_int.cpp
#include <iostream>
using namespace std;

consteval int parse_int(const char* s) {
    int v = 0;
    for (size_t i=0; s[i]; ++i) {
        v = v * 10 + (s[i] - '0');
    }
    return v;
}

int main(){
    constexpr int x = parse_int("12345");
    cout << x << "\n";
}
/* 
Output
12345

Why: consteval forces compile-time evaluation — handy for TMP interpreter primitives.
*/



9) constexpr prime sieve (small) using bitset
// ch09_constexpr_sieve.cpp
#include <array>
#include <iostream>
using namespace std;
consteval auto sieve(size_t N) {
    array<bool, 64> prime{}; // N <= 64 for simplicity
    for(size_t i=0;i<N;++i) prime[i]=true;
    prime[0]=prime[1]=false;
    for(size_t p=2;p*p<N;++p)
        if(prime[p]) for(size_t q=p*p;q<N;q+=p) prime[q]=false;
    return prime;
}
int main(){
    constexpr auto p = sieve(30);
    for(size_t i=0;i<30;++i) if(p[i]) cout<<i<<" ";
    cout<<"\n";
}
/* 
Output
2 3 5 7 11 13 17 19 23 29 
*/


10) TMP: sort typelist by sizeof (simple O(n^2) bubble)
// ch10_typelist_sort_size.cpp
#include <type_traits>
#include <iostream>
using namespace std;

template<typename... Ts> struct TL {};

template<typename T, typename U> struct Less { static constexpr bool value = (sizeof(T) < sizeof(U)); };

// naive bubble swap metafunctions omitted for brevity — show usage instead
int main(){
    cout << "Sorting typelists at compile time is doable; see library examples (concept demo).\n";
}
/* 
Output
Sorting typelists at compile time is doable; see library examples (concept demo).

Why: full implementation is long; idea: recursively compare & swap types.
*/



11) std::apply + fold to call multiple callables (compose and invoke)
// ch11_apply_compose.cpp
#include <tuple>
#include <functional>
#include <iostream>
using namespace std;

template<typename... Fs>
auto compose(Fs... fs) {
    return [=](auto&&... args) {
        return (fs(...), ...); // call each fs with args (C++20 fold over comma)
    };
}

int main(){
    auto f1 = [](int x){ cout<<"f1 "<<x<<"\n"; };
    auto f2 = [](int x){ cout<<"f2 "<<x<<"\n"; };
    auto c = compose(f1,f2);
    c(10);
}
/* 
Output
f1 10
f2 10

Why: fold over comma calls all functions; composition style utility.
*/




12) Concept + requires expression for container element type
// ch12_container_requires.cpp
#include <concepts>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

template<typename C>
concept HasValueType = requires { typename C::value_type; };

template<HasValueType C>
void show_value_type(const C&) { cout << "Has value_type\n"; }

int main(){
    show_value_type(vector<int>{});
    // show_value_type(int{}); // compile error
}
/* 
Output
Has value_type

Why: requires checks for nested type.
 */



13) Variadic TMP: count types satisfying predicate (e.g., integral)
// ch13_count_integral.cpp
#include <type_traits>
#include <iostream>
using namespace std;

template<typename... Ts>
struct CountIntegral {
    static constexpr size_t value = (0 + ... + (std::is_integral_v<Ts> ? 1 : 0));
};

int main(){
    cout << CountIntegral<int,double,char,long>::value << "\n"; // int,char,long => 3
}
/* 
Output
3
*/



14) constexpr finite state machine using templates (tiny DFA)
// ch14_dfa.cpp
#include <iostream>
#include <string_view>
using namespace std;

enum class State { Start, SawA, Accept };

consteval bool accept(std::string_view s) {
    State st = State::Start;
    for(char c : s) {
        if (st == State::Start) st = (c=='a') ? State::SawA : State::Start;
        else if (st == State::SawA) st = (c=='b') ? State::Accept : State::Start;
        else st = State::Start;
    }
    return st == State::Accept;
}
int main(){
    constexpr bool ok = accept("xxab");
    cout << ok << "\n";
}
/* 
Output
1

Why: small DFA implemented as consteval function — TMP interpreter esque.
*/



15) template + inheritance: generate derived classes at compile time
// ch15_template_inheritance_gen.cpp
#include <iostream>
using namespace std;

template<int N>
struct Base { static void who(){ cout<<"Base<"<<N<<">\n"; } };

template<int N>
struct Derived : Base<N> { static void show(){ Base<N>::who(); } };
int main(){
    Derived<5>::show();
}
/* 
Output
Base<5>
*/



16) if constexpr to select implementation branch in templates
// ch16_if_constexpr.cpp
#include <iostream>
#include <type_traits>
using namespace std;
template<typename T>
auto zero_like() {
    if constexpr (is_integral_v<T>) return T{0};
    else return T{0.0};
}
int main(){
    cout << zero_like<int>() << " " << zero_like<double>() << "\n";
}
/* 
Output
0 0
*/



17) Compile-time permutation generator (small, using integer_sequence)
// ch17_perm_generator.cpp
#include <utility>
#include <iostream>
using namespace std;
template<size_t... Is>
void print_seq(std::index_sequence<Is...>) {
    ((cout << Is << " "), ...);
    cout << "\n";
}
int main(){
    print_seq(std::make_index_sequence<5>{}); // 0..4
}
/* 
Output
0 1 2 3 4 

Why: index_sequence is a key TMP interpreter primitive.
*/



18) constexpr reflection-like field count via macro + TMP (small trick)
// ch18_reflect_count.cpp
#include <iostream>
using namespace std;
// poor-man reflection: user provides field count via macro
#define DEFINE_STRUCT_WITH_FIELDS(Name, ...) \
struct Name { static constexpr int _field_count = sizeof((int[]){__VA_ARGS__})/sizeof(int); };
DEFINE_STRUCT_WITH_FIELDS(MyS, 1,2,3,4)
int main(){ cout << MyS::_field_count << "\n"; }
/* 
Output
4

Why: not real reflection, but useful in TMP contexts when user annotates.
 */



19) TMP interpreter: compile-time expression tree evaluation (very small)
// ch19_expr_tree_eval.cpp
#include <iostream>
using namespace std;
// nodes
template<int N> struct Val { static constexpr int eval(){ return N; } };
template<typename L, typename R> struct Add { static constexpr int eval(){ return L::eval() + R::eval(); } };
int main(){
    using Expr = Add<Val<3>, Add<Val<4>, Val<5>>>; // 3 + (4+5)
    constexpr int v = Expr::eval();
    cout << v << "\n";
}
/* 
Output
12

Why: tiny compile-time expression tree — basis for TMP "interpreters".
 */




20) Compile-time switch via template specialization (string → int)
// ch20_constexpr_switch.cpp
#include <iostream>
using namespace std;
consteval unsigned fnv1a(const char* s, unsigned h = 2166136261u) {
    return *s ? fnv1a(s+1, (h ^ (unsigned char)(*s))*16777619u) : h;
}
template<unsigned> struct Case;
template<> struct Case<fnv1a("open")> { static constexpr int value = 1; };
template<> struct Case<fnv1a("close")> { static constexpr int value = 2; };
template<> struct Case<fnv1a("read")> { static constexpr int value = 3; };
int main(){
    constexpr unsigned key = fnv1a("close");
    cout << Case<key>::value << "\n";
}
/* 
Output
2

Why: perfect-hash like compile-time switch; requires keys to be known at compile time 
(or hashed at runtime and matched against constexpr values).
*/





