Memory Management in Python, focusing on smart pointers, references, and internal workings. 
Python does not have C++-style raw/smart pointers, but it achieves similar functionality using references and garbage collection. 
I’ll give all possible program examples, main + output suitable for interviews.

🔷 1️⃣ Python References (Basic Concept)
def main():
    a = [1, 2, 3]   # list object
    b = a            # b references the same object
    print(a is b)    # True → same memory location
    b.append(4)
    print(a, b)      # Both modified

if __name__ == "__main__":
    main()

""" 
🖥 Output
True
[1, 2, 3, 4] [1, 2, 3, 4]

✅ Python variables are references, not raw memory pointers.
"""


🔷 2️⃣ Reference Counting (Internal Mechanism)
Python uses reference counting. Example:

import sys
def main():
    a = [1, 2, 3]
    b = a
    print(sys.getrefcount(a))  # 3 → a, b, argument to getrefcount
    del b
    print(sys.getrefcount(a))  # 2

if __name__ == "__main__":
    main()

""" 
🖥 Output
3
2

✅ When reference count drops to 0 → object is deleted.
"""




🔷 3️⃣ Garbage Collection (GC)
Python automatically frees memory for circular references using gc module:

import gc
class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

def main():
    gc.disable()  # disable automatic collection
    a = Node(10)
    b = Node(20)
    a.next = b
    b.next = a  # circular reference

    del a
    del b

    print("Garbage objects:", gc.collect())  # manually collect

if __name__ == "__main__":
    main()

""" 
🖥 Output
Garbage objects: 2

✅ Circular references do not leak memory thanks to GC.
 """




🔷 4️⃣ Weak References (Python “Smart Pointers”)
Python has weak references via weakref module.
Similar to C++ weak_ptr: does not increase reference count.

import weakref

class MyClass:
    def __init__(self, name):
        self.name = name
    def __del__(self):
        print(f"{self.name} deleted")

def main():
    obj = MyClass("Object1")
    weak_obj = weakref.ref(obj)  # weak reference
    print(weak_obj())            # <__main__.MyClass object at ...>
    
    del obj
    print(weak_obj())            # None → object deleted

if __name__ == "__main__":
    main()

""" 
Output:
Object1 deleted
None

✅ Weak references allow temporary access without preventing garbage collection.
"""



🔷 5️⃣ Circular References and Weak References
import weakref

class Node:
    def __init__(self, value):
        self.value = value
        self.next = None
    def __del__(self):
        print(f"Node {self.value} deleted")

def main():
    a = Node(1)
    b = Node(2)
    a.next = weakref.ref(b)   # weak reference
    b.next = weakref.ref(a)
    
    del a
    del b
    print("GC safe with weak references")

if __name__ == "__main__":
    main()

""" 
Node 2 deleted
Node 1 deleted
GC safe with weak references

✅ Using weakref prevents memory leaks in circular structures.
"""



🔷 6️⃣ Using Context Managers for Memory Management
Context managers manage resource allocation and deallocation (like smart pointers RAII in C++).

class FileHandler:
    def __init__(self, filename):
        self.filename = filename
        self.file = None
    def __enter__(self):
        self.file = open(self.filename, "w")
        return self.file
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file.close()
        print("File closed automatically")

def main():
    with FileHandler("sample.txt") as f:
        f.write("Hello Python")

if __name__ == "__main__":
    main()

""" 
Output:
File closed automatically

✅ Ensures automatic cleanup like unique_ptr in C++.
"""




🔷 7️⃣ Shared Object Example (Reference Counting / Smart Pointer Simulation)
import weakref

class Shared:
    def __init__(self, name):
        self.name = name
    def __del__(self):
        print(f"{self.name} deleted")

def main():
    obj = Shared("SharedObj")
    ref1 = obj  # strong reference
    ref2 = obj  # strong reference
    print("Deleting ref1")
    del ref1
    print("Deleting ref2")
    del ref2  # object deleted automatically

if __name__ == "__main__":
    main()

""" 
Output:
Deleting ref1
Deleting ref2
SharedObj deleted

✅ Mimics C++ shared_ptr behavior.
"""



🔷 8️⃣ Memory Optimization with __slots__ + Weak References
import weakref

class MyClass:
    __slots__ = ['value', '__weakref__']
    def __init__(self, val):
        self.value = val

def main():
    obj = MyClass(10)
    weak_obj = weakref.ref(obj)
    print(weak_obj().value)
    del obj
    print(weak_obj())  # None → object deleted

if __name__ == "__main__":
    main()

""" 
Output:
10
None

✅ __slots__ saves memory + weakref avoids memory leaks. 
"""