#include <iostream>
#include "UnorderedSetStore.hpp"
#include "test_UnorderedSet.h"

int main() {
    // Run all UnorderedSetStore unit tests
    run_unordered_setstore_tests<int>();

    // Optional: manual demonstration
    UnorderedSetStore<int> store;

    store.set(10);
    store.set(20);

    std::cout << "Manual demo:\n";
    std::cout << "exists(10) = " << std::boolalpha << store.exists(10) << "\n";

    try {
        std::cout << "get(20) = " << store.get(20) << "\n";
        std::cout << "get() (any element) = " << store.get() << "\n";
        std::cout << "get(30) = " << store.get(30) << "\n"; // throws
    }
    catch (const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << "\n";
    }

    store.remove(10);
    std::cout << "Size after remove: " << store.size() << "\n";

    store.clear();
    std::cout << "Size after clear: " << store.size() << "\n";

    return 0;
}
/* 
Running UnorderedSetStore Tests...
All UnorderedSetStore tests passed!

Manual demo:
exists(10) = true
get(20) = 20
get() (any element) = 20
get(30) = Exception: UnorderedSetStore::get() - key not found
Size after remove: 1
Size after clear: 0
*/