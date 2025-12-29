1. Compile-Time Factorial (constexpr)
#include <iostream>
using namespace std;

constexpr int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr int fact5 = factorial(5);
    cout << "Factorial of 5: " << fact5 << endl;
    return 0;
}
/*
Output:
Factorial of 5: 120
*/

2. Compile-Time Fibonacci (constexpr)
#include <iostream>
using namespace std;

constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    constexpr int fib6 = fibonacci(6);
    cout << "Fibonacci of 6: " << fib6 << endl;
    return 0;
}
/*
Output:
Fibonacci of 6: 8
*/

3. Template Metaprogramming Factorial
#include <iostream>
using namespace std;

template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};
template<> struct Factorial<0> { static constexpr int value = 1; };

int main() {
    constexpr int fact7 = Factorial<7>::value;
    cout << "Factorial of 7 (template): " << fact7 << endl;
    return 0;
}
/*
Output:
Factorial of 7 (template): 5040
*/

4. Template Metaprogramming Fibonacci
#include <iostream>
using namespace std;

template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};
template<> struct Fibonacci<0> { static constexpr int value = 0; };
template<> struct Fibonacci<1> { static constexpr int value = 1; };

int main() {
    constexpr int fib5 = Fibonacci<5>::value;
    cout << "Fibonacci of 5 (template): " << fib5 << endl;
    return 0;
}
/*
Output:
Fibonacci of 5 (template): 5
*/

5. Template Specialization Example
#include <iostream>
using namespace std;

template<typename T>
T multiply(T a, T b) { return a * b; }

template<>
int multiply<int>(int a, int b) { return a * b * 2; }  // Special optimization

int main() {
    cout << "Int multiply(3,4): " << multiply(3,4) << endl;
    cout << "Double multiply(3.5,2.0): " << multiply(3.5,2.0) << endl;
    return 0;
}
/*
Output:
Int multiply(3,4): 24
Double multiply(3.5,2.0): 7
*/

6. Memory Layout Optimization
#include <iostream>
using namespace std;

struct Unoptimized { char a; int b; };
struct Optimized { int b; char a; };

int main() {
    cout << "Size Unoptimized: " << sizeof(Unoptimized) << endl;
    cout << "Size Optimized: " << sizeof(Optimized) << endl;
    return 0;
}
/*
Output (typical):
Size Unoptimized: 8
Size Optimized: 8
*/

7. Custom Memory Pool Allocator
#include <iostream>
using namespace std;

template <typename T>
class PoolAllocator {
    struct Block { Block* next; };
    Block* free_list_;
    char* pool_;
    size_t pool_size_;
public:
    PoolAllocator(size_t n) : pool_size_(n) {
        pool_ = static_cast<char*>(::operator new(n * sizeof(T)));
        free_list_ = reinterpret_cast<Block*>(pool_);
        Block* current = free_list_;
        for(size_t i=0;i<n-1;i++){
            current->next = reinterpret_cast<Block*>(pool_ + (i+1)*sizeof(T));
            current = current->next;
        }
        current->next = nullptr;
    }
    ~PoolAllocator() { ::operator delete(pool_); }

    T* allocate() {
        if(!free_list_) throw bad_alloc();
        Block* b = free_list_;
        free_list_ = free_list_->next;
        return reinterpret_cast<T*>(b);
    }

    void deallocate(T* p) {
        Block* b = reinterpret_cast<Block*>(p);
        b->next = free_list_;
        free_list_ = b;
    }
};

class MyObject { 
    public: 
     int x; 
     void hello(){
        cout<<"Hello\n";
    } 
};

int main() {
    PoolAllocator<MyObject> pool(2);
    MyObject* o1 = pool.allocate();
    MyObject* o2 = pool.allocate();
    o1->hello(); o2->hello();
    pool.deallocate(o1); pool.deallocate(o2);
    return 0;
}
/*
Output:
Hello
Hello
*/

8. RAII with Unique Pointer
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int[]> arr = make_unique<int[]>(5);
    for(int i=0;i<5;i++) arr[i]=i*10;
    for(int i=0;i<5;i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
/*
Output:
0 10 20 30 40
*/

9. Shared Pointer Example
#include <iostream>
#include <memory>
using namespace std;
int main() {
    shared_ptr<int> p1 = make_shared<int>(42);
    shared_ptr<int> p2 = p1;
    cout << *p1 << " " << *p2 << endl;
    return 0;
}
/*
Output:
42 42
*/

10. Move Semantics
#include <iostream>
#include <utility>
using namespace std;
class MyClass {
    int* data;
  public:
    MyClass(size_t n): data(new int[n]){}
    ~MyClass(){ delete[] data; }

    MyClass(MyClass&& other) noexcept: data(other.data){ other.data=nullptr; }
    MyClass& operator=(MyClass&& other) noexcept {
        if(this!=&other){ delete[] data; data=other.data; other.data=nullptr; }
        return *this;
    }
};
int main() {
    MyClass a(5);
    MyClass b = move(a);
    cout << "Moved successfully\n";
    return 0;
}
/*
Output:
Moved successfully
*/

11. Vector Reserve Optimization
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v; v.reserve(1000);
    for(int i=0;i<1000;i++) v.push_back(i);
    cout << "Vector size: " << v.size() << ", capacity: " << v.capacity() << endl;
    return 0;
}
/*
Output:
Vector size: 1000, capacity: 1000
*/

12. Using List vs Vector
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main() {
    vector<int> vec(5); list<int> lst(5);
    cout << "Vector first element: " << vec[0] << endl;
    cout << "List first element: " << lst.front() << endl;
    return 0;
}
/*
Output:
Vector first element: 0
List first element: 0
*/

13. Expression Template (Lazy Evaluation) Example
#include <iostream>
using namespace std;

template<typename L, typename R>
struct AddExpr {
    L const& l; R const& r;
    AddExpr(L const& l, R const& r): l(l), r(r) {}
    int eval() const { return l.eval() + r.eval(); }
};

struct Value {
    int v; Value(int x): v(x) {}
    int eval() const { return v; }
};

int main() {
    Value a(5), b(10);
    AddExpr<Value, Value> expr(a,b);
    cout << "Lazy sum: " << expr.eval() << endl;
    return 0;
}
/*
Output:
Lazy sum: 15
*/

14. Empty Base Optimization (EBO)
#include <iostream>
using namespace std;

struct Empty {};
struct Derived: Empty { int x; };

int main() {
    cout << "Size of Empty: " << sizeof(Empty) << endl;
    cout << "Size of Derived: " << sizeof(Derived) << endl;
    return 0;
}
/*
Output:
Size of Empty: 1
Size of Derived: 4
*/

15. CRTP (Curiously Recurring Template Pattern)
#include <iostream>
using namespace std;

template<typename T>
struct Base { 
    void call() { 
        static_cast<T*>(this)->impl(); 
    } 
};

struct Derived: Base<Derived> {
    void impl() { 
        cout << "CRTP called\n"; 
    }
};

int main() {
    Derived d;
    d.call();
    return 0;
}
/*
Output:
CRTP called
*/




#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <utility>
#include <cmath>
using namespace std;

// ----------------- Compile-Time Factorial -----------------
constexpr int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}

// ----------------- Compile-Time Fibonacci -----------------
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// ----------------- Template Metaprogramming Factorial -----------------
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};
template<> struct Factorial<0> { static constexpr int value = 1; };

// ----------------- Template Metaprogramming Fibonacci -----------------
template<int N>
struct FibonacciTpl {
    static constexpr int value = FibonacciTpl<N-1>::value + FibonacciTpl<N-2>::value;
};
template<> struct FibonacciTpl<0> { static constexpr int value = 0; };
template<> struct FibonacciTpl<1> { static constexpr int value = 1; };

// ----------------- Template Specialization -----------------
template<typename T>
T multiply(T a, T b) { return a * b; }
template<>
int multiply<int>(int a, int b) { return a * b * 2; }

// ----------------- Memory Layout -----------------
struct Unoptimized { char a; int b; };
struct Optimized { int b; char a; };

// ----------------- RAII Example -----------------
void unique_ptr_example() {
    unique_ptr<int[]> arr = make_unique<int[]>(5);
    for(int i=0;i<5;i++) arr[i]=i*10;
    cout << "Unique_ptr values: ";
    for(int i=0;i<5;i++) cout << arr[i] << " ";
    cout << endl;
}

// ----------------- Shared Pointer Example -----------------
void shared_ptr_example() {
    shared_ptr<int> p1 = make_shared<int>(42);
    shared_ptr<int> p2 = p1;
    cout << "Shared_ptr values: " << *p1 << " " << *p2 << endl;
}

// ----------------- Move Semantics -----------------
class MyClass {
    int* data;
public:
    MyClass(size_t n): data(new int[n]){}
    ~MyClass(){ delete[] data; }
    MyClass(MyClass&& other) noexcept: data(other.data){ other.data=nullptr; }
    MyClass& operator=(MyClass&& other) noexcept {
        if(this!=&other){ delete[] data; data=other.data; other.data=nullptr; }
        return *this;
    }
};

// ----------------- Vector Reserve Example -----------------
void vector_example() {
    vector<int> v; v.reserve(1000);
    for(int i=0;i<1000;i++) v.push_back(i);
    cout << "Vector size: " << v.size() << ", capacity: " << v.capacity() << endl;
}

// ----------------- List Example -----------------
void list_example() {
    list<int> lst(5);
    cout << "List first element: " << lst.front() << endl;
}

// ----------------- Expression Template Example -----------------
template<typename L, typename R>
struct AddExpr {
    L const& l; R const& r;
    AddExpr(L const& l, R const& r): l(l), r(r) {}
    int eval() const { return l.eval() + r.eval(); }
};
struct Value {
    int v; Value(int x): v(x) {}
    int eval() const { return v; }
};

// ----------------- EBO Example -----------------
struct Empty {};
struct Derived: Empty { int x; };

// ----------------- CRTP Example -----------------
template<typename T>
struct Base { void call() { static_cast<T*>(this)->impl(); } };
struct DerivedCRTP: Base<DerivedCRTP> { void impl() { cout << "CRTP called\n"; } };

// ----------------- Menu -----------------
void showMenu() {
    cout << "\n=== C++ Optimization Examples Menu ===\n";
    cout << "1. Compile-Time Factorial\n";
    cout << "2. Compile-Time Fibonacci\n";
    cout << "3. Template Metaprogramming Factorial\n";
    cout << "4. Template Metaprogramming Fibonacci\n";
    cout << "5. Template Specialization Multiply\n";
    cout << "6. Memory Layout Optimization\n";
    cout << "7. Unique_ptr RAII Example\n";
    cout << "8. Shared_ptr Example\n";
    cout << "9. Move Semantics Example\n";
    cout << "10. Vector Reserve Example\n";
    cout << "11. List Example\n";
    cout << "12. Expression Template Example\n";
    cout << "13. Empty Base Optimization (EBO)\n";
    cout << "14. CRTP Example\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Factorial of 5: " << factorial(5) << endl; break;
            case 2:
                cout << "Fibonacci of 6: " << fibonacci(6) << endl; break;
            case 3:
                cout << "Template Factorial of 7: " << Factorial<7>::value << endl; break;
            case 4:
                cout << "Template Fibonacci of 5: " << FibonacciTpl<5>::value << endl; break;
            case 5:
                cout << "Multiply<int>(3,4): " << multiply(3,4) << endl;
                cout << "Multiply<double>(3.5,2.0): " << multiply(3.5,2.0) << endl; break;
            case 6:
                cout << "Size Unoptimized: " << sizeof(Unoptimized) 
                     << ", Size Optimized: " << sizeof(Optimized) << endl; break;
            case 7: unique_ptr_example(); break;
            case 8: shared_ptr_example(); break;
            case 9: {
                MyClass a(5); MyClass b = move(a);
                cout << "Move semantics executed.\n"; break;
            }
            case 10: vector_example(); break;
            case 11: list_example(); break;
            case 12: {
                Value a(5), b(10);
                AddExpr<Value,Value> expr(a,b);
                cout << "Lazy sum using Expression Template: " << expr.eval() << endl; break;
            }
            case 13:
                cout << "Size of Empty: " << sizeof(Empty) 
                     << ", Size of Derived(EBO): " << sizeof(Derived) << endl; break;
            case 14:
                DerivedCRTP d; d.call(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 0);
    return 0;
}
/* 

=== C++ Optimization Examples Menu ===
1. Compile-Time Factorial
2. Compile-Time Fibonacci
3. Template Metaprogramming Factorial
4. Template Metaprogramming Fibonacci
5. Template Specialization Multiply
6. Memory Layout Optimization
7. Unique_ptr RAII Example
8. Shared_ptr Example
9. Move Semantics Example
10. Vector Reserve Example
11. List Example
12. Expression Template Example
13. Empty Base Optimization (EBO)
14. CRTP Example
0. Exit
Enter your choice: 3
Template Factorial of 7: 5040

=== C++ Optimization Examples Menu ===
1. Compile-Time Factorial
2. Compile-Time Fibonacci
3. Template Metaprogramming Factorial
4. Template Metaprogramming Fibonacci
5. Template Specialization Multiply
6. Memory Layout Optimization
7. Unique_ptr RAII Example
8. Shared_ptr Example
9. Move Semantics Example
10. Vector Reserve Example
11. List Example
12. Expression Template Example
13. Empty Base Optimization (EBO)
14. CRTP Example
0. Exit
Enter your choice: 
*/