design patterns and anti design patterns

| Category     | Pattern                | Purpose                  |
| ------------ | ---------------------- | ------------------------ |
| Creational   | Factory                | Create objects           |
| Creational   | Singleton              | Global instance          |
| Structural   | Adapter                | Interface conversion     |
| Structural   | Decorator              | Add features dynamically |
| Behavioral   | Observer               | Event system             |
| Behavioral   | Strategy               | Swap algorithms          |
| Anti-pattern | God Object             | Too much responsibility  |
| Anti-pattern | Spaghetti Code         | No structure             |
| Anti-pattern | Premature Optimization | Optimize too early       |
| Anti-pattern | Resource Leak          | No RAII                  |


Design-pattern
1. Creational
--> Factory
--> Singleton

2. Structural
--> Adapter
--> Decorator

3. Behavioral
--> Observer
--> Strategy


Anti-pattern
--> God Object 
--> Spaghetti Code 
--> Premature Optimization
--> Resource Leak  


/* ------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
1. Creational Patterns
1.1 Factory Method
Creates objects through an interface rather than using new.

✔️ When used?
Exact derived type is unknown until runtime
Avoid if/else or switch for object creation

✔️ Example
class Shape {
  public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};
class Circle : public Shape {
  public:
    void draw() override { cout << "Circle\n"; }
};
class Square : public Shape {
  public:
    void draw() override { cout << "Square\n"; }
};
class ShapeFactory {
  public:
    static unique_ptr<Shape> create(const string& t) {
        if (t == "circle") return make_unique<Circle>();
        if (t == "square") return make_unique<Square>();
        return nullptr;
    }
};

/* ------------------------------------------------- */
#include <iostream>
#include <memory>
#include <string>
using namespace std;
class Shape {
  public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};
class Circle : public Shape {
  public:
    void draw() override { cout << "Circle\n"; }
};
class Square : public Shape {
  public:
    void draw() override { cout << "Square\n"; }
};
class ShapeFactory {
  public:
    static unique_ptr<Shape> create(const string& t) {
        if (t == "circle") return make_unique<Circle>();
        if (t == "square") return make_unique<Square>();
       return nullptr;
    }
};
int main() {
    // Create shapes using the factory
    auto s1 = ShapeFactory::create("circle");
    auto s2 = ShapeFactory::create("square");
    auto s3 = ShapeFactory::create("triangle"); // invalid type
    if (s1) s1->draw();
    if (s2) s2->draw();
    if (!s3) cout << "Unknown shape type\n";
   return 0;
}
/*
Circle
Square
Unknown shape type
*/

/* ------------------------------------------------- */

Design-pattern
1. Creational
--> Factory
--> Abstract Factory
--> Singleton

2. Structural
--> Adapter
--> Decorator

3. Behavioral
--> Observer
--> Strategy


/* ----------------------------------------------------- */

1.2 Abstract Factory
Creates families of related objects.

Example
class Button {
  public:
    virtual void draw() = 0;
};
class WinButton : public Button {
  public:
    void draw() override { cout << "Windows Button\n"; }
};
class MacButton : public Button {
  public:
    void draw() override { cout << "Mac Button\n"; }
};
class GUIFactory {
  public:
    virtual unique_ptr<Button> createButton() = 0;
};
class WinFactory : public GUIFactory {
  public:
    unique_ptr<Button> createButton() override { 
        return make_unique<WinButton>(); 
    }
};
/* ------------------------------------------------- */
#include <iostream>
#include <memory>
#include <string>
using namespace std;
// -------------------- Product A --------------------
class Button {
  public:
    virtual void draw() = 0;
    virtual ~Button() {}
};
class WinButton : public Button {
  public:
    void draw() override { cout << "Windows Button\n"; }
};
class MacButton : public Button {
  public:
    void draw() override { cout << "Mac Button\n"; }
};
// -------------------- Product B --------------------
class Checkbox {
  public:
    virtual void check() = 0;
    virtual ~Checkbox() {}
};
class WinCheckbox : public Checkbox {
  public:
    void check() override { cout << "Windows Checkbox\n"; }
};
class MacCheckbox : public Checkbox {
  public:
    void check() override { cout << "Mac Checkbox\n"; }
};
// -------------------- Abstract Factory --------------------
class GUIFactory {
  public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() {}
};
// -------------------- Concrete Factories --------------------
class WinFactory : public GUIFactory {
  public:
    unique_ptr<Button> createButton() override {
        return make_unique<WinButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<WinCheckbox>();
    }
};
class MacFactory : public GUIFactory {
  public:
    unique_ptr<Button> createButton() override {
        return make_unique<MacButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<MacCheckbox>();
    }
};
// -------------------- Client --------------------
class GUIApplication {
    unique_ptr<Button> button;
    unique_ptr<Checkbox> checkbox;
  public:
    GUIApplication(GUIFactory& factory) {
        button = factory.createButton();
        checkbox = factory.createCheckbox();
    }
    void render() {
        button->draw();
        checkbox->check();
    }
};
// -------------------- MAIN --------------------
int main() {
    cout << "Using Windows Factory:\n";
    WinFactory wf;
    GUIApplication app1(wf);
    app1.render();
    
    cout << "\nUsing Mac Factory:\n";
    MacFactory mf;
    GUIApplication app2(mf);
    app2.render();
   return 0;
}
/*
Using Windows Factory:
Windows Button
Windows Checkbox

Using Mac Factory:
Mac Button
Mac Checkbox
*/
/* ------------------------------------------------- */

1.3 Singleton
Ensures only one object exists.
Example
class Logger {
  public:
    static Logger& get() {
        static Logger instance;
        return instance;
    }
  private:
    Logger() {}  // private constructor
};

/* ------------------------------------------------- */
✅ Why Meyers Singleton Is Best
✔ Lazy initialization (created only on first call)
✔ Thread-safe in C++11 and newer

Static local variable initialization is guaranteed thread-safe
✔ No memory leaks
✔ No need for manual delete
✔ Simple and minimal


#include <iostream>
#include <thread>
using namespace std;
class Test {
  private:
    Test() { 
        cout << "Constructor called\n"; 
    }
  public:
    // Delete copy and move operations
    Test(const Test&) = delete;
    Test& operator=(const Test&) = delete;
    Test(Test&&) = delete;
    Test& operator=(Test&&) = delete;
    static Test& get() {
        static Test instance;  // Meyers' Singleton
        return instance;
    }

    void fun() {
        cout << "Singleton function\n";
    }
};
int main() {
    Test& t1 = Test::get();
    Test& t2 = Test::get();
    t1.fun();
    t2.fun();

    // Check if both references refer to the same object
    cout << "Address t1: " << &t1 << endl;
    cout << "Address t2: " << &t2 << endl;
    cout<<((&t1 == &t2) ? "Same!" : "Different!")<<endl;
    thread t([](){
       Test::get().fun(); 
    });
    t.join();
    return 0;
}
/*
Constructor called
Singleton function
Singleton function
Address t1: 0x4041d1
Address t2: 0x4041d1
Same!
Singleton function
*/

A singleton means:
Only ONE instance of the class should ever exist.
No one should be able to create or clone another object of that class.

But C++ allows MANY ways to create “another object” unless you block them.
So we delete:
Test(const Test&) = delete;
Test& operator=(const Test&) = delete;
Test(Test&&) = delete;
Test& operator=(Test&&) = delete;


Let us break down WHY each one is needed.

❌ Why delete the copy constructor?
Without this:
Test a = Test::get();  // copy constructor → creates NEW object!

Now you have TWO objects:
the original singleton instance
a new copy

👉Singleton violated.



❌ Why delete the copy assignment operator?
Even if you don’t create a new object, you can overwrite the only instance:

Test& a = Test::get();
Test b = Test::get();  // copy not allowed, but assume it is
a = b;                 // copy assignment modifies singleton state

This allows:
overwriting singleton object’s contents
making the single object inconsistent

👉 State corruption.


❌ Why delete the move constructor?
Move constructor ALSO creates a new object:
Test a = std::move(Test::get());   // move ctor → creates NEW object!

Even though it’s a “move”, the moved-to object must be constructed, so:
a new instance is created
old one may become unusable

👉 Still breaks singleton.


❌ Why delete the move assignment operator?
Even if you don’t create a new object, you can overwrite the singleton:

Test& a = Test::get();
a = std::move(Test::get());    // move assignment modifies singleton

This can:
reset internal state
invalidate invariants
partially move-from the singleton

👉 Logically invalid and dangerous.


/* ------------------------------------------------- */

4. Builder
Construct complex objects step-by-step.


#include <iostream>
#include <memory>
#include <string>
using namespace std;
// -------- Product --------
class House {
  public:
    string basement;
    string structure;
    string roof;
    string interior;
    void show() const {
        cout << "House built:\n";
        cout << "  Basement:  " << basement << '\n';
        cout << "  Structure: " << structure << '\n';
        cout << "  Roof:      " << roof << '\n';
        cout << "  Interior:  " << interior << '\n';
    }
};
// -------- Builder interface --------
class HouseBuilder {
  public:
    virtual ~HouseBuilder() = default;
    virtual HouseBuilder& buildBasement(const string& type) = 0;
    virtual HouseBuilder& buildStructure(const string& type) = 0;
    virtual HouseBuilder& buildRoof(const string& type) = 0;
    virtual HouseBuilder& buildInterior(const string& type) = 0;
    virtual unique_ptr<House> getResult() = 0;
};
// -------- Concrete Builder (fluent API) --------
class ConcreteHouseBuilder : public HouseBuilder {
    unique_ptr<House> house_;
  public:
    ConcreteHouseBuilder() { reset(); }
    void reset() { house_ = make_unique<House>(); }
    HouseBuilder& buildBasement(const string& type) override {
        house_->basement = type;
        return *this;
    }
    HouseBuilder& buildStructure(const string& type) override {
        house_->structure = type;
        return *this;
    }
    HouseBuilder& buildRoof(const string& type) override {
        house_->roof = type;
        return *this;
    }
    HouseBuilder& buildInterior(const string& type) override {
        house_->interior = type;
        return *this;
    }
    unique_ptr<House> getResult() override {
        // transfer ownership of the finished product and reset builder
        auto result = move(house_);
        reset();
        return result;
    }
};
// -------- Director (optional) --------
class Director {
public:
    // builds a simple wooden house
    void constructWoodenHouse(HouseBuilder& builder) {
        builder.buildBasement("Wooden Poles")
               .buildStructure("Wood")
               .buildRoof("Shingles")
               .buildInterior("Simple Furnishings");
    }
    // builds a luxurious stone house
    void constructStoneHouse(HouseBuilder& builder) {
        builder.buildBasement("Reinforced Concrete")
               .buildStructure("Stone & Concrete")
               .buildRoof("Slate Tiles")
               .buildInterior("Luxury Finish");
    }
};
// -------- Example usage --------
int main() {
    ConcreteHouseBuilder builder;
    Director director;
    cout << "--- Director builds a wooden house ---\n";
    director.constructWoodenHouse(builder);
    auto woodenHouse = builder.getResult();
    woodenHouse->show();

    cout << "\n--- Director builds a stone house ---\n";
    director.constructStoneHouse(builder);
    auto stoneHouse = builder.getResult();
    stoneHouse->show();

    cout << "\n--- Direct fluent building (custom) ---\n";
    // You can also use the builder directly for custom configuration
    builder.buildBasement("Pile Foundation")
           .buildStructure("Steel Frame")
           .buildRoof("Green Roof")
           .buildInterior("Minimalist");
    auto customHouse = builder.getResult();
    customHouse->show();
  return 0;
}
/*
--- Director builds a wooden house ---
House built:
  Basement:  Wooden Poles
  Structure: Wood
  Roof:      Shingles
  Interior:  Simple Furnishings

--- Director builds a stone house ---
House built:
  Basement:  Reinforced Concrete
  Structure: Stone & Concrete
  Roof:      Slate Tiles
  Interior:  Luxury Finish

--- Direct fluent building (custom) ---
House built:
  Basement:  Pile Foundation
  Structure: Steel Frame
  Roof:      Green Roof
  Interior:  Minimalist
*/

/* ------------------------------------------------- */

5. Prototype
Clone existing objects.


#include <iostream>
#include <memory>
#include <string>
using namespace std;

//Product Interface (Prototype)
class Shape {
public:
    virtual unique_ptr<Shape> clone() const = 0;  // Prototype (clone method)
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

//Concrete Prototypes
class Circle : public Shape {
    int radius;
public:
    Circle(int r) : radius(r) {}

    // Clone method returns a deep copy
    unique_ptr<Shape> clone() const override {
        return make_unique<Circle>(*this); // invokes copy constructor
    }

    void draw() const override {
        cout << "Circle (radius = " << radius << ")\n";
    }
};

class Rectangle : public Shape {
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}

    unique_ptr<Shape> clone() const override {
        return make_unique<Rectangle>(*this);
    }

    void draw() const override {
        cout << "Rectangle (w=" << width << ", h=" << height << ")\n";
    }
};
//Prototype Registry (optional but common)
class ShapeRegistry {
    unique_ptr<Shape> circlePrototype;
    unique_ptr<Shape> rectPrototype;

public:
    ShapeRegistry() {
        circlePrototype = make_unique<Circle>(5);      // default prototype
        rectPrototype   = make_unique<Rectangle>(10,4);
    }

    unique_ptr<Shape> createCircle() {
        return circlePrototype->clone();
    }

    unique_ptr<Shape> createRectangle() {
        return rectPrototype->clone();
    }
};
//Client Code (uses clone, not constructors)
int main() {
    ShapeRegistry registry;

    // Create objects by cloning prototypes
    auto c1 = registry.createCircle();
    auto c2 = registry.createCircle();
    auto r1 = registry.createRectangle();

    cout << "Cloned shapes:\n";
    c1->draw();
    c2->draw();
    r1->draw();

    return 0;
}
/*
Cloned shapes:
Circle (radius = 5)
Circle (radius = 5)
Rectangle (w=10, h=4)
*/



/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */


2. Structural Patterns
1. Adapter
Convert interface of one class into another.
Example
class Printer {
  public:
    void printText(string s) { cout << s; }
};
class IDevice {
  public:
    virtual void print(string) = 0;
};
class PrinterAdapter : public IDevice {
    Printer p;
  public:
    void print(string s) override { p.printText(s); }
};


/* ------------------------------------------------- */
#include <iostream>
using namespace std;

// Existing class (incompatible interface)
class Printer {
public:
    void printText(string s) {
        cout << "Printer prints: " << s << endl;
    }
};

// Target interface expected by client
class IDevice {
public:
    virtual void print(string) = 0;
    virtual ~IDevice() = default;
};

// Adapter: converts IDevice -> Printer
class PrinterAdapter : public IDevice {
    Printer p;  // using existing Printer object
public:
    void print(string s) override {
        p.printText(s);  // adapt call
    }
};

// Client function that expects an IDevice
void clientCode(IDevice* dev) {
    dev->print("Hello from Client!");
}

int main() {
    // Client wants IDevice, but we only have Printer object
    IDevice* dev = new PrinterAdapter();

    clientCode(dev);

    delete dev;
    return 0;
}
/*
Printer prints: Hello from Client!
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
2. Decorator
Add behavior without modifying class.

Example
class Coffee {
  public:
    virtual int cost() = 0;
};
class BasicCoffee : public Coffee {
  public: 
     int cost() override { 
        return 50;
     }
};
class MilkDecorator : public Coffee {
    Coffee* base;
  public:
    MilkDecorator(Coffee* c) : base(c) {}
    int cost() override { return base->cost() + 20; }
};



/* ------------------------------------------------- */
#include <iostream>
using namespace std;
// Base Component
class Coffee {
  public:
    virtual int cost() = 0;
    virtual ~Coffee() = default;
};
// Concrete Component
class BasicCoffee : public Coffee {
  public:
    int cost() override {
        return 50;
    }
};
// Decorator Base Class (optional but good practice)
class CoffeeDecorator : public Coffee {
  protected:
    Coffee* base;
  public:
    CoffeeDecorator(Coffee* c) : base(c) {}
    virtual ~CoffeeDecorator() { delete base; }
};
// Concrete Decorator 1
class MilkDecorator : public CoffeeDecorator {
  public:
    MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}
    int cost() override {
        return base->cost() + 20;
    }
};
// Concrete Decorator 2
class SugarDecorator : public CoffeeDecorator {
  public:
    SugarDecorator(Coffee* c) : CoffeeDecorator(c) {}
    int cost() override {
        return base->cost() + 10;
    }
};
// Concrete Decorator 3
class CreamDecorator : public CoffeeDecorator {
  public:
    CreamDecorator(Coffee* c) : CoffeeDecorator(c) {}
    int cost() override {
        return base->cost() + 30;
    }
};
int main() {
    Coffee* c = new BasicCoffee();       // Base coffee = 50
    c = new MilkDecorator(c);            // +20
    c = new SugarDecorator(c);           // +10
    c = new CreamDecorator(c);           // +30
    cout << "Total Coffee Cost: " << c->cost() << endl;
    delete c;
   return 0;
}
/*
Total Coffee Cost: 110
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
3. Composite
Tree structure (files & folders).

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
// Component
class FileSystem {
  public:
    virtual void show(int indent = 0) = 0;
    virtual ~FileSystem() = default;
};
// Leaf
class File : public FileSystem {
    string name;
  public:
    File(string n) : name(n) {}
    void show(int indent = 0) override {
        cout << string(indent, ' ') << "- File: " << name << endl;
    }
};
// Composite
class Folder : public FileSystem {
    string name;
    vector<unique_ptr<FileSystem>> children;
  public:
    Folder(string n) : name(n) {}
    void add(unique_ptr<FileSystem> fs) {
        children.push_back(move(fs));
    }
    void show(int indent = 0) override {
        cout << string(indent, ' ') << "+ Folder: " << name << endl;
        for (auto& c : children)
            c->show(indent + 4);
    }
};
// Usage
int main() {
    auto root = make_unique<Folder>("Root");

    root->add(make_unique<File>("readme.txt"));
    root->add(make_unique<File>("hello.cpp"));

    auto images = make_unique<Folder>("Images");
    images->add(make_unique<File>("photo1.png"));
    images->add(make_unique<File>("photo2.jpg"));

    auto docs = make_unique<Folder>("Docs");
    docs->add(make_unique<File>("resume.pdf"));
    docs->add(make_unique<File>("notes.txt"));
    
    root->add(move(images));
    root->add(move(docs));
    root->show();
  return 0;
}
/*
+ Folder: Root
    - File: readme.txt
    - File: hello.cpp
    + Folder: Images
        - File: photo1.png
        - File: photo2.jpg
    + Folder: Docs
        - File: resume.pdf
        - File: notes.txt
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
4. Facade
Simplify complex subsystems.

#include <iostream>
using namespace std;
// Subsystem 1
class CPU {
  public:
    void freeze() { cout << "CPU: Freezing\n"; }
    void jump(long position) { cout << "CPU: Jumping to " << position << "\n"; }
    void execute() { cout << "CPU: Executing\n"; }
};
// Subsystem 2
class Memory {
  public:
    void load(long position, string data) {
        cout << "Memory: Loading data '" << data
             << "' at position " << position << "\n";
    }
};
// Subsystem 3
class HardDisk {
  public:
    string read(long lba) {
        cout << "HardDisk: Reading block " << lba << "\n";
        return "OS_BOOT_DATA";
    }
};
// Facade
class ComputerFacade {
    CPU cpu;
    Memory memory;
    HardDisk disk;
  public:
    void start() {
        cout << "=== Starting Computer ===\n";
        cpu.freeze();
        string data = disk.read(0);
        memory.load(100, data);
        cpu.jump(100);
        cpu.execute();
        cout << "=== Computer Started ===\n";
    }
};
// Client
int main() {
    ComputerFacade system;
    system.start();
   return 0;
}
/*
=== Starting Computer ===
CPU: Freezing
HardDisk: Reading block 0
Memory: Loading data 'OS_BOOT_DATA' at position 100
CPU: Jumping to 100
CPU: Executing
=== Computer Started ===
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
5. Proxy
Placeholder for expensive object (e.g., lazy loading).

#include <iostream>
#include <memory>
using namespace std;
// Subject interface
class Image {
  public:
    virtual void display() = 0;
    virtual ~Image() = default;
};
// Real Subject (expensive object)
class RealImage : public Image {
    string filename;
  public:
    RealImage(string file) : filename(file) {
        cout << "Loading image from disk: " << filename << endl;
    }
    void display() override {
        cout << "Displaying: " << filename << endl;
    }
};
// Proxy
class ImageProxy : public Image {
    string filename;
    unique_ptr<RealImage> realImage;   // lazy-loaded
  public:
    ImageProxy(string file) : filename(file) {}
    void display() override {
        if (!realImage) {
            cout << "Image not loaded yet. Creating RealImage...\n";
            realImage = make_unique<RealImage>(filename);
        }
        realImage->display();
    }
};
// Client code
int main() {
    Image* img = new ImageProxy("photo.png");

    cout << "Proxy created. But RealImage not loaded yet.\n\n";

    cout << "First display call:\n";
    img->display();   // loads and displays

    cout << "\nSecond display call:\n";
    img->display();   // already loaded → no cost
    delete img;
  return 0;
}
/*
Proxy created. But RealImage not loaded yet.

First display call:
Image not loaded yet. Creating RealImage...
Loading image from disk: photo.png
Displaying: photo.png

Second display call:
Displaying: photo.png
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
6. Bridge
Decouple abstraction from implementation.


#include <iostream>
#include <memory>
using namespace std;
// -------- Implementation Hierarchy --------
class Color {
  public:
    virtual string fill() = 0;
    virtual ~Color() = default;
};
class Red : public Color {
  public:
    string fill() override { return "Red"; }
};
class Blue : public Color {
  public:
    string fill() override { return "Blue"; }
};
// -------- Abstraction Hierarchy --------
class Shape {
  protected:
    shared_ptr<Color> color;   // Bridge: reference to implementation
  public:
    Shape(shared_ptr<Color> c) : color(c) {}
    virtual void draw() = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
  public:
    Circle(shared_ptr<Color> c) : Shape(c) {}
    void draw() override {
        cout << "Drawing Circle in " << color->fill() << endl;
    }
};
class Square : public Shape {
  public:
    Square(shared_ptr<Color> c) : Shape(c) {}
    void draw() override {
        cout << "Drawing Square in " << color->fill() << endl;
    }
};
// -------- Client Code --------
int main() {
    shared_ptr<Color> red = make_shared<Red>();
    shared_ptr<Color> blue = make_shared<Blue>();

    unique_ptr<Shape> c1 = make_unique<Circle>(red);
    unique_ptr<Shape> c2 = make_unique<Circle>(blue);
    unique_ptr<Shape> s1 = make_unique<Square>(red);

    c1->draw();
    c2->draw();
    s1->draw();
   return 0;
}
/*
Drawing Circle in Red
Drawing Circle in Blue
Drawing Square in Red
*/


/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
3 Behavioral Patterns
1. Observer Pattern
Event notification system.
Example
class Observer {
   public: 
     virtual void update(int val) = 0;
};
class Subject {
    int value;
    vector<Observer*> obs;
  public:
    void attach(Observer* o) { 
        obs.push_back(o);
     }
    void setValue(int v) {
        value = v;
        for (auto* o : obs) o->update(v);
    }
};


/* ------------------------------------------------- */
#include <iostream>
#include <vector>
using namespace std;

// ---------- Observer Interface ----------
class Observer {
public:
    virtual void update(int val) = 0;
    virtual ~Observer() = default;
};

// ---------- Subject ----------
class Subject {
    int value = 0;
    vector<Observer*> observers;
public:
    void attach(Observer* o) {
        observers.push_back(o);
    }

    void setValue(int v) {
        value = v;
        notifyAll();
    }

    void notifyAll() {
        for (auto* o : observers)
            o->update(value);
    }
};

// ---------- Concrete Observers ----------
class DisplayObserver : public Observer {
public:
    void update(int val) override {
        cout << "[Display] Value updated to " << val << endl;
    }
};

class LoggingObserver : public Observer {
public:
    void update(int val) override {
        cout << "[Log] New value = " << val << endl;
    }
};

// ---------- Client Code ----------
int main() {
    Subject subject;

    DisplayObserver d;
    LoggingObserver l;

    subject.attach(&d);
    subject.attach(&l);

    cout << "Setting value to 10:\n";
    subject.setValue(10);

    cout << "\nSetting value to 20:\n";
    subject.setValue(20);

    return 0;
}
/*
Setting value to 10:
[Display] Value updated to 10
[Log] New value = 10

Setting value to 20:
[Display] Value updated to 20
[Log] New value = 20
*/
/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */

2. Strategy
Algorithms encapsulated separately.
Example
class SortStrategy {
  public:
    virtual void sort(vector<int>&) = 0;
};
class QuickSort : public SortStrategy {
  public: 
    void sort(vector<int>& v) override { /* ... */ }
};
class Context {
    SortStrategy* s;
  public:
    Context(SortStrategy* st) : s(st) {}
    void doSort(vector<int>& v) { 
        s->sort(v);
     }
};


/* ------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// -------- Strategy Interface --------
class SortStrategy {
  public:
    virtual void sort(vector<int>& v) = 0;
    virtual ~SortStrategy() = default;
};
// -------- Concrete Strategy 1 --------
class QuickSort : public SortStrategy {
  public:
    void sort(vector<int>& v) override {
        cout << "Using QuickSort...\n";
        std::sort(v.begin(), v.end());
    }
};
// -------- Concrete Strategy 2 --------
class BubbleSort : public SortStrategy {
  public:
    void sort(vector<int>& v) override {
        cout << "Using BubbleSort...\n";
        for (size_t i = 0; i < v.size(); i++)
            for (size_t j = 0; j < v.size() - i - 1; j++)
                if (v[j] > v[j+1])
                    swap(v[j], v[j+1]);
    }
};
// -------- Concrete Strategy 3 --------
class ReverseSort : public SortStrategy {
  public:
    void sort(vector<int>& v) override {
        cout << "Using ReverseSort...\n";
        std::sort(v.begin(), v.end(), greater<int>());
    }
};
// -------- Context --------
class Context {
    SortStrategy* strategy;  
  public:
    Context(SortStrategy* s) : strategy(s) {}

    void setStrategy(SortStrategy* s) {  // allows switching at runtime
        strategy = s;
    }
    void doSort(vector<int>& v) {
        strategy->sort(v);
    }
};
// -------- Client --------
int main() {
    vector<int> data = {5, 2, 8, 1, 9};

    QuickSort q;
    BubbleSort b;
    ReverseSort r;

    Context ctx(&q);

    // First use QuickSort
    ctx.doSort(data);
    for (int x : data) cout << x << " ";
    cout << "\n\n";

    // Reset data
    data = {5, 2, 8, 1, 9};

    // Switch strategy to BubbleSort
    ctx.setStrategy(&b);
    ctx.doSort(data);
    for (int x : data) cout << x << " ";
    cout << "\n\n";

    // Switch strategy to ReverseSort
    ctx.setStrategy(&r);
    ctx.doSort(data);
    for (int x : data) cout << x << " ";
    cout << endl;

    return 0;
}
/*
Using QuickSort...
1 2 5 8 9 

Using BubbleSort...
1 2 5 8 9 

Using ReverseSort...
9 8 5 2 1
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
3. Command
Encapsulate actions as objects (Undo/Redo).


#include <iostream>
#include <stack>
#include <memory>
using namespace std;
// -------- Receiver --------
class Calculator {
    int value = 0;
  public:
    void add(int x) {
        value += x;
        cout << "Value = " << value << endl;
    }
    void subtract(int x) {
        value -= x;
        cout << "Value = " << value << endl;
    }
    int getValue() const { return value; }
};
// -------- Command Interface --------
class Command {
  public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};
// -------- Concrete Command: Add --------
class AddCommand : public Command {
    Calculator& calc;
    int value;
  public:
    AddCommand(Calculator& c, int v) : calc(c), value(v) {}
    void execute() override {
        calc.add(value);
    }
    void undo() override {
        calc.subtract(value);
    }
};
// -------- Concrete Command: Subtract --------
class SubtractCommand : public Command {
    Calculator& calc;
    int value;
  public:
    SubtractCommand(Calculator& c, int v) : calc(c), value(v) {}
    void execute() override {
        calc.subtract(value);
    }
    void undo() override {
        calc.add(value);
    }
};
// -------- Invoker: Manages Commands + Undo/Redo --------
class CommandManager {
    stack<unique_ptr<Command>> undoStack;
    stack<unique_ptr<Command>> redoStack;
  public:
    void executeCommand(unique_ptr<Command> cmd) {
        cmd->execute();
        undoStack.push(move(cmd));
        // Clear redo stack (new timeline)
        while (!redoStack.empty())
            redoStack.pop();
    }
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo.\n";
            return;
        }
        auto cmd = move(undoStack.top());
        undoStack.pop();
        cmd->undo();
        redoStack.push(move(cmd));
    }
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo.\n";
            return;
        }
        auto cmd = move(redoStack.top());
        redoStack.pop();
        cmd->execute();
        undoStack.push(move(cmd));
    }
};
// -------- Client --------
int main() {
    Calculator calc;
    CommandManager mgr;

    cout << "Performing commands...\n";

    mgr.executeCommand(make_unique<AddCommand>(calc, 10));
    mgr.executeCommand(make_unique<AddCommand>(calc, 5));
    mgr.executeCommand(make_unique<SubtractCommand>(calc, 3));

    cout << "\nUndo operations:\n";
    mgr.undo();
    mgr.undo();

    cout << "\nRedo operations:\n";
    mgr.redo();
    mgr.redo();

  return 0;
}
/*
Performing commands...
Value = 10
Value = 15
Value = 12

Undo operations:
Value = 15
Value = 10

Redo operations:
Value = 15
Value = 12
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
4. State
Change behavior based on state object.


#include <iostream>
#include <memory>
using namespace std;

// -------- State Interface --------
class State {
public:
    virtual void onEnter() = 0;
    virtual void handle() = 0;
    virtual ~State() = default;
};

// Forward declaration for context
class Door;

// -------- Concrete State 1: Locked --------
class LockedState : public State {
public:
    void onEnter() override {
        cout << "[State] Door is now LOCKED.\n";
    }

    void handle() override {
        cout << "Door is locked. Unlocking it...\n";
    }
};

// -------- Concrete State 2: Unlocked --------
class UnlockedState : public State {
public:
    void onEnter() override {
        cout << "[State] Door is now UNLOCKED.\n";
    }

    void handle() override {
        cout << "Door is unlocked. Locking it...\n";
    }
};

// -------- Context --------
class Door {
    unique_ptr<State> state;

public:
    Door(unique_ptr<State> initialState) : state(move(initialState)) {
        state->onEnter();
    }

    void setState(unique_ptr<State> newState) {
        state = move(newState);
        state->onEnter();
    }

    void pressButton() {
        state->handle();

        // Switch state after handling
        if (dynamic_cast<LockedState*>(state.get())) {
            setState(make_unique<UnlockedState>());
        } else {
            setState(make_unique<LockedState>());
        }
    }
};

// -------- Client --------
int main() {
    // Door starts locked
    Door door(make_unique<LockedState>());

    cout << "\nPressing button 1:\n";
    door.pressButton();

    cout << "\nPressing button 2:\n";
    door.pressButton();

    cout << "\nPressing button 3:\n";
    door.pressButton();

    return 0;
}
/*
[State] Door is now LOCKED.

Pressing button 1:
Door is locked. Unlocking it...
[State] Door is now UNLOCKED.

Pressing button 2:
Door is unlocked. Locking it...
[State] Door is now LOCKED.

Pressing button 3:
Door is locked. Unlocking it...
[State] Door is now UNLOCKED.
*/

/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
5. Iterator
Traversal mechanism for collections.

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
// -------- Iterator Interface --------
class Iterator {
  public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
    virtual ~Iterator() = default;
};
// -------- Aggregate (Collection) Interface --------
class IterableCollection {
  public:
    virtual unique_ptr<Iterator> createIterator() = 0;
    virtual ~IterableCollection() = default;
};
// -------- Concrete Collection --------
class NumberCollection : public IterableCollection {
    vector<int> data;
  public:
    void add(int v) { data.push_back(v); }
    // Give iterator access to private vector
    const vector<int>& getData() const { return data; }
    unique_ptr<Iterator> createIterator() override;
};
// -------- Concrete Iterator --------
class NumberIterator : public Iterator {
    const vector<int>& ref;
    size_t index = 0;
  public:
    NumberIterator(const vector<int>& r) : ref(r) {}
    bool hasNext() override {
        return index < ref.size();
    }
    int next() override {
        return ref[index++];
    }
};
// Factory method for iterator
unique_ptr<Iterator> NumberCollection::createIterator() {
    return make_unique<NumberIterator>(data);
}
// -------- Client Code --------
int main() {
    NumberCollection col;
    col.add(10);
    col.add(20);
    col.add(30);
    col.add(40);
    unique_ptr<Iterator> it = col.createIterator();
    cout << "Iterating through collection:\n";
    while (it->hasNext()) {
        cout << it->next() << " ";
    }
    cout << endl;
   return 0;
}
/*
Iterating through collection:
10 20 30 40
*/


/* ---------------------------------------------------------------------------------------------------------------------------------------------------- */
❌ Anti-Patterns in C++ (What NOT to Do)
Anti-patterns are common bad practices that cause design problems.

1. God Object
One class does “everything”.
Symptoms:
1000+ lines
Many responsibilities
Hard to test / maintain

Example:
class GameManager {
    // handles graphics, input, physics, sound, AI, networking...
};
Fix: Apply SRP (Single Responsibility Principle).
/* ------------------------------------------------------- */
❌ Bad Example — GOD OBJECT (Anti-Pattern)
One class doing EVERYTHING.

#include <iostream>
using namespace std;
class GameManager {   // ❌ GOD OBJECT
    // Too many responsibilities!
  public:
    // Graphics
    void render() { cout << "Rendering graphics...\n"; }
    // Input
    void handleInput() { cout << "Handling input...\n"; }
    // Physics
    void updatePhysics() { cout << "Updating physics...\n"; }
    // Sound
    void playSound() { cout << "Playing sound...\n"; }
    // AI
    void updateAI() { cout << "Updating AI...\n"; }
    // Networking
    void syncNetwork() { cout << "Syncing network...\n"; }
    void gameLoop() {
        handleInput();
        updatePhysics();
        updateAI();
        render();
        playSound();
        syncNetwork();
    }
};
int main() {
    GameManager gm;
    gm.gameLoop();
  return 0;
}
/*
Handling input...
Updating physics...
Updating AI...
Rendering graphics...
Playing sound...
Syncing network...
*/

Problems:
Handles graphics, physics, input, audio, AI, networking…
Changes in one area break others.
Impossible to test.
Hard to extend or maintain.

✅ GOOD Example — After Applying SRP (Fix the God Object)
Split responsibilities into separate classes.

#include <iostream>
using namespace std;
// ----------------------
// Separate Responsibilities
// ----------------------
class InputHandler {
  public:
    void handle() { cout << "Handling input...\n"; }
};
class PhysicsEngine {
  public:
    void update() { cout << "Updating physics...\n"; }
};
class AIEngine {
  public:
    void update() { cout << "Updating AI...\n"; }
};
class Renderer {
  public:
    void render() { cout << "Rendering graphics...\n"; }
};
class SoundSystem {
  public:
    void play() { cout << "Playing sound...\n"; }
};
class NetworkManager {
  public:
    void sync() { cout << "Syncing network...\n"; }
};
// ----------------------
// Facade-like Game Loop Coordinator
// ----------------------
class Game {
    InputHandler input;
    PhysicsEngine physics;
    AIEngine ai;
    Renderer renderer;
    SoundSystem audio;
    NetworkManager network;
  public:
    void loop() {
        input.handle();
        physics.update();
        ai.update();
        renderer.render();
        audio.play();
        network.sync();
    }
};
int main() {
    Game game;
    game.loop();
  return 0;
}
/*
Handling input...
Updating physics...
Updating AI...
Rendering graphics...
Playing sound...
Syncing network...
*/

✔ Benefits:
Each class does only one job.
Much easier to test and maintain.
Classes become reusable.
System becomes modular and extendable.
/* ------------------------------------------------------- */

2. Spaghetti Code
Unstructured, deeply nested, unclear flow.
Symptoms:
Lots of goto, deeply nested loops, random globals

/* ------------------------------------------------------- */
❌ BAD Example — Spaghetti Code (Anti-Pattern)
Unstructured, nested, confusing, uses goto, random globals.

#include <iostream>
using namespace std;
// Random global variables
int score = 0;
int level = 1;
bool gameOver = false;
int main() {
    cout << "Start Game\n";
  start:
    // deeply nested logic (hard to follow)
    for (int i = 0; i < 3; i++) {
        cout << "Loop i = " << i << "\n";
        for (int j = 0; j < 2; j++) {
            cout << "  Loop j = " << j << "\n";
            if (i == 2 && j == 1) {
                cout << "    Increasing score...\n";
                score += 10;

                if (score > 15) {
                    cout << "    Score high... jumping using goto!\n";
                    goto nextLevel;   // ❌ Spaghetti jump
                }
            }
        }
    }
    cout << "Normal end of loops.\n";
  nextLevel:
    // More unstructured jumps and logic
    cout << "Welcome to next level!\n";
    level++;
    if (level < 3) {
        cout << "Repeating entire game using goto...\n";
        goto start;  // ❌ Another spaghetti jump
    }
    cout << "Game Over\n";
  return 0;
}
/* 
Start Game
Loop i = 0
  Loop j = 0
  Loop j = 1
Loop i = 1
  Loop j = 0
  Loop j = 1
Loop i = 2
  Loop j = 0
  Loop j = 1
    Increasing score...
Normal end of loops.
Welcome to next level!
Repeating entire game using goto...
Loop i = 0
  Loop j = 0
  Loop j = 1
Loop i = 1
  Loop j = 0
  Loop j = 1
Loop i = 2
  Loop j = 0
  Loop j = 1
    Increasing score...
    Score high... jumping using goto!
Welcome to next level!
Game Over
*/

❌ Problems:
Uses goto multiple times
Everything inside main()
Globals everywhere
Deeply nested for loops
Hard to test, debug, or extend

✅ GOOD Example — Structured Code (After Fixing Spaghetti Code)
We fix by:
✔ Breaking into functions
✔ Removing goto
✔ Removing nesting
✔ Encapsulating state inside a class

#include <iostream>
using namespace std;
class Game {
    int score = 0;
    int level = 1;
  public:
    void playLevel() {
        cout << "Playing level " << level << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                process(i, j);
            }
        }
    }
    void process(int i, int j) {
        if (i == 2 && j == 1) {
            score += 10;
            cout << "Scored! Total = " << score << "\n";
        }
    }
    bool shouldAdvance() const {
        return score > 15;
    }
    void nextLevel() {
        level++;
        cout << "Advancing to level " << level << "\n";
    }
    bool isGameComplete() const {
        return level >= 3;
    }
};
int main() {
    Game game;
    cout << "Start Game\n";
    while (true) {
        game.playLevel();

        if (game.shouldAdvance())
            game.nextLevel();

        if (game.isGameComplete())
            break;
    }
    cout << "Game Over\n";
  return 0;
}
/* 
Start Game
Playing level 1
Scored! Total = 10
Playing level 1
Scored! Total = 20
Advancing to level 2
Playing level 2
Scored! Total = 30
Advancing to level 3
Game Over
*/

✔ Improvements:
No goto
Clear game flow
No global variables
Logic broken into readable functions
No nested spaghetti logic


/* ------------------------------------------------------- */

3. Lava Flow
Dead code that no one removes.
Example:
int oldLoggingSystem = 0; // never used but kept



❌ BAD Example — Lava Flow (Anti-Pattern)

Dead, unused code remains in the system because developers are afraid to delete it.

#include <iostream>
using namespace std;
// ------------------------------
// ❌ Lava Flow: Dead Code
// ------------------------------
// Old, unused logging system — nobody removes it
int oldLoggingSystem = 0;
void oldLogMessage(const string& msg) {      // ❌ Dead function
    cout << "[OLD-LOG] " << msg << endl;
}
// Deprecated configuration flags
bool useOldRender = false;                   // ❌ Not used
bool debugLegacyAI = false;                  // ❌ Not used
// Old class kept for “future use”
class LegacyRenderer {                       // ❌ Completely unused
  public:
    void render() {
        cout << "Legacy render system...\n";
    }
};
// ------------------------------
// Real working code
// ------------------------------
void newLogMessage(const string& msg) {
    cout << "[NEW-LOG] " << msg << endl;
}
int main() {
    newLogMessage("Game started.");
    // Actual running logic
    for (int i = 0; i < 3; i++) {
        newLogMessage("Processing item " + to_string(i));
    }
    newLogMessage("Game Finished.");
  return 0;
}
/* 
[NEW-LOG] Game started.
[NEW-LOG] Processing item 0
[NEW-LOG] Processing item 1
[NEW-LOG] Processing item 2
[NEW-LOG] Game Finished.
*/

❌ Problems:
Old variables (oldLoggingSystem, useOldRender, debugLegacyAI)
Unused functions (oldLogMessage)
Unused classes (LegacyRenderer)
Legacy code left to rot → developers are scared to delete it
Codebase grows in size → harder to maintain, test, or understand

✅ GOOD Example — Cleaned Up (Lava Flow Removed)
Below is the same code with the lava removed:

#include <iostream>
using namespace std;
// All old dead code removed.
// Only clean, working code remains.
void logMessage(const string& msg) {
    cout << "[LOG] " << msg << endl;
}
int main() {
    logMessage("Game started.");
    for (int i = 0; i < 3; i++) {
        logMessage("Processing item " + to_string(i));
    }
    logMessage("Game Finished.");
  return 0;
}
/* 
[LOG] Game started.
[LOG] Processing item 0
[LOG] Processing item 1
[LOG] Processing item 2
[LOG] Game Finished.
*/

✔ Improvements:
Clean codebase
No dead variables or unused classes
Smaller, faster, easier to understand
Developers now trust the code

/* ------------------------------------------------------- */

4. Golden Hammer
Using one tool for everything.
Example:
Forcing Singleton everywhere
Using inheritance when composition is needed



❌ BAD Example — Golden Hammer (Anti-Pattern)
Developer uses Singleton as a hammer for every problem — logging, settings, database, audio, even where it hurts design.

#include <iostream>
using namespace std;
// ------------------------------
// ❌ Golden Hammer: EVERYTHING is a Singleton
// ------------------------------
class Logger {
  private:
    Logger() {}
  public:
    static Logger& get() {
        static Logger instance;
        return instance;
    }
    void log(const string& msg) {
        cout << "[LOG] " << msg << endl;
    }
};
class AudioManager {
  private:
    AudioManager() {}
  public:
    static AudioManager& get() {
        static AudioManager instance;
        return instance;
    }
    void playSound(const string& s) {
        cout << "Playing sound: " << s << endl;
    }
};
// ❌ Bad: Even simple classes are forced into Singleton
class GameSettings {
  private:
    GameSettings() {}
  public:
    static GameSettings& get() {          // Unnecessary Singleton
        static GameSettings instance;
        return instance;
    }
    int difficulty = 1;
};
// ❌ Bad: Game depends on global singletons everywhere
class Game {
  public:
    void start() {
        Logger::get().log("Game Started");
        AudioManager::get().playSound("Start.wav");
        int diff = GameSettings::get().difficulty;
        Logger::get().log("Difficulty = " + to_string(diff));
    }
};
int main() {
    Game g;
    g.start();
  return 0;
}
/* 
[LOG] Game Started
Playing sound: Start.wav
[LOG] Difficulty = 1
*/

❌ Why This Is Bad:
Too many singletons → hidden global state
Hard to test
Tight coupling everywhere
Inflexible, no dependency injection
You cannot replace components easily

✅ GOOD Example — Proper Design (Golden Hammer Fixed)
Use composition, interfaces, and dependency injection, NOT singletons everywhere.

#include <iostream>
using namespace std;
// ------------------------------
// Interfaces
// ------------------------------
class ILogger {
  public:
    virtual void log(const string&) = 0;
    virtual ~ILogger() = default;
};
class IAudio {
  public:
    virtual void play(const string&) = 0;
    virtual ~IAudio() = default;
};
// ------------------------------
// Concrete Components
// ------------------------------
class ConsoleLogger : public ILogger {
  public:
    void log(const string& msg) override {
        cout << "[LOG] " << msg << endl;
    }
};
class SimpleAudio : public IAudio {
  public:
    void play(const string& s) override {
        cout << "Playing: " << s << endl;
    }
};
class GameSettings {
  public:
    int difficulty = 1;
};
// ------------------------------
// Game uses composition, not Singletons
// ------------------------------
class Game {
    ILogger* logger;
    IAudio* audio;
    GameSettings settings;
  public:
    Game(ILogger* l, IAudio* a) : logger(l), audio(a) {}
    void start() {
        logger->log("Game started");
        audio->play("Start.wav");
        logger->log("Difficulty = " + to_string(settings.difficulty));
    }
};
int main() {
    ConsoleLogger logger;
    SimpleAudio audio;
    Game g(&logger, &audio);
    g.start();
  return 0;
}
/* 
[LOG] Game started
Playing: Start.wav
[LOG] Difficulty = 1
*/

✔ Why This Is Good:
No singletons → no hidden global state
Easy to test (mock ILogger & IAudio)
Game is decoupled from the concrete implementations
Components can be replaced at runtime
Follows composition over inheritance



/* ------------------------------------------------------- */

5. Copy-Paste Programming
Duplicating logic instead of reusing.


❌ BAD Example — Copy-Paste Programming (Anti-Pattern)
Developer repeats the same logic everywhere instead of reusing code.

#include <iostream>
#include <vector>
using namespace std;
// ❌ Repeated logic: sum of vector elements
int sumVector1(const vector<int>& v) {
    int s = 0;
    for (int i = 0; i < v.size(); i++)      // duplicated
        s += v[i];
    return s;
}
// ❌ Same logic copy-pasted again
int sumVector2(const vector<int>& v) {
    int s = 0;
    for (int i = 0; i < v.size(); i++)      // duplicated again
        s += v[i];
    return s;
}
// ❌ Same logic again for yet another function
int sumVector3(const vector<int>& v) {
    int s = 0;
    for (int i = 0; i < v.size(); i++)      // again!!
        s += v[i];
    return s;
}
int main() {
    vector<int> a = {1,2,3,4,5};
    cout << sumVector1(a) << endl;
    cout << sumVector2(a) << endl;
    cout << sumVector3(a) << endl;
  return 0;
}
/* 
15
15
15
*/
❌ Problems:
Logic repeated 3 times
If a bug appears → must fix in 3 places
Longer code, harder maintenance
Encourages inconsistent updates

✅ GOOD Example — Refactored (No Copy-Paste)
Use a single reusable function.

#include <iostream>
#include <vector>
using namespace std;
// Single reusable function
int sumVector(const vector<int>& v) {
    int s = 0;
    for (int x : v)
        s += x;
    return s;
}
int main() {
    vector<int> a = {1,2,3,4,5};
    cout << sumVector(a) << endl;
    cout << sumVector(a) << endl;  // reuse
    cout << sumVector(a) << endl;  // reuse
  return 0;
}
/* 
15
15
15
*/
✔ Improvements:
One function → zero duplication
Easy to maintain
Clean, readable
Reused logic

⭐ BONUS: Template Version (Reusable for any numeric type)
template<typename T>
T sumVector(const vector<T>& v) {
    T s = 0;
    for (const auto& x : v)
        s += x;
    return s;
}

Works for int, float, double, etc.
/* ------------------------------------------------------- */
#include <iostream>
#include <vector>
using namespace std;
// Template function: works for int, float, double, long long...
template<typename T>
T sumVector(const vector<T>& v) {
    T s = 0;
    for (const auto& x : v)
        s += x;
    return s;
}
int main() {
    // int vector
    vector<int> vi = {1, 2, 3, 4, 5};
    cout << "Sum of ints = " << sumVector(vi) << endl;
    // double vector
    vector<double> vd = {1.5, 2.5, 3.0};
    cout << "Sum of doubles = " << sumVector(vd) << endl;
    // float vector
    vector<float> vf = {0.1f, 0.2f, 0.3f};
    cout << "Sum of floats = " << sumVector(vf) << endl;
    // long long vector
    vector<long long> vll = {10000000000LL, 20000000000LL};
    cout << "Sum of long long = " << sumVector(vll) << endl;
  return 0;
}
/*
Sum of ints = 15
Sum of doubles = 7
Sum of floats = 0.6
Sum of long long = 30000000000
*/
/* ------------------------------------------------------- */

6. Premature Optimization
Optimizing before knowing the bottleneck.
Example:
Using custom allocators before profiling.




A complete C++ example demonstrating the Premature Optimization Anti-Pattern, followed by a clean, correct version.

The idea:
❌ Developer “optimizes” using custom allocators, pointer tricks, micro-loops…
without even profiling → slows the code or makes it unreadable.

❌ BAD Example — Premature Optimization (Anti-Pattern)
Developer tries to “optimize” before measuring anything.

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
// ❌ Developer creates a "super fast custom allocator"
//    even though the program has no performance issues.
class FastAllocator {
    char buffer[1024];
    int index = 0;
  public:
    void* allocate(size_t size) {
        if (index + size > 1024) return nullptr;
        void* p = buffer + index;
        index += size;
        return p;
    }
};
// ❌ Uses custom allocator for trivial operations
//    This makes code harder to maintain and possibly slower.
struct MyObject {
    int x;
    MyObject(int v) : x(v) {}
};
int main() {
    FastAllocator alloc;
    // ❌ Allocating objects manually (unnecessary complexity)
    void* mem1 = alloc.allocate(sizeof(MyObject));
    void* mem2 = alloc.allocate(sizeof(MyObject));
    MyObject* a = new(mem1) MyObject(10);   // placement new
    MyObject* b = new(mem2) MyObject(20);
    cout << "Values: " << a->x << ", " << b->x << endl;
    // ❌ Manual destruction required
    a->~MyObject();
    b->~MyObject();
    // ❌ Unnecessary pointer tricks & micro-optimizations
    int arr[5] = {1,2,3,4,5};
    int sum = 0;
    // Developer unrolls loop manually — premature
    sum += arr[0]; sum += arr[1]; sum += arr[2];
    sum += arr[3]; sum += arr[4];
    cout << "Sum = " << sum << endl;
  return 0;
}
/* 
Values: 10, 20
Sum = 15
*/

❌ Problems:
Custom allocator used even though unnecessary
Manual memory management → risk of bugs
Placement new / destructor calls → complex
Manual loop unrolling → unreadable
No profiling → performance not measured

✅ GOOD Example — Proper, Clean Code (No Premature Optimization)
Use normal C++ memory allocation until profiling shows a need to optimize.

#include <iostream>
#include <vector>
using namespace std;
struct MyObject {
    int x;
    MyObject(int v) : x(v) {}
};
int main() {
    // ✔ Use standard allocation
    vector<MyObject> objs;
    objs.emplace_back(10);
    objs.emplace_back(20);
    cout << "Values: " << objs[0].x << ", " << objs[1].x << endl;
    // ✔ Simple, readable loop
    vector<int> arr = {1,2,3,4,5};
    int sum = 0;
    for (int x : arr)
        sum += x;
    cout << "Sum = " << sum << endl;
  return 0;
}
/* 
Values: 10, 20
Sum = 15
*/

✔ Improvements:
Simple, readable code
Uses standard containers
No micro-optimizations
No unnecessary allocators
Maintainable and safe

⭐ Optional: Correct Optimization Approach
If later profiling shows slowdown:
Profile first (perf, VTune, Valgrind, gprof)
Identify real bottleneck
Apply targeted optimization
Measure gain
Keep code clean

/* ------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
// -----------------------------------------
// Step 1: Clean, simple implementation
// -----------------------------------------
long long sumSlow(const vector<int>& v) {
    long long sum = 0;
    for (int x : v) {
        sum += x;   // clean and readable
    }
   return sum;
}
// -----------------------------------------
// Step 2: Simulated optimized version
// (Only used AFTER profiling shows a bottleneck)
// -----------------------------------------
long long sumFast(const vector<int>& v) {
    // Pretend this is optimized using techniques 
    // such as loop unrolling, SIMD, etc.
    long long sum = 0;
    size_t i = 0;
    // loop unrolling (simple simulation)
    for (; i + 4 < v.size(); i += 4) {
        sum += v[i] + v[i+1] + v[i+2] + v[i+3];
    }
    // remaining elements
    while (i < v.size()) {
        sum += v[i++];
    }
   return sum;
}
// -----------------------------------------
// Helper: measure elapsed time of a function
// -----------------------------------------
template <typename Func>
void profile(const string& name, Func f, const vector<int>& v) {
    auto start = chrono::high_resolution_clock::now();
    long long result = f(v);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> ms = end - start;
    cout << name << " -> Result: " << result 
         << ", Time: " << ms.count() << " ms\n";
}
int main() {
    // Example data
    vector<int> data(10'000'000, 1);
    cout << "=== Correct Optimization Approach ===\n";
    // Step 1: Profile clean code
    profile("Slow (clean) version", sumSlow, data);
    // Step 2: Use optimized version ONLY if profiling shows bottleneck
    profile("Fast (optimized) version", sumFast, data);
    cout << "Optimization applied only after measurement.\n";
   return 0;
}
/*
=== Correct Optimization Approach ===
Slow (clean) version -> Result: 10000000, Time: 175.517 ms
Fast (optimized) version -> Result: 10000000, Time: 22.2501 ms
Optimization applied only after measurement.
*/
/* ------------------------------------------------------- */


7. Magic Numbers
Hardcoded values with no meaning.
if (x > 42)   // WHY 42??



❌ BAD Example — Magic Numbers (Anti-Pattern)
Hardcoded values appear in code without explanation.

#include <iostream>
using namespace std;
int main() {
    int x = 50;
    // ❌ Magic numbers — no meaning
    if (x > 42) {
        cout << "Value is above threshold!\n";
    }
    int bonus = x * 7;        // Why 7??
    int maxItems = 128;       // Why 128??
    cout << "Bonus = " << bonus << endl;
    cout << "Max items = " << maxItems << endl;
  return 0;
}
/* 
Value is above threshold!
Bonus = 350
Max items = 128
*/

❌ Problems:
Why is the threshold 42?
Why multiply by 7?
Why is max 128?
Nobody knows → confusing, unmaintainable
Hard to change later

✅ GOOD Example — Replacing Magic Numbers with Named Constants
Use const, constexpr, or enums.

#include <iostream>
using namespace std;
// Named constants with meaning
constexpr int THRESHOLD = 42;
constexpr int BONUS_MULTIPLIER = 7;
constexpr int MAX_ITEMS_ALLOWED = 128;
int main() {
    int x = 50;
    if (x > THRESHOLD) {
        cout << "Value is above threshold!\n";
    }
    int bonus = x * BONUS_MULTIPLIER;
    int maxItems = MAX_ITEMS_ALLOWED;
    cout << "Bonus = " << bonus << endl;
    cout << "Max items = " << maxItems << endl;
  return 0;
}
/* 
Value is above threshold!
Bonus = 350
Max items = 128
*/

✔ Improvements:
Constants have clear names
No confusion
Easy to modify
Makes intent obvious

⭐ BONUS: Using Enum for Related Constants
enum GameConfig {
    MAX_HEALTH = 100,
    MAX_MANA   = 50,
    START_LEVEL = 1
};
int main() {
    int health = MAX_HEALTH;
    int mana = MAX_MANA;
    cout << "Health = " << health << ", Mana = " << mana << endl;
}

/* ------------------------------------------------------- */
#include <iostream>
using namespace std;
// Enum for game configuration constants
enum GameConfig {
    MAX_HEALTH   = 100,
    MAX_MANA     = 50,
    START_LEVEL  = 1
};
// Function demonstrating the use of enum constants
void startGame() {
    int health = MAX_HEALTH;
    int mana   = MAX_MANA;
    cout << "Starting game...\n";
    cout << "Initial Health = " << health << endl;
    cout << "Initial Mana   = " << mana << endl;
    cout << "Starting Level = " << START_LEVEL << endl;
}
int main() {
    startGame();
    cout << "Game initialized using enum constants.\n";
  return 0;
}
/*
Starting game...
Initial Health = 100
Initial Mana   = 50
Starting Level = 1
Game initialized using enum constants.
*/
/* ------------------------------------------------------- */

8. Resource Leakage
Not using RAII → memory/file/socket leaks.
Bad:
FILE* f = fopen("a.txt", "r");

Fix:
ifstream file("a.txt");




❌ BAD Example — Resource Leakage (Anti-Pattern)
Developer uses raw resources but forgets to release them (FILE*, malloc, new, sockets, etc.).

#include <iostream>
#include <cstdio>      // fopen, fclose
#include <cstring>
using namespace std;
int main() {
    // ❌ BAD: manual resource management, risk of leaks
    FILE* f = fopen("data.txt", "r");
    if (!f) {
        cout << "Could not open file\n";
        return 1;
    }
    char buffer[100];
    // ❌ If an early return happens → f is never closed → resource leak
    if (fgets(buffer, sizeof(buffer), f)) {
        cout << "Read: " << buffer << endl;
        return 0;   // ❌ Forgot fclose(f)
    }
    // ❌ Forgot to close file in another path as well
    cout << "Done\n";
  return 0;       // Resource leak again
}
/* 
Could not open file
*/

❌ Problems:
File not closed on every path
Early return → leak
Hard to maintain
Manual cleanup
Same problem happens with sockets, new, malloc

✅ GOOD Example — RAII Fix (No Resource Leakage)
Use std::ifstream, std::unique_ptr, std::vector, smart resources.

#include <iostream>
#include <fstream>     // ifstream
using namespace std;
int main() {
    // ✔ RAII: ifstream automatically closes the file
    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Could not open file\n";
        return 1;
    }
    string line;
    if (getline(file, line)) {
        cout << "Read: " << line << endl;
        return 0;  // ✔ file auto-closes here
    }
    cout << "Done\n";
   return 0;      // ✔ file auto-closes here too
}
/* 
Could not open file
*/


✔ Improvements:
No manual fclose
Every return path automatically closes file
Zero leaks
Simpler, safer
/* -------------------------------------------- */
⭐ BONUS: RAII with dynamic memory
#include <memory>
using namespace std;
int main() {
    // unique_ptr handles deletion automatically
    unique_ptr<int> p = make_unique<int>(42);
    cout << *p << endl;
} 


/* -------------------------------------------- */
#include <iostream>
#include <memory>
using namespace std;
// A simple class to show RAII behavior
class Resource {
  public:
    Resource()  { cout << "Resource acquired\n"; }
    ~Resource() { cout << "Resource released\n"; }
    void use() { cout << "Using resource...\n"; }
};
// Custom deleter for demonstration
struct CustomDeleter {
    void operator()(Resource* r) const {
        cout << "Custom deleter called\n";
        delete r;
    }
};
int main() {
    // RAII: unique_ptr automatically deletes memory
    unique_ptr<int> p = make_unique<int>(42);
    cout << "Value = " << *p << endl;
    // RAII with class object
    {
        unique_ptr<Resource> res = make_unique<Resource>();
        res->use();
    } // res goes out of scope → destructor called automatically
    // RAII with custom deleter
    {
        unique_ptr<Resource, CustomDeleter> res2(new Resource());
        res2->use();
    } // custom deleter executes here
    cout << "Program ending.\n";
  return 0;
}
/*
Value = 42
Resource acquired
Using resource...
Resource released
Resource acquired
Using resource...
Custom deleter called
Resource released
Program ending.
*/
/* -------------------------------------------- */
⭐ BONUS: RAII with Files using a Custom Wrapper
class FileRAII {
    FILE* f;
  public:
    FileRAII(const char* name, const char* mode) {
        f = fopen(name, mode);
    }
    ~FileRAII() {
        if (f) fclose(f);
    }
    FILE* get() { return f; }
};
/* ------------------------------------------------------- */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
class FileRAII {
    FILE* f;
  public:
    FileRAII(const char* name, const char* mode) {
        f = fopen(name, mode);
        if (!f) {
            cout << "Failed to open file!\n";
        } else {
            cout << "File opened.\n";
        }
    }
    ~FileRAII() {
        if (f) {
            fclose(f);
            cout << "File closed.\n";
        }
    }
    FILE* get() { return f; }
};
int main() {
    // Open the file using RAII wrapper
    {
        FileRAII file("demo.txt", "w");
        FILE* fp = file.get();
        if (fp) {
            const char* msg = "Hello, RAII File Handling!";
            fwrite(msg, sizeof(char), strlen(msg), fp);
            cout << "Data written to file.\n";
        }
    } 
    // file goes out of scope → automatically closed
    cout << "Program finished.\n";
   return 0;
}
/*
Failed to open file!
Program finished.
*/
/* ------------------------------------------------------- */

9. Overusing Inheritance
Using inheritance instead of composition.


❌ BAD Example — Overusing Inheritance (Anti-Pattern)
Developer uses inheritance for everything, even when classes do not share true “is-a” relationships.

#include <iostream>
using namespace std;
// ❌ BAD: Using inheritance just to reuse code
class Engine {
  public:
    void start() {
        cout << "Engine starting...\n";
    }
};
// ❌ BAD: A Car "is-a" Engine? NO! → Wrong inheritance
class Car : public Engine {
  public:
    void drive() {
        cout << "Car driving...\n";
    }
};
// ❌ BAD: A Truck "is-a" Engine? NO!
class Truck : public Engine {
  public:
    void loadCargo() {
        cout << "Truck loading cargo...\n";
    }
};
int main() {
    Car c;
    c.start();   // inherited
    c.drive();

    Truck t;
    t.start();   // inherited
    t.loadCargo();
   return 0;
}
/* 
Engine starting...
Car driving...
Engine starting...
Truck loading cargo...
*/

❌ Problems:
Wrong relationship: Car is NOT an Engine
Violates SOLID (Liskov Substitution)
Forces API inheritance where it doesn’t belong
Base class changes → breaks all derived types

✅ GOOD Example — Use Composition Instead of Inheritance
Use “Car has-a Engine”, not “Car is-a Engine”.

#include <iostream>
using namespace std;
// Engine is a reusable component
class Engine {
  public:
    void start() {
        cout << "Engine starting...\n";
    }
};
// Vehicle types *compose* an engine
class Car {
    Engine engine;           // ✔ composition
  public:
    void start()  { engine.start(); }
    void drive()  { cout << "Car driving...\n"; }
};
class Truck {
    Engine engine;           // ✔ composition
  public:
    void start()     { engine.start(); }
    void loadCargo() { cout << "Truck loading cargo...\n"; }
};
int main() {
    Car c;
    c.start();
    c.drive();

    Truck t;
    t.start();
    t.loadCargo();
  return 0;
}
/* 
Engine starting...
Car driving...
Engine starting...
Truck loading cargo...
*/

✔ Improvements:
Car has an Engine → correct relationship
Engine changes do NOT break Car or Truck
Better encapsulation
Flexible: you can swap engines (dependency injection)
SOLID-compliant


⭐ BONUS: Composition with Dependency Injection
class Car {
    Engine* engine;      // pointer allows swapping engines
   public:
    Car(Engine* e) : engine(e) {}
    void start() { engine->start(); }
};


/* ------------------------------------------------------- */
#include <iostream>
using namespace std;
// ----- Engine Interface -----
class Engine {
  public:
    virtual void start() = 0;
    virtual ~Engine() {}
};
// ----- Concrete Engine 1 -----
class PetrolEngine : public Engine {
  public:
    void start() override {
        cout << "Petrol Engine starting... Vroom!\n";
    }
};
// ----- Concrete Engine 2 -----
class ElectricEngine : public Engine {
  public:
    void start() override {
        cout << "Electric Engine starting... Whirrr!\n";
    }
};
// ----- Car using Composition + Dependency Injection -----
class Car {
    Engine* engine;  // Composition with pointer → allows dynamic engine selection
  public:
    Car(Engine* e) : engine(e) {}
    void start() { 
        engine->start(); 
    }
};
// ----- Main -----
int main() {
    PetrolEngine pEngine;
    ElectricEngine eEngine;
    Car car1(&pEngine);   // Inject Petrol Engine
    Car car2(&eEngine);   // Inject Electric Engine
    car1.start();
    car2.start();
  return 0;
}
/* 
Petrol Engine starting... Vroom!
Electric Engine starting... Whirrr!
*/

/* ------------------------------------------------------- */

10. Poltergeist Classes
Classes created only to call a single function then disappear.



❌ Bad Example — Poltergeist Class
A “poltergeist” (or “gypsy”) class is created to do one tiny job and immediately disappears.

#include <iostream>
using namespace std;
// Poltergeist class — does almost nothing
class TempValidator {
  public:
    bool validate(int v) {
        return (v >= 0 && v <= 100);
    }
};
// Another class unnecessarily using a short-lived helper
class Processor {
  public:
    void process(int value) {
        TempValidator tv; // created only to call one function
        if (tv.validate(value))
            cout << "Valid!\n";
        else
            cout << "Invalid!\n";
    }
};
int main() {
    Processor p;
    p.process(50);
  return 0;
}
/* 
Valid!
*/

❗ Problem
TempValidator adds no state
No lifecycle
Used only once
Only wraps a tiny function → unnecessary abstraction

✅ Good Example — Remove Poltergeist
Replace the temporary one-shot class with:
A free function, or
A static function inside Processor, or
A reusable utility class (if needed)
✔ Using a simple helper function (best fix)

#include <iostream>
using namespace std;
inline bool validate(int v) {
    return (v >= 0 && v <= 100);
}
class Processor {
  public:
    void process(int value) {
        if (validate(value))
            cout << "Valid!\n";
        else
            cout << "Invalid!\n";
    }
};
int main() {
    Processor p;
    p.process(50);
   return 0;
}
/* 
Valid!
*/

✔ Alternative: If validation must be part of Processor
class Processor {
  private:
    static bool validate(int v) {
        return (v >= 0 && v <= 100);
    }
  public:
    void process(int value) {
        if (validate(value))
            cout << "Valid!\n";
        else
            cout << "Invalid!\n";
    }
};

/* ------------------------------------------------------- */
#include <iostream>
using namespace std;
class Processor {
  private:
    static bool validate(int v) {
        return (v >= 0 && v <= 100);
    }
  public:
    void process(int value) {
        if (validate(value))
            cout << "Valid!\n";
        else
            cout << "Invalid!\n";
    }
};
int main() {
    Processor p;
    p.process(50);   // Valid
    p.process(-10);  // Invalid
   return 0;
}
/*
Valid!
Invalid!
*/

/* ---------------------------------------------------------- */