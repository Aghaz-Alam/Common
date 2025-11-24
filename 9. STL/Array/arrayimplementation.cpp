Function Inside Class
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
    // constructors
    MyArray() = default;

    // element access
    constexpr T& operator[](size_t index) noexcept { 
        return arr[index]; 
    }

    constexpr const T& operator[](size_t index) const noexcept {  
        return arr[index];
    }

    // at() performs bounds-check
    T& at(size_t index) {
        if (index >= N) throw std::out_of_range("Index out of range");
        return arr[index];
    }

    const T& at(size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of range");
        return arr[index];
    }

    // capacity
    constexpr size_t size() const noexcept { 
        return N; 
    }

    // modifiers
    void fill(const T& value) {
        for (size_t i = 0; i < N; ++i) arr[i] = value;
    }

    // pointer access
    constexpr T* data() noexcept { return arr; }
    constexpr const T* data() const noexcept { return arr; }

    // iterators
    constexpr T* begin() noexcept { return arr; }
    constexpr const T* begin() const noexcept { return arr; }

    constexpr T* end() noexcept { return arr + N; }
    constexpr const T* end() const noexcept { return arr + N; }
};

int main() {

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


    // Test at() with exception
    try {
        cout << arrStr.at(10) << endl; // out of range
    }
    catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
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
*/


/* 
✅ Corrections & Improvements
❌ operator[] should NOT throw
In the Standard Library, operator[] NEVER throws — only .at() performs bounds checking.
You added a throw inside operator[], which is fine for learning, but not how std::array works.

✔ operator[] should allow UB (undefined behavior) if out-of-bounds
T& operator[](size_t index) { return arr[index]; }

❌ data() should return pointer, not array
Your code correctly returns pointer (arr decays to pointer). Good.

❌ You forgot constexpr
std::array supports constexpr for almost everything.

❌ You missed structured bindings support (tuple_size, tuple_element)
Not required but important if you want to mimic full std::array.


*/




Function Outside Class
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

    // declarations
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
    try {
        cout << arrStr.at(10) << endl;
    }
    catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
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
Exception caught: Index out of range
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














//Dynamic Array using Rule 5
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T, size_t N>
class MyArray {
  private:
    T* arr;  // dynamically allocated block

  public
    // ---------- 1. Constructor ----------
    MyArray():arr(new T[N]) {}   // default-initialize all elements

    // ---------- 2. Destructor ----------
    ~MyArray() {
        delete[] arr;
    }

    // ---------- 3. Copy Constructor ----------
    MyArray(const MyArray& other): arr(new T[N]) {
        for (size_t i = 0; i < N; i++)
            arr[i] = other.arr[i];
    }

    // ---------- 4. Copy Assignment ----------
    MyArray& operator=(const MyArray& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i < N; i++)
            arr[i] = other.arr[i];

        return *this;
    }

    // ---------- 5. Move Constructor ----------
    MyArray(MyArray&& other) noexcept : arr(other.arr){
        other.arr = nullptr;
    }

    // ---------- 6. Move Assignment ----------
    MyArray& operator=(MyArray&& other) noexcept {
        if (this == &other) return *this;

        delete[] arr;            // delete current data
        arr = other.arr;         // steal pointer
        other.arr = nullptr;     // reset source

        return *this;
    }


    // ---------- Element Access ----------
    T& operator[](size_t index) noexcept {
        return arr[index];
    }

    const T& operator[](size_t index) const noexcept {
        return arr[index];
    }

    T& at(size_t index) {
        if (index >= N) throw out_of_range("Index out of range");
        return arr[index];
    }

    const T& at(size_t index) const {
        if (index >= N) throw out_of_range("Index out of range");
        return arr[index];
    }

    // ---------- Capacity ----------
    constexpr size_t size() const noexcept {
        return N;
    }

    // ---------- Modifiers ----------
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++)
            arr[i] = value;
    }

    // ---------- Data Access ----------
    T* data() noexcept { return arr; }
    const T* data() const noexcept { return arr; }

    // ---------- Iterators ----------
    T* begin() noexcept { return arr; }
    const T* begin() const noexcept { return arr; }

    T* end() noexcept { return arr + N; }
    const T* end() const noexcept { return arr + N; }
};


// -------------------------- MAIN ------------------------------

int main() {

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
    try {
        cout << arrStr.at(10) << endl;
    }
    catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
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
Exception caught: Index out of range
*/