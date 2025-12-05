/* 

38. Create a C++ program where an abstract class Car declares pure virtual functions for basic safety features 
and derived classes implement their own behavior. 

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

// ============================================================================
// Abstract Base Class: Car
// ============================================================================
class Car {
protected:
    string name;
    double price;

public:
    Car(string n, double p) : name(n), price(p) {}
    virtual ~Car() {}

    double getPrice() const { return price; }
    string getName() const { return name; }

    // Pure virtual function
    virtual string airbagDetails() const = 0;

    // Virtual function to display features
    virtual void display() const = 0;
};

// ============================================================================
// Hatchback Class
// ============================================================================
class Hatchback : public Car {
public:
    Hatchback(string n, double p) : Car(n, p) {}

    string airbagDetails() const override {
        return "2 basic airbags";
    }

    void display() const override {
        cout << "---- Hatchback Safety Features ----\n";
        cout << "Car: " << name << "\n";
        cout << "Price: " << price << "\n";
        cout << "Airbags: " << airbagDetails() << "\n\n";
    }
};

// ============================================================================
// LuxuryCar Class
// ============================================================================
class LuxuryCar : public Car {
public:
    LuxuryCar(string n, double p) : Car(n, p) {}

    string airbagDetails() const override {
        return "8 airbags (advanced)";
    }

    void display() const override {
        cout << "---- Luxury Car Safety Features ----\n";
        cout << "Car: " << name << "\n";
        cout << "Price: " << price << "\n";
        cout << "Airbags: " << airbagDetails() << "\n\n";
    }
};

// ============================================================================
// SportsCar Class
// ============================================================================
class SportsCar : public Car {
public:
    SportsCar(string n, double p) : Car(n, p) {}

    string airbagDetails() const override {
        return "6 airbags (performance)";
    }

    void display() const override {
        cout << "---- Sports Car Safety Features ----\n";
        cout << "Car: " << name << "\n";
        cout << "Price: " << price << "\n";
        cout << "Airbags: " << airbagDetails() << "\n\n";
    }
};

// ============================================================================
// Showroom Class
// ============================================================================
class Showroom {
private:
    vector<Car*> cars;

public:
    void addCar(Car* car) {
        cars.push_back(car);
    }

    void displayAllCars() const {
        for (auto car : cars) {
            car->display();
        }
    }

    void showSummary() const {
        cout << "-----------------------------------\n";
        cout << "Total Cars: " << cars.size() << "\n";

        double totalValue = 0;
        for (auto car : cars)
            totalValue += car->getPrice();

        cout << "Total Value: " << totalValue << "\n";

        // Find most expensive car
        Car* expensive = cars[0];
        for (auto car : cars) {
            if (car->getPrice() > expensive->getPrice()) {
                expensive = car;
            }
        }

        cout << "Highest Priced Car: " << expensive->getName() << "\n";
    }

    ~Showroom() {
        for (auto car : cars)
            delete car;
    }
};

// ============================================================================
// Main Function
// ============================================================================
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
Total Value: 12650000
Highest Priced Car: Porsche GT
*/