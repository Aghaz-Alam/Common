#include <iostream>
#include "UnorderedMapStore.hpp"
#include "test_unordered_map.h"

int main() {
    std::cout << "==============================\n";
    std::cout << "UnorderedMapStore<K,V> Demo\n";
    std::cout << "==============================\n\n";

    // Run all unit tests
    run_unordered_mapstore_tests<std::string, int>();

    // ------------------------------------------------------
    // Manual demonstration
    // ------------------------------------------------------
    UnorderedMapStore<std::string, int> store;

    std::cout << "[1] Insert values...\n";
    store.set("age", 25);
    store.set("score", 90);
    store.set("level", 5);
    std::cout << "  Inserted: age=25, score=90, level=5\n\n";

    std::cout << "[2] Check existence...\n";
    std::cout << "  exists(age) = " << std::boolalpha << store.exists("age") << "\n";
    std::cout << "  exists(height) = " << store.exists("height") << "\n\n";

    std::cout << "[3] Get values...\n";
    try {
        std::cout << "  get(age) = " << store.get("age") << "\n";
        std::cout << "  get(score) = " << store.get("score") << "\n";
        std::cout << "  get(height) = " << store.get("height") << "\n"; // will throw
    } catch (const std::exception& ex) {
        std::cout << "  Exception: " << ex.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "[4] Overwrite value...\n";
    store.set("age", 30);
    std::cout << "  Updated age = " << store.get("age") << "\n\n";

    std::cout << "[5] Size of map...\n";
    std::cout << "  size = " << store.size() << "\n\n";

    std::cout << "[6] Remove a key...\n";
    store.remove("level");
    std::cout << "  Removed 'level'\n";
    std::cout << "  exists(level) = " << store.exists("level") << "\n";
    std::cout << "  size = " << store.size() << "\n\n";

    std::cout << "[7] Clear the map...\n";
    store.clear();
    std::cout << "  size after clear = " << store.size() << "\n";
    std::cout << "  exists(age) = " << store.exists("age") << "\n\n";

    std::cout << "Demo complete.\n";
    return 0;
}
/* 
==============================
UnorderedMapStore<K,V> Demo
==============================

Running UnorderedMapStore Tests...
All UnorderedMapStore tests passed!

[1] Insert values...
  Inserted: age=25, score=90, level=5

[2] Check existence...
  exists(age) = true
  exists(height) = false

[3] Get values...
  get(age) = 25
  get(score) = 90
  get(height) =   Exception: UnorderedMapStore::get() - key not found

[4] Overwrite value...
  Updated age = 30

[5] Size of map...
  size = 3

[6] Remove a key...
  Removed 'level'
  exists(level) = false
  size = 2

[7] Clear the map...
  size after clear = 0
  exists(age) = false

Demo complete.
*/