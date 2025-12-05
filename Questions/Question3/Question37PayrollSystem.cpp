/* 
37. Create a C++ program that simulates a payroll system. 
    Define a base class `Employee` and derive classes `Manager`, `Engineer`, and `Intern`, 
    each calculating salary differently using a virtual function. 
    
    Maintain a collection of employee objects in the payroll system and print their salary details, 
    also provide functionality to determine the highest-paid employee and the total payout.

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
// ============================
// Base Employee class
// ============================
class Employee {
  protected:
    string name;
    int id;

  public:
    Employee(const string& n, int i) : name(n), id(i) {}
    virtual ~Employee() {}

    // Virtual function to calculate salary
    virtual double calculateSalary() const = 0;

    // Virtual function to display employee info
    virtual void displayInfo() const {
        cout << "Employee: " << name << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }
};

// ============================
// Derived Manager
// ============================
class Manager : public Employee {
  private:
    double baseSalary;
    double bonusPercent; // e.g., 0.1 for 10%

  public:
    Manager(const string& n, int i, double b, double bonus)
        : Employee(n, i), baseSalary(b), bonusPercent(bonus) {}

    double calculateSalary() const override {
        return baseSalary + baseSalary * bonusPercent;
    }

    void displayInfo() const override {
        cout << "Employee: " << name << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }
};

// ============================
// Derived Engineer
// ============================
class Engineer : public Employee {
  private:
    double baseSalary;
    int overtimeHours;
    double overtimeRate;

  public:
    Engineer(const string& n, int i, double b, int h, double rate)
        : Employee(n, i), baseSalary(b), overtimeHours(h), overtimeRate(rate) {}

    double calculateSalary() const override {
        return baseSalary + overtimeHours * overtimeRate;
    }

    void displayInfo() const override {
        cout << "Employee: " << name << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }
};

// ============================
// Derived Intern
// ============================
class Intern : public Employee {
  private:
    double stipend;

  public:
    Intern(const string& n, int i, double s)
        : Employee(n, i), stipend(s) {}

    double calculateSalary() const override {
        return stipend;
    }

    void displayInfo() const override {
        cout << "Employee: " << name << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }
};

// ============================
// PayrollSystem class
// ============================
class PayrollSystem {
  private:
    vector<Employee*> employees;

  public:
    ~PayrollSystem() {
        // Clean up dynamically allocated employees
        for (auto emp : employees)
            delete emp;
    }

    void addEmployee(Employee* emp) {
        employees.push_back(emp);
    }

    void printPayroll() const {
        for (const auto& emp : employees)
            emp->displayInfo();
    }

    double totalSalary() const {
        double total = 0;
        for (const auto& emp : employees)
            total += emp->calculateSalary();
        return total;
    }

    Employee* findHighestPaid() const {
        if (employees.empty()) return nullptr;

        Employee* highest = employees[0];
        for (auto emp : employees) {
            if (emp->calculateSalary() > highest->calculateSalary())
                highest = emp;
        }
        return highest;
    }
};

// ============================
// MAIN
// ============================
int main() {
    PayrollSystem payroll;

    Employee* m = new Manager("Alice", 1001, 80000, 0.10);
    Employee* e = new Engineer("Bob", 1002, 60000, 10, 50);
    Employee* i = new Intern("Charlie", 1003, 1500);

    payroll.addEmployee(m);
    payroll.addEmployee(e);
    payroll.addEmployee(i);

    payroll.printPayroll();

    cout << "\nTotal Salary: " << payroll.totalSalary() << endl;

    Employee* highest = payroll.findHighestPaid();
    if (highest) {
        cout << "\nHighest Paid Employee:" << endl;
        highest->displayInfo();
    }

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