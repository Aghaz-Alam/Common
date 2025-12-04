#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_list_set_get() {
    ListStore<T> ls;
    ls.set(100);
    assert(ls.get() == 100);
}

template<typename T>
void test_list_push_back_behavior() {
    ListStore<T> ls;
    ls.set(1);
    ls.set(2);
    ls.set(3);
    assert(ls.get() == 1);   // since push_back
}

template<typename T>
void test_list_remove() {
    ListStore<T> ls;
    ls.set(10);
    ls.set(20);
    ls.remove();            // removes 10
    assert(ls.get() == 20);
}

template<typename T>
void test_list_size() {
    ListStore<T> ls;
    ls.set(1);
    ls.set(2);
    ls.set(3);
    assert(ls.size() == 3);
}

template<typename T>
void test_list_clear() {
    ListStore<T> ls;
    ls.set(5);
    ls.set(6);
    ls.clear();
    assert(ls.size() == 0);
    assert(ls.exists() == false);
}

template<typename T>
void test_list_exception() {
    ListStore<T> ls;
    bool thrown = false;

    try {
        ls.get();
    } catch(const std::runtime_error&) {
        thrown = true;
    }

    assert(thrown && "Expected exception for get() on empty list");
}

template<typename T>
void run_liststore_tests() {
    std::cout << "Running ListStore Tests...\n";

    test_list_set_get<T>();
    test_list_push_back_behavior<T>();
    test_list_remove<T>();
    test_list_size<T>();
    test_list_clear<T>();
    test_list_exception<T>();

    std::cout << "All ListStore tests passed!\n\n";
}
