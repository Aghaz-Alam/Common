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