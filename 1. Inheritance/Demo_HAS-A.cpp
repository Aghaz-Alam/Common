| Relationship Type | Description    | Lifetime / Ownership            | Example                                  |
| ----------------- | -------------- | ------------------------------- | ---------------------------------------- |
| **Composition**   | Strong “has-a” | Part cannot exist without whole | Car has an Engine (`unique_ptr`)         |
| **Aggregation**   | Weak “has-a”   | Part can exist independently    | Car uses Engine (`Engine*` or `Engine&`) |
| **Inheritance**   | “IS-A”         | Derived is a type of base       | Car IS-A Vehicle                         |

Composition ["Has-a" (strong ownership)]
--> Composition is a strong "has-a" relationship where the contained object (part) cannot exist without the container object (whole). 
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



Aggregation  ["Has-a" (weak ownership)]
---> Aggregation is a weaker "has-a" relationship where the contained object can exist independently of the container object. 
---> The container typically holds a pointer or reference to an object created elsewhere.

#include <iostream>
using namespace std;

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







//Composition
#include <iostream>
#include <string>
#include <memory>   // For unique_ptr
using namespace std;
class Engine final {
  private:
    string type;
  public:
    explicit Engine(string t) : type(move(t)){
        cout << "Engine (" << type << ") Created\n";
    }
    ~Engine() noexcept {
        cout << "Engine (" << type << ") Destroyed\n";
    }
    void start() const noexcept {
        cout << "Engine started\n";
    }
    // Prevent copying
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    
    // Allow moving if usable (optional)
    Engine(Engine&&) noexcept = default;
    Engine& operator=(Engine&&) noexcept = default;
};
class Car final {
  private:
    unique_ptr<Engine> engine;   // Strong ownership
    string name;
  public:
    Car(string n, string engineType): name(move(n)), engine(make_unique<Engine>(move(engineType))){
        cout << "Car (" << name << ") Created\n";
    }
    ~Car() noexcept {
        cout << "Car (" << name << ") Destroyed\n";
        // unique_ptr automatically destroys the Engine
    }
    // Prevent copying (unique_ptr cannot be copied)
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    // Allow moves
    Car(Car&&) noexcept = default;
    Car& operator=(Car&&) noexcept = default;

    void drive() const noexcept {
        cout << "Driving the " << name << ": ";
        engine->start();
    }
};
int main() {
    Car myCar("Sedan", "V6");   // Composition: Engine created *inside* Car
    myCar.drive();
  return 0;
}
/*
Output:
Engine (V6) Created
Car (Sedan) Created
Driving the Sedan: Engine started
Car (Sedan) Destroyed
Engine (V6) Destroyed
*/


Cars
Name: Sedan, Type: V6
Name: Hatchback, Type: Inline-4
Name: SportsCar, Type: V8
Name: HyperCar, Type: W16
Name: MuscleCar, Type: V8 Supercharged
Name: CompactCar, Type: Inline-3 Turbo
Name: LuxuryCar, Type: V12
Name: FamilySUV, Type: V6 Turbo
Name: ElectricSedan, Type: Dual Electric Motors
Name: HybridSUV, Type: Inline-4 Hybrid





//Aggregation
#include <iostream>
#include <string>
using namespace std;
class Engine {
  private:
    string type;
  public:
    explicit Engine(string t): type(move(t)){
        cout << "Engine (" << type << ") Created\n";
    }
    ~Engine() noexcept {
        cout << "Engine (" << type << ") Destroyed\n";
    }
    void start() const noexcept {
        cout << "Engine started\n";
    }
    // Prevent copying
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    // Allow moves
    Engine(Engine&&) noexcept = default;
    Engine& operator=(Engine&&) noexcept = default;
};
class Car final {
  private:
    Engine* engine;   // Non-owning raw pointer → Aggregation
    string name;

  public:
    // Car receives an existing engine → no ownership
    Car(string n, Engine* eng) noexcept: name(move(n)), engine(eng){
        cout << "Car (" << name << ") Created\n";
    }
    ~Car() noexcept {
        cout << "Car (" << name << ") Destroyed\n";
        // Engine is NOT destroyed here — Car does NOT own it
    }

    // No copying or moving needed (but we can delete copy ops anyway)
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    void drive() const noexcept {
        cout << "Driving the " << name << ": ";
        engine->start();   // Polymorphic-safe if Engine were polymorphic
    }
};

int main() {
    Engine engine("V6");      // Engine exists independently
    Car myCar("Sedan", &engine);  // Aggregation → Car uses Engine

    myCar.drive();

    return 0;
}
/*
Output:
Engine (V6) Created
Car (Sedan) Created
Driving the Sedan: Engine started
Car (Sedan) Destroyed
Engine (V6) Destroyed
*/


Cars,
Name: Sedan, Type: V6
Name: SUV, Type: V6
Name: Minivan, Type: V6