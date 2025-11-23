//std::array internal implementation with template
#include <iostream>
#include <stdexcept> // For exception handling
using namespace std;
template <typename T, size_t N>
class MyArray {
  private:
    T arr[N]; // Fixed-size array

  public:
    // Default constructor
    MyArray() = default;

    // Element access operator[]
    T& operator[](size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& operator[](size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // at() provides bounds-checked access
    T& at(size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& at(size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // size() returns the fixed size of the array
    size_t size() const {
        return N;
    }

    // Custom fill() function to assign a value to every element (without std::fill)
    void fill(const T& value) {
        for (size_t i = 0; i < N; ++i) {
            arr[i] = value;
        }
    }

    // Data access for the underlying array (for interoperability with C-style APIs)
    T* data() {
        return arr;
    }

    const T* data() const {
        return arr;
    }

    // Begin and end iterator support (for STL compatibility)
    T* begin() {
        return arr;
    }

    const T* begin() const {
        return arr;
    }

    T* end() {
        return arr + N;
    }

    const T* end() const {
        return arr + N;
    }
};

int main() {
    MyArray<int, 5> arr;
    arr.fill(10); // Fill the array with value 10

    cout << "Array size: " << arr.size() << std::endl;
    cout << "Array elements: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr[2] = 20; // Modify an element at index 2
    cout << "Modified Array elements: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    MyArray<string, 5> arrStr;
    arrStr.fill("Apple"); // Fill the array with value 10

    cout << "Array size: " << arrStr.size() << std::endl;
    cout << "Array elements: ";
    for (size_t i = 0; i < arrStr.size(); ++i) {
        cout << arrStr[i] << " ";
    }
    cout << endl;

    arrStr[2] = "Mango"; // Modify an element at index 2
    cout << "Modified Array elements: ";
    for (size_t i = 0; i < arrStr.size(); ++i) {
        cout << arrStr[i] << " ";
    }
    cout << endl;

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