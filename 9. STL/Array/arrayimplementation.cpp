//std::array internal implementation with template
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

//std::array internal implementation with template
template <typename T, size_t N>
class MyArray {
private:
    T arr[N];

public:
    MyArray() = default;

    constexpr T& operator[](size_t index) noexcept;
    constexpr const T& operator[](size_t index) const noexcept;

    T& at(size_t index);
    const T& at(size_t index) const;

    constexpr size_t size() const noexcept;

    void fill(const T& value);

    constexpr T* data() noexcept;
    constexpr const T* data() const noexcept;

    constexpr T* begin() noexcept;
    constexpr const T* begin() const noexcept;

    constexpr T* end() noexcept;
    constexpr const T* end() const noexcept;
};


// ---------------- MEMBER DEFINITIONS OUTSIDE CLASS ----------------

// operator[]
template <typename T, size_t N>
constexpr T& MyArray<T, N>::operator[](size_t index) noexcept {
    return arr[index];
}

template <typename T, size_t N>
constexpr const T& MyArray<T, N>::operator[](size_t index) const noexcept {
    return arr[index];
}

// at()
template <typename T, size_t N>
T& MyArray<T, N>::at(size_t index) {
    if (index >= N) throw std::out_of_range("Index out of range");
    return arr[index];
}

template <typename T, size_t N>
const T& MyArray<T, N>::at(size_t index) const {
    if (index >= N) throw std::out_of_range("Index out of range");
    return arr[index];
}

// size()
template <typename T, size_t N>
constexpr size_t MyArray<T, N>::size() const noexcept {
    return N;
}

// fill()
template <typename T, size_t N>
void MyArray<T, N>::fill(const T& value) {
    for (size_t i = 0; i < N; ++i)
        arr[i] = value;
}

// data()
template <typename T, size_t N>
constexpr T* MyArray<T, N>::data() noexcept {
    return arr;
}

template <typename T, size_t N>
constexpr const T* MyArray<T, N>::data() const noexcept {
    return arr;
}

// iterators
template <typename T, size_t N>
constexpr T* MyArray<T, N>::begin() noexcept {
    return arr;
}

template <typename T, size_t N>
constexpr const T* MyArray<T, N>::begin() const noexcept {
    return arr;
}

template <typename T, size_t N>
constexpr T* MyArray<T, N>::end() noexcept {
    return arr + N;
}

template <typename T, size_t N>
constexpr const T* MyArray<T, N>::end() const noexcept {
    return arr + N;
}


// -------------------------- MAIN ------------------------------

int main() {

    try {
        // Test with int
        MyArray<int, 5> arr;
        arr.fill(10);

        cout << "Array size: " << arr.size() << endl;
        cout << "Array elements: ";
        for (size_t i = 0; i < arr.size(); ++i)
            cout << arr[i] << " ";
        cout << endl;

        arr[2] = 20;
        cout << "Modified Array elements: ";
        for (auto v : arr)
            cout << v << " ";
        cout << endl;


        // Test with std::string
        MyArray<string, 5> arrStr;
        arrStr.fill("Apple");

        cout << "Array size: " << arrStr.size() << endl;
        cout << "Array elements: ";
        for (auto& s : arrStr)
            cout << s << " ";
        cout << endl;

        arrStr[2] = "Mango";
        cout << "Modified Array elements: ";
        for (auto& s : arrStr)
            cout << s << " ";
        cout << endl;

        // Test at() exception
        cout << arrStr.at(10) << endl;   // out-of-range → will throw

    }
    catch (const std::out_of_range& e) {
        cout << "Out_of_range exception caught: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "General exception caught: " << e.what() << endl;
    }

    return 0;
}
/*
Array size: 5
Array elements: 10 10 10 10 10 
Modified Array elements: 10 10 20 10 10 
Array size: 5
Array elements: Apple Apple Apple Apple Apple 
Modified Array elements: Apple Apple Mango Apple Apple 
Out_of_range exception caught: Index out of range
*/

/* 
✅ Answer: NO — Rule of Five is not required here
Your class does not manage any dynamic memory using new, nor does it acquire any resource externally.
T arr[N];

This is a fixed-size built-in array stored inside the object.
Therefore:
No heap allocation
No manual release
No pointer ownership
No custom copying or moving required
The compiler-generated operations are perfectly correct.

✔ Correct concept: Rule of Zero
This class is a textbook example where Rule of Zero applies:
If a class does not own any resource (memory, file handle, socket, mutex lock, etc),
you do not manually implement destructor, copy/move operations.

Why Rule of Five is unnecessary?
Because default operations already do the right thing:
Copy constructor: copies all elements in arr[]
Copy assignment: assigns all elements
Move constructor: moves all elements (cheap for ints, efficient for std::string)
Destructor: default destructor is correct (no dynamic memory)
*/














// Dynamic Array using Rule of 5
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T, size_t N>
class MyArray {
  private:
    T* arr;

  public:
    // Constructors & Rule of Five
    MyArray();                              
    ~MyArray();                             
    MyArray(const MyArray& other);          
    MyArray& operator=(const MyArray& other); 
    MyArray(MyArray&& other) noexcept;      
    MyArray& operator=(MyArray&& other) noexcept;

    // Element Access
    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;

    T& at(size_t index);
    const T& at(size_t index) const;

    // Capacity
    constexpr size_t size() const noexcept;

    // Modifiers
    void fill(const T& value);

    // Data Access
    T* data() noexcept;
    const T* data() const noexcept;

    // Iterators
    T* begin() noexcept;
    const T* begin() const noexcept;

    T* end() noexcept;
    const T* end() const noexcept;
};

// ---------- 1. Default Constructor ----------
template <typename T, size_t N>
MyArray<T, N>::MyArray() : arr(new T[N]) {}

// ---------- 2. Destructor ----------
template <typename T, size_t N>
MyArray<T, N>::~MyArray() {
    delete[] arr;
}

// ---------- 3. Copy Constructor ----------
template <typename T, size_t N>
MyArray<T, N>::MyArray(const MyArray& other) : arr(new T[N]) {
    for (size_t i = 0; i < N; i++)
        arr[i] = other.arr[i];
}

// ---------- 4. Copy Assignment ----------
template <typename T, size_t N>
MyArray<T, N>& MyArray<T, N>::operator=(const MyArray& other) {
    if (this == &other) return *this;
    for (size_t i = 0; i < N; i++)
        arr[i] = other.arr[i];
    return *this;
}

// ---------- 5. Move Constructor ----------
template <typename T, size_t N>
MyArray<T, N>::MyArray(MyArray&& other) noexcept : arr(other.arr) {
    other.arr = nullptr;
}

// ---------- 6. Move Assignment ----------
template <typename T, size_t N>
MyArray<T, N>& MyArray<T, N>::operator=(MyArray&& other) noexcept {
    if (this == &other) return *this;
    delete[] arr;
    arr = other.arr;
    other.arr = nullptr;
    return *this;
}

// ---------- Element Access ----------
template <typename T, size_t N>
T& MyArray<T, N>::operator[](size_t index) noexcept {
    return arr[index];
}

template <typename T, size_t N>
const T& MyArray<T, N>::operator[](size_t index) const noexcept {
    return arr[index];
}

template <typename T, size_t N>
T& MyArray<T, N>::at(size_t index) {
    if (index >= N) throw out_of_range("Index out of range");
    return arr[index];
}

template <typename T, size_t N>
const T& MyArray<T, N>::at(size_t index) const {
    if (index >= N) throw out_of_range("Index out of range");
    return arr[index];
}

// ---------- Capacity ----------
template <typename T, size_t N>
constexpr size_t MyArray<T, N>::size() const noexcept {
    return N;
}

// ---------- Modifiers ----------
template <typename T, size_t N>
void MyArray<T, N>::fill(const T& value) {
    for (size_t i = 0; i < N; i++)
        arr[i] = value;
}

// ---------- Data Access ----------
template <typename T, size_t N>
T* MyArray<T, N>::data() noexcept { return arr; }

template <typename T, size_t N>
const T* MyArray<T, N>::data() const noexcept { return arr; }

// ---------- Iterators ----------
template <typename T, size_t N>
T* MyArray<T, N>::begin() noexcept { return arr; }

template <typename T, size_t N>
const T* MyArray<T, N>::begin() const noexcept { return arr; }

template <typename T, size_t N>
T* MyArray<T, N>::end() noexcept { return arr + N; }

template <typename T, size_t N>
const T* MyArray<T, N>::end() const noexcept { return arr + N; }


int main() {

    try {
        cout << "===== Testing int array =====\n";

        MyArray<int, 5> arr;
        arr.fill(10);

        cout << "Array size: " << arr.size() << endl;
        cout << "Array elements: ";
        for (size_t i = 0; i < arr.size(); ++i)
            cout << arr[i] << " ";
        cout << endl;

        arr[2] = 20;

        cout << "Modified Array elements: ";
        for (auto v : arr)
            cout << v << " ";
        cout << endl;
    }
    catch (const exception& e) {
        cout << "Error in int array block: " << e.what() << endl;
    }

    try {
        cout << "\n===== Testing string array =====\n";

        MyArray<string, 5> arrStr;
        arrStr.fill("Apple");

        cout << "Array size: " << arrStr.size() << endl;
        cout << "Array elements: ";
        for (auto& s : arrStr)
            cout << s << " ";
        cout << endl;

        arrStr[2] = "Mango";

        cout << "Modified Array elements: ";
        for (auto& s : arrStr)
            cout << s << " ";
        cout << endl;

        // Test at() exception
        cout << "\nTesting out-of-range access...\n";
        cout << arrStr.at(10) << endl;   // will throw
    }
    catch (const out_of_range& e) {
        cout << "out_of_range caught: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "General exception: " << e.what() << endl;
    }

    return 0;
}
/*
===== Testing int array =====
Array size: 5
Array elements: 10 10 10 10 10 
Modified Array elements: 10 10 20 10 10 

===== Testing string array =====
Array size: 5
Array elements: Apple Apple Apple Apple Apple 
Modified Array elements: Apple Apple Mango Apple Apple 

Testing out-of-range access...
out_of_range caught: Index out of range
*/