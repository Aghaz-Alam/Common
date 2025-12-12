
//✅ SECTION 1 — IS-A (Inheritance)

//Challenge 1 — Simple Inheritance & Method Override
#include <iostream>
using namespace std;
class Animal {
  public:
    void eat() { cout << "Animal eats\n"; }
};
class Dog : public Animal {
  public:
    void bark() { cout << "Dog barks\n"; }
};
int main() {
    Dog d;
    d.eat();
    d.bark();
}
/* 
Output
Animal eats
Dog barks

Explanation: Dog IS-A Animal, so it inherits eat().
*/



//Challenge 2 — Function Overriding (Runtime Polymorphism)
#include <iostream>
using namespace std;
class Car {
  public:
    virtual void start() { cout << "Car starts\n"; }
};
class SportsCar : public Car {
 public:
    void start() override { cout << "SportsCar starts fast\n"; }
};
int main() {
    Car* c = new SportsCar();
    c->start();
    delete c;
}
/* 
Output
SportsCar starts fast

Explanation: Virtual ensures runtime dispatch.
*/


//Challenge 3 — Protected Members Inherited
#include <iostream>
using namespace std;
class Base {
  protected:
    int x = 10;
};
class Derived : public Base {
  public:
    void show() { cout << "x = " << x << "\n"; }
};
int main() {
    Derived d;
    d.show();
}
/* 
Output
x = 10

Explanation: protected allows derived access.
*/


//Challenge 4 — Constructors Order in Inheritance
#include <iostream>
using namespace std;
class A {
  public:
    A() { cout << "A ctor\n"; }
};
class B : public A {
  public:
    B() { cout << "B ctor\n"; }
};
int main() {
    B b;
}
/* 
Output
A ctor
B ctor

Explanation: Base constructed first, then derived.
*/


//Challenge 5 — Destructor Order
#include <iostream>
using namespace std;
class A {
  public:
    ~A() { cout << "A dtor\n"; }
};
class B : public A {
  public:
    ~B() { cout << "B dtor\n"; }
};
int main() {
    B b;
}
/* 
Output
B dtor
A dtor

Explanation: Destruction happens reverse order.
*/


//Challenge 6 — Ambiguous Function Call (Multiple Inheritance)
#include <iostream>
using namespace std;
class A { public: void fun(){ cout << "A fun\n"; } };
class B { public: void fun(){ cout << "B fun\n"; } };
class C : public A, public B {};
int main() {
    C c;
    c.A::fun();
    c.B::fun();
}
/* 
Output
A fun
B fun

Explanation: Must resolve ambiguity using scope.
*/


//Challenge 7 — Diamond Inheritance Without virtual
#include <iostream>
using namespace std;
class A { public: int x = 10; };
class B : public A {};
class C : public A {};
class D : public B, public C {};
int main() {
    D d;
    // cout << d.x;  // ERROR ambiguous
    cout << d.B::x << "\n"; 
}
/* 
Output
10

Explanation: Two A subobjects exist → ambiguity.
*/


//Challenge 8 — Virtual Inheritance Fixes Diamond
#include <iostream>
using namespace std;
class A { public: int x = 10; };
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};
int main() {
    D d;
    cout << d.x << "\n";
}
/* 
Output
10

Explanation: Now only one A instance → no ambiguity.
*/



//✅ SECTION 2 — HAS-A Composition (Strong Ownership) — 6 Challenges
//Challenge 9 — Composition Basic
#include <iostream>
using namespace std;
class Engine {
  public:
    void start() { cout << "Engine start\n"; }
};
class Car {
    Engine eng;   // Composition (Car OWNS engine)
  public:
    void run() {
        eng.start();
        cout << "Car running\n";
    }
};
int main() {
    Car c;
    c.run();
}
/* 
Output
Engine start
Car running

Explanation: Engine lifetime tied to Car.
*/


//Challenge 10 — Composition: Constructor Initialization
#include <iostream>
using namespace std;
class Battery {
  public:
    Battery(int p){ cout << "Battery: " << p << "%\n"; }
};
class Laptop {
    Battery bat;
  public:
    Laptop() : bat(90) {}
};
int main() {
    Laptop l;
}
/* 
Output
Battery: 90%
*/

//Challenge 11 — Composition: Nested Object Behavior
#include <iostream>
using namespace std;
class Address {
  public:
    void print() { cout << "City: Delhi\n"; }
};
class Person {
    Address addr;
  public:
    void showAddress() { addr.print(); }
};
int main() {
    Person p;
    p.showAddress();
}
/* 
Output
City: Delhi
*/


//Challenge 12 — Composition with Multiple Objects
#include <iostream>
using namespace std;
class Wheel { 
  public: 
     Wheel() { cout << "Wheel created\n"; } 
};
class Bike {
    Wheel w1, w2;
  public:
    Bike() { cout << "Bike constructed\n"; }
};
int main() {
    Bike b;
}
/* 
Output
Wheel created
Wheel created
Bike constructed
*/


//Challenge 13 — Composition Destruction Order
#include <iostream>
using namespace std;
class A { public: ~A(){ cout << "A destroyed\n"; } };
class B { public: ~B(){ cout << "B destroyed\n"; } };
class C {
    A a;
    B b;
};
int main() {
    C c;
}
/* 
Output
B destroyed
A destroyed

Explanation: Members destroyed in reverse order of definition.
*/


//Challenge 14 — Forcing Dependency in Composition
#include <iostream>
using namespace std;
class CPU {
  public:
    CPU(){ cout << "CPU ready\n"; }
};
class Computer {
    CPU cpu;
  public:
    Computer(){ cout << "Computer ON\n"; }
};
int main() {
    Computer c;
}
/* 
Output
CPU ready
Computer ON
*/

//✅ SECTION 3 — HAS-A Aggregation (Weak Ownership) — 6 Challenges
//Challenge 15 — Aggregation Basic
#include <iostream>
using namespace std;
class Engine {
  public:
    void start(){ cout << "Engine start\n"; }
};
class Car {
    Engine* eng;      // Aggregation — Car DOES NOT own Engine
  public:
    Car(Engine* e): eng(e){}
    void run(){
        eng->start();
        cout << "Car running\n";
    }
};
int main(){
    Engine e;
    Car c(&e);
    c.run();
}
/* 
Output
Engine start
Car running

Explanation: Engine lives even without Car.
*/


//Challenge 16 — Aggregation: Shared Object
#include <iostream>
using namespace std;
class Teacher {
   public:
    string name;
    Teacher(string n):name(n){}
};
class Student {
    Teacher* t;
   public:
    Student(Teacher* t):t(t){}
    void print(){ cout << "Teacher: " << t->name << "\n"; }
};
int main(){
    Teacher t("Rahul");
    Student s1(&t), s2(&t);
    s1.print();
    s2.print();
}
/* 
Output
Teacher: Rahul
Teacher: Rahul
*/



//Challenge 17 — Aggregation: Lifetime Independence
#include <iostream>
using namespace std;
class Address {
  public:
    string city;
    Address(string c):city(c){}
};
class Employee {
    Address* addr;
  public:
    Employee(Address* a):addr(a){}
    void show(){ cout << addr->city << "\n"; }
};
int main(){
    Address* a = new Address("Mumbai");
    {
        Employee e(a);
        e.show();
    }
    cout << a->city << "\n";  
    delete a;
}
/* 
Output
Mumbai
Mumbai

Explanation: Address outlives Employee → aggregation.
*/


//Challenge 18 — Aggregation with vector of pointers
#include <iostream>
#include <vector>
using namespace std;
class Book{
  public:
    string name;
    Book(string n):name(n){}
};
class Library{
    vector<Book*> books;   // aggregation
  public:
    void add(Book* b){ books.push_back(b); }
    void show(){
        for(auto b: books) cout << b->name << "\n";
    }
};
int main(){
    Book b1("C++"), b2("Python");
    Library lib;
    lib.add(&b1);
    lib.add(&b2);
    lib.show();
}
/* 
Output
C++
Python
*/



//Challenge 19 — Composition vs Aggregation Difference
#include <iostream>
using namespace std;
class Engine{
  public:
    Engine(){ cout<<"Engine built\n"; }
};
class Car{       // Composition
    Engine e;
  public:
    Car(){ cout<<"Car built\n"; }
};
class Person{    // Aggregation
    Engine* e;
  public:
    Person(Engine* ee):e(ee){}
    void show(){ cout<<"Person owns engine externally\n"; }
};
int main(){
    Car c;
    Engine sharedEngine;
    Person p(&sharedEngine);
    p.show();
}
/* 
Output
Engine built
Car built
Engine built
Person owns engine externally
*/


//Challenge 20 — Complex Aggregation: Company Has Many Employees
#include <iostream>
#include <vector>
using namespace std;
class Employee{
  public:
    string name;
    Employee(string n):name(n){}
};
class Company{
    vector<Employee*> emps;
  public:
    void hire(Employee* e){ emps.push_back(e); }
    void list(){
        for(auto e: emps) cout << e->name << "\n";
    }
};
int main(){
    Employee e1("Aman"), e2("Rohan");
    Company c;
    c.hire(&e1);
    c.hire(&e2);
    c.list();
}
/* 
Output
Aman
Rohan

Explanation: Employees exist independently → aggregation.
*/













//✅ 1. Show IS-A using classical inheritance + virtual functions
//Concept: Runtime polymorphism using IS-A
//Question:
//Create a Shape base class and override area() in Circle.

//Code
#include <iostream>
using namespace std;
class Shape {
  public:
    virtual double area() const { return 0; }
    virtual ~Shape() {}
};
class Circle : public Shape {   // IS-A
    double r;
  public:
    Circle(double radius) : r(radius) {}
    double area() const override { return 3.14 * r * r; }
};
int main() {
    Shape* s = new Circle(5);  
    cout << s->area();
    delete s;
}
/* 
Output
78.5

Explanation
Circle IS-A Shape, so base pointer calls overridden method.
*/



//✅ 2. Demonstrate HAS-A (Composition) with strong ownership
//Concept: Composition = lifetime ownership
//Question:
//A Car HAS-A Engine (Engine is destroyed with Car).

//Code
#include <iostream>
using namespace std;
class Engine {
  public:
    Engine() { cout << "Engine constructed\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
};
class Car {  // HAS-A (composition)
    Engine engine; 
};
int main() {
    Car c;
}
/* 
Output
Engine constructed
Engine destroyed

Explanation
Composition ensures Engine dies with Car.
*/


//✅ 3. Demonstrate HAS-A (Aggregation) with weak association
//Concept: Aggregation = no ownership
//Question:
//A Team has players, but players exist independently.

//Code
#include <iostream>
using namespace std;
class Player {
 public:
    string name;
    Player(string n) : name(n) {}
};
class Team {
  public:
    Player* p;   // aggregation: NOT owned
    Team(Player* player) : p(player) {}
};
int main() {
    Player p("Ronaldo");
    Team t(&p);
    cout << t.p->name;
}
/* 
Output
Ronaldo

Explanation
Team doesn’t own the player → aggregation.
*/



//✅ 4. IS-A with multiple levels (multilevel inheritance)
//Question:
//Implement Animal → Mammal → Dog.

#include <iostream>
using namespace std;
class Animal { public: virtual void sound(){ cout<<"Animal\n"; } };
class Mammal : public Animal { public: void sound() override { cout<<"Mammal\n"; } };
class Dog : public Mammal { public: void sound() override { cout<<"Dog\n"; } };
int main(){ Animal* a = new Dog(); a->sound(); }
/* 
Output
Dog
*/



//✅ 5. Composition challenge: Bank account with transaction history
//Question:
//BankAccount HAS-A vector<Transaction>.

#include <iostream>
#include <vector>
using namespace std;
class Transaction {
  public:
    string type;
    int amount;
    Transaction(string t, int a) : type(t), amount(a) {}
};
class BankAccount {
    vector<Transaction> history; // composition
  public:
    void deposit(int amt) { history.emplace_back("Deposit", amt); }
    void print() {
        for (auto& t : history)
            cout << t.type << " : " << t.amount << endl;
    }
};
int main() {
    BankAccount b;
    b.deposit(500);
    b.deposit(200);
    b.print();
}
/* 
Output
Deposit : 500
Deposit : 200
*/


//✅ 6. Aggregation challenge: University with Students
#include <iostream>
#include <vector>
using namespace std;
class Student { public: string name; Student(string n):name(n){} };
class University {
  public:
    vector<Student*> students;  // aggregation
    void add(Student* s){ students.push_back(s); }
};
int main(){
    Student s1("A"), s2("B");
    University u;
    u.add(&s1); u.add(&s2);
    cout << u.students[1]->name;
}
/* 
Output
B
*/


//✅ 7. IS-A: Pure virtual class (abstract)
#include <iostream>
using namespace std;
class Device { public: virtual void start()=0; };
class Laptop : public Device { public: void start(){ cout<<"Laptop start\n"; } };
int main(){ Device* d=new Laptop(); d->start(); }
/* 
Output
Laptop start
*/


//✅ 8. Composition: Laptop HAS-A Battery
#include <iostream>
using namespace std;
class Battery { public: Battery(){ cout<<"Battery ok\n"; } };
class Laptop { Battery b; };
int main(){ Laptop l; }
/* 
Output
Battery ok
*/


//✅ 9. Aggregation: Flight HAS-A Pilot (but does not own)
#include <iostream>
using namespace std;
class Pilot { public: string name; Pilot(string n):name(n){} };
class Flight {
  public:
    Pilot* p;   // aggregation
    Flight(Pilot* p):p(p){}
};
int main(){
    Pilot p("Captain Z");
    Flight f(&p);
    cout << f.p->name;
}
/* 
Output
Captain Z
*/




//✅ 10. IS-A + HAS-A mixed
// Question:
// Ferrari IS-A Car
// Car HAS-A Engine

#include <iostream>
using namespace std;
class Engine { public: int hp; Engine(int h):hp(h){} };
class Car {
  protected:
    Engine e;  // composition
  public:
    Car(int hp):e(hp){}
};
class Ferrari : public Car {  // IS-A
  public:
    Ferrari():Car(800){}
    void show(){ cout<<"HP "<<e.hp; }
};
int main(){ Ferrari f; f.show(); }
/* 
Output
HP 800
*/


//✅ 11. Composition for resource management (RAII)
#include <iostream>
using namespace std;
class File {
  public: File(){ cout<<"Opened\n"; }
        ~File(){ cout<<"Closed\n"; }
};
class Logger { File f; }; // composition = RAII
int main(){ Logger l; }
/* 
Output
Opened
Closed
*/


//✅ 12. Aggregation in Observer Pattern
#include <iostream>
#include <vector>
using namespace std;
class Observer { public: virtual void update() = 0; };
class Subject {
  public:
    vector<Observer*> obs; // aggregation
    void add(Observer* o) { obs.push_back(o); }
    void notify() { for (auto* o : obs) o->update(); }
};
class Listener : public Observer {
public: void update(){ cout<<"Updated\n"; }
};
int main(){
    Subject s; Listener l;
    s.add(&l);
    s.notify();
}
/* 
Output
Updated
*/


//✅ 13. IS-A: using protected base methods
#include <iostream>
using namespace std;
class Base { protected: void msg(){ cout<<"Base\n"; } };
class Derived : public Base { public: void call(){ msg(); } };
int main(){ Derived d; d.call(); }
/* 
Output
Base
*/


//✅ 14. Composition: Game HAS-A PhysicsEngine
#include <iostream>
using namespace std;
class PhysicsEngine { public: void simulate(){ cout<<"Simulate\n"; } };
class Game {
    PhysicsEngine pe;  // composition
  public:
    void frame(){ pe.simulate(); }
};
int main(){ Game g; g.frame(); }
/* 
Output
Simulate
*/


//✅ 15. Aggregation: City HAS-A list of Buildings
#include <iostream>
#include <vector>
using namespace std;
class Building { public: string name; Building(string n):name(n){} };
class City {
  public:
    vector<Building*> b; // aggregation
};
int main(){
    Building b1("Mall"), b2("Hospital");
    City c; c.b={&b1,&b2};
    cout<<c.b[0]->name;
}
/* 
Output
Mall
*/


//✅ 16. IS-A: Multiple inheritance (Interface style)
#include <iostream>
using namespace std;
class Drawable { public: virtual void draw()=0; };
class Movable { public: virtual void move()=0; };
class Sprite : public Drawable, public Movable {
  public:
    void draw(){ cout<<"Draw\n"; }
    void move(){ cout<<"Move\n"; }
};
int main(){
    Sprite s; s.draw(); s.move();
}
/* 
Output
Draw
Move
*/

//✅ 17. Composition: Stack HAS-A vector
#include <iostream>
#include <vector>
using namespace std;
class Stack {
    vector<int> data; // composition
  public:
    void push(int x){ data.push_back(x); }
    int top(){ return data.back(); }
};
int main(){ Stack s; s.push(10); cout<<s.top(); }
/* 
Output
10
*/


//✅ 18. Aggregation: Company HAS-A Employees
#include <iostream>
#include <vector>
using namespace std;
class Employee { public: string name; Employee(string n):name(n){} };
class Company {
  public:
    vector<Employee*> e; // aggregation
};
int main(){
    Employee e1("John");
    Company c; c.e.push_back(&e1);
    cout << c.e[0]->name;
}
/* 
Output
John
*/



//✅ 19. IS-A: Overriding method with more logic
#include <iostream>
using namespace std;
class Media { public: virtual void play(){ cout<<"Media\n"; } };
class Video : public Media { public: void play(){ cout<<"Video\n"; } };
int main(){ 
    Media* m = new Video(); 
    m->play(); 
}
/* 
Output
Video
*/


//✅ 20. Composition + IS-A mix: Engine inside SportsCar
#include <iostream>
using namespace std;
class Engine { public: int hp; Engine(int h):hp(h){} };
class Vehicle { public: virtual void show()=0; };
class SportsCar : public Vehicle {  // IS-A Vehicle
    Engine e; // HAS-A Engine
  public:
    SportsCar() : e(900) {}
    void show(){ cout<<"HP "<<e.hp; }
};
int main(){ 
    SportsCar s; 
    s.show(); 
}
/* 
Output
HP 900
*/



























