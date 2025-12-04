#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_set_insert() {
    SetStore<T> ss;
    ss.set(10);
    assert(ss.exists(10));
}

template<typename T>
void test_set_unique_behavior() {
    SetStore<T> ss;
    ss.set(5);
    ss.set(5);
    ss.set(5);
    assert(ss.size() == 1);   // duplicates ignored
}

template<typename T>
void test_set_remove() {
    SetStore<T> ss;
    ss.set(1);
    ss.set(2);
    ss.remove(1);
    assert(!ss.exists(1));
    assert(ss.exists(2));
}

template<typename T>
void test_set_exists() {
    SetStore<T> ss;
    ss.set(50);
    assert(ss.exists(50));
    assert(!ss.exists(5));
}

template<typename T>
void test_set_clear() {
    SetStore<T> ss;
    ss.set(10);
    ss.set(20);
    ss.clear();
    assert(ss.size() == 0);
    assert(!ss.exists(10));
}

template<typename T>
void test_set_get_value() {
    SetStore<T> ss;
    ss.set(10);
    ss.set(3);
    ss.set(7);
    assert(ss.get(7) == 7);
    assert(ss.get(10) == 10);
}

template<typename T>
void test_set_get_smallest() {
    SetStore<T> ss;
    ss.set(40);
    ss.set(10);
    ss.set(25);
    assert(ss.get() == 10);     // smallest element
}

template<typename T>
void test_set_get_invalid() {
    SetStore<T> ss;
    bool thrown = false;

    try {
        ss.get(99);
    }
    catch (const std::exception&) {
        thrown = true;
    }

    assert(thrown == true);
}

template<typename T>
void test_set_get_empty() {
    SetStore<T> ss;
    bool thrown = false;

    try {
        ss.get();   // get smallest
    }
    catch (const std::exception&) {
        thrown = true;
    }

    assert(thrown == true);
}

template<typename T>
void run_setstore_tests() {
    std::cout << "Running SetStore Tests...\n";

    test_set_insert<T>();
    test_set_unique_behavior<T>();
    test_set_remove<T>();
    test_set_exists<T>();
    test_set_clear<T>();
    test_set_get_value<T>();
    test_set_get_smallest<T>();
    test_set_get_invalid<T>();
    test_set_get_empty<T>();

    std::cout << "All SetStore tests passed!\n\n";
}
