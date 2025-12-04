#include <iostream>
#include "VectorStore.hpp"
#include "test_VectorStore.h"

int main() {
    // Run automated unit tests
    run_vectorstore_tests();

    // Manual demonstration
    std::cout << "==============================\n";
    std::cout << "VectorStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    VectorStore<int> vec;

    try {
        vec.set(0, 10);
        vec.set(1, 20);
        vec.set(5, 99);  // auto-resize
        std::cout << "Values set: {10,20,0,0,0,99}\n\n";

        std::cout << "vec.get(0) = " << vec.get(0) << "\n";
        std::cout << "vec.get(1) = " << vec.get(1) << "\n";
        std::cout << "vec.get(5) = " << vec.get(5) << "\n\n";

        std::cout << "exists(1): " << std::boolalpha << vec.exists(1) << "\n";
        std::cout << "exists(10): " << std::boolalpha << vec.exists(10) << "\n\n";

        vec.remove(1);
        std::cout << "After remove(1), vec.get(1) = " << vec.get(1) << "\n\n";

        std::cout << "Size = " << vec.size() << "\n\n";

        vec.clear();
        std::cout << "Size after clear = " << vec.size() << "\n\n";

        std::cout << "Attempting vec.get(100) to trigger exception:\n";
        std::cout << vec.get(100) << "\n"; // will throw

    } catch(const std::exception& ex) {
        std::cerr << "[EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}
/* 
Running VectorStore Tests...
All VectorStore tests passed!

==============================
VectorStore<T> Demonstration
==============================

Values set: {10,20,0,0,0,99}

vec.get(0) = 10
vec.get(1) = 20
vec.get(5) = 99

exists(1): true
exists(10): false

After remove(1), vec.get(1) = 0

Size = 5

Size after clear = 0

Attempting vec.get(100) to trigger exception:
[EXCEPTION]: Index out of range
Demo complete.
*/