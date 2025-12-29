1. Custom Allocators
STL containers allow custom memory allocators for optimized memory management.

#include <vector>
#include <iostream>
#include <memory>
int main() {
    std::vector<int, std::allocator<int>> vec; // default allocator
    vec.push_back(1);
    vec.push_back(2);
    for (auto x : vec) std::cout << x << " ";
  return 0;
}
/*
Output:
1 2
*/
You can implement a custom allocator to control memory allocations for performance-critical applications.




2. Function Objects / Functors
A functor is an object that can be called as a function. 
STL algorithms allow functors for custom operations.

#include <algorithm>
#include <vector>
#include <iostream>
struct Square {
    void operator()(int &x) { x = x * x; }
};
int main() {
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), Square());
    for(auto x : v) std::cout << x << " ";
    
   return 0;
}
/*
Output:
1 4 9 16 
*/





3. Lambda Expressions with STL
Modern C++ uses lambdas for inline function objects.

#include <vector>
#include <algorithm>
#include <iostream>
int main() {
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), [](int &x){ x += 10; });
    for(auto x : v) std::cout << x << " ";
  return 0;
}
/*
Output:
11 12 13 14 
*/




4. Custom Comparators
For set, map, priority_queue, you can define custom sorting rules.

#include <set>
#include <iostream>
struct Descending {
    bool operator()(int a, int b) const { return a > b; }
};
int main() {
    std::set<int, Descending> s = {1, 5, 3};
    for(auto x : s) std::cout << x << " "; // 5 3 1
  return 0;
}
/*
Output:
5 3 1
*/






5. Advanced Map/Set Usage
unordered_map and unordered_set (hash-based, average O(1))
multi_map / multi_set (allow duplicates)
map::lower_bound / upper_bound for range queries

#include <map>
#include <iostream>
int main() {
    std::map<int, std::string> mp = {{1,"A"}, {3,"C"}, {5,"E"}};
    auto it = mp.lower_bound(2); 
    std::cout << it->first << " " << it->second; // 3 C
  return 0;
}
/*
Output:
3 C
*/





6. Iterator Tricks
Reverse iterators: rbegin(), rend()
advance(), next(), prev()
insert_iterator, back_inserter, front_inserter

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
int main() {
    std::vector<int> v = {1,2,3};
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  return 0;
}
/*
Output:
1 2 3
*/






7. STL Algorithms Beyond Basics
Some advanced algorithms:
std::partial_sort, std::nth_element (efficient selection)
std::transform, std::accumulate, std::reduce (C++17)
std::partition, std::stable_partition
std::binary_search, std::lower_bound, std::upper_bound

#include <vector>
#include <algorithm>
#include <iostream>
int main() {
    std::vector<int> v = {5,1,3,2,4};
    std::nth_element(v.begin(), v.begin()+2, v.end()); // 3rd smallest element
    std::cout << v[2]; // 3
}
/*
Output:
3
*/





8. std::optional, std::variant, std::any with STL
std::optional<T>: container may or may not have value
std::variant: type-safe union
std::any: type-erased container

#include <optional>
#include <iostream>
int main() {
    std::optional<int> x;
    x = 42;
    if(x) std::cout << *x;
}
/*
Output: C++17
42
*/





9. std::tuple & Structured Bindings
Tuples can store heterogeneous elements and be unpacked easily.

#include <tuple>
#include <iostream>
int main() {
    std::tuple<int, std::string, double> t(1, "Hello", 3.14);
    auto [i, s, d] = t; 
    std::cout << i << " " << s << " " << d;
  return 0;
}
/*
Output: C++17
1 Hello 3.14
*/





10. std::bitset
Efficient bit manipulation and storage.

#include <bitset>
#include <iostream>
int main() {
    std::bitset<8> b("10101010");
    b.flip();
    std::cout << b; // 01010101
}
/*
Output: 
01010101
*/






11. std::deque Advanced Use
Efficient insertion/removal at both ends
Random access like vector

#include <deque>
#include <iostream>

int main() {
    std::deque<int> dq;

    // Insert elements at the back
    dq.push_back(10);
    dq.push_back(20);

    // Insert elements at the front
    dq.push_front(5);
    dq.push_front(2);

    std::cout << "Deque after push_front and push_back: ";
    for (auto x : dq) std::cout << x << " ";
    std::cout << std::endl;

    // Access elements randomly
    std::cout << "Element at index 2: " << dq[2] << std::endl;

    // Remove elements from both ends
    dq.pop_front(); // removes 2
    dq.pop_back();  // removes 20

    std::cout << "Deque after pop_front and pop_back: ";
    for (auto x : dq) std::cout << x << " ";
    std::cout << std::endl;

    // Insert in the middle using iterator
    auto it = dq.begin() + 1;
    dq.insert(it, 15); // Insert 15 at second position

    std::cout << "Deque after inserting 15 in middle: ";
    for (auto x : dq) std::cout << x << " ";
    std::cout << std::endl;

    // Erase element using iterator
    dq.erase(dq.begin() + 1); // removes 15

    std::cout << "Deque after erasing middle element: ";
    for (auto x : dq) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
/* 
Deque after push_front and push_back: 2 5 10 20 
Element at index 2: 10
Deque after pop_front and pop_back: 5 10 
Deque after inserting 15 in middle: 5 15 10 
Deque after erasing middle element: 5 10 
*/




12. Move Semantics & Emplace Functions
emplace_back, emplace, try_emplace to avoid unnecessary copies.

#include <vector>
#include <string>
#include <iostream>
int main() {
    std::vector<std::string> v;
    v.emplace_back("Hello"); // constructs in place
    std::cout << v[0] << std::endl; // print the first element
  return 0;
}
/*
Output: 
Hello
*/





13. std::priority_queue with custom comparators
#include <queue>
#include <vector>
#include <iostream>
int main() {
    auto cmp = [](int a,int b){ return a<b; }; // max heap
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
    pq.push(3); pq.push(1); pq.push(5);
    std::cout << pq.top(); // 5
  return 0;
}
/*
Output: 
5
*/





14. std::string_view with STL
Efficient string handling without copies

#include <string_view>
#include <iostream>
int main() {
    std::string_view sv = "Hello World";
    std::cout << sv.substr(0,5); // Hello
  return 0;
}
/*
Output: C++17
Hello
*/






15. Parallel STL (C++17/20)
Use execution policies for parallel algorithms

#include <vector>
#include <algorithm>
#include <execution>
#include <iostream>
int main() {
    std::vector<int> v = {5,1,4,2,3};
    std::sort(std::execution::par, v.begin(), v.end());
    for(auto x:v) std::cout<<x<<" ";
  return 0;
}
/*
Output: C++17
1 2 3 4 5
*/

✅ These are the key advanced STL concepts that are useful for interviews, competitive programming, and production C++.
















1. What is an Allocator?
An allocator is a class that defines how memory is allocated, constructed, and deallocated for container elements.
Default: std::allocator<T>
Custom: you can create your own allocator for performance or memory tracking.

Allocator responsibilities:
allocate(n): allocate memory for n objects of type T.
deallocate(p, n): deallocate memory at pointer p for n objects.
construct(p, args...): construct an object at pointer p.
destroy(p): destroy the object at pointer p.



2. Default Allocator Example
#include <vector>
#include <iostream>
#include <memory>
int main() {
    std::vector<int, std::allocator<int>> vec; // default allocator
    vec.push_back(1);
    vec.push_back(2);

    for (auto x : vec) std::cout << x << " ";
    return 0;
}
/* 
Output:
1 2

Here std::allocator<int> handles memory for the vector elements.
*/


3. Custom Allocator
We can implement a custom allocator for logging, debugging, or custom memory management.

#include <iostream>
#include <memory>
template <typename T>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    template <class U>
    constexpr MyAllocator(const MyAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};
int main() {
    std::vector<int, MyAllocator<int>> vec;
    vec.push_back(10);
    vec.push_back(20);
}
/* 
Output:
Allocating 1 element(s)
Allocating 2 element(s)
Deallocating 1 element(s)

Notes: STL containers may allocate more memory than you insert due to capacity growth.
*/


4. Key Concepts and Typedefs in Allocators
A custom allocator should define:

template<typename T>
struct Alloc {
    using value_type = T;          // mandatory
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template<class U> struct rebind { using other = Alloc<U>; };
};

rebind<U> allows the allocator to allocate memory for different types (needed internally by containers).


5. Allocator Functions
| Function                | Purpose                                    |
| ----------------------- | ------------------------------------------ |
| `allocate(n)`           | Allocate memory for `n` elements           |
| `deallocate(p, n)`      | Free memory pointed by `p`                 |
| `construct(p, args...)` | Construct an object at `p`                 |
| `destroy(p)`            | Destroy object at `p`                      |
| `max_size()`            | Returns max elements that can be allocated |


6. Example with construct and destroy
#include <iostream>
#include <memory>
int main() {
    std::allocator<int> alloc;

    int* p = alloc.allocate(2);          // allocate memory for 2 ints
    alloc.construct(p, 42);              // construct first element
    alloc.construct(p + 1, 99);          // construct second element

    std::cout << p[0] << " " << p[1] << "\n";

    alloc.destroy(p);                     // destroy first element
    alloc.destroy(p + 1);                 // destroy second element
    alloc.deallocate(p, 2);               // free memory
  return 0;
}
/* 
Output:
42 99
*/


7. Advanced Concepts
Stateful Allocators
Allocators can store state, like memory pools, and containers will copy the allocator state when copied/moved.

Propagate Allocators
STL supports:
propagate_on_container_copy_assignment
propagate_on_container_move_assignment

propagate_on_container_swap
These traits define how allocators are propagated during operations.

Pool Allocators / Performance Optimization
Instead of calling new/delete for each element, use a memory pool to reduce overhead.
Often used in game engines, high-frequency trading, or performance-critical apps.

Tracking Memory Usage
Custom allocators can log memory allocations and deallocations (useful in debugging).

8. Summary
Allocators are advanced memory management tools for STL containers.
std::allocator is the default, but custom allocators give fine control over allocation, construction, and destruction.
Key STL containers supporting custom allocators: vector, list, deque, map, set, unordered_map, unordered_set.
Useful for: performance-critical apps, memory pools, debugging memory leaks, logging allocations.












Advanced allocator concepts in C++
1. Stateful Allocators
2. Propagate Allocators
3. Pool Allocators / Performance Optimization
4. Tracking Memory Usage

1. Stateful Allocator
A stateful allocator stores internal data, for example a counter, which will be copied/moved when the container is copied/moved.

#include <iostream>
#include <vector>
#include <memory>
template <typename T>
struct StatefulAllocator {
    using value_type = T;

    int id; // state variable to identify allocator
    StatefulAllocator(int id = 0) : id(id) {}

    template <class U>
    StatefulAllocator(const StatefulAllocator<U>& other) : id(other.id) {}

    T* allocate(std::size_t n) {
        std::cout << "[Allocator " << id << "] Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "[Allocator " << id << "] Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};
int main() {
    std::vector<int, StatefulAllocator<int>> v1(StatefulAllocator<int>(1));
    v1.push_back(10);
    v1.push_back(20);

    // Copy vector
    std::vector<int, StatefulAllocator<int>> v2 = v1;
    v2.push_back(30);

  return 0;
}
/* 
Sample Output:
[Allocator 1] Allocating 1 element(s)
[Allocator 1] Allocating 2 element(s)
[Allocator 1] Allocating 2 element(s)  // copy allocates new memory

Here, the allocator’s state id is preserved when copying the container.
*/



2. Propagate Allocators
C++ STL containers provide traits to control whether the allocator should be propagated during operations like copy, move, or swap.
propagate_on_container_copy_assignment
propagate_on_container_move_assignment
propagate_on_container_swap
We demonstrate copy assignment with allocator propagation:

#include <vector>
#include <iostream>
#include <memory>
template <typename T>
struct MyAllocator {
    using value_type = T;
    int id;
    MyAllocator(int id=0) : id(id) {}
    template <typename U> MyAllocator(const MyAllocator<U>& other) : id(other.id) {}
    T* allocate(std::size_t n) { return static_cast<T*>(::operator new(n*sizeof(T))); }
    void deallocate(T* p, std::size_t n) { ::operator delete(p); }
    
    using propagate_on_container_copy_assignment = std::true_type; // propagate allocator on copy
};
int main() {
    std::vector<int, MyAllocator<int>> v1(MyAllocator<int>(1));
    v1.push_back(1);
    v1.push_back(2);

    std::vector<int, MyAllocator<int>> v2(MyAllocator<int>(2));
    v2 = v1; // allocator propagated because of propagate_on_container_copy_assignment

    std::cout << "v2 elements: ";
    for(auto x:v2) std::cout<<x<<" ";
    std::cout << std::endl;
  return 0;
}
/* 
Output:
v2 elements: 1 2

With propagate_on_container_copy_assignment = true, v2 uses v1’s allocator. Otherwise, it uses its original allocator.
*/


3. Pool Allocators / Performance Optimization
A pool allocator preallocates memory blocks to avoid repeated new/delete calls. This is efficient for performance-critical apps.

#include <iostream>
#include <vector>
template <typename T>
struct PoolAllocator {
    using value_type = T;
    static const int POOL_SIZE = 1024;
    static char pool[POOL_SIZE * sizeof(T)];
    static int used;

    T* allocate(std::size_t n) {
        if (used + n > POOL_SIZE) throw std::bad_alloc();
        T* ptr = reinterpret_cast<T*>(&pool[used * sizeof(T)]);
        used += n;
        std::cout << "Allocating " << n << " element(s) from pool\n";
        return ptr;
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocate called, but pool does not free individual elements\n";
    }
};

template <typename T>
char PoolAllocator<T>::pool[PoolAllocator<T>::POOL_SIZE * sizeof(T)];
template <typename T>
int PoolAllocator<T>::used = 0;
int main() {
    std::vector<int, PoolAllocator<int>> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
  return 0;
}
/* 
Sample Output:
Allocating 1 element(s) from pool
Allocating 2 element(s) from pool

Here, memory is taken from the pool without calling new for each element.
*/


4. Tracking Memory Usage
A custom allocator can log allocations and deallocations for debugging memory leaks.

#include <iostream>
#include <vector>
template <typename T>
struct LoggingAllocator {
    using value_type = T;

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n*sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};
int main() {
    std::vector<int, LoggingAllocator<int>> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.clear(); // triggers deallocation eventually
  return 0;
}
/* 
Sample Output:
Allocating 1 element(s)
Allocating 2 element(s)
Deallocating 1 element(s)

This helps track memory usage and detect leaks.
*/

✅ Summary of Advanced Allocator Concepts
| Concept              | Description                                                                         |
| -------------------- | ----------------------------------------------------------------------------------- |
| Stateful Allocator   | Stores internal state, preserved on container copy/move                             |
| Propagate Allocators | Controls whether the allocator state is propagated during copy/move/swap operations |
| Pool Allocator       | Preallocates memory to reduce `new/delete` overhead, improves performance           |
| Tracking Allocations | Logs allocations/deallocations for debugging memory issues                          |


































Deallocation in C++
1. Basics of Deallocation in C++
C++ uses manual memory management when we allocate memory dynamically using new or new[]. Deallocation is done using:
delete → for single objects
delete[] → for arrays

#include <iostream>
int main() {
    int* ptr = new int(42);   // allocate single int
    delete ptr;               // deallocate

    int* arr = new int[3]{1,2,3}; // allocate array
    delete[] arr;                  // deallocate array

   return 0;
}

Key points:
Always match new with delete and new[] with delete[].
Not deallocating memory leads to memory leaks.



2. Deallocation in STL Containers
STL containers manage memory automatically:
std::vector, std::string, std::map, etc. allocate/deallocate memory internally.
clear() removes elements and calls destructors, but may not reduce capacity.
shrink_to_fit() requests memory reduction.

#include <vector>
#include <iostream>
int main() {
    std::vector<int> v = {1,2,3,4,5};
    v.clear();              // elements destroyed
    std::cout << "Size after clear: " << v.size() << std::endl;
    v.shrink_to_fit();       // request to reduce capacity
    std::cout << "Capacity after shrink_to_fit: " << v.capacity() << std::endl;
  return 0;
}
/* 
Sample Output:
Size after clear: 0
Capacity after shrink_to_fit: 0  // implementation dependent
*/



3. Custom Deallocator via Allocators
STL containers can use custom allocators that define deallocate().

#include <iostream>
#include <vector>
template<typename T>
struct LoggingAllocator {
    using value_type = T;

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};
int main() {
    std::vector<int, LoggingAllocator<int>> v;
    v.push_back(10);
    v.push_back(20);
    v.clear(); // triggers deallocation eventually
  return 0;
}
/* 
Output:
Allocating 1 element(s)
Allocating 2 element(s)
Deallocating 1 element(s)

Using custom allocators allows tracking memory deallocation, important for debugging.
*/



4. Smart Pointers (Automatic Deallocation)
Modern C++ prefers smart pointers to avoid manual deallocation:

std::unique_ptr<T> → single ownership, automatically deletes object
std::shared_ptr<T> → shared ownership, deletes object when last reference is gone
std::weak_ptr<T> → non-owning reference, doesn’t affect deallocation

#include <iostream>
#include <memory>
int main() {
    // unique_ptr
    std::unique_ptr<int> up(new int(42));
    std::cout << *up << std::endl; // prints 42
    // automatic deallocation when up goes out of scope

    // shared_ptr
    std::shared_ptr<int> sp1 = std::make_shared<int>(100);
    std::shared_ptr<int> sp2 = sp1; // reference count increases
    std::cout << *sp2 << std::endl;
    // memory deleted when last shared_ptr goes out of scope

    return 0;
}
/* 
Output:
42
100

No explicit delete required. Memory is automatically deallocated.
*/



5. Custom Deleters in Smart Pointers
unique_ptr and shared_ptr support custom deleters.

#include <iostream>
#include <memory>
struct MyStruct {
    int x;
};
int main() {
    auto deleter = [](MyStruct* p){
        std::cout << "Custom deleting MyStruct with x = " << p->x << std::endl;
        delete p;
    };

    std::unique_ptr<MyStruct, decltype(deleter)> up(new MyStruct{42}, deleter);
  return 0;
}
/* 
Output:
Custom deleting MyStruct with x = 42

Useful when memory needs special cleanup, e.g., closing file handles, freeing GPU memory.
*/



6. Deallocation in Exception-Safe Code
Always ensure memory is deallocated on exceptions:

#include <iostream>
int main() {
    int* ptr = new int(10);
    try {
        throw std::runtime_error("Error!");
        delete ptr; // never reached
    } catch(...) {
        delete ptr; // ensure memory freed
    }
}
/* 
Output: program safely exits without memory leak.
Modern C++ uses RAII (Resource Acquisition Is Initialization) and smart pointers to handle this automatically.
*/



7. Memory Pool Deallocators (Advanced)
For performance-critical applications, we often preallocate a memory pool and deallocate at once.

#include <iostream>
#include <vector>
struct Pool {
    int pool[100];
    int used = 0;

    int* allocate() {
        return &pool[used++];
    }

    void deallocateAll() {
        std::cout << "Deallocating entire pool\n";
        used = 0;
    }
};
int main() {
    Pool p;
    int* a = p.allocate();
    int* b = p.allocate();

    *a = 10; *b = 20;
    std::cout << *a << " " << *b << std::endl;

    p.deallocateAll();
  return 0;
}
/* 
Output:
10 20
Deallocating entire pool

Useful in game engines, real-time apps, high-frequency trading where frequent small allocations are costly.
*/

8. Summary Table
| Type             | Example                                 | Notes                          |
| ---------------- | --------------------------------------- | ------------------------------ |
| `delete`         | `int* p = new int; delete p;`           | Single object                  |
| `delete[]`       | `int* arr = new int[10]; delete[] arr;` | Array                          |
| STL Container    | `v.clear(); v.shrink_to_fit();`         | Automatic destruction          |
| Custom Allocator | `allocator.deallocate(p,n)`             | Logs memory, pool, or tracking |
| Smart Pointer    | `unique_ptr` / `shared_ptr`             | Automatic, RAII                |
| Custom Deleter   | `unique_ptr<T, deleter>`                | Special cleanup                |
| Memory Pool      | Manual pool with deallocateAll()        | Batch deallocation             |










1. Manual Deallocation (delete / delete[])
When you allocate memory dynamically using new or new[], you must free it manually using:

#include <iostream>
int main() {
    // Single object
    int* ptr = new int(42);
    delete ptr;  // deallocate

    // Array
    int* arr = new int[3]{1, 2, 3};
    delete[] arr; // deallocate array
  return 0;
}

Key Points:
new ↔ delete
new[] ↔ delete[]
Not deallocating → memory leak.




2. Deallocation in STL Containers
STL containers manage memory automatically:

#include <vector>
#include <iostream>
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    v.clear();              // destroys elements
    std::cout << "Size: " << v.size() << std::endl;
    v.shrink_to_fit();      // requests memory release
    std::cout << "Capacity: " << v.capacity() << std::endl;
  return 0;
}
/* 
Output (implementation dependent):
Size: 0
Capacity: 0

clear() destroys elements but may not free memory. shrink_to_fit() requests memory reduction.
*/



3. Custom Deallocator in Allocators
Custom allocators can define how memory is deallocated.

#include <iostream>
#include <vector>
template<typename T>
struct LoggingAllocator {
    using value_type = T;

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};
int main() {
    std::vector<int, LoggingAllocator<int>> v;
    v.push_back(10);
    v.push_back(20);
    v.clear(); // triggers deallocation eventually
  return 0;
}
/* 
Sample Output:
Allocating 1 element(s)
Allocating 2 element(s)
Deallocating 1 element(s)
*/



4. Smart Pointers (Automatic Deallocation)
C++ provides smart pointers that automatically deallocate memory:

#include <iostream>
#include <memory>
int main() {
    // unique_ptr
    std::unique_ptr<int> up(new int(42));
    std::cout << *up << std::endl;
    // automatically deleted when 'up' goes out of scope

    // shared_ptr
    std::shared_ptr<int> sp1 = std::make_shared<int>(100);
    std::shared_ptr<int> sp2 = sp1; // reference count increases
    std::cout << *sp2 << std::endl;
    // deleted when last shared_ptr goes out of scope
}
/* 
Output:
42
100
*/



5. Custom Deleters in Smart Pointers
You can define a custom deallocator for special cleanup:

#include <iostream>
#include <memory>
struct MyStruct { int x; };
int main() {
    auto deleter = [](MyStruct* p){
        std::cout << "Custom deleting MyStruct with x = " << p->x << std::endl;
        delete p;
    };

    std::unique_ptr<MyStruct, decltype(deleter)> up(new MyStruct{42}, deleter);
  return 0;
}
/* 
Output:
Custom deleting MyStruct with x = 42
*/



6. Memory Pool Deallocator (Advanced)
For performance-critical apps:

#include <iostream>
struct Pool {
    int pool[100];
    int used = 0;

    int* allocate() { return &pool[used++]; }

    void deallocateAll() { 
        std::cout << "Deallocating entire pool\n"; 
        used = 0; 
    }
};
int main() {
    Pool p;
    int* a = p.allocate();
    int* b = p.allocate();
    *a = 10; *b = 20;
    std::cout << *a << " " << *b << std::endl;
    p.deallocateAll();
  retur 0;
}
/* 
Output:
10 20
Deallocating entire pool

Batch deallocation is faster than delete for many small objects.
*/


7. Exception-Safe Deallocation
Always ensure memory is freed during exceptions:

#include <iostream>
#include <stdexcept>
int main() {
    int* ptr = new int(10);
    try {
        throw std::runtime_error("Error!");
        delete ptr; // not reached
    } catch(...) {
        delete ptr; // ensure memory freed
    }
  return 0;
}

8. Summary Table
| Type             | Example                                 | Notes                       |
| ---------------- | --------------------------------------- | --------------------------- |
| `delete`         | `int* p = new int; delete p;`           | Single object               |
| `delete[]`       | `int* arr = new int[10]; delete[] arr;` | Array                       |
| STL Containers   | `v.clear(); v.shrink_to_fit();`         | Automatic destruction       |
| Custom Allocator | `allocator.deallocate(p,n)`             | Logs memory, pool, tracking |
| Smart Pointer    | `unique_ptr`, `shared_ptr`              | Automatic, RAII             |
| Custom Deleter   | `unique_ptr<T, deleter>`                | Special cleanup             |
| Memory Pool      | Preallocate and deallocateAll()         | Batch deallocation          |









A single C++ program demonstrating all these best practices together:
1. Smart pointers for automatic deallocation
2. STL containers with optional custom allocator
3. Memory pool for performance
4. Exception-safe deallocation

This will be a comprehensive example with outputs.
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

// --------------------
// Memory Pool
// --------------------
struct Pool {
    int pool[100];
    int used = 0;

    int* allocate() {
        if (used >= 100) throw std::bad_alloc();
        return &pool[used++];
    }

    void deallocateAll() {
        std::cout << "Deallocating entire pool\n";
        used = 0;
    }
};

// --------------------
// Custom Allocator with Logging
// --------------------
template<typename T>
struct LoggingAllocator {
    using value_type = T;

    T* allocate(std::size_t n) {
        std::cout << "[Allocator] Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "[Allocator] Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};

int main() {
    std::cout << "=== Smart Pointer Demo ===\n";
    // --------------------
    // Smart pointers (RAII)
    // --------------------
    try {
        std::unique_ptr<int> up(new int(42));
        std::shared_ptr<int> sp1 = std::make_shared<int>(100);
        std::shared_ptr<int> sp2 = sp1;

        std::cout << "unique_ptr value: " << *up << std::endl;
        std::cout << "shared_ptr value: " << *sp2 << std::endl;

    } catch (...) {
        std::cout << "Exception occurred in smart pointer demo\n";
    }

    std::cout << "\n=== STL Container with Custom Allocator ===\n";
    // --------------------
    // STL vector with custom allocator
    // --------------------
    std::vector<int, LoggingAllocator<int>> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.clear(); // triggers deallocation

    std::cout << "\n=== Memory Pool Demo ===\n";
    // --------------------
    // Memory pool allocation
    // --------------------
    Pool pool;
    int* a = pool.allocate();
    int* b = pool.allocate();
    *a = 1;
    *b = 2;
    std::cout << "Pool values: " << *a << " " << *b << std::endl;
    pool.deallocateAll();

    std::cout << "\n=== Exception-Safe Deallocation Demo ===\n";
    // --------------------
    // Exception safety
    // --------------------
    int* ptr = new int(99);
    try {
        throw std::runtime_error("Simulated exception!");
        delete ptr; // won't reach here
    } catch (...) {
        delete ptr; // safe deallocation
        std::cout << "Memory safely deallocated after exception\n";
    }

    return 0;
}
/* 
Expected Output:
=== Smart Pointer Demo ===
unique_ptr value: 42
shared_ptr value: 100

=== STL Container with Custom Allocator ===
[Allocator] Allocating 1 element(s)
[Allocator] Allocating 2 element(s)
[Allocator] Deallocating 1 element(s)

=== Memory Pool Demo ===
Pool values: 1 2
Deallocating entire pool

=== Exception-Safe Deallocation Demo ===
Memory safely deallocated after exception

✅ Explanation of Features
Smart pointers
unique_ptr automatically deletes the object when it goes out of scope.
shared_ptr deletes the object when the last reference goes out of scope.
STL containers with custom allocator
Vector uses LoggingAllocator to track allocations/deallocations.
Optimizes memory usage if needed.
Memory pool
Allocates memory from a preallocated array.
Reduces overhead for frequent small allocations.
Exception-safe deallocation
Ensures delete is called even if an exception occurs.
RAII (smart pointers) automatically handles this in modern C++.
*/



















✅ 1. Smart Pointers
✔ unique_ptr — owns memory exclusively
✔ shared_ptr — shared ownership, ref-counted

Memory is freed automatically → No manual delete needed.

Program 1 — Smart Pointers Demo
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== unique_ptr Demo ===\n";

    {
        std::unique_ptr<int> up(new int(42));
        std::cout << "unique_ptr value: " << *up << std::endl;
        // deleted automatically here
    }

    std::cout << "\n=== shared_ptr Demo ===\n";

    {
        std::shared_ptr<int> sp1 = std::make_shared<int>(100);
        std::shared_ptr<int> sp2 = sp1; // reference count increases

        std::cout << "shared_ptr value (sp1): " << *sp1 << std::endl;
        std::cout << "shared_ptr value (sp2): " << *sp2 << std::endl;
        std::cout << "Reference Count: " << sp1.use_count() << std::endl;
        // memory deleted when last shared_ptr dies
    }

    return 0;
}
/* 
Output
=== unique_ptr Demo ===
unique_ptr value: 42

=== shared_ptr Demo ===
shared_ptr value (sp1): 100
shared_ptr value (sp2): 100
Reference Count: 2
*/


✅ 2. STL Containers with Custom Allocator
A custom allocator controls how memory is allocated and deallocated internally.

✔ Useful for:
Tracking memory
Debugging
Performance optimization
Pool allocators



Program 2 — Custom Logging Allocator with vector
#include <iostream>
#include <vector>
template<typename T>
struct LoggingAllocator {
    using value_type = T;

    T* allocate(std::size_t n) {
        std::cout << "[Allocator] Allocating " << n << " element(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "[Allocator] Deallocating " << n << " element(s)\n";
        ::operator delete(p);
    }
};
int main() {
    std::cout << "=== Vector with Custom Allocator ===\n";

    std::vector<int, LoggingAllocator<int>> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.clear(); // destroys elements
    // memory freed later when v's destructor calls deallocate

    return 0;
}
/* 
Output
=== Vector with Custom Allocator ===
[Allocator] Allocating 1 element(s)
[Allocator] Allocating 2 element(s)
[Allocator] Allocating 3 element(s)
[Allocator] Deallocating 3 element(s)
*/


✅ 3. Memory Pool (Fixed-size Allocator)
✔ Why use a memory pool?
Faster than new / delete
Avoids heap fragmentation
Ideal for frequent small allocations (games, engines, HFT systems)
This example uses a simple static pool of 100 integers.

Program 3 — Memory Pool Demo
#include <iostream>

struct Pool {
    int pool[100];
    int used = 0;

    int* allocate() {
        if (used >= 100) throw std::bad_alloc();
        return &pool[used++];
    }

    void deallocateAll() {
        std::cout << "Deallocating entire pool\n";
        used = 0;  
    }
};
int main() {
    std::cout << "=== Memory Pool Demo ===\n";

    Pool pool;
    int* a = pool.allocate();
    int* b = pool.allocate();

    *a = 10;
    *b = 20;

    std::cout << "Pool values: " << *a << " " << *b << std::endl;

    pool.deallocateAll();

    return 0;
}
/* 
Output
=== Memory Pool Demo ===
Pool values: 10 20
Deallocating entire pool
*/


✅ 4. Exception-Safe Deallocation
✔ Problem:
If an exception occurs, delete might never be called → memory leak.

✔ Solution:
Use try-catch and manually delete
OR use RAII + smart pointers (automatic)

Program 4 — Exception-Safe Deallocation
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "=== Exception-Safe Deallocation Demo ===\n";

    int* ptr = new int(99);

    try {
        std::cout << "Throwing exception...\n";
        throw std::runtime_error("Error occurred!");
        delete ptr; // skipped
    }
    catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        delete ptr; // safe cleanup
        std::cout << "Memory safely deallocated after exception\n";
    }

    return 0;
}
/* 
Output
=== Exception-Safe Deallocation Demo ===
Throwing exception...
Caught exception: Error occurred!
Memory safely deallocated after exception 
*/











