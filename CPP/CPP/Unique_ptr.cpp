//unique_ptr implementation
#include <iostream>
#include <utility>   // std::move, std::forward, std::swap
#include <cassert>   // optional assert for debugging

using namespace std;

template <typename T>
class UniquePtr {
  private:
    T* ptr;

  public:
    // --- Constructors ---
    UniquePtr() noexcept : ptr(nullptr) {}                    // default constructs to nullptr
    explicit UniquePtr(T* p) noexcept : ptr(p) {}            // take ownership of raw pointer

    // Disable copy
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor: steal other's pointer and null the other
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment: free current resource, then steal other's pointer
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;                 // release current resource
            ptr = other.ptr;            // take ownership
            other.ptr = nullptr;        // leave other empty
        }
        return *this;
    }

    // Destructor: delete owned object (if any)
    ~UniquePtr() {
        delete ptr;
    }

    // --- Observers ---
    T* get() const noexcept { return ptr; }

    // Dereference: caller must ensure ptr != nullptr. Use assert for debug builds.
    T& operator*() const {
        assert(ptr && "Dereferencing nullptr UniquePtr");
        return *ptr;
    }

    T* operator->() const noexcept {
        assert(ptr && "Accessing member through nullptr UniquePtr");
        return ptr;
    }

    explicit operator bool() const noexcept { return ptr != nullptr; }

    // --- Modifiers ---

    // release: relinquish ownership and return the raw pointer; UniquePtr becomes empty.
    // Caller is responsible for deleting the returned pointer (or handing it elsewhere).
    T* release() noexcept {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    // reset: delete current object and take ownership of p (which defaults to nullptr).
    // If p == ptr (rare / dangerous), this check prevents deleting same pointer twice.
    void reset(T* p = nullptr) noexcept {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    // swap: exchange owned pointers with another UniquePtr, noexcept and uses std::swap
    void swap(UniquePtr& other) noexcept {
        using std::swap;
        swap(ptr, other.ptr);
    }
};

// Helper function similar to std::make_unique (single-object version)
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));  //forward preserves value-category
}

// Simple test struct to show construction/destruction and a method call
struct Test {
    Test()  { cout << "Test created\n"; }
    ~Test() { cout << "Test destroyed\n"; }
    void print() { cout << "Hello\n"; }
};
int main() {

    // ---------------------------
    // 1. make_unique + operator-> 
    // ---------------------------
    auto p = make_unique<Test>();     // allocates Test, returns UniquePtr<Test>
    p->print();                       // operator->() gives access to Test::print()

    // ---------------------------
    // 2. get()
    // ---------------------------
    UniquePtr<int> up1(new int(50));
    cout << "Using get(): " << up1.get() << "\n";   // prints RAW ADDRESS held inside UniquePtr

    // ---------------------------
    // 3. operator*()
    // ---------------------------
    cout << "Dereferencing using operator*(): " << *up1 << "\n";

    // ---------------------------
    // 4. operator bool()
    // ---------------------------
    if (up1)    // equivalent to (up1.get() != nullptr)
        cout << "up1 is not empty\n";

    // ---------------------------
    // 5. Move semantics with move()
    // ---------------------------
    UniquePtr<int> up2 = std::move(up1);

    if (!up1)   // operator bool() → false
        cout << "up1 is now empty after move\n";

    cout << "Value in up2: " << *up2 << "\n";

    // ---------------------------
    // 6. release()
    // ---------------------------
    int* rawPtr = up2.release();  // up2 loses ownership and returns raw pointer
    cout << "Value from released raw pointer: " << *rawPtr << "\n";

    delete rawPtr;   // YOU must delete it manually (VERY important)

    // ---------------------------
    // 7. reset()
    // ---------------------------
    UniquePtr<int> up3(new int(100));
    cout << "Before reset(), up3 = " << *up3 << "\n";

    up3.reset(new int(200));      // deletes old 100, takes ownership of 200

    cout << "After reset(), up3 = " << *up3 << "\n";

    up3.reset();                  // deletes pointer, becomes empty

    if (!up3)
        cout << "up3 is empty after reset(nullptr)\n";

    // ---------------------------
    // 8. swap()
    // ---------------------------
    UniquePtr<int> A(new int(10));
    UniquePtr<int> B(new int(20));

    cout << "Before swap: A=" << *A << " B=" << *B << "\n";

    A.swap(B);   // swaps the two pointers internally

    cout << "After swap: A=" << *A << " B=" << *B << "\n";


    return 0;
}
/*
Test created
Hello
Using get(): 0x5efbc4a7b6e0
Dereferencing using operator*(): 50
up1 is not empty
up1 is now empty after move
Value in up2: 50
Value from released raw pointer: 50
Before reset(), up3 = 100
After reset(), up3 = 200
up3 is empty after reset(nullptr)
Before swap: A=10 B=20
After swap: A=20 B=10
Test destroyed
*/


