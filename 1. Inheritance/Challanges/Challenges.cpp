
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
    string type() const override { return "Car"; }
};
class Driver { public: string name; Driver(string n):name(n){} };
class Rider  { public: string name; Rider(string n):name(n){} };
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





// 2. Online Shopping System
// CreditCard IS-A PaymentMethod
// Order HAS-A Cart

#include <iostream>
#include <vector>
using namespace std;

class PaymentMethod {
public: virtual void pay(double amt)=0; };

class CreditCard : public PaymentMethod {        // IS-A
public: void pay(double amt){ cout<<"Paid "<<amt<<" using Card"; } };
class Cart {
    vector<int> items;                           // HAS-A
  public:
    void add(int price){ items.push_back(price); }
    int total() { int sum=0; for(int x:items) sum+=x; return sum; }
};
class Order {
    Cart c;                                      // composition
  public:
    void addItem(int price){ c.add(price); }
    void checkout(PaymentMethod& p){ p.pay(c.total()); }
};
int main(){
    Order o;
    o.addItem(100); o.addItem(200);
    CreditCard cc;
    o.checkout(cc);
}




// 3. Media Player System
// AudioPlayer & VideoPlayer IS-A Player
// Playlist HAS-A vector<Player>*

#include <iostream>
#include <vector>
using namespace std;

class Player { public: virtual void play()=0; };

class AudioPlayer : public Player {              // IS-A
public: void play(){ cout<<"Playing audio\n"; } };

class VideoPlayer : public Player {              // IS-A
public: void play(){ cout<<"Playing video\n"; } };
class Playlist {
    vector<Player*> plist;                       // aggregation
  public:
    void add(Player* p){ plist.push_back(p); }
    void playAll(){ for(auto* p:plist) p->play(); }
};
int main(){
    AudioPlayer a;
    VideoPlayer v;
    Playlist p;
    p.add(&a);
    p.add(&v);
    p.playAll();
}



// 4. Airport Management System
// CargoPlane IS-A Plane
// Airport HAS-A list<Plane>*
#include <iostream>
#include <list>
using namespace std;

class Plane { public: virtual void land()=0; };

class CargoPlane : public Plane {                // IS-A
public: void land(){ cout<<"Cargo plane landing\n"; } };

class PassengerPlane : public Plane {            // IS-A
public: void land(){ cout<<"Passenger plane landing\n"; } };

class Airport {
    list<Plane*> runway;                         // aggregation
public:
    void requestLanding(Plane* p){ runway.push_back(p); }
    void process(){ for(auto* p:runway) p->land(); }
};

int main(){
    CargoPlane c;
    PassengerPlane p;
    Airport a;
    a.requestLanding(&c);
    a.requestLanding(&p);
    a.process();
}




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
    string role(){ return "Surgeon"; } 
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
    void perform(){ cout<<d->role()<<" operating "<<p->name; }
};
int main(){
    Surgeon s;
    Patient p("Ravi");
    Surgery op(&s, &p);
    op.perform();
}



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
    void show(){ cout<<"Savings account\n"; } 
};

class CurrentAccount : public Account {          // IS-A
  public: 
    void show(){ cout<<"Current account\n"; } 
};
class Bank {
    vector<Account*> acc;                        // aggregation
  public:
    void add(Account* a){ acc.push_back(a); }
    void list(){ for(auto* a:acc) a->show(); }
};
int main(){
    SavingsAccount s;
    CurrentAccount c;
    Bank b;
    b.add(&s);
    b.add(&c);
    b.list();
}



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
    string type(){ return "Deluxe"; } 
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
    void show(){ cout<<c->name<<" booked "<<r->type(); }
};

int main(){
    DeluxeRoom d;
    Customer c("Aman");
    Booking b(&d,&c);
    b.show();
}



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
    void update(){ cout<<"Enemy update\n"; } 
};

class Player : public Entity {                   // IS-A
  public: 
    void update(){ cout<<"Player update\n"; } 
};
class GameWorld {
    vector<Entity*> ents;                        // aggregation
  public:
    void add(Entity* e){ ents.push_back(e); }
    void tick(){ for(auto* e:ents) e->update(); }
};
int main(){
    Enemy e;
    Player p;
    GameWorld g;
    g.add(&e);
    g.add(&p);
    g.tick();
}




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
    void connect(){ cout<<"MySQL connected\n"; } 
};

class Repository {
    DBConnection& db;                            // HAS-A
  public:
    Repository(DBConnection& d):db(d){}
    void load(){ db.connect(); }
};
int main(){
    MySQLConnection m;
    Repository r(m);
    r.load();
}



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
     void send(){ cout<<"Email sent\n"; } 
};

class SMS : public Notification {                // IS-A
  public: 
    void send(){ cout<<"SMS sent\n"; } 
};
class Notifier {
    Notification* n;                             // aggregation
  public:
    Notifier(Notification* N):n(N){}
    void alert(){ n->send(); }
};
int main(){
    SMS s;
    Notifier n(&s);
    n.alert();
}



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
    void info(){ cout<<"Laptop\n"; } 
};

class Phone : public Product {                   // IS-A
  public: 
    void info(){ cout<<"Phone\n"; } 
};
class Warehouse {
    vector<Product*> items;                      // aggregation
  public:
    void add(Product* p){ items.push_back(p); }
    void print(){ for(auto* p:items) p->info(); }
};
int main(){
    Laptop l; Phone p;
    Warehouse w;
    w.add(&l); w.add(&p);
    w.print();
}



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
    void on(){ cout<<"Light on\n"; } 
};

class Fan : public Device {                      // IS-A
  public: 
    void on(){ cout<<"Fan on\n"; } 
};
class Home {
    vector<Device*> d;                           // aggregation
  public:
    void add(Device* x){ d.push_back(x); }
    void activate(){ for(auto* x:d) x->on(); }
};
int main(){
    Light l; Fan f;
    Home h;
    h.add(&l); h.add(&f);
    h.activate();
}





//13. Logistics Delivery System
//Truck IS-A Vehicle
//Delivery HAS-A Vehicle + Package
#include <iostream>
using namespace std;
class Vehicle { public: virtual void move()=0; };
class Truck : public Vehicle {                   // IS-A
  public: 
    void move(){ cout<<"Truck moving\n"; } 
};

class Package { public: string id; Package(string i):id(i){} };

class Delivery {
    Vehicle* v; Package* p;                      // aggregation
  public:
    Delivery(Vehicle* V, Package* P):v(V),p(P){}
    void send(){ v->move(); cout<<"Package "<<p->id; }
};
int main(){
    Truck t;
    Package p("BX101");
    Delivery d(&t,&p);
    d.send();
}



//14. Payroll Processing System
//FullTimeEmployee IS-A Employee
//Payroll HAS-A vector<Employee>*
#include <iostream>
#include <vector>
using namespace std;
class Employee { public: virtual int salary()=0; };
class FullTimeEmployee : public Employee {       // IS-A
public: int salary(){ return 5000; } };
class PartTimeEmployee : public Employee {       // IS-A
public: int salary(){ return 2000; } };
class Payroll {
    vector<Employee*> emps;                      // aggregation
  public:
    void add(Employee* e){ emps.push_back(e); }
    int total(){ int s=0; for(auto* e:emps) s+=e->salary(); return s; }
};
int main(){
    FullTimeEmployee f; 
    PartTimeEmployee p;
    Payroll pay;
    pay.add(&f); pay.add(&p);
    cout<<pay.total();
}




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
  string format(){ return "EBook"; } 
};
class PaperBook : public Book {                  // IS-A
  public: 
    string format(){ return "PaperBook"; } 
};

class Library {
    list<Book*> books;                           // aggregation
  public:
    void add(Book* b){ books.push_back(b); }
    void show(){ for(auto* b:books) cout<<b->format()<<endl; }
};
int main(){
    EBook e; PaperBook p;
    Library l;
    l.add(&e); l.add(&p);
    l.show();
}





