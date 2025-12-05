/* 
Question 9 : Queue Implementation

Write a C++ class that implements a queue data structure. Include methods for enqueuing an element into the queue, dequeuing an element from the queue, and checking if the queue is empty.

Sample Input :  myQueue.enqueue(1);
    		myQueue.enqueue(2);
    		myQueue.enqueue(3);

Expected result : Front element: 1
		          Front element after dequeue: 2 
*/


#include <iostream>
using namespace std;
class Queue {
  private:
    // Node structure
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };
    Node* front; // points to front element
    Node* rear;  // points to last element

  public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr) {}
    // Check if queue is empty
    bool isEmpty() const {
        return front == nullptr;
    }
    // Enqueue operation
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    // Dequeue operation
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot dequeue." << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr; // queue becomes empty
        }
    }
    // Get front element
    int getFront() const {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return front->data;
    }
    // Destructor to free memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};
int main() {
    Queue myQueue;

    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.enqueue(3);
    cout << "Front element: " << myQueue.getFront() << endl;
    myQueue.dequeue();
    cout << "Front element after dequeue: " << myQueue.getFront() << endl;
   return 0;
}
/*
Front element: 1
Front element after dequeue: 2
*/