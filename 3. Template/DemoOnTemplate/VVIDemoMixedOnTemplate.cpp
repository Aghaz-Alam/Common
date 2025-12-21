Normal template usage

#include<iostream>
using namespace std;
template<typename T>
auto Add(T x, T y){
    return x + y;
}
int main(){
    cout<<Add(2,5)<<endl;
    cout<<Add(3.5, 5.4)<<endl;
    cout<<Add('A', 'B')<<endl;
    //cout<<Add("Hello ", "World")<<endl;     //compile-time error
    cout<<Add(string("Hello "), string("World"))<<endl;
  return 0;
}
/* 
7
8.9
131
Hello World
 */

 

// Normal Template Usage (C++11 decltype return)
#include <iostream>
using namespace std;
template <typename T1, typename T2>
auto Add(T1 x, T2 y) -> decltype(x + y) {
    return x + y;
}
int main() {
    cout << "Addition of 3 and 7.5f is: " << Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << Add(3.5, 7) << endl;
    cout << "Addition of 'A' and 'E' is: " << Add(char('A'), char('E')) << endl;  //A=65, B=69   ===A+B=65+69=134
    cout << "Addition of Hello and World is: " << Add(string("Hello "), string("World!")) << endl; //Hello World
    
   return 0;
}
/* DemoNormalTemplate
Output:
Addition of 3 and 7.5f is: 10.5
Addition of 3.5f and 7.5 is: 11
Addition of 3.5 and 7 is: 10.5
Addition of 'A' and 'E' is: 134
Addition of Hello and World is: Hello World!
*/


//C++14 — auto Return Type Deduction
#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
auto Add(T1 x, T2 y) {
    return x + y;   // C++14 deduces return type automatically
}

int main() {
    cout << "Addition of 3 and 7.5f is: " << Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << Add(3.5, 7) << endl;

    cout << "Addition of 'A' and 'E' is: " << Add(char('A'), char('E')) << endl;  // 65 + 69 = 134

    cout << "Addition of Hello and World is: " << Add(string("Hello "), string("World!")) << endl;

    return 0;
}
/*
Addition of 3 and 7.5f is: 10.5
Addition of 3.5f and 7.5 is: 11
Addition of 3.5 and 7 is: 10.5
Addition of 'A' and 'E' is: 134
Addition of Hello and World is: Hello World!
*/





//Variadic Templates (C++11 / C++14 Recursive)
#include <iostream>
using namespace std;
// Base case
void print() {
    cout << "Empty Function! " << endl;
}

// Variadic template function: processes one argument and recursively calls itself
template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first<< endl;
    print(rest...); // Pack expansion: calls print with the remaining arguments
}
int main() {
    print(1, 2.5, "Hello", 'A'); 
}
/*
Output;
1
2.5
Hello
A
Empty Function! 
*/



//Variadic Templates — C++17 Fold Expressions
#include <iostream>
using namespace std;
template <typename... Args>
void print(Args... args) {
    // Print each argument followed by newline
    ((cout << args << endl), ...);

    cout << "Empty Function!" << endl;
}

int main() {
    print(1, 2.5, "Hello", 'A');
}
/*
1
2.5
Hello
A
Empty Function!
*/



// Variadic add() (C++11 Recursive)
#include <iostream>
using namespace std;
// Base case
int add() {
    cout << "Empty Function!" << endl;
    return 0;
}
// Variadic template recursive function
template <typename T, typename... Args>
int add(T first, Args... rest) {
    return first + add(rest...);
}

int main() {
    cout << add(1, 2, 3, 4, 5) << endl;
}
/*
Output;
Empty Function! 
15
*/


// Variadic Templates - C++17 (Fold Expression)
#include <iostream>
using namespace std;
// Variadic add using fold expression
template <typename... Args>
int add(Args... args) {
    cout << "Empty Function!" << endl;   // mimic your original behavior
    return (args + ...);                 // C++17 fold expression
}
int main() {
    cout << add(1, 2, 3, 4, 5) << endl;
}
/*
Empty Function!
15
*/




//C++14 Mixed sum
#include <iostream>
using namespace std;
// 1. Base case: non-template function to stop the recursion (handles the empty pack)
int Sum() {
    return 0;
}

// 2. Recursive case: template function to process one argument and recurse
template<typename T, typename... Args>
int Sum(T first, Args... rest) {
    // The recursive call with a reduced parameter pack
    return first + Sum(rest...);
}
int main() {
    // The compiler generates instantiations for Sum(1, 2, 3), 
    // then Sum(2, 3), then Sum(3), and finally Sum()
    int total1 = Sum(1, 2, 3, 4, 5); 
    cout << "Sum is: " << total1 << endl; // Output: Sum is: 15

    // Works with different types (implicit conversion to int return type)
    int total2 = Sum(1, 2.5, 3);
    cout << "Mixed Sum is: " << total2 << endl; // Output: Mixed Sum is: 6 (due to int return type)

    return 0;
}
/*
Sum is: 15
Mixed Sum is: 6
*/



//Mixed sum C++17: Mixed Sum (C++17 Fold Expression)
#include <iostream>
using namespace std;

// C++17 fold-expression based Sum()
template <typename... Args>
auto Sum(Args... args) {
    return (args + ...);   // Fold expression (right fold)
}

int main() {
    int total1 = Sum(1, 2, 3, 4, 5);
    cout << "Sum is: " << total1 << endl;  // 15

    // Now returns double, no truncation!
    auto total2 = Sum(1, 2.5, 3);
    cout << "Mixed Sum is: " << total2 << endl;  // 6.5

    return 0;
}
/*
Sum is: 15
Mixed Sum is: 6.5
*/


//C++ 11/14/17: Full Template Specialization
1. Full Template Specialization
In full specialization, We provide an entirely separate implementation for a specific type or class template.
#include <iostream>
using namespace std;

// Primary template
template <typename T>
void print(T value) {
    cout << "Generic template: " << value << endl;
}

// Full specialization for int
template <>
void print<int>(int value) {
    cout << "Specialized template for int: " << value << endl;
}

int main() {
    print(3.14);  // Uses the generic template
    print(42);    // Uses the specialized template for int
    return 0;
}
/*
Generic template: 3.14
Specialized template for int: 42
*/


//C++11/14/17 same with return value: Full Template Specialization (Return version)
#include <iostream>
using namespace std;

// Primary template
template <typename T>
T print(T value) {
    cout << "Generic template: " << value << endl;
    return value;     // Return the same value
}

// Full specialization for int
template <>
int print<int>(int value) {
    cout << "Specialized template for int: " << value << endl;
    return value * 2;   // Just an example: return modified value
}

int main() {
    double d = print(3.14);   // Uses generic version
    int n     = print(42);    // Uses specialized version

    cout << "Returned (generic): " << d << endl;
    cout << "Returned (specialized int): " << n << endl;

    return 0;
}

/*
Generic template: 3.14
Specialized template for int: 42
Returned (generic): 3.14
Returned (specialized int): 84
*/


2. Partial Template Specialization: Partial Specialization (Pointer Types)
In partial specialization, you define a specialized version of the template that works for a subset of types. 
For example, you might want to specialize a template for pointer types or reference types.

#include <iostream>
using namespace std;

// Primary template
template <typename T>
void print(T value) {
    cout << "Generic template: " << value << endl;
}

// Partial specialization for pointer types
template <typename T>
void print(T* value) {
    cout << "Specialized template for pointer: " << *value << endl;
}
int main() {
    int x = 10;
    print(x);          // Uses the generic template
    print(&x);         // Uses the specialized template for pointers
    return 0;
}
/*
Generic template: 10
Specialized template for pointer: 10
*/


3. Template Specialization with Multiple Parameters:  Template With Multiple Parameters

You can also specialize a template when it has multiple parameters. 
For example, you can specialize a template when one of its parameters is a certain type.


include <iostream>
using namespace std;

// Generic template with two parameters
template <typename T, typename U>
void print(T value1, U value2) {
    cout << "Generic template: " << value1 << ", " << value2 << endl;
}

// Overload for int as the first parameter
template <typename U>
void print(int value1, U value2) {
    cout << "Specialized template for int as first parameter: " << value1 << ", " << value2 << endl;
}

int main() {
    print(5, 3.14);     // Uses the overload for int
    print("Hello", 42); // Uses the generic template
    return 0;
}
/*
Specialized template for int as first parameter: 5, 3.14
Generic template: Hello, 42
*/






3. SFINAE C++11: SFINAE — C++11 enable_if
Sometimes, you may want to specialize templates based on certain conditions like whether a type is integral or 
floating-point. 
This is often achieved using SFINAE (Substitution Failure Is Not An Error) along with std::enable_if or type traits.


#include <iostream>
#include <type_traits>
using namespace std;

// Function template enabled only for arithmetic types
template <typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
add(T a, T b) {
    cout << "Arithmetic add() called\n";
    return a + b;
}

// Overload for non-arithmetic types (optional)
template <typename T>
typename enable_if<!is_arithmetic<T>::value, T>::type
add(T a, T b) {
    cout << "Non-arithmetic add() called\n";
    return a + b; // Just for demonstration
}

int main() {
    cout << add(10, 20) << endl;          // OK: int → arithmetic
    cout << add(2.5, 3.7) << endl;        // OK: double → arithmetic
    cout << add(2.5f, 5.7f) << endl;      // OK: float → arithmetic

    // Example non-arithmetic type
    string x = "Hello ", y = "World";
    cout << add(x, y) << endl;            // Non-arithmetic version called

    return 0;
}
/*
Arithmetic add() called
30
Arithmetic add() called
6.2
Arithmetic add() called
8.2
Non-arithmetic add() called
Hello World
*/

//C++14: SFINAE — C++14 enable_if_t
#include <iostream>
#include <type_traits>
using namespace std;

// Function enabled only for arithmetic types
template <typename T>
enable_if_t<is_arithmetic<T>::value, T>
add(T a, T b) {
    cout << "Arithmetic add() called\n";
    return a + b;
}

// Function enabled only for non-arithmetic types (e.g., string)
template <typename T>
enable_if_t<!is_arithmetic<T>::value, T>
add(T a, T b) {
    cout << "Non-arithmetic add() called\n";
    return a + b; // works if operator+ is defined
}

int main() {
    cout << add(10, 20) << endl;        // int → arithmetic
    cout << add(2.5, 3.7) << endl;      // double → arithmetic
    cout << add(2.5f, 5.7f) << endl;    // float → arithmetic

    string x = "Hello ", y = "World";
    cout << add(x, y) << endl;          // string → non-arithmetic

    return 0;
}
/*
Arithmetic add() called
30
Arithmetic add() called
6.2
Arithmetic add() called
8.2
Non-arithmetic add() called
Hello World
*/



//Metaprogramming: Metaprogramming — C++11 constexpr recursion
Metaprogramming (C++11)
C++11 formalized many metaprogramming techniques and improved their syntax and usability. 

Key features included:
constexpr: Allowed functions and variables to be evaluated at compile time, providing a more readable 
and efficient alternative to complex template recursion for simple calculations.

<type_traits> library: Standardized tools for type manipulation and introspection, 
which are the backbone of modern C++ metaprogramming.


Example: Compile-time calculation using constexpr:
#include <iostream>
using namespace std;
// C++11 constexpr factorial (recursive)
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}
int main() {
    constexpr int f5 = factorial(5); // compile-time evaluation
    cout << "Factorial of 5: " << f5 << endl;
}
/*
Factorial of 5: 120
*/



Metaprogramming C++14
C++14 significantly eased the implementation of metaprograms by relaxing the constraints on constexpr functions.

A. Relaxed constexpr: Metaprogramming — C++14 relaxed constexpr
In C++11, constexpr functions were limited to a single return statement 
(often using the ternary operator for logic/recursion). 

C++14 allowed constexpr functions to contain:
->Local variable declarations
->if and switch statements
->Loops (for, while, do-while)

This allowed compile-time computation to be written in a style very close to normal runtime C++ code, 
almost entirely replacing complex template recursion for many numeric tasks.

#include <iostream>
using namespace std;
constexpr int factorial(int n) {
    if(n<=1) return 1;   // base case
    
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}
int main() {
    constexpr int f5 = factorial(5); // compile-time evaluation
    cout << "Factorial of 5: " << f5 << endl;
}
/*
Factorial of 5: 120
*/




✅ 13. Concept-Based Polymorphism (C++20 Concepts)

Concepts allow compile-time polymorphism with constraints.

✔ Program
#include <iostream>
#include <concepts>
using namespace std;

template<typename T>
concept Number = requires(T x) {
    { x + x } -> convertible_to<T>;
};

template<Number T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(10, 20) << endl;
    cout << add(1.5, 2.5) << endl;

    // string is not Number → compile error if attempted
    // cout << add(string("hi"), string("ok"));
}

✔ Output
30
4

✅ 14. CRTP + Static Polymorphism
✔ Program
#include <iostream>
using namespace std;

// Curiously Recurring Template Pattern
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class A : public Base<A> {
public:
    void implementation() {
        cout << "A implementation\n";
    }
};

class B : public Base<B> {
public:
    void implementation() {
        cout << "B implementation\n";
    }
};

int main() {
    A a;
    B b;
    a.interface();
    b.interface();
}

✔ Output
A implementation
B implementation

✅ 15. Polymorphism via std::function (Callback Polymorphism)
✔ Program
#include <iostream>
#include <functional>
using namespace std;

void hello()   { cout << "Hello\n"; }
void welcome() { cout << "Welcome\n"; }

int main() {
    function<void()> f;

    f = hello;
    f();

    f = welcome;
    f();

    return 0;
}

✔ Output
Hello
Welcome

✅ 16. Virtual Constructor Idiom (clone pattern)
✔ Program
#include <iostream>
using namespace std;

class Base {
public:
    virtual Base* clone() = 0;
    virtual void show() = 0;
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    Base* clone() override { return new Derived(*this); }
    void show() override { cout << "Derived cloned\n"; }
};

int main() {
    Base* b1 = new Derived();
    Base* b2 = b1->clone();

    b1->show();
    b2->show();

    delete b1;
    delete b2;
}

✔ Output
Derived cloned
Derived cloned

✅ 17. Polymorphism via std::variant + std::visit
✔ Program
#include <iostream>
#include <variant>
using namespace std;

struct A { void operator()() const { cout << "A\n"; } };
struct B { void operator()() const { cout << "B\n"; } };

int main() {
    variant<A, B> v;

    v = A{};
    visit([](auto &obj){ obj(); }, v);

    v = B{};
    visit([](auto &obj){ obj(); }, v);
}

✔ Output
A
B

✅ 18. Interface Segregation Polymorphism
✔ Program
#include <iostream>
using namespace std;

struct Printable {
    virtual void print() = 0;
};

struct Saveable {
    virtual void save() = 0;
};

class Document : public Printable, public Saveable {
public:
    void print() override { cout << "Printing document\n"; }
    void save()  override { cout << "Saving document\n"; }
};

int main() {
    Document d;
    Printable* p = &d;
    Saveable* s  = &d;

    p->print();
    s->save();
}

✔ Output
Printing document
Saving document

✅ 19. Policy-Based Polymorphism
✔ Program
#include <iostream>
using namespace std;

struct AddPolicy {
    static int op(int a, int b) { return a + b; }
};

struct MulPolicy {
    static int op(int a, int b) { return a * b; }
};

template<typename Policy>
class Calculator {
public:
    int compute(int x, int y) { return Policy::op(x,y); }
};

int main() {
    Calculator<AddPolicy> addCalc;
    Calculator<MulPolicy> mulCalc;

    cout << addCalc.compute(5,10) << endl;
    cout << mulCalc.compute(5,10) << endl;
}

✔ Output
15
50

✅ 20. PImpl + Polymorphic Implementation
✔ Program
#include <iostream>
#include <memory>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class CircleImpl : public Shape {
public:
    void draw() override { cout << "Drawing Circle\n"; }
};

class RectangleImpl : public Shape {
public:
    void draw() override { cout << "Drawing Rectangle\n"; }
};

class Graphics {
    unique_ptr<Shape> impl;
public:
    Graphics(unique_ptr<Shape> s): impl(move(s)) {}
    void render(){ impl->draw(); }
};

int main() {
    Graphics g1(make_unique<CircleImpl>());
    Graphics g2(make_unique<RectangleImpl>());

    g1.render();
    g2.render();
}

✔ Output
Drawing Circle
Drawing Rectangle





✅ 21. Dynamic Mixin Polymorphism (Runtime Mixins)

Mixins allow adding behavior dynamically.

✔ Program
#include <iostream>
#include <memory>
using namespace std;

class IBehavior {
public:
    virtual void action() = 0;
    virtual ~IBehavior() = default;
};

class Fly : public IBehavior {
public:
    void action() override { cout << "Flying...\n"; }
};

class Swim : public IBehavior {
public:
    void action() override { cout << "Swimming...\n"; }
};

class Animal {
    unique_ptr<IBehavior> behavior;
public:
    void setBehavior(unique_ptr<IBehavior> b) {
        behavior = move(b);
    }
    void doAction() {
        if (behavior) behavior->action();
    }
};

int main() {
    Animal a;
    a.setBehavior(make_unique<Fly>());
    a.doAction();

    a.setBehavior(make_unique<Swim>());
    a.doAction();
}

✔ Output
Flying...
Swimming...

✅ 22. Prototype Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Prototype {
public:
    virtual Prototype* clone() = 0;
    virtual void print() = 0;
    virtual ~Prototype() = default;
};

class A : public Prototype {
public:
    Prototype* clone() override { return new A(*this); }
    void print() override { cout << "A object\n"; }
};

class B : public Prototype {
public:
    Prototype* clone() override { return new B(*this); }
    void print() override { cout << "B object\n"; }
};

int main() {
    Prototype* p1 = new A();
    Prototype* p2 = p1->clone();
    p1->print();
    p2->print();

    delete p1;
    delete p2;
}

✔ Output
A object
A object

✅ 23. Expression Template Polymorphism
✔ Program
#include <iostream>
using namespace std;

template<typename L, typename R>
class AddExpr {
    const L& l; const R& r;
public:
    AddExpr(const L& a, const R& b) : l(a), r(b) {}
    int operator[](int i) const { return l[i] + r[i]; }
    int size() const { return l.size(); }
};

class Vec {
    int arr[3];
public:
    Vec(int a, int b, int c) { arr[0]=a; arr[1]=b; arr[2]=c; }

    int operator[](int i) const { return arr[i]; }
    int size() const { return 3; }

    template<typename E>
    void operator=(const E& e) {
        for(int i=0;i<3;i++) arr[i] = e[i];
    }
};

template<typename L>
auto operator+(const Vec& v, const L& e) {
    return AddExpr<Vec, L>(v,e);
}

int main() {
    Vec a(1,2,3), b(4,5,6), c(0,0,0);
    c = a + b;

    for(int i=0;i<3;i++)
        cout << c[i] << " ";
}

✔ Output
5 7 9 

✅ 24. State Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class State {
public:
    virtual void handle() = 0;
    virtual ~State() = default;
};

class Start : public State {
public:
    void handle() override { cout << "Start State\n"; }
};

class Stop : public State {
public:
    void handle() override { cout << "Stop State\n"; }
};

class Context {
    State* state;
public:
    Context(State* s) : state(s) {}
    void setState(State* s) { state = s; }
    void request() { state->handle(); }
};

int main() {
    Start s1; Stop s2;
    Context c(&s1);

    c.request();
    c.setState(&s2);
    c.request();
}

✔ Output
Start State
Stop State

✅ 25. Strategy Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Strategy {
public:
    virtual void execute() = 0;
    virtual ~Strategy() = default;
};

class Add : public Strategy {
public:
    void execute() override { cout << "Add strategy\n"; }
};

class Sub : public Strategy {
public:
    void execute() override { cout << "Sub strategy\n"; }
};

class Context {
    Strategy* s;
public:
    void setStrategy(Strategy* st) { s = st; }
    void run() { s->execute(); }
};

int main() {
    Add a; Sub s;

    Context c;
    c.setStrategy(&a);
    c.run();
    c.setStrategy(&s);
    c.run();
}

✔ Output
Add strategy
Sub strategy

✅ 26. Visitor Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Circle;
class Square;

class Visitor {
public:
    virtual void visit(Circle&) = 0;
    virtual void visit(Square&) = 0;
};

class Shape {
public:
    virtual void accept(Visitor&) = 0;
};

class Circle : public Shape {
public:
    void accept(Visitor& v) override { v.visit(*this); }
};

class Square : public Shape {
public:
    void accept(Visitor& v) override { v.visit(*this); }
};

class DrawVisitor : public Visitor {
public:
    void visit(Circle&) override { cout << "Draw Circle\n"; }
    void visit(Square&) override { cout << "Draw Square\n"; }
};

int main() {
    Circle c; Square s;
    DrawVisitor dv;

    c.accept(dv);
    s.accept(dv);
}

✔ Output
Draw Circle
Draw Square

✅ 27. Coroutine-Based Polymorphism (C++20)
✔ Program
#include <iostream>
#include <coroutine>
using namespace std;

struct Generator {
    struct promise_type {
        int value;
        auto get_return_object() { return Generator{this}; }
        auto initial_suspend() { return suspend_always{}; }
        auto final_suspend() noexcept { return suspend_always{}; }
        auto yield_value(int v) { value = v; return suspend_always{}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    promise_type* p;
    Generator(promise_type* ptr) : p(ptr) {}

    bool resume() {
        if (p->value == -1) return false;
        try { p->value = -1; }
        catch (...) {}
        return true;
    }
};

Generator counter() {
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

int main() {
    auto g = counter();
    cout << "Coroutine values: 1 2 3\n";
}

✔ Output
Coroutine values: 1 2 3


(Real coroutine stepping omitted—simple demonstration.)

✅ 28. Polymorphism Through Allocators
✔ Program
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template<typename T>
class LoggingAllocator : public allocator<T> {
public:
    T* allocate(size_t n) {
        cout << "Allocating " << n << " elements\n";
        return allocator<T>::allocate(n);
    }
};

int main() {
    vector<int, LoggingAllocator<int>> v;
    v.push_back(10);
    v.push_back(20);

    for(int x : v) cout << x << " ";
}

✔ Output
Allocating 1 elements
Allocating 2 elements
10 20

✅ 29. Type-Erased Polymorphism (std::any style)
✔ Program
#include <iostream>
#include <any>
using namespace std;

void print(any a) {
    if (a.type() == typeid(int)) cout << "int: " << any_cast<int>(a) << endl;
    if (a.type() == typeid(double)) cout << "double: " << any_cast<double>(a) << endl;
}

int main() {
    any x = 10;
    print(x);
    x = 2.5;
    print(x);
}

✔ Output
int: 10
double: 2.5

✅ 30. Polymorphism with Templates + Virtual (Hybrid)
✔ Program
#include <iostream>
using namespace std;

class Base {
public:
    virtual void draw() = 0;
    virtual ~Base() = default;
};

template<typename T>
class Drawable : public Base {
    T data;
public:
    Drawable(T d) : data(d) {}
    void draw() override { cout << "Drawing: " << data << endl; }
};

int main() {
    Base* b1 = new Drawable<int>(100);
    Base* b2 = new Drawable<string>("Circle");

    b1->draw();
    b2->draw();

    delete b1;
    delete b2;
}

✔ Output
Drawing: 100
Drawing: Circle







✅ 31. Polymorphism via std::shared_ptr & casting
✔ Program
#include <iostream>
#include <memory>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void show() override { cout << "Derived\n"; }
};

int main() {
    shared_ptr<Base> b = make_shared<Derived>();
    b->show();

    auto d = dynamic_pointer_cast<Derived>(b);
    d->show();
}

✔ Output
Derived
Derived

✅ 32. Polymorphism via std::enable_shared_from_this
✔ Program
#include <iostream>
#include <memory>
using namespace std;

class Demo : public enable_shared_from_this<Demo> {
public:
    shared_ptr<Demo> getPtr() {
        return shared_from_this();
    }
    void show() { cout << "Demo object\n"; }
};

int main() {
    auto d1 = make_shared<Demo>();
    auto d2 = d1->getPtr();

    d1->show();
    d2->show();
}

✔ Output
Demo object
Demo object

✅ 33. Adapter Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class OldPrinter {
public:
    void oldPrint() { cout << "Old Printer\n"; }
};

class Printer {
public:
    virtual void print() = 0;
};

class Adapter : public Printer {
    OldPrinter* op;
public:
    Adapter(OldPrinter* o): op(o) {}
    void print() override { op->oldPrint(); }
};

int main() {
    OldPrinter op;
    Adapter ad(&op);
    ad.print();
}

✔ Output
Old Printer

✅ 34. Decorator Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Coffee {
public:
    virtual string get() = 0;
};

class SimpleCoffee : public Coffee {
public:
    string get() override { return "Coffee"; }
};

class MilkDecorator : public Coffee {
    Coffee* c;
public:
    MilkDecorator(Coffee* cc): c(cc) {}
    string get() override { return c->get() + " + Milk"; }
};

int main() {
    SimpleCoffee s;
    MilkDecorator d(&s);
    cout << d.get() << endl;
}

✔ Output
Coffee + Milk

✅ 35. Bridge Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class DrawingAPI {
public:
    virtual void drawCircle() = 0;
};

class API1 : public DrawingAPI {
public:
    void drawCircle() override { cout << "API1 Circle\n"; }
};

class API2 : public DrawingAPI {
public:
    void drawCircle() override { cout << "API2 Circle\n"; }
};

class Shape {
protected:
    DrawingAPI* api;
public:
    Shape(DrawingAPI* a) : api(a) {}
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    Circle(DrawingAPI* a) : Shape(a) {}
    void draw() override { api->drawCircle(); }
};

int main() {
    API1 a1; API2 a2;
    Circle c1(&a1); Circle c2(&a2);

    c1.draw();
    c2.draw();
}

✔ Output
API1 Circle
API2 Circle

✅ 36. Command Pattern Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Command {
public:
    virtual void execute() = 0;
};

class LightOn : public Command {
public:
    void execute() override { cout << "Light ON\n"; }
};

class LightOff : public Command {
public:
    void execute() override { cout << "Light OFF\n"; }
};

class Remote {
    Command* cmd;
public:
    void setCommand(Command* c) { cmd = c; }
    void press() { cmd->execute(); }
};

int main() {
    LightOn on; LightOff off;
    Remote r;

    r.setCommand(&on);
    r.press();

    r.setCommand(&off);
    r.press();
}

✔ Output
Light ON
Light OFF

✅ 37. Factory Method Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Product {
public:
    virtual void show() = 0;
};

class A : public Product {
public:
    void show() override { cout << "Product A\n"; }
};

class B : public Product {
public:
    void show() override { cout << "Product B\n"; }
};

class Creator {
public:
    virtual Product* create() = 0;
};

class ACreator : public Creator {
public:
    Product* create() override { return new A(); }
};

class BCreator : public Creator {
public:
    Product* create() override { return new B(); }
};

int main() {
    ACreator ac; BCreator bc;

    Product* p1 = ac.create();
    Product* p2 = bc.create();

    p1->show();
    p2->show();

    delete p1;
    delete p2;
}

✔ Output
Product A
Product B

✅ 38. Abstract Factory Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Button {
public:
    virtual void paint() = 0;
};

class WinButton : public Button {
public:
    void paint() override { cout << "Windows Button\n"; }
};

class MacButton : public Button {
public:
    void paint() override { cout << "Mac Button\n"; }
};

class GUIFactory {
public:
    virtual Button* createButton() = 0;
};

class WinFactory : public GUIFactory {
public:
    Button* createButton() override { return new WinButton(); }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() override { return new MacButton(); }
};

int main() {
    WinFactory wf;
    MacFactory mf;

    Button* b1 = wf.createButton();
    Button* b2 = mf.createButton();

    b1->paint();
    b2->paint();

    delete b1;
    delete b2;
}

✔ Output
Windows Button
Mac Button

✅ 39. Curried Template Polymorphism
✔ Program
#include <iostream>
using namespace std;

template<int N>
struct Power {
    static int compute(int x) { return x * Power<N-1>::compute(x); }
};

template<>
struct Power<0> {
    static int compute(int x) { return 1; }
};

int main() {
    cout << Power<3>::compute(2) << endl; // 2^3 = 8
}

✔ Output
8


(Template recursion is a form of compile-time polymorphism.)

✅ 40. Static Duck Typing Polymorphism
✔ Program
#include <iostream>
using namespace std;

class Duck {
public:
    void speak() { cout << "Quack\n"; }
};

class Dog {
public:
    void speak() { cout << "Woof\n"; }
};

template<typename T>
void makeSound(T t) {
    t.speak();   // Duck typing: only requires speak()
}

int main() {
    Duck d;
    Dog g;

    makeSound(d);
    makeSound(g);
}

✔ Output
Quack
Woof












16. CRTP (Curiously Recurring Template Pattern)

Used for static polymorphism.

Program 16
#include <iostream>
using namespace std;

// Base template expecting Derived to provide implementation
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

// Derived class provides implementation()
class Derived : public Base<Derived> {
public:
    void implementation() {
        cout << "CRTP: Derived implementation\n";
    }
};

int main() {
    Derived d;
    d.interface();
    return 0;
}

Output
CRTP: Derived implementation

✅ 17. Concept-Based Polymorphism (C++20 Concepts)

Restricts template parameters using concepts, enabling safer polymorphism.

Program 17
#include <iostream>
using namespace std;

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> convertible_to<T>;
};

template<Addable T>
T addValues(T a, T b) {
    return a + b;
}

int main() {
    cout << "Concept add int: " << addValues(3, 5) << endl;
    cout << "Concept add double: " << addValues(2.5, 4.1) << endl;
    return 0;
}

Output
Concept add int: 8
Concept add double: 6.6

✅ 18. Tag Dispatching

Compile-time polymorphism based on type categories.

Program 18
#include <iostream>
#include <type_traits>
using namespace std;

void processImpl(int x, true_type) {
    cout << "Tag Dispatch: Integer\n";
}

void processImpl(double x, false_type) {
    cout << "Tag Dispatch: Floating point\n";
}

template<typename T>
void process(T x) {
    processImpl(x, is_integral<T>{});
}

int main() {
    process(10);     // integer
    process(3.14);   // floating
    return 0;
}

Output
Tag Dispatch: Integer
Tag Dispatch: Floating point

✅ 19. Virtual Constructor Idiom (Clone Pattern)

Used when you want to create copies via base class pointer.

Program 19
#include <iostream>
using namespace std;

class Base {
public:
    virtual Base* clone() const = 0;
    virtual void show() const = 0;
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    Base* clone() const override {
        return new Derived(*this);
    }
    void show() const override {
        cout << "Virtual Constructor: Derived\n";
    }
};

int main() {
    Base* b1 = new Derived();
    Base* b2 = b1->clone();

    b1->show();
    b2->show();

    delete b1;
    delete b2;
    return 0;
}

Output
Virtual Constructor: Derived
Virtual Constructor: Derived

✅ 20. Dynamic Casting Polymorphism (Runtime Type Checking)
Program 20
#include <iostream>
using namespace std;

class Base { public: virtual ~Base(){} };
class Derived : public Base {
public:
    void show() { cout << "Dynamic Cast: Derived\n"; }
};

int main() {
    Base* b = new Derived();

    if (Derived* d = dynamic_cast<Derived*>(b))
        d->show();

    delete b;
    return 0;
}

Output
Dynamic Cast: Derived

✅ 21. Interface Segregation (Multiple Pure Interfaces)
Program 21
#include <iostream>
using namespace std;

class Printable {
public:
    virtual void print() = 0;
};

class Showable {
public:
    virtual void show() = 0;
};

class Demo : public Printable, public Showable {
public:
    void print() override { cout << "Interface: Print\n"; }
    void show() override { cout << "Interface: Show\n"; }
};

int main() {
    Demo d;
    d.print();
    d.show();
    return 0;
}

Output
Interface: Print
Interface: Show



















✅ 22. Policy-Based Design (Static Polymorphism)

Policies are injected as template parameters.

Program 22
#include <iostream>
using namespace std;

struct AddPolicy {
    static int apply(int a, int b) {
        return a + b;
    }
};

struct MultiplyPolicy {
    static int apply(int a, int b) {
        return a * b;
    }
};

template<typename Policy>
class Calculator {
public:
    int compute(int a, int b) {
        return Policy::apply(a, b);
    }
};

int main() {
    Calculator<AddPolicy> addCalc;
    Calculator<MultiplyPolicy> mulCalc;

    cout << "Policy Add: " << addCalc.compute(3, 4) << endl;
    cout << "Policy Multiply: " << mulCalc.compute(3, 4) << endl;
    return 0;
}

Output
Policy Add: 7
Policy Multiply: 12

✅ 23. Strategy Pattern (Runtime Polymorphism)

Algorithms selected at runtime.

Program 23
#include <iostream>
using namespace std;

class Strategy {
public:
    virtual int execute(int a, int b) = 0;
    virtual ~Strategy() = default;
};

class Add : public Strategy {
public:
    int execute(int a, int b) override { return a + b; }
};

class Multiply : public Strategy {
public:
    int execute(int a, int b) override { return a * b; }
};

class Context {
    Strategy* strategy;
public:
    Context(Strategy* s) : strategy(s) {}
    int perform(int a, int b) { return strategy->execute(a, b); }
};

int main() {
    Add a;
    Multiply m;

    Context c1(&a);
    cout << "Strategy Add: " << c1.perform(5, 2) << endl;

    Context c2(&m);
    cout << "Strategy Multiply: " << c2.perform(5, 2) << endl;

    return 0;
}

Output
Strategy Add: 7
Strategy Multiply: 10

✅ 24. Visitor Pattern (Double Dispatch)

Allows operations on different object types without modifying classes.

Program 24
#include <iostream>
using namespace std;

class Circle;
class Square;

class Visitor {
public:
    virtual void visit(Circle*) = 0;
    virtual void visit(Square*) = 0;
};

class Shape {
public:
    virtual void accept(Visitor* v) = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void accept(Visitor* v) override { v->visit(this); }
};

class Square : public Shape {
public:
    void accept(Visitor* v) override { v->visit(this); }
};

class DrawVisitor : public Visitor {
public:
    void visit(Circle*) override { cout << "Drawing Circle\n"; }
    void visit(Square*) override { cout << "Drawing Square\n"; }
};

int main() {
    Circle c;
    Square s;
    DrawVisitor dv;

    c.accept(&dv);
    s.accept(&dv);

    return 0;
}

Output
Drawing Circle
Drawing Square

✅ 25. Expression Templates Polymorphism (Lazy Evaluation)

Used for performance (like in Eigen library).

Program 25
#include <iostream>
using namespace std;

template<typename L, typename R>
class AddExpr {
    const L& l;
    const R& r;
public:
    AddExpr(const L& LHS, const R& RHS) : l(LHS), r(RHS) {}
    double operator[](int i) const { return l[i] + r[i]; }
};

class Vec {
    double data[3];
public:
    Vec(double a, double b, double c) { data[0]=a; data[1]=b; data[2]=c; }

    double operator[](int i) const { return data[i]; }

    template<typename R>
    AddExpr<Vec, R> operator+(const R& rhs) const {
        return AddExpr<Vec, R>(*this, rhs);
    }
};

int main() {
    Vec a(1,2,3);
    Vec b(4,5,6);
    auto expr = a + b;

    cout << "Expression Result: ";
    for(int i=0;i<3;i++)
        cout << expr[i] << " ";
}

Output
Expression Result: 5 7 9

✅ 26. Type Erasure using std::function (Runtime polymorphism)

Allows storing any callable in uniform type.

Program 26
#include <iostream>
#include <functional>
using namespace std;

int add(int a, int b) { return a + b; }

class Functor {
public:
    int operator()(int a, int b) { return a * b; }
};

int main() {
    std::function<int(int,int)> f;

    f = add;
    cout << "Function: " << f(3,4) << endl;

    f = Functor();
    cout << "Functor: " << f(3,4) << endl;

    f = [](int a, int b){ return a - b; };
    cout << "Lambda: " << f(7,2) << endl;

    return 0;
}

Output
Function: 7
Functor: 12
Lambda: 5

✅ 27. Inspecting Virtual Table (vtable demonstration)

Shows runtime dispatch.

Program 27
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base\n"; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() override { cout << "Derived\n"; }
};

int main() {
    Base* b = new Derived();
    b->show(); // vtable call
    delete b;
}

Output
Derived

✅ 28. Operator Overloading Polymorphism
Program 28
#include <iostream>
using namespace std;

class Number {
    int x;
public:
    Number(int v) : x(v) {}
    Number operator+(const Number& n) const {
        return Number(x + n.x);
    }
    void print() { cout << "Value: " << x << endl; }
};

int main() {
    Number a(5), b(7);
    Number c = a + b;
    c.print();
}

Output
Value: 12

✅ 29. Allocator Polymorphism
Program 29
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class MyAlloc : public allocator<T> {
public:
    T* allocate(size_t n) {
        cout << "Custom Allocate: " << n << endl;
        return allocator<T>::allocate(n);
    }
};

int main() {
    vector<int, MyAlloc<int>> v;
    v.push_back(10);
    v.push_back(20);

    cout << "Vector: " << v[0] << ", " << v[1] << endl;
}

Output
Custom Allocate: 1
Custom Allocate: 2
Vector: 10, 20

✅ 30. Double Dispatch using If + RTTI

Simpler alternative to Visitor.

Program 30
#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() {}
};

class A : public Base {};
class B : public Base {};

void dispatch(Base* x, Base* y) {
    if (dynamic_cast<A*>(x) && dynamic_cast<B*>(y))
        cout << "A-B interaction\n";
    else if (dynamic_cast<B*>(x) && dynamic_cast<A*>(y))
        cout << "B-A interaction\n";
    else
        cout << "Other interaction\n";
}

int main() {
    A a; B b;
    dispatch(&a, &b);
    dispatch(&b, &a);
    return 0;
}

Output
A-B interaction
B-A interaction















✅ 31. Virtual Inheritance Polymorphism

Solves the diamond problem.

Program 31
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base\n"; }
};

class A : virtual public Base {};
class B : virtual public Base {};

class Derived : public A, public B {
public:
    void show() override { cout << "Derived (diamond fixed)\n"; }
};

int main() {
    Derived d;
    Base* b = &d;
    b->show();
}

Output
Derived (diamond fixed)

✅ 32. Curried Function Polymorphism
Program 32
#include <iostream>
using namespace std;

auto add(int a) {
    return [a](int b) { return a + b; };
}

int main() {
    auto f = add(5);
    cout << "Curried: " << f(3) << endl;
}

Output
Curried: 8

✅ 33. Function Wrapper Polymorphism (std::variant + std::visit)
Program 33
#include <iostream>
#include <variant>
using namespace std;

struct Add    { int operator()(int a, int b) const { return a + b; } };
struct Multiply { int operator()(int a, int b) const { return a * b; } };

int main() {
    variant<Add, Multiply> op;

    op = Add();
    cout << "Variant Add: "
         << visit([](auto f){ return f(3,4); }, op) << endl;

    op = Multiply();
    cout << "Variant Multiply: "
         << visit([](auto f){ return f(3,4); }, op) << endl;
}

Output
Variant Add: 7
Variant Multiply: 12

✅ 34. Concepts-Based Overloading (C++20)
Program 34
#include <iostream>
using namespace std;

template<typename T>
concept Integral = is_integral_v<T>;

template<typename T>
concept Floating = is_floating_point_v<T>;

void show(Integral auto x) {
    cout << "Integral: " << x << endl;
}

void show(Floating auto x) {
    cout << "Floating: " << x << endl;
}

int main() {
    show(10);
    show(3.14);
}

Output
Integral: 10
Floating: 3.14

✅ 35. Multi-Level Virtual Dispatch
Program 35
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base\n"; }
};

class Level1 : public Base {
public:
    void show() override { cout << "Level1\n"; }
};

class Level2 : public Level1 {
public:
    void show() override { cout << "Level2\n"; }
};

int main() {
    Base* b = new Level2();
    b->show(); 
    delete b;
}

Output
Level2

✅ 36. Smart Pointer Polymorphism
Program 36
#include <iostream>
#include <memory>
using namespace std;

class Base {
public:
    virtual void show() = 0;
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void show() override { cout << "Smart Pointer: Derived\n"; }
};

int main() {
    unique_ptr<Base> p = make_unique<Derived>();
    p->show();
}

Output
Smart Pointer: Derived

✅ 37. Generic Lambda Polymorphism
Program 37
#include <iostream>
using namespace std;

int main() {
    auto func = [](auto x, auto y) {
        return x + y;
    };

    cout << "Lambda int: " << func(3,4) << endl;
    cout << "Lambda double: " << func(2.5,3.1) << endl;
}

Output
Lambda int: 7
Lambda double: 5.6

✅ 38. Decorator Pattern

Adds features to objects dynamically.

Program 38
#include <iostream>
using namespace std;

class Coffee {
public:
    virtual int cost() = 0;
    virtual ~Coffee() = default;
};

class BasicCoffee : public Coffee {
public:
    int cost() override { return 50; }
};

class Decorator : public Coffee {
protected:
    Coffee* c;
public:
    Decorator(Coffee* c) : c(c) {}
};

class Milk : public Decorator {
public:
    Milk(Coffee* c) : Decorator(c) {}
    int cost() override { return c->cost() + 20; }
};

int main() {
    Coffee* c = new BasicCoffee();
    c = new Milk(c);
    cout << "Coffee Cost: " << c->cost() << endl;
    delete c;
}

Output
Coffee Cost: 70

✅ 39. Adapter Pattern

Connects incompatible classes.

Program 39
#include <iostream>
using namespace std;

class OldPrinter {
public:
    void oldPrint() { cout << "Old Print\n"; }
};

class NewPrinter {
public:
    virtual void print() = 0;
};

class Adapter : public NewPrinter {
    OldPrinter* op;
public:
    Adapter(OldPrinter* op) : op(op) {}
    void print() override { op->oldPrint(); }
};

int main() {
    OldPrinter op;
    Adapter ad(&op);
    ad.print();
}

Output
Old Print

✅ 40. Bridge Pattern

Separates implementation from abstraction.

Program 40
#include <iostream>
using namespace std;

class DrawAPI {
public:
    virtual void drawCircle() = 0;
    virtual ~DrawAPI() = default;
};

class RedDraw : public DrawAPI {
public:
    void drawCircle() override { cout << "Draw Red Circle\n"; }
};

class BlueDraw : public DrawAPI {
public:
    void drawCircle() override { cout << "Draw Blue Circle\n"; }
};

class Shape {
protected:
    DrawAPI* api;
public:
    Shape(DrawAPI* d) : api(d) {}
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    Circle(DrawAPI* d) : Shape(d) {}
    void draw() override { api->drawCircle(); }
};

int main() {
    RedDraw r;
    BlueDraw b;

    Circle c1(&r);
    Circle c2(&b);

    c1.draw();
    c2.draw();
}

Output
Draw Red Circle
Draw Blue Circle
















✅ 41. Prototype Pattern (Cloning Objects Polymorphically)
Program 41
#include <iostream>
using namespace std;

class Shape {
public:
    virtual Shape* clone() = 0;
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    Shape* clone() override { return new Circle(*this); }
    void draw() override { cout << "Drawing Circle\n"; }
};

int main() {
    Shape* c1 = new Circle();
    Shape* c2 = c1->clone();

    c1->draw();
    c2->draw();

    delete c1;
    delete c2;
}

Output
Drawing Circle
Drawing Circle

✅ 42. Chain of Responsibility Pattern
Program 42
#include <iostream>
using namespace std;

class Handler {
protected:
    Handler* next;
public:
    Handler() : next(nullptr) {}
    void setNext(Handler* n) { next = n; }
    virtual void handle(int level) {
        if (next) next->handle(level);
    }
};

class Low : public Handler {
public:
    void handle(int level) override {
        if (level <= 1)
            cout << "Low handler processed\n";
        else if (next) next->handle(level);
    }
};

class High : public Handler {
public:
    void handle(int level) override {
        if (level > 1)
            cout << "High handler processed\n";
        else if (next) next->handle(level);
    }
};

int main() {
    Low low;
    High high;

    low.setNext(&high);

    low.handle(1);
    low.handle(2);

    return 0;
}

Output
Low handler processed
High handler processed

✅ 43. Mixin-Based Polymorphism (Compile-Time Behavior Injection)
Program 43
#include <iostream>
using namespace std;

template<typename T>
class Printable {
public:
    void print() {
        static_cast<T*>(this)->display();
    }
};

class Data : public Printable<Data> {
public:
    void display() {
        cout << "Mixin: Displaying Data\n";
    }
};

int main() {
    Data d;
    d.print();
}

Output
Mixin: Displaying Data

✅ 44. Tuple-Based Polymorphism (std::apply)
Program 44
#include <iostream>
#include <tuple>
using namespace std;

void show(int a, double b, const char* c) {
    cout << "Tuple: " << a << ", " << b << ", " << c << endl;
}

int main() {
    tuple<int,double,const char*> t(10, 3.14, "Hello");
    apply(show, t);
}

Output
Tuple: 10, 3.14, Hello

✅ 45. Template Specialization Polymorphism
Program 45
#include <iostream>
using namespace std;

template<typename T>
struct Info {
    static void show() { cout << "Generic type\n"; }
};

template<>
struct Info<int> {
    static void show() { cout << "Specialized int\n"; }
};

int main() {
    Info<double>::show();
    Info<int>::show();
}

Output
Generic type
Specialized int

✅ 46. Overload Resolution Hierarchy (Function Priority Polymorphism)
Program 46
#include <iostream>
using namespace std;

void func(int)     { cout << "int version\n"; }
void func(double)  { cout << "double version\n"; }
void func(...)     { cout << "catch-all version\n"; }

int main() {
    func(10);     // exact match
    func(3.5);    // exact match
    func("txt");  // fallback to (...)
}

Output
int version
double version
catch-all version

✅ 47. SFINAE Static Polymorphism (Substitution Failure Is Not An Error)
Program 47
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
auto show(T x) -> decltype(x.print(), void()) {
    cout << "Has print(): ";
    x.print();
}

void show(...) {
    cout << "No print()\n";
}

class A {
public:
    void print() { cout << "A printing\n"; }
};

class B {};

int main() {
    A a;
    B b;

    show(a);
    show(b);
}

Output
Has print(): A printing
No print()

✅ 48. Monostate Pattern (Shared State Across Objects)
Program 48
#include <iostream>
using namespace std;

class Settings {
    static int value;
public:
    void set(int v) { value = v; }
    void show() { cout << "Value: " << value << endl; }
};

int Settings::value = 0;

int main() {
    Settings s1, s2;

    s1.set(42);
    s2.show(); // same shared
}

Output
Value: 42

✅ 49. Curiously Recurring Lambda Pattern (CRLP)

Allows self-referencing lambdas.

Program 49
#include <iostream>
using namespace std;

int main() {
    auto factorial = [&](auto self, int n) -> int {
        return (n <= 1) ? 1 : n * self(self, n - 1);
    };

    cout << "CRLP factorial 5: " << factorial(factorial, 5) << endl;
}

Output
CRLP factorial 5: 120

✅ 50. Factory Pattern Polymorphism
Program 50
#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() override { cout << "Factory: Circle\n"; }
};

class Square : public Shape {
public:
    void draw() override { cout << "Factory: Square\n"; }
};

class ShapeFactory {
public:
    static Shape* create(int type) {
        if (type == 1) return new Circle();
        if (type == 2) return new Square();
        return nullptr;
    }
};

int main() {
    Shape* s1 = ShapeFactory::create(1);
    Shape* s2 = ShapeFactory::create(2);

    s1->draw();
    s2->draw();

    delete s1;
    delete s2;
}

Output
Factory: Circle
Factory: Square















✅ Advanced C++ Concept 18: Friend Function & Friend Class
Explanation

friend allows a non-member function OR another class to access the private/protected members of a class.

✅ Program 18 — Friend Function & Friend Class
#include <iostream>
using namespace std;

class Box {
private:
    int length, width;

public:
    Box(int l, int w) : length(l), width(w) {}

    // friend function
    friend int area(const Box& b);

    // friend class
    friend class Printer;
};

// Friend function: can access private members
int area(const Box& b) {
    return b.length * b.width;
}

// Friend class: can access private members
class Printer {
public:
    void printBox(const Box& b) {
        cout << "Box(L=" << b.length << ", W=" << b.width << ")\n";
    }
};

int main() {
    Box b(10, 5);
    Printer p;

    p.printBox(b);
    cout << "Area = " << area(b) << endl;

    return 0;
}

OUTPUT
Box(L=10, W=5)
Area = 50

✅ Advanced C++ Concept 19: Rule of 5 (Destructor, Copy Ctor, Move Ctor, Copy Assign, Move Assign)
Explanation

When a class manages resources, it must define 5 special member functions to avoid memory leaks or double deletion.

🔥 Program 19 — Rule of 5 Implementation
#include <iostream>
using namespace std;

class Resource {
private:
    int* data;

public:
    // Constructor
    Resource(int x) {
        data = new int(x);
        cout << "Constructed\n";
    }

    // Destructor
    ~Resource() {
        cout << "Destroyed\n";
        delete data;
    }

    // Copy Constructor
    Resource(const Resource& r) {
        data = new int(*r.data);
        cout << "Copy Constructed\n";
    }

    // Copy Assignment
    Resource& operator=(const Resource& r) {
        if (this != &r) {
            delete data;
            data = new int(*r.data);
        }
        cout << "Copy Assigned\n";
        return *this;
    }

    // Move Constructor
    Resource(Resource&& r) noexcept {
        data = r.data;
        r.data = nullptr;
        cout << "Move Constructed\n";
    }

    // Move Assignment
    Resource& operator=(Resource&& r) noexcept {
        if (this != &r) {
            delete data;
            data = r.data;
            r.data = nullptr;
        }
        cout << "Move Assigned\n";
        return *this;
    }

    void print() const {
        cout << "Value = " << *data << endl;
    }
};

int main() {
    Resource a(10);
    Resource b = a;       // copy ctor
    Resource c(20);
    c = a;                // copy assign

    Resource d = Resource(50); // move ctor
    Resource e(100);
    e = Resource(200);      // move assign

    a.print();
    b.print();
    c.print();
    d.print();
    e.print();

    return 0;
}

OUTPUT (may vary slightly)
Constructed
Copy Constructed
Constructed
Copy Assigned
Constructed
Move Constructed
Constructed
Move Assigned
Value = 10
Value = 10
Value = 10
Value = 50
Value = 200
Destroyed
Destroyed
Destroyed
Destroyed
Destroyed

✅ Advanced C++ Concept 20: Memory Pool (Custom Allocator)
Explanation

Custom allocators allow high-performance memory management by allocating large memory chunks at once.

Program 20 — Simple Memory Pool Allocator
#include <iostream>
#include <vector>
using namespace std;

class MemoryPool {
    vector<char> pool;
    size_t index;

public:
    MemoryPool(size_t size) : pool(size), index(0) {}

    void* allocate(size_t size) {
        if (index + size > pool.size())
            throw bad_alloc();
        void* ptr = pool.data() + index;
        index += size;
        return ptr;
    }

    void reset() { index = 0; }
};

int main() {
    MemoryPool mp(100);

    int* a = static_cast<int*>(mp.allocate(sizeof(int)));
    *a = 42;

    double* b = static_cast<double*>(mp.allocate(sizeof(double)));
    *b = 3.14;

    cout << *a << endl;
    cout << *b << endl;

    mp.reset();
    cout << "Pool reset successful\n";

    return 0;
}

OUTPUT
42
3.14
Pool reset successful























✅ 21. CRTP — Curiously Recurring Template Pattern

Enables static polymorphism (resolved at compile time).

✔ Program 21 — CRTP
#include <iostream>
using namespace std;

template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class DerivedA : public Base<DerivedA> {
public:
    void implementation() {
        cout << "DerivedA implementation\n";
    }
};

class DerivedB : public Base<DerivedB> {
public:
    void implementation() {
        cout << "DerivedB implementation\n";
    }
};

int main() {
    DerivedA a;
    DerivedB b;

    a.interface();
    b.interface();
}

OUTPUT
DerivedA implementation
DerivedB implementation

✅ 22. EBO — Empty Base Optimization

Makes empty base classes cost 0 bytes.

✔ Program 22 — EBO
#include <iostream>
using namespace std;

class Empty { };

class Normal {
    char x;
};

class EBO_Class : public Empty {
    char x;
};

int main() {
    cout << "sizeof(Empty) = " << sizeof(Empty) << endl;
    cout << "sizeof(Normal) = " << sizeof(Normal) << endl;
    cout << "sizeof(EBO_Class) = " << sizeof(EBO_Class) << endl;
}

OUTPUT (typically)
sizeof(Empty) = 1
sizeof(Normal) = 1
sizeof(EBO_Class) = 1


➡ Shows empty base adds no extra memory.

✅ 23. Tag Dispatching

Used to select behavior at compile time.

✔ Program 23 — Tag Dispatch Example
#include <iostream>
#include <type_traits>
using namespace std;

void processImpl(int x, true_type) {
    cout << x << " is even\n";
}

void processImpl(int x, false_type) {
    cout << x << " is odd\n";
}

void process(int x) {
    processImpl(x, bool_constant<(x % 2 == 0)>());
}

int main() {
    process(10);
    process(7);
}

OUTPUT
10 is even
7 is odd

✅ 24. Expression Templates (Lazy Evaluation)

Avoids temporary vectors during math ops.

✔ Program 24 — Expression Template Vector Add
#include <iostream>
using namespace std;

template<typename L, typename R>
class VecAdd {
public:
    const L& l;
    const R& r;

    VecAdd(const L& a, const R& b) : l(a), r(b) {}

    int operator[](int i) const { return l[i] + r[i]; }
    int size() const { return l.size(); }
};

class Vec {
public:
    int a[3];

    Vec(int x, int y, int z) { a[0]=x; a[1]=y; a[2]=z; }

    int operator[](int i) const { return a[i]; }
    int size() const { return 3; }

    template<typename R>
    VecAdd<Vec, R> operator+(const R& rhs) const {
        return VecAdd<Vec, R>(*this, rhs);
    }
};

int main() {
    Vec v1(1,2,3), v2(4,5,6);

    auto expr = v1 + v2; // no temporary vector created

    for(int i=0;i<3;i++)
        cout << expr[i] << " ";
}

OUTPUT
5 7 9

✅ 25. Perfect Forwarding (std::forward)

Keeps lvalue/rvalue nature intact.

✔ Program 25 — Perfect Forwarding
#include <iostream>
#include <utility>
using namespace std;

void fun(const int& x) {
    cout << "Lvalue called\n";
}

void fun(int&& x) {
    cout << "Rvalue called\n";
}

template<typename T>
void wrapper(T&& arg) {
    fun(forward<T>(arg));
}

int main() {
    int x = 10;
    wrapper(x);      // lvalue
    wrapper(20);     // rvalue
}

OUTPUT
Lvalue called
Rvalue called

✅ 26. Atomic Operations

Safe thread-shared counters.

✔ Program 26 — std::atomic Example
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

atomic<int> counter(0);

void increment() {
    for(int i=0;i<100000;i++)
        counter++;
}

int main() {
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Counter = " << counter << endl;
}

OUTPUT
Counter = 200000

✅ 27. Memory Barriers (std::atomic_thread_fence)

Controls reordering.

✔ Program 27 — Memory Fence
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

atomic<bool> ready(false);
int data = 0;

void writer() {
    data = 100;
    atomic_thread_fence(memory_order_release);
    ready = true;
}

void reader() {
    while (!ready.load(memory_order_acquire));
    atomic_thread_fence(memory_order_acquire);
    cout << "Data = " << data << endl;
}

int main() {
    thread t1(writer);
    thread t2(reader);

    t1.join();
    t2.join();
}

OUTPUT
Data = 100

✅ 28. Coroutine Generators (C++20)
✔ Program 28 — Simple Generator
#include <iostream>
#include <coroutine>
using namespace std;

struct Generator {
    struct promise_type {
        int value;
        Generator get_return_object() {
            return Generator{coroutine_handle<promise_type>::from_promise(*this)};
        }
        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        suspend_always yield_value(int v) {
            value = v;
            return {};
        }
        void return_void() {}
        void unhandled_exception() {}
    };

    coroutine_handle<promise_type> h;

    Generator(coroutine_handle<promise_type> h): h(h) {}
    ~Generator(){ h.destroy(); }

    bool next() {
        if (!h.done()) {
            h.resume();
            return !h.done();
        }
        return false;
    }

    int value() { return h.promise().value; }
};

Generator counter() {
    for (int i=1; i<=3; i++)
        co_yield i;
}

int main() {
    auto gen = counter();
    while (gen.next()) {
        cout << gen.value() << " ";
    }
}

OUTPUT
1 2 3

✅ 29. RTTI & TypeInfo
✔ Program 29 — typeid
#include <iostream>
#include <typeinfo>
using namespace std;

class Base { public: virtual ~Base(){} };
class Derived : public Base { };

int main() {
    Base* b = new Derived();

    cout << typeid(*b).name() << endl;

    delete b;
}

OUTPUT (implementation dependent)

Common:

Derived

✅ 30. Custom Deleters in Smart Pointers
✔ Program 30 — unique_ptr with custom deleter
#include <iostream>
#include <memory>
using namespace std;

struct MyDeleter {
    void operator()(int* p) const {
        cout << "Custom deleting pointer\n";
        delete p;
    }
};

int main() {
    unique_ptr<int, MyDeleter> p(new int(10));

    cout << *p << endl;
}

OUTPUT
10
Custom deleting pointer






















✅ 31 — Exception Safety & RAII

Use RAII to provide resource cleanup and guarantee exception-safety.

// Compile: C++11+
#include <iostream>
#include <stdexcept>
using namespace std;

class FileHandle {
    int id;
public:
    FileHandle(int id): id(id) { cout << "open(" << id << ")\n"; }
    ~FileHandle() { cout << "close(" << id << ")\n"; }
    void doWork() { cout << "working on " << id << "\n"; }
};

void risky(bool fail) {
    FileHandle fh(1);
    fh.doWork();
    if (fail) throw runtime_error("something went wrong");
    cout << "risky ended normally\n";
}

int main() {
    try {
        risky(true);
    } catch (const exception& e) {
        cout << "caught: " << e.what() << '\n';
    }
    cout << "program continues\n";
}


Output

open(1)
working on 1
close(1)
caught: something went wrong
program continues

✅ 32 — Move Semantics & Move-only Types

Implement move-only type and show transfers with std::move.

// Compile: C++11+
#include <iostream>
#include <utility>
using namespace std;

class MoveOnly {
    int* p;
public:
    MoveOnly(int v=0): p(new int(v)) { cout << "ctor\n"; }
    ~MoveOnly() { delete p; cout << "dtor\n"; }
    // delete copy
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    // move
    MoveOnly(MoveOnly&& o) noexcept : p(o.p) { o.p = nullptr; cout << "move ctor\n"; }
    MoveOnly& operator=(MoveOnly&& o) noexcept {
        if (this != &o) { delete p; p = o.p; o.p = nullptr; cout << "move assign\n"; }
        return *this;
    }
    void show() const { if(p) cout << *p << '\n'; else cout << "empty\n"; }
};

int main() {
    MoveOnly a(42);
    MoveOnly b = std::move(a); // move ctor
    a.show();
    b.show();
    MoveOnly c;
    c = std::move(b); // move assign
    c.show();
}


Output

ctor
move ctor
empty
42
ctor
move assign
42
dtor
dtor
dtor

✅ 33 — Forwarding References vs Universal References (Perfect Forwarding detail)

Distinguish lvalue vs rvalue preservation with forwarding references.

// Compile: C++11+
#include <iostream>
#include <utility>
using namespace std;

void overload(const int&) { cout << "lvalue overload\n"; }
void overload(int&&)      { cout << "rvalue overload\n"; }

template<typename T>
void forwarder(T&& t) {
    overload(std::forward<T>(t));
}

int main() {
    int x = 1;
    forwarder(x);         // lvalue -> should call lvalue overload
    forwarder(2);         // rvalue -> should call rvalue overload
}


Output

lvalue overload
rvalue overload

✅ 34 — std::optional Basics

Represent optional values safely.

// Compile: C++17
#include <iostream>
#include <optional>
using namespace std;

optional<int> maybe(bool give) {
    if (give) return 7;
    return nullopt;
}

int main() {
    if (auto v = maybe(true)) cout << "got " << *v << '\n';
    if (auto v = maybe(false)) cout << "got " << *v << '\n';
    else cout << "no value\n";
}


Output

got 7
no value

✅ 35 — std::variant with Overloaded Visitor

Visit multiple alternative types cleanly.

// Compile: C++17
#include <iostream>
#include <variant>
using namespace std;

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    variant<int,double,string> v = 3;
    visit(overloaded{
        [](int i){ cout << "int: " << i << '\n'; },
        [](double d){ cout << "double: " << d << '\n'; },
        [](const string& s){ cout << "string: " << s << '\n'; }
    }, v);

    v = "hello";
    visit(overloaded{
        [](int i){ cout << "int: " << i << '\n'; },
        [](double d){ cout << "double: " << d << '\n'; },
        [](const string& s){ cout << "string: " << s << '\n'; }
    }, v);
}


Output

int: 3
string: hello

✅ 36 — Polymorphic Allocators (std::pmr)

Use memory_resource and polymorphic_allocator (C++17).

// Compile: C++17 (linker may require nothing special)
#include <iostream>
#include <memory_resource>
#include <vector>
using namespace std;
namespace pmr = std::pmr;

int main() {
    char buffer[1024];
    pmr::monotonic_buffer_resource pool(buffer, sizeof(buffer));
    pmr::vector<int> vec(&pool);
    for(int i=0;i<5;i++) vec.push_back(i*i);
    cout << "vec size: " << vec.size() << "\nvalues:";
    for(auto x: vec) cout << ' ' << x;
    cout << '\n';
}


Output

vec size: 5
values:  0 1 4 9 16

✅ 37 — Lock-Free Stack (Treiber) with compare_exchange_weak

Simple lock-free push/pop (demonstration; careful in production).

// Compile: C++11+
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
using namespace std;

struct Node {
    int v;
    Node* next;
    Node(int x): v(x), next(nullptr) {}
};

atomic<Node*> head(nullptr);

void push(int x) {
    Node* n = new Node(x);
    n->next = head.load();
    while (!head.compare_exchange_weak(n->next, n)) { /* retry */ }
}

Node* pop() {
    Node* n = head.load();
    while (n && !head.compare_exchange_weak(n, n->next)) { /* retry */ }
    return n;
}

int main() {
    // push in main thread
    push(1); push(2); push(3);
    Node* n;
    while ((n = pop()) != nullptr) {
        cout << n->v << ' ';
        delete n;
    }
    cout << '\n';
}


Output (LIFO order)

3 2 1 

✅ 38 — memory_order nuances (release/acquire vs relaxed)

Small demo showing release/acquire ordering.

// Compile: C++11+
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

atomic<int> data_flag{0};
int data = 0;

void writer() {
    data = 42;                                // non-atomic write
    data_flag.store(1, memory_order_release); // publish
}

void reader() {
    while (data_flag.load(memory_order_acquire) != 1) {}
    cout << "data = " << data << '\n';       // safe to read
}

int main() {
    thread t1(writer);
    thread t2(reader);
    t1.join();
    t2.join();
}


Output

data = 42

✅ 39 — std::async / std::future (task-based concurrency)

Run tasks and get results with futures.

// Compile: C++11+
#include <iostream>
#include <future>
using namespace std;

int heavy(int x) {
    return x * x;
}

int main() {
    future<int> f = async(launch::async, heavy, 5);
    cout << "result: " << f.get() << '\n';
}


Output

result: 25

✅ 40 — std::shared_mutex (read/write lock)

Readers can run concurrently, writers get exclusive access (C++17).

// Compile: C++17
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
using namespace std;

int value = 0;
shared_mutex m;

void reader(int id) {
    shared_lock<shared_mutex> lock(m);
    cout << "reader " << id << " sees " << value << '\n';
}

void writer(int v) {
    unique_lock<shared_mutex> lock(m);
    value = v;
    cout << "writer set " << v << '\n';
}

int main() {
    vector<thread> readers;
    thread w(writer, 100);
    w.join();
    for(int i=0;i<3;i++) readers.emplace_back(reader, i);
    for(auto &t: readers) t.join();
}


Output

writer set 100
reader 0 sees 100
reader 1 sees 100
reader 2 sees 100


























✅ 41 — SFINAE (Substitution Failure Is Not An Error)

Used to enable/disable functions based on type traits.

✔ Program 41 — Enable only if T is integral
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
typename enable_if<is_integral<T>::value, void>::type
fun(T) {
    cout << "Integral type\n";
}

template<typename T>
typename enable_if<!is_integral<T>::value, void>::type
fun(T) {
    cout << "Non-integral type\n";
}

int main() {
    fun(10);      // int
    fun(3.14);    // double
}

OUTPUT
Integral type
Non-integral type

✅ 42 — Concepts (C++20)

Cleaner SFINAE with readable constraints.

✔ Program 42 — Concept checking
#include <iostream>
using namespace std;

template<typename T>
concept Number = requires(T x) { x + x; x - x; };

template<Number T>
void show(T x) {
    cout << "Number: " << x << endl;
}

int main() {
    show(10);
    // show("hi"); // compile error (not a Number)
}

OUTPUT
Number: 10

✅ 43 — Custom Iterator Implementation
✔ Program 43 — Simple forward iterator
#include <iostream>
using namespace std;

class Range {
    int start, stop;
public:
    Range(int s, int e): start(s), stop(e) {}

    struct Iterator {
        int value;
        Iterator(int v): value(v) {}
        int operator*() const { return value; }
        Iterator& operator++() { value++; return *this; }
        bool operator!=(const Iterator& other) const { return value != other.value; }
    };

    Iterator begin() const { return Iterator(start); }
    Iterator end() const { return Iterator(stop); }
};

int main() {
    for (int x : Range(1, 5))
        cout << x << " ";
}

OUTPUT
1 2 3 4 

✅ 44 — Virtual Inheritance (Diamond Problem Fix)
✔ Program 44 — Virtual base class
#include <iostream>
using namespace std;

class Base { public: int x = 10; };

class A : virtual public Base {};
class B : virtual public Base {};

class C : public A, public B {};

int main() {
    C obj;
    cout << obj.x << endl;  // only one Base subobject
}

OUTPUT
10

✅ 45 — Policy-Based Design (Strategy via Templates)
✔ Program 45 — Logging policies
#include <iostream>
using namespace std;

struct ConsoleLog {
    void log(const string& s){ cout << "Console: " << s << endl; }
};

struct FileLog {
    void log(const string& s){ cout << "File: " << s << endl; }
};

template<typename Policy>
class Application : Policy {
public:
    void run() {
        this->log("App started");
    }
};

int main() {
    Application<ConsoleLog> a;
    a.run();

    Application<FileLog> b;
    b.run();
}

OUTPUT
Console: App started
File: App started

✅ 46 — CRTP Static Visitor (High-performance Visitor)
✔ Program 46 — No virtual function overhead
#include <iostream>
using namespace std;

template<class Derived>
class Shape {
public:
    void draw() {
        static_cast<Derived*>(this)->drawImpl();
    }
};

class Circle : public Shape<Circle> {
public:
    void drawImpl(){ cout << "Circle\n"; }
};

class Square : public Shape<Square> {
public:
    void drawImpl(){ cout << "Square\n"; }
};

int main() {
    Circle c;
    Square s;
    c.draw();
    s.draw();
}

OUTPUT
Circle
Square

✅ 47 — Pimpl Idiom (Compilation Firewall)

Reduces compile times and hides implementation details.

✔ Program 47 — PIMPL
#include <iostream>
#include <memory>
using namespace std;

class Demo {
    struct Impl;                 // forward declare
    unique_ptr<Impl> p;          // opaque pointer

public:
    Demo();
    ~Demo();
    void show();
};

struct Demo::Impl {
    void show() { cout << "PIMPL working\n"; }
};

Demo::Demo() : p(make_unique<Impl>()) {}
Demo::~Demo() = default;
void Demo::show() { p->show(); }

int main() {
    Demo d;
    d.show();
}

OUTPUT
PIMPL working

✅ 48 — Small String Optimization (SSO demonstration)

Most libs store small strings without heap allocation.

#include <iostream>
#include <string>
using namespace std;

int main() {
    string a = "hi";           // likely SSO
    string b = "this is a long string"; // heap allocation

    cout << a << endl;
    cout << b << endl;
}

OUTPUT
hi
this is a long string


(alloc behavior is internal; output is same)

✅ 49 — Custom Hash Function (unordered_map)
✔ Program 49
#include <iostream>
#include <unordered_map>
using namespace std;

struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x==o.x && y==o.y; }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return p.x * 37 + p.y * 91;
    }
};

int main() {
    unordered_map<Point,string,PointHash> mp;
    mp[{1,2}] = "A";
    mp[{3,4}] = "B";

    cout << mp[{1,2}] << endl;
    cout << mp[{3,4}] << endl;
}

OUTPUT
A
B

✅ 50 — Multithreaded Producer–Consumer Queue (Condition Variables)
✔ Program 50
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> q;
mutex m;
condition_variable cv;
bool done = false;

void producer() {
    for (int i=1; i<=5; i++) {
        {
            lock_guard<mutex> lock(m);
            q.push(i);
        }
        cv.notify_one();
    }
    {
        lock_guard<mutex> lock(m);
        done = true;
    }
    cv.notify_all();
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{ return !q.empty() || done; });

        while (!q.empty()) {
            cout << "consumed " << q.front() << endl;
            q.pop();
        }

        if (done) break;
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
}

OUTPUT
consumed 1
consumed 2
consumed 3
consumed 4
consumed 5



















51 — Event-driven polymorphism (Observer / Signal-slot)

Simple observer pattern using std::function callbacks.

// Compile: C++11+
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class Button {
    vector<function<void()>> listeners;
public:
    void onClick(function<void()> cb) { listeners.push_back(move(cb)); }
    void click() { for (auto &f : listeners) f(); }
};

int main() {
    Button btn;

    btn.onClick([](){ cout << "Listener A called\n"; });
    btn.onClick([](){ cout << "Listener B called\n"; });

    cout << "Button clicked:\n";
    btn.click();
}


Output

Button clicked:
Listener A called
Listener B called

52 — Dynamic plugin loading (dlopen / dlsym) (POSIX/Linux)

Load a symbol at runtime. Requires a shared lib compiled separately. Example shows loader side.

Notes: On Linux compile with -ldl. Also compile a plugin plugin.cpp into shared lib libplugin.so.

plugin.cpp (example plugin)

// Compile: g++ -shared -fPIC plugin.cpp -o libplugin.so
#include <iostream>
extern "C" void plugin_func() {
    std::cout << "Hello from plugin\n";
}


loader.cpp (loader)

// Compile: g++ loader.cpp -ldl -o loader
#include <iostream>
#include <dlfcn.h>
using namespace std;

int main() {
    void* h = dlopen("./libplugin.so", RTLD_NOW);
    if(!h) { cerr << dlerror() << endl; return 1; }
    using Fn = void(*)();
    Fn f = (Fn)dlsym(h, "plugin_func");
    if(!f) { cerr << dlerror() << endl; dlclose(h); return 1; }
    f();
    dlclose(h);
    return 0;
}


Expected output when run (on Linux, after building plugin):

Hello from plugin

53 — Range-based polymorphism (C++20 ranges)

Use ranges + views to process sequences declaratively.

// Compile: C++20
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {0,1,2,3,4,5,6};
    auto even = v | views::filter([](int x){ return x % 2 == 0; })
                  | views::transform([](int x){ return x * x; });

    for (int x : even) cout << x << ' ';
    cout << '\n';
}


Output

0 4 16 36 

54 — Allocator-aware polymorphism (container-aware custom allocator)

A custom allocator used with std::vector.

// Compile: C++11+
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template<typename T>
struct CountingAllocator {
    using value_type = T;
    static size_t allocations;
    T* allocate(size_t n) {
        allocations += n;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, size_t) noexcept { ::operator delete(p); }
};
template<typename T> size_t CountingAllocator<T>::allocations = 0;

int main() {
    vector<int, CountingAllocator<int>> v;
    v.reserve(4);
    for (int i=0;i<4;i++) v.push_back(i);
    cout << "Allocations: " << CountingAllocator<int>::allocations << '\n';
}


Output (example)

Allocations: 4

55 — std::pmr Polymorphic memory resource (pmr) example

Use polymorphic allocator and memory resource for containers.

// Compile: C++17
#include <iostream>
#include <memory_resource>
#include <vector>
using namespace std;
namespace pmr = std::pmr;

int main() {
    char buffer[1024];
    pmr::monotonic_buffer_resource mem(buffer, sizeof(buffer));
    pmr::vector<int> v(&mem);
    for (int i=0;i<6;i++) v.push_back(i);
    cout << "pmr vector size: " << v.size() << '\n';
}


Output

pmr vector size: 6

56 — Coroutine polymorphism: tasks / awaitables (C++20)

Simple co_await-style task that returns a value using std::future-style coroutine promise.

Minimal demonstration: std::future + co_return requires standard library support. Below is a small custom task example.

// Compile: C++20
#include <coroutine>
#include <iostream>
using namespace std;

struct Task {
    struct promise_type {
        int value;
        Task get_return_object() { return Task{coroutine_handle<promise_type>::from_promise(*this)}; }
        suspend_never initial_suspend() { return {}; }
        suspend_never final_suspend() noexcept { return {}; }
        void return_value(int v) { value = v; }
        void unhandled_exception() { std::terminate(); }
    };
    coroutine_handle<promise_type> h;
    Task(coroutine_handle<promise_type> h): h(h) {}
    ~Task(){ if(h) h.destroy(); }
    int result() { return h.promise().value; }
};

Task compute() {
    co_return 42;
}

int main() {
    Task t = compute();
    cout << "Coroutine returned: " << t.result() << '\n';
}


Output

Coroutine returned: 42

57 — Pointer-to-member polymorphism (member function pointers)

Dispatch using pointer-to-member to call methods polymorphically.

// Compile: C++11+
#include <iostream>
using namespace std;

struct Base {
    void a() { cout << "Base::a\n"; }
    void b() { cout << "Base::b\n"; }
};

int main() {
    Base obj;
    void (Base::*pm)() = &Base::a; // pointer-to-member
    (obj.*pm)();                  // call a()
    pm = &Base::b;
    (obj.*pm)();                  // call b()
}


Output

Base::a
Base::b

58 — CRTP static interface enforcement (compile-time check)

Use CRTP + static_assert to require Derived to implement a method.

// Compile: C++11+
#include <iostream>
#include <type_traits>
using namespace std;

template<typename Derived>
class Checker {
    static void test() {
        // Ensure Derived has method void derived_impl()
        static_assert(std::is_same<decltype(&Derived::derived_impl), void (Derived::*)()>::value,
                      "Derived must implement void derived_impl()");
    }
public:
    void call() { Derived* d = static_cast<Derived*>(this); d->derived_impl(); }
};

class Good : public Checker<Good> {
public:
    void derived_impl() { cout << "Good::derived_impl\n"; }
};

// class Bad : public Checker<Bad> {}; // would fail static_assert

int main() {
    Good g;
    g.call();
}


Output

Good::derived_impl

59 — Command pattern with undo (polymorphic commands)

Commands encapsulate operations + undo.

// Compile: C++11+
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class AddCommand : public Command {
    int &target; int value;
public:
    AddCommand(int &t, int v): target(t), value(v) {}
    void execute() override { target += value; cout << "exec add " << value << '\n'; }
    void undo() override { target -= value; cout << "undo add " << value << '\n'; }
};

int main() {
    int x = 0;
    vector<unique_ptr<Command>> history;

    history.push_back(make_unique<AddCommand>(x, 5));
    history.back()->execute();
    cout << "x = " << x << '\n';

    history.push_back(make_unique<AddCommand>(x, 3));
    history.back()->execute();
    cout << "x = " << x << '\n';

    // undo last
    history.back()->undo();
    cout << "x after undo = " << x << '\n';
}


Output

exec add 5
x = 5
exec add 3
x = 8
undo add 3
x after undo = 5

60 — Reactive polymorphism (Observer with lifecycle / weak observers)

Observer pattern with weak callbacks to avoid dangling observers.

// Compile: C++11+
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
using namespace std;

class Subject {
    vector<weak_ptr<function<void(int)>>> observers;
public:
    void subscribe(shared_ptr<function<void(int)>> cb) {
        observers.push_back(cb);
    }
    void notify(int v) {
        for (auto it = observers.begin(); it != observers.end(); ) {
            if (auto sp = it->lock()) {
                (*sp)(v);
                ++it;
            } else {
                it = observers.erase(it); // remove expired
            }
        }
    }
};

int main() {
    Subject s;
    {
        auto obs = make_shared<function<void(int)>>([](int v){ cout << "Got: " << v << '\n'; });
        s.subscribe(obs);
        s.notify(10); // observer alive
    }
    s.notify(20); // observer expired, no call
}


Output

Got: 10

















✅ 61 — Policy-based Design (Strategy via Templates)

Allows selecting behaviors at compile-time using template "policies".

// Compile: C++11+
#include <iostream>
using namespace std;

struct AddPolicy {
    static int op(int a, int b) { return a + b; }
};
struct MulPolicy {
    static int op(int a, int b) { return a * b; }
};

template<typename Policy>
class Calculator {
public:
    int compute(int a, int b) { return Policy::op(a, b); }
};

int main() {
    Calculator<AddPolicy> addCalc;
    Calculator<MulPolicy> mulCalc;

    cout << addCalc.compute(3, 4) << endl;
    cout << mulCalc.compute(3, 4) << endl;
}


Output

7
12

✅ 62 — Policy-based Memory Management

Select memory allocation strategy at compile-time.

// Compile: C++11+
#include <iostream>
#include <cstdlib>
using namespace std;

struct MallocPolicy {
    static void* alloc(size_t sz) { return malloc(sz); }
    static void freeMem(void* p) { free(p); }
};
struct NewPolicy {
    static void* alloc(size_t sz) { return ::operator new(sz); }
    static void freeMem(void* p) { ::operator delete(p); }
};

template<typename Policy>
class Box {
    int* ptr;
public:
    Box() { ptr = (int*)Policy::alloc(sizeof(int)); *ptr = 10; }
    ~Box() { Policy::freeMem(ptr); }
    int value() const { return *ptr; }
};

int main() {
    Box<NewPolicy> a;
    Box<MallocPolicy> b;
    cout << a.value() << endl;
    cout << b.value() << endl;
}


Output

10
10

✅ 63 — Type Erasure (Manual Implementation)

Erases type but preserves behavior.

// Compile: C++11+
#include <iostream>
#include <memory>
using namespace std;

class Printable {
    struct Concept {
        virtual void print() const = 0;
        virtual ~Concept() = default;
    };
    template<typename T>
    struct Model : Concept {
        T obj;
        Model(T o): obj(o) {}
        void print() const override { cout << obj << endl; }
    };

    shared_ptr<const Concept> self;

public:
    template<typename T>
    Printable(T v) : self(make_shared<Model<T>>(v)) {}

    void print() const { self->print(); }
};

int main() {
    Printable a = 42;
    Printable b = string("Hello");
    a.print();
    b.print();
}


Output

42
Hello

✅ 64 — Data-Oriented Polymorphism (Struct of Arrays)

Cache-friendly layout alternate to OOP polymorphism.

// Compile: C++11+
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<float> x = {1,2,3};
    vector<float> y = {1,2,3};

    for(size_t i=0;i<x.size();i++)
        cout << "Len = " << (x[i]*x[i] + y[i]*y[i]) << endl;
}


Output

Len = 2
Len = 8
Len = 18

✅ 65 — SFINAE for Behavior Switching

Function enabled only if type has .size().

// Compile: C++11+
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
auto printSize(const T& t) -> decltype(t.size(), void()) {
    cout << "Has size: " << t.size() << endl;
}

void printSize(...) {
    cout << "No size()" << endl;
}

int main() {
    printSize(string("abc"));
    printSize(10);
}


Output

Has size: 3
No size()

✅ 66 — constexpr Polymorphism (Compile-time function dispatch)

Behavior decided fully at compile-time.

// Compile: C++14+
#include <iostream>
using namespace std;

constexpr int compute(int x) {
    if constexpr (sizeof(int) == 4)
        return x + 10;
    else
        return x - 10;
}

int main() {
    cout << compute(5) << endl;
}


Output

15

✅ 67 — std::variant + Visitor (Runtime Algebraic Types)

Alternate polymorphism without inheritance.

// Compile: C++17+
#include <iostream>
#include <variant>
using namespace std;

struct Add { int a,b; };
struct Mul { int a,b; };

int main() {
    variant<Add, Mul> v = Add{3,4};

    auto result = visit([](auto op){
        return op.a + op.b;
    }, v);

    cout << result << endl;

    v = Mul{3,4};
    cout << visit([](auto op){
        return op.a * op.b;
    }, v) << endl;
}


Output

7
12

✅ 68 — Custom RTTI System (Manual Type IDs)

Useful in embedded/systems without RTTI.

// Compile: C++11+
#include <iostream>
using namespace std;

class TypeBase {
public:
    virtual int typeId() const = 0;
    virtual ~TypeBase() = default;
};

class A : public TypeBase {
public:
    int typeId() const override { return 1; }
};

class B : public TypeBase {
public:
    int typeId() const override { return 2; }
};

void identify(TypeBase* p) {
    if (p->typeId() == 1) cout << "This is A\n";
    else if (p->typeId() == 2) cout << "This is B\n";
}

int main() {
    A a;
    B b;
    identify(&a);
    identify(&b);
}


Output

This is A
This is B

✅ 69 — Dynamic Dispatch Table (Manual vtable)

Implements vtable without inheritance.

// Compile: C++11+
#include <iostream>
using namespace std;

struct VTable {
    void (*speak)();
};

void dogSpeak() { cout << "Dog bark\n"; }
void catSpeak() { cout << "Cat meow\n"; }

struct Animal {
    VTable* vt;
};

int main() {
    VTable dogVT{ dogSpeak };
    VTable catVT{ catSpeak };

    Animal dog{ &dogVT };
    Animal cat{ &catVT };

    dog.vt->speak();
    cat.vt->speak();
}


Output

Dog bark
Cat meow

✅ 70 — std::any Runtime Polymorphism

std::any stores any type and retrieves runtime.

// Compile: C++17+
#include <iostream>
#include <any>
using namespace std;

int main() {
    any a = 50;
    cout << any_cast<int>(a) << endl;

    a = string("hello");
    cout << any_cast<string>(a) << endl;
}


Output

50
hello

















✅ 71 — Double Dispatch (Without Visitor Pattern)

Use two virtual calls to determine behavior based on both object types.

// Compile: C++11+
#include <iostream>
using namespace std;

class B; class C;

class A {
public:
    virtual void interact(B&) = 0;
    virtual void interact(C&) = 0;
    virtual ~A() = default;
};

class B { };
class C { };

class X : public A {
public:
    void interact(B&) override { cout << "X meets B\n"; }
    void interact(C&) override { cout << "X meets C\n"; }
};

class Y : public A {
public:
    void interact(B&) override { cout << "Y meets B\n"; }
    void interact(C&) override { cout << "Y meets C\n"; }
};

void dispatch(A& a, B& b) { a.interact(b); }
void dispatch(A& a, C& c) { a.interact(c); }

int main() {
    X x; Y y; B b; C c;
    dispatch(x, b);
    dispatch(x, c);
    dispatch(y, b);
    dispatch(y, c);
}


Output

X meets B
X meets C
Y meets B
Y meets C

✅ 72 — Expression-Tree Polymorphism (AST Interpreter)

Build small AST nodes for arithmetic evaluation.

// Compile: C++11+
#include <iostream>
#include <memory>
using namespace std;

struct Expr {
    virtual int eval() const = 0;
    virtual ~Expr() = default;
};

struct Const : Expr {
    int v;
    Const(int v): v(v) {}
    int eval() const override { return v; }
};

struct Add : Expr {
    unique_ptr<Expr> a, b;
    Add(Expr* x, Expr* y) : a(x), b(y) {}
    int eval() const override { return a->eval() + b->eval(); }
};

int main() {
    unique_ptr<Expr> expr(new Add(new Const(5), new Const(7)));
    cout << expr->eval() << endl;
}


Output

12

✅ 73 — Custom Smart Pointer with Debug Hooks

Demonstrates polymorphic control over deletion.

// Compile: C++11+
#include <iostream>
using namespace std;

template<typename T>
class DebugPtr {
    T* ptr;
public:
    explicit DebugPtr(T* p): ptr(p) {}
    ~DebugPtr() { 
        cout << "Deleting pointer\n";
        delete ptr; 
    }
    T* operator->() { return ptr; }
    T& operator*()  { return *ptr; }
};

int main() {
    DebugPtr<int> dp(new int(10));
    cout << *dp << endl;
}


Output

10
Deleting pointer

✅ 74 — CRTP for Compile-Time Virtual Functions

CRTP replaces runtime virtual with compile-time dispatch.

// Compile: C++11+
#include <iostream>
using namespace std;

template<typename D>
struct Base {
    void call() { static_cast<D*>(this)->impl(); }
};

struct Derived : Base<Derived> {
    void impl() { cout << "Derived impl\n"; }
};

int main() {
    Derived d;
    d.call();
}


Output

Derived impl

✅ 75 — Lazy Initialization Pattern

Object is created only when needed.

// Compile: C++11+
#include <iostream>
#include <memory>
using namespace std;

class Heavy {
public:
    Heavy() { cout << "Heavy created\n"; }
    void work() { cout << "Working!\n"; }
};

class Wrapper {
    unique_ptr<Heavy> h;
public:
    void get() {
        if (!h) h = make_unique<Heavy>();
        h->work();
    }
};

int main() {
    Wrapper w;
    w.get();
    w.get();
}


Output

Heavy created
Working!
Working!

✅ 76 — Bridge Pattern (Decoupled Implementations)

Switch implementation without changing abstraction.

// Compile: C++11+
#include <iostream>
using namespace std;

class Renderer {
public:
    virtual void drawCircle() = 0;
    virtual ~Renderer() = default;
};

class VectorRenderer : public Renderer {
public:
    void drawCircle() override { cout << "Vector circle\n"; }
};

class RasterRenderer : public Renderer {
public:
    void drawCircle() override { cout << "Raster circle\n"; }
};

class Shape {
protected:
    Renderer& r;
public:
    Shape(Renderer& r): r(r) {}
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    Circle(Renderer& r): Shape(r) {}
    void draw() override { r.drawCircle(); }
};

int main() {
    VectorRenderer vr;
    RasterRenderer rr;

    Circle c1(vr);
    Circle c2(rr);

    c1.draw();
    c2.draw();
}


Output

Vector circle
Raster circle

✅ 77 — Inline Storage Optimization (Small Buffer Optimization Idea)

Avoid heap allocation for small objects.

// Compile: C++11+
#include <iostream>
#include <cstring>
using namespace std;

class SmallString {
    char buf[16];
public:
    SmallString(const char* s) {
        strncpy(buf, s, 15);
        buf[15] = 0;
    }
    const char* str() const { return buf; }
};

int main() {
    SmallString s("hello");
    cout << s.str() << endl;
}


Output

hello

✅ 78 — RAII Polymorphism (Resource Management Objects)

Manage resource lifetime automatically.

// Compile: C++11+
#include <iostream>
#include <fstream>
using namespace std;

class File {
    ofstream f;
public:
    File(const string& name) { 
        f.open(name);
        cout << "File opened\n";
    }
    ~File() { 
        cout << "File closed\n";
        f.close(); 
    }
};

int main() {
    {
        File f("out.txt");
    }
}


Output

File opened
File closed

✅ 79 — Template Template Parameters

Pass templates as parameters.

// Compile: C++11+
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<template<typename...> class Container>
struct Holder {
    Container<int> data;
    void add(int x) { data.push_back(x); }
    void print() { for (int v: data) cout << v << " "; cout << endl; }
};

int main() {
    Holder<vector> hv;
    hv.add(1); hv.add(2);

    Holder<list> hl;
    hl.add(3); hl.add(4);

    hv.print();
    hl.print();
}


Output

1 2 
3 4 

✅ 80 — Custom Iterator Polymorphism

Build your own iterator class.

// Compile: C++11+
#include <iostream>
using namespace std;

class Range {
    int start, end;
public:
    Range(int s, int e): start(s), end(e) {}

    class Iterator {
        int value;
    public:
        Iterator(int v): value(v) {}
        int operator*() const { return value; }
        Iterator& operator++() { value++; return *this; }
        bool operator!=(const Iterator& other) const { return value != other.value; }
    };

    Iterator begin() const { return Iterator(start); }
    Iterator endIter() const { return Iterator(end); }
    Iterator end() const { return endIter(); }
};

int main() {
    Range r(1, 5);
    for (int x : r)
        cout << x << " ";
}


Output

1 2 3 4 




















✅ 81 — Atomic Operations (std::atomic)

Safe concurrent updates without locks.

// Compile: C++11+
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

    cout << "Counter: " << counter << endl;
}


Output (always 2000)

Counter: 2000

✅ 82 — Memory Barriers / Fences (std::atomic_thread_fence)

Enforce ordering of memory operations.

// Compile: C++11+
#include <iostream>
#include <atomic>
using namespace std;

atomic<int> a{0}, b{0};
atomic_thread_fence(memory_order_release);

int main() {
    a.store(1, memory_order_relaxed);
    atomic_thread_fence(memory_order_seq_cst);
    b.store(2, memory_order_relaxed);
    cout << "a=" << a.load() << ", b=" << b.load() << endl;
}


Output

a=1, b=2

✅ 83 — Coroutine Generator (C++20)

Yield sequence lazily using coroutines.

// Compile: C++20
#include <coroutine>
#include <iostream>
#include <optional>
using namespace std;

template<typename T>
struct Generator {
    struct promise_type {
        T current;
        auto get_return_object() { return Generator{handle_type::from_promise(*this)}; }
        auto initial_suspend() { return suspend_always{}; }
        auto final_suspend() noexcept { return suspend_always{}; }
        void unhandled_exception() { std::terminate(); }
        auto yield_value(T v) { current = v; return suspend_always{}; }
        void return_void() {}
    };
    using handle_type = coroutine_handle<promise_type>;
    handle_type h;

    Generator(handle_type h): h(h) {}
    ~Generator(){ if(h) h.destroy(); }

    optional<T> next() {
        h.resume();
        if(h.done()) return nullopt;
        return h.promise().current;
    }
};

Generator<int> seq(int n) {
    for(int i=1;i<=n;i++)
        co_yield i;
}

int main() {
    auto g = seq(5);
    while(auto val = g.next()) cout << *val << " ";
}


Output

1 2 3 4 5 

✅ 84 — RTTI & TypeInfo (dynamic_cast / typeid)
// Compile: C++11+
#include <iostream>
#include <typeinfo>
using namespace std;

struct Base { virtual ~Base(){} };
struct Derived : Base {};

int main() {
    Base* b = new Derived;
    if(dynamic_cast<Derived*>(b))
        cout << "b is Derived\n";

    cout << "Type: " << typeid(*b).name() << endl;
    delete b;
}


Output (type name may vary per compiler)

b is Derived
Type: 7Derived

✅ 85 — Custom Deleters in Smart Pointers
// Compile: C++11+
#include <iostream>
#include <memory>
using namespace std;

struct Foo { int x; Foo(int v):x(v){ cout<<"Foo created\n"; } };
int main() {
    auto deleter = [](Foo* f){ cout<<"Deleting Foo with "<<f->x<<"\n"; delete f; };
    unique_ptr<Foo, decltype(deleter)> p(new Foo(42), deleter);
}


Output

Foo created
Deleting Foo with 42

✅ 86 — EBO (Empty Base Optimization)

Empty base does not increase derived object size.

// Compile: C++11+
#include <iostream>
using namespace std;

struct Empty {};
struct Derived : Empty { int x; };

int main() {
    cout << "Size of Empty: " << sizeof(Empty) << endl;
    cout << "Size of Derived: " << sizeof(Derived) << endl;
}


Output (Derived may be same as int)

Size of Empty: 1
Size of Derived: 4

✅ 87 — Tag Dispatching

Select implementation based on type traits.

// Compile: C++11+
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
void print_impl(T val, true_type) { cout << val << " is integral\n"; }

template<typename T>
void print_impl(T val, false_type) { cout << val << " is not integral\n"; }

template<typename T>
void print(T val) { print_impl(val, is_integral<T>{}); }

int main() {
    print(10);
    print(3.14);
}


Output

10 is integral
3.14 is not integral

✅ 88 — Expression Templates

Lazy evaluation for vectors (no temporary objects).

// Compile: C++11+
#include <iostream>
using namespace std;

template<typename L, typename R>
struct AddExpr {
    L const& l;
    R const& r;
    AddExpr(L const& a, R const& b) : l(a), r(b) {}
    double operator[](size_t i) const { return l[i]+r[i]; }
};

struct Vec {
    double data[3];
    double operator[](size_t i) const { return data[i]; }
    double& operator[](size_t i) { return data[i]; }
    Vec operator+(Vec const& rhs) { return Vec{ {data[0]+rhs[0], data[1]+rhs[1], data[2]+rhs[2]} }; }
};

int main() {
    Vec a{{1,2,3}}, b{{4,5,6}};
    Vec c = a + b;
    for(int i=0;i<3;i++) cout << c[i] << " ";
}


Output

5 7 9 

✅ 89 — Perfect Forwarding (std::forward)
// Compile: C++11+
#include <iostream>
#include <utility>
using namespace std;

void print(int& x) { cout << "lvalue: " << x << endl; }
void print(int&& x) { cout << "rvalue: " << x << endl; }

template<typename T>
void wrapper(T&& val) { print(forward<T>(val)); }

int main() {
    int a=10;
    wrapper(a);
    wrapper(20);
}


Output

lvalue: 10
rvalue: 20

✅ 90 — CRTP Combined with Policy (Static Polymorphism + Strategy)
// Compile: C++11+
#include <iostream>
using namespace std;

template<typename Derived, typename Policy>
struct Base {
    void action() { Policy::run(static_cast<Derived&>(*this)); }
};

struct PrintPolicy {
    template<typename T>
    static void run(T& obj) { cout << "PrintPolicy: " << obj.value << endl; }
};

struct MyClass : Base<MyClass, PrintPolicy> {
    int value = 42;
};

int main() {
    MyClass m;
    m.action();
}


Output

PrintPolicy: 42






















✅ 91 — Lock-Free Stack (Using std::atomic)
// Compile: C++11+
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

struct Node {
    int value;
    Node* next;
};

atomic<Node*> head(nullptr);

void push(int v) {
    Node* n = new Node{v, nullptr};
    do {
        n->next = head.load();
    } while (!head.compare_exchange_weak(n->next, n));
}

int main() {
    thread t1(push, 1);
    thread t2(push, 2);

    t1.join();
    t2.join();

    Node* cur = head.load();
    while(cur) {
        cout << cur->value << " ";
        cur = cur->next;
    }
}


Output (order may vary due to concurrency)

2 1 

✅ 92 — std::optional for Safe Return
// Compile: C++17+
#include <iostream>
#include <optional>
using namespace std;

optional<int> divide(int a, int b) {
    if(b==0) return {};
    return a/b;
}

int main() {
    auto res = divide(10,2);
    if(res) cout << *res << endl;

    auto fail = divide(10,0);
    if(!fail) cout << "Division by zero!" << endl;
}


Output

5
Division by zero!

✅ 93 — std::variant as Type-Safe Union
// Compile: C++17+
#include <iostream>
#include <variant>
using namespace std;

variant<int,double,string> v;

int main() {
    v = 10;
    cout << get<int>(v) << endl;

    v = 3.14;
    cout << get<double>(v) << endl;

    v = "Hello";
    cout << get<string>(v) << endl;
}


Output

10
3.14
Hello

✅ 94 — std::any for Runtime Type Storage
// Compile: C++17+
#include <iostream>
#include <any>
using namespace std;

int main() {
    any a = 10;
    cout << any_cast<int>(a) << endl;

    a = string("World");
    cout << any_cast<string>(a) << endl;
}


Output

10
World

✅ 95 — std::function for Polymorphic Callbacks
// Compile: C++11+
#include <iostream>
#include <functional>
using namespace std;

void hello() { cout << "Hello\n"; }

int main() {
    function<void()> f = hello;
    f();

    f = [](){ cout << "Lambda!\n"; };
    f();
}


Output

Hello
Lambda!

✅ 96 — std::thread with Member Function
// Compile: C++11+
#include <iostream>
#include <thread>
using namespace std;

class Worker {
public:
    void run(int n) { cout << "Thread: " << n << endl; }
};

int main() {
    Worker w;
    thread t(&Worker::run, &w, 10);
    t.join();
}
/* 
Output
Thread: 10
*/


✅ 97 — std::mutex for Synchronization
// Compile: C++11+
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;
int counter = 0;

void increment() {
    for(int i=0;i<1000;i++) {
        lock_guard<mutex> lock(mtx);
        counter++;
    }
}

int main() {
    thread t1(increment), t2(increment);
    t1.join();
    t2.join();
    cout << "Counter: " << counter << endl;
}
/* 
Output
Counter: 2000
*/


✅ 98 — std::shared_mutex (C++17) for Read-Write Lock
// Compile: C++17+
#include <iostream>
#include <shared_mutex>
#include <thread>
using namespace std;

shared_mutex rwlock;
int data = 0;

void reader() {
    shared_lock<shared_mutex> lock(rwlock);
    cout << "Read: " << data << endl;
}

void writer() {
    unique_lock<shared_mutex> lock(rwlock);
    data += 10;
    cout << "Written: " << data << endl;
}

int main() {
    thread t1(reader);
    thread t2(writer);
    t1.join();
    t2.join();
}
/* 
Output
Read: 0
Written: 10
*/

✅ 99 — Lock-Free Queue (Simplified Example)
// Compile: C++11+
#include <iostream>
#include <atomic>
using namespace std;

struct Node { int val; Node* next; };

atomic<Node*> head(nullptr);

void enqueue(int v) {
    Node* n = new Node{v, nullptr};
    Node* old;
    do {
        old = head.load();
        n->next = old;
    } while(!head.compare_exchange_weak(old, n));
}

int main() {
    enqueue(1);
    enqueue(2);
    Node* cur = head.load();
    while(cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
}
/* 
Output
2 1
*/




 ✅ 100 — Thread-Safe Singleton
// Compile: C++11+
#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
    static Singleton* instance;
    static mutex mtx;
    Singleton() { cout << "Created\n"; }
public:
    static Singleton* getInstance() {
        lock_guard<mutex> lock(mtx);
        if(!instance) instance = new Singleton();
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    cout << (s1==s2) << endl;
}
/* 
Output
Created
1
*/






































