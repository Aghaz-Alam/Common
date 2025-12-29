#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_deque_set_and_get() {
    DequeStore<T> dq;
    dq.set(0, 42);
    assert(dq.get(0) == 42);
}

template<typename T>
void test_deque_resize_on_set() {
    DequeStore<T> dq;
    dq.set(5, 99);  // forces resize
    assert(dq.size() == 6);
    assert(dq.get(5) == 99);
}

template<typename T>
void test_deque_remove() {
    DequeStore<T> dq;
    dq.set(0, 10);
    dq.set(1, 20);
    dq.remove(0);
    assert(dq.get(0) == 20);
    assert(dq.size() == 1);
}

template<typename T>
void test_deque_exists() {
    DequeStore<T> dq;
    dq.set(2, 50);
    assert(dq.exists(2));
    assert(!dq.exists(10));
}

template<typename T>
void test_deque_clear() {
    DequeStore<T> dq;
    dq.set(0, 1);
    dq.set(1, 2);
    dq.clear();
    assert(dq.size() == 0);
    assert(!dq.exists(0));
}

template<typename T>
void test_deque_out_of_range() {
    DequeStore<T> dq;
    bool thrown = false;
    try {
        dq.get(10);
    } catch(const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown && "Expected out_of_range exception");
}

template<typename T>
void run_dequestore_tests() {
    std::cout << "Running DequeStore Tests...\n";
    test_deque_set_and_get<T>();
    test_deque_resize_on_set<T>();
    test_deque_remove<T>();
    test_deque_exists<T>();
    test_deque_clear<T>();
    test_deque_out_of_range<T>();
    std::cout << "All DequeStore tests passed!\n\n";
}
