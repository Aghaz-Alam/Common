//queue dynamic grow and shrink 
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    T* arr;
    size_t frontIndex;
    size_t count;
    size_t cap;

    void resize(size_t newCap) {
        if (newCap < count)
            newCap = count;   // capacity must hold all elements

        if (newCap == 0)
            newCap = 1;       // minimum safe allocation

        T* newArr = new T[newCap];

        for (size_t i = 0; i < count; i++)
            newArr[i] = arr[frontIndex + i];

        delete[] arr;

        arr = newArr;
        cap = newCap;
        frontIndex = 0;
    }

public:
    Queue() : arr(nullptr), frontIndex(0), count(0), cap(0) {}

    ~Queue() {
        delete[] arr;
    }

    void push(const T& value) {
        if (count == cap) {
            size_t newCap = (cap == 0 ? 1 : cap * 2);
            resize(newCap);
        }
        arr[frontIndex + count] = value;
        count++;
    }

    void pop() {
        if (count == 0)
            throw underflow_error("Queue is empty!");

        frontIndex++;
        count--;

        // shrink dynamically
        if (count <= cap / 4 && cap > 1)
            resize(cap / 2);
    }

    T& front() {
        if (count == 0)
            throw underflow_error("Queue is empty!");
        return arr[frontIndex];
    }

    T& back() {
        if (count == 0)
            throw underflow_error("Queue is empty!");
        return arr[frontIndex + count - 1];
    }

    size_t size() const { return count; }
    size_t capacity() const { return cap; }

    bool empty() const { return count == 0; }

    void print() const {
        if (count == 0) {
            cout << "(empty)\n";
            return;
        }
        for (size_t i = 0; i < count; i++)
            cout << arr[frontIndex + i] << " ";
        cout << "\n";
    }
};

// ---------------------- TEST MAIN -------------------------
int main() {
    Queue<int> q;

    cout << "Pushing 10, 20, 30...\n";
    q.push(10);
    q.push(20);
    q.push(30);

    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n";

    cout << "Front = " << q.front() << "\n";
    cout << "Back  = " << q.back() << "\n\n";

    cout << "Popping one...\n";
    q.pop();
    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n\n";

    cout << "Adding more elements...\n";
    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);

    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n\n";

    cout << "Popping until shrink happens...\n";
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n\n";

    return 0;
}
/*
Pushing 10, 20, 30...
10 20 30 
size = 3, capacity = 4
Front = 10
Back  = 30

Popping one...
20 30 
size = 2, capacity = 4

Adding more elements...
20 30 40 50 60 70 
size = 6, capacity = 8

Popping until shrink happens...
60 70 
size = 2, capacity = 4
*/




#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
  private:
    T* arr;
    size_t frontIndex;
    size_t count;
    size_t cap;

    void resize(size_t newCap);

  public:
    Queue();
    ~Queue();

    void push(const T& value);
    void pop();
    T& front();
    T& back();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void print() const;
};


// Constructor
template <typename T>
Queue<T>::Queue()
    : arr(nullptr), frontIndex(0), count(0), cap(0) {}

// Destructor
template <typename T>
Queue<T>::~Queue() {
    delete[] arr;
}

// Resize (common for grow + shrink)
template <typename T>
void Queue<T>::resize(size_t newCap) {
    if (newCap < 4) newCap = 4;   // minimum capacity

    T* newArr = new T[newCap];
    for (size_t i = 0; i < count; i++)
        newArr[i] = arr[frontIndex + i];

    delete[] arr;
    arr = newArr;
    frontIndex = 0;
    cap = newCap;
}

// PUSH
template <typename T>
void Queue<T>::push(const T& value) {
    // grow if needed
    if (count == cap) {
        size_t newCap = (cap == 0 ? 4 : cap * 2);
        resize(newCap);
    }

    arr[frontIndex + count] = value;
    count++;
}

// POP
template <typename T>
void Queue<T>::pop() {
    if (count == 0)
        throw underflow_error("Queue is empty!");

    frontIndex++;
    count--;

    // shrink rule
    if (count > 0 && count <= cap / 4 && cap > 4)
        resize(cap / 2);
}

// FRONT
template <typename T>
T& Queue<T>::front() {
    if (count == 0)
        throw underflow_error("Queue is empty!");
    return arr[frontIndex];
}

// BACK
template <typename T>
T& Queue<T>::back() {
    if (count == 0)
        throw underflow_error("Queue is empty!");
    return arr[frontIndex + count - 1];
}

// SIZE
template <typename T>
size_t Queue<T>::size() const {
    return count;
}

// CAPACITY
template <typename T>
size_t Queue<T>::capacity() const {
    return cap;
}

// EMPTY CHECK
template <typename T>
bool Queue<T>::empty() const {
    return count == 0;
}

// PRINT
template <typename T>
void Queue<T>::print() const {
    if (count == 0) {
        cout << "(empty)\n";
        return;
    }
    for (size_t i = 0; i < count; i++)
        cout << arr[frontIndex + i] << " ";
    cout << "\n";
}


int main() {
    Queue<int> q;

    cout << "Pushing 10, 20, 30...\n";
    q.push(10);
    q.push(20);
    q.push(30);

    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n";

    cout << "Front = " << q.front() << "\n";
    cout << "Back  = " << q.back() << "\n\n";

    cout << "Popping one...\n";
    q.pop();
    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n\n";

    cout << "Adding more elements...\n";
    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);

    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n\n";

    cout << "Popping until shrink happens...\n";
    q.pop();
    q.pop();
    q.pop();
    q.pop();

    q.print();
    cout << "size = " << q.size() << ", capacity = " << q.capacity() << "\n\n";

    return 0;
}
/*
Pushing 10, 20, 30...
10 20 30 
size = 3, capacity = 4
Front = 10
Back  = 30

Popping one...
20 30 
size = 2, capacity = 4

Adding more elements...
20 30 40 50 60 70 
size = 6, capacity = 8

Popping until shrink happens...
50 60 
size = 2, capacity = 4
*/










// std::queue - Custom circular Queue (Dynamic Array) with Dynamic Grow + Shrink

#include <iostream>
#include <stdexcept>
using namespace std;

class MyQueue {
    int* arr;
    int frontIndex;
    int rearIndex;
    int count;
    int cap;

    void resize(int newCap);   // SINGLE resize()

public:
    MyQueue();
    ~MyQueue();

    void push(const int& val);
    void pop();
    int front() const;
    int back() const;

    bool empty() const;
    int size() const;
    int capacity() const;

    void display() const;
};

/*-------------------- CTOR / DTOR --------------------*/

MyQueue::MyQueue()
    : arr(new int[1]), frontIndex(0), rearIndex(0), count(0), cap(1) {}

MyQueue::~MyQueue() {
    delete[] arr;
}

/*-------------------- RESIZE (COMMON FOR GROW + SHRINK) --------------------*/

void MyQueue::resize(int newCap) {

    if (newCap < 1) newCap = 1;   // minimum cap = 1
    if (newCap == cap) return;    // no change

    int* newArr = new int[newCap];

    for (int i = 0; i < count; i++)
        newArr[i] = arr[(frontIndex + i) % cap];

    delete[] arr;

    arr = newArr;
    cap = newCap;
    frontIndex = 0;
    rearIndex = count;
}

/*-------------------- PUSH --------------------*/

void MyQueue::push(const int& val) {

    if (count == cap)
        resize(cap * 2);   // grow

    arr[rearIndex] = val;
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

/*-------------------- POP --------------------*/

void MyQueue::pop() {
    if (count == 0) throw underflow_error("Queue is empty.");

    frontIndex = (frontIndex + 1) % cap;
    count--;

    // SHRINK if queue <= 1/4 full AND cap > 1
    if (count > 0 && count <= cap / 4 && cap > 1)
        resize(cap / 2);
}

/*-------------------- FRONT & BACK --------------------*/

int MyQueue::front() const {
    if (count == 0) throw underflow_error("Queue is empty.");
    return arr[frontIndex];
}

int MyQueue::back() const {
    if (count == 0) throw underflow_error("Queue is empty.");
    return arr[(rearIndex - 1 + cap) % cap];
}

/*-------------------- BASIC QUERIES --------------------*/

bool MyQueue::empty() const { return count == 0; }
int MyQueue::size() const { return count; }
int MyQueue::capacity() const { return cap; }

/*-------------------- DISPLAY --------------------*/

void MyQueue::display() const {
    cout << "Queue Elements: ";
    for (int i = 0; i < count; i++)
        cout << arr[(frontIndex + i) % cap] << " ";
    cout << endl;
}

/*-------------------- MAIN --------------------*/

int main() {

    try {
        MyQueue q;

        cout << "\n=== Pushing Elements ===\n";
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);

        q.display();
        cout << "Front: " << q.front() << endl;
        cout << "Back : " << q.back()  << endl;
        cout << "Size : " << q.size()  << endl;
        cout << "Cap  : " << q.capacity() << endl;
        
        
        /*--- Demonstrate shrink ---*/
        cout << "\n=== Popping to shrink ===\n";
        q.pop();  // 4
        q.pop();  // 3
        q.pop();  // 2 -> should SHRINK
        q.display();

        cout << "Size : " << q.size() << endl;
        cout << "Cap  : " << q.capacity() << endl;

        /*--- Empty completely ---*/
        q.pop();
        q.pop();  // last valid pop

        cout << "\nTrying extra pop...\n";
        q.pop();  // Exception

    }
    catch (const exception& e) {
        cout << "Exception Caught: " << e.what() << endl;
    }

    return 0;
}
/*
=== Pushing Elements ===
Queue Elements: 10 20 30 40 50 
Front: 10
Back : 50
Size : 5
Cap  : 8

=== Popping to shrink ===
Queue Elements: 40 50 
Size : 2
Cap  : 4

Trying extra pop...
Exception Caught: Queue is empty.
*/







// std::queue - Custom Circular Queue (Dynamic Array) with Dynamic Grow + Shrink
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyQueue {
    T* arr;
    size_t frontIndex;
    size_t rearIndex;
    size_t count;
    size_t cap;

    void resize(size_t newCap);   // SINGLE resize()

public:
    MyQueue();                     // default ctor
    ~MyQueue();                    // dtor

    MyQueue(const MyQueue& other);             // copy ctor
    MyQueue& operator=(const MyQueue& other);  // copy assignment

    MyQueue(MyQueue&& other) noexcept;         // move ctor
    MyQueue& operator=(MyQueue&& other) noexcept; // move assignment

    void push(const T& val);
    void pop();
    T& front() const;
    T& back() const;

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    void display() const;
};

/*-------------------- CTOR --------------------*/
template <typename T>
MyQueue<T>::MyQueue()
    : arr(new T[1]), frontIndex(0), rearIndex(0), count(0), cap(1) {}

/*-------------------  DTOR --------------------*/
template <typename T>
MyQueue<T>::~MyQueue() {
    delete[] arr;
}

/*-------------------- COPY CONSTRUCTOR --------------------*/
template <typename T>
MyQueue<T>::MyQueue(const MyQueue& other)
    : arr(new T[other.cap]),
      frontIndex(other.frontIndex),
      rearIndex(other.rearIndex),
      count(other.count),
      cap(other.cap)
{
    for (size_t i = 0; i < cap; i++)
        arr[i] = other.arr[i];
}

/*-------------------- COPY ASSIGNMENT --------------------*/
template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other) {
    if (this == &other) return *this;

    delete[] arr;

    arr = new T[other.cap];
    frontIndex = other.frontIndex;
    rearIndex  = other.rearIndex;
    count      = other.count;
    cap        = other.cap;

    for (size_t i = 0; i < cap; i++)
        arr[i] = other.arr[i];

    return *this;
}

/*-------------------- MOVE CONSTRUCTOR --------------------*/
template <typename T>
MyQueue<T>::MyQueue(MyQueue&& other) noexcept
    : arr(other.arr),
      frontIndex(other.frontIndex),
      rearIndex(other.rearIndex),
      count(other.count),
      cap(other.cap)
{
    other.arr = nullptr;
    other.frontIndex = 0;
    other.rearIndex = 0;
    other.count = 0;
    other.cap = 0;
}

/*-------------------- MOVE ASSIGNMENT --------------------*/
template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other) noexcept {
    if (this == &other) return *this;

    delete[] arr;

    arr = other.arr;
    frontIndex = other.frontIndex;
    rearIndex  = other.rearIndex;
    count      = other.count;
    cap        = other.cap;

    other.arr = nullptr;
    other.frontIndex = 0;
    other.rearIndex = 0;
    other.count = 0;
    other.cap = 0;

    return *this;
}

/*-------------------- RESIZE --------------------*/
template <typename T>
void MyQueue<T>::resize(size_t newCap) {

    if (newCap < 1) newCap = 1;
    if (newCap == cap) return;

    T* newArr = new T[newCap];

    for (size_t i = 0; i < count; i++)
        newArr[i] = arr[(frontIndex + i) % cap];

    delete[] arr;

    arr = newArr;
    cap = newCap;
    frontIndex = 0;
    rearIndex = count;
}

/*-------------------- PUSH --------------------*/
template <typename T>
void MyQueue<T>::push(const T& val) {

    if (count == cap)
        resize(cap * 2);

    arr[rearIndex] = val;
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

/*-------------------- POP --------------------*/
template <typename T>
void MyQueue<T>::pop() {
    if (count == 0) throw underflow_error("Queue is empty.");

    frontIndex = (frontIndex + 1) % cap;
    count--;

    if (count > 0 && count <= cap / 4 && cap > 1)
        resize(cap / 2);
}

/*-------------------- FRONT & BACK --------------------*/
template <typename T>
T& MyQueue<T>::front() const {
    if (count == 0) throw underflow_error("Queue is empty.");
    return arr[frontIndex];
}

template <typename T>
T& MyQueue<T>::back() const {
    if (count == 0) throw underflow_error("Queue is empty.");
    return arr[(rearIndex - 1 + cap) % cap];
}

/*-------------------- BASIC QUERIES --------------------*/
template <typename T>
bool MyQueue<T>::empty() const { return count == 0; }

template <typename T>
size_t MyQueue<T>::size() const { return count; }

template <typename T>
size_t MyQueue<T>::capacity() const { return cap; }

/*-------------------- DISPLAY --------------------*/
template <typename T>
void MyQueue<T>::display() const {
    cout << "Queue Elements: ";
    for (size_t i = 0; i < count; i++)
        cout << arr[(frontIndex + i) % cap] << " ";
    cout << endl;
}

/*-------------------- MAIN --------------------*/
int main() {
    try {
        MyQueue<int> q;

        cout << "=== Pushing Elements ===\n";
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);

        q.display();

        /*===========================
          COPY CONSTRUCTOR TEST
        ============================*/
        cout << "\n=== Testing Copy Constructor ===\n";
        MyQueue<int> q2(q);
        q2.display();

        /*===========================
          COPY ASSIGNMENT TEST
        ============================*/
        cout << "\n=== Testing Copy Assignment ===\n";
        MyQueue<int> q3;
        q3 = q;
        q3.display();

        /*===========================
          MOVE CONSTRUCTOR TEST
        ============================*/
        cout << "\n=== Testing Move Constructor ===\n";
        MyQueue<int> q4(std::move(q));
        q4.display();

        /*===========================
          MOVE ASSIGNMENT TEST
        ============================*/
        cout << "\n=== Testing Move Assignment ===\n";
        MyQueue<int> q5;
        q5 = std::move(q2);
        q5.display();


        cout << "\n=== Shrink Test ===\n";
        q4.pop();
        q4.pop();
        q4.pop();
        q4.display();
        cout << "Size: " << q4.size() << "  Cap: " << q4.capacity() << endl;

        cout << "\nTrying extra pop...\n";
        q4.pop();
        q4.pop();
        q4.pop(); // should throw

    }
    catch (const exception& e) {
        cout << "Exception Caught: " << e.what() << endl;
    }
}
/*
=== Pushing Elements ===
Queue Elements: 10 20 30 40 50 

=== Testing Copy Constructor ===
Queue Elements: 10 20 30 40 50 

=== Testing Copy Assignment ===
Queue Elements: 10 20 30 40 50 

=== Testing Move Constructor ===
Queue Elements: 10 20 30 40 50 

=== Testing Move Assignment ===
Queue Elements: 10 20 30 40 50 

=== Shrink Test ===
Queue Elements: 40 50 
Size: 2  Cap: 4

Trying extra pop...
Exception Caught: Queue is empty.
*/














// Custom Queue Implementation Using a Dynamic Array without template with R-value and L-value
#include <iostream>
#include <stdexcept>
using namespace std;

class MyQueue {
    int* arr;
    int frontIndex;
    int rearIndex;
    int count;
    int cap;

    void resize();

public:
    MyQueue();
    ~MyQueue();

    // L-value overload
    void push(const int& val);

    // R-value overload
    void push(int&& val);

    void pop();
    int front() const;
    int back() const;
    bool empty() const;
    int size() const;
    int capacity() const;
    void display() const;
};

MyQueue::MyQueue() : arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(0) {}

MyQueue::~MyQueue() { delete[] arr;}

void MyQueue::resize() {
    int oldCap = cap;
    cap = (cap == 0) ? 1 : cap * 2;

    int* newArr = new int[cap];

    for (int i = 0; i < count; i++) {
        newArr[i] = arr[(frontIndex + i) % oldCap];
    }

    delete[] arr;
    arr = newArr;
    frontIndex = 0;
    rearIndex = count;
}

// L-value push
void MyQueue::push(const int& val) {
    if (count == cap) resize();
    arr[rearIndex] = val;
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

// R-value push (will move)
void MyQueue::push(int&& val) {
    if (count == cap) resize();
    arr[rearIndex] = std::move(val); // though int move has no effect, but demonstrates r-value API
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

void MyQueue::pop() {
    if (count == 0) throw underflow_error("Queue is empty.");
    frontIndex = (frontIndex + 1) % cap;
    count--;
}

int MyQueue::front() const {
    if (count == 0) throw underflow_error("Queue is empty.");
    return arr[frontIndex];
}

int MyQueue::back() const {
    if (count == 0) throw underflow_error("Queue is empty.");
    return arr[(rearIndex - 1 + cap) % cap];
}

bool MyQueue::empty() const {
    return count == 0;
}

int MyQueue::size() const {
    return count;
}

int MyQueue::capacity() const {
    return cap;
}

void MyQueue::display() const {
    cout << "Queue Elements: ";
    for (int i = 0; i < count; i++) {
        cout << arr[(frontIndex + i) % cap] << " ";
    }
    cout << endl;
}

int main() {

    try {
        MyQueue q;

        cout << "=== L-VALUE PUSH TEST ===\n";
        int a = 10;
        int b = 20;
        q.push(a);   // L-value
        q.push(b);   // L-value
        cout<<"Queue Elements with L-value: ";
        q.display();
        
        
        cout << "\n=== R-VALUE PUSH TEST ===\n";
        q.push(30);  // r-value literal
        q.push(40);  // r-value literal
        q.push(50);  // r-value literal
        cout<<"Queue Elements with R-value:";
        q.display();

        cout << "Front Element: " << q.front() << endl;
        cout << "Rear Element: " << q.back() << endl;
        cout << "Size: " << q.size() << endl;
        cout << "Capacity: " << q.capacity() << endl;

        q.pop();
        cout << "After pop: " << endl;
        q.display();

        cout << "Front Element: " << q.front() << endl;
        cout << "Rear Element: " << q.back() << endl;
        cout << "Size: " << q.size() << endl;
        cout << "Capacity: " << q.capacity() << endl;

        // popping until empty
        q.pop();
        q.pop();
        q.pop();
        q.pop();   // last valid pop

        // This will throw exception
        cout << "Trying one more pop on empty queue..." << endl;
        q.pop();   // throws underflow_error
    }
    catch (const underflow_error& e) {
        cout << "Underflow Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "General Error: " << e.what() << endl;
    }

    return 0;
}
/*
=== L-VALUE PUSH TEST ===
Queue Elements with L-value: Queue Elements: 10 20 

=== R-VALUE PUSH TEST ===
Queue Elements with R-value:Queue Elements: 10 20 30 40 50 
Front Element: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Queue Elements: 20 30 40 50 
Front Element: 20
Rear Element: 50
Size: 4
Capacity: 8
Trying one more pop on empty queue...
Underflow Error: Queue is empty.
*/
























