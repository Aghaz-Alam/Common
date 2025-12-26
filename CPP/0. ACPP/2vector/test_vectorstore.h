#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_vector_set_and_get() {
    VectorStore<T> v;
    v.set(0, T{42});
    assert(v.get(0) == T{42});
}

template<typename T>
void test_vector_resize_on_set() {
    VectorStore<T> v;
    v.set(5, T{99});          // forces resize to size 6
    assert(v.size() == 6);
    assert(v.get(5) == T{99});
}

template<typename T>
void test_vector_remove() {
    VectorStore<T> v;
    v.set(0, T{10});
    v.set(1, T{20});
    v.remove(0);
    assert(v.get(0) == T{20});
}

template<typename T>
void test_vector_exists() {
    VectorStore<T> v;
    v.set(2, T{50});
    assert(v.exists(2));
    assert(!v.exists(10));
}

template<typename T>
void test_vector_clear() {
    VectorStore<T> v;
    v.set(0, T{1});
    v.clear();
    assert(v.size() == 0);
}

template<typename T>
void test_vector_out_of_range_get() {
    VectorStore<T> v;
    bool thrown = false;
    try {
        v.get(10);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown && "Expected out_of_range exception");
}

template<typename T>
void run_vectorstore_tests() {
    std::cout << "Running VectorStore Tests...\n";
    
    test_vector_set_and_get<T>();
    test_vector_resize_on_set<T>();
    test_vector_remove<T>();
    test_vector_exists<T>();
    test_vector_clear<T>();
    test_vector_out_of_range_get<T>();
    
    std::cout << "All VectorStore tests passed!\n\n";
}



