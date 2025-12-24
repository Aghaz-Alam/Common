Pointersadvanced pointer concepts in C++11 through C++20, with examples and expected output. I’ll cover:
Basic pointers
Pointer arithmetic
Pointers and arrays
Pointers to functions
Pointers to pointers

Smart pointers (unique_ptr, shared_ptr, weak_ptr)
std::unique_ptr with custom deleters (C++11)
std::shared_ptr and std::weak_ptr (C++11)
Pointer-related modern features (std::addressof, std::to_address)




1️⃣ Basic Pointers
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int* ptr = &a; // pointer to int

    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << &a << endl;
    cout << "Pointer ptr points to: " << ptr << endl;
    cout << "Value at pointer ptr: " << *ptr << endl;

    *ptr = 20; // modifying value via pointer
    cout << "New value of a: " << a << endl;

    return 0;
}
/* 
Output:
Value of a: 10
Address of a: 0x7ffeefbff5ac
Pointer ptr points to: 0x7ffeefbff5ac
Value at pointer ptr: 10
New value of a: 20
*/



2️⃣ Pointer Arithmetic
#include <iostream>
using namespace std;
int main() {
    int arr[] = {10, 20, 30, 40};
    int* ptr = arr;

    cout << "First element: " << *ptr << endl;
    ptr++;
    cout << "Second element: " << *ptr << endl;
    ptr += 2;
    cout << "Fourth element: " << *ptr << endl;

    return 0;
}
/* 
Output:
First element: 10
Second element: 20
Fourth element: 40
*/


3️⃣ Pointers and Arrays
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr;

    for (int i = 0; i < 5; i++) {
        cout << "Element " << i << ": " << *(ptr + i) << endl;
    }

    return 0;
}
/* 
Output:
Element 0: 1
Element 1: 2
Element 2: 3
Element 3: 4
Element 4: 5
*/



4️⃣ Pointers to Functions
#include <iostream>
using namespace std;

void greet() {
    cout << "Hello from function!" << endl;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    void (*fptr)() = greet;
    fptr(); // call via pointer

    int (*aptr)(int, int) = add;
    cout << "Sum: " << aptr(5, 10) << endl;

    return 0;
}
/* 
Output:
Hello from function!
Sum: 15
*/



5️⃣ Pointers to Pointers
#include <iostream>
using namespace std;

int main() {
    int a = 50;
    int* ptr = &a;
    int** pptr = &ptr;

    cout << "Value of a: " << a << endl;
    cout << "Value via ptr: " << *ptr << endl;
    cout << "Value via pptr: " << **pptr << endl;

    return 0;
}
/* 
Output:
Value of a: 50
Value via ptr: 50
Value via pptr: 50
*/


6️⃣ Smart Pointers: unique_ptr (C++11)
#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> ptr = make_unique<int>(100);
    cout << "Value: " << *ptr << endl;

    // unique_ptr cannot be copied
    // unique_ptr<int> ptr2 = ptr; // Error

    unique_ptr<int> ptr2 = move(ptr); // Transfer ownership
    cout << "Value via ptr2: " << *ptr2 << endl;

    return 0;
}
/* 
Output:
Value: 100
Value via ptr2: 100
*/


7️⃣ Smart Pointers: shared_ptr & weak_ptr (C++11)
#include <iostream>
#include <memory>
using namespace std;
int main() {
    shared_ptr<int> sp1 = make_shared<int>(200);
    shared_ptr<int> sp2 = sp1; // shared ownership

    cout << "sp1: " << *sp1 << ", sp2: " << *sp2 << endl;
    cout << "Use count: " << sp1.use_count() << endl;

    weak_ptr<int> wp = sp1; // non-owning pointer
    cout << "wp expired? " << (wp.expired() ? "Yes" : "No") << endl;

    sp1.reset(); // release one shared_ptr
    cout << "Use count after sp1.reset(): " << sp2.use_count() << endl;

    return 0;
}
/* 
Output:
sp1: 200, sp2: 200
Use count: 2
wp expired? No
Use count after sp1.reset(): 1
*/



8️⃣ Advanced: std::to_address (C++20)
C++20 introduced std::to_address for pointers and fancy pointers (like iterators).

#include <iostream>
#include <memory>
using namespace std;
int main() {
    int x = 500;
    int* p = &x;

    int* addr = to_address(p); // gets raw address
    cout << "Value via to_address: " << *addr << endl;

    return 0;
}
/* 
Output:
Value via to_address: 500
*/



1️⃣ Basic Pointer
#include <iostream>
using namespace std;
int main() {
    int a = 10;
    int* ptr = &a; // pointer to int

    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << &a << endl;
    cout << "Pointer ptr points to: " << ptr << endl;
    cout << "Value at pointer ptr: " << *ptr << endl;

    *ptr = 20; // modify value via pointer
    cout << "New value of a: " << a << endl;

    return 0;
}
/* 
Output:
Value of a: 10
Address of a: 0x7ffee3bff5ac
Pointer ptr points to: 0x7ffee3bff5ac
Value at pointer ptr: 10
New value of a: 20
*/



2️⃣ Pointer Arithmetic
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40};
    int* ptr = arr;

    cout << "First element: " << *ptr << endl;
    ptr++;
    cout << "Second element: " << *ptr << endl;
    ptr += 2;
    cout << "Fourth element: " << *ptr << endl;

    return 0;
}
/* 
Output:
First element: 10
Second element: 20
Fourth element: 40
*/


3️⃣ Pointers and Arrays
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr;

    for (int i = 0; i < 5; i++) {
        cout << "Element " << i << ": " << *(ptr + i) << endl;
    }

    return 0;
}
/* 
Output:
Element 0: 1
Element 1: 2
Element 2: 3
Element 3: 4
Element 4: 5
*/


4️⃣ Pointer to Pointer
#include <iostream>
using namespace std;
int main() {
    int a = 50;
    int* ptr = &a;
    int** pptr = &ptr;

    cout << "Value of a: " << a << endl;
    cout << "Value via ptr: " << *ptr << endl;
    cout << "Value via pptr: " << **pptr << endl;

    return 0;
}
/* 
Output:
Value of a: 50
Value via ptr: 50
Value via pptr: 50
*/


5️⃣ Pointers to Functions
#include <iostream>
using namespace std;
void greet() {
    cout << "Hello from function!" << endl;
}
int add(int a, int b) {
    return a + b;
}
int main() {
    void (*fptr)() = greet;
    fptr(); // call via pointer

    int (*aptr)(int, int) = add;
    cout << "Sum: " << aptr(5, 10) << endl;

    return 0;
}
/* 
Output:
Hello from function!
Sum: 15
*/


6️⃣ nullptr Usage (C++11)
#include <iostream>
using namespace std;
int main() {
    int* ptr = nullptr;
    if (ptr == nullptr)
        cout << "Pointer is null" << endl;

    return 0;
}
/* 
Output:
Pointer is null
*/


7️⃣ Smart Pointer: unique_ptr (C++11)
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> ptr = make_unique<int>(100);
    cout << "Value: " << *ptr << endl;

    unique_ptr<int> ptr2 = move(ptr); // transfer ownership
    cout << "Value via ptr2: " << *ptr2 << endl;

    return 0;
}
/* 
Output:
Value: 100
Value via ptr2: 100
*/


8️⃣ Smart Pointer: shared_ptr & weak_ptr (C++11)
#include <iostream>
#include <memory>
using namespace std;
int main() {
    shared_ptr<int> sp1 = make_shared<int>(200);
    shared_ptr<int> sp2 = sp1; // shared ownership

    cout << "sp1: " << *sp1 << ", sp2: " << *sp2 << endl;
    cout << "Use count: " << sp1.use_count() << endl;

    weak_ptr<int> wp = sp1; // non-owning pointer
    cout << "wp expired? " << (wp.expired() ? "Yes" : "No") << endl;

    sp1.reset(); // release one shared_ptr
    cout << "Use count after sp1.reset(): " << sp2.use_count() << endl;

    return 0;
}
/* 
Output:
sp1: 200, sp2: 200
Use count: 2
wp expired? No
Use count after sp1.reset(): 1
*/


9️⃣ Custom Deleter with unique_ptr (C++11)
#include <iostream>
#include <memory>
using namespace std;
int main() {
    auto deleter = [](int* p){ cout << "Deleting " << *p << endl; delete p; };
    unique_ptr<int, decltype(deleter)> ptr(new int(300), deleter);

    return 0;
}
/* 
Output:
Deleting 300
*/


🔟 Pointer and Lambda Capture
#include <iostream>
using namespace std;
int main() {
    int a = 5;
    auto doubleValue = [&a]() { a *= 2; };
    doubleValue();

    cout << "Value of a after lambda: " << a << endl;

    return 0;
}
/* 
Output:
Value of a after lambda: 10
*/


1️⃣1️⃣ std::addressof (C++11)
#include <iostream>
#include <memory>
using namespace std;
int main() {
    int x = 10;
    int* p = addressof(x);

    cout << "Address of x: " << p << endl;

    return 0;
}
/* 
Output:
Address of x: 0x7ffee3bff5ac
*/


1️⃣2️⃣ Const Pointers
#include <iostream>
using namespace std;
int main() {
    int a = 5, b = 10;
    const int* p1 = &a; // pointer to const int
    // *p1 = 6; // Error: cannot modify via p1
    p1 = &b; // OK

    int* const p2 = &a; // const pointer to int
    *p2 = 6; // OK
    // p2 = &b; // Error: cannot change pointer

    cout << "*p1: " << *p1 << ", *p2: " << *p2 << endl;

    return 0;
}
/* 
Output:
*p1: 10, *p2: 6
*/


1️⃣3️⃣ Pointer to Class Members
#include <iostream>
using namespace std;
struct S {
    int x;
};
int main() {
    S obj{42};
    int S::*px = &S::x;

    cout << "Value of x via pointer to member: " << obj.*px << endl;

    return 0;
}
/* 
Output:
Value of x via pointer to member: 42
*/


1️⃣4️⃣ std::to_address (C++20)
#include <iostream>
#include <memory>
using namespace std;
int main() {
    int x = 500;
    int* p = &x;

    int* addr = to_address(p); // C++20
    cout << "Value via to_address: " << *addr << endl;

    return 0;
}
/* 
Output:
Value via to_address: 500
*/


1️⃣5️⃣ Pointers with Ranges/Iterators (C++20)
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v{1,2,3};
    for(auto p = v.begin(); p != v.end(); ++p)
        cout << *p << ' ';
    cout << endl;

    return 0;
}
/* 
Output:
1 2 3
*/


1️⃣6️⃣ std::span (C++20)
#include <iostream>
#include <span>
using namespace std;
int main() {
    int arr[] = {10,20,30};
    span<int> s(arr);

    for(auto x : s)
        cout << x << ' ';
    cout << endl;

    return 0;
}
/* 
Output:
10 20 30
*/



| **Concept**                        | **Description**                               | **C++ Version** | **Example Code**                                                                                      | **Output** |
| ---------------------------------- | --------------------------------------------- | --------------- | ----------------------------------------------------------------------------------------------------- | ---------- |
| **Basic Pointer**                  | Pointer stores address of a variable          | C++11+          | `cpp\nint a=10;\nint* ptr=&a;\ncout<<*ptr;\n`                                                         | 10         |
| **Pointer Arithmetic**             | Increment/decrement pointers, traverse arrays | C++11+          | `cpp\nint arr[]={1,2,3};\nint* p=arr;\np++;\ncout<<*p;\n`                                             | 2          |
| **Pointers and Arrays**            | Array elements accessed via pointers          | C++11+          | `cpp\nint arr[]={1,2,3};\nint* p=arr;\nfor(int i=0;i<3;i++) cout<<*(p+i)<<' ';\n`                     | 1 2 3      |
| **Pointer to Pointer**             | Pointer stores address of another pointer     | C++11+          | `cpp\nint a=5;\nint* p=&a;\nint** pp=&p;\ncout<<**pp;\n`                                              | 5          |
| **Pointers to Functions**          | Call functions via pointers                   | C++11+          | `cpp\nint add(int x,int y){return x+y;}\nint (*fp)(int,int)=add;\ncout<<fp(3,4);\n`                   | 7          |
| **nullptr**                        | Null pointer literal                          | C++11           | `cpp\nint* p=nullptr;\ncout<<(p==nullptr);\n`                                                         | 1          |
| **Smart Pointer: unique_ptr**      | Exclusive ownership, auto-delete              | C++11           | `cpp\nunique_ptr<int> p=make_unique<int>(50);\ncout<<*p;\n`                                           | 50         |
| **unique_ptr Move Semantics**      | Transfer ownership                            | C++11           | `cpp\nunique_ptr<int> p2=move(p);\ncout<<*p2;\n`                                                      | 50         |
| **Smart Pointer: shared_ptr**      | Shared ownership                              | C++11           | `cpp\nshared_ptr<int> sp1=make_shared<int>(100);\nshared_ptr<int> sp2=sp1;\ncout<<sp1.use_count();\n` | 2          |
| **weak_ptr**                       | Non-owning pointer to shared_ptr              | C++11           | `cpp\nweak_ptr<int> wp=sp1;\ncout<<wp.expired();\n`                                                   | 0 (false)  |
| **Custom deleter with unique_ptr** | Custom cleanup                                | C++11           | `cpp\nunique_ptr<int,void(*)(int*)> p(new int(10),[](int* ptr){cout<<\"Deleting\"; delete ptr;});\n`  | Deleting   |
| **Pointer and lambda**             | Lambda capturing pointer                      | C++11           | `cpp\nint a=5;\na=[&a]{a*=2;}();\ncout<<a;\n`                                                         | 10         |
| **std::addressof**                 | Get true address ignoring operator& overload  | C++11           | `cpp\nint x=10;\ncout<<addressof(x);\n`                                                               | 0x...      |
| **Const Pointers**                 | `int* const p` vs `const int* p`              | C++11+          | `cpp\nint a=5;\nconst int* p=&a;\nint b=10;\np=&b;\n`                                                 | -          |
| **Pointer to Class Members**       | Access via `->*` / `.*`                       | C++11+          | `cpp\nstruct S{int x;};\nint S::*px=&S::x;\nS s{s};\ncout<<s.*px;\n`                                  | 5          |
| **std::to_address**                | Get address from fancy pointer                | C++20           | `cpp\nint x=100;\nint* p=&x;\ncout<<*to_address(p);\n`                                                | 100        |
| **Pointer and Ranges/Views**       | Access via iterators (C++20)                  | C++20           | `cpp\nvector<int> v{1,2,3};\nfor(auto p=v.begin();p!=v.end();++p) cout<<*p<<' ';\n`                   | 1 2 3      |
| **std::span**                      | Lightweight view over array/pointer           | C++20           | `cpp\nint arr[]={1,2,3};\nspan<int> s(arr);\nfor(auto x:s) cout<<x<<' ';\n`                           | 1 2 3      |
