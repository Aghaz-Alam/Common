'''
11. Object-Oriented Programming (OOP)
🔹 Short Note
Class = blueprint
Object = instance of class
'''

#✅ Program
class Student:
    def __init__(self, name):
        self.name = name

    def display(self):
        print("Name:", self.name)

def main():
    s1 = Student("Alex")
    s1.display()

if __name__ == "__main__":
    main()


'''
🖥 Output
Name: Alex
'''



# class
class Student:
    def show(self):
        print("Student class")

def main():
    s = Student()
    s.show()

if __name__ == "__main__":
    main()

'''
🖥 Output
Student class
'''





# Class with constructor and destructor
class Student:
    def __init__(self, name):
        # Constructor: called when object is created
        self.name = name
        print(f"Constructor called: {self.name}")

    def show(self):
        print(f"Student name is {self.name}")

    def __del__(self):
        # Destructor: called when object is destroyed
        print(f"Destructor called: {self.name}")

def main():
    s = Student("Alice")  # Object creation
    s.show()
    del s  # Explicitly delete object (optional, destructor called automatically at program end)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Constructor called: Alice
Student name is Alice
Destructor called: Alice
"""





#1️⃣ Class with Constructor and Destructor
class Student:
    def __init__(self, name):
        self.name = name
        print(f"Constructor called: {self.name}")

    def show(self):
        print(f"Student name is {self.name}")

    def __del__(self):
        print(f"Destructor called: {self.name}")

def main():
    s = Student("Alice")
    s.show()
    del s

if __name__ == "__main__":
    main()

""" 
🖥 Output
Constructor called: Alice
Student name is Alice
Destructor called: Alice
"""




#2️⃣ Multiple Objects and Constructor
class Student:
    def __init__(self, name):
        self.name = name
        print(f"{self.name} created")

def main():
    s1 = Student("Alice")
    s2 = Student("Bob")
    print("Objects created successfully")

if __name__ == "__main__":
    main()


""" 
🖥 Output
Alice created
Bob created
Objects created successfully
"""





#3️⃣ Class Variable vs Instance Variable
class Student:
    school = "XYZ School"  # Class variable

    def __init__(self, name):
        self.name = name     # Instance variable

    def show(self):
        print(f"{self.name} studies in {Student.school}")

def main():
    s1 = Student("Alice")
    s2 = Student("Bob")
    s1.show()
    s2.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alice studies in XYZ School
Bob studies in XYZ School
"""



#class object
class Student:
    def __init__(self, name):
        self.name = name
    def show(self): 
        print(f"{self.name} created")

def main():
    s1 = Student("Alice")
    s2 = Student("Bob")
    s1.show()
    s2.show()
    print("Objects created successfully")

if __name__ == "__main__":
    main()


""" 
🖥 Output
Alice created
Bob created
Objects created successfully
"""


#4️⃣ Method Overriding (Inheritance)
class Parent:
    def greet(self):
        print("Hello from Parent")

class Child(Parent):
    def greet(self):
        print("Hello from Child")  # Overrides Parent method

def main():
    p = Parent()
    c = Child()
    p.greet()
    c.greet()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello from Parent
Hello from Child
"""

#5️⃣ Single Inheritance Example
class Parent:
    def show_parent(self):
        print("This is Parent class")

class Child(Parent):
    def show_child(self):
        print("This is Child class")

def main():
    c = Child()
    c.show_parent()
    c.show_child()

if __name__ == "__main__":
    main()

""" 
🖥 Output
This is Parent class
This is Child class
"""





#6️⃣ Multiple Inheritance Example
class A:
    def showA(self):
        print("Class A method")

class B:
    def showB(self):
        print("Class B method")

class C(A, B):
    def showC(self):
        print("Class C method")

def main():
    obj = C()
    obj.showA()
    obj.showB()
    obj.showC()

if __name__ == "__main__":
    main()


""" 
🖥 Output
Class A method
Class B method
Class C method
"""




#7️⃣ Object Counting (Using Class Variable)
class Student:
    count = 0  # Class variable

    def __init__(self, name):
        self.name = name
        Student.count += 1

def main():
    s1 = Student("Alice")
    s2 = Student("Bob")
    s3 = Student("Charlie")
    print(f"Total students: {Student.count}")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Total students: 3
"""






#8️⃣ Destructor Called Automatically
class Demo:
    def __init__(self, n):
        self.n = n
        print(f"Object {n} created")

    def __del__(self):
        print(f"Object {self.n} destroyed")

def main():
    d1 = Demo(1)
    d2 = Demo(2)
    print("Main finished")

if __name__ == "__main__":
    main()


""" 
🖥 Output
Object 1 created
Object 2 created
Main finished
Object 2 destroyed
Object 1 destroyed
"""





#9️⃣ Polymorphism (Same Method Different Classes)
class Cat:
    def speak(self):
        print("Meow")

class Dog:
    def speak(self):
        print("Bark")

def main():
    for animal in (Cat(), Dog()):
        animal.speak()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Meow
Bark
"""





#🔟 Using super() in Inheritance
class Parent:
    def __init__(self):
        print("Parent Constructor")

class Child(Parent):
    def __init__(self):
        super().__init__()  # Call Parent constructor
        print("Child Constructor")

def main():
    c = Child()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Parent Constructor
Child Constructor
"""










1️⃣ Encapsulation
class Student:
    def __init__(self, name, marks):
        self.name = name        # Public
        self.__marks = marks    # Private (encapsulated)

    def show(self):
        print(f"Name: {self.name}, Marks: {self.__marks}")

    def set_marks(self, marks):
        self.__marks = marks    # Setter method

def main():
    s = Student("Alice", 90)
    s.show()
    s.set_marks(95)
    s.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Name: Alice, Marks: 90
Name: Alice, Marks: 95
"""







2️⃣ Polymorphism
2a. Compile-time (Function Overloading)
⚠️ Python does not support traditional function overloading, but we can use default arguments:

class Calculator:
    def add(self, a, b=0, c=0):   # Single method handles multiple parameters
        return a + b + c

def main():
    calc = Calculator()
    print(calc.add(5))
    print(calc.add(5, 10))
    print(calc.add(5, 10, 15))

if __name__ == "__main__":
    main()

""" 
🖥 Output
5
15
30
"""






2b. Compile-time (Operator Overloading)

class Number:
    def __init__(self, value):
        self.value = value

    def __add__(self, other):   # Overloading +
        return Number(self.value + other.value)

    def display(self):
        print(self.value)

def main():
    n1 = Number(5)
    n2 = Number(10)
    n3 = n1 + n2
    n3.display()

if __name__ == "__main__":
    main()

""" 
🖥 Output
15
"""





2c. Run-time (Function Overriding)

class Parent:
    def greet(self):
        print("Hello from Parent")

class Child(Parent):
    def greet(self):
        print("Hello from Child")   # Overrides parent method

def main():
    p = Parent()
    c = Child()
    p.greet()
    c.greet()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello from Parent
Hello from Child
"""


2d. Run-time (Operator Overriding)

class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return f"Vector({self.x}, {self.y})"

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

def main():
    v1 = Vector(2, 3)
    v2 = Vector(5, 6)
    v3 = v1 + v2
    print(v3)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Vector(7, 9)
"""




3️⃣ Inheritance
3a. Single Inheritance

class Parent:
    def show_parent(self):
        print("This is Parent class")

class Child(Parent):
    def show_child(self):
        print("This is Child class")

def main():
    c = Child()
    c.show_parent()
    c.show_child()

if __name__ == "__main__":
    main()

""" 
🖥 Output
This is Parent class
This is Child class
"""






3b. Multilevel Inheritance

class GrandParent:
    def show_grandparent(self):
        print("GrandParent class")

class Parent(GrandParent):
    def show_parent(self):
        print("Parent class")

class Child(Parent):
    def show_child(self):
        print("Child class")

def main():
    c = Child()
    c.show_grandparent()
    c.show_parent()
    c.show_child()

if __name__ == "__main__":
    main()


""" 
🖥 Output
GrandParent class
Parent class
Child class
"""



3c. Multiple Inheritance

class A:
    def showA(self):
        print("Class A method")

class B:
    def showB(self):
        print("Class B method")

class C(A, B):
    def showC(self):
        print("Class C method")

def main():
    obj = C()
    obj.showA()
    obj.showB()
    obj.showC()

if __name__ == "__main__":
    main()


""" 
🖥 Output
Class A method
Class B method
Class C method
"""





3d. Hierarchical Inheritance

class Parent:
    def show(self):
        print("Parent class")

class Child1(Parent):
    def show1(self):
        print("Child1 class")

class Child2(Parent):
    def show2(self):
        print("Child2 class")

def main():
    c1 = Child1()
    c2 = Child2()
    c1.show()
    c1.show1()
    c2.show()
    c2.show2()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Parent class
Child1 class
Parent class
Child2 class
"""





3e. Hybrid Inheritance

class A:
    def showA(self):
        print("A class")

class B(A):
    def showB(self):
        print("B class")

class C(A):
    def showC(self):
        print("C class")

class D(B, C):
    def showD(self):
        print("D class")

def main():
    d = D()
    d.showA()
    d.showB()
    d.showC()
    d.showD()

if __name__ == "__main__":
    main()

""" 
🖥 Output
A class
B class
C class
D class
"""



4️⃣ Abstraction
4a. Virtual Function (Python: just overriding a method)

class Parent:
    def show(self):
        print("Parent show")

class Child(Parent):
    def show(self):   # Overrides parent (virtual function concept)
        print("Child show")

def main():
    p = Child()
    p.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Child show
"""



4b. Pure Virtual Function (Abstract Base Class)
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Square(Shape):
    def __init__(self, side):
        self.side = side
    def area(self):
        return self.side * self.side

def main():
    s = Square(5)
    print(f"Area: {s.area()}")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Area: 25
"""



4c. Interface (Using Abstract Base Class)
from abc import ABC, abstractmethod

class Drawable(ABC):
    @abstractmethod
    def draw(self):
        pass

class Circle(Drawable):
    def draw(self):
        print("Drawing Circle")

def main():
    c = Circle()
    c.draw()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Drawing Circle
"""






#5️⃣ Data Hiding / Function Hiding
class Test:
    def __init__(self):
        self.__a = 10      # Private variable

    def __show(self):       # Private function
        print("Private function", self.__a)

    def access(self):
        self.__show()       # Access inside class

def main():
    t = Test()
    t.access()             # Works
    # t.__show()           # Would cause error
    # print(t.__a)         # Would cause error

if __name__ == "__main__":
    main()

""" 
🖥 Output
Private function 10
"""