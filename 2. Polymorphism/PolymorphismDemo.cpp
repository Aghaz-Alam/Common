1️⃣ Static Polymorphism
A. Function Overloading & Templates (Compile-time)

#include <iostream>
using namespace std;

// Function overloading
void print(int x) { cout << "int: " << x << endl; }
void print(double x) { cout << "double: " << x << endl; }

// Template (generic)
template<typename T>
void printTemplate(T x) {
    cout << "Template: " << x << endl;
}
int main() {
    print(10);
    print(3.14);

    printTemplate(42);
    printTemplate("Hello");

    return 0;
}
/* 
Output:
int: 10
double: 3.14
Template: 42
Template: Hello

Compiler decides which function to call at compile-time → no runtime overhead.
*/



#include <iostream>
using namespace std;
// ---------------------------
// Function overloading
// ---------------------------
void print(int x) { cout << "int: " << x << endl; }
void print(double x) { cout << "double: " << x << endl; }

// ---------------------------
// Template (generic)
// ---------------------------
template<typename T>
void printTemplate(T x) {
    cout << "Generic Template: " << x << endl;
}

// ---------------------------
// FULL SPECIALIZATION for int
// ---------------------------
template<>
void printTemplate<int>(int val) {
    cout << "Full specialization for int: " << val << endl;
}

// ---------------------------
// "Partial specialization" via overloading
// (because function templates CANNOT be partially specialized)
// ---------------------------
template <typename T>
void printPartialTempSpe(T* value) {
    cout << "Function overload for pointer type: " << *value << endl;
}

// ---------------------------
// Overload for int as first parameter
// ---------------------------
template <typename U>
void print1stOverload(int value1, U value2) {
    cout << "Overload for int as first param: "
         << value1 << ", " << value2 << endl;
}
int main() {
    print(10);
    print(3.14);

    printTemplate(42);
    printTemplate("Hello");

    printTemplate(20);   // calls full specialization for int

    int x = 99;
    printPartialTempSpe(&x);     // Overload for pointer types
    print1stOverload(5, 3.14);   // Overload for int as first argument
  return 0;
}
/*
int: 10
double: 3.14
Full specialization for int: 42
Generic Template: Hello
Full specialization for int: 20
Function overload for pointer type: 99
Overload for int as first param: 5, 3.14
*/





B. CRTP (Curiously Recurring Template Pattern)
#include <iostream>
using namespace std;
template <typename Derived>
struct Base {
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

struct Derived1 : Base<Derived1> {
    void implementation() { cout << "Derived1 implementation\n"; }
};

struct Derived2 : Base<Derived2> {
    void implementation() { cout << "Derived2 implementation\n"; }
};

int main() {
    Derived1 d1;
    Derived2 d2;

    d1.interface();
    d2.interface();
}
/* 
Output:
Derived1 implementation
Derived2 implementation

Achieves polymorphism without virtual functions.
Zero runtime overhead; resolved at compile-time.
*/



#include <iostream>
using namespace std;
template <typename Derived>
class Base {
  public:
    void interface() {
        // Compile-time polymorphism (no virtual)
        static_cast<Derived*>(this)->implementation();
    }
};
class Derived1 : public Base<Derived1> {
  public:
    void implementation() {
        cout << "Derived1 implementation\n";
    }
};
class Derived2 : public Base<Derived2> {
  public:
    void implementation() {
        cout << "Derived2 implementation\n";
    }
};
int main() {
    Derived1 d1;
    Derived2 d2;

    d1.interface();
    d2.interface();
}
/*
Output
Derived1 implementation
Derived2 implementation
*/



C. std::variant (Type-safe alternative)
#include <variant>
#include <iostream>
using namespace std;
struct Circle { void draw() { cout << "Circle\n"; } };
struct Square { void draw() { cout << "Square\n"; } };
int main() {
    variant<Circle, Square> shape = Circle{};
    visit([](auto& s){ s.draw(); }, shape);

    shape = Square{};
    visit([](auto& s){ s.draw(); }, shape);
}
/* 
Output:
Circle
Square

Polymorphism without inheritance or virtual functions.
Type-safe, resolved at compile-time.
*/



#include <variant>
#include <iostream>
using namespace std;

class Circle {
  public:
    void draw() {
        cout << "Circle\n";
    }
};

class Square {
  public:
    void draw() {
        cout << "Square\n";
    }
};

int main() {
    variant<Circle, Square> shape = Circle{};

    visit([](auto& s) {
        s.draw();
    }, shape);

    shape = Square{};

    visit([](auto& s) {
        s.draw();
    }, shape);

    return 0;
}
/* 
Output:
Circle
Square

Decision happens at runtime using virtual table (vtable).
*/




2️⃣ Dynamic Polymorphism (Runtime)
A. Virtual Functions

#include <iostream>
using namespace std;
struct Shape {
    virtual void draw() const = 0; // pure virtual
    virtual ~Shape() = default;
};
struct Circle : Shape {
    void draw() const override { cout << "Circle\n"; }
};
struct Square : Shape {
    void draw() const override { cout << "Square\n"; }
};
int main() {
    Shape* s1 = new Circle();
    Shape* s2 = new Square();

    s1->draw();
    s2->draw();

    delete s1;
    delete s2;
}
/* 
Output:
Circle
Square

Decision happens at runtime using virtual table (vtable).
*/




#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() const = 0;     // pure virtual function
    virtual ~Shape() = default;        // virtual destructor
};

class Circle : public Shape {
  public:
    void draw() const override {
        cout << "Circle\n";
    }
};

class Square : public Shape {
  public:
    void draw() const override {
        cout << "Square\n";
    }
};

int main() {
    Shape* s1 = new Circle();
    Shape* s2 = new Square();

    s1->draw();
    s2->draw();

    delete s1;
    delete s2;
}
/* 
Output:
Circle
Square

Decision happens at runtime using virtual table (vtable).
*/



B. Type Erasure (std::function example)
#include <iostream>
#include <functional>
using namespace std;
int main() {
    function<void()> f;

    f = []{ cout << "Lambda 1\n"; };
    f();

    f = []{ cout << "Lambda 2\n"; };
    f();
}
/* 
Output:
Lambda 1
Lambda 2

Encapsulates any callable type behind a uniform interface → runtime polymorphism.
*/

C. Visitor Pattern (Double Dispatch)
#include <iostream>
using namespace std;
struct Circle;
struct Square;
struct Visitor {
    virtual void visit(const Circle&) = 0;
    virtual void visit(const Square&) = 0;
};
struct Shape {
    virtual void accept(Visitor&) const = 0;
};
struct Circle : Shape {
    void accept(Visitor& v) const override { v.visit(*this); }
};
struct Square : Shape {
    void accept(Visitor& v) const override { v.visit(*this); }
};
struct DrawVisitor : Visitor {
    void visit(const Circle&) override { cout << "Draw Circle\n"; }
    void visit(const Square&) override { cout << "Draw Square\n"; }
};
int main() {
    Circle c;
    Square s;
    DrawVisitor dv;

    c.accept(dv);
    s.accept(dv);
}
/* 
Output:
Draw Circle
Draw Square

Handles operations based on both runtime types (double dispatch).
*/




#include <iostream>
using namespace std;

class Circle;
class Square;

// Visitor Base Class
class Visitor {
  public:
    virtual void visit(const Circle&) = 0;
    virtual void visit(const Square&) = 0;
    virtual ~Visitor() = default;
};

// Shape Base Class
class Shape {
  public:
    virtual void accept(Visitor&) const = 0;
    virtual ~Shape() = default;
};

// Circle Class
class Circle : public Shape {
public:
    void accept(Visitor& v) const override { v.visit(*this); }
};

// Square Class
class Square : public Shape {
  public:
    void accept(Visitor& v) const override { v.visit(*this); }
};

// Concrete Visitor
class DrawVisitor : public Visitor {
  public:
    void visit(const Circle&) override { cout << "Draw Circle\n"; }
    void visit(const Square&) override { cout << "Draw Square\n"; }
};

int main() {
    Circle c;
    Square s;
    DrawVisitor dv;

    c.accept(dv);
    s.accept(dv);
}
/* 
Output:
Draw Circle
Draw Square

Handles operations based on both runtime types (double dispatch).
*/



3️⃣ Modern C++ Emphasis
A. RAII & Smart Pointers
#include <iostream>
#include <memory>
using namespace std;
struct Shape {
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};
struct Circle : Shape {
    void draw() const override { cout << "Circle\n"; }
};
int main() {
    unique_ptr<Shape> s = make_unique<Circle>();
    s->draw();  // No manual delete required
}
/* 
Output:
Circle

Automatic memory management.
Safer and more modern than raw pointers.
*/


B. Minimal Runtime Overhead
Using CRTP or std::variant instead of virtual functions wherever possible reduces runtime cost. Already demonstrated in section 1.

4️⃣ Advanced Patterns
A. Covariant Return Types
#include <iostream>
using namespace std;
struct Base {
    virtual Base* clone() const { return new Base(*this); }
    virtual void show() { cout << "Base\n"; }
    virtual ~Base() = default;
};
struct Derived : Base {
    Derived* clone() const override { return new Derived(*this); }
    void show() override { cout << "Derived\n"; }
};
int main() {
    Base* b = new Derived();
    Base* copy = b->clone();
    copy->show();

    delete b;
    delete copy;
}
/* 
Output:
Derived

Allows overriding to return more specific type safely.
*/


B. Multiple Inheritance with Virtual Bases
#include <iostream>
using namespace std;
struct A { virtual void f() { cout << "A\n"; } };
struct B : virtual A {};
struct C : virtual A {};
struct D : B, C {};
int main() {
    D d;
    d.f();  // Only one copy of A exists
}
/* 
Avoids diamond problem in multiple inheritance.
*/