#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_stack_push_and_get() {
    StackStore<T> s;
    s.set(42);
    assert(s.get() == 42);
}

template<typename T>
void test_stack_remove() {
    StackStore<T> s;
    s.set(10);
    s.set(20);
    s.remove();
    assert(s.get() == 10);
    assert(s.size() == 1);
}

template<typename T>
void test_stack_exists_and_size() {
    StackStore<T> s;
    assert(!s.exists());
    s.set(5);
    assert(s.exists());
    assert(s.size() == 1);
}

template<typename T>
void test_stack_clear() {
    StackStore<T> s;
    s.set(1);
    s.set(2);
    s.clear();
    assert(s.size() == 0);
    assert(!s.exists());
}

template<typename T>
void test_stack_exception() {
    StackStore<T> s;
    bool thrown = false;
    try {
        s.get();
    } catch(const std::runtime_error&) {
        thrown = true;
    }
    assert(thrown && "Expected exception on get() for empty stack");
}

template<typename T>
void run_stackstore_tests() {
    std::cout << "Running StackStore Tests...\n";
    test_stack_push_and_get<T>();
    test_stack_remove<T>();
    test_stack_exists_and_size<T>();
    test_stack_clear<T>();
    test_stack_exception<T>();
    std::cout << "All StackStore tests passed!\n\n";
}
