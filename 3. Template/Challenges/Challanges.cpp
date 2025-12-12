Templates 
- Normal template 
- template specialization
- SFINAE 
- metaprogramming


1. NORMAL TEMPLATE – Basic Generic Function
Example
#include <iostream>
using namespace std;
template<typename T>
T add(T a, T b) {
    return a + b;
}
int main() {
    cout << add(2, 3) << endl;       // int
    cout << add(2.5, 4.1) << endl;   // double
}



2. TEMPLATE SPECIALIZATION
Example
#include <iostream>
using namespace std;
template<typename T>
void print(T x) {
    cout << "General: " << x << endl;
}
template<>
void print<string>(string x) {             // Specialization
    cout << "String: " << x << endl;
}
int main() {
    print(10);
    print(string("Hello"));
}



3. PARTIAL SPECIALIZATION
#include <iostream>
using namespace std;
template<typename T, typename U>
class Pair {
 public:
    static void show() { cout << "General template\n"; }
};
// Partial specialization when both are same type
template<typename T>
class Pair<T, T> {
  public:
    static void show() { cout << "Partial specialization\n"; }
};
int main() {
    Pair<int, double>::show();
    Pair<int, int>::show();
}



4. SFINAE (Substitution Failure Is Not An Error)
Enable function only if T is integer-like
#include <iostream>
#include <type_traits>
using namespace std;
template<typename T>
typename enable_if<is_integral<T>::value, T>::type
square(T x) {
    return x * x;
}
int main() {
    cout << square(5) << endl;
    // cout << square(2.5) << endl; // compile error
}



5. Template Metaprogramming (Recursive Compile-Time Computation)
Compile-time factorial
#include <iostream>
using namespace std;
template<int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};
template<>
struct Factorial<0> {
    static const int value = 1;
};
int main() {
    cout << Factorial<5>::value; // 120
}



20 TEMPLATES CODING CHALLENGES (WITH SOLUTIONS)
✔ 1. Generic Stack (class template)
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
class Stack {
    vector<T> v;
  public:
    void push(T x){ v.push_back(x); }
    void pop(){ v.pop_back(); }
    T top(){ return v.back(); }
};
int main(){
    Stack<int> s;
    s.push(10);
    cout << s.top();
}




✔ 2. Template function for swapping
template<typename T>
void mySwap(T &a, T &b) {
    T temp=a;
    a=b;
    b=temp;
}
int main(){
    int a=10,b=20;
    mySwap(a,b);
    cout<<a<<" "<<b;
}



✔ 3. Variadic Template Sum
#include <iostream>
using namespace std;
template<typename T>
T sum(T x){ return x; }
template<typename T, typename... Args>
T sum(T x, Args... args){
    return x + sum(args...);
}
int main(){
    cout << sum(1,2,3,4,5);
}




✔ 4. Class Template with default parameter
template<typename T = int>
class Box {
  public:
    T value;
};
int main(){
    Box<> b;
    b.value = 10;
    cout << b.value;
}




✔ 5. Template Specialization for char length*
template<typename T>
int length(T x){ return sizeof(x); }
template<>
int length<char*>(char* s){
    int c=0;
    while(*s++) c++;
    return c;
}
int main(){
    char s[]="Hello";
    cout << length(s);
}



✔ 6. SFINAE: enable only for floating types
#include <iostream>
#include <type_traits>
using namespace std;
template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type
half(T x) {
    return x / 2;
}
int main(){
    cout << half(4.6);
}



✔ 7. Detect if a class has “print()” method (SFINAE)
#include <iostream>
using namespace std;
template<typename T>
class has_print {
    typedef char yes[1];
    typedef char no[2];

    template<typename U, void (U::*)()> struct SFINAE {};
    template<typename U> static yes& test(SFINAE<U, &U::print>*);
    template<typename U> static no&  test(...);

  public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};
class A { public: void print(){} };
class B {};
int main(){
    cout << has_print<A>::value << endl;
    cout << has_print<B>::value << endl;
}



✔ 8. TMP Power<N, M> (M exponent)
template<int N, int P>
struct Power {
    static const int value = N * Power<N, P-1>::value;
};
template<int N>
struct Power<N,0>{
    static const int value = 1;
};
int main(){
    cout<<Power<2,5>::value;
}




✔ 9. Overload resolution using SFINAE
#include <iostream>
using namespace std;
template<typename T>
auto print(T x) -> decltype(x+1, void()) {
    cout<<"Can add 1\n";
}
void print(...) { cout<<"Cannot add 1\n"; }
int main(){
    print(10);     // ok
    struct X{}; X x;
    print(x);      // fallback
}




✔ 10. Partial specialization for pointers
template<typename T>
struct Info {
    static void show(){ cout<<"Not pointer\n"; }
};
template<typename T>
struct Info<T*> {
    static void show(){ cout<<"Pointer\n"; }
};
int main(){
    Info<int>::show();
    Info<int*>::show();
}




✔ 11. TypeList meta-programming container
template<typename... Ts>
struct TypeList {};
using MyTypes = TypeList<int, float, double>;



✔ 12. Template-based Singleton
template<typename T>
class Singleton {
  public:
    static T& instance() {
        static T obj;
        return obj;
    }
};
class Logger {};
int main(){
    Logger& l = Singleton<Logger>::instance();
}



✔ 13. CRTP (Curiously Recurring Template Pattern)
#include <iostream>
using namespace std;
template<typename T>
class Base {
 public:
    void interface(){ static_cast<T*>(this)->impl(); }
};
class Derived : public Base<Derived> {
  public:
    void impl(){ cout << "Derived implementation\n"; }
};
int main(){
    Derived d;
    d.interface();
}




✔ 14. Compile-time Fibonacci (TMP)
template<int N>
struct Fib {
    static const int value = Fib<N-1>::value + Fib<N-2>::value;
};

template<>
struct Fib<0> { static const int value = 0; };

template<>
struct Fib<1> { static const int value = 1; };
int main(){
    cout<<Fib<10>::value;
}


✔ 15. Template for printing any container
#include <iostream>
using namespace std;
template<typename Container>
void printContainer(const Container& c){
    for(auto &x : c) cout<<x<<" ";
}
int main(){
    vector<int> v{1,2,3};
    printContainer(v);
}



✔ 16. Template deduction guide
template<typename T>
class Wrapper {
 public:
    T value;
    Wrapper(T v):value(v){}
};
Wrapper(const char*) -> Wrapper<string>;
int main(){
    Wrapper w = "hello";
    cout << w.value;
}



✔ 17. Compile-time check for even number
template<int N>
struct IsEven {
    static const bool value = (N % 2 == 0);
};
int main(){
    cout << IsEven<42>::value;
}



✔ 18. Custom enable_if implementation
template<bool B, typename T = void>
struct my_enable_if {};

template<typename T>
struct my_enable_if<true, T> { using type = T; };

template<typename T>
typename my_enable_if<is_integral<T>::value, T>::type foo(T x){
    return x + 1;
}
int main(){
    cout << foo(10);
}



✔ 19. Detect if type is pointer (custom trait)
template<typename T>
struct is_ptr { static const bool value = false; };

template<typename T>
struct is_ptr<T*> { static const bool value = true; };

int main(){
    cout << is_ptr<int*>::value;
}



✔ 20. Compile-time min of two values
template<int A, int B>
struct Min {
    static const int value = (A < B ? A : B);
};
int main(){
    cout<<Min<4,9>::value;
}





1) Implement a tuple using templates (simple recursive inheritance)
// tuple_impl.cpp
#include <iostream>
#include <type_traits>
using namespace std;
// Tuple implementation: recursive inheritance
template<typename... Ts> struct Tuple;
template<>
struct Tuple<> {};
template<typename Head, typename... Tail>
struct Tuple<Head, Tail...> : Tuple<Tail...> {
    Head value;
    Tuple() = default;
    Tuple(const Head& h, const Tail&... tail) : Tuple<Tail...>(tail...), value(h) {}
};
// get by index (0-based) - helper
template<size_t idx, typename TupleT>
struct TupleElement;
template<typename Head, typename... Tail>
struct TupleElement<0, Tuple<Head, Tail...>> {
    using type = Head;
    static Head& get(Tuple<Head, Tail...>& t) { return t.value; }
};
template<size_t idx, typename Head, typename... Tail>
struct TupleElement<idx, Tuple<Head, Tail...>> {
    using type = typename TupleElement<idx-1, Tuple<Tail...>>::type;
    static type& get(Tuple<Head, Tail...>& t) {
        Tuple<Tail...>& base = t; // upcast
        return TupleElement<idx-1, Tuple<Tail...>>::get(base);
    }
};
int main(){
    Tuple<int, double, string> t(42, 3.14, string("hello"));
    cout << TupleElement<0, decltype(t)>::get(t) << "\n";
    cout << TupleElement<1, decltype(t)>::get(t) << "\n";
    cout << TupleElement<2, decltype(t)>::get(t) << "\n";
}
/* 
Output
42
3.14
hello

Explanation: Tuple stores Head and inherits Tuple<Tail...>. TupleElement<idx,...> recursively picks element and returns a reference.
*/



2) Implement optional<T> (basic)
// optional_impl.cpp
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;
template<typename T>
class Optional {
    alignas(T) unsigned char storage[sizeof(T)];
    bool engaged = false;
    T* ptr() { return reinterpret_cast<T*>(storage); }
  public:
    Optional() = default;
    Optional(const T& v){ new(ptr()) T(v); engaged = true; }
    Optional(T&& v){ new(ptr()) T(std::move(v)); engaged = true; }
    ~Optional(){ reset(); }
    bool has_value() const { return engaged; }
    T& operator*(){ return *ptr(); }
    const T& operator*() const{ return *ptr(); }
    void reset(){ if(engaged){ ptr()->~T(); engaged=false; } }
    template<typename... Args>
    void emplace(Args&&... args){ reset(); new(ptr()) T(std::forward<Args>(args)...); engaged=true; }
};
int main(){
    Optional<int> o;
    cout << o.has_value() << "\n";
    o.emplace(123);
    cout << o.has_value() << " " << *o << "\n";
    o.reset();
    cout << o.has_value() << "\n";
}
/* 
Output
0
1 123
0

Explanation: Optional stores raw bytes and constructs/destructs T manually; has_value() tracks engagement.
*/



3) Implement a simple variant<Ts...> using recursive storage
This is a compact educational variant (no visitation helpers other than get<T> and holds index).

// variant_impl.cpp
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;
template<typename... Ts> struct Variant;
template<>
struct Variant<> {};
template<typename T, typename... Rest>
struct Variant<T, Rest...> {
    union {
        T head;
        Variant<Rest...> tail;
    };
    size_t index = 0; // 0 -> head, otherwise 1 + index in tail

    Variant() { new(&head) T(); index = 0; }
    Variant(const T& v){ new(&head) T(v); index = 0; }
    Variant(int dummy, const Variant<Rest...>& v){ new(&tail) Variant<Rest...>(v); index = v.index + 1; }

    Variant(const Variant& other){
        if(other.index == 0){ new(&head) T(other.head); index = 0; }
        else { new(&tail) Variant<Rest...>(other.tail); index = other.index; }
    }
    ~Variant(){
        if(index == 0) head.~T();
        else tail.~Variant<Rest...>();
    }

    // helper constructor for rest types
    template<typename U, typename = typename enable_if<!is_same<U,T>::value>::type>
    Variant(const U& v) : Variant(0, Variant<Rest...>(v)) {}

    bool holds_index(size_t i) const { return index == i; }

    template<typename U>
    U& get(){
        if constexpr (is_same<U,T>::value) {
            if(index != 0) throw runtime_error("bad_variant_access");
            return head;
        } else {
            if(index == 0) throw runtime_error("bad_variant_access");
            return tail.template get<U>();
        }
    }
};
int main(){
    Variant<int, double, string> v = 10;
    cout << v.get<int>() << "\n";
    Variant<int,double,string> v2 = string("bye");
    cout << v2.get<string>() << "\n";
    Variant<int,double,string> v3 = 2.5;
    cout << v3.get<double>() << "\n";
}
/* 
Output
10
bye
2.5

Explanation: Recursive Variant stores either head or tail variant. get<T>() resolves at compile-time using if constexpr. (Note: minimal, lacks many safety/assignment features of std::variant.)
*/



4) Compile-time string length using template metaprogramming (char pack)
// ct_strlen.cpp
#include <iostream>
using namespace std;
// Define a compile-time string via char pack
template<char... Cs> struct CTString {
    static constexpr size_t size = sizeof...(Cs);
};
// helper to create CTString via user-provided alias (for demo)
using Hello = CTString<'H','e','l','l','o'>;
int main(){
    cout << "Hello length = " << Hello::size << "\n";
    // Another:
    using Empty = CTString<>;
    cout << "Empty length = " << Empty::size << "\n";
}
/* 
Output
Hello length = 5
Empty length = 0

Explanation: This is a pure-TMP approach: a CTString packs characters into template parameters; sizeof...(Cs) is the length. (In practice, user-defined literal machinery or constexpr functions are used; this demonstrates pure TMP.)
*/



5) Implement type trait is_same<T, U>
// is_same_impl.cpp
#include <iostream>
using namespace std;
template<typename A, typename B> struct is_same { static constexpr bool value = false; };
template<typename A> struct is_same<A, A> { static constexpr bool value = true; };

int main(){
    cout << is_same<int,int>::value << "\n";
    cout << is_same<int,double>::value << "\n";
}
/* 
Output
1
0

Explanation: Primary template yields false; specialization for identical types yields true.
*/


6) Build a policy-based design using templates
// policy_design.cpp
#include <iostream>
using namespace std;
// Policies:
struct NoLog { void log(const string&){ } };
struct ConsoleLog { void log(const string& s){ cout << "[LOG] " << s << "\n"; } };
struct DefaultAllocator {
    template<typename T, typename... Args>
    static T* create(Args&&... args){ return new T(std::forward<Args>(args)...); }
    template<typename T> static void destroy(T* p){ delete p; }
};
// A class parameterized by policies
template<typename LoggerPolicy = NoLog, typename AllocPolicy = DefaultAllocator>
class Service : private LoggerPolicy, private AllocPolicy {
  public:
    void start(){
        LoggerPolicy::log("Service starting");
    }
    template<typename T, typename... Args>
    T* make(Args&&... args){
        T* p = AllocPolicy::create<T>(std::forward<Args>(args)...);
        LoggerPolicy::log("Object created");
        return p;
    }
    template<typename T>
    void destroy(T* p){ AllocPolicy::destroy<T>(p); LoggerPolicy::log("Object destroyed"); }
};
struct X { int v; X(int a):v(a){} };
int main(){
    Service<ConsoleLog> s;
    s.start();
    X* x = s.make<X>(42);
    cout << "X.v = " << x->v << "\n";
    s.destroy(x);
}
/* 
Output
[LOG] Service starting
[LOG] Object created
X.v = 42
[LOG] Object destroyed

Explanation: Service composes behavior from LoggerPolicy and AllocPolicy. Swapping policies changes behavior without code changes.
*/


7) Write a generic factory using templates (ID -> creation function)
// generic_factory.cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
using namespace std;
template<typename Base, typename Key = string, typename... Args>
class Factory {
    unordered_map<Key, function<unique_ptr<Base>(Args...)>> creators;
  public:
    void register_creator(const Key& k, function<unique_ptr<Base>(Args...)> f){ creators[k] = f; }
    unique_ptr<Base> create(const Key& k, Args... args){
        auto it = creators.find(k);
        if(it==creators.end()) return nullptr;
        return it->second(std::forward<Args>(args)...);
    }
};
struct Product { virtual void info()=0; virtual ~Product()=default; };
struct P1 : Product { P1(int x):v(x){} int v; void info(){ cout<<"P1 "<<v<<"\n"; } };
struct P2 : Product { P2(string s):s(s){} string s; void info(){ cout<<"P2 "<<s<<"\n"; } };
int main(){
    Factory<Product, string> f;
    f.register_creator("p1", [](int x){ return make_unique<P1>(x); });
    f.register_creator("p2", [](string s){ return make_unique<P2>(s); });

    auto a = f.create("p1", 10);
    a->info();
    auto b = f.create("p2", string("hello"));
    b->info();
}
/* 
Output
P1 10
P2 hello

Explanation: Factory stores creator lambdas keyed by a string (or other key). It returns polymorphic unique_ptr<Base> created with provided args.
*/



8) Implement static polymorphism using CRTP
// crtp.cpp
#include <iostream>
using namespace std;
template<typename Derived>
struct Base {
    void interface() { static_cast<Derived*>(this)->implementation(); }
};
struct ImplA : Base<ImplA> {
    void implementation(){ cout << "ImplA behavior\n"; }
};
struct ImplB : Base<ImplB> {
    void implementation(){ cout << "ImplB behavior\n"; }
};
int main(){
    ImplA a; ImplB b;
    a.interface();
    b.interface();
}
/* 
Output
ImplA behavior
ImplB behavior

Explanation: CRTP gives compile-time polymorphism: no vtable, calls resolved at compile time.
*/



9) Create a "concept-like" SFINAE constraints system (simple requires check)
// sfinae_concepts.cpp
#include <iostream>
#include <type_traits>
using namespace std;
// A simple "concept": HasToString -> has to_string() member returning string
template<typename T>
class has_to_string {
    template<typename U, typename = decltype(std::declval<U>().to_string())>
    static true_type test(int);
    template<typename> static false_type test(...);
public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

// function enabled only if T has to_string()
template<typename T, typename = typename std::enable_if<has_to_string<T>::value>::type>
void print_as_string(const T& x) {
    cout << x.to_string() << "\n";
}

struct A { string to_string() const { return string("A"); } };
struct B {};

int main(){
    A a;
    print_as_string(a);          // OK
    // B b; print_as_string(b);  // would fail to compile (SFINAE removes overload)
    cout << "has_to_string<A>=" << has_to_string<A>::value << "\n";
    cout << "has_to_string<B>=" << has_to_string<B>::value << "\n";
}
/* 
Output
A
has_to_string<A>=1
has_to_string<B>=0

Explanation: has_to_string<T> uses SFINAE to detect presence of to_string(). print_as_string is only enabled when the trait is true.
*/


10) Implement type_index → integer mapping using TMP (type list + index_of)
// type_index_map.cpp
#include <iostream>
using namespace std;

// typelist
template<typename... Ts> struct TypeList {};

// index_of: find index of T in TypeList
template<typename List, typename T> struct index_of;

template<typename T, typename... Ts>
struct index_of<TypeList<T,Ts...>, T> { static constexpr int value = 0; };

template<typename U, typename T, typename... Ts>
struct index_of<TypeList<U,Ts...>, T> {
    static constexpr int next = index_of<TypeList<Ts...>, T>::value;
    static constexpr int value = (next== -1 ? -1 : 1 + next);
};

template<typename T>
struct index_of<TypeList<>, T> { static constexpr int value = -1; };

// Example usage
using MyTypes = TypeList<int, double, char, std::string>;

int main(){
    cout << "int -> " << index_of<MyTypes, int>::value << "\n";
    cout << "double -> " << index_of<MyTypes, double>::value << "\n";
    cout << "char -> " << index_of<MyTypes, char>::value << "\n";
    cout << "string -> " << index_of<MyTypes, std::string>::value << "\n";
    cout << "float -> " << index_of<MyTypes, float>::value << "\n"; // not found
}
/*
Output
int -> 0
double -> 1
char -> 2
string -> 3
float -> -1

Explanation: A TypeList packs types; index_of recursively computes the 0-based index of a type (-1 if not found). This is a compile-time type-to-integer mapping useful for static dispatch tables.
*/