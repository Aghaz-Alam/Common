Ways We Can Define/Use Parent Classes in C++
Only mechanisms involving inheritance create parent–child relationships.

✔ Valid mechanisms
--> Single Inheritance
--> Multiple Inheritance
--> Multilevel Inheritance
--> Hierarchical Inheritance
--> Hybrid (Multiple + Multilevel) Inheritance
--> Virtual Inheritance (to solve the diamond problem)

❌ NOT ways to define a parent class
--> Threading
--> Recursion
--> Polymorphism
--> Templates (they allow generic programming, not parent–child relationship)



Single Inheritance
One parent → one child.
Diagram
Animal (parent)
   ↑
 Dog (child)

Code
#include <iostream>
using namespace std;

class Animal {
public:
    void eat() { cout << "Animal Eating\n"; }
};

class Dog : public Animal {
public:
    void bark() { cout << "Dog Barking\n"; }
};

int main() {
    Dog d;
    d.eat();   // inherited
    d.bark();
}





Multiple Inheritance
A child inherits from multiple parents.
Diagram
   Animal    Pet
      \      /
        \   /
         Dog

Code
#include <iostream>
using namespace std;

class Animal {
public:
    void eat() { cout << "Animal Eating\n"; }
};

class Pet {
public:
    void play() { cout << "Pet Playing\n"; }
};

class Dog : public Animal, public Pet {
public:
    void bark() { cout << "Dog Barking\n"; }
};

int main() {
    Dog d;
    d.eat();
    d.play();
    d.bark();
}







Multilevel Inheritance
Parent → Child → Grandchild.
Diagram
LivingBeing
     ↑
   Animal
     ↑
    Dog

Code
#include <iostream>
using namespace std;

class LivingBeing {
public:
    void live() { cout << "Living...\n"; }
};

class Animal : public LivingBeing {
public:
    void eat() { cout << "Eating...\n"; }
};

class Dog : public Animal {
public:
    void bark() { cout << "Barking...\n"; }
};

int main() {
    Dog d;
    d.live();
    d.eat();
    d.bark();
}





Hierarchical Inheritance
One parent → multiple children.
Diagram
         Animal
        /      \
     Dog       Cat

Code
#include <iostream>
using namespace std;

class Animal {
public:
    void eat() { cout << "Animal Eating\n"; }
};

class Dog : public Animal {
public:
    void bark() { cout << "Dog Barking\n"; }
};

class Cat : public Animal {
public:
    void meow() { cout << "Cat Meowing\n"; }
};

int main() {
    Dog d;
    Cat c;
    d.eat(); d.bark();
    c.eat(); c.meow();
}






Hybrid Inheritance (Combination)
Mix of multiple + multilevel.
Example: “Diamond Problem”
Diagram
      Animal
      /    \
 Worker   Pet
      \   /
       RobotDog

Code
#include <iostream>
using namespace std;

class Animal {
public:
    void eat() { cout << "Animal Eating\n"; }
};

class Worker : public Animal {
public:
    void work() { cout << "Dog Working\n"; }
};

class Pet : public Animal {
public:
    void play() { cout << "Pet Playing\n"; }
};

class RobotDog : public Worker, public Pet {
public:
    void beep() { cout << "RobotDog Beeping\n"; }
};

int main() {
    RobotDog rd;

    // rd.eat();  // ❌ Ambiguous: from both Worker and Pet

    rd.Worker::eat(); // ✔ Specify
    rd.Pet::eat();

    rd.work();
    rd.play();
    rd.beep();
}





Virtual Inheritance (solving the Diamond Problem)
Diagram
      Animal
       /  \
 virtual  virtual
     Worker  Pet
        \   /
       RobotDog

Code
#include <iostream>
using namespace std;

class Animal {
public:
    void eat() { cout << "Animal Eating\n"; }
};

class Worker : virtual public Animal {
public:
    void work() { cout << "Working\n"; }
};

class Pet : virtual public Animal {
public:
    void play() { cout << "Playing\n"; }
};

class RobotDog : public Worker, public Pet {
public:
    void beep() { cout << "Beeping\n"; }
};
int main() {
    RobotDog rd;

    rd.eat();  // ✔ No ambiguity
    rd.work();
    rd.play();
    rd.beep();
}








❌ Why "threading" & "recursion" are not ways to define a parent class
🔹 Threading
Threading allows functions to run concurrently using std::thread.
It has nothing to do with defining parent-child classes.

🔹 Recursion
Recursion is when a function calls itself.
Again, unrelated to inheritance.
Example (recursion):
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
This does not create parent classes.