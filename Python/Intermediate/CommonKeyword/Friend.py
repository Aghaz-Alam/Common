🔷 What is a Friend in C++?

In C++:
friend allows outside functions or classes to access private members
Breaks encapsulation intentionally

Python approach:
No strict private

Uses:
_protected (convention)
__private (name mangling)
Explicit getter / controlled access





1️⃣ Friend Function (Python Equivalent)
🔹 C++ idea
friend void show(Student&);

🔹 Python Equivalent
✔ A normal function can access object data
✔ Even private data (via name mangling)

class Student:
    def __init__(self, name, marks):
        self.__marks = marks   # private variable
        self.name = name

# friend-like function
def show_details(obj):
    print("Name:", obj.name)
    print("Marks:", obj._Student__marks)  # name mangling access

def main():
    s = Student("Alex", 90)
    show_details(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Name: Alex
Marks: 90

📌 Explanation
No friend keyword
Function accesses private data using name mangling
This acts like a friend function
"""





2️⃣ Friend Class (Python Equivalent)
🔹 C++ idea
friend class Teacher;

🔹 Python Equivalent
✔ One class explicitly accesses another class’s internals

class Student:
    def __init__(self, marks):
        self.__marks = marks

class Teacher:
    def show_marks(self, student):
        print("Student marks:", student._Student__marks)

def main():
    s = Student(85)
    t = Teacher()
    t.show_marks(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Student marks: 85

📌 Teacher behaves like a friend class
"""




3️⃣ Mutual Friendship (Two Classes Access Each Other)
🔹 C++ idea
class A { friend class B; };
class B { friend class A; };



🔹 Python Equivalent
✔ Both classes access each other’s private members

class A:
    def __init__(self, value):
        self.__value = value

    def show_from_b(self, b):
        print("A accessing B:", b._B__data)

class B:
    def __init__(self, data):
        self.__data = data

    def show_from_a(self, a):
        print("B accessing A:", a._A__value)

def main():
    a = A(10)
    b = B(20)

    a.show_from_b(b)
    b.show_from_a(a)

if __name__ == "__main__":
    main()

""" 
🖥 Output
A accessing B: 20
B accessing A: 10

📌 Mutual friendship achieved via name mangling
"""



4️⃣ Friend Function Using Protected Members (Recommended Python Style)
⚠️ Pythonic way → use _protected instead of private

class Student:
    def __init__(self, marks):
        self._marks = marks   # protected (convention)

def show_marks(student):
    print("Marks:", student._marks)

def main():
    s = Student(95)
    show_marks(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Marks: 95

📌 This is the preferred Python approach
"""

5️⃣ Why Python Has No friend Keyword (Interview Answer)
✔ Python philosophy: “We are all consenting adults here”
✔ No strict access restriction
✔ Trust the developer
✔ Access is by convention, not enforcement