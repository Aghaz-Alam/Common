/* 
37. Create a C++ program that simulates a payroll system. Define a base class `Employee` and derive classes `Manager`, `Engineer`, and `Intern`, each calculating salary differently using a virtual function. Maintain a collection of employee objects in the payroll system and print their salary details, also provide functionality to determine the highest-paid employee and the total payout.

Requirements:

Create a base class Employee that represents any employee in an organization.

The Employee class should:
-Contain member variables for employee name and employee ID.
- Provide a virtual function that should be used to calculate salary.
- Provide a virtual function that should be used to print employee details.

Implement three specialized employee types:

Manager

- Should hold base salary and bonus percentage.
- Salary should be calculated based on base salary plus additional bonus amount.
- Display function should print role, employee information, and computed salary.

Engineer

- Should hold base salary, number of overtime hours worked, and overtime rate.
- Salary should be calculated considering base salary plus overtime earnings.
- Display function should print required employee information and computed salary details.

Intern

- Should hold a fixed stipend value.
- Salary should simply return this stipend value.
- Display function should show role, employee details, and stipend.

Additionally, design a PayrollSystem that:

- Maintains a collection of employees.
- Allows adding employees into this collection.
- Can display salary information for all employees by calling their respective display functionality.
- Can compute the total payout by accumulating salaries.
- Can find the highest-paid employee by comparing salaries.

Sample Code:

PayrollSystem payroll;

Employee* m = new Manager("Alice", 1001, 80000, 0.10);
Employee* e = new Engineer("Bob", 1002, 60000, 10, 50);
Employee* i = new Intern("Charlie", 1003, 1500);

// Add to payroll
payroll.addEmployee(m);
payroll.addEmployee(e);
payroll.addEmployee(i);

// Display
payroll.printPayroll();

std::cout << "Total Salary: " << payroll.totalSalary() << std::endl;

Employee* highest = payroll.findHighestPaid();
std::cout << "Highest Paid Employee:" << std::endl;
highest->displayInfo();

Output expected:

Employee: Alice, ID: 1001, Salary: 88000
Employee: Bob, ID: 1002, Salary: 60500
Employee: Charlie, ID: 1003, Salary: 1500

Total Salary: 150000

Highest Paid Employee:
Employee: Alice, ID: 1001, Salary: 88000

*/



#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================================================================
// Base Class: Employee
// ============================================================================
class Employee {
protected:
    string name;
    int id;

public:
    Employee(string n, int i) : name(n), id(i) {}
    virtual ~Employee() {}

    // Pure virtual functions
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const = 0;
};

// ============================================================================
// Derived Class: Manager
// ============================================================================
class Manager : public Employee {
private:
    double baseSalary;
    double bonusPercent;

public:
    Manager(string n, int i, double base, double bonus)
        : Employee(n, i), baseSalary(base), bonusPercent(bonus) {}

    double calculateSalary() const override {
        return baseSalary + (baseSalary * bonusPercent);
    }

    void displayInfo() const override {
        cout << "Employee: " << name
             << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }
};

// ============================================================================
// Derived Class: Engineer
// ============================================================================
class Engineer : public Employee {
private:
    double baseSalary;
    int overtimeHours;
    double overtimeRate;

public:
    Engineer(string n, int i, double base, int hours, double rate)
        : Employee(n, i), baseSalary(base), overtimeHours(hours), overtimeRate(rate) {}

    double calculateSalary() const override {
        return baseSalary + (overtimeHours * overtimeRate);
    }

    void displayInfo() const override {
        cout << "Employee: " << name
             << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }
};

// ============================================================================
// Derived Class: Intern
// ============================================================================
class Intern : public Employee {
private:
    double stipend;

public:
    Intern(string n, int i, double st)
        : Employee(n, i), stipend(st) {}

    double calculateSalary() const override {
        return stipend;
    }

    void displayInfo() const override {
        cout << "Employee: " << name
             << ", ID: " << id
             << ", Salary: " << stipend << endl;
    }
};

// ============================================================================
// PayrollSystem Class
// ============================================================================
class PayrollSystem {
private:
    vector<Employee*> employees;

public:
    void addEmployee(Employee* emp) {
        employees.push_back(emp);
    }

    void printPayroll() const {
        for (const auto& emp : employees) {
            emp->displayInfo();
        }
    }

    double totalSalary() const {
        double total = 0;
        for (const auto& emp : employees) {
            total += emp->calculateSalary();
        }
        return total;
    }

    Employee* findHighestPaid() const {
        if (employees.empty()) return nullptr;

        Employee* highest = employees[0];
        for (const auto& emp : employees) {
            if (emp->calculateSalary() > highest->calculateSalary()) {
                highest = emp;
            }
        }
        return highest;
    }

    ~PayrollSystem() {
        for (auto emp : employees) {
            delete emp;
        }
    }
};

// ============================================================================
// Main Function
// ============================================================================
int main() {
    PayrollSystem payroll;

    Employee* m = new Manager("Alice", 1001, 80000, 0.10);
    Employee* e = new Engineer("Bob", 1002, 60000, 10, 50);
    Employee* i = new Intern("Charlie", 1003, 1500);

    // Add employees
    payroll.addEmployee(m);
    payroll.addEmployee(e);
    payroll.addEmployee(i);

    // Display payroll
    payroll.printPayroll();

    cout << "\nTotal Salary: " << payroll.totalSalary() << endl << endl;

    // Highest Paid Employee
    Employee* highest = payroll.findHighestPaid();
    cout << "Highest Paid Employee:\n";
    highest->displayInfo();

    return 0;
}
/* 
Employee: Alice, ID: 1001, Salary: 88000
Employee: Bob, ID: 1002, Salary: 60500
Employee: Charlie, ID: 1003, Salary: 1500

Total Salary: 150000

Highest Paid Employee:
Employee: Alice, ID: 1001, Salary: 88000
*/