#pragma once
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "MapStore.hpp"

// -------------------------------------------------------------
// Test: Insert and existence
// -------------------------------------------------------------
template<typename K, typename V>
void test_map_insert() {
    MapStore<K, V> mp;
    mp.set("key1", V(100));
    assert(mp.exists("key1"));
}

// -------------------------------------------------------------
// Test: get(key)
// -------------------------------------------------------------
template<typename K, typename V>
void test_map_get() {
    MapStore<K, V> mp;
    mp.set("key1", V(42));
    assert(mp.get("key1") == 42);

    bool thrown = false;
    try {
        mp.get("keyX"); // should throw
    } catch (const std::exception&) {
        thrown = true;
    }
    assert(thrown);
}

// -------------------------------------------------------------
// Test: overwrite value
// -------------------------------------------------------------
template<typename K, typename V>
void test_map_overwrite() {
    MapStore<K, V> mp;
    mp.set("key1", V(10));
    mp.set("key1", V(20));
    assert(mp.get("key1") == 20);
}

// -------------------------------------------------------------
// Test: remove key
// -------------------------------------------------------------
template<typename K, typename V>
void test_map_remove() {
    MapStore<K, V> mp;
    mp.set("a", V(1));
    mp.set("b", V(2));

    mp.remove("a");
    assert(!mp.exists("a"));
    assert(mp.exists("b"));
}

// -------------------------------------------------------------
// Test: clear map
// -------------------------------------------------------------
template<typename K, typename V>
void test_map_clear() {
    MapStore<K, V> mp;
    mp.set("x", V(10));
    mp.set("y", V(20));

    mp.clear();
    assert(mp.size() == 0);
    assert(!mp.exists("x"));
}

// -------------------------------------------------------------
// Run all tests
// -------------------------------------------------------------
template<typename K, typename V>
void run_mapstore_tests() {
    std::cout << "Running MapStore Tests...\n";

    test_map_insert<K, V>();
    test_map_get<K, V>();
    test_map_overwrite<K, V>();
    test_map_remove<K, V>();
    test_map_clear<K, V>();

    std::cout << "All MapStore tests passed!\n\n";
}
