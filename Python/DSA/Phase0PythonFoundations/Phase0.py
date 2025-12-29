""" 
Phase 0 – Python Foundations (1–2 weeks)
Learn:
Variables, keywords, operators.
conditions, conditional statements
typecasting,
Input / Output
Input from users 
Loops (for, while)
Functions
Lists, Tuples
Dictionaries, Sets
String operations
List comprehension
lambda, map, filter
collections module
defaultdict
Counter
deque
heapq
bisect
"""




#1️⃣ Variables, Keywords, Operators
#Variables
A variable stores data in memory.

def main():
    x = 10
    y = 20
    name = "Aman"

    print(x, y)
    print(name)

if __name__ == "__main__":
    main()
""" 
🖥 Output
10 20
Aman
"""


#Keywords
#Reserved words with special meaning.
Examples:
if, else, for, while, break, continue, return, True, False, None

❌ You cannot use keywords as variable names.
""" ========================================================== """
🔹 1️⃣ if / else / elif
def main():
    x = 15

    if x < 10:
        print("x is less than 10")
    elif x == 15:
        print("x is 15")
    else:
        print("x is greater than 10 but not 15")

main()

""" 
🖥 Output
x is 15

Explanation: Conditional execution.
"""


🔹 2️⃣ for
def main():
    for i in range(5):
        print(i, end=" ")

main()

""" 
🖥 Output
0 1 2 3 4

Explanation: Loop over a sequence (list, range, string, etc.)
"""


🔹 3️⃣ while
def main():
    i = 0
    while i < 5:
        print(i, end=" ")
        i += 1

main()

""" 
🖥 Output
0 1 2 3 4

Explanation: Loop with condition, executes while condition is True
"""


🔹 4️⃣ break
def main():
    for i in range(5):
        if i == 3:
            break
        print(i, end=" ")

main()

""" 
🖥 Output
0 1 2

Explanation: Exit loop immediately
"""

🔹 5️⃣ continue
def main():
    for i in range(5):
        if i == 3:
            continue
        print(i, end=" ")

main()

""" 
🖥 Output
0 1 2 4

Explanation: Skip current iteration and continue with next
"""


🔹 6️⃣ return
def add(a, b):
    return a + b

def main():
    result = add(5, 3)
    print(result)

main()


""" 
🖥 Output
8

Explanation: Returns value from function
"""


🔹 7️⃣ True / False
def main():
    flag = True

    if flag:
        print("Flag is True")
    else:
        print("Flag is False")

main()

""" 
🖥 Output
Flag is True

Explanation: Boolean values, used in conditions
"""


🔹 8️⃣ None
def main():
    x = None

    if x is None:
        print("x has no value")
    else:
        print("x has a value")

main()

""" 
🖥 Output
x has no value

Explanation: Represents absence of value, similar to null
"""


🔹 9️⃣ pass (interview trap)
def main():
    for i in range(5):
        if i % 2 == 0:
            pass  # do nothing
        else:
            print(i, end=" ")

main()

""" 
🖥 Output
1 3

Explanation: Placeholder for empty blocks (loops, functions, classes)
"""

🔹10️⃣ and / or / not
def main():
    a = True
    b = False

    print(a and b)  # False
    print(a or b)   # True
    print(not a)    # False

main()

""" 
🖥 Output
False
True
False

Explanation: Logical operations for conditions
"""

🔹11️⃣ is / is not (HARD INTERVIEW TRAP)
def main():
    a = [1,2]
    b = a
    c = [1,2]

    print(a is b)      # True
    print(a is c)      # False
    print(a == c)      # True

main()

""" 
🖥 Output
True
False
True

Explanation: is → memory comparison, == → value comparison
"""


🔹12️⃣ in / not in
def main():
    arr = [1,2,3]

    print(2 in arr)      # True
    print(5 not in arr)  # True

main()

""" 
🖥 Output
True
True

Explanation: Membership testing
"""


🔹13️⃣ global / nonlocal (advanced)
x = 10
def main():
    global x
    x += 5
    print(x)

main()
""" 
🖥 Output
15

Explanation: Modify global variable inside a function
"""

🔹14️⃣ def / class
def greet():
    print("Hello Python")

class Person:
    def __init__(self, name):
        self.name = name

def main():
    greet()
    p = Person("Aman")
    print(p.name)

main()
""" 
🖥 Output
Hello Python
Aman

Explanation: Define functions and classes
"""

🧠 Interview Tip
Never use keywords as variable names:
if = 5  # ❌ SyntaxError

Know boolean keywords (True, False, None)
Know flow control (if, for, while, break, continue)
Know function / module (def, return, global, nonlocal)

""" ========================================================== """
#Operators
| Type       | Operators       |           |
| ---------- | --------------- | --------- |
| Arithmetic | + - * / % // ** |           |
| Relational | < > <= >= == != |           |
| Logical    | and or not      |           |
| Assignment | = += -= *=      |           |
| Bitwise    | &               | ^ ~ << >> |

def main():
    a = 10
    b = 3

    print(a + b)
    print(a // b)     //Floor Division
    print(a > b)
    print(a & b)

if __name__ == "__main__":
    main()
""" 
🖥 Output
13
3
True
2
"""
""" ============================================= """
Python Operators: // vs %
| Operator | Name           | Meaning                                                                    |
| -------- | -------------- | -------------------------------------------------------------------------- |
| `/`      | Division       | Regular floating-point division → result is **float**                      |
| `//`     | Floor Division | Divide and **take floor** → result is **integer** if operands are integers |
| `%`      | Modulo         | Remainder after division                                                   |



🔹 // — Floor Division
def main():
    a = 17
    b = 5

    print(a / b)   # Regular division
    print(a // b)  # Floor division
    print(a % b)   # Modulo

if __name__ == "__main__":
    main()

""" 
🖥 Output
3.4
3
2
"""
Explanation:
a / b = 17 / 5 = 3.4 → float
a // b = floor(3.4) = 3 → integer
a % b = remainder = 2
So // is NOT modulo. It gives quotient, floored.

🔹 Floor Division with negative numbers (interview trap)
def main():
    print(17 // 5)   # 3
    print(-17 // 5)  # -4
    print(17 // -5)  # -4
    print(-17 // -5) # 3

if __name__ == "__main__":
    main()

""" 
🖥 Output
3
-4
-4
3
"""
💡 Trick: Floor division always floors toward minus infinity, not zero.
🔹 Shortcut formula
a = b * (a // b) + (a % b)

✅ Always holds true in Python.

""" ============================================= """



#2️⃣ Conditions & Conditional Statements
#if / elif / else
def main():
    x = 15

    if x > 20:
        print("Greater than 20")
    elif x == 15:
        print("Equal to 15")
    else:
        print("Less than 20")

if __name__ == "__main__":
    main()
""" 
🖥 Output
Equal to 15
"""
""" =================================================== """
🔹 1️⃣ Python Ternary Operator Syntax
value_if_true if condition else value_if_false

It returns a value based on a condition.
🔹 Convert your example

Original:
def main():
    x = 15

    if x > 20:
        print("Greater than 20")
    elif x == 15:
        print("Equal to 15")
    else:
        print("Less than 20")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Equal to 15
"""



Ternary version (nested ternary)
def main():
    x = 15

    print("Greater than 20" if x > 20 else "Equal to 15" if x == 15 else "Less than 20")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Equal to 15

✅ Nested ternary allows if-elif-else in a single line
"""





🔹 2️⃣ Beginner Ternary Examples
Example 1: Find max of two numbers
def main():
    a, b = 10, 20
    max_val = a if a > b else b
    print("Max:", max_val)

main()
""" 
🖥 Output
Max: 20
"""



Example 2: Even or Odd
def main():
    n = 7
    print("Even" if n % 2 == 0 else "Odd")

main()

""" 
🖥 Output
Odd
"""





🔹 3️⃣ Intermediate Ternary Examples
Example 3: Absolute value
def main():
    x = -10
    abs_val = x if x >= 0 else -x
    print("Absolute:", abs_val)

main()

""" 
🖥 Output
Absolute: 10
"""





Example 4: Check multiple conditions (nested)
def main():
    x = 0
    result = "Positive" if x > 0 else "Zero" if x == 0 else "Negative"
    print(result)

main()

""" 
🖥 Output
Zero
"""




🔹 4️⃣ Advanced Ternary Examples
Example 5: Min of three numbers
def main():
    a, b, c = 10, 5, 7
    min_val = a if a < b and a < c else b if b < c else c
    print("Min:", min_val)

main()

""" 
🖥 Output
Min: 5
"""



Example 6: Grade system
def main():
    marks = 85
    grade = "A" if marks >= 90 else "B" if marks >= 75 else "C" if marks >= 60 else "F"
    print("Grade:", grade)

main()

""" 
🖥 Output
Grade: B
"""




🔹 5️⃣ Hard / Tricky Ternary Examples (Interview Level)
Example 7: Find sign of number (-1, 0, 1)
def main():
    x = -15
    sign = 1 if x > 0 else -1 if x < 0 else 0
    print("Sign:", sign)

main()

""" 
🖥 Output
Sign: -1
"""




Example 8: Max in a list using ternary + reduce
from functools import reduce

def main():
    arr = [3, 7, 2, 9, 5]
    max_val = reduce(lambda a,b: a if a > b else b, arr)
    print("Max:", max_val)

main()

""" 
🖥 Output
Max: 9

✅ Advanced trick: ternary inside lambda for functional programming
"""




Example 9: Nested dictionary ternary (hard)
def main():
    user = {"role": "admin"}
    message = "Admin Access" if user.get("role") == "admin" else "Guest Access" if user.get("role") == "guest" else "No Access"
    print(message)

main()

""" 
🖥 Output
Admin Access
"""



Example 10: Multiple ternary in one line (real interview trap)
def main():
    x = 20
    result = ("FizzBuzz" if x % 3 == 0 and x % 5 == 0 else
              "Fizz" if x % 3 == 0 else
              "Buzz" if x % 5 == 0 else
              str(x))
    print(result)

main()

""" 
🖥 Output
Buzz
"""
✅ This is exactly like LeetCode FizzBuzz one-liner
""" =================================================== """
#3️⃣ Typecasting
#Converting one data type to another.
def main():
    a = "100"
    b = int(a)
    c = float(b)

    print(type(a), type(b), type(c))
    print(b + 10)

if __name__ == "__main__":
    main()
""" 
🖥 Output
<class 'str'> <class 'int'> <class 'float'>
110
📌 Interview trap:
int("10.5") ❌ → error
int(float("10.5")) ✅
"""

""" =============================================== """
0️⃣ Why Python doesn’t need C++-style casts

C++:
Statically typed
Compile-time type enforcement
Direct memory access

Python:
Dynamically typed
Runtime type checking
No direct pointer arithmetic
Safety over raw memory control
So Python replaces casts with runtime checks + object behavior.




1️⃣ static_cast (C++) → Python equivalent
C++ static_cast

Used for:
Safe numeric conversions
Compile-time conversions
int x = static_cast<int>(3.14);



✅ Python Equivalent: Built-in type conversion
def main():
    x = 3.14
    y = int(x)      # similar to static_cast<int>

    print(y, type(y))

if __name__ == "__main__":
    main()

""" 
🖥 Output
3 <class 'int'>
"""

Interview Mapping
| C++                   | Python   |
| --------------------- | -------- |
| static_cast<int>(x)   | int(x)   |
| static_cast<float>(x) | float(x) |


📌 Python casting is runtime, not compile-time






2️⃣ dynamic_cast (C++) → Python equivalent
C++ dynamic_cast

Used for:
Safe downcasting in inheritance
RTTI (runtime type checking)

Base* b = new Derived();
Derived* d = dynamic_cast<Derived*>(b);



✅ Python Equivalent: isinstance() (VERY IMPORTANT)
class Base:
    pass

class Derived(Base):
    pass

def main():
    b = Derived()

    if isinstance(b, Derived):
        print("b is Derived")
    else:
        print("Not Derived")

if __name__ == "__main__":
    main()

""" 
🖥 Output
b is Derived
"""

Interview Mapping
| C++          | Python                    |
| ------------ | ------------------------- |
| dynamic_cast | isinstance()              |
| RTTI         | Runtime object inspection |


📌 Python automatically handles polymorphism → duck typing





3️⃣ const_cast (C++) → Python equivalent
C++ const_cast

Used to:
Remove const qualifier (dangerous)
const int x = 10;
int& y = const_cast<int&>(x);

❌ Python has NO const
Python variables are names bound to objects.
Python Reality
Immutable objects act like const
Mutable objects can change





✅ Python “const-like” behavior using immutability
def main():
    x = 10
    print(x)

    # x is immutable, cannot be modified in-place
    x = x + 5
    print(x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
15

📌 You didn’t modify 10 — you created a new object.
"""


⚠️ Interview Trap (mutable inside immutable)
def main():
    t = ([1, 2], 3)
    t[0].append(4)

    print(t)

if __name__ == "__main__":
    main()

""" 
🖥 Output
([1, 2, 4], 3)

📌 Tuple is immutable, but contains mutable list.
"""




4️⃣ reinterpret_cast (C++) → Python equivalent
C++ reinterpret_cast

Used for:
Low-level memory reinterpretation
Pointer casting (VERY DANGEROUS)

int x = 65;
char* c = reinterpret_cast<char*>(&x);
❌ Python has NO direct equivalent
Python does not allow raw pointer casting.
BUT there are advanced low-level alternatives 👇

⚠️ Python Low-Level Equivalent 1: struct module
import struct
def main():
    x = 65
    packed = struct.pack('i', x)
    unpacked = struct.unpack('cxxx', packed)

    print(unpacked)

if __name__ == "__main__":
    main()

""" 
🖥 Output
(b'A',)

📌 This is closest to reinterpret_cast (binary reinterpretation)
"""



⚠️ Python Low-Level Equivalent 2: ctypes (VERY ADVANCED)
import ctypes
def main():
    x = ctypes.c_int(65)
    char_ptr = ctypes.cast(ctypes.pointer(x), ctypes.POINTER(ctypes.c_char))

    print(char_ptr.contents.value)

if __name__ == "__main__":
    main()

""" 
🖥 Output
b'A'
"""

📌 This is dangerous and used only in:
OS
C extensions
Drivers

5️⃣ Summary Table (INTERVIEW GOLD)
| C++ Cast         | Exists in Python? | Python Alternative            |
| ---------------- | ----------------- | ----------------------------- |
| static_cast      | ❌                 | `int()`, `float()`, `str()`   |
| dynamic_cast     | ❌                 | `isinstance()`                |
| const_cast       | ❌                 | Immutability                  |
| reinterpret_cast | ❌                 | `struct`, `ctypes` (advanced) |




Python does not support C++-style casts because it is dynamically typed.
Instead, Python uses built-in type conversion, runtime checks like isinstance, 
immutability for const-like behavior, and advanced modules like ctypes for low-level memory operations.

""" ================================================ """


#4️⃣ Input / Output
def main():
    print("Hello Python")

if __name__ == "__main__":
    main()
""" 
🖥 Output
Hello Python
"""


#5️⃣ Input From User
def main():
    age = int(input("Enter age: "))
    print("Age is:", age)

if __name__ == "__main__":
    main()
""" 
🖥 Output
Enter age: 21
Age is: 21
📌 Input is always string, convert explicitly.
"""





#6️⃣ Loops (for, while)
#for loop
def main():
    for i in range(1, 6):
        print(i)

if __name__ == "__main__":
    main()
""" 
🖥 Output
1
2
3
4
5
"""
""" ================================================ """
✅ Method 1: Using end (MOST COMMON & INTERVIEW-SAFE)
def main():
    for i in range(1, 6):
        print(i, end=" ")

if __name__ == "__main__":
    main()

""" 
🖥 Output
1 2 3 4 5 

📌 end=" " replaces the default newline with a space.
"""



✅ Method 2: Print after loop (CLEANER)
def main():
    for i in range(1, 6):
        print(i, end=" ")

    print()  # for newline

if __name__ == "__main__":
    main()

""" 
🖥 Output
1 2 3 4 5
"""





✅ Method 3: Using join (PYTHONIC & FAST)
def main():
    print(" ".join(str(i) for i in range(1, 6)))

if __name__ == "__main__":
    main()

""" 
🖥 Output
1 2 3 4 5

📌 Best for large output (avoids many print calls).
"""




✅ Method 4: Convert range to list (BEGINNER)
def main():
    print(list(range(1, 6)))

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 2, 3, 4, 5]

⚠️ Not exactly same format (brackets & commas).
"""



✅ Method 5: Using unpacking (*) (INTERVIEW FAVORITE)
def main():
    print(*range(1, 6))

if __name__ == "__main__":
    main()

🖥 Output
1 2 3 4 5

📌 Default separator is space (sep=" ").




🔥 BONUS: Custom separator
def main():
    print(*range(1, 6), sep=", ")

if __name__ == "__main__":
    main()

Output
1, 2, 3, 4, 5

🧠 Interview Recommendation
| Scenario        | Best Method         |
| --------------- | ------------------- |
| Simple loop     | `print(i, end=" ")` |
| Large output    | `" ".join()`        |
| Clean one-liner | `print(*range())`   |

""" ================================================ """
#while loop
def main():
    i = 1
    while i <= 5:
        print(i)
        i += 1

if __name__ == "__main__":
    main()
""" 
🖥 Output
1
2
3
4
5
"""


#while loop
def main():
    i = 1
    while i <= 5:
        print(i, end=" ")
        i += 1

if __name__ == "__main__":
    main()
""" 
🖥 Output
1 2 3 4 5
"""





7️⃣ Functions
def add(a, b):
    return a + b
def main():
    result = add(5, 3)
    print(result)

if __name__ == "__main__":
    main()
""" 
🖥 Output
8
📌 Functions reduce repetition & help recursion later.
"""



#8️⃣ Lists
#Ordered, mutable, indexed.
def main():
    arr = [10, 20, 30, 40]

    arr.append(50)
    arr.remove(20)

    print(arr)
    print(arr[0])

if __name__ == "__main__":
    main()
""" 
🖥 Output
[10, 30, 40, 50]
10
📌 Python list = Dynamic Array
"""

""" =================================================== """
BEGINNER LEVEL (Foundations)
1️⃣ Create & Access List
def main():
    arr = [1, 2, 3, 4]
    print(arr)
    print(arr[0], arr[-1])

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 2, 3, 4]
1 4
"""

""" ------------------------ """
How list indexing works in Python
arr = [1, 2, 3, 4]

📍 Positive Indexing (LEFT → RIGHT)
| Index | Value |
| ----- | ----- |
| 0     | 1     |
| 1     | 2     |
| 2     | 3     |
| 3     | 4     |


print(arr[0])  # 1
print(arr[3])  # 4

📌 Rule:
index = position - 1


🔹 Negative Indexing (RIGHT → LEFT)
| Index | Value |
| ----- | ----- |
| -1    | 4     |
| -2    | 3     |
| -3    | 2     |
| -4    | 1     |

print(arr[-1])  # 4
print(arr[-2])  # 3

📌 Rule:
-1 always means last element

💡 Internally:
arr[-1] == arr[len(arr) - 1]


Why arr[-1] works (INTERVIEW EXPLANATION)
Python converts negative index like this:

arr[-1] → arr[len(arr) + (-1)]
        → arr[4 - 1]
        → arr[3]

✅ That’s why it prints 4.


🔹 Common Confusion: END INDEX DOES NOT EXIST
❌ This is invalid:
arr[4]  # IndexError

Because valid indices are:
0 to len(arr) - 1

🔹 Slicing vs Indexing (BIG TRAP 🔥)
def main():
    arr = [1, 2, 3, 4]
    print(arr[1:3])

if __name__ == "__main__":
    main()

🖥 Output
[2, 3]

🧠 Rule:
arr[start : end]
✔ start → included
❌ end → excluded

Visual Explanation
Index:   0   1   2   3
Value:   1   2   3   4
Slice:      [-------)
arr[1:3] → 2, 3

🔥 Negative Index in Slicing
def main():
    arr = [1, 2, 3, 4]
    print(arr[-3:-1])

if __name__ == "__main__":
    main()

🖥 Output
[2, 3]

Because:
-3 → index 1
-1 → index 3 (excluded)

🎯 Master Formula (Remember This)
arr[a:b] → from a to b-1
arr[-1] → last element
arr[len(arr)] ❌


🧪 Interview Trap Question
arr = [1, 2, 3]
print(arr[len(arr)])

❌ IndexError

But:
print(arr[len(arr)-1])
✅ 3

🧠 One-Line Interview Answer
Python lists are 0-indexed, support negative indexing, and slicing excludes the end index.


#---------------------------------#
Common Interview Traps
arr = [1,2,3,4]

print(arr[:])     # [0:len(arr))
print(arr[:3])    # [0:3)
print(arr[2:])    # [2:len(arr))
print(arr[-3:-1]) # [-3:-1)

Outputs
[1, 2, 3, 4]
[1, 2, 3]
[3, 4]
[2, 3]
#------------------------------#
The symbols [ ) together represent a very important concept called a half-open interval, mainly used in Python slicing and ranges.

🔹 Meaning of [ ) in Python
[ start , end )

✔ Included on the LEFT
❌ Excluded on the RIGHT

📌 Where you see [ ) in Python
1️⃣ List / String / Tuple slicing
arr = [10, 20, 30, 40, 50]
print(arr[1:4])

🖥 Output
[20, 30, 40]

Explanation:
[1:4) → index 1 included, index 4 excluded

2️⃣ range() function
def main():
    for i in range(1, 5):
        print(i, end=" ")

if __name__ == "__main__":
    main()

🖥 Output
1 2 3 4

Meaning:
range(1, 5) → [1, 5)


3️⃣ Why Python uses [ ) (INTERVIEW ANSWER)
Python uses half-open intervals because:
✔ Easy length calculation
✔ Easy chaining
✔ No overlap bugs
✔ Works naturally with 0-indexing

Example:
len(arr[a:b]) == b - a

🔥 Visual Example
Index:   0   1   2   3   4
Value:   A   B   C   D   E

Slice: arr[1:4)
       B   C   D

🧠 Why RIGHT side is excluded?
If both sides were inclusive:
[1,4] → how many elements?

Confusing ❌
With [ ):
[1,4) → 4 - 1 = 3 elements

Clean & predictable ✅

🔥 Common Interview Traps
arr = [1,2,3,4]

print(arr[:])     # [0:len(arr))
print(arr[:3])    # [0:3)
print(arr[2:])    # [2:len(arr))
print(arr[-3:-1]) # [-3:-1)

Outputs
[1, 2, 3, 4]
[1, 2, 3]
[3, 4]
[2, 3]

🧪 Mental Rule (Remember Forever)
[start : end]
start → included
end   → excluded

🎯 Interview One-Liner
Python follows half-open intervals [start, end) where the start index is included and the end index is excluded.

""" ------------------------ """
2️⃣ Append vs Insert
def main():
    arr = [1, 2, 3]
    arr.append(4)
    arr.insert(1, 99)

    print(arr)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 99, 2, 3, 4]
"""



3️⃣ Remove vs Pop (INTERVIEW FAVORITE)
def main():
    arr = [10, 20, 30, 40]

    arr.remove(20)
    x = arr.pop()

    print(arr)
    print(x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[10, 30, 40]
40
"""





⚙️ INTERMEDIATE LEVEL (CORE TRAPS)
4️⃣ List Copy Trap (VERY IMPORTANT)
def main():
    a = [1, 2, 3]
    b = a

    b.append(4)

    print(a)
    print(b)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 2, 3, 4]
[1, 2, 3, 4]

📌 b points to same memory.
"""




5️⃣ Correct Copy
def main():
    a = [1, 2, 3]
    b = a.copy()

    b.append(4)

    print(a)
    print(b)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 2, 3]
[1, 2, 3, 4]
"""




6️⃣ Slicing Does NOT Modify Original
def main():
    arr = [1, 2, 3, 4, 5]

    print(arr[1:4])
    print(arr)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[2, 3, 4]
[1, 2, 3, 4, 5]
"""





7️⃣ Reverse List (3 ways)
def main():
    arr = [1, 2, 3]

    print(arr[::-1])

    arr.reverse()
    print(arr)

    print(list(reversed(arr)))

if __name__ == "__main__":
    main()


""" 
🖥 Output
[3, 2, 1]
[3, 2, 1]
[1, 2, 3]
"""





🚀 ADVANCED LEVEL (DSA + INTERVIEWS)
8️⃣ List Comprehension with Condition
def main():
    arr = [1, 2, 3, 4, 5]

    even = [x for x in arr if x % 2 == 0]

    print(even)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[2, 4]
"""




9️⃣ Nested List Comprehension
def main():
    matrix = [[1, 2], [3, 4]]

    flat = [x for row in matrix for x in row]

    print(flat)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 2, 3, 4]
"""





🔟 Sorting Trap
def main():
    arr = [3, 1, 2]

    x = arr.sort()
    print(x)
    print(arr)

if __name__ == "__main__":
    main()

""" 
🖥 Output
None
[1, 2, 3]

📌 sort() modifies in place and returns None.
"""




1️⃣1️⃣ sorted() vs sort()
def main():
    arr = [3, 1, 2]

    x = sorted(arr)

    print(arr)
    print(x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[3, 1, 2]
[1, 2, 3]
"""






🧨 HARD LEVEL (INTERVIEW TRAPS)
1️⃣2️⃣ Mutable Default Argument TRAP 🔥🔥
def add_item(item, arr=[]):
    arr.append(item)
    return arr

def main():
    print(add_item(1))
    print(add_item(2))
    print(add_item(3))

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1]
[1, 2]
[1, 2, 3]

📌 Default list is shared!
"""







1️⃣3️⃣ Fix Mutable Default
def add_item(item, arr=None):
    if arr is None:
        arr = []
    arr.append(item)
    return arr

def main():
    print(add_item(1))
    print(add_item(2))

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1]
[2]
"""




1️⃣4️⃣ += vs + (CRITICAL)
def main():
    a = [1, 2]
    b = a

    a += [3]
    print(a, b)

    a = [1, 2]
    b = a

    a = a + [3]
    print(a, b)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 2, 3] [1, 2, 3]
[1, 2, 3] [1, 2]
"""




1️⃣5️⃣ List Equality vs Identity
def main():
    a = [1, 2, 3]
    b = [1, 2, 3]

    print(a == b)
    print(a is b)

if __name__ == "__main__":
    main()

""" 
🖥 Output
True
False
"""




🔰 EASY
1️⃣ Reverse a List (In-place)
Concept: Two pointers
def main():
    arr = [1, 2, 3, 4, 5]
    l, r = 0, len(arr) - 1

    while l < r:
        arr[l], arr[r] = arr[r], arr[l]
        l += 1
        r -= 1

    print(arr)

if __name__ == "__main__":
    main()

""" 
Output
[5, 4, 3, 2, 1]
"""




2️⃣ Find Maximum & Minimum
Concept: Linear scan
def main():
    arr = [7, 2, 9, 4, 1]
    mn = mx = arr[0]

    for x in arr:
        if x < mn: mn = x
        if x > mx: mx = x

    print(mn, mx)

if __name__ == "__main__":
    main()

""" 
Output
1 9
"""




⚙️ MEDIUM
3️⃣ Remove Duplicates (Preserve Order)
Concept: Hash set + list
def main():
    arr = [1, 2, 2, 3, 1, 4]
    seen = set()
    res = []

    for x in arr:
        if x not in seen:
            seen.add(x)
            res.append(x)

    print(res)

if __name__ == "__main__":
    main()

""" 
Output
[1, 2, 3, 4]
"""




4️⃣ Rotate Array by K (Right Rotation)
Concept: Slicing (O(n))

def main():
    arr = [1, 2, 3, 4, 5]
    k = 2
    k %= len(arr)

    arr = arr[-k:] + arr[:-k]
    print(arr)

if __name__ == "__main__":
    main()

""" 
Output
[4, 5, 1, 2, 3]
"""




5️⃣ Two Sum
Concept: Hash map (O(n))
def main():
    arr = [2, 7, 11, 15]
    target = 9
    mp = {}

    for i, x in enumerate(arr):
        if target - x in mp:
            print(mp[target - x], i)
            return
        mp[x] = i

if __name__ == "__main__":
    main()

""" 
Output
0 1
"""




🚀 ADVANCED
6️⃣ Move All Zeros to End
Concept: Two pointers (stable)
def main():
    arr = [0, 1, 0, 3, 12]
    pos = 0

    for x in arr:
        if x != 0:
            arr[pos] = x
            pos += 1

    for i in range(pos, len(arr)):
        arr[i] = 0

    print(arr)

if __name__ == "__main__":
    main()

""" 
Output
[1, 3, 12, 0, 0]
"""




7️⃣ Maximum Subarray Sum (Kadane’s Algorithm)
Concept: DP / Greedy
def main():
    arr = [-2,1,-3,4,-1,2,1,-5,4]
    max_sum = curr = arr[0]

    for x in arr[1:]:
        curr = max(x, curr + x)
        max_sum = max(max_sum, curr)

    print(max_sum)

if __name__ == "__main__":
    main()

""" 
Output
6
"""



🧨 HARD (INTERVIEW TRAPS)
8️⃣ Product of Array Except Self
Concept: Prefix & Suffix (No division)
def main():
    arr = [1, 2, 3, 4]
    n = len(arr)
    res = [1] * n

    left = 1
    for i in range(n):
        res[i] = left
        left *= arr[i]

    right = 1
    for i in range(n-1, -1, -1):
        res[i] *= right
        right *= arr[i]

    print(res)

if __name__ == "__main__":
    main()

""" 
Output
[24, 12, 8, 6]
"""





9️⃣ Find Missing Number (0..n)
Concept: XOR trick
def main():
    arr = [3, 0, 1]
    n = len(arr)
    ans = n

    for i in range(n):
        ans ^= i ^ arr[i]

    print(ans)

if __name__ == "__main__":
    main()


""" 
Output
2
 """




🔟 Longest Consecutive Sequence
Concept: Set (O(n))
def main():
    arr = [100, 4, 200, 1, 3, 2]
    s = set(arr)
    longest = 0

    for x in s:
        if x - 1 not in s:
            curr = x
            length = 1
            while curr + 1 in s:
                curr += 1
                length += 1
            longest = max(longest, length)

    print(longest)

if __name__ == "__main__":
    main()

""" 
Output
4
"""
""" =================================================== """
#9️⃣ Tuples
#Ordered, immutable.
def main():
    t = (1, 2, 3)
    print(t)
    print(t[1])

if __name__ == "__main__":
    main()
""" 
🖥 Output
(1, 2, 3)
2
📌 Faster than list, safe for constants.
"""




#🔟 Dictionaries
#Key–Value pairs.
def main():
    mp = {"a": 1, "b": 2}
    mp["c"] = 3

    print(mp)
    print(mp["a"])

if __name__ == "__main__":
    main()
""" 
🖥 Output
{'a': 1, 'b': 2, 'c': 3}
1
📌 O(1) average lookup.
"""





#1️⃣1️⃣ Sets
Unique elements only.
def main():
    s = {1, 2, 2, 3}
    s.add(4)

    print(s)

if __name__ == "__main__":
    main()
""" 
🖥 Output
Copy code
{1, 2, 3, 4}
"""



#1️⃣2️⃣ String Operations
def main():
    s = "python"

    print(s.upper())
    print(s[::-1])
    print(s.count('o'))

if __name__ == "__main__":
    main()
""" 
🖥 Output
nginx
Copy code
PYTHON
nohtyp
1
📌 Strings are immutable.
"""



#1️⃣3️⃣ List Comprehension
#Compact loops.
def main():
    squares = [x*x for x in range(5)]
    print(squares)

if __name__ == "__main__":
    main()
""" 
🖥 Output
csharp
Copy code
[0, 1, 4, 9, 16]
"""



#1️⃣4️⃣ lambda, map, filter
#lambda
Anonymous function.
def main():
    add = lambda a, b: a + b
    print(add(3, 4))

if __name__ == "__main__":
    main()
""" 
🖥 Output
Copy code
7
"""


#map
def main():
    nums = [1, 2, 3]
    result = list(map(lambda x: x * 2, nums))
    print(result)

if __name__ == "__main__":
    main()
""" 
🖥 Output
csharp
Copy code
[2, 4, 6]
"""


#filter
def main():
    nums = [1, 2, 3, 4, 5]
    even = list(filter(lambda x: x % 2 == 0, nums))
    print(even)

if __name__ == "__main__":
    main()
""" 
🖥 Output
csharp
Copy code
[2, 4]
"""




#1️⃣5️⃣ collections Module
#defaultdict
from collections import defaultdict
def main():
    mp = defaultdict(int)
    arr = [1, 2, 1, 3, 2]

    for x in arr:
        mp[x] += 1

    print(dict(mp))

if __name__ == "__main__":
    main()
""" 
🖥 Output
{1: 2, 2: 2, 3: 1}
📌 Avoids KeyError.
 """



#Counter
from collections import Counter
def main():
    arr = [1, 2, 1, 3, 2]
    cnt = Counter(arr)

    print(cnt)

if __name__ == "__main__":
    main()
'''
🖥 Output
Counter({1: 2, 2: 2, 3: 1})
'''


#deque
from collections import deque
def main():
    dq = deque()
    dq.append(10)
    dq.appendleft(5)
    dq.pop()

    print(dq)

if __name__ == "__main__":
    main()
'''
🖥 Output
deque([5])
📌 O(1) from both ends.
'''





#1️⃣6️⃣ heapq (Priority Queue)
import heapq
def main():
    arr = [5, 1, 3, 2]
    heapq.heapify(arr)

    heapq.heappush(arr, 0)
    print(heapq.heappop(arr))

if __name__ == "__main__":
    main()
'''
🖥 Output
Copy code
0
📌 Min-heap by default.
'''




#1️⃣7️⃣ bisect (Binary Search)
import bisect
def main():
    arr = [1, 3, 5, 7]
    pos = bisect.bisect_left(arr, 4)

    print(pos)

if __name__ == "__main__":
    main()
''' 
🖥 Output
Copy code
2



What bisect_left ACTUALLY does
pos = bisect.bisect_left(arr, 4)

❌ It does NOT search for 4
✅ It finds the position where 4 SHOULD be inserted
so that the list remains sorted
How does Python calculate pos = 2?
Python internally performs binary search.

Step 1: Compare with middle
Middle element ≈ 5
4 < 5 → go LEFT

Step 2: Compare with next middle
Element ≈ 3
4 > 3 → go RIGHT

Step 3: No exact match found
➡️ Insert before 5

So:
Insert position = index of 5 = 2

📍 Visual Insertion
[1, 3, | 5, 7]
        ↑
       4 goes here

Thus:
pos = 2
'''





1️⃣ Variables & Assignment (Advanced)
#Multiple Assignment
a, b, c = 1, 2, 3

#Swapping (NO temp variable)
a, b = b, a


📌 Interview trap:
This is tuple packing + unpacking, not magic.

#Mutable vs Immutable (VERY IMPORTANT)
a = 10
b = a
b += 1
print(a)   # 10

a = [1, 2]
b = a
b.append(3)
print(a)   # [1, 2, 3]


| Type                   | Mutable |
| ---------------------- | ------- |
| int, float, str, tuple | ❌       |
| list, dict, set        | ✅       |
""" ========================================================================= """
1️⃣ int (Immutable)
def main():
    a = 10
    print("Before:", a, id(a))

    a = a + 5
    print("After :", a, id(a))

if __name__ == "__main__":
    main()

🖥 Output
Before: 10 140312345678912
After : 15 140312345679040

🔍 Explanation
a + 5 creates new integer object
Memory address changes

📌 Interview line:
Integers are immutable because arithmetic creates new objects.




2️⃣ float (Immutable)
def main():
    x = 10.5
    print("Before:", x, id(x))

    x += 1.5
    print("After :", x, id(x))

if __name__ == "__main__":
    main()

🖥 Output
Before: 10.5 140312345680112
After : 12.0 140312345680240

📌 Same behavior as int.



3️⃣ str (Immutable) ⚠️ VERY IMPORTANT
def main():
    s = "hello"
    print("Before:", s, id(s))

    s = s + " world"
    print("After :", s, id(s))

if __name__ == "__main__":
    main()

🖥 Output
Before: hello 140312345680480
After : hello world 140312345681024

🔍 Explanation
"hello" + " world" creates a new string
Original string remains unchanged

📌 Interview trap:
str += str inside loop = O(n²) behavior





4️⃣ tuple (Immutable)
def main():
    t = (1, 2, 3)
    print("Before:", t, id(t))

    t = t + (4,)
    print("After :", t, id(t))

if __name__ == "__main__":
    main()

🖥 Output
Before: (1, 2, 3) 140312345681536
After : (1, 2, 3, 4) 140312345682048

📌 You cannot modify elements
t[0] = 10   # ❌ TypeError
✅ Mutable Types



5️⃣ list (Mutable)
def main():
    arr = [1, 2, 3]
    print("Before:", arr, id(arr))

    arr.append(4)
    print("After :", arr, id(arr))

if __name__ == "__main__":
    main()

🖥 Output
Before: [1, 2, 3] 140312345682432
After : [1, 2, 3, 4] 140312345682432

🔍 Explanation
List modified in-place
Same memory address
📌 Used heavily in DSA.




6️⃣ dict (Mutable)
def main():
    mp = {"a": 1}
    print("Before:", mp, id(mp))

    mp["b"] = 2
    print("After :", mp, id(mp))

if __name__ == "__main__":
    main()

🖥 Output
Before: {'a': 1} 140312345682944
After : {'a': 1, 'b': 2} 140312345682944

📌 Hash maps → average O(1) access




7️⃣ set (Mutable)
def main():
    s = {1, 2, 3}
    print("Before:", s, id(s))

    s.add(4)
    print("After :", s, id(s))

if __name__ == "__main__":
    main()

🖥 Output
Before: {1, 2, 3} 140312345683456
After : {1, 2, 3, 4} 140312345683456
📌 Used for uniqueness, fast lookup




⚠️ HARD INTERVIEW TRAP (VERY IMPORTANT)
Tuple containing mutable object
def main():
    t = ([1, 2], 3)
    print("Before:", t)

    t[0].append(4)
    print("After :", t)

if __name__ == "__main__":
    main()

🖥 Output
Before: ([1, 2], 3)
After : ([1, 2, 4], 3)

🔥 Key Insight
Tuple is immutable
But it contains a mutable object
That object can still change

""" ========================================================================== """

2️⃣ Input / Output (Advanced)
Fast I/O (competitive programming)
import sys
data = sys.stdin.readline().strip()

📌 Used when input size is 10⁵+



3️⃣ Loops (Advanced Patterns)
🔹 Loop with index + value
for i, val in enumerate(arr):
    print(i, val)

🔹 Reverse loop
for i in range(len(arr)-1, -1, -1):
    print(arr[i])


📌 Common in two-pointer & DP






4️⃣ Functions (Advanced)
🔹 Default arguments
def power(x, n=2):
    return x ** n

🔹 Pass by object reference (HARD TRAP)
def modify(x):
    x.append(100)

arr = [1, 2]
modify(arr)
print(arr)   # [1,2,100]

📌 Python is neither pass-by-value nor pass-by-reference





5️⃣ Lists (HARD LEVEL)
🔹 Shallow Copy vs Deep Copy
a = [1, 2, 3]
b = a[:]      # shallow copy

import copy
b = copy.deepcopy(a)


📌 Used in backtracking & recursion

🔹 List slicing traps
arr = [1, 2, 3, 4]
print(arr[1:3])   # [2,3]


End index excluded

Negative indexing allowed

🔹 Sorting with key (INTERVIEW GOLD)
arr = [(1,3),(2,1),(4,2)]
arr.sort(key=lambda x: x[1])


📌 Used in greedy algorithms




6️⃣ Tuples (Advanced)
Tuple as Dictionary Key
mp = {}
mp[(1,2)] = "point"


📌 Because tuples are hashable




7️⃣ Dictionaries (HARD LEVEL)
🔹 defaultdict vs dict
from collections import defaultdict
mp = defaultdict(list)


📌 Avoids KeyError in graph problems

🔹 Dictionary iteration
for k, v in mp.items():
    print(k, v)

🔹 Sorting dictionary by value
sorted(mp.items(), key=lambda x: x[1])


📌 Used in frequency-based problems






8️⃣ Sets (Advanced)
🔹 Set operations
a = {1,2,3}
b = {3,4,5}
print(a & b)   # intersection
print(a | b)   # union


📌 Used in graph + dedup problems





9️⃣ Strings (HARD LEVEL)
🔹 Strings are immutable
s = "abc"
s = s + "d"

📌 Every concat creates a new string

🔹 Efficient string building
res = []
res.append('a')
res.append('b')
print("".join(res))


📌 Critical for large inputs




🔟 List Comprehension (Advanced)
[x for x in range(10) if x % 2 == 0]

Nested:
[(i,j) for i in range(2) for j in range(2)]

📌 Used in matrix traversal




1️⃣1️⃣ lambda / map / filter (Interview Truth)

❌ Overused by beginners
✅ Useful in sorting & short transforms
arr.sort(key=lambda x: x[1])




1️⃣2️⃣ collections (HARD MODE)
🔹 Counter operations
from collections import Counter
c = Counter("aabbc")
print(c.most_common(1))

🔹 deque vs list
| Operation | list | deque |
| --------- | ---- | ----- |
| pop left  | O(n) | O(1)  |
| pop right | O(1) | O(1)  |


📌 Sliding window = deque




1️⃣3️⃣ heapq (HARD INTERVIEW LEVEL)
Max Heap Trick
import heapq
heap = []
heapq.heappush(heap, -10)

📌 Python has no max heap

K largest elements
heapq.nlargest(k, arr)





1️⃣4️⃣ bisect (ADVANCED)
Range count
count = bisect_right(arr, r) - bisect_left(arr, l)

📌 Used in offline queries




1️⃣5️⃣ Python Truths (HARD INTERVIEW)
Boolean evaluation
if arr:
    print("Not empty")

Chained comparison
if 0 < x < 10:
    pass


#Boolean Evaluation in Python (if arr:)
✅ What it means
if arr:

Python does NOT check length explicitly.
It calls:
bool(arr)

Truth rules:
| Object            | bool(obj) |
| ----------------- | --------- |
| Empty list `[]`   | False     |
| Non-empty list    | True      |
| Empty string `""` | False     |
| Non-empty string  | True      |
| 0                 | False     |
| None              | False     |

✅ Complete Code
def main():
    arr1 = []
    arr2 = [1, 2, 3]

    if arr1:
        print("arr1 is not empty")
    else:
        print("arr1 is empty")

    if arr2:
        print("arr2 is not empty")
    else:
        print("arr2 is empty")

if __name__ == "__main__":
    main()
""" 
🖥 Output
arr1 is empty
arr2 is not empty
"""

🧠 Interview Insight
❌ Bad style:
if len(arr) > 0:

✅ Pythonic & faster:
if arr:

🔹 2️⃣ Chained Comparison (if 0 < x < 10:)
✅ What it means
if 0 < x < 10:

Python internally converts this to:
if (0 < x) and (x < 10):

✔ x is evaluated only once


✅ Complete Code
def main():
    x = 7

    if 0 < x < 10:
        print("x is between 0 and 10")
    else:
        print("x is outside the range")

if __name__ == "__main__":
    main()

""" 
🖥 Output
x is between 0 and 10
"""
🔍 Compare with wrong C/C++ style (TRAP)
if 0 < x and x < 10:   # correct but verbose

❌ INVALID in C/C++
0 < x < 10   // wrong in C++

✔ VALID in Python




🔥 HARD Interview Demonstration
def main():
    x = -5

    print(0 < x < 10)
    print(0 < x and x < 10)

if __name__ == "__main__":
    main()

""" 
🖥 Output
False
False
"""

🧠 Why Python does this?
Cleaner syntax
Fewer comparisons
Less bug-prone
Faster execution

🧪 Bonus Truth (VERY HARD)
def main():
    a = []
    b = []

    print(a == b)
    print(a is b)

if __name__ == "__main__":
    main()

""" 
🖥 Output
True
False
"""
📌 == → value comparison
📌 is → memory comparison

🎯 Interview One-Line Answers
Boolean evaluation:
Python evaluates objects directly in conditions using their truth value.

Chained comparison:
Python allows chained comparisons which are equivalent to logical AND but more readable and efficient.