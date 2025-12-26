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






# Inheritance
#a. Single Inheritance

class Parent:
    def show_parent(self):
        print("This is Parent class")

class Child(Parent):
    def show_child(self):
        print("This is Child class")

def main():
    c = Child()
    c.show_parent()
    c.show_child()

if __name__ == "__main__":
    main()

""" 
🖥 Output
This is Parent class
This is Child class
"""






#b. Multilevel Inheritance

class GrandParent:
    def show_grandparent(self):
        print("GrandParent class")

class Parent(GrandParent):
    def show_parent(self):
        print("Parent class")

class Child(Parent):
    def show_child(self):
        print("Child class")

def main():
    c = Child()
    c.show_grandparent()
    c.show_parent()
    c.show_child()

if __name__ == "__main__":
    main()


""" 
🖥 Output
GrandParent class
Parent class
Child class
"""



#c. Multiple Inheritance

class A:
    def showA(self):
        print("Class A method")

class B:
    def showB(self):
        print("Class B method")

class C(A, B):
    def showC(self):
        print("Class C method")

def main():
    obj = C()
    obj.showA()
    obj.showB()
    obj.showC()

if __name__ == "__main__":
    main()


""" 
🖥 Output
Class A method
Class B method
Class C method
"""





#d. Hierarchical Inheritance

class Parent:
    def show(self):
        print("Parent class")

class Child1(Parent):
    def show1(self):
        print("Child1 class")

class Child2(Parent):
    def show2(self):
        print("Child2 class")

def main():
    c1 = Child1()
    c2 = Child2()
    c1.show()
    c1.show1()
    c2.show()
    c2.show2()

if __name__ == "__main__":
    main()

""" 
🖥 Output
Parent class
Child1 class
Parent class
Child2 class
"""





#e. Hybrid Inheritance

class A:
    def showA(self):
        print("A class")

class B(A):
    def showB(self):
        print("B class")

class C(A):
    def showC(self):
        print("C class")

class D(B, C):
    def showD(self):
        print("D class")

def main():
    d = D()
    d.showA()
    d.showB()
    d.showC()
    d.showD()

if __name__ == "__main__":
    main()

""" 
🖥 Output
A class
B class
C class
D class
"""






1️⃣ Diamond Problem (Ambiguity)
Problem Setup
A base class A
Two classes B and C inherit A
Class D inherits from both B and C

# Diamond Problem Example
class A:
    def show(self):
        print("A class")

class B(A):
    def show(self):
        print("B class")

class C(A):
    def show(self):
        print("C class")

class D(B, C):
    pass  # No show() method in D

def main():
    d = D()
    d.show()  # Ambiguous: should it call B.show or C.show?

if __name__ == "__main__":
    main()

""" 
🖥 Output
B class

Explanation
Python automatically resolves ambiguity using MRO (Method Resolution Order).
MRO for D:
print(D.__mro__)

(<class '__main__.D'>, <class '__main__.B'>, <class '__main__.C'>, <class '__main__.A'>, <class 'object'>)

Python calls the first method it finds → B.show()
Unlike C++, Python does not need virtual keyword.
Ambiguity may appear if you want both B.show() and C.show() to run.
"""





2️⃣ Solution: Explicitly Call Parent Methods
Option 1: Override in Child and Call Both Parents
# Solution to Diamond Problem
class A:
    def show(self):
        print("A class")

class B(A):
    def show(self):
        print("B class")

class C(A):
    def show(self):
        print("C class")

class D(B, C):
    def show(self):
        B.show(self)  # Call B.show
        C.show(self)  # Call C.show
        print("D class method executed")

def main():
    d = D()
    d.show()

if __name__ == "__main__":
    main()

""" 
🖥 Output
B class
C class
D class method executed

Explanation
By overriding show() in D, we can explicitly call both parent methods.
This resolves ambiguity, similar to virtual inheritance in C++.
Python automatically manages MRO, but explicit calls give control.
"""






3️⃣ Option 2: Check MRO
class D(B, C):
    pass

def main():
    d = D()
    d.show()            # Python follows MRO
    print(D.__mro__)    # Shows method resolution order

if __name__ == "__main__":
    main()


""" 
🖥 Output
B class
(<class '__main__.D'>, <class '__main__.B'>, <class '__main__.C'>, <class '__main__.A'>, <class 'object'>)

This shows Python resolves ambiguity automatically.
First method found in MRO is used. 
"""