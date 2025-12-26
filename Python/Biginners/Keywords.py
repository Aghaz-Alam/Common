'''
Python Keywords & Comments
🔹 Short Notes
Keywords are reserved words (if, else, while, etc.)
Comments improve readability
'''

# → single-line comment

#✅ Program
def main():
    # This is a comment
    print("Python is easy")

if __name__ == "__main__":
    main()

'''
🖥 Output
Python is easy
'''









#1️⃣ if, else
def main():
    x = 10
    if x > 5:
        print("Greater than 5")
    else:
        print("Less than or equal to 5")

if __name__ == "__main__":
    main()

'''
🖥 Output
Greater than 5
'''




#2️⃣ elif
def main():
    x = 0
    if x > 0:
        print("Positive")
    elif x == 0:
        print("Zero")
    else:
        print("Negative")

if __name__ == "__main__":
    main()

'''
🖥 Output
Zero
'''




#3️⃣ while
def main():
    i = 1
    while i <= 3:
        print(i)
        i += 1

if __name__ == "__main__":
    main()

'''
🖥 Output
1
2
3
'''




#4️⃣ for
def main():
    for i in range(3):
        print("Hello")

if __name__ == "__main__":
    main()

'''
🖥 Output
Hello
Hello
Hello
'''


#5️⃣ break
def main():
    for i in range(5):
        if i == 3:
            break
        print(i)

if __name__ == "__main__":
    main()

'''
🖥 Output
0
1
2
'''



#6️⃣ continue
def main():
    for i in range(5):
        if i == 2:
            continue
        print(i)

if __name__ == "__main__":
    main()

'''
🖥 Output
0
1
3
4
'''




#7️⃣ pass
def main():
    if True:
        pass
    print("Pass executed")

if __name__ == "__main__":
    main()

'''
🖥 Output
Pass executed
'''



#8️⃣ def, return
def add():
    return 5 + 3

def main():
    print(add())

if __name__ == "__main__":
    main()

'''
🖥 Output
8
'''




#9️⃣ True, False
def main():
    x = True
    if x:
        print("True value")

if __name__ == "__main__":
    main()

'''
🖥 Output
True value
'''



#🔟 and, or, not
def main():
    a = 5
    b = 10
    if a < b and b > 5:
        print("Condition true")

if __name__ == "__main__":
    main()

'''
🖥 Output
Condition true
'''


# or
def main():
    a = 5
    b = 10
    if a > b or b > 5:
        print("Condition true")

if __name__ == "__main__":
    main()

'''
🖥 Output
Condition true
'''




# not
def main():
    a = 5
    if not a > 10:
        print("Condition true")

if __name__ == "__main__":
    main()

'''
🖥 Output
Condition true
'''




#1️⃣1️⃣ in
def main():
    x = "a"
    if x in "apple":
        print("Found")

if __name__ == "__main__":
    main()

'''
🖥 Output
Found
'''




#1️⃣2️⃣ is
def main():
    a = None
    if a is None:
        print("None value")

if __name__ == "__main__":
    main()

'''
🖥 Output
None value
'''




#1️⃣3️⃣ None
def main():
    x = None
    print(x)

if __name__ == "__main__":
    main()

'''
🖥 Output
None
'''




#1️⃣4️⃣ try, except
def main():
    try:
        print(10 / 0)
    except:
        print("Error occurred")

if __name__ == "__main__":
    main()

'''
🖥 Output
Error occurred
'''




#1️⃣5️⃣ finally
def main():
    try:
        print("Try block")
    finally:
        print("Finally block")

if __name__ == "__main__":
    main()

'''
🖥 Output
Try block
Finally block
'''



#1️⃣6️⃣ class
class Student:
    def show(self):
        print("Student class")

def main():
    s = Student()
    s.show()

if __name__ == "__main__":
    main()

'''
🖥 Output
Student class
'''





#1️⃣7️⃣ import
import math

def main():
    print(math.sqrt(16))

if __name__ == "__main__":
    main()

'''
🖥 Output
4.0
'''







#1️⃣8️⃣ global
x = 10
def main():
    global x
    x = 20
    print(x)

if __name__ == "__main__":
    main()

'''
🖥 Output
20
'''