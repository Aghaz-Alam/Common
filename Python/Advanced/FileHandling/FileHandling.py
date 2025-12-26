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