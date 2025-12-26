In Python, there is no static keyword like C++, but the same behavior is achieved in multiple ways.
Below is a complete, exam + interview-oriented list of ALL possible “static” use cases in Python, 
each with program code + main() + output, written clearly.

🔷 What does “static” mean?
In C++:
Belongs to class, not object
Shared among all objects
Single copy in memory

In Python:
Achieved using:
Class variables
@staticmethod
@classmethod
Static local variables (function attributes)
Static behavior using modules

1️⃣ Static Variable (Class Variable)
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

📌 One copy shared by all objects
"""




2️⃣ Static Variable Accessed Using Object vs Class
class Demo:
    x = 10   # static variable

def main():
    d1 = Demo()
    d2 = Demo()

    print(d1.x)
    print(d2.x)
    print(Demo.x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
10
10
"""





3️⃣ Modifying Static Variable (Correct vs Wrong Way)
class Demo:
    x = 10

def main():
    d = Demo()
    d.x = 20      # creates instance variable
    print(d.x)
    print(Demo.x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
20
10

📌 Interview trap ⭐
✔ Correct way → Demo.x = value
"""




4️⃣ Static Method (@staticmethod)
class MathUtil:
    @staticmethod
    def add(a, b):
        return a + b

def main():
    print(MathUtil.add(5, 3))

if __name__ == "__main__":
    main()

""" 
🖥 Output
8

📌 No self, no cls
"""




5️⃣ Calling Static Method Using Object
class Test:
    @staticmethod
    def show():
        print("Static method")

def main():
    t = Test()
    t.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Static method

📌 Allowed, but not recommended
"""




6️⃣ Static Method vs Instance Method
class Example:
    @staticmethod
    def static_fun():
        print("Static function")

    def instance_fun(self):
        print("Instance function")

def main():
    Example.static_fun()
    e = Example()
    e.instance_fun()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Static function
Instance function
"""






7️⃣ Static Method Accessing Static Variable
class Counter:
    count = 0

    @staticmethod
    def increment():
        Counter.count += 1

def main():
    Counter.increment()
    Counter.increment()
    print("Count:", Counter.count)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Count: 2
"""




8️⃣ Class Method (@classmethod) – Static-like Behavior
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

📌 Uses cls instead of self
"""





9️⃣ Class Method Modifying Static Variable
class Student:
    count = 0

    @classmethod
    def increment(cls):
        cls.count += 1

def main():
    Student.increment()
    Student.increment()
    print(Student.count)

if __name__ == "__main__":
    main()

""" 
🖥 Output
2
"""





🔟 Static Local Variable (Function Attribute)
def counter():
    if not hasattr(counter, "count"):
        counter.count = 0
    counter.count += 1
    print(counter.count)

def main():
    counter()
    counter()
    counter()

if __name__ == "__main__":
    main()

""" 
🖥 Output
1
2
3

📌 Python replacement for C++ static local variable
"""





1️⃣1️⃣ Static Variable in Inheritance
class A:
    x = 10

class B(A):
    pass

def main():
    print(B.x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
"""






1️⃣2️⃣ Static Variable Overridden in Child
class A:
    x = 10

class B(A):
    x = 20

def main():
    print(A.x)
    print(B.x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
20
"""





1️⃣3️⃣ Static Data Shared Across Objects
class Bank:
    interest_rate = 5

def main():
    b1 = Bank()
    b2 = Bank()

    print(b1.interest_rate)
    print(b2.interest_rate)

if __name__ == "__main__":
    main()

""" 
🖥 Output
5
"""






1️⃣4️⃣ Static Behavior via Module Variable
📌 Modules behave like static storage

# file: config.py
value = 10

# main file
import config

def main():
    print(config.value)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
"""







1️⃣5️⃣ Static Constant (Convention)
class AppConfig:
    MAX_USERS = 100

def main():
    print(AppConfig.MAX_USERS)

if __name__ == "__main__":
    main()

""" 
🖥 Output
100

📌 Constants by naming convention
"""