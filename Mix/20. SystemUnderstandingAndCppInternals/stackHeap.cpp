1. Stack Memory in C++

The stack is used for automatic storage. Variables are automatically destroyed when they go out of scope.

1.1 Basic Stack Variable
#include <iostream>
int main() {
    int x = 10; // stored on the stack
    int arr[5] = {1,2,3,4,5}; // stack array
    std::cout << "x = " << x << ", arr[2] = " << arr[2] << "\n";
    return 0;
}


Output:

x = 10, arr[2] = 3


Stack allocation is fast.

Memory is automatically released when function exits.

Size of stack variable must be known at compile time (except with VLA in some compilers, not standard C++).

1.2 Stack and Scope
#include <iostream>
void func() {
    int y = 20; // stack variable
    std::cout << "y = " << y << "\n";
}
int main() {
    func();
    // y is not accessible here, it is destroyed after func ends
    return 0;
}

1.3 C++11/14/17 Stack Examples

constexpr variables: compile-time stack variables

#include <iostream>
constexpr int square(int x) { return x*x; }
int main() {
    int val = square(5); // stack variable
    std::cout << val << "\n";
    return 0;
}

2. Heap Memory in C++

The heap is used for dynamic memory allocation. Memory is manually managed (allocated & deallocated).

2.1 Basic new and delete (C++11+)
#include <iostream>
int main() {
    int* p = new int(42); // allocate on heap
    std::cout << "*p = " << *p << "\n";
    delete p; // free memory
    return 0;
}


Output:

*p = 42


Use new[] for arrays:

int* arr = new int[5]{1,2,3,4,5};
delete[] arr;

2.2 Modern C++11 Smart Pointers

C++11 introduced smart pointers in <memory> to manage heap memory automatically.

2.2.1 std::unique_ptr (exclusive ownership)
#include <iostream>
#include <memory>
int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(100); // heap allocation
    std::cout << "*ptr = " << *ptr << "\n";
    // no delete needed, automatically freed
    return 0;
}


std::unique_ptr for arrays:

std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);
arr[0] = 1;

2.2.2 std::shared_ptr (shared ownership)
#include <iostream>
#include <memory>
int main() {
    std::shared_ptr<int> sp1 = std::make_shared<int>(200);
    std::shared_ptr<int> sp2 = sp1; // shared ownership
    std::cout << "*sp1 = " << *sp1 << ", use_count = " << sp1.use_count() << "\n";
    return 0;
}


Output:

*sp1 = 200, use_count = 2


Memory is automatically freed when last shared_ptr goes out of scope.

2.2.3 std::weak_ptr (non-owning reference)
#include <iostream>
#include <memory>
int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(300);
    std::weak_ptr<int> wp = sp; // doesn't increase ref count
    if (auto temp = wp.lock()) {
        std::cout << "*temp = " << *temp << "\n";
    }
    return 0;
}


Useful to avoid cyclic references in shared_ptr.

2.3 Placement new

Allocates object in pre-allocated memory.

#include <iostream>
#include <new>
int main() {
    char buffer[sizeof(int)];
    int* p = new(buffer) int(500); // construct in buffer
    std::cout << "*p = " << *p << "\n";
    p->~int(); // manually call destructor
    return 0;
}

3. Differences Between Stack and Heap
| Feature           | Stack                    | Heap                    |
| ----------------- | ------------------------ | ----------------------- |
| Allocation        | Automatic                | Manual (new/malloc)     |
| Lifetime          | Function scope           | Until delete/free       |
| Speed             | Fast                     | Slower                  |
| Size Limit        | Limited by OS/stack size | Large (depends on RAM)  |
| Memory Management | Automatic                | Manual / Smart Pointers |


4. C++17/20 Stack and Heap Enhancements
4.1 std::allocator (Heap abstraction)
#include <iostream>
#include <memory>
int main() {
    std::allocator<int> alloc;
    int* p = alloc.allocate(1);  // allocate 1 int on heap
    alloc.construct(p, 42);      // construct object
    std::cout << "*p = " << *p << "\n";
    alloc.destroy(p);            // destroy object
    alloc.deallocate(p, 1);      // free memory
    return 0;
}
/* 
*p = 42
*/




4.2 std::pmr::memory_resource (C++17 Polymorphic Memory Resource)
Custom memory allocation strategies:

#include <iostream>
#include <memory_resource>
#include <vector>
int main() {
    char buffer[1024];
    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};
    std::pmr::vector<int> vec{&pool};
    vec.push_back(10);
    std::cout << "vec[0] = " << vec[0] << "\n";
    return 0;
}
/* 
Output: C++17
vec[0] = 10
*/



4.3 C++20: std::span (stack views)
Not heap allocation, but stack-based array view:

#include <iostream>
#include <span>
int main() {
    int arr[] = {1,2,3,4};
    std::span<int> s(arr);
    for(auto v : s) std::cout << v << " ";
    return 0;
}
/* 
1 2 3 4 
*/




✅ Summary of Ways to Use Stack and Heap
Stack
Local variables (int x)
Arrays on stack (int arr[10])
constexpr variables
std::span views
Function parameters



1. Local Variables
Local variables are stored on the stack and automatically destroyed when they go out of scope.

#include <iostream>
void func() {
    int x = 42; // stack variable
    std::cout << "Inside func(), x = " << x << "\n";
}
int main() {
    func();
    // x is not accessible here
    return 0;
}
/* 
Output:
Inside func(), x = 42

Explanation:
x is automatically created when func() is called.
It is destroyed when func() ends.
*/



2. Arrays on Stack
Arrays with fixed size can be allocated on the stack.

#include <iostream>
int main() {
    int arr[5] = {1, 2, 3, 4, 5}; // stack array
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    }
    return 0;
}
/* 
Output:
arr[0] = 1
arr[1] = 2
arr[2] = 3
arr[3] = 4
arr[4] = 5


Explanation:
The array arr is on the stack.
It is automatically deallocated when main() ends.
*/



3. constexpr Variables (C++11+)
constexpr variables are compile-time constants and stored in stack (or sometimes optimized away).

#include <iostream>
constexpr int square(int x) {
    return x * x;
}
int main() {
    int val = square(6); // stack variable
    std::cout << "val = " << val << "\n";
    return 0;
}
/* 
Output:
val = 36


Explanation:
val is a stack variable.
constexpr ensures square(6) is calculated at compile-time.
*/



4. std::span Views (C++20)
std::span provides a stack-based view of an array (no heap allocation).

#include <iostream>
#include <span>
int main() {
    int arr[] = {10, 20, 30, 40};
    std::span<int> s(arr); // view over stack array
    for (auto v : s) {
        std::cout << v << " ";
    }
   return 0;
}
/* 
Output:
10 20 30 40

Explanation:
std::span does not copy data; it only points to the stack array.
Useful for safe, non-owning access to arrays.
*/



5. Function Parameters (Pass by Value)
Function parameters are stored on the stack for each call.

#include <iostream>
void printValue(int x) { // x is on the stack
    std::cout << "Value inside function: " << x << "\n";
}
int main() {
    int num = 99;
    printValue(num);
   return 0;
}
/* 
Output:
Value inside function: 99

Explanation:
x is a stack variable inside printValue.
It is created each time the function is called and destroyed when the function returns.
*/







Heap
new/delete and new[]/delete[]
std::unique_ptr, std::shared_ptr, std::weak_ptr
std::make_unique / std::make_shared
std::allocator
Placement new
std::pmr memory resources



1. new / delete
Dynamic memory allocation on the heap.

#include <iostream>
int main() {
    int* p = new int(42); // allocate on heap
    std::cout << "*p = " << *p << "\n";
    delete p; // free memory
    return 0;
}
/* 
Output:
*p = 42
*/


1.1 new[] / delete[] (heap arrays)
#include <iostream>
int main() {
    int* arr = new int[5]{1,2,3,4,5}; // allocate array on heap
    for(int i = 0; i < 5; ++i)
        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    delete[] arr; // free memory
    return 0;
}
/* 
Output:
arr[0] = 1
arr[1] = 2
arr[2] = 3
arr[3] = 4
arr[4] = 5

Explanation:
Heap memory manually managed.
Must use delete[] for arrays.
*/




2. std::unique_ptr (C++11)
Exclusive ownership of heap memory; automatically destroyed.

#include <iostream>
#include <memory>
int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(100); // heap allocation
    std::cout << "*ptr = " << *ptr << "\n";
    // No need to delete, automatically freed
    return 0;
}
/* 
Output:
*ptr = 100
*/




2.1 std::unique_ptr for arrays
#include <iostream>
#include <memory>
int main() {
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(3);
    arr[0] = 10; arr[1] = 20; arr[2] = 30;
    for(int i = 0; i < 3; ++i) std::cout << arr[i] << " ";
    return 0;
}

Output:
10 20 30




3. std::shared_ptr (C++11)
Shared ownership; memory freed when last owner is destroyed.

#include <iostream>
#include <memory>
int main() {
    std::shared_ptr<int> sp1 = std::make_shared<int>(200);
    std::shared_ptr<int> sp2 = sp1; // shared ownership
    std::cout << "*sp1 = " << *sp1 << ", use_count = " << sp1.use_count() << "\n";
    return 0;
}
/* 
Output:
*sp1 = 200, use_count = 2
*/





4. std::weak_ptr (C++11)
Non-owning reference to a shared pointer; prevents cyclic references.

#include <iostream>
#include <memory>
int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(300);
    std::weak_ptr<int> wp = sp; // weak reference
    if(auto temp = wp.lock()) {
        std::cout << "*temp = " << *temp << "\n";
    }
    return 0;
}
/* 
Output:
*temp = 300
*/





5. std::allocator (C++11)
Manual heap management using allocator.

#include <iostream>
#include <memory>
int main() {
    std::allocator<int> alloc;
    int* p = alloc.allocate(1); // allocate memory
    alloc.construct(p, 42);     // construct object
    std::cout << "*p = " << *p << "\n";
    alloc.destroy(p);            // destroy object
    alloc.deallocate(p, 1);      // free memory
    return 0;
}
/* 
Output:
*p = 42
*/



6. Placement new
Construct object at a specific memory location (heap or stack).

#include <iostream>
#include <new> // for placement new
int main() {
    char buffer[sizeof(int)];
    int* p = new(buffer) int(500); // construct in buffer
    std::cout << "*p = " << *p << "\n";
    p->~int(); // manually destroy
    return 0;
}
/* 
Output:
*p = 500
*/





7. std::pmr::memory_resource (C++17)
Custom heap allocation strategy for containers.

#include <iostream>
#include <memory_resource>
#include <vector>
int main() {
    char buffer[1024];
    std::pmr::monotonic_buffer_resource pool{buffer, sizeof(buffer)};
    std::pmr::vector<int> vec{&pool};
    vec.push_back(10);
    vec.push_back(20);
    std::cout << "vec[0] = " << vec[0] << ", vec[1] = " << vec[1] << "\n";
    return 0;
}
/* 
Output:
vec[0] = 10, vec[1] = 20


Explanation:
std::pmr::vector uses custom memory pool (stack-based buffer in this example).
Efficient memory allocation for performance-critical code.
*/