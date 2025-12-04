/* 
ShallowCopy&DeepCopy

Question 5: Write a C++ program taking a class Student with dynamically allocated data members to store the student's name and marks. 
Define and implement the class Student with appropriate constructors and destructors to manage the memory correctly 
and to demonstrate the difference between shallow copy and deep copy operations when dealing with dynamic data in objects of the Student class.

*/



#include <iostream>
#include <cstring>
using namespace std;
class Student {
  private:
    char* name;       // dynamically allocated
    int* marks;       // dynamically allocated

  public:
    // Default constructor
    Student() {
        name = nullptr;
        marks = nullptr;
    }

    // Parameterized constructor
    Student(const char* n, int m) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        marks = new int;
        *marks = m;

        cout << "Constructor called for: " << name << endl;
    }

    // Copy Constructor (DEEP COPY)
    Student(const Student& other) {
        cout << "Deep Copy Constructor Called\n";

        // allocate new memory and copy values
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);

        marks = new int;
        *marks = *(other.marks);
    }

    // Assignment Operator (DEEP COPY)
    Student& operator=(const Student& other) {
        cout << "Deep Copy Assignment Operator Called\n";

        // Avoid self-assignment
        if (this == &other)
            return *this;

        // Delete old memory
        delete[] name;
        delete marks;

        // Allocate & copy new memory
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);

        marks = new int;
        *marks = *(other.marks);

        return *this;
    }

    // Destructor
    ~Student() {
        cout << "Destructor called for: " << (name ? name : "null") << endl;
        delete[] name;
        delete marks;
    }

    // Function to display student info
    void display() const {
        cout << "Name: " << name << ", Marks: " << *marks << endl;
    }

    // Modify marks to show independence of objects
    void updateMarks(int newMarks) {
        *marks = newMarks;
    }
};

/* ============================================================
   MAIN — DEMONSTRATION OF SHALLOW vs DEEP COPY
============================================================ */
int main() {
    cout << "=== Creating Student A ===\n";
    Student A("Ravi", 90);

    cout << "\n=== Creating Student B using Deep Copy Constructor ===\n";
    Student B = A;  // invokes deep copy

    cout << "\nInitial values:\n";
    A.display();
    B.display();

    cout << "\n=== Modifying B's marks to show deep copy ===\n";
    B.updateMarks(50);

    cout << "\nAfter modification:\n";
    cout << "Student A: ";
    A.display();
    cout << "Student B: ";
    B.display();

    cout << "\n=== Assignment Operator Demo ===\n";
    Student C;
    C = A;  // calls deep copy assignment

    cout << "\nValues in C:\n";
    C.display();

    cout << "\n=== Program Ends (Destructors will be called) ===\n";

    return 0;
}
/*
=== Creating Student A ===
Constructor called for: Ravi

=== Creating Student B using Deep Copy Constructor ===
Deep Copy Constructor Called

Initial values:
Name: Ravi, Marks: 90
Name: Ravi, Marks: 90

=== Modifying B's marks to show deep copy ===

After modification:
Student A: Name: Ravi, Marks: 90
Student B: Name: Ravi, Marks: 50

=== Assignment Operator Demo ===
Deep Copy Assignment Operator Called

Values in C:
Name: Ravi, Marks: 90

=== Program Ends (Destructors will be called) ===
Destructor called for: Ravi
Destructor called for: Ravi
Destructor called for: Ravi
*/