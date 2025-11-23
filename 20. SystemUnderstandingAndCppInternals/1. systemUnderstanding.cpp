System understanding & cpp internals
----------------------------------------
1. What is heap ?
2. What is stack trace ? what element / pointer used to represent stack.  ----------vvi
3. what concepts in c++ can be used for better memeory management
4. explain std move. how std move is implemented underneath.
5. design patterns and anti design patterns
6. design principles, SOLID





✅ 1. What is Heap?
The heap is a large region of memory used for dynamic allocation at runtime using:

new / delete
malloc / free
smart pointers (std::unique_ptr, std::shared_ptr)
containers that allocate internally (std::vector, std::string)

✔️ Characteristics
Slower than stack allocation
Memory is manually managed (or via smart pointers)
Size is large (depends on OS)
If not freed → memory leak

✔️ Example
int* p = new int(10);   // allocated on heap
cout << *p << endl;
delete p;              // must be deleted




✅ 2. What is a Stack Trace? What element/pointer represents stack?
A stack trace is a list of function calls that led to a specific point in the program (commonly printed during exceptions or crashes).

Example format:
main()
  ↓
f1()
  ↓
f2()
  ↓
crash

✔️ What represents the stack internally? (Very Important 🔥)
The stack is represented using:
1️⃣ Stack Pointer (SP / RSP)
Points to the top of the stack
Moves automatically during function calls and returns

2️⃣ Frame Pointer (FP / BP / RBP)
Points to the current function’s stack frame
Used for accessing parameters & local variables

3️⃣ Program Counter (PC / RIP)
Holds address of current instruction
Used for stack trace walking

✔️ How stack frames work (C++ example)
#include <iostream>
using namespace std;
void f2() {
    int x = 10;   // stored in stack frame of f2
    throw runtime_error("Error!");
}
void f1() {
    int y = 20;   // stored in f1's stack frame
    f2();
}
int main() {
    try {
        f1();
    }
    catch(const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
}


During exception, the stack trace unwinds:
f2 → f1 → main

✅ 3. Concepts in C++ for Better Memory Management
✔️ Core Techniques
RAII (Resource Acquisition Is Initialization)
Smart Pointers
Move Semantics
Allocators
Containers Instead of raw arrays
Avoiding new/delete

✔️ RAII Example
class File {
    FILE* f;
  public:
    File(const char* name){
        f = fopen(name, "w");
    }
    ~File(){
        fclose(f);  // auto cleanup
    }
};

✅ 4. Explain std::move. How is it implemented underneath?
✔️ What is std::move ?
std::move does NOT move anything.
It casts an object to an rvalue, enabling move constructor / move assignment.

✔️ Underlying Implementation (actual code from standard)
template <typename T>
typename remove_reference<T>::type&& move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}

Meaning:
std::move(x) → static_cast< T&& >(x )

this tells compiler:
✔️ treat x as a temporary → move is allowed
❌ NOT copy

✔️ Example showing the effect
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1,2,3};
    vector<int> v2 = std::move(v);   // move instead of copy
    cout << "v size: " << v.size() << endl;   // 0
    cout << "v2 size:" << v2.size() << endl;  // 3
}


✅ 5. Design Patterns + Code + When To Use
✔️ 1. Singleton
class Singleton {
    Singleton() {}
  public:
    static Singleton& instance() {
        static Singleton inst;
        return inst;
    }
};

✔️ 2. Factory
class Shape { public: virtual void draw() = 0; };
class Circle : public Shape { void draw() override { cout << "Circle\n"; } };
class ShapeFactory {
  public:
    static Shape* createCircle() { return new Circle(); }
};

✔️ 3. Strategy
class Strategy {
public:
    virtual int execute(int a, int b) = 0;
};

class Add : public Strategy {
public: int execute(int a,int b){ return a+b; }
};

class Context {
    Strategy* s;
public:
    Context(Strategy* s) : s(s) {}
    int doOp(int a,int b){ return s->execute(a,b); }
};

✔️ 4. Observer
class Observer {
public:
    virtual void update(int value)=0;
};

class Subject {
    vector<Observer*> obs;
    int data;
public:
    void add(Observer* o){ obs.push_back(o); }
    void setData(int d){
        data = d;
        for(auto o:obs) o->update(data);
    }
};

❌ Anti-Patterns
Spaghetti code → no structure
God Object → one class knows too much
Lava Flow → dead code left forever
Copy-Paste Programming
Magic numbers
Overengineering

✅ 6. SOLID Principles
S — Single Responsibility
One class = one reason to change.

O — Open/Closed
Open for extension, closed for modification.

L — Liskov Substitution
Child classes must replace parent without breaking code.

I — Interface Segregation
Prefer many small interfaces over one big one.

D — Dependency Inversion
High-level modules should depend on abstractions.

✔️ SOLID Example (short)
// S - Single Responsibility
class FileReader {
public: string read(string path);
};

// O - Open/Closed (extend writer without modifying FileWriter)
class Writer {
public: virtual void write(string)=0;
};
class ConsoleWriter : public Writer {
public: void write(string s) override { cout << s; }
};


