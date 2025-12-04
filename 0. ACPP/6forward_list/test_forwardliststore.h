#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_forwardlist_set_get() {
    ForwardListStore<T> fl;
    fl.set(5);
    assert(fl.get() == 5);
}

template<typename T>
void test_forwardlist_multiple_push() {
    ForwardListStore<T> fl;
    fl.set(1);
    fl.set(2);
    fl.set(3);
    assert(fl.get() == 3); // LIFO, push_front
}

template<typename T>
void test_forwardlist_remove() {
    ForwardListStore<T> fl;
    fl.set(10);
    fl.set(20);
    fl.remove();
    assert(fl.get() == 10);
}

template<typename T>
void test_forwardlist_size() {
    ForwardListStore<T> fl;
    fl.set(1);
    fl.set(2);
    fl.set(3);
    assert(fl.size() == 3);
}

template<typename T>
void test_forwardlist_clear() {
    ForwardListStore<T> fl;
    fl.set(10);
    fl.set(20);
    fl.clear();
    assert(fl.size() == 0);
    assert(!fl.exists());
}

template<typename T>
void test_forwardlist_exception() {
    ForwardListStore<T> fl;
    bool thrown = false;

    try {
        fl.get();
    } catch(const std::runtime_error&) {
        thrown = true;
    }

    assert(thrown && "Expected runtime_error for empty get()");
}

template<typename T>
void run_forwardliststore_tests() {
    std::cout << "Running ForwardListStore Tests...\n";

    test_forwardlist_set_get<T>();
    test_forwardlist_multiple_push<T>();
    test_forwardlist_remove<T>();
    test_forwardlist_size<T>();
    test_forwardlist_clear<T>();
    test_forwardlist_exception<T>();

    std::cout << "All ForwardListStore tests passed!\n\n";
}
