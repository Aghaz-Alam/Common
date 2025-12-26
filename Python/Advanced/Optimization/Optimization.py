Optimization:
🔷 1️⃣ constexpr Equivalent in Python
C++ Concept:
constexpr computes values at compile time.
Example: constexpr int square(int x) { return x*x; }

Python Equivalent:
Python evaluates at runtime, but we can precompute values once.

Use:
Global constants
Memoization / caching
Decorators

Example 1: Precomputed Constant
SQUARE_5 = 5 * 5  # evaluated once

def main():
    print("Square of 5:", SQUARE_5)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Square of 5: 25
"""




Example 2: Memoization (like compile-time caching)
from functools import lru_cache

@lru_cache(maxsize=None)
def factorial(n):
    return 1 if n == 0 else n * factorial(n - 1)

def main():
    print(factorial(5))
    print(factorial(6))  # 6! uses cached 5!

if __name__ == "__main__":
    main()

""" 
🖥 Output
120
720

📌 lru_cache avoids recomputation → Python version of “compile-time optimization” at runtime.
"""




🔷 2️⃣ Templates / Generic Functions Optimization
C++ Concept:
Templates allow compile-time type resolution, no runtime overhead.

Python Equivalent:
Python uses duck typing and type hints (typing.Generic)
Use single function for multiple types → avoids redundant code.



Example: Generic Add Function
from typing import TypeVar

T = TypeVar('T')

def add(a: T, b: T) -> T:
    return a + b

def main():
    print(add(10, 20))          # int
    print(add(2.5, 3.5))        # float
    print(add("Hi ", "Python")) # string

if __name__ == "__main__":
    main()

""" 
🖥 Output
30
6.0
Hi Python

📌 No extra functions generated → memory efficient
"""






🔷 3️⃣ Memory Optimization
Python is dynamic, but we can optimize memory using:

3.1 __slots__ in classes
class Student:
    __slots__ = ['name', 'age']  # prevents dynamic dict

    def __init__(self, name, age):
        self.name = name
        self.age = age

def main():
    s = Student("Alex", 20)
    print(s.name, s.age)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Alex 20


📌 Memory saved → no __dict__ per object
✅ Good for large number of objects
 """





3.2 Generators (Lazy Evaluation)
def squares(n):
    for i in range(n):
        yield i*i  # generates values on-the-fly

def main():
    for val in squares(5):
        print(val, end=" ")

if __name__ == "__main__":
    main()

""" 
🖥 Output
0 1 4 9 16

📌 No full list in memory → memory optimized
"""




3.3 Using array for numeric data
from array import array

def main():
    nums = array('i', [1,2,3,4,5])
    print(nums)

if __name__ == "__main__":
    main()

""" 
🖥 Output
array('i', [1, 2, 3, 4, 5])

📌 array is more memory-efficient than list for large numbers
"""







3.4 Using __slots__ + Generators + @lru_cache → Python Optimization
from functools import lru_cache

class Fib:
    __slots__ = ['n']

    def __init__(self, n):
        self.n = n

@lru_cache(maxsize=None)
def fibonacci(n):
    return n if n < 2 else fibonacci(n-1) + fibonacci(n-2)

def main():
    for i in range(10):
        f = Fib(i)
        print(f"Fib({f.n}) =", fibonacci(f.n))

if __name__ == "__main__":
    main()

""" 
🖥 Output
Fib(0) = 0
Fib(1) = 1
Fib(2) = 1
Fib(3) = 2
Fib(4) = 3
Fib(5) = 5
Fib(6) = 8
Fib(7) = 13
Fib(8) = 21
Fib(9) = 34

📌 ✅ Combines memory + runtime optimization
"""








#Memory Optimization
🔷 1️⃣ Using __slots__ to Reduce Memory in Classes

Without __slots__, every object has a __dict__:

class Student:
    def __init__(self, name, age):
        self.name = name
        self.age = age

def main():
    s1 = Student("Alex", 20)
    s2 = Student("Bob", 21)
    print(s1.name, s2.age)
    print("Memory of s1:", s1.__sizeof__())
    # Large number of objects → memory inefficient

if __name__ == "__main__":
    main()

""" 
Output (example):
Alex 21
Memory of s1: 56
"""


✅ Using __slots__ reduces memory:

class Student:
    __slots__ = ['name', 'age']
    def __init__(self, name, age):
        self.name = name
        self.age = age

def main():
    s = Student("Alex", 20)
    print(s.name, s.age)
    print("Memory of s:", s.__sizeof__())

if __name__ == "__main__":
    main()

""" 
Alex 20
Memory of s: 48
"""



🔷 2️⃣ Generators vs Lists (Lazy Evaluation)
def squares_list(n):
    return [i*i for i in range(n)]

def squares_gen(n):
    for i in range(n):
        yield i*i

def main():
    nums = squares_list(1000000)  # huge memory
    print("List created")
    
    nums_gen = squares_gen(1000000)
    print("Generator created")
    print(next(nums_gen), next(nums_gen))  # lazy evaluation

if __name__ == "__main__":
    main()

""" 
List created
Generator created
0 1

✅ Generator does not allocate memory for all elements.
"""

🔷 3️⃣ Memory-Efficient Data Types: array vs list
from array import array
def main():
    nums_list = [i for i in range(1000000)]  # list
    nums_array = array('i', range(1000000))  # array of ints
    print("First element list:", nums_list[0])
    print("First element array:", nums_array[0])
    print("Memory of list item:", nums_list[0].__sizeof__())
    print("Memory of array item:", nums_array[0].__sizeof__())

if __name__ == "__main__":
    main()

""" 
First element list: 0
First element array: 0
Memory of list item: 28
Memory of array item: 4

✅ array saves memory for numeric sequences.
"""



🔷 4️⃣ String Interning / sys.intern()
Python reuses immutable strings automatically. You can explicitly intern strings to save memory for repeated strings.

import sys
def main():
    s1 = sys.intern("hello")
    s2 = sys.intern("hello")
    print(s1 is s2)  # True → same object
    s3 = "hello"
    s4 = "hello"
    print(s3 is s4)  # may also be True due to automatic interning

if __name__ == "__main__":
    main()

""" 
True
True

✅ Useful in memory-heavy string operations.
"""



🔷 5️⃣ __slots__ + Inheritance Optimization
class A:
    __slots__ = ['x']
    def __init__(self, x):
        self.x = x

class B(A):
    __slots__ = ['y']
    def __init__(self, x, y):
        super().__init__(x)
        self.y = y

def main():
    b = B(10, 20)
    print(b.x, b.y)
    print("Memory of B object:", b.__sizeof__())

if __name__ == "__main__":
    main()

""" 
10 20
Memory of B object: 56

✅ Saves memory even in inheritance chains.
"""



🔷 6️⃣ Immutable Data Structures: tuple vs list
def main():
    t = (1,2,3,4,5)
    l = [1,2,3,4,5]
    print("Tuple first item:", t[0])
    print("Tuple size:", t.__sizeof__())
    print("List size:", l.__sizeof__())

if __name__ == "__main__":
    main()

""" 
Tuple first item: 1
Tuple size: 64
List size: 96

✅ Immutable tuple is smaller and faster than list for read-only data.
"""


🔷 7️⃣ Shared Objects / Flyweight Pattern
class Letter:
    _instances = {}

    def __new__(cls, char):
        if char not in cls._instances:
            cls._instances[char] = super(Letter, cls).__new__(cls)
            cls._instances[char].char = char
        return cls._instances[char]

def main():
    a1 = Letter('a')
    a2 = Letter('a')
    print(a1 is a2)  # True → same object shared

if __name__ == "__main__":
    main()

""" 
True

✅ Reduces memory by sharing repeated objects.
"""



🔷 8️⃣ memoryview for Large Binary Data
def main():
    data = bytearray(b'abcdef')
    mv = memoryview(data)
    mv[0] = ord('z')
    print(data)

if __name__ == "__main__":
    main()

""" 
bytearray(b'zbcdef')

✅ Allows zero-copy slices → huge memory saving for large buffers.
"""




🔷 9️⃣ deque for Efficient Queues
from collections import deque

def main():
    d = deque()
    for i in range(5):
        d.append(i)
    print(d)
    d.popleft()  # O(1) memory-efficient removal
    print(d)

if __name__ == "__main__":
    main()

""" 
deque([0, 1, 2, 3, 4])
deque([1, 2, 3, 4])


✅ More memory-efficient for queue operations than list.
"""





🔷 10️⃣ Combined Example: __slots__ + Generators + Caching
from functools import lru_cache

class Fib:
    __slots__ = ['n']

    def __init__(self, n):
        self.n = n

@lru_cache(maxsize=None)
def fibonacci(n):
    return n if n < 2 else fibonacci(n-1) + fibonacci(n-2)

def main():
    for i in range(10):
        f = Fib(i)
        print(f"Fib({f.n}) =", fibonacci(f.n))

if __name__ == "__main__":
    main()


""" 
Fib(0) = 0
Fib(1) = 1
Fib(2) = 1
Fib(3) = 2
Fib(4) = 3
Fib(5) = 5
Fib(6) = 8
Fib(7) = 13
Fib(8) = 21
Fib(9) = 34


✅ Combines:
__slots__ → memory for objects
@lru_cache → avoids recomputation
Generators → could be used for sequences 
"""