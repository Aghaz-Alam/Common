1️⃣ IS-A Relationship (Inheritance)
👉 One class inherits another
👉 Uses class Child(Parent)

# IS-A Relationship Example
class Vehicle:
    def show(self):
        print("This is a Vehicle")

class Car(Vehicle):  # Car IS-A Vehicle
    def display(self):
        print("This is a Car")

def main():
    c = Car()
    c.show()
    c.display()

if __name__ == "__main__":
    main()

""" 
🖥 Output
This is a Vehicle
This is a Car

📌 Explanation
Car is a Vehicle
Implemented using inheritance
"""






2️⃣ HAS-A Relationship (Composition – Strong Relationship)
👉 Object is created inside another object
👉 Owner controls lifetime of the object
👉 Example: Car owns Engine

# HAS-A (Composition)
class Engine:
    def __init__(self):
        print("Engine created")

    def start(self):
        print("Engine started")

class Car:
    def __init__(self):
        print("Car created")
        self.engine = Engine()  # Engine created inside Car (strong ownership)

    def drive(self):
        self.engine.start()
        print("Car is moving")

def main():
    c = Car()
    c.drive()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Car created
Engine created
Engine started
Car is moving


📌 Key Point
Engine cannot exist without Car
When Car is destroyed → Engine is destroyed
This is COMPOSITION
"""






3️⃣ HAS-A Relationship (Aggregation – Weak Relationship)
👉 Object is passed from outside
👉 Owner does not control lifetime
👉 Example: Car uses Engine but does not own it

# HAS-A (Aggregation)
class Engine:
    def start(self):
        print("Engine started")

class Car:
    def __init__(self, engine):
        self.engine = engine  # Engine passed from outside (weak ownership)

    def drive(self):
        self.engine.start()
        print("Car is moving")

def main():
    e = Engine()      # Engine exists independently
    c = Car(e)
    c.drive()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Engine started
Car is moving


📌 Key Point
Engine can exist without Car
Multiple cars can share same engine
This is AGGREGATION
"""