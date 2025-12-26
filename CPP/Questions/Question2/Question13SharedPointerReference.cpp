/* 
Question 13: Shared Pointer Reference Counting Demo

Implement a minimal SharedPtr<T> class showing reference counting.
Functions: constructor, copy constructor, destructor, getCount().
Ensure no memory leak and proper deletion when count reaches zero.

Sample Input:

SharedPtr<int> p1(new int(5));
SharedPtr<int> p2 = p1;
cout << p1.getCount();
*/

//Custom SharedPtr Implementation
#include <iostream>

template <typename T>
class SharedPtr {
  private:
    T* ptr;             // raw pointer
    int* refCount;      // shared reference count

  public:
    // Constructor
    explicit SharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1)) {}

    // Copy Constructor
    SharedPtr(const SharedPtr& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        ++(*refCount);
    }

    // Copy Assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            // Decrement old count
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            // Copy new
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }

    // Destructor
    ~SharedPtr() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    // Access
    T* get() const { return ptr; }

    // Reference Count
    int getCount() const { return *refCount; }
};

// ------------------------------
// Demo
// ------------------------------
int main() {
    SharedPtr<int> p1(new int(5));
    SharedPtr<int> p2 = p1;    // copy

    std::cout << p1.getCount() << std::endl;  // Output: 2

    return 0;
}
/*
Expected Output: 
2
*/