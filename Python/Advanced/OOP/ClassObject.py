🔷 1. Single Object
class Student:
    def __init__(self, name):
        self.name = name

    def show(self):
        print("Name:", self.name)

def main():
    s = Student("Alex")
    s.show()

if __name__ == "__main__":
    main()

🖥 Output
Name: Alex

🔷 2. Multiple Objects
class Student:
    def __init__(self, name):
        self.name = name

    def show(self):
        print(self.name)

def main():
    s1 = Student("Alice")
    s2 = Student("Bob")
    s1.show()
    s2.show()

if __name__ == "__main__":
    main()

🖥 Output
Alice
Bob

🔷 3. Array of Objects (List of Objects)
class Student:
    def __init__(self, name):
        self.name = name

    def show(self):
        print(self.name)

def main():
    students = [
        Student("Alice"),
        Student("Bob"),
        Student("Charlie")
    ]

    for s in students:
        s.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alice
Bob
Charlie

📌 C++: Student s[3];
📌 Python: List of objects
"""




🔷 4. Pointer Object (Python Reference)
⚠️ Python has no pointers like C++, but object references behave like pointers.

class Student:
    def __init__(self, name):
        self.name = name

    def show(self):
        print(self.name)

def main():
    s1 = Student("Alice")
    s2 = s1          # reference to same object
    s2.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alice

📌 Both s1 and s2 point to the same object
"""





🔷 5. Const Object (Read-only concept)
⚠️ Python has no const keyword
✔ Achieved using private variables + no setter

class Student:
    def __init__(self, name):
        self.__name = name   # private

    def show(self):
        print(self.__name)

def main():
    s = Student("Alex")
    s.show()
    # s.__name = "Bob"  # ❌ not allowed

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex
"""






🔷 6. Static Object / Static Variable
class Student:
    count = 0   # static variable

    def __init__(self):
        Student.count += 1

def main():
    s1 = Student()
    s2 = Student()
    s3 = Student()
    print("Total objects:", Student.count)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Total objects: 3
"""







🔷 7. Implicit and Explicit Object Call
class Student:
    def show(self):
        print("Hello Student")

def main():
    s = Student()

    # Implicit call
    s.show()

    # Explicit call
    Student.show(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello Student
Hello Student
"""





🔷 8. Function Object (Object as Argument)
class Student:
    def __init__(self, name):
        self.name = name

def display(obj):
    print(obj.name)

def main():
    s = Student("Alice")
    display(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alice
"""





🔷 9. Function Pointer (Python Equivalent)
⚠️ Python has no function pointers, but functions are objects.

def greet():
    print("Hello")

def main():
    func = greet   # function reference
    func()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello

📌 C++: function pointer
📌 Python: function reference
"""






🔷 10. Lambda Expression (Anonymous Function)
def main():
    add = lambda a, b: a + b
    print(add(5, 3))

if __name__ == "__main__":
    main()

""" 
🖥 Output
8
"""




🔷 11. Object Returned from Function
class Student:
    def __init__(self, name):
        self.name = name

def create_student():
    return Student("Alex")

def main():
    s = create_student()
    print(s.name)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex
"""





🔷 12. Object Comparison
class Student:
    def __init__(self, name):
        self.name = name

def main():
    s1 = Student("Alice")
    s2 = Student("Alice")

    print(s1 == s2)   # compares reference

if __name__ == "__main__":
    main()

""" 
🖥 Output
False
"""





🔷 13. __str__() Object Representation
class Student:
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return self.name

def main():
    s = Student("Alex")
    print(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex
"""







🔷 14. Object as Class Attribute
class Address:
    def __init__(self, city):
        self.city = city

class Student:
    def __init__(self, name, address):
        self.name = name
        self.address = address

def main():
    addr = Address("Delhi")
    s = Student("Alex", addr)
    print(s.name, s.address.city)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex Delhi

📌 Object inside another object (HAS-A relationship)
"""






🔷 15. Shallow Copy of Object
import copy

class Student:
    def __init__(self, name):
        self.name = name

def main():
    s1 = Student("Alice")
    s2 = copy.copy(s1)
    print(s1.name)
    print(s2.name)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alice
Alice
"""






🔷 16. Deep Copy of Object
import copy

class Student:
    def __init__(self, marks):
        self.marks = marks

def main():
    s1 = Student([90, 80])
    s2 = copy.deepcopy(s1)

    s1.marks.append(70)
    print(s1.marks)
    print(s2.marks)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[90, 80, 70]
[90, 80]
"""








🔷 17. Class Method
class Student:
    school = "ABC School"

    @classmethod
    def show_school(cls):
        print(cls.school)

def main():
    Student.show_school()

if __name__ == "__main__":
    main()

""" 
🖥 Output
ABC School
"""





🔷 18. Static Method
class MathUtil:
    @staticmethod
    def add(a, b):
        return a + b

def main():
    print(MathUtil.add(3, 4))

if __name__ == "__main__":
    main()

""" 
🖥 Output
7

📌 No self, no object needed
"""





🔷 19. Method Chaining
class Student:
    def set_name(self, name):
        self.name = name
        return self

    def set_age(self, age):
        self.age = age
        return self

    def show(self):
        print(self.name, self.age)

def main():
    s = Student()
    s.set_name("Alex").set_age(20).show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex 20
"""




🔷 20. Operator Overloading (==)
class Student:
    def __init__(self, marks):
        self.marks = marks

    def __eq__(self, other):
        return self.marks == other.marks

def main():
    s1 = Student(90)
    s2 = Student(90)
    print(s1 == s2)

if __name__ == "__main__":
    main()

""" 
🖥 Output
True
"""






🔷 21. Call Object Like Function (__call__)
class Greet:
    def __call__(self):
        print("Hello")

def main():
    g = Greet()
    g()   # object behaves like function

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello
"""






🔷 22. Object Lifetime (Constructor + Destructor)
class Test:
    def __init__(self):
        print("Object created")

    def __del__(self):
        print("Object destroyed")

def main():
    t = Test()
    print("Inside main")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Object created
Inside main
Object destroyed
"""







🔷 23. isinstance() – Object Type Check
class Student:
    pass

def main():
    s = Student()
    print(isinstance(s, Student))

if __name__ == "__main__":
    main()

""" 
🖥 Output
True
"""






🔷 24. Duck Typing (Polymorphism)
class Dog:
    def speak(self):
        print("Bark")

class Cat:
    def speak(self):
        print("Meow")

def make_sound(animal):
    animal.speak()

def main():
    make_sound(Dog())
    make_sound(Cat())

if __name__ == "__main__":
    main()

""" 
🖥 Output
Bark
Meow
"""






🔷 25. Dynamic Object Attributes
class Student:
    pass

def main():
    s = Student()
    s.name = "Alex"
    s.age = 20
    print(s.name, s.age)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex 20
"""








🔷 26. Object Deletion (del)
class Student:
    def __init__(self, name):
        self.name = name

def main():
    s = Student("Alex")
    print(s.name)
    del s
    # print(s.name)  # error

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex
"""





🔷 27. getattr() / setattr()
class Student:
    def __init__(self):
        self.name = "Alex"

def main():
    s = Student()
    print(getattr(s, "name"))
    setattr(s, "age", 20)
    print(s.age)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex
20
"""




🔷 28. Object Truth Value
class Student:
    def __bool__(self):
        return False

def main():
    s = Student()
    if s:
        print("True")
    else:
        print("False")

if __name__ == "__main__":
    main()

""" 
🖥 Output
False
"""