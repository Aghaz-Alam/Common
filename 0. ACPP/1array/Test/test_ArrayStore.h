#pragma once
#include <cassert>
#include <iostream>
#include "ArrayStore.hpp"

inline void run_arraystore_tests() {
    std::cout << "Running ArrayStore Tests...\n";

    ArrayStore<int, 5> arr;

    // Test set/get
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);
    assert(arr.get(0) == 10);
    assert(arr.get(1) == 20);
    assert(arr.get(2) == 30);

    // Test exists
    assert(arr.exists(0));
    assert(arr.exists(4));
    assert(!arr.exists(5));

    // Test remove
    arr.remove(1);
    assert(arr.get(1) == 0);

    // Test clear
    arr.clear();
    for (std::size_t i = 0; i < arr.size(); ++i)
        assert(arr.get(i) == 0);

    // Test exception
    bool thrown = false;
    try { arr.get(10); } catch(...) { thrown = true; }
    assert(thrown);

    std::cout << "All ArrayStore tests passed!\n\n";
}
