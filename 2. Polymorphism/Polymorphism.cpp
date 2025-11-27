Polymorphisms 
- Creating interfaces and using them
- defining concrete classes and accessing them
- casting between objects
- virtual function and behaviour of ctor and dtor



1. Creating Interfaces and Using Them
An interface defines a contract for behavior that a class must implement, 
without defining how that behavior is carried out. 

In C++, pure abstract classes serve as interfaces. 
A class is a pure abstract class if it contains at least one pure virtual function. 
A pure virtual function is defined using the syntax = 0 in its declaration.



#include <iostream>
#include <memory>
using namespace std;
// Define the Interface (Abstract Class with pure virtual function)
class IDrawable {
  public:
    // Pure virtual function
    virtual void draw() const = 0;

    // Virtual destructor is vital in polymorphic base classes
    virtual ~IDrawable() = default;
};

/*---------------------------complete code-------------------------------------*/
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// Define the Interface (Abstract Class with pure virtual function)
class IDrawable {
  public:
    // Pure virtual function
    virtual void draw() const = 0;

    // Virtual destructor is vital in polymorphic base classes
    virtual ~IDrawable() = default;
};

// Concrete Class 1 (implements the interface)
class Circle : public IDrawable {
  public:
    void draw() const override {
        cout << "Drawing a Circle on screen." << endl;
    }
};

// Concrete Class 2 (implements the interface)
class Square : public IDrawable {
  public:
    void draw() const override {
        cout << "Drawing a Square on screen." << endl;
    }
};

// Function that accepts any object that satisfies the IDrawable interface
void render_shape(const IDrawable& shape) {
    shape.draw();
}

int main() {
    // 1. Using individual pointers
    // We use the Base/Interface pointer type to point to Derived/Concrete objects.
    unique_ptr<IDrawable> shape1 = make_unique<Circle>();
    unique_ptr<IDrawable> shape2 = make_unique<Square>();

    cout << "--- Drawing individual shapes ---" << endl;
    shape1->draw();
    shape2->draw();

    // 2. Passing objects to a function polymorphically
    cout << "\n--- Rendering shapes using a generic function ---" << endl;
    render_shape(*shape1);
    render_shape(*shape2);
    
    // 3. Storing multiple different shapes in a single container
    cout << "\n--- Drawing shapes from a vector ---" << endl;
    vector<unique_ptr<IDrawable>> canvas;
    canvas.push_back(make_unique<Circle>());
    canvas.push_back(make_unique<Square>());
    canvas.push_back(make_unique<Circle>());

    for (const auto& shape : canvas) {
        shape->draw();
    }

    // When main returns, all unique_ptrs go out of scope and
    // the virtual destructors are correctly called.

    return 0;
}
/* 
Output:
--- Drawing individual shapes ---
Drawing a Circle on screen.
Drawing a Square on screen.

--- Rendering shapes using a generic function ---
Drawing a Circle on screen.
Drawing a Square on screen.

--- Drawing shapes from a vector ---
Drawing a Circle on screen.
Drawing a Square on screen.
Drawing a Circle on screen.
*/
/*----------------------------------------------------------------*/
2. Defining Concrete Classes and Accessing Them
Concrete classes inherit from the interface and must provide an implementation 
for all pure virtual functions defined in the interface.

#include <iostream>
#include <memory>
using namespace std;
// Define the Interface (Abstract Class with pure virtual function)
class IDrawable {
  public:
    // Pure virtual function
    virtual void draw() const = 0;

    // Virtual destructor is vital in polymorphic base classes
    virtual ~IDrawable() = default;
};
// Concrete Class 1
class Circle : public IDrawable {
  public:
    void draw() const override {
        std::cout << "Drawing a Circle." << std::endl;
    }
};

// Concrete Class 2
class Square : public IDrawable {
 public: 
    void draw() const override {
        std::cout << "Drawing a Square." << std::endl;
    }
};

// Accessing them polymorphically
int main() {
    // We store pointers to the concrete objects using the Base Interface type (IDrawable*)
    std::unique_ptr<IDrawable> shape1 = std::make_unique<Circle>();
    std::unique_ptr<IDrawable> shape2 = std::make_unique<Square>();

    // The call to draw() behaves differently based on the actual object type at runtime
    shape1->draw(); 
    shape2->draw();
    
    return 0;
}
/*
Output:
Drawing a Circle.
Drawing a Square.
*/



3. Casting Between Objects
Casting between objects in a polymorphic hierarchy (upcasting and downcasting) allows you 
to treat objects with different levels of specificity.

Upcasting: Implicitly safe. Treating a derived class object as a base class object 
(e.g., casting Square* to IDrawable*). 
This is how polymorphism usually works.

Downcasting: Requires explicit handling and is potentially unsafe if the cast is incorrect. 
C++ provides dynamic_cast for safe, runtime-checked downcasting in polymorphic hierarchies.


#include <iostream>
#include <typeinfo> // Required for typeid operator
class Base { 
    public: 
      virtual ~Base() = default; 
}; // Must have at least one virtual function
class Derived : public Base { 
    public: 
       void specificFunction() { 
        std::cout << "Called derived function!" << std::endl; 
       } 
};
class Unrelated { };

int main() {
    Base* basePtr = new Derived(); // Upcasting (Implicit and Safe)

    // Downcasting safely with dynamic_cast
    // Tries to convert basePtr to a Derived*. If valid, it returns the pointer; otherwise, nullptr.
    if (Derived* derivedPtr = dynamic_cast<Derived*>(basePtr)) {
        std::cout << "Downcast successful. ";
        derivedPtr->specificFunction();
    } else {
        std::cout << "Downcast failed." << std::endl;
    }

    // Example of a failed cast (Base* to Unrelated*)
    Unrelated* unrelatedPtr = dynamic_cast<Unrelated*>(basePtr);
    if (!unrelatedPtr) {
        std::cout << "Attempted cast to Unrelated class failed as expected." << std::endl;
    }
    
    delete basePtr;
    return 0;
}
/* 
Output:
Downcast successful. Called derived function!
Attempted cast to Unrelated class failed as expected.
*/


//Abstract class making a pure virtual function in the Base class
#include <iostream>
using namespace std;
class Base { 
    public: 
      virtual void specificFunction()=0;
      virtual ~Base() = default; 
}; // Must have at least one virtual function
class Derived : public Base { 
    public: 
       void specificFunction(){ 
         cout << "Called derived function!" << endl; 
       } 
};

int main() {
    Base* basePtr = new Derived(); // Upcasting (Implicit and Safe)

    // Downcasting safely with dynamic_cast
    // Tries to convert basePtr to a Derived*. If valid, it returns the pointer; otherwise, nullptr.
    if (Derived* derivedPtr = dynamic_cast<Derived*>(basePtr)) {
        cout << "Downcast successful. ";
        derivedPtr->specificFunction();
    } else {
        cout << "Downcast failed." << endl;
    }
    
    delete basePtr;
    return 0;
}
/*
Downcast successful. Called derived function!
*/


4. Virtual Functions and Behavior of Ctor and Dtor

Virtual Functions:
Virtual functions enable dynamic binding (runtime polymorphism). 
The method called is determined by the actual type of the object being pointed to, 
not the type of the pointer/reference. 

The override keyword in derived classes makes this relationship explicit and compiler-checked (C++11 feature).

Constructor Behavior:
Constructors cannot be virtual.
When a derived class object is created, the base class constructor runs first, 
initializing the base part of the object. Within the constructor of a base class, 
the object is treated as that base type; 
polymorphic behavior (calling virtual functions overridden in the derived class) 
does not apply because the derived part of the object has not yet been constructed.



Destructor Behavior
Destructors should be virtual in polymorphic base classes.
If you delete an object via a pointer to a base class, but the destructor in the base class is not virtual, 
only the base class's destructor is called, leading to a memory leak (the derived part isn't cleaned up) 
and undefined behavior.

By making the base class destructor virtual, the correct derived class destructor is called polymorphically 
at runtime, followed automatically by the base class destructor.

#include <iostream>
class Base {
  public:
    Base() { 
        std::cout << "Base Ctor" << std::endl; 
    }
    // MUST BE VIRTUAL for correct cleanup
    virtual ~Base() { 
        std::cout << "Base Dtor" << std::endl; 
    }
};
class Derived : public Base {
  public:
    Derived() { 
        std::cout << "Derived Ctor" << std::endl; 
    }
    ~Derived() override { 
        std::cout << "Derived Dtor" << std::endl; 
    }
};
int main() {
    std::cout << "Creating Derived object via Base pointer:" << std::endl;
    Base* ptr = new Derived(); // Base Ctor runs, then Derived Ctor

    std::cout << "\nDeleting object via Base pointer (virtual dtor works):" << std::endl;
    delete ptr; // Calls Derived Dtor first, then Base Dtor

  return 0;
}
/* 
Output:
Creating Derived object via Base pointer:
Base Ctor
Derived Ctor

Deleting object via Base pointer (virtual dtor works):
Derived Dtor
Base Dtor
*/








#include <iostream>
using namespace std;
class Base { 
    public: 
      virtual void fun()=0;
      virtual ~Base() = default; 
};
class Derived : public Base { 
    public: 
       void fun(){ 
         cout << "Called derived function!" << endl; 
       } 
};

int main() {
    Base* basePtr = new Derived(); 
    basePtr->fun();

    delete basePtr;
    return 0;
}
/*
Called derived function!
*/




1. At Compile Time:

During compile time, the compiler knows about the structure of the classes and the virtual functions defined in those classes. 
It does not know the exact object type being used (since that depends on runtime behavior), 
but it does set up the mechanism for handling virtual function calls via the vtable.


Compile-time Structure
Class Base:
-> Base has a pure virtual function fun().
-> Base's vtable will have an entry for fun(). 
   However, since fun() is pure virtual, the compiler will set up a "dummy" or "empty" implementation in the vtable, 
   which will be overridden by derived classes.



Class Derived:
-> Derived has an overridden version of fun().
-> Derived's vtable will point to the actual implementation of fun().

The vtable is generated per class that has virtual functions or inherits from a class with virtual functions. 
The vtable stores pointers to the functions that are part of the class. Each class that has virtual functions has a unique vtable.



Visualizing Vtable at Compile Time:
For Base and Derived, the vtables are set up as follows:

Base Class (Compile-Time Vtable):
-> vtable for Base: 
   It contains a pointer to the pure virtual function fun(), which doesn't have an actual implementation (since it's pure virtual, 
   so the call to fun() will be deferred to the derived class).

| vptr for Base | ---> [ Address of pure virtual function `fun()` ]



Derived Class (Compile-Time Vtable):
-> vtable for Derived: It contains a pointer to the actual implementation of fun() in the Derived class.

| vptr for Derived | ---> [ Address of function `fun()` in Derived ]





2. At Run-Time:

During runtime, when you create an object of type Derived, the system creates a vptr for that object. 
This vptr points to the appropriate vtable (depending on the actual type of the object).

At runtime, when you call basePtr->fun(), the program will use the vptr of the object (basePtr points to a Derived object), 
and this vptr will refer to the vtable of the Derived class. It will then call the correct version of fun() (the one in Derived).



Runtime Behavior:
-> Creating the Object:
   When Base* basePtr = new Derived(); is executed, a Derived object is created, and the vptr for this object points to the vtable of Derived.

-> Function Call via vptr:
   When basePtr->fun(); is called, the vptr inside the Derived object is used to look up the actual function in the vtable of Derived, 
   which points to the Derived::fun() function.

->Deleting the Object:
  The delete basePtr; statement calls the destructor of the Derived class (and then the destructor of the Base class), 
  again using the vptr mechanism to ensure that the correct destructor is called.



Visualizing Vptr and Vtable at Runtime:
->Creating Derived Object:
  The vptr in the Derived object points to the vtable of the Derived class.

->Calling basePtr->fun():
  The basePtr points to a Derived object. The vptr inside this object points to the vtable of Derived.
  The program looks up fun() in the Derived vtable and calls the Derived::fun() method.




Runtime Vtable for Base and Derived:
-> Derived Object (Runtime):
   Object of Derived:
   | vptr (points to Derived's vtable) | ---> [ Address of `Derived::fun()` ]


-> Base (Virtual Table):
   vtable for Base (No actual function address for `fun()`):
   | [ Address of pure virtual function (abstract) ]


-> Derived (Virtual Table):
   vtable for Derived:
   | [ Address of `Derived::fun()` ]  // Overridden function





Diagram:
Here is a diagram that shows how the vptr and vtable work in both compile-time and runtime:

Compile-time:
                Base Class (Compile-time)
        +---------------------------+
        | vptr for Base             |
        | --------------------------| 
        | [ Address of pure virtual ]|
        +---------------------------+

               Derived Class (Compile-time)
        +---------------------------+
        | vptr for Derived           |
        | --------------------------|
        | [ Address of `Derived::fun()` ]
        +---------------------------+



Runtime:

When we run the program and create a Derived object:
    Derived Object (Runtime)
   +----------------------------+
   | vptr (points to Derived's vtable) |
   | ----------------------------|
   | [ Address of `Derived::fun()` ]    |
   +----------------------------+
            |
            v
     +-------------------------+
     | vtable for Derived      |
     | ------------------------|
     | [ Address of `Derived::fun()` ]  |
     +-------------------------+


At runtime, when basePtr->fun() is invoked, it uses the vptr in the Derived object to call the correct function from the vtable of Derived.



Final Explanation:
-> At compile time, the compiler sets up the vtables for each class that has virtual functions. 
   It also determines where each function (virtual or overridden) is located in memory.


-> At runtime, the vptr in each object points to the appropriate vtable for that class. When a virtual function is called, 
   the vptr is used to look up the function in the corresponding vtable, ensuring that the correct version of the function 
   (based on the actual object type) is called.

Output:
For the provided code:
Base* basePtr = new Derived();
basePtr->fun();  // This will call Derived::fun()
delete basePtr;


The output is:
Called derived function!









VVI

how can we overload both types of casting operators:

1. Conversion Operator (Implicit Type Casting)
This allows you to implicitly convert an object of a class to another type.

Example of Implicit Casting:
#include <iostream>
using namespace std;
class MyClass {
  public:
    int value;  
    MyClass(int v) : value(v) {}
    // Conversion operator to convert MyClass to int
    operator int() const {
        return value;
    }
};
int main() {
    MyClass obj(42);
    int x = obj;  // Implicit conversion from MyClass to int using the overloaded operator
    cout << "Converted value: " << x << endl;  
    return 0;
}

Explanation:
The operator int() is a conversion operator that allows an object of type MyClass to be implicitly converted to an int.
The line int x = obj; will call the operator int() function to perform the conversion.

Output:
Converted value: 42

In this case, the MyClass object obj is implicitly converted to an int because of the overloaded operator int().


2. Explicit Conversion Operator (Prevent Implicit Conversion)
If you want to prevent implicit conversions and force the user to perform an explicit cast, you can use the explicit keyword.
Example of Explicit Casting:
#include <iostream>
using namespace std;
class MyClass {
  public:
    int value;  
    MyClass(int v) : value(v) {}
    // Explicit conversion operator to convert MyClass to int
    explicit operator int() const {
        return value;
    }
};
int main() {
    MyClass obj(42);
    // int x = obj;  // Error: Cannot implicitly convert MyClass to int
    // Use explicit casting
    int x = static_cast<int>(obj);  // Explicit conversion using static_cast
    cout << "Converted value: " << x << endl;
    return 0;
}

Explanation:
The operator int() is marked as explicit, so you cannot implicitly convert MyClass to int.
You must now use explicit casting with static_cast<int>(obj) to perform the conversion.

Output:
Converted value: 42

This approach is often used when you want to avoid accidental or undesired implicit conversions and require the user to explicitly cast objects.



3. Dynamic Cast Operator (for Polymorphic Classes)
--> You cannot directly overload the dynamic_cast operator. 
--> However, polymorphic classes (classes with at least one virtual function) can be casted using dynamic_cast to safely convert 
    base class pointers or references to derived class pointers or references.
--> Here’s an example of how dynamic_cast works in polymorphic classes, although you don't overload dynamic_cast:

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class\n"; } // Virtual function to enable polymorphism
};

class Derived : public Base {
public:
    void show() override { cout << "Derived class\n"; }
};

int main() {
    Base* basePtr = new Derived();  // Base class pointer pointing to Derived class object

    // Using dynamic_cast to safely cast from Base* to Derived*
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);

    if (derivedPtr) {
        derivedPtr->show();  // This will call the Derived class's show() method
    } else {
        cout << "Cast failed\n";
    }

    delete basePtr;
    return 0;
}

Explanation:

dynamic_cast is used here to safely cast the Base* pointer to a Derived* pointer.

This works only when there is polymorphism (at least one virtual function in the base class).

If the cast is invalid (e.g., casting to a wrong type), dynamic_cast returns nullptr (for pointers) or throws std::bad_cast (for references).

Output:
Derived class

Summary of Overloading Type-Casting Operators:

Conversion Operators (operator Type): Allows implicit conversion from one type to another (e.g., operator int() to convert a class to an integer).

Explicit Conversion Operators (explicit operator Type): Forces the user to perform explicit casting, preventing implicit conversions.

dynamic_cast: Cannot be overloaded, but it allows safe downcasting in polymorphic classes (requires at least one virtual function).