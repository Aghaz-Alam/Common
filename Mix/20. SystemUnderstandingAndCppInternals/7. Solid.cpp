design principles, SOLID

SOLID — the five principles
S: Single Responsibility Principle (SRP)
O: Open/Closed Principle (OCP)
L: Liskov Substitution Principle (LSP)
I: Interface Segregation Principle (ISP)
D: Dependency Inversion Principle (DIP)


1) Single Responsibility Principle (SRP)
Definition: A class should have one reason to change — one responsibility.
Why: Easier to understand, test, and modify.

C++ example:
// Responsibility A: user data model
struct User {
    std::string name;
    std::string email;
};
// Responsibility B: storing users (persistence)
class UserRepository {
  public:
    void save(const User& u) {
        // write to DB / file
    }
    User load(int id) {
        // read from DB
        return {};
    }
};
// Responsibility C: presenting users (UI / formatting)
class UserPresenter {
  public:
    static std::string toJSON(const User& u) {
        return "{\"name\":\"" + u.name + "\",\"email\":\"" + u.email + "\"}";
    }
};

Tip: Don’t mix DB & formatting in the same class. If a class grows multiple responsibilities, split it.



2) Open/Closed Principle (OCP)
Definition: Software entities should be open for extension but closed for modification.
Why: Add features without changing tested code.

C++ example (polymorphism):
struct Shape {
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
struct Circle : Shape {
    double r;
    Circle(double r): r(r) {}
    double area() const override { return 3.141592653589793 * r * r; }
};
struct Rectangle : Shape {
    double w, h;
    Rectangle(double w, double h): w(w), h(h) {}
    double area() const override { return w * h; }
};
// Add new shapes by adding a new subclass; existing code using Shape doesn't change.
double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double sum = 0;
    for (auto const& s : shapes) sum += s->area();
    return sum;
}

Tip: Use extension via inheritance, strategy objects, or templates. Avoid editing core logic to add features.



3) Liskov Substitution Principle (LSP)
Definition: Objects of a superclass should be replaceable with objects of subclasses without altering correctness.
Why: Ensures derived classes behave as expected by clients of base class.
Pitfall example (violating LSP):

struct Bird {
    virtual void fly() = 0;
    virtual ~Bird() = default;
};
struct Sparrow : Bird {
    void fly() override { /* flies */ }
};
struct Ostrich : Bird {
    void fly() override { throw std::logic_error("Ostrich can't fly"); } // breaks substitution
};
Fix: Rework the hierarchy so only flying birds have fly():
struct Bird { virtual ~Bird() = default; };
struct FlyingBird : Bird { virtual void fly() = 0; };
struct Sparrow : FlyingBird { void fly() override { /* ok */ } };
struct Ostrich : Bird { /* no fly method */ };

Tip: Design interfaces according to behavior; avoid adding methods to base class that some subclasses can't meaningfully implement.



4) Interface Segregation Principle (ISP)
Definition: Clients should not be forced to depend on interfaces they don't use — prefer many specific interfaces to one fat interface.
Why: Reduces coupling and unnecessary implementations.

C++ example:
struct Printer {
    virtual void print(const std::string& s) = 0;
    virtual ~Printer() = default;
};
struct Scanner {
    virtual std::string scan() = 0;
    virtual ~Scanner() = default;
};
struct MultiFunctionDevice : Printer, Scanner {}; // compose interfaces
// A class that only needs printing can depend on Printer alone.

Tip: Use small, focused abstract classes (pure virtual) rather than one giant interface.



5) Dependency Inversion Principle (DIP)
Definition: High-level modules should not depend on low-level modules; both should depend on abstractions. Abstractions should not depend on details; details should depend on abstractions.
Why: Makes swapping implementations (e.g., real DB vs mock) trivial and improves testability.

C++ example (constructor injection + abstract interface):
struct ILogger {
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() = default;
};
class ConsoleLogger : public ILogger {
  public:
    void log(const std::string& msg) override {
        std::cout << msg << '\n';
    }
};
class Service {
    std::shared_ptr<ILogger> logger_;
  public:
    Service(std::shared_ptr<ILogger> logger) : logger_(std::move(logger)) {}
    void doWork() {
        logger_->log("doing work");
    }
};
// In production:
auto svc = Service(std::make_shared<ConsoleLogger>());
// In tests: inject a mock logger

Tip: Prefer constructor injection and program to interfaces (std::unique_ptr/shared_ptr to abstract type or references).
Short examples combining SOLID

A small dependency-injected processing pipeline:
struct IProcessor { virtual void process(int) = 0; virtual ~IProcessor() = default; };
struct Logger : IProcessor {
    void process(int x) override { std::cout << "log " << x << '\n'; }
};
struct Counter : IProcessor {
    int sum = 0;
    void process(int x) override { sum += x; }
};
void runPipeline(const std::vector<std::shared_ptr<IProcessor>>& pipeline, int value) {
    for (auto& p : pipeline) p->process(value);
}

SRP: each processor has one job.
OCP: add new processors without modifying runPipeline.
DIP: pipeline depends on IProcessor abstraction.

Practical C++ tips & idioms that support SOLID
Use interfaces (abstract classes with pure virtual functions) for behaviors.
Prefer composition over inheritance when appropriate.
Use smart pointers (unique_ptr, shared_ptr, weak_ptr) to express ownership.
Prefer constructor injection for dependencies (DIP).
Use final to prevent further derivation when you need to lock behavior.
Keep classes small and focused — one concept per class (SRP).
For extension, prefer the strategy pattern, or policy-based design (templates) when you need compile-time customization.
Use CRTP or templates when LSP and polymorphism at runtime aren’t needed but you need zero-overhead customization.
Write unit tests using mocks/stubs; DIP makes this easy.