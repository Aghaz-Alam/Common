//1. encapsulation 
#include<iostream>
using namespace std;
class Base{
  //encapsulation
  protected:
   int x, y;  
  public:
    Base(int a, int b):x(a), y(b){}
    void setX(int val){
      x=val;
    }
    //Abstraction
    virtual void Add() const=0;
    virtual ~Base()=default;
};
//inheritance
class Derived: public Base{
    public:
     Derived(int x, int y):Base(x, y){}
     void Add() const override{
         cout<<x + y<<endl;
     }
     
};
//polymorphism
void testFun(const Base& Obj){
   Obj.Add();   
}
int main(){
   Base* b = new Derived(10,20);
   testFun(*b);                                       //30
   
   //Or
    
   Derived d(100, 200);
   
   Base& ptr = d;
   testFun(ptr);                                        //300
   
   Base* p=&d;
   testFun(*p);                                          //300
   
  return 0;
}
/* 
30
300
300
*/








#include <iostream>
#include <memory>
using namespace std;

// 1. Encapsulation → hiding internal data
class Base {
  private:
    int x, y;

  public:
    Base(int val1, int val2) : x(val1), y(val2) {}

    int getX() const { return x; }
    void setX(int a) { x = a; }
    
    int getY() const { return y; }
    void setY(int b) { y = b; }


    // 2. Abstraction → pure virtual function
    virtual void Add() = 0;

    virtual ~Base() = default;
};

// 3. Inheritance
class Derived : public Base {
  public:
    Derived(int x, int y) : Base(x, y) {}

    void Add() override {
        cout << "Addition: " << getX() + getY() << "\n";
    }
};

// 4. Polymorphism
void testBase(const unique_ptr<Base>& v) {
    v->Add();
}

int main() {
    unique_ptr<Base> d = make_unique<Derived>(120, 50);
    
    testBase(d);


    d->setX(100);  
    d->setY(200);
    testBase(d);
    return 0;
}
/* 
Addition: 170
Addition: 300
*/




#include <iostream>
#include <memory>      // for smart pointers (modern C++)
#include <string>
using namespace std;

// 1. ENCAPSULATION  → Hiding data using private members
class Vehicle {
  private:
    int speed;          // hidden data
    int fuel;

  public:
    Vehicle(int s, int f) : speed(s), fuel(f) {}

    // Getter / Setter → controlled access
    int getSpeed() const { return speed; }
    void setSpeed(int s) { speed = s; }

    int getFuel() const { return fuel; }
    void setFuel(int f) { fuel = f; }

    // ============================================================
    // 2. ABSTRACTION → Exposing only necessary information
    // ============================================================
    virtual void start() const = 0;  // Pure virtual → Abstract
    virtual void stop() const = 0;

    virtual ~Vehicle() = default;
};

// ============================================================
// 3. INHERITANCE → Car and Bike inherit from Vehicle
// ============================================================
class Car : public Vehicle {
  public:
    Car(int s, int f) : Vehicle(s, f) {}

    void start() const override {
        cout << "Car started with speed " << getSpeed() << " km/h\n";
    }

    void stop() const override {
        cout << "Car stopped.\n";
    }
};

class Bike : public Vehicle {
  public:
    Bike(int s, int f) : Vehicle(s, f) {}

    void start() const override {
        cout << "Bike started with speed " << getSpeed() << " km/h\n";
    }

    void stop() const override {
        cout << "Bike stopped.\n";
    }
};

// ============================================================
// 4. POLYMORPHISM → Same interface, different behavior
// Using virtual functions + smart pointers
// ============================================================
void testVehicle(const unique_ptr<Vehicle>& v) {
    v->start();
    v->stop();
}

int main() {
    // modern C++ uses smart pointers
    unique_ptr<Vehicle> car  = make_unique<Car>(120, 50);
    unique_ptr<Vehicle> bike = make_unique<Bike>(80, 10);

    testVehicle(car);
    testVehicle(bike);

    return 0;
}
/*
Car started with speed 120 km/h
Car stopped.
Bike started with speed 80 km/h
Bike stopped.
*/




✅ Explanation (Interview-Ready)
1. Encapsulation
speed and fuel are private
Controlled using getSpeed(), setSpeed()
Prevents direct modification → protects data

2. Abstraction
Vehicle has only important functions exposed:
start()
stop()
Internal complexity hidden

3. Inheritance
Car and Bike extend Vehicle
Reuse and extend existing behavior

4. Polymorphism
testVehicle() takes a Vehicle*, but behaves differently for Car and Bike
Achieved using virtual functions
Modern C++ uses unique_ptr for memory safety















// C++17/C++20 style (compiles with -std=c++17 or -std=c++20)
// File: zoo.cpp

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

// -------------------------------
// 1) ABSTRACT BASE (Abstraction + Encapsulation)
// -------------------------------
class Animal {
  private:
    // Encapsulation: internal state hidden
    std::string name_;
    int age_;
    double weightKg_;

  protected:
    // Protected constructor — cannot instantiate directly
    Animal(std::string name, int age, double weight)
        : name_(std::move(name)), age_(age), weightKg_(weight) {}

  public:
    // Abstraction: public interface to interact with animals
    virtual ~Animal() = default;                     // polymorphic base: virtual dtor
    virtual void makeSound() const = 0;              // pure virtual -> abstract
    virtual void eat(double foodKg) {                // default behavior
        weightKg_ += foodKg * 0.5;                   // simplistic weight gain model
        std::cout << name_ << " ate " << foodKg << " kg, now weight: "
                  << weightKg_ << " kg\n";
    }

    // Encapsulated accessors
    const std::string& name() const { return name_; }
    int age() const { return age_; }
    double weight() const { return weightKg_; }

    // A polymorphic clone — helpful for copying animals via base pointer
    virtual std::unique_ptr<Animal> clone() const = 0;
};

// -------------------------------
// 2) INHERITANCE: Specific animals
// -------------------------------
class Dog : public Animal {
  private:
    std::string breed_;

  public:
    Dog(std::string name, int age, double weight, std::string breed)
        : Animal(std::move(name), age, weight), breed_(std::move(breed)) {}

    void makeSound() const override {
        std::cout << name() << " (Dog, " << breed_ << ") says: Woof!\n";
    }

    // override eat to show specialized behavior (polymorphism)
    void eat(double foodKg) override {
        // Call base behavior first (reuse code)
        Animal::eat(foodKg);
        std::cout << name() << " wags tail happily after eating.\n";
    }

    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Dog>(*this);
    }
};

class Parrot : public Animal {
  private:
    bool canTalk_;

  public:
    Parrot(std::string name, int age, double weight, bool canTalk)
        : Animal(std::move(name), age, weight), canTalk_(canTalk) {}

    void makeSound() const override {
        if (canTalk_)
            std::cout << name() << " (Parrot) says: Hello!\n";
        else
            std::cout << name() << " (Parrot) squawks.\n";
    }

    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Parrot>(*this);
    }
};

// -------------------------------
// 3) POLYMORPHISM: Zoo container & Keeper actions
// -------------------------------
class Zoo {
  private:
    // Encapsulation: vector of owned animals (unique ownership)
    std::vector<std::unique_ptr<Animal>> animals_;

  public:
    Zoo() = default;

    // Add an animal (accepts any Animal or derived)
    void add(std::unique_ptr<Animal> a) {
        animals_.push_back(std::move(a));
    }

    // Demonstrates runtime polymorphism: call makeSound() on each animal
    void morningCall() const {
        std::cout << "Morning roll-call:\n";
        for (const auto& a : animals_) a->makeSound();
    }

    // Feed all animals the same amount using virtual eat
    void feedAll(double kgPerAnimal) {
        std::cout << "Feeding all animals " << kgPerAnimal << " kg each:\n";
        for (auto& a : animals_) a->eat(kgPerAnimal);
    }

    // Demonstrates cloning (uses virtual clone)
    Zoo cloneZoo() const {
        Zoo z;
        for (const auto& a : animals_) z.add(a->clone());
        return z;
    }
};

// -------------------------------
// 4) STATIC (compile-time) polymorphism example:
//    a small generic feeder that works for any container of objects
//    that have a feedable function (duck typing).
// -------------------------------
template <typename Container>
void quickFeed(Container& c, double foodKgPer) {
    // static_assert for friendly error if bad type used
    static_assert(std::is_same_v<typename std::remove_cv<typename std::remove_reference<decltype(*std::begin(c))>::type>::type, typename std::remove_reference<decltype(*std::begin(c))>::type> ||
                  true,
                  "quickFeed expects an iterable container.");
    for (auto& item : c) {
        // two possibilities: item is Animal*/unique_ptr<Animal> or direct object
        if constexpr (std::is_pointer_v<std::remove_reference_t<decltype(item)>>) {
            item->eat(foodKgPer);
        } else {
            // assume object supports eat(double)
            item.eat(foodKgPer);
        }
    }
}

// -------------------------------
// Main: put it together
// -------------------------------
int main() {
    Zoo z;
    z.add(std::make_unique<Dog>("Rex", 4, 18.5, "Labrador"));
    z.add(std::make_unique<Parrot>("Polly", 2, 0.9, true));
    z.add(std::make_unique<Dog>("Mika", 3, 12.0, "Beagle"));

    // Polymorphic behavior at runtime:
    z.morningCall();

    std::cout << "----\n";
    z.feedAll(0.5);

    std::cout << "----\n";
    // Clone the zoo (shows how virtual clone gives correct derived-type copy)
    Zoo z2 = z.cloneZoo();
    z2.morningCall();

    std::cout << "----\n";
    // static polymorphism example:
    // create a small vector of pointers to animals (non-owning raw pointers here)
    std::vector<Animal*> pointers;
    // copy raw pointers (non-owning) into pointers vector by pointing to z's animals
    // WARNING: we access internal animals_ only for demonstration — usually provide accessor
    // For demo, we will recreate a couple objects:
    Dog d("Buddy", 5, 20.0, "Shepherd");
    Parrot p("Echo", 1, 0.7, false);
    std::vector<Animal*> demo = { &d, &p };
    quickFeed(demo, 0.1); // compile-time polymorphism (duck-typing on eat())

    return 0;
}
/* 
Morning roll-call:
Rex (Dog, Labrador) says: Woof!
Polly (Parrot) says: Hello!
Mika (Dog, Beagle) says: Woof!
----
Feeding all animals 0.5 kg each:
Rex ate 0.5 kg, now weight: 18.75 kg
Rex wags tail happily after eating.
Polly ate 0.5 kg, now weight: 1.15 kg
Mika ate 0.5 kg, now weight: 12.25 kg
Mika wags tail happily after eating.
----
Morning roll-call:
Rex (Dog, Labrador) says: Woof!
Polly (Parrot) says: Hello!
Mika (Dog, Beagle) says: Woof!
----
Buddy ate 0.1 kg, now weight: 20.05 kg
Buddy wags tail happily after eating.
Echo ate 0.1 kg, now weight: 0.8 kg

*/


Thorough explanation, pillar by pillar
1) Encapsulation (data hiding & controlled access)
In Animal the members name_, age_, weightKg_ are private. External code cannot modify them directly.
Accessors (name(), age(), weight()) provide controlled read access. eat() manipulates internal state — the class controls how its state changes.
Zoo also encapsulates its internal animals_ vector as private — external code can’t mutate it directly.
Why this matters: encapsulation prevents incorrect external changes and centralizes invariants (e.g., how an animal’s weight changes when fed).

2) Abstraction (expose only necessary operations)
Animal exposes a minimal, high-level interface: makeSound(), eat(), clone(), and accessors.
Implementation details (how weight changes when eating, how sound is produced) are hidden inside derived classes.
Zoo exposes high-level operations like add(), feedAll(), morningCall() rather than exposing details of iteration or storage.
Why this matters: user of Zoo or Animal needs to know what operations are possible, not how they’re implemented.

3) Inheritance (code reuse and semantics)
Dog and Parrot inherit from Animal. They reuse base behavior (eat() default) and override as needed (e.g., Dog::eat()).
Animal is an abstract base (pure virtual makeSound()), so derived classes must implement concrete behavior.
Why this matters: common behavior moves into Animal, reducing duplication, while allowing specialization in derived classes.

4) Polymorphism (same interface, different behavior)
Runtime polymorphism: std::unique_ptr<Animal> in Zoo stores different derived types. Calling a->makeSound() or a->eat() dispatches to the appropriate derived override at runtime because the methods are virtual.

Demonstrated by z.morningCall() and z.feedAll().
Static (compile-time) polymorphism: quickFeed(Container&) template works with any container of objects/pointers that support eat(double). 
This is not virtual; it’s resolved at compile time (duck typing). Useful when you care about performance or working with concrete types.
Why this matters: runtime polymorphism gives flexibility to work with heterogenous types through a base pointer;
static polymorphism gives performance and compile-time safety for homogeneous types or templates.

Additional best practices shown

Use unique_ptr for ownership to avoid manual delete.

Provide a virtual destructor in base classes (virtual ~Animal() = default;) to ensure derived destructors run.

Provide a clone() virtual method when you need to copy polymorphic objects (since copy via base pointer would slice).

Prefer override to catch mistakes when overriding virtual functions.

Use protected constructor in abstract base so you can’t instantiate Animal.

Caveats & things to watch out for

In quickFeed I used a simple if constexpr + pointer test to support both pointer and direct object containers. Real code might use clearer overloads or concepts (C++20) to constrain templates.
The demo in main that creates raw pointers into z’s animals is not safe in general: exposing raw pointers to internal ownership-managed objects requires careful lifetime management. I recreated objects to avoid lifetime issues.
clone() returns unique_ptr<Animal> to preserve polymorphic copy semantics.







#include <iostream>
#include <memory>     
using namespace std;

// 1. Encapsulation  → Hiding data using private members
class Base {
  private:
    int x;          // hidden data
  public:
    Base(int val) :x(val){}

    // Getter / Setter → controlled access
    int getX() const { return x; }
    void setX(int a) { x = a; }

    // 2. Abstraction → Exposing only necessary information
    virtual void Add() = 0;  // Pure virtual → Abstract
    virtual ~Base() = default;
};


// 3. Inheritance → Car and Bike inherit from Vehicle
class Derived1 : public Base {
    int y;
  public:
    Derived1(int x, int y) : Base(x), y(y) {}

    void Add() override {
        cout << "Addition: " << getX()+y << "\n";
    }

    
};
class Derived2 : public Base {
    int z;
  public:
    Derived2(int x, int z) : Base(x) , z(z){}
    void Add() override {
        cout << "Addition: " << getX()+z << "\n";
    }
};

// 4. Polymorphisms → Same interface, different behavior
void tetBase(const unique_ptr<Base>& v) {
    v->Add();
}

int main() {
    // modern C++ uses smart pointers
    unique_ptr<Base> d1  = make_unique<Derived1>(120, 50);
    unique_ptr<Base> d2 = make_unique<Derived2>(80, 10);

    tetBase(d1);
    tetBase(d2);

    return 0;
}
/*
Addition: 170
Addition: 90
*/







//Modern C++
#include <iostream>
#include <memory>
#include <utility>
class Base {
  private:
    int x;  // Encapsulated data

  public:
    explicit Base(int val) noexcept : x(val) {}
    virtual ~Base() noexcept = default;     // Polymorphic base class

    // Getter / Setter with modern attributes
    [[nodiscard]] int getX() const noexcept { return x; }
    void setX(int a) noexcept { x = a; }

    // Abstract behavior (Abstraction)
    virtual void Add() const = 0;
};

// Derived class #1
class Derived1 final : public Base {
  private:
    int y;

  public:
    Derived1(int x, int y) noexcept : Base(x), y(y) {}

    void Add() const override {
        std::cout << "Addition: " << getX() + y << '\n';
    }
};

// Derived class #2
class Derived2 final : public Base {
  private:
    int z;

  public:
    Derived2(int x, int z) noexcept : Base(x), z(z) {}

    void Add() const override {
        std::cout << "Addition: " << getX() + z << '\n';
    }
};

// Polymorphic function
void testBase(const std::unique_ptr<Base>& obj) {
    obj->Add();
}

int main() {
    auto d1 = std::make_unique<Derived1>(120, 50);
    auto d2 = std::make_unique<Derived2>(80, 10);

    testBase(d1);
    testBase(d2);

    return 0;
}
/*
Addition: 170
Addition: 90
*/






















#include <iostream>
#include <memory>
using namespace std;

// 1. Encapsulation → hiding internal data
class Base {
  private:
    int x, y;

  public:
    Base(int val1, int val2) : x(val1), y(val2) {}

    int getX() const { return x; }
    void setX(int a) { x = a; }
    
    int getY() const { return y; }
    void setY(int b) { y = b; }


    // 2. Abstraction → pure virtual function
    virtual void Add() = 0;

    virtual ~Base() = default;
};

// 3. Inheritance
class Derived : public Base {
  public:
    Derived(int x, int y) : Base(x, y) {}

    void Add() override {
        cout << "Addition: " << getX() + getY() << "\n";
    }
};

// 4. Polymorphism
void testBase(const unique_ptr<Base>& v) {
    v->Add();
}

int main() {
    unique_ptr<Base> d = make_unique<Derived>(120, 50);
    testBase(d);


    d->setX(100);  
    d->setY(200);
    testBase(d);
    return 0;
}
/*
Addition: 170
Addition: 300
*/













