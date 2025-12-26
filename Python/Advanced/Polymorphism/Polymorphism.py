🔷 1. Creating Interfaces and Using Them (Python way)
🔹 Concept
Python has no interface keyword like Java/C++
Uses Abstract Base Classes (ABC)
Enforces method implementation → polymorphism

✅ Program (Interface + Implementation)
from abc import ABC, abstractmethod

# Interface
class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

# Concrete class
class Square(Shape):
    def __init__(self, side):
        self.side = side

    def area(self):
        return self.side * self.side

def main():
    s = Square(4)
    print("Area:", s.area())

if __name__ == "__main__":
    main()

""" 
🖥 Output
Area: 16

📌 Key Point
Shape acts like an interface
Square must implement area()
"""





🔷 2. Defining Concrete Classes and Accessing Them (Runtime Polymorphism)
🔹 Concept
Same method name
Different class behavior
Accessed using base class reference

✅ Program
class Animal:
    def speak(self):
        print("Animal speaks")

class Dog(Animal):
    def speak(self):
        print("Dog barks")

class Cat(Animal):
    def speak(self):
        print("Cat meows")

def main():
    animals = [Dog(), Cat()]

    for a in animals:
        a.speak()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Dog barks
Cat meows

📌 Same function call → different behavior
"""





🔷 3. Casting Between Objects (C++ vs Python)
🔹 Concept
C++ → explicit casting needed
Python → no casting, uses duck typing


✅ Program (Base reference to derived object)
class Parent:
    def show(self):
        print("Parent class")

class Child(Parent):
    def show(self):
        print("Child class")

def main():
    p = Child()   # Parent reference, Child object
    p.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Child class


📌 Explanation
Python automatically calls Child’s method
No (Child*)p like C++
"""





🔷 4. Virtual Function (Python default behavior)
🔹 Concept
In Python, all methods are virtual by default
Method call depends on object type, not reference type

✅ Program
class Base:
    def display(self):
        print("Base display")

class Derived(Base):
    def display(self):
        print("Derived display")

def main():
    obj = Derived()
    obj.display()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Derived display

📌 No virtual keyword needed in Python
"""




🔷 5. Constructor Behavior in Polymorphism
🔹 Concept
Base class constructor does NOT auto-call
Must use super()

✅ Program
class Base:
    def __init__(self):
        print("Base constructor")

class Derived(Base):
    def __init__(self):
        super().__init__()
        print("Derived constructor")

def main():
    d = Derived()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Base constructor
Derived constructor

📌 Similar to C++ constructor chaining
"""






🔷 6. Destructor (dtor) Behavior in Polymorphism
🔹 Concept
Python uses garbage collection
Destructors are not deterministic
Order: Derived → Base

✅ Program
class Base:
    def __del__(self):
        print("Base destructor")

class Derived(Base):
    def __del__(self):
        print("Derived destructor")
        super().__del__()

def main():
    d = Derived()
    del d

if __name__ == "__main__":
    main()

""" 
🖥 Output
Derived destructor
Base destructor

📌 Similar to virtual destructor behavior in C++
"""






🔷 7. Interface + Multiple Implementations (Real Polymorphism)
from abc import ABC, abstractmethod

class Payment(ABC):
    @abstractmethod
    def pay(self, amount):
        pass

class CreditCard(Payment):
    def pay(self, amount):
        print(f"Paid {amount} using Credit Card")

class UPI(Payment):
    def pay(self, amount):
        print(f"Paid {amount} using UPI")

def main():
    payments = [CreditCard(), UPI()]

    for p in payments:
        p.pay(100)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Paid 100 using Credit Card
Paid 100 using UPI
"""





🔷 8. Duck Typing (Python-specific Polymorphism)
class Car:
    def move(self):
        print("Car moves")

class Person:
    def move(self):
        print("Person walks")

def travel(obj):
    obj.move()

def main():
    travel(Car())
    travel(Person())

if __name__ == "__main__":
    main()

""" 
🖥 Output
Car moves
Person walks

📌 “If it behaves like a duck, it’s a duck”
"""






🔷 9. Polymorphism via Function Arguments
class Circle:
    def area(self):
        return 10

class Square:
    def area(self):
        return 20

def print_area(shape):
    print(shape.area())

def main():
    print_area(Circle())
    print_area(Square())

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
20
"""