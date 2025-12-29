#pragma once
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "UnorderedSetStore.hpp"   // ensure this is the header containing your class

// -------------------------------------------------------------
// Test: Insert and existence
// -------------------------------------------------------------
template<typename T>
void test_unordered_set_insert() {
    UnorderedSetStore<T> ss;
    ss.set(10);
    assert(ss.exists(10));
}

// -------------------------------------------------------------
// Test: get(value)
// -------------------------------------------------------------
template<typename T>
void test_unordered_set_get() {
    UnorderedSetStore<T> ss;
    ss.set(42);
    assert(ss.get(42) == 42);

    bool thrown = false;
    try {
        ss.get(99); // should throw
    }
    catch (const std::exception&) {
        thrown = true;
    }
    assert(thrown);
}

// -------------------------------------------------------------
// Test: get() returning any element
// -------------------------------------------------------------
template<typename T>
void test_unordered_set_get_any() {
    UnorderedSetStore<T> ss;
    ss.set(7);

    const T& v = ss.get(); // should not throw
    assert(v == 7);
}

// -------------------------------------------------------------
// Test: duplicate insertion is ignored
// -------------------------------------------------------------
template<typename T>
void test_unordered_set_unique_behavior() {
    UnorderedSetStore<T> ss;
    ss.set(5);
    ss.set(5);
    ss.set(5);
    assert(ss.size() == 1);
}

// -------------------------------------------------------------
// Test: remove()
// -------------------------------------------------------------
template<typename T>
void test_unordered_set_remove() {
    UnorderedSetStore<T> ss;
    ss.set(1);
    ss.set(2);

    ss.remove(1);
    assert(!ss.exists(1));
    assert(ss.exists(2));
}

// -------------------------------------------------------------
// Test: clear()
// -------------------------------------------------------------
template<typename T>
void test_unordered_set_clear() {
    UnorderedSetStore<T> ss;
    ss.set(10);
    ss.set(20);

    ss.clear();
    assert(ss.size() == 0);
    assert(!ss.exists(10));
}

// -------------------------------------------------------------
// Run all tests
// -------------------------------------------------------------
template<typename T>
void run_unordered_setstore_tests() {
    std::cout << "Running UnorderedSetStore Tests...\n";

    test_unordered_set_insert<T>();
    test_unordered_set_get<T>();
    test_unordered_set_get_any<T>();
    test_unordered_set_unique_behavior<T>();
    test_unordered_set_remove<T>();
    test_unordered_set_clear<T>();

    std::cout << "All UnorderedSetStore tests passed!\n\n";
}
