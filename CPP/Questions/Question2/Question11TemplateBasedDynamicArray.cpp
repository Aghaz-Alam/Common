/* 
Question 11: Template-Based Dynamic Array

Write a C++ template class DynamicArray<T> that supports adding elements, getting elements by index, and resizing automatically when full.
Implement: push_back(), operator[], size(), capacity().
Ensure deep copy using copy constructor and assignment operator.

Sample Input:
DynamicArray<int> arr;
arr.push_back(10);
arr.push_back(20);
cout << arr[1];


Expected Output:
20
*/


Question 11: Template-Based Dynamic Array with:

✔ push_back()
✔ operator[]
✔ size()
✔ capacity()
✔ Auto-resizing
✔ Deep copy (copy constructor + assignment operator)

Matches your expected output.

#include <iostream>
using namespace std;

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t _size;
    size_t _capacity;

    // Resizes array when full
    void resize() {
        _capacity *= 2;
        T* newData = new T[_capacity];

        for (size_t i = 0; i < _size; i++)
            newData[i] = data[i];

        delete[] data;
        data = newData;
    }

public:
    // Constructor
    DynamicArray(size_t cap = 2) : _size(0), _capacity(cap) {
        data = new T[_capacity];
    }

    // Copy Constructor (Deep Copy)
    DynamicArray(const DynamicArray &other) {
        _size = other._size;
        _capacity = other._capacity;
        data = new T[_capacity];
        for (size_t i = 0; i < _size; i++)
            data[i] = other.data[i];
    }

    // Assignment Operator (Deep Copy)
    DynamicArray& operator=(const DynamicArray &other) {
        if (this != &other) {
            delete[] data;

            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            for (size_t i = 0; i < _size; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Add element to array
    void push_back(const T& value) {
        if (_size == _capacity)
            resize();
        data[_size++] = value;
    }

    // Element access
    T& operator[](size_t index) {
        return data[index];
    }

    // Get size
    size_t size() const {
        return _size;
    }
    
    // Get capacity
    size_t capacity() const {
        return _capacity;
    }
};
int main() {
    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    cout << arr[1];  // Expected Output: 20
  return 0;
}
/* 
Expected Output
20
*/