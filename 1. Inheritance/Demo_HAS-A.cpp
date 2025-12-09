//Aggregation
#include<iostream>
#include<string>
#include<memory>
using namespace std;    
class Engine final{
     string type;
    public: 
      explicit Engine(string t):type(t){
           cout<<"Engine "<<type<<" created!"<<endl;
      }
      ~Engine(){
          cout<<"Engine "<<type<< " destroyed!"<<endl;
      };
      void start(){
          cout<<"Engine "<< type<<" started!"<<endl;
      }
};
class Car final{
      Engine* engine; 
      string name;
    public:
      explicit Car(string n, Engine* engType): name(n), engine(engType){
          cout<<"Car "<<name<<" started!"<<endl;
      }
      ~Car(){
          cout<<"Car "<<name<<" destroyed!"<<endl;
      }
      void drive(){
          engine->start();
          cout<<"Car "<<name<< " is driving!"<<endl;
      }
};
int main(){
    Engine e("V6");{
        Car c("Sedan", &e);
        c.drive();
    }
}
/*
Engine V6 created!
Car Sedan started!
Engine V6 started!
Car Sedan is driving!
Car Sedan destroyed!
Engine V6 destroyed!
*/



//Aggregation
#include<iostream>
#include<string>
#include<memory>
using namespace std;    
class Engine final{
     string type;
    public: 
      explicit Engine(string t):type(t){
           cout<<"Engine "<<type<<" created!"<<endl;
      }
      ~Engine(){
          cout<<"Engine "<<type<< " destroyed!"<<endl;
      };
      void start(){
          cout<<"Engine "<< type<<" started!"<<endl;
      }
};
class Car final{
      shared_ptr<Engine> engine; 
      string name;
    public:
      explicit Car(string n, shared_ptr<Engine> engType): name(n), engine(engType){
          cout<<"Car "<<name<<" started!"<<endl;
      }
      ~Car(){
          cout<<"Car "<<name<<" destroyed!"<<endl;
      }
      void drive(){
          engine->start();
          cout<<"Car "<<name<< " is driving!"<<endl;
      }
};
int main(){
    shared_ptr<Engine> e = make_shared<Engine>("V6");
    Car c("Sedan", e);
    c.drive();
    
}
/*
Engine V6 created!
Car Sedan started!
Engine V6 started!
Car Sedan is driving!
Car Sedan destroyed!
Engine V6 destroyed!
*/





//Compostion
/*
#include<iostream>
#include<string>
#include<memory>
using namespace std;    
class Engine final{
     string type;
    public: 
      explicit Engine(string t):type(t){
           cout<<"Engine "<<type<<" created!"<<endl;
      }
      ~Engine(){
          cout<<"Engine "<<type<< " destroyed!"<<endl;
      };
      void start(){
          cout<<"Engine "<< type<<" started!"<<endl;
      }
};
class Car final{
      unique_ptr<Engine> engine; 
      string name;
    public:
      explicit Car(string n, string engType ):name(n), engine(make_unique<Engine>(engType)){
          cout<<"Car "<<name<<" started!"<<endl;
      }
      ~Car(){
          cout<<"Car "<<name<<" destroyed!"<<endl;
      }
      void drive(){
          engine->start();
          cout<<"Car "<<name<< " is driving!"<<endl;
      }
};
int main(){
    Car c("Sedan", "V6");
    c.drive();
    
}
/*
Engine V6 created!
Car Sedan started!
Engine V6 started!
Car Sedan is driving!
Car Sedan destroyed!
Engine V6 destroyed!
*/








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
Name: Sedan, SUVs, Type: V6
Name: Hatchback, Type: Inline-4
Name: SportsCar, Type: V8
Name: HyperCar, Type: W16
Name: MuscleCar, Type: V8 Supercharged
Name: CompactCar, Type: Inline-3 Turbo
Name: LuxuryCar, supercars, Type: V12
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








// Composition -- Person owns Address
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class Address {
  private:
    string street;
    string city;
  public:
    Address(string s, string c): street(move(s)), city(move(c)){
        cout << "Address Created: " << street << ", " << city << '\n';
    }
    ~Address() noexcept {
        cout << "Address Destroyed: " << street << ", " << city << '\n';
    }
    const string& getStreet() const noexcept { return street; }
    const string& getCity() const noexcept { return city; }

    // Prevent copying
    Address(const Address&) = delete;
    Address& operator=(const Address&) = delete;

    // Allow moving
    Address(Address&&) noexcept = default;
    Address& operator=(Address&&) noexcept = default;
};
class Person {
  private:
    string name;
    unique_ptr<Address> address;   // Strong ownership
  public:
    Person(string n, string street, string city): name(move(n)), address(make_unique<Address>(move(street), move(city))){
        cout << "Person Created: " << name << '\n';
    }
    ~Person() noexcept {
        cout << "Person Destroyed: " << name << '\n';
        // unique_ptr automatically destroys Address
    }
    // Prevent copying (unique_ptr is non-copyable)
    Person(const Person&) = delete;
    Person& operator=(const Person&) = delete;

    // Allow move semantics
    Person(Person&&) noexcept = default;
    Person& operator=(Person&&) noexcept = default;

    void display() const noexcept {
        std::cout << "Name: " << name<< ", Address: " << address->getStreet()<< ", " << address->getCity() << '\n';
    }
};
int main() {
    Person p1("Alice", "123 Main St", "Anytown");
    p1.display();
  return 0;
}
/*
--- Creating Person (Composition) ---
Address Created: 123 Main St, Anytown
Person Created: Alice
Name: Alice, Address: 123 Main St, Anytown
--- End of main ---
Person Destroyed: Alice
Address Destroyed: 123 Main St, Anytown
*/






// Aggregation -- Person uses Address
#include <iostream>
#include <string>
using namespace std;
class Address {
  private:
    string street;
    string city;
  public:
    Address(string s, string c): street(move(s)), city(move(c)){
        cout << "Address Created: " << street << ", " << city << '\n';
    }
    ~Address() noexcept {
        cout << "Address Destroyed: " << street << ", " << city << '\n';
    }
    const string& getStreet() const noexcept { return street; }
    const string& getCity()   const noexcept { return city; }

    // Disable copying
    Address(const Address&) = delete;
    Address& operator=(const Address&) = delete;

    // Allow moves
    Address(Address&&) noexcept = default;
    Address& operator=(Address&&) noexcept = default;
};
class Person {
  private:
    string name;
    const Address* addressPtr;   // Non-owning → aggregation

  public:
    // Person receives an Address from outside (weak relationship)
    Person(string n, const Address* addr) noexcept: name(move(n)), addressPtr(addr){
        cout << "Person Created: " << name << '\n';
    }
    ~Person() noexcept {
        cout << "Person Destroyed: " << name << '\n';
        // DO NOT delete addressPtr → Person does NOT own Address
    }
    // Prevent copy
    Person(const Person&) = delete;
    Person& operator=(const Person&) = delete;

    // Move allowed
    Person(Person&&) noexcept = default;
    Person& operator=(Person&&) noexcept = default;

    void display() const noexcept {
        cout << "Name: " << name << ", Address: " << addressPtr->getStreet()<< ", " << addressPtr->getCity() << '\n';
    }
};
int main() {
    Address addr("123 Main St", "Anytown");  // Independent object

    Person p1("Alice", &addr); // Person does NOT own Address
    p1.display();

  return 0;
}
/*
Address Created: 123 Main St, Anytown
Person Created: Alice
Name: Alice, Address: 123 Main St, Anytown
Person Destroyed: Alice
Address Destroyed: 123 Main St, Anytown
*/







//“Car owns Engine” (strong HAS-A relationship)-Composition
#include <iostream>
using namespace std;
class Engine {
  public:
    virtual void start() { cout << "Generic engine start\n"; }
    virtual ~Engine() {}
};
class PetrolEngine : public Engine {
  public:
    void start() override { cout << "Petrol engine start\n"; }
};
class Car {
  private:
    Engine* engine;  // Car owns this
   public:
    Car() {
        // Car creates the engine → strong ownership
        engine = new PetrolEngine();
    }
    void startCar() {
        engine->start(); // Polymorphism works here
    }
    ~Car() {
        delete engine; // Car destroys the engine
    }
};
int main() {
    Car c;
    c.startCar();
}
/*
Petrol engine start
*/

Explanation (Composition)
--> Car creates the Engine object inside its constructor.
--> Car destroys the engine in its destructor.
--> Engine object cannot exist without the Car.
--> This is Composition. 
--> Polymorphism is used because Engine* points to PetrolEngine.




//AGGREGATION- “Car uses Engine” (weak HAS-A relationship)
#include <iostream>
using namespace std;
class Engine {
  public:
    virtual void start() { cout << "Generic engine start\n"; }
    virtual ~Engine() {}
};
class DieselEngine : public Engine {
  public:
    void start() override { cout << "Diesel engine start\n"; }
};
class Car {
  private:
    Engine* engine; // Car does NOT own the engine
  public:
    Car(Engine* eng) : engine(eng) {} // Car only uses engine

    void startCar() {
        engine->start(); // Polymorphism works here
    }
    // No delete! Car does NOT own engine
};
int main() {
    Engine* eng = new DieselEngine(); // Engine created outside Car
    Car c(eng);
    c.startCar();

    delete eng; // Engine must be deleted by creator
  return 0
}
/*
Diesel engine start
*/

Explanation (Aggregation)
--> Engine is created outside the Car.
--> Car only uses the existing Engine.
--> Car does not destroy the Engine.
--> Engine can live independently even after Car is destroyed.
--> This is Aggregation.
--> Polymorphism works because Engine* can point to DieselEngine.




//COMPOSITION (Modern C++)-- “Car owns Engine” → strong HAS-A
// Modern C++ Version (using std::unique_ptr)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    virtual void start() { cout << "Generic engine start\n"; }
    virtual ~Engine() = default;
};
class PetrolEngine : public Engine {
  public:
    void start() override { cout << "Petrol engine start\n"; }
};
class Car {
  private:
    unique_ptr<Engine> engine;  // Car owns this strongly
  public:
    Car() : engine(std::make_unique<PetrolEngine>()) {}  // Composition
    void startCar() {
        engine->start();  // Polymorphism
    }
};
int main() {
    Car c;
    c.startCar();
}
/*
Output
Petrol engine start
*/
✔ Explanation (Composition)
--> Car uses unique_ptr<Engine> → exclusive ownership
--> Car creates the Engine internally
--> Car automatically destroys the Engine (RAII)
--> Engine cannot exist without Car → Composition
--> Polymorphism through Engine pointer




//AGGREGATION (Modern C++)--“Car uses Engine” → weak HAS-A
//Modern C++ Version (using std::shared_ptr)
#include <iostream>
#include <memory>
using namespace std;
class Engine {
  public:
    virtual void start() { cout << "Generic engine start\n"; }
    virtual ~Engine() = default;
};
class DieselEngine : public Engine {
  public:
    void start() override { cout << "Diesel engine start\n"; }
};
class Car {
  private:
    shared_ptr<Engine> engine;   // Car does NOT own the engine strongly
  public:
    Car(shared_ptr<Engine> eng) : engine(eng) {}  // Aggregation
    void startCar() {
        engine->start();  // Polymorphism
    }
};
int main() {
    auto eng = std::make_shared<DieselEngine>();  // Engine created outside Car
    Car c(eng);
    c.startCar();
}
/*
Output
Diesel engine start
*/
✔ Explanation (Aggregation)
--> Engine is created outside the Car
--> Car receives a shared_ptr<Engine> → non-owning usage
--> Engine can live even after Car is destroyed
--> This is aggregation
--> Polymorphism works through the Engine pointer
