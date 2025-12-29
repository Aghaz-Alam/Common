✅ Allocators in C++ — Full Explanation
Allocators abstract how memory is obtained and released in standard containers.
Think of them as pluggable memory managers for STL containers.

⭐ 1. What Is an Allocator?
An allocator is responsible for:
Allocation — reserving raw, unconstructed storage.
Deallocation — freeing the storage.
Construction — creating objects in that storage.
Destruction — destroying objects.

⭐ 2. Why Allocators?
Allocators allow:
✔ Custom memory management
e.g., allocate from shared memory, GPUs, large pre-allocated blocks, etc.

✔ Faster than new/delete
(e.g., pool allocators, monotonic allocators)

✔ Deterministic / real-time performance
(avoid fragmentation, avoid unpredictable slowdowns)

✔ Tracking and debugging allocations
(log sizes, print info, prevent leaks)

✔ Using STL containers in non-standard memory spaces
(e.g., memory-mapped files, network shared memory, embedded systems)

⭐ 3. Default Allocator (std::allocator)
This is what all STL containers use if you don’t specify anything.
std::vector<int> v;  // uses std::allocator<int>

It uses:
operator new → for raw storage
placement new → to construct elements
delete → to free storage

⭐ 4. Allocator Types in Modern C++
✔ C++17/20 recommend using allocator_traits
Instead of directly accessing allocator methods.

✔ Newer “fancy pointer” support
Allocators can use custom pointers (e.g., pointer-to-shared-memory).

⭐ 5. Allocator Requirements (Traditional)
A standard allocator must define:

value_type
pointer
const_pointer
size_type
difference_type

allocate()
deallocate()

⭐ 6. How STL Uses Allocators
Every container has an allocator template parameter:

template<
    class T,
    class Allocator = std::allocator<T>
> class vector;

Internally:
Use alloc.allocate(n) to reserve memory
Use alloc.construct(ptr, value) (C++03)
Use std::allocator_traits<Alloc>::construct (C++11+)
Use alloc.deallocate(ptr, n) to free

⭐ 7. Writing Your Own Allocator (Complete Example)
Here is a minimal C++17 custom allocator:

template<typename T>
struct LoggingAllocator {
    using value_type = T;
    LoggingAllocator() = default;
    template<class U>
    constexpr LoggingAllocator(const LoggingAllocator<U>&) noexcept {}
    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " objects\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocating " << n << " objects\n";
        ::operator delete(p);
    }
};

template <class T, class U>
bool operator==(const LoggingAllocator<T>&, const LoggingAllocator<U>&) { return true; }
template <class T, class U>
bool operator!=(const LoggingAllocator<T>&, const LoggingAllocator<U>&) { return false; }

Usage:
std::vector<int, LoggingAllocator<int>> v;
v.push_back(10);
v.push_back(20);

⭐ 8. Pool Allocator Example (Fast Allocations)
A pool allocator uses a big buffer and dishes out pieces.
template <typename T, size_t PoolSize = 1024>
struct PoolAllocator {
    using value_type = T;
    static inline char pool[PoolSize * sizeof(T)];
    static inline size_t offset = 0;
    T* allocate(size_t n) {
        size_t bytes = n * sizeof(T);
        if (offset + bytes > sizeof(pool))
            throw std::bad_alloc();
        T* ptr = reinterpret_cast<T*>(pool + offset);
        offset += bytes;
        return ptr;
    }
    void deallocate(T*, size_t) noexcept {}
};

Usage:
std::vector<int, PoolAllocator<int>> v;

⭐ 9. std::pmr — Polymorphic Allocators (C++17)
Modern C++17 introduced polymorphic allocators under <memory_resource>.
✔ Core Idea
Instead of template allocators, use a runtime memory_resource.
Example with PMR:
#include <memory_resource>
char buffer[1024];
std::pmr::monotonic_buffer_resource pool(buffer, sizeof(buffer));
std::pmr::vector<int> v(&pool);

Benefits:
Faster
Cleaner code
Can switch memory source at runtime
Ideal for game engines, financial systems, RTOS

⭐ 10. Types of PMR Allocators
| Memory Resource                | Characteristics                         |
| ------------------------------ | --------------------------------------- |
| `monotonic_buffer_resource`    | Very fast, only deallocates all-at-once |
| `unsynchronized_pool_resource` | Thread-unsafe, pool based               |
| `synchronized_pool_resource`   | Thread-safe                             |
| `new_delete_resource`          | Wrapper around `new`/`delete`           |
| `null_memory_resource`         | Always throws                           |


⭐ 11. Using Containers with PMR
std::pmr::vector<std::pmr::string> names{&pool};
names.emplace_back("Alice");

⭐ 12. Difference: Classic Allocators vs PMR
| Feature          | std::allocator | pmr::*                          |
| ---------------- | -------------- | ------------------------------- |
| When chosen      | Compile-time   | Run-time                        |
| Performance      | Good           | Often best                      |
| Flexibility      | Limited        | Very flexible                   |
| Fancy pointers   | Supports       | Supports                        |
| Used in industry | Old systems    | Modern systems, gaming, finance |

⭐ 13. Real-World Use Cases
✔ High-performance systems

Game engines, simulations, trading systems.

✔ Custom memory domains

GPU buffers

NUMA memory

Shared memory

✔ Memory pools for small objects

Avoids fragmentation.

✔ Logging/debug allocators

Detect leaks, track usage.

⭐ 14. Interview-Level Summary

Allocators abstract memory allocation strategy.
Containers depend on them for storage.
Custom allocators enable faster, safer, or specialized memory handling.
C++17 PMR makes allocators flexible at runtime and easier to use.















✅ 1. What is an Allocator in Modern C++?
An allocator is responsible for separating memory allocation from object construction.
Allocators provide two distinct operations:

✔ Allocation / Deallocation
Works on raw bytes
allocate(n)
deallocate(ptr, n)

✔ Construction / Destruction
Constructs or destroys an object at a memory location
std::allocator_traits::construct(a, p, args...)
std::allocator_traits::destroy(a, p)
Since C++17, direct use of construct and destroy in allocators is removed:
Use allocator_traits instead.




📌 PROGRAM 1: Using std::allocator (C++11 → C++20)
Full program with output.

#include <iostream>
#include <memory>

int main() {
    std::allocator<int> alloc;

    // Allocate memory for 5 ints (uninitialized)
    int* p = alloc.allocate(5);

    // Construct values
    for (int i = 0; i < 5; ++i)
        std::allocator_traits<std::allocator<int>>::construct(alloc, p + i, i * 10);

    // Print values
    std::cout << "Values stored using std::allocator:\n";
    for (int i = 0; i < 5; i++)
        std::cout << p[i] << " ";
    std::cout << "\n";

    // Destroy constructed objects
    for (int i = 0; i < 5; i++)
        std::allocator_traits<std::allocator<int>>::destroy(alloc, p + i);

    // Deallocate raw memory
    alloc.deallocate(p, 5);
}
/* 
✅ Output
Values stored using std::allocator:
0 10 20 30 40
*/






📌 PROGRAM 2: Custom Allocator (C++11 → C++20)
A simple custom allocator that logs operations.

#include <iostream>
#include <memory>

template <typename T>
struct LoggingAllocator {
    using value_type = T;

    LoggingAllocator() = default;

    template <typename U>
    LoggingAllocator(const LoggingAllocator<U>&) {}

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " object(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " object(s)\n";
        ::operator delete(p);
    }
};

int main() {
    LoggingAllocator<int> alloc;

    int* p = alloc.allocate(3);

    for (int i = 0; i < 3; i++)
        std::allocator_traits<LoggingAllocator<int>>::construct(alloc, p + i, i + 1);

    std::cout << "Values: ";
    for (int i = 0; i < 3; i++)
        std::cout << p[i] << " ";
    std::cout << "\n";

    for (int i = 0; i < 3; i++)
        std::allocator_traits<LoggingAllocator<int>>::destroy(alloc, p + i);

    alloc.deallocate(p, 3);
}
/* 
✅ Output
Allocating 3 object(s)
Values: 1 2 3
Deallocating 3 object(s)
*/




📌 PROGRAM 3: Allocator with std::vector
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::vector<int, std::allocator<int>> vec;

    vec.push_back(5);
    vec.push_back(10);

    std::cout << "Vector elements: ";
    for (int v : vec)
        std::cout << v << " ";
}
/* 
Output
Vector elements: 5 10
*/



🔥 C++17–C++20: Polymorphic Allocator (std::pmr)
<memory_resource> introduced in C++17 gives:
std::pmr::memory_resource
std::pmr::polymorphic_allocator
Predefined memory resources:
monotonic_buffer_resource
unsynchronized_pool_resource
synchronized_pool_resource
new_delete_resource()
These enable runtime-selectable allocation strategy.



📌 PROGRAM 4: Using pmr::monotonic_buffer_resource (C++17/20)
#include <iostream>
#include <vector>
#include <memory_resource>
int main() {
    std::byte buffer[1024];

    std::pmr::monotonic_buffer_resource pool(buffer, sizeof(buffer));
    std::pmr::vector<int> vec(&pool);

    for (int i = 1; i <= 5; i++)
        vec.push_back(i * 10);

    std::cout << "Values stored using monotonic buffer resource:\n";
    for (int v : vec)
        std::cout << v << " ";
}
/* 
Output
Values stored using monotonic buffer resource:
10 20 30 40 50
*/




📌 PROGRAM 5: pmr::unsynchronized_pool_resource (C++17/20)
#include <iostream>
#include <memory_resource>
#include <vector>
int main() {
    std::pmr::unsynchronized_pool_resource pool;
    std::pmr::vector<int> vec(&pool);

    for (int i = 0; i < 4; ++i)
        vec.push_back(i + 1);

    std::cout << "Using unsynchronized pool resource:\n";
    for (int x : vec)
        std::cout << x << " ";
}
/* 
Output
Using unsynchronized pool resource:
1 2 3 4
*/





📌 PROGRAM 6: Run-time switchable allocator (pmr) (C++17/20)
#include <iostream>
#include <memory_resource>
#include <vector>
void test(std::pmr::memory_resource* mr) {
    std::pmr::vector<int> v(mr);
    v.push_back(100);
    v.push_back(200);

    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}
int main() {
    std::pmr::monotonic_buffer_resource mono;
    std::pmr::unsynchronized_pool_resource pool;

    std::cout << "Using monotonic buffer resource: ";
    test(&mono);

    std::cout << "Using unsynchronized pool: ";
    test(&pool);
}
/* 
Output
Using monotonic buffer resource: 100 200 
Using unsynchronized pool: 100 200
*/