1️⃣ List (Intermediate)
Concepts
Mutable
Slicing
Comprehension
Shallow vs Deep copy

def main():
    arr = [1, 2, 3]
    arr.append(4)
    arr[0] = 100
    print(arr)

if __name__ == "__main__":
    main()
"""
Output
[100, 2, 3, 4]
"""

2️⃣ Tuple
Concepts
Immutable
Faster than list
Used as dictionary keys

def main():
    t = (1, 2, 3)
    print(t[1])

if __name__ == "__main__":
    main()
"""
Output
2
"""

3️⃣ Set
Concepts
Unique elements
Unordered
Fast lookup

def main():
    s = {1, 2, 2, 3}
    print(s)

if __name__ == "__main__":
    main()
"""
Output
{1, 2, 3}
"""

4️⃣ Dictionary (IMPORTANT)
Concepts
Hash map
Key–value
Mutable

def main():
    d = {"a": 1, "b": 2}
    d["c"] = 3
    print(d)

if __name__ == "__main__":
    main()
"""
Output
{'a': 1, 'b': 2, 'c': 3}
"""

5️⃣ Loops (for & while)
def main():
    for i in range(3):
        print(i)
    
    print()   #for new line

    i = 0
    while i < 3:
        print(i)
        i += 1

if __name__ == "__main__":
    main()
"""
Output
0
1
2

0
1
2
"""

6️⃣ Functions (FULL BREAKDOWN)
Definition, Declaration, Call, Arguments
def add(a, b):        # definition
    return a + b

def main():
    x = 5
    y = 3
    print(add(x, y))  # calling (actual arguments)

if __name__ == "__main__":
    main()
"""
Output
8
"""

7️⃣ Function Types
a) No arguments
def greet():
    print("Hello")

def main():
    greet()

if __name__ == "__main__":
    main()
"""
Output
Hello
"""

b) Return value
def square(x):
    return x * x

8️⃣ Lambda Function
Anonymous one-line function
def main():
    add = lambda a, b: a + b
    print(add(3, 4))

if __name__ == "__main__":
    main()
"""
Output
7
"""

9️⃣ Array (Python vs C++)
Python has no built-in array like C++
Uses:
list
array module
NumPy

from array import array

def main():
    arr = array('i', [1, 2, 3])
    print(arr)

if __name__ == "__main__":
    main()
"""
Output
array('i', [1, 2, 3])
"""

🔟 String (Intermediate)
def main():
    s = "Python"
    print(s[::-1])
    print(s.upper())

if __name__ == "__main__":
    main()
"""
Output
nohtyP
PYTHON
"""


C++ KEYWORDS YOU LISTED → PYTHON REALITY CHECK
| C++ Concept           | Python Equivalent / Status        |
| --------------------- | --------------------------------- |
| const / constexpr     | ❌ Not supported (convention only) |
| friend function/class | ❌ No direct concept               |
| static                | ✅ Class variable                  |
| global / local        | ✅ Yes                             |
| mutable / immutable   | ✅ Core Python concept             |
| explicit / implicit   | ❌ Python is implicit              |
| inline                | ❌ Handled by interpreter          |
| extern                | ❌ Not needed                      |
| volatile              | ❌ Not applicable                  |
| virtual               | ✅ Default in Python               |
| vtable / vptr         | ❌ Internal, abstracted            |
| constructor           | ✅ `__init__`                      |
| destructor            | ✅ `__del__`                       |
| move semantics        | ❌ Reference-based                 |
| copy assignment       | ✅ `copy` module                   |


Example: Constructor & Destructor
class Test:
    def __init__(self):
        print("Constructor")

    def __del__(self):
        print("Destructor")

def main():
    t = Test()

if __name__ == "__main__":
    main()

"""
Output
Constructor
Destructor
"""




Static Variable Example
class Counter:
    count = 0   # static

    def __init__(self):
        Counter.count += 1

def main():
    a = Counter()
    b = Counter()
    print(Counter.count)

if __name__ == "__main__":
    main()

"""
Output
2
"""




def nums():
    for i in range(3):
        yield i

def main():
    for x in nums():
        print(x)

if __name__ == "__main__":
    main()

"""
Output
0
1
2
"""






🔷 1️⃣ List Comprehension
What it is
A compact way to create lists using loops + conditions.

def main():
    squares = [x * x for x in range(1, 6)]
    print(squares)

if __name__ == "__main__":
    main()

"""
Output
[1, 4, 9, 16, 25]
"""






🔷 2️⃣ Dictionary Comprehension
What it is
Create dictionaries dynamically.

def main():
    squares = {x: x * x for x in range(1, 6)}
    print(squares)

if __name__ == "__main__":
    main()

"""
Output
{1: 1, 2: 4, 3: 9, 4: 16, 5: 25}
"""





🔷 3️⃣ Exception Handling
What it is
Graceful handling of runtime errors.

def main():
    try:
        a = 10
        b = 0
        print(a // b)
    except ZeroDivisionError:
        print("Division by zero error")
    finally:
        print("Done")

if __name__ == "__main__":
    main()

"""
Output
Division by zero error
Done
"""






🔷 4️⃣ File Handling
What it is
Read/write data from files.

def main():
    with open("demo.txt", "w") as f:
        f.write("Hello Python")

    with open("demo.txt", "r") as f:
        print(f.read())

if __name__ == "__main__":
    main()
"""
Output
Hello Python
"""





🔷 5️⃣ Shallow Copy vs Deep Copy
Difference
Shallow copy → references nested objects
Deep copy → copies everything

import copy
def main():
    a = [[1, 2], [3, 4]]
    b = copy.copy(a)
    c = copy.deepcopy(a)

    a[0][0] = 100
    print(b)
    print(c)

if __name__ == "__main__":
    main()
"""
Output
[[100, 2], [3, 4]]
[[1, 2], [3, 4]]
"""





🔷 6️⃣ Modules & Imports
What it is
Reuse code across files.

import math

def main():
    print(math.sqrt(25))

if __name__ == "__main__":
    main()
"""
Output
5.0
"""






🔷 7️⃣ *args (Variable Arguments)
What it is
Accept multiple positional arguments.

def add(*args):
    return sum(args)

def main():
    print(add(1, 2, 3, 4))

if __name__ == "__main__":
    main()
"""
Output
10
"""






🔷 8️⃣ **kwargs (Keyword Arguments)
What it is
Accept multiple named arguments.

def show(**kwargs):
    for k, v in kwargs.items():
        print(k, v)

def main():
    show(name="Python", level="Intermediate")

if __name__ == "__main__":
    main()
"""
Output
name Python
level Intermediate
"""





🔷 9️⃣ Decorators (INTRO)
What it is
A function that modifies another function.

def my_decorator(func):
    def wrapper():
        print("Before function")
        func()
        print("After function")
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
Before function
Hello
After function
"""





🔷 🔟 Iterators
What it is
Object that produces values one by one.

def main():
    arr = [1, 2, 3]
    it = iter(arr)

    print(next(it))
    print(next(it))
    print(next(it))

if __name__ == "__main__":
    main()
"""
Output
1
2
3
"""




🔷 1️⃣1️⃣ Generators
What it is
Functions that use yield to produce values lazily.

def numbers():
    for i in range(3):
        yield i

def main():
    for x in numbers():
        print(x)

if __name__ == "__main__":
    main()
"""
Output
0
1
2
"""



Example (zip):
def main():
    names = ["A", "B", "C"]
    scores = [10, 20, 30]

    for n, s in zip(names, scores):
        print(n, s)

if __name__ == "__main__":
    main()
"""
Output
A 10
B 20
C 30
"""





1️⃣ enumerate()
What it is
Provides index + value while iterating.

def main():
    fruits = ["apple", "banana", "cherry"]
    for index, fruit in enumerate(fruits):
        print(index, fruit)

if __name__ == "__main__":
    main()

"""
Output
0 apple
1 banana
2 cherry
"""



2️⃣ zip()
What it is
Combine multiple iterables element-wise.

def main():
    names = ["Alice", "Bob", "Charlie"]
    scores = [85, 90, 78]
    for name, score in zip(names, scores):
        print(name, score)

if __name__ == "__main__":
    main()

"""
Output
Alice 85
Bob 90
Charlie 78
"""




3️⃣ map(), filter(), reduce()
map() → apply function to all elements
def main():
    nums = [1, 2, 3, 4]
    squares = list(map(lambda x: x*x, nums))
    print(squares)

if __name__ == "__main__":
    main()
"""
Output
[1, 4, 9, 16]
"""


filter() → filter elements by condition
def main():
    nums = [1, 2, 3, 4, 5]
    even = list(filter(lambda x: x % 2 == 0, nums))
    print(even)

if __name__ == "__main__":
    main()

"""
Output
[2, 4]
"""


reduce() → cumulative computation (from functools)
from functools import reduce

def main():
    nums = [1, 2, 3, 4]
    total = reduce(lambda x, y: x + y, nums)
    print(total)

if __name__ == "__main__":
    main()

"""
Output
10
"""



4️⃣ Context Managers (with)
What it is
Safely handle resources like files (auto-close).

def main():
    with open("demo.txt", "w") as f:
        f.write("Python is awesome")

    with open("demo.txt", "r") as f:
        print(f.read())

if __name__ == "__main__":
    main()

"""
Output
Python is awesome
"""






5️⃣ Python Memory Model (References)
What it is
Python variables are references, not copies by default.

def main():
    a = [1, 2, 3]
    b = a
    b.append(4)
    print(a)  # a is affected
    print(b)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3, 4]
[1, 2, 3, 4]
"""




6️⃣ Mutable vs Immutable behavior in functions
def modify_list(lst):
    lst.append(100)  # mutable, changes affect original

def modify_number(n):
    n += 100         # immutable, original unchanged
    return n

def main():
    a = [1, 2, 3]
    modify_list(a)
    print(a)  # modified

    x = 10
    y = modify_number(x)
    print(x)  # original unchanged
    print(y)  # returned new value

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3, 100]
10
110
"""





1️⃣ Functional Tools – map(), filter(), reduce()
🔹 map() – Transform elements
Concept
Applies a function to each element of an iterable.

def main():
    numbers = [1, 2, 3, 4, 5]
    squares = list(map(lambda x: x * x, numbers))
    print(squares)

if __name__ == "__main__":
    main()

"""
Output
[1, 4, 9, 16, 25]
"""




🔹 filter() – Select elements
Concept
Keeps elements that satisfy a condition.

def main():
    numbers = [1, 2, 3, 4, 5, 6]
    even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
    print(even_numbers)

if __name__ == "__main__":
    main()

"""
Output
[2, 4, 6]
"""



🔹 reduce() – Accumulate values
Concept
Reduces iterable to single value.

from functools import reduce

def main():
    numbers = [1, 2, 3, 4]
    result = reduce(lambda a, b: a + b, numbers)
    print(result)

if __name__ == "__main__":
    main()

"""
Output
10
"""



2️⃣ Iteration Helpers – enumerate() and zip()
🔹 enumerate()
Concept
Gives index + value during iteration.

def main():
    languages = ["Python", "C++", "Java"]
    for index, lang in enumerate(languages):
        print(index, lang)

if __name__ == "__main__":
    main()

"""
Output
0 Python
1 C++
2 Java
"""



🔹 zip()
Concept
Iterates over multiple iterables together.

def main():
    names = ["Alice", "Bob", "Charlie"]
    marks = [85, 90, 78]

    for name, mark in zip(names, marks):
        print(name, mark)

if __name__ == "__main__":
    main()

"""
Output
Alice 85
Bob 90
Charlie 78
"""





3️⃣ Resource Management – with (Context Manager)
🔹 with Statement
Concept
Automatically opens and closes resources (files, locks).

def main():
    with open("sample.txt", "w") as file:
        file.write("Hello Python")

    with open("sample.txt", "r") as file:
        print(file.read())

if __name__ == "__main__":
    main()

"""
Output
Hello Python
"""

✅ No need to call file.close() manually.





4️⃣ Python Memory Model – References
🔹 Reference Behavior
Concept
Variables point to objects, not values.

def main():
    a = [1, 2, 3]
    b = a          # reference copy
    b.append(4)

    print(a)
    print(b)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3, 4]
[1, 2, 3, 4]
"""

🧠 Both a and b refer to the same object.




5️⃣ Mutable vs Immutable Behavior in Functions
🔹 Mutable Example (list)
def update_list(lst):
    lst.append(99)

def main():
    data = [1, 2, 3]
    update_list(data)
    print(data)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3, 99]
"""




🔹 Immutable Example (int)
def update_number(num):
    num += 10
    return num

def main():
    x = 5
    y = update_number(x)
    print(x)
    print(y)

if __name__ == "__main__":
    main()

"""
Output
5
15
"""

🧠 Immutable objects cannot be modified in-place.




6️⃣ Combined Example (Interview Favorite)
def modify(items, value):
    items.append(value)
    value += 10
    return value

def main():
    my_list = [1, 2]
    num = 5

    new_num = modify(my_list, num)

    print(my_list)
    print(num)
    print(new_num)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 5]
5
15
"""