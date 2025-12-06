Advanced Structure Concepts in C++
1. Structure with Constructor & Destructor
Unlike C in C++, C++ allows structures to have constructors and destructors just like classes. This allows initialization and cleanup.


#include <iostream>
using namespace std;
struct Point {
    int x, y;

    // Constructor
    Point(int a, int b) : x(a), y(b) {
        cout << "Point constructed: (" << x << ", " << y << ")" << endl;
    }

    // Destructor
    ~Point() {
        cout << "Point destructed: (" << x << ", " << y << ")" << endl;
    }
};
int main() {
    Point p1(5, 10); // Constructor is called
  return 0;         // Destructor is called automatically
}
/* 
Output:
Point constructed: (5, 10)
Point destructed: (5, 10)

Advantage: Allows RAII (Resource Acquisition Is Initialization) style management.
*/


2. Structure with const Members
You can define constant members in a structure. They must be initialized using constructor initializer lists.

#include <iostream>
using namespace std;
struct Circle {
    const double PI;
    double radius;

    Circle(double r) : PI(3.14159), radius(r) {}

    double area() const {
        return PI * radius * radius;
    }
};
int main() {
    Circle c1(5.0);
    cout << "Area: " << c1.area() << endl;
   return 0;
}
/* 
Output:
Area: 78.5398

const members cannot be modified after initialization.
*/


3. Structure Inheritance
Structures in C++ can inherit from other structures or classes. Members are public by default.

#include <iostream>
using namespace std;
struct Shape {
    int x, y;
};
struct Circle : Shape {
    double radius;
    double area() const {
        return 3.14159 * radius * radius;
    }
};
int main() {
    Circle c;
    c.x = 0; c.y = 0; c.radius = 5.0;
    cout << "Circle at (" << c.x << ", " << c.y << ") has area " << c.area() << endl;
  return 0;
}
/* 
Output:
Circle at (0, 0) has area 78.5398

Structures support single & multiple inheritance, just like classes.
*/


4. Bit-Fields in Structures
Bit-fields allow you to pack data tightly, often useful in embedded systems.

#include <iostream>
using namespace std;
struct PackedData {
    unsigned int a : 3;  // 3 bits
    unsigned int b : 5;  // 5 bits
};

int main() {
    PackedData pd;
    pd.a = 5;  // max 7 (3 bits)
    pd.b = 17; // max 31 (5 bits)
    
    cout << "a: " << pd.a << ", b: " << pd.b << endl;
  return 0;
}
/* 
Output:
a: 5, b: 17

Bit-fields are useful for memory-efficient storage.
*/


5. Anonymous Structures
You can define structures without a name and use them immediately.

#include <iostream>
using namespace std;

struct {
    int x, y;
} point;

int main() {
    point.x = 10;
    point.y = 20;
    cout << "Point: (" << point.x << ", " << point.y << ")" << endl;
  return 0;
}
/* 
Output:
Point: (10, 20)
*/


6. Structure with static Members
Static members are shared among all instances of a structure.

#include <iostream>
using namespace std;
struct Counter {
    static int count;
    Counter() { count++; }
};

int Counter::count = 0;

int main() {
    Counter c1, c2, c3;
    cout << "Total objects created: " << Counter::count << endl;
  return 0;
}
/* 
Output:
Total objects created: 3
*/


7. Structure Templates
You can define generic structures with templates.

#include <iostream>
using namespace std;
template <typename T>
struct Pair {
    T first, second;
    Pair(T a, T b) : first(a), second(b) {}
    void print() const { cout << "(" << first << ", " << second << ")" << endl; }
};

int main() {
    Pair<int> p1(1, 2);
    Pair<string> p2("Hello", "World");

    p1.print();
    p2.print();
   return 0;
}
/* 
Output:
(1, 2)
(Hello, World)
*/



8. Operator Overloading (Advanced)
Structures can have arithmetic and assignment operators overloaded for custom behavior.

#include <iostream>
using namespace std;
struct Vector2D {
    int x, y;

    Vector2D operator+(const Vector2D& v) const {
        return {x + v.x, y + v.y};
    }

    void print() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};
int main() {
    Vector2D v1{1, 2}, v2{3, 4};
    Vector2D v3 = v1 + v2;
    v3.print();
   return 0;
}
/* 
Output:
(4, 6)
*/



9. Alignment and Padding
Structures may have padding bytes for alignment. You can control alignment using #pragma pack or alignas.

#include <iostream>
using namespace std;
#pragma pack(push, 1)
struct Packed {
    char a;
    int b;
};
#pragma pack(pop)
int main() {
    cout << "Size of Packed structure: " << sizeof(Packed) << endl;
  return 0;
}
/* 
Output (may vary):
Size of Packed structure: 5
Without #pragma pack(1), the size would typically be 8 due to padding.
*/



10. Structures and decltype, auto
You can use decltype and auto with structures for type inference.

#include <iostream>
using namespace std;

struct Point { int x, y; };

int main() {
    Point p1{10, 20};
    decltype(p1) p2 = {30, 40};  // Same type as p1
    auto p3 = p1;                 // p3 is of type Point

    cout << p2.x << ", " << p2.y << endl;
    cout << p3.x << ", " << p3.y << endl;
  return 0;
}
/* 
Output:
30, 40
10, 20
*/

✅ Conclusion
Advanced structure concepts in C++ allow you to:
Initialize members through constructors.
Use const, static, and template members.
Inherit from other structures/classes.
Overload operators.
Manage memory efficiently with bit-fields and dynamic allocation.
Handle alignment and type inference.
This gives you class-like flexibility with the simplicity and default public access of structures.