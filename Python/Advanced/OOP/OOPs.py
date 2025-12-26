'''
11. Object-Oriented Programming (OOP)
🔹 Short Note
Class = blueprint
Object = instance of class
'''

#✅ Program
class Student:
    def __init__(self, name):
        self.name = name

    def display(self):
        print("Name:", self.name)

def main():
    s1 = Student("Alex")
    s1.display()

if __name__ == "__main__":
    main()


'''
🖥 Output
Name: Alex
'''