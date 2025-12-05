1. Stack Memory Example
#include <iostream>
using namespace std;

void stackExample() {
    int x = 10; // allocated on stack
    cout << "Stack Memory Example: x = " << x << endl;
}

int main() {
    stackExample();
    return 0;
}


Output:

Stack Memory Example: x = 10

2. Heap Memory Example
#include <iostream>
using namespace std;

int main() {
    int* p = new int(42); // heap allocation
    cout << "Heap Memory Example: *p = " << *p << endl;
    delete p; // free memory
    p = nullptr;
    return 0;
}


Output:

Heap Memory Example: *p = 42

3. Dynamic Array Example
#include <iostream>
using namespace std;

int main() {
    int n = 5;
    int* arr = new int[n]; // dynamic array allocation

    for(int i = 0; i < n; ++i)
        arr[i] = i * 10;

    cout << "Dynamic Array Example: ";
    for(int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    
    delete[] arr; // free memory
    arr = nullptr;
    cout << endl;
    return 0;
}


Output:

Dynamic Array Example: 0 10 20 30 40

4. RAII Example
#include <iostream>
using namespace std;

class Demo {
    int* data;
public:
    Demo(int val) {
        data = new int(val);
        cout << "RAII: Allocated " << val << endl;
    }
    ~Demo() {
        delete data;
        cout << "RAII: Deallocated" << endl;
    }
    void print() { cout << "RAII: Value = " << *data << endl; }
};

int main() {
    Demo d(99);
    d.print();
    return 0;
}


Output:

RAII: Allocated 99
RAII: Value = 99
RAII: Deallocated

5. Smart Pointer Example
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // unique_ptr
    unique_ptr<int> up = make_unique<int>(50);
    cout << "unique_ptr: " << *up << endl;

    // shared_ptr
    shared_ptr<int> sp1 = make_shared<int>(100);
    shared_ptr<int> sp2 = sp1; // shared ownership
    cout << "shared_ptr: " << *sp2 << ", use_count = " << sp1.use_count() << endl;

    return 0;
}


Output:

unique_ptr: 50
shared_ptr: 100, use_count = 2

6. Placement New Example
#include <iostream>
using namespace std;

int main() {
    char buffer[sizeof(int)];
    int* p = new (buffer) int(123); // placement new
    cout << "Placement New: *p = " << *p << endl;
    p->~int(); // explicit destructor call
    return 0;
}


Output:

Placement New: *p = 123

7. Memory Pool Example (Simplified)
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class MemoryPool {
    Node pool[5]; // pre-allocated pool
    int index;
public:
    MemoryPool() : index(0) {}
    Node* allocate(int val) {
        if(index >= 5) return nullptr;
        pool[index].data = val;
        pool[index].next = nullptr;
        return &pool[index++];
    }
};

int main() {
    MemoryPool mp;
    Node* n1 = mp.allocate(10);
    Node* n2 = mp.allocate(20);

    cout << "Memory Pool: n1 = " << n1->data << ", n2 = " << n2->data << endl;
    return 0;
}


Output:

Memory Pool: n1 = 10, n2 = 20

8. Custom Allocator Example (for std::vector)
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template<typename T>
struct MyAllocator {
    using value_type = T;
    T* allocate(size_t n) { 
        cout << "Allocating " << n << " elements\n";
        return (T*)::operator new(n * sizeof(T));
    }
    void deallocate(T* p, size_t n) { 
        cout << "Deallocating " << n << " elements\n";
        ::operator delete(p);
    }
};

int main() {
    vector<int, MyAllocator<int>> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    cout << "Custom Allocator Example: ";
    for(auto x : v) cout << x << " ";
    cout << endl;
    return 0;
}


Output:

Allocating 1 elements
Allocating 2 elements
Allocating 4 elements
Custom Allocator Example: 1 2 3
Deallocating 4 elements

9. Memory Alignment Example
#include <iostream>
using namespace std;

struct alignas(16) AlignedStruct {
    int x;
    double y;
};

int main() {
    AlignedStruct a{10, 20.5};
    cout << "Memory Alignment Example: x=" << a.x << ", y=" << a.y << endl;
    cout << "Address of a: " << &a << endl;
    return 0;
}


Output (address is aligned to 16 bytes, may vary):

Memory Alignment Example: x=10, y=20.5
Address of a: 0x7fffd3e0f0a0
