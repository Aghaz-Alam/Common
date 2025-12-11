SOLID Principles in C++ (Explained with Examples)
SOLID is a set of five object-oriented design principles that help you write clean, maintainable, flexible code.

SOLID stands for:
S — Single Responsibility Principle (SRP)
O — Open/Closed Principle (OCP)
L — Liskov Substitution Principle (LSP)
I — Interface Segregation Principle (ISP)
D — Dependency Inversion Principle (DIP)



1️⃣ Single Responsibility Principle (SRP)
A class should have ONE and ONLY ONE reason to change.
❌ Bad: One class does too many things
class Report {
public:
    string generate() { return "data"; }
    void saveToFile(const string& data) {
        // file handling
    }
};

This class:
-->Generates data
-->Saves data to file
   = Two responsibilities → SRP violated

✔ Good: Split responsibilities
class ReportGenerator {
  public:
    string generate() { return "data"; }
};
class FileSaver {
  public:
    void save(const string& data) {
        // save to file
    }
};

2️⃣ Open/Closed Principle (OCP)
Software should be open for extension, but closed for modification.
This means:
You should add new behavior without editing existing code

❌ Bad: Modify code every time new type is added
class AreaCalculator {
public:
    double area(int shapeType) {
        if (shapeType == 1) return 10;
        if (shapeType == 2) return 20;
        return 0;
    }
};
If new shape → modify function → OCP violated.

✔ Good: Use polymorphism
class Shape {
  public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
  public:
    double area() const override { return 3.14 * 5 * 5; }
};
class Square : public Shape {
  public:
    double area() const override { return 10 * 10; }
};
Now adding a new shape does not modify existing code.

3️⃣ Liskov Substitution Principle (LSP)
Derived classes must be substitutable for their base classes without breaking behavior.
If B is derived from A, you should be able to replace A with B, and nothing breaks.

❌ Bad: Violates expected behavior
class Bird {
  public:
    virtual void fly() {}
};
class Ostrich : public Bird {
  public:
    void fly() override {
        throw runtime_error("Cannot fly!");
    }
};
Clients expect all birds to fly → Ostrich breaks LSP.

✔ Good: Separate interfaces
class FlyingBird {
  public:
    virtual void fly() = 0;
};
class Sparrow : public FlyingBird {
  public:
    void fly() override {}
};
class Ostrich {
    // no flying interface implemented
};

4️⃣ Interface Segregation Principle (ISP)
Clients should not be forced to depend on methods they do not use.
❌ Bad: Big interface with unrelated functions
class Worker {
  public:
    virtual void work() = 0;
    virtual void eat() = 0; // Robots don't eat!
};
Robots must implement eat() unnecessarily.

✔ Good: Split interfaces
class Workable {
  public:
    virtual void work() = 0;
};
class Eatable {
  public:
    virtual void eat() = 0;
};


5️⃣ Dependency Inversion Principle (DIP)
**High-level modules should not depend on low-level modules.
Both should depend on abstractions.**

❌ Bad: High-level depends on low-level class
class MySQLDatabase {
  public:
    void connect() {}
};
class UserService {
    MySQLDatabase db;   // tightly coupled → bad
  public:
    void login() { db.connect(); }
};
Change DB → must modify UserService.

✔ Good: Depend on abstraction (interface)
class IDatabase {
  public:
    virtual void connect() = 0;
    virtual ~IDatabase() = default;
};
class MySQLDatabase : public IDatabase {
  public:
    void connect() override {}
};
class UserService {
    IDatabase& db;   // dependency injected
  public:
    UserService(IDatabase& database) : db(database) {}
    void login() { db.connect(); }
};

Now you can plug in:
MySQLDatabase
PostgresDB
MockDatabase (for unit testing)
