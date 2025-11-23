// Online C++ compiler to run C++ program online

//Correct Behavior: cap = (cap == 0) ? 1 : cap * 2
#include <iostream>
#include <stdexcept>
using namespace std;

class MyVector {
    int* arr;
    int n;   // Number of elements in the vector
    int cap; // Capacity of the vector
    
  public:
    // Constructor
    MyVector() : arr(nullptr), n(0), cap(0) {}

    // Method to add an element at the end of the vector
    void push_back(const int& val) {
        // If the current size is equal to capacity, we need to resize the array
        if (n == cap) {
            // If capacity is 0, initialize to 1, otherwise double the current capacity
            cap = (cap == 0) ? 1 : cap * 2;
            int* newArr = new int[cap];  // Create a new array with the new capacity

            // Copy existing elements into the new array
            for (int i = 0; i < n; ++i) {
                newArr[i] = arr[i];
            }

            // Delete the old array
            delete[] arr;
            arr = newArr;  // Point to the newly allocated array
        }
        arr[n++] = val;  // Insert the value at the end and increment the size
    }

    // Method to remove the last element from the vector (no return value)
    void pop_back() {
        if (n == 0) {
            throw runtime_error("pop_back called on an empty vector");
        }
        --n;  // Decrement the size (effectively removing the last element)
    }

    // Overload subscript operator for element access
    int& operator[](int i) {
        if (i >= n) {
            throw out_of_range("Index out of range");
        }
        return arr[i];
    }

    // Method to get the number of elements in the vector
    int size() const {
        return n;
    }

    // Method to get the current capacity of the vector
    int capacity() const {
        return cap;
    }

    // Method to clear the vector (reset the size to 0)
    void clear() {
        n = 0;
    }

    // Destructor to free dynamically allocated memory
    ~MyVector() {
        delete[] arr;
    }

    // Display elements of the vector
    void Display() const {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
};

int main() {
    MyVector v;

    // Adding elements to the vector
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    // Display size and capacity
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;

    // Display elements using operator[]
    cout << "Elements using operator[]: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    // Display elements using Display()
    cout << "Elements using Display(): ";
    v.Display();

    // Pop last element and display results
    v.pop_back();
    cout << "Size after pop_back: " << v.size() << endl;
    cout << "Capacity after pop_back: " << v.capacity() << endl;

    // Display elements after pop_back()
    cout << "Elements after pop_back(): ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    // Clear the vector
    v.clear();
    cout << "After clear: Size: " << v.size() << endl;
    cout << "After clear: Capacity: " << v.capacity() << endl;

    
    return 0;
}
/*
Size: 5
Capacity: 8
Elements using operator[]: 10 20 30 40 50 
Elements using Display(): 10 20 30 40 50 
Size after pop_back: 4
Capacity after pop_back: 8
Elements after pop_back(): 10 20 30 40 
After clear: Size: 0
After clear: Capacity: 8
*/







//Internal implementation of vector with Template 
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class MyVector {
    T* arr;
    size_t n;   // Number of elements in the vector
    size_t cap; // Capacity of the vector
    
public:
    // Constructor
    MyVector() : arr(nullptr), n(0), cap(0) {}

    // Method to add an element at the end of the vector
    void push_back(const T& val) {
        // If the current size is equal to capacity, we need to resize the array
        if (n == cap) {
            // If capacity is 0, initialize to 1, otherwise double the current capacity
            cap = (cap == 0) ? 1 : cap * 2;
            T* newArr = new T[cap];  // Create a new array with the new capacity

            // Copy existing elements into the new array
            for (size_t i = 0; i < n; ++i) {
                newArr[i] = arr[i];
            }

            // Delete the old array
            delete[] arr;
            arr = newArr;  // Point to the newly allocated array
        }
        arr[n++] = val;  // Insert the value at the end and increment the size
    }

    // Method to remove the last element from the vector (no return value)
    void pop_back() {
        if (n == 0) {
            throw runtime_error("pop_back called on an empty vector");
        }
        --n;  // Decrement the size (effectively removing the last element)
    }

    // Overload subscript operator for element access
    T& operator[](size_t i) {
        if (i >= n) {
            throw out_of_range("Index out of range");
        }
        return arr[i];
    }

    // Method to get the number of elements in the vector
    size_t size() const {
        return n;
    }

    // Method to get the current capacity of the vector
    size_t capacity() const {
        return cap;
    }

    // Method to clear the vector (reset the size to 0)
    void clear() {
        n = 0;
    }

    // Destructor to free dynamically allocated memory
    ~MyVector() {
        delete[] arr;
    }

    // Display elements of the vector
    void Display() const {
        for (size_t i = 0; i < n; ++i) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
};

int main() {
    MyVector<int> intV;

    // Adding elements to the vector
    intV.push_back(10);
    intV.push_back(20);
    intV.push_back(30);
    intV.push_back(40);
    intV.push_back(50);

    // Display size and capacity
    cout << "Size: " << intV.size() << endl;
    cout << "Capacity: " << intV.capacity() << endl;

    // Display elements using operator[]
    cout << "Elements using operator[]: ";
    for (size_t i = 0; i < intV.size(); i++) {
        cout << intV[i] << " ";
    }
    cout << endl;

    // Display elements using Display()
    cout << "Elements using Display(): ";
    intV.Display();

    // Pop last element and display results
    intV.pop_back();
    cout << "Size after pop_back: " << intV.size() << endl;
    cout << "Capacity after pop_back: " << intV.capacity() << endl;

    // Display elements after pop_back()
    cout << "Elements after pop_back(): ";
    for (size_t i = 0; i < intV.size(); i++) {
        cout << intV[i] << " ";
    }
    cout << endl;

    // Clear the vector
    intV.clear();
    cout << "After clear: Size: " << intV.size() << endl;
    cout << "After clear: Capacity: " << intV.capacity() << endl;

    // String vector example
    MyVector<string> strV;
    strV.push_back("Apple");
    strV.push_back("Mango");
    strV.push_back("Guava");
    strV.push_back("Pomegranate");
    strV.push_back("Lychee");

    // Display size and capacity
    cout << "Size: " << strV.size() << endl;
    cout << "Capacity: " << strV.capacity() << endl;

    // Display elements using operator[]
    cout << "Elements using operator[]: ";
    for (size_t i = 0; i < strV.size(); i++) {
        cout << strV[i] << " ";
    }
    cout << endl;

    // Display elements using Display()
    cout << "Elements using Display(): ";
    strV.Display();

    // Pop last element and display results
    strV.pop_back();
    cout << "Size after pop_back: " << strV.size() << endl;
    cout << "Capacity after pop_back: " << strV.capacity() << endl;

    // Display elements after pop_back()
    cout << "Elements after pop_back(): ";
    for (size_t i = 0; i < strV.size(); i++) {
        cout << strV[i] << " ";
    }
    cout << endl;

    // Clear the vector
    strV.clear();
    cout << "After clear: Size: " << strV.size() << endl;
    cout << "After clear: Capacity: " << strV.capacity() << endl;

    return 0;
}
/*
Size: 5
Capacity: 8
Elements using operator[]: 10 20 30 40 50 
Elements using Display(): 10 20 30 40 50 
Size after pop_back: 4
Capacity after pop_back: 8
Elements after pop_back(): 10 20 30 40 
After clear: Size: 0
After clear: Capacity: 8
Size: 5
Capacity: 8
Elements using operator[]: Apple Mango Guava Pomegranate Lychee 
Elements using Display(): Apple Mango Guava Pomegranate Lychee 
Size after pop_back: 4
Capacity after pop_back: 8
Elements after pop_back(): Apple Mango Guava Pomegranate 
After clear: Size: 0
After clear: Capacity: 8
*/









//without template
#include <iostream>
#include <stdexcept>
using namespace std;
class MyVector {
    int* arr;   // Pointer to the dynamic array
    size_t n;   // Number of elements in the vector
    size_t cap; // Capacity of the vector
    
  public:
    // Constructor
    MyVector() : arr(nullptr), n(0), cap(0) {}

    // Method to add an element at the end of the vector
    void push_back(const int& val) {
        // If the current size is equal to capacity, we need to resize the array
        if (n == cap) {
            // If capacity is 0, initialize to 1, otherwise double the current capacity
            cap = (cap == 0) ? 1 : cap * 2;
            int* newArr = new int[cap];  // Create a new array with the new capacity

            // Copy existing elements into the new array
            for (size_t i = 0; i < n; ++i) {  // Use size_t for safe indexing
                newArr[i] = arr[i];
            }

            // Delete the old array
            delete[] arr;
            arr = newArr;  // Point to the newly allocated array
        }
        arr[n++] = val;  // Insert the value at the end and increment the size
    }

    // Method to get the size of the vector
    size_t size() const {
        return n;
    }

    // Method to get the capacity of the vector
    size_t capacity() const {
        return cap;
    }

    // Method to display all elements in the vector
    void Display() const {
        for (size_t i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Destructor to free allocated memory
    ~MyVector() {
        delete[] arr;
    }
};

int main() {
    MyVector vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);

    cout << "Vector elements: ";
    vec.Display();

    cout << "Size: " << vec.size() << endl;
    cout << "Capacity: " << vec.capacity() << endl;

    return 0;
}
/*
Vector elements: 10 20 30 40 50 
Size: 5
Capacity: 8
*/




//with template
#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class MyVector {
    T* arr;   // Pointer to the dynamic array
    size_t n;   // Number of elements in the vector
    size_t cap; // Capacity of the vector
    
  public:
    // Constructor
    MyVector() : arr(nullptr), n(0), cap(0) {}

    // Method to add an element at the end of the vector
    void push_back(const T& val) {
        // If the current size is equal to capacity, we need to resize the array
        if (n == cap) {
            // If capacity is 0, initialize to 1, otherwise double the current capacity
            cap = (cap == 0) ? 1 : cap * 2;
            T* newArr = new T[cap];  // Create a new array with the new capacity

            // Copy existing elements into the new array
            for (size_t i = 0; i < n; ++i) {  // Use size_t for safe indexing
                newArr[i] = arr[i];
            }

            // Delete the old array
            delete[] arr;
            arr = newArr;  // Point to the newly allocated array
        }
        arr[n++] = val;  // Insert the value at the end and increment the size
    }

    // Method to get the size of the vector
    size_t size() const {
        return n;
    }

    // Method to get the capacity of the vector
    size_t capacity() const {
        return cap;
    }

    // Method to display all elements in the vector
    void Display() const {
        for (size_t i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Destructor to free allocated memory
    ~MyVector() {
        delete[] arr;
    }
};

int main() {
    MyVector <int> vecInt;

    vecInt.push_back(10);
    vecInt.push_back(20);
    vecInt.push_back(30);
    vecInt.push_back(40);
    vecInt.push_back(50);

    cout << "Vector elements: ";
    vecInt.Display();

    cout << "Size: " << vecInt.size() << endl;
    cout << "Capacity: " << vecInt.capacity() << endl;
    
    MyVector <string> vecStr;

    vecStr.push_back("Apple");
    vecStr.push_back("Mango");
    vecStr.push_back("Orange");
    vecStr.push_back("PineApple");
    vecStr.push_back("Litchi");

    cout << "Vector elements: ";
    vecStr.Display();

    cout << "Size: " << vecStr.size() << endl;
    cout << "Capacity: " << vecStr.capacity() << endl;
    return 0;
}
/*
Vector elements: 10 20 30 40 50 
Size: 5
Capacity: 8
Vector elements: Apple Mango Orange PineApple Litchi 
Size: 5
Capacity: 8
*/






































































//Code Example with cap = cap * 2:
#include <iostream>
using namespace std;

class MyVector {
    int* arr;
    int n;    // current number of elements
    int cap;  // capacity of the vector

public:
    MyVector() : arr(nullptr), n(0), cap(0) {}  // Initial state: arr is nullptr, n = 0, cap = 0

    void push_back(int val) {
        if (n == cap) {
            cap = cap * 2;  // Problem: cap starts at 0, so cap = 0 * 2 = 0
            //cap =(cap==0)? 1: cap*2;
            cout << "Attempting to allocate " << cap << " elements" << endl;
            int* newarr = new int[cap];  // Trying to allocate an array of size 0
            for (int i = 0; i < n; i++) {
                newarr[i] = arr[i];  // Copy existing elements (none in this case, as cap == 0)
            }
            delete[] arr;  // Clean up old array (nullptr in this case)
            arr = newarr;  // arr still points to nullptr (or invalid memory)
        }
        arr[n++] = val;  // Add the new element to the vector
    }

    int size() const {
        return n;
    }

    int capacity() const {
        return cap;
    }

    ~MyVector() {
        delete[] arr;  // Clean up allocated memory
    }
};

int main() {
    MyVector v;
    
    cout << "Before push_back:" << endl;
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    // Add the first element
    v.push_back(10);  // This will try to allocate an array with 0 capacity, causing issues

    cout << "\nAfter push_back:" << endl;
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    return 0;
}
/*
Before push_back:
Size: 0, Capacity: 0
Attempting to allocate 0 elements

After push_back:
Size: 1, Capacity: 0
*/


















//self

#include<iostream>
#include<stdexcept>
using namespace std;
class MyVector{
    int* arr;
    int n; 
    int cap;
  public:
    MyVector(): arr(nullptr), n(0), cap(0){}
    ~MyVector(){ delete[] arr;}
    void push_back(const int& val);
    void pop_back();
    int& operator[](const int& index);
    int size() const;
    int capacity() const;
    void display() const;
};

 void MyVector::push_back(const int& val){
      if(n==cap){
          cap = (cap==0)? 1: cap*2;
          int* newArr = new int[cap];
          for(int i=0; i<n; i++){
              newArr[i] = arr[i];
          }
          delete[] arr;
          arr = newArr;
      }     
      arr[n++] = val;
 }
 
 void MyVector::pop_back(){
     if(n==0) throw runtime_error("Vector is empty!");
     --n;
 }
 
  int& MyVector::operator[](const int& index){
      if(index>=n) throw runtime_error("Vector is out of range!");
      
      return arr[index];
  }
 
int MyVector::size() const{
    return n;
}

int MyVector::capacity() const{
    return cap;
}
    
 void MyVector::display() const{
     for(int i=0; i<n; i++){
         cout<<arr[i]<<" ";
     }
     cout<<endl;
 }
 int main(){
     MyVector v;
     v.push_back(10);
     v.push_back(20);
     v.push_back(30);
     v.push_back(40);
     
     cout<<"Vector Elements: ";
     v.display();
     cout<<"Size: "<<v.size()<<endl;
     cout<<"Capacity: "<<v.capacity()<<endl;
     
     v.pop_back();
     cout<<"Vector Elements after pop: ";
     v.display();
     cout<<"Size: "<<v.size()<<endl;
     cout<<"Capacity: "<<v.capacity()<<endl;
     cout<<"Vector Elements using [] operator: ";
     for(int i=0; i<v.size(); i++){
         cout<<v[i]<<" ";
     }
     cout<<endl;
    return 0;
 }
 /*
 Vector Elements: 10 20 30 40 
Size: 4
Capacity: 4
Vector Elements after pop: 10 20 30 
Size: 3
Capacity: 4
Vector Elements using [] operator: 10 20 30 
 */
 
 
 
 
 
 
 
 
 