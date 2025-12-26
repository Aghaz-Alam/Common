How deallocation triggers once code(object) goes out of scope?

1. Automatic Deallocation (Stack Allocation)
   When an object is created on the stack (i.e., its lifetime is tied to a block or function scope), 
   it is automatically destroyed (and memory is deallocated) when it goes out of scope.

Example:
#include <iostream>
using namespace std;
class MyClass {
  public:
    MyClass() { cout << "Object created\n"; }
    ~MyClass() { cout << "Object destroyed\n"; }
};
void functionScope() {
    MyClass obj;  // Local object created on the stack
    cout << "Inside functionScope\n";
}  // 'obj' goes out of scope here, and its destructor is automatically called
int main() {
    cout << "Start of main\n";
    functionScope();
    cout << "End of main\n";
  return 0;
}

Explanation:
Stack allocation: 
    The object obj is created on the stack in functionScope(). 
    Its lifetime is automatically managed, meaning the memory is allocated when the object is created, 
    and it will be automatically deallocated when the function exits.

Destructor: 
    The destructor ~MyClass() is automatically called when the object goes out of scope, which happens when the function exits.

Output:
Start of main
Object created
Inside functionScope
Object destroyed
End of main


In this case, you can see that the destructor is automatically called once the object obj goes out of scope, and the memory is freed.

2. Manual Deallocation (Heap Allocation)
   For objects created on the heap using new, memory deallocation does not happen automatically. 
   You must explicitly use delete to free that memory.

Example:
#include <iostream>
using namespace std;
class MyClass {
  public:
    MyClass() { cout << "Object created\n"; }
    ~MyClass() { cout << "Object destroyed\n"; }
};
void heapAllocation() {
    MyClass* obj = new MyClass();  // Object created on the heap using 'new'
    cout << "Inside heapAllocation\n";
    delete obj;  // Object is explicitly destroyed using 'delete'
}  // No automatic deallocation here
int main() {
    cout << "Start of main\n";
    heapAllocation();
    cout << "End of main\n";
    return 0;
}

Explanation:

Heap allocation: 
    The object obj is created on the heap using new. Since this is heap memory, it will not be automatically freed when heapAllocation() exits.

Manual deallocation: 
    The object is explicitly deallocated using delete within the heapAllocation() function. 
    If you don’t call delete, the memory would not be freed, leading to a memory leak.

Output:
Start of main
Object created
Inside heapAllocation
Object destroyed
End of main


Here, the destructor is called when delete obj is executed, and memory is deallocated. 
This is manual memory management where you are responsible for freeing the memory.




3. Automatic Deallocation for Dynamically Allocated Objects with Smart Pointers

C++11 and beyond provide smart pointers (such as std::unique_ptr, std::shared_ptr) to automatically manage 
the lifetime of dynamically allocated objects. 
These smart pointers automatically release memory when they go out of scope, ensuring no memory leaks.

Example using std::unique_ptr:
#include <iostream>
#include <memory>  // For smart pointers
using namespace std;

class MyClass {
  public:
    MyClass() { cout << "Object created\n"; }
    ~MyClass() { cout << "Object destroyed\n"; }
};

void smartPointerExample() {
    // Creating a unique pointer to manage the lifetime of a dynamically allocated object
    std::unique_ptr<MyClass> obj = std::make_unique<MyClass>();  
    cout << "Inside smartPointerExample\n";
}  // The unique pointer goes out of scope here, and the object is automatically destroyed

int main() {
    cout << "Start of main\n";
    smartPointerExample();
    cout << "End of main\n";
   return 0;
}

Explanation:

Smart Pointer: 
    A std::unique_ptr is used to manage the object. When the unique_ptr goes out of scope (at the end of the smartPointerExample function), it automatically calls the destructor of the object it points to, and the memory is deallocated.

Automatic cleanup: 
    The unique_ptr takes care of the deallocation, so there’s no need to explicitly call delete.

Output:
Start of main
Object created
Inside smartPointerExample
Object destroyed
End of main


In this case, memory is automatically freed when the unique_ptr goes out of scope, and you don’t need to manually call delete. This is the most modern approach to memory management in C++.

4. Example of Both Stack and Heap Memory Management Together

Here’s a program that combines both automatic deallocation (stack memory) and manual deallocation (heap memory):

#include <iostream>
using namespace std;

class MyClass {
public:
    MyClass() { cout << "Object created\n"; }
    ~MyClass() { cout << "Object destroyed\n"; }
};

void functionScope() {
    MyClass obj1;  // Automatically deallocated when functionScope() ends
    cout << "Inside functionScope\n";
}

void heapAllocation() {
    MyClass* obj2 = new MyClass();  // Dynamically allocated on heap
    cout << "Inside heapAllocation\n";
    delete obj2;  // Manually deallocate memory
}

int main() {
    cout << "Start of main\n";
    
    // Stack memory deallocation happens automatically
    functionScope();
    
    // Heap memory deallocation happens manually
    heapAllocation();
    
    cout << "End of main\n";
    return 0;
}

Explanation:

functionScope: The object obj1 is created on the stack, so it will be automatically destroyed when the function scope ends.

heapAllocation: The object obj2 is created on the heap, so we need to manually delete it using delete to avoid a memory leak.

Output:
Start of main
Object created
Inside functionScope
Object destroyed
Inside heapAllocation
Object created
Object destroyed
End of main

Summary of Deallocation:

Stack-based objects: Automatically deallocated when they go out of scope (e.g., function exits).

Heap-based objects: Must be manually deallocated using delete (or delete[] for arrays).

Smart pointers (e.g., std::unique_ptr, std::shared_ptr): Automatically handle memory deallocation when they go out of scope.