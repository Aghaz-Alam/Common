//Abstract   
//interface  

Difference Between Abstract Class and Interface in C++

In C++, both abstract classes and interfaces are used to define abstract behaviors and allow for polymorphism, 
but they differ in their purpose, usage, and how they are implemented. 


1. Abstract Class
   An abstract class is a class that cannot be instantiated directly, and it typically contains pure virtual functions 
   (functions without a definition) that must be overridden in derived classes. 
   
   An abstract class can also have non-abstract methods (methods with a definition) and member variables, 
   which means it can have both implemented and unimplemented functions.
    ->Pure Virtual Function: A function is made pure virtual by assigning it the value 0 (e.g., virtual void foo() = 0;).
    ->An abstract class may or may not have member variables.
    ->An abstract class can have constructors, destructors, and member variables.



2. Interface
   In C++, there is no explicit interface keyword, but you can simulate interfaces by creating an abstract class that
   only contains pure virtual functions and no data members or implemented methods. 
   
   An interface is typically a contract that a class agrees to implement, and it provides only the declaration of methods, 
   but not their implementation.

    ->Pure Virtual Functions Only: An interface is essentially an abstract class with only pure virtual functions and no data members.
    ->Interfaces in C++ do not have constructors, destructors, or member variables (in most cases).
    ->Interfaces focus on defining a set of methods that implementing classes must provide.



Key Differences:
| Feature                      | Abstract Class                                                | Interface                                                        |
| ---------------------------- | ------------------------------------------------------------- | ---------------------------------------------------------------- |
| **Purpose**                  | To define common behavior and provide partial implementation. | To define a contract for classes to implement, with no behavior. |
| **Pure Virtual Functions**   | Can have both pure virtual and normal functions.              | Can only have pure virtual functions.                            |
| **Data Members**             | Can have data members.                                        | Cannot have data members.                                        |
| **Constructors/Destructors** | Can have constructors and destructors.                        | Cannot have constructors or destructors.                         |
| **Multiple Inheritance**     | C++ supports multiple inheritance of abstract classes.        | C++ allows multiple inheritance of interfaces.                   |
| **Access Modifiers**         | Can have private, protected, and public members.              | All members are by default public.                               |




1. Abstract Class Example
   An abstract class can have both pure virtual functions (which must be overridden by derived classes) and 
   regular functions (which can be optionally overridden).

#include <iostream>
using namespace std;
// Abstract class
class AbstractShape {
  public:
    // Pure virtual function (no implementation here)
    virtual void draw() = 0;

    // Regular function (can have an implementation)
    void printArea() {
        cout << "Calculating area..." << endl;
    }

    // Virtual destructor (optional, but good practice for abstract classes)
    virtual ~AbstractShape() {}
};
class Circle : public AbstractShape {
  public:
    // Override the pure virtual function
    void draw() override {
        cout << "Drawing a Circle" << endl;
    }
};
class Rectangle : public AbstractShape {
  public:
    // Override the pure virtual function
    void draw() override {
        cout << "Drawing a Rectangle" << endl;
    }
};
int main() {
    // AbstractShape s; // Cannot instantiate an abstract class

    AbstractShape* shape1 = new Circle();
    AbstractShape* shape2 = new Rectangle();

    shape1->draw();    // Output: Drawing a Circle
    shape1->printArea(); // Output: Calculating area...

    shape2->draw();    // Output: Drawing a Rectangle
    shape2->printArea(); // Output: Calculating area...

    delete shape1;
    delete shape2;

    return 0;
}

Explanation:
--> AbstractShape is an abstract class with one pure virtual function (draw()) and one regular function (printArea()).
--> Derived classes Circle and Rectangle override the draw() function, but they do not need to implement printArea(), 
    since it is already implemented in the base class.
--> The program cannot instantiate AbstractShape because it is an abstract class, but it can instantiate Circle and Rectangle 
    because they provide implementations for the pure virtual function draw().





2. Interface Example
   An interface in C++ can be implemented as a class with only pure virtual functions and no data members or implementation.

#include <iostream>
using namespace std;
// Interface: All methods must be pure virtual and have no implementation
class Drawable {
  public:
    virtual void draw() = 0; // Pure virtual function
    virtual void resize() = 0; // Pure virtual function
    virtual ~Drawable() {} // Virtual destructor (optional)
};

class Circle : public Drawable {
  public:
    // Implement the interface methods
    void draw() override {
        cout << "Drawing a Circle" << endl;
    }
    void resize() override {
        cout << "Resizing the Circle" << endl;
    }
};

class Square : public Drawable {
  public:
    // Implement the interface methods
    void draw() override {
        cout << "Drawing a Square" << endl;
    }
    void resize() override {
        cout << "Resizing the Square" << endl;
    }
};
int main() {
    Drawable* shape1 = new Circle();
    Drawable* shape2 = new Square();

    shape1->draw();     // Output: Drawing a Circle
    shape1->resize();   // Output: Resizing the Circle

    shape2->draw();     // Output: Drawing a Square
    shape2->resize();   // Output: Resizing the Square

    delete shape1;
    delete shape2;

  return 0;
}

Explanation:
--> Drawable is an interface in C++ (simulated as an abstract class with only pure virtual functions).
--> The Circle and Square classes implement the methods defined in the Drawable interface.
--> The program cannot instantiate Drawable directly because it contains pure virtual functions, 
    but it can instantiate Circle and Square, which provide concrete implementations of the interface methods.




Key Takeaways:

Abstract Class:
--> Can have both pure virtual functions and regular functions.
--> Can have data members and a constructor.
--> Provides partial implementation and defines common behavior.
--> Used for creating base classes that other classes can inherit from and provide specific implementations.



Interface (Simulated with Abstract Class):
--> Can only have pure virtual functions (methods with no implementation).
--> Cannot have data members or constructors/destructors (in most cases).
--> Provides a contract that classes must follow.
--> Used for defining a common set of methods that any implementing class must provide.



Conclusion:
--> Abstract classes are used when you want to provide some common functionality (e.g., implemented functions) and 
    enforce that derived classes must implement certain methods (pure virtual functions).

--> Interfaces are typically used to define a contract that classes must follow, with no default behavior or data. 
    In C++, interfaces are implemented using abstract classes that only contain pure virtual functions.

/* ------------------------------------------------------------------------------------------------------------------- */
Key Scenarios Where virtual Keyword is Used:
1. Virtual Functions and Runtime Polymorphism
2. Virtual Destructors
3. Virtual Inheritance (not very common but possible)
4. Pure Virtual Functions and Abstract Classes


1. Virtual Functions and Runtime Polymorphism
   When a function is declared as virtual, it enables dynamic polymorphism, where the method call is resolved based on the object type 
   (not the pointer/reference type) at runtime.

Example: Virtual Function and Polymorphism
#include <iostream>
using namespace std;
class Base {
  public:
    virtual void display() {  // Virtual function
        cout << "Base class display function\n";
    }
};
class Derived : public Base {
  public:
    void display() override {  // Override the base class function
        cout << "Derived class display function\n";
    }
};
int main() {
    Base* b;  // Pointer of type Base
    Derived d;

    b = &d;  // Base pointer points to Derived object

    b->display();  // Calls Derived's display because of virtual function

   return 0;
}

Explanation:
--> The function display() is declared as virtual in the Base class.
--> Even though b is a pointer of type Base, when it points to an object of Derived, the Derived class’s display() function is called at runtime.
--> This is possible because of dynamic polymorphism enabled by the virtual keyword.

Output:
Derived class display function

--> Without the virtual keyword, the Base class's display() function would have been called, as the function call would be resolved 
    at compile-time based on the pointer type.









2. Virtual Destructors
   A virtual destructor ensures that when a derived class object is deleted through a base class pointer, 
   the destructor of the derived class is called first, followed by the base class destructor. 
   
   This is important to avoid memory leaks or undefined behavior when dealing with inheritance and dynamic memory allocation.

Example: Virtual Destructor
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {  // Virtual destructor
        cout << "Base class destructor\n";
    }
};
class Derived : public Base {
  public:
    ~Derived() {  // Destructor
        cout << "Derived class destructor\n";
    }
};
int main() {
    Base* b = new Derived();  // Base pointer to Derived object
    delete b;  // Deletes the Derived object

  return 0;
}

Explanation:
--> Virtual destructor ensures that when delete is called on a Base pointer that points to a Derived object, 
    both the Derived and Base destructors are called properly.
--> Without the virtual keyword, only the Base class destructor would be called, potentially causing a memory leak 
    if the derived class had allocated resources.

Output:
Derived class destructor
Base class destructor








3. Virtual Inheritance (Diamond Problem)
   In multiple inheritance, the virtual keyword can be used to avoid ambiguity when multiple classes in the inheritance hierarchy 
   share a common base class.
   This is most commonly associated with the diamond problem, where a class inherits from two classes that both inherit from a common base class.

Example: Virtual Inheritance
#include <iostream>
using namespace std;
class A {
  public:
    void showA() { cout << "Class A\n"; }
};
class B : virtual public A {  // Virtual inheritance
  public:
    void showB() { cout << "Class B\n"; }
};
class C : virtual public A {  // Virtual inheritance
  public:
    void showC() { cout << "Class C\n"; }
};
class D : public B, public C {
  public:
    void showD() { cout << "Class D\n"; }
};
int main() {
    D obj;
    obj.showA();  // No ambiguity, A's function is called
    obj.showB();
    obj.showC();
    obj.showD();

  return 0;
}

Explanation:
-->In this example, classes B and C both virtually inherit from A, ensuring that D only has one instance of A even though D inherits 
   from both B and C.
-->Without virtual inheritance, D would contain two copies of A (one from B and one from C), leading to ambiguity when accessing members of A.

Output:
Class A
Class B
Class C
Class D







4. Pure Virtual Functions and Abstract Classes
   A pure virtual function is a function that has no implementation in the base class and must be implemented in the derived class. 
   It makes the base class abstract, meaning it cannot be instantiated directly.

Example: Pure Virtual Function
#include <iostream>
using namespace std;
class Shape {
  public:
    virtual void draw() = 0;  // Pure virtual function makes Shape an abstract class
    virtual ~Shape() {}
};
class Circle : public Shape {
  public:
    void draw() override {  // Override the pure virtual function
        cout << "Drawing Circle\n";
    }
};
class Square : public Shape {
  public:
    void draw() override {  // Override the pure virtual function
        cout << "Drawing Square\n";
    }
};
int main() {
    Shape* shape1 = new Circle();
    Shape* shape2 = new Square();

    shape1->draw();  // Output: Drawing Circle
    shape2->draw();  // Output: Drawing Square

    delete shape1;
    delete shape2;

  return 0;
}

Explanation:
--> The class Shape is an abstract class because it has a pure virtual function draw().
--> Derived classes like Circle and Square provide the implementation for the draw() function.
--> You cannot create an object of Shape directly, but you can use pointers to Shape to create objects of derived classes 
    and call the draw() method dynamically.

Output:
Drawing Circle
Drawing Square

Summary of Virtual Keyword Use:
--> Virtual Functions: Used to achieve runtime polymorphism. The function to be called is determined at runtime based on the actual object type 
    (not the pointer/reference type).
--> Virtual Destructors: Ensures proper cleanup of derived class objects when deleted through a base class pointer, preventing memory leaks.
--> Virtual Inheritance: Resolves ambiguity in multiple inheritance by ensuring only one instance of the common base class.
--> Pure Virtual Functions: Used in abstract classes to define a contract that derived classes must implement, thus enabling abstract behavior.

Conclusion:
--> The virtual keyword in C++ plays a critical role in enabling polymorphism, managing proper resource cleanup with virtual destructors, 
    and solving inheritance-related issues like the diamond problem in multiple inheritance. 
--> Understanding its correct usage is essential for writing robust, maintainable object-oriented C++ code.
/* ------------------------------------------------------------------------------------------------------------------- */
// //dynamic & static polymorphism

Polymorphism in C++
--> Polymorphism in C++ refers to the ability to use a single interface to represent different underlying forms. 
--> It allows objects of different types to be treated as objects of a common base type, typically through pointers or references. 
--> Polymorphism is crucial for achieving flexibility and reusability in object-oriented programming.


There are two types of polymorphism in C++:
-->Static Polymorphism (Compile-time Polymorphism)
-->Dynamic Polymorphism (Run-time Polymorphism)





1. Static Polymorphism (Compile-time Polymorphism)
==> Static polymorphism occurs when the function to be called is resolved at compile-time. 
==> It is typically achieved using function overloading and operator overloading.

Key Points:
==> The decision on which function to call is made at compile-time.
==> It is implemented through function overloading (same function name with different parameters) or operator overloading.

Example: Function Overloading (Static Polymorphism)
#include <iostream>
using namespace std;
class Printer {
  public:
    // Overloaded function to print integers
    void print(int i) {
        cout << "Printing integer: " << i << endl;
    }
    // Overloaded function to print doubles
    void print(double d) {
        cout << "Printing double: " << d << endl;
    }
    // Overloaded function to print strings
    void print(const string& s) {
        cout << "Printing string: " << s << endl;
    }
};
int main() {
    Printer p;
    
    p.print(42);        // Calls print(int)
    p.print(3.14);      // Calls print(double)
    p.print("Hello!");  // Calls print(string)
    
   return 0;
}

Explanation:
-> The print() function is overloaded to handle different data types: int, double, and string.
-> The compiler resolves which print() function to call at compile-time based on the argument type passed.

Output:
Printing integer: 42
Printing double: 3.14
Printing string: Hello!




Example: Operator Overloading (Static Polymorphism)
#include <iostream>
using namespace std;
class Complex {
  public:
    int real, imag;

    Complex(int r, int i) : real(r), imag(i) {}

    // Overload the '+' operator to add two complex numbers
    Complex operator+(const Complex& obj) {
        return Complex(real + obj.real, imag + obj.imag);
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3, 4), c2(1, 2);

    Complex c3 = c1 + c2;  // Calls overloaded operator+
    c3.display();

   return 0;
}

Explanation:
--> The + operator is overloaded to add two complex numbers.
--> This is an example of static polymorphism where the compiler resolves the appropriate operator at compile-time.

Output:
4 + 6i








2. Dynamic Polymorphism (Run-time Polymorphism)
--> Dynamic polymorphism occurs when the function to be called is determined at runtime. 
--> It is achieved through inheritance and virtual functions. 
--> The decision of which function to call is based on the actual type of the object, not the pointer/reference type.

Key Points:
--> Virtual functions are used to achieve dynamic polymorphism.
--> The function to be called is determined at runtime based on the type of the object being pointed to, not the type of the pointer.

Example: Dynamic Polymorphism with Virtual Functions
#include <iostream>
using namespace std;
class Base {
  public:
    // Virtual function to be overridden in derived classes
    virtual void display() {
        cout << "Base class display function\n";
    }
    virtual ~Base() {} // Virtual destructor
};
class Derived : public Base {
  public:
    void display() override { // Override the base class function
        cout << "Derived class display function\n";
    }
};
int main() {
    Base* b;  // Pointer of type Base
    Derived d;  // Derived class object

    b = &d;  // Base pointer pointing to a Derived object

    b->display();  // Virtual function call, resolved at runtime

   return 0;
}

Explanation:
--> Base class has a virtual function display().
--> Derived class overrides the display() function.
--> At runtime, the Base class pointer b, which points to a Derived object, will call the display() function of the 
    Derived class because the function is virtual.
--> This is dynamic polymorphism, where the decision of which function to call is made at runtime based on the object type.

Output:
Derived class display function




Example: Virtual Destructor in Dynamic Polymorphism
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {  // Virtual destructor
        cout << "Base class destructor\n";
    }
};
class Derived : public Base {
  public:
    ~Derived() {  // Destructor
        cout << "Derived class destructor\n";
    }
};
int main() {
    Base* b = new Derived();  // Base pointer to Derived object
    delete b;  // Deletes the Derived object, calls both destructors
  return 0;
}
Explanation:
--> If you delete a Derived object through a Base pointer, it will call the Derived class destructor first, and then the Base class destructor.
--> This is important for proper cleanup, especially if the derived class has dynamically allocated memory. 
    Without a virtual destructor, only the Base class destructor would be called, causing a potential memory leak.

Output:
Derived class destructor
Base class destructor







Key Differences Between Static and Dynamic Polymorphism
| Feature                      | Static Polymorphism                                                               | Dynamic Polymorphism                                                                         |
| ---------------------------- | --------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
| **Binding Time**             | Resolved at **compile-time**                                                      | Resolved at **runtime**                                                                      |
| **Mechanism**                | Function Overloading, Operator Overloading                                        | Virtual Functions, Inheritance                                                               |
| **Function Call Resolution** | Based on **function signature**                                                   | Based on **object type**                                                                     |
| **Performance**              | Typically faster (because resolved at compile-time)                               | May involve overhead due to runtime resolution (virtual table lookup)                        |
| **Use Case**                 | When the function signature can be determined at compile-time (e.g., overloading) | When behavior needs to vary depending on the object's runtime type (e.g., method overriding) |


Conclusion
--> Static Polymorphism (Compile-time) is achieved through function overloading or operator overloading. 
    The appropriate function is chosen at compile time based on the function signature or operator.

--> Dynamic Polymorphism (Run-time) is achieved through virtual functions and inheritance. 
    The appropriate function is chosen at runtime based on the actual object type being pointed to, 
    allowing for more flexible and extensible designs.

/* -------------------------------------------------------------------------------------------------------------------- */
#include <iostream>
using namespace std;

class Base {
public:
    virtual void fun() { cout << "Hello "; }
    virtual ~Base() {}  // Virtual destructor
};

class Derived : public Base {
public:
    void fun() override { cout << "Hi!"<<endl; }  // Override virtual function
};

int main() {
    Derived d;
    
    // Allocate an array of Base pointers
    Base* b[2];  // Array of pointers to Base
    
    // Assign the address of Derived object to Base pointers
    b[0] = &d;
    b[1] = &d;

    // Call the virtual function through Base pointer
    b[0]->fun();  // Should print "Hi!"
    
    b[1]->fun();  // Should print "Hi!"
    
    // No need to delete anything since b is not dynamically allocated
    // It's a statically allocated array of Base pointers, so no delete[] is needed.
    
    return 0;
}
/*
Hi!
Hi!
*/




#include <iostream>
using namespace std;

class Base {
public:
    virtual void fun() { cout << "Hello "; }
    virtual ~Base() {}  // Virtual destructor
};

class Derived : public Base {
public:
    void fun() override { cout << "Hi!"<<endl; }  // Override virtual function
};

int main() {
    // Dynamically allocate an array of Base pointers (size 2)
    Base** b = new Base*[2];  // Array of pointers to Base
    
 for(int i=0; i<2; i++){
    b[i] = new Derived();  // Dynamically allocate Derived object
 }  


 for(int i=0; i<2; i++){
    // Call the virtual function through Base pointer
    b[0]->fun();  // Should print "Hi!"
}
    cout << endl;
   
 for(int i=0; i<2; i++){   
    // Deallocate the dynamically allocated Derived objects
    delete b[i];  // Delete the first Derived object
 }   
    // Deallocate the array of Base pointers
    delete[] b;  // Delete the array of Base pointers

    return 0;
}
/*
Hi!
Hi!
*/



#include <iostream>
using namespace std;

class Base {
public:
    virtual void fun() { cout << "Hello "; }
    virtual ~Base() {}  // Virtual destructor
};

class Derived : public Base {
public:
    void fun() override { cout << "Hi!"; }  // Override virtual function
};

int main() {
    // Dynamically allocate an array of Base pointers (size 2)
    Base** b = new Base*[2];  // Array of pointers to Base
    
    // Dynamically allocate Derived objects and assign their addresses to Base pointers
    b[0] = new Derived();  // Dynamically allocate Derived object
    b[1] = new Derived();  // Dynamically allocate another Derived object

    // Call the virtual function through Base pointer
    b[0]->fun();  // Should print "Hi!"
    cout << endl;
    b[1]->fun();  // Should print "Hi!"
    
    // Deallocate the dynamically allocated Derived objects
    delete b[0];  // Delete the first Derived object
    delete b[1];  // Delete the second Derived object
    
    // Deallocate the array of Base pointers
    delete[] b;  // Delete the array of Base pointers

    return 0;
}
/*
Hi!
Hi!
*/


/* ---------------------------------------------------------------------------------------------------------------------- */
#include<iostream>
#include<memory>
void allocate() {
    //int* data = new int(10); 
    std::unique_ptr<int> data =std::make_unique<int>(10);
    
    std::cout << "Value: " << *data << std::endl;
}
 
int main() {
    for (int i = 0; i < 5; ++i) {
        allocate(); 
    }
 
    return 0;
}



// valgrine ./*.cpp

Understanding Valgrind Output in Detail
When you run a program with Valgrind, the tool tracks memory operations in your program, and provides detailed information in the terminal. 
To understand this better, let us go step by step with an example.

Example C++ Program with a Memory Leak:
#include <iostream>
using namespace std;
class MyClass {
  public:
    MyClass() { cout << "MyClass constructor\n"; }
    ~MyClass() { cout << "MyClass destructor\n"; }
};
int main() {
    MyClass* obj = new MyClass;  // Memory allocated, but not freed
    // Forget to call delete obj;
  return 0;
}

Steps to Compile and Run with Valgrind:
Compile the Program:
First, you compile your program with debugging information (-g flag) so Valgrind can show you better results.
g++ -g -o program program.cpp

Run the Program with Valgrind:
Then, you run the compiled program with Valgrind to detect any memory issues:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program


Valgrind Output Breakdown
Once the program runs under Valgrind, you’ll see an output like this:

==12345== Memcheck, a memory error detector
==12345== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==12345== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==12345== Command: ./program
==12345==
MyClass constructor
MyClass destructor
==12345== 16 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4C2A6D2: operator new(unsigned long) (vg_replace_malloc.c:344)
==12345==    by 0x4005BC: main (program.cpp:10)
==12345==
==12345== LEAK SUMMARY:
==12345==    definitely lost: 16 bytes in 1 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==    possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345==    suppressed: 0 bytes in 0 blocks
==12345==
==12345== For counts of detected and suppressed errors, rerun with: -v
==12345== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


Now, let's break down what Valgrind is telling us:

1. Memcheck Summary (Top part)
==12345== Memcheck, a memory error detector
==12345== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==12345== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==12345== Command: ./program


==12345== is the Valgrind process ID. This helps you identify the process running under Valgrind.

It tells you that Memcheck, which is Valgrind’s memory error detector, is being used.




2. Constructor and Destructor Messages
MyClass constructor
MyClass destructor

This output is from your program, not Valgrind. It indicates that the constructor of MyClass was called to create an object 
and the destructor was called when the program finished.

Valgrind does not output this, but it tracks memory allocated in this section of the code.





3. Memory Leak Information:
This is the most important section where Valgrind detects memory issues. The memory leak details are displayed as:

==12345== 16 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4C2A6D2: operator new(unsigned long) (vg_replace_malloc.c:344)
==12345==    by 0x4005BC: main (program.cpp:10)

Key Parts of the Leak Report:

Memory Lost:
16 bytes in 1 blocks are definitely lost

16 bytes of memory are leaked, and it was allocated in 1 block.

Definitely lost means that the allocated memory is unreachable at the time the program ends. 
This is usually the most critical kind of memory leak because it’s allocated but never freed.

Stack Trace:

==12345==    at 0x4C2A6D2: operator new(unsigned long) (vg_replace_malloc.c:344)
==12345==    by 0x4005BC: main (program.cpp:10)


0x4C2A6D2: This is a memory address where the allocation happened. This is part of Valgrind's internal memory tracking.

operator new(unsigned long): This indicates that the memory was allocated via the new operator. 
The issue occurred at the address shown here (0x4C2A6D2), which is part of Valgrind’s internal memory management.

main (program.cpp:10): This indicates that the memory allocation happened at line 10 in your main function, 
where the object obj was created (MyClass* obj = new MyClass;).

Valgrind can also track where in your code the allocation occurred, making it easy to see exactly where you missed the delete or delete[].







4. Leak Summary (Bottom part):
==12345== LEAK SUMMARY:
==12345==    definitely lost: 16 bytes in 1 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==    possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345==    suppressed: 0 bytes in 0 blocks


-->Leak Summary tells you how much memory was leaked in total and gives you a breakdown of different types of leaks:
-->definitely lost: Memory that was allocated but has no references to it anymore. This is the most important kind of leak and usually indicates a bug.
-->indirectly lost: Memory that was lost due to another object being lost (e.g., if an object with a pointer to dynamically allocated memory is 
   itself leaked).
-->possibly lost: This refers to memory that may have been lost (e.g., if the pointer was overwritten).
-->still reachable: This is memory that is still pointed to at the end of the program. It might not be a leak, 
   but it’s suboptimal because it wasn’t freed before the program terminated.





5. Final Error Summary:
==12345== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


This tells you that 1 memory leak was detected from 1 location in the code.
It also shows you if there were any suppressed errors (in this case, none).

What You Should Focus On:
The memory leak is specifically reported as 16 bytes in 1 blocks are definitely lost.
The stack trace shows where in your code the memory allocation occurred (in main() at line 10, where you used new MyClass).

Fixing the Memory Leak:
To fix the memory leak, ensure that the memory is properly deallocated using delete:

#include <iostream>
using namespace std;
class MyClass {
 public:
    MyClass() { cout << "MyClass constructor\n"; }
    ~MyClass() { cout << "MyClass destructor\n"; }
};
int main() {
    MyClass* obj = new MyClass;  // Memory allocated
    delete obj;  // Memory properly freed
   return 0;
}

Conclusion:
-->Valgrind helps you track memory usage by monitoring allocations and deallocations.
-->It reports memory leaks (memory that was allocated but not freed) and provides useful stack trace information 
   so you can pinpoint the exact location in your code where the memory leak occurred.
-->Memory leaks are the most critical problem detected by Valgrind, but it can also catch other issues like 
   uninitialized memory access and buffer overflows.
-->Valgrind's output gives you detailed insights, including where memory was allocated and how much memory was leaked,
   making it easier to debug memory-related issues in your C++ programs.



/* ---------------------------------------------------------------------------------------------------------------------- */
// array
// vector  [], at()
// list     
// forward_list
// queue
// stack
// map
// multimap
// set
// multiset


// vector
// class
// 50 members
When choosing the most appropriate STL (Standard Template Library) container to represent a class with 50 students, 
we need to consider a few factors:

--> Type of Operations (access, modification, insertion, deletion)
--> Order of Students (whether the order is important or not)
--> Efficiency (in terms of time complexity for common operations)
--> Need for Dynamic Resizing (whether the number of students can change)
--> Direct Access to Elements (whether random access to specific students is required)


Possible STL Containers
--> std::vector
--> std::list
--> std::deque
--> std::array
--> std::set
--> std::map
--> std::unordered_set
--> std::unordered_map



Let us discuss each container in more detail and determine the best choice.
1. std::vector
--> Description: A std::vector is a dynamic array that allows for random access to elements and resizes dynamically 
    when elements are added or removed.

--> Best for: Fast random access, and efficient at handling sequential data.

Pros:
--> Fast random access (constant time complexity for accessing elements).
--> Efficient memory usage and resizing (amortized constant time complexity for insertions).
--> You can reserve space ahead of time to avoid reallocations.

Cons:
--> Inserting or deleting elements in the middle of the vector is slower (O(n) for shifting elements).
--> Not suitable for when frequent insertions/deletions happen in the middle or at the beginning.



Why Choose std::vector?
--> Access speed: With 50 students, random access is generally more useful. 
    If you need to frequently access specific students (e.g., by index), std::vector provides constant time access.
--> Insertion efficiency: Given that the class has a fixed number of students (50), frequent insertions might not happen, 
    so resizing won't be an issue.
--> Memory efficiency: Since the number of students is fixed (50), std::vector provides a good balance between memory efficiency and performance.

Code Example:
#include <iostream>
#include <vector>
#include <string>
class Student {
  public:
    std::string name;
    int age;  
    Student(std::string n, int a) : name(n), age(a) {}
};
int main() {
    // Create a vector of 50 students
    std::vector<Student> students;

    // Adding 50 students
    for (int i = 0; i < 50; ++i) {
        students.push_back(Student("Student" + std::to_string(i+1), 20 + i));
    }

    // Accessing a student by index (random access)
    std::cout << "Student 1: " << students[0].name << ", Age: " << students[0].age << std::endl;

  return 0;
}








2. std::list
--> Description: A doubly linked list that provides efficient insertion and deletion at both ends (head and tail).
--> Best for: Frequent insertions and deletions, especially in the middle of the container.

Pros:
--> Fast insertions and deletions (O(1)) at the beginning or the end.
--> No need to shift elements (as with a std::vector).

Cons:
--> Slow random access (O(n) to access an element, because it requires traversing the list).
--> Higher memory overhead due to the pointers in each node.


Why Not std::list?
--> If you don’t need frequent insertions and deletions and you need fast access to students by index, 
    std::list is not ideal. Its lack of random access would make accessing a student by index inefficient.


Code Example:
#include <iostream>
#include <list>
#include <string>
class Student {
  public:
    std::string name;
    int age;
    
    Student(std::string n, int a) : name(n), age(a) {}
};
int main() {
    // Create a list of 50 students
    std::list<Student> students;

    // Adding 50 students
    for (int i = 0; i < 50; ++i) {
        students.push_back(Student("Student" + std::to_string(i+1), 20 + i));
    }

    // Accessing a student (slow, O(n) traversal)
    auto it = students.begin();
    std::advance(it, 10);  // Accessing the 11th student
    std::cout << "Student 11: " << it->name << ", Age: " << it->age << std::endl;

  return 0;
}





3. std::deque
--> Description: A double-ended queue that allows for efficient insertions and deletions at both ends, and provides random access.
--> Best for: Scenarios where you need to efficiently add/remove elements from both the front and the back.

Pros:
--> Provides constant time access to elements by index (like std::vector).
--> Efficient insertions and deletions at both ends.

Cons:
--> Inserting/removing from the middle is slower than std::vector (O(n)).
--> Generally, slightly more memory overhead than std::vector.


Why Not std::deque?
--> If you are not performing frequent insertions or deletions at both ends, std::deque does not provide significant advantages over 
    std::vector for your use case.

Code Example:
#include <iostream>
#include <deque>
#include <string>
class Student {
  public:
    std::string name;
    int age;
    
    Student(std::string n, int a) : name(n), age(a) {}
};
int main() {
    // Create a deque of 50 students
    std::deque<Student> students;

    // Adding 50 students
    for (int i = 0; i < 50; ++i) {
        students.push_back(Student("Student" + std::to_string(i+1), 20 + i));
    }

    // Accessing a student by index (random access)
    std::cout << "Student 1: " << students[0].name << ", Age: " << students[0].age << std::endl;

  return 0;
}











4. std::array
--> Description: A fixed-size array (known at compile-time), provides random access and has a fixed size.
--> Best for: When the number of students is fixed and known at compile time.

Pros:
--> Fixed size makes it ideal for fixed-size collections.
--> Fast access (constant time for random access).

Cons:
--> The size is fixed and cannot change once it is initialized, so it is not suitable for dynamic datasets.
--> Limited flexibility compared to other containers like std::vector.


Why Not std::array?
--> If the number of students is fixed (50), and you don’t need to resize the collection, std::array is a valid option. 
    However, std::vector still offers more flexibility in case you need dynamic resizing in the future.

Code Example:
#include <iostream>
#include <array>
#include <string>
class Student {
  public:
    std::string name;
    int age;
    
    Student(std::string n, int a) : name(n), age(a) {}
};
int main() {
    // Create a fixed-size array of 50 students
    std::array<Student, 50> students;

    // Adding 50 students
    for (int i = 0; i < 50; ++i) {
        students[i] = Student("Student" + std::to_string(i+1), 20 + i);
    }

    // Accessing a student by index (random access)
    std::cout << "Student 1: " << students[0].name << ", Age: " << students[0].age << std::endl;

  return 0;
}

Conclusion
--> For a class of 50 students, std::vector is generally the best choice. Here’s why:
--> Random access is typically needed for tasks like accessing a specific student by index.
--> Efficient resizing: Although the number of students is fixed at 50, std::vector will provide flexibility in case that number changes
    in the future.
--> It provides good memory efficiency and fast access for a relatively small number of elements like 50.
--> In summary, std::vector is the most appropriate STL container for this use case because it provides:
--> Efficient access to individual students (O(1) for random access).
--> Efficient memory usage and dynamic resizing, should the number of students change.

/* ---------------------------------------------------------------------------------------------------------------------- */
// deadlock   lock_guard<muex>lock(), unique_lock<mutex>lock()
// livelock   -

Deadlock and Livelock in C++ Threading
--> In multithreaded programming, deadlock and livelock are two types of concurrency issues that can occur 
    when threads interact with each other inappropriately. These problems can cause programs to hang, crash, or behave incorrectly.

1. Deadlock
--> Deadlock occurs when two or more threads are unable to proceed because they are each waiting for the other to release resources. 
--> This results in a cyclical dependency where no thread can continue its execution.


Conditions for Deadlock
Deadlock occurs when the following four conditions are met simultaneously:
--> Mutual Exclusion: At least one resource is held in a non-shareable mode, i.e., only one thread can use the resource at a time.
--> Hold and Wait: A thread is holding at least one resource and waiting for additional resources held by other threads.
--> No Preemption: A resource cannot be forcibly taken from a thread holding it; it must be released voluntarily.
--> Circular Wait: A set of threads are waiting for each other in a circular chain, where each thread is holding a resource that 
    the next thread in the chain needs.



Deadlock Example in C++
In this example, we have two threads trying to lock two mutexes (m1 and m2) in reverse order, leading to a deadlock.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
std::mutex m1, m2;

void thread1() {
    std::lock_guard<std::mutex> lock1(m1);
    std::cout << "Thread 1: Locked m1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    std::lock_guard<std::mutex> lock2(m2);  // Will block here
    std::cout << "Thread 1: Locked m2\n";
}

void thread2() {
    std::lock_guard<std::mutex> lock1(m2);
    std::cout << "Thread 2: Locked m2\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    std::lock_guard<std::mutex> lock2(m1);  // Will block here
    std::cout << "Thread 2: Locked m1\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

   return 0;
}

Explanation:
--> Thread 1 locks m1, sleeps for 100ms, then tries to lock m2.
--> Thread 2 locks m2, sleeps for 100ms, then tries to lock m1.
--> Result: Both threads are stuck because Thread 1 is waiting for m2, and Thread 2 is waiting for m1, causing a deadlock.


How to Avoid Deadlock:
--> Lock ordering: Always acquire locks in a fixed order to prevent circular wait.
--> Timeouts: Use timeouts to break out of waiting if a lock cannot be acquired within a reasonable time.
--> Avoid holding multiple locks: Try to avoid situations where a thread needs to hold more than one lock at a time.













2. Livelock
--> Livelock is a situation where two or more threads keep changing their states in response to each other 
    but do not make any progress. 
--> Unlike deadlock, in livelock, the threads are not blocked—they are still active—but they are caught in a cycle where they 
    keep trying to acquire resources or perform actions, but their progress is continually hindered by the actions of others.

Livelock Example in C++

In this example, we simulate livelock by having two threads repeatedly release and acquire locks to avoid deadlock but never make progress.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1, m2;

void thread1() {
    while (true) {
        if (m1.try_lock()) {
            std::cout << "Thread 1: Locked m1\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
            if (m2.try_lock()) {
                std::cout << "Thread 1: Locked m2\n";
                // Do work
                break;  // Done with work
            } else {
                m1.unlock();  // Release m1 and try again
                std::cout << "Thread 1: Released m1 and retrying\n";
            }
        }
    }
}

void thread2() {
    while (true) {
        if (m2.try_lock()) {
            std::cout << "Thread 2: Locked m2\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
            if (m1.try_lock()) {
                std::cout << "Thread 2: Locked m1\n";
                // Do work
                break;  // Done with work
            } else {
                m2.unlock();  // Release m2 and try again
                std::cout << "Thread 2: Released m2 and retrying\n";
            }
        }
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}

Explanation:
--> Thread 1 and Thread 2 try to acquire locks on m1 and m2 respectively.
--> If a thread can not acquire both locks, it releases the one it has and tries again.
--> This results in a livelock where the threads are repeatedly trying to acquire locks but never make progress 
    because they are continuously releasing and retrying.



How to Avoid Livelock:
--> Introduce a backoff strategy: Instead of constantly retrying, introduce a delay before retrying the action.
--> Use more sophisticated synchronization techniques like semaphores or condition variables to avoid unnecessary retries.

Timeouts: If a thread is unable to make progress after a certain period, it should give up or attempt a different action.

Key Differences Between Deadlock and Livelock
| Feature        | **Deadlock**                                                                | **Livelock**                                                                      |
| -------------- | --------------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| **Condition**  | Threads are blocked and **cannot proceed**.                                 | Threads are **actively running**, but **not making progress**.                    |
| **Cause**      | Circular waiting for resources.                                             | Threads keep retrying or adjusting but fail to make progress.                     |
| **Example**    | Two threads waiting for each other to release resources.                    | Two threads continuously trying to acquire resources and retrying.                |
| **Resolution** | Break the circular wait by ordering locks, timeouts, or deadlock detection. | Use backoff strategies, retries with delays, or other synchronization mechanisms. |



Real-World Use Cases
Deadlock and Livelock are common in systems where multiple threads or processes interact and share resources. Common examples include:
Database transactions: When two transactions try to lock the same rows but in a different order, leading to a deadlock.
Operating systems: When multiple processes or threads try to access system resources, leading to resource contention.
Networking: When threads need to acquire locks on shared resources, like network connections or files.



How to Prevent Deadlock and Livelock:

Deadlock Prevention:
--> Lock ordering: Always acquire locks in the same order across all threads.
--> Avoid nested locks: If you must acquire multiple locks, acquire them one by one, but ensure there is a fixed order.
--> Timeouts: Implement timeouts to avoid waiting indefinitely for a lock.

Livelock Prevention:
--> Backoff strategies: Introduce random delays or exponential backoff when a thread cannot proceed.
--> Limit retries: Give up after a certain number of failed attempts and try a different strategy.
--> Use condition variables or semaphores for better synchronization.

Conclusion
--> Both deadlock and livelock are critical issues in multithreading, and careful attention to thread synchronization is required to avoid them. 
    In C++, mechanisms like mutexes, locks, and condition variables can help prevent these issues, but developers need to carefully design 
    their programs and ensure proper resource management to avoid these concurrency bugs.





A comprehensive explanation of how to avoid livelock, followed by C++ program examples for each strategy:
--> Backoff strategy (random / exponential)
--> Using proper synchronization primitives (mutex + condition variables, semaphores)
--> Retry limits with fallback strategy


Each example demonstrates both the livelock scenario and its fix.

✅ 1. What is Livelock?
--> A livelock occurs when two or more threads continuously respond to each other in a way that prevents all of them from making progress.
--> They are not blocked, but they keep retrying in a loop—forever.

✅ 2. Scenario A — Livelock Example & Fix Using Random Backoff
❌ Livelock Example (Two threads constantly yielding to each other)

Both threads try to acquire the same two locks, but on failure they release and retry—forever.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1, m2;

void livelock_worker(const std::string& name) {
    while (true) {
        std::unique_lock<std::mutex> lock1(m1, std::try_to_lock);

        if (!lock1.owns_lock()) {
            continue;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        std::unique_lock<std::mutex> lock2(m2, std::try_to_lock);
        if (!lock2.owns_lock()) {
            // Livelock: releasing lock1 to let the other thread try
            lock1.unlock();
            continue;
        }

        std::cout << name << " acquired both locks!\n";
        break;
    }
}

int main() {
    std::thread t1(livelock_worker, "Thread 1");
    std::thread t2(livelock_worker, "Thread 2");

    t1.join();
    t2.join();
  return 0;
}

//🔴 Both threads endlessly unlock and retry → livelock.




✅ Fix: Introduce Random Backoff

Adding a random delay reduces the chance that both threads retry simultaneously.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

std::mutex m1b, m2b;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(1, 10);

void worker_with_backoff(const std::string& name) {
    while (true) {
        std::unique_lock<std::mutex> lock1(m1b, std::try_to_lock);
        if (!lock1.owns_lock()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
            continue;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        std::unique_lock<std::mutex> lock2(m2b, std::try_to_lock);
        if (!lock2.owns_lock()) {
            lock1.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen))); // Random backoff
            continue;
        }

        std::cout << name << " acquired both locks (with backoff).\n";
        break;
    }
}

int main() {
    std::thread t1(worker_with_backoff, "Thread A");
    std::thread t2(worker_with_backoff, "Thread B");

    t1.join();
    t2.join();
}

//🟢 Random backoff breaks symmetry → prevents livelock.







✅ 3. Scenario B — Avoid Livelock With Condition Variables (No Busy Retry)

Instead of retrying repeatedly, a thread waits until a condition becomes true.

✔ Proper synchronization avoids livelock entirely:
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
bool resource_available = false;
std::condition_variable cv;

void producer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::lock_guard<std::mutex> lock(m);
    resource_available = true;
    std::cout << "Producer: resource created.\n";
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [] { return resource_available; });
    std::cout << "Consumer: resource acquired.\n";
}

int main() {
    std::thread t1(consumer);
    std::thread t2(producer);

    t1.join();
    t2.join();
}

//🟢 No retrying loops → no livelock.





✅ 4. Scenario C — Avoid Livelock Using Semaphores

(Simulated with C++20 counting_semaphore or a simple wrapper.)

✔ Both threads wait until they can proceed instead of constantly retrying.
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::counting_semaphore<1> sem(1);

void task(const std::string& name) {
    sem.acquire();  // blocks instead of retrying
    std::cout << name << " entered critical section.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    sem.release();
}

int main() {
    std::thread t1(task, "Thread 1");
    std::thread t2(task, "Thread 2");

    t1.join();
    t2.join();
}

//🟢 Semaphore ensures progress → no livelock.



✅ 5. Scenario D — Limit Retries (Give Up and Try Different Strategy)

If a thread cannot proceed after several attempts, it aborts or changes behavior.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1c, m2c;

void worker_limited_retry(const std::string& name) {
    int retries = 0;

    while (retries < 10) {
        std::unique_lock<std::mutex> lk1(m1c, std::try_to_lock);
        if (!lk1.owns_lock()) {
            retries++;
            continue;
        }

        std::unique_lock<std::mutex> lk2(m2c, std::try_to_lock);
        if (!lk2.owns_lock()) {
            retries++;
            lk1.unlock();
            continue;
        }

        std::cout << name << " acquired both locks.\n";
        return;
    }

    std::cout << name << " gave up after 10 retries. Switching strategy.\n";
}

int main() {
    std::thread t1(worker_limited_retry, "Thread X");
    std::thread t2(worker_limited_retry, "Thread Y");

    t1.join();
    t2.join();
}


🟢 After too many failures, thread gives up → prevents infinite livelock.
/* ---------------------------------------------------------------------------------------------------------------------- */
// mutex     
// condition_varaible  cv
// simaphore


✅ 1. std::mutex
---> A mutex (mutual exclusion) is a lock that allows only one thread at a time to access a shared resource.

⭐ Purpose:
--> Protect shared data from concurrent access
--> Prevent race conditions
--> Ensure only one thread enters the critical section

✔ Example: Using std::mutex to Protect Shared Counter
Without Mutex (Race Condition)
#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; i++) {
        counter++; // Race condition!
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter = " << counter << "\n";
}

❌ Output will be inconsistent (never 200000).



With Mutex (Safe)
#include <iostream>
#include <thread>
#include <mutex>

int counter2 = 0;
std::mutex m;

void increment_safe() {
    for (int i = 0; i < 100000; i++) {
        std::lock_guard<std::mutex> lock(m);  
        counter2++;  
    }
}

int main() {
    std::thread t1(increment_safe);
    std::thread t2(increment_safe);

    t1.join();
    t2.join();

    std::cout << "Counter (safe) = " << counter2 << "\n";
}

🔍 What happens?
--> std::lock_guard locks the mutex in its constructor
--> Unlocks automatically when leaving scope
--> Prevents both threads from modifying the counter simultaneously
--> No race condition → Always prints 200000






✅ 2. std::condition_variable
--> A condition variable allows a thread to wait until a certain condition becomes true, without wasting CPU cycles.

⭐ Purpose:
--> Blocking wait (no busy-waiting)
--> Thread synchronization based on events
--> Producer–consumer problems

✔ Example: Producer–Consumer (Wait until data is available)
--> Producer: creates data
--> Consumer: waits until producer notifies it

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;
int shared_data = 0;

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        shared_data = 42;
        data_ready = true;
        std::cout << "Producer: Data prepared.\n";
    }

    cv.notify_one();  // Notify waiting consumer
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [] { return data_ready; }); // Wait until condition is true

    std::cout << "Consumer: Got data = " << shared_data << "\n";
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}

🔍 What happens?
--> Consumer waits on cv.wait(...)
--> Producer prepares the data and calls notify_one()
--> Consumer wakes and safely reads the data

Advantages:
--> No CPU waste
--> Avoids livelock and busy loops
--> Perfect for producer–consumer communication





✅ 3. Semaphore
--> C++20 introduced std::counting_semaphore.
--> A semaphore is a counter that controls how many threads can access a resource simultaneously.

⭐ Purpose:
--> Limit simultaneous access (like allowing 3 threads at a time)
--> Works like a lock with a counter

Useful for:
--> Resource pools
--> Connection limits
--> Multi-thread task scheduling

✔ Example: Semaphore Allowing Only 2 Threads at a Time
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::counting_semaphore<2> sem(2); // allow 2 threads at a time

void worker(int id) {
    sem.acquire();  // wait if limit reached

    std::cout << "Thread " << id << " entered critical section.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Thread " << id << " leaving critical section.\n";
    sem.release();  // allow other thread to enter
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    std::thread t4(worker, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

🔍 What Happens?
--> Only two threads can run in the critical section at once
--> Other threads wait until someone calls release()
--> This is different from a mutex (mutex allows only one thread)








/* ---------------------------------------------------------------------------------------------------------------------- */

// //one
// writer()  mutex, and cv  ,  lock_guard<muex>lock()    ---once (RAII) cv.notify_one()
// reader()  mutex, and cv,    unique_lock<mutex>lock() ---cv.wait(lock,[]{retur data!=0;})




Yes — in C++ you can have:
--> one producer / one consumer
--> multiple producers / one consumer
--> one producer / multiple consumers
--> multiple producers / multiple consumers

All using std::condition_variable safely.
--> Below is a complete, clean, modern C++ program demonstrating all scenarios using the same core logic.
    You can select how many producers/consumers to run.

✅ Key Principles
1. Shared State
std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
bool done = false;   // signals producers finished
const size_t MAX_BUFFER = 10;



2. Producer Logic
Wait if buffer is full
Push work
Notify a consumer




3. Consumer Logic
Wait if buffer empty but producers not finished
Pop work
Stop when buffer empty and done == true


✅ Full Working Program (C++17+)
--> This program allows any number of producers & consumers simply by changing constants.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
bool done = false;  // Set true when ALL producers finish
const size_t MAX_BUFFER = 10;

// ---------------- Producer ----------------
void producer(int id, int itemsToProduce) {
    for (int i = 0; i < itemsToProduce; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return buffer.size() < MAX_BUFFER; });

        buffer.push(i);
        std::cout << "Producer " << id << " produced " << i << "\n";

        lock.unlock();
        cv.notify_all();     // notify consumers
    }

    // Mark completion (done only when all producers finish)
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Producer " << id << " finished.\n";
}

// ---------------- Consumer ----------------
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, []{
            return !buffer.empty() || done; 
        });

        if (buffer.empty() && done) {
            // no more work
            std::cout << "Consumer " << id << " exiting.\n";
            break;
        }

        int item = buffer.front();
        buffer.pop();

        std::cout << "Consumer " << id << " consumed " << item << "\n";

        lock.unlock();
        cv.notify_all(); // notify producers
    }
}

// ---------- Main: Run ALL scenarios ----------
int main() {
    const int NUM_PRODUCERS = 3;   // <-- change here
    const int NUM_CONSUMERS = 2;   // <-- change here
    const int ITEMS_PER_PRODUCER = 5;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // launch consumers
    for (int i = 0; i < NUM_CONSUMERS; i++)
        consumers.emplace_back(consumer, i);

    // launch producers
    for (int i = 0; i < NUM_PRODUCERS; i++)
        producers.emplace_back(producer, i, ITEMS_PER_PRODUCER);

    // wait producers
    for (auto &p : producers) p.join();

    // mark done
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();

    // wait consumers
    for (auto &c : consumers) c.join();

    std::cout << "All threads finished.\n";
    return 0;
}

✅ Scenarios Supported
✔ One Producer / One Consumer
const int NUM_PRODUCERS = 1;
const int NUM_CONSUMERS = 1;

✔ Multiple Producers / One Consumer
const int NUM_PRODUCERS = 3;
const int NUM_CONSUMERS = 1;

✔ One Producer / Multiple Consumers
const int NUM_PRODUCERS = 1;
const int NUM_CONSUMERS = 4;

✔ Multiple Producers / Multiple Consumers
const int NUM_PRODUCERS = 5;
const int NUM_CONSUMERS = 5;

✅ Notes

cv.notify_all() ensures correct wake-up when multiple producers or consumers may wait.

done is used to properly stop consumers when production ends.

This implementation is race-free and handles all multi-thread scenarios cleanly.

/* ---------------------------------------------------------------------------------------------------------------------- */
Yes — in C++ you can have:
--> one producer / one consumer
--> multiple producers / one consumer
--> one producer / multiple consumers
--> multiple producers / multiple consumers

/* ----------------------------one producer / one consumer----------------------------------- */
//execution of one thread to the other: one producer / one consumer
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include <atomic>
using namespace std;
mutex mtx;
condition_variable cv;
//int result = 0;  // global value
atomic<int> result{0};  // atomic variable
void Add(int x, int y) {
    lock_guard<mutex> lock(mtx);
    result = x + y; 
    cout << result << endl;
    cv.notify_one();  
}
void Compute() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []{ return result != 0; });  
    cout << result << endl;
}
int main() {
    thread t1(Add, 5, 6); 
    thread t2(Compute); 
    
    t1.join();
    t2.join();

   return 0;
}
/*
11
11
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include<chrono>
using namespace std;

mutex mtx;
condition_variable cv;

int result = 0;       // shared data
bool ready = false;   // signal flag

// Producer
void Add(int x, int y) {
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lock(mtx);
        result = x + y;
        ready = true;            // mark data as ready
        cout << "Producer: " << result << endl;
    }
    cv.notify_one();             // wake consumer
}
// Consumer
void Compute() {
    unique_lock<mutex> lock(mtx);

    // Wait until producer sets "ready = true"
    cv.wait(lock, [] { return ready; });

    cout << "Consumer: " << result << endl;
}
int main() {
    thread t1(Add, 5, 6);
    thread t2(Compute);

    t1.join();
    t2.join();

  return 0;
}
/*
Producer: 11
Consumer: 11
*/


/* ------------------------------Multiple Producers / One Consumer---------------------------------- */
✅ Multiple Producers / One Consumer (C++17)
Fully working program based on your original code:
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;

queue<int> results;   // shared queue of results
bool done = false;    // indicates all producers finished

void Producer(int x, int y, int id) {
    // Simulate computation delay
    this_thread::sleep_for(chrono::milliseconds(100 * id));

    {
        lock_guard<mutex> lock(mtx);
        int value = x + y;
        results.push(value);
        cout << "Producer " << id << " produced: " << value << endl;
    }

    cv.notify_one();   // notify consumer
}

// Consumer reads until all producers finish AND queue is empty
void Consumer(int producerCount) {
    unique_lock<std::mutex> lock(mtx);

    while (true) {
        cv.wait(lock, [&] {
            return !results.empty() || done;
        });

        // If producers finished and nothing left to consume -> exit
        if (results.empty() && done)
            break;

        int value = results.front();
        results.pop();
        cout << "Consumer consumed: " << value << endl;
    }
}

int main() {
    const int NUM_PRODUCERS = 3;

    vector<thread> producers;
    producers.reserve(NUM_PRODUCERS);

    // Launch producers
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(Producer, i + 1, (i + 1) * 2, i);
    }

    // Launch one consumer
    thread consumer(Consumer, NUM_PRODUCERS);

    // Wait producers
    for (auto& t : producers) t.join();

    // Signal completion
    {
        lock_guard<mutex> lock(mtx);
        done = true;
    }
    cv.notify_one();

    // Wait consumer
    consumer.join();

    return 0;
}

How It Works
✔ Producers
--> Each producer computes a result, and pushes it into a shared queue:
--> results.push(value);

✔ Consumer
The consumer waits until:
--> There is data in the queue (!results.empty())
--> OR all producers have finished (done == true)

Then:
--> Consumes (pops) values from the queue
--> Stops when queue is empty and done == true

✔ Synchronization
--> mutex protects the queue
--> condition_variable avoids busy waiting
--> done ensures the consumer does not block forever

Example Output (order may vary)
Producer 0 produced: 1
Consumer consumed: 1
Producer 1 produced: 4
Producer 2 produced: 6
Consumer consumed: 4
Consumer consumed: 6



#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;

queue<int> results;   // shared queue for produced values
bool done = false;    // indicates all producers have finished

// ------------------- Producer -------------------
void Add(int x, int y, int id) {
    // Simulate some computation delay
    this_thread::sleep_for(chrono::milliseconds(100 * id));

    {
        lock_guard<mutex> lock(mtx);
        int value = x + y;
        results.push(value);
        cout << "Producer " << id << " added: " << value << endl;
    }

    cv.notify_one();  // signal consumer
}

// ------------------- Consumer -------------------
void Compute(int producerCount) {
    unique_lock<mutex> lock(mtx);

    while (true) {
        cv.wait(lock, [] {
            return !results.empty() || done;
        });

        // stop when producers finished and no more results
        if (results.empty() && done)
            break;

        int value = results.front();
        results.pop();
        cout << "Consumer computed: " << value << endl;
    }
}

// ------------------- Main -------------------
int main() {
    const int NUM_PRODUCERS = 3;

    vector<thread> producers;
    producers.reserve(NUM_PRODUCERS);

    // launch producers
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(Add, i + 1, (i + 1) * 2, i);
    }

    // launch consumer
    thread consumer(Compute, NUM_PRODUCERS);

    // wait for producers to finish
    for (auto &t : producers)
        t.join();

    // signal consumer that production is done
    {
        lock_guard<mutex> lock(mtx);
        done = true;
    }
    cv.notify_one();

    // wait for consumer
    consumer.join();

    return 0;
}
/*
Producer 0 added: 3
Consumer computed: 3
Producer 1 added: 6
Consumer computed: 6
Producer 2 added: 9
Consumer computed: 9
*/

/* ----------------------------One Producer / Multiple Consumers-------------------------------- */
//✅ Complete Working Program (C++17)
//One Producer / Multiple Consumers
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;

queue<int> results;   // shared queue
bool done = false;    // producer finished

// ----------------- Producer -----------------
void Add() {
    for (int i = 1; i <= 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(100)); // simulate work

        {
            lock_guard<mutex> lock(mtx);
            results.push(i);
            cout << "Producer added: " << i << endl;
        }

        cv.notify_all();  // wake all consumers
    }

    // Producer finished
    {
        lock_guard<mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();
}

// ----------------- Consumer -----------------
void Compute(int id) {
    unique_lock<mutex> lock(mtx);

    while (true) {
        cv.wait(lock, [] {
            return !results.empty() || done;
        });

        if (results.empty() && done) {
            cout << "Consumer " << id << " exiting.\n";
            break;
        }

        int value = results.front();
        results.pop();
        cout << "Consumer " << id << " consumed: " << value << endl;
    }
}

// ------------------- Main -------------------
int main() {
    const int NUM_CONSUMERS = 3;

    thread producer(Add);

    vector<thread> consumers;
    consumers.reserve(NUM_CONSUMERS);

    for (int i = 0; i < NUM_CONSUMERS; ++i)
        consumers.emplace_back(Compute, i);

    producer.join();

    for (auto &t : consumers)
        t.join();

    return 0;
}
/*
✔ How it Works
Producer (Add()):
Produces numbers 1 → 10
Pushes to queue
Calls notify_all() so multiple consumers can wake


Consumers (Compute(int id)):
Each waits for data or producer completion
Pops items from the queue

Stops when:
Queue is empty
AND producer has set done = true

Synchronization:
mutex protects the queue
condition_variable prevents busy waiting
done ensures consumers exit safely

📌 Example Output (order varies)
Producer added: 1
Consumer 1 consumed: 1
Producer added: 2
Consumer 1 consumed: 2
Producer added: 3
Consumer 0 consumed: 3
Producer added: 4
Consumer 2 consumed: 4
Producer added: 5
Consumer 2 consumed: 5
Producer added: 6
Consumer 0 consumed: 6
Producer added: 7
Consumer 0 consumed: 7
Producer added: 8
Consumer 0 consumed: 8
Producer added: 9
Consumer 2 consumed: 9
Producer added: 10
Consumer 2 consumed: 10
Consumer 2 exiting.
Consumer 0 exiting.
Consumer 1 exiting.
*/


/* ---------------------------Multiple Producers / Multiple Consumers--------------------------------------------- */

✅ Complete C++ Program (C++17)
Multiple Producers / Multiple Consumers

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;

queue<int> results;   // shared queue
bool done = false;    // all producers finished
int activeProducers = 0;   // number of running producers

// -------------------- Producer --------------------
void Add(int startValue, int count, int id) {
    {
        lock_guard<mutex> lock(mtx);
        activeProducers++;     // register producer
    }

    for (int i = 0; i < count; i++) {
        this_thread::sleep_for(chrono::milliseconds(100 * (id + 1)));

        {
            lock_guard<mutex> lock(mtx);
            int value = startValue + i;
            results.push(value);
            cout << "Producer " << id << " added: " << value << endl;
        }

        cv.notify_all();   // wake all consumers
    }

    // Producer finished
    {
        lock_guard<mutex> lock(mtx);
        activeProducers--;
        if (activeProducers == 0)
            done = true;   // last producer sets done
    }

    cv.notify_all();
}

// -------------------- Consumer --------------------
void Compute(int id) {
    unique_lock<mutex> lock(mtx);

    while (true) {
        cv.wait(lock, [] {
            return !results.empty() || done;
        });

        if (results.empty() && done) {
            cout << "Consumer " << id << " exiting.\n";
            break;
        }

        int value = results.front();
        results.pop();

        cout << "Consumer " << id << " consumed: " << value << endl;
    }
}

// ------------------------ Main ------------------------
int main() {
    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 4;

    vector<thread> producers;
    vector<thread> consumers;

    // Launch producers
    for (int i = 0; i < NUM_PRODUCERS; i++)
        producers.emplace_back(Add, (i + 1) * 10, 5, i);  
        // producer i generates 5 values starting from 10, 20, 30, ...

    // Launch consumers
    for (int i = 0; i < NUM_CONSUMERS; i++)
        consumers.emplace_back(Compute, i);

    // Wait producers
    for (auto &t : producers)
        t.join();

    // Wait consumers
    for (auto &t : consumers)
        t.join();

    return 0;
}
/*
Producer 0 added: 10
Consumer 1 consumed: 10
Producer 0 added: 11
Consumer 2 consumed: 11
Producer 1 added: 20
Consumer 3 consumed: 20
Producer 2 added: 30
Consumer 2 consumed: 30
Producer 0 added: 12
Consumer 3 consumed: 12
Producer 1 added: 21
Consumer 3 consumed: 21
Producer 0 added: 13
Consumer 0 consumed: 13
Producer 0 added: 14
Consumer 0 consumed: 14
Producer 2 added: 31
Consumer 2 consumed: 31
Producer 1 added: 22
Consumer 0 consumed: 22
Producer 1 added: 23
Consumer 1 consumed: 23
Producer 2 added: 32
Consumer 0 consumed: 32
Producer 1 added: 24
Consumer 3 consumed: 24
Producer 2 added: 33
Consumer 2 consumed: 33
Producer 2 added: 34
Consumer 3 consumed: 34
Consumer 3 exiting.
Consumer 1 exiting.
Consumer 0 exiting.
Consumer 2 exiting.
*/


✔ How It Works
✔ Multiple Producers:
Each producer generates a sequence of values
Pushes into the shared queue
Notifies all consumers
Decrements activeProducers when done
The last producer sets:
done = true;

✔ Multiple Consumers:
Wait until data is available OR done == true
Pop and process values

Stop when:
queue is empty AND done == true

✔ Thread-Safe Queue Logic:
Protected with:
mutex mtx;
condition_variable cv;


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
queue<int> results;
bool done = false;

// -------------------- Producer --------------------
void Producer(int startValue, int count, int id) {
    for (int i = 0; i < count; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));

        {
            lock_guard<mutex> lock(mtx);
            int value = startValue + i;
            results.push(value);
            cout << "Producer " << id << " added: " << value << endl;
        }

        cv.notify_one(); // notify one consumer
    }
}

// -------------------- Consumer --------------------
void Consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !results.empty() || done; });

        if (results.empty() && done) {
            cout << "Consumer " << id << " exiting.\n";
            break;
        }

        int value = results.front();
        results.pop();
        cout << "Consumer " << id << " consumed: " << value << endl;
    }
}

// -------------------- Main --------------------
int main() {
    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;

    vector<thread> producers;
    vector<thread> consumers;

    // Launch consumers first
    for (int i = 0; i < NUM_CONSUMERS; i++)
        consumers.emplace_back(Consumer, i);

    // Launch producers
    for (int i = 0; i < NUM_PRODUCERS; i++)
        producers.emplace_back(Producer, (i + 1) * 3, 2, i);

    // Wait producers
    for (auto &t : producers)
        t.join();

    // Signal consumers to finish
    {
        lock_guard<mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();

    // Wait consumers
    for (auto &t : consumers)
        t.join();

    return 0;
}
/*
Producer 1 added: 6
Consumer 0 consumed: 6
Producer 0 added: 3
Producer 2 added: 9
Consumer 1 consumed: 3
Consumer 1 consumed: 9
Producer 1 added: 7
Consumer 1 consumed: 7
Producer 0 added: 4
Consumer 0 consumed: 4
Producer 2 added: 10
Consumer 1 consumed: 10
Consumer 0 exiting.
Consumer 1 exiting.
*/

/* ---------------------------------------------------------------------------------------------------------------------- */
#include<iostream>
#include<thread>
#include<chrono>
using namespace std;
void add(int x, int y){
    cout<<x+y<<endl;
}

int main(){
  thread t(add, 2,4);
//   t.join();      //waits for main thread to finish

this_thread::sleep_for(chrono::milliseconds(100));
t.detach();    //in the background
return 0;
}


/* ---------------------------------------------------------------------------------------------------------------------- */
//Reentrant Function

1. Reentrant Function in C++
   If you are asking about a reentrant function, this refers to a function that can be safely called again ("re-entered") 
   before the previous executions are completed, without causing issues. 
   
   A reentrant function is typically thread-safe and can be interrupted and safely called again 
   (e.g., in the case of recursive calls or being executed in multiple threads).

   
   A function is reentrant if:
   It does not rely on shared state.
   It does not modify global/static variables.
   It does not perform non-atomic operations that could be interrupted.

//Example of a Reentrant Function:
#include <iostream>
// Reentrant function: no shared state, no global variables
int add(int a, int b) {
    return a + b;  // Purely functional, no side effects
}

int main() {
    std::cout << "5 + 3 = " << add(5, 3) << std::endl;  // Safe to call repeatedly
    return 0;
}

This function is reentrant because it only uses its local parameters and has no side effects.

Why is Reentrancy Important?
Multithreading: If two threads call a reentrant function simultaneously, it will not interfere with the state of the function.
Interrupt Handling: If a function is used in an interrupt context, it must be reentrant because the interrupt could occur at any time.




2. Recursive Functions

Sometimes people might refer to "reentrant" functions when they are talking about recursive functions. 
While recursion does not always imply reentrancy, recursive functions are often written in a reentrant 
manner because they only use local state and avoid shared global variables.

// Example of a recursive (and reentrant) factorial function
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    std::cout << "Factorial of 5: " << factorial(5) << std::endl;
    return 0;
}

In this case, the recursive factorial function is reentrant because each recursive call operates on its own stack frame, 
and there are no shared resources or global variables.






3. Reentrant in the Context of Interrupts (Embedded Systems)

In low-level programming, like in embedded systems or kernel programming, reentrancy often becomes critical for interrupt service routines (ISRs).
Reentrancy in ISRs means the interrupt can safely execute if it is triggered while another interrupt is already in progress.

An example might be an ISR that handles sensor data, but it does not rely on shared or static variables to ensure it can be safely 
called multiple times without corrupting data.


Key Characteristics of Reentrant Functions:
No Static or Global Variables: It does not rely on data shared by other calls.
No Modifications to Shared Resources: It avoids side effects like modifying shared memory, files, etc.
Self-contained: All data required for the function is passed via arguments or local variables.


Example of a Non-Reentrant Function (Using Global Variables):
#include <iostream>
int global = 0;
// Not reentrant: modifies global state
int nonReentrantFunction(int a) {
    global += a;  // Global state is modified
   return global;
}
int main() {
    std::cout << "Result 1: " << nonReentrantFunction(5) << std::endl; 
    std::cout << "Result 2: " << nonReentrantFunction(10) << std::endl; // Results are affected by previous call
    return 0;
}

Here, nonReentrantFunction modifies the global variable global, so calling it multiple times or from different threads can lead to issues.


/* ---------------------------------------------------------------------------------------------------------------------- */



//stack
#include<iostream>
#include<stdexcept>
using namespace std;
class MyStack{
    int *arr;
    int topIndex;
    int cap;
  public:
    MyStack():arr(nullptr), topIndex(-1), cap(0){}
    ~MyStack(){
        delete[] arr;
    }
    void push(int val){
        if(topIndex+1 == cap){
            cap = (cap==0)? 1: cap*2;
            int *newArr = new int[cap];
            for(int i=0; i<=topIndex; i++){
                newArr[i] = arr[i];
            }
            delete arr;
            arr = newArr;
        }
        arr[++topIndex] = val;
    }
    void pop(){
        if(topIndex == -1){
            throw underflow_error("Stack is empty!");
        }
        --topIndex;
    }
    int top() const{
      if(topIndex==-1){
          throw underflow_error("Stack is empty!");
      }
       return arr[topIndex]; 
    }
    bool empty() const{
        return topIndex == -1;
    }
    int size() const{
        return topIndex + 1;
    }
    int capacity() const{
        return cap;
    }
    void display(){
        for(int i=0; i<=topIndex; i++){
          cout<< arr[i]<<" ";
        }
        cout<<endl;
    }
};
int main(){
    MyStack stk;

    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    cout<<"Stack Elements: ";
    stk.display();
    
    cout<<"Size: "<<stk.size()<<endl;
    cout<<"Capacity: "<<stk.capacity()<<endl;
    if(stk.empty()){
        cout<<"Stack is empty!"<<endl;
    }
    cout<<"After pop(), top() element: ";
    stk.pop();
    cout<<stk.top()<<endl;
    cout<<"Stack Elements:";
    stk.display();
    
    cout<<"Size: "<<stk.size()<<endl;
    cout<<"Capacity: "<<stk.capacity()<<endl;
  return 0;
}
/*
Stack Elements: 10 20 30 40 
Size: 4
Capacity: 4
After pop(), top() element: 30
Stack Elements:10 20 30 
Size: 3
Capacity: 4 
*/






























































