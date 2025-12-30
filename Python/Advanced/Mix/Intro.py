1️⃣ Class & Object
Concept
Class → Blueprint
Object → Instance of class

class Person:
    def say_hello(self):
        print("Hello")

def main():
    p = Person()   # object
    p.say_hello()

if __name__ == "__main__":
    main()

"""
Output
Hello
"""



#int sum using a parameterized function
class Calculator:
    def add(self, a, b):
        sum = a + b
        print("Sum:", sum)

def main():
    c = Calculator()   # object
    c.add(5,10)

if __name__ == "__main__":
    main()

"""
Output
Sum: 15
"""


2️⃣ Constructor (__init__)
class Person:
    def __init__(self, name):
        self.name = name

    def show(self):
        print(self.name)

def main():
    p = Person("Alice")
    p.show()

if __name__ == "__main__":
    main()

"""
Output
Alice
"""




3️⃣ Destructor (__del__)
⚠ Not deterministic (GC-based)

class Demo:
    def __del__(self):
        print("Destructor called")

def main():
    obj = Demo()
    del obj

if __name__ == "__main__":
    main()

"""
Output
Destructor called
"""



#int sum using a default function, passing parameters to the constructor
class Calculator:
    def add(self, a, b):
        sum = a + b
        print("Sum:", sum)
    
    def __init__(self):
        print("constructor called")
    
    def __del__(self):
        print("destructor called")

def main():
    c = Calculator()   # object
    c.add(5.5,10)

if __name__ == "__main__":
    main()

"""
Output
constructor called
Sum: 15.5
destructor called
"""



class Calculator:
    def __init__(self, a, b):
        self.a = a
        self.b = b
        print("constructor called")
    
    def __del__(self):
        print("destructor called")
    
    def show(self):
        sum = self.a + self.b
        print("Sum: ", sum)

def main():
    c = Calculator(10, 20)   # object
    c.show()

if __name__ == "__main__":
    main()

"""
Output
constructor called
Sum: 30
destructor called
"""




4️⃣ Copying Objects (Python equivalent of Copy Constructor)
Shallow Copy
import copy

class Data:
    def __init__(self, x):
        self.x = x

def main():
    d1 = Data([1, 2])
    d2 = copy.copy(d1)
    d2.x.append(3)

    print(d1.x)
    print(d2.x)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3]
[1, 2, 3]
"""



Deep Copy (closest to C++ deep copy)
import copy

def main():
    a = [[1, 2], [3, 4]]
    b = copy.deepcopy(a)
    b[0].append(99)

    print(a)
    print(b)

if __name__ == "__main__":
    main()

"""
Output
[[1, 2], [3, 4]]
[[1, 2, 99], [3, 4]]
"""
❌ Move Constructor / Move Assignment



👉 Python does NOT have move semantics
Instead:
Reference reassignment
Garbage Collection

def main():
    a = [1, 2, 3]
    b = a
    a = None

    print(b)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3]
"""





5️⃣ Encapsulation (Public / Protected / Private)
#Public
class Demo:
    def __init__(self):
        self.x = 10

def main():
    d = Demo()
    print(d.x)

if __name__ == "__main__":
    main()

"""
Output
10
"""

#public
class Calculator:
    def __init__(self, a, b):
        self.a = a
        self.b = b
        print("Constructor called")

    def __del__(self):
        print("Destructor called!")
    
def main():
    c = Calculator(10,20)
    print("Sum:", c.a + c.b)

if __name__ == "__main__":
    main()

''' 
Output:
Constructor called
Sum: 30
Destructor called!
'''


#Protected (_var – convention)
class Demo:
    def __init__(self):
        self._x = 20

def main():
    d = Demo()
    print(d._x)

if __name__ == "__main__":
    main()

"""
Output
20
"""

#protected
class Calculator:
    def __init__(self, a, b):
        self._a = a
        self._b = b
        print("Constructor called")

    def __del__(self):
        print("Destructor called!")
    
def main():
    c = Calculator(10,20)
    print("Sum:", c._a + c._b)

if __name__ == "__main__":
    main()

''' 
Output:
Constructor called
Sum: 30
Destructor called!
'''



Private (__var – name mangling)
class Demo:
    def __init__(self):
        self.__x = 30

def main():
    d = Demo()
    print(d._Demo__x)

if __name__ == "__main__":
    main()

"""
Output
30
"""


#private
class Calculator:
    def __init__(self, a, b):
        self.__a = a
        self.__b = b
        print("Constructor called")

    def __del__(self):
        print("Destructor called!")
    
def main():
    c = Calculator(10,20)
    print("Sum:", c._Calculator__a + c._Calculator__b)

if __name__ == "__main__":
    main()

''' 
Output:
Constructor called
Sum: 30
Destructor called!
'''


6️⃣ Inheritance
class Animal:
    def speak(self):
        print("Animal speaks")

class Dog(Animal):
    def bark(self):
        print("Dog barks")

def main():
    d = Dog()
    d.speak()
    d.bark()

if __name__ == "__main__":
    main()

"""
Output
Animal speaks
Dog barks
"""





7️⃣ Polymorphism (Method Overriding)
class Shape:
    def area(self):
        print("Unknown")

class Square(Shape):
    def area(self):
        print("Square area")

def main():
    s = Square()
    s.area()

if __name__ == "__main__":
    main()

"""
Output
Square area
"""





8️⃣ Function Hiding (Method Overriding)
class A:
    def show(self):
        print("A")

class B(A):
    def show(self):
        print("B")

def main():
    obj = B()
    obj.show()

if __name__ == "__main__":
    main()

"""
Output
B
"""




9️⃣ Data Hiding
class Bank:
    def __init__(self):
        self.__balance = 1000

    def get_balance(self):
        return self.__balance

def main():
    b = Bank()
    print(b.get_balance())

if __name__ == "__main__":
    main()

"""
Output
1000
"""






🔟 Abstraction (ABC)
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Circle(Shape):
    def area(self):
        print("Circle area")

def main():
    c = Circle()
    c.area()

if __name__ == "__main__":
    main()

"""
Output
Circle area
"""






1️⃣1️⃣ Decorators
def my_decorator(func):
    def wrapper():
        print("Before")
        func()
        print("After")
    return wrapper

@my_decorator
def hello():
    print("Hello")

def main():
    hello()

if __name__ == "__main__":
    main()

"""
Output
Before
Hello
After
"""







1️⃣2️⃣ Threading
import threading

def task():
    print("Task running")

def main():
    t = threading.Thread(target=task)
    t.start()
    t.join()

if __name__ == "__main__":
    main()

"""
Output
Task running
"""







1️⃣3️⃣ Memory Management
import sys

def main():
    x = [1, 2, 3]
    print(sys.getsizeof(x))

if __name__ == "__main__":
    main()

"""
Output
(implementation dependent, e.g. 88)
"""






1️⃣4️⃣ Modules
import math

def main():
    print(math.sqrt(16))

if __name__ == "__main__":
    main()

"""
Output
4.0
"""







1️⃣5️⃣ Optimization (List vs Generator)
def main():
    squares = (i*i for i in range(5))
    print(list(squares))

if __name__ == "__main__":
    main()

"""
Output
[0, 1, 4, 9, 16]
"""






1️⃣6️⃣ Templates ❌ (C++ only)
👉 Python equivalent = Generics via duck typing

def add(a, b):
    return a + b

def main():
    print(add(2, 3))
    print(add("Hi ", "Python"))

if __name__ == "__main__":
    main()

"""
Output
5
Hi Python
"""





1️⃣7️⃣ File Handling
def main():
    with open("file.txt", "w") as f:
        f.write("Advanced Python")

    with open("file.txt", "r") as f:
        print(f.read())

if __name__ == "__main__":
    main()

"""
Output
Advanced Python
"""




1️⃣8️⃣ Exception Handling
def main():
    try:
        x = int("abc")
    except ValueError:
        print("Error occurred")
    finally:
        print("Done")

if __name__ == "__main__":
    main()

"""
Output
Error occurred
Done
"""
