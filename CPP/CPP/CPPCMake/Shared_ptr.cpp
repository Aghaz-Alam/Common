#include <iostream>
using namespace std;
template <typename T>
class SharedPtr {
    T* ptr;
    size_t* refCount;
  public:
    SharedPtr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}
    // Copy constructor
    SharedPtr(const SharedPtr& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        ++(*refCount);
    }
    // Assignment operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();

            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }
    void release() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }
    ~SharedPtr() {
        release();
    }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    size_t use_count() const { return *refCount; }

};

// Test class for operator->
class Test {
public:
    int x;
    Test(int v) : x(v) {}

    void show() {
        cout << "Value of x in Test Class= " << x << endl;
    }
};
int main() {
    SharedPtr<int> p1(new int(10));
    
    // operator*
    cout<<"p1 before modification: "<<*p1<<endl;
    *p1 = 20;   // modifies the underlying object
    cout<<"p1 after modification: "<<*p1<<endl;
    
    // Copy
    cout << "p1.use_count(): "<<p1.use_count() << endl; // 1
    SharedPtr<int> p2 = p1;        
    cout << "p2.use_count(): "<<p2.use_count() << endl; // 2
    

    // Manual release of p2
    p2.release();
    cout << "After p2.release(), \np1.use_count(): " << p1.use_count() << endl;
    
    
    // operator->
    SharedPtr<Test> obj(new Test(100));
    obj->show();      // calls operator->()



  return 0;
}
/* 
p1 before modification: 10
p1 after modification: 20
p1.use_count(): 1
p2.use_count(): 2
After p2.release(), 
p1.use_count(): 1
Value of x in Test Class= 100
*/


