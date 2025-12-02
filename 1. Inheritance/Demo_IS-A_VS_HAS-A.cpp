Can we achieve polymorphism using HAS-A relationships (composition or aggregation)?
Ans: Polymorphism and HAS-A relationships
--> Polymorphism in C++ generally works with IS-A (inheritance) relationships:
    Vehicle* v = new Car();  // IS-A
    v->start();              // Calls Car::start() → runtime polymorphism

--> Polymorphism requires virtual functions in a base class.
--> A derived class overrides them, and you call them through a base class pointer or reference.


Yes, we can achieve polymorphism using HAS-A relationships (compostion or aggregation) but in an indirect way.
Key idea: we can store a base class pointer/reference inside our class (HAS-A) and call virtual functions on it.

| Relationship            | Polymorphism?                  | Ownership                                          | Example                       |
| ----------------------- | ------------------------------ | -------------------------------------------------- | ----------------------------- |
| **IS-A**                | Direct                         | Derived owns base part                             | Car IS-A Vehicle              |
| **HAS-A (Composition)** | Indirect via member            | Strong → contained object destroyed with container | Car HAS-A Engine (unique_ptr) |
| **HAS-A (Aggregation)** | Indirect via pointer/reference | Weak → contained object independent                | Car HAS-A Engine* (pointer)   |


1️⃣ IS-A Polymorphism (Inheritance)
Concept:
--> A derived class is a type of base class.
--> Allows runtime polymorphism using virtual functions.
--> Example: Car IS-A Vehicle.

Code Example:
#include <iostream>
#include <string>
using namespace std;
// Base Class: Vehicle (IS-A relationship)
class Vehicle {
  public:
    Vehicle() noexcept = default;
    virtual ~Vehicle() noexcept = default;  // Virtual destructor for safe polymorphism

    // Virtual functions for polymorphism
    virtual void start() const noexcept {
        cout << "Vehicle: Engine started\n";
    }

    virtual void stop() noexcept {
        cout << "Vehicle: Vehicle stopped\n";
    }

    // Prevent copying
    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;
};
// Derived Class: Car (IS-A Vehicle)
class Car final : public Vehicle {
  public:
    Car() noexcept = default;
    ~Car() noexcept override = default;

    // Override base class function
    void start() const noexcept override {
        cout << "Car: Engine started using push-button\n";
    }

    // Car-specific function
    void honk() const noexcept {
        cout << "Car horn: Beep! Beep!\n";
    }
};
// Utility function demonstrating polymorphism
void testDrive(const Vehicle& vehicle) noexcept {
    vehicle.start();  // Calls derived version if passed a derived object
}
// Main function
int main() {
    Car myCar;

    myCar.start();      // Calls Car::start()
    myCar.honk();       // Car-specific
    testDrive(myCar);   // Polymorphism via base class reference

   return 0;
}
/* Output:
Car: Engine started using push-button
Car horn: Beep! Beep!
Car: Engine started using push-button
*/

Key Points:
--> Car IS-A Vehicle
--> Virtual function start() → overridden in derived class
--> Base class reference (Vehicle&) can call derived class method

2️⃣ HAS-A Polymorphism via Composition (Strong Ownership)
Concept:
--> Car HAS-A Engine → Car owns the Engine
--> Polymorphism works if Engine is polymorphic
--> Lifetime of Engine is tied to Car

Code Example:
#include <iostream>
#include <memory>
using namespace std;
// Engine Base Class (Polymorphic for HAS-A)
class Engine {
  public:
    Engine() noexcept = default;
    virtual ~Engine() noexcept = default;

    // Virtual function → allows polymorphism
    virtual void start() const noexcept {
        cout << "Generic Engine started\n";
    }

    // Prevent copying
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};

// Derived Engine: ElectricEngine
class ElectricEngine final : public Engine {
  public:
    ElectricEngine() noexcept = default;
    ~ElectricEngine() noexcept override = default;

    void start() const noexcept override {
        cout << "Electric Engine started\n";
    }
};
// Car Class (HAS-A Engine via composition)
class Car final {
  private:
    unique_ptr<Engine> engine;  // Composition → Car owns Engine

  public:
    explicit Car(unique_ptr<Engine> eng) noexcept: engine(move(eng)) {}

    ~Car() noexcept = default; // unique_ptr automatically cleans up Engine

    // Prevent copying (unique_ptr cannot be copied)
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    // Allow moving
    Car(Car&&) noexcept = default;
    Car& operator=(Car&&) noexcept = default;

    // Car behavior
    void drive() const noexcept {
        engine->start(); // Polymorphic call
        cout << "Car is driving\n";
    }
};

// Main Function
int main() {
    auto engine = make_unique<ElectricEngine>();  // Create polymorphic engine
    Car myCar(move(engine));                        // Composition → Car owns Engine

    myCar.drive();  // Calls ElectricEngine::start() via polymorphism

    return 0;
}
/* Output:
Electric Engine started
Car is driving
*/


Key Points:
--> Car HAS-A Engine
--> Engine is polymorphic (start() virtual) → different engine types possible
--> Strong ownership → Engine destroyed when Car destroyed



3️⃣ HAS-A Polymorphism via Aggregation (Weak Ownership)
Concept:
--> Car uses Engine → Engine can exist independently
--> Polymorphism works via pointer/reference
--> Lifetime of Engine not tied to Car

Code Example:
#include <iostream>
using namespace std;
// Engine Base Class (Polymorphic for HAS-A)
class Engine {
  public:
    Engine() noexcept = default;
    virtual ~Engine() noexcept = default;

    // Virtual function → allows polymorphism
    virtual void start() const noexcept {
        cout << "Generic Engine started\n";
    }

    // Prevent copying
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};

// Derived Engine: ElectricEngine
class ElectricEngine final : public Engine {
  public:
    ElectricEngine() noexcept = default;
    ~ElectricEngine() noexcept override = default;

    void start() const noexcept override {
        cout << "Electric Engine started\n";
    }
};

// Car Class (Aggregation → Engine is external)
class Car final {
  private:
    Engine* enginePtr;  // Non-owning pointer → weak HAS-A

  public:
    explicit Car(Engine* eng) noexcept : enginePtr(eng) {}

    ~Car() noexcept = default; // Car does NOT delete Engine

    // Prevent copying
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    void drive() const noexcept {
        if (enginePtr) {
            enginePtr->start(); // Polymorphic call
            cout << "Car is driving\n";
        }
    }
};

// Main Function
int main() {
    ElectricEngine engine;  // Engine lifetime independent
    Car myCar(&engine);     // Aggregation → Car does not own Engine

    myCar.drive();          // Calls ElectricEngine::start() via polymorphism

    return 0;
}
/* Output:
Electric Engine started
Car is driving
*/

Key Points:
--> Car HAS-A Engine (weak) → Car does not delete Engine
--> Engine lifetime managed externally
--> Polymorphism works using base class pointer/reference