🧩 PHASE-1: Absolute Basics (1–20)
1️⃣ Print “Hello, World!”
💡 Concept
Basic printing.


✅ Code
def main():
    print("Hello, World!")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Hello, World!

🧠 Dry Run
print() sends text to output.

⚠ Edge Case
None.
"""


2️⃣ Print your name
def main():
    name = "Aman"
    print(name)

if __name__ == "__main__":
    main()

""" 
Output
Aman

Dry Run
Variable name stores string.
Printed once.
"""


3️⃣ Add two numbers
def main():
    a = 10
    b = 20
    print(a + b)

if __name__ == "__main__":
    main()

""" 
Output
30

Dry Run
a = 10, b = 20
a + b = 30

Edge Case
Large numbers still work (Python handles big integers).
"""




4️⃣ Take input and print it
def main():
    x = input("Enter value: ")
    print(x)

if __name__ == "__main__":
    main()

""" 
Output
Enter value: 5
5

Dry Run
input() always returns string.

⚠ Edge Case
Input "5" is string, not integer.
"""


5️⃣ Convert string to integer
def main():
    x = input("Enter number: ")
    y = int(x)
    print(y + 1)

if __name__ == "__main__":
    main()

""" 
Output
Enter number: 5
6

Dry Run
"5" → int(5)
5 + 1 = 6

⚠ Edge Case
Input "abc" → ❌ ValueError
"""


6️⃣ Check even or odd
def main():
    n = 4
    if n % 2 == 0:
        print("Even")
    else:
        print("Odd")

if __name__ == "__main__":
    main()

""" 
Output
Even

Dry Run
4 % 2 = 0
Condition true

⚠ Edge Case
Negative numbers still valid.
"""



7️⃣ Find greater of two numbers
def main():
    a = 10
    b = 20

    if a > b:
        print(a)
    else:
        print(b)

if __name__ == "__main__":
    main()

""" 
Output
20

Dry Run
10 > 20 → False
"""



8️⃣ Check positive, negative or zero
def main():
    n = -5

    if n > 0:
        print("Positive")
    elif n < 0:
        print("Negative")
    else:
        print("Zero")

if __name__ == "__main__":
    main()

""" 
Output
Negative
"""




9️⃣ Print numbers from 1 to 5
def main():
    for i in range(1, 6):
        print(i)

if __name__ == "__main__":
    main()


""" 
Output
1
2
3
4
5

Dry Run
range(1,6) → 1 to 5
"""



🔟 Sum of first N numbers
def main():
    n = 5
    total = 0

    for i in range(1, n + 1):
        total += i

    print(total)

if __name__ == "__main__":
    main()

""" 
Output
15

Dry Run
1+2+3+4+5 = 15

⚠ Edge Case
n = 0 → sum = 0
"""




1️⃣1️⃣ Multiplication table
def main():
    n = 3
    for i in range(1, 11):
        print(n * i)

if __name__ == "__main__":
    main()






1️⃣2️⃣ Count digits in a number
def main():
    n = 1234
    count = 0

    while n > 0:
        count += 1
        n //= 10

    print(count)

if __name__ == "__main__":
    main()


⚠ Edge Case
n = 0 → should manually print 1






1️⃣3️⃣ Reverse a number
def main():
    n = 123
    rev = 0

    while n > 0:
        rev = rev * 10 + n % 10
        n //= 10

    print(rev)

if __name__ == "__main__":
    main()






1️⃣4️⃣ Check palindrome number
def main():
    n = 121
    temp = n
    rev = 0

    while n > 0:
        rev = rev * 10 + n % 10
        n //= 10

    print(temp == rev)

if __name__ == "__main__":
    main()




1️⃣5️⃣ Sum of digits
def main():
    n = 123
    s = 0

    while n > 0:
        s += n % 10
        n //= 10

    print(s)

if __name__ == "__main__":
    main()





1️⃣6️⃣ Factorial of a number
def main():
    n = 5
    fact = 1

    for i in range(1, n + 1):
        fact *= i

    print(fact)

if __name__ == "__main__":
    main()


⚠ Edge Case
0! = 1





1️⃣7️⃣ Check prime number
def main():
    n = 7
    is_prime = True

    if n <= 1:
        is_prime = False
    else:
        for i in range(2, n):
            if n % i == 0:
                is_prime = False
                break

    print(is_prime)

if __name__ == "__main__":
    main()





1️⃣8️⃣ Print all even numbers till N
def main():
    n = 10
    for i in range(2, n + 1, 2):
        print(i)

if __name__ == "__main__":
    main()





1️⃣9️⃣ Find largest in list
def main():
    arr = [3, 7, 2, 9]
    print(max(arr))

if __name__ == "__main__":
    main()




2️⃣0️⃣ Count elements in list
def main():
    arr = [1, 2, 3, 4]
    count = 0

    for _ in arr:
        count += 1

    print(count)

if __name__ == "__main__":
    main()






2️⃣1️⃣ Count characters in a string
Concept
Length of string without using len().

Code
def main():
    s = "python"
    count = 0

    for _ in s:
        count += 1

    print(count)

if __name__ == "__main__":
    main()

""" 
Output
6

Dry Run
Loop runs once per character
count increments 6 times

Edge Case
Empty string → count = 0
"""




2️⃣2️⃣ Reverse a string
def main():
    s = "python"
    rev = ""

    for ch in s:
        rev = ch + rev

    print(rev)

if __name__ == "__main__":
    main()

""" 
Output
nohtyp

Dry Run
p → "p"
y → "yp"
…

final reversed string
"""



2️⃣3️⃣ Check palindrome string
def main():
    s = "madam"
    print(s == s[::-1])

if __name__ == "__main__":
    main()

""" 
Output
True
Edge Case
Single character → always palindrome
"""



2️⃣4️⃣ Count vowels in string
def main():
    s = "education"
    vowels = "aeiou"
    count = 0

    for ch in s:
        if ch in vowels:
            count += 1

    print(count)

if __name__ == "__main__":
    main()

""" 
Output
5
"""




2️⃣5️⃣ Convert string to uppercase
def main():
    s = "python"
    print(s.upper())

if __name__ == "__main__":
    main()

""" 
Output
PYTHON
"""




2️⃣6️⃣ Replace space with underscore
def main():
    s = "hello world python"
    print(s.replace(" ", "_"))

if __name__ == "__main__":
    main()

""" 
Output
hello_world_python
"""



2️⃣7️⃣ Find frequency of a character
def main():
    s = "banana"
    ch = 'a'
    count = 0

    for c in s:
        if c == ch:
            count += 1

    print(count)

if __name__ == "__main__":
    main()

""" 
Output
3
"""




2️⃣8️⃣ Split string into words
def main():
    s = "learn python step by step"
    words = s.split()
    print(words)

if __name__ == "__main__":
    main()

""" 
Output
['learn', 'python', 'step', 'by', 'step']
"""




2️⃣9️⃣ Find length of each word
def main():
    s = "python is easy"
    words = s.split()

    for w in words:
        print(w, len(w))

if __name__ == "__main__":
    main()

""" 
Output
python 6
is 2
easy 4
"""



3️⃣0️⃣ Check if string contains only digits
def main():
    s = "12345"
    print(s.isdigit())

if __name__ == "__main__":
    main()

""" 
Output
True
"""



🔹 LIST PROBLEMS
3️⃣1️⃣ Print list elements
def main():
    arr = [10, 20, 30]
    for x in arr:
        print(x)

if __name__ == "__main__":
    main()



3️⃣2️⃣ Sum of list elements
def main():
    arr = [1, 2, 3, 4]
    total = 0

    for x in arr:
        total += x

    print(total)

if __name__ == "__main__":
    main()

""" 
Output
10
"""



3️⃣3️⃣ Find largest element (manual)
def main():
    arr = [3, 7, 2, 9]
    max_val = arr[0]

    for x in arr:
        if x > max_val:
            max_val = x

    print(max_val)

if __name__ == "__main__":
    main()





3️⃣4️⃣ Find smallest element
def main():
    arr = [3, 7, 2, 9]
    min_val = arr[0]

    for x in arr:
        if x < min_val:
            min_val = x

    print(min_val)

if __name__ == "__main__":
    main()






3️⃣5️⃣ Count even numbers in list
def main():
    arr = [1, 2, 3, 4, 6]
    count = 0

    for x in arr:
        if x % 2 == 0:
            count += 1

    print(count)

if __name__ == "__main__":
    main()

""" 
Output
3
"""



3️⃣6️⃣ Reverse a list
def main():
    arr = [1, 2, 3]
    rev = []

    for x in arr:
        rev = [x] + rev

    print(rev)

if __name__ == "__main__":
    main()




3️⃣7️⃣ Check element exists in list
def main():
    arr = [10, 20, 30]
    print(20 in arr)

if __name__ == "__main__":
    main()

""" 
Output
True
"""



3️⃣8️⃣ Remove duplicates from list
def main():
    arr = [1, 2, 2, 3, 1]
    result = []

    for x in arr:
        if x not in result:
            result.append(x)

    print(result)

if __name__ == "__main__":
    main()

""" 
Output
[1, 2, 3]
"""



3️⃣9️⃣ Count frequency of elements
def main():
    arr = [1, 2, 2, 3, 1]
    freq = {}

    for x in arr:
        freq[x] = freq.get(x, 0) + 1

    print(freq)

if __name__ == "__main__":
    main()

""" 
Output
{1: 2, 2: 2, 3: 1}
"""



4️⃣0️⃣ Merge two lists
def main():
    a = [1, 2]
    b = [3, 4]
    c = a + b
    print(c)

if __name__ == "__main__":
    main()

""" 
Output
[1, 2, 3, 4]
"""





4️⃣1️⃣ Simple function to add two numbers
Concept
Functions make code reusable.

def add(a, b):
    return a + b

def main():
    print(add(3, 4))

if __name__ == "__main__":
    main()

""" 
Output
7

Dry Run
add(3,4) → returns 7

Edge Case
Works for negative numbers too.
"""



4️⃣2️⃣ Function to find square of number
def square(n):
    return n * n

def main():
    print(square(5))

if __name__ == "__main__":
    main()

""" 
Output
25
"""



4️⃣3️⃣ Function with default argument
def greet(name="User"):
    print("Hello", name)

def main():
    greet()
    greet("Aman")

if __name__ == "__main__":
    main()

""" 
Output
Hello User
Hello Aman
"""


4️⃣4️⃣ Return multiple values from function
def calc(a, b):
    return a + b, a - b

def main():
    s, d = calc(10, 3)
    print(s, d)

if __name__ == "__main__":
    main()

""" 
Output
13 7
"""



4️⃣5️⃣ Check even using function
def is_even(n):
    return n % 2 == 0

def main():
    print(is_even(8))

if __name__ == "__main__":
    main()

""" 
Output
True
"""




🔹 TUPLES
4️⃣6️⃣ Access tuple elements
def main():
    t = (10, 20, 30)
    print(t[1])

if __name__ == "__main__":
    main()

""" 
Output
20

Edge Case
Tuples are immutable → t[0]=5 ❌
"""


4️⃣7️⃣ Count element in tuple
def main():
    t = (1, 2, 2, 3)
    print(t.count(2))

if __name__ == "__main__":
    main()

""" 
Output
2
"""



4️⃣8️⃣ Find max in tuple
def main():
    t = (5, 3, 9, 1)
    print(max(t))

if __name__ == "__main__":
    main()




4️⃣9️⃣ Convert list to tuple
def main():
    arr = [1, 2, 3]
    t = tuple(arr)
    print(t)

if __name__ == "__main__":
    main()





🔹 SETS
5️⃣0️⃣ Remove duplicates using set
def main():
    arr = [1, 2, 2, 3]
    s = set(arr)
    print(s)

if __name__ == "__main__":
    main()

""" 
Output
{1, 2, 3}

Edge Case
Order is not preserved.
"""


5️⃣1️⃣ Union of two sets
def main():
    a = {1, 2}
    b = {2, 3}
    print(a | b)

if __name__ == "__main__":
    main()

""" 
Output
{1, 2, 3}
"""



5️⃣2️⃣ Intersection of sets
def main():
    a = {1, 2, 3}
    b = {2, 3, 4}
    print(a & b)

if __name__ == "__main__":
    main()

""" 
Output
{2, 3}
"""



5️⃣3️⃣ Difference of sets
def main():
    a = {1, 2, 3}
    b = {2}
    print(a - b)

if __name__ == "__main__":
    main()

Output
{1, 3}





🔹 DICTIONARIES
5️⃣4️⃣ Access dictionary values
def main():
    d = {"name": "Python", "ver": 3}
    print(d["name"])

if __name__ == "__main__":
    main()



5️⃣5️⃣ Add key to dictionary
def main():
    d = {}
    d["x"] = 10
    print(d)

if __name__ == "__main__":
    main()




5️⃣6️⃣ Loop through dictionary
def main():
    d = {"a": 1, "b": 2}

    for k, v in d.items():
        print(k, v)

if __name__ == "__main__":
    main()

""" 
Output
a 1
b 2
"""



5️⃣7️⃣ Count frequency using dictionary
def main():
    arr = [1, 2, 2, 3]
    freq = {}

    for x in arr:
        freq[x] = freq.get(x, 0) + 1

    print(freq)

if __name__ == "__main__":
    main()






🔹 NESTED LOOPS
5️⃣8️⃣ Print square pattern
def main():
    for i in range(3):
        for j in range(3):
            print("*", end=" ")
        print()

if __name__ == "__main__":
    main()

""" 
Output
* * *
* * *
* * *
"""



5️⃣9️⃣ Number triangle
def main():
    for i in range(1, 4):
        for j in range(1, i + 1):
            print(j, end=" ")
        print()

if __name__ == "__main__":
    main()

""" 
Output
1
1 2
1 2 3
"""



6️⃣0️⃣ Multiplication table (1 to 3)
def main():
    for i in range(1, 4):
        for j in range(1, 4):
            print(i * j, end=" ")
        print()

if __name__ == "__main__":
    main()

""" 
Output
1 2 3
2 4 6
3 6 9
"""




6️⃣1️⃣ Print numbers from 1 to N
def main():
    n = 5
    for i in range(1, n + 1):
        print(i, end=" ")

if __name__ == "__main__":
    main()
"""
Output
1 2 3 4 5
"""

6️⃣2️⃣ Sum of elements in list
def main():
    arr = [1, 2, 3, 4]
    s = 0
    for x in arr:
        s += x
    print(s)

if __name__ == "__main__":
    main()
"""
Output
10
"""

6️⃣3️⃣ Count even numbers in list
def main():
    arr = [1, 2, 4, 5, 6]
    count = 0
    for x in arr:
        if x % 2 == 0:
            count += 1
    print(count)

if __name__ == "__main__":
    main()
"""
Output
3
"""

6️⃣4️⃣ Find maximum element
def main():
    arr = [3, 9, 1, 6]
    mx = arr[0]
    for x in arr:
        if x > mx:
            mx = x
    print(mx)

if __name__ == "__main__":
    main()
"""
Output
9
"""

6️⃣5️⃣ Find minimum element
def main():
    arr = [3, 9, 1, 6]
    mn = arr[0]
    for x in arr:
        if x < mn:
            mn = x
    print(mn)

if __name__ == "__main__":
    main()
"""
Output
1
"""

6️⃣6️⃣ Reverse a list
def main():
    arr = [1, 2, 3]
    rev = []
    for x in arr:
        rev = [x] + rev
    print(rev)

if __name__ == "__main__":
    main()
"""
Output
[3, 2, 1]
"""

6️⃣7️⃣ Check element present in list
def main():
    arr = [10, 20, 30]
    print(20 in arr)

if __name__ == "__main__":
    main()
"""
Output
True
"""

6️⃣8️⃣ Remove duplicates from list
def main():
    arr = [1, 2, 2, 3, 1]
    res = []
    for x in arr:
        if x not in res:
            res.append(x)
    print(res)

if __name__ == "__main__":
    main()
"""
Output
[1, 2, 3]
"""

6️⃣9️⃣ Count frequency of list elements
def main():
    arr = [1, 2, 2, 3]
    freq = {}
    for x in arr:
        freq[x] = freq.get(x, 0) + 1
    print(freq)

if __name__ == "__main__":
    main()
"""
Output
{1: 1, 2: 2, 3: 1}
"""

7️⃣0️⃣ Sum of digits of number
def main():
    n = 123
    s = 0
    while n > 0:
        s += n % 10
        n //= 10
    print(s)

if __name__ == "__main__":
    main()
"""
Output
6
"""

7️⃣1️⃣ Reverse a number
def main():
    n = 123
    rev = 0
    while n > 0:
        rev = rev * 10 + n % 10
        n //= 10
    print(rev)

if __name__ == "__main__":
    main()
"""
Output
321
"""

7️⃣2️⃣ Check palindrome number
def main():
    n = 121
    temp = n
    rev = 0
    while n > 0:
        rev = rev * 10 + n % 10
        n //= 10
    print(temp == rev)

if __name__ == "__main__":
    main()
"""
Output
True
"""

7️⃣3️⃣ Factorial of a number
def main():
    n = 5
    fact = 1
    for i in range(1, n + 1):
        fact *= i
    print(fact)

if __name__ == "__main__":
    main()
"""
Output
120
"""

7️⃣4️⃣ Check prime number
def main():
    n = 7
    prime = True
    if n <= 1:
        prime = False
    else:
        for i in range(2, n):
            if n % i == 0:
                prime = False
                break
    print(prime)

if __name__ == "__main__":
    main()
"""
Output
True
"""

7️⃣5️⃣ Print even numbers till N
def main():
    n = 10
    for i in range(2, n + 1, 2):
        print(i, end=" ")

if __name__ == "__main__":
    main()
"""
Output
2 4 6 8 10
"""

7️⃣6️⃣ Count characters in string
def main():
    s = "python"
    count = 0
    for _ in s:
        count += 1
    print(count)

if __name__ == "__main__":
    main()
"""
Output
6
"""

7️⃣7️⃣ Reverse a string
def main():
    s = "python"
    rev = ""
    for ch in s:
        rev = ch + rev
    print(rev)

if __name__ == "__main__":
    main()
"""
Output
nohtyp
"""

7️⃣8️⃣ Check palindrome string
def main():
    s = "madam"
    print(s == s[::-1])

if __name__ == "__main__":
    main()
"""
Output
True
"""

7️⃣9️⃣ Count vowels in string
def main():
    s = "education"
    vowels = "aeiou"
    count = 0
    for ch in s:
        if ch in vowels:
            count += 1
    print(count)

if __name__ == "__main__":
    main()
"""
Output
5
"""

8️⃣0️⃣ Merge two lists
def main():
    a = [1, 2]
    b = [3, 4]
    c = a + b
    print(c)

if __name__ == "__main__":
    main()
"""
Output
[1, 2, 3, 4]
"""



8️⃣1️⃣ Find length of list
def main():
    arr = [1, 2, 3, 4]
    count = 0
    for _ in arr:
        count += 1
    print(count)

if __name__ == "__main__":
    main()
"""
Output
4
"""

8️⃣2️⃣ Check list is empty
def main():
    arr = []
    print(len(arr) == 0)

if __name__ == "__main__":
    main()
"""
Output
True
"""

8️⃣3️⃣ Find second largest element
def main():
    arr = [10, 20, 5, 8]
    arr = list(set(arr))
    arr.sort()
    print(arr[-2])

if __name__ == "__main__":
    main()
"""
Output
10
"""

8️⃣4️⃣ Count positive numbers
def main():
    arr = [-1, 2, 3, -4, 5]
    count = 0
    for x in arr:
        if x > 0:
            count += 1
    print(count)

if __name__ == "__main__":
    main()
"""
Output
3
"""

8️⃣5️⃣ Find common elements in two lists
def main():
    a = [1, 2, 3]
    b = [2, 3, 4]
    common = []
    for x in a:
        if x in b:
            common.append(x)
    print(common)

if __name__ == "__main__":
    main()
"""
Output
[2, 3]
"""

8️⃣6️⃣ Convert list to string
def main():
    arr = ['p', 'y', 't', 'h', 'o', 'n']
    s = ""
    for ch in arr:
        s += ch
    print(s)

if __name__ == "__main__":
    main()
"""
Output
python
"""

8️⃣7️⃣ Count words in string
def main():
    s = "python is very easy"
    words = s.split()
    print(len(words))

if __name__ == "__main__":
    main()
"""
Output
4
"""

8️⃣8️⃣ Find longest word
def main():
    s = "python is very powerful"
    words = s.split()
    longest = words[0]
    for w in words:
        if len(w) > len(longest):
            longest = w
    print(longest)

if __name__ == "__main__":
    main()
"""
Output
powerful
"""

8️⃣9️⃣ Replace character in string
def main():
    s = "banana"
    print(s.replace('a', 'o'))

if __name__ == "__main__":
    main()
"""
Output
bonono
"""

9️⃣0️⃣ Count uppercase letters
def main():
    s = "PyThOn"
    count = 0
    for ch in s:
        if ch.isupper():
            count += 1
    print(count)

if __name__ == "__main__":
    main()
"""
Output
3
"""

9️⃣1️⃣ Check string is alphabetic
def main():
    s = "Python"
    print(s.isalpha())

if __name__ == "__main__":
    main()
"""
Output
True
"""

9️⃣2️⃣ Swap two numbers
def main():
    a = 5
    b = 10
    a, b = b, a
    print(a, b)

if __name__ == "__main__":
    main()
"""
Output
10 5
"""

9️⃣3️⃣ Generate Fibonacci series
def main():
    n = 5
    a, b = 0, 1
    for _ in range(n):
        print(a, end=" ")
        a, b = b, a + b

if __name__ == "__main__":
    main()
"""
Output
0 1 1 2 3
"""

9️⃣4️⃣ Find GCD of two numbers
def main():
    a = 12
    b = 18
    while b != 0:
        a, b = b, a % b
    print(a)

if __name__ == "__main__":
    main()
"""
Output
6
"""

9️⃣5️⃣ Find LCM of two numbers
def main():
    a = 4
    b = 6
    max_val = max(a, b)
    while True:
        if max_val % a == 0 and max_val % b == 0:
            print(max_val)
            break
        max_val += 1

if __name__ == "__main__":
    main()
"""
Output
12
"""

9️⃣6️⃣ Check Armstrong number
def main():
    n = 153
    temp = n
    s = 0
    while n > 0:
        digit = n % 10
        s += digit ** 3
        n //= 10
    print(s == temp)

if __name__ == "__main__":
    main()
"""
Output
True
"""

9️⃣7️⃣ Print ASCII value of character
def main():
    ch = 'A'
    print(ord(ch))

if __name__ == "__main__":
    main()
"""
Output
65
"""

9️⃣8️⃣ Convert ASCII to character
def main():
    val = 65
    print(chr(val))

if __name__ == "__main__":
    main()
"""
Output
A
"""

9️⃣9️⃣ Check leap year
def main():
    year = 2024
    if year % 400 == 0 or (year % 4 == 0 and year % 100 != 0):
        print(True)
    else:
        print(False)

if __name__ == "__main__":
    main()
"""
Output
True
"""

🔟0️⃣0️⃣ Simple calculator
def main():
    a = 10
    b = 5
    print(a + b)
    print(a - b)
    print(a * b)
    print(a // b)

if __name__ == "__main__":
    main()
"""
Output
15
5
50
2
"""