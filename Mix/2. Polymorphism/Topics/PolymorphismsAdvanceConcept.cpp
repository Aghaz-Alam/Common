1. Function Overloading
✔ Same function name, different parameter types
#include <iostream>
using namespace std;
void show(int x) { 
    cout << "int: " << x << endl; 
}
void show(double x) { 
    cout << "double: " << x << endl; 
}
void show(string x) { 
    cout << "string: " << x << endl; 
}
int main() {
    show(10);
    show(3.14);
    show("Hello");
}
/* 
int: 10
double: 3.14
string: Hello
*/




🌟 2. Template Function (Generic)
#include <iostream>
using namespace std;
template<typename T>
void display(T x) {
    cout << "Generic template: " << x << endl;
}
int main() {
    display(10);
    display(3.14);
    display("Hi");
}
/* 
Generic template: 10
Generic template: 3.14
Generic template: Hi
*/



🌟 3. Full Template Specialization
#include <iostream>
using namespace std;
template<typename T>
void func(T x) {
    cout << "Generic template: " << x << endl;
}

template<>
void func<int>(int x) {
    cout << "Full specialization for int: " << x << endl;
}
int main() {
    func(10);
    func(3.14);
}
/* 
Full specialization for int: 10
Generic template: 3.14
*/


🌟 **4. “Partial Specialization” via Overloading
(Function templates cannot be partially specialized)**

#include <iostream>
using namespace std;
template<typename T>
void showPtr(T* p) {
    cout << "Pointer overload: " << *p << endl;
}
int main() {
    int x = 10;
    showPtr(&x);
}
/* 
Pointer overload: 10
*/


🌟 5. Template Overload with Special First Argument

#include <iostream>
using namespace std;
template<typename U>
void combine(int a, U b) {
    cout << "Overload with int first: " << a << ", " << b << endl;
}
template<typename A, typename B>
void combine(A a, B b) {
    cout << "Generic template: " << a << ", " << b << endl;
}
int main() {
    combine(5, 4.2);    // overload selected
    combine("Hi", 10);  // generic template
}
/* 
Overload with int first: 5, 4.2
Generic template: Hi, 10
*/


🌟 6. Class Template (Generic)

#include <iostream>
using namespace std;
template<typename T>
class Box {
  public:
    T value;
    Box(T v) : value(v) {}
    void show() { cout << "Box: " << value << endl; }
};
int main() {
    Box<int> b1(10);
    Box<string> b2("Hello");

    b1.show();
    b2.show();
}
/* 
Box: 10
Box: Hello
*/


🌟 7. Class Template Partial Specialization

#include <iostream>
using namespace std;
template<typename T>
class Wrapper {
  public:
    static void info() { cout << "Generic Wrapper\n"; }
};

template<>
class Wrapper<int> {
  public:
    static void info() { cout << "Specialized for int\n"; }
};
template<typename T>
class Wrapper<T*> {
  public:
    static void info() { cout << "Pointer specialization\n"; }
};
int main() {
    Wrapper<double>::info();
    Wrapper<int>::info();
    Wrapper<int*>::info();
}
/* 
Generic Wrapper
Specialized for int
Pointer specialization
*/


🌟 8. CRTP — Compile-time Polymorphism

#include <iostream>
using namespace std;
template<typename Derived>
class Base {
  public:
    void run() {
        static_cast<Derived*>(this)->doWork();
    }
};

class A : public Base<A> {
  public:
    void doWork() { cout << "A doing work\n"; }
};

class B : public Base<B> {
  public:
    void doWork() { cout << "B doing work\n"; }
};
int main() {
    A a;
    B b;
    a.run();
    b.run();
}
/* 
A doing work
B doing work
*/



🌟 9. std::variant + std::visit (Static Polymorphism)

#include <variant>
#include <iostream>
using namespace std;
class Circle { public: void draw() { cout << "Circle\n"; } };
class Square { public: void draw() { cout << "Square\n"; } };
int main() {
    variant<Circle, Square> shape = Circle{};
    visit([](auto& s){ s.draw(); }, shape);

    shape = Square{};
    visit([](auto& s){ s.draw(); }, shape);
}
/* 
Circle
Square
*/



🌟 10. Dynamic Polymorphism (Virtual Functions)

#include <iostream>
using namespace std;
class Shape {
  public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
  public:
    void draw() const override { cout << "Circle\n"; }
};
class Square : public Shape {
  public:
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
Circle
Square
*/



🌟 11. Visitor Pattern (Double Dispatch)

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
};
class Circle : public Shape {
  public:
    void accept(Visitor& v) const override { v.visit(*this); }
};
class Square : public Shape {
  public:
    void accept(Visitor& v) const override { v.visit(*this); }
};
class Draw : public Visitor {
  public:
    void visit(const Circle&) override { cout << "Draw Circle\n"; }
    void visit(const Square&) override { cout << "Draw Square\n"; }
};
int main() {
    Circle c;
    Square s;
    Draw d;
    c.accept(d);
    s.accept(d);
}
/* 
Draw Circle
Draw Square
*/



🌟 12. Type Erasure (std::function)

#include <iostream>
#include <functional>
using namespace std;
int main() {
    function<void()> f;

    f = [](){ cout << "Lambda 1\n"; };
    f();

    f = [](){ cout << "Lambda 2\n"; };
    f();
}
/* 
Lambda 1
Lambda 2
*/