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