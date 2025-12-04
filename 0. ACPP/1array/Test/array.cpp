#include <iostream>
#include "ArrayStore.hpp"
#include "test_ArrayStore.h"

int main() {
    // Run automated unit tests
    run_arraystore_tests();

    // Manual demo
    std::cout << "==============================\n";
    std::cout << "ArrayStore<T, N> Demonstration\n";
    std::cout << "==============================\n\n";

    ArrayStore<int, 5> arr;

    try {
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        std::cout << "Values set: {10, 20, 30, 0, 0}\n\n";

        std::cout << "arr.get(0) = " << arr.get(0) << "\n";
        std::cout << "arr.get(1) = " << arr.get(1) << "\n";
        std::cout << "arr.get(2) = " << arr.get(2) << "\n\n";

        std::cout << "exists(0): " << std::boolalpha << arr.exists(0) << "\n";
        std::cout << "exists(3): " << std::boolalpha << arr.exists(3) << "\n";
        std::cout << "exists(5): " << std::boolalpha << arr.exists(5) << "\n\n";

        arr.remove(1);
        std::cout << "After remove(1), arr.get(1) = " << arr.get(1) << "\n\n";

        std::cout << "Size = " << arr.size() << "\n\n";

        arr.clear();
        std::cout << "After clear, arr.get(0) = " << arr.get(0) << "\n\n";

        std::cout << "Attempting arr.get(10) to trigger exception:\n";
        std::cout << arr.get(10) << "\n";

    } catch (const std::exception& ex) {
        std::cerr << "[Exception Caught]: " << ex.what() << "\n";
    }

    std::cout << "\nDemo complete.\n";
    return 0;
}
/* 
All ArrayStore tests passed!

==============================
ArrayStore<T, N> Demonstration
==============================

Values set: {10, 20, 30, 0, 0}

arr.get(0) = 10
arr.get(1) = 20
arr.get(2) = 30

exists(0): true
exists(3): true
exists(5): false

After remove(1), arr.get(1) = 0

Size = 5

After clear, arr.get(0) = 0

Attempting arr.get(10) to trigger exception:
[Exception Caught]: Array index out of range

Demo complete.
*/