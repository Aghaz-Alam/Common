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


Inheriting Constructors: This allows a derived class to automatically inherit constructors from its 
base class using the using BaseClass::BaseClass; syntax, reducing boilerplate code.


Smart Pointers: The introduction of std::unique_ptr, std::shared_ptr, and std::weak_ptr provides safer, 
automated memory management, strongly favoring composition and aggregation by managing object lifetimes 
and reducing memory leaks. This makes the "has-a" relationship more robust. 




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
// The "contained" class
class Engine {
 public:
    void start() {
        std::cout << "The engine has started." << std::endl;
    }
};

// The "container" class
class Car {
  private:
    std::string brand;
    // This member variable creates the "Has-a" relationship:
    // A Car HAS an Engine as a direct, integral part of its definition.
    Engine engine; 

  public:
    Car(std::string b) : brand(b) {}

    void drive() {
        std::cout << "The " << brand << " is moving." << std::endl;
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

#include <iostream>
#include <string>
#include <memory> // Required for smart pointers, which are good for composition

// The 'Part' class (Engine)
class Engine {
  private:
    std::string type;

  public:
    Engine(std::string t) : type(t) {
        std::cout << "Engine (" << type << ") Created" << std::endl;
    }

    ~Engine() {
        std::cout << "Engine (" << type << ") Destroyed" << std::endl;
    }

    void start() {
        std::cout << "Engine started" << std::endl;
    }
};

// The 'Whole' class (Car) - strongly owns the Engine
class Car {
  private:
    // Engine is a member variable, its lifetime is tied to the Car
    // std::unique_ptr ensures single ownership and automatic destruction
    std::unique_ptr<Engine> engine;
    std::string name;

  public:
    Car(std::string n, std::string engineType) : name(n) {
        engine = std::make_unique<Engine>(engineType);
        std::cout << "Car (" << name << ") Created" << std::endl;
    }

    ~Car() {
        std::cout << "Car (" << name << ") Destroyed" << std::endl;
        // The unique_ptr automatically destroys the Engine here
    }

    void drive() {
        std::cout << "Driving the " << name << ": ";
        engine->start();
    }
};

int main() {
    std::cout << "--- Entering main scope ---" << std::endl;
    
    // When the Car object is created, the Engine object is automatically created inside it.
    Car myCar("Sedan", "V6");

    myCar.drive();

    std::cout << "--- Exiting main scope (Car destroyed) ---" << std::endl;
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



4. Aggregation  ["Has-a" (weak ownership)]
Aggregation is a weaker "has-a" relationship where the contained object can exist independently of 
the container object. 

The container typically holds a pointer or reference to an object created elsewhere.

#include <iostream>
#include <string>

// The 'Part' class (Address) - can exist independently
class Address {
  public:
    std::string street;
    std::string city;

    Address(std::string s, std::string c) : street(s), city(c) {
        std::cout << "Address Created: " << street << ", " << city << std::endl;
    }
    
    ~Address() {
         std::cout << "Address Destroyed: " << street << ", " << city << std::endl;
    }
};

// The 'Whole' class (Person) - has a pointer/reference to Address
class Person {
  private:
    std::string name;
    // A pointer/reference to an Address object (not responsible for lifetime)
    Address* address; 

  public:
    Person(std::string n, Address* addr) : name(n), address(addr) {
        std::cout << "Person Created: " << name << std::endl;
    }

    ~Person() {
        std::cout << "Person Destroyed: " << name << std::endl;
        // We do NOT delete the address here, as the Person doesn't own it.
    }

    void display() {
        std::cout << "Name: " << name << ", Address: " << address->street << ", " << address->city << std::endl;
    }
};

int main() {
    std::cout << "--- Creating an independent Address object ---" << std::endl;
    // The address exists first and manages its own lifetime
    Address addr1("123 Main St", "Anytown");

    std::cout << "\n--- Creating a Person (aggregating the Address) ---" << std::endl;
    Person p1("Alice", &addr1); // Pass the address reference

    p1.display();

    std::cout << "\n--- Destroying Person object ---" << std::endl;
    // When p1 is destroyed, addr1 still exists
    // (p1 goes out of scope implicitly at the end of main)

    std::cout << "--- Address object still exists after Person is gone ---" << std::endl;

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
