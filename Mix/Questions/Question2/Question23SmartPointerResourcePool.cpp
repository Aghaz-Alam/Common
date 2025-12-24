/* 
23. Smart Pointer Resource Pool (Smart pointers, RAII)

Problem: Build a ResourcePool that hands out unique resources using std::unique_ptr and returns them to the pool when released.

Requirements / Features:
Resource is a simple struct Connection { int id; }.
ResourcePool preallocates N resources.
Provide acquire() returning std::unique_ptr<Connection, custom_deleter> where the custom deleter returns the resource to the pool instead of deleting.
Ensure thread-safety (use std::mutex) for pool operations.
Demonstrate usage by acquiring multiple resources and releasing some, showing reuse of IDs.

Sample Output: Acquire id 1, 2; release 1; next acquire returns id 1.
*/


//Smart Pointer Resource Pool
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <queue>

// Simple resource
struct Connection {
    int id;
    Connection(int i) : id(i) {}
};

// Forward declaration
class ResourcePool;

// Custom deleter that returns the resource to the pool
struct ResourceDeleter {
    ResourcePool* pool;

    void operator()(Connection* conn);
};

// Resource Pool
class ResourcePool {
private:
    std::mutex mtx;
    std::queue<std::unique_ptr<Connection>> available;

public:
    ResourcePool(int N) {
        for (int i = 1; i <= N; ++i) {
            available.push(std::make_unique<Connection>(i));
        }
    }

    // Acquire resource: returns unique_ptr with custom deleter
    std::unique_ptr<Connection, ResourceDeleter> acquire() {
        std::lock_guard<std::mutex> lock(mtx);

        if (available.empty())
            throw std::runtime_error("No available resources");

        auto conn = std::move(available.front());
        available.pop();

        return std::unique_ptr<Connection, ResourceDeleter>(conn.release(), ResourceDeleter{this});
    }

    // Return resource to the pool
    void release(Connection* conn) {
        std::lock_guard<std::mutex> lock(mtx);
        available.push(std::unique_ptr<Connection>(conn));
    }

    // For debugging: print available IDs
    void printAvailable() {
        std::lock_guard<std::mutex> lock(mtx);
        std::queue<std::unique_ptr<Connection>> copy = available;
        std::cout << "Available IDs: ";
        while (!copy.empty()) {
            std::cout << copy.front()->id << " ";
            copy.pop();
        }
        std::cout << "\n";
    }
};

// Define the custom deleter
void ResourceDeleter::operator()(Connection* conn) {
    pool->release(conn);
}
//Demonstration
int main() {
    ResourcePool pool(3); // preallocate 3 resources

    auto r1 = pool.acquire();
    std::cout << "Acquired id " << r1->id << "\n";

    auto r2 = pool.acquire();
    std::cout << "Acquired id " << r2->id << "\n";

    pool.printAvailable();

    // Release r1 manually (by letting unique_ptr go out of scope)
    r1.reset(); // returned to pool
    std::cout << "Released r1\n";

    pool.printAvailable();

    // Acquire again, should reuse id 1
    auto r3 = pool.acquire();
    std::cout << "Acquired id " << r3->id << "\n";

    pool.printAvailable();

    return 0;
}
/* 
Sample Output:
Acquired id 1
Acquired id 2
Available IDs: 3 
Released r1
Available IDs: 3 1 
Acquired id 1
Available IDs: 3 
*/