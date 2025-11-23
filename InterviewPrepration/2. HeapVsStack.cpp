Difference between Heap and Stack
| Feature                 | **Stack**                       | **Heap**                                      |
| ----------------------- | ------------------------------- | --------------------------------------------- |
| **Memory management**   | Automatic                       | Manual (new/delete) or smart pointers         |
| **Lifetime**            | Bound to scope                  | Program-controlled                            |
| **Allocation speed**    | Very fast                       | Slower (requires OS / allocator)              |
| **Size limit**          | Limited, fixed per thread       | Large, only limited by system RAM             |
| **Fragmentation**       | None                            | Possible                                      |
| **Typical usage**       | Local variables, function calls | Dynamic objects, large or variable-sized data |
| **Allocation syntax**   | `int x = 5;`                    | `int* p = new int(5);`                        |
| **Deallocation syntax** | Automatic                       | `delete p;` or smart pointers                 |
| **Thread behavior**     | Each thread has its own stack   | Heap is shared across threads                 |



1. Memory Management: Automatic (Stack) vs Manual (Heap)
Stack Example (Automatic Memory Management)
---> Memory is automatically allocated and freed when scope ends.

#include <iostream>
using namespace std;
void stackFunction() {
    int x = 10;  // allocated on stack
    cout << "Stack value: " << x << endl;
} // x is automatically destroyed here
int main() {
    stackFunction();
    cout << "Stack variable gone automatically!" << endl;
  return 0;
}


Heap Example (Manual Memory Management)
---> You must manually delete what you allocate.

#include <iostream>
using namespace std;
void heapFunction() {
    int* p = new int(10);  // allocated on heap
    cout << "Heap value: " << *p << endl;
    delete p; // must delete manually
}
int main() {
    heapFunction();
    cout << "Heap variable deleted manually!" << endl;
  return 0;
}




✅ 2. Lifetime: Bound to Scope (Stack) vs Program-controlled (Heap)
---> Stack Example (Ends with scope)
#include <iostream>
using namespace std;
int main() {
    {
        int a = 100; // stack
        cout << "Inside scope: " << a << endl;
    } // a is destroyed here

    // cout << a; // ERROR: a no longer exists
}


---> Heap Example (You control lifetime)
#include <iostream>
using namespace std;
int main() {
    int* p = new int(100); // heap
    cout << "Heap value still alive: " << *p << endl;

    // still exists even after exiting inner scopes
    delete p; 
  return 0;
}


✅ 3. Allocation Speed: Stack (Fast) vs Heap (Slow)
---> (Stack is just pointer movement; heap involves OS/allocator.)

---> Stack Example: 
#include <iostream>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        int x = i; // fast allocation
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Stack allocation done!\n";
  return 0;
}

---> Heap Example
#include <iostream>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        int* p = new int(i); // slow allocation
        delete p;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Heap allocation done!\n";
  return 0;
}


✅ 4. Size Limit: Stack (Small) vs Heap (Large)
---> Stack Example (Stack overflow risk)
#include <iostream>
using namespace std;
int main() {
    int arr[10000000]; // ~40MB may crash depending on stack size
    cout << "Large stack array created!" << endl;
  return 0;
}


---> Heap Example (Much larger allocation possible)
#include <iostream>
using namespace std;
int main() {
    int* arr = new int[10000000]; // ~40MB usually fine
    cout << "Large heap array created!" << endl;
    delete[] arr;
  return 0;
}


✅ 5. Fragmentation: None (Stack) vs Possible (Heap)
---> Stack Example (Always contiguous)
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    double b = 20.5;
    char c = 'A';
    // All placed contiguously on stack frame
  return 0;
}

---> Heap Example (Fragmentation illustration)
#include <iostream>
using namespace std;
int main() {
    int* p1 = new int(1);
    int* p2 = new int(2);

    delete p1; // creates gap in memory

    int* p3 = new int(3); // may or may not reuse p1's spot

    delete p2;
    delete p3;
  return 0;
}


---> (You cannot “see” fragmentation directly, but this shows how it happens.)





✅ 6. Typical Usage
---> Stack Example (local variables)
void process() {
    int a = 5;      // stack
    double b = 3.14;
}


---> Heap Example (large or variable-sized data)
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    int* arr = new int[n]; // size known at runtime → heap

    delete[] arr;
  return 0;
}



✅ 7. Allocation Syntax
---> Stack Syntax
int x = 5;

---> Heap Syntax (raw pointer)
int* p = new int(5);
delete p;


---> Heap Syntax (smart pointer)
#include<iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> ptr = make_unique<int>(5);
    cout<<"Value: "<<*ptr;  //Value: 5
  return 0;
}



✅ 8. Deallocation Syntax
---> Stack: automatic
{
    int x = 10;
} // x destroyed here automatically

---> Heap: manual or smart pointer
int* p = new int(10);
delete p; // manual

// or
auto ptr = make_unique<int>(10); // auto delete



✅ 9. Thread Behavior: Stack (per thread) vs Heap (shared)
---> Stack Example (Each thread has its own stack)
#include <iostream>
#include <thread>
using namespace std;
void worker(int id) {
    int x = id; // lives on thread's own stack
    cout << "Thread " << id << " stack x = " << x << endl;
}
int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);

    t1.join();
    t2.join();
  return 0;
}
/* 
Thread Thread 1 stack x = 12 stack x = 2
*/


---> Heap Example (Shared across threads)
#include <iostream>
#include <thread>
using namespace std;
int* sharedValue = new int(10); // heap, shared by threads
void worker(int id) {
    cout << "Thread " << id << " sees value = " << *sharedValue << endl;
}
int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);

    t1.join();
    t2.join();

    delete sharedValue;
  return 0;
}
/* 
Output:
Thread 1 sees value = 10
Thread 2 sees value = 10
*/

/* ------------------------------------------------------------------------------------- */
C++11: Big Changes to Heap Management
C++11 introduced many features that reduced the need for manual heap allocation.

✔ New Features Affecting Heap/Stack
1. Smart pointers (unique_ptr, shared_ptr)
---> Replaces most raw new/delete usage.
---> Automated heap management.

2. Move semantics
---> Objects can be transferred efficiently without deep copying.
---> Reduces need for heap allocations.

3. std::make_shared, std::make_unique
---> Safer and faster than new.

4. Thread-local storage (thread_local keyword)
---> Each thread has its own stack-like TLS segment.

5. Improved alignment support
---> alignas and alignof.

➡ Net effect:
---> Much safer and more efficient heap usage.



/* ------------------------------------------------------------------------------------- */
C++14: Minor Enhancements
C++14 didn’t change memory fundamentals, but it improved convenience.

✔ Enhancements
---> std::make_unique finalized (not in C++11).
---> Small improvements to smart pointers.
---> Better constexpr → more things can be evaluated at compile-time → less runtime heap usage.

➡ Net effect:
---> Cleaner and safer heap allocation patterns.


/* ------------------------------------------------------------------------------------- */
C++17: More compile-time, fewer heap allocations
C++17 encourages stack or static allocations by enabling more compile-time evaluation.

✔ Relevant improvements
1. std::optional, std::variant, std::any
---> These types avoid heap allocation unless necessary.
/* ---------------------------- */
✅ 1. std::optional — Represent “maybe value / maybe no value”
Why do we need std::optional?
Before C++17, we returned:
---> sentinel values (like -1, 0, NULL)
---> error codes
---> bool + output parameter
---> This was unsafe or unclear.

std::optional<T> represents:
---> A value of type T, OR nothing.

Use cases
---> Function might return a value OR not (search, find, parse)
---> Avoid returning pointers or special error values
---> Cleaner & safer code

✅ Example Program: Using std::optional for find()
#include <iostream>
#include <optional>
#include <vector>
using namespace std;
optional<int> findNumber(const vector<int>& data, int target) {
    for (int x : data) {
        if (x == target)
            return x;  // found → return value
    }
    return nullopt;  // not found
}
int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    auto result = findNumber(nums, 3);
    if (result.has_value()) {
        cout << "Found number: " << *result << endl;
    } else {
        cout << "Number not found!" << endl;
    }
}

✔ Explanation
optional<int> means the function might return an integer.
nullopt means “no result”.
No need for:
returning -1
returning NULL

output parameters
→ Much safer & clear.



✅ 2. std::variant — A type-safe union (store one of many types)
Why do we need std::variant?
Before C++17, we used:
---> unions (unsafe, no type checking)
---> class hierarchies
---> void pointers (unsafe)
---> std::variant lets a variable hold one of multiple types, checked at runtime.

Use cases
---> Number/string hybrid values (JSON, settings)
---> Representing states: Loading, Success, Error
---> Replaces unsafe unions

✅ Example Program: Calculator input (int OR double OR string)
#include <iostream>
#include <variant>
#include <string>
using namespace std;
void printValue(const variant<int, double, string>& v) {
    visit([](auto&& arg) {
        cout << "Value: " << arg << endl;
    }, v);
}
int main() {
    variant<int, double, string> value;
    value = 10;
    printValue(value);

    value = 3.14;
    printValue(value);

    value = "Hello Variant!";
    printValue(value);
}

✔ Explanation
---> The variable value can store:
---> int OR double OR string
---> visit() automatically calls correct function depending on the stored type.
---> Safe, checked at compile-time.



✅ 3. std::any — Store any type at runtime
Why do we need std::any?
---> Sometimes you don’t know the type until runtime.
---> It is like a “type-safe void pointer”.
---> Unlike variant, it can store any type (not fixed list).

Use cases
---> Plugin systems
---> Mixed-type containers
---> Runtime type inspection
---> When variant types are not known at compile-time

✅ Example Program: Mixed-type storage using std::any
#include <iostream>
#include <any>
#include <string>
using namespace std;
int main() {
    any data;

    data = 42;
    cout << "Stored int: " << any_cast<int>(data) << endl;

    data = string("Hello any!");
    cout << "Stored string: " << any_cast<string>(data) << endl;

    // Safe type checking
    if (data.type() == typeid(string)) {
        cout << "data currently holds a string" << endl;
    }
}

✔ Explanation
---> any can hold any type.
---> any_cast throws exception if type mismatched.
---> More flexible than variant but less type-safe.

/* ---------------------------- */
2. Guaranteed RVO (Return Value Optimization)
---> Returning objects from functions does not require copying or heap allocation.

3. More powerful constexpr
---> More objects can be placed in static storage instead of heap.

4. string_view
---> Avoids allocating strings → significantly reduces heap churn.

➡ Net effect:
---> Even fewer reasons to manually allocate on the heap.

/* ------------------------------------------------------------------------------------- */
C++20: Even more compile-time power
---> Memory model unchanged, but compile-time features again reduce heap usage.

✔ Major additions affecting memory habits
1. consteval, stronger constexpr
---> More computations and objects can live in read-only static memory.

2. Modules
---> Do not change heap vs. stack, but reduce overhead and fragmentation in huge codebases.

3. std::span
---> Non-owning view over contiguous memory → avoids heap allocation.

4. Coroutines
---> Coroutine frame is usually allocated on the heap unless optimized.

➡ Net effect:
---> Heap usage becomes more controlled and predictable, sometimes optional.


/* ------------------------------------------------------------------------------------ */

Summary Table: Stack vs Heap Evolution in C++11 → C++20
| C++ Version | Stack Behavior | Heap Behavior                  | Key Features Affecting Memory                  |
| ----------- | -------------- | ------------------------------ | ---------------------------------------------- |
| **C++11**   | Same           | Safer & automatic              | Smart pointers, move semantics, TLS            |
| **C++14**   | Same           | Cleaner usage                  | make_unique, constexpr improvements            |
| **C++17**   | Same           | Reduced need                   | string_view, optional, variant, guaranteed RVO |
| **C++20**   | Same           | More compile-time alternatives | consteval, span, coroutines                    |



Difference between heap and stack
✅ 1) What is the Stack?
The stack is a region of memory used for:
--> function calls
--> local variables
--> function parameters
--> return addresses
--> temporary objects

Key Properties
| Feature       | Stack                         |
| ------------- | ----------------------------- |
| Allocation    | Automatic (compiler-managed)  |
| Speed         | Very fast                     |
| Lifetime      | Until the function returns    |
| Memory size   | Small (usually MBs)           |
| Ownership     | No manual deletion required   |
| Thread safety | Each thread has its own stack |

Example
void fun() {
    int x = 10;       // stored on stack
}  



✅ 2) What is the Heap?
The heap is a large pool of free memory used for dynamic allocation.

Allocated using:
new, new[]
malloc() (C style)

Freed using:
delete, delete[]
free() (C style)

Key Properties
| Feature     | Heap                                         |
| ----------- | -------------------------------------------- |
| Allocation  | Manual (`new`) or via smart pointers         |
| Speed       | Slower                                       |
| Lifetime    | Until `delete` OR smart pointer auto cleanup |
| Memory size | Large (GBs)                                  |
| Ownership   | Programmer responsible                       |

Example
void fun() {
    int* p = new int(10);  // stored on heap
    delete p;              // manual delete required
}



⭐ 3) Diagram — Stack vs Heap
+--------------------------+
|        Stack             |
|--------------------------|
| fun() local variables    |
| main() local variables   |
| return addresses         |
| temporary objects        |
+--------------------------+

              |
              v

+--------------------------+
|          Heap            |
|--------------------------|
| new int(10)              |
| new Node()               |
| new int[1000]            |
| dynamic memory blocks    |
+--------------------------+



⭐ 4) Lifetime Difference
✔ Stack variable
Destroyed automatically:

void f() {
    int x = 5;   // destroyed when function ends
}

✔ Heap variable
Stays alive until manually deleted:

void f() {
    int* p = new int(5);
} // memory leak! p destroyed but memory stays


⭐ 5) Speed Difference
Stack: operates with simple pointer increment/decrement → extremely fast
Heap: requires allocation algorithms → much slower

⭐ 6) Errors & Risks
❗ Stack Risks
Stack overflow (deep recursion / huge local arrays)
int arr[10000000]; // may cause stack overflow

❗ Heap Risks
Memory leak (forgetting delete)
Dangling pointer (delete too early)
Double delete
Fragmentation
Smart pointers solve most heap issues.

⭐ 7) Practical Examples
Stack — automatic storage
void func() {
    int a = 10;
    vector<int> v = {1,2,3};
} // a and v destroyed automatically

Heap — dynamic storage
int* p = new int(10);
delete p;

Using smart pointers (preferred)
auto p = make_unique<int>(10);   // no delete needed

⭐ 8) Summary Table
| Feature          | Stack                           | Heap                                         |
| ---------------- | ------------------------------- | -------------------------------------------- |
| Managed by       | Compiler                        | Programmer / Smart pointers                  |
| Lifetime         | End of scope                    | Until manually freed                         |
| Allocation Speed | Very fast                       | Slow                                         |
| Size             | Small (MBs)                     | Large (GBs)                                  |
| Failure          | Stack Overflow                  | Memory leak, fragmentation                   |
| Use cases        | Local variables, function calls | Dynamic memory, large data, lifetime control |

⭐ Interview Answer (Short 10-sec version)
Stack is automatic memory for local variables and function calls, very fast, destroyed at the end of scope.
Heap is dynamic memory, manually managed using new/delete, slower, meant for objects needing variable size or lifetime.