'''
13. Exception Handling
🔹 Short Note
Prevents program crash
Uses try-except
'''

#✅ Program
def main():
    try:
        x = int(input("Enter number: "))
        print(10 / x)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()


'''
🖥 Output
Enter number: 0
Error: division by zero
'''






#1️⃣ Basic try-except
def main():
    try:
        x = int(input("Enter a number: "))
        print("Result:", 10 / x)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter a number: 0
Error: division by zero
"""






2️⃣ Catching specific exceptions
def main():
    try:
        x = int(input("Enter a number: "))
        print(10 / x)
    except ZeroDivisionError:
        print("Error: Cannot divide by zero")
    except ValueError:
        print("Error: Invalid input, enter integer")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter a number: a
Error: Invalid input, enter integer
"""








3️⃣ Using else with try-except
def main():
    try:
        x = int(input("Enter a number: "))
    except ValueError:
        print("Invalid input")
    else:
        print("You entered:", x)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter a number: 5
You entered: 5
"""





4️⃣ Using finally
def main():
    try:
        x = int(input("Enter number: "))
        print(10 / x)
    except Exception as e:
        print("Error:", e)
    finally:
        print("Execution completed")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter number: 0
Error: division by zero
Execution completed
"""




5️⃣ Raising exceptions (throw in C++)
def main():
    x = int(input("Enter age: "))
    if x < 18:
        raise ValueError("Age must be 18 or above")
    else:
        print("Welcome!")

if __name__ == "__main__":
    try:
        main()
    except ValueError as e:
        print("Error:", e)

""" 
🖥 Output
Enter age: 15
Error: Age must be 18 or above
"""







6️⃣ Multiple exceptions in one except block
def main():
    try:
        x = int(input("Enter number: "))
        y = int(input("Enter another number: "))
        print(x / y)
    except (ZeroDivisionError, ValueError) as e:
        print("Error:", e)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter number: 5
Enter another number: 0
Error: division by zero
"""







7️⃣ Nested try-except
def main():
    try:
        x = int(input("Enter numerator: "))
        try:
            y = int(input("Enter denominator: "))
            print(x / y)
        except ZeroDivisionError:
            print("Denominator cannot be zero")
    except ValueError:
        print("Enter valid integer numbers")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter numerator: 5
Enter denominator: 0
Denominator cannot be zero
"""







8️⃣ Custom Exception Class
class AgeError(Exception):
    pass

def check_age(age):
    if age < 18:
        raise AgeError("Age must be 18 or above")
    else:
        print("Access granted")

def main():
    try:
        age = int(input("Enter age: "))
        check_age(age)
    except AgeError as e:
        print("Error:", e)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter age: 15
Error: Age must be 18 or above
"""









9️⃣ Catching all exceptions (not recommended)
def main():
    try:
        x = int(input("Enter number: "))
        print(10 / x)
    except:
        print("Some error occurred")
    finally:
        print("Execution completed")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter number: 0
Some error occurred
Execution completed
"""






🔟 Using assert to raise exception
def main():
    x = int(input("Enter number: "))
    assert x > 0, "Number must be positive"
    print("You entered:", x)

if __name__ == "__main__":
    try:
        main()
    except AssertionError as e:
        print("Error:", e)

""" 
🖥 Output
Enter number: -5
Error: Number must be positive
"""





1️⃣1️⃣ Logging exceptions (advanced/interview)
import logging
logging.basicConfig(level=logging.ERROR)

def main():
    try:
        x = int(input("Enter number: "))
        print(10 / x)
    except Exception as e:
        logging.error("Exception occurred", exc_info=True)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Enter number: 0
ERROR:root:Exception occurred
Traceback (most recent call last):
  File "file.py", line 6, in main
    print(10 / x)
ZeroDivisionError: division by zero
"""





#1️⃣2️⃣ Using with for resource management (context manager)
def main():
    try:
        with open("test.txt", "r") as f:
            data = f.read()
            print(data)
    except FileNotFoundError as e:
        print("Error:", e)

if __name__ == "__main__":
    main()


""" 
🖥 Output
Error: [Errno 2] No such file or directory: 'test.txt'
"""