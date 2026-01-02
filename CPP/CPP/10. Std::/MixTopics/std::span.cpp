//Pointer provenance: using std::span to carry pointer + length safely (C++20 note—we emulate with pair)
// span_emulate.cpp
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct Span { T* ptr; size_t len; };

int main(){
    vector<int> v{1,2,3,4};
    Span<int> s{v.data(), v.size()};
    for(size_t i=0;i<s.len;++i) cout << s.ptr[i] << " ";
    cout<<"\n";
}
/* 
Output
1 2 3 4 
*/

Why: std::span (C++20) packages pointer + length to avoid raw pointer pitfalls?
The core problem with raw pointers.
In C/C++, a raw pointer only knows an address, not what it points to or how many elements exist.

void process(int* p) {
    // ❌ How many elements can we safely access?
}

Pitfalls of raw pointers
| Pitfall                     | What goes wrong              |
| --------------------------- | ---------------------------- |
| No size info                | Leads to buffer overruns     |
| Pointer arithmetic          | Easy to go out of bounds     |
| Lifetime ambiguity          | Pointer may outlive data     |
| Mismatched pointer + length | Bugs from passing wrong size |
| Poor self-documentation     | API intent unclear           |

Classic bugs:
process(arr);           // size lost
process(ptr + 5);       // shifted pointer, size unknown
process(nullptr);       // unchecked

What std::span is
std::span (C++20) is a non-owning view over a contiguous sequence.
Think of it as pointer + length bundled together safely.
std::span<int> s;

Internally:
struct span {
    T* ptr;
    size_t length;
};

Why std::span exists
1️⃣ It fixes the “lost size” problem
void process(std::span<int> s) {
    for (size_t i = 0; i < s.size(); ++i)
        std::cout << s[i] << " ";
}

Call sites:
int arr[5] = {1,2,3,4,5};
process(arr);                 // size known (5)

std::vector<int> v = {1,2,3};
process(v);                   // size known (3)

✔ No need to pass (ptr, size) pairs
✔ Impossible to mismatch pointer and length



2️⃣ Bounds safety (debug-mode checking)
-->s[10];          // ❌ UB with raw pointer
-->s.at(10);       // throws (debug/checked builds)
This is huge for safety-critical and embedded systems.



3️⃣ Clear API intent (readability + correctness)
Compare:
void read(int* buf, size_t len);
vs
void read(std::span<int> buf);

✔ span says:
-->contiguous memory
-->known size
-->non-owning
This improves code review, maintenance, and static analysis.




4️⃣ Prevents common pointer arithmetic bugs
void f(int* p, size_t n) {
    p += 5;    // ❌ size now wrong
}

With span:
void f(std::span<int> s) {
    s = s.subspan(5);   // ✔ size automatically adjusted
}
✔ No accidental size mismatch
✔ Safer slicing



/* =========================================================== */
❌ Problematic version (raw pointer)
#include <iostream>
using namespace std;
void f(int* p, size_t n) {
    p += 5;            // pointer moved
    // ❌ n is STILL the old size → BUG

    for (size_t i = 0; i < n; i++) {
        cout << p[i] << " ";   // out-of-bounds access possible
    }
    cout << endl;
}
int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    f(arr, 10);
}

❌ What goes wrong
p now points to arr[5]
n is still 10
Loop accesses memory past array end
Undefined behavior


/* ------------------------------ */
#include <iostream>
using namespace std;

void f(int* begin, int* end) {
    begin += 5;   // move start

    for (int* p = begin; p < end; ++p) {
        cout << *p << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    f(arr, arr + 10);
}
//6 7 8 9 10 
/* ------------------------------ */

✅ Safe version using std::span
#include <iostream>
#include <span>
using namespace std;
void f(span<int> s) {
    s = s.subspan(5);   // ✔ pointer + size updated safely

    for (int x : s) {
        cout << x << " ";
    }
    cout << endl;
}
int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,10};

    f(arr);   // array → span automatically
}
/* 
✔ Output
6 7 8 9 10
*/
/* =========================================================== */

5️⃣ Works with all contiguous containers
std::span seamlessly accepts:
-->T[N] (C arrays)
-->std::array
-->std::vector
-->std::string / std::string_view (for char)

void log(std::span<const int> s);
log(arr);
log(vec);
log(std::array<int,3>{1,2,3});




6️⃣ Zero overhead abstraction
Important for performance-critical code:
-->No heap allocation
-->No ownership
-->Same cost as (pointer, size) pair
-->Inlined and optimized by compiler

📌 Span is a safety abstraction, not a performance penalty

What std::span deliberately does NOT do
| Not provided       | Reason                   |
| ------------------ | ------------------------ |
| Ownership          | Avoid double free        |
| Lifetime extension | Keeps semantics explicit |
| Deep copy          | Cheap view only          |

So this is not a replacement for:
-->std::vector
-->std::unique_ptr
-->std::array

When to use std::span (rule of thumb)
✅ Use std::span when:
-->Function reads/writes contiguous data
-->You don’t want ownership
-->Size matters
-->You want safe slicing

void encrypt(std::span<uint8_t> buffer);

❌ Avoid when:
-->Data is non-contiguous (list, map)
-->Ownership/lifetime must be controlled
-->Data is produced/consumed dynamically


Why it’s especially important for modern C++ / safety code
Given your interest in:
-->STL internals
-->MISRA / automotive
-->memory models & pointer correctness

std::span directly addresses:
-->MISRA rule violations around raw pointers
-->Safer APIs for ECU and embedded code
-->Easier static analysis & testing

Many modern guidelines say:
-->“Accept span, not pointer + size.”