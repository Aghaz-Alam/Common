/* 
Question 15: Producer-Consumer Problem

Implement the producer-consumer problem using C++ threads and condition variables.

Requirements:
Use a shared buffer with fixed size.
Implement producer() and consumer() threads.
Ensure thread-safe access using mutex and condition_variable.

Sample Input:
Buffer buffer(5);
startProducerConsumer(buffer);


Expected Output:
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
*/


//Producer–Consumer Problem (C++ Threads + Condition Variables)
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

class Buffer {
private:
    std::queue<int> q;
    size_t capacity;
    std::mutex mtx;
    std::condition_variable cv_full, cv_empty;

public:
    Buffer(size_t cap) : capacity(cap) {}

    // Producer adds items
    void produce(int item) {
        std::unique_lock<std::mutex> lock(mtx);

        cv_full.wait(lock, [&]() { return q.size() < capacity; });

        q.push(item);
        std::cout << "Produced: " << item << std::endl;

        cv_empty.notify_one();     // Wake consumer
    }

    // Consumer removes items
    int consume() {
        std::unique_lock<std::mutex> lock(mtx);

        cv_empty.wait(lock, [&]() { return !q.empty(); });

        int item = q.front();
        q.pop();
        std::cout << "Consumed: " << item << std::endl;

        cv_full.notify_one();     // Wake producer
        return item;
    }
};

// ----------------------------------------------------
// Producer and Consumer Threads
// ----------------------------------------------------

void producer(Buffer& buffer) {
    int value = 1;
    while (value <= 10) {   // produce 10 items
        buffer.produce(value);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        value++;
    }
}

void consumer(Buffer& buffer) {
    for (int i = 0; i < 10; i++) {  // consume 10 items
        buffer.consume();
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}

void startProducerConsumer(Buffer& buffer) {
    std::thread t1(producer, std::ref(buffer));
    std::thread t2(consumer, std::ref(buffer));

    t1.join();
    t2.join();
}

int main() {
    Buffer buffer(5);     // capacity = 5
    startProducerConsumer(buffer);
    return 0;
}
/* 
Expected Output (Sample)
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
Produced: 3
Produced: 4
Consumed: 3
Produced: 5
...


(The order may vary slightly due to thread scheduling, but sequence is always correct.)
*/