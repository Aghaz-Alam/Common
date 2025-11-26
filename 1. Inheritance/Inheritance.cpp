Inheritance
- Public, private inheritance
- Is-a relation, has-a relation, composition, aggregation



C++11
C++11 brought significant enhancements to object-oriented programming, primarily focused on explicitness 
and memory safety:

override specifier: This contextual keyword ensures that a function in a derived class is indeed 
overriding a virtual function from a base class. 
If the signatures do not match, the compiler produces an error, preventing common mistakes.


final specifier: This specifier prevents a virtual function from being overridden further in derived classes, 
or prevents a class from being inherited from at all.

/* --------------------------------------------------- */
Inheriting Constructors: This allows a derived class to automatically inherit constructors from its 
base class using the BaseClass::BaseClass; syntax, reducing boilerplate code.


✅ What is Boilerplate Code?
Boilerplate code refers to code that is repeated over and over with little or no change, just because the language requires it — even when 
it feels unnecessary.

In C++, when a derived class needs the same constructors as its base class, traditionally you had to rewrite all base constructors manually.
This repeated constructor forwarding is boilerplate code.

❌ Without Inheriting Constructors (Boilerplate Code)
#include <iostream>
using namespace std;

class Base {
public:
    Base(int x) { cout << "Base(int) called: x=" << x << endl; }
    Base(string s) { cout << "Base(string) called: s=" << s << endl; }
};

class Derived : public Base {
public:
    // BOILERPLATE: must manually rewrite each constructor
    Derived(int x) : Base(x) {}
    Derived(string s) : Base(s) {}
};

int main() {
    Derived d1(10);
    Derived d2("Hello");
  return 0;
}


✅ With Inheriting Constructors (No Boilerplate)
#include <iostream>
using namespace std;
class Base {
  public:
    Base(int x) { cout << "Base(int) called: x=" << x << endl; }
    Base(string s) { cout << "Base(string) called: s=" << s << endl; }
};
class Derived : public Base {
  public:
    using Base::Base;   // ✔ Inherit all Base constructors
};
int main() {
    Derived d1(10);       // Uses Base(int)
    Derived d2("Hello");  // Uses Base(string)
   return 0;
}
/* 
Base(int) called: x=10
Base(string) called: s=Hello
*/
/* ------------------------------------------------ */

Smart Pointers: The introduction of std::unique_ptr, std::shared_ptr, and std::weak_ptr provides safer, 
automated memory management, strongly favoring composition and aggregation by managing object lifetimes 
and reducing memory leaks. This makes the "has-a" relationship more robust. 

/* ----------------------------------------------------------------- */
✅ Why Smart Pointers Make a “has-a” Relationship More Robust
1. Automatic Lifetime Management (No Manual delete)
A class that has-a pointer member becomes error-prone if you forget to delete it.
❌ Before (raw pointer)
class Car {
    Engine* engine;
  public:
    Car() { engine = new Engine(); }
    ~Car() { delete engine; }   // must remember!
};

Problems:
If you forget the delete → memory leak.
If exceptions occur before destructor → leak.
If you copy the object → double deletes or no deletes.

✅ With smart pointer
class Car {
    std::unique_ptr<Engine> engine;
  public:
    Car() : engine(std::make_unique<Engine>()) {}
};

Now:
No need to write destructor.
Object always destroyed correctly.
No leak even during exceptions.
👉 This makes the “has-a” relationship automatically safe.

2. Clear Ownership Semantics
Smart pointers clearly express who owns an object.

unique_ptr
→ exclusive ownership
→ perfect for strong “has-a” relationship
→ the containing object truly owns the resource

shared_ptr
→ shared ownership
→ used when multiple objects "contain/use" the same object

weak_ptr
→ avoids cyclic ownership
→ prevents memory leaks in graphs, trees, observers
With raw pointers, ownership is ambiguous.

3. Safe Copying and Moving
A class with raw-pointer members becomes dangerous when copied:
Car c1;
Car c2 = c1;   // two Car objects pointing to SAME engine → double delete

Smart pointers solve this:
unique_ptr → cannot copy (ownership transfer only via move)
shared_ptr → handles reference counting
weak_ptr → breaks cycles
👉 This prevents accidental sharing or deleting of owned objects.

4. Stronger Encapsulation
When the owned object is wrapped inside a smart pointer:
Clients cannot accidentally delete it
Memory is guaranteed to be managed correctly
The class cleanly owns its sub-objects
This strengthens the composition relationship.

✔ Example: “Car has-a Engine”
Using smart pointer:
class Car {
    std::unique_ptr<Engine> engine;
  public:
    Car() : engine(std::make_unique<Engine>()) {}
};

Car owns Engine
When Car dies, engine dies
No manual deletion
No double deletion
No leaks
No dangling pointers
This is a robust has-a relationship.

✔ Example: Graph / Tree with parent-child
To avoid circular ownership:
struct Node {
    std::shared_ptr<Node> child;
    std::weak_ptr<Node>   parent;   // weak breaks cycle
};

This prevents memory leaks that raw pointers could easily cause.

//Has-A relation (composition-strong relationship between car and engin)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    Engine() {
        cout << "Engine created\n";
    }

    ~Engine() {
        cout << "Engine destroyed\n";
    }

    void start() const {
        cout << "Engine started\n";
    }
};

class Car {
    unique_ptr<Engine> engine;   // Car owns Engine
  public:
    Car() : engine(make_unique<Engine>()) {
        cout << "Car created\n";
    }

    ~Car() {
        cout << "Car destroyed\n";
    }

    void drive() const {
        cout << "Car is driving...\n";
        engine->start();
    }
};

int main() {
    {
        Car myCar;        // Car object created
        myCar.drive();    // Uses its Engine
    }                     // Car goes out of scope → Engine also destroyed

    cout << "Program finished\n";
   return 0;
}
/*
Engine created
Car created
Car is driving...
Engine started
Car destroyed
Engine destroyed
Program finished
*/








✅ 1. Composition (Strong Has-A) using std::unique_ptr
✔ Rules
Car owns the Engine exclusively.
Engine cannot exist without Car.
When Car is destroyed → Engine is also destroyed.
Ownership is exclusive and non-shared.

✔ Code (Composition)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    Engine()  { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
    void start() const { cout << "Engine started\n"; }
};
class Car {
    unique_ptr<Engine> engine;  // Exclusive ownership
  public:
    Car() : engine(make_unique<Engine>()) {
        cout << "Car created\n";
    }
    ~Car() {
        cout << "Car destroyed\n";
    }
    void drive() const {
        engine->start();
    }
};
int main() {
    {
        Car c;
        c.drive();
    } // Car destroyed → Engine destroyed (composition)

    return 0;
}
/*
✔ Output (Important!)
Engine created
Car created
Engine started
Car destroyed
Engine destroyed
*/
➡️ Engine dies WITH Car → Composition.


#include <iostream>
#include <string>
#include <memory> // Required for smart pointers, which are good for composition
using namespace std;
// The 'Part' class (Engine)
class Engine {
  private:
    string type;

  public:
    Engine(string t) : type(t) {
        cout << "Engine (" << type << ") Created" << endl;
    }

    ~Engine() {
        cout << "Engine (" << type << ") Destroyed" << endl;
    }

    void start() {
        cout << "Engine started" << endl;
    }
};

// The 'Whole' class (Car) - strongly owns the Engine
class Car {
  private:
    // Engine is a member variable, its lifetime is tied to the Car
    // std::unique_ptr ensures single ownership and automatic destruction
    unique_ptr<Engine> engine;
    string name;

  public:
    Car(string n, string engineType) : name(n), engine(make_unique<Engine>(engineType)) {
        cout << "Car (" << name << ") Created" << std::endl;
    }

    ~Car() {
        cout << "Car (" << name << ") Destroyed" << endl;
        // The unique_ptr automatically destroys the Engine here
    }

    void drive() {
        cout << "Driving the " << name << ": ";
        engine->start();
    }
};

int main() {
    cout << "--- Entering main scope ---" << endl;
    
    // When the Car object is created, the Engine object is automatically created inside it.
    Car myCar("Sedan", "V6");

    myCar.drive();

    cout << "--- Exiting main scope (Car destroyed) ---" << endl;
    // When myCar goes out of scope, its destructor is called, which destroys the Engine.
    
    return 0;
}
/* 
Output:
--- Entering main scope ---
Engine (V6) Created
Car (Sedan) Created
Driving the Sedan: Engine started
--- Exiting main scope (Car destroyed) ---
Car (Sedan) Destroyed
Engine (V6) Destroyed
*/


Cars
Name: Sedan, Type: V6
Name: Hatchback, Type: Inline-4
Name: SportsCar, Type: V8
Name: HyperCar, Type: W16
Name: MuscleCar, Type: V8 Supercharged
Name: CompactCar, Type: Inline-3 Turbo
Name: LuxuryCar, Type: V12
Name: FamilySUV, Type: V6 Turbo
Name: ElectricSedan, Type: Dual Electric Motors
Name: HybridSUV, Type: Inline-4 Hybrid




✅ 2. Aggregation (Weak Has-A) using std::shared_ptr
✔ Rules
Car uses an Engine but does NOT strictly own it.
The Engine can exist even after Car is destroyed.
Multiple Cars may share the same Engine.
Engine’s lifetime is not tied to Car.

✔ Code (Aggregation)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    Engine()  { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
    void start() const { cout << "Engine started\n"; }
};
class Car {
    shared_ptr<Engine> engine;  // Shared ownership (weak has-a)
  public:
    Car(shared_ptr<Engine> e) : engine(e) {
        cout << "Car created\n";
    }
    ~Car() {
        cout << "Car destroyed\n";
    }
    void drive() const {
        engine->start();
    }
};
int main() {
    shared_ptr<Engine> eng = make_shared<Engine>();
    {
        Car c1(eng);
        Car c2(eng);
        c1.drive();
        c2.drive();
    } 
    // Both cars destroyed, BUT engine still alive
    cout << "Cars destroyed, but engine should still exist (shared)\n";
    eng.reset(); // Now engine reference count becomes 0 -> destroyed
    return 0;
}
/*
✔ Output (Important!)
Engine created
Car created
Car created
Engine started
Engine started
Car destroyed
Car destroyed
Cars destroyed, but engine should still exist (shared)
Engine destroyed
*/

#include <iostream>
#include <string>
#include <memory>
using namespace std;
// ===== Engine Class =====
class Engine {
  private:
    string type;

  public:
    Engine(string t) : type(t) {
        cout << "Engine (" << type << ") Created" << endl;
    }
    ~Engine() {
        cout << "Engine (" << type << ") Destroyed" << endl;
    }
    void start() {
        cout << "Engine (" << type << ") started" << endl;
    }
};
// ===== Car Class (Aggregation) =====
// Car does NOT own Engine. It only uses it.
class Car {
  private:
    shared_ptr<Engine> engine;   // weak HAS-A (aggregation)
    string name;

  public:
    Car(string n, shared_ptr<Engine> eng) : name(n), engine(eng) {
        cout << "Car (" << name << ") Created" << endl;
    }
    ~Car() {
        cout << "Car (" << name << ") Destroyed" << endl;
    }
    void drive() {
        cout << name << " is driving: ";
        engine->start();
    }
};
int main() {
    cout << "--- Entering main scope ---" << endl;
    // Engine created independently (not inside any Car)
    shared_ptr<Engine> eng = make_shared<Engine>("V6");
    // Multiple cars share the SAME engine → aggregation
    Car c1("Sedan", eng);
    Car c2("SUV", eng);

    c1.drive();
    c2.drive();   // YES! c2 can also call engine->start()

    cout << "--- Exiting main scope ---" << endl;
    return 0;
}

/*
Expected Output:

--- Entering main scope ---
Engine (V6) Created
Car (Sedan) Created
Car (SUV) Created
Sedan is driving: Engine (V6) started
SUV is driving: Engine (V6) started
--- Exiting main scope ---
Car (SUV) Destroyed
Car (Sedan) Destroyed
Engine (V6) Destroyed
*/



Cars,
Name: Sedan, Type: V6
Name: SUV, Type: V6
Name: Minivan, Type: V6




➡️ Engine stays alive even after both Cars die → Aggregation.

✅ 3. Easy Comparison Table
| Feature                         | Composition (`unique_ptr`)     | Aggregation (`shared_ptr`)       |
| ------------------------------- | ------------------------------ | -------------------------------- |
| Ownership                       | Exclusive                      | Shared / Weak                    |
| Lifetime                        | Car controls Engine’s lifetime | Engine can outlive Car           |
| Relationship                    | Strong has-a                   | Weak has-a                       |
| Can be shared?                  | ❌ No                           | ✔ Yes                            |
| Engine destroyed when Car dies? | ✔ Yes                          | ❌ No                             |
| Who deletes the Engine?         | Car’s destructor               | Last shared_ptr reference holder |
| Real-world meaning              | Car **contains** Engine        | Car **uses** Engine              |



/* ----------------------------------------------------------------- */


C++14
C++14 was a minor release that primarily provided relaxations and small improvements to existing C++11 features, 
with few direct impacts on core inheritance mechanics:

Relaxed constexpr: Allowed more complex logic (like loops and if statements) inside constexpr functions, 
which can be part of inherited class functionality evaluated at compile time.

Aggregate member initializers: C++14 relaxed a restriction that prevented classes with in-class member initializers 
from using aggregate initialization. This improved the flexibility of initializing members within composite objects. 



C++17
C++17 further refined how aggregates (which previously could not have base classes) could be initialized: 

Aggregate Initialization for Classes with Base Classes: C++17 expanded the definition of an aggregate to 
include classes that publicly inherit from base classes (as long as the base classes have 
no non-static private members, etc.). 

This allows for a more concise brace initialization syntax for an object and its base class members:

struct Base { int i, j; };
struct Derived : Base { int k; };
Derived d{ {1, 2}, 3 }; // Valid in C++17; initializes i=1, j=2, k=3



Summary of Relationships
The semantic meaning of inheritance access specifiers remains the same across these standards:

Access Specifier 	Relationship Model	        Description
public	            Is-a (Subtyping)	        The derived class is a type of the base class. This supports polymorphism.
private	            Is-implemented-in-terms-of	The derived class uses the base class's implementation internally, but outside code cannot treat the derived class as an instance of the base. This closely models a "has-a" or composition relationship.
protected	        Is-implemented-in-terms-of	Similar to private, but members are also accessible to further derived classes.



Is-a Relation
The "Is-a" relationship is the most common and standard interpretation of inheritance. 

It signifies that the derived class is a specific type of the base class and can be used wherever 
the base class is expected (polymorphism). 

Implementation: The "Is-a" relationship is primarily implemented using public inheritance.

Example: A Car is a Vehicle. The Car class publicly inherits from the Vehicle class, 
meaning any function that accepts a Vehicle can also accept a Car. 


"Has-a" Relation, Composition, and Aggregation 
These terms refer to relationships where one class contains or uses another class as a member, 
rather than inheriting from it. 

This is known as composition or aggregation, collectively referred to as the "Has-a" relationship. 

Implementation: These are implemented using containment (having an instance of one class as a member variable 
within another class), not inheritance 


Composition/Aggregation ("Has-a") continues to be the preferred method for building objects from other objects 
when a subtyping relationship is not appropriate, and modern C++ features 
(smart pointers, C++17 aggregate init improvements) continue to support this design pattern. 


Composition vs. Aggregation
The difference between composition and aggregation lies in the ownership and lifetime of the contained object [1, 2]: 


Feature 	    Aggregation	                                                            Composition
Relationship	"Has-a" (weak ownership)	                                            "Has-a" (strong ownership)
Lifetime	    Contained object can exist independently of the container object .	Contained object's lifetime is tied to the container object; it cannot exist without it [1].
Example	        A Library has Books. Books exist even if the library is closed.	    A Car has an Engine. The engine is an integral part of the car and usually does not exist independently of it


1. Is-a Relation (Public Inheritance)
This relationship signifies that the derived class is a specific type of the base class. 
It is implemented using public inheritance. A Car is a Vehicle.

#include <iostream>
#include <string>
// Base Class (Parent)
class Vehicle {
  public:
    std::string brand = "Ford";

    void honk() {
        std::cout << "Tuut, tuut!" << std::endl;
    }
};
// Derived Class (Child)
class Car : public Vehicle {
  public:
    std::string model = "Mustang";
};

int main() {
    Car myCar;
    // We can access base class members through the derived class object
    myCar.honk(); 
    std::cout << "Brand: " << myCar.brand << ", Model: " << myCar.model << std::endl;
   return 0;
}
/* 
Output:
Tuut, tuut!
Brand: Ford, Model: Mustang
*/




2. "Has-a" Relation (General Containment)
The "Has-a" relationship is a general term for when one class contains an object of another class as 
a member variable. 

The following examples (Composition and Aggregation) are specific types of "Has-a" relationships.


#include <iostream>
#include <string>
using namespace std;
// The "contained" class
class Engine {
 public:
    void start() {
        cout << "The engine has started." << endl;
    }
};

// The "container" class
class Car {
  private:
    string brand;
    // This member variable creates the "Has-a" relationship:
    // A Car HAS an Engine as a direct, integral part of its definition.
    Engine engine; 

  public:
    Car(string b) : brand(b) {}

    void drive() {
        cout << "The " << brand << " is moving." << std::endl;
        // The Car class uses its internal Engine object to perform actions.
        engine.start(); 
    }
};

int main() {
    Car myCar("Toyota");

    // The main program only interacts with the Car object.
    // The Engine object is contained entirely within the Car's scope.
    myCar.drive();

    return 0;
}
/* 
The Toyota is moving.
The engine has started.
*/







3. Composition ["Has-a" (strong ownership)]
Composition is a strong "has-a" relationship where the contained object (part) cannot exist without 
the container object (whole). 

If the container is destroyed, the contained object is also destroyed.

Composition (Strong Has-A) using std::unique_ptr
✔ Rules
Car owns the Engine exclusively.
Engine cannot exist without Car.
When Car is destroyed → Engine is also destroyed.
Ownership is exclusive and non-shared.

✔ Code (Composition)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    Engine()  { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
    void start() const { cout << "Engine started\n"; }
};
class Car {
    unique_ptr<Engine> engine;  // Exclusive ownership
  public:
    Car() : engine(make_unique<Engine>()) {
        cout << "Car created\n";
    }
    ~Car() {
        cout << "Car destroyed\n";
    }
    void drive() const {
        engine->start();
    }
};
int main() {
    {
        Car c;
        c.drive();
    } // Car destroyed → Engine destroyed (composition)

    return 0;
}
/*
✔ Output (Important!)
Engine created
Car created
Engine started
Car destroyed
Engine destroyed
*/
➡️ Engine dies WITH Car → Composition.







#include <iostream>
#include <string>
#include <memory> // Required for smart pointers, which are good for composition
using namespace std;
// The 'Part' class (Engine)
class Engine {
  private:
    string type;

  public:
    Engine(string t) : type(t) {
        cout << "Engine (" << type << ") Created" << endl;
    }

    ~Engine() {
        cout << "Engine (" << type << ") Destroyed" << endl;
    }

    void start() {
        cout << "Engine started" << endl;
    }
};

// The 'Whole' class (Car) - strongly owns the Engine
class Car {
  private:
    // Engine is a member variable, its lifetime is tied to the Car
    // std::unique_ptr ensures single ownership and automatic destruction
    unique_ptr<Engine> engine;
    string name;

  public:
    Car(string n, string engineType) : name(n), engine(make_unique<Engine>(engineType)) {
        cout << "Car (" << name << ") Created" << std::endl;
    }

    ~Car() {
        cout << "Car (" << name << ") Destroyed" << endl;
        // The unique_ptr automatically destroys the Engine here
    }

    void drive() {
        cout << "Driving the " << name << ": ";
        engine->start();
    }
};

int main() {
    cout << "--- Entering main scope ---" << endl;
    
    // When the Car object is created, the Engine object is automatically created inside it.
    Car myCar("Sedan", "V6");

    myCar.drive();

    cout << "--- Exiting main scope (Car destroyed) ---" << endl;
    // When myCar goes out of scope, its destructor is called, which destroys the Engine.
    
    return 0;
}
/* 
Output:
--- Entering main scope ---
Engine (V6) Created
Car (Sedan) Created
Driving the Sedan: Engine started
--- Exiting main scope (Car destroyed) ---
Car (Sedan) Destroyed
Engine (V6) Destroyed
*/


Cars
Name: Sedan, Type: V6
Name: Hatchback, Type: Inline-4
Name: SportsCar, Type: V8
Name: HyperCar, Type: W16
Name: MuscleCar, Type: V8 Supercharged
Name: CompactCar, Type: Inline-3 Turbo
Name: LuxuryCar, Type: V12
Name: FamilySUV, Type: V6 Turbo
Name: ElectricSedan, Type: Dual Electric Motors
Name: HybridSUV, Type: Inline-4 Hybrid



// Composition -- Person owns Address
#include <iostream>
#include <string>
#include <memory>
using namespace std;

// The 'Part' class (Address) - exists ONLY inside Person
class Address {
 public:
    string street;
    string city;

    Address(string s, string c) : street(s), city(c) {
        cout << "Address Created: " << street << ", " << city << endl;
    }

    ~Address() {
        cout << "Address Destroyed: " << street << ", " << city << endl;
    }
};

// Person strongly owns Address (Composition)
class Person {
  private:
    string name;
    unique_ptr<Address> address;   // Strong ownership

  public:
    // Person CREATES its own Address → COMPOSITION
    Person(string n, string street, string city) : name(n), address(make_unique<Address>(street, city)){
        cout << "Person Created: " << name << endl;
    }

    ~Person() {
        cout << "Person Destroyed: " << name << endl;
        // unique_ptr automatically destroys address
    }

    void display() {
        cout << "Name: " << name << ", Address: " << address->street << ", " << address->city << endl;
    }
};

int main() {
    cout << "--- Creating Person (composition) ---" << endl;

    Person p1("Alice", "123 Main St", "Anytown");

    p1.display();

    cout << "--- End of main ---" << endl;

    return 0;
}
/*
--- Creating Person (composition) ---
Address Created: 123 Main St, Anytown
Person Created: Alice
Name: Alice, Address: 123 Main St, Anytown
--- End of main ---
Person Destroyed: Alice
Address Destroyed: 123 Main St, Anytown
*/


4. Aggregation  ["Has-a" (weak ownership)]
Aggregation is a weaker "has-a" relationship where the contained object can exist independently of 
the container object. 

The container typically holds a pointer or reference to an object created elsewhere.


✅ 2. Aggregation (Weak Has-A) using std::shared_ptr
✔ Rules
Car uses an Engine but does NOT strictly own it.
The Engine can exist even after Car is destroyed.
Multiple Cars may share the same Engine.
Engine’s lifetime is not tied to Car.

✔ Code (Aggregation)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    Engine()  { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
    void start() const { cout << "Engine started\n"; }
};
class Car {
    shared_ptr<Engine> engine;  // Shared ownership (weak has-a)
  public:
    Car(shared_ptr<Engine> e) : engine(e) {
        cout << "Car created\n";
    }
    ~Car() {
        cout << "Car destroyed\n";
    }
    void drive() const {
        engine->start();
    }
};
int main() {
    shared_ptr<Engine> eng = make_shared<Engine>();
    {
        Car c1(eng);
        Car c2(eng);
        c1.drive();
        c2.drive();
    } 
    // Both cars destroyed, BUT engine still alive
    cout << "Cars destroyed, but engine should still exist (shared)\n";
    eng.reset(); // Now engine reference count becomes 0 -> destroyed
    return 0;
}
/*
✔ Output (Important!)
Engine created
Car created
Car created
Engine started
Engine started
Car destroyed
Car destroyed
Cars destroyed, but engine should still exist (shared)
Engine destroyed
*/







#include <iostream>
#include <string>
#include <memory>
using namespace std;

// ===== Engine Class =====
class Engine {
  private:
    string type;

  public:
    Engine(string t) : type(t) {
        cout << "Engine (" << type << ") Created" << endl;
    }

    ~Engine() {
        cout << "Engine (" << type << ") Destroyed" << endl;
    }

    void start() {
        cout << "Engine (" << type << ") started" << endl;
    }
};

// ===== Car Class (Aggregation) =====
// Car does NOT own Engine. It only uses it.
class Car {
  private:
    shared_ptr<Engine> engine;   // weak HAS-A (aggregation)
    string name;

  public:
    Car(string n, shared_ptr<Engine> engType) : name(n), engine(engType) {
        cout << "Car (" << name << ") Created" << endl;
    }

    ~Car() {
        cout << "Car (" << name << ") Destroyed" << endl;
    }

    void drive() {
        cout << name << " is driving: ";
        engine->start();
    }
};

int main() {
    cout << "--- Entering main scope ---" << endl;

    // Engine created independently (not inside any Car)
    shared_ptr<Engine> eng = make_shared<Engine>("V6");

    // Multiple cars share the SAME engine → aggregation
    Car c1("Sedan", eng);
    Car c2("SUV", eng);

    c1.drive();
    c2.drive();   // YES! c2 can also call engine->start()

    cout << "--- Exiting main scope ---" << endl;
    return 0;
}

/*
Expected Output:

--- Entering main scope ---
Engine (V6) Created
Car (Sedan) Created
Car (SUV) Created
Sedan is driving: Engine (V6) started
SUV is driving: Engine (V6) started
--- Exiting main scope ---
Car (SUV) Destroyed
Car (Sedan) Destroyed
Engine (V6) Destroyed
*/



Cars,
Name: Sedan, Type: V6
Name: SUV, Type: V6
Name: Minivan, Type: V6




➡️ Engine stays alive even after both Cars die → Aggregation.













//Aggregation  --Person Vs Address
#include <iostream>
#include <string>
using namespace std;
// The 'Part' class (Address) - can exist independently
class Address {
  public:
    string street;
    string city;

    Address(string s, string c) : street(s), city(c) {
        cout << "Address Created: " << street << ", " << city << endl;
    }
    
    ~Address() {
         cout << "Address Destroyed: " << street << ", " << city << endl;
    }
};

// The 'Whole' class (Person) - has a pointer/reference to Address
class Person {
  private:
    string name;
    // A pointer/reference to an Address object (not responsible for lifetime)
    Address* address; 

  public:
    Person(string n, Address* addr) : name(n), address(addr) {
        cout << "Person Created: " << name << endl;
    }

    ~Person() {
        cout << "Person Destroyed: " << name << endl;
        // We do NOT delete the address here, as the Person doesn't own it.
    }

    void display() {
        cout << "Name: " << name << ", Address: " << address->street << ", " << address->city << endl;
    }
};

int main() {
    cout << "--- Creating an independent Address object ---" << endl;
    // The address exists first and manages its own lifetime
    Address addr1("123 Main St", "Anytown");

    cout << "\n--- Creating a Person (aggregating the Address) ---" << endl;
    Person p1("Alice", &addr1); // Pass the address reference

    p1.display();

    cout << "\n--- Destroying Person object ---" << endl;
    // When p1 is destroyed, addr1 still exists
    // (p1 goes out of scope implicitly at the end of main)

    cout << "--- Address object still exists after Person is gone ---" << endl;

  return 0;
}
/* 
Output:
--- Creating an independent Address object ---
Address Created: 123 Main St, Anytown

--- Creating a Person (aggregating the Address) ---
Person Created: Alice
Name: Alice, Address: 123 Main St, Anytown

--- Destroying Person object ---
Person Destroyed: Alice
--- Address object still exists after Person is gone ---
Address Destroyed: 123 Main St, Anytown
*/





#include <iostream>
#include <string>
#include <vector>
// Department class has Employees (Aggregation)
class Employee {
  private:
    std::string name;
  public:
    Employee(const std::string& name) : name(name) {
        std::cout << "Employee created: " << name << std::endl;
    }
    ~Employee() {
        std::cout << "Employee destroyed: " << name << std::endl;
    }
    void showName() {
        std::cout << "Employee: " << name << std::endl;
    }
};

class Department {
  public:
    Department(const std::string& deptName) : department_name(deptName) {
        std::cout << "Department created: " << department_name << std::endl;
    }
    ~Department() {
        std::cout << "Department destroyed: " << department_name << std::endl;
    }

    void addEmployee(Employee* employee) {
        employees.push_back(employee);  // Aggregation: Department has Employees
    }

    void showEmployees() {
        std::cout << "Employees in " << department_name << " Department:\n";
        for (auto* emp : employees) {
            emp->showName();
        }
    }

  private:
    std::string department_name;
    std::vector<Employee*> employees;  // Aggregation: Employee objects are not owned by Department
};

int main() {
    Employee emp1("John");
    Employee emp2("Jane");

    Department dept("HR");

    dept.addEmployee(&emp1);  // Adding employee to the department
    dept.addEmployee(&emp2);

    dept.showEmployees();  // Display employees in the department

    return 0;  // Only Department object is destroyed here; Employee objects are not destroyed
}
/*
Explanation:
The Department class contains a list of Employee pointers, and this is an Aggregation relationship.
Employees are not created or destroyed by the Department. They exist independently.

The Department holds references (or pointers) to Employee objects, but it does not own them. 
If the Department object is destroyed, the Employee objects can still exist.

The Employee objects are created and managed outside the Department (independently), 
meaning they could belong to other departments or be used elsewhere. This is Aggregation.
*/

Key Differences Between Composition and Aggregation:
| **Aspect**               | **Composition**                                                             | **Aggregation**                                                                            |
| ------------------------ | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| **Ownership**            | Strong ownership; the contained object’s lifetime is tied to the container. | Weaker ownership; the contained object exists independently.                               |
| **Lifetime**             | If the container is destroyed, the contained object is destroyed as well.   | The contained object can live on after the container is destroyed.                         |
| **Example**              | A `Car` contains an `Engine` (the `Engine` cannot exist without the `Car`). | A `Department` aggregates `Employee` objects (Employees can exist without the Department). |
| **Type of Relationship** | Part-of relationship (strong "has-a").                                      | Has-a relationship (weak "has-a").                                                         |



Private and Protected Inheritance
Private and protected inheritance establish a relationship where the derived class is implemented 
in terms of the base class, but it is not a subtype of the base class from an outside perspective. 

Private Inheritance: The public and protected members of the base class become private members of the derived class. 
Outside code cannot treat the derived class as an instance of the base class. 
It is a form of implementation reuse, similar to composition in some ways.

Protected Inheritance: The public and protected members of the base class become protected members of the 
derived class. 
This allows the derived class's own members and subsequent derived classes to access the base members, 
but not outside code.

Summary Table:
Concept 	                    Relationship Type	                                Implementation Method	        External View
Public Inheritance	            Is-a (Subtyping)	                                Inheritance	                    Derived is a Base
Private/Protected Inheritance	Is-implemented-in-terms-of (Implementation reuse)	Inheritance	                    Derived is not a Base
Composition/Aggregation	        Has-a (Containment)	                                Member variable	                Container has a Contained       



/* --------------------- */
✅ COMPOSITION Examples (Strong Has-A)
Rule:
The part cannot exist without the whole.
The whole object owns the part's lifetime.

🔹 1. Car has-a Engine
Engine is created inside Car
When Car is destroyed, Engine is also destroyed

🔹 2. Human has-a Heart
A Heart cannot exist meaningfully without its Human
Lifetimes tied together

🔹 3. House has-a Room
Destroying the house means rooms are also destroyed
Rooms do not exist independently

🔹 4. Computer has-a CPU / RAM
CPU/RAM components are part of the computer
Can't exist by themselves in a useful way

🔹 5. Tree has-a Root
Root is part of Tree
When tree dies → roots die

🔹 6. Smartphone has-a Battery
Battery belongs to the phone
When the phone is destroyed → battery becomes useless

🔹 7. Book has-a Page
Pages are created as part of the book
Destroying the book destroys the pages

🔹 8. Person has-a Brain
Brain exists as an internal part
Lifetimes are linked
➡️ All these represent COMPOSITION because the “part” depends on the “whole.”

✅ AGGREGATION Examples (Weak Has-A)
Rule:
The part can exist independently of the whole.
The whole object uses or references the part but does not own it.

🔹 1. Car has-a Driver
Driver can exist without the car
Car does not own the driver's lifetime

🔹 2. Teacher has-a Student
Students exist independently from teachers
Multiple teachers may use the same student (like in shared_ptr)

🔹 3. Library has-a Book
Library stores books
Removing the library or closing it does NOT destroy the book

🔹 4. Team has-a Player
Players exist independently of the team
Can join or leave teams

🔹 5. Company has-a Employee
Employees exist independently
Company does not own their lifetime

🔹 6. University has-a Professor
Professors can leave the university
They are not owned by the university

🔹 7. Classroom has-a Chair
Chairs can be moved to a different room
They are not strictly tied to one classroom

🔹 8. Store has-a Customer
Customers exist independently
They come and go
➡️ All these represent AGGREGATION because the part DOES NOT depend on the whole.
/* -------------------- */




1. Private Inheritance
When a class is inherited privately, all public and protected members of the base class become private members of the derived class. 
This means they can only be accessed within the derived class, and not by objects of the derived class or by other classes.

Key Points:
Members inherited from the base class are not accessible outside the derived class.
It is used when you want to model a "has-a" relationship but want to hide the base class implementation details.

Code Example:
#include <iostream>
using namespace std;

class Base {
  public:
    int publicVar;
    
    Base() {
        publicVar = 10;
    }
    
    void show() {
        cout << "Base show() called" << endl;
    }
};

class Derived : private Base {  // Private inheritance
  public:
    void display() {
        // Accessing base class public member
        cout << "publicVar from Base: " << publicVar << endl;
        show(); // Accessing base class public function
    }
};
int main() {
    Derived d;
    d.display(); // Works fine inside Derived class
    
    // The following lines would produce an error
    // cout << d.publicVar;  // Error: 'publicVar' is private in 'Derived'
    // d.show();  // Error: 'show' is private in 'Derived'
    
    return 0;
}


Explanation:

The Derived class inherits from Base privately.
Inside the Derived class, we can access the Base's public members like publicVar and the show() method. 
However, outside the class (in main()), we cannot access them directly.




2. Protected Inheritance
When a class is inherited protectedly, all public and protected members of the base class become protected members of the derived class. 
This means they can be accessed within the derived class and by classes that inherit from the derived class, but not by other external code.

Key Points:
Members inherited from the base class are not accessible outside the derived class, but they can be accessed by classes further down the inheritance chain.
It's used when you want to allow derived classes to access the base class's members while still restricting direct external access.

Code Example:
#include <iostream>
using namespace std;
class Base {
  public:
    int publicVar;
    
    Base() {
        publicVar = 20;
    }
    
    void show() {
        cout << "Base show() called" << endl;
    }
};

class Derived : protected Base {  // Protected inheritance
  public:
    void display() {
        // Accessing base class public member
        cout << "publicVar from Base: " << publicVar << endl;
        show(); // Accessing base class public function
    }
};

class FurtherDerived : public Derived {
  public:
    void anotherDisplay() {
        // Accessing protected members from base class through Derived class
        cout << "Accessing from FurtherDerived: " << publicVar << endl;
        show();
    }
};

int main() {
    Derived d;
    d.display(); // Works fine inside Derived class
    
    // The following lines would produce an error
    // cout << d.publicVar;  // Error: 'publicVar' is protected in 'Derived'
    // d.show();  // Error: 'show' is protected in 'Derived'
    
    FurtherDerived fd;
    fd.anotherDisplay(); // Works because FurtherDerived can access protected members
    
    return 0;
}


Explanation:
Derived inherits Base protectedly, so publicVar and show() are protected in Derived.
FurtherDerived can access these protected members because it’s a subclass of Derived.
Outside of the inheritance chain, external code cannot access these protected members.




3. Public Inheritance
When a class is inherited publicly, all public members of the base class remain public in the derived class, 
and all protected members remain protected. 
This is the most common form of inheritance and represents an "is-a" relationship.

Key Points:
Public inheritance implies that the derived class is a specialized version of the base class.
The public interface of the base class is available to the derived class and external code.

Code Example:
#include <iostream>
using namespace std;

class Base {
  public:
    int publicVar;
    
    Base() {
        publicVar = 30;
    }
    
    void show() {
        cout << "Base show() called" << endl;
    }
};

class Derived : public Base {  // Public inheritance
  public:
    void display() {
        // Accessing base class public member
        cout << "publicVar from Base: " << publicVar << endl;
        show(); // Accessing base class public function
    }
};

int main() {
    Derived d;
    d.display(); // Works fine because Derived class is publicly inheriting Base class
    
    // Accessing public members directly
    cout << "Direct access to publicVar: " << d.publicVar << endl;
    d.show(); // Directly calling show() from Base
    
    return 0;
}
/* 
Explanation:
Derived inherits Base publicly, so publicVar and show() are available to external code.
The derived class can access the public members of the base class, and objects of Derived can also access the public members directly.
*/

Summary of Differences:
| Inheritance Type | Access to Base Class Members                 | When to Use                                                                                        |
| ---------------- | -------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| **Private**      | Inaccessible outside Derived                 | For hiding implementation details or when modeling a "has-a" relationship                          |
| **Protected**    | Accessible within Derived and its subclasses | When you want to allow subclasses to access base class members, but not the external code          |
| **Public**       | Accessible outside Derived                   | For a true "is-a" relationship, where derived class should be able to be treated as the base class |
