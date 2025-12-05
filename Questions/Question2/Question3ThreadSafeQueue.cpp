/* 
ThreadSafeQueue:

Question 3 : Design a thread-safe queue data structure in C++ that supports concurrent push, pop, and size operations. Ensure that the implementation does not lead to race conditions or deadlocks.

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

// ==============================
// ThreadSafeQueue class
// ==============================
template <typename T>
class ThreadSafeQueue {
private:
    queue<T> q;
    mutable mutex mtx;
    condition_variable cv;

public:
    // Push element into queue
    void push(const T& value) {
        {
            lock_guard<mutex> lock(mtx);
            q.push(value);
            cout << "Push value: " << value << endl;
        }
        cv.notify_one();
    }

    // Pop element from queue
    T pop() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this](){ return !q.empty(); });
        T value = q.front();
        q.pop();
        cout << "Popped value: " << value << endl;
        return value;
    }

    // Get current size
    size_t size() const {
        lock_guard<mutex> lock(mtx);
        return q.size();
    }
};

// ==============================
// MAIN
// ==============================
int main() {
    ThreadSafeQueue<int> tsq;

    // Producer thread
    auto producer = [&tsq]() {
        for (int i = 0; i < 10; ++i) {
            tsq.push(i);
        }
    };

    // Consumer thread
    auto consumer = [&tsq]() {
        for (int i = 0; i < 10; ++i) {
            tsq.pop();
        }
    };

    // Start threads
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

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