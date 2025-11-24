//Dynamic array and without rulle 5
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class CQueue {
  private:
    T* arr;               // dynamic array for queue
    size_t frontIndex;    // index of the front element
    size_t rearIndex;     // index of the rear element (next insertion spot)
    size_t cap;           // capacity
    size_t count;         // number of elements

  public:
    // Constructor
    CQueue(size_t capacity): arr(new T[capacity]), frontIndex(0), rearIndex(0), cap(capacity), count(0) {}

    // Destructor
    ~CQueue() {
        delete[] arr;
    }
    void push(T value);
    void pop();
    T front() const; 
    T back() const;
    bool empty() const ;
    size_t size() const; 
    size_t capacity() const;
    void Display() const;

};
// Push an element (circular)
template <typename T>
void CQueue<T>::push(T value) {
   if (count == cap) {
        // Overwrite oldest element
        frontIndex = (frontIndex + 1) % cap;
    } 
    else {
        count++;
    }

    arr[rearIndex] = value;
    rearIndex = (rearIndex + 1) % cap;
}

// Pop an element
template <typename T>
void CQueue<T>::pop() {
    if (count == 0)
       throw underflow_error("Queue is empty!");

    frontIndex = (frontIndex + 1) % cap;
    count--;
}

// Front element
template <typename T>
T CQueue<T>::front() const {
    if (count == 0)
        throw underflow_error("Queue is empty!");
    return arr[frontIndex];
}

// Back element
template <typename T>
T CQueue<T>::back() const {
    if (count == 0)
        throw underflow_error("Queue is empty!");

    return arr[(rearIndex - 1 + cap) % cap];
}

// Check if empty
template <typename T>
bool CQueue<T>::empty() const {
    return count == 0;
}

// Size
template <typename T>
size_t CQueue<T>::size() const {
    return count;
}

// Capacity
template <typename T>
size_t CQueue<T>::capacity() const {
     return cap;
 }

// Display elements
template <typename T>
void CQueue<T>::Display() const {
    if (count == 0) {
        cout << "Queue is empty!" << endl;
        return;
    }

    for (size_t i = 0; i < count; i++)
        cout << arr[(frontIndex + i) % cap] << " ";
    cout << endl;
}


int main() {
    // Integer queue
    CQueue<int> q(5);

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
    CQueue<string> qs(3);
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



//using Dynamic array and rule 5
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class CQueue {
  private:
    T* arr;               // dynamic array
    size_t frontIndex;    // index of the front element
    size_t rearIndex;     // index of the rear element
    size_t cap;           // capacity
    size_t count;         // number of elements

  public:
    // Constructor
    CQueue(size_t capacity)
        : arr(new T[capacity]), frontIndex(0), rearIndex(0),
          cap(capacity), count(0) {}

    // ---------------------------
    // Rule of 5: Copy Constructor
    // ---------------------------
    CQueue(const CQueue& other)
        : arr(new T[other.cap]), frontIndex(other.frontIndex),
          rearIndex(other.rearIndex), cap(other.cap), count(other.count)
    {
        for (size_t i = 0; i < cap; i++)
            arr[i] = other.arr[i];
    }

    // ---------------------------------
    // Copy Assignment Operator
    // ---------------------------------
    CQueue& operator=(const CQueue& other) {
        if (this != &other) {
            delete[] arr;

            arr = new T[other.cap];
            for (size_t i = 0; i < other.cap; i++)
                arr[i] = other.arr[i];

            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            cap       = other.cap;
            count     = other.count;
        }
        return *this;
    }

    // ---------------------------
    // Move Constructor
    // ---------------------------
    CQueue(CQueue&& other) noexcept
        : arr(other.arr), frontIndex(other.frontIndex),
          rearIndex(other.rearIndex), cap(other.cap), count(other.count)
    {
        other.arr = nullptr;
        other.count = 0;
        other.cap = 0;
        other.frontIndex = 0;
        other.rearIndex = 0;
    }

    // ---------------------------------
    // Move Assignment Operator
    // ---------------------------------
    CQueue& operator=(CQueue&& other) noexcept {
        if (this != &other) {
            delete[] arr;

            arr = other.arr;
            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            cap = other.cap;
            count = other.count;

            other.arr = nullptr;
            other.count = 0;
            other.cap = 0;
            other.frontIndex = 0;
            other.rearIndex = 0;
        }
        return *this;
    }

    // Destructor
    ~CQueue() { delete[] arr; }

    // Member functions
    void push(T value);
    void pop();
    T front() const;
    T back() const;
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void Display() const;
};

// Push
template <typename T>
void CQueue<T>::push(T value) {
    if (count == cap) {
        // overwrite oldest
        frontIndex = (frontIndex + 1) % cap;
    } else {
        count++;
    }
    arr[rearIndex] = value;
    rearIndex = (rearIndex + 1) % cap;
}

// Pop
template <typename T>
void CQueue<T>::pop() {
    if (count == 0)
        throw underflow_error("Queue is empty!");

    frontIndex = (frontIndex + 1) % cap;
    count--;
}

// Front
template <typename T>
T CQueue<T>::front() const {
    if (count == 0)
        throw underflow_error("Queue is empty!");
    return arr[frontIndex];
}

// Back
template <typename T>
T CQueue<T>::back() const {
    if (count == 0)
        throw underflow_error("Queue is empty!");
    return arr[(rearIndex - 1 + cap) % cap];
}

// Empty
template <typename T>
bool CQueue<T>::empty() const {
    return count == 0;
}

// Size
template <typename T>
size_t CQueue<T>::size() const {
    return count;
}

// Capacity
template <typename T>
size_t CQueue<T>::capacity() const {
    return cap;
}

// Display
template <typename T>
void CQueue<T>::Display() const {
    if (count == 0) {
        cout << "Queue is empty!" << endl;
        return;
    }
    for (size_t i = 0; i < count; i++)
        cout << arr[(frontIndex + i) % cap] << " ";
    cout << endl;
}

// ---------------------------
// MAIN PROGRAM
// ---------------------------
int main() {
    cout << "=== Integer Queue ===\n";
    CQueue<int> q(5);

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

    // ---------------------------------------
    // Test Copy Constructor
    // ---------------------------------------
    cout << "\n=== Copy Constructor Test ===\n";
    q.push(100);
    q.push(200);
    q.push(300);

    CQueue<int> copyQ = q;   // deep copy
    cout << "Original: "; q.Display();
    cout << "Copy:     "; copyQ.Display();

    // ---------------------------------------
    // Test Move Constructor
    // ---------------------------------------
    cout << "\n=== Move Constructor Test ===\n";
    CQueue<int> movedQ = std::move(q);
    cout << "Moved Queue: ";
    movedQ.Display();
    cout << "Original after move: ";
    q.Display(); // should be empty or invalid state

    // ---------------------------------------
    // String queue example
    // ---------------------------------------
    cout << "\n=== String Queue ===\n";
    CQueue<string> qs(3);
    qs.push("apple");
    qs.push("banana");
    qs.push("cherry");

    cout << "String Queue Front: " << qs.front() << endl;
    cout << "String Queue Back: " << qs.back() << endl;

    qs.Display();

    return 0;
}
/*
=== Integer Queue ===
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

=== Copy Constructor Test ===
Original: 100 200 300 
Copy:     100 200 300 

=== Move Constructor Test ===
Moved Queue: 100 200 300 
Original after move: Queue is empty!

=== String Queue ===
String Queue Front: apple
String Queue Back: cherry
apple banana cherry 
*/