'''
3. Type Casting
🔹 Short Notes
Convert one data type to another
Common functions: int(), float(), str()


Type Casting means converting one data type into another.
🔹 Common Type Casting Functions
int() → converts to integer
float() → converts to float
str() → converts to string
bool() → converts to boolean



🔹 Types of Type Casting
Implicit Type Casting
Done automatically by Python
Example: int + float → float

Explicit Type Casting
Done manually by programmer
Example: int("10")
'''

#✅ Program
def main():
    x = "10"
    y = int(x)
    print(y + 5)

if __name__ == "__main__":
    main()

'''
🖥 Output
15
'''




#1. String to Integer
def main():
    x = "25"
    y = int(x)
    print(y + 5)

if __name__ == "__main__":
    main()

'''
🖥 Output
30
'''


'''
#1️⃣ String to Integer
def main():
    x = "10"        # x is a string
    y = int(x)      # converting string to integer
    print(y + 5)    # adding integer

if __name__ == "__main__":
    main()
'''


#2. String to Float
def main():
    x = "12.5"
    y = float(x)
    print(y + 2.5)

if __name__ == "__main__":
    main()

'''
🖥 Output
15.0
'''



#3. Integer to Float
def main():
    x = 10
    y = float(x)
    print(y)

if __name__ == "__main__":
    main()

'''
🖥 Output
10.0
'''


'''
2️⃣ Integer to Float
def main():
    x = 5           # integer value
    y = float(x)    # convert int to float
    print(y)

if __name__ == "__main__":
    main()
'''


#4. Float to Integer
def main():
    x = 9.8
    y = int(x)
    print(y)

if __name__ == "__main__":
    main()

'''
🖥 Output
9
'''
'''
3️⃣ Float to Integer
def main():
    x = 8.9         # float value
    y = int(x)      # decimal part removed
    print(y)

if __name__ == "__main__":
    main()
'''


#5. Integer to String
def main():
    x = 100
    y = str(x)
    print(y + " rupees")

if __name__ == "__main__":
    main()

'''
🖥 Output
100 rupees
'''

'''
4️⃣ Integer to String
def main():
    x = 20
    y = str(x)      # convert int to string
    print(y + " apples")

if __name__ == "__main__":
    main()
'''


#6. Float to String
def main():
    x = 7.5
    y = str(x)
    print("Value is " + y)

if __name__ == "__main__":
    main()

'''
🖥 Output
Value is 7.5
'''



#6 String to Float
def main():
    x = "3.5"
    y = float(x)
    print(y + 1.5)

if __name__ == "__main__":
    main()

'''
Output:
5.0
'''

#7. String to Boolean
def main():
    x = "True"
    y = bool(x)
    print(y)

if __name__ == "__main__":
    main()

'''
🖥 Output
True
'''





#8. Integer to Boolean
def main():
    x = 0
    y = bool(x)
    print(y)

if __name__ == "__main__":
    main()

'''
🖥 Output
False
'''

#9. Boolean to Integer
def main():
    x = True
    y = int(x)
    print(y)

if __name__ == "__main__":
    main()

'''
🖥 Output
1
'''
'''
6️⃣ Boolean to Integer
def main():
    x = True
    y = int(x)      # True → 1
    print(y)

if __name__ == "__main__":
    main()
'''



#10. Taking Input and Type Casting
def main():
    x = input("Enter a number: ")
    y = int(x)
    print(y + 10)

if __name__ == "__main__":
    main()

'''
Output:


'''