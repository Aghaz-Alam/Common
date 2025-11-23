Memory management is a critical aspect of C++ programming, as it gives the programmer fine-grained control over how memory is allocated, used, and deallocated. Proper memory management ensures efficient resource usage, prevents memory leaks, and avoids undefined behavior. Here are the key C++ concepts used for better memory management, explained with their typical use cases:

1. Stack vs Heap Memory

Stack Memory:
--> Stack memory is used for local variables and function calls. 
    It’s managed automatically—when a function call ends, its local variables are destroyed.

--> Stack memory is fast to allocate and deallocate, but limited in size. 
    It’s generally used for small, temporary objects.



Heap Memory:
--> Heap memory is used for dynamic memory allocation via new or malloc(). 
    It’s more flexible but requires manual management (deallocation via delete or free()).

--> Heap memory is slower to allocate/deallocate compared to stack memory but allows for larger, 
    long-lived objects that need to persist beyond the scope of a single function.

Scenario Example:
--> If you need to allocate a large array dynamically based on user input, 
    you would typically allocate memory on the heap.

int* arr = new int[1000]; // Heap memory
delete[] arr; // Manually deallocating heap memory

/* --------------------------- */
#include <iostream>
using namespace std;
void demonstrateMemoryManagement() {
    // Stack allocation for a simple integer
    int a = 10;  // 'a' is allocated on the stack

    // Heap allocation for an array of 1000 integers
    int* arr = new int[1000];  // 'arr' points to a block of 1000 integers in the heap
    
    // Initialize the array
    for (int i = 0; i < 1000; ++i) {
        arr[i] = i;  // Populating the array with values
    }
    
    // Printing the first few values to confirm
    cout << "arr[0] = " << arr[0] << ", arr[999] = " << arr[999] << endl;

    // Cleanup: Free the dynamically allocated memory from the heap
    delete[] arr;  // deallocating the memory on the heap
}

int main() {
    demonstrateMemoryManagement();  // Calling the function to demonstrate stack & heap memory
    return 0;
}
//arr[0] = 0, arr[999] = 999



Memory Allocation Process (Stack vs Heap)
--> To visualize memory allocation, let us use a simple stack and heap diagram that shows 
    what happens during the execution of the program.

Step-by-Step Memory Allocation
--> Let us break the program down into steps and show how stack and heap are used:

1. Stack Allocation (Function Call and Local Variables)
--> When demonstrateMemoryManagement() is called, a new stack frame is created. 
    The stack is used for local variables such as a.
--> The stack grows and shrinks as functions are called and return.
--> Memory is automatically allocated and freed when the function scope is entered and exited.

|----------------------| <- Top of the stack (Memory for the function call)
|  arr (pointer)       |  <-- This pointer holds the address of the allocated heap array.
|----------------------|
|  a = 10              |  <-- 'a' is a local variable in the stack.
|----------------------| <- Bottom of the stack


Here:
--> a is allocated on the stack.
--> arr is a pointer (located on the stack) that points to memory allocated on the heap.




2. Heap Allocation (new Keyword)
--> The statement int* arr = new int[1000]; allocates 1000 integers on the heap.

Heap (Dynamic Memory):
--------------------------
| arr[0] | arr[1] | arr[2] | ... | arr[999] |
--------------------------
|    Memory for 1000 integers allocated dynamically    |
--------------------------
--> The memory block for arr is allocated on the heap.
--> The pointer arr in the stack points to the memory location in the heap.



3. Deallocation of Heap Memory (delete[])
--> After using the dynamically allocated memory, we call delete[] arr; to free the allocated memory. 
    This ensures that the heap memory is properly deallocated to avoid memory leaks.
--> The pointer arr still exists in the stack, but it is now pointing to deallocated memory.

Heap (Memory Freed):
--------------------------
|  Freed Memory (deallocated)  |
--------------------------




4. End of Function Scope
--> After the function demonstrateMemoryManagement() finishes execution, the stack frame is destroyed, which means:
    *Local variables (a and arr) are automatically cleaned up.
    *The heap memory for arr has already been deallocated by delete[], so there's no memory leak.

Final Stack and Heap State:
After the function execution:
--> The stack is empty (except for the return address and the saved state of main()).
--> The heap memory for arr has been deallocated using delete[].

Memory Diagram Summary:
   ------------------------              -------------------------
  |  Stack Memory          |            |   Heap Memory         |
  |------------------------|            |-----------------------|
  |  a = 10                |            |  arr[0] = 0           |
  |------------------------|            |  arr[1] = 1           |
  |  arr (pointer)         |            |  ...                  |
  |------------------------|            |  arr[999] = 999       |
   ------------------------              -------------------------
       |                                          |
       |                                          |
   (Pointer to Heap)                           (Memory Freed)
       |
       v
    Dynamically allocated memory (1000 ints)  -> freed by delete[]

Key Points to Remember:
--> Stack memory is fast and automatic but limited in size. It’s used for local variables and function calls.
--> Heap memory is used for dynamic memory allocation, and it must be manually deallocated to avoid memory leaks.
--> RAII (Resource Acquisition Is Initialization) principles can be applied to manage memory automatically 
    using smart pointers like std::unique_ptr and std::shared_ptr.
--> Memory leaks occur when dynamically allocated memory is not properly deallocated (i.e., delete[] is omitted).


/* --------------------------------------------------------------------------------------------- */
2. Automatic Storage Duration (ASD)
--> Local variables with automatic storage duration are allocated on the stack and destroyed 
    when they go out of scope. This is automatic memory management.

--> Use for temporary objects that don’t need to persist beyond the current scope.

Scenario:
void foo() {
    int a = 10;  // 'a' is automatically allocated on the stack.
} // 'a' is destroyed here when it goes out of scope.



/* ------------------------- */
#include <iostream>
using namespace std;
void foo() {
    int a = 10;  // 'a' is automatically allocated on the stack.
    cout << "Inside foo(), a = " << a << endl;
} // 'a' is destroyed when it goes out of scope here.
int main() {
    foo();  // Call foo(), which uses stack memory for variable 'a'
    // 'a' is no longer accessible here because it's out of scope and has been destroyed.
    cout << "Outside foo(), a is not accessible anymore." << endl;
  return 0;
}

Output:
Inside foo(), a = 10
Outside foo(), a is not accessible anymore.

/* ----------------- */
Diagram of Stack Allocation:

Here’s a diagram to visualize the stack allocation and deallocation:

At the start of foo():
|----------------------| <- Stack pointer
|  (Main function)     |   <- Main's stack frame
|----------------------|
|  (foo function)      |   <- foo's stack frame
|----------------------|
|  a = 10              |   <- Memory allocated for 'a' on the stack
|----------------------|

After foo() returns (memory for a is deallocated):
|----------------------| <- Stack pointer (back to `main`)
|  (Main function)     |   <- Main's stack frame
|----------------------|
|  (foo function)      |   <- foo's stack frame no longer exists
|----------------------|


After foo() completes, the memory used by a is freed automatically when the stack frame for foo() is popped.



/* --------------------------------------------------------------------------------------------- */
3. Dynamic Memory Allocation (new and delete)
--> new is used to allocate memory on the heap, while delete deallocates it. 
    This is manual memory management and essential for dynamic objects that need to persist for 
    a longer duration than a single scope.

New for Single Object:
int* ptr = new int(10);  // Allocating memory for a single integer.
delete ptr;              // Deallocating memory after use.

New for Array:

int* arr = new int[100];  // Allocating memory for an array of 100 integers.
delete[] arr;             // Deallocating memory after use.

Important: If delete is not called after using new, you get a memory leak.

/* ------------------------------ */
#include <iostream>
using namespace std;
void demonstrateSingleObjectAllocation() {
    // Allocating memory for a single integer on the heap using 'new'
    int* ptr = new int(10);  // 'ptr' points to a dynamically allocated integer with value 10
    cout << "Single object allocation: *ptr = " << *ptr << endl;
    
    // Deallocating the memory after use using 'delete'
    delete ptr;  // Deallocates the memory for the single integer
    cout << "Memory for single object deallocated." << endl;
}
void demonstrateArrayAllocation() {
    // Allocating memory for an array of 100 integers on the heap
    int* arr = new int[100];  // Dynamically allocated array of 100 integers
    
    // Initializing the array
    for (int i = 0; i < 100; ++i) {
        arr[i] = i;  // Assigning values to the array
    }

    // Printing some values from the array to verify
    cout << "Array allocation: arr[0] = " << arr[0] << ", arr[99] = " << arr[99] << endl;
    
    // Deallocating the memory after use using 'delete[]'
    delete[] arr;  // Deallocates memory for the entire array
    cout << "Memory for array deallocated." << endl;
}
int main() {
    // Demonstrate single object allocation and deallocation
    demonstrateSingleObjectAllocation();
    
    // Demonstrate array allocation and deallocation
    demonstrateArrayAllocation();
    
    return 0;
}
/* 
Output:
Single object allocation: *ptr = 10
Memory for single object deallocated.
Array allocation: arr[0] = 0, arr[99] = 99
Memory for array deallocated.
*/
Diagram of Memory Allocation:
1. Single Object Allocation on Heap:
When new is used to allocate a single integer:
Stack:
----------------------
|  (Main Function)    |
|----------------------|
|  ptr (pointer)      |  <-- Points to the heap memory
----------------------

Heap:
------------------------
| 10  |  (allocated memory) |
------------------------

ptr in the stack points to the memory address allocated on the heap.
After delete ptr;, the memory on the heap is freed.

/* ---------------------------------------------- */
2. Array Allocation on Heap:
When new[] is used to allocate an array:

Stack:
----------------------
|  (Main Function)    |
|----------------------|
|  arr (pointer)      |  <-- Points to the array in heap
----------------------

Heap:
----------------------------------------
|  0  |  1  |  2  |  ...  |  99 |  (array of 100 integers)
----------------------------------------

arr in the stack points to the array of integers on the heap.
After delete[] arr;, the memory for the entire array is freed from the heap.


/* --------------------------------------------------------------------------------------------- */
4. Smart Pointers (RAII - Resource Acquisition Is Initialization)
std::unique_ptr:
--> A smart pointer that owns a dynamically allocated object exclusively. 
--> It automatically deletes the object when it goes out of scope.

std::shared_ptr:
--> A reference-counted smart pointer that allows multiple pointers to share ownership of an object. 
--> The object is destroyed when the last shared_ptr is destroyed.

std::weak_ptr:
--> Used to break circular references in shared ownership relationships. 
--> It does not affect the reference count.

Scenario Example:
std::unique_ptr<int> ptr1 = std::make_unique<int>(10);  // Unique ownership
// No need for delete, it's automatically cleaned up.


Circular Reference Example:
--> If you use shared_ptr for two objects referring to each other, 
    it can create a circular reference that would not be cleaned up. 
    
    To fix this, you use weak_ptr.
    *std::shared_ptr<Node> node1 = std::make_shared<Node>();
    *std::shared_ptr<Node> node2 = std::make_shared<Node>();
    *node1->next = node2;
    *node2->next = node1;  // Circular reference

    // Use weak_ptr to avoid the circular reference:
    *std::weak_ptr<Node> weakNode = node1;



/* --------------------------------------------------------------------------------------------- */
5. Memory Pools
--> Memory pools are a custom allocator mechanism designed to handle frequent allocation and 
    deallocation of objects of a certain size. 
    They help minimize the overhead caused by repeatedly allocating and deallocating memory on the heap.
--> A pool allocator allocates a block of memory upfront and then uses that block for repeated object allocation, 
    reducing fragmentation and allocation time.
--> Scenario: If you are creating many small objects, using a memory pool can improve performance.




/* --------------------------------------------------------------------------------------------- */
6. Garbage Collection (Not Native in C++)
--> Unlike languages like Java or Python, C++ does not have built-in garbage collection. 
    However, garbage collection can be implemented via smart pointers or third-party libraries.

--> Some libraries, such as Boosts Shared Pointer or Mimalloc, offer garbage collection-like features, 
    but it is up to the programmer to manage resources effectively.




/* --------------------------------------------------------------------------------------------- */
7. Move Semantics and Rvalue References
--> Move Semantics allows resources to be transferred from one object to another without copying, 
    improving performance for dynamic memory management.
--> Rvalue references (&&) allow objects to "transfer ownership" rather than making deep copies, 
    which is especially useful for containers like std::vector or std::string.

--> Scenario Example:
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = std::move(vec1);  // Moves vec1’s data to vec2 (no copying)




/* --------------------------------------------------------------------------------------------- */
8. Object Slicing and Memory Management
--> Object Slicing occurs when an object of a derived class is assigned to a variable of a base class. 
    This causes the derived class’s specific attributes (which may involve dynamically allocated memory) 
    to be "sliced off".
--> To manage this properly, the base class should define a virtual destructor, 
    allowing derived class objects to be cleaned up correctly when deleted through a base class pointer.

Scenario:
class Base {
  public:
    virtual ~Base() = default;  // Virtual destructor to handle polymorphic cleanup
};

class Derived : public Base {
  public:
    ~Derived() override { /* Cleanup if needed */ }
};


/* --------------------------------------------------------------------------------------------- */
9. Custom Memory Allocators
--> For high-performance applications, such as game engines, custom memory allocators might be used 
    instead of the default new/delete operators. 
    These allocators control how memory is allocated and deallocated, allowing the programmer 
    to fine-tune memory management for specific needs.

Scenario Example:
--> Game engines often implement custom allocators to optimize memory usage and fragmentation 
    when handling many small objects (e.g., bullets, enemies).





/* --------------------------------------------------------------------------------------------- */
10. Placement new and delete
--> Placement new allows you to construct an object in a pre-allocated memory block. 
--> This is useful in certain cases, such as in memory pools or in shared memory systems 
    where you need to control memory allocation and construction explicitly.

Scenario:
char* buffer = new char[sizeof(MyClass)];
MyClass* obj = new (buffer) MyClass;  // Placement new
obj->~MyClass();  // Explicitly call destructor
delete[] buffer;  // Clean up memory block




/* --------------------------------------------------------------------------------------------- */
11. Exceptions and Memory Management
--> In C++, exceptions can complicate memory management, especially in the case of resources allocated on the heap.   
    If an exception is thrown, you need to ensure that resources are cleaned up.

--> RAII (Resource Acquisition Is Initialization) ensures that resources are cleaned up when 
    an object goes out of scope, even if an exception is thrown.

Scenario Example:
void foo() {
    std::unique_ptr<int> ptr(new int(10));  // Automatically deallocated if exception thrown
    // If exception thrown, memory will be cleaned up as unique_ptr goes out of scope.
}

/* --------------------------------------------------------------------------------------------- */