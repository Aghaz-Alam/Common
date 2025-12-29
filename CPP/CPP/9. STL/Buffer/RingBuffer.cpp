A ring buffer (or circular buffer) is a fixed-size data structure that uses a single, 
contiguous memory block as if the ends were connected, forming a loop. 

It is implemented in C++ using a standard container (like std::vector or a raw array) and indices or pointers 
to track the read and write positions. 

This avoids costly data shifting when elements are consumed or produced, making operations highly efficient (O(1) time complexity). 



Key Components of an Implementation
A typical C++ implementation uses a class template for type safety and reusability, with the following members:
(a) buffer: The underlying fixed-size storage (e.g., std::vector<T> data or std::unique_ptr<T[]> data).
(b) head (write index): Index where the next item will be written/produced.
(c) tail (read index): Index where the next item will be read/consumed.
(d) capacity / maxSize: The maximum number of elements the buffer can hold.

State Management: A way to distinguish between a full and an empty buffer 
(as both conditions can result in head == tail). Common methods include:
->Using an additional count variable.
->Wasting one slot in the buffer (a common and simple approach in embedded systems).
->Using a separate boolean flag. 

Core Operations
The operations rely heavily on the modulo operator (%) to handle the "wrap-around" behavior, 
ensuring indices stay within the buffer's bounds. The formula is index = (index + 1) % capacity. 

enqueue() (Pushing Data)
->Check if the buffer is full.
->If full, decide whether to throw an exception or overwrite the oldest data (advanced the tail pointer).
->Store the new item at the current head position.
->Advance the head index using modulo arithmetic.
->Update the element count or state flag. 


dequeue() (Reading Data)
->Check if the buffer is empty. If so, throw an exception or return an error/empty value 
(e.g., std::optional<T> in C++17).
->Retrieve the item at the current tail position.
->Advance the tail index using modulo arithmetic.
->Update the element count or state flag.
->Return the retrieved item. 

Example Implementation (using count variable)
A basic C++ implementation using a std::vector and a count variable can be structured as a class template. The class would contain members for the underlying buffer (buffer), read and write indices (tail and head), the buffer's maximum capacity (capacity), and the current number of elements (count).
The constructor initializes the buffer with the specified capacity. 
The enqueue function adds an element. If the buffer is full, it might overwrite the oldest element by advancing the tail. It then places the new item at the head and advances the head using modulo arithmetic. The count is updated. 
The dequeue function removes and returns the oldest element. It checks if the buffer is empty, throwing an exception if it is. Otherwise, it retrieves the element at the tail, advances the tail using modulo arithmetic, decrements the count, and returns the element. 
Helper functions isEmpty, isFull, and size can be included to check the buffer's state and current size. For a full code example, refer to the provided source document. 





#include <iostream>
#include <vector>
#include <stdexcept>
class CircularBuffer {
  private:
    std::vector<int> buffer; // The buffer array
    int head;                // Points to the head of the buffer (where data is read)
    int tail;                // Points to the tail of the buffer (where data is written)
    int count;               // Number of elements in the buffer
    int capacity;            // Maximum size of the buffer
 public:
   CircularBuffer(int size) : buffer(size), head(0), tail(0), count(0), capacity(size) {}

    // Push an element into the buffer
    void push(const int& value) {
        if (isFull()) {
            throw std::overflow_error("Buffer is full");
        }

        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        count++;
    }

    // Pop an element from the buffer
    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("Buffer is empty");
        }

        int value = buffer[head];
        head = (head + 1) % capacity;
        count--;
        return value;
    }

    // Check if the buffer is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Check if the buffer is full
    bool isFull() const {
        return count == capacity;
    }

    // Get the current size of the buffer
    int size() const {
        return count;
    }

    // Get the capacity of the buffer
    int getCapacity() const {
        return capacity;
    }
};

int main() {
    CircularBuffer buffer(3); // Create a buffer with capacity of 3

    // Push elements into the buffer
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);

    std::cout << "Buffer size: " << buffer.size() << std::endl; // Output: 3

    // Pop an element from the buffer
    std::cout << "Popped: " << buffer.pop() << std::endl; // Output: 1

    // Push another element (this will overwrite the oldest element)
    buffer.push(4);

    std::cout << "Buffer size: " << buffer.size() << std::endl; // Output: 3

    // Pop all elements from the buffer
    while (!buffer.isEmpty()) {
        std::cout << "Popped: " << buffer.pop() << std::endl; // Output: 2, 3, 4
    }

    return 0;
}




Circular Buffer Implementation in C++
Here's a simple implementation of a circular buffer using an array:

#include <iostream>
#include <vector>
#include <stdexcept>
template <typename T>
class CircularBuffer {
  public:
    CircularBuffer(size_t size) : buffer(size), head(0), tail(0), count(0), capacity(size) {}

    // Push an element into the buffer
    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Buffer is full");
        }

        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        count++;
    }

    // Pop an element from the buffer
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Buffer is empty");
        }

        T value = buffer[head];
        head = (head + 1) % capacity;
        count--;
        return value;
    }

    // Check if the buffer is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Check if the buffer is full
    bool isFull() const {
        return count == capacity;
    }

    // Get the current size of the buffer
    size_t size() const {
        return count;
    }

    // Get the capacity of the buffer
    size_t getCapacity() const {
        return capacity;
    }

private:
    std::vector<T> buffer; // The buffer array
    size_t head;           // Points to the head of the buffer (where data is read)
    size_t tail;           // Points to the tail of the buffer (where data is written)
    size_t count;          // Number of elements in the buffer
    size_t capacity;       // Maximum size of the buffer
};

int main() {
    CircularBuffer<int> buffer(3); // Create a buffer with capacity of 3

    // Push elements into the buffer
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);

    std::cout << "Buffer size: " << buffer.size() << std::endl; // Output: 3

    // Pop an element from the buffer
    std::cout << "Popped: " << buffer.pop() << std::endl; // Output: 1

    // Push another element (this will overwrite the oldest element)
    buffer.push(4);

    std::cout << "Buffer size: " << buffer.size() << std::endl; // Output: 3

    // Pop all elements from the buffer
    while (!buffer.isEmpty()) {
        std::cout << "Popped: " << buffer.pop() << std::endl; // Output: 2, 3, 4
    }

    return 0;
}







//Circular Buffer/Ring Buffer/Circular Queue using Dynamic Array
#include <iostream>
#include <stdexcept>
using namespace std;

class Queue {
private:
    int* arr;       // dynamic array for queue
    size_t frontIndex;    // front index
    size_t rearIndex;    // rear index
    size_t cap;     // capacity
    size_t count;   // number of elements

public:
    // Constructor
    Queue(size_t capacity)
        : arr(new int[capacity]), frontIndex(0), rearIndex(0), cap(capacity), count(0) {}

    // Destructor
    ~Queue() {
        delete[] arr;
    }

    // Push an element
    void push(int value) {
        if (count == cap) {
            // Overwrite oldest element
            frontIndex = (frontIndex + 1) % cap;
        } else {
            count++;
        }

        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;
    }

    // Pop an element
    void pop() {
        if (count == 0) {
            throw underflow_error("Queue is empty!");
        }

        frontIndex = (frontIndex + 1) % cap;
        count--;
    }

    // Front element
    int front() const {
        if (count == 0) {
            throw underflow_error("Queue is empty!");
        }
        return arr[frontIndex];
    }

    // Back element
    int back() const {
        if (count == 0) {
            throw underflow_error("Queue is empty!");
        }
        return arr[(rearIndex - 1 + cap) % cap];
    }

    // Is empty?
    bool empty() const {
        return count == 0;
    }

    // Size of queue
    size_t size() const {
        return count;
    }

    // Capacity
    size_t capacity() const {
        return cap;
    }

    // Display elements
    void Display() const {
        if (count == 0) {
            cout << "Queue is empty!" << endl;
            return;
        }

        for (size_t i = 0; i < count; i++) {
            cout << arr[(frontIndex + i) % cap] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    cout<<"Elements: ";
    q.Display();
    
    cout << "Front: " << q.front() << endl; // 10
    cout << "Back: " << q.back() << endl;   // 50
    
    cout << "Size: " << q.size() << endl;
    cout << "Capacity: " << q.capacity() << endl;
   

    q.pop();
    cout<<"Elements after pop: ";
    q.Display();
    
    cout << "Front after pop: " << q.front() << endl; // 20
    cout << "Back after pop: " << q.back() << endl;   // 50
    
    cout << "Size after pop: " << q.size() << endl;
    cout << "Capacity after pop: " << q.capacity() << endl;

    while (!q.empty()) {
        cout << "Popped: " << q.front() << endl;
        q.pop();
    }

    cout << "Queue empty? " << (q.empty() ? "Yes" : "No") << endl;

    return 0;
}
/*
Elements: 10 20 30 40 50 
Front: 10
Back: 50
Size: 5
Capacity: 5
Elements after pop: 20 30 40 50 
Front after pop: 20
Back after pop: 50
Size after pop: 4
Capacity after pop: 5
Popped: 20
Popped: 30
Popped: 40
Popped: 50
Queue empty? Yes
*/






//Circular Buffer/Ring Buffer/Circular Queue using Dynamic Array
#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
class Queue {
 private:
    T* arr;       // dynamic array for queue
    size_t frontIndex;    // front index
    size_t rearIndex;    // rear index
    size_t cap;     // capacity
    size_t count;   // number of elements

 public:
    // Constructor
    Queue(size_t capacity)
        : arr(new T[capacity]), frontIndex(0), rearIndex(0), cap(capacity), count(0) {}

    // Destructor
    ~Queue() {
        delete[] arr;
    }

    // Push an element
    void push(const T& value) {
        if (count == cap) {
            // Overwrite oldest element
            frontIndex = (frontIndex + 1) % cap;
        } else {
            count++;
        }

        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;
    }

    // Pop an element
    void pop() {
        if (count == 0) {
            throw underflow_error("Queue is empty!");
        }

        frontIndex = (frontIndex + 1) % cap;
        count--;
    }

    // Front element
    T front() const {
        if (count == 0) {
            throw underflow_error("Queue is empty!");
        }
        return arr[frontIndex];
    }

    // Back element
    T back() const {
        if (count == 0) {
            throw underflow_error("Queue is empty!");
        }
        return arr[(rearIndex - 1 + cap) % cap];
    }

    // Is empty?
    bool empty() const {
        return count == 0;
    }

    // Size of queue
    size_t size() const {
        return count;
    }

    // Capacity
    size_t capacity() const {
        return cap;
    }

    // Display elements
    void Display() const {
        if (count == 0) {
            cout << "Queue is empty!" << endl;
            return;
        }

        for (size_t i = 0; i < count; i++) {
            cout << arr[(frontIndex + i) % cap] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue<int> q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    cout<<"Elements: ";
    q.Display();
    
    cout << "Front: " << q.front() << endl; // 10
    cout << "Back: " << q.back() << endl;   // 50
    
    cout << "Size: " << q.size() << endl;
    cout << "Capacity: " << q.capacity() << endl;
   

    q.pop();
    cout<<"Elements after pop: ";
    q.Display();
    
    cout << "Front after pop: " << q.front() << endl; // 20
    cout << "Back after pop: " << q.back() << endl;   // 50
    
    cout << "Size after pop: " << q.size() << endl;
    cout << "Capacity after pop: " << q.capacity() << endl;

    while (!q.empty()) {
        cout << "Popped: " << q.front() << endl;
        q.pop();
    }

    cout << "Queue empty? " << (q.empty() ? "Yes" : "No") << endl;

    return 0;
}
/*
Elements: 10 20 30 40 50 
Front: 10
Back: 50
Size: 5
Capacity: 5
Elements after pop: 20 30 40 50 
Front after pop: 20
Back after pop: 50
Size after pop: 4
Capacity after pop: 5
Popped: 20
Popped: 30
Popped: 40
Popped: 50
Queue empty? Yes
*/








//Circular Buffer/Ring Buffer/Circular Queue using Dynamic Array
#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;

template <typename T>
class Queue {
private:
    T* arr;        // Pointer to dynamic array (queue storage)
    size_t head;   // Index of the front element in the queue
    size_t tail;   // Index of the rear element in the queue
    size_t cap;    // Capacity of the queue (size of the underlying array)
    size_t count;  // Number of elements in the queue

 public:
    // Constructor
    Queue(size_t capacity) : arr(new T[capacity]), head(0), tail(0), count(0), cap(capacity) {}

    // Destructor to free allocated memory
    ~Queue() {
        delete[] arr;
    }

// Push an element into the queue (circular buffer behavior)
    void push(T value) {
        if (count == cap) {
            // Overwrite the front element if the queue is full (cyclic behavior)
            head = (head + 1) % cap; // Move head to the next position
        } else {
            count++; // Increment count only when queue is not full
        }
        arr[tail] = value;  // Insert the new value at the tail
        tail = (tail + 1) % cap;  // Circular increment of tail
    }

    // Pop an element from the queue
    void pop() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        head = (head + 1) % cap;  // Circular increment of head
        count--;
    }

    // Return the front element without removing it
    T front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[head];
    }

    // Return the rear element without removing it
    T back() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[(tail - 1 + cap) % cap];  // Get the last inserted element
    }

    // Check if the queue is empty
    bool empty() const {
        return count == 0;
    }

    // Get the size of the queue
    size_t size() const {
        return count;
    }

    // Get the capacity of the queue
    size_t capacity() const {
        return cap;
    }

    // Display all elements in the queue
    void Display() const {
        if (count == 0) {
            cout << "Queue is empty!" << endl;
            return;
        }
        // Loop through the queue elements starting from head and considering the circular nature
        for (size_t i = 0; i < count; ++i) {
            cout << arr[(head + i) % cap] << " ";  // Circular indexing
        }
        cout << endl;
    }
};

int main() {
    // Create a cyclic queue with a fixed capacity (for example, 5 elements)
    Queue<int> qInt(5);

    // Enqueue elements into the queue
    qInt.push(10);
    qInt.push(20);
    qInt.push(30);
    qInt.push(40);
    qInt.push(50);

    // Display the front and rear elements
    cout << "Integer Queue - Front element: " << qInt.front() << endl; // Output: 10
    cout << "Integer Queue - Rear element: " << qInt.back() << endl;   // Output: 50
    
    cout << "Integer Queue Elements: ";
    qInt.Display();
    
    // Pop an element
    qInt.pop();

    // Display the front element after pop
    cout << "Integer Queue - Front element after pop: " << qInt.front() << endl; // Output: 20

    // Display the queue size and capacity
    cout << "Integer Queue size: " << qInt.size() << endl;      // Output: 4
    cout << "Integer Queue capacity: " << qInt.capacity() << endl; // Output: 5

    // Check if the queue is empty
    if (!qInt.empty()) {
        cout << "Integer Queue is not empty" << endl; // Output: Integer Queue is not empty
    }

    // Pop all elements
    qInt.pop();
    cout << "Integer Queue - Front element after pop: " << qInt.front() << endl;

    qInt.pop();
    cout << "Integer Queue - Front element after pop: " << qInt.front() << endl;
    
    qInt.pop();
    cout << "Integer Queue - Front element after pop: " << qInt.front() << endl;
    
    qInt.pop();
    
    // Check if the queue is empty
    if (qInt.empty()) {
        cout << "Integer Queue is empty" << endl; // Output: Integer Queue is empty
    }

    // Create a queue of strings
    Queue<string> qStr(3);

    // Enqueue string elements into the queue
    qStr.push("apple");
    qStr.push("banana");
    qStr.push("cherry");

    cout << "String Queue - Front element: " << qStr.front() << endl;  // Output: apple
    cout << "String Queue - Rear element: " << qStr.back() << endl;    // Output: cherry
    
    cout << "String Queue Elements: ";
    qStr.Display();

    // Pop an element from the string queue
    qStr.pop();
    cout << "String Queue - Front element after pop: " << qStr.front() << endl; // Output: banana

    return 0;
}
/*
Integer Queue - Front element: 10
Integer Queue - Rear element: 50
Integer Queue Elements: 10 20 30 40 50 
Integer Queue - Front element after pop: 20
Integer Queue size: 4
Integer Queue capacity: 5
Integer Queue is not empty
Integer Queue - Front element after pop: 30
Integer Queue - Front element after pop: 40
Integer Queue - Front element after pop: 50
Integer Queue is empty
String Queue - Front element: apple
String Queue - Rear element: cherry
String Queue Elements: apple banana cherry 
String Queue - Front element after pop: banana
*/






















//Circular Buffer/Ring Buffer/Circular Queue using Dynamic Array
#include <iostream>
#include <stdexcept>
using namespace std;

class Queue {
private:
    int* arr;            // dynamic array for queue
    size_t frontIndex;   // index of the front element
    size_t rearIndex;    // index of the rear element (next insertion spot)
    size_t cap;          // capacity
    size_t count;        // number of elements

public:
    // Constructor
    Queue(size_t capacity): arr(new int[capacity]), frontIndex(0), rearIndex(0), cap(capacity), count(0) {}

    // Destructor
    ~Queue() {
        delete[] arr;
    }

    // Push an element
    void push(int value) {
        if (count == cap) {
            // Overwrite oldest element
            frontIndex = (frontIndex + 1) % cap;
        } else {
            count++;
        }

        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;
    }

    // Pop an element
    void pop() {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        frontIndex = (frontIndex + 1) % cap;
        count--;
    }

    // Front element
    int front() const {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        return arr[frontIndex];
    }

    // Back element
    int back() const {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        return arr[(rearIndex - 1 + cap) % cap];
    }

    // Check if empty
    bool empty() const {
        return count == 0;
    }

    // Size
    size_t size() const {
        return count;
    }

    // Capacity
    size_t capacity() const {
        return cap;
    }

    // Display elements
    void Display() const {
        if (count == 0) {
            cout << "Queue is empty!" << endl;
            return;
        }

        for (size_t i = 0; i < count; i++)
            cout << arr[(frontIndex + i) % cap] << " ";

        cout << endl;
    }
};

int main() {
    Queue q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;

    q.Display();

    q.pop();
    cout << "Front after pop: " << q.front() << endl;

    cout << "Size: " << q.size() << endl;
    cout << "Capacity: " << q.capacity() << endl;

    while (!q.empty()) {
        cout << "Popped: " << q.front() << endl;
        q.pop();
    }

    cout << "Queue empty? " << (q.empty() ? "Yes" : "No") << endl;

    return 0;
}
/*
Front: 10
Back: 50
10 20 30 40 50 
Front after pop: 20
Size: 4
Capacity: 5
Popped: 20
Popped: 30
Popped: 40
Popped: 50
Queue empty? Yes
*/




//with template
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    T* arr;               // dynamic array for queue
    size_t frontIndex;    // index of the front element
    size_t rearIndex;     // index of the rear element (next insertion spot)
    size_t cap;           // capacity
    size_t count;         // number of elements

public:
    // Constructor
    Queue(size_t capacity): arr(new T[capacity]), frontIndex(0), rearIndex(0), cap(capacity), count(0) {}

    // Destructor
    ~Queue() {
        delete[] arr;
    }

    // Push an element (circular)
    void push(T value) {
        if (count == cap) {
            // Overwrite oldest element
            frontIndex = (frontIndex + 1) % cap;
        } else {
            count++;
        }

        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;
    }

    // Pop an element
    void pop() {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        frontIndex = (frontIndex + 1) % cap;
        count--;
    }

    // Front element
    T front() const {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        return arr[frontIndex];
    }

    // Back element
    T back() const {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        return arr[(rearIndex - 1 + cap) % cap];
    }

    // Check if empty
    bool empty() const {
        return count == 0;
    }

    // Size
    size_t size() const {
        return count;
    }

    // Capacity
    size_t capacity() const {
        return cap;
    }

    // Display elements
    void Display() const {
        if (count == 0) {
            cout << "Queue is empty!" << endl;
            return;
        }

        for (size_t i = 0; i < count; i++)
            cout << arr[(frontIndex + i) % cap] << " ";

        cout << endl;
    }
};

int main() {
    // Integer queue
    Queue<int> q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;

    q.Display();

    q.pop();
    cout << "Front after pop: " << q.front() << endl;

    cout << "Size: " << q.size() << endl;
    cout << "Capacity: " << q.capacity() << endl;

    while (!q.empty()) {
        cout << "Popped: " << q.front() << endl;
        q.pop();
    }

    cout << "Queue empty? " << (q.empty() ? "Yes" : "No") << endl;


    // String queue example
    Queue<string> qs(3);
    qs.push("apple");
    qs.push("banana");
    qs.push("cherry");

    cout << "\nString queue front: " << qs.front() << endl;
    cout << "String queue back: " << qs.back() << endl;

    qs.Display();

    return 0;
}
/*
Front: 10
Back: 50
10 20 30 40 50 
Front after pop: 20
Size: 4
Capacity: 5
Popped: 20
Popped: 30
Popped: 40
Popped: 50
Queue empty? Yes

String queue front: apple
String queue back: cherry
apple banana cherry 
*/












#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;

class Queue {
  private:
    int* arr;           // Pointer to dynamic array (queue storage)
    int frontIndex;     // Index of the front element in the queue
    int rearIndex;      // Index of the rear element in the queue
    int cap;            // Capacity of the queue (size of the underlying array)
    int count;          // Number of elements in the queue

  public:
    // Constructor
    Queue(int capacity) : arr(new int[capacity]), frontIndex(0), rearIndex(0), count(0), cap(capacity) {}

    // Destructor to free allocated memory
    ~Queue() {
        delete[] arr;
    }

    // Inserts elements at the rear (or back) of the queue.
    void push(const int& value) {
        if (count == cap) {
            throw std::overflow_error("Queue is full! Cannot enqueue.");
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;  // Circular increment  moves the rearIndex forward when you push an element. Move rear forward after push, Wraps around end of array
        count++;
    }

    // Removes elements from the front of the queue.
    void pop() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex = (frontIndex + 1) % cap;  // Circular increment moves the frontIndex forward when you pop an element. Move front forward after pop, Avoids going out of bounds
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
    int back() const {
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

    // Display elements in the queue
    void Display() {
        if (count == 0) {
            cout << "Queue is empty." << endl;
            return;
        }
        // Loop through the queue elements starting from frontIndex and considering the circular nature
        for (int i = 0; i < count; ++i) {
            cout << arr[(frontIndex + i) % cap] << " ";  // Circular indexing
        }
    }
};

int main() {
    Queue cq(5);  

    // Push elements into the queue
    cq.push(10);
    cq.push(20);
    cq.push(30);
    cq.push(40);
    cq.push(50);
    cout << "Queue Elements are: ";
    cq.Display();
    cout << endl;

    // // Attempt to push an element when the queue is full
    try {
        cq.push(60);  // This will throw an overflow_error
    } catch (const std::overflow_error& e) {
        cout << "Error: " << e.what() << endl;  // Handle the error
    }

    // Display the front and rear elements
    cout << "Front element: " << cq.front() << endl; // Output: 10
    cout << "Rear element: " << cq.back() << endl;   // Output: 50

    // Pop all elements
    cq.pop();
    
    cout << "Queue Elements after pop: ";
    cq.Display();
    cout << endl;

    // Display the front and rear elements after pop
    cout << "Front element after pop: " << cq.front() << endl; // Output: 20
    cout << "Rear element after pop: " << cq.back() << endl;   // Output: 50
  
    cq.pop();
    cq.pop();
    cq.pop();
    cq.pop();
    
    // Check if the queue is empty
    if (cq.empty()) {
        cout << "Queue is empty" << endl; // Output: Queue is empty
    }

    return 0;
}
/*
Queue Elements are: 10 20 30 40 50 
Error: Queue is full! Cannot enqueue.
Front element: 10
Rear element: 50
Queue Elements after pop: 20 30 40 50 
Front element after pop: 20
Rear element after pop: 50
Queue is empty
*/


































#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;
class CirQueue {
  private:
    int* arr;   // Pointer to dynamic array (queue storage)
    int frontIndex;  // Index of the front element in the queue
    int rearIndex;   // Index of the rear element in the queue
    int cap;    // Capacity of the queue (size of the underlying array)
    int count;       // Number of elements in the queue

    // Private function to resize the underlying array when capacity is full
    void resize() {
        cap = (cap == 0) ? 1 : cap * 2;  // Double the capacity
        int* newArr = nullptr;
        try {
            newArr = new int[cap];  // Allocate new array with increased capacity
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            throw;  // Rethrow the exception
        }
        // Copy elements to the new array
        for (int i = 0; i < count; ++i) {
            newArr[i] = arr[(frontIndex + i) % cap];
        }
        delete[] arr;  // Free the old array
        arr = newArr;  // Point to the new array
        frontIndex = 0;  // Reset front index
        rearIndex = count; // Set rear index to count
    }

public:
    // Constructor
    CirQueue(): arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap() {}

    // Destructor to free allocated memory
    ~CirQueue() {
        delete[] arr;
    }

    // Enqueue an element into the queue
    void push(int value) {
        if (count == cap) {
            resize();  // Call the resize function if capacity is full
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;  // Circular increment
        count++;
    }

    // Dequeue an element from the queue
    void pop() {
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
    int back() const {
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

    // Display the queue elements
    void Display() {
        for (int i = 0; i < count; ++i) {
            cout << arr[(frontIndex + i) % cap] << " ";  // Circular indexing
        }
    }
};

int main() {
    CirQueue cq;  

    // Enqueue elements into the queue
    cq.push(10);
    cq.push(20);
    cq.push(30);
    cq.push(40);
    cq.push(50);
    
    cout << "Circular Queue Elements are: ";
    cq.Display();
    cout << endl;

    // Display the front and rear elements
    cout << "Front element: " << cq.front() << endl;
    cout << "Rear element: " << cq.back() << endl;

    // Dequeue elements
    cq.pop();
    cout << "Circular Queue Elements after pop: ";
    cq.Display();
    cout << endl;
    cout << "Front element after pop: " << cq.front() << endl;
    cout << "Rear element after pop: " << cq.back() << endl;

    cq.pop();
    cq.pop();
    cq.pop();
    cq.pop();
    
    // Check if the queue is empty
    if (cq.empty()) {
        cout << "Circular Queue is empty" << endl;
    }

    return 0;
}
/*
Circular Queue Elements are: 10 20 30 40 50 
Front element: 10
Rear element: 50
Circular Queue Elements after pop: 20 30 40 50 
Front element after pop: 20
Rear element after pop: 50
Circular Queue is empty
*/






#include <iostream>
#include<stdexcept>
using namespace std;

template<class T>
class MyCircularQueue{
  int* arr;
  int frontIndex;
  int rearIndex;
  int count;
  int cap;
 public:
  MyCircularQueue():arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(){}
  
  ~MyCircularQueue(){ delete[] arr; }
  
  void resize();
  void push(const int& val);
  void pop();
  int front() const;
  int back() const;
  bool empty() const ;
  int size() const;
  int capacity() const;
  void display() const;
  
};  
  template<class T>
  void MyCircularQueue<T>::resize(){
      cap = (cap == 0) ? 1: cap*2;
      T* newArr = new T[cap];
      for(int i=0; i<count; i++){
          newArr[i] = arr[(frontIndex+i)%cap];
      }
      delete[] arr;
      arr = newArr;
      frontIndex =0;
      rearIndex = count;
  }
  
  //insert at back
  template<class T>
  void MyCircularQueue<T>::push(const int& val){
     if(count == cap) {
         resize();
     }
     
     arr[rearIndex] = val;
     rearIndex = (rearIndex +1) % cap;
     count ++;
     
  }
  
  //remove from front
  template<class T>
  void MyCircularQueue<T>::pop(){
      if(count == 0) throw underflow_error("CQ is empty.");
      
      frontIndex = (frontIndex + 1) % cap;
      count --;
  }
  
  //get front element
  template<class T>
  int MyCircularQueue<T>::front() const{
      if(count == 0) throw underflow_error("CQ is empty.");
      return arr[frontIndex];
  }
  
  //get rear element
  template<class T>
  int MyCircularQueue<T>::back() const{
       if(count == 0) throw underflow_error("CQ is empty.");
      return arr[(rearIndex -1 +cap) % cap];
  }
  
  //queue is empty or not 
  template<class T>
  bool MyCircularQueue<T>::empty() const {
    return count == 0;
  }
  
  //get the size 
  template<class T>
  int MyCircularQueue<T>::size() const {
     return count;
  }
  //get the capacity
  template<class T>
  int MyCircularQueue<T>::capacity() const {
     return cap;
  }
  
  //Display queue elements
  template<class T>
  void MyCircularQueue<T>::display() const {
      cout<<"Circular Queue Elements: ";
      for(int i=0; i<count; i++){
          cout<<arr[(frontIndex +i) % cap]<<" ";
      }
      cout<<endl;
  }
  
int main() {
    MyCircularQueue<int> cq;
    cq.push(10);
    cq.push(20);
    cq.push(30);
    cq.push(40);
    cq.push(50);
   
    
    
    cq.display();
    
    cout<<"Front ELement: "<<cq.front()<<endl;
    cout<<"Rear Element: "<<cq.back()<<endl;
    cout<<"Size: "<<cq.size()<<endl;
    cout<<"Capacity: "<<cq.capacity()<<endl;
    
    cq.pop();
    cout<<"After pop: "<<endl;
    cq.display();
    cout<<"Front ELement: "<<cq.front()<<endl;
    cout<<"Rear Element: "<<cq.back()<<endl;
    cout<<"Size: "<<cq.size()<<endl;
    cout<<"Capacity: "<<cq.capacity()<<endl;
    
    cq.pop();
    cq.pop();
    cq.pop();
    cq.pop();
    if(cq.empty()){
        cout<<"Queue is empty!"<<endl;
    }
    
    
    return 0;
}
/*
Circular Queue Elements: 10 20 30 40 50 
Front ELement: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Circular Queue Elements: 20 30 40 50 
Front ELement: 20
Rear Element: 50
Size: 4
Capacity: 8
Queue is empty!
*/






//Circular Ring Buffer with fixed sized 
#include <iostream>
#include <stdexcept>
using namespace std;

template<class T, size_t cap>
class MyCircularQueue {
    T arr[cap];
    size_t frontIndex;
    size_t rearIndex;
    size_t count;

public:
    MyCircularQueue() : frontIndex(0), rearIndex(0), count(0) {}

    // Destructor is unnecessary, because no dynamic memory is allocated
    // ~MyCircularQueue() { delete[] arr; }

    void push(const T& val);
    void pop();
    T front() const;
    T back() const;
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void display() const;
};

// Insert at back
template<class T, size_t cap>
void MyCircularQueue<T, cap>::push(const T& val) {
    if (count == cap) throw overflow_error("CQ is full.");

    arr[rearIndex] = val;
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

// Remove from front
template<class T, size_t cap>
void MyCircularQueue<T, cap>::pop() {
    if (count == 0) throw underflow_error("CQ is empty.");

    frontIndex = (frontIndex + 1) % cap;
    count--;
}

// Get front element
template<class T, size_t cap>
T MyCircularQueue<T, cap>::front() const {
    if (count == 0) throw underflow_error("CQ is empty.");
    return arr[frontIndex];
}

// Get rear element
template<class T, size_t cap>
T MyCircularQueue<T, cap>::back() const {
    if (count == 0) throw underflow_error("CQ is empty.");
    return arr[(rearIndex - 1 + cap) % cap];
}

// Check if the queue is empty
template<class T, size_t cap>
bool MyCircularQueue<T, cap>::empty() const {
    return count == 0;
}

// Get the size
template<class T, size_t cap>
size_t MyCircularQueue<T, cap>::size() const {
    return count;
}

// Get the capacity
template<class T, size_t cap>
size_t MyCircularQueue<T, cap>::capacity() const {
    return cap;
}

// Display queue elements
template<class T, size_t cap>
void MyCircularQueue<T, cap>::display() const {
    if (count == 0) {
        cout << "Circular Queue is empty!" << endl;
        return;
    }

    cout << "Circular Queue Elements: ";
    for (size_t i = 0; i < count; i++) {
        cout << arr[(frontIndex + i) % cap] << " ";
    }
    cout << endl;
}

int main() {
    MyCircularQueue<int, 5> cq;
    
    cq.push(10);
    cq.push(20);
    cq.push(30);
    cq.push(40);
    cq.push(50);
    
    cq.display();  // Should print all elements correctly
    
    cout << "Front Element: " << cq.front() << endl;
    cout << "Rear Element: " << cq.back() << endl;
    cout << "Size: " << cq.size() << endl;
    cout << "Capacity: " << cq.capacity() << endl;
    
    cq.pop();  // Remove front element
    cout << "After pop:" << endl;
    cq.display();
    cout << "Front Element: " << cq.front() << endl;
    cout << "Rear Element: " << cq.back() << endl;
    cout << "Size: " << cq.size() << endl;
    
    cq.pop();
    cq.pop();
    cq.pop();
    cq.pop();
    
    if (cq.empty()) {
        cout << "Queue is empty!" << endl;
    }
    
    return 0;
}
/*
Circular Queue Elements: 10 20 30 40 50 
Front Element: 10
Rear Element: 50
Size: 5
Capacity: 5
After pop:
Circular Queue Elements: 20 30 40 50 
Front Element: 20
Rear Element: 50
Size: 4
Queue is empty!
*/



































//static
#include <iostream>
#include <stdexcept>

template <typename T, size_t Capacity>
class StaticRingBuffer {
private:
    T buffer[Capacity];  // Fixed-size buffer
    size_t head;         // Index of the next element to write
    size_t tail;         // Index of the next element to read
    size_t size;         // Current size of the buffer (number of elements)

public:
    // Constructor
    StaticRingBuffer() : head(0), tail(0), size(0) {}

    // Push an element into the buffer
    void push(const T& item) {
        if (size == Capacity) {
            throw std::overflow_error("Ring buffer is full.");
        }
        buffer[head] = item;
        head = (head + 1) % Capacity;
        ++size;
    }

    // Pop an element from the buffer
    T pop() {
        if (size == 0) {
            throw std::underflow_error("Ring buffer is empty.");
        }
        T item = buffer[tail];
        tail = (tail + 1) % Capacity;
        --size;
        return item;
    }

    // Check if the buffer is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Check if the buffer is full
    bool isFull() const {
        return size == Capacity;
    }

    // Get the current size of the buffer
    size_t getSize() const {
        return size;
    }

    // Get the capacity of the buffer
    size_t getCapacity() const {
        return Capacity;
    }

    // Peek at the front item (without removing it)
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Ring buffer is empty.");
        }
        return buffer[tail];
    }
};

int main() {
    try {
        // Create a static ring buffer with a capacity of 5
        StaticRingBuffer<int, 5> rb;

        // Push elements into the buffer
        rb.push(10);
        rb.push(20);
        rb.push(30);
        rb.push(40);
        rb.push(50);
        
        std::cout << "Buffer size after pushing 5 elements: " << rb.getSize() << std::endl;
        
        // Pop elements from the buffer
        std::cout << "Popped: " << rb.pop() << std::endl;
        std::cout << "Popped: " << rb.pop() << std::endl;

        std::cout << "Buffer size after popping 2 elements: " << rb.getSize() << std::endl;

        // Push more elements into the buffer
        rb.push(60);
        rb.push(70);
        
        std::cout << "Buffer size after pushing 2 more elements: " << rb.getSize() << std::endl;
        std::cout << "Peek at front: " << rb.peek() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
