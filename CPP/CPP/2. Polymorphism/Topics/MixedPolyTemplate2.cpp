✅ 1. Virtual Functions (Runtime Polymorphism)

#include <iostream>
using namespace std;
class Shape {
  public:
    virtual void draw() { cout << "Shape\n"; }
    virtual ~Shape() = default;
};
class Circle : public Shape {
  public:
    void draw() override { cout << "Circle\n"; }
};
int main() {
    Shape* s = new Circle();
    s->draw();
    delete s;
}
/* 
Output
Circle
*/



✅ 2. Function Overloading (Compile-time Polymorphism)

#include <iostream>
using namespace std;

void show(int x) { cout << "int\n"; }
void show(double x) { cout << "double\n"; }

int main() {
    show(10);
    show(3.14);
}
/* 
Output
int
double
*/


✅ 3. Operator Overloading

#include <iostream>
using namespace std;
class Number {
    int x;
  public:
    Number(int v) : x(v) {}
    Number operator+(const Number& other) const {
        return Number(x + other.x);
    }
    void print() const { cout << x << endl; }
};
int main() {
    Number a(5), b(7);
    Number c = a + b;
    c.print();
}
/* 
Output
12
*/


✅ 4. Function Templates

#include <iostream>
using namespace std;
template<typename T>
T add(T a, T b) { return a + b; }

int main() {
    cout << add(3, 7) << endl;
    cout << add(2.5, 3.1) << endl;
}
/* 
Output
10
5.6
*/


✅ 5. Class Templates

#include <iostream>
using namespace std;
template<typename T>
class Box {
    T value;
  public:
    Box(T v) : value(v) {}
    void print() { cout << value << endl; }
};
int main() {
    Box<int> b1(10);
    Box<string> b2("Hello");
    b1.print();
    b2.print();
}
/* 
Output
10
Hello
*/


✅ 6. Template Specialization

#include <iostream>
using namespace std;
template<typename T>
void print(T x) { cout << "Generic: " << x << endl; }

template<>
void print<int>(int x) { cout << "Specialized int: " << x << endl; }
int main() {
    print(10);
    print(3.14);
}
/* 
Output
Specialized int: 10
Generic: 3.14
*/




✅ 7. CRTP — Curiously Recurring Template Pattern

#include <iostream>
using namespace std;
template<typename Derived>
class Base {
  public:
    void call() {
        static_cast<Derived*>(this)->impl();
    }
};
class Derived1 : public Base<Derived1> {
  public:
    void impl() { cout << "Derived1\n"; }
};
int main() {
    Derived1 d;
    d.call();
}
/* 
Output
Derived1
*/


✅ 8. Type Erasure (std::function-like)

#include <iostream>
#include <memory>
using namespace std;
class Callable {
    struct Concept {
        virtual void call() = 0;
        virtual ~Concept() = default;
    };
    template<typename T>
    struct Model : Concept {
        T obj;
        Model(T o) : obj(o) {}
        void call() override { obj(); }
    };
    unique_ptr<Concept> ptr;

  public:
    template<typename T>
    Callable(T t) : ptr(new Model<T>(t)) {}

    void operator()() { ptr->call(); }
};
int main() {
    Callable c([](){ cout << "Lambda called\n"; });
    c();
}
/* 
Output
Lambda called
*/



✅ 9. std::variant Polymorphism

#include <iostream>
#include <variant>
using namespace std;
class Circle { public: void draw(){ cout<<"Circle\n"; } };
class Square { public: void draw(){ cout<<"Square\n"; } };
int main() {
    variant<Circle, Square> shape = Circle{};
    visit([](auto& s){ s.draw(); }, shape);

    shape = Square{};
    visit([](auto& s){ s.draw(); }, shape);
}
/* 
Output
Circle
Square
*/



✅ 10. Multiple Inheritance Polymorphism

#include <iostream>
using namespace std;
class A { public: void showA(){ cout<<"A\n"; } };
class B { public: void showB(){ cout<<"B\n"; } };
class C : public A, public B {};
int main() {
    C obj;
    obj.showA();
    obj.showB();
}
/* 
Output
A
B
*/



✅ 11. Covariant Return Types

#include <iostream>
using namespace std;
class Base {
  public:
    virtual Base* clone() { return new Base(); }
};
class Derived : public Base {
  public:
    Derived* clone() override { return new Derived(); }
};
int main() {
    Derived d;
    Base* b = d.clone();
    cout << "Cloned\n";
    delete b;
}
/* 
Output
Cloned
*/


✅ 12. Virtual Inheritance

#include <iostream>
using namespace std;
class Base { public: int x = 10; };
class A : virtual public Base {};
class B : virtual public Base {};
class C : public A, public B {};
int main() {
    C obj;
    cout << obj.x << endl;
}
/* 
Output
10
*/


✅ 13. Pure Abstract Interfaces

#include <iostream>
using namespace std;
class IShape {
  public:
    virtual void draw() = 0;
    virtual ~IShape() = default;
};
class Circle : public IShape {
  public:
    void draw() override { cout << "Circle\n"; }
};
int main() {
    IShape* s = new Circle();
    s->draw();
    delete s;
}
/* 
Output
Circle
*/




✅ 14. Overriding vs Overloading Demonstration

#include <iostream>
using namespace std;
class A {
  public:
    virtual void show() { cout << "A show\n"; }
};
class B : public A {
  public:
    void show() override { cout << "B show\n"; } // overriding
    void show(int x) { cout << "Overloaded: " << x << endl; } // overloading
};
int main() {
    B b;
    b.show();
    b.show(5);
}
/* 
Output
B show
Overloaded: 5
*/

✅ 15. Final Classes & Methods

#include <iostream>
using namespace std;
class A {
  public:
    virtual void test() final { cout << "final method\n"; }
};
class B : public A {
    // void test() override {}  // ERROR — cannot override final
};
int main() {
    B b;
    b.test();
}
/* 
Output
final method
*/


✅ 16. Virtual Destructors

#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base(){ cout << "Base dtor\n"; }
};

class Derived : public Base {
  public:
    ~Derived(){ cout << "Derived dtor\n"; }
};
int main(){
    Base* b = new Derived();
    delete b;
}
/* 
Output
Derived dtor
Base dtor
*/



✅ 17. Dynamic Casting

#include <iostream>
using namespace std;
class Base { public: virtual ~Base() = default; };
class Derived : public Base {};
int main() {
    Base* b = new Derived();
    if (auto d = dynamic_cast<Derived*>(b))
        cout << "Downcast success\n";
    delete b;
}
/* 
Output
Downcast success
*/




✅ 18. Visitor Pattern (Double Dispatch)

#include <iostream>
using namespace std;
class Circle;
class Square;
class Visitor {
  public:
    virtual void visit(const Circle&) = 0;
    virtual void visit(const Square&) = 0;
};
class Shape {
  public:
    virtual void accept(Visitor&) const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
  public:
    void accept(Visitor& v) const override { v.visit(*this); }
};
class Square : public Shape {
  public:
    void accept(Visitor& v) const override { v.visit(*this); }
};
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
Output
Draw Circle
Draw Square 
*/