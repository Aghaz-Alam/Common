1.Your First Python Program
   print("Hello, World!")
  📌 print() displays output on the screen


2.Variables (Storing Data)
   name = "Aman"
   age = 21
   price = 99.5

✔ No need to define data type
✔ Python decides automatically



3. Data Types
| Type  | Example         |
| ----- | --------------- |
| int   | `10`            |
| float | `10.5`          |
| str   | `"Hello"`       |
| bool  | `True`, `False` |

x = 10
y = 3.14
z = "Python"

4. Input from User
name = input("Enter your name: ")
print("Hello", name)

Input is always string
Convert when needed:
age = int(input("Enter age: "))


5. Operators
   Arithmetic:  +  -  *  /  %  **  //

a = 10
b = 3
print(a + b)   # 13
print(a // b)  # 3



6. Conditional Statements (if–else)
age = 18

if age >= 18:
    print("You can vote")
else:
    print("You cannot vote")

📌 Python uses indentation, not braces {}



7. Loops
🔹 for loop
for i in range(1, 6):
    print(i)

🔹 while loop
i = 1
while i <= 5:
    print(i)
    i += 1



8. Lists (Collection of Items)
   numbers = [1, 2, 3, 4]
   print(numbers[0])  # 1

   Add items:
   numbers.append(5)


""" ================================================ """
Example List
numbers = [1, 2, 3, 4, 5]

Length of list = 5

Positive Indexing (Left → Right)
Positive indices start from 0.
Index:     0   1   2   3   4
List:     [1,  2,  3,  4,  5]

Examples:
numbers[0]  # 1
numbers[1]  # 2
numbers[4]  # 5

📌 Rule:
First element → index 0
Last element → length − 1




Negative Indexing (Right → Left)
Negative indices start from -1.
Index:    -5  -4  -3  -2  -1
List:     [1,  2,  3,  4,  5]

Examples:
numbers[-1]  # 5  (last element)
numbers[-2]  # 4
numbers[-5]  # 1

📌 Rule:
Last element → -1
First element → -length




Getting All Indices from List
#code Using range(): 
for i in range(len(numbers)):
    print(i, numbers[i])

Output:
0 1
1 2
2 3
3 4
4 5



Getting Negative Indices Programmatically
#code
length = len(numbers)
for i in range(length):
    print(i - length, numbers[i])

Output:
-5 1
-4 2
-3 3
-2 4
-1 5

""" ================================================ """

9. Functions
def add(a, b):
    return a + b

result = add(3, 4)
print(result)

✔ Code reuse
✔ Cleaner programs