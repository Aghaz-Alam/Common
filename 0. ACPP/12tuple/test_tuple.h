#pragma once
#include <cassert>
#include <iostream>
#include "TupleStore.hpp"

inline void run_tuplestore_tests() {
    std::cout << "Running TupleStore Tests...\n";

    TupleStore<int, double, std::string> ts;

    // ------------------------------------------------------
    // Test set and get
    // ------------------------------------------------------
    ts.set<0>(42);
    ts.set<1>(3.14);
    ts.set<2>("hello");

    assert(ts.get<0>() == 42);
    assert(ts.get<1>() == 3.14);
    assert(ts.get<2>() == "hello");

    // ------------------------------------------------------
    // Test exists<I>() — use runtime assert instead of static_assert
    // ------------------------------------------------------
    assert(ts.exists<0>() == true);
    assert(ts.exists<1>() == true);
    assert(ts.exists<2>() == true);

    // ------------------------------------------------------
    // Test remove<I>()
    // ------------------------------------------------------
    ts.remove<1>();
    assert(ts.get<1>() == 0.0);  // default-constructed double

    ts.remove<2>();
    assert(ts.get<2>() == "");   // default-constructed string

    // ------------------------------------------------------
    // Test clear()
    // ------------------------------------------------------
    ts.clear();
    assert(ts.get<0>() == 0);    // default-constructed int
    assert(ts.get<1>() == 0.0);
    assert(ts.get<2>() == "");

    // ------------------------------------------------------
    // Test size()
    // ------------------------------------------------------
    assert(ts.size() == 3);

    std::cout << "All TupleStore tests passed!\n\n";
}
