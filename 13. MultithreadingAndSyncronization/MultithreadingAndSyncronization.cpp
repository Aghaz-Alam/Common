multithreading and syncronization
- lock_guard, unique_lock
- condition variables
- calling class members from thread , or using as thread function





Multithreading and Synchronization in C++11, C++14, and C++17:
To demonstrate the differences and the commonalities in multithreading and synchronization in C++ across versions, we'll focus on:
Thread Creation and Joining using std::thread
Synchronization using std::mutex, std::lock_guard, std::unique_lock, and std::condition_variable
Calling Class Members from Threads



Let's break down the versions and provide examples:
C++11 Example:
In C++11, the std::thread, std::mutex, std::lock_guard, std::unique_lock, and std::condition_variable were all introduced.

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>
using namespace std;

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;

class Producer {
  public:
    void produce(int numItems) {
        for (int i = 0; i < numItems; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "Produced item: " << i << std::endl;
            cv.notify_all();
        }
    }
};

class Consumer {
  public:
    void consume() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []() { return !dataQueue.empty(); });
            int item = dataQueue.front();
            dataQueue.pop();
            lock.unlock();
            std::cout << "Consumed item: " << item << std::endl;
            if (item == 9) break;
        }
    }
};

int main() {
    Producer producer;
    Consumer consumer;

    std::thread producerThread(&Producer::produce, &producer, 10);
    std::thread consumerThread(&Consumer::consume, &consumer);

    producerThread.join();
    consumerThread.join();

    std::cout << "All items produced and consumed." << std::endl;
  return 0;
}

Explanation:
std::mutex: Used to prevent data races when accessing the shared queue.
std::lock_guard: Provides a simple way to lock and unlock the mutex.
std::unique_lock: Used in the consumer to allow more flexibility, such as manually unlocking the mutex.
std::condition_variable: Allows threads to wait until a certain condition is met (i.e., the queue is not empty).






C++14 Example:
In C++14, the multithreading features from C++11 remain unchanged, but the key difference lies in lambda expressions 
and std::condition_variable::wait with predicates becoming more flexible.

Changes in C++14:
Improved lambda expressions: In C++14, you can use lambda expressions directly with std::condition_variable::wait for predicates.

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>
using namespace std;
std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;

class Producer {
public:
    void produce(int numItems) {
        for (int i = 0; i < numItems; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "Produced item: " << i << std::endl;
            cv.notify_all();
        }
    }
};

class Consumer {
  public:
    void consume() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []() { return !dataQueue.empty(); });  // C++14 lambda with condition variable
            int item = dataQueue.front();
            dataQueue.pop();
            lock.unlock();
            std::cout << "Consumed item: " << item << std::endl;
            if (item == 9) break;
        }
    }
};

int main() {
    Producer producer;
    Consumer consumer;

    std::thread producerThread(&Producer::produce, &producer, 10);
    std::thread consumerThread(&Consumer::consume, &consumer);

    producerThread.join();
    consumerThread.join();

    std::cout << "All items produced and consumed." << std::endl;
  return 0;
}

Explanation:
C++14 Enhancements: The key difference is the improved lambda expression syntax, particularly in the condition_variable::wait function 
where a lambda can be used to specify the predicate directly.



C++17 Example:
C++17 introduces a few changes and improvements, including std::shared_mutex and the std::scoped_lock (which allows multiple mutexes 
to be locked at once), but in terms of the basic threading and synchronization mechanisms 
(std::thread, std::mutex, std::lock_guard, std::unique_lock, std::condition_variable), it remains mostly the same as C++14.



In C++17, there is also the introduction of std::scoped_lock to simplify locking multiple mutexes.
Changes in C++17:
std::scoped_lock: It allows locking multiple mutexes at once, avoiding potential deadlocks.

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>
using namespace std;
std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;

class Producer {
 public:
    void produce(int numItems) {
        for (int i = 0; i < numItems; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "Produced item: " << i << std::endl;
            cv.notify_all();
        }
    }
};
class Consumer {
  public:
    void consume() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []() { return !dataQueue.empty(); });
            int item = dataQueue.front();
            dataQueue.pop();
            lock.unlock();
            std::cout << "Consumed item: " << item << std::endl;
            if (item == 9) break;
        }
    }
};

int main() {
    Producer producer;
    Consumer consumer;

    std::thread producerThread(&Producer::produce, &producer, 10);
    std::thread consumerThread(&Consumer::consume, &consumer);

    producerThread.join();
    consumerThread.join();

    std::cout << "All items produced and consumed." << std::endl;
  return 0;
}

Explanation:
No major changes in multithreading: In this specific example, the main functionality remains almost identical to C++14, 
but C++17 introduces std::scoped_lock for more convenient locking when multiple mutexes need to be locked at the same time, 
which simplifies code and avoids some types of deadlocks.