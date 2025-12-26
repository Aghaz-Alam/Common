Below is a **comprehensive set of pointer challenges in C++**, ordered from **fundamental** to **hardcore/UB-level**.

Each challenge is **independent**, with:

* 📌 Concept
* 💥 Challenge / trap
* ✅ Complete program (`main()` included)
* 🖨️ Output (or allowed behavior)
* 🧠 Explanation


## 1️⃣ Basic Pointer Dereference
### 📌 Concept
Pointer stores address, `*` dereferences.
#include <iostream>
int main() {
    int x = 10;
    int* p = &x;
    std::cout << *p << "\n";
}
/* 
**Output**
10
*/




## 2️⃣ Null Pointer Dereference (UB)
#include <iostream>
int main() {
    int* p = nullptr;
    // std::cout << *p; // ❌ UB, UB = Undefined Behavior
}
/* 
**Output**: ❌ Undefined behavior (may crash)
*/





## 3️⃣ Pointer Reassignment vs Value Change
#include <iostream>
int main() {
    int a = 5, b = 7;
    int* p = &a;
    p = &b;
    std::cout << *p;
}
/* 
**Output**
7
*/





## 4️⃣ Pointer Arithmetic (Array Traversal)
#include <iostream>
int main() {
    int arr[] = {1,2,3};
    int* p = arr;
    std::cout << *(p+1);
}
/* 
**Output**
2
*/






## 5️⃣ Out-of-Bounds Pointer Arithmetic (UB)
#include <iostream>
int main() {
    int arr[3] = {1,2,3};
    int* p = arr + 5;
    // std::cout << *p; // ❌ UB, UB = Undefined Behavior
}




## 6️⃣ Pointer vs Array Name
#include <iostream>
int main() {
    int arr[3];
    int* p = arr;
    std::cout << (p == arr);
}
/* 
**Output**
1
*/





## 7️⃣ sizeof(pointer) vs sizeof(array)
#include <iostream>
int main() {
    int arr[10];
    int* p = arr;
    std::cout << sizeof(arr) << " " << sizeof(p);
}
/* 
**Output (64-bit)**
40 8
*/



## 8️⃣ Dangling Pointer (Stack)
#include <iostream>
int* foo() {
    int x = 10;
    return &x; // ❌ dangling
}
int main() {
    int* p = foo();
    // std::cout << *p; // UB, UB = Undefined Behavior
}





## 9️⃣ Dangling Pointer (Heap Free)
#include <iostream>
int main() {
    int* p = new int(5);
    delete p;
    // std::cout << *p; // ❌ UB, UB = Undefined Behavior
}





## 🔟 Double Delete (UB)
#include <iostream>
int main() {
    int* p = new int(10);
    delete p;
    // delete p; // ❌ UB, UB = Undefined Behavior
}






## 1️⃣1️⃣ Memory Leak
#include <iostream>
int main() {
    int* p = new int(5);
    p = nullptr; // leaked
}




## 1️⃣2️⃣ Const Pointer vs Pointer to Const
#include <iostream>
int main() {
    int x = 5, y = 10;
    const int* p1 = &x;   // value const
    int* const p2 = &x;   // pointer const
    p1 = &y;
    *p2 = 20;
    std::cout << x;
}
/* 
**Output**
20
*/




## 1️⃣3️⃣ Pointer to Pointer
#include <iostream>
int main() {
    int x = 5;
    int* p = &x;
    int** pp = &p;
    std::cout << **pp;
}
/* 
**Output**
5
*/




## 1️⃣4️⃣ Void Pointer
#include <iostream>
int main() {
    int x = 42;
    void* p = &x;
    std::cout << *(static_cast<int*>(p));
}
/* 
**Output**
42
*/




## 1️⃣5️⃣ Function Pointer
#include <iostream>
void foo() { std::cout << "Hello"; }
int main() {
    void (*fp)() = foo;
    fp();
}
/* 
**Output**
Hello
*/




## 1️⃣6️⃣ Pointer Aliasing Violation (Strict Aliasing UB)
#include <iostream>
int main() {
    int x = 0x3f800000;
    float* f = reinterpret_cast<float*>(&x);
    std::cout << *f; // ❌ UB,     UB = Undefined Behavior
}
/* 
1
*/




## 1️⃣7️⃣ Reinterpret Cast Trap
#include <iostream>
int main() {
    int x = 65;
    char* p = reinterpret_cast<char*>(&x);
    std::cout << *p;
}
/* 
**Output** (endianness dependent)
A or garbage
*/




## 1️⃣8️⃣ Pointer Comparison (Same Array Only)
#include <iostream>
int main() {
    int a[2], b[2];
    std::cout << (&a[0] < &b[0]); // ❌ UB = Undefined Behavior
}
/* 
0
*/



## 1️⃣9️⃣ Wild Pointer
#include <iostream>
int main() {
    int* p; // uninitialized
    // std::cout << *p; // ❌ UB = Undefined Behavior
}
/* 
493120961
*/



## 2️⃣0️⃣ Pointer Lifetime vs Object Lifetime
#include <iostream>
struct A { int x; };
int main() {
    alignas(A) char buf[sizeof(A)];
    A* p = new(buf) A{10};
    p->~A();
    std::cout << p->x; // ❌ UB
}
/* 
10
*/

# 🏆 FINAL POINTER CHALLENGE SUMMARY

| Category    | Risk                |
| ----------- | ------------------- |
| Null / wild | Crash               |
| Dangling    | Silent corruption   |
| Aliasing    | Compiler miscompile |
| Arithmetic  | UB                  |
| Lifetime    | Hardest bugs        |






//UB = Undefined Behavior

This level focuses on **where experienced C++ developers still fail**:

• Pointer + **object lifetime**
• Pointer + **compiler optimizations**
• Pointer + **memory model UB**
• Pointer + **aliasing rules**

Each challenge is **independent**, with full `main()` and outcome.

---

## 2️⃣1️⃣ Pointer Publication Without Synchronization (UB)  //UB = Undefined Behavior

### Concept

Publishing a pointer without a happens-before edge.

```cpp
#include <thread>
#include <iostream>
using namespace std;

int* p;

void writer() {
    int* x = new int(42);
    p = x;              // ❌ data race
}

void reader() {
    while (!p) {}
    cout << *p << '\n';
}

int main() {
    p = nullptr;
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
```

**Result**: ❌ Undefined behavior (may print garbage or crash)

---

## 2️⃣2️⃣ FIXED: Atomic Pointer Publication

```cpp
#include <atomic>
#include <thread>
#include <iostream>
using namespace std;

atomic<int*> p;

void writer() {
    int* x = new int(42);
    p.store(x, memory_order_release);
}

void reader() {
    int* local;
    while (!(local = p.load(memory_order_acquire))) {}
    cout << *local << '\n';
}

int main() {
    p.store(nullptr);
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
```

**Output**

```
42
```

---

## 2️⃣3️⃣ Strict Aliasing Optimizer Trap

### Concept

Compiler assumes different pointer types do NOT alias.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 0;
    float* f = reinterpret_cast<float*>(&x);
    *f = 1.0f;
    cout << x << '\n'; // ❌ UB,   UB = Undefined Behavior
}
```

**Result**: ❌ Compiler may print `0`

---

## 2️⃣4️⃣ FIXED: memcpy Type Punning

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int x;
    float f = 1.0f;
    memcpy(&x, &f, sizeof(int));
    cout << x << '\n';
}
```

**Output**: Implementation-defined but **not UB**

---

## 2️⃣5️⃣ Pointer Past Object Lifetime

```cpp
#include <iostream>
using namespace std;

struct A { int x; };

int main() {
    A* p;
    {
        A a{10};
        p = &a;
    }
    cout << p->x; // ❌ UB, UB = Undefined Behavior
}
```

---

## 2️⃣6️⃣ Placement New Lifetime Reset

```cpp
#include <iostream>
using namespace std;

struct A { int x; };

int main() {
    alignas(A) char buf[sizeof(A)];
    A* p = new(buf) A{10};
    p->~A();
    p = new(buf) A{20};
    cout << p->x;
}
```

**Output**

```
20
```

---

## 2️⃣7️⃣ Pointer Comparison Across Objects (UB)

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << (&a < &b); // ❌ UB, UB = Undefined Behavior
}
```

---

## 2️⃣8️⃣ Pointer Arithmetic on `void*` (Non-Standard)

```cpp
#include <iostream>
using namespace std;

int main() {
    void* p = malloc(10);
    // p++; // ❌ illegal in C++
}
```

---

## 2️⃣9️⃣ Pointer Escapes Before Initialization

```cpp
#include <thread>
#include <iostream>
using namespace std;

struct Data { int x; };
Data* p;

void publish() {
    p = new Data;      // published
    p->x = 10;         // too late
}

void consume() {
    while (!p) {}
    cout << p->x;      // ❌ UB, UB = Undefined Behavior
}

int main() {
    p = nullptr;
    thread t1(publish), t2(consume);
    t1.join(); t2.join();
}
```

---

## 3️⃣0️⃣ FIXED: Safe Publication

```cpp
#include <atomic>
#include <thread>
#include <iostream>
using namespace std;

struct Data { int x; };
atomic<Data*> p;

void publish() {
    Data* d = new Data{10};
    p.store(d, memory_order_release);
}

void consume() {
    Data* d;
    while (!(d = p.load(memory_order_acquire))) {}
    cout << d->x;
}

int main() {
    p.store(nullptr);
    thread t1(publish), t2(consume);
    t1.join(); t2.join();
}
```

**Output**

```
10
```

---

# 🏆 NEXT POINTER LEVEL SUMMARY

| Area        | Risk                 |
| ----------- | -------------------- |
| Lifetime    | Silent corruption    |
| Aliasing    | Optimizer miscompile |
| Publication | Data races           |
| Comparison  | UB                   |

---

### Ready for the next descent?

🔥 **POINTER × MULTITHREADING (ABA, hazard pointers)**
🔥 **MISRA pointer bans & rules**
🔥 **Compiler disassembly proof (Godbolt-style)**

Say **NEXT POINTER BOSS** ⚔️










🔥 PART 1 — 20 UB Prediction Interview Problems
🔥 UB #1 — Use After Free
#include <iostream>
int main() {
    int* p = new int(10);
    delete p;
    std::cout << *p << "\n";
}
/* 
❌ UB Reason
Accessing memory after object lifetime ends.

❓ Output
➡️ Undefined (may print 10, garbage, crash)
*/

/* 
🔥 UB #2 — Dereferencing NULL
#include <iostream>
int main() {
    int* p = nullptr;
    std::cout << *p;
}

❌ UB Reason
Null pointer dereference.

❓ Output
➡️ Crash / undefined
*/


🔥 UB #3 — Uninitialized Variable
#include <iostream>
int main() {
    int x;
    std::cout << x;
}
/* 
❌ UB Reason
Reading indeterminate value.

❓ Output
➡️ Garbage / anything
*/


🔥 UB #4 — Out-of-Bounds Access
#include <iostream>
int main() {
    int a[3] = {1,2,3};
    std::cout << a[5];
}
/* 
❌ UB Reason
Array bounds violation.

❓ Output
➡️ Undefined
*/


🔥 UB #5 — Strict Aliasing Violation
#include <iostream>
int main() {
    float f = 1.23f;
    int* p = (int*)&f;
    std::cout << *p;
}
/* 
❌ UB Reason
Illegal type punning.
*/


🔥 UB #6 — i = i++
#include <iostream>
int main() {
    int i = 1;
    i = i++;
    std::cout << i;
}
/* 
❌ UB Reason
Unsequenced modification & read.
*/



🔥 UB #7 — Double Delete
#include <iostream>
int main() {
    int* p = new int(5);
    delete p;
    delete p;
}
/* 
❌ UB Reason
Double free.
*/



🔥 UB #8 — Mismatched delete
#include <iostream>
int main() {
    int* p = new int[5];
    delete p;
}
/* 
❌ UB Reason
Must use delete[].
*/


🔥 UB #9 — Dangling Reference
#include <iostream>
int& foo() {
    int x = 10;
    return x;
}
int main() {
    int& r = foo();
    std::cout << r;
}
/* 
❌ UB Reason
Reference to destroyed object.
*/



🔥 UB #10 — Signed Overflow
#include <iostream>
int main() {
    int x = INT32_MAX;
    x += 1;
    std::cout << x;
}
/* 
❌ UB Reason
Signed integer overflow.
*/



🔥 UB #11 — Reinterpret Cast Object
#include <iostream>
struct A { 
    int x; 
};
struct B { 
    double y; 
};
int main() {
    A a{10};
    B* b = reinterpret_cast<B*>(&a);
    std::cout << b->y;
}
/* 
❌ UB Reason
Accessing wrong object type.
*/

/* ------------------------------ */
✅ Correct Fix #1 — Use the Correct Type (Best Fix)
If you actually want a B, create a B.

#include <iostream>
struct A {
    int x;
};
struct B {
    double y;
};
int main() {
    B b{3.14};
    std::cout << b.y;
}

✔ Defined behavior
✔ Zero hacks
✔ Best practice



✅ Correct Fix #2 — Use a Common Layout Type (If Sharing Memory)
If your intention is to interpret the same memory safely, use a union or standard-layout wrapper.
Using union (Still restricted, but defined in limited cases)

#include <iostream>
union U {
    int x;
    double y;
};
int main() {
    U u;
    u.y = 3.14;          // Active member is y
    std::cout << u.y;   // ✅ OK
}
⚠️ Reading inactive union members is still tricky and limited.



✅ Correct Fix #3 — Use std::memcpy (Type-Punning Safely)
This is the interview gold standard.
#include <iostream>
#include <cstring>
struct A {
    int x;
};
struct B {
    double y;
};
int main() {
    A a{0};

    B b;
    std::memcpy(&b, &a, sizeof(double));  // Only if size/layout make sense

    std::cout << b.y;  // ✅ Defined (but value may be meaningless)
}
/* 
✔ Obeys aliasing rules
✔ No UB
❗ Semantic meaning still questionable
*/

❌ What Is NOT a Fix (Still UB)
B b = *reinterpret_cast<B*>(&a);  // ❌ Still UB
auto& br = reinterpret_cast<B&>(a);  // ❌ Still UB
static_cast<B*>(&a);  // ❌ Illegal cast

🔥 Interview One-Liner Answer
reinterpret_cast does not create an object.
Accessing memory as a different type without a valid object violates strict aliasing and causes undefined behavior.

/* ================================================================= */

🔥 UB #12 — Reading Past String
#include <iostream>
int main() {
    char s[] = "abc";
    std::cout << s[10];
}
/* 
❌ UB Reason
Out-of-bounds read.
*/


🔥 UB #13 — memcpy Non-Trivial Object
#include <iostream>
#include <string>
#include <cstring>
int main() {
    std::string a = "hello";
    std::string b;
    memcpy(&b, &a, sizeof(std::string));
}
/* 
❌ UB Reason
Bypassing constructors.
*/



🔥 UB #14 — Access After move
#include <iostream>
#include <string>
int main() {
    std::string a = "hi";
    std::string b = std::move(a);
    std::cout << a[0];
}
/* 
❌ UB Reason
Moved-from object state unspecified.
*/



🔥 UB #15 — Invalid Alignment
#include <iostream>
int main() {
    char buf[8];
    int* p = (int*)(buf + 1);
    *p = 10;
}
/* 
❌ UB Reason
Misaligned access.
*/


🔥 UB #16 — Free stack memory
#include <iostream>
int main() {
    int x;
    int* p = &x;
    delete p;
}
/* 
❌ UB Reason
Deleting non-heap memory.
*/



🔥 UB #17 — Modify const
#include <iostream>
int main() {
    const int x = 10;
    int* p = (int*)&x;
    *p = 20;
}
/* 
❌ UB Reason
Modifying const object.
*/



🔥 UB #18 — Overlapping memcpy
#include <iostream>
#include <cstring>
int main() {
    char buf[] = "hello";
    memcpy(buf+1, buf, 4);
}
/* 
❌ UB Reason
Overlapping regions → use memmove.
*/




🔥 UB #19 — Returning pointer to local
#include <iostream>
int* foo() {
    int x = 5;
    return &x;
}
int main() {
    std::cout << *foo();
}
/* 
❌ UB Reason
Dangling pointer.
*/



🔥 UB #20 — sizeof dereference null
#include <iostream>
int main() {
    int* p = nullptr;
    std::cout << sizeof(*p);
}
/* 
✅ NOT UB
sizeof does not evaluate expression.
*/




🧵 PART 2 — Threading UB Traps (FULL Programs)
🧵 Thread UB #1 — Data Race
#include <iostream>
#include <thread>

int x = 0;

void f() { x++; }

int main() {
    std::thread t1(f), t2(f);
    t1.join(); t2.join();
    std::cout << x;
}
/* 
❌ UB Reason
Unsynchronized shared access.
*/



🧵 Thread UB #2 — Non-atomic flag
#include <thread>
#include <iostream>

bool ready = false;

void worker() {
    while (!ready) {}
}

int main() {
    std::thread t(worker);
    ready = true;
    t.join();
}
/* 
❌ UB Reason
Data race on ready.
*/




🧵 Thread UB #3 — Dangling reference to thread
#include <thread>
void start() {
    int x = 10;
    std::thread([&]{ x++; }).detach();
}
int main() {
    start();
}
/* 
❌ UB Reason
Thread uses destroyed stack variable.
*/




🧵 Thread UB #4 — Destroying mutex while locked
#include <mutex>
#include <thread>

std::mutex m;

int main() {
    m.lock();
}
/* 
❌ UB Reason
Mutex destroyed while locked.
*/



🧵 Thread UB #5 — Non-atomic double checked locking
#include <thread>

int* p = nullptr;

void init() {
    if (!p)
        p = new int(10);
}

int main() {
    std::thread t1(init), t2(init);
    t1.join(); t2.join();
}
/* 
❌ UB Reason
Data race + reordering.
*/



🧵 Thread UB #6 — Relaxed atomics misuse
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<bool> ready(false);
int data = 0;

void producer() {
    data = 42;
    ready.store(true, std::memory_order_relaxed);
}
void consumer() {
    while (!ready.load(std::memory_order_relaxed)) {}
    std::cout << data;
}
int main() {
    std::thread t1(producer), t2(consumer);
    t1.join(); t2.join();
}
/* 
❌ UB Reason
No happens-before → stale read.
*/



🧵 Thread UB #7 — Unlocking чужой mutex
#include <mutex>
std::mutex m;
int main() {
    m.unlock();
}
/* 
❌ UB Reason
Unlock without owning lock.
*/



🧵 Thread UB #8 — Access after join
#include <thread>
#include <iostream>

int* p;

void f() { p = new int(10); }

int main() {
    std::thread t(f);
    t.join();
    delete p;
    std::cout << *p;
}
/* 
❌ UB Reason
Use after free.
*/




🧵 Thread UB #9 — Race on vector
#include <vector>
#include <thread>

std::vector<int> v;

void push() { 
    v.push_back(1); 
}

int main() {
    std::thread t1(push), t2(push);
    t1.join(); 
    t2.join();
}
/* 
❌ UB Reason
Concurrent modification.
*/



🧵 Thread UB #10 — Missing join/detach
#include <thread>
int main() {
    std::thread t([]{});
}
/* 
❌ UB Reason
std::terminate called.
*/







🔥 20 ULTRA-HARD UB PUZZLES (C++)
🔥 UB #41 — Placement new without launder
#include <iostream>
#include <new>

struct A { int x; };

int main() {
    alignas(A) char buf[sizeof(A)];
    A* p = new (buf) A{1};
    p->~A();
    new (buf) A{2};
    std::cout << p->x;
}
/* 
❌ UB Reason
Old pointer must be std::laundered.
 */



🔥 UB #42 — Reading inactive union member
#include <iostream>
union U {
    int i;
    float f;
};

int main() {
    U u;
    u.i = 42;
    std::cout << u.f;
}
/* 
❌ UB Reason
Reading inactive union member.
 */




🔥 UB #43 — Modifying string literal
#include <iostream>
int main() {
    char* p = (char*)"hello";
    p[0] = 'H';
}
/* 
❌ UB Reason
String literals are immutable.
*/


🔥 UB #44 — Pointer past object
#include <iostream>
int main() {
    int x = 10;
    int* p = &x + 1;
    std::cout << *p;
}
/* 
❌ UB Reason
Dereferencing one-past-the-end.
 */



🔥 UB #45 — Lifetime not started
#include <iostream>
#include <cstdlib>

struct A { int x; };

int main() {
    void* mem = malloc(sizeof(A));
    A* a = static_cast<A*>(mem);
    std::cout << a->x;
}
/* 
❌ UB Reason
Object not constructed.
 */



🔥 UB #46 — reinterpret_cast reference
#include <iostream>
int main() {
    double d = 3.14;
    int& r = reinterpret_cast<int&>(d);
    std::cout << r;
}
/* 
❌ UB Reason
Violates strict aliasing & alignment.
 */



🔥 UB #47 — Virtual call in destructor
#include <iostream>

struct B {
    virtual void f() { std::cout << "B\n"; }
    virtual ~B() { f(); }
};

struct D : B {
    void f() override { std::cout << "D\n"; }
};

int main() {
    B* b = new D;
    delete b;
}
/* 
❌ UB Reason
Virtual dispatch during destruction uses base vtable.
 */




🔥 UB #48 — std::move + const
#include <iostream>
#include <string>

int main() {
    const std::string s = "hello";
    auto t = std::move(s);
    std::cout << s;
}
/* 
❌ UB Reason
Moving from const → copy semantics violated assumptions.
 */



🔥 UB #49 — memcpy vptr
#include <iostream>
#include <cstring>

struct A {
    virtual void f() {}
};

int main() {
    A a, b;
    memcpy(&b, &a, sizeof(A));
}
/* 
❌ UB Reason
Corrupts vtable pointer.
 */



🔥 UB #50 — delete through base without virtual dtor
#include <iostream>

struct B {
    ~B() {}
};

struct D : B {
    ~D() { std::cout << "D\n"; }
};

int main() {
    B* b = new D;
    delete b;
}
/* 
❌ UB Reason
Missing virtual destructor.
 */




🔥 UB #51 — Using pointer after realloc
#include <cstdlib>
#include <iostream>

int main() {
    int* p = (int*)malloc(4);
    int* q = (int*)realloc(p, 8);
    std::cout << *p;
}
/* 
❌ UB Reason
Old pointer invalid after realloc.
 */



🔥 UB #52 — Atomic without alignment
#include <atomic>
#include <iostream>
int main() {
    char buf[sizeof(std::atomic<int>)];
    auto* a = reinterpret_cast<std::atomic<int>*>(buf);
    a->store(1);
}
/* 
❌ UB Reason
Atomic misalignment.
*/



🔥 UB #53 — Destroying object twice
#include <iostream>
struct A {
    ~A() { std::cout << "A\n"; }
};
int main() {
    A a;
    a.~A();
}
/* 
❌ UB Reason
Automatic object destroyed again at scope exit.
*/




🔥 UB #54 — Returning reference to temporary
#include <iostream>
const int& f() {
    return 10;
}
int main() {
    std::cout << f();
}
/* 
❌ UB Reason
Dangling reference.
*/




🔥 UB #55 — Thread + non-atomic pointer publication
#include <thread>

int* p;

void writer() {
    p = new int(42);
}

void reader() {
    if (p) *p = 10;
}
int main() {
    std::thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
❌ UB Reason
Data race + reordering.
*/




🔥 UB #56 — std::vector reallocation invalidation
#include <vector>
#include <iostream>
int main() {
    std::vector<int> v{1,2,3};
    int* p = &v[0];
    v.push_back(4);
    std::cout << *p;
}
/* 
❌ UB Reason
Pointer invalidated.
*/



🔥 UB #57 — Access object after std::move
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v{1,2};
    auto u = std::move(v);
    std::cout << v[0];
}
/* 
❌ UB Reason
Moved-from container accessed.
*/



🔥 UB #58 — Thread uses destroyed object
#include <thread>
struct A {
    int x = 0;
    void run() { x++; }
};
int main() {
    A a;
    std::thread t(&A::run, &a);
}
/* 
❌ UB Reason
Thread not joined → object destroyed.
*/



🔥 UB #59 — Function pointer cast
#include <iostream>
void f(int) {}
int main() {
    void (*p)(double) = (void(*)(double))f;
    p(3.14);
}
/* 
❌ UB Reason
Calling through incompatible function type.
*/


🔥 UB #60 — Destroying polymorphic object via placement new
#include <iostream>
#include <new>

struct B { virtual ~B() {} };
struct D : B {};

int main() {
    alignas(D) char buf[sizeof(D)];
    B* b = new (buf) D;
    b->~B();
}
/* 
❌ UB Reason
Wrong destructor call for placement new.
*/
🎯 Interview Super-Rule
If you violate object lifetime, aliasing, alignment, or happens-before — the compiler is allowed to break your brain.




