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
    char* name;   // dynamically allocated
    int* marks;   // dynamically allocated

public:
    // -------------------------------
    // Default Constructor
    // -------------------------------
    Student(const char* n, int m) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        marks = new int;
        *marks = m;
    }

    // -------------------------------
    // Deep Copy Constructor
    // -------------------------------
    Student(const Student& other) {
        cout << "Deep Copy Constructor Called!" << endl;

        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);

        marks = new int;
        *marks = *(other.marks);
    }

    // -------------------------------
    // Deep Copy Assignment Operator
    // -------------------------------
    Student& operator=(const Student& other) {
        cout << "Deep Copy Assignment Operator Called!" << endl;

        if (this != &other) {
            // free old memory
            delete[] name;
            delete marks;

            // allocate new memory
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);

            marks = new int;
            *marks = *(other.marks);
        }
        return *this;
    }

    // -------------------------------
    // Destructor
    // -------------------------------
    ~Student() {
        delete[] name;
        delete marks;
        cout << "Destructor called for: " << name << endl;
    }

    // -------------------------------
    // Print Function
    // -------------------------------
    void display() const {
        cout << "Name: " << name << ", Marks: " << *marks << endl;
    }

    // -------------------------------
    // Modify marks for testing
    // -------------------------------
    void setMarks(int m) {
        *marks = m;
    }
};

int main() {
    cout << "=== ORIGINAL OBJECT ===" << endl;
    Student s1("Aghaz", 90);
    s1.display();

    cout << "\n=== CREATING COPY (DEEP COPY) ===" << endl;
    Student s2 = s1;   // Calls deep copy constructor
    s2.display();

    cout << "\nModifying s2.marks to 100..." << endl;
    s2.setMarks(100);

    cout << "\n=== AFTER MODIFYING COPY ===" << endl;
    cout << "Original: ";
    s1.display();
    cout << "Copy:     ";
    s2.display();

    cout << "\n=== ASSIGNMENT OPERATOR TEST ===" << endl;
    Student s3("Temp", 50);
    s3 = s1;   // Calls deep copy assignment
    s3.display();

    return 0;
}
/* 
=== ORIGINAL OBJECT ===
Name: Aghaz, Marks: 90

=== CREATING COPY (DEEP COPY) ===
Deep Copy Constructor Called!
Name: Aghaz, Marks: 90

Modifying s2.marks to 100...

=== AFTER MODIFYING COPY ===
Original: Name: Aghaz, Marks: 90
Copy:     Name: Aghaz, Marks: 100

=== ASSIGNMENT OPERATOR TEST ===
Deep Copy Assignment Operator Called!
Name: Aghaz, Marks: 90

Destructor called for: Aghaz
Destructor called for: Aghaz
Destructor called for: Aghaz
*/