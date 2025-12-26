Variables and Function Usage in Python, especially concepts like pass by value, pass by reference, constants, 
and type hints (Python equivalent of const, decltype, etc.). 

I’ll provide complete programs + main + output, suitable for interview prep.

🔷 1️⃣ Pass by Value vs Pass by Reference
Python Concept:
Everything in Python is an object reference.
Mutable objects → act like pass by reference
Immutable objects → act like pass by value

Example 1: Immutable Object (Pass by Value)
def modify_number(x):
    x += 10
    print("Inside function:", x)

def main():
    num = 5
    modify_number(num)
    print("Outside function:", num)  # num unchanged

if __name__ == "__main__":
    main()

""" 
🖥 Output
Inside function: 15
Outside function: 5

✅ Immutable objects (int, str, tuple) behave like pass by value.
"""




Example 2: Mutable Object (Pass by Reference)
def modify_list(lst):
    lst.append(4)
    print("Inside function:", lst)

def main():
    my_list = [1, 2, 3]
    modify_list(my_list)
    print("Outside function:", my_list)  # list modified

if __name__ == "__main__":
    main()

""" 
🖥 Output
Inside function: [1, 2, 3, 4]
Outside function: [1, 2, 3, 4]

✅ Mutable objects (list, dict, set) behave like pass by reference.
"""


🔷 2️⃣ Python Equivalent of const in Functions
Python does not have a const keyword, but you can simulate constants by convention or using tuples / properties.

def display_name(name: str):
    # name cannot be changed (immutable string)
    print("Name:", name)

def main():
    my_name = "Alex"
    display_name(my_name)
    print(my_name)  # original string unchanged

if __name__ == "__main__":
    main()

""" 
🖥 Output
Name: Alex
Alex

✅ Immutable types act like const parameters in functions.
"""


🔷 3️⃣ Using *args and **kwargs (Flexible Reference Passing)
def greet(*names, **messages):
    for name in names:
        print(f"Hello {name}")
    for k, v in messages.items():
        print(f"{k}: {v}")

def main():
    greet("Alice", "Bob", msg1="Good Morning", msg2="Welcome")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello Alice
Hello Bob
msg1: Good Morning
msg2: Welcome

✅ Flexible argument passing → similar to templates in C++.
"""


🔷 4️⃣ Using Type Hints (Similar to decltype / Function Directives)
def add(a: int, b: int) -> int:
    return a + b

def main():
    x: int = 5
    y: int = 10
    result: int = add(x, y)
    print("Result:", result)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Result: 15

✅ a: int and -> int are like C++ type directives (decltype).
"""



🔷 5️⃣ Using Default and Constant Parameters
def multiply(x: int, y: int = 2):
    return x * y

def main():
    print(multiply(5))    # uses default y=2
    print(multiply(5, 3)) # y overridden

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
15

✅ Default arguments act like constant function parameters.
"""



🔷 6️⃣ Simulating const Object Parameters
class Student:
    def __init__(self, name):
        self._name = name

    @property
    def name(self):
        return self._name  # read-only property

def display_student(s: Student):
    print(s.name)
    # s.name = "Bob"  # ❌ cannot modify (simulates const object)

def main():
    s = Student("Alex")
    display_student(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex

✅ Read-only property → simulates const object in function.
"""



🔷 7️⃣ Combining Reference Passing + Type Hints + Const Simulation
from typing import List

def append_numbers(nums: List[int]):
    nums.append(10)

def display_numbers(nums: List[int]):
    for n in nums:
        print(n, end=" ")

def main():
    my_nums: List[int] = [1, 2, 3]
    append_numbers(my_nums)
    display_numbers(my_nums)

if __name__ == "__main__":
    main()

""" 
🖥 Output
1 2 3 10

✅ Mutable object → reference passing
✅ Type hints → similar to decltype
✅ Could use tuple → const-like behavior
"""

