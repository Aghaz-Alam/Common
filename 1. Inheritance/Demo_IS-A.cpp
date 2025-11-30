| Relationship Type | Description    | Lifetime / Ownership            | Example                                  |
| ----------------- | -------------- | ------------------------------- | ---------------------------------------- |
| **Composition**   | Strong “has-a” | Part cannot exist without whole | Car has an Engine (`unique_ptr`)         |
| **Aggregation**   | Weak “has-a”   | Part can exist independently    | Car uses Engine (`Engine*` or `Engine&`) |
| **Inheritance**   | “IS-A”         | Derived is a type of base       | Car IS-A Vehicle                         |




3. Inheritance ["IS-A" Relation]
   --> Inheritance represents an “IS-A” relationship between classes.
   --> A derived class is a specialized type of the base class.
   --> The derived class inherits the properties and behavior of the base class.

   Example: Car IS-A Vehicle
   --> Car inherits methods like start() and stop() from Vehicle.
   --> Car can also extend or override base class behavior.

Key points:
   --> Supports polymorphism → base class pointer/reference can refer to derived class objects.
   --> Enables code reuse and extensibility.


#include <iostream>
#include <string>   // Needed for std::string
using namespace std;
class Vehicle {
  public:
    Vehicle() noexcept = default;
    virtual ~Vehicle() noexcept = default;  // Virtual destructor → safe polymorphism

    virtual void start() const noexcept {
        cout << "Vehicle: Engine started.\n";
    }

    virtual void stop() noexcept {
        cout << "Vehicle: Vehicle stopped.\n";
    }

    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;
};

class Car final : public Vehicle {
  public:
    Car() noexcept = default;
    ~Car() noexcept override = default;

    void start() const noexcept override {
        cout << "Car: Engine started using push-button ignition.\n";
    }

    void honk() const noexcept {
        cout << "Car horn: Beep! Beep!\n";
    }

    void turnOnAc() const noexcept {
        cout << "Car: Air conditioner turned ON.\n";
    }

    void playMusic(const string& trackName) noexcept {
        cout << "Car: Now playing - " << trackName << '\n';
    }
};

void testDrive(const Vehicle& vehicle) noexcept {
    cout << "Test Drive: ";
    vehicle.start();  // Calls Car::start() if derived object
}

int main() {
    // Stack object → no manual memory management needed
    Car myCar;

    myCar.start();                 
    myCar.turnOnAc();              
    myCar.playMusic("Shape of You");
    myCar.honk();                  
    myCar.stop();                  

    // Demonstrate polymorphism using reference
    Vehicle& vehicleRef = myCar;
    testDrive(vehicleRef);         

    return 0;
}
/*
Car: Engine started using push-button ignition.
Car: Air conditioner turned ON.
Car: Now playing - Shape of You
Car horn: Beep! Beep!
Vehicle: Vehicle stopped.
Test Drive: Car: Engine started using push-button ignition.
*/






//Modern C++ IS-A relation
#include <iostream>
#include <string>
using namespace std;
class Vehicle {                             // Base Class: Vehicle
  private:
    int speed;
    float fuelLevel;

  public:
    // Compile-time constants
    constexpr static int MAX_SPEED = 300;
    constexpr static float MAX_FUEL = 100.0f;

    // Explicit constructor to avoid implicit conversions
    explicit Vehicle(int initialSpeed = 0, float initialFuel = MAX_FUEL) noexcept: speed(initialSpeed), fuelLevel(initialFuel) {}

    // Virtual destructor for safe polymorphism
    virtual ~Vehicle() noexcept = default;   //Use the compiler-generated destructor.

    // Getters
    [[nodiscard]] int getSpeed() const noexcept { return speed; }
    [[nodiscard]] float getFuelLevel() const noexcept { return fuelLevel; }

    // Virtual methods
    virtual void start() noexcept {
        cout << "Vehicle: Engine started.\n";
    }

    virtual void stop() noexcept {
        speed = 0;
        cout << "Vehicle: Stopped.\n";
    }

    void accelerate(const int amount) noexcept {
        speed = min(speed + amount, MAX_SPEED);
        cout << "Vehicle: Accelerating... Current speed: " << speed << " km/h\n";
    }

    void refuel(const float amount) noexcept {
        fuelLevel = min(fuelLevel + amount, MAX_FUEL);
        cout << "Vehicle: Refueled. Current fuel: " << fuelLevel << "%\n";
    }
};

// Derived Class: Car
class Car final : public Vehicle {
  private:
    string currentTrack {"Default Track"};

  public:
    explicit Car(int initialSpeed = 0, float initialFuel = MAX_FUEL) noexcept: Vehicle(initialSpeed, initialFuel) {}

    // Override base class method
    void start() noexcept override {
        cout << "Car: Engine started using push-button.\n";
    }

    void honk() const noexcept {
        cout << "Car: Honk! Honk!\n";
    }

    void turnOnAc() const noexcept {
        cout << "Car: Air conditioner turned ON.\n";
    }

    void playMusic(const string& trackName) noexcept {
        currentTrack = trackName;
        cout << "Car: Now playing - " << currentTrack << '\n';
    }
};
// Utility Function
void testDrive(const Vehicle& vehicleRef) noexcept {
    cout << "Test Drive: Vehicle is currently at "<< vehicleRef.getSpeed() << " km/h\n";
}

int main() {
    Car myCar;

    myCar.start();                                 // overridden function
    myCar.accelerate(40);
    myCar.refuel(15.5f);
    myCar.turnOnAc();
    myCar.playMusic("Shape of You");
    myCar.honk();
    myCar.stop();

    testDrive(myCar);                            // Demonstrate polymorphism safely with reference

    return 0;
}
/*
Car: Engine started using push-button.
Vehicle: Accelerating... Current speed: 40 km/h
Vehicle: Refueled. Current fuel: 100%
Car: Air conditioner turned ON.
Car: Now playing - Shape of You
Car: Honk! Honk!
Vehicle: Stopped.
Test Drive: Vehicle is currently at 0 km/h
*/







