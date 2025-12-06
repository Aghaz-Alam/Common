1️⃣ Basic Reference

A reference is an alias to an existing variable.

#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int& ref = a;  // reference to a

    cout << "Value of a: " << a << endl;
    cout << "Value via ref: " << ref << endl;

    ref = 20;  // modify value via reference
    cout << "New value of a: " << a << endl;

    return 0;
}


Output:

Value of a: 10
Value via ref: 10
New value of a: 20

2️⃣ Const Reference
#include <iostream>
using namespace std;

int main() {
    int a = 50;
    const int& ref = a;  // read-only reference

    cout << "Value via const ref: " << ref << endl;
    // ref = 100; // Error: cannot modify

    return 0;
}


Output:

Value via const ref: 50


Use case: Pass large objects efficiently to functions without copying.

3️⃣ Reference as Function Parameter
#include <iostream>
using namespace std;

void increment(int& x) {  // pass by reference
    x += 10;
}

int main() {
    int a = 5;
    increment(a);
    cout << "After increment: " << a << endl;
    return 0;
}


Output:

After increment: 15

4️⃣ Reference as Function Return Value
#include <iostream>
using namespace std;

int& getValue(int& x) {
    return x;  // return reference
}

int main() {
    int a = 100;
    int& ref = getValue(a);
    ref += 50;
    cout << "Value of a after modification: " << a << endl;
    return 0;
}


Output:

Value of a after modification: 150

5️⃣ Reference to Array
#include <iostream>
using namespace std;

int main() {
    int arr[3] = {1,2,3};
    int (&ref)[3] = arr;  // reference to array

    for(int i=0; i<3; i++)
        cout << ref[i] << ' ';
    cout << endl;

    return 0;
}


Output:

1 2 3

6️⃣ Rvalue References (C++11)

Rvalue references allow moving resources instead of copying.

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1 = {1,2,3};
    vector<int> v2 = move(v1);  // move constructor

    cout << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;

    return 0;
}


Output:

v1 size: 0
v2 size: 3


Use case: Perfect for performance optimization with large objects.

7️⃣ Rvalue References as Function Parameters (C++11)
#include <iostream>
#include <string>
using namespace std;

void printString(string&& s) {
    cout << "String: " << s << endl;
}

int main() {
    printString("Hello Rvalue");  // rvalue passed directly
    string str = "Lvalue";
    // printString(str); // Error: lvalue cannot bind to rvalue reference
    printString(move(str)); // OK: move converts to rvalue

    return 0;
}


Output:

String: Hello Rvalue
String: Lvalue

8️⃣ Universal (Forwarding) References (C++11)
#include <iostream>
#include <utility>
using namespace std;

template <typename T>
void forwardExample(T&& val) {  // universal reference
    T copy = val;
    cout << "Value: " << copy << endl;
}

int main() {
    int x = 10;
    forwardExample(x);      // lvalue
    forwardExample(20);     // rvalue

    return 0;
}


Output:

Value: 10
Value: 20


Use case: Perfect for perfect forwarding in templates.

9️⃣ Reference Collapsing (C++11)

T& & → T&

T& && → T&

T&& & → T&

T&& && → T&&

#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int& lref = a;
    int&& rref = 10;

    int& ref1 = lref;   // T& &
    int& ref2 = rref;   // T&& &
    int&& ref3 = 20;    // T&& &&
    
    cout << ref1 << " " << ref2 << " " << ref3 << endl;
    return 0;
}


Output:

5 10 20

🔟 Reference with auto (C++11+)
#include <iostream>
using namespace std;

int main() {
    int a = 50;
    auto& ref = a;  // auto deduces reference type
    ref += 10;

    cout << "Value of a: " << a << endl;
    return 0;
}


Output:

Value of a: 60

1️⃣1️⃣ Structured Bindings with References (C++17)
#include <iostream>
#include <tuple>
using namespace std;

int main() {
    tuple<int,int> t(1,2);
    auto& [x,y] = t;  // reference binding

    x += 10;
    cout << "Tuple values: " << get<0>(t) << ", " << get<1>(t) << endl;

    return 0;
}


Output:

Tuple values: 11, 2

1️⃣2️⃣ Reference and std::span (C++20)
#include <iostream>
#include <span>
using namespace std;

int main() {
    int arr[] = {1,2,3};
    span<int> s(arr);
    for(int& x : s) x *= 2;  // reference to span element

    for(auto x : s) cout << x << ' ';
    cout << endl;

    return 0;
}


Output:

2 4 6


✅ This covers all reference concepts from basic → advanced → modern C++20, including:
Basic reference
Const reference
Reference in functions
Array references
Rvalue references
Universal references
Reference collapsing
auto and structured bindings
References with std::span





#include <iostream>
#include <vector>
#include <tuple>
#include <span>
#include <string>
#include <utility> // for move
using namespace std;

// 1️⃣ Basic Reference
void basicReference() {
    cout << "\n--- Basic Reference ---\n";
    int a = 10;
    int& ref = a;
    cout << "Value of a: " << a << endl;
    cout << "Value via ref: " << ref << endl;
    ref = 20;
    cout << "New value of a: " << a << endl;
}

// 2️⃣ Const Reference
void constReference() {
    cout << "\n--- Const Reference ---\n";
    int a = 50;
    const int& ref = a;
    cout << "Value via const ref: " << ref << endl;
}

// 3️⃣ Reference as Function Parameter
void increment(int& x) { x += 10; }
void referenceParameter() {
    cout << "\n--- Reference as Function Parameter ---\n";
    int a = 5;
    increment(a);
    cout << "After increment: " << a << endl;
}

// 4️⃣ Reference as Function Return
int& getValue(int& x) { return x; }
void referenceReturn() {
    cout << "\n--- Reference as Function Return ---\n";
    int a = 100;
    int& ref = getValue(a);
    ref += 50;
    cout << "Value of a after modification: " << a << endl;
}

// 5️⃣ Reference to Array
void referenceArray() {
    cout << "\n--- Reference to Array ---\n";
    int arr[3] = {1,2,3};
    int (&ref)[3] = arr;
    for(int i=0; i<3; i++) cout << ref[i] << ' ';
    cout << endl;
}

// 6️⃣ Rvalue Reference (C++11)
void rvalueReference() {
    cout << "\n--- Rvalue Reference (C++11) ---\n";
    vector<int> v1 = {1,2,3};
    vector<int> v2 = move(v1);
    cout << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;
}

// 7️⃣ Rvalue Reference as Function Parameter
void printString(string&& s) { cout << "String: " << s << endl; }
void rvalueFunctionParameter() {
    cout << "\n--- Rvalue Reference as Function Parameter ---\n";
    printString("Hello Rvalue");
    string str = "Lvalue";
    printString(move(str));
}

// 8️⃣ Universal (Forwarding) Reference
template <typename T>
void forwardExample(T&& val) {
    T copy = val;
    cout << "Value: " << copy << endl;
}
void universalReference() {
    cout << "\n--- Universal (Forwarding) Reference ---\n";
    int x = 10;
    forwardExample(x);
    forwardExample(20);
}

// 9️⃣ Reference Collapsing
void referenceCollapsing() {
    cout << "\n--- Reference Collapsing ---\n";
    int a = 5;
    int& lref = a;
    int&& rref = 10;
    int& ref1 = lref;   
    int& ref2 = rref;   
    int&& ref3 = 20;    
    cout << ref1 << " " << ref2 << " " << ref3 << endl;
}

// 🔟 Reference with auto
void referenceAuto() {
    cout << "\n--- Reference with auto ---\n";
    int a = 50;
    auto& ref = a;
    ref += 10;
    cout << "Value of a: " << a << endl;
}

// 1️⃣1️⃣ Structured Bindings with References (C++17)
void structuredBindings() {
    cout << "\n--- Structured Bindings with References (C++17) ---\n";
    tuple<int,int> t(1,2);
    auto& [x,y] = t;
    x += 10;
    cout << "Tuple values: " << get<0>(t) << ", " << get<1>(t) << endl;
}

// 1️⃣2️⃣ Reference with std::span (C++20)
void referenceSpan() {
    cout << "\n--- Reference with std::span (C++20) ---\n";
    int arr[] = {1,2,3};
    span<int> s(arr);
    for(int& x : s) x *= 2;
    for(auto x : s) cout << x << ' ';
    cout << endl;
}

// Menu
int main() {
    int choice;
    do {
        cout << "\n===== Reference Examples Menu =====\n";
        cout << "1. Basic Reference\n2. Const Reference\n3. Reference as Function Parameter\n";
        cout << "4. Reference as Function Return\n5. Reference to Array\n6. Rvalue Reference (C++11)\n";
        cout << "7. Rvalue Reference as Function Parameter\n8. Universal Reference\n";
        cout << "9. Reference Collapsing\n10. Reference with auto\n";
        cout << "11. Structured Bindings with References (C++17)\n";
        cout << "12. Reference with std::span (C++20)\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: basicReference(); break;
            case 2: constReference(); break;
            case 3: referenceParameter(); break;
            case 4: referenceReturn(); break;
            case 5: referenceArray(); break;
            case 6: rvalueReference(); break;
            case 7: rvalueFunctionParameter(); break;
            case 8: universalReference(); break;
            case 9: referenceCollapsing(); break;
            case 10: referenceAuto(); break;
            case 11: structuredBindings(); break;
            case 12: referenceSpan(); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while(choice != 0);

    return 0;
}





#include <iostream>
#include <memory>
#include <vector>
#include <span>
#include <string>
using namespace std;

// 1️⃣ Basic Pointer
void basicPointer() {
    cout << "\n--- Basic Pointer ---\n";
    int a = 10;
    int* ptr = &a;
    cout << "Value of a: " << a << endl;
    cout << "Value via pointer: " << *ptr << endl;
    *ptr = 20;
    cout << "New value of a: " << a << endl;
}

// 2️⃣ Pointer Arithmetic
void pointerArithmetic() {
    cout << "\n--- Pointer Arithmetic ---\n";
    int arr[] = {10,20,30,40};
    int* ptr = arr;
    cout << "First element: " << *ptr << endl;
    ptr++;
    cout << "Second element: " << *ptr << endl;
    ptr += 2;
    cout << "Fourth element: " << *ptr << endl;
}

// 3️⃣ Pointer and Arrays
void pointerArray() {
    cout << "\n--- Pointer and Arrays ---\n";
    int arr[] = {1,2,3,4,5};
    int* ptr = arr;
    for(int i=0;i<5;i++) cout << *(ptr+i) << ' ';
    cout << endl;
}

// 4️⃣ Pointer to Pointer
void pointerToPointer() {
    cout << "\n--- Pointer to Pointer ---\n";
    int a = 50;
    int* ptr = &a;
    int** pptr = &ptr;
    cout << "Value via pptr: " << **pptr << endl;
}

// 5️⃣ Pointer to Function
void greet() { cout << "Hello from function!" << endl; }
int add(int a,int b) { return a+b; }
void pointerFunction() {
    cout << "\n--- Pointer to Function ---\n";
    void (*fptr)() = greet;
    fptr();
    int (*aptr)(int,int) = add;
    cout << "Sum via function pointer: " << aptr(5,10) << endl;
}

// 6️⃣ nullptr
void pointerNullptr() {
    cout << "\n--- nullptr ---\n";
    int* ptr = nullptr;
    if(ptr == nullptr) cout << "Pointer is null" << endl;
}

// 7️⃣ unique_ptr
void uniquePtrExample() {
    cout << "\n--- unique_ptr ---\n";
    unique_ptr<int> ptr = make_unique<int>(100);
    cout << "Value via unique_ptr: " << *ptr << endl;
    unique_ptr<int> ptr2 = move(ptr);
    cout << "Value via moved unique_ptr: " << *ptr2 << endl;
}

// 8️⃣ shared_ptr and weak_ptr
void sharedWeakPtrExample() {
    cout << "\n--- shared_ptr and weak_ptr ---\n";
    shared_ptr<int> sp1 = make_shared<int>(200);
    shared_ptr<int> sp2 = sp1;
    cout << "sp1: " << *sp1 << ", sp2: " << *sp2 << endl;
    cout << "Use count: " << sp1.use_count() << endl;
    weak_ptr<int> wp = sp1;
    cout << "wp expired? " << (wp.expired() ? "Yes":"No") << endl;
    sp1.reset();
    cout << "Use count after sp1.reset(): " << sp2.use_count() << endl;
}

// 9️⃣ Custom deleter with unique_ptr
void uniquePtrCustomDeleter() {
    cout << "\n--- unique_ptr with Custom Deleter ---\n";
    auto deleter = [](int* p){ cout << "Deleting " << *p << endl; delete p; };
    unique_ptr<int, decltype(deleter)> ptr(new int(300), deleter);
}

// 🔟 Pointer and Lambda
void pointerLambda() {
    cout << "\n--- Pointer and Lambda ---\n";
    int a = 5;
    auto doubleValue = [&a](){ a *= 2; };
    doubleValue();
    cout << "Value after lambda: " << a << endl;
}

// 1️⃣1️⃣ std::addressof
void pointerAddressof() {
    cout << "\n--- std::addressof ---\n";
    int x = 10;
    int* p = addressof(x);
    cout << "Address via addressof: " << p << endl;
}

// 1️⃣2️⃣ Const Pointers
void constPointers() {
    cout << "\n--- Const Pointers ---\n";
    int a = 5, b=10;
    const int* p1 = &a;
    p1 = &b;
    int* const p2 = &a;
    *p2 = 6;
    cout << "*p1: " << *p1 << ", *p2: " << *p2 << endl;
}

// 1️⃣3️⃣ Pointer to Class Members
struct S { int x; };
void pointerToClassMember() {
    cout << "\n--- Pointer to Class Members ---\n";
    S obj{42};
    int S::*px = &S::x;
    cout << "Value via pointer to member: " << obj.*px << endl;
}

// 1️⃣4️⃣ std::to_address (C++20)
void pointerToAddress() {
    cout << "\n--- std::to_address (C++20) ---\n";
    int x = 500;
    int* p = &x;
    int* addr = to_address(p);
    cout << "Value via to_address: " << *addr << endl;
}

// 1️⃣5️⃣ Pointers with Iterators/Ranges (C++20)
void pointerIterators() {
    cout << "\n--- Pointers with Iterators (C++20) ---\n";
    vector<int> v{1,2,3};
    for(auto p=v.begin(); p!=v.end(); ++p) cout << *p << ' ';
    cout << endl;
}

// 1️⃣6️⃣ std::span (C++20)
void pointerSpan() {
    cout << "\n--- std::span (C++20) ---\n";
    int arr[]={10,20,30};
    span<int> s(arr);
    for(auto x : s) cout << x << ' ';
    cout << endl;
}

// Menu
int main() {
    int choice;
    do {
        cout << "\n===== Pointer Examples Menu =====\n";
        cout << "1. Basic Pointer\n2. Pointer Arithmetic\n3. Pointer and Arrays\n";
        cout << "4. Pointer to Pointer\n5. Pointer to Function\n6. nullptr\n";
        cout << "7. unique_ptr\n8. shared_ptr & weak_ptr\n9. unique_ptr with Custom Deleter\n";
        cout << "10. Pointer and Lambda\n11. std::addressof\n12. Const Pointers\n";
        cout << "13. Pointer to Class Members\n14. std::to_address (C++20)\n";
        cout << "15. Pointers with Iterators (C++20)\n16. std::span (C++20)\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: basicPointer(); break;
            case 2: pointerArithmetic(); break;
            case 3: pointerArray(); break;
            case 4: pointerToPointer(); break;
            case 5: pointerFunction(); break;
            case 6: pointerNullptr(); break;
            case 7: uniquePtrExample(); break;
            case 8: sharedWeakPtrExample(); break;
            case 9: uniquePtrCustomDeleter(); break;
            case 10: pointerLambda(); break;
            case 11: pointerAddressof(); break;
            case 12: constPointers(); break;
            case 13: pointerToClassMember(); break;
            case 14: pointerToAddress(); break;
            case 15: pointerIterators(); break;
            case 16: pointerSpan(); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }

    } while(choice != 0);

    return 0;
}




#include <iostream>
#include <vector>
#include <tuple>
#include <span>
#include <string>
#include <memory>
#include <utility>
using namespace std;

// ================= POINTER EXAMPLES =================

// 1️⃣ Basic Pointer
void basicPointer() {
    cout << "\n--- Basic Pointer ---\n";
    int a = 10;
    int* ptr = &a;
    cout << "Value of a: " << a << endl;
    cout << "Value via pointer: " << *ptr << endl;
    *ptr = 20;
    cout << "New value of a: " << a << endl;
}

// 2️⃣ Pointer Arithmetic
void pointerArithmetic() {
    cout << "\n--- Pointer Arithmetic ---\n";
    int arr[] = {10,20,30,40};
    int* ptr = arr;
    cout << "First element: " << *ptr << endl;
    ptr++;
    cout << "Second element: " << *ptr << endl;
    ptr += 2;
    cout << "Fourth element: " << *ptr << endl;
}

// 3️⃣ Pointer to Pointer
void pointerToPointer() {
    cout << "\n--- Pointer to Pointer ---\n";
    int a = 50;
    int* ptr = &a;
    int** pptr = &ptr;
    cout << "Value via pptr: " << **pptr << endl;
}

// 4️⃣ Pointer to Function
void greet() { cout << "Hello from function!" << endl; }
int add(int a,int b) { return a+b; }
void pointerFunction() {
    cout << "\n--- Pointer to Function ---\n";
    void (*fptr)() = greet;
    fptr();
    int (*aptr)(int,int) = add;
    cout << "Sum via function pointer: " << aptr(5,10) << endl;
}

// 5️⃣ nullptr
void pointerNullptr() {
    cout << "\n--- nullptr ---\n";
    int* ptr = nullptr;
    if(ptr == nullptr) cout << "Pointer is null" << endl;
}

// 6️⃣ unique_ptr
void uniquePtrExample() {
    cout << "\n--- unique_ptr ---\n";
    unique_ptr<int> ptr = make_unique<int>(100);
    cout << "Value via unique_ptr: " << *ptr << endl;
    unique_ptr<int> ptr2 = move(ptr);
    cout << "Value via moved unique_ptr: " << *ptr2 << endl;
}

// 7️⃣ shared_ptr and weak_ptr
void sharedWeakPtrExample() {
    cout << "\n--- shared_ptr and weak_ptr ---\n";
    shared_ptr<int> sp1 = make_shared<int>(200);
    shared_ptr<int> sp2 = sp1;
    cout << "sp1: " << *sp1 << ", sp2: " << *sp2 << endl;
    cout << "Use count: " << sp1.use_count() << endl;
    weak_ptr<int> wp = sp1;
    cout << "wp expired? " << (wp.expired() ? "Yes":"No") << endl;
    sp1.reset();
    cout << "Use count after sp1.reset(): " << sp2.use_count() << endl;
}

// 8️⃣ Pointer and Lambda
void pointerLambda() {
    cout << "\n--- Pointer and Lambda ---\n";
    int a = 5;
    auto doubleValue = [&a](){ a *= 2; };
    doubleValue();
    cout << "Value after lambda: " << a << endl;
}

// 9️⃣ std::addressof
void pointerAddressof() {
    cout << "\n--- std::addressof ---\n";
    int x = 10;
    int* p = addressof(x);
    cout << "Address via addressof: " << p << endl;
}

// 🔟 Const Pointers
void constPointers() {
    cout << "\n--- Const Pointers ---\n";
    int a = 5, b=10;
    const int* p1 = &a;
    p1 = &b;
    int* const p2 = &a;
    *p2 = 6;
    cout << "*p1: " << *p1 << ", *p2: " << *p2 << endl;
}

// 1️⃣1️⃣ Pointer to Class Members
struct S { int x; };
void pointerToClassMember() {
    cout << "\n--- Pointer to Class Members ---\n";
    S obj{42};
    int S::*px = &S::x;
    cout << "Value via pointer to member: " << obj.*px << endl;
}

// 1️⃣2️⃣ std::to_address (C++20)
void pointerToAddress() {
    cout << "\n--- std::to_address (C++20) ---\n";
    int x = 500;
    int* p = &x;
    int* addr = to_address(p);
    cout << "Value via to_address: " << *addr << endl;
}

// 1️⃣3️⃣ std::span (C++20)
void pointerSpan() {
    cout << "\n--- std::span (C++20) ---\n";
    int arr[]={10,20,30};
    span<int> s(arr);
    for(auto x : s) cout << x << ' ';
    cout << endl;
}

// ================= REFERENCE EXAMPLES =================

// 1️⃣ Basic Reference
void basicReference() {
    cout << "\n--- Basic Reference ---\n";
    int a = 10;
    int& ref = a;
    cout << "Value of a: " << a << endl;
    cout << "Value via ref: " << ref << endl;
    ref = 20;
    cout << "New value of a: " << a << endl;
}

// 2️⃣ Const Reference
void constReference() {
    cout << "\n--- Const Reference ---\n";
    int a = 50;
    const int& ref = a;
    cout << "Value via const ref: " << ref << endl;
}

// 3️⃣ Reference as Function Parameter
void increment(int& x) { x += 10; }
void referenceParameter() {
    cout << "\n--- Reference as Function Parameter ---\n";
    int a = 5;
    increment(a);
    cout << "After increment: " << a << endl;
}

// 4️⃣ Reference as Function Return
int& getValue(int& x) { return x; }
void referenceReturn() {
    cout << "\n--- Reference as Function Return ---\n";
    int a = 100;
    int& ref = getValue(a);
    ref += 50;
    cout << "Value of a after modification: " << a << endl;
}

// 5️⃣ Reference to Array
void referenceArray() {
    cout << "\n--- Reference to Array ---\n";
    int arr[3] = {1,2,3};
    int (&ref)[3] = arr;
    for(int i=0; i<3; i++) cout << ref[i] << ' ';
    cout << endl;
}

// 6️⃣ Rvalue Reference (C++11)
void rvalueReference() {
    cout << "\n--- Rvalue Reference (C++11) ---\n";
    vector<int> v1 = {1,2,3};
    vector<int> v2 = move(v1);
    cout << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;
}

// 7️⃣ Rvalue Reference as Function Parameter
void printString(string&& s) { cout << "String: " << s << endl; }
void rvalueFunctionParameter() {
    cout << "\n--- Rvalue Reference as Function Parameter ---\n";
    printString("Hello Rvalue");
    string str = "Lvalue";
    printString(move(str));
}

// 8️⃣ Universal Reference
template <typename T>
void forwardExample(T&& val) {
    T copy = val;
    cout << "Value: " << copy << endl;
}
void universalReference() {
    cout << "\n--- Universal (Forwarding) Reference ---\n";
    int x = 10;
    forwardExample(x);
    forwardExample(20);
}

// 9️⃣ Reference Collapsing
void referenceCollapsing() {
    cout << "\n--- Reference Collapsing ---\n";
    int a = 5;
    int& lref = a;
    int&& rref = 10;
    int& ref1 = lref;   
    int& ref2 = rref;   
    int&& ref3 = 20;    
    cout << ref1 << " " << ref2 << " " << ref3 << endl;
}

// 🔟 Reference with auto
void referenceAuto() {
    cout << "\n--- Reference with auto ---\n";
    int a = 50;
    auto& ref = a;
    ref += 10;
    cout << "Value of a: " << a << endl;
}

// 1️⃣1️⃣ Structured Bindings with References (C++17)
void structuredBindings() {
    cout << "\n--- Structured Bindings with References (C++17) ---\n";
    tuple<int,int> t(1,2);
    auto& [x,y] = t;
    x += 10;
    cout << "Tuple values: " << get<0>(t) << ", " << get<1>(t) << endl;
}

// 1️⃣2️⃣ Reference with std::span (C++20)
void referenceSpan() {
    cout << "\n--- Reference with std::span (C++20) ---\n";
    int arr[] = {1,2,3};
    span<int> s(arr);
    for(int& x : s) x *= 2;
    for(auto x : s) cout << x << ' ';
    cout << endl;
}

// ================= MENU SYSTEM =================

int main() {
    int choice;
    do {
        cout << "\n===== Pointers & References Menu =====\n";
        cout << "--- POINTER EXAMPLES ---\n";
        cout << "1. Basic Pointer\n2. Pointer Arithmetic\n3. Pointer to Pointer\n";
        cout << "4. Pointer to Function\n5. nullptr\n6. unique_ptr\n";
        cout << "7. shared_ptr & weak_ptr\n8. Pointer and Lambda\n9. std::addressof\n";
        cout << "10. Const Pointers\n11. Pointer to Class Members\n12. std::to_address\n";
        cout << "13. std::span (C++20)\n";
        cout << "--- REFERENCE EXAMPLES ---\n";
        cout << "14. Basic Reference\n15. Const Reference\n16. Reference as Function Parameter\n";
        cout << "17. Reference as Function Return\n18. Reference to Array\n19. Rvalue Reference\n";
        cout << "20. Rvalue Reference as Function Parameter\n21. Universal Reference\n";
        cout << "22. Reference Collapsing\n23. Reference with auto\n24. Structured Bindings\n";
        cout << "25. Reference with std::span\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: basicPointer(); break;
            case 2: pointerArithmetic(); break;
            case 3: pointerToPointer(); break;
            case 4: pointerFunction(); break;
            case 5: pointerNullptr(); break;
            case 6: uniquePtrExample(); break;
            case 7: sharedWeakPtrExample(); break;
            case 8: pointerLambda(); break;
            case 9: pointerAddressof(); break;
            case 10: constPointers(); break;
            case 11: pointerToClassMember(); break;
            case 12: pointerToAddress(); break;
            case 13: pointerSpan(); break;
            case 14: basicReference(); break;
            case 15: constReference(); break;
            case 16: referenceParameter(); break;
            case 17: referenceReturn(); break;
            case 18: referenceArray(); break;
            case 19: rvalueReference(); break;
            case 20: rvalueFunctionParameter(); break;
            case 21: universalReference(); break;
            case 22: referenceCollapsing(); break;
            case 23: referenceAuto(); break;
            case 24: structuredBindings(); break;
            case 25: referenceSpan(); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while(choice != 0);

    return 0;
}












1️⃣ Pointer vs Reference
#include <iostream>
using namespace std;

int main() {
    int x = 10;

    // Pointer
    int* p = &x;
    cout << "Pointer p points to value: " << *p << endl;
    *p = 20; // modify through pointer
    cout << "After modifying through pointer, x = " << x << endl;

    // Reference
    int& r = x;
    cout << "Reference r refers to value: " << r << endl;
    r = 30; // modify through reference
    cout << "After modifying through reference, x = " << x << endl;

    // Pointer can be reassigned
    int y = 50;
    p = &y;
    cout << "Pointer p now points to y: " << *p << endl;

    // Reference cannot be reseated
    // int& r2 = y; // This would create a new reference, r still points to x

    return 0;
}
/* 
Output:
Pointer p points to value: 10
After modifying through pointer, x = 20
Reference r refers to value: 20
After modifying through reference, x = 30
Pointer p now points to y: 50
*/


2️⃣ Memory Management (Raw Pointer Example)
#include <iostream>
using namespace std;

int main() {
    // Allocate memory dynamically
    int* p = new int(100);
    cout << "Dynamically allocated value: " << *p << endl;

    // Modify value
    *p = 200;
    cout << "Modified value: " << *p << endl;

    // Free memory
    delete p;

    // Dangling pointer (unsafe)
    // cout << *p << endl; // Undefined behavior

    return 0;
}
/* 
Output:
Dynamically allocated value: 100
Modified value: 200

✅ Note: Accessing *p after delete is undefined behavior.
*/


3️⃣ unique_ptr Example
#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> ptr = make_unique<int>(42);
    cout << "Unique pointer value: " << *ptr << endl;

    // Modify value
    *ptr = 50;
    cout << "Modified value: " << *ptr << endl;

    // Transfer ownership
    unique_ptr<int> ptr2 = move(ptr);
    if(!ptr) cout << "ptr is now nullptr after move" << endl;
    cout << "ptr2 now owns value: " << *ptr2 << endl;

    return 0;
}
/* 
Output:
Unique pointer value: 42
Modified value: 50
ptr is now nullptr after move
ptr2 now owns value: 50
*/



4️⃣ shared_ptr Example
#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> sp1 = make_shared<int>(100);
    cout << "Shared pointer sp1 value: " << *sp1 << endl;

    shared_ptr<int> sp2 = sp1; // shared ownership
    cout << "Shared pointer sp2 value: " << *sp2 << endl;

    cout << "Use count: " << sp1.use_count() << endl;

    *sp2 = 200;
    cout << "Modified value through sp2: " << *sp1 << endl;

    return 0;
}
/* 
Output:
Shared pointer sp1 value: 100
Shared pointer sp2 value: 100
Use count: 2
Modified value through sp2: 200
*/


5️⃣ Rvalue References & Move Semantics
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1 = {1, 2, 3, 4};
    cout << "Original v1: ";
    for(auto x : v1) cout << x << " ";
    cout << endl;

    // Move v1 to v2
    vector<int> v2 = move(v1);

    cout << "After move, v1 size: " << v1.size() << endl; // v1 is empty
    cout << "v2 contains: ";
    for(auto x : v2) cout << x << " ";
    cout << endl;

    return 0;
}
/* 
Output:
Original v1: 1 2 3 4
After move, v1 size: 0
v2 contains: 1 2 3 4

✅ Key: move() avoids copying large vectors; resources are transferred.
*/



6️⃣ std::span Example (C++20)
#include <iostream>
#include <vector>
#include <span>
using namespace std;

int main() {
    vector<int> vec = {10, 20, 30, 40, 50};

    // Create a span (non-owning view)
    span<int> s(vec);

    cout << "Span elements: ";
    for(auto x : s) cout << x << " ";
    cout << endl;

    // Modify through span
    s[0] = 100;
    cout << "Modified vector through span: ";
    for(auto x : vec) cout << x << " ";
    cout << endl;

    return 0;
}
/* 
Output:
Span elements: 10 20 30 40 50
Modified vector through span: 100 20 30 40 50

✅ Key: span is safe and lightweight, does not own the memory, avoids copying.
*/