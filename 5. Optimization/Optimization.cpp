Optimization
- constexpr, templates ( compile time resolution)
- memory optimization



In C++, optimization can be approached at multiple levels, including compile-time resolution, memory efficiency, and runtime performance. 
Two key aspects you mentioned are constexpr and templates, as well as memory optimization. 

Let us break down each of these and see how they work in C++.
1. Compile-time Optimization with constexpr and Templates constexpr (Constant Expressions)

constexpr is a keyword in C++ that allows you to declare that a function or variable can be evaluated at compile-time rather than runtime. 
It is particularly useful for constant folding, where expressions are evaluated at compile time to reduce runtime overhead.

a) constexpr variables: These are variables whose values are known at compile time and can be used in places where 
constant expressions are required (e.g., array sizes, template arguments).

constexpr int square(int x) {
    return x * x;
}
constexpr int x = square(5);  // x is computed at compile time




#include <iostream>
using namespace std;
// A constexpr function to compute the square of a number
constexpr int square(int x) {
    return x * x;
}
// A constexpr variable initialized with a function call
constexpr int x = square(5);  // x is computed at compile time
int main() {
    // We can use the constexpr variable to define the size of an array
    int arr[x];  // Array size is determined at compile time
    // Initialize the array elements
    for (int i = 0; i < x; ++i) {
        arr[i] = i * 2;
    }
    // Print the array
    cout << "Array of size " << x << ":\n";
    for (int i = 0; i < x; ++i) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    // You can also use constexpr values in template arguments
    constexpr int y = 10;
    int result = square(y);  // Calling the square function with a constant expression
    cout << "\nSquare of " << y << " is: " << result << endl;

  return 0;
}
/*
Array of size 25:
arr[0] = 0
arr[1] = 2
arr[2] = 4
arr[3] = 6
arr[4] = 8
arr[5] = 10
arr[6] = 12
arr[7] = 14
arr[8] = 16
arr[9] = 18
arr[10] = 20
arr[11] = 22
arr[12] = 24
arr[13] = 26
arr[14] = 28
arr[15] = 30
arr[16] = 32
arr[17] = 34
arr[18] = 36
arr[19] = 38
arr[20] = 40
arr[21] = 42
arr[22] = 44
arr[23] = 46
arr[24] = 48

Square of 10 is: 100
*/



b) constexpr functions: Functions that can be evaluated at compile time if all arguments are constant expressions.
constexpr int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}
constexpr int fact5 = factorial(5);  // Computed at compile time




#include <iostream>
using namespace std;
// A constexpr function to compute the factorial of a number
constexpr int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}
// Precompute factorial at compile-time
constexpr int fact5 = factorial(5);  // Computed at compile time
constexpr int fact7 = factorial(7);  // Computed at compile time
// A constexpr function to compute Fibonacci numbers
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}
int main() {
    // Printing the precomputed factorial results at compile-time
    cout << "Factorial of 5: " << fact5 << endl;  // Output: 120
    cout << "Factorial of 7: " << fact7 << endl;  // Output: 5040

    // Using the factorial function directly in code
    int n = 6;
    cout << "Factorial of " << n << ": " << factorial(n) << std::endl;  // Output: 720

    // Demonstrating Fibonacci numbers computed at compile-time
    constexpr int fib5 = fibonacci(5);  // Computed at compile time
    constexpr int fib6 = fibonacci(6);  // Computed at compile time
    cout << "\nFibonacci of 5: " << fib5 << endl;  // Output: 5
    cout << "Fibonacci of 6: " << fib6 << endl;  // Output: 8

  return 0;
}
/*
Factorial of 5: 120
Factorial of 7: 5040
Factorial of 6: 720

Fibonacci of 5: 5
Fibonacci of 6: 8
*/

Benefits:
Can lead to faster code execution since computations are done during the compilation.
Reduces runtime overhead by removing unnecessary computations during execution.





Templates (Compile-Time Resolution)
Templates in C++ allow for generic programming, but when combined with constexpr, they can be used for compile-time computation, 
which makes your programs faster and more memory efficient.

a) Template metaprogramming: This is a technique where templates are used to compute values at compile time. 
Template parameters can be non-type parameters (e.g., integers) that are known at compile time and used to compute values.

template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};
template <>
struct Factorial<0> {
    static constexpr int value = 1;
};
constexpr int result = Factorial<5>::value;  // Evaluates to 120 at compile time

In this example, the factorial is computed at compile time.


//Complete Code Example: Template Metaprogramming for Factorial Calculation
#include <iostream>
using namespace std;
// Template metaprogramming: Factorial computation at compile time
template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};
// Specialization for the base case of factorial (Factorial<0>)
template <>
struct Factorial<0> {
    static constexpr int value = 1;
};
// Test for compile-time computation
constexpr int result = Factorial<5>::value;  // 5! = 120
constexpr int result7 = Factorial<7>::value; // 7! = 5040

// Template metaprogramming for Fibonacci numbers
template <int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};
// Specialization for Fibonacci base cases (Fibonacci<0> and Fibonacci<1>)
template <>
struct Fibonacci<0> {
    static constexpr int value = 0;
};
template <>
struct Fibonacci<1> {
    static constexpr int value = 1;
};
// Test Fibonacci computation
constexpr int fib5 = Fibonacci<5>::value; // Fibonacci of 5 = 5
constexpr int fib6 = Fibonacci<6>::value; // Fibonacci of 6 = 8
// Template metaprogramming for power of a number (x^n)
template <int X, int N>
struct Power {
    static constexpr int value = X * Power<X, N - 1>::value;
};
// Specialization for the base case of power (x^0 = 1)
template <int X>
struct Power<X, 0> {
    static constexpr int value = 1;
};
// Test Power computation
constexpr int power2_3 = Power<2, 3>::value; // 2^3 = 8
constexpr int power3_4 = Power<3, 4>::value; // 3^4 = 81
int main() {
    // Displaying results of template metaprogramming computations
    cout << "Factorial of 5: " << result << endl; // Output: 120
    cout << "Factorial of 7: " << result7 << endl; // Output: 5040

    cout << "\nFibonacci of 5: " << fib5 << endl; // Output: 5
    cout << "Fibonacci of 6: " << fib6 << endl; // Output: 8

    cout << "\n2^3 = " << power2_3 << endl; // Output: 8
    cout << "3^4 = " << power3_4 << endl; // Output: 81

    return 0;
}
/*
Factorial of 5: 120
Factorial of 7: 5040

Fibonacci of 5: 5
Fibonacci of 6: 8

2^3 = 8
3^4 = 81
*/


b) Template specialization: You can use template specialization to optimize code for specific values, 
especially when dealing with common cases where the computation can be simplified.

template <typename T>
T multiply(T a, T b) {
    return a * b;
}

template <>
int multiply<int>(int a, int b) {
    return a * b * 2;  // Special case for int
}


//Complete Code Example with Template Specialization
#include <iostream>
#include <cmath>  // Include the cmath header for the round() function

using namespace std;

// General template function for multiplication
template <typename T>
T multiply(T a, T b) {
    return a * b;
}

// Specialization for the 'int' type to multiply by an additional factor of 2
template <>
int multiply<int>(int a, int b) {
    return a * b * 2;  // Special case for int (extra optimization)
}

// Specialization for the 'double' type to round the result (for example purposes)
template <>
double multiply<double>(double a, double b) {
    return round(a * b);  // Round the result for doubles
}

// Specialization for the 'float' type to return the result as an integer
template <>
float multiply<float>(float a, float b) {
    return static_cast<int>(a * b);  // Return as integer
}

// A specialized version for 'std::string' to concatenate two strings instead of multiplying
template <>
std::string multiply<std::string>(std::string a, std::string b) {
    return a + b;  // Special case for std::string, concatenate the strings
}

int main() {
    // General case: multiplying two integers
    int intResult = multiply(3, 4);  // Should use the specialized version for int
    cout << "Int multiplication (3 * 4): " << intResult << endl;  // Output: 24 (3 * 4 * 2)

    // General case: multiplying two doubles
    double doubleResult = multiply(3.5, 2.0);  // Should use the specialized version for double
    cout << "Double multiplication (3.5 * 2.0): " << doubleResult << endl;  // Output: 7.0 (rounded)

    // General case: multiplying two floats
    float floatResult = multiply(3.3f, 2.1f);  // Should use the specialized version for float
    cout << "Float multiplication (3.3 * 2.1): " << floatResult << endl;  // Output: 6 (cast to int)

    // Special case: concatenating two strings
    string stringResult = multiply(std::string("Hello "), string("World"));
    cout << "String multiplication (concatenation): " << stringResult << endl;  // Output: Hello World

    return 0;
}
/*
Int multiplication (3 * 4): 24
Double multiplication (3.5 * 2.0): 7
Float multiplication (3.3 * 2.1): 6
String multiplication (concatenation): Hello World
*/
Benefits:
Improves runtime performance since calculations are done during compilation.
Reduces code bloat by avoiding unnecessary function calls at runtime.
Can produce specialized code that is tailored to specific scenarios, improving both speed and memory usage.






2. Memory Optimization in C++
Memory optimization in C++ is critical for building efficient, high-performance applications. It can be done at multiple levels:

a. Memory Layout Optimization (Data Packing)
When working with large data structures, the order of fields in a class or struct can have a significant impact on memory usage due to padding.
Rearranging struct members: Ensure that larger types are aligned together to minimize padding and reduce memory fragmentation.

struct Unoptimized {
    char a;  // 1 byte
    int b;   // 4 bytes, but might cause 3 bytes of padding
};

struct Optimized {
    int b;   // 4 bytes
    char a;  // 1 byte
};

In the Optimized struct, the larger types (int) are placed before smaller types (char), minimizing padding.


//Complete Code Example: Memory Layout Optimization (Data Packing)
#include <iostream>
#include <iomanip>  // For std::setw to align output
using namespace std;

// Unoptimized struct with potential padding
struct Unoptimized {
    char a;  // 1 byte
    int b;   // 4 bytes, but might cause 3 bytes of padding
};

// Optimized struct with better memory packing
struct Optimized {
    int b;   // 4 bytes
    char a;  // 1 byte
};

int main() {
    // Create instances of the structs
    Unoptimized unoptimized;
    Optimized optimized;

    // Print the size of both structs to compare memory usage
    cout << "Size of Unoptimized struct: " << sizeof(Unoptimized) << " bytes" << endl;
    cout << "Size of Optimized struct: " << sizeof(Optimized) << " bytes" << endl;

    // Show the memory layout and padding for each struct
    cout << "\nMemory layout comparison (sizes with padding):" << endl;
    cout << "Unoptimized struct:" << endl;
    cout << " - char a: 1 byte" << endl;
    cout << " - int b: 4 bytes" << endl;
    cout << " - Padding: 3 bytes" << endl;  // Typically, the compiler will add 3 bytes of padding after 'char a'

    cout << "\nOptimized struct:" << endl;
    cout << " - int b: 4 bytes" << endl;
    cout << " - char a: 1 byte" << endl;
    cout << " - Padding: 0 bytes" << endl;  // No padding, as 'int' and 'char' are properly aligned

    return 0;
}
/*
Size of Unoptimized struct: 8 bytes
Size of Optimized struct: 8 bytes

Memory layout comparison (sizes with padding):
Unoptimized struct:
 - char a: 1 byte
 - int b: 4 bytes
 - Padding: 3 bytes

Optimized struct:
 - int b: 4 bytes
 - char a: 1 byte
 - Padding: 0 bytes
*/


b. Memory Pooling / Custom Allocators

When dealing with dynamic memory allocation (e.g., new, delete), custom allocators can be used to optimize memory usage, 
especially in performance-critical applications.

Custom memory allocators: Custom allocators help avoid fragmentation and improve the efficiency of memory allocation/deallocation 
in situations where many small objects are created and destroyed.

template <typename T>
class PoolAllocator {
public:
    T* allocate(size_t n) {
        // Custom allocation logic (e.g., memory pool)
        return new T[n];
    }

    void deallocate(T* p, size_t n) {
        // Custom deallocation logic
        delete[] p;
    }
};



//Complete Code for Custom Memory Allocator (PoolAllocator)
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class PoolAllocator {
public:
    // Constructor to initialize the pool with a given size
    PoolAllocator(size_t pool_size) : pool_size_(pool_size), pool_(nullptr), free_list_(nullptr) {
        pool_ = static_cast<char*>(::operator new(pool_size_ * sizeof(T))); // Allocate raw memory for pool
        free_list_ = reinterpret_cast<Block*>(pool_); // Treat the raw memory as a list of blocks

        // Initialize the free list with the addresses of all objects in the pool
        Block* current = free_list_;
        for (size_t i = 0; i < pool_size_ - 1; ++i) {
            current->next = reinterpret_cast<Block*>(pool_ + (i + 1) * sizeof(T));
            current = current->next;
        }
        current->next = nullptr; // Last block points to nullptr
    }

    // Destructor to deallocate the memory pool
    ~PoolAllocator() {
        ::operator delete(pool_);
    }

    // Custom allocation
    T* allocate() {
        if (free_list_ == nullptr) {
            throw std::bad_alloc(); // Out of memory in the pool
        }
        // Get the first free element from the free list
        Block* result_block = free_list_;
        free_list_ = free_list_->next;

        // Convert the block to a pointer of type T
        T* result = reinterpret_cast<T*>(result_block);

        // Call the constructor of T (placement new)
        new (result) T();
        return result;
    }

    // Custom deallocation
    void deallocate(T* p) {
        // Explicitly call the destructor of the object
        p->~T();

        // Convert the pointer back to a Block*
        Block* block = reinterpret_cast<Block*>(p);
        block->next = free_list_;
        free_list_ = block;
    }

private:
    struct Block {
        Block* next;  // Used for the free list
    };

    size_t pool_size_;
    char* pool_;           // Raw memory for the pool (char pointer)
    Block* free_list_;     // Free list to track available blocks
};

class MyObject {
public:
    MyObject() {
        std::cout << "MyObject created\n";
    }

    ~MyObject() {
        std::cout << "MyObject destroyed\n";
    }

    // A simple example member
    void say_hello() {
        std::cout << "Hello, world!\n";
    }

private:
    int x;
    float y;
};

int main() {
    // Create a memory pool for 10 objects of type MyObject
    PoolAllocator<MyObject> allocator(10);

    // Allocate a few objects from the pool
    MyObject* obj1 = allocator.allocate();
    MyObject* obj2 = allocator.allocate();

    obj1->say_hello();
    obj2->say_hello();

    // Deallocate objects and return them to the pool
    allocator.deallocate(obj1);
    allocator.deallocate(obj2);

    // Reallocate objects to ensure memory reuse
    MyObject* obj3 = allocator.allocate();
    MyObject* obj4 = allocator.allocate();

    obj3->say_hello();
    obj4->say_hello();

    // Clean up is handled by the allocator destructor
    return 0;
}
/*
MyObject created
MyObject created
Hello, world!
Hello, world!
MyObject destroyed
MyObject destroyed
MyObject created
MyObject created
Hello, world!
Hello, world!
*/




c. Avoiding Memory Leaks (RAII Pattern)

The RAII (Resource Acquisition Is Initialization) idiom is used to ensure that resources (such as memory) are automatically 
cleaned up when they are no longer needed. This is a powerful way to manage memory in C++ without leaks.

Using smart pointers (std::unique_ptr, std::shared_ptr) helps ensure that dynamically allocated memory is cleaned up 
automatically when no longer in use.

void example() {
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(1000);
    // No need to manually free memory; it's automatically freed when `arr` goes out of scope
}


//1. Using std::unique_ptr for Exclusive Ownership:
std::unique_ptr is a smart pointer that ensures there is only one owner of a resource
When the unique_ptr goes out of scope, the memory is automatically deallocated.
#include <iostream>
#include <memory> // For std::unique_ptr

void example() {
    // Create a unique pointer to an array of 1000 integers
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(1000);
    
    // You can use the array like a regular pointer
    arr[0] = 42;  // Example of setting a value
    
    // No need to manually delete the array, it's automatically cleaned up when `arr` goes out of scope
    std::cout << "First element: " << arr[0] << std::endl; // Output: 42
}

int main() {
    example();  // When the function ends, arr is automatically destroyed
    return 0;
}
/*
First element: 42
*/


// Using std::shared_ptr for Shared Ownership:
std::shared_ptr is a smart pointer that allows multiple pointers to share ownership of the same resource. 
The resource will only be freed when the last shared_ptr pointing to it is destroyed.

#include <iostream>
#include <memory> // For std::shared_ptr

void shared_ptr_example() {
    // Create a shared pointer to an integer
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    
    std::cout << "Value: " << *ptr1 << std::endl;  // Output: 42
    
    // ptr2 now shares ownership of the same integer
    std::shared_ptr<int> ptr2 = ptr1;  
    
    std::cout << "Value from ptr2: " << *ptr2 << std::endl;  // Output: 42
    
    // Memory will only be freed when both ptr1 and ptr2 go out of scope
}

int main() {
    shared_ptr_example();  // ptr1 and ptr2 go out of scope and memory is freed
    return 0;
}
/*
Value: 42
Value from ptr2: 42
*/

d. Avoiding Copies with Move Semantics
C++11 introduced move semantics, which allow you to transfer ownership of resources (like memory) instead of copying them, 
improving memory efficiency.

Move constructors and move assignment operators help in transferring ownership rather than duplicating the underlying memory.

class MyClass {
public:
    MyClass(MyClass&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
private:
    int* data;
};





#include <iostream>
#include <utility>  // For std::move
using namespace std;
class MyClass {
  public:
    // Constructor to allocate memory and initialize data
    MyClass(size_t size) : size(size), data(new int[size]) {
        cout << "Constructor: Allocated " << size << " integers.\n";
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;  // Initialize with some values
        }
    }

    // Destructor to clean up allocated memory
    ~MyClass() {
        delete[] data;
        std::cout << "Destructor: Cleaned up memory.\n";
    }

    // Move Constructor
    MyClass(MyClass&& other) noexcept
        : size(other.size), data(other.data) {
        // Transfer ownership of the data
        other.data = nullptr;  // Set the original object's data to nullptr
        other.size = 0;        // Reset the size of the original object
        cout << "Move Constructor: Transferred ownership of data.\n";
    }

    // Move Assignment Operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            // Clean up the current resource (if any)
            delete[] data;

            // Transfer ownership of the data
            data = other.data;
            size = other.size;

            // Set the other object's data to nullptr to prevent double deletion
            other.data = nullptr;
            other.size = 0;

            cout << "Move Assignment Operator: Transferred ownership of data.\n";
        }
        return *this;
    }

    // Copy Constructor (optional, if you need it)
    MyClass(const MyClass& other)
        : size(other.size), data(new int[other.size]) {
        cout << "Copy Constructor: Created a copy of data.\n";
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Copy Assignment Operator (optional, if you need it)
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete[] data;  // Clean up existing resource
            size = other.size;
            data = new int[size];
            cout << "Copy Assignment Operator: Copied data.\n";
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // A method to display data (for demonstration)
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

  private:
    size_t size;
    int* data;
};

int main() {
    // Create an object using the constructor
    MyClass obj1(5);
    obj1.print();

    // Use the move constructor
    MyClass obj2 = move(obj1);  // Move obj1 to obj2
    obj2.print();

    // After move, obj1's resources have been nullified
    // obj1.print(); // This would be invalid because obj1's data is now nullptr

    // Use the move assignment operator
    MyClass obj3(3);
    obj3 = move(obj2);  // Move obj2 to obj3
    obj3.print();

  return 0;
}
/*
Constructor: Allocated 5 integers.
0 1 2 3 4 
Move Constructor: Transferred ownership of data.
0 1 2 3 4 
Constructor: Allocated 3 integers.
Move Assignment Operator: Transferred ownership of data.
0 1 2 3 4 
Destructor: Cleaned up memory.
Destructor: Cleaned up memory.
Destructor: Cleaned up memory.
*/





e. Using Containers Efficiently
When working with STL containers, choosing the appropriate container can have a significant impact on memory usage.
std::vector vs. std::list: std::vector stores data contiguously in memory, which can be more memory-efficient than std::list, 
which stores elements in nodes that include pointers.

Reserve space: Use std::vector::reserve() to avoid reallocations as the vector grows dynamically.

std::vector<int> vec;
vec.reserve(1000);  // Allocates memory for 1000 elements upfront, avoiding multiple reallocations


//Complete Example with std::vector:
#include <iostream>
#include <vector>
#include <list>
using namespace std;
void demonstrate_vector_usage() {
    vector<int> vec;
    
    // Reserve space for 1000 elements upfront to avoid multiple reallocations
    vec.reserve(1000);  

    // Add some elements to the vector
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);  // Adding elements
    }

    // Display some elements to verify
    cout << "First 5 elements in vector: ";
    for (int i = 0; i < 5; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "Size of vector: " << vec.size() << endl;
    cout << "Capacity of vector: " << vec.capacity() << endl;
}

void demonstrate_list_usage() {
    list<int> lst;

    // Insert elements at the back of the list
    for (int i = 0; i < 1000; ++i) {
        lst.push_back(i);  // Adding elements to the list
    }

    // Display the first few elements in the list
    cout << "First 5 elements in list: ";
    int count = 0;
    for (int value : lst) {
        cout << value << " ";
        if (++count == 5) break;
    }
    cout << endl;
}

int main() {
    std::cout << "Demonstrating vector usage with reserved space:\n";
    demonstrate_vector_usage();
    cout << "\nDemonstrating list usage:\n";
    demonstrate_list_usage();

    return 0;
}
/*
Demonstrating vector usage with reserved space:
First 5 elements in vector: 0 1 2 3 4 
Size of vector: 1000
Capacity of vector: 1000

Demonstrating list usage:
First 5 elements in list: 0 1 2 3 4 
*/



3. Practical C++ Optimization Example:
Combining the above concepts, here’s a small example that demonstrates compile-time optimization with constexpr and template metaprogramming 
while considering memory efficiency:

#include <iostream>
#include <vector>
using namespace std;
template <int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template <>
struct Fibonacci<1> {
    static constexpr int value = 1;
};
int main() {
    constexpr int fib5 = Fibonacci<5>::value;  // Evaluated at compile-time
    cout << "Fibonacci of 5: " << fib5 << endl;

    vector<int> vec;
    vec.reserve(100);  // Memory optimization to avoid reallocations

    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }

  return 0;
}
/*
Fibonacci of 5: 5
*/

Key Takeaways
constexpr and template metaprogramming allow you to do computations at compile-time, which can reduce runtime overhead and improve performance.
Memory optimization in C++ requires careful attention to data layout, avoiding unnecessary copies, and using custom memory allocators 
or smart pointers.
Move semantics and RAII help to prevent memory leaks and unnecessary resource duplication.