//Strict aliasing safe swap using std::launder (C++17 nuance)
// ch14_launder.cpp
#include <iostream>
#include <new>
#include <utility>
using namespace std;
struct A { 
    int x; 
};
struct B { 
    int x; 
};
int main() {
    alignas(A) unsigned char buf[sizeof(A)];
    A* pa = new(buf) A{5};
    // reinterpret as B; use std::launder when object representation reused
    B* pb = reinterpret_cast<B*>(pa);
    cout << pb->x << "\n"; // reading common initial sequence is ok for trivial layout
    pa->~A();
}
/* 
Output
5
*/

Why: careful with reinterpret_cast; std::launder can be needed in complex cases. 
This example keeps UB risk minimal by using trivially copyable types.

Why be careful with reinterpret_cast
and why std::launder may be needed
1️⃣ What reinterpret_cast really does
T* p = reinterpret_cast<T*>(raw_memory);


reinterpret_cast does NOT:
Create an object
Start object lifetime
Guarantee aliasing legality
It only reinterprets bits as a different type.
👉 The compiler is free to assume type-based aliasing rules.




2️⃣ The real danger: object lifetime & aliasing
UB happens when:
You access memory as type T
But no T object’s lifetime has begun there
Or you access it through an old pointer after placement-new





3️⃣ Example: subtle UB without std::launder
#include <new>
struct S { 
    int x; 
};
alignas(S) unsigned char buf[sizeof(S)];
int main() {
    S* p = new (buf) S{10};
    p->x = 20;
    // Reconstruct object in same storage
    p = new (buf) S{30};
    int v = p->x;   // ❌ may be UB without launder
}
/* 
Why UB?
The compiler may assume:
“p still refers to the old object”
But the old object was destroyed and a new one was created.
*/




4️⃣ What std::launder does
#include <new>
p = std::launder(reinterpret_cast<S*>(buf));

std::launder:
Tells the compiler:
“A new object of type S lives here now.”

Prevents invalid pointer caching
Restores defined behavior




5️⃣ Correct version (defined behavior)
#include <iostream>
#include <new>
struct S { 
    int x; 
};
int main() {
    alignas(S) unsigned char buf[sizeof(S)];

    S* p = new (buf) S{10};
    std::cout << p->x << "\n";

    p->~S();  // end lifetime

    new (buf) S{42};

    S* q = std::launder(reinterpret_cast<S*>(buf));
    std::cout << q->x << "\n";
}
/* 
Output
10
42
*/


6️⃣ Why reinterpret_cast alone is insufficient
reinterpret_cast:
Does not account for:
Lifetime changes
Strict aliasing
Compiler optimizations

Compiler optimization example:
int a = p->x;
new (buf) S{20};
int b = p->x;  // compiler may reuse a

The compiler assumes p->x cannot change.





7️⃣ Why trivially copyable types reduce risk
Trivially copyable types:
Can be memcpy-ed
Have no user-defined destructor
Have predictable object representation

struct POD { int x; double y; };  // trivially copyable

Why safer:
No destructor/lifetime side-effects
Bitwise copy is allowed
Often tolerated in low-level code
⚠️ But still not a free pass.




8️⃣ Trivially copyable ≠ lifetime-safe
This is still UB without lifetime start:

unsigned char buf[sizeof(int)];
int* p = reinterpret_cast<int*>(buf);
*p = 10;  // ❌ lifetime not started

Correct way:
int* p = new (buf) int(10);




9️⃣ When std::launder is required (summary)
You need std::launder when:
| Situation                          | Need launder |
| ---------------------------------- | ------------ |
| Placement-new over same storage    | ✅            |
| Reusing union storage              | ✅            |
| Type-punning with lifetime restart | ✅            |
| Accessing through old pointer      | ✅            |
| First-time placement-new           | ❌            |
| Plain `memcpy` into active object  | ❌            |





🔟 Memory model diagram
Before reconstruction
buf:
+--------+
| S{10}  | ← p
+--------+

After placement-new (without launder)
buf:
+--------+
| S{42}  | ← compiler thinks p still old
+--------+

After std::launder
buf:
+--------+
| S{42}  | ← q (laundered pointer)
+--------+




11️⃣ Why this matters in real systems
Used in:
Memory pools
Custom allocators
Object caches
Lock-free data structures
Embedded systems
Serialization engines



🔥 Interview-ready explanation (perfect answer)
reinterpret_cast only reinterprets bits; it does not start object lifetime or inform the compiler about placement-new reconstruction.
When an object is destroyed and a new one is constructed in the same storage, accessing it through an old pointer is undefined behavior unless std::launder is used.
Using trivially copyable types reduces risk because their representations are simple, but lifetime rules still apply.