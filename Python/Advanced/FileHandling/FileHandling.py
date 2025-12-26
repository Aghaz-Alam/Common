'''
14. File Handling
🔹 Short Note
Used to read/write files
open(), read(), write()
'''

#✅ Program
def main():
    file = open("sample.txt", "w")
    file.write("Hello Python")
    file.close()

    file = open("sample.txt", "r")
    print(file.read())
    file.close()

if __name__ == "__main__":
    main()

'''
🖥 Output
Hello Python
'''







1️⃣ Writing to a File
def main():
    file = open("sample.txt", "w")  # Write mode
    file.write("Hello Python\n")
    file.write("Welcome to file handling")
    file.close()
    print("Data written successfully")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Data written successfully
"""






2️⃣ Reading from a File
def main():
    file = open("sample.txt", "r")  # Read mode
    content = file.read()
    print("File content:")
    print(content)
    file.close()

if __name__ == "__main__":
    main()

""" 
🖥 Output
File content:
Hello Python
Welcome to file handling
"""






3️⃣ Reading File Line by Line
def main():
    file = open("sample.txt", "r")
    print("Reading line by line:")
    for line in file:
        print(line.strip())  # strip() removes extra newline
    file.close()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Reading line by line:
Hello Python
Welcome to file handling
"""





4️⃣ Appending Data to a File
def main():
    file = open("sample.txt", "a")  # Append mode
    file.write("\nThis line is appended")
    file.close()

    # Reading to check
    file = open("sample.txt", "r")
    print(file.read())
    file.close()

if __name__ == "__main__":
    main()



""" 
🖥 Output
Hello Python
Welcome to file handling
This line is appended
"""





5️⃣ Writing and Reading from Same File
def main():
    # Writing
    with open("sample.txt", "w") as f:
        f.write("Line 1\nLine 2\nLine 3")

    # Reading
    with open("sample.txt", "r") as f:
        content = f.read()
        print("Content after writing:")
        print(content)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Content after writing:
Line 1
Line 2
Line 3
"""





6️⃣ Using readlines()
def main():
    with open("sample.txt", "r") as f:
        lines = f.readlines()
        print("List of lines:")
        print(lines)

if __name__ == "__main__":
    main()

""" 
🖥 Output
List of lines:
['Line 1\n', 'Line 2\n', 'Line 3']
"""





7️⃣ Using seek() and tell()
def main():
    with open("sample.txt", "r") as f:
        print("Current position:", f.tell())  # Start at 0
        print(f.read(5))                      # Read first 5 characters
        print("Position after reading 5 chars:", f.tell())
        f.seek(0)                             # Go back to beginning
        print("Position after seek:", f.tell())
        print(f.read())                        # Read entire file

if __name__ == "__main__":
    main()

""" 
🖥 Output
Current position: 0
Line 
Position after reading 5 chars: 5
Position after seek: 0
Line 1
Line 2
Line 3
"""





8️⃣ Writing Multiple Lines (writelines)
def main():
    lines = ["Python\n", "File Handling\n", "Example\n"]
    with open("sample.txt", "w") as f:
        f.writelines(lines)

    with open("sample.txt", "r") as f:
        print(f.read())

if __name__ == "__main__":
    main()

""" 
🖥 Output
Python
File Handling
Example
"""





9️⃣ Using with Statement (Best Practice)
def main():
    with open("sample.txt", "w") as f:
        f.write("Using with statement\n")
        f.write("Automatic file closing")

    with open("sample.txt", "r") as f:
        print(f.read())

if __name__ == "__main__":
    main()

""" 
🖥 Output
Using with statement
Automatic file closing
"""







🔟 Handling File Not Found (Exception Handling + File)
def main():
    try:
        with open("nofile.txt", "r") as f:
            print(f.read())
    except FileNotFoundError as e:
        print("Error:", e)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Error: [Errno 2] No such file or directory: 'nofile.txt'
"""








1️⃣1️⃣ Reading Large Files (line by line, memory efficient)
def main():
    with open("sample.txt", "r") as f:
        for line in f:
            print(line.strip())

if __name__ == "__main__":
    main()

""" 
🖥 Output
Python
File Handling
Example
"""






1️⃣2️⃣ Binary File Handling
def main():
    data = b"Binary Data Example"
    with open("binaryfile.bin", "wb") as f:
        f.write(data)

    with open("binaryfile.bin", "rb") as f:
        content = f.read()
        print(content)

if __name__ == "__main__":
    main()

""" 
🖥 Output
b'Binary Data Example'
"""









1️⃣3️⃣ Advanced: Copying File Contents
def main():
    with open("sample.txt", "r") as src, open("copy.txt", "w") as dest:
        for line in src:
            dest.write(line)

    print("File copied successfully")

if __name__ == "__main__":
    main()

""" 
🖥 Output
File copied successfully
"""