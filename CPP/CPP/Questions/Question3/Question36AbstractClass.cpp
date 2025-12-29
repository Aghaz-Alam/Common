/* 
38. Create a C++ program where an abstract class Car declares pure virtual functions for basic safety features and 
    derived classes implement their own behavior. 

    Additionally, introduce a Showroom class that maintains a collection of Car objects, displays their features (including price), 
    and evaluates showroom value using runtime polymorphism.

The Car (Abstract Class) should provide the following behavior:
Store car name and its price.
A pure virtual function to return details about airbags.
A virtual function to display all features—such as name, price, and safety details—which derived classes must override.

The Hatchback class should support the following behavior:
Airbags: Provide basic configuration (e.g., 2 airbags).
Display features including car name and its price.
Represent a relatively low-cost model.

The LuxuryCar class should support the following behavior:
Airbags: Provide premium configuration (e.g., 6–8 high-grade airbags).
Display luxury-oriented features including name and price.
Represent a high-value model.

The SportsCar class should support the following behavior:
Airbags: Provide performance-oriented configuration.
Display performance-focused features including name and price.

Represent a premium performance-focused model.

Introduce a Showroom class that:
Maintains a collection of Car objects (any internal storage mechanism may be chosen).
Allows adding different Car objects into the showroom.
Displays complete feature information of all cars present by invoking their overridden display behavior polymorphically.
Computes total value of all cars present in the showroom.
Identifies and provides the most expensive car.

Ensures proper cleanup of allocated Car objects when necessary.

Sample Usage :

Showroom showroom;
showroom.addCar(new Hatchback("Swift", 600000));
showroom.addCar(new LuxuryCar("BMW X5", 4500000));
showroom.addCar(new SportsCar("Porsche GT", 7500000));

showroom.displayAllCars();
showroom.showSummary();


Expected Output Format (Conceptual Representation):

---- Hatchback Safety Features ----
Car: Swift
Price: 600000
Airbags: 2 basic airbags

---- Luxury Car Safety Features ----
Car: BMW X5
Price: 4500000
Airbags: 8 airbags (advanced)


---- Sports Car Safety Features ----
Car: Porsche GT
Price: 7500000
Airbags: 6 airbags (performance)

-----------------------------------
Total Cars: 3
Total Value: 12650000
Highest Priced Car: Porsche GT
*/



#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ==============================
// Abstract Car class
// ==============================
class Car {
  protected:
    string name;
    long price;

  public:
    Car(const string& n, long p) : name(n), price(p) {}

    virtual ~Car() {}

    // Pure virtual function: airbags
    virtual string airbags() const = 0;

    // Virtual function to display features
    virtual void displayFeatures() const {
        cout << "Car: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Airbags: " << airbags() << endl;
    }

    long getPrice() const { return price; }
    string getName() const { return name; }
};

// ==============================
// Derived Hatchback
// ==============================
class Hatchback : public Car {
  public:
    Hatchback(const string& n, long p) : Car(n, p) {}

    string airbags() const override {
        return "2 basic airbags";
    }

    void displayFeatures() const override {
        cout << "---- Hatchback Safety Features ----" << endl;
        Car::displayFeatures();
        cout << endl;
    }
};

// ==============================
// Derived LuxuryCar
// ==============================
class LuxuryCar : public Car {
  public:
    LuxuryCar(const string& n, long p) : Car(n, p) {}

    string airbags() const override {
        return "8 airbags (advanced)";
    }

    void displayFeatures() const override {
        cout << "---- Luxury Car Safety Features ----" << endl;
        Car::displayFeatures();
        cout << endl;
    }
};

// ==============================
// Derived SportsCar
// ==============================
class SportsCar : public Car {
  public:
    SportsCar(const string& n, long p) : Car(n, p) {}

    string airbags() const override {
        return "6 airbags (performance)";
    }

    void displayFeatures() const override {
        cout << "---- Sports Car Safety Features ----" << endl;
        Car::displayFeatures();
        cout << endl;
    }
};

// ==============================
// Showroom class
// ==============================
class Showroom {
  private:
    vector<Car*> cars;

  public:
    // Add a car
    void addCar(Car* car) {
        cars.push_back(car);
    }

    // Display all cars
    void displayAllCars() const {
        for (const auto& car : cars)
            car->displayFeatures();
    }

    // Show summary: total cars, total value, highest priced car
    void showSummary() const {
        long totalValue = 0;
        long highestPrice = 0;
        string highestCar;

        for (const auto& car : cars) {
            totalValue += car->getPrice();
            if (car->getPrice() > highestPrice) {
                highestPrice = car->getPrice();
                highestCar = car->getName();
            }
        }

        cout << "-----------------------------------" << endl;
        cout << "Total Cars: " << cars.size() << endl;
        cout << "Total Value: " << totalValue << endl;
        cout << "Highest Priced Car: " << highestCar << endl;
    }

    // Destructor: cleanup
    ~Showroom() {
        for (auto car : cars) {
            delete car;
        }
    }
};

// ==============================
// MAIN
// ==============================
int main() {
    Showroom showroom;

    showroom.addCar(new Hatchback("Swift", 600000));
    showroom.addCar(new LuxuryCar("BMW X5", 4500000));
    showroom.addCar(new SportsCar("Porsche GT", 7500000));

    showroom.displayAllCars();
    showroom.showSummary();

    return 0;
}
/*
---- Hatchback Safety Features ----
Car: Swift
Price: 600000
Airbags: 2 basic airbags

---- Luxury Car Safety Features ----
Car: BMW X5
Price: 4500000
Airbags: 8 airbags (advanced)

---- Sports Car Safety Features ----
Car: Porsche GT
Price: 7500000
Airbags: 6 airbags (performance)

-----------------------------------
Total Cars: 3
Total Value: 12600000
Highest Priced Car: Porsche GT
*/