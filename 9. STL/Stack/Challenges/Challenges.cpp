✅ 1. How to pass the address of a stack variable to a pointer?

You have a stack variable:

int x = 10;


To pass its address to a pointer, you simply use &x:

int* p = &x;

✔ Full Example
#include <iostream>
using namespace std;

void setTo50(int* ptr) { 
    *ptr = 50; 
}

int main() {
    int a = 10;      // stack variable
    setTo50(&a);     // pass address of stack variable
    cout << a << "\n";
}

Output
50

🔥 How to pass address of a pointer (&pointer) to a function?
void foo(int** pp) {       // pointer to pointer
    **pp = 99;
}

int main() {
    int x = 10;
    int* p = &x;

    foo(&p);               // address of pointer
    cout << x << "\n";
}

Output
99


✔ &p gives address of the pointer, not address of the integer.
✔ Used in memory managament, double-pointer APIs, smart-pointer internals.

✅ 2. How to do polymorphism on stack?

Polymorphism requires a pointer or reference, but the object itself can be on the stack.

✔ Stack-based polymorphism example:
#include <iostream>
using namespace std;

class Base {
public:
    virtual void speak() { cout << "Base\n"; }
};

class Dog : public Base {
public:
    void speak() override { cout << "Dog\n"; }
};

void call(Base& b) {  // reference → polymorphism
    b.speak();
}

int main() {
    Dog d;       // stack object
    call(d);     // polymorphism
}

Output
Dog


✔ Polymorphism works using Base& or Base*.
✔ The derived object can still be on the stack.

🔥 Stack polymorphism (object slicing mistake)

If you do by value, polymorphism breaks:

void call(Base b) {   // ❌ slicing
    b.speak();
}


❌ Always use references or pointers, not values.

💥 List of 20 coding challenges (stack, pointers, polymorphism, &pointer)

Below are 20 advanced challenges with full code + main + output.

🔥 Challenge 1 — Pass &pointer (pointer to pointer)
#include <iostream>
using namespace std;

void change(int** pp) {
    static int y = 200;
    *pp = &y;
}

int main() {
    int x = 10;
    int* p = &x;

    change(&p);

    cout << *p << "\n";
}

Output
200

🔥 Challenge 2 — Polymorphism with stack objects using references
#include <iostream>
using namespace std;

class A { public: virtual void f(){ cout<<"A\n"; } };
class B: public A { public: void f(){ cout<<"B\n"; } };

void process(A& obj) { obj.f(); }

int main() {
    B b;
    process(b);
}

Output
B

🔥 Challenge 3 — Wrong: object slicing
#include <iostream>
using namespace std;

class A { public: virtual void f(){ cout<<"A\n"; } };
class B: public A { public: void f(){ cout<<"B\n"; } };

void process(A obj) { obj.f(); }

int main() {
    B b;
    process(b);   // sliced
}

Output
A

🔥 Challenge 4 — Passing reference to pointer (int&)*
void modify(int*& p) {
    static int y = 500;
    p = &y;
}

int main() {
    int x = 10;
    int* p = &x;

    modify(p);
    cout << *p << "\n";
}

Output
500

🔥 Challenge 5 — Function returning pointer to stack (Wrong!)
int* bad() {
    int a = 10;
    return &a;   // ❌ dangerous
}

Output
Undefined behavior

🔥 Challenge 6 — Fix with static variable
int* good() {
    static int a = 10;
    return &a;   // ✔ OK
}

🔥 Challenge 7 — Base pointer, derived stack object
class Base { public: virtual void f(){ cout<<"Base\n"; } };
class D : public Base { public: void f(){ cout<<"Derived\n"; } };

int main() {
    D d;
    Base* b = &d;    // stack → OK
    b->f();
}

Output
Derived

🔥 Challenge 8 — Reference collapsing with templates
template<typename T>
void foo(T&& x) {
    cout << (is_lvalue_reference<T>::value ? "L" : "R") << "\n";
}

int main() {
    int a = 5;
    foo(a);   // L
    foo(10);  // R
}

Output
L
R

🔥 Challenge 9 — Polymorphism using stack array of objects
Base* arr[3];
Dog d; Cat c; Base b;
arr[0]=&d; arr[1]=&c; arr[2]=&b;

🔥 Challenge 10 — Pointer to pointer polymorphism
void call(Base** pp) {
    (*pp)->f();
}

🔥 Challenge 11 — Polymorphic factory returning stack objects (WRONG)

Cannot return stack references stored inside function.

🔥 Challenge 12 — Correct: return pointer to static polymorphic objects
Base* factory() {
    static Dog d;
    return &d;
}

🔥 Challenge 13 — Dynamic dispatch through reference wrapper
void invoke(Base& b) { b.f(); }

🔥 Challenge 14 — Swapping pointer targets using pointer to pointer
void swapPtr(int** p1, int** p2) {
    int* tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

🔥 Challenge 15 — Return reference to stack object (compile error)
int& bad() {
    int x = 10;
    return x;      // ❌
}

🔥 Challenge 16 — Reference to pointer const correctness
void foo(int* const &p) { /* p constant, *p modifiable */ }

🔥 Challenge 17 — Pointer aliasing showing tricky stack behavior
🔥 Challenge 18 — Polymorphism on stack inside container
vector<Base*> v = {&d1, &d2};

🔥 Challenge 19 — Using std::reference_wrapper for polymorphism
🔥 Challenge 20 — Perfect forwarding + stack polymorphism
template<typename T>
void forwardCall(T&& obj) {
    call(std::forward<T>(obj));
}



/* ===================================================== */

PART 1 — MEMORY MODEL DIAGRAMS (STACK POLYMORPHISM)
A. Normal virtual polymorphism layout (object on stack)
class Base { 
    virtual void f(); 
    int x; 
};
class Derived : public Base { 
    int y; 
};

When you do:
Derived d;  // on STACK
Base* b = &d;

Memory Diagram
STACK AREA
+---------------------------+
| d (Derived object)        |
|   +---------------------+ |
|   | vptr ---> ----------|--------+
|   +---------------------+ |      |
|   | Base::x             | |      |
|   +---------------------+ |      |
|   | Derived::y          | |      |
+---------------------------+      |
                                   |
HEAP: (none)                       |
                                   |
VIRTUAL METHOD TABLE (vtable) <----+
+-------------------------------+
|  vtable for Derived           |
|   [0] &Derived::f()           |
|   [1] &Base::~Base()          |
+-------------------------------+


✔ Polymorphism works even though the object is on stack.
✔ vptr is inside the stack object.




🔥 PART 2 — 20 FULL CHALLENGES WITH CODE + OUTPUT + EXPLANATION
✅ Challenge 1 — Passing &pointer (pointer-to-pointer)
#include <iostream>
using namespace std;
void change(int** pp) {
    static int y = 200;
    *pp = &y;  // redirect pointer
}
int main() {
    int x = 10;
    int* p = &x;

    change(&p);

    cout << *p << "\n";
}
/* 
Output
200

Explanation
change(&p) passes address of pointer, so *pp is p.
Memory:

STACK
x = 10
p → x

After change:
p → static y (200)
*/



✅ Challenge 2 — Stack-based polymorphism using reference
#include <iostream>
using namespace std;

class A { public: virtual void f(){ cout<<"A\n"; } };
class B : public A { public: void f(){ cout<<"B\n"; } };

void call(A& obj) { obj.f(); }

int main() {
    B b;     // stack object
    call(b); // polymorphism
}
/* 
Output
B

✔ No slicing — using reference.
 */



✅ Challenge 3 — Object slicing (WRONG polymorphism)
#include <iostream>
using namespace std;

class A { public: virtual void f(){ cout<<"A\n"; } };
class B: public A{ public: void f(){ cout<<"B\n"; } };

void call(A obj) { obj.f(); }

int main() {
    B b;
    call(b);    // sliced → calls A::f
}
/* 
Output
A
 */





✅ Challenge 4 — Passing pointer by reference (int&)*
#include <iostream>
using namespace std;

void modify(int*& p) {
    static int z = 500;
    p = &z;
}

int main() {
    int a = 10;
    int* p = &a;

    modify(p);
    cout << *p << "\n";
}
/* 
Output
500
 */





✅ Challenge 5 — Pointer-to-pointer allocation
#include <iostream>
using namespace std;

void allocate(int** pp) {
    *pp = new int(77);
}

int main() {
    int* p = nullptr;

    allocate(&p);
    cout << *p << "\n";

    delete p;
}
/* 
Output
77
 */







✅ Challenge 6 — Wrong: returning pointer to stack
int* bad() {
    int a = 10;
    return &a;   // ❌ DEAD after function ends
}
/* 
Output: undefined behavior

Memory:
STACK
a dies after function → pointer invalid
 */





✅ Challenge 7 — Correct: static lifetime
#include <iostream>
using namespace std;

int* good() {
    static int a = 10;
    return &a;
}

int main() {
    cout << *good() << "\n";
}
/* 
Output
10
 */







✅ Challenge 8 — Stack object, base pointer polymorphism
#include <iostream>
using namespace std;

class Base { public: virtual void f(){ cout<<"Base\n"; } };
class D : public Base { public: void f(){ cout<<"Derived\n"; } };

int main() {
    D d;         // stack
    Base* b = &d;

    b->f();      // polymorphism
}
/* 
Output
Derived
 */






✅ Challenge 9 — Reference collapsing with templates
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
void test(T&& x) {
    cout << (is_lvalue_reference<T>::value ? "Lvalue\n" : "Rvalue\n");
}

int main() {
    int a = 10;
    test(a);      // L
    test(50);     // R
}
/* 
Output
Lvalue
Rvalue
 */







✅ Challenge 10 — Polymorphism in array of pointers (all stack objects)
#include <iostream>
using namespace std;

class Animal { public: virtual void speak(){ cout<<"Animal\n"; } };
class Dog: public Animal { public: void speak(){ cout<<"Dog\n"; } };
class Cat: public Animal { public: void speak(){ cout<<"Cat\n"; } };

int main() {
    Dog d; Cat c; Animal a;

    Animal* arr[3] = {&d, &c, &a};

    for (auto p : arr)
        p->speak();
}
/* 
Output
Dog
Cat
Animal
 */







 ✅ Challenge 11 — Pointer-to-pointer polymorphism
#include <iostream>
using namespace std;

class Base { public: virtual void f(){ cout<<"Base\n"; } };
class D : public Base { public: void f(){ cout<<"Derived\n"; } };

void caller(Base** pp) {
    (*pp)->f();
}

int main() {
    D d;
    Base* bp = &d;

    caller(&bp);
}
/* 
Output
Derived
 */








 ✅ Challenge 12 — Static polymorphic factory
#include <iostream>
using namespace std;

class Base { public: virtual void f(){ cout<<"Base\n"; } };
class Dog : public Base { public: void f(){ cout<<"Dog\n"; } };

Base* factory() {
    static Dog d;   // static stack → OK
    return &d;
}

int main() {
    Base* p = factory();
    p->f();
}
/* 
Output
Dog
 */







✅ Challenge 13 — Reference wrapper for polymorphism
#include <iostream>
#include <functional>
using namespace std;

class A { public: virtual void f(){ cout<<"A\n"; } };
class B : public A { public: void f(){ cout<<"B\n"; } };

int main() {
    B b;

    reference_wrapper<A> r = b;  // no slicing

    r.get().f();
}
/* 
Output
B
 */







✅ Challenge 14 — Swap pointers using pointer-to-pointer
#include <iostream>
using namespace std;
void swapPtr(int** p1, int** p2) {
    int* tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
int main() {
    int a = 10, b = 20;

    int* p1 = &a;
    int* p2 = &b;

    swapPtr(&p1, &p2);

    cout << *p1 << " " << *p2 << "\n";
}
/* 
Output
20 10
 */





//✅ Challenge 15 — Wrong: return reference to stack
int& bad() {
    int x = 10;
    return x;  // ❌ invalid
}
/* 
Output: undefined behavior
 */








//✅ Challenge 16 — Const-reference-to-pointer
#include <iostream>
using namespace std;

void f(int* const &p) {
    cout << *p << "\n";  // can modify *p, cannot reassign p
}

int main() {
    int x = 42;
    int* p = &x;

    f(p);
}
/* 
Output
42
 */




//✅ Challenge 17 — Pointer aliasing demonstration
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int* p = &x;
    int* q = p;

    *q = 99;

    cout << x << " " << *p << " " << *q << "\n";
}
/* 
Output
99 99 99
 */






//✅ Challenge 18 — Vector of stack objects via pointer polymorphism
#include <iostream>
#include <vector>
using namespace std;

class Base{ public: virtual void f(){ cout<<"Base\n"; } };
class D1: public Base{ public: void f(){ cout<<"D1\n"; } };
class D2: public Base{ public: void f(){ cout<<"D2\n"; } };

int main() {
    D1 d1; D2 d2;

    vector<Base*> v = {&d1, &d2};

    for (auto p : v)
        p->f();
}
/* 
Output
D1
D2
*/






//✅ Challenge 19 — Using std::ref to prevent slicing
#include <iostream>
#include <functional>
using namespace std;
class A { public: virtual void f(){ cout<<"A\n"; } };
class B : public A { public: void f(){ cout<<"B\n"; } };
void call(A& r) { r.f(); }
int main() {
    B b;

    auto wrapped = ref(b);
    call(wrapped);
}
/* 
Output
B
*/






//✅ Challenge 20 — Perfect forwarding + polymorphic call
#include <iostream>
#include <utility>
using namespace std;

class Base{ public: virtual void f(){ cout<<"Base\n"; } };
class D: public Base{ public: void f(){ cout<<"Derived\n"; } };

void call(Base& b) { b.f(); }

template<typename T>
void forwardCall(T&& obj) {
    call(std::forward<T>(obj));
}
int main() {
    D d;
    forwardCall(d);   // lvalue
}
/* 
Output
Derived
*/