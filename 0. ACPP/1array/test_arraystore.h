#pragma once
#include <iostream>
#include <cassert>

template<typename T, std::size_t N>
void test_set_and_get() {
    ArrayStore<T, N> arr;
    arr.set(0, T{42});
    assert(arr.get(0) == T{42});
}

template<typename T, std::size_t N>
void test_out_of_range_set() {
    ArrayStore<T, N> arr;
    bool thrown = false;
    try {
        arr.set(N + 1, T{10});
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown && "Expected std::out_of_range for invalid set()");
}

template<typename T, std::size_t N>
void test_remove() {
    ArrayStore<T, N> arr;
    arr.set(1, T{55});
    arr.remove(1);
    assert(arr.get(1) == T{});  // reset to default value
}

template<typename T, std::size_t N>
void test_exists() {
    ArrayStore<T, N> arr;
    arr.set(0, T{10});
    assert(arr.exists(0));
    assert(!arr.exists(N));   // out of bounds
}

template<typename T, std::size_t N>
void test_size() {
    ArrayStore<T, N> arr;
    assert(arr.size() == N);
}

template<typename T, std::size_t N>
void test_clear() {
    ArrayStore<T, N> arr;
    arr.set(0, T{99});
    arr.clear();
    assert(arr.get(0) == T{});  // reset to default
}

template<typename T, std::size_t N>
void test_get_out_of_range() {
    ArrayStore<T, N> arr;
    bool thrown = false;
    try {
        arr.get(N);  // invalid
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown && "Expected std::out_of_range for get()");
}

template<typename T, std::size_t N>
void run_all_arraystore_tests() {
    std::cout << "\nRunning ArrayStore Unit Tests...\n";

    test_set_and_get<T, N>();
    test_out_of_range_set<T, N>();
    test_remove<T, N>();
    test_exists<T, N>();
    test_size<T, N>();
    test_clear<T, N>();
    test_get_out_of_range<T, N>();

    std::cout << "All ArrayStore tests passed successfully!\n";
}
