| Relationship Type | Description    | Lifetime / Ownership            | Example                                  |
| ----------------- | -------------- | ------------------------------- | ---------------------------------------- |
| **Composition**   | Strong “has-a” | Part cannot exist without whole | Car has an Engine (`unique_ptr`)         |
| **Aggregation**   | Weak “has-a”   | Part can exist independently    | Car uses Engine (`Engine*` or `Engine&`) |
| **Inheritance**   | “IS-A”         | Derived is a type of base       | Car IS-A Vehicle                         |


1. Composition ["Has-a" (strong ownership)]
   --> Composition is a strong "has-a" relationship where the contained object (part) cannot exist without 
       the container object (whole). 
   --> If the container is destroyed, the contained object is also destroyed.

#include <iostream>
#include <memory>
using namespace std;
class Engine final {
 public:
    explicit Engine() noexcept { 
        cout << "Engine created\n"; 
    }
    ~Engine() noexcept = default;  // Let unique_ptr handle destruction
    void start() const noexcept { 
        cout << "Engine started\n"; 
    }
};
class Car final {
 private:
    unique_ptr<Engine> engine;  // Exclusive ownership (composition)
 public:
    explicit Car() noexcept : engine(make_unique<Engine>()) 
    {
        cout << "Car created\n";
    }
    ~Car() noexcept = default; // unique_ptr automatically cleans up Engine

    // Prevent copying (unique_ptr cannot be copied)
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;
    
    // Allow moving (optional)
    Car(Car&&) noexcept = default;
    Car& operator=(Car&&) noexcept = default;

    void drive() const noexcept {
        engine->start();
        cout << "Car is driving\n";
    }
};
int main() {
    {
        Car myCar;
        myCar.drive();
    } // Car destroyed → Engine automatically destroyed

    return 0;
}
/* Output:
Engine created
Car created
Engine started
Car is driving
Car destroyed
Engine destroyed
*/



2. Aggregation  ["Has-a" (weak ownership)]
   ---> Aggregation is a weaker "has-a" relationship where the contained object can exist independently of 
        the container object. 
   ---> The container typically holds a pointer or reference to an object created elsewhere.

#include <iostream>
using namespace std;
// =====================================
// Engine Class
// Represents an engine whose lifetime is independent of Car
// =====================================
class Engine final {
  public:
    explicit Engine() noexcept {
        cout << "Engine created\n";  // Engine is constructed
    }
    ~Engine() noexcept {
        cout << "Engine destroyed\n";  // Engine is destructed
    }
    void start() const noexcept {
        cout << "Engine started\n";  // Start the engine
    }
};
// =====================================
// Car Class
// Demonstrates aggregation: Car uses Engine (weak “has-a” relationship)
// Car does NOT own Engine; Engine lifetime is independent
// =====================================
class Car final {
  private:
    Engine* enginePtr;  // Non-owning pointer → aggregation

  public:
    explicit Car(Engine* engine) noexcept : enginePtr(engine)  // Car uses Engine → does not create or delete it
    {
        cout << "Car created\n";  // Car is constructed
    }

    ~Car() noexcept {
        cout << "Car destroyed\n";  // Car is destructed
        // Do NOT delete enginePtr → Car does NOT own Engine
    }

    // Prevent copying (unique relationship to Engine pointer)
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    // Drive the car → uses the engine
    void drive() const noexcept {
        if (enginePtr) {
            enginePtr->start();       // Car uses Engine
            cout << "Car is driving\n";  // Action of the car
        }
    }
};
int main() {
    Engine engine;               // Engine created independently
    {
        Car myCar(&engine);      // Car uses Engine → aggregation
        myCar.drive();           // Car drives using Engine
    } // Car destroyed → Engine still exists (weak relationship)

    cout << "Main ends, Engine still exists until here\n";

    return 0;
}
/* Output:
Engine created
Car created
Engine started
Car is driving
Car destroyed
Main ends, Engine still exists until here
Engine destroyed
*/
