#pragma once
#include <cassert>
#include <iostream>
#include "VectorStore.hpp"

inline void run_vectorstore_tests() {
    std::cout << "Running VectorStore Tests...\n";

    VectorStore<int> vs;

    // Test set/get
    vs.set(0, 10);
    vs.set(1, 20);
    vs.set(5, 99);  // auto-resize
    assert(vs.get(0) == 10);
    assert(vs.get(1) == 20);
    assert(vs.get(5) == 99);

    // Test exists
    assert(vs.exists(0));
    assert(!vs.exists(10));

    // Test remove
    vs.remove(1);
    assert(vs.get(1) == 0); // default int after erase shift
    assert(vs.size() == 5);

    // Test clear
    vs.clear();
    assert(vs.size() == 0);

    // Test exception
    bool thrown = false;
    try { vs.get(0); }
    catch (...) { thrown = true; }
    assert(thrown);

    std::cout << "All VectorStore tests passed!\n\n";
}
