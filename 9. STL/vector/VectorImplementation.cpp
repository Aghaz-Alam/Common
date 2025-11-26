//fixed sized vector
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T, size_t CAP>
class MyVector {
private:
    T* arr;
    size_t n;

public:
    // Constructor
    MyVector();

    // Destructor
    ~MyVector();

    // Copy Constructor
    MyVector(const MyVector& other);

    // Copy Assignment
    MyVector& operator=(const MyVector& other);

    // Move Constructor
    MyVector(MyVector&& other) noexcept;

    // Move Assignment
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const T& value);
    void pop_back();

    T& operator[](size_t index);
    T& at(size_t index);

    size_t size() const;
    size_t capacity() const;

    void clear();
    void Display() const;
};

/* =======================
      DEFINITIONS
   ======================= */

template<typename T, size_t CAP>
MyVector<T, CAP>::MyVector() : arr(new T[CAP]), n(0) {}

template<typename T, size_t CAP>
MyVector<T, CAP>::~MyVector() {
    delete[] arr;
}

template<typename T, size_t CAP>
MyVector<T, CAP>::MyVector(const MyVector& other)
    : arr(new T[CAP]), n(other.n)
{
    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];
}

template<typename T, size_t CAP>
MyVector<T, CAP>& MyVector<T, CAP>::operator=(const MyVector& other)
{
    if (this == &other)
        return *this;

    n = other.n;
    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];

    return *this;
}

template<typename T, size_t CAP>
MyVector<T, CAP>::MyVector(MyVector&& other) noexcept
    : arr(other.arr), n(other.n)
{
    other.arr = nullptr;
    other.n = 0;
}

template<typename T, size_t CAP>
MyVector<T, CAP>& MyVector<T, CAP>::operator=(MyVector&& other) noexcept
{
    if (this != &other) {
        delete[] arr;

        arr = other.arr;
        n = other.n;

        other.arr = nullptr;
        other.n = 0;
    }
    return *this;
}

template<typename T, size_t CAP>
void MyVector<T, CAP>::push_back(const T& value)
{
    if (n == CAP)
        throw runtime_error("push_back overflow: Vector is full");

    arr[n++] = value;
}

template<typename T, size_t CAP>
void MyVector<T, CAP>::pop_back()
{
    if (n == 0)
        throw runtime_error("pop_back underflow: Vector is empty");
    n--;
}

template<typename T, size_t CAP>
T& MyVector<T, CAP>::operator[](size_t index)
{
    if (index >= n)
        throw out_of_range("operator[] index out of range");
    return arr[index];
}

template<typename T, size_t CAP>
T& MyVector<T, CAP>::at(size_t index)
{
    if (index >= n)
        throw out_of_range("at() index out of range");
    return arr[index];
}

template<typename T, size_t CAP>
size_t MyVector<T, CAP>::size() const {
    return n;
}

template<typename T, size_t CAP>
size_t MyVector<T, CAP>::capacity() const {
    return CAP;
}

template<typename T, size_t CAP>
void MyVector<T, CAP>::clear() {
    n = 0;
}

template<typename T, size_t CAP>
void MyVector<T, CAP>::Display() const
{
    for (size_t i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

/* =======================
        MAIN TEST
   ======================= */

int main() {
    try {
        MyVector<int,5> v;

        v.push_back(10);
        v.push_back(20);
        v.push_back(30);
        cout << "After pushes: "; v.Display();
        cout << "Size: " << v.size() << " Capacity: " << v.capacity() << "\n\n";

        cout << "POP...\n";
        v.pop_back();
        cout << "After pop: "; v.Display();
        cout << "Size: " << v.size() << " Capacity: " << v.capacity() << "\n\n";

        cout << "---COPY CTOR TEST---\n";
        MyVector<int,5> v2 = v;
        cout << "v2: "; v2.Display();

        cout << "---MOVE CTOR TEST---\n";
        MyVector<int,5> v3 = std::move(v2);
        cout << "v3: "; v3.Display();

        cout << "---COPY ASSIGNMENT TEST---\n";
        MyVector<int,5> v4;
        v4 = v;
        cout << "v4 after copy = v: "; 
        v4.Display();

        cout << "---MOVE ASSIGNMENT TEST---\n";
        MyVector<int,5> v5;
        v5 = std::move(v4);
        cout << "v5 after move = std::move(v4): "; 
        v5.Display();

        cout << "\nFilling to capacity...\n";
        v.push_back(40);
        v.push_back(50);
        v.push_back(60);
        cout << "After filling: "; v.Display();
        cout << "Size: " << v.size() << " Capacity: " << v.capacity() << "\n\n";

        cout << "Attempting one more push (should throw)...\n";
        v.push_back(70);

    } catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
/*
After pushes: 10 20 30 
Size: 3 Capacity: 5

POP...
After pop: 10 20 
Size: 2 Capacity: 5

---COPY CTOR TEST---
v2: 10 20 
---MOVE CTOR TEST---
v3: 10 20 
---COPY ASSIGNMENT TEST---
v4 after copy = v: 10 20 
---MOVE ASSIGNMENT TEST---
v5 after move = std::move(v4): 10 20 

Filling to capacity...
After filling: 10 20 40 50 60 
Size: 5 Capacity: 5

Attempting one more push (should throw)...
Exception caught: push_back overflow: Vector is full
*/




//vector implementation dynamically grow and shrink
#include <iostream>
#include <stdexcept>
using namespace std;

class MyVector {
  private:
    int* arr;
    size_t n;
    size_t cap;

    void resize(size_t newCap);

  public:
    MyVector();

    // Rule of Five
    ~MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const int& value);
    void pop_back();

    int& operator[](size_t index);
    int& at(size_t index);

    size_t size() const;
    size_t capacity() const;

    void clear();
    void Display() const;
};

// Constructor
MyVector::MyVector() : arr(nullptr), n(0), cap(0) {}

MyVector::~MyVector() {
    delete[] arr;
}

// Copy Constructor
MyVector::MyVector(const MyVector& other) : n(other.n), cap(other.cap) {
    arr = new int[cap];
    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];
}

// Copy Assignment
MyVector& MyVector::operator=(const MyVector& other) {
    if (this == &other) return *this;

    delete[] arr;

    n = other.n;
    cap = other.cap;

    arr = new int[cap];
    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];

    return *this;
}

// Move Constructor
MyVector::MyVector(MyVector&& other) noexcept
    : arr(other.arr), n(other.n), cap(other.cap) {

    other.arr = nullptr;
    other.n = 0;
    other.cap = 0;
}

// Move Assignment
MyVector& MyVector::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;

        arr = other.arr;
        n = other.n;
        cap = other.cap;

        other.arr = nullptr;
        other.n = 0;
        other.cap = 0;
    }
    return *this;
}

// resize()
void MyVector::resize(size_t newCap) {
    if (newCap < n) newCap = n;
    if (newCap == 0) newCap = 1;

    int* newArr = new int[newCap];

    for (size_t i = 0; i < n; ++i)
        newArr[i] = arr[i];

    delete[] arr;
    arr = newArr;
    cap = newCap;
}

// push_back
void MyVector::push_back(const int& value) {
    if (n == cap) {
        size_t newCap = (cap == 0 ? 1 : cap * 2);
        resize(newCap);
    }
    arr[n++] = value;
}

// pop_back
void MyVector::pop_back() {
    if (n == 0)
        throw runtime_error("pop_back on empty vector");

    n--;

    if (n > 0 && n <= cap / 4 && cap > 1)
        resize(cap / 2);
}

// operator[]
int& MyVector::operator[](size_t index) {
    if (index >= n)
        throw out_of_range("operator[] index out of range");
    return arr[index];
}

// at() with exception
int& MyVector::at(size_t index) {
    if (index >= n)
        throw out_of_range("at() index out of range");
    return arr[index];
}

size_t MyVector::size() const { return n; }
size_t MyVector::capacity() const { return cap; }

void MyVector::clear() {
    n = 0;
    resize(1);
}

void MyVector::Display() const {
    for (size_t i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    try {
        cout << "---Original Vector---\n";
        MyVector v;
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);
        v.Display();

        cout << "\n---Copy Constructor Test---\n";
        MyVector v2 = v;
        v2.Display();

        cout << "\n---Copy Assignment Test---\n";
        MyVector v3;
        v3 = v;
        v3.Display();

        cout << "\n---Move Constructor Test---\n";
        MyVector v4 = std::move(v2);
        v4.Display();
        cout << "v2 size after move = " << v2.size() << "\n";

        cout << "\n---Move Assignment Test---\n";
        MyVector v5;
        v5 = std::move(v3);
        v5.Display();
        cout << "v3 size after move = " << v3.size() << "\n";

        cout << "\n---Exception Test: calling at(10)--- \n";
        cout << v.at(10);  // Should throw

    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
/*
---Original Vector---
10 20 30 

---Copy Constructor Test---
10 20 30 

---Copy Assignment Test---
10 20 30 

---Move Constructor Test---
10 20 30 
v2 size after move = 0

---Move Assignment Test---
10 20 30 
v3 size after move = 0

---Exception Test: calling at(10)--- 
Exception caught: at() index out of range
*/








//Vector implementation without template shrink and grow dynamically
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

class MyVector {
  private:
    int* arr;
    size_t n;
    size_t cap;

    void resize(size_t newCap);

  public:
    MyVector();
    ~MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const int& value);
    void push_back(int&& value);

    template<typename... Args>
    void emplace_back(Args&&... args);

    void pop_back();

    int& operator[](size_t index);
    int& at(size_t index);

    size_t size() const { return n; }
    size_t capacity() const { return cap; }

    void clear();
    void Display() const;
};

// Constructor
MyVector::MyVector() : arr(nullptr), n(0), cap(0) {}

// Destructor
MyVector::~MyVector() {
    delete[] arr;
}

// Copy Constructor
MyVector::MyVector(const MyVector& other)
    : n(other.n), cap(other.cap)
{
    arr = (cap == 0 ? nullptr : new int[cap]);
    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];
}

// Copy Assignment
MyVector& MyVector::operator=(const MyVector& other) {
    if (this == &other) return *this;

    delete[] arr;

    n = other.n;
    cap = other.cap;
    arr = (cap == 0 ? nullptr : new int[cap]);

    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];

    return *this;
}

// Move Constructor
MyVector::MyVector(MyVector&& other) noexcept
    : arr(other.arr), n(other.n), cap(other.cap)
{
    other.arr = nullptr;
    other.n = 0;
    other.cap = 0;
}

// Move Assignment
MyVector& MyVector::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;

        arr = other.arr;
        n = other.n;
        cap = other.cap;

        other.arr = nullptr;
        other.n = 0;
        other.cap = 0;
    }
    return *this;
}

// resize()
void MyVector::resize(size_t newCap) {
    if (newCap < n) newCap = n;
    if (newCap == 0) newCap = 1;

    int* newArr = new int[newCap];
    for (size_t i = 0; i < n; ++i)
        newArr[i] = std::move(arr[i]);

    delete[] arr;
    arr = newArr;
    cap = newCap;
}

// push_back (lvalue)
void MyVector::push_back(const int& value) {
    if (n == cap)
        resize(cap == 0 ? 1 : cap * 2);

    arr[n++] = value;
}

// push_back (rvalue)
void MyVector::push_back(int&& value) {
    if (n == cap)
        resize(cap == 0 ? 1 : cap * 2);

    arr[n++] = std::move(value);
}

// emplace_back
template<typename... Args>
void MyVector::emplace_back(Args&&... args) {
    if (n == cap)
        resize(cap == 0 ? 1 : cap * 2);

    new (&arr[n]) int(std::forward<Args>(args)...);
    n++;
}

// pop_back
void MyVector::pop_back() {
    if (n == 0) throw runtime_error("pop_back on empty vector");

    n--;
    if (cap > 1 && n <= cap / 4)
        resize(cap / 2);
}

// operator[]
int& MyVector::operator[](size_t index) {
    if (index >= n) throw out_of_range("operator[] index out of range");
    return arr[index];
}

// at()
int& MyVector::at(size_t index) {
    if (index >= n) throw out_of_range("at index out of range");
    return arr[index];
}

// clear()
void MyVector::clear() {
    n = 0;
    resize(1);
}

// Display
void MyVector::Display() const {
    for (size_t i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}


// MAIN - Fully Restored Output
int main() {
    try {
        MyVector v;

        cout << "--push_back (lvalue)--\n";
        int a = 100;
        v.push_back(a);
        v.Display();
        cout << "Size: " << v.size() << "\nCapacity: " << v.capacity() << "\n";

        cout << "\n--After adding one element using push_back (rvalue)--\n";
        int x = 200;
        v.push_back(std::move(x));
        v.Display();
        cout << "Size: " << v.size() << "\nCapacity: " << v.capacity() << "\n";

        cout << "\n--emplace_back--\n";
        v.emplace_back(300);
        v.emplace_back(400);
        v.emplace_back(500);
        v.Display();
        cout << "Size: " << v.size() << "\nCapacity: " << v.capacity() << "\n";

        cout << "\n--Using operator[]--\n";
        cout << "Element at index 2:" << v[2] << "\n";

        cout << "--Using at()--\n";
        cout << "Element at index 2:" << v.at(2) << "\n";

        v.pop_back();
        v.pop_back();
        v.pop_back();
        cout << "\nVector Elements after pop_back: ";
        v.Display();
        cout << "Size: " << v.size() << "\nCapacity: " << v.capacity() << "\n";

        v.clear();
        cout << "\n--After clear--Size: " << v.size()
             << "\nCapacity: " << v.capacity() << "\n";

        MyVector v1;
        v1.push_back(100);

        cout << "\n---COPY CONSTRUCTOR TEST---\n";
        MyVector v2 = v1;
        cout<<"Vector Element: ";
        v2.Display();

        cout << "\n---COPY ASSIGNMENT TEST---\n";
        MyVector v3;
        v3 = v1;
        cout<<"Vector Element: ";
        v3.Display();

        cout << "\n---MOVE CONSTRUCTOR TEST---\n";
        MyVector v4 = std::move(v1);
        cout<<"Vector Elements: ";
        v4.Display();
        cout << "v1 size after move: " << v1.size() << "\n";

        cout << "\n---MOVE ASSIGNMENT TEST---\n";
        MyVector v5;
        v5 = std::move(v4);
        cout<<"Vector Elements: ";
        v5.Display();
        cout << "v4 size after move: " << v4.size() << "\n";

        cout << "\n--Trying to pop from empty vector--\n";
        v.pop_back(); // will throw

    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}
/*
--push_back (lvalue)--
100 
Size: 1
Capacity: 1

--After adding one element using push_back (rvalue)--
100 200 
Size: 2
Capacity: 2

--emplace_back--
100 200 300 400 500 
Size: 5
Capacity: 8

--Using operator[]--
Element at index 2:300
--Using at()--
Element at index 2:300

Vector Elements after pop_back: 100 200 
Size: 2
Capacity: 4

--After clear--Size: 0
Capacity: 1

---COPY CONSTRUCTOR TEST---
Vector Element: 100 

---COPY ASSIGNMENT TEST---
Vector Element: 100 

---MOVE CONSTRUCTOR TEST---
Vector Elements: 100 
v1 size after move: 0

---MOVE ASSIGNMENT TEST---
Vector Elements: 100 
v4 size after move: 0

--Trying to pop from empty vector--
Exception: pop_back on empty vector
*/




//Vector implementation with template shrink and grow dynamically
#include <iostream>
#include <stdexcept>
#include <utility>   // for std::move, std::forward
using namespace std;
template <typename T>
class MyVector {
  private:
    T* arr;
    size_t n;
    size_t cap;
    void resize(size_t newCap);

  public:
    MyVector();

    // Rule of Five
    ~MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const T& value);
    void push_back(T&& value);

    template<typename... Args>
    void emplace_back(Args&&... args);

    void pop_back();

    T& operator[](size_t index);
    T& at(size_t index);

    size_t size() const { return n; }
    size_t capacity() const { return cap; }

    void clear();
    void Display() const;
};


// Constructor
template <typename T>
MyVector<T>::MyVector() : arr(nullptr), n(0), cap(0) {}


// Destructor
template <typename T>
MyVector<T>::~MyVector() {
    delete[] arr;
}


// Copy Constructor
template <typename T>
MyVector<T>::MyVector(const MyVector& other)
    : n(other.n), cap(other.cap)
{
    arr = (cap == 0 ? nullptr : new T[cap]);
    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];
}


// Copy Assignment
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) return *this;

    delete[] arr;

    n = other.n;
    cap = other.cap;
    arr = (cap == 0 ? nullptr : new T[cap]);

    for (size_t i = 0; i < n; ++i)
        arr[i] = other.arr[i];

    return *this;
}


// Move Constructor
template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : arr(other.arr), n(other.n), cap(other.cap)
{
    other.arr = nullptr;
    other.n = 0;
    other.cap = 0;
}


// Move Assignment
template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;

        arr = other.arr;
        n = other.n;
        cap = other.cap;

        other.arr = nullptr;
        other.n = 0;
        other.cap = 0;
    }
    return *this;
}


// resize()
template <typename T>
void MyVector<T>::resize(size_t newCap) {
    if (newCap < n) newCap = n;
    if (newCap == 0) newCap = 1;

    T* newArr = new T[newCap];
    for (size_t i = 0; i < n; ++i)
        newArr[i] = std::move(arr[i]);

    delete[] arr;
    arr = newArr;
    cap = newCap;
}


// push_back lvalue
template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (n == cap)
        resize(cap == 0 ? 1 : cap * 2);

    arr[n++] = value;
}


// push_back rvalue
template <typename T>
void MyVector<T>::push_back(T&& value) {
    if (n == cap)
        resize(cap == 0 ? 1 : cap * 2);

    arr[n++] = std::move(value);
}


// emplace_back
template <typename T>
template <typename... Args>
void MyVector<T>::emplace_back(Args&&... args) {
    if (n == cap)
        resize(cap == 0 ? 1 : cap * 2);

    new (&arr[n]) T(std::forward<Args>(args)...);
    n++;
}


// pop_back
template <typename T>
void MyVector<T>::pop_back() {
    if (n == 0) throw runtime_error("pop_back on empty vector");

    n--; // Destroy element count

    if (cap > 1 && n <= cap / 4)
        resize(cap / 2);
}


// operator[]
template <typename T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= n) throw out_of_range("operator[] index out of range");
    return arr[index];
}


// at()
template <typename T>
T& MyVector<T>::at(size_t index) {
    if (index >= n) throw out_of_range("at index out of range");
    return arr[index];
}


// clear()
template <typename T>
void MyVector<T>::clear() {
    n = 0;
    resize(1);
}


// Display
template <typename T>
void MyVector<T>::Display() const {
    for (size_t i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    try {
        MyVector<int> v;

        cout << "--push_back (lvalue)--" << endl;
        int a = 100;
        v.push_back(a);
        cout << "Vector Elements lvalue: ";
        v.Display();

        cout << "Size: " << v.size() << endl;
        cout << "Capacity: " << v.capacity() << endl;


        cout << "\n--After adding one element using push_back (rvalue)--" << endl;
        int x = 200;
        v.push_back(std::move(x));
        cout << "Vector Elements rvalue: ";
        v.Display();

        cout << "Size: " << v.size() << endl;
        cout << "Capacity: " << v.capacity() << endl;


        cout << "\n--emplace_back--";
        v.emplace_back(300);
        v.emplace_back(400);
        v.emplace_back(500);

        cout << "\nVector Elements: ";
        v.Display();

        cout << "Size: " << v.size() << endl;
        cout << "Capacity: " << v.capacity() << endl;

        cout << "\n--Using operator[]--" << endl;
        cout << "Element at index 2:" << v[2];

        cout << "\n--Using at()--" << endl;
        cout << "Element at index 2:" << v.at(2) << endl;


        v.pop_back();
        v.pop_back();
        v.pop_back();
        cout << "\nVector Elements after pop_back: ";
        v.Display();

        cout << "Size: " << v.size() << endl;
        cout << "Capacity: " << v.capacity() << endl;


        v.clear();
        cout << "\n--After clear--";
        cout << "Size: " << v.size() << endl;
        cout << "Capacity: " << v.capacity() << endl;



        MyVector<int> v1;
        v1.push_back(100);


        cout << "\n---COPY CONSTRUCTOR TEST---\n";
        MyVector<int> v2 = v1;
        cout << "v2 elements (copied from v1): ";
        v2.Display();


        cout << "\n---COPY ASSIGNMENT TEST---\n";
        MyVector<int> v3;
        v3 = v1;
        cout << "v3 elements (assigned from v1): ";
        v3.Display();


        cout << "\n---MOVE CONSTRUCTOR TEST---\n";
        MyVector<int> v4 = std::move(v1);
        cout << "v4 elements (moved from v1): ";
        v4.Display();
        cout << "v1 size after move: " << v1.size() << endl;


        cout << "\n---MOVE ASSIGNMENT TEST---\n";
        MyVector<int> v5;
        v5 = std::move(v4);
        cout << "v5 elements (moved from v4): ";
        v5.Display();
        cout << "v4 size after move: " << v4.size() << endl;


        // FIXED crashing print
        cout << "\n--Trying to pop from empty vector--" << endl;
        cout.flush();   // ensure print happens BEFORE exception
        v.pop_back();   // throws

    } 
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }
}
/*
--push_back (lvalue)--
Vector Elements lvalue: 100 
Size: 1
Capacity: 1

--After adding one element using push_back (rvalue)--
Vector Elements rvalue: 100 200 
Size: 2
Capacity: 2

--emplace_back--
Vector Elements: 100 200 300 400 500 
Size: 5
Capacity: 8

--Using operator[]--
Element at index 2:300
--Using at()--
Element at index 2:300

Vector Elements after pop_back: 100 200 
Size: 2
Capacity: 4

--After clear--Size: 0
Capacity: 1

---COPY CONSTRUCTOR TEST---
v2 elements (copied from v1): 100 

---COPY ASSIGNMENT TEST---
v3 elements (assigned from v1): 100 

---MOVE CONSTRUCTOR TEST---
v4 elements (moved from v1): 100 
v1 size after move: 0

---MOVE ASSIGNMENT TEST---
v5 elements (moved from v4): 100 
v4 size after move: 0

--Trying to pop from empty vector--
Exception: pop_back on empty vector
*/