1️⃣ Singleton Pattern
Use Case
Ensure only one instance exists (DB, Logger).

class Singleton:
    _instance = None
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

def main():
    a = Singleton()
    b = Singleton()
    print(a is b)

if __name__ == "__main__":
    main()

"""
Output
True
"""

2️⃣ Factory Pattern
Use Case
Create objects without specifying exact class.

class Dog:
    def speak(self):
        return "Bark"

class Cat:
    def speak(self):
        return "Meow"

class AnimalFactory:
    @staticmethod
    def create(animal):
        if animal == "dog":
            return Dog()
        if animal == "cat":
            return Cat()

def main():
    pet = AnimalFactory.create("dog")
    print(pet.speak())

if __name__ == "__main__":
    main()

"""
Output
Bark
"""

3️⃣ Builder Pattern
Use Case
Step-by-step object creation.

class Car:
    def __init__(self):
        self.parts = []

    def add(self, part):
        self.parts.append(part)

    def show(self):
        print(self.parts)

class CarBuilder:
    def build_engine(self, car):
        car.add("Engine")

    def build_wheels(self, car):
        car.add("Wheels")

def main():
    car = Car()
    builder = CarBuilder()
    builder.build_engine(car)
    builder.build_wheels(car)
    car.show()

if __name__ == "__main__":
    main()

"""
Output
['Engine', 'Wheels']
"""

🔹 STRUCTURAL PATTERNS
4️⃣ Adapter Pattern
Use Case
Make incompatible interfaces work together.

class OldSystem:
    def old_request(self):
        return "Old request"

class Adapter:
    def __init__(self, old):
        self.old = old

    def request(self):
        return self.old.old_request()

def main():
    old = OldSystem()
    adapter = Adapter(old)
    print(adapter.request())

if __name__ == "__main__":
    main()

"""
Output
Old request
"""

5️⃣ Decorator Pattern
Use Case
Add behavior dynamically.

def bold(func):
    def wrapper():
        return "<b>" + func() + "</b>"
    return wrapper

@bold
def text():
    return "Hello"

def main():
    print(text())

if __name__ == "__main__":
    main()

"""
Output
<b>Hello</b>
"""

6️⃣ Proxy Pattern
Use Case
Control access to an object.

class RealService:
    def fetch(self):
        return "Data"

class Proxy:
    def __init__(self):
        self.service = RealService()

    def fetch(self):
        print("Checking access")
        return self.service.fetch()

def main():
    p = Proxy()
    print(p.fetch())

if __name__ == "__main__":
    main()

"""
Output
Checking access
Data
"""

🔹 BEHAVIORAL PATTERNS
7️⃣ Observer Pattern
Use Case
One-to-many notifications (event systems).

class Subject:
    def __init__(self):
        self.observers = []

    def attach(self, obs):
        self.observers.append(obs)

    def notify(self):
        for obs in self.observers:
            obs.update()

class Observer:
    def update(self):
        print("Observer notified")

def main():
    s = Subject()
    o1 = Observer()
    o2 = Observer()
    s.attach(o1)
    s.attach(o2)
    s.notify()

if __name__ == "__main__":
    main()

"""
Output
Observer notified
Observer notified
"""

8️⃣ Strategy Pattern
Use Case
Select algorithm at runtime.

def add(a, b):
    return a + b

def multiply(a, b):
    return a * b

class Calculator:
    def __init__(self, strategy):
        self.strategy = strategy

    def execute(self, a, b):
        return self.strategy(a, b)

def main():
    calc = Calculator(add)
    print(calc.execute(2, 3))

    calc.strategy = multiply
    print(calc.execute(2, 3))

if __name__ == "__main__":
    main()

"""
Output
5
6
"""

9️⃣ Command Pattern
Use Case
Encapsulate request as object.

class Light:
    def on(self):
        print("Light ON")

class Command:
    def execute(self):
        pass

class LightOn(Command):
    def __init__(self, light):
        self.light = light

    def execute(self):
        self.light.on()

def main():
    light = Light()
    cmd = LightOn(light)
    cmd.execute()

if __name__ == "__main__":
    main()

"""
Output
Light ON
"""

🔟 Iterator Pattern
Use Case
Custom iteration logic.

class Count:
    def __init__(self, limit):
        self.limit = limit

    def __iter__(self):
        self.num = 0
        return self

    def __next__(self):
        if self.num < self.limit:
            val = self.num
            self.num += 1
            return val
        raise StopIteration

def main():
    for i in Count(3):
        print(i)

if __name__ == "__main__":
    main()

"""
Output
0
1
2
"""