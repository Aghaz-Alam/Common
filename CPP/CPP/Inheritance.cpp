//Inheritance
//- Public, private inheritance
//- Is-a relation, has-a relation, composition, aggregation

//Modern C++ IS-A relation
#include <iostream>
#include <string>
using namespace std;
class Vehicle {
  private:
    int speed;
    float fuelLevel;

  public:
    // Compile-time constants
    constexpr static int MAX_SPEED = 300;
    constexpr static float MAX_FUEL = 100.0f;

    explicit Vehicle(int initialSpeed = 0, float initialFuel = MAX_FUEL) noexcept: speed(initialSpeed), fuelLevel(initialFuel) {}

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

void testDrive(const Vehicle& vehicleRef) noexcept {
    cout << "Test Drive: Vehicle is currently at "<< vehicleRef.getSpeed() << " km/h\n";
}

int main() {
    Car myCar;

    myCar.start();
    myCar.accelerate(40);
    myCar.refuel(15.5f);
    myCar.turnOnAc();
    myCar.playMusic("Shape of You");
    myCar.honk();
    myCar.stop();

    testDrive(myCar);

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


valgrind --tool=memcheck --leak-check=full ./Inheritance


*/

