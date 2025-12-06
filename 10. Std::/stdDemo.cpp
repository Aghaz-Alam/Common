C++11 ADDITIONS
✔ Functional Utilities
std::function
std::bind
std::placeholders
std::mem_fn
std::ref, std::cref
std::hash specializations for many types
/* ----------------------------------------------------------- */

//✅ 1. std::function – Storing Functions / Lambdas / Functors
#include <iostream>
#include <functional>
using namespace std;
int add(int a, int b) { 
    return a + b; 
}
int main() {
    std::function<int(int, int)> func;

    func = add;
    cout << "add(10, 20) = " << func(10, 20) << endl;

    func = [](int a, int b) { return a * b; };
    cout << "lambda multiply(10, 20) = " << func(10, 20) << endl;

    struct Functor {
        int operator()(int a, int b) const { return a - b; }
    };

    func = Functor();
    cout << "functor subtract(10, 20) = " << func(10, 20) << endl;

    return 0;
}
/* 
OUTPUT
add(10, 20) = 30
lambda multiply(10, 20) = 200
functor subtract(10, 20) = -10
*/



//✅ 2. std::bind – Bind arguments to a function
#include <iostream>
#include <functional>
using namespace std;
int multiply(int a, int b, int c) {
    return a * b * c;
}
int main() {
    auto bindFunc = std::bind(multiply, 2, 3, 4);
    cout << "multiply(2,3,4) = " << bindFunc() << endl;

    auto partial = std::bind(multiply, 2, 3, std::placeholders::_1);
    cout << "multiply(2,3,x) where x=5 → " << partial(5) << endl;

    return 0;
}
/* 
OUTPUT
multiply(2,3,4) = 24
multiply(2,3,x) where x=5 → 30
*/



//✅ 3. std::placeholders – Reordering & partial binding
#include <iostream>
#include <functional>
using namespace std;
void show(int a, int b, int c) {
    cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
}
int main() {
    auto reorder = std::bind(show,
                             std::placeholders::_2,
                             std::placeholders::_3,
                             std::placeholders::_1);

    reorder(10, 20, 30);

    return 0;
}
/* 
OUTPUT
a=20, b=30, c=10


✔ Notice how arguments were reordered using _1, _2, _3
*/



//✅ 4. std::mem_fn – Call class member functions
#include <iostream>
#include <functional>
using namespace std;
struct Demo {
    void print(int x) {
        cout << "Demo::print called with " << x << endl;
    }
};
int main() {
    Demo obj;

    auto memCall = std::mem_fn(&Demo::print);
    memCall(obj, 50);

    return 0;
}
/* 
OUTPUT
Demo::print called with 50
*/


✅ 5. std::ref / std::cref – Pass variables by reference
#include <iostream>
#include <functional>
using namespace std;
void increment(int &x) {
    x++;
}
int main() {
    int value = 10;

    auto f = std::bind(increment, std::ref(value));
    f();

    cout << "value after increment = " << value << endl;

    return 0;
}
/* 
OUTPUT
value after increment = 11


✔ Without std::ref, the value would NOT change.
*/



//✅ 6. std::hash – Hashing custom values
#include <iostream>
#include <functional>
#include <string>
using namespace std;
int main() {
    string s = "Hello";
    int number = 12345;

    std::hash<string> hashStr;
    std::hash<int> hashInt;

    cout << "Hash of string 'Hello' = " << hashStr(s) << endl;
    cout << "Hash of int 12345 = " << hashInt(number) << endl;

    return 0;
}
/* 
POSSIBLE OUTPUT (hash values vary by compiler)
Hash of string 'Hello' = 13274012033293761331
Hash of int 12345 = 12345
*/

/* ----------------------------------------------------------- */

✔ Smart Pointers
std::unique_ptr
std::shared_ptr
std::weak_ptr
std::make_unique (C++14)
std::make_shared
/* ----------------------------------------------------------- */
✅ 1. std::unique_ptr – Exclusive Ownership

#include <iostream>
#include <memory>
using namespace std;
class Test {
  public:
    Test() { cout << "Test Created\n"; }
    ~Test() { cout << "Test Destroyed\n"; }
    void show() { cout << "Hello from Test\n"; }
};
int main() {
    unique_ptr<Test> ptr1 = make_unique<Test>();
    ptr1->show();

    // Transfer ownership
    unique_ptr<Test> ptr2 = std::move(ptr1);

    if (!ptr1)
        cout << "ptr1 is empty after move\n";

    ptr2->show();

    return 0;
}
/* 
OUTPUT
Test Created
Hello from Test
ptr1 is empty after move
Hello from Test
Test Destroyed
*/



//✅ 2. std::shared_ptr – Shared Ownership
#include <iostream>
#include <memory>
using namespace std;
class Demo {
  public:
    Demo() { cout << "Demo Created\n"; }
    ~Demo() { cout << "Demo Destroyed\n"; }
};
int main() {
    shared_ptr<Demo> p1 = make_shared<Demo>();
    cout << "Use count after p1 = " << p1.use_count() << endl;

    {
        shared_ptr<Demo> p2 = p1;
        cout << "Use count after p2 = " << p1.use_count() << endl;

        {
            shared_ptr<Demo> p3 = p2;
            cout << "Use count after p3 = " << p1.use_count() << endl;
        }
        cout << "Use count after p3 destroyed = " << p1.use_count() << endl;
    }

    cout << "Use count after p2 destroyed = " << p1.use_count() << endl;

    return 0;
}
/* 
OUTPUT
Demo Created
Use count after p1 = 1
Use count after p2 = 2
Use count after p3 = 3
Use count after p3 destroyed = 2
Use count after p2 destroyed = 1
Demo Destroyed
*/


//✅ 3. std::weak_ptr – Non-Owning Observer
#include <iostream>
#include <memory>
using namespace std;
class Resource {
  public:
    Resource() { cout << "Resource Created\n"; }
    ~Resource() { cout << "Resource Destroyed\n"; }
};
int main() {
    weak_ptr<Resource> weakRef;

    {
        shared_ptr<Resource> sharedObj = make_shared<Resource>();
        weakRef = sharedObj;

        cout << "Shared count = " << sharedObj.use_count() << endl;

        if (auto locked = weakRef.lock()) {
            cout << "Lock successful: Resource is still alive\n";
        }
    }

    // Now shared_ptr is destroyed
    if (weakRef.expired())
        cout << "weak_ptr expired: Resource is destroyed\n";

    return 0;
}
/* 
OUTPUT
Resource Created
Shared count = 1
Lock successful: Resource is still alive
Resource Destroyed
weak_ptr expired: Resource is destroyed
*/



//✅ 4. std::make_unique (C++14) – Safe unique_ptr Construction
#include <iostream>
#include <memory>
using namespace std;

int main() {
    auto ptr = std::make_unique<int>(500);

    cout << "Value inside unique_ptr = " << *ptr << endl;

    return 0;  // Automatic destruction
}
/* 
OUTPUT
Value inside unique_ptr = 500
*/


//✅ 5. std::make_shared – Efficient shared_ptr Creation
#include <iostream>
#include <memory>
using namespace std;
class MyClass {
  public:
    MyClass(int x) : value(x) {
        cout << "MyClass(" << value << ") Created\n";
    }
    ~MyClass() {
        cout << "MyClass(" << value << ") Destroyed\n";
    }
    int value;
};
int main() {
    auto p1 = make_shared<MyClass>(42);
    auto p2 = p1;

    cout << "Use count = " << p1->value << " has " << p1.use_count() << " owners\n";

    return 0;
}
/* 
OUTPUT
MyClass(42) Created
Use count = 42 has 2 owners
MyClass(42) Destroyed
*/
/* ----------------------------------------------------------- */

✔ Type Traits (<type_traits>)
(huge list, major ones)
std::enable_if
std::conditional
std::is_same
std::decay
std::remove_reference
std::remove_const, std::remove_volatile
std::is_void
std::is_integral, std::is_floating_point
std::is_enum, std::is_class
std::is_reference, std::is_lvalue_reference
std::is_trivial, std::is_standard_layout
std::is_constructible, std::is_default_constructible
std::is_convertible
std::alignment_of, std::aligned_storage

/* ----------------------------------------------------------- */
✅ 1. std::enable_if — SFINAE

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
typename enable_if<is_integral<T>::value, void>::type
func(T x) {
    cout << "Integral version: " << x << endl;
}

template <typename T>
typename enable_if<!is_integral<T>::value, void>::type
func(T x) {
    cout << "Non-integral version: " << x << endl;
}

int main() {
    func(10);     // integral
    func(3.14);   // non-integral
}
/* 
OUTPUT
Integral version: 10
Non-integral version: 3.14
*/


//✅ 2. std::conditional
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    using T = conditional<true, int, double>::type;
    T x = 100;

    cout << "Type is int, value = " << x << endl;
}
/* 
OUTPUT
Type is int, value = 100
*/


//✅ 3. std::is_same
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << boolalpha;
    cout << "int and int? " << is_same<int,int>::value << endl;
    cout << "int and double? " << is_same<int,double>::value << endl;
}
/* 
OUTPUT
int and int? true
int and double? false
*/


//✅ 4. std::decay
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    using T = decay<int&>::type;

    cout << boolalpha;
    cout << "decay<int&> is int? " << is_same<T,int>::value << endl;
}
/* 
OUTPUT
decay<int&> is int? true
*/


//✅ 5. std::remove_reference
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    using T = remove_reference<int&>::type;

    cout << boolalpha;
    cout << "remove_reference<int&> is int? " << is_same<T,int>::value << endl;
}
/* 
OUTPUT
remove_reference<int&> is int? true
*/


//✅ 6. std::remove_const / std::remove_volatile
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    using A = remove_const<const int>::type;
    using B = remove_volatile<volatile int>::type;

    cout << boolalpha;
    cout << "remove_const<const int> → int? " << is_same<A,int>::value << endl;
    cout << "remove_volatile<volatile int> → int? " << is_same<B,int>::value << endl;
}
/* 
OUTPUT
remove_const<const int> → int? true
remove_volatile<volatile int> → int? true
*/


//✅ 7. std::is_void
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << boolalpha;
    cout << "is_void<void>? " << is_void<void>::value << endl;
    cout << "is_void<int>?  " << is_void<int>::value << endl;
}
/* 
OUTPUT
is_void<void>? true
is_void<int>?  false
*/


//✅ 8. std::is_integral / std::is_floating_point
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << boolalpha;
    cout << "is_integral<int>? " << is_integral<int>::value << endl;
    cout << "is_floating_point<double>? " << is_floating_point<double>::value << endl;
}
/* 
OUTPUT
is_integral<int>? true
is_floating_point<double>? true
*/


//✅ 9. std::is_enum / std::is_class
#include <iostream>
#include <type_traits>
using namespace std;

enum Color { Red, Green };
class Demo {};

int main() {
    cout << boolalpha;
    cout << "is_enum<Color>? " << is_enum<Color>::value << endl;
    cout << "is_class<Demo>? " << is_class<Demo>::value << endl;
}
/* 
OUTPUT
is_enum<Color>? true
is_class<Demo>? true
*/



//✅ 10. std::is_reference / std::is_lvalue_reference
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << boolalpha;
    cout << "is_reference<int&>? " << is_reference<int&>::value << endl;
    cout << "is_lvalue_reference<int&>? " << is_lvalue_reference<int&>::value << endl;
}
/* 
OUTPUT
is_reference<int&>? true
is_lvalue_reference<int&>? true
*/



//✅ 11. std::is_trivial / std::is_standard_layout
#include <iostream>
#include <type_traits>
using namespace std;

struct A { int x; };        // trivial
struct B { virtual void f(){} }; // non-trivial

int main() {
    cout << boolalpha;
    cout << "A is trivial? " << is_trivial<A>::value << endl;
    cout << "B is trivial? " << is_trivial<B>::value << endl;

    cout << "A is standard layout? " << is_standard_layout<A>::value << endl;
    cout << "B is standard layout? " << is_standard_layout<B>::value << endl;
}
/* 
OUTPUT
A is trivial? true
B is trivial? false
A is standard layout? true
B is standard layout? false
*/


//✅ 12. std::is_constructible / std::is_default_constructible
#include <iostream>
#include <type_traits>
using namespace std;

struct A { A(int) {} };
struct B { B() = default; };

int main() {
    cout << boolalpha;
    cout << "A(10) constructible? " 
         << is_constructible<A,int>::value << endl;

    cout << "A default constructible? " 
         << is_default_constructible<A>::value << endl;

    cout << "B default constructible? " 
         << is_default_constructible<B>::value << endl;
}
/* 
OUTPUT
A(10) constructible? true
A default constructible? false
B default constructible? true
*/


//✅ 13. std::is_convertible
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    cout << boolalpha;
    cout << "int → double convertible? " 
         << is_convertible<int,double>::value << endl;
    cout << "double → int* convertible? " 
         << is_convertible<double,int*>::value << endl;
}
/* 
OUTPUT
int → double convertible? true
double → int* convertible? false
*/


//✅ 14. std::alignment_of
#include <iostream>
#include <type_traits>
using namespace std;
struct A { 
    double x; int y; 
};
int main() {
    cout << "Alignment of A = " 
         << alignment_of<A>::value << endl;
}
/* 
OUTPUT (varies by compiler)
Alignment of A = 8
*/


//✅ 15. std::aligned_storage
#include <iostream>
#include <type_traits>
using namespace std;
struct Test {
    int x;
    double y;
};
int main() {
    typedef aligned_storage<sizeof(Test), alignof(Test)>::type Storage;

    Storage rawMemory;

    // Construct object inside raw memory
    Test* obj = new(&rawMemory) Test{10, 20.5};

    cout << "x = " << obj->x << ", y = " << obj->y << endl;

    obj->~Test();
}
/* 
OUTPUT
x = 10, y = 20.5
*/

/* ----------------------------------------------------------- */

✔ Move Semantics / Utility
std::move
std::forward
std::swap overloads
std::declval
std::move_if_noexcept
std::addressof
std::index_sequence, std::make_index_sequence
/* ----------------------------------------------------------- */
✅ 1. std::move — Convert lvalue → rvalue to enable moving
#include <iostream>
#include <utility>
#include <string>
using namespace std;

int main() {
    string a = "Hello";
    string b = std::move(a); // move a into b

    cout << "b = " << b << endl;
    cout << "a (moved-from) = \"" << a << "\"" << endl;
}

OUTPUT
b = Hello
a (moved-from) = ""

✅ 2. std::forward — Perfect Forwarding
#include <iostream>
#include <utility>
using namespace std;

void process(int& x) { cout << "Lvalue processed\n"; }
void process(int&& x) { cout << "Rvalue processed\n"; }

template<typename T>
void wrapper(T&& x) {
    process(std::forward<T>(x));  // preserves value category
}

int main() {
    int a = 10;
    wrapper(a);        // lvalue
    wrapper(20);       // rvalue
}

OUTPUT
Lvalue processed
Rvalue processed

✅ 3. std::swap — Custom Swap Overload
#include <iostream>
#include <utility>
using namespace std;

struct Demo {
    int x;
};

void swap(Demo& a, Demo& b) {
    cout << "Custom swap called!\n";
    std::swap(a.x, b.x);
}

int main() {
    Demo d1{10}, d2{20};

    std::swap(d1, d2);

    cout << "d1.x = " << d1.x << endl;
    cout << "d2.x = " << d2.x << endl;
}

OUTPUT
Custom swap called!
d1.x = 20
d2.x = 10

✅ 4. std::declval — Create “fake” rvalues for type deduction

Used in type traits and SFINAE to express:
“Pretend I have an object of type T without constructing it”.

#include <iostream>
#include <type_traits>
using namespace std;

struct A {
    int func() const { return 42; }
};

template<typename T>
using func_return_t = decltype(declval<T>().func());

int main() {
    cout << "Return type is int? " << boolalpha
         << is_same<func_return_t<A>, int>::value << endl;
}

OUTPUT
Return type is int? true

✅ 5. std::move_if_noexcept — Move only if noexcept, otherwise copy
#include <iostream>
#include <utility>
using namespace std;

struct NoThrow {
    NoThrow() {}
    NoThrow(NoThrow&&) noexcept { cout << "NoThrow moved\n"; }
};

struct CanThrow {
    CanThrow() {}
    CanThrow(CanThrow&&) { cout << "CanThrow moved (may throw)\n"; }
};

int main() {
    NoThrow a;
    NoThrow b = std::move_if_noexcept(a);   // prefers move

    CanThrow x;
    CanThrow y = std::move_if_noexcept(x);  // prefers COPY, not move

    cout << "Completed\n";
}

OUTPUT (likely)
NoThrow moved
Completed


(Copy of CanThrow is trivial and silent, since move is not noexcept.)

✅ 6. std::addressof — Get address even if operator& is overloaded
#include <iostream>
#include <memory>
using namespace std;

struct Weird {
    int x = 10;
    int* operator&() { return nullptr; }   // overload operator &
};

int main() {
    Weird w;

    cout << "Overloaded &: " << &w << endl;               // prints nullptr
    cout << "Real address: " << std::addressof(w) << endl; // correct
}

OUTPUT
Overloaded &: 0
Real address: 0x7ffd23a5f0b8    (example)

✅ 7. std::index_sequence + std::make_index_sequence

Used for unpacking tuples, parameter packs, and compile-time indexing.

#include <iostream>
#include <tuple>
#include <utility>
using namespace std;

template<typename Tuple, size_t... I>
void printTuple(const Tuple& t, index_sequence<I...>) {
    ((cout << get<I>(t) << " "), ...);
}

int main() {
    auto tup = make_tuple(10, 20, 30);

    printTuple(tup, make_index_sequence<3>{});
}

OUTPUT
10 20 30 





✅ Program 5: std::declval

Used to create a pretend value of a type in unevaluated contexts (e.g., SFINAE).

✔ Code
#include <iostream>
#include <type_traits>
using namespace std;

class Demo {
public:
    int hello() { return 42; }
};

template<typename T>
auto test() -> decltype(declval<T>().hello()) {
    return 999;
}

int main() {
    cout << test<Demo>() << endl;   // Uses declval to call hello()
}

✔ Output
999

✅ Program 6: std::move_if_noexcept

Moves only if the move constructor is noexcept, otherwise copies.

✔ Code
#include <iostream>
#include <utility>
using namespace std;

struct SafeMove {
    SafeMove() {}
    SafeMove(const SafeMove&) { cout << "Copy\n"; }
    SafeMove(SafeMove&&) noexcept { cout << "Move\n"; }
};

struct UnsafeMove {
    UnsafeMove() {}
    UnsafeMove(const UnsafeMove&) { cout << "Copy\n"; }
    UnsafeMove(UnsafeMove&&) { cout << "Move (may throw)\n"; }
};

int main() {
    SafeMove a;
    SafeMove b = std::move_if_noexcept(a);   // move

    cout << "----\n";

    UnsafeMove x;
    UnsafeMove y = std::move_if_noexcept(x); // copy (move is NOT noexcept)
}

✔ Output
Move
----
Copy

✅ Program 7: std::addressof

Gets the real memory address even if operator& is overloaded.

✔ Code
#include <iostream>
#include <memory>
using namespace std;

struct A {
    int value = 10;
    int* operator&() { return &value; } // Overloaded &
};

int main() {
    A obj;

    cout << "operator&(): " << &obj << endl;
    cout << "std::addressof(): " << std::addressof(obj) << endl;
}

✔ Output (example)
operator&(): 0x7ffdeacc8c
std::addressof(): 0x7ffdeacc90

✅ Program 8: std::index_sequence & std::make_index_sequence

Used for compile-time expansion of indices.

✔ Code
#include <iostream>
#include <utility>
using namespace std;

// Print tuple helper
template<typename Tuple, size_t... I>
void print_tuple(const Tuple& t, index_sequence<I...>) {
    ((cout << get<I>(t) << " "), ...);
}

int main() {
    auto tup = make_tuple(10, 20, 30);

    print_tuple(tup, make_index_sequence<3>{});
}

✔ Output
10 20 30





✅ Program 9: std::pair
✔ Code
#include <iostream>
#include <utility>
using namespace std;

int main() {
    pair<int, string> p = {10, "Hello"};

    cout << p.first << endl;
    cout << p.second << endl;
}

✔ Output
10
Hello

✅ Program 10: std::tuple
✔ Code
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    tuple<int, string, double> t(42, "Hi", 3.14);

    cout << get<0>(t) << endl;
    cout << get<1>(t) << endl;
    cout << get<2>(t) << endl;
}

✔ Output
42
Hi
3.14

✅ Program 11: std::tie

Used for unpacking tuple/pair.

✔ Code
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    auto t = make_tuple(1, 2.5, string("Aghaz"));

    int a;
    double b;
    string c;

    tie(a, b, c) = t;

    cout << a << " " << b << " " << c << endl;
}

✔ Output
1 2.5 Aghaz

✅ Program 12: std::ignore

Ignore values while unpacking.

✔ Code
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    auto t = make_tuple(10, 20, 30);

    int x, z;

    tie(x, ignore, z) = t;

    cout << x << " " << z << endl;
}

✔ Output
10 30

✅ Program 13: std::get over Array
✔ Code
#include <iostream>
#include <array>
using namespace std;

int main() {
    array<int, 3> arr = {5, 10, 15};

    cout << get<0>(arr) << endl;
    cout << get<1>(arr) << endl;
    cout << get<2>(arr) << endl;
}

✔ Output
5
10
15

✅ Program 14: std::integer_sequence (general)

General form (basis of index_sequence).

✔ Code
#include <iostream>
#include <utility>
using namespace std;

template<typename T, T... I>
void show(integer_sequence<T, I...>) {
    ((cout << I << " "), ...);
}

int main() {
    show(integer_sequence<int, 3, 6, 9>{});
}

✔ Output
3 6 9




🟦 Program 15 — std::optional (C++17)

Represents a value that may or may not exist.

✔ Code
#include <iostream>
#include <optional>
using namespace std;

optional<int> findValue(bool ok) {
    if (ok) return 42;
    return nullopt;
}

int main() {
    optional<int> x = findValue(true);
    optional<int> y = findValue(false);

    if (x) cout << "x = " << *x << endl;
    else   cout << "x is empty\n";

    if (y.has_value()) cout << "y = " << y.value() << endl;
    else               cout << "y is empty\n";
}

✔ Output
x = 42
y is empty

🟩 Program 16 — std::variant (C++17)

Type-safe union.

✔ Code
#include <iostream>
#include <variant>
using namespace std;

int main() {
    variant<int, float, string> v;

    v = 10;
    cout << "int: " << get<int>(v) << endl;

    v = 3.14f;
    cout << "float: " << get<float>(v) << endl;

    v = string("Aghaz");
    cout << "string: " << get<string>(v) << endl;

    // index()
    cout << "Current index: " << v.index() << endl;
}

✔ Output
int: 10
float: 3.14
string: Aghaz
Current index: 2

🟧 Program 17 — std::visit with std::variant

Pattern matching–style access.

✔ Code
#include <iostream>
#include <variant>
using namespace std;

struct Printer {
    void operator()(int v) const { cout << "int: " << v << endl; }
    void operator()(float v) const { cout << "float: " << v << endl; }
    void operator()(const string& v) const { cout << "string: " << v << endl; }
};

int main() {
    variant<int, float, string> v = 25;

    visit(Printer{}, v);

    v = string("Hello");
    visit(Printer{}, v);
}

✔ Output
int: 25
string: Hello

🟥 Program 18 — std::monostate

Used when a variant needs a "default empty" state.

✔ Code
#include <iostream>
#include <variant>
using namespace std;

int main() {
    variant<monostate, int, string> v;

    cout << "Index = " << v.index() << endl;

    v = 100;
    cout << "int: " << get<int>(v) << endl;
}

✔ Output
Index = 0
int: 100

🟨 Program 19 — std::in_place_type / std::in_place_index

Construct values in-place inside containers like optional, variant, any.

✔ Code
#include <iostream>
#include <variant>
using namespace std;

int main() {
    variant<int, string> v(in_place_type<string>, 5, 'A');
    cout << get<string>(v) << endl;

    variant<int, string> w(in_place_index<0>, 999);
    cout << get<0>(w) << endl;
}

✔ Output
AAAAA
999

🟦 Program 20 — std::any (C++17)

Holds any type (type-erased).

✔ Code
#include <iostream>
#include <any>
#include <string>
using namespace std;

int main() {
    any a = 10;

    cout << any_cast<int>(a) << endl;

    a = string("Hello");
    cout << any_cast<string>(a) << endl;

    // Checking type
    if (a.type() == typeid(string))
        cout << "a contains a string" << endl;

    // Reset
    a.reset();
    cout << boolalpha << a.has_value() << endl;
}

✔ Output
10
Hello
a contains a string
false




🟦 Program 21 — std::begin / std::end
✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30};

    for (auto it = begin(v); it != end(v); ++it)
        cout << *it << " ";
}

✔ Output
10 20 30

🟩 Program 22 — std::cbegin / std::cend

Produces const iterators.

✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};

    auto it = cbegin(v);
    //*it = 99; // ❌ compile error: const iterator

    for (auto p = cbegin(v); p != cend(v); ++p)
        cout << *p << " ";
}

✔ Output
1 2 3

🟧 Program 23 — std::next

Moves iterator ahead by N steps.

✔ Code
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main() {
    vector<int> v = {5, 10, 15, 20};

    auto it = next(v.begin(), 2);

    cout << *it << endl;
}

✔ Output
15

🟥 Program 24 — std::prev

Moves iterator backward by N steps.

✔ Code
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40};

    auto it = prev(v.end(), 3); // 40 -> 30

    cout << *it << endl;
}

✔ Output
20

🟨 Program 25 — std::advance

Advance iterator (supports negative for bidirectional).

✔ Code
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main() {
    list<int> L = {10, 20, 30, 40, 50};

    auto it = L.begin();
    advance(it, 3); // +3 steps

    cout << *it << endl;
}

✔ Output
40

🟦 Program 26 — std::distance

Returns distance between two iterators.

✔ Code
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main() {
    vector<int> v = {2, 4, 6, 8, 10};

    int dist = distance(v.begin(), v.end());

    cout << dist << endl;
}

✔ Output
5

🟩 Program 27 — Reverse Iterators (rbegin, rend)
✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4};

    for (auto it = v.rbegin(); it != v.rend(); ++it)
        cout << *it << " ";
}

✔ Output
4 3 2 1

🟥 Program 28 — Demonstrating Iterator Categories
• Input iterator
• Forward iterator
• Bidirectional iterator
• Random access iterator

This example prints the category of a given iterator.

✔ Code
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
using namespace std;

template<typename It>
void test(It) {
    using Cat = typename iterator_traits<It>::iterator_category;

    if constexpr (is_same_v<Cat, random_access_iterator_tag>)
        cout << "Random Access Iterator\n";
    else if constexpr (is_same_v<Cat, bidirectional_iterator_tag>)
        cout << "Bidirectional Iterator\n";
    else if constexpr (is_same_v<Cat, forward_iterator_tag>)
        cout << "Forward Iterator\n";
    else if constexpr (is_same_v<Cat, input_iterator_tag>)
        cout << "Input Iterator\n";
    else
        cout << "Unknown\n";
}

int main() {
    vector<int> v = {1, 2, 3};
    list<int>   L = {1, 2, 3};

    test(v.begin());
    test(L.begin());
}

✔ Output
Random Access Iterator
Bidirectional Iterator

/* ----------------------------------------------------------- */

✔ Memory / Allocators
std::align
std::allocator_traits
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */


✔ Concurrency
std::thread
std::mutex, std::recursive_mutex
std::timed_mutex, std::recursive_timed_mutex
std::unique_lock
std::lock_guard
std::condition_variable
std::future, std::promise
std::async
std::packaged_task
std::atomic (all atomic types)
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */


✔ Chrono
std::chrono::duration
std::chrono::time_point
std::chrono::system_clock
std::chrono::steady_clock
std::chrono::high_resolution_clock
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */


✔ Containers
std::array
std::forward_list
std::unordered_map, std::unordered_set
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Misc
std::initializer_list
std::tuple
std::tie
std::ratio
std::regex
std::to_string
std::stoi, std::stoll, etc.
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

⭐ C++14 ADDITIONS
✔ Functional / Utility
std::make_unique
std::integer_sequence
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Type Traits
std::is_final
std::is_null_pointer
std::make_integer_sequence
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Chrono / Ratio
Minor enhancements

✔ Heterogeneous Lookup (unordered_map, map)
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

⭐ C++17 ADDITIONS
✔ Optional / Variant / Any
std::optional
std::variant
std::any
std::in_place_t, std::in_place_type, std::in_place_index
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ String & Filesystem
std::string_view
std::filesystem
std::filesystem::path, exists, copy, etc.
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Parallel Algorithms
All <algorithm> functions got execution policy overloads:
std::execution::seq
std::execution::par
std::execution::par_unseq
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Type Traits Additions
std::void_t
std::invoke_result
std::conjunction
std::disjunction
std::negation
std::is_aggregate
std::is_invocable, std::invoke
std::is_swappable, std::is_nothrow_swappable
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Filesystem Support
<filesystem> fully standardized.
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Concurrency
std::shared_mutex
std::scoped_lock
std::hardware_destructive_interference_size
std::hardware_constructive_interference_size
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Utility
std::size for arrays
std::as_const
std::byte
std::launder
std::clamp
std::apply (for tuples)
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */


⭐ C++20 ADDITIONS
✔ Concepts (<concepts>)
std::same_as
std::integral
std::floating_point
std::invocable
std::predicate
std::regular
std::semiregular
std::totally_ordered
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */


✔ Ranges (<ranges>)
std::ranges::begin, end
std::ranges::sort
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

Views:
std::views::filter
std::views::transform
std::views::reverse
std::views::iota
std::views::take
std::views::drop
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Coroutines (<coroutine>)
std::coroutine_handle
std::suspend_always
std::suspend_never
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Calendar & Time
std::chrono::year, month, day
std::chrono::zoned_time
std::chrono::local_time
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Atomic Improvements
std::atomic_ref
std::atomic_wait
std::atomic_notify_one, notify_all
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Containers
std::span
std::flat_map (C++23 but widely implemented)
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ Utility
std::bit_cast
std::remove_cvref
std::endian
std::source_location
std::format (Python-style formatting)
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */

✔ std::stop_token (Cooperative cancellation)
std::stop_source
std::stop_callback
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */





