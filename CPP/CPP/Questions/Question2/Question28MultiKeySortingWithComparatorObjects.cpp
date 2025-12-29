/* 
28. Multi-key Sorting with Comparator Objects (STL, functors)

Problem: Given a struct Employee { id, name, dept, salary }, sort a vector of Employee by dept ascending, then by salary descending, 
then by name ascending.

Requirements / Features:
Implement custom comparator as a functor object and as a lambda.
Demonstrate stable sort where relevant.

Sample Input: 5 employees; Sample Output: sorted listing.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Employee {
    int id;
    std::string name;
    std::string dept;
    double salary;
};

// ------------------------------------------------------
// Functor Comparator (dept ↑ , salary ↓ , name ↑)
// ------------------------------------------------------
struct EmployeeComparator {
    bool operator()(const Employee& a, const Employee& b) const {
        if (a.dept != b.dept)
            return a.dept < b.dept;              // dept ascending

        if (a.salary != b.salary)
            return a.salary > b.salary;          // salary descending

        return a.name < b.name;                  // name ascending
    }
};

// Utility print function
void printEmployees(const std::vector<Employee>& v) {
    for (const auto& e : v) {
        std::cout << e.id << "  "
                  << e.name << "  "
                  << e.dept << "  "
                  << e.salary << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::vector<Employee> employees = {
        {101, "Alice",   "HR",    50000},
        {102, "Bob",     "IT",    75000},
        {103, "Charlie", "HR",    60000},
        {104, "David",   "IT",    75000},
        {105, "Eve",     "IT",    50000}
    };

    std::cout << "Original List:\n";
    printEmployees(employees);

    // ------------------------------------------------------
    // Approach 1: Functor-based sorting
    // ------------------------------------------------------
    std::stable_sort(employees.begin(), employees.end(), EmployeeComparator());

    std::cout << "Sorted using Functor Comparator:\n";
    printEmployees(employees);

    // ------------------------------------------------------
    // Approach 2: Lambda-based sorting
    // ------------------------------------------------------
    std::stable_sort(employees.begin(), employees.end(),
        [](const Employee& a, const Employee& b) {
            if (a.dept != b.dept)
                return a.dept < b.dept;

            if (a.salary != b.salary)
                return a.salary > b.salary;

            return a.name < b.name;
        }
    );

    std::cout << "Sorted using Lambda Comparator:\n";
    printEmployees(employees);

    return 0;
}
/* 
Original List:
101  Alice   HR  50000
102  Bob     IT  75000
103  Charlie HR  60000
104  David   IT  75000
105  Eve     IT  50000

Sorted using Functor Comparator:
103  Charlie HR  60000
101  Alice   HR  50000
102  Bob     IT  75000
104  David   IT  75000
105  Eve     IT  50000

Sorted using Lambda Comparator:
103  Charlie HR  60000
101  Alice   HR  50000
102  Bob     IT  75000
104  David   IT  75000
105  Eve     IT  50000
*/