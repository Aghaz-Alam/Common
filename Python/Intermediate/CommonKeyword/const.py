In Python, there is NO const keyword like in C/C++.
But Python provides multiple ways to achieve “constant-like” behavior by convention and design.

Below is a complete, exam + interview-ready explanation of all possible const equivalents in Python, 
with program code + main() + output.

🔷 What does const mean?
In C/C++:
Value cannot be modified
Compile-time enforcement

In Python:
No compile-time constants

Achieved using:
Naming conventions
Properties
Read-only objects
dataclass(frozen=True)
Enums
Custom classes





1️⃣ Constant by Naming Convention (Most Common)
PI = 3.14

def main():
    print(PI)
    # PI = 3.1415   # allowed but discouraged

if __name__ == "__main__":
    main()

""" 
🖥 Output
3.14

📌 Capital letters imply constant
 """





2️⃣ Constant Inside a Class (Class-Level Constant)
class MathConstants:
    PI = 3.14

def main():
    print(MathConstants.PI)

if __name__ == "__main__":
    main()

""" 
🖥 Output
3.14
 """




3️⃣ Read-Only Variable Using Property
class Student:
    def __init__(self, roll):
        self._roll = roll

    @property
    def roll(self):
        return self._roll

def main():
    s = Student(101)
    print(s.roll)
    # s.roll = 102   # ❌ AttributeError

if __name__ == "__main__":
    main()

""" 
🖥 Output
101

📌 Instance-level constant
"""





4️⃣ Constant Object (Immutable Types)
def main():
    x = 10          # int is immutable
    y = x
    y = 20
    print(x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10

📌 int, float, str, tuple are immutable
 """



5️⃣ Constant Using dataclass(frozen=True)
📌 Best replacement for C++ const object

from dataclasses import dataclass
@dataclass(frozen=True)
class Student:
    name: str
    age: int

def main():
    s = Student("Alex", 20)
    print(s)
    # s.age = 21  # ❌ FrozenInstanceError

if __name__ == "__main__":
    main()

""" 
🖥 Output
Student(name='Alex', age=20)
"""





6️⃣ Constant Collection Using Tuple
def main():
    days = ("Mon", "Tue", "Wed")
    print(days)
    # days[0] = "Sun"  # ❌ error

if __name__ == "__main__":
    main()

""" 
🖥 Output
('Mon', 'Tue', 'Wed')
"""





7️⃣ Constant Using Enum (Strongest Guarantee)
from enum import Enum

class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3

def main():
    print(Color.RED)
    print(Color.RED.value)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Color.RED
1

📌 Enum members cannot be reassigned
"""




8️⃣ Module-Level Constant
# config.py
MAX_USERS = 100

# main.py
import config

def main():
    print(config.MAX_USERS)

if __name__ == "__main__":
    main()

""" 
🖥 Output
100
"""





9️⃣ Prevent Modification Using __setattr__
class Constants:
    def __init__(self):
        self.PI = 3.14

    def __setattr__(self, name, value):
        if hasattr(self, name):
            raise AttributeError("Cannot modify constant")
        super().__setattr__(name, value)

def main():
    c = Constants()
    print(c.PI)
    # c.PI = 3.1415  # ❌ error

if __name__ == "__main__":
    main()

""" 
🖥 Output
3.14
"""