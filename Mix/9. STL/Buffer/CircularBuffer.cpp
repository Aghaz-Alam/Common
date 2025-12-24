What is a Circular Buffer in C++?
A Circular Buffer (also known as a Ring Buffer or Cyclic Buffer) is a data structure that uses a fixed-size buffer 
in a way that it wraps around when the end of the buffer is reached. 

It is designed for efficient use of memory and is often used in situations where data is continuously produced and consumed, 
such as in streaming, buffering, real-time systems, and producer-consumer problems.



In a circular buffer, when you reach the end of the buffer, instead of blocking further writing, 
the data starts overwriting the oldest elements in the buffer. 

This "wrapping" behavior makes it especially useful in scenarios where you don’t want the buffer to run out of space 
but also don’t want to allocate memory dynamically or deal with resizing.

Internal Implementation of a Circular Buffer
Key Concepts
Head Pointer: Points to the next location to be read (or consumed).
Tail Pointer: Points to the next location to be written (or produced).
Buffer Size: The maximum number of elements the buffer can hold.
Full Condition: The buffer is full when the tail pointer is one step behind the head pointer.
Empty Condition: The buffer is empty when the head pointer equals the tail pointer.


In a typical implementation, the buffer is an array of fixed size, and the head and tail pointers are used 
to keep track of the read and write positions.

Basic Operations
Push (Insert or Write):
Insert data into the buffer at the position indicated by the tail pointer.
After insertion, the tail pointer is incremented, and if it reaches the end of the buffer, it wraps around to the beginning.

Pop (Remove or Read):
Remove data from the buffer at the position indicated by the head pointer.
After removal, the head pointer is incremented, and it wraps around to the beginning when it reaches the end of the buffer.

Check Empty: The buffer is empty if the head pointer equals the tail pointer.

Check Full: The buffer is full if the tail pointer is one step behind the head pointer, indicating that no more elements can be written until some are removed.




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

Explanation of the Code
Constructor (CircularBuffer(size_t size)): Initializes the buffer with a given capacity and sets the head, tail, and count to 0.
push(): Inserts an element at the tail of the buffer and increments the tail pointer. If the buffer is full, it throws an exception.
pop(): Removes and returns the element at the head of the buffer, then increments the head pointer. If the buffer is empty, it throws an exception.
isFull() and isEmpty(): Check the buffer’s status based on the relationship between the head, tail, and count.
Wrapping with Modulo: The (head + 1) % capacity and (tail + 1) % capacity expressions ensure that the pointers wrap around when they reach the end of the buffer.

Use Cases for a Circular Buffer
Streaming Data: Circular buffers are commonly used in audio/video streaming where data is continuously produced and consumed. Once the buffer is full, the oldest data is overwritten, keeping the latest data in memory.
Producer-Consumer Problems: In multi-threaded environments, a circular buffer is often used to manage the data produced by one thread and consumed by another. Producers write to the buffer, and consumers read from it.
Networking: In networking, circular buffers are used to store packets of data before they are transmitted or processed.
Real-time Systems: Circular buffers are useful for real-time applications that require fast data reading/writing without the overhead of dynamic memory allocation.
Embedded Systems: Many embedded systems use circular buffers to handle UART, SPI, I2C, or other communication protocols where incoming data is continuously received.

Advantages of Using a Circular Buffer
Fixed Size: Circular buffers have a fixed size, making them memory-efficient.
Efficient: Since the buffer wraps around, there’s no need to shift elements (as with a regular queue), resulting in O(1) time complexity for both push and pop operations.
No Memory Overhead: Unlike dynamic buffers, which may require memory reallocation as the data grows, circular buffers never need to be resized.

Limitations
Fixed Size: Once the buffer is full, new data will overwrite the oldest data, which might not be desirable in all cases.
No Dynamic Resizing: A circular buffer has a fixed capacity, so if you need to grow it dynamically based on usage, you need a more complex implementation.

Conclusion
A Circular Buffer is a highly efficient data structure for handling fixed-size buffers where the oldest data is overwritten when new data arrives. 
It’s widely used in streaming, real-time processing, and multithreading scenarios where you need continuous, non-blocking data storage with fast read and write operations.













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
