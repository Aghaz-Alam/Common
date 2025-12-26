/* 
Question 9 : Queue Implementation

Write a C++ class that implements a queue data structure. Include methods for enqueuing an element into the queue, dequeuing an element from the queue, and checking if the queue is empty.

Sample Input :  myQueue.enqueue(1);
    		myQueue.enqueue(2);
    		myQueue.enqueue(3);

Expected result : Front element: 1
		  Front element after dequeue: 2
*/

//C++ Queue Class Implementation
#include <iostream>
#include <stdexcept>
using namespace std;

class Queue {
  private:
    int arr[100];   // fixed-size queue for simplicity
    int frontIndex;
    int rearIndex;
    int count;

  public:
    Queue() : frontIndex(0), rearIndex(0), count(0) {}

    // Check if queue is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Enqueue operation
    void enqueue(int value) {
        if (count == 100) {
            throw runtime_error("Queue is full");
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % 100;
        count++;
    }

    // Dequeue operation
    int dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        int value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % 100;
        count--;
        return value;
    }

    // Get front element
    int front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return arr[frontIndex];
    }
};

// -------------------------------
// Main Demonstration
// -------------------------------
int main() {
    Queue myQueue;

    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.enqueue(3);

    cout << "Front element: " << myQueue.front() << endl;

    myQueue.dequeue();

    cout << "Front element after dequeue: " << myQueue.front() << endl;

    return 0;
}
/* 
Expected Output
Front element: 1
Front element after dequeue: 2
*/