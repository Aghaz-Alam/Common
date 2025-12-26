A queue is a linear data structure that follows the First-In-First-Out (FIFO) principle, 
meaning that the element inserted first will be the one removed first. 

It is commonly used in scenarios such as scheduling tasks, handling requests, or managing buffer systems.

Using std::queue:

C++ provides the std::queue container adapter, which is built on top of a deque or list and already implements the basic queue operations. If you don’t need to implement a custom queue, you can use std::queue as follows:

#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    // Enqueue elements
    q.push(10);
    q.push(20);
    q.push(30);

    // Display front and rear elements
    std::cout << "Front: " << q.front() << std::endl; // Output: 10
    std::cout << "Rear: " << q.back() << std::endl;   // Output: 30

    // Dequeue an element
    q.pop();

    // Display front element after dequeue
    std::cout << "Front after dequeue: " << q.front() << std::endl; // Output: 20

    return 0;
}




In C++, you can implement a queue using several methods, but here, we will implement it using a dynamic array 
(similar to how you might implement a stack using an array) and also explore the use of std::queue from the C++ Standard Library.

Custom Queue Implementation Using a Dynamic Array
#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;
class Queue {
  private:
    int* data;          // Pointer to dynamic array (queue storage)
    int frontIndex;     // Index of the front element in the queue
    int rearIndex;      // Index of the rear element in the queue
    int capacity;       // Capacity of the queue (size of the underlying array)
    int count;          // Number of elements in the queue

    // Resize the array when the queue is full
    void resize(int newCapacity) {
        int* newData = new int[newCapacity];  // Allocate new array with increased capacity
        for (int i = 0; i < count; ++i) {
            newData[i] = data[(frontIndex + i) % capacity];  // Copy elements to the new array
        }
        delete[] data;  // Free the old array
        data = newData;  // Point to the new array
        frontIndex = 0;  // Reset front index
        rearIndex = count; // Set rear index to count
        capacity = newCapacity;  // Update the capacity
    }

  public:
    // Constructor
    Queue(int initialCapacity = 10) : frontIndex(0), rearIndex(0), count(0), capacity(initialCapacity) {
        data = new int[capacity];  // Allocate memory for the array
    }

    // Destructor to free allocated memory
    ~Queue() {
        delete[] data;
    }

    // Enqueue an element into the queue
    void enqueue(int value) {
        if (count == capacity) {
            resize(capacity * 2);  // Double the capacity if the queue is full
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;  // Circular increment
        count++;
    }

    // Dequeue an element from the queue
    void dequeue() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex = (frontIndex + 1) % capacity;  // Circular increment
        count--;
    }

    // Return the front element without removing it
    int front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return data[frontIndex];
    }

    // Return the rear element without removing it
    int rear() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return data[(rearIndex - 1 + capacity) % capacity];  // Get the last inserted element
    }

    // Check if the queue is empty
    bool empty() const {
        return count == 0;
    }

    // Get the size of the queue
    int size() const {
        return count;
    }

    // Get the capacity of the queue
    int getCapacity() const {
        return capacity;
    }
};

int main() {
    Queue queue;  // Create a queue with default initial capacity (10)

    // Enqueue elements into the queue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    // Display the front and rear elements
    cout << "Front element: " << queue.front() << endl; // Output: 10
    cout << "Rear element: " << queue.rear() << endl;   // Output: 40

    // Dequeue an element
    queue.dequeue();

    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl; // Output: 20

    // Display the queue size and capacity
    cout << "Queue size: " << queue.size() << endl;      // Output: 3
    cout << "Queue capacity: " << queue.getCapacity() << endl; // Output: 10

    // Check if queue is empty
    if (!queue.empty()) {
        cout << "Queue is not empty" << endl; // Output: Queue is not empty
    }

    // Dequeue all elements
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    // Check if the queue is empty
    if (queue.empty()) {
        cout << "Queue is empty" << endl; // Output: Queue is empty
    }

    return 0;
}
/*
Front element: 10
Rear element: 40
Front element after dequeue: 20
Queue size: 3
Queue capacity: 10
Queue is not empty
Queue is empty
*/


Advantages of this Custom Implementation:
Manual Memory Management: You have control over the resizing mechanism, which can be optimized based on the specific needs of your application.
Circular Queue: The queue implements a circular buffer, which optimizes memory usage and ensures no space is wasted.

Disadvantages:
Manual Memory Management: You are responsible for resizing and managing memory, which can lead to bugs or inefficient memory usage if not carefully handled.
No Built-In Operations: Compared to using std::queue, this implementation lacks built-in thread-safety or other optimizations.






Custom Queue Implementation Using std::vector
#include <iostream>
#include <vector>
#include <stdexcept> // For exceptions
using namespace std;
class Queue {
  private:
    std::vector<int> data;  // Vector to hold queue elements
    int frontIndex;         // Index of the front element of the queue
    int rearIndex;          // Index of the rear element of the queue

  public:
    // Constructor to initialize the queue
    Queue() : frontIndex(0), rearIndex(0) {}

    // Enqueue operation: Add an element to the rear of the queue
    void enqueue(int value) {
        data.push_back(value);  // Add value to the end of the vector
        rearIndex++;            // Move rear index forward
    }

    // Dequeue operation: Remove an element from the front of the queue
    void dequeue() {
        if (empty()) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex++;  // Move front index forward
    }

    // Return the front element without removing it
    int front() const {
        if (empty()) {
            throw std::underflow_error("Queue is empty!");
        }
        return data[frontIndex];  // Return the element at the front of the queue
    }

    // Return the rear element without removing it
    int rear() const {
        if (empty()) {
            throw std::underflow_error("Queue is empty!");
        }
        return data[rearIndex - 1];  // Return the last element in the queue
    }

    // Check if the queue is empty
    bool empty() const {
        return frontIndex == rearIndex;
    }

    // Get the size of the queue
    int size() const {
        return rearIndex - frontIndex;
    }
};

int main() {
    Queue queue;  // Create a queue object

    // Enqueue some elements
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    // Display the front and rear elements
    cout << "Front element: " << queue.front() << endl; // Output: 10
    cout << "Rear element: " << queue.rear() << endl;   // Output: 30

    // Dequeue an element
    queue.dequeue();

    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl; // Output: 20

    // Display the queue size
    cout << "Queue size: " << queue.size() << endl;      // Output: 2

    // Check if the queue is empty
    if (!queue.empty()) {
        cout << "Queue is not empty" << endl; // Output: Queue is not empty
    }

    // Dequeue all elements
    queue.dequeue();
    queue.dequeue();

    // Check if the queue is empty
    if (queue.empty()) {
        cout << "Queue is empty" << endl; // Output: Queue is empty
    }

    return 0;
}
/*
Front element: 10
Rear element: 30
Front element after dequeue: 20
Queue size: 2
Queue is not empty
Queue is empty
*/



Circular Queue Implementation:
#include <iostream>
#include <stdexcept>  // For exceptions
using namespace std;
class CircularQueue {
  private:
    int* queue;       // Pointer to the array storing the queue elements
    int front;        // Points to the front of the queue
    int rear;         // Points to the rear of the queue
    int capacity;     // Maximum capacity of the queue
    int size;         // Current size of the queue

  public:
    // Constructor to initialize the queue with a given capacity
    CircularQueue(int cap) : capacity(cap), front(0), rear(0), size(0) {
        queue = new int[capacity];
    }

    // Destructor to release the allocated memory
    ~CircularQueue() {
        delete[] queue;
    }

    // Enqueue: Add an element to the queue
    void enqueue(int value) {
        if (isFull()) {
            throw std::overflow_error("Queue is full!");
        }

        queue[rear] = value;
        rear = (rear + 1) % capacity;  // Circular increment
        size++;
    }

    // Dequeue: Remove an element from the front of the queue
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty!");
        }

        int value = queue[front];
        front = (front + 1) % capacity;  // Circular increment
        size--;
        return value;
    }

    // Front: Get the front element without removing it
    int frontElement() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty!");
        }
        return queue[front];
    }

    // Rear: Get the rear element
    int rearElement() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty!");
        }
        return queue[(rear - 1 + capacity) % capacity]; // Adjust rear index circularly
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Check if the queue is full
    bool isFull() const {
        return size == capacity;
    }

    // Get the current size of the queue
    int getSize() const {
        return size;
    }

    // Get the capacity of the queue
    int getCapacity() const {
        return capacity;
    }
};

int main() {
    CircularQueue cq(5); // Create a circular queue with a capacity of 5

    // Enqueue elements into the queue
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);

    cout << "Front Element: " << cq.frontElement() << endl;  // Output: 10
    cout << "Rear Element: " << cq.rearElement() << endl;    // Output: 50
    cout << "Queue Size: " << cq.getSize() << endl;          // Output: 5

    // Dequeue some elements
    cout << "Dequeued: " << cq.dequeue() << endl;  // Output: 10
    cout << "Dequeued: " << cq.dequeue() << endl;  // Output: 20

    // Enqueue again
    cq.enqueue(60);
    cout << "Front Element: " << cq.frontElement() << endl;  // Output: 30
    cout << "Rear Element: " << cq.rearElement() << endl;    // Output: 60

    // Check the current size of the queue
    cout << "Queue Size: " << cq.getSize() << endl;  // Output: 4

    return 0;
}
/*
Front Element: 10
Rear Element: 50
Queue Size: 5
Dequeued: 10
Dequeued: 20
Front Element: 30
Rear Element: 60
Queue Size: 4
*/


Key Characteristics of a Queue in C++:
A queue is a linear data structure that follows the First-In-First-Out (FIFO) principle. 
The first element that is added to the queue is the first one to be removed, similar to a queue in real-life (like a line at a ticket counter). 
Here's a breakdown of the key characteristics of a queue in C++:

1. FIFO (First-In, First-Out) Order
A queue operates on the FIFO principle, meaning the first element inserted into the queue will be the first one removed.
This ensures that the order of elements is maintained. The element added first will always be dequeued first.



2. Enqueue Operation
The enqueue operation adds an element to the rear (or tail) of the queue.
In C++, this is typically done using the push() function or an equivalent method.
Time Complexity: O(1) (constant time).
Example:
queue.push(10);  // Adds 10 to the rear of the queue


3. Dequeue Operation
The dequeue operation removes an element from the front (or head) of the queue.
In C++, this is typically done using the pop() function.
Time Complexity: O(1) (constant time).
Example:
queue.pop();  // Removes the front element from the queue


4. Front Operation
The front operation retrieves the element at the front of the queue without removing it.
In C++, this is typically done using the front() function.
Time Complexity: O(1) (constant time).
Example:
int frontValue = queue.front();  // Retrieves the front element without removing it


5. Rear Operation
The rear operation retrieves the element at the rear (or tail) of the queue without removing it.
In C++, this is typically done using the back() function (for std::queue).
Time Complexity: O(1) (constant time).
Example:
int rearValue = queue.back();  // Retrieves the rear element without removing it


6. Empty Check
The empty operation checks whether the queue has any elements. It returns true if the queue is empty and false otherwise.
In C++, this is typically done using the empty() function.
Time Complexity: O(1) (constant time).
Example:
if (queue.empty()) {
    std::cout << "Queue is empty" << std::endl;
}


7. Size
The size operation returns the number of elements currently in the queue.
In C++, this is typically done using the size() function.
Time Complexity: O(1) (constant time).
Example:
int queueSize = queue.size();  // Returns the number of elements in the queue


8. Queue Implementation
In C++, queues can be implemented using several data structures, such as:
Array-based Queue: A fixed-size or dynamic array can be used.
Linked List-based Queue: Nodes are linked together to form the queue.
Circular Queue: A circular array or linked list can be used to implement the queue to avoid wasted space when the front and rear pointers 
reach the end of the queue.
Standard Library Queue (std::queue): The standard std::queue in C++ uses a deque (double-ended queue) by default as the underlying container.





9. Thread Safety (Optional)
Thread-safe Queues: Some queue implementations provide mechanisms for thread-safe operations. 
In concurrent programming, a multi-threaded queue ensures that only one thread can modify the queue at any given time.

The C++ Standard Library std::queue is not thread-safe by default. 
However, it can be made thread-safe by using mutexes or other synchronization mechanisms.



Common Operations and Their Time Complexity in a Queue
OperationDescriptionTime Complexityenqueue(x)Adds element x to the rear of the queueO(1)dequeue()Removes the element 
from the front of the queueO(1)front()Returns the front element without removing itO(1)back()Returns the rear element without 
removing itO(1)size()Returns the number of elements in the queueO(1)empty()Checks if the queue is emptyO(1)

Example of Queue in C++ Using std::queue
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;

    // Enqueue elements
    q.push(10);
    q.push(20);
    q.push(30);

    // Display front and rear elements
    std::cout << "Front element: " << q.front() << std::endl; // Output: 10
    std::cout << "Rear element: " << q.back() << std::endl;   // Output: 30

    // Dequeue an element
    q.pop();

    // Display the front element after dequeue
    std::cout << "Front element after dequeue: " << q.front() << std::endl; // Output: 20

    // Display the size of the queue
    std::cout << "Queue size: " << q.size() << std::endl;      // Output: 2

    // Check if the queue is empty
    if (!q.empty()) {
        std::cout << "Queue is not empty" << std::endl; // Output: Queue is not empty
    }

    // Dequeue all elements
    q.pop();
    q.pop();

    // Check if the queue is empty
    if (q.empty()) {
        std::cout << "Queue is empty" << std::endl; // Output: Queue is empty
    }

    return 0;
}
/* 
Output:
Front element: 10
Rear element: 30
Front element after dequeue: 20
Queue size: 2
Queue is not empty
Queue is empty
 */

When to Use a Queue in C++:
Task Scheduling: In operating systems or scheduling algorithms, tasks are processed in the order they arrive.
Buffering: Queues are used in networking and streaming applications to buffer incoming data.
Breadth-First Search (BFS): In graph traversal, BFS uses a queue to explore nodes level by level.
Data Processing Pipelines: Queues can be used to manage tasks or data in a pipeline where each task is processed in sequence.


Advantages of Using a Queue:
Simple and Efficient: The FIFO model is simple and efficient for many real-world applications (e.g., task scheduling).
Fairness: Guarantees that all elements will be processed in the order they arrive, ensuring fairness.


Disadvantages:
No Random Access: You cannot directly access elements in the middle of a queue; you must dequeue elements in order.
Limited to FIFO: Some use cases might require a different processing order (e.g., priority processing), in which case a queue may not be suitable.












//Custom Queue Implementation Using a Dynamic Array
#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;
class Queue {
  private:
    int* arr;   // Pointer to dynamic array (queue storage)
    int frontIndex;  // Index of the front element in the queue
    int rearIndex;   // Index of the rear element in the queue
    int cap;    // Capacity of the queue (size of the underlying array)
    int count;       // Number of elements in the queue

  public:
    // Constructor
    Queue(): arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(0){}

    // Destructor to free allocated memory
    ~Queue() {
        delete[] arr;
    }
    
    
    // Enqueue an element into the queue
    void enqueue(int value) {
        if (count == cap) {
            cap = (cap==0)? 1 : cap*2;
            int* newArr = new int[cap];  // Allocate new array with increased capacity
            for (int i = 0; i < count; ++i) {
                newArr[i] = arr[(frontIndex + i) % cap];  // Copy elements to the new array
            }
            delete[] arr;  // Free the old array
            arr = newArr;  // Point to the new array
            frontIndex = 0;  // Reset front index
            rearIndex = count; // Set rear index to count
            //capacity = newCapacity;  // Update the capacity
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;  // Circular increment
        count++;
    }

    // Dequeue an element from the queue
    void dequeue() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex = (frontIndex + 1) % cap;  // Circular increment
        count--;
    }

    // Return the front element without removing it
    int front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[frontIndex];
    }

    // Return the rear element without removing it
    int rear() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[(rearIndex - 1 + cap) % cap];  // Get the last inserted element
    }

    // Check if the queue is empty
    bool empty() const {
        return count == 0;
    }

    // Get the size of the queue
    int size() const {
        return count;
    }

    // Get the capacity of the queue
    int capacity() const {
        return cap;
    }
};

int main() {
    Queue queue;  // Create a queue with default initial capacity (10)

    // Enqueue elements into the queue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    // Display the front and rear elements
    cout << "Front element: " << queue.front() << endl; // Output: 10
    cout << "Rear element: " << queue.rear() << endl;   // Output: 40

    // Dequeue an element
    queue.dequeue();

    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl; // Output: 20

    // Display the queue size and capacity
    cout << "Queue size: " << queue.size() << endl;      // Output: 3
    cout << "Queue capacity: " << queue.capacity() << endl; // Output: 10

    // Check if queue is empty
    if (!queue.empty()) {
        cout << "Queue is not empty" << endl; // Output: Queue is not empty
    }

    // Dequeue all elements
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    // Check if the queue is empty
    if (queue.empty()) {
        cout << "Queue is empty" << endl; // Output: Queue is empty
    }

    return 0;
}
/*
Front element: 10
Rear element: 50
Front element after dequeue: 20
Queue size: 4
Queue capacity: 8
Queue is not empty
Queue is empty
*/











//Custom Queue Implementation Using a Dynamic Array
#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;
class Queue {
  private:
    int* arr;   // Pointer to dynamic array (queue storage)
    int frontIndex;  // Index of the front element in the queue
    int rearIndex;   // Index of the rear element in the queue
    int cap;    // Capacity of the queue (size of the underlying array)
    int count;       // Number of elements in the queue

  public:
    // Constructor
    Queue(): arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(0){}

    // Destructor to free allocated memory
    ~Queue() {
        delete[] arr;
    }
    
    
    // Enqueue an element into the queue
    void enqueue(int value) {
        if (count == cap) {
            cap = (cap==0)? 1 : cap*2;
            int* newArr = new int[cap];  // Allocate new array with increased capacity
            for (int i = 0; i < count; ++i) {
                newArr[i] = arr[(frontIndex + i) % cap];  // Copy elements to the new array
            }
            delete[] arr;  // Free the old array
            arr = newArr;  // Point to the new array
            frontIndex = 0;  // Reset front index
            rearIndex = count; // Set rear index to count
            //capacity = newCapacity;  // Update the capacity
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;  // Circular increment
        count++;
    }

    // Dequeue an element from the queue
    void dequeue() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex = (frontIndex + 1) % cap;  // Circular increment
        count--;
    }

    // Return the front element without removing it
    int front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[frontIndex];
    }

    // Return the rear element without removing it
    int rear() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[(rearIndex - 1 + cap) % cap];  // Get the last inserted element
    }

    // Check if the queue is empty
    bool empty() const {
        return count == 0;
    }

    // Get the size of the queue
    int size() const {
        return count;
    }

    // Get the capacity of the queue
    int capacity() const {
        return cap;
    }
};

int main() {
    Queue queue;  // Create a queue with default initial capacity (10)

    // Enqueue elements into the queue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    // Display the front and rear elements
    cout << "Front element: " << queue.front() << endl; // Output: 10
    cout << "Rear element: " << queue.rear() << endl;   // Output: 40

    // Dequeue an element
    queue.dequeue();

    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl; // Output: 20

    // Display the queue size and capacity
    cout << "Queue size: " << queue.size() << endl;      // Output: 3
    cout << "Queue capacity: " << queue.capacity() << endl; // Output: 10

    // Check if queue is empty
    if (!queue.empty()) {
        cout << "Queue is not empty" << endl; // Output: Queue is not empty
    }

    // Dequeue all elements
    queue.dequeue();
    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl;
    queue.dequeue();
    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl;
    queue.dequeue();
    // Display the front element after dequeuing
    cout << "Front element after dequeue: " << queue.front() << endl;
    queue.dequeue();
    
    // Check if the queue is empty
    if (queue.empty()) {
        cout << "Queue is empty" << endl; // Output: Queue is empty
    }

    return 0;
}
/*
Front element: 10
Rear element: 50
Front element after dequeue: 20
Queue size: 4
Queue capacity: 8
Queue is not empty
Front element after dequeue: 30
Front element after dequeue: 40
Front element after dequeue: 50
Queue is empty
*/
