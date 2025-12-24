Structures & operations


In C++, structures (often abbreviated as struct) are user-defined data types that group together variables of different data types
under a single name. 

They allow you to create complex data models that represent real-world entities with multiple properties.


1. Basic Structure Declaration and Initialization
A struct is defined using the struct keyword. Each member of the structure can be of any data type (including other structures, arrays, etc.).

Example of Structure Declaration and Initialization:
#include <iostream>
using namespace std;
struct Point {
    int x;
    int y;
};
int main() {
    // Initializing a structure instance
    Point p1 = {10, 20};  // Using an initializer list

    cout << "Point p1: (" << p1.x << ", " << p1.y << ")" << endl;
   return 0;
}
/* 
Output:
Point p1: (10, 20)

Here, Point is a structure with two integer members x and y.
p1 is an instance of the structure Point with x initialized to 10 and y initialized to 20.
*/




2. Accessing Structure Members
Structure members can be accessed using the dot (.) operator.
Example of Accessing Members:
#include <iostream>
using namespace std;
struct Rectangle {
    int length;
    int width;
};
int main() {
    Rectangle r1 = {5, 3};  // Length = 5, Width = 3

    cout << "Length: " << r1.length << endl;  // Accessing member 'length'
    cout << "Width: " << r1.width << endl;    // Accessing member 'width'
    
   return 0;
}
/* 
Output:

Length: 5
Width: 3
*/



3. Structure with Member Functions
Just like classes, structures in C++ can also have functions (called member functions). 
The main difference between classes and structures is that members of a structure are public by default, 
while members of a class are private by default.

Example of Structure with Member Functions:
#include <iostream>
using namespace std;
struct Circle {
    double radius;

    // Member function to calculate the area of the circle
    double area() const {
        return 3.14159 * radius * radius;
    }
};
int main() {
    Circle c1;
    c1.radius = 5.0;

    cout << "Area of the circle: " << c1.area() << endl;
  return 0;
}
/* 
Output:
Area of the circle: 78.5398

The structure Circle has a member function area() that computes the area of the circle.
const after the function declaration ensures that this function does not modify the state of the structure (radius).
*/



4. Passing Structures to Functions
Structures can be passed to functions by value, by reference, or by constant reference.
Pass by Value: A copy of the structure is passed.
Pass by Reference: The function can modify the original structure.
Pass by Const Reference: The function cannot modify the structure, but avoids copying.

Example of Passing Structures:
#include <iostream>
using namespace std;
struct Point {
    int x;
    int y;
};
// Pass by value (creates a copy)
void printPointByValue(Point p) {
    cout << "Inside printPointByValue: (" << p.x << ", " << p.y << ")" << endl;
}
// Pass by reference (can modify the original)
void movePointByReference(Point& p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
}
// Pass by const reference (cannot modify the original)
void printPointByConstReference(const Point& p) {
    cout << "Inside printPointByConstReference: (" << p.x << ", " << p.y << ")" << endl;
}
int main() {
    Point p1 = {10, 20};
    
    printPointByValue(p1);  // Pass by value, doesn't modify p1
    printPointByConstReference(p1);  // Pass by const reference, doesn't modify p1
    
    movePointByReference(p1, 5, -10);  // Pass by reference, modifies p1
    cout << "After move: (" << p1.x << ", " << p1.y << ")" << endl;
    
  return 0;
}
/* 
Output:

Inside printPointByValue: (10, 20)
Inside printPointByConstReference: (10, 20)
After move: (15, 10)
*/



5. Array of Structures
You can create arrays of structures, which is useful for managing multiple instances of a similar data structure.
Example of Array of Structures:
#include <iostream>
using namespace std;
struct Student {
    string name;
    int age;
};
int main() {
    Student students[3] = {
        {"Alice", 20},
        {"Bob", 22},
        {"Charlie", 19}
    };

    for (int i = 0; i < 3; i++) {
        cout << students[i].name << " is " << students[i].age << " years old." << endl;
    }

  return 0;
}
/* 
Output:

Alice is 20 years old.
Bob is 22 years old.
Charlie is 19 years old.
*/



6. Dynamic Memory Allocation for Structures
Structures can also be dynamically allocated using new and deallocated with delete.
Example of Dynamic Memory Allocation for a Structure:
#include <iostream>
using namespace std;
struct Student {
    string name;
    int age;
};
int main() {
    // Dynamically allocate memory for a Student
    Student* pStudent = new Student;
    
    // Initialize the Student instance
    pStudent->name = "David";
    pStudent->age = 21;

    // Access the structure's members
    cout << pStudent->name << " is " << pStudent->age << " years old." << endl;

    // Free the dynamically allocated memory
    delete pStudent;
    
   return 0;
}
/* 
Output:

David is 21 years old.
*/


7. Structure with Nested Structures
Structures can also contain other structures as members. This is helpful when modeling more complex real-world objects.
Example of Nested Structures:
#include <iostream>
using namespace std;
struct Date {
    int day;
    int month;
    int year;
};
struct Person {
    string name;
    Date birthdate;  // Nested structure
};
int main() {
    Person p1 = {"John", {15, 7, 1990}};  // Initialize nested structure directly

    cout << "Name: " << p1.name << endl;
    cout << "Birthdate: " << p1.birthdate.day << "/"
         << p1.birthdate.month << "/" << p1.birthdate.year << endl;

  return 0;
}
/* 
Output:

Name: John
Birthdate: 15/7/1990
*/



8. Operations on Structures
You can define custom operators for structures, such as ==, =, or other arithmetic operators, to make them more usable.
Example of Overloading the == Operator:
#include <iostream>
using namespace std;
struct Point {
    int x;
    int y;

    // Overloading the '==' operator to compare two points
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
};
int main() {
    Point p1 = {10, 20};
    Point p2 = {10, 20};
    Point p3 = {30, 40};

    cout << "p1 == p2: " << (p1 == p2 ? "True" : "False") << endl;
    cout << "p1 == p3: " << (p1 == p3 ? "True" : "False") << endl;

   return 0;
}
/* 
Output:

p1 == p2: True
p1 == p3: False

Conclusion
Structures in C++ provide a way to represent complex data types by grouping different data elements under one roof. 
They allow you to create well-defined data models for real-world entities. 
Understanding how to use structures, along with various operations like passing by reference, overloading operators, a
nd using dynamic memory, will greatly improve your ability to manage and manipulate data in C++. 
*/