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
/* 
✔ Output
Random Access Iterator
Bidirectional Iterator
*/
/* ----------------------------------------------------------- */

✔ Memory / Allocators
std::align
std::allocator_traits
/* ----------------------------------------------------------- */
Program 29 — std::array
✔ Code
#include <iostream>
#include <array>
using namespace std;
int main() {
    array<int, 4> arr = {10, 20, 30, 40};

    cout << "size = " << arr.size() << endl;

    for (int x : arr) cout << x << " ";
}
/* 
✔ Output
size = 4
10 20 30 40
*/



Program 30 — std::vector (C++11/14/17 features)
Shows:
emplace_back
shrink_to_fit
reserve
iteration


✔ Code
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {
        cout << "Construct (" << a << "," << b << ")\n";
    }
};
int main() {
    vector<Point> v;

    v.reserve(3);      // avoid reallocations

    v.emplace_back(1, 2);
    v.emplace_back(3, 4);
    v.emplace_back(5, 6);

    cout << "Size=" << v.size() << ", Capacity=" << v.capacity() << endl;

    v.shrink_to_fit(); // reduce capacity

    cout << "Capacity after shrink=" << v.capacity() << endl;

    for (auto &p : v)
        cout << "(" << p.x << "," << p.y << ") ";
}
/* 
✔ Output
Construct (1,2)
Construct (3,4)
Construct (5,6)
Size=3, Capacity=3
Capacity after shrink=3
(1,2) (3,4) (5,6)
*/


Program 31 — std::deque
✔ Code
#include <iostream>
#include <deque>
using namespace std;
int main() {
    deque<int> dq;

    dq.push_back(10);
    dq.push_front(20);
    dq.push_back(30);

    for (int x : dq)
        cout << x << " ";
}
/* 
✔ Output
20 10 30
*/


Program 32 — std::forward_list (Singly Linked List)
C++11 container with:
push_front
insert_after
erase_after

✔ Code
#include <iostream>
#include <forward_list>
using namespace std;
int main() {
    forward_list<int> fl = {10, 20, 30};

    fl.push_front(5);
    auto it = fl.begin();
    fl.insert_after(it, 7);  // after 5

    fl.erase_after(it);      // erase 7

    for (int x : fl)
        cout << x << " ";
}
/* 
✔ Output
5 10 20 30
*/


Program 33 — std::list (Doubly Linked List)
Demonstrates:
push_front
push_back
sort
reverse

✔ Code
#include <iostream>
#include <list>
using namespace std;
int main() {
    list<int> L = {30, 10, 50, 20};

    L.push_front(5);
    L.push_back(100);

    L.sort();
    L.reverse();

    for (int x : L)
        cout << x << " ";
}
/* 
✔ Output
100 50 30 20 10 5
*/



✅ 6. std::addressof – Get the real memory address even if operator& is overloaded
Sometimes a class overloads operator&, making the normal &object give incorrect results.
std::addressof always returns the true object address.

✔ Program – Using std::addressof
#include <iostream>
#include <memory>
class Example {
  public:
    int x;

    Example(int v) : x(v) {}

    // Overload operator&
    Example* operator&() {
        std::cout << "custom operator& called!" << std::endl;
        return this + 10;     // Wrong address on purpose
    }
};
int main() {
    Example obj(42);

    std::cout << "Using overloaded &: " << &obj << std::endl;

    // Get the true memory address
    std::cout << "Using std::addressof: " << std::addressof(obj) << std::endl;

    return 0;
}
/* 
Output (approx)
custom operator& called!
Using overloaded &: 0x7ffee333af90 (fake wrong)
Using std::addressof: 0x7ffee333af38 (real correct)
*/


✅ 7. std::index_sequence / std::make_index_sequence
Used heavily in template metaprogramming, especially for unpacking tuple elements.

✔ Program – Expanding tuple using index_sequence
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;
// Helper to print tuple using index_sequence
template<typename Tuple, size_t... I>
void printTuple(const Tuple& t, index_sequence<I...>) {
    ((cout << get<I>(t) << " "), ...);
    cout << endl;
}

// Wrapper
template<typename... Args>
void printTuple(const tuple<Args...>& t) {
    printTuple(t, make_index_sequence<sizeof...(Args)>{});
}

int main() {
    auto t = make_tuple(10, 20.5, "Hello");

    cout << "Tuple elements: ";
    printTuple(t);  // automatically expands using index_sequence

    return 0;
}
/* 
Output
Tuple elements: 10 20.5 Hello
*/



✅ 1. std::integral_constant
Used for compile-time constants and template metaprogramming.

✔ Program — Using std::integral_constant
#include <iostream>
#include <type_traits>
template<typename T>
void checkType() {
    if constexpr (std::is_same_v<T, std::integral_constant<int, 5>>) {
        std::cout << "Value is exactly 5\n";
    } else {
        std::cout << "Other type\n";
    }
}
int main() {
    using Five = std::integral_constant<int, 5>;
    using Six  = std::integral_constant<int, 6>;

    std::cout << "Five::value = " << Five::value << std::endl;
    std::cout << "Six::value  = " << Six::value  << std::endl;

    checkType<Five>();
    checkType<Six>();

    return 0;
}
/* 
Output:
Five::value = 5
Six::value = 6
Value is exactly 5
Other type
*/


✅ 2. std::enable_if
Used to enable/disable functions based on type conditions.

✔ Program — Enable only for integral types
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_integral_v<T>, void>
printType(T x) {
    std::cout << "Integral: " << x << std::endl;
}

template<typename T>
std::enable_if_t<!std::is_integral_v<T>, void>
printType(T x) {
    std::cout << "Non-integral: " << x << std::endl;
}

int main() {
    printType(10);      // integral
    printType(3.14);    // non-integral
    return 0;
}
/* 
Output:
Integral: 10
Non-integral: 3.14
*/

✅ 3. std::conditional
Choose one type based on a condition.

✔ Program — Using std::conditional
#include <iostream>
#include <type_traits>
template<bool flag>
void test() {
    using Type = typename std::conditional<flag, int, double>::type;
    std::cout << (flag ? "Type is int" : "Type is double") << std::endl;
}
int main() {
    test<true>();
    test<false>();
    return 0;
}
/* 
Output:
Type is int
Type is double
*/


✅ 4. std::is_same / std::is_base_of
✔ Program — Type comparison
#include <iostream>
#include <type_traits>

class A {};
class B : public A {};
class C {};

int main() {
    std::cout << std::boolalpha;

    std::cout << "is_same<int,int>: "
              << std::is_same_v<int,int> << std::endl;

    std::cout << "is_same<int,double>: "
              << std::is_same_v<int,double> << std::endl;

    std::cout << "is_base_of<A,B>: "
              << std::is_base_of_v<A,B> << std::endl;

    std::cout << "is_base_of<A,C>: "
              << std::is_base_of_v<A,C> << std::endl;

    return 0;
}
/* 
Output:
is_same<int,int>: true
is_same<int,double>: false
is_base_of<A,B>: true
is_base_of<A,C>: false
*/


✅ 5. std::invoke
Calls any callable (function, functor, lambda, member function).

✔ Program — Using std::invoke
#include <iostream>
#include <functional>

struct Foo {
    void hello() const {
        std::cout << "Member function hello()\n";
    }
};

void normalFunction() {
    std::cout << "Normal function called\n";
}

int main() {
    Foo f;

    std::invoke(normalFunction);
    std::invoke(&Foo::hello, f);

    auto lambda = [](){ std::cout << "Lambda called\n"; };
    std::invoke(lambda);

    return 0;
}
/* 
Output:
Normal function called
Member function hello()
Lambda called
*/


✅ 6. std::apply
Used to expand a tuple into function arguments.

✔ Program — Using std::apply
#include <tuple>
#include <iostream>

int sum(int a, int b, int c) {
    return a + b + c;
}

int main() {
    auto t = std::make_tuple(10, 20, 30);

    int result = std::apply(sum, t);

    std::cout << "Sum = " << result << std::endl;

    return 0;
}
/* 
Output:
Sum = 60
*/


✅ 7. std::reference_wrapper
Creates references inside STL containers.

✔ Program — Using reference_wrapper
#include <iostream>
#include <functional>
#include <vector>
int main() {
    int a = 10, b = 20, c = 30;

    std::vector<std::reference_wrapper<int>> v = {a, b, c};

    for (int& x : v) x += 5;

    std::cout << a << " " << b << " " << c << std::endl;

    return 0;
}
/* 
Output:
15 25 35
*/

✅ 8. std::launder
Used to safely access objects created in the same storage via placement new.

✔ Program — Using std::launder
#include <iostream>
#include <new>

struct X {
    int val;
    X(int v) : val(v) {}
};

int main() {
    alignas(X) unsigned char buffer[sizeof(X)];

    X* p = new(buffer) X(10);

    p->~X();
    X* q = new(buffer) X(20);

    X* safePtr = std::launder(reinterpret_cast<X*>(buffer));

    std::cout << safePtr->val << std::endl;

    return 0;
}
/* 
Output:
20
*/


✅ 9. std::aligned_storage & aligned_alloc
✔ Program — Using aligned storage
#include <iostream>
#include <type_traits>

struct Data { double x, y, z; };

int main() {
    std::aligned_storage_t<sizeof(Data), alignof(Data)> storage;

    Data* p = new(&storage) Data{1.1, 2.2, 3.3};

    std::cout << p->x << " " << p->y << " " << p->z << std::endl;

    p->~Data();
    return 0;
}
/* 
Output:
1.1 2.2 3.3
*/





✅ 1. std::optional
Represents a value that may or may not be present.

✔ Program — std::optional basic use
#include <iostream>
#include <optional>
using namespace std;
optional<int> getValue(bool ok) {
    if (ok) return 42;
    return nullopt;
}
int main() {
    auto v1 = getValue(true);
    auto v2 = getValue(false);

    if (v1)
        cout << "v1 = " << *v1 << endl;
    else
        cout << "v1 is empty\n";

    if (v2.has_value())
        cout << "v2 = " << v2.value() << endl;
    else
        cout << "v2 is empty\n";

    return 0;
}
/* 
Output:
v1 = 42
v2 is empty
*/


✅ 2. std::variant
Type-safe union: can hold one of many types.

✔ Program — std::variant with std::visit
#include <iostream>
#include <variant>
#include <string>
using namespace std;
int main() {
    variant<int, double, string> v;

    v = 10;
    cout << "int: " << get<int>(v) << endl;

    v = 3.14;
    cout << "double: " << get<double>(v) << endl;

    v = string("Hello");
    cout << "string: " << get<string>(v) << endl;

    return 0;
}
/* 
Output:
int: 10
double: 3.14
string: Hello
*/


✅ 3. std::visit
Apply a function/lambda to the value inside variant.

✔ Program — std::visit
#include <iostream>
#include <variant>
#include <string>
using namespace std;
int main() {
    variant<int, double, string> v = 3.14;

    auto printer = [](auto&& value){
        cout << "Value = " << value << endl;
    };

    visit(printer, v);

    v = string("Test");
    visit(printer, v);

    return 0;
}
/* 
Output:
Value = 3.14
Value = Test
*/



✅ 4. std::monostate
Used when variant needs a "default" empty state.

✔ Program — std::monostate
#include <iostream>
#include <variant>
#include <string>
using namespace std;
int main() {
    variant<monostate, int, string> v;

    cout << "Index = " << v.index() << endl; // monostate = index 0

    v = 42;
    cout << "Index = " << v.index() << " value = " << get<int>(v) << endl;

    return 0;
}
/* 
Output:
Index = 0
Index = 1 value = 42
*/


✅ 5. std::any
Can store any type (type-erased container).

✔ Program — Basic std::any usage
#include <iostream>
#include <any>
#include <string>
using namespace std;
int main() {
    any a = 10;
    cout << "a = " << any_cast<int>(a) << endl;

    a = string("Hello World");
    cout << "a = " << any_cast<string>(a) << endl;

    // check stored type
    if (a.type() == typeid(string))
        cout << "a holds a string\n";

    return 0;
}
/* 
Output:
a = 10
a = Hello World
a holds a string
*/



✅ 6. std::in_place, std::in_place_type
Construct variant/optional directly without temporary objects.

✔ Program — in_place construction
#include <iostream>
#include <variant>
#include <string>
using namespace std;

int main() {
    variant<int, string> v(in_place_type<string>, 5, 'A'); 
    // Creates string of 5 'A's

    cout << "variant holds string = " << get<string>(v) << endl;

    return 0;
}
/* 
Output:
variant holds string = AAAAA
*/



✅ 7. std::string_view
Non-owning, lightweight string reference.

✔ Program — string_view example
#include <iostream>
#include <string_view>
using namespace std;

void print(string_view sv) {
    cout << "String view: " << sv << endl;
}

int main() {
    string s = "Hello world";
    print(s);
    print("Temporary literal");

    return 0;
}
/* 
Output:
String view: Hello world
String view: Temporary literal
*/


✅ 8. std::byte
Type-safe byte representation.

✔ Program — std::byte operations
#include <iostream>
#include <cstddef>
using namespace std;
int main() {
    byte b{0x3F};

    cout << "b = " << to_integer<int>(b) << endl;

    b = b | byte{0x40};   // bitwise OR
    cout << "after OR = " << to_integer<int>(b) << endl;

    return 0;
}
/* 
Output:
b = 63
after OR = 127
*/





✅ 1. std::filesystem
✔ Program — List files in a directory
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main() {
    string path = "."; // current directory

    cout << "Files in directory:\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << entry.path().string() << endl;
    }

    return 0;
}
/* 
Output (example):
./a.out
./main.cpp
./notes.txt
./folder
*/


✅ 2. std::async / std::future / std::promise
✔ Program — async computes sum in background
#include <iostream>
#include <future>
using namespace std;

int compute() {
    int sum = 0;
    for (int i = 1; i <= 5; i++) sum += i;
    return sum;
}

int main() {
    future<int> f = async(launch::async, compute);

    cout << "Waiting for result...\n";
    cout << "Result = " << f.get() << endl;

    return 0;
}
/* 
Output:
Waiting for result...
Result = 15
*/


✔ Program — using std::promise
#include <iostream>
#include <future>
using namespace std;

void worker(promise<int> p) {
    p.set_value(100);
}

int main() {
    promise<int> p;
    future<int> f = p.get_future();

    thread t(worker, move(p));
    t.join();

    cout << "Value from promise = " << f.get() << endl;

    return 0;
}
/* 
Output:
Value from promise = 100
*/


✅ 3. std::thread
✔ Program — Simple thread
#include <iostream>
#include <thread>
using namespace std;

void task() {
    cout << "Thread running...\n";
}

int main() {
    thread t(task);
    t.join();

    cout << "Main done.\n";
    return 0;
}
/* 
Output:
Thread running...
Main done.
*/


✅ 4. std::jthread (C++20)
Automatically joins on destruction.

✔ Program — jthread auto-joins
#include <iostream>
#include <thread>
using namespace std;

void work() {
    cout << "jthread executing...\n";
}

int main() {
    jthread jt(work); // automatically joins
    cout << "Main thread...\n";

    return 0;
}
/* 
Output:
jthread executing...
Main thread...
*/


✅ 5. std::mutex / std::scoped_lock
✔ Program — scoped_lock prevents deadlocks
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m1, m2;

void task1() {
    scoped_lock lock(m1, m2);
    cout << "Task1 acquired both locks\n";
}

void task2() {
    scoped_lock lock(m1, m2);
    cout << "Task2 acquired both locks\n";
}

int main() {
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();
}
/* 
Output:
Task1 acquired both locks
Task2 acquired both locks
*/


✅ 6. std::shared_mutex / shared_lock
Allows multiple readers, single writer.

✔ Program — shared_mutex example
#include <iostream>
#include <thread>
#include <shared_mutex>
using namespace std;

shared_mutex smtx;
int data = 0;

void reader(int id) {
    shared_lock lock(smtx);
    cout << "Reader " << id << " read: " << data << endl;
}

void writer() {
    unique_lock lock(smtx);
    data += 10;
    cout << "Writer updated data.\n";
}

int main() {
    thread r1(reader, 1);
    thread r2(reader, 2);
    thread w(writer);
    thread r3(reader, 3);

    r1.join();
    r2.join();
    w.join();
    r3.join();
}
/* 
Example Output:
Reader 1 read: 0
Reader 2 read: 0
Writer updated data.
Reader 3 read: 10
*/


✅ 7. std::latch (C++20)
Latch waits until counter hits zero.

✔ Program — latch example
#include <iostream>
#include <thread>
#include <latch>
using namespace std;

latch sync_point(3);

void worker(int id) {
    cout << "Worker " << id << " done.\n";
    sync_point.count_down(); // signal completion
}

int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    sync_point.wait();  
    cout << "All workers finished.\n";

    t1.join();
    t2.join();
    t3.join();
}
/* 
Output:
Worker 1 done.
Worker 2 done.
Worker 3 done.
All workers finished.
*/


✅ 8. std::barrier (C++20)
Lets multiple threads synchronize at phases.

✔ Program — barrier example
#include <iostream>
#include <thread>
#include <barrier>
#include <vector>
using namespace std;

barrier sync_point(3);

void task(int id) {
    cout << "Thread " << id << " reached barrier\n";
    sync_point.arrive_and_wait();
    cout << "Thread " << id << " passed barrier\n";
}

int main() {
    vector<thread> threads;

    for (int i = 1; i <= 3; i++)
        threads.emplace_back(task, i);

    for (auto& t : threads)
        t.join();

    return 0;
}
/* 
Output:
Thread 1 reached barrier
Thread 2 reached barrier
Thread 3 reached barrier
Thread 1 passed barrier
Thread 2 passed barrier
Thread 3 passed barrier
*/




✅ 1. std::span

Non-owning view over contiguous memory (array, vector, C-array).

✔ Program — Using std::span
#include <iostream>
#include <span>
#include <vector>
using namespace std;

void print(span<int> s) {
    for (int x : s) cout << x << " ";
    cout << endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    vector<int> v = {10, 20, 30, 40};

    print(arr);
    print(v);

    print(span(arr).subspan(1, 3)); // 2 3 4

    return 0;
}

Output:
1 2 3 4 5
10 20 30 40
2 3 4

✅ 2. std::ranges (filters, transform, pipeline)
✔ Program — Ranges pipeline: filter -> transform
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4,5,6,7,8};

    auto result =
        v | ranges::views::filter([](int x){ return x % 2 == 0; })
          | ranges::views::transform([](int x){ return x * x; });

    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}

Output:
4 16 36 64

✅ 3. concepts & requires
✔ Program — concept restricting function to integral types
#include <iostream>
using namespace std;

template<typename T>
concept Integral = is_integral_v<T>;

template<Integral T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(10, 20) << endl;
    // add(1.5, 2.5); // ERROR at compile time
    return 0;
}

Output:
30

✔ Program — using requires clause
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
requires requires (T x) { x + x; }   // only types that support +
T twice(T x) {
    return x + x;
}

int main() {
    cout << twice(5) << endl;
    cout << twice(2.5) << endl;
    return 0;
}

Output:
10
5

✅ 4. Spaceship operator <=>

Compiler auto-generates comparison logic.

✔ Program — Auto-comparison with <=>
#include <iostream>
#include <compare>
using namespace std;

struct Point {
    int x, y;

    auto operator<=>(const Point&) const = default;
};

int main() {
    Point a{1,2};
    Point b{1,3};

    cout << boolalpha;
    cout << (a < b) << endl;
    cout << (a == b) << endl;

    return 0;
}

Output:
true
false

✅ 5. std::source_location

Captures file name, line, function name automatically.

✔ Program — source_location example
#include <iostream>
#include <source_location>
using namespace std;

void log(const string& msg,
         const source_location& loc = source_location::current()) 
{
    cout << "Message: " << msg << endl;
    cout << "File: " << loc.file_name() << endl;
    cout << "Function: " << loc.function_name() << endl;
    cout << "Line: " << loc.line() << endl;
}

int main() {
    log("Something happened!");
    return 0;
}
/* 
Output (example):
Message: Something happened!
File: main.cpp
Function: main
Line: 14
*/


✅ 6. std::format (C++20)
Modern safe formatting.

✔ Program — using std::format
#include <iostream>
#include <format>
using namespace std;

int main() {
    string s = format("Hello {}, your score is {}%", "John", 95);
    cout << s << endl;

    cout << format("{:>10}", 123) << endl;  // right aligned
    cout << format("{:^10}", 123) << endl;  // centered

    return 0;
}
/* 
Output:
Hello John, your score is 95%
       123
   123   






1. "{:>10}" → Right alignment
cout << format("{:>10}", 123) << endl;

> means right-align the value.
10 means the total width of the field is 10 characters.
123 has 3 characters.

To make it fit into a field of width 10, the remaining 10 - 3 = 7 spaces are added to the left.
So the output is:
_______123   (7 spaces + 123)




2. "{:^10}" → Center alignment
cout << format("{:^10}", 123) << endl;

^ means center-align the value.
Again, width is 10, value length is 3 → remaining space is 10 - 3 = 7.
Center alignment distributes spaces roughly equally on both sides:
Left: 7 / 2 = 3 spaces
Right: 7 - 3 = 4 spaces

So the output looks like:
___123____   (3 spaces + 123 + 4 spaces)



And their position depends on the alignment (< left, > right, ^ center).
*/



✅ 7. Coroutines — generator
C++20 coroutines return values lazily.

✔ Program — Simple generator coroutine
#include <iostream>
#include <coroutine>
#include <optional>
using namespace std;
template<typename T>
struct Generator {
    struct promise_type {
        T value;
        suspend_always yield_value(T v) {
            value = v;
            return {};
        }
        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        Generator get_return_object() {
            return Generator(coroutine_handle<promise_type>::from_promise(*this));
        }
        void return_void() {}
        void unhandled_exception() { terminate(); }
    };

    coroutine_handle<promise_type> handle;

    Generator(coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    optional<T> next() {
        if (!handle.done()) {
            handle.resume();
            return handle.promise().value;
        }
        return nullopt;
    }
};
Generator<int> counter(int n) {
    for (int i = 1; i <= n; i++)
        co_yield i;
}
int main() {
    auto g = counter(5);

    while (auto val = g.next())
        cout << *val << " ";

    return 0;
}
/* 
Output:
1 2 3 4 5
*/



✅ 1. std::sync_wait + task (C++23 coroutines)
✔ Program — simple coroutine task
#include <iostream>
#include <coroutine>
#include <syncstream>
#include <thread>
using namespace std;
struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        suspend_never initial_suspend() { return {}; }
        suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { terminate(); }
    };
};
Task printNumbers() {
    for (int i = 1; i <= 5; ++i) {
        cout << i << " ";
        co_await std::suspend_never{};
    }
    cout << endl;
}

int main() {
    printNumbers();
    return 0;
}
/* 
Output:
1 2 3 4 5

(Note: In C++23, std::sync_wait can also wait on coroutine tasks asynchronously.)
*/

✅ 2. std::ranges enhancements (C++23)
take, drop, join

✔ Program — ranges::take / drop / join
#include <iostream>
#include <vector>
#include <ranges>
#include <string>
using namespace std;
int main() {
    vector<int> v = {1,2,3,4,5,6,7};

    auto first3 = v | ranges::views::take(3);  // 1,2,3
    auto skip2 = v | ranges::views::drop(2);   // 3,4,5,6,7

    for(int x:first3) cout << x << " ";
    cout << endl;

    for(int x:skip2) cout << x << " ";
    cout << endl;

    vector<vector<int>> vv = {{1,2},{3,4},{5,6}};
    for(int x : vv | ranges::views::join)
        cout << x << " ";
    cout << endl;

    return 0;
}
/* 
Output:
1 2 3
3 4 5 6 7
1 2 3 4 5 6
*/


✅ 3. std::flat_map / std::flat_set (C++23)
Cache-friendly alternatives to map/set.

✔ Program — flat_map example
#include <iostream>
#include <flat_map>
using namespace std;
int main() {
    flat_map<int, string> fm;
    fm[3] = "three";
    fm[1] = "one";
    fm[2] = "two";

    for(auto &[k,v] : fm)
        cout << k << " -> " << v << endl;

    return 0;
}
/* 
Output:
1 -> one
2 -> two
3 -> three
*/


✅ 4. std::print / std::format_to (C++23)
✔ Program — std::print example
#include <iostream>
#include <print>
#include <format>
using namespace std;
int main() {
    print("Hello {}, your score is {}\n", "Alice", 98);

    string s = format_to<string>("{} + {} = {}\n", 2, 3, 5);
    cout << s;

    return 0;
}
/* 
Output:
Hello Alice, your score is 98
2 + 3 = 5
*/


✅ 5. std::expected / std::unwrap (C++23)**
std::expected<T, E> is like a result type (value or error).

✔ Program — std::expected
#include <iostream>
#include <expected>
using namespace std;

expected<int, string> divide(int a, int b) {
    if(b == 0) return unexpected("Division by zero");
    return a / b;
}

int main() {
    auto res1 = divide(10,2);
    if(res1) cout << "Result = " << res1.value() << endl;
    else cout << "Error: " << res1.error() << endl;

    auto res2 = divide(5,0);
    if(res2) cout << "Result = " << res2.value() << endl;
    else cout << "Error: " << res2.error() << endl;

    return 0;
}
/* 
Output:
Result = 5
Error: Division by zero
*/



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
1. std::thread
#include <iostream>
#include <thread>

void printNumbers() {
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::thread t(printNumbers); // create thread
    t.join();                    // wait for thread to finish
    return 0;
}

/* Output:
1 2 3 4 5
*/

2. std::mutex
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        ++counter;
        std::cout << "Counter: " << counter << std::endl;
        mtx.unlock();
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    return 0;
}

/* Output (order may vary):
Counter: 1
Counter: 2
Counter: 3
...
*/

3. std::lock_guard
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 5; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // RAII locking
        ++counter;
        std::cout << "Counter: " << counter << std::endl;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    return 0;
}

/* Output (order may vary):
Counter: 1
Counter: 2
...
*/

4. std::unique_lock
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        ++counter;
        std::cout << "Counter: " << counter << std::endl;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    return 0;
}

/* Output similar to lock_guard example */

5. std::condition_variable
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void printEven() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; }); // wait until ready is true
    std::cout << "Even numbers: 2 4 6 8 10" << std::endl;
}

void prepare() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Data ready" << std::endl;
    }
    cv.notify_one();
}

int main() {
    std::thread t1(printEven);
    std::thread t2(prepare);
    t1.join();
    t2.join();
    return 0;
}

/* Output:
Data ready
Even numbers: 2 4 6 8 10
*/

6. std::future and std::promise
#include <iostream>
#include <thread>
#include <future>

void compute(std::promise<int> prom) {
    int result = 42; // some computation
    prom.set_value(result);
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    
    std::thread t(compute, std::move(prom));
    
    std::cout << "Result from thread: " << fut.get() << std::endl;
    t.join();
    return 0;
}

/* Output:
Result from thread: 42
*/

7. std::async
#include <iostream>
#include <future>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

int main() {
    std::future<int> fut = std::async(std::launch::async, factorial, 5);
    std::cout << "Factorial of 5: " << fut.get() << std::endl;
    return 0;
}

/* Output:
Factorial of 5: 120
*/

8. std::packaged_task
#include <iostream>
#include <future>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    std::packaged_task<int(int,int)> task(multiply);
    std::future<int> result = task.get_future();
    
    std::thread t(std::move(task), 6, 7);
    std::cout << "6 * 7 = " << result.get() << std::endl;
    t.join();
    return 0;
}

/* Output:
6 * 7 = 42
*/

9. std::atomic
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);

void increment() {
    for (int i = 0; i < 1000; ++i) {
        ++counter;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Final counter: " << counter.load() << std::endl;
    return 0;
}

/* Output:
Final counter: 2000
*/


/* ----------------------------------------------------------- */


✔ Chrono
std::chrono::duration
std::chrono::time_point
std::chrono::system_clock
std::chrono::steady_clock
std::chrono::high_resolution_clock
/* ----------------------------------------------------------- */
✅ 1. std::chrono::duration
Represents a time duration with a count and period (seconds, milliseconds, etc.).

✔ Program — Using std::chrono::duration
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    duration<int> d1(10); // 10 seconds
    cout << "d1 = " << d1.count() << " seconds" << endl;

    milliseconds ms(500);
    cout << "ms = " << ms.count() << " milliseconds" << endl;

    auto sec = duration_cast<seconds>(ms);
    cout << "ms converted to seconds = " << sec.count() << " seconds" << endl;

    return 0;
}
/* 
Output:
d1 = 10 seconds
ms = 500 milliseconds
ms converted to seconds = 0 seconds
*/


✅ 2. std::chrono::time_point
Represents a point in time with respect to a clock.

✔ Program — Using std::chrono::time_point
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    system_clock::time_point now = system_clock::now();
    auto epoch_time = now.time_since_epoch();
    auto seconds_since_epoch = duration_cast<seconds>(epoch_time).count();

    cout << "Seconds since epoch: " << seconds_since_epoch << endl;

    // Add 5 seconds to now
    system_clock::time_point future = now + seconds(5);
    auto future_sec = duration_cast<seconds>(future.time_since_epoch()).count();
    cout << "Future (now + 5s) = " << future_sec << " seconds since epoch" << endl;

    return 0;
}
/* 
Output (example):
Seconds since epoch: 1700000000
Future (now + 5s) = 1700000005
*/


✅ 3. std::chrono::system_clock
Represents the real-world clock (wall-clock time).

✔ Program — system_clock example
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

int main() {
    system_clock::time_point now = system_clock::now();
    time_t tt = system_clock::to_time_t(now);

    cout << "Current time: " << ctime(&tt); // ctime converts to readable string

    // Measure elapsed time after sleep
    auto start = system_clock::now();
    this_thread::sleep_for(seconds(2));
    auto end = system_clock::now();
    cout << "Elapsed = " 
         << duration_cast<milliseconds>(end - start).count() 
         << " ms" << endl;

    return 0;
}
/* 
Output (example):
Current time: Fri Dec  6 12:45:32 2025
Elapsed = 2000 ms
*/



✅ 4. std::chrono::steady_clock
Monotonic clock cannot go backward, useful for measuring intervals.

✔ Program — steady_clock example
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

int main() {
    auto start = steady_clock::now();
    this_thread::sleep_for(milliseconds(500));
    auto end = steady_clock::now();

    auto elapsed = duration_cast<milliseconds>(end - start);
    cout << "Elapsed time (steady_clock) = " << elapsed.count() << " ms" << endl;

    return 0;
}
/* 
Output:
Elapsed time (steady_clock) = 500 ms
*/



✅ 5. std::chrono::high_resolution_clock
Clock with the shortest tick period, may be an alias for steady_clock or system_clock.

✔ Program — high_resolution_clock example
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();
    this_thread::sleep_for(milliseconds(200));
    auto end = high_resolution_clock::now();

    auto elapsed = duration_cast<microseconds>(end - start);
    cout << "Elapsed time (high_resolution_clock) = " 
         << elapsed.count() << " microseconds" << endl;

    return 0;
}
/* 
Output (example):
Elapsed time (high_resolution_clock) = 200123 microseconds
*/
/* ----------------------------------------------------------- */


✔ Containers
std::array
std::forward_list
std::unordered_map, std::unordered_set

/* ----------------------------------------------------------- */
✅ 1. std::array

Fixed-size array with STL-like interface.

✔ Program — Using std::array
#include <iostream>
#include <array>
using namespace std;

int main() {
    array<int, 5> arr = {10, 20, 30, 40, 50};

    cout << "Array elements: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << "Size of array: " << arr.size() << endl;

    arr[2] = 100;
    cout << "After modifying index 2: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}

Output:
Array elements: 10 20 30 40 50
Size of array: 5
After modifying index 2: 10 20 100 40 50

✅ 2. std::forward_list

Singly linked list (efficient for insert/remove at front).

✔ Program — Using std::forward_list
#include <iostream>
#include <forward_list>
using namespace std;

int main() {
    forward_list<int> fl = {1, 2, 3, 4};

    cout << "Original forward_list: ";
    for (int x : fl) cout << x << " ";
    cout << endl;

    fl.push_front(0); // add at front
    cout << "After push_front(0): ";
    for (int x : fl) cout << x << " ";
    cout << endl;

    fl.pop_front(); // remove front
    cout << "After pop_front(): ";
    for (int x : fl) cout << x << " ";
    cout << endl;

    // Insert after first element
    auto it = fl.begin();
    ++it;
    fl.insert_after(it, 100);

    cout << "After insert_after second element (100): ";
    for (int x : fl) cout << x << " ";
    cout << endl;

    return 0;
}

Output:
Original forward_list: 1 2 3 4
After push_front(0): 0 1 2 3 4
After pop_front(): 1 2 3 4
After insert_after second element (100): 1 2 100 3 4

✅ 3. std::unordered_map

Hash-based map (key → value).

✔ Program — Using std::unordered_map
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> umap;

    // Insert elements
    umap["apple"] = 3;
    umap["banana"] = 5;
    umap["orange"] = 2;

    // Access elements
    cout << "apple = " << umap["apple"] << endl;

    // Iterate
    cout << "All key-value pairs:\n";
    for (auto &[key, value] : umap)
        cout << key << " -> " << value << endl;

    // Check if key exists
    if (umap.find("banana") != umap.end())
        cout << "banana found!\n";

    return 0;
}

Output (example, order may vary):
apple = 3
All key-value pairs:
orange -> 2
apple -> 3
banana -> 5
banana found!

✅ 4. std::unordered_set

Hash-based set (unique elements, fast lookup).

✔ Program — Using std::unordered_set
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> uset = {10, 20, 30, 40};

    cout << "Original unordered_set: ";
    for (int x : uset) cout << x << " ";
    cout << endl;

    // Insert element
    uset.insert(25);
    cout << "After insert(25): ";
    for (int x : uset) cout << x << " ";
    cout << endl;

    // Check if element exists
    if (uset.count(30)) cout << "30 exists in set\n";

    // Remove element
    uset.erase(20);
    cout << "After erase(20): ";
    for (int x : uset) cout << x << " ";
    cout << endl;

    return 0;
}

Output (example, order may vary):
Original unordered_set: 40 10 20 30
After insert(25): 40 10 25 20 30
30 exists in set
After erase(20): 40 10 25 30




✅ 1. std::deque

Double-ended queue: efficient insert/remove at both ends.

✔ Program — Using std::deque
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> dq = {10, 20, 30};

    cout << "Original deque: ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    dq.push_front(5);
    dq.push_back(40);
    cout << "After push_front(5) and push_back(40): ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    dq.pop_front();
    dq.pop_back();
    cout << "After pop_front() and pop_back(): ";
    for (int x : dq) cout << x << " ";
    cout << endl;

    return 0;
}

Output:
Original deque: 10 20 30
After push_front(5) and push_back(40): 5 10 20 30 40
After pop_front() and pop_back(): 10 20 30

✅ 2. std::list

Doubly linked list: efficient insert/remove anywhere.

✔ Program — Using std::list
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> lst = {1, 2, 3, 4};

    cout << "Original list: ";
    for (int x : lst) cout << x << " ";
    cout << endl;

    lst.push_front(0);
    lst.push_back(5);
    cout << "After push_front(0) and push_back(5): ";
    for (int x : lst) cout << x << " ";
    cout << endl;

    // Insert 100 after second element
    auto it = lst.begin();
    ++it; // move to second
    ++it; // move to third
    lst.insert(it, 100);

    cout << "After insert(100) at 3rd position: ";
    for (int x : lst) cout << x << " ";
    cout << endl;

    // Remove element
    lst.remove(3);
    cout << "After remove(3): ";
    for (int x : lst) cout << x << " ";
    cout << endl;

    return 0;
}

Output:
Original list: 1 2 3 4
After push_front(0) and push_back(5): 0 1 2 3 4 5
After insert(100) at 3rd position: 0 1 100 2 3 4 5
After remove(3): 0 1 100 2 4 5

✅ 3. std::map

Ordered key → value container (balanced tree).

✔ Program — Using std::map
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> mp;

    mp["apple"] = 3;
    mp["banana"] = 5;
    mp["orange"] = 2;

    cout << "All key-value pairs (ordered):\n";
    for (auto &[k,v] : mp)
        cout << k << " -> " << v << endl;

    // Accessing values
    cout << "apple = " << mp["apple"] << endl;

    // Erase key
    mp.erase("banana");
    cout << "After erase(banana):\n";
    for (auto &[k,v] : mp)
        cout << k << " -> " << v << endl;

    return 0;
}

Output:
All key-value pairs (ordered):
apple -> 3
banana -> 5
orange -> 2
apple = 3
After erase(banana):
apple -> 3
orange -> 2

✅ 4. std::set

Ordered set of unique elements.

✔ Program — Using std::set
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s = {5, 1, 3, 4, 2};

    cout << "Original set (sorted): ";
    for (int x : s) cout << x << " ";
    cout << endl;

    s.insert(6);
    cout << "After insert(6): ";
    for (int x : s) cout << x << " ";
    cout << endl;

    s.erase(3);
    cout << "After erase(3): ";
    for (int x : s) cout << x << " ";
    cout << endl;

    if (s.count(4)) cout << "4 exists in set\n";

    return 0;
}

Output:
Original set (sorted): 1 2 3 4 5
After insert(6): 1 2 3 4 5 6
After erase(3): 1 2 4 5 6
4 exists in set

✅ 5. std::multimap / std::multiset

Allow duplicate keys/elements.

✔ Program — Using std::multimap
#include <iostream>
#include <map>
using namespace std;

int main() {
    multimap<string, int> mmap;

    mmap.insert({"apple", 1});
    mmap.insert({"apple", 2});
    mmap.insert({"banana", 3});

    cout << "multimap contents:\n";
    for (auto &[k,v] : mmap)
        cout << k << " -> " << v << endl;

    return 0;
}

Output:
multimap contents:
apple -> 1
apple -> 2
banana -> 3

✔ Program — Using std::multiset
#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int> ms = {1,2,2,3,4,4,4};

    cout << "Original multiset: ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    ms.insert(5);
    cout << "After insert(5): ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    ms.erase(2); // erases all 2s
    cout << "After erase(2): ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    return 0;
}

Output:
Original multiset: 1 2 2 3 4 4 4
After insert(5): 1 2 2 3 4 4 4 5
After erase(2): 1 3 4 4 4 5




✅ 1. std::stack

LIFO container adapter (last-in, first-out).

✔ Program — Using std::stack
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> st;

    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top element: " << st.top() << endl;

    st.pop();
    cout << "After pop, top element: " << st.top() << endl;

    cout << "Stack elements (from top to bottom): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    return 0;
}

Output:
Top element: 30
After pop, top element: 20
Stack elements (from top to bottom): 20 10

✅ 2. std::queue

FIFO container adapter (first-in, first-out).

✔ Program — Using std::queue
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.front() << endl;
    cout << "Back element: " << q.back() << endl;

    q.pop();
    cout << "After pop, front element: " << q.front() << endl;

    cout << "Queue elements: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    return 0;
}

Output:
Front element: 10
Back element: 30
After pop, front element: 20
Queue elements: 20 30

✅ 3. std::priority_queue

Heap-based queue (by default max-heap).

✔ Program — Using std::priority_queue
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    priority_queue<int> pq; // max-heap

    pq.push(10);
    pq.push(30);
    pq.push(20);

    cout << "Priority queue elements (pop order): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    // Min-heap example
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(10);
    min_pq.push(30);
    min_pq.push(20);

    cout << "Min-heap elements (pop order): ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";
        min_pq.pop();
    }
    cout << endl;

    return 0;
}

Output:
Priority queue elements (pop order): 30 20 10
Min-heap elements (pop order): 10 20 30




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
✅ 1. std::initializer_list

Represents a list of elements that can be used for uniform initialization.

✔ Program — Using std::initializer_list
#include <iostream>
#include <initializer_list>
using namespace std;

void printList(initializer_list<int> list) {
    for (auto x : list) cout << x << " ";
    cout << endl;
}

int main() {
    printList({1, 2, 3, 4, 5});
    return 0;
}

Output:
1 2 3 4 5

✅ 2. std::tuple

Stores a fixed-size collection of heterogeneous types.

✔ Program — Using std::tuple
#include <iostream>
#include <tuple>
#include <string>
using namespace std;

int main() {
    tuple<int, string, double> t = {1, "Alice", 3.14};

    cout << "Tuple elements: "
         << get<0>(t) << ", "
         << get<1>(t) << ", "
         << get<2>(t) << endl;

    return 0;
}

Output:
Tuple elements: 1, Alice, 3.14

✅ 3. std::tie

Unpacks tuple elements into variables.

✔ Program — Using std::tie
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    tuple<int,int,int> t = {10,20,30};
    int a,b,c;

    tie(a,b,c) = t; // unpack tuple

    cout << "a=" << a << ", b=" << b << ", c=" << c << endl;

    return 0;
}

Output:
a=10, b=20, c=30

✅ 4. std::ratio

Represents compile-time rational numbers (used with chrono).

✔ Program — Using std::ratio
#include <iostream>
#include <ratio>
using namespace std;

int main() {
    typedef ratio<1, 1000> milli;
    typedef ratio<60> minute;

    cout << "1 milli = " << milli::num << "/" << milli::den << endl;
    cout << "1 minute = " << minute::num << "/" << minute::den << endl;

    return 0;
}

Output:
1 milli = 1/1000
1 minute = 60/1

✅ 5. std::regex

Regular expressions for pattern matching.

✔ Program — Using std::regex
#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
    string text = "Email: test@example.com";
    regex pattern(R"(\w+@\w+\.\w+)"); // simple email regex

    smatch match;
    if (regex_search(text, match, pattern))
        cout << "Found email: " << match.str() << endl;

    return 0;
}

Output:
Found email: test@example.com

✅ 6. std::to_string

Convert numbers to strings.

✔ Program — Using std::to_string
#include <iostream>
#include <string>
using namespace std;

int main() {
    int x = 42;
    double y = 3.14159;

    string sx = to_string(x);
    string sy = to_string(y);

    cout << "Integer to string: " << sx << endl;
    cout << "Double to string: " << sy << endl;

    return 0;
}

Output:
Integer to string: 42
Double to string: 3.141590

✅ 7. std::stoi / std::stoll / std::stod etc.

Convert strings to numbers.

✔ Program — Using std::stoi, std::stoll, std::stod
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1 = "123";
    string s2 = "9876543210";
    string s3 = "3.14159";

    int i = stoi(s1);
    long long ll = stoll(s2);
    double d = stod(s3);

    cout << "stoi: " << i << endl;
    cout << "stoll: " << ll << endl;
    cout << "stod: " << d << endl;

    return 0;
}

Output:
stoi: 123
stoll: 9876543210
stod: 3.14159





✅ 8. std::any

Type-safe container for single values of any type.

✔ Program — Using std::any
#include <iostream>
#include <any>
#include <string>
using namespace std;

int main() {
    any a = 10;
    cout << "a holds int: " << any_cast<int>(a) << endl;

    a = string("Hello Any");
    cout << "a now holds string: " << any_cast<string>(a) << endl;

    // Check type
    if (a.type() == typeid(string))
        cout << "a is a string type\n";

    return 0;
}

Output:
a holds int: 10
a now holds string: Hello Any
a is a string type

✅ 9. std::variant

Holds one of several types safely (type-safe union).

✔ Program — Using std::variant
#include <iostream>
#include <variant>
#include <string>
using namespace std;

int main() {
    variant<int, double, string> v;

    v = 42;
    cout << "v holds int: " << get<int>(v) << endl;

    v = 3.14;
    cout << "v now holds double: " << get<double>(v) << endl;

    v = "Hello Variant";
    cout << "v now holds string: " << get<string>(v) << endl;

    return 0;
}

Output:
v holds int: 42
v now holds double: 3.14
v now holds string: Hello Variant

✅ 10. std::optional

Represents a value that may or may not exist.

✔ Program — Using std::optional
#include <iostream>
#include <optional>
#include <string>
using namespace std;

optional<int> findEven(int x) {
    if (x % 2 == 0) return x;
    return nullopt;
}

int main() {
    optional<int> a = findEven(5);
    optional<int> b = findEven(8);

    if(a) cout << "a = " << a.value() << endl;
    else cout << "a has no value\n";

    if(b) cout << "b = " << b.value() << endl;

    return 0;
}

Output:
a has no value
b = 8

✅ 11. std::enable_if (SFINAE)

Conditional function enabling based on type traits.

✔ Program — Using std::enable_if
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
typename enable_if<is_integral<T>::value, T>::type
square(T x) { return x*x; }

int main() {
    cout << "Square of 5: " << square(5) << endl;
    // square(3.14); // Compile-time error
    return 0;
}

Output:
Square of 5: 25

✅ 12. std::forward_list

Already covered in containers, but commonly used in low-memory operations.

✅ 13. std::atomic / std::memory_order

For thread-safe variables and lock-free programming.

✔ Program — Using std::atomic
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

atomic<int> counter(0);

void increment() {
    for(int i=0;i<1000;i++)
        counter++;
}

int main() {
    thread t1(increment);
    thread t2(increment);
    t1.join();
    t2.join();

    cout << "Counter = " << counter.load() << endl;
    return 0;
}

Output:
Counter = 2000

✅ 14. std::string_view (C++17)

Lightweight non-owning view of string.

✔ Program — Using std::string_view
#include <iostream>
#include <string_view>
using namespace std;

void print_sv(string_view sv) {
    cout << sv << endl;
}

int main() {
    string s = "Hello StringView";
    print_sv(s);             // from std::string
    print_sv("Literal Text"); // from string literal
    return 0;
}

Output:
Hello StringView
Literal Text

✅ 15. std::scoped_lock / std::mutex

For thread synchronization.

✔ Program — Using std::scoped_lock
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;

void print_safe(const string& msg) {
    scoped_lock lock(mtx);
    cout << msg << endl;
}

int main() {
    thread t1(print_safe, "Thread 1");
    thread t2(print_safe, "Thread 2");

    t1.join();
    t2.join();
    return 0;
}

Output (order may vary):
Thread 1
Thread 2

/* ----------------------------------------------------------- */

⭐ C++14 ADDITIONS
✔ Functional / Utility
std::make_unique
std::integer_sequence

/* ----------------------------------------------------------- */
✅ 1. std::make_unique (C++14)

std::make_unique is used to create a unique_ptr safely. It avoids manual new and ensures exception safety.

✔ Program — Using std::make_unique
#include <iostream>
#include <memory>
using namespace std;

class MyClass {
public:
    MyClass(int x) { cout << "Constructor called with x=" << x << endl; }
    void display() { cout << "Display function called\n"; }
};

int main() {
    // Create unique_ptr using make_unique
    unique_ptr<MyClass> ptr = make_unique<MyClass>(42);

    ptr->display();

    // No need to delete, automatically freed
    return 0;
}

Output:
Constructor called with x=42
Display function called


Key Notes:

Safer than unique_ptr<MyClass> ptr(new MyClass(42));

Automatically deallocates memory when pointer goes out of scope.

✅ 2. std::integer_sequence (C++14)

std::integer_sequence is a compile-time sequence of integers used often with template metaprogramming.
It’s commonly paired with std::index_sequence.

✔ Program — Using std::integer_sequence
#include <iostream>
#include <utility> // For integer_sequence
using namespace std;

// Function to print an integer_sequence
template<int... Ints>
void print_sequence(integer_sequence<int, Ints...>) {
    ((cout << Ints << " "), ...); // Fold expression (C++17) style
    cout << endl;
}

int main() {
    // Create integer_sequence 0,1,2,3,4
    integer_sequence<int, 0,1,2,3,4> seq;

    cout << "Integer sequence: ";
    print_sequence(seq);

    // Or generate using make_integer_sequence
    auto seq2 = make_integer_sequence<int, 5>{}; // 0,1,2,3,4
    cout << "Generated integer sequence: ";
    print_sequence(seq2);

    return 0;
}

Output:
Integer sequence: 0 1 2 3 4 
Generated integer sequence: 0 1 2 3 4 


Key Notes:

Useful for expanding tuples, parameter packs, and compile-time loops.

Works with template metaprogramming to generate indices.







C++14 ADDITIONS (continued)
3️⃣ Generic Lambdas

C++14 allows auto parameters in lambdas, making them generic.

✔ Program — Generic Lambda
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    auto add = [](auto a, auto b) { return a + b; };

    cout << add(5, 3) << endl;      // integers
    cout << add(2.5, 3.5) << endl;  // doubles

    vector<int> v = {1,2,3,4,5};
    int sum = 0;
    for_each(v.begin(), v.end(), [&](auto x){ sum += x; });

    cout << "Sum of vector: " << sum << endl;
    return 0;
}

Output:
8
6
Sum of vector: 15

4️⃣ Return Type Deduction (auto)

C++14 allows automatic return type deduction in functions.

✔ Program — Return Type Deduction
#include <iostream>
using namespace std;

auto multiply(auto a, auto b) { return a * b; } // C++14 feature

int main() {
    cout << multiply(5, 4) << endl;       // int
    cout << multiply(2.5, 3.0) << endl;   // double
    return 0;
}

Output:
20
7.5

5️⃣ Variable Templates

C++14 allows templated variables for constants.

✔ Program — Variable Templates
#include <iostream>
using namespace std;

template<typename T>
constexpr T pi = T(3.1415926535897932385);

int main() {
    cout << pi<float> << endl;
    cout << pi<double> << endl;
    return 0;
}

Output:
3.14159
3.14159

6️⃣ std::shared_timed_mutex (C++14)

Allows shared (reader) and exclusive (writer) locks.

✔ Program — Shared Timed Mutex
#include <iostream>
#include <thread>
#include <shared_mutex>
using namespace std;

shared_timed_mutex smtx;
int data = 0;

void reader() {
    shared_lock lock(smtx);
    cout << "Reader sees data = " << data << endl;
}

void writer() {
    unique_lock lock(smtx);
    data += 10;
    cout << "Writer updated data to " << data << endl;
}

int main() {
    thread t1(reader);
    thread t2(writer);
    thread t3(reader);

    t1.join(); t2.join(); t3.join();
    return 0;
}

Output (example, order may vary):
Reader sees data = 0
Writer updated data to 10
Reader sees data = 10

7️⃣ std::make_integer_sequence (already covered with std::integer_sequence)

Used to generate compile-time sequences.






/* ----------------------------------------------------------- */

✔ Type Traits
std::is_final
std::is_null_pointer
std::make_integer_sequence

complete each with complete code in c++ with main and suitable example each separate program code
/* ----------------------------------------------------------- */
1️⃣ std::is_final

std::is_final checks at compile time whether a class is final (cannot be inherited).

#include <iostream>
#include <type_traits>

using namespace std;

// A final class
class FinalClass final {};

// A normal class
class NormalClass {};

int main() {
    cout << boolalpha; // print true/false instead of 1/0
    
    cout << "Is FinalClass final? " << is_final<FinalClass>::value << endl;
    cout << "Is NormalClass final? " << is_final<NormalClass>::value << endl;

    return 0;
}


Output:

Is FinalClass final? true
Is NormalClass final? false

2️⃣ std::is_null_pointer

std::is_null_pointer checks if a type is std::nullptr_t.

#include <iostream>
#include <type_traits>

using namespace std;

int main() {
    cout << boolalpha;

    cout << "Is nullptr type null pointer? " 
         << is_null_pointer<decltype(nullptr)>::value << endl;
    
    cout << "Is int null pointer? " 
         << is_null_pointer<int>::value << endl;

    return 0;
}


Output:

Is nullptr type null pointer? true
Is int null pointer? false

3️⃣ std::make_integer_sequence

std::make_integer_sequence generates a compile-time sequence of integers from 0 to N-1. Useful with templates and parameter packs.

#include <iostream>
#include <utility> // for std::integer_sequence, make_integer_sequence

using namespace std;

// Function to print integer sequence
template<typename Seq>
void print_sequence(Seq) {}

template<size_t... Is>
void print_sequence(integer_sequence<size_t, Is...>) {
    ((cout << Is << " "), ...); // fold expression to print all
    cout << endl;
}

int main() {
    using seq = make_integer_sequence<size_t, 5>; // generates 0,1,2,3,4
    
    cout << "Integer sequence generated by make_integer_sequence: ";
    print_sequence(seq{});

    return 0;
}


Output:

Integer sequence generated by make_integer_sequence: 0 1 2 3 4 






Advanced Example: Using make_integer_sequence to print a tuple
#include <iostream>
#include <tuple>
#include <utility> // for make_integer_sequence

using namespace std;

// Helper function to print a tuple using index sequence
template<typename Tuple, size_t... Is>
void print_tuple(const Tuple& t, std::index_sequence<Is...>) {
    ((cout << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    cout << endl;
}

// Wrapper function
template<typename... Args>
void print_tuple(const tuple<Args...>& t) {
    print_tuple(t, make_index_sequence<sizeof...(Args)>{});
}

int main() {
    tuple<int, string, double> t{42, "Hello", 3.14};
    
    cout << "Tuple elements: ";
    print_tuple(t);

    return 0;
}


Output:

Tuple elements: 42, Hello, 3.14


✅ Explanation:

make_index_sequence<sizeof...(Args)> generates a compile-time sequence 0, 1, 2… for tuple indices.

The helper function expands the indices using fold expressions to print all elements.

This avoids manual loops and works for tuples of any size at compile time.













Example: Compile-time array initialization with make_integer_sequence
#include <iostream>
#include <utility> // for make_integer_sequence, index_sequence
using namespace std;
// Function to initialize array with values equal to index squared
template<size_t... Is>
constexpr auto make_squared_array(index_sequence<Is...>) {
    return array<int, sizeof...(Is)>{ ((Is * Is))... };
}
int main() {
    constexpr auto arr = make_squared_array(make_index_sequence<10>{}); // 0..9 squared

    cout << "Array of squares: ";
    for (auto x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

Output:
Array of squares: 0 1 4 9 16 25 36 49 64 81

✅ Explanation:
make_index_sequence<10> generates indices 0,1,2,...,9.
The parameter pack Is... expands to each index.
The fold-like expansion ((Is * Is))... computes squares at compile-time.
constexpr ensures the array is fully computed at compile-time, which is efficient and avoids runtime loops.



Example: Apply a function to every tuple element
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;
// Function to apply a callable to each element of a tuple
template<typename Tuple, typename Func, size_t... Is>
void for_each_in_tuple(Tuple&& t, Func&& f, index_sequence<Is...>) {
    // Expand the indices and call the function on each element
    (f(get<Is>(t)), ...);  // fold expression
}
// Wrapper function
template<typename Tuple, typename Func>
void for_each_in_tuple(Tuple&& t, Func&& f) {
    for_each_in_tuple(forward<Tuple>(t), forward<Func>(f),
                      make_index_sequence<tuple_size_v<remove_reference_t<Tuple>>>{});
}
int main() {
    auto t = make_tuple(1, 2.5, "Hello");

    cout << "Applying function to each tuple element:" << endl;
    for_each_in_tuple(t, [](const auto& x) { cout << x << " "; });
    cout << endl;

    return 0;
}

Output:
Applying function to each tuple element:
1 2.5 Hello 


✅ Explanation:
make_index_sequence<tuple_size_v<Tuple>> generates indices for all tuple elements.
The helper expands indices with a fold expression: (f(get<Is>(t)), ...).
This allows you to apply any callable (lambda, function pointer, functor) to each element of a tuple at compile-time.
Works for tuples with heterogeneous types, no runtime loops needed.




/* ----------------------------------------------------------- */

✔ Chrono / Ratio
Minor enhancements

✔ Heterogeneous Lookup (unordered_map, map)

complete each with complete code in c++ with main and suitable example each separate program code
/* ----------------------------------------------------------- */
1️⃣ Chrono / Ratio – Minor Enhancements

C++ <chrono> and <ratio> allow us to work with time durations, clocks, and compile-time rational numbers. C++11 onward introduced them, and minor enhancements in later standards include user-defined literals for durations, and easier conversions.

Example: Using chrono with ratio and literals

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    // Using chrono literals (C++14 onward)
    auto duration1 = 5s;       // 5 seconds
    auto duration2 = 200ms;    // 200 milliseconds

    // Using duration_cast to convert milliseconds to seconds
    auto duration_sec = duration_cast<seconds>(duration2);

    cout << "Duration1: " << duration1.count() << " seconds" << endl;
    cout << "Duration2: " << duration2.count() << " milliseconds" << endl;
    cout << "Duration2 converted to seconds: " << duration_sec.count() << " seconds" << endl;

    // Using ratio: defining minutes using ratio
    typedef ratio<60> one_minute; // 60 seconds
    cout << "One minute = " << one_minute::num << "/" << one_minute::den << " seconds" << endl;

    return 0;
}


Sample Output:

Duration1: 5 seconds
Duration2: 200 milliseconds
Duration2 converted to seconds: 0 seconds
One minute = 60/1 seconds


✅ Notes:

5s and 200ms are user-defined literals (chrono_literals).

ratio helps define compile-time rational numbers (ratio<60> for 1 minute).

2️⃣ Heterogeneous Lookup in unordered_map / map

Heterogeneous lookup allows us to search a map or unordered_map with keys of different, but compatible types, without creating a temporary key object. This requires the transparent comparator (std::less<> for map or std::hash<> for unordered_map).

Example: Using Heterogeneous Lookup in unordered_map

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    // unordered_map with string keys
    unordered_map<string, int> umap = {
        {"apple", 5},
        {"banana", 3},
        {"orange", 7}
    };

    // Heterogeneous lookup: using a const char* instead of string
    auto it = umap.find("banana"); // const char* key, no need to construct std::string

    if (it != umap.end()) {
        cout << "Found banana: " << it->second << endl;
    } else {
        cout << "Banana not found" << endl;
    }

    return 0;
}


Sample Output:

Found banana: 3


Example: Using Heterogeneous Lookup in map with Transparent Comparator

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    // map with string keys, transparent comparator for heterogeneous lookup
    map<string, int, std::less<>> mymap = {
        {"cat", 1},
        {"dog", 2},
        {"bird", 3}
    };

    // Searching using const char* instead of string
    auto it = mymap.find("dog");

    if (it != mymap.end()) {
        cout << "Found dog: " << it->second << endl;
    } else {
        cout << "Dog not found" << endl;
    }

    return 0;
}


Sample Output:

Found dog: 2


✅ Notes:

std::less<> allows heterogeneous lookup without constructing a std::string.

For unordered_map, C++14 onward allows transparent hash and equality comparison via std::hash<> and std::equal_to<>.

/* ----------------------------------------------------------- */

⭐ C++17 ADDITIONS
✔ Optional / Variant / Any
std::optional
std::variant
std::any
std::in_place_t, std::in_place_type, std::in_place_index


complete each with complete code in c++ with main and suitable example each separate program code

/* ----------------------------------------------------------- */
1️⃣ std::optional

std::optional is a wrapper that may or may not contain a value. It’s useful for representing "optional" values instead of using nullptr or sentinel values.

#include <iostream>
#include <optional>
#include <string>

int main() {
    std::optional<int> opt1;           // empty optional
    std::optional<int> opt2 = 42;      // contains value

    if(opt1) {
        std::cout << "opt1: " << *opt1 << std::endl;
    } else {
        std::cout << "opt1 is empty" << std::endl;
    }

    if(opt2.has_value()) {
        std::cout << "opt2: " << opt2.value() << std::endl;
    }

    // Assign a new value
    opt1 = 100;
    std::cout << "opt1 after assignment: " << *opt1 << std::endl;

    return 0;
}


Output:

opt1 is empty
opt2: 42
opt1 after assignment: 100

2️⃣ std::variant

std::variant is a type-safe union that can hold one value from a set of types.

#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, float, std::string> v;

    v = 10;  // holds int
    std::cout << "v holds int: " << std::get<int>(v) << std::endl;

    v = 3.14f; // holds float
    std::cout << "v holds float: " << std::get<float>(v) << std::endl;

    v = "Hello Variant"; // holds string
    std::cout << "v holds string: " << std::get<std::string>(v) << std::endl;

    // Using std::visit to handle all types
    std::visit([](auto&& arg){
        std::cout << "Visited value: " << arg << std::endl;
    }, v);

    return 0;
}


Output:

v holds int: 10
v holds float: 3.14
v holds string: Hello Variant
Visited value: Hello Variant

3️⃣ std::any

std::any can hold any type of value, type-checked at runtime.

#include <iostream>
#include <any>
#include <string>

int main() {
    std::any a = 10;  // stores int
    std::cout << "a holds int: " << std::any_cast<int>(a) << std::endl;

    a = std::string("Hello Any"); // stores string
    std::cout << "a holds string: " << std::any_cast<std::string>(a) << std::endl;

    // Check type at runtime
    if(a.type() == typeid(int)) {
        std::cout << "a holds int" << std::endl;
    } else if(a.type() == typeid(std::string)) {
        std::cout << "a holds string" << std::endl;
    }

    return 0;
}


Output:

a holds int: 10
a holds string: Hello Any
a holds string

4️⃣ std::in_place_t, std::in_place_type, std::in_place_index

These allow direct construction of objects inside optional or variant, avoiding extra copies.

#include <iostream>
#include <variant>
#include <optional>
#include <string>

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

int main() {
    // std::optional with in_place
    std::optional<Point> optPoint(std::in_place, 10, 20);
    std::cout << "optPoint: (" << optPoint->x << ", " << optPoint->y << ")" << std::endl;

    // std::variant with in_place_type
    std::variant<int, std::string> v(std::in_place_type<std::string>, "Hello InPlace");
    std::cout << "v holds string: " << std::get<std::string>(v) << std::endl;

    // std::variant with in_place_index
    std::variant<int, std::string> v2(std::in_place_index<0>, 12345); // index 0 = int
    std::cout << "v2 holds int: " << std::get<0>(v2) << std::endl;

    return 0;
}


Output:

optPoint: (10, 20)
v holds string: Hello InPlace
v2 holds int: 12345

/* ----------------------------------------------------------- */

✔ String & Filesystem
std::string_view
std::filesystem
std::filesystem::path, exists, copy, etc.


complete each with complete code in c++ with main and suitable example each separate program code

/* ----------------------------------------------------------- */
1️⃣ std::string_view

std::string_view provides a lightweight, non-owning view of a string. It avoids unnecessary copying.

#include <iostream>
#include <string>
#include <string_view>

void print_view(std::string_view sv) {
    std::cout << "String view: " << sv << "\n";
}

int main() {
    std::string str = "Hello, C++17!";
    std::string_view sv = str;  // View over str, no copy

    print_view(sv);

    // Substring without copying
    std::string_view sub = sv.substr(7, 5);
    std::cout << "Substring view: " << sub << "\n";

    return 0;
}


Output:

String view: Hello, C++17!
Substring view: C++17


✅ Efficient for read-only operations without allocating new memory.

2️⃣ std::filesystem basics

C++17 introduced <filesystem> for portable file and directory operations.

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path p = "example.txt";

    // Check if file exists
    if (fs::exists(p)) {
        std::cout << p << " exists.\n";
    } else {
        std::cout << p << " does not exist.\n";
    }

    // Get parent path
    std::cout << "Parent path: " << p.parent_path() << "\n";

    // File name
    std::cout << "File name: " << p.filename() << "\n";

    return 0;
}


Output (if example.txt exists):

example.txt exists.
Parent path: 
File name: example.txt

3️⃣ Copying a file using std::filesystem
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path source = "example.txt";
    fs::path destination = "example_copy.txt";

    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully.\n";
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}


Output (if successful):

File copied successfully.

4️⃣ Listing files in a directory
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path dir = ".";  // Current directory

    if (fs::exists(dir) && fs::is_directory(dir)) {
        std::cout << "Files in " << dir << ":\n";
        for (const auto& entry : fs::directory_iterator(dir)) {
            std::cout << entry.path().filename() << "\n";
        }
    }

    return 0;
}


Output (example):

Files in .:
example.txt
example_copy.txt
main.cpp

/* ----------------------------------------------------------- */

✔ Parallel Algorithms
All <algorithm> functions got execution policy overloads:
std::execution::seq
std::execution::par
std::execution::par_unseq


complete each with complete code in c++ with main and suitable example each separate program code
/* ----------------------------------------------------------- */
1️⃣ Sequential execution (std::execution::seq)

Sequential execution is the normal, single-threaded execution.

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> v = {5, 2, 9, 1, 7};

    // Sort sequentially
    std::sort(std::execution::seq, v.begin(), v.end());

    std::cout << "Sequential sort: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}


Output:

Sequential sort: 1 2 5 7 9


✅ Works exactly like the normal std::sort, single-threaded.

2️⃣ Parallel execution (std::execution::par)

Parallel execution runs the algorithm on multiple threads.

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> v = {10, 7, 3, 1, 8, 2};

    // Sort in parallel
    std::sort(std::execution::par, v.begin(), v.end());

    std::cout << "Parallel sort: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}


Output:

Parallel sort: 1 2 3 7 8 10


✅ Potentially faster for large datasets, uses multiple threads.

3️⃣ Parallel + vectorized execution (std::execution::par_unseq)

par_unseq allows parallel threads + vectorization, enabling even more performance optimizations if the algorithm supports it.

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>

int main() {
    std::vector<int> v(1000000);

    // Fill vector with 1, 2, 3, ..., 1000000
    std::iota(v.begin(), v.end(), 1);

    // Shuffle for randomness
    std::random_shuffle(v.begin(), v.end());

    // Sort with parallel + vectorization
    std::sort(std::execution::par_unseq, v.begin(), v.end());

    std::cout << "First 10 elements after par_unseq sort: ";
    for (int i = 0; i < 10; ++i) std::cout << v[i] << " ";
    std::cout << "\n";

    return 0;
}

Output (first 10 elements):
First 10 elements after par_unseq sort: 1 2 3 4 5 6 7 8 9 10

✅ Best for large datasets, allows maximum performance using threads + SIMD.




4️⃣ Parallel std::for_each example
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    // Multiply each element by 2 in parallel
    std::for_each(std::execution::par, v.begin(), v.end(),
                  [](int &n) { n *= 2; });

    std::cout << "After parallel for_each: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}

Output:
After parallel for_each: 2 4 6 8 10





C++17 program that:
Sorts the same large dataset using all three execution policies (seq, par, par_unseq).
Measures the time taken for each.
Prints the first 10 elements to verify correctness.

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <chrono>
#include <random>

int main() {
    const size_t SIZE = 5'000'000;
    std::vector<int> data(SIZE);

    // Fill with 1..SIZE
    std::iota(data.begin(), data.end(), 1);

    // Shuffle the vector
    std::mt19937 rng(123); // fixed seed for reproducibility
    std::shuffle(data.begin(), data.end(), rng);

    auto print_first10 = [](const std::vector<int>& v){
        for(int i = 0; i < 10; ++i) std::cout << v[i] << " ";
        std::cout << "\n";
    };

    // Sequential sort
    std::vector<int> seq_data = data;
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::seq, seq_data.begin(), seq_data.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Sequential sort time: " 
              << std::chrono::duration<double>(end - start).count() << " seconds\n";
    std::cout << "First 10 elements: ";
    print_first10(seq_data);

    // Parallel sort
    std::vector<int> par_data = data;
    start = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::par, par_data.begin(), par_data.end());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel sort time: " 
              << std::chrono::duration<double>(end - start).count() << " seconds\n";
    std::cout << "First 10 elements: ";
    print_first10(par_data);

    // Parallel + vectorized sort
    std::vector<int> par_unseq_data = data;
    start = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::par_unseq, par_unseq_data.begin(), par_unseq_data.end());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel + vectorized sort time: " 
              << std::chrono::duration<double>(end - start).count() << " seconds\n";
    std::cout << "First 10 elements: ";
    print_first10(par_unseq_data);

    return 0;
}

✅ What this does
Creates a large vector of 5 million integers.
Shuffles it for randomness.
Sorts it three times using seq, par, and par_unseq.
Measures execution time for each.
Prints first 10 elements to ensure all sorted correctly.

⚡ Expected Output (times may vary by system)
Sequential sort time: 0.85 seconds
First 10 elements: 1 2 3 4 5 6 7 8 9 10
Parallel sort time: 0.35 seconds
First 10 elements: 1 2 3 4 5 6 7 8 9 10
Parallel + vectorized sort time: 0.30 seconds
First 10 elements: 1 2 3 4 5 6 7 8 9 10


✅ Notice: par and par_unseq are faster on large datasets due to multi-threading and SIMD.

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
1️⃣ std::void_t

std::void_t is a helper type used in template metaprogramming to detect valid types or expressions.

#include <iostream>
#include <type_traits>

template <typename, typename = std::void_t<>>
struct has_type_member : std::false_type {};

template <typename T>
struct has_type_member<T, std::void_t<typename T::type>> : std::true_type {};

struct A { using type = int; };
struct B {};

int main() {
    std::cout << std::boolalpha;
    std::cout << "A has type member: " << has_type_member<A>::value << "\n"; // true
    std::cout << "B has type member: " << has_type_member<B>::value << "\n"; // false
    return 0;
}


Output:

A has type member: true
B has type member: false

2️⃣ std::invoke_result

Determines the return type of a callable with given arguments.

#include <iostream>
#include <type_traits>
#include <functional>

int add(int a, int b) { return a + b; }

int main() {
    using result_type = std::invoke_result<decltype(add), int, int>::type;
    result_type sum = add(3, 5);
    std::cout << "Sum: " << sum << "\n";  // 8
    return 0;
}


Output:

Sum: 8

3️⃣ std::conjunction

Logical AND of type traits.

#include <iostream>
#include <type_traits>

int main() {
    using all_true = std::conjunction<std::true_type, std::true_type, std::false_type>;
    std::cout << std::boolalpha;
    std::cout << "All true: " << all_true::value << "\n"; // false
    return 0;
}


Output:

All true: false

4️⃣ std::disjunction

Logical OR of type traits.

#include <iostream>
#include <type_traits>

int main() {
    using any_true = std::disjunction<std::false_type, std::true_type, std::false_type>;
    std::cout << std::boolalpha;
    std::cout << "Any true: " << any_true::value << "\n"; // true
    return 0;
}


Output:

Any true: true

5️⃣ std::negation

Logical NOT of a type trait.

#include <iostream>
#include <type_traits>

int main() {
    using not_true = std::negation<std::true_type>;
    std::cout << std::boolalpha;
    std::cout << "Negation of true: " << not_true::value << "\n"; // false
    return 0;
}


Output:

Negation of true: false

6️⃣ std::is_aggregate

Checks if a type is an aggregate (can be initialized with {}).

#include <iostream>
#include <type_traits>

struct S { int x; double y; };
class C { int x; public: C(int a) : x(a) {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << "S is aggregate: " << std::is_aggregate<S>::value << "\n"; // true
    std::cout << "C is aggregate: " << std::is_aggregate<C>::value << "\n"; // false
    return 0;
}


Output:

S is aggregate: true
C is aggregate: false

7️⃣ std::is_invocable & std::invoke

Check if a callable can be invoked with given arguments, and actually invoke it.

#include <iostream>
#include <type_traits>
#include <functional>

int multiply(int a, int b) { return a * b; }

int main() {
    std::cout << std::boolalpha;
    std::cout << "multiply is invocable with (int, int): " 
              << std::is_invocable<decltype(multiply), int, int>::value << "\n"; // true

    int result = std::invoke(multiply, 4, 5);
    std::cout << "Result of multiply via invoke: " << result << "\n"; // 20
    return 0;
}


Output:

multiply is invocable with (int, int): true
Result of multiply via invoke: 20

8️⃣ std::is_swappable & std::is_nothrow_swappable

Check if two objects can be swapped (and if swapping is noexcept).

#include <iostream>
#include <type_traits>
#include <utility>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << "int is swappable: " << std::is_swappable<int>::value << "\n"; // true
    std::cout << "A is swappable: " << std::is_swappable<A>::value << "\n";     // true
    std::cout << "int is nothrow swappable: " << std::is_nothrow_swappable<int>::value << "\n"; // true
    return 0;
}


Output:

int is swappable: true
A is swappable: true
int is nothrow swappable: true







#include <iostream>
#include <type_traits>
#include <functional>
#include <utility>

struct A { using type = int; };
struct B {};
struct S { int x; double y; };
class C { int x; public: C(int a) : x(a) {} };

int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

int main() {
    std::cout << std::boolalpha;

    std::cout << "================ std::void_t =================\n";
    // void_t example
    template <typename, typename = std::void_t<>>
    struct has_type_member : std::false_type {};
    template <typename T>
    struct has_type_member<T, std::void_t<typename T::type>> : std::true_type {};

    std::cout << "A has type member: " << has_type_member<A>::value << "\n"; // true
    std::cout << "B has type member: " << has_type_member<B>::value << "\n"; // false

    std::cout << "\n================ std::invoke_result =================\n";
    using result_type = std::invoke_result<decltype(add), int, int>::type;
    result_type sum = add(3, 5);
    std::cout << "Sum of add(3,5): " << sum << "\n"; // 8

    std::cout << "\n================ std::conjunction =================\n";
    using all_true = std::conjunction<std::true_type, std::true_type, std::false_type>;
    std::cout << "All true: " << all_true::value << "\n"; // false

    std::cout << "\n================ std::disjunction =================\n";
    using any_true = std::disjunction<std::false_type, std::true_type, std::false_type>;
    std::cout << "Any true: " << any_true::value << "\n"; // true

    std::cout << "\n================ std::negation =================\n";
    using not_true = std::negation<std::true_type>;
    std::cout << "Negation of true: " << not_true::value << "\n"; // false

    std::cout << "\n================ std::is_aggregate =================\n";
    std::cout << "S is aggregate: " << std::is_aggregate<S>::value << "\n"; // true
    std::cout << "C is aggregate: " << std::is_aggregate<C>::value << "\n"; // false

    std::cout << "\n================ std::is_invocable & std::invoke =================\n";
    std::cout << "multiply is invocable with (int,int): "
              << std::is_invocable<decltype(multiply), int, int>::value << "\n"; // true
    int result = std::invoke(multiply, 4, 5);
    std::cout << "Result of multiply via invoke: " << result << "\n"; // 20

    std::cout << "\n================ std::is_swappable & std::is_nothrow_swappable =================\n";
    std::cout << "int is swappable: " << std::is_swappable<int>::value << "\n"; // true
    std::cout << "S is swappable: " << std::is_swappable<S>::value << "\n";     // true
    std::cout << "int is nothrow swappable: " << std::is_nothrow_swappable<int>::value << "\n"; // true

    return 0;
}

/* 
✅ Explanation:
Each section has a header line like ================ std::void_t ================= to clearly separate the examples.
All traits are demonstrated with simple but meaningful examples.
You can compile with g++ -std=c++17 filename.cpp -o test and run ./test.
*/
/* ----------------------------------------------------------- */

✔ Filesystem Support
<filesystem> fully standardized.

complete each with complete code in c++ with main and suitable example each separate program code
/* ----------------------------------------------------------- */
1️⃣ Path Manipulation (std::filesystem::path)
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path p1 = "/home/user/docs";
    fs::path p2 = "file.txt";

    fs::path fullPath = p1 / p2;  // concatenate paths

    std::cout << "Base path: " << p1 << "\n";
    std::cout << "File path: " << p2 << "\n";
    std::cout << "Full path: " << fullPath << "\n";

    std::cout << "Parent path: " << fullPath.parent_path() << "\n";
    std::cout << "Filename: " << fullPath.filename() << "\n";
    std::cout << "Extension: " << fullPath.extension() << "\n";

    return 0;
}

/*
Sample Output:
Base path: /home/user/docs
File path: file.txt
Full path: /home/user/docs/file.txt
Parent path: /home/user/docs
Filename: file.txt
Extension: .txt
*/

2️⃣ Check File or Directory Existence
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path file = "example.txt";
    fs::path dir = "my_folder";

    if (fs::exists(file))
        std::cout << file << " exists.\n";
    else
        std::cout << file << " does not exist.\n";

    if (fs::exists(dir))
        std::cout << dir << " exists.\n";
    else
        std::cout << dir << " does not exist.\n";

    return 0;
}

/*
Sample Output (depends on your filesystem):
example.txt does not exist.
my_folder does not exist.
*/

3️⃣ Create Directory
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path dir = "new_folder";

    if (!fs::exists(dir)) {
        fs::create_directory(dir);
        std::cout << "Directory created: " << dir << "\n";
    } else {
        std::cout << "Directory already exists: " << dir << "\n";
    }

    return 0;
}

/*
Sample Output:
Directory created: new_folder
*/

4️⃣ Copying, Moving, and Removing Files
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path src = "source.txt";
    fs::path dest = "destination.txt";

    // Create a dummy source file
    std::ofstream(src) << "Hello, filesystem!";

    // Copy file
    fs::copy(src, dest, fs::copy_options::overwrite_existing);
    std::cout << "File copied to " << dest << "\n";

    // Rename (move) file
    fs::rename(dest, "renamed.txt");
    std::cout << "File renamed to renamed.txt\n";

    // Remove files
    fs::remove(src);
    fs::remove("renamed.txt");
    std::cout << "Files removed\n";

    return 0;
}

/*
Sample Output:
File copied to destination.txt
File renamed to renamed.txt
Files removed
*/

5️⃣ Iterating Directory Contents
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path dir = "."; // current directory

    std::cout << "Listing files in directory: " << dir << "\n";
    for (const auto& entry : fs::directory_iterator(dir)) {
        std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") 
                  << entry.path().filename() << "\n";
    }

    return 0;
}

/*
Sample Output:
Listing files in directory: .
[FILE] main.cpp
[DIR] new_folder
[FILE] example.txt
*/

/* ----------------------------------------------------------- */

✔ Concurrency
std::shared_mutex
std::scoped_lock
std::hardware_destructive_interference_size
std::hardware_constructive_interference_size

complete each with complete code in c++ with main and suitable example each separate program code
/* ----------------------------------------------------------- */
1️⃣ std::shared_mutex

A std::shared_mutex allows multiple threads to read (shared lock) simultaneously but only one thread to write (exclusive lock).

#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    std::shared_lock lock(rw_mutex); // shared lock
    std::cout << "Reader " << id << " sees value: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void writer(int id) {
    std::unique_lock lock(rw_mutex); // exclusive lock
    shared_data += 10;
    std::cout << "Writer " << id << " updated value to: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

int main() {
    std::vector<std::thread> threads;

    // Start readers
    for (int i = 1; i <= 3; ++i)
        threads.emplace_back(reader, i);

    // Start writers
    for (int i = 1; i <= 2; ++i)
        threads.emplace_back(writer, i);

    for (auto& t : threads)
        t.join();

    return 0;
}


Output (example, may vary due to threading):

Reader 1 sees value: 0
Reader 2 sees value: 0
Reader 3 sees value: 0
Writer 1 updated value to: 10
Writer 2 updated value to: 20

2️⃣ std::scoped_lock

std::scoped_lock is a RAII wrapper to lock multiple mutexes at once safely.

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void task(int id) {
    std::scoped_lock lock(m1, m2); // locks both m1 and m2 safely
    std::cout << "Thread " << id << " acquired both locks." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();

    return 0;
}


Output:

Thread 1 acquired both locks.
Thread 2 acquired both locks.

3️⃣ std::hardware_destructive_interference_size

This represents the number of bytes that are likely to occupy the same cache line and cause false sharing.

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <new> // for std::hardware_destructive_interference_size

struct alignas(std::hardware_destructive_interference_size) PaddedCounter {
    std::atomic<int> value{0};
};

int main() {
    std::cout << "Hardware destructive interference size: "
              << std::hardware_destructive_interference_size << " bytes\n";

    PaddedCounter counters[4];

    auto increment = [&](int id) {
        for (int i = 0; i < 100000; ++i)
            counters[id].value.fetch_add(1, std::memory_order_relaxed);
    };

    std::thread t1(increment, 0);
    std::thread t2(increment, 1);
    std::thread t3(increment, 2);
    std::thread t4(increment, 3);

    t1.join(); t2.join(); t3.join(); t4.join();

    int total = 0;
    for (auto &c : counters) total += c.value;
    std::cout << "Total count: " << total << std::endl;

    return 0;
}


Output:

Hardware destructive interference size: 64 bytes
Total count: 400000

4️⃣ std::hardware_constructive_interference_size

Represents the number of bytes that can be packed together efficiently into a cache line for constructive cache sharing.

#include <iostream>
#include <new> // for std::hardware_constructive_interference_size

struct alignas(std::hardware_constructive_interference_size) CacheOptimized {
    int data[std::hardware_constructive_interference_size / sizeof(int)]{};
};

int main() {
    std::cout << "Hardware constructive interference size: "
              << std::hardware_constructive_interference_size << " bytes\n";

    CacheOptimized arr[2];
    arr[0].data[0] = 10;
    arr[1].data[0] = 20;

    std::cout << "arr[0].data[0] = " << arr[0].data[0] << "\n";
    std::cout << "arr[1].data[0] = " << arr[1].data[0] << "\n";

    return 0;
}

Output (example):
Hardware constructive interference size: 64 bytes
arr[0].data[0] = 10
arr[1].data[0] = 20


✅ These examples cover:
Shared/exclusive locks with std::shared_mutex
Safe multiple mutex locking with std::scoped_lock
Cache-line alignment hints with std::hardware_destructive_interference_size and std::hardware_constructive_interference_size













An advanced combined example where we:
Use std::shared_mutex for shared/exclusive access.
Use std::scoped_lock to safely lock multiple mutexes.
Use std::hardware_destructive_interference_size to avoid false sharing by padding counters.
This will simulate multiple threads reading and writing counters safely and efficiently.

#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <atomic>
#include <vector>
#include <new> // for interference sizes

// Shared resource protected by shared_mutex
int shared_data = 0;
std::shared_mutex rw_mutex;

// Multiple padded counters to avoid false sharing
struct alignas(std::hardware_destructive_interference_size) PaddedCounter {
    std::atomic<int> value{0};
};

PaddedCounter counters[4];

// Additional mutexes for some critical operations
std::mutex m1, m2;

// Reader function: reads shared_data with shared lock
void reader(int id) {
    std::shared_lock lock(rw_mutex);
    std::cout << "[Reader " << id << "] sees shared_data = " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// Writer function: updates shared_data with exclusive lock
void writer(int id) {
    std::unique_lock lock(rw_mutex);
    shared_data += 10;
    std::cout << "[Writer " << id << "] updated shared_data to " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// Increment padded counters using scoped_lock to protect multiple mutexes
void increment_counter(int id) {
    std::scoped_lock lock(m1, m2); // lock both mutexes safely
    for (int i = 0; i < 100000; ++i)
        counters[id].value.fetch_add(1, std::memory_order_relaxed);
}

int main() {
    std::cout << "Hardware destructive interference size: "
              << std::hardware_destructive_interference_size << " bytes\n\n";

    std::vector<std::thread> threads;

    // Start some readers
    for (int i = 1; i <= 3; ++i)
        threads.emplace_back(reader, i);

    // Start some writers
    for (int i = 1; i <= 2; ++i)
        threads.emplace_back(writer, i);

    // Increment padded counters in multiple threads
    for (int i = 0; i < 4; ++i)
        threads.emplace_back(increment_counter, i);

    // Wait for all threads to finish
    for (auto& t : threads)
        t.join();

    // Compute total count
    int total = 0;
    for (int i = 0; i < 4; ++i)
        total += counters[i].value;

    std::cout << "\nTotal count in padded counters: " << total << std::endl;
    std::cout << "Final shared_data value: " << shared_data << std::endl;

    return 0;
}

✅ What this does:
std::shared_mutex ensures multiple readers can read simultaneously while writers have exclusive access.
std::scoped_lock safely locks m1 and m2 when incrementing counters to prevent deadlocks.
PaddedCounter avoids false sharing by padding atomic counters to cache line size using std::hardware_destructive_interference_size.

Example Output (thread-scheduling may vary):
Hardware destructive interference size: 64 bytes
[Reader 1] sees shared_data = 0
[Reader 2] sees shared_data = 0
[Reader 3] sees shared_data = 0
[Writer 1] updated shared_data to 10
[Writer 2] updated shared_data to 20

Total count in padded counters: 400000
Final shared_data value: 20


/* ----------------------------------------------------------- */

✔ Utility
std::size for arrays
std::as_const
std::byte
std::launder
std::clamp
std::apply (for tuples)

/* ----------------------------------------------------------- */
1️⃣ std::size for arrays
#include <iostream>
#include <iterator> // for std::size

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    std::cout << "Size of array: " << std::size(arr) << std::endl;
    return 0;
}
/*
Output:
Size of array: 5
*/

2️⃣ std::as_const
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Make a const reference so the lambda cannot modify elements
    std::for_each(std::as_const(vec).begin(), std::as_const(vec).end(),
                  [](int x){ std::cout << x << " "; });

    std::cout << std::endl;

    // vec remains unchanged
    vec[0] = 100;
    std::cout << "First element after modification: " << vec[0] << std::endl;
    return 0;
}
/*
Output:
1 2 3 4 5 
First element after modification: 100
*/

3️⃣ std::byte
#include <iostream>
#include <cstddef> // for std::byte

int main() {
    std::byte b1{0x1F}; // hexadecimal 1F
    std::byte b2{0x0F};

    // Bitwise OR
    std::byte b3 = b1 | b2;

    std::cout << "b3 as integer: " << std::to_integer<int>(b3) << std::endl;
    return 0;
}
/*
Output:
b3 as integer: 31
*/

4️⃣ std::launder
#include <iostream>
#include <new> // for placement new

struct MyStruct {
    int x;
};

int main() {
    alignas(MyStruct) char buffer[sizeof(MyStruct)];

    MyStruct* p1 = new(buffer) MyStruct{42}; // placement new
    MyStruct* p2 = std::launder(reinterpret_cast<MyStruct*>(buffer));

    std::cout << "Value using launder: " << p2->x << std::endl;
    return 0;
}
/*
Output:
Value using launder: 42
*/

5️⃣ std::clamp
#include <iostream>
#include <algorithm> // for std::clamp

int main() {
    int value = 15;
    int min_val = 10;
    int max_val = 12;

    int clamped = std::clamp(value, min_val, max_val);
    std::cout << "Clamped value: " << clamped << std::endl;

    return 0;
}
/*
Output:
Clamped value: 12
*/

6️⃣ std::apply (for tuples)
#include <iostream>
#include <tuple>
#include <numeric> // for std::accumulate
#include <array>

int main() {
    auto tpl = std::make_tuple(1, 2, 3);

    // Sum all tuple elements using std::apply
    int sum = std::apply([](auto... args){ return (args + ...); }, tpl);

    std::cout << "Sum of tuple elements: " << sum << std::endl;
    return 0;
}
/*
Output:
Sum of tuple elements: 6
*/









#include <iostream>
#include <iterator>   // std::size
#include <vector>
#include <algorithm>  // std::for_each, std::clamp
#include <cstddef>    // std::byte
#include <new>        // std::launder, placement new
#include <tuple>      // std::tuple, std::apply

struct MyStruct {
    int x;
};

int main() {
    std::cout << "=== std::size ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50};
    std::cout << "Size of array: " << std::size(arr) << "\n\n";

    std::cout << "=== std::as_const ===" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::for_each(std::as_const(vec).begin(), std::as_const(vec).end(),
                  [](int x){ std::cout << x << " "; });
    std::cout << std::endl;
    vec[0] = 100; // original vector can still be modified
    std::cout << "First element after modification: " << vec[0] << "\n\n";

    std::cout << "=== std::byte ===" << std::endl;
    std::byte b1{0x1F};
    std::byte b2{0x0F};
    std::byte b3 = b1 | b2;
    std::cout << "b3 as integer: " << std::to_integer<int>(b3) << "\n\n";

    std::cout << "=== std::launder ===" << std::endl;
    alignas(MyStruct) char buffer[sizeof(MyStruct)];
    MyStruct* p1 = new(buffer) MyStruct{42}; // placement new
    MyStruct* p2 = std::launder(reinterpret_cast<MyStruct*>(buffer));
    std::cout << "Value using launder: " << p2->x << "\n\n";

    std::cout << "=== std::clamp ===" << std::endl;
    int value = 15, min_val = 10, max_val = 12;
    int clamped = std::clamp(value, min_val, max_val);
    std::cout << "Clamped value: " << clamped << "\n\n";

    std::cout << "=== std::apply ===" << std::endl;
    auto tpl = std::make_tuple(1, 2, 3);
    int sum = std::apply([](auto... args){ return (args + ...); }, tpl);
    std::cout << "Sum of tuple elements: " << sum << std::endl;

    return 0;
}
/* 
Output:
=== std::size ===
Size of array: 5

=== std::as_const ===
1 2 3 4 5 
First element after modification: 100

=== std::byte ===
b3 as integer: 31

=== std::launder ===
Value using launder: 42

=== std::clamp ===
Clamped value: 12

=== std::apply ===
Sum of tuple elements: 6

*/
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
1️⃣ std::same_as

Checks if two types are the same.

#include <concepts>
#include <iostream>

template<typename T, typename U>
requires std::same_as<T, U>
void checkSame(T a, U b) {
    std::cout << "Types are the same!" << std::endl;
}

int main() {
    int x = 10;
    int y = 20;
    // Valid
    checkSame(x, y);

    // std::string s = "Hi";
    // checkSame(x, s); // Error: types are not the same
    return 0;
}


Output:

Types are the same!

2️⃣ std::integral

Checks if a type is an integral type (int, long, char, etc.)

#include <concepts>
#include <iostream>

template<std::integral T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int x = 5, y = 10;
    std::cout << "Sum: " << add(x, y) << std::endl;

    // double d1 = 1.2, d2 = 2.3;
    // add(d1, d2); // Error: double is not integral
    return 0;
}


Output:

Sum: 15

3️⃣ std::floating_point

Checks if a type is a floating-point type (float, double, long double)

#include <concepts>
#include <iostream>

template<std::floating_point T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    double x = 3.5, y = 2.0;
    std::cout << "Product: " << multiply(x, y) << std::endl;

    // int a = 5, b = 10;
    // multiply(a, b); // Error: int is not floating-point
    return 0;
}


Output:

Product: 7

4️⃣ std::invocable

Checks if a callable object can be invoked with given arguments

#include <concepts>
#include <iostream>

template<typename F, typename... Args>
requires std::invocable<F, Args...>
void callFunction(F f, Args... args) {
    std::cout << "Result: " << f(args...) << std::endl;
}

int add(int a, int b) { return a + b; }

int main() {
    callFunction(add, 3, 4); // Works
    return 0;
}


Output:

Result: 7

5️⃣ std::predicate

Checks if a callable returns something convertible to bool.

#include <concepts>
#include <iostream>

template<typename F, typename T>
requires std::predicate<F, T>
bool check(F f, T value) {
    return f(value);
}

bool isPositive(int x) { return x > 0; }

int main() {
    int n = 5;
    std::cout << std::boolalpha << check(isPositive, n) << std::endl; // true
    return 0;
}


Output:

true

6️⃣ std::regular

Checks if a type is regular: default constructible, copyable, movable, equality comparable

#include <concepts>
#include <iostream>

struct Point {
    int x = 0, y = 0;
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

template<std::regular T>
void printEqual(const T& a, const T& b) {
    std::cout << std::boolalpha << (a == b) << std::endl;
}

int main() {
    Point p1{1, 2}, p2{1, 2};
    printEqual(p1, p2); // true
    return 0;
}


Output:

true

7️⃣ std::semiregular

Checks if a type is default constructible, copyable, movable, but not necessarily equality comparable

#include <concepts>
#include <iostream>

struct Widget {
    int id = 0;
};

template<std::semiregular T>
void printID(T t) {
    std::cout << "ID: " << t.id << std::endl;
}

int main() {
    Widget w{42};
    printID(w); // Works
    return 0;
}


Output:

ID: 42

8️⃣ std::totally_ordered

Checks if a type supports all comparison operators (<, <=, >, >=, ==, !=)

#include <concepts>
#include <iostream>

struct Number {
    int value;
    bool operator==(const Number& other) const { return value == other.value; }
    bool operator<(const Number& other) const { return value < other.value; }
};

template<std::totally_ordered T>
void compare(T a, T b) {
    std::cout << std::boolalpha;
    std::cout << "a < b: " << (a < b) << "\n";
    std::cout << "a <= b: " << (a <= b) << "\n";
    std::cout << "a == b: " << (a == b) << "\n";
}

int main() {
    Number n1{5}, n2{10};
    compare(n1, n2);
    return 0;
}


Output:

a < b: true
a <= b: true
a == b: false















#include <iostream>
#include <concepts>
#include <string>
#include <functional>

// ------------------------------------------------------------
// 1. std::same_as
// ------------------------------------------------------------
template<typename T, typename U>
requires std::same_as<T, U>
void demo_same_as(T a, U b) {
    std::cout << "[same_as] Types are same: " << a << ", " << b << "\n";
}

// ------------------------------------------------------------
// 2. std::integral
// ------------------------------------------------------------
template<std::integral T>
T demo_integral(T a, T b) {
    return a + b;
}

// ------------------------------------------------------------
// 3. std::floating_point
// ------------------------------------------------------------
template<std::floating_point T>
T demo_floating_point(T a, T b) {
    return a * b;
}

// ------------------------------------------------------------
// 4. std::invocable
// ------------------------------------------------------------
template<typename F, typename... Args>
requires std::invocable<F, Args...>
void demo_invocable(F f, Args... args) {
    std::cout << "[invocable] Result = " << f(args...) << "\n";
}

// ------------------------------------------------------------
// 5. std::predicate
// ------------------------------------------------------------
template<typename P, typename T>
requires std::predicate<P, T>
bool demo_predicate(P pred, T value) {
    return pred(value);
}

// ------------------------------------------------------------
// 6. std::regular
// ------------------------------------------------------------
struct Point {
    int x = 0, y = 0;

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

template<std::regular T>
void demo_regular(const T& a, const T& b) {
    std::cout << "[regular] Are equal? " << std::boolalpha << (a == b) << "\n";
}

// ------------------------------------------------------------
// 7. std::semiregular
// ------------------------------------------------------------
struct Widget {
    int id = 0;
};

template<std::semiregular T>
void demo_semiregular(T t) {
    std::cout << "[semiregular] ID = " << t.id << "\n";
}

// ------------------------------------------------------------
// 8. std::totally_ordered
// ------------------------------------------------------------
struct Number {
    int value;

    bool operator==(const Number& other) const { return value == other.value; }
    bool operator<(const Number& other) const { return value < other.value; }
};

template<std::totally_ordered T>
void demo_totally_ordered(T a, T b) {
    std::cout << "[totally_ordered] a < b  = " << (a < b) << "\n";
    std::cout << "[totally_ordered] a <= b = " << (a <= b) << "\n";
    std::cout << "[totally_ordered] a == b = " << (a == b) << "\n";
}

// ------------------------------------------------------------
// MAIN PROGRAM
// ------------------------------------------------------------
int main() {

    std::cout << "\n=== C++20 Concepts Demonstration ===\n\n";

    // same_as
    demo_same_as(10, 20);

    // integral
    std::cout << "[integral] Sum = " << demo_integral(5, 10) << "\n";

    // floating_point
    std::cout << "[floating_point] Product = " 
              << demo_floating_point(2.5, 4.0) << "\n";

    // invocable
    auto add = [](int a, int b){ return a + b; };
    demo_invocable(add, 3, 7);

    // predicate
    auto isEven = [](int x){ return x % 2 == 0; };
    std::cout << "[predicate] isEven(6) = " 
              << demo_predicate(isEven, 6) << "\n";

    // regular
    Point p1{2, 3}, p2{2, 3};
    demo_regular(p1, p2);

    // semiregular
    Widget w{42};
    demo_semiregular(w);

    // totally_ordered
    Number n1{5}, n2{10};
    demo_totally_ordered(n1, n2);

    return 0;
}
/* 
Output:
=== C++20 Concepts Demonstration ===

[same_as] Types are same: 10, 20
[integral] Sum = 15
[floating_point] Product = 10
[invocable] Result = 10
[predicate] isEven(6) = 1
[regular] Are equal? true
[semiregular] ID = 42
[totally_ordered] a < b  = 1
[totally_ordered] a <= b = 1
[totally_ordered] a == b = 0
*/
/* ----------------------------------------------------------- */


✔ Ranges (<ranges>)
std::ranges::begin, end
std::ranges::sort


/* ----------------------------------------------------------- */
✅ 1. Program: std::ranges::begin / std::ranges::end
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    // Using std::ranges::begin and end
    auto it_begin = std::ranges::begin(v);
    auto it_end   = std::ranges::end(v);

    std::cout << "First element: " << *it_begin << "\n";

    std::cout << "All elements: ";
    for (auto it = it_begin; it != it_end; ++it)
        std::cout << *it << " ";

    std::cout << "\n";

    return 0;
}

/*
Output:
First element: 10
All elements: 10 20 30 40 50
*/

✅ 2. Program: std::ranges::sort
#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {5, 2, 9, 1, 7};

    std::cout << "Before sorting: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    // Sorting using ranges::sort
    std::ranges::sort(v);

    std::cout << "After sorting: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

/*
Output:
Before sorting: 5 2 9 1 7
After sorting: 1 2 5 7 9
*/
/* ----------------------------------------------------------- */

Views:
std::views::filter
std::views::transform
std::views::reverse
std::views::iota
std::views::take
std::views::drop

/* ----------------------------------------------------------- */
✅ 1. std::views::filter — keep only even numbers
#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> v = {1,2,3,4,5,6};

    auto even_view = v | std::views::filter([](int x){ return x % 2 == 0; });

    std::cout << "Even numbers: ";
    for (int x : even_view)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}


Output

Even numbers: 2 4 6

✅ 2. std::views::transform — square every number
#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> v = {1,2,3,4,5};

    auto sq_view = v | std::views::transform([](int x){ return x*x; });

    std::cout << "Squares: ";
    for (int x : sq_view)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}


Output

Squares: 1 4 9 16 25

✅ 3. std::views::reverse — reverse elements
#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> v = {10, 20, 30, 40};

    auto rev = v | std::views::reverse;

    std::cout << "Reversed: ";
    for (int x : rev)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}


Output

Reversed: 40 30 20 10

✅ 4. std::views::iota — generate a range of numbers
#include <iostream>
#include <ranges>

int main() {
    auto numbers = std::views::iota(1, 10); // from 1 to 9

    std::cout << "Iota numbers: ";
    for (int x : numbers)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}


Output

Iota numbers: 1 2 3 4 5 6 7 8 9

✅ 5. std::views::take — take first N items
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v = {5, 10, 15, 20, 25, 30};

    auto first3 = v | std::views::take(3);

    std::cout << "First 3 values: ";
    for (int x : first3)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}


Output

First 3 values: 5 10 15

✅ 6. std::views::drop — skip first N items
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v = {5, 10, 15, 20, 25, 30};

    auto after2 = v | std::views::drop(2);

    std::cout << "After dropping first 2: ";
    for (int x : after2)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

Output
After dropping first 2: 15 20 25 30





#include <iostream>
#include <ranges>

int main() {
    // Generate numbers from 1 to 50
    auto pipeline =
        std::views::iota(1, 51)                                      // 1..50
        | std::views::filter([](int x){ return x % 3 == 0; })        // multiples of 3
        | std::views::transform([](int x){ return x * x; })          // square them
        | std::views::drop(2)                                        // drop first 2 squares
        | std::views::take(5)                                        // take next 5
        | std::views::reverse;                                       // reverse final list

    std::cout << "Pipeline output: ";
    for (int x : pipeline)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Pipeline output: 405 324 225 144 81
*/









1) Pipeline on Strings (filter → transform → take → reverse)
Task
Given a list of words:
→ keep only those with length > 3
→ convert to uppercase
→ take first 3
→ reverse the final order

✅ Code
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <cctype>
int main() {
    std::vector<std::string> words = {
        "cat", "tiger", "lion", "elephant", "fox", "wolf", "rabbit"
    };

    auto pipeline =
        words
        | std::views::filter([](const std::string& s){ return s.size() > 3; })
        | std::views::transform([](std::string s){
                std::transform(s.begin(), s.end(), s.begin(), ::toupper);
                return s;
          })
        | std::views::take(3)
        | std::views::reverse;

    std::cout << "Result: ";
    for (auto& w : pipeline)
        std::cout << w << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Result: ELEPHANT LION TIGER
*/


⭐ 2) Pipeline on Structs (filter → transform)
Task
We have Employee objects;
→ filter salary > 40000
→ transform to only employee names.

✅ Code
#include <iostream>
#include <vector>
#include <ranges>

struct Employee {
    std::string name;
    int salary;
};
int main() {
    std::vector<Employee> people = {
        {"Amit", 35000},
        {"Neha", 50000},
        {"Raj", 60000},
        {"Pooja", 30000},
        {"Rohan", 75000}
    };

    auto names =
        people
        | std::views::filter([](const Employee& e){ return e.salary > 40000; })
        | std::views::transform([](const Employee& e){ return e.name; });

    std::cout << "Employees with salary > 40000: ";
    for (auto& name : names)
        std::cout << name << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Employees with salary > 40000: Neha Raj Rohan
*/


⭐ 3) Advanced Numerical Pipeline (iota → filter → transform → drop → take)
Task
Generate 1..100,
→ keep even numbers
→ cube them
→ skip first 3
→ take next 5.

✅ Code
#include <iostream>
#include <ranges>
int main() {
    auto pipeline =
        std::views::iota(1, 101)
        | std::views::filter([](int x){ return x % 2 == 0; })      // even numbers
        | std::views::transform([](int x){ return x * x * x; })     // cube
        | std::views::drop(3)                                       // skip 3 cubes
        | std::views::take(5);                                      // take next 5

    std::cout << "Pipeline output: ";
    for (int x : pipeline)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Pipeline output: 512 1000 1728 2744 4096
*/


/* ----------------------------------------------------------- */

✔ Coroutines (<coroutine>)
std::coroutine_handle
std::suspend_always
std::suspend_never

/* ----------------------------------------------------------- */
✅ 1. Example: std::coroutine_handle
Shows manual resuming and destroying a coroutine using its handle.

✔ Program 1
#include <iostream>
#include <coroutine>

struct Task {
    struct promise_type {
        Task get_return_object() {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    std::coroutine_handle<promise_type> handle;

    Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { if (handle) handle.destroy(); }
};

Task example() {
    std::cout << "Inside coroutine: step 1\n";
    co_await std::suspend_always{};
    std::cout << "Inside coroutine: step 2\n";
}

int main() {
    Task t = example();

    std::cout << "Resuming coroutine (1)...\n";
    t.handle.resume();

    std::cout << "Resuming coroutine (2)...\n";
    t.handle.resume();

    return 0;
}
/* 
✔ Output
Inside coroutine: step 1
Resuming coroutine (1)...
Inside coroutine: step 2
Resuming coroutine (2)...
*/



✅ 2. Example: std::suspend_always
Coroutine always suspends at each co_await.

✔ Program 2
#include <iostream>
#include <coroutine>

struct SuspendAlways {
    struct promise_type {
        SuspendAlways get_return_object() {
            return SuspendAlways{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> handle;

    SuspendAlways(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~SuspendAlways() { if (handle) handle.destroy(); }
};

SuspendAlways test_suspend() {
    std::cout << "Point A\n";
    co_await std::suspend_always{};
    std::cout << "Point B\n";
    co_await std::suspend_always{};
    std::cout << "Point C\n";
}

int main() {
    auto t = test_suspend();

    std::cout << "Resume 1\n";
    t.handle.resume();

    std::cout << "Resume 2\n";
    t.handle.resume();

    std::cout << "Resume 3\n";
    t.handle.resume();
}
/* 
✔ Output
Point A
Resume 1
Point B
Resume 2
Point C
Resume 3
*/


✅ 3. Example: std::suspend_never
Coroutine never suspends → runs from start to end immediately.

✔ Program 3
#include <iostream>
#include <coroutine>

struct NoSuspend {
    struct promise_type {
        NoSuspend get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

NoSuspend run_now() {
    std::cout << "Coroutine running immediately!\n";
    co_return;
}

int main() {
    run_now();   // runs immediately, no suspension
    std::cout << "Back in main.\n";
    return 0;
}
/* 
✔ Output
Coroutine running immediately!
Back in main.
*/
/* ----------------------------------------------------------- */

✔ Calendar & Time
std::chrono::year, month, day
std::chrono::zoned_time
std::chrono::local_time

/* ----------------------------------------------------------- */
✅ 1. std::chrono::year, month, day Example
✔ Uses:
std::chrono::year, month, day, year_month_day

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main() {
    year y{2025};
    month m{12};
    day d{6};

    year_month_day ymd{y, m, d};

    cout << "Year  : " << int(y) << "\n";
    cout << "Month : " << unsigned(m) << "\n";
    cout << "Day   : " << unsigned(d) << "\n";
    cout << "Combined date (YYYY-MM-DD): " << ymd << "\n";

    // Check if leap year
    cout << "Is leap year? " << (y.is_leap() ? "Yes" : "No") << "\n";

    return 0;
}
/* 
Sample Output
Year  : 2025
Month : 12
Day   : 6
Combined date (YYYY-MM-DD): 2025-12-06
Is leap year? No
*/


✅ 2. std::chrono::zoned_time Example
✔ Features

Gets current system time

Converts to specific time zone

Uses std::chrono::zoned_time

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    // Time zone: Asia/Kolkata (any IANA zone works)
    zoned_time zt{"Asia/Kolkata", system_clock::now()};

    cout << "Current time in Asia/Kolkata: " << zt << "\n";

    return 0;
}
/* 
Sample Output
Current time in Asia/Kolkata: 2025-12-06 15:52:44.123456 IST

(Exact time will differ.)
*/


✅ 3. std::chrono::local_time Example
✔ Features

Create local_time from year-month-day + time

Convert to sys_time

Show combined date-time

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    year y{2025};
    month m{12};
    day d{6};
    
    hours h{15};
    minutes min{30};
    seconds sec{45};

    local_time<seconds> lt = local_days{y/m/d} + h + min + sec;

    cout << "Local date-time: " << lt << "\n";

    // Convert local time to system_clock time (assuming timezone offset +05:30)
    // Example: IST offset
    sys_time<seconds> st = lt - hours{5} - minutes{30};

    cout << "Equivalent system time (UTC): " << st << "\n";

    return 0;
}
/* 
Sample Output
Local date-time: 2025-12-06 15:30:45
Equivalent system time (UTC): 2025-12-06 10:00:45
*/
/* ----------------------------------------------------------- */

✔ Atomic Improvements
std::atomic_ref
std::atomic_wait
std::atomic_notify_one, notify_all

/* ----------------------------------------------------------- */
✅ 1. std::atomic_ref Example
✔ Allows atomic operations on existing non-atomic objects

(Super useful for shared counters)

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

int main() {
    int value = 0;                   // normal int
    atomic_ref<int> atomicValue(value); // atomic reference

    vector<thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < 1000; ++j)
                atomicValue.fetch_add(1);
        });
    }

    for (auto &t : threads) t.join();

    cout << "Final value: " << value << "\n";

    return 0;
}
/* 
Sample Output
Final value: 5000
*/



✅ 2. std::atomic_wait Example
✔ Thread waits until atomic value changes
✔ Very lightweight (uses futex-like mechanism)
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    atomic<int> flag{0};

    thread waiter([&]() {
        cout << "Waiting for flag to become 1...\n";

        int expected = 0;
        flag.wait(expected);   // waits until flag != expected

        cout << "Flag changed! New value: " << flag.load() << "\n";
    });

    this_thread::sleep_for(1s);

    cout << "Setting flag = 1\n";
    flag.store(1);
    flag.notify_one();     // wake waiting thread

    waiter.join();
    return 0;
}
/* 
Sample Output
Waiting for flag to become 1...
Setting flag = 1
Flag changed! New value: 1
*/



✅ 3. std::atomic_notify_one and std::atomic_notify_all Example
✔ Multiple threads wait on the same atomic
✔ Notify one vs all
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    atomic<int> flag{0};

    vector<thread> workers;

    for (int i = 0; i < 3; ++i) {
        workers.emplace_back([&, i]() {
            int expected = 0;
            cout << "Worker " << i << " waiting...\n";
            flag.wait(expected);
            cout << "Worker " << i << " woke up! Flag = " << flag.load() << "\n";
        });
    }

    this_thread::sleep_for(1s);

    cout << "Notify ONE worker (flag = 1)\n";
    flag.store(1);
    flag.notify_one();     // wakes only one

    this_thread::sleep_for(1s);

    cout << "Notify ALL workers (flag = 2)\n";
    flag.store(2);
    flag.notify_all();     // wakes remaining threads

    for (auto &t : workers) t.join();
    return 0;
}
/* 
Sample Output
Worker 0 waiting...
Worker 1 waiting...
Worker 2 waiting...
Notify ONE worker (flag = 1)
Worker 0 woke up! Flag = 1
Notify ALL workers (flag = 2)
Worker 1 woke up! Flag = 2
Worker 2 woke up! Flag = 2
*/





✅ 1. std::atomic_flag — Spinlock Example
✔ atomic_flag is the fastest lock primitive
✔ Used to build spinlocks
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

class Spinlock {
    atomic_flag flag = ATOMIC_FLAG_INIT;

  public:
    void lock() {
        while (flag.test_and_set(memory_order_acquire)) {
            // spin
        }
    }

    void unlock() {
        flag.clear(memory_order_release);
    }
};

int main() {
    Spinlock lock;
    int counter = 0;

    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < 1000; ++j) {
                lock.lock();
                ++counter;
                lock.unlock();
            }
        });
    }

    for (auto &t : threads) t.join();

    cout << "Final counter = " << counter << endl;
    return 0;
}
/* 
Output
Final counter = 5000
*/


✅ 2. std::atomic_shared_ptr (C++23)
✔ Thread-safe automatically
✔ Lock-free reference counting
#include <iostream>
#include <memory>
#include <atomic>
#include <thread>

using namespace std;

int main() {
    atomic_shared_ptr<int> ptr;
    ptr.store(make_shared<int>(100));

    thread t1([&]() {
        for (int i = 0; i < 5; ++i) {
            shared_ptr<int> p = ptr.load();
            cout << "T1 sees: " << *p << endl;
        }
    });

    thread t2([&]() {
        this_thread::sleep_for(1s);
        ptr.store(make_shared<int>(200));
        cout << "T2 updated ptr to 200\n";
    });

    t1.join();
    t2.join();

    cout << "Main sees: " << *ptr.load() << endl;
    return 0;
}
/* 
Sample Output
T1 sees: 100
T1 sees: 100
T1 sees: 100
T1 sees: 100
T1 sees: 100
T2 updated ptr to 200
Main sees: 200
*/


✅ 3. Lock-Free Stack (Treiber Stack)
✔ Uses std::atomic
✔ No mutexes
✔ Classic lock-free structure
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* next;
};

class LockFreeStack {
    atomic<Node*> head{nullptr};

  public:
    void push(int val) {
        Node* newNode = new Node{val, nullptr};
        do {
            newNode->next = head.load(memory_order_relaxed);
        } while (!head.compare_exchange_weak(newNode->next, newNode));
    }

    bool pop(int& result) {
        Node* oldHead = head.load();
        while (oldHead && 
              !head.compare_exchange_weak(oldHead, oldHead->next))
            ;
        if (!oldHead) return false;

        result = oldHead->value;
        delete oldHead;
        return true;
    }
};

int main() {
    LockFreeStack stack;

    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < 100; ++j)
                stack.push(j);
        });
    }

    for (auto& t : threads) t.join();

    int x;
    int count = 0;
    while (stack.pop(x)) count++;

    cout << "Total popped: " << count << endl;
    return 0;
}
/* 
Sample Output
Total popped: 500
*/


✅ 4. Hazard-Pointer Style Safe Reclamation (Minimal Demo)

NOTE: Full hazard pointer implementation is long.
Below is a tiny conceptual example showing:
Threads protect a pointer before reading
Prevents deleting a node still in use
Simulated reclamation list

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

atomic<int*> global_ptr{nullptr};
atomic<int*> hazard_ptr{nullptr};   // each thread would have its own

void safe_delete(int* p) {
    // If no one is using it, delete
    if (hazard_ptr.load() != p) {
        delete p;
        cout << "Deleted safely\n";
    } else {
        cout << "Cannot delete: hazard pointer in use\n";
    }
}

int main() {
    global_ptr = new int(100);

    thread reader([&]() {
        int* p = global_ptr.load();
        hazard_ptr.store(p);          // protect

        this_thread::sleep_for(500ms);
        cout << "Reader sees value = " << *p << endl;

        hazard_ptr.store(nullptr);    // release
    });

    this_thread::sleep_for(100ms);

    // Try to delete while reader may still use it
    int* old = global_ptr.exchange(new int(200));
    safe_delete(old);

    reader.join();

    // Now safe to delete latest
    delete global_ptr.load();

    return 0;
}
/* 
Sample Output
Cannot delete: hazard pointer in use
Reader sees value = 100
Deleted safely
*/





/* ----------------------------------------------------------- */

✔ Containers
std::span
std::flat_map (C++23 but widely implemented)

/* ----------------------------------------------------------- */
✅ 1. std::span Example (C++20)
✔ View over arrays/vectors
✔ No copying
✔ Safe slicing
#include <iostream>
#include <span>
#include <vector>

using namespace std;

void printSpan(span<int> s) {
    cout << "Span elements: ";
    for (int x : s) cout << x << " ";
    cout << "\n";
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};

    span<int> s1(arr);         // span over array
    printSpan(s1);

    vector<int> v = {1, 2, 3, 4, 5, 6};
    span<int> s2(v);           // span over vector
    printSpan(s2);

    cout << "Subspan (2 elements starting at index 2): ";
    span<int> sub = s2.subspan(2, 2);
    for (int x : sub) cout << x << " ";
    cout << "\n";

    return 0;
}
/* 
Sample Output
Span elements: 10 20 30 40 50 
Span elements: 1 2 3 4 5 6 
Subspan (2 elements starting at index 2): 3 4 
*/


✅ 2. std::flat_map Example (C++23)
✔ Ordered map implemented as a sorted vector
✔ Very cache-friendly
✔ Faster for small/medium maps
✔ Requires C++23
#include <iostream>
#include <flat_map>

using namespace std;

int main() {
    flat_map<int, string> fm;

    // Insert values
    fm.emplace(3, "Three");
    fm.emplace(1, "One");
    fm.emplace(2, "Two");

    // flat_map keeps keys sorted automatically
    cout << "Contents of flat_map:\n";
    for (auto &p : fm)
        cout << p.first << " => " << p.second << "\n";

    // Access value
    cout << "Value at key 2 = " << fm.at(2) << "\n";

    // Contains check
    if (fm.contains(3))
        cout << "Key 3 exists\n";

    // Erase
    fm.erase(1);

    cout << "After erase(1):\n";
    for (auto &p : fm)
        cout << p.first << " => " << p.second << "\n";

    return 0;
}
/* 
Sample Output
Contents of flat_map:
1 => One
2 => Two
3 => Three
Value at key 2 = Two
Key 3 exists
After erase(1):
2 => Two
3 => Three
*/




✅ 1. std::flat_set Example (C++23)
✔ Sorted vector-based set
✔ No duplicates
✔ Very cache-friendly
✔ Faster than std::set for most workloads
#include <iostream>
#include <flat_set>

using namespace std;

int main() {
    flat_set<int> fs;

    fs.insert(50);
    fs.insert(10);
    fs.insert(30);
    fs.insert(20);
    fs.insert(30);   // duplicate ignored

    cout << "Elements of flat_set (sorted automatically):\n";
    for (int x : fs)
        cout << x << " ";
    cout << "\n";

    // contains()
    cout << "Contains 20? " 
         << (fs.contains(20) ? "Yes" : "No") << "\n";

    // Erase element
    fs.erase(10);

    cout << "After erase(10): ";
    for (int x : fs) cout << x << " ";
    cout << "\n";

    return 0;
}

Sample Output
Elements of flat_set (sorted automatically):
10 20 30 50 
Contains 20? Yes
After erase(10): 20 30 50 

✅ 2. std::mdspan Example (C++23)
✔ Multi-dimensional non-owning view
✔ Zero overhead
✔ Works with raw arrays, vectors, new[]
✔ Replaces std::span for multi-dimensional data
Example: 2D Matrix View with mdspan
#include <iostream>
#include <mdspan>
#include <array>

using namespace std;
using namespace std::mdspan;

int main() {
    // 2×3 matrix stored in row-major order
    array<int, 6> data = {1, 2, 3,
                          4, 5, 6};

    // create mdspan for 2 rows, 3 cols
    mdspan<int, extents<size_t, 2, 3>> mat(data.data());

    cout << "Matrix:\n";
    for (size_t i = 0; i < mat.extent(0); ++i) {
        for (size_t j = 0; j < mat.extent(1); ++j)
            cout << mat(i, j) << " ";
        cout << "\n";
    }

    cout << "Element at (1,2) = " << mat(1, 2) << "\n";

    // Modify matrix via mdspan
    mat(0, 1) = 99;

    cout << "\nModified Matrix:\n";
    for (size_t i = 0; i < mat.extent(0); ++i) {
        for (size_t j = 0; j < mat.extent(1); ++j)
            cout << mat(i, j) << " ";
        cout << "\n";
    }

    return 0;
}

Sample Output
Matrix:
1 2 3
4 5 6
Element at (1,2) = 6

Modified Matrix:
1 99 3
4 5 6







✅ 1. std::mdspan — Dynamic Extents Example (C++23)
✔ Dimensions known only at runtime
✔ Still zero overhead
#include <iostream>
#include <mdspan>
#include <vector>

using namespace std;
using namespace std::mdspan;

int main() {
    size_t rows = 3, cols = 4;
    vector<int> data(rows * cols);

    // Fill with sequence numbers
    for (int i = 0; i < data.size(); i++)
        data[i] = i + 1;

    mdspan<int, dynamic_extents<size_t, 2>> mat(data.data(), rows, cols);

    cout << "Dynamic mdspan matrix:\n";
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            cout << mat(i, j) << " ";
        cout << "\n";
    }

    return 0;
}

Sample Output
Dynamic mdspan matrix:
1 2 3 4
5 6 7 8
9 10 11 12

✅ 2. std::pmr::vector — Using a Memory Resource (C++17–C++23)
✔ Faster vector for many allocations
✔ Uses memory pools
✔ Perfect for game engines / real-time systems
#include <iostream>
#include <vector>
#include <memory_resource>

using namespace std;

int main() {
    // Local buffer for memory pool
    std::byte buffer[1024];

    // Monotonic resource using the buffer
    pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};

    pmr::vector<int> vec{&pool};   // allocate from pool

    for (int i = 1; i <= 10; ++i)
        vec.push_back(i * 10);

    cout << "pmr::vector values: ";
    for (int x : vec) cout << x << " ";
    cout << "\n";

    return 0;
}

Sample Output
pmr::vector values: 10 20 30 40 50 60 70 80 90 100

✅ 3. std::pmr::unordered_map — Memory Resource Map
✔ Fast, pooled hashing
✔ Fully uses PMR allocator
#include <iostream>
#include <unordered_map>
#include <memory_resource>

using namespace std;

int main() {
    std::byte buffer[2048];
    pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};

    pmr::unordered_map<string, int> umap{&pool};

    umap["apple"] = 10;
    umap["banana"] = 20;
    umap["orange"] = 30;

    for (auto &p : umap)
        cout << p.first << " => " << p.second << "\n";

    return 0;
}

Sample Output
banana => 20
apple => 10
orange => 30


(Iteration order is unspecified.)

✅ 4. std::deque — Fast Push Front/Back
✔ Double-ended queue
✔ Great for large front insertions
✔ Used internally in thread pools, BFS, etc.
#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> dq;

    dq.push_back(10);
    dq.push_front(5);
    dq.push_back(20);
    dq.push_front(1);

    cout << "Deque contents: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    cout << "Front: " << dq.front() << "\n";
    cout << "Back: " << dq.back() << "\n";

    dq.pop_front();
    dq.pop_back();

    cout << "After pops: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    return 0;
}

Sample Output
Deque contents: 1 5 10 20
Front: 1
Back: 20
After pops: 5 10

✅ 5. std::forward_list — Singly Linked List
✔ Very low memory overhead
✔ Best for fast insert_after
✔ Used in hash table buckets
#include <iostream>
#include <forward_list>

using namespace std;

int main() {
    forward_list<int> fl = {10, 20, 30};

    // Insert after first element
    auto it = fl.begin();
    fl.insert_after(it, 15);

    cout << "Forward list contents: ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    // Remove elements
    fl.remove(20);

    cout << "After removing 20: ";
    for (int x : fl) cout << x << " ";
    cout << "\n";

    return 0;
}

Sample Output
Forward list contents: 10 15 20 30
After removing 20: 10 15 30







✅ 1. std::unordered_map — Heterogeneous Lookup (C++20)
✔ Lookup with both std::string and char*
✔ No temporary allocation
✔ Faster than usual find("key")
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct TransparentHash {
    using is_transparent = void;

    size_t operator()(string_view sv) const noexcept {
        return hash<string_view>{}(sv);
    }
    size_t operator()(const string& s) const noexcept {
        return hash<string>{}(s);
    }
    size_t operator()(const char* s) const noexcept {
        return hash<string_view>{}(s);
    }
};

int main() {
    unordered_map<string, int, TransparentHash, equal_to<>> table;

    table["apple"] = 100;
    table["banana"] = 200;

    // lookup using char*
    if (auto it = table.find("apple"); it != table.end())
        cout << "Found apple => " << it->second << "\n";

    // lookup using string_view
    string_view key = "banana";
    if (auto it = table.find(key); it != table.end())
        cout << "Found banana => " << it->second << "\n";

    return 0;
}

Sample Output
Found apple => 100
Found banana => 200

✅ 2. std::priority_queue with Custom Comparator
✔ Min-heap
✔ Works with structs
✔ Great for Dijkstra, A* search, etc.
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int distance;
    int id;
};

// For a MIN-HEAP, return true if a > b
struct MinCompare {
    bool operator()(const Node& a, const Node& b) const {
        return a.distance > b.distance;
    }
};

int main() {
    priority_queue<Node, vector<Node>, MinCompare> pq;

    pq.push({10, 1});
    pq.push({5, 2});
    pq.push({20, 3});

    while (!pq.empty()) {
        auto n = pq.top();
        pq.pop();
        cout << "Popped node id=" << n.id 
             << " dist=" << n.distance << "\n";
    }

    return 0;
}

Sample Output
Popped node id=2 dist=5
Popped node id=1 dist=10
Popped node id=3 dist=20

✅ 3. std::stack and std::queue — Container Adapters
✔ Built on top of existing containers
✔ Default: stack uses deque, queue uses deque
(A) std::stack Example
#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> st;

    st.push(1);
    st.push(2);
    st.push(3);

    while (!st.empty()) {
        cout << "Top = " << st.top() << "\n";
        st.pop();
    }

    return 0;
}

Output
Top = 3
Top = 2
Top = 1

(B) std::queue Example
#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<string> q;

    q.push("Alice");
    q.push("Bob");
    q.push("Charlie");

    while (!q.empty()) {
        cout << "Front = " << q.front() << "\n";
        q.pop();
    }

    return 0;
}

Sample Output
Front = Alice
Front = Bob
Front = Charlie

✅ 4. std::string — Small String Optimization Demonstration
✔ Most implementations store small strings without heap allocation
✔ Makes short strings extremely fast

This program prints whether memory address changes (indicating allocation).

#include <iostream>
#include <string>

using namespace std;

void show(const string& s) {
    cout << "String: \"" << s << "\"  "
         << "Address: " << static_cast<const void*>(s.data()) << "\n";
}

int main() {
    string s1 = "Hi";   // small, SSO
    string s2 = "This is a very long string that exceeds SSO";

    show(s1);
    show(s2);

    return 0;
}

Possible Output (platform-dependent)
String: "Hi"  Address: 0x7ffc9a34f900
String: "This is a very long string that exceeds SSO"  Address: 0x5586ebb46370

(First one often inside stack-allocated buffer; second one heap-allocated.)






✅ 6. std::flat_set (C++23 — widely implemented)

std::flat_set is a sorted vector-based associative container.
It stores keys contiguously → very cache-friendly and faster for small datasets.

⭐ Program: std::flat_set Example (C++23)
#include <iostream>
#include <flat_set>
#include <string>

int main() {
    std::flat_set<int> fs = {5, 1, 7, 3};

    // Elements automatically sorted
    std::cout << "Elements in flat_set: ";
    for (int x : fs) std::cout << x << " ";
    std::cout << "\n";

    // Insert new elements
    fs.insert(2);
    fs.insert(9);

    std::cout << "After inserting 2 and 9: ";
    for (int x : fs) std::cout << x << " ";
    std::cout << "\n";

    // Find element
    if (fs.contains(7))
        std::cout << "7 exists in the set.\n";
    else
        std::cout << "7 NOT found.\n";

    // Erase element
    fs.erase(3);

    std::cout << "After erasing 3: ";
    for (int x : fs) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

✔ Sample Output
Elements in flat_set: 1 3 5 7
After inserting 2 and 9: 1 2 3 5 7 9
7 exists in the set.
After erasing 3: 1 2 5 7 9

/* ----------------------------------------------------------- */

✔ Utility
std::bit_cast
std::remove_cvref
std::endian
std::source_location
std::format (Python-style formatting)


/* ----------------------------------------------------------- */
✅ 1. std::bit_cast Example (C++20)

Safely reinterpret one type as another of the same size.

✔ Program 1 — std::bit_cast
#include <iostream>
#include <bit>
#include <cstdint>

int main() {
    float f = 3.14f;

    // reinterpret float bits as uint32_t
    uint32_t bits = std::bit_cast<uint32_t>(f);

    std::cout << "Float value: " << f << "\n";
    std::cout << "Reinterpreted bits (hex): 0x" << std::hex << bits << "\n";

    // convert back to float
    float restored = std::bit_cast<float>(bits);
    std::cout << std::dec << "Restored float: " << restored << "\n";

    return 0;
}

Output (example)
Float value: 3.14
Reinterpreted bits (hex): 0x4048f5c3
Restored float: 3.14

✅ 2. std::remove_cvref Example (C++20)

Removes const, volatile, and reference qualifiers.

✔ Program 2 — std::remove_cvref
#include <iostream>
#include <type_traits>

template <typename T>
void printType() {
    std::cout << typeid(T).name() << "\n";
}

int main() {
    const int& x = 10;

    using T1 = decltype(x);
    using T2 = std::remove_cvref_t<T1>;

    std::cout << "Original type: ";
    printType<T1>();

    std::cout << "After remove_cvref: ";
    printType<T2>();

    return 0;
}

Output (example)
Original type: int const&
After remove_cvref: int

✅ 3. std::endian Example (C++20)

Detect system endianness.

✔ Program 3 — std::endian
#include <iostream>
#include <bit>

int main() {
    if constexpr (std::endian::native == std::endian::little)
        std::cout << "System is Little Endian\n";
    else if constexpr (std::endian::native == std::endian::big)
        std::cout << "System is Big Endian\n";
    else
        std::cout << "System is Mixed Endian\n";

    return 0;
}

Possible Output
System is Little Endian

✅ 4. std::source_location Example (C++20)

Captures file name, function name, line number automatically.

✔ Program 4 — std::source_location
#include <iostream>
#include <source_location>

void log(const std::string& message,
         const std::source_location& loc = std::source_location::current()) 
{
    std::cout << "Message: " << message << "\n"
              << "File: " << loc.file_name() << "\n"
              << "Function: " << loc.function_name() << "\n"
              << "Line: " << loc.line() << "\n\n";
}

int main() {
    log("Hello from main!");
    log("Another log message");

    return 0;
}

Output (example)
Message: Hello from main!
File: main.cpp
Function: main
Line: 13

Message: Another log message
File: main.cpp
Function: main
Line: 14

✅ 5. std::format (Python-style formatting) — C++20
✔ Program 5 — std::format
#include <iostream>
#include <format>
#include <string>

int main() {
    std::string name = "John";
    int score = 95;

    std::string s1 = std::format("Hello {}, your score is {}%", name, score);
    std::cout << s1 << "\n";

    // Alignment
    std::cout << std::format("{:>10}", 123) << "\n";   // right align
    std::cout << std::format("{:^10}", 123) << "\n";   // centered
    std::cout << std::format("{:<10}", 123) << "\n";   // left align

    // Format number in hex
    std::cout << std::format("Hex value: {:#x}", 255) << "\n";

    return 0;
}

Output (example)
Hello John, your score is 95%
       123
   123    
123       
Hex value: 0xff









✅ 1. std::error_code and std::error_condition Example
#include <iostream>
#include <system_error>
#include <fstream>

int main() {
    std::ifstream file("missing.txt");
    if (!file) {
        std::error_code ec(errno, std::generic_category());
        std::cout << "Error opening file: " << ec.message() << "\n";
        std::cout << "Error value: " << ec.value() << "\n";
    } else {
        std::cout << "File opened successfully.\n";
    }

    return 0;
}

Possible Output:
Error opening file: No such file or directory
Error value: 2

✅ 2. std::unexpected (from C++23 expected)
#include <iostream>
#include <expected>
#include <string>

std::expected<int, std::string> divide(int a, int b) {
    if (b == 0)
        return std::unexpected("Division by zero!");
    return a / b;
}

int main() {
    auto result = divide(10, 0);

    if (result) {
        std::cout << "Result = " << *result << "\n";
    } else {
        std::cout << "Error: " << result.error() << "\n";
    }

    return 0;
}

Output:
Error: Division by zero!

✅ 3. std::swap (modern usage)
#include <iostream>
#include <utility>

struct MyObj {
    int x;
    MyObj(int v) : x(v) {}
};

int main() {
    MyObj a(10), b(20);

    std::cout << "Before swap: a=" << a.x << ", b=" << b.x << "\n";

    std::swap(a, b);

    std::cout << "After swap: a=" << a.x << ", b=" << b.x << "\n";

    return 0;
}

Output:
Before swap: a=10, b=20
After swap: a=20, b=10

✅ 4. std::ranges::swap (C++20)

Uses ADL + concepts to choose the best swap.

#include <iostream>
#include <ranges>

int main() {
    int a = 5, b = 9;

    std::cout << "Before swap: a=" << a << ", b=" << b << "\n";

    std::ranges::swap(a, b);

    std::cout << "After swap: a=" << a << ", b=" << b << "\n";

    return 0;
}

Output:
Before swap: a=5, b=9
After swap: a=9, b=5

✅ 5. std::ignore Example

A utility for ignoring tuple bindings.

#include <iostream>
#include <tuple>

std::tuple<int, int, int> getData() {
    return {10, 20, 30};
}

int main() {
    int a, c;

    std::tie(a, std::ignore, c) = getData(); // ignore the second element

    std::cout << "a = " << a << "\n";
    std::cout << "c = " << c << "\n";

    return 0;
}

Output:
a = 10
c = 30






✅ 1. std::to_chars / std::from_chars (C++17/20)
Fast, locale-independent conversions between numbers and strings.

#include <iostream>
#include <charconv>
#include <string>

int main() {
    // to_chars: int → string
    int value = 12345;
    char buffer[20];
    auto [ptr, ec] = std::to_chars(buffer, buffer + 20, value);
    *ptr = '\0';
    std::cout << "to_chars result: " << buffer << "\n";

    // from_chars: string → int
    int x;
    std::from_chars(buffer, ptr, x);
    std::cout << "from_chars result: " << x << "\n";

    return 0;
}
/* 
Output
to_chars result: 12345
from_chars result: 12345
*/


✅ 2. std::string_view (C++17)

Non-owning, lightweight string reference.

#include <iostream>
#include <string_view>
#include <string>

void printView(std::string_view sv) {
    std::cout << "View: " << sv << "\n";
}

int main() {
    std::string s = "Hello, C++20!";
    std::string_view sv(s);

    printView(sv);

    // Can slice without copying
    printView(sv.substr(7, 4)); // prints "C++2"

    return 0;
}
/* 
Output
View: Hello, C++20!
View: C++2
*/


✅ 3. std::bitset — Bit manipulation utility
#include <iostream>
#include <bitset>

int main() {
    std::bitset<8> b(42); // 00101010

    std::cout << "Bitset: " << b << "\n";

    b.set(0);   // set LSB
    b.reset(1); // reset 2nd bit
    b.flip(3);  // flip 4th bit

    std::cout << "Modified Bitset: " << b << "\n";
    std::cout << "Count of 1s: " << b.count() << "\n";

    return 0;
}
/* 
Output
Bitset: 00101010
Modified Bitset: 00111101
Count of 1s: 5
*/



✅ 4. std::unique_ptr and std::shared_ptr Utilities
#include <iostream>
#include <memory>

struct Node {
    int value;
    Node(int v) : value(v) { std::cout << "Node created: " << value << "\n"; }
    ~Node() { std::cout << "Node destroyed: " << value << "\n"; }
};

int main() {
    // unique_ptr
    std::unique_ptr<Node> up = std::make_unique<Node>(10);

    // shared_ptr
    std::shared_ptr<Node> sp1 = std::make_shared<Node>(20);
    std::shared_ptr<Node> sp2 = sp1; // reference count increases

    std::cout << "sp1 use_count: " << sp1.use_count() << "\n";

    sp1.reset(); // decrease ref count
    std::cout << "sp2 still alive, use_count: " << sp2.use_count() << "\n";

    return 0;
}
/* 
Sample Output
Node created: 10
Node created: 20
sp1 use_count: 2
Node destroyed: 10
sp2 still alive, use_count: 1
Node destroyed: 20
*/



✅ 5. std::scoped_lock and std::lock_guard (Utility for concurrency)
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void printMessage(const std::string& msg) {
    std::scoped_lock lock(mtx); // safe lock
    std::cout << msg << "\n";
}

int main() {
    std::thread t1(printMessage, "Thread 1");
    std::thread t2(printMessage, "Thread 2");

    t1.join();
    t2.join();

    return 0;
}
/* 
Possible Output
Thread 1
Thread 2
*/




✅ 1. std::invoke & std::invoke_result (C++17/20)
✔ Call any callable object uniformly
✔ Determine return type at compile time
#include <iostream>
#include <functional>
#include <type_traits>

int add(int a, int b) { return a + b; }

struct Multiply {
    int operator()(int a, int b) const { return a * b; }
};
int main() {
    // Using std::invoke
    int sum = std::invoke(add, 2, 3);
    std::cout << "Sum = " << sum << "\n";

    Multiply mul;
    int product = std::invoke(mul, 4, 5);
    std::cout << "Product = " << product << "\n";

    // std::invoke_result
    using ResultType = std::invoke_result_t<Multiply, int, int>;
    std::cout << "Return type of Multiply: " << typeid(ResultType).name() << "\n";

    return 0;
}
/* 
Output
Sum = 5
Product = 20
Return type of Multiply: int
*/



✅ 2. std::apply (C++17)
✔ Apply a tuple to a callable
✔ Useful for unpacking arguments
#include <iostream>
#include <tuple>
#include <utility>

int add3(int a, int b, int c) { return a + b + c; }

int main() {
    std::tuple<int, int, int> t = {1, 2, 3};

    int sum = std::apply(add3, t); // unpack tuple into add3
    std::cout << "Sum from tuple = " << sum << "\n";

    return 0;
}
/* 
Output
Sum from tuple = 6
*/


✅ 3. std::make_integer_sequence (C++14/17)
✔ Generates compile-time sequences
✔ Useful in template metaprogramming
#include <iostream>
#include <utility>

template<typename Seq>
void printSequence();

template<std::size_t... Is>
void printSequence<std::index_sequence<Is...>>() {
    ((std::cout << Is << " "), ...); // fold expression
    std::cout << "\n";
}

int main() {
    using Seq = std::make_index_sequence<5>; // 0 1 2 3 4
    printSequence<Seq>();
    return 0;
}
/* 
Output
0 1 2 3 4 
*/



✅ 4. std::remove_cvref (C++20)
✔ Remove const, volatile, and reference qualifiers
#include <iostream>
#include <type_traits>

template<typename T>
void check() {
    using Clean = std::remove_cvref_t<T>;
    std::cout << "Cleaned type: " << typeid(Clean).name() << "\n";
}

int main() {
    const volatile int& x = 42;
    check<decltype(x)>();
    return 0;
}
/* 
Output
Cleaned type: int
*/



✅ 5. std::ignore in tuple unpacking
#include <iostream>
#include <tuple>

int main() {
    std::tuple<int, int, int> t = {1, 2, 3};
    int a, c;

    std::tie(a, std::ignore, c) = t;

    std::cout << "a = " << a << ", c = " << c << "\n";

    return 0;
}
/* 
Output
a = 1, c = 3
*/







✅ 1. Advanced std::bit_cast Example
✔ Reinterpret struct as bytes safely
#include <iostream>
#include <bit>
#include <array>

struct Vec2 {
    float x, y;
};

int main() {
    Vec2 v{1.5f, -2.5f};

    // reinterpret Vec2 as array of 2 floats
    auto bytes = std::bit_cast<std::array<uint32_t, 2>>(v);

    std::cout << "Vec2 reinterpreted as uint32_t: ";
    for (auto b : bytes) std::cout << std::hex << b << " ";
    std::cout << "\n";

    // Convert back
    Vec2 restored = std::bit_cast<Vec2>(bytes);
    std::cout << std::dec << "Restored Vec2: (" << restored.x << ", " << restored.y << ")\n";

    return 0;
}
/* 
Sample Output
Vec2 reinterpreted as uint32_t: 3fc00000 c0200000 
Restored Vec2: (1.5, -2.5)
*/


✅ 2. std::span — Multi-dimensional slicing
#include <iostream>
#include <span>
#include <array>

int main() {
    std::array<int, 9> arr{1,2,3,4,5,6,7,8,9};

    std::span<int> s(arr);
    std::span<int> sub = s.subspan(3, 3); // elements 4,5,6

    std::cout << "Original array: ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Subspan (3 elements starting at index 3): ";
    for (int x : sub) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Original array: 1 2 3 4 5 6 7 8 9 
Subspan (3 elements starting at index 3): 4 5 6 
*/



✅ 3. std::atomic_ref Example (C++20)
✔ Atomically manipulate non-atomic objects
#include <iostream>
#include <atomic>
#include <thread>

int main() {
    int value = 0;
    std::atomic_ref<int> atomicVal(value);

    std::thread t1([&]() { for(int i=0;i<1000;++i) atomicVal.fetch_add(1); });
    std::thread t2([&]() { for(int i=0;i<1000;++i) atomicVal.fetch_add(1); });

    t1.join();
    t2.join();

    std::cout << "Final value = " << value << "\n"; // expected 2000
    return 0;
}
/* 
Output
Final value = 2000
*/



✅ 4. std::expected — Simple error handling (C++23)
#include <iostream>
#include <expected>
#include <string>

std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) return std::unexpected("Division by zero");
    return a / b;
}

int main() {
    auto res = divide(10, 0);
    if (res) {
        std::cout << "Result: " << *res << "\n";
    } else {
        std::cout << "Error: " << res.error() << "\n";
    }

    res = divide(10, 2);
    std::cout << "Result: " << *res << "\n";

    return 0;
}
/* 
Output
Error: Division by zero
Result: 5
*/




✅ 5. std::source_location — Advanced Logging
#include <iostream>
#include <source_location>

void log(const std::string& msg,
         const std::source_location& loc = std::source_location::current()) {
    std::cout << "[" << loc.file_name() << ":" << loc.line() << " - "
              << loc.function_name() << "] " << msg << "\n";
}

int main() {
    log("Starting program");
    log("Performing an operation");

    return 0;
}
/* 
Sample Output
[main.cpp:14 - main] Starting program
[main.cpp:15 - main] Performing an operation
*/


✅ 1. std::flat_map — Advanced Usage (C++23)
#include <iostream>
#include <flat_map>
#include <string>
int main() {
    std::flat_map<std::string, int> fm;

    // Insert multiple elements
    fm.emplace("Alice", 25);
    fm.emplace("Bob", 30);
    fm.emplace("Charlie", 22);

    std::cout << "Contents of flat_map:\n";
    for (auto &p : fm)
        std::cout << p.first << " => " << p.second << "\n";

    // Find using contains
    if (fm.contains("Bob"))
        std::cout << "Bob exists in map\n";

    // Erase an element
    fm.erase("Alice");

    std::cout << "After erasing Alice:\n";
    for (auto &p : fm)
        std::cout << p.first << " => " << p.second << "\n";

    return 0;
}
/* 
Sample Output
Contents of flat_map:
Alice => 25
Bob => 30
Charlie => 22
Bob exists in map
After erasing Alice:
Bob => 30
Charlie => 22
*/




✅ 2. std::flat_set — Advanced Example (C++23)
#include <iostream>
#include <flat_set>

int main() {
    std::flat_set<int> fs = {5, 1, 3, 4};

    // Automatically sorted
    std::cout << "flat_set contents: ";
    for (int x : fs) std::cout << x << " ";
    std::cout << "\n";

    fs.insert(2);
    fs.insert(6);

    std::cout << "After inserting 2 and 6: ";
    for (int x : fs) std::cout << x << " ";
    std::cout << "\n";

    fs.erase(4);

    std::cout << "After erasing 4: ";
    for (int x : fs) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Sample Output
flat_set contents: 1 3 4 5
After inserting 2 and 6: 1 2 3 4 5 6
After erasing 4: 1 2 3 5 6
*/


✅ 3. std::mdspan — Dynamic Extents (C++23)
#include <iostream>
#include <mdspan>
#include <vector>

int main() {
    size_t rows = 2, cols = 3;
    std::vector<int> data = {1, 2, 3, 4, 5, 6};

    std::mdspan<int, std::dynamic_extent, std::dynamic_extent> mat(data.data(), rows, cols);

    std::cout << "Matrix:\n";
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            std::cout << mat(i, j) << " ";
        std::cout << "\n";
    }

    // Modify element
    mat(1, 2) = 99;

    std::cout << "After modification:\n";
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            std::cout << mat(i, j) << " ";
        std::cout << "\n";
    }

    return 0;
}
/* 
Sample Output
Matrix:
1 2 3
4 5 6
After modification:
1 2 3
4 5 99
*/


✅ 4. std::atomic_wait & std::atomic_notify_one/all (C++20)
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> flag = 0;

void waiter() {
    std::cout << "Waiter thread waiting for flag == 1\n";
    flag.wait(0); // wait until value != 0
    std::cout << "Flag changed to " << flag.load() << "\n";
}

void notifier() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    flag.store(1);
    flag.notify_one(); // wake up waiter
    std::cout << "Notifier thread set flag = 1\n";
}

int main() {
    std::thread t1(waiter);
    std::thread t2(notifier);

    t1.join();
    t2.join();

    return 0;
}
/* 
Sample Output
Waiter thread waiting for flag == 1
Notifier thread set flag = 1
Flag changed to 1
*/






✅ 1. std::atomic_ref — Advanced Usage (C++20)
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

int main() {
    int counter = 0;
    std::atomic_ref<int> atomicCounter(counter);

    auto worker = [&]() {
        for (int i = 0; i < 1000; ++i) {
            atomicCounter.fetch_add(1, std::memory_order_relaxed);
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << "\n"; // expected 2000

    return 0;
}
/* 
Sample Output
Final counter value: 2000
*/



✅ 2. std::shared_mutex & std::scoped_lock (C++17/20)
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex mtx;
int shared_data = 0;

void reader(int id) {
    std::shared_lock lock(mtx);
    std::cout << "Reader " << id << " reads: " << shared_data << "\n";
}

void writer(int value) {
    std::scoped_lock lock(mtx);
    shared_data = value;
    std::cout << "Writer updates to " << value << "\n";
}

int main() {
    std::thread w1(writer, 10);
    std::thread r1(reader, 1);
    std::thread r2(reader, 2);
    std::thread w2(writer, 20);

    w1.join();
    r1.join();
    r2.join();
    w2.join();

    return 0;
}
/* 
Sample Output (order may vary)
Writer updates to 10
Reader 1 reads: 10
Reader 2 reads: 10
Writer updates to 20
*/



✅ 3. std::barrier (C++20)
#include <iostream>
#include <barrier>
#include <thread>
#include <vector>

int main() {
    std::barrier sync_point(3, [](){ 
        std::cout << "All threads reached the barrier!\n"; 
    });

    auto worker = [&](int id) {
        std::cout << "Thread " << id << " working...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500 * id));
        sync_point.arrive_and_wait(); // wait for others
        std::cout << "Thread " << id << " continues...\n";
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
/* 
Sample Output
Thread 1 working...
Thread 2 working...
Thread 3 working...
All threads reached the barrier!
Thread 1 continues...
Thread 2 continues...
Thread 3 continues...
*/



✅ 4. std::latch (C++20)
#include <iostream>
#include <latch>
#include <thread>
#include <vector>

int main() {
    std::latch done(3);

    auto worker = [&](int id){
        std::cout << "Worker " << id << " starting...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300 * id));
        std::cout << "Worker " << id << " done\n";
        done.count_down();
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    done.wait(); // wait until all workers finished
    std::cout << "All workers finished!\n";

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
/* 
Sample Output
Worker 1 starting...
Worker 2 starting...
Worker 3 starting...
Worker 1 done
Worker 2 done
Worker 3 done
All workers finished!
*/



✅ 5. C++20 Ranges — Combining Views and Actions
#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9};

    // Filter even numbers, multiply by 10, take first 3
    auto view = v 
                | std::views::filter([](int x){ return x % 2 == 0; })
                | std::views::transform([](int x){ return x * 10; })
                | std::views::take(3);

    std::cout << "Processed elements: ";
    for (int x : view) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed elements: 20 40 60
*/







✅ 1. std::flat_map — Multi-threaded Access Simulation
#include <iostream>
#include <flat_map>
#include <thread>
#include <shared_mutex>

std::flat_map<int, std::string> fm;
std::shared_mutex mtx;

void writer(int key, const std::string& val) {
    std::scoped_lock lock(mtx);
    fm[key] = val;
    std::cout << "Inserted: " << key << " => " << val << "\n";
}

void reader(int key) {
    std::shared_lock lock(mtx);
    auto it = fm.find(key);
    if (it != fm.end())
        std::cout << "Read: " << key << " => " << it->second << "\n";
    else
        std::cout << "Key " << key << " not found\n";
}

int main() {
    std::thread t1(writer, 1, "One");
    std::thread t2(writer, 2, "Two");
    t1.join();
    t2.join();

    std::thread t3(reader, 1);
    std::thread t4(reader, 3);
    t3.join();
    t4.join();

    return 0;
}
/* 
Sample Output
Inserted: 1 => One
Inserted: 2 => Two
Read: 1 => One
Key 3 not found
*/



✅ 2. std::mdspan — Multi-dimensional Slicing
#include <iostream>
#include <mdspan>
#include <vector>
int main() {
    std::vector<int> data(12);
    for (int i = 0; i < 12; ++i) data[i] = i+1;

    std::mdspan<int, std::dynamic_extent, std::dynamic_extent> mat(data.data(), 3, 4);

    std::cout << "Original matrix:\n";
    for (size_t i=0;i<3;++i){
        for (size_t j=0;j<4;++j)
            std::cout << mat(i,j) << " ";
        std::cout << "\n";
    }

    // Slice: row 1
    auto row1 = std::submdspan(mat, 1, std::span<int,4>{});
    std::cout << "Row 1: ";
    for (size_t j=0;j<4;++j)
        std::cout << mat(1,j) << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Original matrix:
1 2 3 4
5 6 7 8
9 10 11 12
Row 1: 5 6 7 8
*/



✅ 3. std::atomic_wait + notify_one Pipeline Example
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> pipeline_data = 0;

void producer() {
    for(int i=1;i<=5;++i){
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        pipeline_data.store(i);
        std::cout << "Produced: " << i << "\n";
        pipeline_data.notify_one();
    }
}

void consumer() {
    for(int i=1;i<=5;++i){
        pipeline_data.wait(i-1); // wait until data changes
        std::cout << "Consumed: " << pipeline_data.load() << "\n";
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
/* 
Sample Output
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
Produced: 3
Consumed: 3
Produced: 4
Consumed: 4
Produced: 5
Consumed: 5
*/



✅ 4. Polymorphic Allocators (PMR) Example
#include <iostream>
#include <memory_resource>
#include <vector>
int main() {
    // monotonic buffer resource
    char buffer[1024];
    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};
    std::pmr::vector<int> v{&pool};

    for(int i=1;i<=5;++i)
        v.push_back(i);

    std::cout << "Vector elements: ";
    for(auto x:v) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Vector elements: 1 2 3 4 5
*/


✅ 5. Combining flat_set + ranges
#include <iostream>
#include <flat_set>
#include <ranges>

int main() {
    std::flat_set<int> fs = {5, 2, 8, 1, 7};

    auto view = fs 
                | std::views::filter([](int x){ return x%2==1; }) // odd numbers
                | std::views::transform([](int x){ return x*10; });

    std::cout << "Processed elements: ";
    for(auto x:view) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed elements: 10 50 70 
*/







✅ 1. Ranges + Views + Actions Pipeline
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    // Filter even numbers, square them, reverse the view
    auto view = v 
                | std::views::filter([](int x){ return x % 2 == 0; })
                | std::views::transform([](int x){ return x * x; })
                | std::views::reverse;

    std::cout << "Processed elements: ";
    for(int x:view) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed elements: 100 64 36 16 4
*/


✅ 2. Parallel Algorithms with Execution Policies (C++17/20)
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> v(1'000'000);
    std::iota(v.begin(), v.end(), 1);

    // Multiply each element by 2 in parallel
    std::for_each(std::execution::par, v.begin(), v.end(), [](int &x){ x *= 2; });

    std::cout << "First 5 elements after parallel transform: ";
    for(int i=0;i<5;i++) std::cout << v[i] << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
First 5 elements after parallel transform: 2 4 6 8 10
*/


✅ 3. Advanced Atomic Pipeline with notify_all
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> stage = 0;

void stage_worker(int id, int wait_for) {
    stage.wait(wait_for);
    std::cout << "Thread " << id << " processing stage " << wait_for + 1 << "\n";
    stage.store(wait_for + 1);
    stage.notify_all();
}

int main() {
    std::thread t1(stage_worker, 1, 0);
    std::thread t2(stage_worker, 2, 1);
    std::thread t3(stage_worker, 3, 2);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
/* 
Sample Output
Thread 1 processing stage 1
Thread 2 processing stage 2
Thread 3 processing stage 3
*/


✅ 4. PMR with Custom Allocator
#include <iostream>
#include <memory_resource>
#include <vector>

class logging_resource : public std::pmr::memory_resource {
protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        std::cout << "Allocating " << bytes << " bytes\n";
        return std::malloc(bytes);
    }
    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        std::cout << "Deallocating " << bytes << " bytes\n";
        std::free(p);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

int main() {
    logging_resource log_res;
    std::pmr::vector<int> v{&log_res};

    for(int i=0;i<5;i++) v.push_back(i);

    std::cout << "Vector elements: ";
    for(auto x:v) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Sample Output
Allocating 24 bytes
Vector elements: 0 1 2 3 4
Deallocating 24 bytes
*/



✅ 5. Combining flat_map + ranges + views
#include <iostream>
#include <flat_map>
#include <ranges>

int main() {
    std::flat_map<int, std::string> fm = {{1,"one"},{2,"two"},{3,"three"}};

    auto view = fm 
                | std::views::filter([](auto &p){ return p.first % 2 == 1; })
                | std::views::transform([](auto &p){ return p.second + "!"; });

    std::cout << "Processed map values: ";
    for(auto s:view) std::cout << s << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed map values: one! three!
*/







✅ 1. C++23 Ranges + Actions (to, sort, unique)
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> v = {5, 2, 3, 5, 2, 4, 1};

    // Sort and remove duplicates using ranges actions
    auto result = v 
                  | std::views::all 
                  | std::ranges::to<std::vector>; // create a copy

    std::ranges::sort(result);
    auto last = std::ranges::unique(result);
    result.erase(last.begin(), result.end());

    std::cout << "Sorted & unique elements: ";
    for(int x:result) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Sorted & unique elements: 1 2 3 4 5
*/


✅ 2. flat_set with Custom Comparator
#include <iostream>
#include <flat_set>

struct Descending {
    bool operator()(int a, int b) const { return a > b; }
};

int main() {
    std::flat_set<int, Descending> fs = {5, 2, 8, 3};

    std::cout << "flat_set in descending order: ";
    for(int x:fs) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
flat_set in descending order: 8 5 3 2
*/




✅ 3. Atomic Producer-Consumer Queue
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <queue>

std::atomic<bool> ready = false;
std::queue<int> q;
std::mutex mtx;

void producer() {
    for(int i=1;i<=5;++i) {
        {
            std::scoped_lock lock(mtx);
            q.push(i);
            std::cout << "Produced: " << i << "\n";
        }
        ready.store(true);
        std::atomic_notify_all(&ready);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer() {
    int consumed = 0;
    while(consumed < 5) {
        ready.wait(false); // wait until ready is true
        int value = 0;
        {
            std::scoped_lock lock(mtx);
            if(!q.empty()) {
                value = q.front();
                q.pop();
                consumed++;
            }
        }
        if(value != 0)
            std::cout << "Consumed: " << value << "\n";
        ready.store(false);
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
/* 
Sample Output
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
Produced: 3
Consumed: 3
Produced: 4
Consumed: 4
Produced: 5
Consumed: 5
*/



✅ 4. PMR + Polymorphic Containers Pipeline
#include <iostream>
#include <memory_resource>
#include <vector>
#include <string>

int main() {
    char buffer[1024];
    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};
    std::pmr::vector<std::pmr::string> words{&pool};

    words.push_back("hello");
    words.push_back("world");
    words.push_back("pmr");

    std::cout << "Words in PMR vector: ";
    for(auto &w:words) std::cout << w << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Words in PMR vector: hello world pmr
*/


✅ 5. flat_map with Custom Comparator and Ranges Filter
#include <iostream>
#include <flat_map>
#include <ranges>
#include <string>

struct Desc {
    bool operator()(const int &a, const int &b) const { return a > b; }
};

int main() {
    std::flat_map<int, std::string, Desc> fm = {{1,"one"}, {3,"three"}, {2,"two"}};

    // Filter keys >1 and append '!'
    auto view = fm 
                | std::views::filter([](auto &p){ return p.first > 1; })
                | std::views::transform([](auto &p){ return p.second + "!"; });

    std::cout << "Processed map values: ";
    for(auto &s:view) std::cout << s << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed map values: three! two!
*/







✅ 1. std::mdspan — Multi-dimensional views & slices
#include <iostream>
#include <mdspan>
#include <vector>

int main() {
    std::vector<int> data = {1,2,3,4,5,6,7,8,9};
    std::mdspan<int, 3, 3> mat(data.data());

    std::cout << "Original 3x3 matrix:\n";
    for (size_t i=0;i<3;++i){
        for (size_t j=0;j<3;++j)
            std::cout << mat(i,j) << " ";
        std::cout << "\n";
    }

    // Slice first two rows
    auto slice = std::submdspan(mat, std::pair{0,2}, std::pair{0,3});
    std::cout << "Slice (first 2 rows):\n";
    for (size_t i=0;i<2;++i){
        for (size_t j=0;j<3;++j)
            std::cout << slice(i,j) << " ";
        std::cout << "\n";
    }

    return 0;
}
/* 
Output
Original 3x3 matrix:
1 2 3
4 5 6
7 8 9
Slice (first 2 rows):
1 2 3
4 5 6
*/


✅ 2. Ranges with Lazy Evaluation and Pipeline Composition
#include <iostream>
#include <vector>
#include <ranges>
int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    auto pipeline = v 
                    | std::views::filter([](int x){ return x%3==0; }) // divisible by 3
                    | std::views::transform([](int x){ return x*x; }) // square
                    | std::views::reverse; // reverse order

    std::cout << "Processed pipeline elements: ";
    for (int x : pipeline) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed pipeline elements: 81 36 9
Lazy evaluation ensures computations happen only when iterated.
*/



✅ 3. Multi-stage Atomic Pipeline with Wait/Notify
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> stage = 0;

void worker(int id, int wait_for) {
    stage.wait(wait_for);
    std::cout << "Worker " << id << " processing stage " << wait_for+1 << "\n";
    stage.store(wait_for+1);
    stage.notify_all();
}

int main() {
    std::thread t1(worker, 1, 0);
    std::thread t2(worker, 2, 1);
    std::thread t3(worker, 3, 2);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
/* 
Sample Output
Worker 1 processing stage 1
Worker 2 processing stage 2
Worker 3 processing stage 3

Each thread waits for the previous stage to complete using atomic.wait and notifies the next stage.
*/


✅ 4. PMR + Nested Polymorphic Containers
#include <iostream>
#include <memory_resource>
#include <vector>
#include <string>
#include <map>
#include <string_view>

int main() {
    char buffer[2048];
    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};

    std::pmr::map<std::string, std::pmr::vector<std::string>> directory{&pool};

    directory["fruits"].push_back("apple");
    directory["fruits"].push_back("banana");
    directory["vegetables"].push_back("carrot");

    std::cout << "Directory contents:\n";
    for(auto &[category, items]:directory){
        std::cout << category << ": ";
        for(auto &item:items) std::cout << item << " ";
        std::cout << "\n";
    }

    return 0;
}
/* 
Output
Directory contents:
fruits: apple banana 
vegetables: carrot 

Nested PMR containers allow multiple polymorphic memory-managed structures to share the same memory resource efficiently.
*/


✅ 5. flat_map + mdspan + Ranges Integration
#include <iostream>
#include <flat_map>
#include <mdspan>
#include <ranges>
int main() {
    std::flat_map<int, int> fm = {{1,10},{2,20},{3,30}};

    // Create a view of values using ranges
    auto values_view = fm | std::views::transform([](auto &p){ return p.second; });

    // Copy to contiguous memory for mdspan
    std::vector<int> values(values_view.begin(), values_view.end());
    std::mdspan<int, 1> span(values.data(), values.size());

    std::cout << "Values via mdspan: ";
    for(size_t i=0;i<span.extent(0);++i) std::cout << span(i) << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Values via mdspan: 10 20 30
*/





✅ 1. Ranges Actions — to, chunk, zip
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    // Chunk into groups of 3
    auto chunks = v 
                  | std::views::chunk(3); // C++23 chunk view

    std::cout << "Chunks of 3:\n";
    for (auto chunk : chunks) {
        for (int x : chunk) std::cout << x << " ";
        std::cout << "\n";
    }

    // Zip two sequences (simulate)
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David"};
    auto zipped = std::views::zip(v, names); // Conceptual; some compilers need ranges-v3

    return 0;
}
/* 
Sample Output
Chunks of 3:
1 2 3 
4 5 6 
7 8 9 
10

zip requires ranges-v3 or custom implementation until fully standardized.
*/


✅ 2. flat_set + Transformations Pipeline
#include <iostream>
#include <flat_set>
#include <ranges>
int main() {
    std::flat_set<int> fs = {1,2,3,4,5,6};

    // Keep even numbers and multiply by 100
    auto view = fs
                | std::views::filter([](int x){ return x % 2 == 0; })
                | std::views::transform([](int x){ return x * 100; });

    std::cout << "Processed flat_set: ";
    for(int x:view) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed flat_set: 200 400 600
*/


✅ 3. Multi-consumer Atomic Queue
#include <iostream>
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>

std::atomic<bool> ready = false;
std::queue<int> q;
std::mutex mtx;

void producer() {
    for(int i=1;i<=5;++i){
        {
            std::scoped_lock lock(mtx);
            q.push(i);
            std::cout << "Produced: " << i << "\n";
        }
        ready.store(true);
        std::atomic_notify_all(&ready);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int id){
    int consumed = 0;
    while(consumed < 3){
        ready.wait(false);
        int value = 0;
        {
            std::scoped_lock lock(mtx);
            if(!q.empty()){
                value = q.front();
                q.pop();
                consumed++;
            }
        }
        if(value != 0)
            std::cout << "Consumer " << id << " consumed " << value << "\n";
        ready.store(false);
    }
}

int main() {
    std::thread p(producer);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p.join();
    c1.join();
    c2.join();

    return 0;
}
/* 
Sample Output (order may vary)
Produced: 1
Consumer 1 consumed 1
Produced: 2
Consumer 2 consumed 2
Produced: 3
Consumer 1 consumed 3
Produced: 4
Consumer 2 consumed 4
Produced: 5
Consumer 1 consumed 5
*/





✅ 4. PMR — Complex Graph/Tree Structure
#include <iostream>
#include <memory_resource>
#include <vector>
#include <map>
#include <string>
struct Node {
    std::string name;
    std::pmr::vector<Node*> children;
    Node(const std::string &n, std::pmr::memory_resource* mr) : name(n), children(mr) {}
};
int main() {
    char buffer[4096];
    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};

    Node root("root", &pool);
    Node child1("child1", &pool);
    Node child2("child2", &pool);

    root.children.push_back(&child1);
    root.children.push_back(&child2);

    std::cout << "Tree structure:\n";
    std::cout << root.name << "\n";
    for(auto child: root.children)
        std::cout << "  " << child->name << "\n";

    return 0;
}
/* 
Output
Tree structure:
root
  child1
  child2

PMR allows dynamic nested structures (like trees or graphs) to share the same memory efficiently.
*/






✅ 5. flat_map + Transformations + Filter
#include <iostream>
#include <flat_map>
#include <ranges>
int main() {
    std::flat_map<int, std::string> fm = {{1,"one"}, {2,"two"}, {3,"three"}, {4,"four"}};

    auto view = fm
                | std::views::filter([](auto &p){ return p.first % 2 == 0; })
                | std::views::transform([](auto &p){ return p.second + "++"; });

    std::cout << "Processed flat_map: ";
    for(auto &s:view) std::cout << s << " ";
    std::cout << "\n";

    return 0;
}
/* 
Output
Processed flat_map: two++ four++
*/

/* ----------------------------------------------------------- */

✔ std::stop_token (Cooperative cancellation)
std::stop_source
std::stop_callback

1️⃣ Example: std::stop_source and std::stop_token
This demonstrates how a thread can be cooperatively canceled using std::stop_source and std::stop_token.
/* ----------------------------------------------------------- */
#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

void worker(std::stop_token stoken) {
    int count = 0;
    while (!stoken.stop_requested()) {  // Check for stop request
        std::cout << "Working... step " << count++ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Worker received stop request. Exiting...\n";
}

int main() {
    std::stop_source ssource;              // Source of stop requests
    std::stop_token stoken = ssource.get_token();  // Token to pass to thread

    std::thread t(worker, stoken);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Main thread requesting stop...\n";
    ssource.request_stop();  // Ask worker thread to stop

    t.join();
    std::cout << "Main thread finished.\n";
    return 0;
}
/* 
Output (example):
Working... step 0
Working... step 1
Working... step 2
Working... step 3
Main thread requesting stop...
Worker received stop request. Exiting...
Main thread finished.
*/



2️⃣ Example: std::stop_callback
This demonstrates how to attach a callback to a std::stop_token which executes when a stop is requested.

#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

void worker_with_callback(std::stop_token stoken) {
    std::stop_callback callback(stoken, []() {
        std::cout << "Stop callback triggered!\n";
    });

    int count = 0;
    while (!stoken.stop_requested()) {
        std::cout << "Working... step " << count++ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Worker finished after stop request.\n";
}

int main() {
    std::stop_source ssource;
    std::stop_token stoken = ssource.get_token();

    std::thread t(worker_with_callback, stoken);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Main thread requesting stop...\n";
    ssource.request_stop();  // triggers stop and callback

    t.join();
    return 0;
}
/* 
Output (example):
Working... step 0
Working... step 1
Main thread requesting stop...
Stop callback triggered!
Worker finished after stop request.
*/










3️⃣ Standalone std::stop_token usage

This example shows how multiple threads can share the same stop token and react cooperatively.

#include <iostream>
#include <thread>
#include <vector>
#include <stop_token>
#include <chrono>

void worker(int id, std::stop_token stoken) {
    while (!stoken.stop_requested()) {
        std::cout << "Thread " << id << " working...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    std::cout << "Thread " << id << " stopping...\n";
}

int main() {
    std::stop_source ssource;
    std::stop_token stoken = ssource.get_token();

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i)
        threads.emplace_back(worker, i, stoken);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Main thread requesting stop for all threads...\n";
    ssource.request_stop();

    for (auto& t : threads) t.join();
    std::cout << "All threads stopped.\n";
    return 0;
}
/* 
Output (example):

Thread 0 working...
Thread 1 working...
Thread 2 working...
Thread 0 working...
Thread 1 working...
Thread 2 working...
Main thread requesting stop for all threads...
Thread 0 stopping...
Thread 1 stopping...
Thread 2 stopping...
All threads stopped.


✅ Key Points:
std::stop_source generates stop requests.
std::stop_token is passed to threads to check for cancellation.
std::stop_callback allows you to react immediately when a stop is requested.
Multiple threads can share a single stop token for cooperative cancellation. 
*/

/* ----------------------------------------------------------- */







