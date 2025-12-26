'''
12. Inheritance
Child class inherits parent class
Promotes code reuse
'''

#✅ Program
class Animal:
    def speak(self):
        print("Animal speaks")

class Dog(Animal):
    def bark(self):
        print("Dog barks")

def main():
    d = Dog()
    d.speak()
    d.bark()

if __name__ == "__main__":
    main()


'''
🖥 Output
Animal speaks
Dog barks
'''