'''
1. Python Basics (Print & Variables)
print() displays output
Variables store data (no type declaration needed)
'''
#✅ Program
def main():
    name = "Alex"          #indentaion is must 1-tab or 4-spaces 
    age = 15               #indentaion is must 1-tab or 4-spaces 
    print("Name:", name)
    print("Age:", age)

if __name__ == "__main__":
    main()

'''
🖥 Output
Name: Alex
Age: 15
'''





1️⃣ Keywords
📌 What are keywords?
Keywords are reserved words in Python with special meaning.
You cannot use them as variable names.

🔑 Common Keywords
if, else, elif, for, while, break, continue, return, True, False, None, class, def, import

✅ Example
def main():
    # if = 5   ❌ Invalid
    value = 5   # ✅ Valid
    print(value)

if __name__ == "__main__":
    main()

""" 
🖥 Output
5
"""




2️⃣ Variables
📌 What is a variable?
A variable stores data in memory.
Python is dynamically typed → no need to declare type.

✅ Example
def main():
    x = 10
    y = 3.5
    name = "Python"

    print(x)
    print(y)
    print(name)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
3.5
Python
"""

3️⃣ Data Types
📌 Built-in Data Types
| Type     | Example      |
| -------- | ------------ |
| int      | 10           |
| float    | 3.14         |
| str      | "Hello"      |
| bool     | True / False |
| list     | [1,2,3]      |
| tuple    | (1,2,3)      |
| set      | {1,2,3}      |
| dict     | {"a":1}      |
| NoneType | None         |



✅ Example
def main():
    a = 10
    b = 2.5
    c = "Hi"
    d = True
    e = [1,2,3]
    f = (1,2)
    g = {1,2}
    h = {"x":10}

    print(type(a), type(b), type(c))
    print(type(d), type(e), type(f))
    print(type(g), type(h))

if __name__ == "__main__":
    main()

""" 
🖥 Output
<class 'int'> <class 'float'> <class 'str'>
<class 'bool'> <class 'list'> <class 'tuple'>
<class 'set'> <class 'dict'>
"""





4️⃣ Operators
📌 Types of Operators
Arithmetic: + - * / % // **
Relational: > < >= <= == !=
Logical: and or not
Assignment: = += -=
Membership: in, not in

✅ Example
def main():
    a = 10
    b = 3

    print(a + b)
    print(a > b)
    print(a % b)
    print(a and b)

if __name__ == "__main__":
    main()

""" 
🖥 Output
13
True
1
3
"""



5️⃣ Conditional Statements
📌 Used for decision making
Syntax
if condition:
    ...
elif condition:
    ...
else:
    ...

✅ Example
def main():
    x = 10

    if x > 0:
        print("Positive")
    elif x == 0:
        print("Zero")
    else:
        print("Negative")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Positive
"""



6️⃣ Loops
📌 Used to repeat code
🔁 for Loop
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



🔁 while Loop
def main():
    i = 1
    while i <= 3:
        print(i)
        i += 1

if __name__ == "__main__":
    main()


""" 
🖥 Output
1
2
3
"""



7️⃣ Control Statements
📌 Used inside loops
break → stop loop
continue → skip iteration
pass → placeholder

✅ Example
def main():
    for i in range(1, 6):
        if i == 3:
            continue
        print(i)

if __name__ == "__main__":
    main()

""" 
🖥 Output
1
2
4
5
"""




8️⃣ Functions ⭐ (VERY IMPORTANT)
📌 Reusable block of code
Syntax
def function_name():
    ...

✅ Example
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
"""



9️⃣ Input & Output
📌 Taking input from user
✅ Example
def main():
    name = input("Enter name: ")
    print("Hello", name)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter name: Aman
Hello Aman
"""



🔟 Type Casting
📌 Converting one type to another
✅ Example
def main():
    a = "10"
    b = int(a)
    print(b + 5)

if __name__ == "__main__":
    main()

""" 
🖥 Output
15
"""



1️⃣1️⃣ Strings
📌 String operations
Indexing
Slicing
Methods

✅ Example
def main():
    s = "Python"
    print(s[0])
    print(s[1:4])
    print(s.upper())

if __name__ == "__main__":
    main()


""" 
🖥 Output
P
yth
PYTHON
"""


1️⃣2️⃣ Lists (Most Used)
📌 Mutable, ordered collection
✅ Example
def main():
    arr = [1, 2, 3]
    arr.append(4)
    arr.remove(2)
    print(arr)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[1, 3, 4]
"""



1️⃣3️⃣ Tuples
📌 Immutable collection
def main():
    t = (1, 2, 3)
    print(t[0])

if __name__ == "__main__":
    main()

""" 
🖥 Output
1
"""



1️⃣4️⃣ Dictionaries
📌 Key–Value pairs
def main():
    d = {"name": "Python", "version": 3}
    print(d["name"])

if __name__ == "__main__":
    main()

""" 
🖥 Output
Python
"""



1️⃣5️⃣ Sets
📌 Unique elements only
def main():
    s = {1, 2, 2, 3}
    print(s)

if __name__ == "__main__":
    main()

""" 
🖥 Output
{1, 2, 3}
"""