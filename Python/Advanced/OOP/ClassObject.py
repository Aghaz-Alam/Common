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