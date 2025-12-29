/* 
30. Student Records System with Deep Copy & Move Semantics

Problem statement:
Create a Student class that maintains dynamic resources (heap-allocated C-style char* for name, and a dynamic array int* marks of length nMarks). Implement correct Rule of Five semantics: copy constructor, move constructor, copy assignment, move assignment, destructor. Provide clone() to return a deep copy. Also implement a StudentDB class that stores students (by value) and demonstrates copying and moving behavior.

Requirements / Features:

Student fields: int id, char* name (null-terminated), int* marks, size_t nMarks.

Constructors:
Student(int id, const char* name, const std::vector<int>& marks);
Implement destructor freeing memory.
Implement copy constructor/assignment performing deep copies.
Implement move constructor/assignment transferring ownership and leaving source in valid empty state.
Provide print() which prints id, name, marks, average.
StudentDB holds std::vector<Student> and supports addStudent(Student), getStudentById(int), showing copying vs moving behavior (e.g., using emplace_back vs push_back with copy).
Throw std::runtime_error if getStudentById not found.

Sample Input (usage)
Student s1(1, "Alice", {90, 80, 85});
Student s2 = s1;               // copy
Student s3 = std::move(s1);    // move

StudentDB db;
db.addStudent(s2);             // copy into db
db.addStudent(std::move(s3));  // move into db

db.getStudentById(2).print();  // should throw (no id 2)
db.getStudentById(1).print();

Expected Output
terminate called after throwing an instance of 'std::runtime_error'
  what(): Student with id 2 not found
# (Program aborts here due to exception; but if caught:)
Student ID: 1
Name: Alice
Marks: 90 80 85
Average: 85
*/



#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
using namespace std;

// ========================================================
//                       Student
// ========================================================
class Student {
private:
    int id;
    char* name;
    int* marks;
    size_t nMarks;

public:

    // -------- Constructor --------
    Student(int id, const char* name, const vector<int>& marksVec)
        : id(id), name(nullptr), marks(nullptr), nMarks(marksVec.size())
    {
        // allocate name
        size_t len = strlen(name);
        this->name = new char[len + 1];
        strcpy(this->name, name);

        // allocate marks
        marks = new int[nMarks];
        for (size_t i = 0; i < nMarks; i++)
            marks[i] = marksVec[i];
    }

    // -------- Destructor --------
    ~Student() {
        delete[] name;
        delete[] marks;
    }

    // -------- Copy Constructor --------
    Student(const Student& other)
        : id(other.id), nMarks(other.nMarks)
    {
        // deep copy name
        size_t len = strlen(other.name);
        name = new char[len + 1];
        strcpy(name, other.name);

        // deep copy marks
        marks = new int[nMarks];
        for (size_t i = 0; i < nMarks; i++)
            marks[i] = other.marks[i];
    }

    // -------- Move Constructor --------
    Student(Student&& other) noexcept
        : id(other.id), name(other.name), marks(other.marks), nMarks(other.nMarks)
    {
        // leave other in a valid empty state
        other.name = nullptr;
        other.marks = nullptr;
        other.nMarks = 0;
    }

    // -------- Copy Assignment --------
    Student& operator=(const Student& other) {
        if (this == &other) return *this;

        // cleanup old memory
        delete[] name;
        delete[] marks;

        id = other.id;
        nMarks = other.nMarks;

        // deep copy
        size_t len = strlen(other.name);
        name = new char[len + 1];
        strcpy(name, other.name);

        marks = new int[nMarks];
        for (size_t i = 0; i < nMarks; i++)
            marks[i] = other.marks[i];

        return *this;
    }

    // -------- Move Assignment --------
    Student& operator=(Student&& other) noexcept {
        if (this == &other) return *this;

        // cleanup old memory
        delete[] name;
        delete[] marks;

        id = other.id;
        name = other.name;
        marks = other.marks;
        nMarks = other.nMarks;

        other.name = nullptr;
        other.marks = nullptr;
        other.nMarks = 0;

        return *this;
    }

    // -------- clone() → deep copy --------
    Student clone() const {
        return Student(*this);  // uses copy constructor
    }

    // -------- Getters --------
    int getId() const { return id; }

    // -------- Print --------
    void print() const {
        cout << "Student ID: " << id << endl;
        cout << "Name: " << (name ? name : "(null)") << endl;
        cout << "Marks: ";
        for (size_t i = 0; i < nMarks; i++)
            cout << marks[i] << " ";
        cout << endl;

        // compute average
        int sum = 0;
        for (size_t i = 0; i < nMarks; i++) sum += marks[i];
        double avg = nMarks > 0 ? (double)sum / nMarks : 0.0;

        cout << "Average: " << avg << endl;
    }
};

// ========================================================
//                       StudentDB
// ========================================================
class StudentDB {
private:
    vector<Student> db;

public:
    // copy or move depending on argument
    void addStudent(const Student& s) {
        db.push_back(s); // COPY
    }

    void addStudent(Student&& s) {
        db.push_back(std::move(s)); // MOVE
    }

    Student& getStudentById(int id) {
        for (auto& s : db)
            if (s.getId() == id)
                return s;
        throw runtime_error("Student with id " + to_string(id) + " not found");
    }
};

// ========================================================
//                            MAIN
// ========================================================
int main() {
    Student s1(1, "Alice", {90, 80, 85});
    Student s2 = s1;               // copy
    Student s3 = std::move(s1);    // move

    StudentDB db;
    db.addStudent(s2);             // copy into db
    db.addStudent(std::move(s3));  // move into db

    // This line will throw:
    // db.getStudentById(2).print();

    // Uncomment to see the expected program abort:
    // db.getStudentById(2).print();

    // Normal correct lookup:
    db.getStudentById(1).print();

    return 0;
}
/* 
Sample Expected Output
If line db.getStudentById(2).print(); is executed, it throws as required:
terminate called after throwing an instance of 'std::runtime_error'
  what(): Student with id 2 not found


If caught and then printing id 1:
Student ID: 1
Name: Alice
Marks: 90 80 85
Average: 85
*/