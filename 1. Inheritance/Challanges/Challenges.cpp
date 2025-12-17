
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
    virtual void start() { 
      cout << "Car starts\n"; 
    }
};
class SportsCar : public Car {
 public:
    void start() override { 
      cout << "SportsCar starts fast\n"; 
    }
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
    void show() { 
      cout << "x = " << x << "\n"; 
    }
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
    A() { 
      cout << "A ctor\n"; 
    }
};
class B : public A {
  public:
    B() { 
      cout << "B ctor\n"; 
    }
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
    ~A() { 
      cout << "A dtor\n"; 
    }
};
class B : public A {
  public:
    ~B() { 
      cout << "B dtor\n"; 
    }
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
class A { 
  public: 
    void fun(){ 
      cout << "A fun\n"; 
    } 
};
class B { 
  public: 
    void fun(){ 
      cout << "B fun\n"; 
    } 
};
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
class A { 
  public: 
     int x = 10; 
};
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

/* ==================================================================== */

//✅ SECTION 2 — HAS-A Composition (Strong Ownership) — 6 Challenges
//Challenge 9 — Composition Basic
#include <iostream>
using namespace std;
class Engine {
  public:
    void start() { 
      cout << "Engine start\n"; 
    }
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


//Composition using std::unique_ptr (OWNERSHIP)
//Car exclusively owns Engine
#include <iostream>
#include <memory>
using namespace std;
class Engine {
 public:
    void start() {
        cout << "Engine start\n";
    }
};
class Car {
  private:
    unique_ptr<Engine> eng;   // ✅ Composition (exclusive ownership)
  public:
    Car() : eng(make_unique<Engine>()) {}  // Car creates & owns Engine

    void run() {
        eng->start();
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

Why this is composition
Car owns Engine
Engine lifetime == Car lifetime
Cannot be shared or copied
Engine destroyed automatically when Car is destroyed
✔️ Heap-based composition 
*/



/* ---------------------------------------------------- */
//Using std::shared_ptr (NOT composition) --Aggregation relation
//Engine lifetime is shared → NOT exclusive ownership

#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    void start() {
        cout << "Engine start\n";
    }
};
class Car {
  private:
    shared_ptr<Engine> eng;   // Aggregation - Engine can exist without Car
  public:
    Car(shared_ptr<Engine> e) : eng(e) {}
    void run() {
        eng->start();
        cout << "Car running\n";
    }
};
int main() {
    auto engine = make_shared<Engine>();
    Car c1(engine);
    Car c2(engine);   // same Engine shared

    c1.run();
    c2.run();
}
/* 
Output
Engine start
Car running
Engine start
Car running

Why this is NOT composition
Engine can exist without Car
Multiple Cars can share same Engine
Lifetime not tied to a single owner
❌ This is aggregation / shared association 
*/

/* ========================================================================================== */

//Challenge 10 — Composition: Constructor Initialization
#include <iostream>
using namespace std;
class Battery {
  public:
    Battery(int p){ 
      cout << "Battery: " << p << "%\n"; 
    }
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

/* ---------------------------------------------- */
Using std::unique_ptr (TRUE COMPOSITION)
Laptop exclusively owns Battery

#include <iostream>
#include <memory>
using namespace std;
class Battery {
  public:
    Battery(int p) {
        cout << "Battery: " << p << "%\n";
    }
};
class Laptop {
 private:
    unique_ptr<Battery> bat;   // ✅ Exclusive ownership

  public:
    Laptop() : bat(make_unique<Battery>(90)) {}
};
int main() {
    Laptop l;
}
/* 
Output
Battery: 90%

Why this is composition
Laptop creates the Battery
No other owner exists
Battery destroyed with Laptop
Heap-based exclusive ownership
*/

/* ------------------------------------------------------ */
❌ 2️⃣ Using std::shared_ptr (NOT COMPOSITION)--Aggregation
Battery ownership is shared

#include <iostream>
#include <memory>
using namespace std;
class Battery {
  public:
    Battery(int p) {
        cout << "Battery: " << p << "%\n";
    }
};
class Laptop {
  private:
    shared_ptr<Battery> bat;   // ❌ Shared ownership
  public:
    Laptop(shared_ptr<Battery> b) : bat(b) {}
};
int main() {
    auto battery = make_shared<Battery>(90);

    Laptop l1(battery);
    Laptop l2(battery);   // Same Battery shared
}
/* 
Output
Battery: 90%

(Constructed only once, shared by both laptops)
*/


/* ============================================================================================== */

//Challenge 11 — Composition: Nested Object Behavior
#include <iostream>
using namespace std;
class Address {
  public:
    void print() { 
      cout << "City: Delhi\n"; 
    }
};
class Person {
    Address addr;
  public:
    void showAddress() { 
      addr.print(); 
    }
};
int main() {
    Person p;
    p.showAddress();
}
/* 
Output
City: Delhi
*/

/* --------------------------------------------------- */

Using std::unique_ptr — Composition (Exclusive Ownership)

#include <iostream>
#include <memory>
using namespace std;
class Address {
  public:
    void print() {
        cout << "City: Delhi\n";
    }
};
class Person {
 private:
    unique_ptr<Address> addr;   // ✅ Composition
 public:
    Person() : addr(make_unique<Address>()) {}
    void showAddress() {
        addr->print();
    }
};
int main() {
    Person p;
    p.showAddress();
}
/* 
Output
City: Delhi

Why this is composition
Person creates the Address
No other object can own or share it
Address lifetime == Person lifetime
*/
/* ------------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Shared Ownership (Aggregation)
#include <iostream>
#include <memory>
using namespace std;
class Address {
  public:
    void print() {
        cout << "City: Delhi\n";
    }
};
class Person {
  private:
    shared_ptr<Address> addr;   // ❌ Shared ownership

  public:
    Person(shared_ptr<Address> a) : addr(a) {}

    void showAddress() {
        addr->print();
    }
};
int main() {
    auto sharedAddress = make_shared<Address>();

    Person p1(sharedAddress);
    Person p2(sharedAddress);   // Same Address shared

    p1.showAddress();
    p2.showAddress();
}
/* 
Output
City: Delhi
City: Delhi
*/


/* ================================================================================================ */

//Challenge 12 — Composition with Multiple Objects
#include <iostream>
using namespace std;
class Wheel { 
  public: 
    Wheel() { 
      cout << "Wheel created\n"; 
    } 
};
class Bike {
    Wheel w1, w2;
  public:
    Bike() { 
      cout << "Bike constructed\n"; 
    }
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
/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (Exclusive Ownership)
#include <iostream>
#include <memory>
using namespace std;
class Wheel {
 public:
    Wheel() {
        cout << "Wheel created\n";
    }
};
class Bike {
 private:
    unique_ptr<Wheel> w1;
    unique_ptr<Wheel> w2;   // ✅ Exclusive ownership

 public:
    Bike()
        : w1(make_unique<Wheel>()),
          w2(make_unique<Wheel>()) {
        cout << "Bike constructed\n";
    }
};
int main() {
    Bike b;
}
/* 
Output
Wheel created
Wheel created
Bike constructed

Why this is composition
Bike creates both wheels
Each wheel has exactly one owner
Wheels cannot outlive the bike
*/

/* ----------------------------------------------------- */
❌ 2️⃣ Using std::shared_ptr — Shared Ownership (Aggregation)
#include <iostream>
#include <memory>
using namespace std;
class Wheel {
  public:
    Wheel() {
        cout << "Wheel created\n";
    }
};
class Bike {
  private:
    shared_ptr<Wheel> w1;
    shared_ptr<Wheel> w2;   // ❌ Shared ownership

  public:
    Bike(shared_ptr<Wheel> a, shared_ptr<Wheel> b)
        : w1(a), w2(b) {
        cout << "Bike constructed\n";
    }
};
int main() {
    auto frontWheel = make_shared<Wheel>();
    auto rearWheel  = make_shared<Wheel>();

    Bike b(frontWheel, rearWheel);

    // Wheels may outlive Bike
}
/* 
Output
Wheel created
Wheel created
Bike constructed
*/



/* ====================================================================================================== */
//Challenge 13 — Composition Destruction Order
#include <iostream>
using namespace std;
class A { 
  public: 
    ~A(){ 
      cout << "A destroyed\n"; 
    } 
};
class B { 
  public: 
    ~B(){ 
      cout << "B destroyed\n"; 
    } 
};
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

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (C OWNS A and B)
C exclusively owns its members. Destructor order is automatically handled.

#include <iostream>
#include <memory>
using namespace std;
class A {
  public:
    ~A() {
        cout << "A destroyed\n";
    }
};
class B {
  public:
    ~B() {
        cout << "B destroyed\n";
    }
};
class C {
  private:
    unique_ptr<A> a;
    unique_ptr<B> b;

  public:
    C() : a(make_unique<A>()), b(make_unique<B>()) {}

    // Destructor automatically called, no manual deletion needed
};

int main() {
    C c;
}
/* 
Expected Output
B destroyed
A destroyed

Why this is composition
C owns A and B
Exclusive ownership (unique_ptr)
Destruction happens automatically in reverse order of initialization
Lifetime bound to C
*/

/* ----------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Ownership)
A and B can exist independently and be shared across multiple C objects.

#include <iostream>
#include <memory>
using namespace std;
class A {
  public:
    ~A() {
        cout << "A destroyed\n";
    }
};
class B {
  public:
    ~B() {
        cout << "B destroyed\n";
    }
};
class C {
  public:
    shared_ptr<A> a;
    shared_ptr<B> b;

    C(const shared_ptr<A>& a_ptr, const shared_ptr<B>& b_ptr) 
        : a(a_ptr), b(b_ptr) {}
};
int main() {
    auto a_ptr = make_shared<A>();
    auto b_ptr = make_shared<B>();

    C c1(a_ptr, b_ptr);
    C c2(a_ptr, b_ptr);  // same A and B shared

    // Destruction happens when last shared_ptr goes out of scope
}
/* 
Expected Output
A destroyed
B destroyed

(Destruction may occur later, only when the last shared_ptr goes out of scope.)
*/



/* ============================================================================================================= */
//Challenge 14 — Forcing Dependency in Composition
#include <iostream>
using namespace std;
class CPU {
  public:
    CPU(){ 
      cout << "CPU ready\n"; 
    }
};
class Computer {
    CPU cpu;
  public:
    Computer(){ 
      cout << "Computer ON\n"; 
    }
};
int main() {
    Computer c;
}
/* 
Output
CPU ready
Computer ON
*/



/* ======================================================== */

//✅ SECTION 3 — HAS-A Aggregation (Weak Ownership) — 6 Challenges
//Challenge 15 — Aggregation Basic
#include <iostream>
using namespace std;
class Engine {
  public:
    void start(){ 
      cout << "Engine start\n"; 
    }
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

/* ======================================================== */
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
    void print(){ 
      cout << "Teacher: " << t->name << "\n"; 
    }
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


/* ======================================================== */
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
    void show(){ 
      cout << addr->city << "\n"; 
    }
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

/* ======================================================== */
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
    void add(Book* b){ 
      books.push_back(b); 
    }
    void show(){
        for(auto b: books) 
           cout << b->name << "\n";
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

/* ======================================================== */

//Challenge 19 — Composition vs Aggregation Difference
#include <iostream>
using namespace std;
class Engine{
  public:
    Engine(){ 
      cout<<"Engine built\n"; 
    }
};
class Car{       // Composition
    Engine e;
  public:
    Car(){ 
      cout<<"Car built\n"; 
    }
};
class Person{    // Aggregation
    Engine* e;
  public:
    Person(Engine* ee):e(ee){}
    void show(){ 
      cout<<"Person owns engine externally\n"; 
    }
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

/* ======================================================== */
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
    void hire(Employee* e){ 
      emps.push_back(e); 
    }
    void list(){
        for(auto e: emps) 
          cout << e->name << "\n";
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


/* ======================================================== */










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
    double area() const override { 
      return 3.14 * r * r; 
    }
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

/* ======================================================== */

//✅ 2. Demonstrate HAS-A (Composition) with strong ownership
//Concept: Composition = lifetime ownership
//Question:
//A Car HAS-A Engine (Engine is destroyed with Car).

//Code
#include <iostream>
using namespace std;
class Engine {
  public:
    Engine() { 
      cout << "Engine constructed\n"; 
    }
    ~Engine() { 
      cout << "Engine destroyed\n"; 
    }
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
/* ======================================================== */

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
/* ----------------------------------------- */
//Aggregation keeping object in private
#include <iostream>
using namespace std;
class Player {
  public:
    string name;
    Player(string n) : name(n) {}
};

class Team {
  private:
    Player* p;   // aggregation: NOT owned

  public:
    explicit Team(Player* player) : p(player) {}

    void showPlayer() const {
        cout << p->name;
    }
};

int main() {
    Player p("Ronaldo");
    Team t(&p);
    t.showPlayer();
}
/*
Ronaldo
*/

/* ---------------------------------------- */
//Composition using std::unique_ptr (Team OWNS Player)
#include <iostream>
#include <memory>
using namespace std;
class Player {
  public:
    string name;
    Player(string n) : name(n) {}
};
class Team {
  private:
    unique_ptr<Player> p;   // ✅ Composition (owned)

  public:
    Team(string playerName): p(make_unique<Player>(playerName)) {}

    void show() const {
        cout << p->name;
    }
};
int main() {
    Team t("Ronaldo");
    t.show();
}
/* 
Output
Ronaldo
*/


/* ======================================================== */

//✅ 4. IS-A with multiple levels (multilevel inheritance)
//Question:
//Implement Animal → Mammal → Dog.

#include <iostream>
using namespace std;
class Animal { 
  public: 
    virtual void sound(){ 
      cout<<"Animal\n"; 
    } 
};
class Mammal: public Animal { 
    public: 
      void sound() override { 
        cout<<"Mammal\n"; 
      } 
};
class Dog : public Mammal { 
  public: 
    void sound() override { 
      cout<<"Dog\n"; 
    } 
};
int main(){ 
  Animal* a = new Dog(); 
  a->sound(); 
}
/* 
Output
Dog
*/

/* ======================================================== */

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
    void deposit(int amt) { 
      history.emplace_back("Deposit", amt); 
    }
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
/* ======================================================== */

//✅ 6. Aggregation challenge: University with Students
#include <iostream>
#include <vector>
using namespace std;
class Student { 
  public: 
    string name; 
    Student(string n):name(n){} 
};
class University {
  public:
    vector<Student*> students;  // aggregation
    void add(Student* s){ 
      students.push_back(s); 
    }
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
/* ======================================================== */

//✅ 7. IS-A: Pure virtual class (abstract)
#include <iostream>
using namespace std;
class Device { 
  public: 
     virtual void start()=0; 
};
class Laptop : public Device { 
  public: 
    void start(){ 
      cout<<"Laptop start\n"; 
    } 
};
int main(){ 
  Device* d=new Laptop(); 
  d->start(); 
}
/* 
Output
Laptop start
*/




/* ======================================================== */
//✅ 8. Composition: Laptop HAS-A Battery
#include <iostream>
using namespace std;
class Battery { 
  public: 
    Battery(){ 
      cout<<"Battery ok\n"; 
    } 
};
class Laptop { 
  Battery b; 
};
int main(){ 
  Laptop l; 
}
/* 
Output
Battery ok
*/

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (Laptop OWNS Battery)

#include <iostream>
#include <memory>
using namespace std;
class Battery {
  public:
    Battery() {
        cout << "Battery ok\n";
    }
};
class Laptop {
  private:
    unique_ptr<Battery> b;   // ✅ Composition
  public:
    Laptop() : b(make_unique<Battery>()) {}
};
int main() {
    Laptop l;
}
/* 
Output
Battery ok

Why this is composition
Laptop creates the Battery
Exclusive ownership (unique_ptr)
Battery lifetime == Laptop lifetime
*/

/* ------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Battery)
#include <iostream>
#include <memory>
using namespace std;
class Battery {
  public:
    Battery() {
        cout << "Battery ok\n";
    }
};
class Laptop {
  public:
    shared_ptr<Battery> b;   // ❌ Aggregation

    Laptop(const shared_ptr<Battery>& battery) : b(battery) {}
};
int main() {
    auto battery = make_shared<Battery>();

    Laptop l1(battery);
    Laptop l2(battery);   // Same battery shared
}
/* 
Output
Battery ok
*/


/* ======================================================== */

//✅ 9. Aggregation: Flight HAS-A Pilot (but does not own)
#include <iostream>
using namespace std;
class Pilot { 
  public: 
    string name; 
    Pilot(string n):name(n){} 
};
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

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (Flight OWNS Pilot)
The Flight creates, owns, and destroys its Pilot.

#include <iostream>
#include <memory>
using namespace std;
class Pilot {
  public:
    string name;
    Pilot(string n) : name(n) {}
};
class Flight {
  private:
    unique_ptr<Pilot> p;   // ✅ Composition
  public:
    Flight() : p(make_unique<Pilot>("Captain Z")) {}
    
    void showPilot() {
        cout << p->name;
    }
};
int main() {
    Flight f;
    f.showPilot();
}
/* 
Output
Captain Z

Why this is composition
Flight owns Pilot
Exclusive ownership (unique_ptr)
Pilot lifetime == Flight lifetime
*/
/* --------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Pilot)
Pilot exists independently and can be shared across flights.

#include <iostream>
#include <memory>
using namespace std;
class Pilot {
  public:
    string name;
    Pilot(string n) : name(n) {}
};
class Flight {
  public:
    shared_ptr<Pilot> p;   // ❌ Aggregation

    Flight(const shared_ptr<Pilot>& pilot) : p(pilot) {}
};
int main() {
    auto pilot = make_shared<Pilot>("Captain Z");

    Flight f1(pilot);
    Flight f2(pilot);   // Same pilot shared

    cout << f1.p->name;
}
/* 
Output
Captain Z
*/




/* ======================================================== */


//✅ 10. IS-A + HAS-A mixed
// Question:
// Ferrari IS-A Car
// Car HAS-A Engine

#include <iostream>
using namespace std;
class Engine { 
  public: 
    int hp; 
    Engine(int h):hp(h){} 
};
class Car {
  protected:
    Engine e;  // composition
  public:
    Car(int hp):e(hp){}
};
class Ferrari : public Car {  // IS-A
  public:
    Ferrari():Car(800){}
    void show(){ 
      cout<<"HP "<<e.hp; 
    }
};
int main(){ 
  Ferrari f; 
  f.show(); 
}
/* 
Output
HP 800
*/

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition + Inheritance
Ferrari IS-A Car
Car HAS-A Engine (exclusive ownership)

#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    int hp;
    Engine(int h) : hp(h) {}
};
class Car {
  protected:
    unique_ptr<Engine> e;   // ✅ Composition

  public:
    explicit Car(int hp) : e(make_unique<Engine>(hp)) {}
    virtual ~Car() = default;
};
class Ferrari : public Car {   // IS-A Car
  public:
    Ferrari() : Car(800) {}

    void show() {
        cout << "HP " << e->hp;
    }
};
int main() {
    Ferrari f;
    f.show();
}
/* 
Output
HP 800

Why this is correct composition
Car creates and owns Engine
Ferrari inherits ownership via Car
Engine lifetime == Car/Ferrari lifetime
No sharing possible
*/
/* -------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation + Inheritance
Engine lifetime is shared, not owned by Car

#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    int hp;
    Engine(int h) : hp(h) {}
};
class Car {
  protected:
    shared_ptr<Engine> e;   // ❌ Aggregation
  public:
    explicit Car(shared_ptr<Engine> engine) : e(engine) {}
    virtual ~Car() = default;
};
class Ferrari : public Car {
  public:
    Ferrari(shared_ptr<Engine> engine) : Car(engine) {}

    void show() {
        cout << "HP " << e->hp;
    }
};
int main() {
    auto engine = make_shared<Engine>(800);

    Ferrari f(engine);
    f.show();
}
/* 
Output
HP 800
*/











/* ======================================================== */

//✅ 11. Composition for resource management (RAII)
#include <iostream>
using namespace std;
class File {
  public: 
    File(){ 
      cout<<"Opened\n"; 
    }
    ~File(){ 
      cout<<"Closed\n"; 
    }
};
class Logger { 
  File f; 
}; // composition = RAII
int main(){ 
  Logger l; 
}
/* 
Output
Opened
Closed
*/

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (RAII, Exclusive Ownership)
Logger owns the File.
File opens on creation and closes when Logger is destroyed.

#include <iostream>
#include <memory>
using namespace std;
class File {
 public:
    File() {
        cout << "Opened\n";
    }
    ~File() {
        cout << "Closed\n";
    }
};
class Logger {
  private:
    unique_ptr<File> f;   // ✅ Composition (RAII)
  public:
    Logger() : f(make_unique<File>()) {}
};
int main() {
    Logger l;
}
/* 
Output
Opened
Closed

Why this is composition & RAII
Logger creates the File
Exclusive ownership (unique_ptr)
Destructor of File runs automatically
Perfect RAII semantics on the heap
*/

/* ---------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Resource)
File lifetime is not tied to Logger.

#include <iostream>
#include <memory>
using namespace std;
class File {
  public:
    File() {
        cout << "Opened\n";
    }
    ~File() {
        cout << "Closed\n";
    }
};
class Logger {
  private:
    shared_ptr<File> f;   // ❌ Aggregation
  public:
    Logger(const shared_ptr<File>& file) : f(file) {}
};
int main() {
    auto file = make_shared<File>();

    {
        Logger l1(file);
        Logger l2(file);   // same file shared
    }                     // File NOT closed yet

    // File closed only here
}
/* 
Output
Opened
Closed

(Closed only when last owner goes out of scope)
*/

/* ======================================================== */

//✅ 12. Aggregation in Observer Pattern
#include <iostream>
#include <vector>
using namespace std;
class Observer { 
  public: 
    virtual void update() = 0; 
};
class Subject {
  public:
    vector<Observer*> obs; // aggregation
    void add(Observer* o) { 
      obs.push_back(o); 
    }
    void notify() { 
      for (auto* o : obs) 
           o->update(); 
    }
};
class Listener : public Observer {
  public: 
    void update(){ 
      cout<<"Updated\n"; 
    }
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

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (Subject OWNS Observers)
Subject creates, owns, and destroys its observers.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Observer {
  public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};
class Subject {
  public:
    vector<unique_ptr<Observer>> obs;   // ✅ Composition

    void add(unique_ptr<Observer> o) {
        obs.push_back(std::move(o));
    }

    void notify() {
        for (auto& o : obs)
            o->update();
    }
};
class Listener : public Observer {
  public:
    void update() override {
        cout << "Updated\n";
    }
};
int main() {
    Subject s;
    s.add(make_unique<Listener>());
    s.notify();
}
/* 
Output
Updated

Why this is composition
Subject owns the observers
Observers cannot exist independently
Lifetime strictly controlled by Subject
*/

/* ---------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Observers Shared)
Observers exist independently and can subscribe/unsubscribe.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Observer {
  public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};
class Subject {
  public:
    vector<shared_ptr<Observer>> obs;   // ❌ Aggregation

    void add(const shared_ptr<Observer>& o) {
        obs.push_back(o);
    }

    void notify() {
        for (auto& o : obs)
            o->update();
    }
};
class Listener : public Observer {
  public:
    void update() override {
        cout << "Updated\n";
    }
};
int main() {
    auto l = make_shared<Listener>();

    Subject s;
    s.add(l);      // shared ownership
    s.notify();
}
/* 
Output
Updated
*/




/* ======================================================== */

//✅ 13. IS-A: using protected base methods
#include <iostream>
using namespace std;
class Base { 
  protected: 
     void msg(){ 
      cout<<"Base\n"; 
    } 
};
class Derived : public Base { 
  public: 
    void call(){ 
      msg(); 
    } 
};
int main(){ 
  Derived d; 
  d.call(); 
}
/* 
Output
Base
*/

/* ======================================================== */
//✅ 14. Composition: Game HAS-A PhysicsEngine
#include <iostream>
using namespace std;
class PhysicsEngine { 
  public: 
    void simulate(){ 
      cout<<"Simulate\n"; 
    } 
};
class Game {
    PhysicsEngine pe;  // composition
  public:
    void frame(){ 
      pe.simulate(); 
    }
};
int main(){ 
  Game g; 
  g.frame(); 
}
/* 
Output
Simulate
*/


/* ----------------------------------------------------- */

Using std::unique_ptr — Composition (Game OWNS PhysicsEngine)
#include <iostream>
#include <memory>
using namespace std;
class PhysicsEngine {
  public:
    void simulate() {
        cout << "Simulate\n";
    }
};
class Game {
  private:
    unique_ptr<PhysicsEngine> pe;   // ✅ Composition

  public:
    Game() : pe(make_unique<PhysicsEngine>()) {}

    void frame() {
        pe->simulate();
    }
};
int main() {
    Game g;
    g.frame();
}
/* 
Output
Simulate

Why this is composition
Game creates the PhysicsEngine
Exclusive ownership (unique_ptr)
Engine lifetime == Game lifetime
*/

/* ---------------------------------------------------- */
❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared PhysicsEngine)
#include <iostream>
#include <memory>
using namespace std;
class PhysicsEngine {
  public:
    void simulate() {
        cout << "Simulate\n";
    }
};
class Game {
  private:
    shared_ptr<PhysicsEngine> pe;   // ❌ Aggregation

  public:
    Game(shared_ptr<PhysicsEngine> engine) : pe(engine) {}

    void frame() {
        pe->simulate();
    }
};
int main() {
    auto engine = make_shared<PhysicsEngine>();

    Game g1(engine);
    Game g2(engine);   // Same engine shared

    g1.frame();
}
/* 
Output
Simulate
*/

/* ======================================================== */

//✅ 15. Aggregation: City HAS-A list of Buildings
#include <iostream>
#include <vector>
using namespace std;
class Building { 
  public: 
    string name; 
    Building(string n):name(n){} 
};
class City {
  public:
    vector<Building*> b; // aggregation
};
int main(){
    Building b1("Mall"), b2("Hospital");
    City c; 
    c.b={&b1,&b2};
    cout<<c.b[0]->name;
}
/* 
Output
Mall
*/

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (City OWNS Buildings)
Buildings are created, owned, and destroyed by City.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Building {
 public:
    string name;
    Building(string n) : name(n) {}
};
class City {
  public:
    vector<unique_ptr<Building>> b;   // ✅ Composition

    void addBuilding(const string& name) {
        b.push_back(make_unique<Building>(name));
    }
};
int main() {
    City c;
    c.addBuilding("Mall");
    c.addBuilding("Hospital");

    cout << c.b[0]->name;
}
/* 
Output
Mall

Why this is composition
City creates Building
Exclusive ownership (unique_ptr)
Buildings cannot exist without the City
*/
/* --------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Buildings)
Buildings can exist independently and be shared across cities.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Building {
  public:
    string name;
    Building(string n) : name(n) {}
};
class City {
  public:
    vector<shared_ptr<Building>> b;   // ❌ Aggregation
};
int main() {
    auto b1 = make_shared<Building>("Mall");
    auto b2 = make_shared<Building>("Hospital");

    City c1;
    c1.b = { b1, b2 };

    City c2;
    c2.b.push_back(b1);   // Same Mall shared by another city

    cout << c1.b[0]->name;
}
/* 
Output
Mall
*/




/* ======================================================== */
//✅ 16. IS-A: Multiple inheritance (Interface style)
#include <iostream>
using namespace std;
class Drawable { 
   public: 
     virtual void draw()=0; 
};
class Movable { 
   public: 
     virtual void move()=0; 
};
class Sprite : public Drawable, public Movable {
  public:
    void draw(){ 
      cout<<"Draw\n"; 
    }
    void move(){ 
      cout<<"Move\n"; 
    }
};
int main(){
    Sprite s; 
    s.draw(); 
    s.move();
}
/* 
Output
Draw
Move
*/

/* ======================================================== */
//✅ 17. Composition: Stack HAS-A vector
#include <iostream>
#include <vector>
using namespace std;
class Stack {
    vector<int> data; // composition
  public:
    void push(int x){ 
      data.push_back(x); 
    }
    int top(){ 
      return data.back(); 
    }
};
int main(){ 
  Stack s; 
  s.push(10); 
  cout<<s.top(); 
}
/* 
Output
10
*/

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (Stack OWNS its data)
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Stack {
 private:
    unique_ptr<vector<int>> data;   // ✅ Composition

 public:
    Stack() : data(make_unique<vector<int>>()) {}

    void push(int x) {
        data->push_back(x);
    }

    int top() {
        return data->back();
    }
};
int main() {
    Stack s;
    s.push(10);
    cout << s.top();
}
/* 
Output
10

Why this is composition
Stack creates the vector
Exclusive ownership (unique_ptr)
Vector lifetime == Stack lifetime
*/

/* ------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Data)
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Stack {
  private:
    shared_ptr<vector<int>> data;   // ❌ Aggregation
  public:
    Stack(shared_ptr<vector<int>> d) : data(d) {}

    void push(int x) {
        data->push_back(x);
    }

    int top() {
        return data->back();
    }
};
int main() {
    auto sharedData = make_shared<vector<int>>();

    Stack s1(sharedData);
    Stack s2(sharedData);   // Same underlying storage

    s1.push(10);
    cout << s2.top();       // 10 (shared!)
}
/* 
Output
10
*/





/* ======================================================== */
//✅ 18. Aggregation: Company HAS-A Employees
#include <iostream>
#include <vector>
using namespace std;
class Employee { 
  public: 
    string name; 
    Employee(string n):name(n){} 
};
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
/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (Company OWNS Employees)
Employees are created, owned, and destroyed by Company.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Employee {
  public:
    string name;
    Employee(string n) : name(n) {}
};
class Company {
  public:
    vector<unique_ptr<Employee>> e;   // ✅ Composition

    void hire(string name) {
        e.push_back(make_unique<Employee>(name));
    }
};
int main() {
    Company c;
    c.hire("John");

    cout << c.e[0]->name;
}
/* 
Output
John

Why this is composition
Company creates Employee
Exclusive ownership (unique_ptr)
Employee lifetime == Company lifetime
*/
/* ----------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Aggregation (Shared Ownership)
Employees can exist independently and be shared.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Employee {
  public:
    string name;
    Employee(string n) : name(n) {}
};
class Company {
  public:
    vector<shared_ptr<Employee>> e;   // ❌ Aggregation
};
int main() {
    auto e1 = make_shared<Employee>("John");

    Company c;
    c.e.push_back(e1);   // Company references employee

    cout << c.e[0]->name;
}
/* 
Output
John
*/

/* ======================================================== */

//✅ 19. IS-A: Overriding method with more logic
#include <iostream>
using namespace std;
class Media { 
  public: 
    virtual void play(){ 
      cout<<"Media\n"; 
    } 
};
class Video : public Media { 
   public: 
      void play(){ 
        cout<<"Video\n"; 
      } 
};
int main(){ 
    Media* m = new Video(); 
    m->play(); 
}
/* 
Output
Video
*/







/* ======================================================== */
//✅ 20. Composition + IS-A mix: Engine inside SportsCar
#include <iostream>
using namespace std;
class Engine { 
  public: 
    int hp; 
    Engine(int h):hp(h){} 
};
class Vehicle { 
  public: 
    virtual void show()=0; 
};
class SportsCar : public Vehicle {  // IS-A Vehicle
    Engine e; // HAS-A Engine
  public:
    SportsCar() : e(900) {}
    void show(){ 
      cout<<"HP "<<e.hp; 
    }
};
int main(){ 
    SportsCar s; 
    s.show(); 
}
/* 
Output
HP 900
*/

/* -------------------------------------------------------- */

Using std::unique_ptr — Composition (HAS-A Engine)
SportsCar exclusively owns its Engine

#include <iostream>
#include <memory>
using namespace std;
class Engine {
 public:
    int hp;
    Engine(int h) : hp(h) {}
};
class Vehicle {
 public:
    virtual void show() = 0;
    virtual ~Vehicle() = default;
};
class SportsCar : public Vehicle {   // IS-A Vehicle
  private:
    unique_ptr<Engine> e;             // ✅ HAS-A (composition)

  public:
    SportsCar() : e(make_unique<Engine>(900)) {}

    void show() override {
        cout << "HP " << e->hp;
    }
};
int main() {
    SportsCar s;
    s.show();
}
/* 
Output
HP 900

Why this is correct composition
SportsCar creates and owns Engine
No other object can share it
Engine lifetime == SportsCar lifetime
*/

/* --------------------------------------------------------- */

❌ 2️⃣ Using std::shared_ptr — Shared Ownership (NOT Composition)
Engine ownership can be shared → Aggregation

#include <iostream>
#include <memory>
using namespace std;
class Engine {
 public:
    int hp;
    Engine(int h) : hp(h) {}
};
class Vehicle {
  public:
    virtual void show() = 0;
    virtual ~Vehicle() = default;
};
class SportsCar : public Vehicle {
  private:
    shared_ptr<Engine> e;   // ❌ Shared ownership

  public:
    SportsCar(shared_ptr<Engine> engine) : e(engine) {}

    void show() override {
        cout << "HP " << e->hp;
    }
};
int main() {
    auto engine = make_shared<Engine>(900);

    SportsCar s1(engine);
    SportsCar s2(engine);   // Same engine shared

    s1.show();
}
/* 
Output
HP 900
*/


/* ======================================================== */


















// 1. Ride Sharing System (Uber-like)
// Car IS-A Vehicle
// Trip HAS-A Driver, Rider, Vehicle

#include <iostream>
#include <string>
using namespace std;
class Vehicle {
 public:
    virtual string type() const = 0;
};
class Car : public Vehicle {                     // IS-A
 public:
    string type() const override { 
      return "Car"; 
    }
};
class Driver { 
  public: 
    string name; 
    Driver(string n):name(n){} 
};
class Rider  { 
  public: 
    string name; 
    Rider(string n):name(n){} 
};
class Trip {                                     // HAS-A
    Driver* d;
    Rider* r;
    Vehicle* v;
  public:
    Trip(Driver* D, Rider* R, Vehicle* V) : d(D), r(R), v(V) {}
    void start() {
        cout << r->name << " riding with " << d->name << " in a " << v->type();
    }
};
int main() {
    Car c;
    Driver d("Alex");
    Rider  r("Bob");
    Trip t(&d, &r, &c);
    t.start();
}
/* 
Bob riding with Alex in a Car
*/




// 2. Online Shopping System
// CreditCard IS-A PaymentMethod
// Order HAS-A Cart

#include <iostream>
#include <vector>
using namespace std;

class PaymentMethod {
  public: virtual void pay(double amt)=0; 
};

class CreditCard : public PaymentMethod {        // IS-A
  public: 
    void pay(double amt){ 
      cout<<"Paid "<<amt<<" using Card"; 
    } 
};
class Cart {
    vector<int> items;                           // HAS-A
  public:
    void add(int price){ 
      items.push_back(price); 
    }
    int total() { 
      int sum=0; 
      for(int x:items) 
        sum+=x; 
      return sum; 
    }
};
class Order {
    Cart c;                                      // composition
  public:
    void addItem(int price){ 
      c.add(price); 
    }
    void checkout(PaymentMethod& p){ 
      p.pay(c.total()); 
    }
};
int main(){
    Order o;
    o.addItem(100); o.addItem(200);
    CreditCard cc;
    o.checkout(cc);
}
/* 
Paid 300 using Card
*/



// 3. Media Player System
// AudioPlayer & VideoPlayer IS-A Player
// Playlist HAS-A vector<Player>*

#include <iostream>
#include <vector>
using namespace std;

class Player { 
  public: 
    virtual void play()=0; 
};

class AudioPlayer : public Player {              // IS-A
  public: void play(){ 
    cout<<"Playing audio\n"; 
  } 
};

class VideoPlayer : public Player {              // IS-A
  public: 
    void play(){ 
      cout<<"Playing video\n"; 
    } 
};
class Playlist {
    vector<Player*> plist;                       // aggregation
  public:
    void add(Player* p){ 
      plist.push_back(p); 
    }
    void playAll(){ 
      for(auto* p:plist) 
        p->play(); 
    }
};
int main(){
    AudioPlayer a;
    VideoPlayer v;
    Playlist p;
    p.add(&a);
    p.add(&v);
    p.playAll();
}
/* 
Playing audio
Playing video
*/





// 4. Airport Management System
// CargoPlane IS-A Plane
// Airport HAS-A list<Plane>*
#include <iostream>
#include <list>
using namespace std;

class Plane { 
  public: 
    virtual void land()=0; 
};

class CargoPlane : public Plane {                // IS-A
  public: 
    void land(){ 
       cout<<"Cargo plane landing\n"; 
    } 
};

class PassengerPlane : public Plane {            // IS-A
  public: 
    void land(){ 
      cout<<"Passenger plane landing\n"; 
    } 
};

class Airport {
    list<Plane*> runway;                         // aggregation
  public:
    void requestLanding(Plane* p){ 
      runway.push_back(p); 
    }
    void process(){ 
      for(auto* p:runway) 
        p->land(); 
    }
};

int main(){
    CargoPlane c;
    PassengerPlane p;
    Airport a;
    a.requestLanding(&c);
    a.requestLanding(&p);
    a.process();
}
/* 
Cargo plane landing
Passenger plane landing
*/



//5. Hospital Management System
//Surgeon IS-A Doctor
//Surgery HAS-A Doctor & Patient
#include <iostream>
using namespace std;
class Doctor { 
    public: 
      virtual string role()=0;
};

class Surgeon : public Doctor {                  // IS-A
  public: 
    string role(){ 
      return "Surgeon"; 
    } 
};

class Patient { 
  public: 
    string name; 
    Patient(string n):name(n){} 
};
class Surgery {                                  // HAS-A
    Doctor* d;
    Patient* p;
  public:
    Surgery(Doctor* D, Patient* P) : d(D), p(P) {}
    void perform(){ 
      cout<<d->role()<<" operating "<<p->name; 
    }
};
int main(){
    Surgeon s;
    Patient p("Ravi");
    Surgery op(&s, &p);
    op.perform();
}
/* 
Surgeon operating Ravi
*/


//6. Banking System
//SavingsAccount IS-A Account
//Bank HAS-A vector<Account>*
#include <iostream>
#include <vector>
using namespace std;

class Account { 
    public: 
      virtual void show()=0; 
};

class SavingsAccount : public Account {          // IS-A
  public: 
    void show(){ 
      cout<<"Savings account\n"; 
    } 
};

class CurrentAccount : public Account {          // IS-A
  public: 
    void show(){ 
      cout<<"Current account\n"; 
    } 
};
class Bank {
    vector<Account*> acc;                        // aggregation
  public:
    void add(Account* a){ 
      acc.push_back(a); 
    }
    void list(){ 
      for(auto* a:acc) 
        a->show(); 
      }
};
int main(){
    SavingsAccount s;
    CurrentAccount c;
    Bank b;
    b.add(&s);
    b.add(&c);
    b.list();
}
/* 
Savings account
Current account
*/


//7. Hotel Booking System
//DeluxeRoom IS-A Room
//Booking HAS-A Room + Customer
#include <iostream>
using namespace std;

class Room { 
  public: 
    virtual string type()=0; 
};

class DeluxeRoom : public Room {                 // IS-A
  public: 
    string type(){ 
      return "Deluxe"; 
    } 
};

class Customer { 
  public: 
    string name; 
    Customer(string n):name(n){} 
};

class Booking {
    Room* r; Customer* c;                        // aggregation
   public:
    Booking(Room* R, Customer* C):r(R),c(C){}
    void show(){ 
      cout<<c->name<<" booked "<<r->type(); 
    }
};

int main(){
    DeluxeRoom d;
    Customer c("Aman");
    Booking b(&d,&c);
    b.show();
}
/* 
Aman booked Deluxe
*/


//8. Game Engine System
//Enemy IS-A Entity
//GameWorld HAS-A vector<Entity>*
#include <iostream>
#include <vector>
using namespace std;
class Entity { 
    public: 
      virtual void update()=0; 
};

class Enemy : public Entity {                    // IS-A
  public: 
    void update(){ 
      cout<<"Enemy update\n"; 
    } 
};

class Player : public Entity {                   // IS-A
  public: 
    void update(){ 
      cout<<"Player update\n"; 
    } 
};
class GameWorld {
    vector<Entity*> ents;                        // aggregation
  public:
    void add(Entity* e){ 
      ents.push_back(e);
    }
    void tick(){ 
      for(auto* e:ents) 
        e->update(); 
    }
};
int main(){
    Enemy e;
    Player p;
    GameWorld g;
    g.add(&e);
    g.add(&p);
    g.tick();
}
/* 
Enemy update
Player update
*/



//9. Database Connection Manager
//MySQLConnection IS-A DBConnection
//Repository HAS-A DBConnection
#include <iostream>
using namespace std;

class DBConnection { 
    public: 
      virtual void connect()=0; 
};

class MySQLConnection : public DBConnection {    // IS-A
  public: 
    void connect(){ 
      cout<<"MySQL connected\n"; 
    } 
};

class Repository {
    DBConnection& db;                            // HAS-A
  public:
    Repository(DBConnection& d):db(d){}
    void load(){ 
      db.connect(); 
    }
};
int main(){
    MySQLConnection m;
    Repository r(m);
    r.load();
}
/* 
MySQL connected
*/





//10. Messaging System
//Email IS-A Notification
//Notifier HAS-A Notification
#include <iostream>
using namespace std;
class Notification { 
    public: 
      virtual void send()=0;
};

class Email : public Notification {              // IS-A
   public: 
     void send(){ 
      cout<<"Email sent\n"; 
    } 
};

class SMS : public Notification {                // IS-A
  public: 
    void send(){ 
      cout<<"SMS sent\n"; 
    } 
};
class Notifier {
    Notification* n;                             // aggregation
  public:
    Notifier(Notification* N):n(N){}
    void alert(){ 
      n->send(); 
    }
};
int main(){
    SMS s;
    Notifier n(&s);
    n.alert();
}
/* 
SMS sent
*/





//11. E-commerce Inventory System
//Laptop IS-A Product
//Warehouse HAS-A Product inventory
#include <iostream>
#include <vector>
using namespace std;
class Product { 
    public: 
    virtual void info()=0; 
};

class Laptop : public Product {                  // IS-A
  public: 
    void info(){ 
      cout<<"Laptop\n"; 
    } 
};

class Phone : public Product {                   // IS-A
  public: 
    void info(){ 
      cout<<"Phone\n"; 
    } 
};
class Warehouse {
    vector<Product*> items;                      // aggregation
  public:
    void add(Product* p){ 
      items.push_back(p); 
    }
    void print(){ 
      for(auto* p:items) 
        p->info(); 
    }
};
int main(){
    Laptop l; Phone p;
    Warehouse w;
    w.add(&l); w.add(&p);
    w.print();
}
/* 
Laptop
Phone
*/




//12. Smart Home Automation
//Light IS-A Device
//Home HAS-A vector<Device>*
#include <iostream>
#include <vector>
using namespace std;
class Device { 
   public: 
     virtual void on()=0; 
};
class Light : public Device {                    // IS-A
  public: 
    void on(){ 
      cout<<"Light on\n"; 
    } 
};

class Fan : public Device {                      // IS-A
  public: 
    void on(){ 
      cout<<"Fan on\n"; 
    } 
};
class Home {
    vector<Device*> d;                           // aggregation
  public:
    void add(Device* x){ 
      d.push_back(x); 
    }
    void activate(){ 
      for(auto* x:d) 
        x->on(); 
    }
};
int main(){
    Light l; Fan f;
    Home h;
    h.add(&l); h.add(&f);
    h.activate();
}
/* 
Light on
Fan on
*/




//13. Logistics Delivery System
//Truck IS-A Vehicle
//Delivery HAS-A Vehicle + Package
#include <iostream>
using namespace std;
class Vehicle { 
  public: 
    virtual void move()=0; 
};
class Truck : public Vehicle {                   // IS-A
  public: 
    void move(){ 
      cout<<"Truck moving\n"; 
    } 
};

class Package { 
  public: 
    string id; 
    Package(string i):id(i){} 
};

class Delivery {
    Vehicle* v; Package* p;                      // aggregation
  public:
    Delivery(Vehicle* V, Package* P):v(V),p(P){}
    void send(){ 
       v->move(); 
       cout<<"Package "<<p->id; 
    }
};
int main(){
    Truck t;
    Package p("BX101");
    Delivery d(&t,&p);
    d.send();
}
/* 
Truck moving
Package BX101
*/


//14. Payroll Processing System
//FullTimeEmployee IS-A Employee
//Payroll HAS-A vector<Employee>*
#include <iostream>
#include <vector>
using namespace std;
class Employee { 
  public: 
    virtual int salary()=0; 
};
class FullTimeEmployee : public Employee {       // IS-A
  public: 
    int salary(){ 
      return 5000; 
    } 
};
class PartTimeEmployee : public Employee {       // IS-A
  public: 
    int salary(){ 
      return 2000; 
    } 
};
class Payroll {
    vector<Employee*> emps;                      // aggregation
  public:
    void add(Employee* e){ 
      emps.push_back(e); 
    }
    int total(){ 
      int s=0; 
      for(auto* e:emps) 
        s+=e->salary(); 
      return s; 
    }
};
int main(){
    FullTimeEmployee f; 
    PartTimeEmployee p;
    Payroll pay;
    pay.add(&f); pay.add(&p);
    cout<<pay.total();
}
/* 
7000
*/



//15. Library Management System
//EBook IS-A Book
//Library HAS-A list<Book>*
#include <iostream>
#include <list>
using namespace std;
class Book { 
    public: 
      virtual string format()=0; 
};
class EBook : public Book {                      // IS-A
  public: 
  string format(){ 
    return "EBook"; 
  } 
};
class PaperBook : public Book {                  // IS-A
  public: 
    string format(){ 
      return "PaperBook"; 
    } 
};

class Library {
    list<Book*> books;                           // aggregation
  public:
    void add(Book* b){ 
      books.push_back(b); 
    }
    void show(){ 
      for(auto* b:books) 
        cout<<b->format()<<endl; 
    }
};
int main(){
    EBook e; PaperBook p;
    Library l;
    l.add(&e); l.add(&p);
    l.show();
}
/* 
Output:
EBook
PaperBook
*/




