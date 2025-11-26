// Fixed-size Circular Queue 
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class CQueue {
private:
    T arr[N];
    size_t frontIndex;
    size_t rearIndex;
    size_t count;

public:
    CQueue();

    // Basic Queue Operations
    void push(const T& value);
    void pop();
    T front() const;
    T back() const;

    // Additional Methods
    T peekFront() const;   // alias of front()
    T peekBack() const;    // alias of back()
    void clear();          // reset queue
    bool full() const;     // check full state

    // Utility
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void Display() const;
};

// Constructor
template <typename T, size_t N>
CQueue<T, N>::CQueue() : frontIndex(0), rearIndex(0), count(0) {}

// Push
template <typename T, size_t N>
void CQueue<T, N>::push(const T& value) {
    if (count == N) throw overflow_error("Queue is full!");

    arr[rearIndex] = value;
    rearIndex = (rearIndex + 1) % N;
    ++count;
}

// Pop
template <typename T, size_t N>
void CQueue<T, N>::pop() {
    if (count == 0) throw underflow_error("Queue is empty!");

    frontIndex = (frontIndex + 1) % N;
    --count;
}

// Front
template <typename T, size_t N>
T CQueue<T, N>::front() const {
    if (count == 0) throw underflow_error("Queue is empty!");
    return arr[frontIndex];
}

// Back
template <typename T, size_t N>
T CQueue<T, N>::back() const {
    if (count == 0) throw underflow_error("Queue is empty!");
    return arr[(rearIndex - 1 + N) % N];
}

// Aliases
template <typename T, size_t N>
T CQueue<T, N>::peekFront() const {
    return front();
}

template <typename T, size_t N>
T CQueue<T, N>::peekBack() const {
    return back();
}

// Clear queue
template <typename T, size_t N>
void CQueue<T, N>::clear() {
    frontIndex = rearIndex = count = 0;
}

// Check full
template <typename T, size_t N>
bool CQueue<T, N>::full() const {
    return count == N;
}

// empty, size, capacity
template <typename T, size_t N>
bool CQueue<T, N>::empty() const { return count == 0; }

template <typename T, size_t N>
size_t CQueue<T, N>::size() const { return count; }

template <typename T, size_t N>
size_t CQueue<T, N>::capacity() const { return N; }

// Display
template <typename T, size_t N>
void CQueue<T, N>::Display() const {
    if (count == 0) {
        cout << "Queue is empty!" << endl;
        return;
    }
    for (size_t i = 0; i < count; i++)
        cout << arr[(frontIndex + i) % N] << " ";
    cout << endl;
}


// ------------------------ MAIN METHOD ------------------------
int main() {
    cout << "--- INT QUEUE ---\n";
    try {
        CQueue<int, 5> q;

        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);

        cout << "Queue elements: ";
        q.Display();

        cout << "Front: " << q.front() << endl;
        cout << "Back: " << q.back() << endl;

        // Testing new alias functions
        cout << "PeekFront: " << q.peekFront() << endl;
        cout << "PeekBack: " << q.peekBack() << endl;

        // Test full()
        cout << "Is full? " << (q.full() ? "Yes" : "No") << endl;

        // Pop and re-push → wrap-around test
        q.pop(); // remove 10
        q.pop(); // remove 20

        q.push(60);
        q.push(70);   // wrap-around inserts at beginning

        cout << "\nAfter wrap-around insert: ";
        q.Display();

        // Test clear()
        cout << "\nClearing queue...\n";
        q.clear();
        cout << "Size after clear: " << q.size() << endl;
        cout << "Empty? " << (q.empty() ? "Yes" : "No") << endl;

    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    
    
        cout << "\n--- STRING QUEUE ---\n";
    try {
        CQueue<string, 3> qs;

        qs.push("apple");
        qs.push("banana");
        qs.push("cherry");

        cout << "Queue elements: ";
        qs.Display();

        cout << "Front: " << qs.front() << endl;
        cout << "Back: " << qs.back() << endl;

        // new alias functions
        cout << "PeekFront: " << qs.peekFront() << endl;
        cout << "PeekBack: " << qs.peekBack() << endl;

        // full() check
        cout << "Is full? " << (qs.full() ? "Yes" : "No") << endl;

        // Wrap-around test (pop 1 then push 1)
        qs.pop();  // remove "apple"
        cout << "\nAfter pop: ";
        qs.Display();
        cout << "Front now: " << qs.front() << endl;

        qs.push("dates");  // wrap-around insert
        cout << "After wrap-around push: ";
        qs.Display();
        cout << "Back now: " << qs.back() << endl;

        // clear()
        cout << "\nClearing string queue...\n";
        qs.clear();
        cout << "Size after clear: " << qs.size() << endl;
        cout << "Empty? " << (qs.empty() ? "Yes" : "No") << endl;

        // Underflow test
        cout << "\nTrying pop on empty queue:\n";
        qs.pop();   // will throw

    }
    catch (const underflow_error& e) {
        cout << "String Queue Underflow: " << e.what() << endl;
    }

    return 0;
}
/*
--- INT QUEUE ---
Queue elements: 10 20 30 40 50 
Front: 10
Back: 50
PeekFront: 10
PeekBack: 50
Is full? Yes

After wrap-around insert: 30 40 50 60 70 

Clearing queue...
Size after clear: 0
Empty? Yes

--- STRING QUEUE ---
Queue elements: apple banana cherry 
Front: apple
Back: cherry
PeekFront: apple
PeekBack: cherry
Is full? Yes

After pop: banana cherry 
Front now: banana
After wrap-around push: banana cherry dates 
Back now: dates

Clearing string queue...
Size after clear: 0
Empty? Yes

Trying pop on empty queue:
String Queue Underflow: Queue is empty!
*/






//Dynamic in size circular queue 
#include <iostream>
#include <stdexcept>
#include <utility>   // move

template <typename T>
class CQueue {
  private:
    T* arr;
    size_t frontIndex;
    size_t rearIndex;
    size_t cap;
    size_t count;

    void resize(size_t newCap);

  public:
    CQueue();                        // default ctor
    ~CQueue();                       // destructor

    CQueue(const CQueue& other);     // copy ctor
    CQueue(CQueue&& other) noexcept; // move ctor

    CQueue& operator=(const CQueue& other);     // copy assignment
    CQueue& operator=(CQueue&& other) noexcept; // move assignment

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    void push(const T& value);
    void push(T&& value);

    void pop();

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    void Display() const;
};


/*------------------- DEFAULT CTOR -------------------*/
template <typename T>
CQueue<T>::CQueue(): arr(new T[1]), frontIndex(0), rearIndex(0), cap(1), count(0) {}

/*------------------- DESTRUCTOR -------------------*/
template <typename T>
CQueue<T>::~CQueue() {
    delete[] arr;
}

/*------------------- RESIZE -------------------*/
template <typename T>
void CQueue<T>::resize(size_t newCap) {
    T* newArr = new T[newCap];

    for (size_t i = 0; i < count; i++)
        newArr[i] = std::move(arr[(frontIndex + i) % cap]);

    delete[] arr;
    arr = newArr;
    cap = newCap;

    frontIndex = 0;
    rearIndex = count;
}

/*------------------- COPY CTOR -------------------*/
template <typename T>
CQueue<T>::CQueue(const CQueue& other): arr(new T[other.cap]), frontIndex(other.frontIndex), rearIndex(other.rearIndex), cap(other.cap), count(other.count){
    for (size_t i = 0; i < cap; i++)
        arr[i] = other.arr[i];
}

/*------------------- MOVE CTOR -------------------*/
template <typename T>
CQueue<T>::CQueue(CQueue&& other) noexcept: arr(other.arr), frontIndex(other.frontIndex), rearIndex(other.rearIndex), cap(other.cap), count(other.count){
    other.arr = nullptr;
    other.cap = other.count = other.frontIndex = other.rearIndex = 0;
}

/*------------------- COPY ASSIGNMENT -------------------*/
template <typename T>
CQueue<T>& CQueue<T>::operator=(const CQueue& other) {
    if (this == &other)
        return *this;

    delete[] arr;
    arr = new T[other.cap];

    for (size_t i = 0; i < other.cap; i++)
        arr[i] = other.arr[i];

    cap = other.cap;
    count = other.count;
    frontIndex = other.frontIndex;
    rearIndex = other.rearIndex;

    return *this;
}

/*------------------- MOVE ASSIGNMENT -------------------*/
template <typename T>
CQueue<T>& CQueue<T>::operator=(CQueue&& other) noexcept {
    if (this == &other)
        return *this;

    delete[] arr;

    arr = other.arr;
    frontIndex = other.frontIndex;
    rearIndex = other.rearIndex;
    cap = other.cap;
    count = other.count;

    other.arr = nullptr;
    other.cap = other.count = other.frontIndex = other.rearIndex = 0;

    return *this;
}

/*------------------- BASIC QUERIES -------------------*/
template <typename T>
bool CQueue<T>::empty() const { return count == 0; }

template <typename T>
size_t CQueue<T>::size() const { return count; }

template <typename T>
size_t CQueue<T>::capacity() const { return cap; }

/*------------------- PUSH (Lvalue) -------------------*/
template <typename T>
void CQueue<T>::push(const T& value) {
    if (count == cap)
        resize(cap * 2);

    arr[rearIndex] = value;
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

/*------------------- PUSH (Rvalue) -------------------*/
template <typename T>
void CQueue<T>::push(T&& value) {
    if (count == cap)
        resize(cap * 2);

    arr[rearIndex] = std::move(value);
    rearIndex = (rearIndex + 1) % cap;
    count++;
}

/*------------------- POP -------------------*/
template <typename T>
void CQueue<T>::pop() {
    if (empty())
        throw std::underflow_error("Queue is empty");

    frontIndex = (frontIndex + 1) % cap;
    count--;

    if (count > 0 && count <= cap / 4 && cap > 1)  //count > 0                 -----Never shrink to 0 capacity.
        resize(cap / 2);                           //count <= cap / 4          -----Shrink only when queue becomes 1/4th full or less. This avoids oscillation (grow → shrink → grow → shrink). – When queue becomes 100% full → capacity doubles, – When queue becomes ≤25% full → capacity halves
}                                                  //cap > 1                   -----Minimum capacity allowed is 1, so don’t shrink further.

/*------------------- FRONT -------------------*/
template <typename T>
T& CQueue<T>::front() {
    if (empty()) throw std::underflow_error("Queue is empty");
    return arr[frontIndex];
}

template <typename T>
const T& CQueue<T>::front() const {
    if (empty()) throw std::underflow_error("Queue is empty");
    return arr[frontIndex];
}

/*------------------- BACK -------------------*/
template <typename T>
T& CQueue<T>::back() {
    if (empty()) throw std::underflow_error("Queue is empty");
    size_t idx = (rearIndex == 0 ? cap - 1 : rearIndex - 1);
    return arr[idx];
}

template <typename T>
const T& CQueue<T>::back() const {
    if (empty()) throw std::underflow_error("Queue is empty");
    size_t idx = (rearIndex == 0 ? cap - 1 : rearIndex - 1);
    return arr[idx];
}

/*------------------- DISPLAY -------------------*/
template <typename T>
void CQueue<T>::Display() const {
    for (size_t i = 0; i < count; i++)
        std::cout << arr[(frontIndex + i) % cap] << " ";
    std::cout << "\n";
}


int main() {
    try {
        CQueue<int> q;

        std::cout << "=== Testing Push ===\n";
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);

        q.Display();
        std::cout << "Size: " << q.size() << "  Cap: " << q.capacity() << "\n\n";

        std::cout << "=== Testing Rvalue Push ===\n";
        q.push(50);
        q.push(60);

        q.Display();
        std::cout << "Size: " << q.size() << "  Cap: " << q.capacity() << "\n\n";

        std::cout << "Front: " << q.front() << "\n";
        std::cout << "Back : " << q.back() << "\n\n";

        std::cout << "=== Testing Pop + Shrink ===\n";
        q.pop();
        q.pop();
        q.pop();

        q.Display();
        std::cout << "Size: " << q.size() << "  Cap: " << q.capacity() << "\n\n";

        std::cout << "=== Testing Copy Constructor ===\n";
        CQueue<int> q2 = q;
        q2.Display();

        std::cout << "=== Testing Move Constructor ===\n";
        CQueue<int> q3 = std::move(q2);
        q3.Display();

        std::cout << "=== Testing Copy Assignment ===\n";
        CQueue<int> a;
        a = q3;
        a.Display();

        std::cout << "=== Testing Move Assignment ===\n";
        CQueue<int> b;
        b = std::move(a);
        b.Display();

        std::cout << "=== Testing Exception ===\n";
        CQueue<int> ex;
        ex.pop(); // throws

    } catch (const std::exception& e) {
        std::cerr << "Exception Caught: " << e.what() << "\n";
    }

    return 0;
}
/*
=== Testing Push ===
10 20 30 40 
Size: 4  Cap: 4

=== Testing Rvalue Push ===
10 20 30 40 50 60 
Size: 6  Cap: 8

Front: 10
Back : 60

=== Testing Pop + Shrink ===
40 50 60 
Size: 3  Cap: 8

=== Testing Copy Constructor ===
40 50 60 
=== Testing Move Constructor ===
40 50 60 
=== Testing Copy Assignment ===
40 50 60 
=== Testing Move Assignment ===
40 50 60 
=== Testing Exception ===
Exception Caught: Queue is empty
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

























