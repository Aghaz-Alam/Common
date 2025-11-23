//Internal Implementation of Dequeue
#include <iostream>
#include <stdexcept>
using namespace std;

class DeQueue {
private:
    int* arr;              // dynamic array
    size_t frontIndex;     // index of front element
    size_t rearIndex;      // index of next insertion at rear
    size_t cap;            // capacity
    size_t count;          // number of stored elements

public:
    // Constructor
    DeQueue() : arr(nullptr), frontIndex(0), rearIndex(0), cap(0), count(0) {}

    // Destructor
    ~DeQueue() {
        delete[] arr;
    }

    // Push at back
    void push_back(int value) {
        if (count == cap) {
            resize();
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;
        count++;
    }

    // Push at front
    void push_front(int value) {
        if (count == cap) {
            resize();
        }
        frontIndex = (frontIndex - 1 + cap) % cap;
        arr[frontIndex] = value;
        count++;
    }

    // Pop front
    void pop_front() {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        frontIndex = (frontIndex + 1) % cap;
        count--;
    }

    // Pop back
    void pop_back() {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        rearIndex = (rearIndex - 1 + cap) % cap;
        count--;
    }

    // Get front
    int front() const {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        return arr[frontIndex];
    }

    // Get back
    int back() const {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        return arr[(rearIndex - 1 + cap) % cap];
    }

    // Empty check
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

    // Display all elements
    void Display() const {
        for (size_t i = 0; i < count; i++)
            cout << arr[(frontIndex + i) % cap] << " ";
        cout << endl;
    }

private:
    // Resize dynamic array (double capacity)
    void resize() {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        int* newArr = new int[newCap];

        for (size_t i = 0; i < count; ++i) {
            newArr[i] = arr[(frontIndex + i) % cap];
        }

        delete[] arr;
        arr = newArr;
        frontIndex = 0;
        rearIndex = count;
        cap = newCap;
    }
};


// ====================== MAIN =========================

int main() {
    DeQueue dq;

    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.push_back(40);
    dq.push_back(50);

    cout << "Deque Elements after push_back: ";
    dq.Display();

    cout << "Front element: " << dq.front() << endl;
    cout << "Rear element: " << dq.back() << endl;

    dq.push_front(5);

    cout << "Deque Elements after push_front: ";
    dq.Display();

    cout << "Front element: " << dq.front() << endl;
    cout << "Rear element: " << dq.back() << endl;

    dq.pop_front();
    cout << "Deque Elements after pop_front: ";
    dq.Display();

    dq.pop_back();
    cout << "Deque Elements after pop_back: ";
    dq.Display();

    return 0;
}
/*
Deque Elements after push_back: 10 20 30 40 50 
Front element: 10
Rear element: 50
Deque Elements after push_front: 5 10 20 30 40 50 
Front element: 5
Rear element: 50
Deque Elements after pop_front: 10 20 30 40 50 
Deque Elements after pop_back: 10 20 30 40 
*/


//Internal implementation of DeQueue 
#include <iostream>
#include <stdexcept> // For exception handling
using namespace std;

template <typename T>
class DeQueue {
private:
    T* arr;              // Pointer to dynamic array (queue storage)
    size_t frontIndex;   // Index of the front element in the queue
    size_t rearIndex;    // Index of the rear element in the queue
    size_t cap;          // Capacity of the queue (size of the underlying array)
    size_t count;        // Number of elements in the queue

public:
    // Constructor
    DeQueue() : arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(0) {}

    // Destructor to free allocated memory
    ~DeQueue() {
        delete[] arr;
    }
    
    // Push an element at the rear end of the queue
    void push_back(T value) {
        if (count == cap) {
            resize();
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap; // Circular increment
        count++;
    }

    // Push an element at the front end of the queue
    void push_front(T value) {
        if (count == cap) {
            resize();
        }
        frontIndex = (frontIndex - 1 + cap) % cap; // Circular decrement
        arr[frontIndex] = value;
        count++;
    }

    // Pop an element from the front of the queue
    void pop_front() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex = (frontIndex + 1) % cap; // Circular increment
        count--;
    }

    // Pop an element from the rear of the queue
    void pop_back() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        rearIndex = (rearIndex - 1 + cap) % cap; // Circular decrement
        count--;
    }

    // Return the front element without removing it
    T front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[frontIndex];
    }

    // Return the rear element without removing it
    T back() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[(rearIndex - 1 + cap) % cap]; // Circular indexing
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
        for (size_t i = 0; i < count; ++i) {
            cout << arr[(frontIndex + i) % cap] << " ";  // Circular indexing
        }
        cout << endl;
    }
    
   private: 
    // Resize the queue (double the capacity)
    void resize() {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newArr = new T[newCap];
        for (size_t i = 0; i < count; ++i) {
            newArr[i] = arr[(frontIndex + i) % cap]; // Copy elements to the new array
        }
        delete[] arr;
        arr = newArr;
        frontIndex = 0; // Reset front index
        rearIndex = count; // Set rear index to count
        cap = newCap;
    }
};

int main() {
    // Create a deque of integers
    DeQueue<int> dq;

    // Enqueue elements into the deque (at the back)
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.push_back(40);
    dq.push_back(50);

    // Display the deque elements
    cout << "Deque Elements after push_back: ";
    dq.Display();

     // Front and rear elements
    cout << "Front element: " << dq.front() << endl;
    cout << "Rear element: " << dq.back() << endl;
    
    
    // Enqueue an element at the front
    dq.push_front(5);

    // Display the deque elements after pushing at the front
    cout << "Deque Elements after push_front: ";
    dq.Display();

    
     // Front and rear elements
    cout << "Front element: " << dq.front() << endl;
    cout << "Rear element: " << dq.back() << endl;


    // Pop an element from the front
    dq.pop_front();

    // Display the deque elements after pop_front
    cout << "Deque Elements after pop_front: ";
    dq.Display();

     // Front and rear elements
    cout << "Front element: " << dq.front() << endl;
    cout << "Rear element: " << dq.back() << endl;

    // Pop an element from the rear
    dq.pop_back();

    // Display the deque elements after pop_back
    cout << "Deque Elements after pop_back: ";
    dq.Display();

    // Front and rear elements
    cout << "Front element: " << dq.front() << endl;
    cout << "Rear element: " << dq.back() << endl;

    return 0;
}
/*
Deque Elements after push_back: 10 20 30 40 50 
Front element: 10
Rear element: 50
Deque Elements after push_front: 5 10 20 30 40 50 
Front element: 5
Rear element: 50
Deque Elements after pop_front: 10 20 30 40 50 
Front element: 10
Rear element: 50
Deque Elements after pop_back: 10 20 30 40 
Front element: 10
Rear element: 40
*/