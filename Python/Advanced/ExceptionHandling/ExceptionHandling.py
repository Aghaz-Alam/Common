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