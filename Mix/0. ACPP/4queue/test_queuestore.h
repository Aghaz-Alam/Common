#pragma once
#include <cassert>
#include <iostream>

template<typename T>
void test_queue_enqueue_and_get() {
    QueueStore<T> q;
    q.set(42);
    assert(q.get() == 42);
}

template<typename T>
void test_queue_remove() {
    QueueStore<T> q;
    q.set(10);
    q.set(20);
    q.remove();
    assert(q.get() == 20);
    assert(q.size() == 1);
}

template<typename T>
void test_queue_exists_and_size() {
    QueueStore<T> q;
    assert(!q.exists());
    q.set(5);
    assert(q.exists());
    assert(q.size() == 1);
}

template<typename T>
void test_queue_clear() {
    QueueStore<T> q;
    q.set(1);
    q.set(2);
    q.clear();
    assert(q.size() == 0);
    assert(!q.exists());
}

template<typename T>
void test_queue_exception() {
    QueueStore<T> q;
    bool thrown = false;
    try {
        q.get();
    } catch(const std::runtime_error&) {
        thrown = true;
    }
    assert(thrown && "Expected exception on get() for empty queue");
}

template<typename T>
void run_queuestore_tests() {
    std::cout << "Running QueueStore Tests...\n";
    test_queue_enqueue_and_get<T>();
    test_queue_remove<T>();
    test_queue_exists_and_size<T>();
    test_queue_clear<T>();
    test_queue_exception<T>();
    std::cout << "All QueueStore tests passed!\n\n";
}
