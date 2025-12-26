1️⃣ Normal Template Usage (Generic Function)
🔹 C++ Meaning
template<typename T>
T add(T a, T b);


🔹 Python Equivalent (Duck Typing)
def add(a, b):
    return a + b

def main():
    print(add(2, 3))          # int
    print(add(2.5, 3.5))      # float
    print(add("Hello ", "Python"))  # string

if __name__ == "__main__":
    main()

""" 
🖥 Output
5
6.0
Hello Python


📌 Python automatically works for any type that supports +
"""




2️⃣ Template Class (Generic Class)
🔹 Python Equivalent
class Box:
    def __init__(self, value):
        self.value = value

    def get(self):
        return self.value

def main():
    b1 = Box(10)
    b2 = Box("Python")

    print(b1.get())
    print(b2.get())

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
Python

📌 Acts like template<class T> in C++
"""





3️⃣ Template Specialization (Type-based behavior)
🔹 C++ Meaning
template<>
void func<int>(int x);


🔹 Python Equivalent → singledispatch
from functools import singledispatch

@singledispatch
def show(value):
    print("Generic value:", value)

@show.register(int)
def _(value):
    print("Integer value:", value)

@show.register(str)
def _(value):
    print("String value:", value)

def main():
    show(10)
    show("Hello")
    show(3.5)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Integer value: 10
String value: Hello
Generic value: 3.5

📌 This is template specialization in Python
"""




4️⃣ SFINAE (Substitution Failure Is Not An Error)
🔹 C++ Meaning
Enable a function only if type supports an operation

🔹 Python Equivalent → Duck Typing (try-except)
def length(obj):
    try:
        return len(obj)
    except TypeError:
        return "Object has no length"

def main():
    print(length([1, 2, 3]))
    print(length("Python"))
    print(length(10))

if __name__ == "__main__":
    main()

""" 
🖥 Output
3
6
Object has no length

📌 Python tries the operation instead of checking type
📌 This is runtime SFINAE
"""




🔹 SFINAE using hasattr
def call_show(obj):
    if hasattr(obj, "show"):
        obj.show()
    else:
        print("show() not supported")

class A:
    def show(self):
        print("A show")

class B:
    pass

def main():
    call_show(A())
    call_show(B())

if __name__ == "__main__":
    main()

""" 
🖥 Output
A show
show() not supported
"""






5️⃣ Metaprogramming (Code that writes code)
🔹 Decorator Example
def my_decorator(func):
    def wrapper():
        print("Before function")
        func()
        print("After function")
    return wrapper

@my_decorator
def say_hello():
    print("Hello")

def main():
    say_hello()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Before function
Hello
After function

📌 Function modified at runtime
"""







6️⃣ Metaprogramming using type() (Dynamic Class Creation)
def show(self):
    print("Dynamically created class")

MyClass = type("MyClass", (), {"show": show})

def main():
    obj = MyClass()
    obj.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Dynamically created class

📌 Python creates classes at runtime
"""






7️⃣ Metaprogramming using Metaclass (Advanced)
class MyMeta(type):
    def __new__(cls, name, bases, dct):
        dct["greet"] = lambda self: print("Hello from metaclass")
        return super().__new__(cls, name, bases, dct)

class Test(metaclass=MyMeta):
    pass

def main():
    t = Test()
    t.greet()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello from metaclass

📌 Used in frameworks like Django, SQLAlchemy
"""











🔷 1️⃣ Generic Function with Type Constraints (Typing Module)
📌 C++: template<typename T> with constraints
📌 Python: TypeVar + typing

from typing import TypeVar
T = TypeVar('T')

def maximum(a: T, b: T) -> T:
    return a if a > b else b

def main():
    print(maximum(10, 20))
    print(maximum("apple", "banana"))

if __name__ == "__main__":
    main()

""" 
🖥 Output
20
banana

📌 Compile-time checking (for type checkers)
"""




🔷 2️⃣ Template Class with Multiple Types
📌 Similar to template<class T, class U>

class Pair:
    def __init__(self, first, second):
        self.first = first
        self.second = second

    def show(self):
        print(self.first, self.second)

def main():
    p1 = Pair(10, "Python")
    p2 = Pair(3.14, [1, 2, 3])

    p1.show()
    p2.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
10 Python
3.14 [1, 2, 3]
"""





🔷 3️⃣ Template Specialization (Custom Object Types)
📌 Using singledispatch for user-defined classes

from functools import singledispatch

class Student:
    def __init__(self, name):
        self.name = name

@singledispatch
def process(obj):
    print("Generic processing")

@process.register(Student)
def _(obj):
    print("Processing student:", obj.name)

def main():
    process(10)
    process(Student("Alex"))

if __name__ == "__main__":
    main()

""" 
🖥 Output
Generic processing
Processing student: Alex
"""




🔷 4️⃣ SFINAE-like Behavior Using callable()
📌 Enable function only if method exists

def execute(obj):
    if callable(getattr(obj, "run", None)):
        obj.run()
    else:
        print("run() not supported")

class A:
    def run(self):
        print("A running")

class B:
    pass

def main():
    execute(A())
    execute(B())

if __name__ == "__main__":
    main()

""" 
🖥 Output
A running
run() not supported
"""




🔷 5️⃣ Enable Function Only for Numbers (Type Checking)
📌 Similar to enable_if in C++

def square(x):
    if isinstance(x, (int, float)):
        return x * x
    raise TypeError("Only numbers allowed")

def main():
    print(square(5))
    # print(square("a"))  # error

if __name__ == "__main__":
    main()

""" 
🖥 Output
25
"""





🔷 6️⃣ Compile-time Polymorphism (Operator Overloading)
📌 Equivalent to template operator overloading

class Data:
    def __init__(self, value):
        self.value = value

    def __add__(self, other):
        return Data(self.value + other.value)

def main():
    d1 = Data(10)
    d2 = Data(20)
    d3 = d1 + d2
    print(d3.value)

if __name__ == "__main__":
    main()

""" 
🖥 Output
30
"""





🔷 7️⃣ Metaprogramming: Auto-Generate Methods
📌 Code writing code dynamically

def auto_methods(cls):
    cls.say_hello = lambda self: print("Hello")
    cls.say_bye = lambda self: print("Bye")
    return cls

@auto_methods
class MyClass:
    pass

def main():
    obj = MyClass()
    obj.say_hello()
    obj.say_bye()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello
Bye
"""




🔷 8️⃣ Template Metaprogramming → Python Expression Evaluation
📌 C++ TMP computes values at compile time
📌 Python evaluates at runtime

def factorial(n):
    return 1 if n == 0 else n * factorial(n - 1)

def main():
    print(factorial(5))

if __name__ == "__main__":
    main()

""" 
🖥 Output
120
"""





🔷 9️⃣ Static Polymorphism using __class__
class A:
    def show(self):
        print("Class A")

class B(A):
    def show(self):
        print("Class B")

def main():
    obj = B()
    print(obj.__class__)
    obj.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
<class '__main__.B'>
Class B
"""






🔷 🔟 Metaclass Enforcing Template Rules
📌 Enforce method presence (like concept constraints)

class InterfaceMeta(type):
    def __new__(cls, name, bases, dct):
        if name != "Base" and "run" not in dct:
            raise TypeError("run() must be implemented")
        return super().__new__(cls, name, bases, dct)

class Base(metaclass=InterfaceMeta):
    pass

class Good(Base):
    def run(self):
        print("Running")

def main():
    g = Good()
    g.run()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Running
"""