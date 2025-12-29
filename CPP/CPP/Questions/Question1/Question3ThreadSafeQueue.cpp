/* 
ThreadSafeQueue:
Question 3 : Design a thread-safe queue data structure in C++ that supports concurrent push, pop, and size operations. 
Ensure that the implementation does not lead to race conditions or deadlocks.

Expected result : Push value: 0
		  Popped value: 0
		  Push value: 1
	  	  Popped value: 1
	  	  Push value: 2
	  	  Popped value: 2
	  	  Push value: 3
	  	  Popped value: 3
	  	  Push value: 4
	  	  Popped value: 4
	  	  Push value: 5
	  	  Popped value: 5
	  	  Push value: 6
	  	  Popped value: 6
	  	  Push value: 7
	  	  Popped value: 7
	  	  Push value: 8
	  	  Popped value: 8
	  	  Push value: 9
	  	  Popped value: 9
*/



#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
/* ============================================================
   THREAD-SAFE QUEUE IMPLEMENTATION
============================================================ */
template<typename T>
class ThreadSafeQueue {
  private:
    queue<T> q;
    mutable mutex m;
    condition_variable cv;

  public:
    // Push element into queue (thread-safe)
    void push(T value) {
        lock_guard<mutex> lock(m);
        q.push(value);
        cv.notify_one();     // notify a waiting thread
    }

    // Pop element (wait until available)
    T pop() {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this] { return !q.empty(); });  // wait until queue is non-empty
        T value = q.front();
        q.pop();
        return value;
    }

    // Get current size
    size_t size() const {
        lock_guard<mutex> lock(m);
        return q.size();
    }
};
/* ============================================================
   DEMO: PRODUCER & CONSUMER
============================================================ */
int main() {
    ThreadSafeQueue<int> tsq;

    // Producer thread
    thread producer([&]() {
        for (int i = 0; i < 10; i++) {
            cout << "Push value: " << i << endl;
            tsq.push(i);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    // Consumer thread
    thread consumer([&]() {
        for (int i = 0; i < 10; i++) {
            int val = tsq.pop();
            cout << "Popped value: " << val << endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
/*
Push value: 0
Popped value: 0
Push value: 1
Popped value: 1
Push value: 2
Popped value: 2
Push value: 3
Popped value: 3
Push value: 4
Popped value: 4
Push value: 5
Popped value: 5
Push value: 6
Popped value: 6
Push value: 7
Popped value: 7
Push value: 8
Popped value: 8
Push value: 9
Popped value: 9
*/