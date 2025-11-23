What is Polymorphism in C++?
Polymorphism means one interface, many forms.

In simple words:
A single function or pointer can behave differently depending on the type of object it is acting on.

Example:
A Dog and Cat both respond to speak(), but differently.


Two Main Types of Polymorphism in C++
a. Compile-Time Polymorphism (Static / Early binding)
--> Happens at compile time.
--> Includes:
    *Function overloading
    *Operator overloading
    *Templates (generic polymorphism)



B. Runtime Polymorphism (Dynamic / Late binding)
--> Happens at runtime using:
    *Virtual functions
    *Base class pointers/references pointing to derived objects
--> This is the famous "dynamic dispatch" mechanism.



Part A — Compile-Time Polymorphism Examples
a. Function Overloading
Same function name, different parameters.

#include <iostream>
using namespace std;
void print(int x) {
    cout << "Integer: " << x << endl;
}
void print(double x) {
    cout << "Double: " << x << endl;
}
void print(string x) {
    cout << "String: " << x << endl;
}
int main() {
    print(10);
    print(3.14);
    print("Hello");
  return 0;
}

b. Operator Overloading
You can redefine operators for your class.

#include <iostream>
using namespace std;
class Complex {
  public:
    int real, imag;
    Complex(int r, int i) : real(r), imag(i) {}
    // operator overloading
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
};
int main() {
    Complex a(2, 3), b(4, 5);
    Complex c = a + b;
    cout << c.real << " + " << c.imag << "i\n";
  return 0;
}



Part B — Runtime Polymorphism (Dynamic Polymorphism)
This is the core concept interviewers care about.
How Runtime Polymorphism Works Internally
✔ You need:
--> Base class pointer/reference
--> Derived class object
--> Virtual function

✔ Virtual Table (vtable)
--> Every class with a virtual function gets a hidden vtable
--> Contains addresses of overridden functions
--> Base pointer uses vtable of the actual object

Example 1 — Basic Virtual Function Polymorphism
#include <iostream>
using namespace std;
class Animal {
  public:
    virtual void speak() {
        cout << "Animal speaks\n";
    }
};
class Dog : public Animal {
  public:
    void speak() override {
        cout << "Dog barks\n";
    }
};
class Cat : public Animal {
  public:
    void speak() override {
        cout << "Cat meows\n";
    }
};
int main() {
    Animal* a;

    Dog d;
    Cat c;

    a = &d;
    a->speak();  // Dog barks

    a = &c;
    a->speak();  // Cat meows
  return 0;
}

/* 
✔ Explanation
a is a base pointer
Behavior depends on actual object (Dog, Cat)
This is dynamic dispatch
*/




Example 2 — Reference-Based Polymorphism
#include <iostream>
using namespace std;
class Shape {
  public:
    virtual void draw() {
        cout << "Drawing shape\n";
    }
};
class Circle : public Shape {
  public:
    void draw() override {
        cout << "Drawing Circle\n";
    }
};
class Rectangle : public Shape {
  public:
    void draw() override {
        cout << "Drawing Rectangle\n";
    }
};
void render(Shape& s) {
    s.draw(); // calls correct derived version
}
int main() {
    Circle c;
    Rectangle r;

    render(c); // Circle
    render(r); // Rectangle
  return 0;
}



Example 3 — Pure Virtual Function (Abstract Class)
When designing frameworks, we define interfaces.
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() = 0;  // pure virtual
};

class Cow : public Animal {
public:
    void makeSound() override {
        cout << "Cow moos\n";
    }
};

int main() {
    // Animal a; // ERROR: abstract class
    Cow c;
    c.makeSound();
}
/* 
✔ Why use pure virtual?
Forces derived classes to implement specific behavior
Creates interfaces
*/


Example 4 — Polymorphism with Arrays of Base Pointers
#include <iostream>
using namespace std;
class Shape {
  public:
    virtual void draw() { cout << "Shape\n"; }
};
class Square : public Shape {
  public:
    void draw() override { cout << "Square\n"; }
};
class Triangle : public Shape {
  public:
    void draw() override { cout << "Triangle\n"; }
};
int main() {
    Shape* arr[3];
    arr[0] = new Shape();
    arr[1] = new Square();
    arr[2] = new Triangle();

    for (int i = 0; i < 3; i++)
        arr[i]->draw();
  return 0;
}

Example 5 — Polymorphism + Smart Pointers (C++11+)
#include <iostream>
#include <memory>
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
    unique_ptr<Base> ptr = make_unique<Derived>();
    ptr->show(); // Derived
  return 0;
}



Example 6 — Virtual Destructor Requirement
If you delete through a base pointer, destructor must be virtual.

#include <iostream>
using namespace std;
class Base {
  public:
    Base() { cout << "Base constructed\n"; }
    virtual ~Base() { cout << "Base destroyed\n"; }
};
class Derived : public Base {
  public:
    Derived() { cout << "Derived constructed\n"; }
    ~Derived() { cout << "Derived destroyed\n"; }
};
int main() {
    Base* b = new Derived();
    delete b;  // calls both destructors
  return 0;
}



/* -------------------------------- */

✅ Approach 1 — Using switch/if Chains (BAD DESIGN)
❌ Tight coupling
❌ Hard to extend
❌ Violates Open/Closed Principle
❌ Requires modifying existing code whenever new types are added

We will use the Shape Drawing Example.

APPROACH 1 — switch/if Chains (Full Program)
#include <iostream>
using namespace std;
// Shape type codes
enum ShapeType {
    CIRCLE = 1,
    SQUARE = 2,
    TRIANGLE = 3
};
// Functions for each shape
void drawCircle() {
    cout << "Drawing Circle\n";
}
void drawSquare() {
    cout << "Drawing Square\n";
}
void drawTriangle() {
    cout << "Drawing Triangle\n";
}
// BAD APPROACH: Decision logic based on type codes
void drawShape(int type) {
    switch (type) {
    case CIRCLE:
        drawCircle();
        break;

    case SQUARE:
        drawSquare();
        break;

    case TRIANGLE:
        drawTriangle();
        break;

    default:
        cout << "Unknown Shape\n";
    }
}
int main() {
    int shapes[] = { CIRCLE, SQUARE, TRIANGLE };

    for (int type : shapes) {
        drawShape(type);
    }

    return 0;
}

❌ Why this is bad?
If we add a Hexagon, we must modify:
---> The enum
---> The switch
---> The functions
---> All switch statements across the entire system
---> This grows worse as the application grows.





✅ Approach 2 — Using Polymorphism (GOOD DESIGN)
✔ Clean
✔ Flexible
✔ Extensible
✔ Uses dynamic dispatch
✔ Follows Open/Closed Principle

APPROACH 2 — Polymorphism (Full Program)
#include <iostream>
#include <vector>
using namespace std;
// Base class
class Shape {
  public:
    virtual void draw() = 0;   // Pure virtual function
    virtual ~Shape() {}
};
// Derived classes implementing polymorphic behavior
class Circle : public Shape {
  public:
    void draw() override {
        cout << "Drawing Circle\n";
    }
};
class Square : public Shape {
  public:
    void draw() override {
        cout << "Drawing Square\n";
    }
};
class Triangle : public Shape {
  public:
    void draw() override {
        cout << "Drawing Triangle\n";
    }
};
int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Circle());
    shapes.push_back(new Square());
    shapes.push_back(new Triangle());

    // NO SWITCH, NO IF — polymorphism at work!
    for (auto s : shapes) {
        s->draw();          // Calls the correct derived version
    }

    // Clean-up
    for (auto s : shapes) {
        delete s;
    }

    return 0;
}
