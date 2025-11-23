1. write a function to reverse a vector which is passed in argument - also tell what is better way to pass vector
2. Create thread and pass vector in that and print vector. How can we pass vector as reference in thread.


/* ------------------------------------------------------------------------------------------------------------------------------------------------- */
1. write a function to reverse a vector which is passed in argument - also tell what is better way to pass vector
✅ 1. Function to reverse a vector passed as an argument
Approach A: Pass by reference (Best for modification)
--> If you want the function to MODIFY the original vector → pass by non-const reference.
#include <vector>
#include <algorithm>
void reverseVector(std::vector<int>& v) {
    std::reverse(v.begin(), v.end());
}
Usage:
std::vector<int> vec = {1, 2, 3, 4, 5};
reverseVector(vec);


✅ 2. Best way to pass a vector?
Depends on what you want to achieve.
✔️ Case 1: You want to MODIFY the vector
➡️ Pass by reference:
void func(std::vector<int>& v);
Why?
No copying overhead
Changes reflect to caller
Fastest way for modifiable parameters


✔️ Case 2: You only need to READ the vector
➡️ Pass by const reference:
void func(const std::vector<int>& v);
Why?
Avoids copying
Prevents accidental modification
Standard for read-only parameters


✔️ Case 3: You want your function to TAKE OWNERSHIP
➡️ Pass by value, then move it or modify internally:
void func(std::vector<int> v);   // v is a copy

OR caller can move:
func(std::move(largeVector));
Used when:
You need your own copy
You intend to store the vector

Which is the BEST way for reversing?
✔️ Pass by non-const reference
Because:
You want to modify the caller’s vector
No unnecessary copy
void reverseVector(std::vector<int>& v);
This is the correct and optimal way.


🚀 Bonus: Manual reverse without std::reverse
void reverseVector(std::vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n / 2; i++) {
        std::swap(v[i], v[n - i - 1]);
    }
}
/* ---------------------------------------------------------------------------------------------------------------------------------- */

All Approaches to Pass a Vector in C++
✔️ Approach A — Pass by Reference (modifiable)
➡️ Best when function modifies the vector.
void reverseVector(std::vector<int>& v) {
    std::reverse(v.begin(), v.end());
}

Pros:
No copy
Fast
Changes reflect back
Ideal for reverse/sort/push_back etc.

✔️ Approach B — Pass by Const Reference (read-only)
➡️ Best when function only needs to read the vector.
void printVector(const std::vector<int>& v) {
    for (int x : v) std::cout << x << " ";
}

Pros:
No copy
Prevents modification
Most common in real-world code

✔️ Approach C — Pass by Value (copy semantics)
➡️ Function receives its own copy, modifications do NOT affect caller.
void reverseCopy(std::vector<int> v) {
    std::reverse(v.begin(), v.end());
    // used internally only
}

Pros:
Safe (caller data unchanged)
Good if the function needs a full copy anyway
Enables move optimization:
reverseCopy(std::move(largeVec));

✔️ Approach D — Pass by Pointer
➡️ Old C-style, not recommended unless interoperability is required.
void reversePtr(std::vector<int>* v) {
    if (!v) return;
    std::reverse(v->begin(), v->end());
}

Pros:
Can pass nullptr
Explicit "may be null" semantic

Cons:
Verbose
Less safe than references

✔️ Approach E — Pass by rvalue reference (&&)
➡️ When you want to take ownership of a temporary/movable vector.
void takeVector(std::vector<int>&& v) {
    // now v is yours; caller cannot use it
    std::reverse(v.begin(), v.end());
}

Used when:
Processing large temporary vectors
Building pipelines
Perfect forwarding scenarios



✔️ Approach F — Pass with std::span (C++20)
➡️ To pass a view of the data, not the vector itself.
void process(std::span<int> s) {
    for (int& x : s) x *= 2;
}

Call:
std::vector<int> v = {1,2,3};
process(v);   // works

Pros:
No copy
Works with arrays + vectors
Great for read/write views

✔️ Approach G — Pass Iterators instead of vector
➡️ When the function should operate on any container.
template <typename It>
void reverseRange(It begin, It end) {
    std::reverse(begin, end);
}

Call:
reverseRange(v.begin(), v.end());

Pros:
Generic
Works with vector, list, deque, array
Most flexible design






/* --------------------------------------------------------------------------------------------------------- */

2. Create thread and pass vector in that and print vector. How can we pass vector as reference in thread.

✅ Part 1 — Create a thread and pass a vector (as reference or otherwise)
C++ threads copy arguments by default.
To pass a vector by reference, you must use std::ref().

⭐ 1) Thread — Pass vector BY VALUE
#include <iostream>
#include <vector>
#include <thread>
void printVec(std::vector<int> v) {     // copy
    for (int x : v) std::cout << x << " ";
}
int main() {
    std::vector<int> v = {1,2,3,4};
    std::thread t(printVec, v);         // copied
    t.join();
  return 0;
}

⭐ 2) Thread — Pass vector BY REFERENCE (correct way)
❗ Threads always copy arguments unless wrapped in std::ref.
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
void printVec(const std::vector<int>& v) {  // reference
    for (int x : v) std::cout << x << " ";
}
int main() {
    std::vector<int> v = {1,2,3,4};

    std::thread t(printVec, std::ref(v));   // <-- pass as reference
    t.join();
  return 0;
}

⭐ 3) Thread — Pass vector using LAMBDA (captures reference)
std::vector<int> v = {1,2,3};
std::thread t([&]() {   // capture by reference
    for (int x : v) std::cout << x << " ";
});
t.join();

⭐ 4) Thread — Move the vector into the thread (std::move)
std::vector<int> v = {1,2,3};
std::thread t([](std::vector<int> v){
    for(int x: v) std::cout << x << " ";
}, std::move(v));
t.join();

Function receives rvalue → vector becomes empty outside.

⭐ 5) Thread — Pass vector pointer
void printPtr(const std::vector<int>* v) {
    for (int x : *v) std::cout << x << " ";
}
std::vector<int> v = {1,2,3};
std::thread t(printPtr, &v);  // pass pointer
t.join();


⭐ 6) Thread — Pass vector as shared_ptr
void printSP(std::shared_ptr<std::vector<int>> v) {
    for (int x : *v) std::cout << x << " ";
}
auto v = std::make_shared<std::vector<int>>(std::initializer_list<int>{1,2,3});
std::thread t(printSP, v);
t.join();


⭐ 7) Thread — Pass vector using future/promise
std::promise<std::vector<int>> p;
auto f = p.get_future();
std::thread t([&]() {
    auto v = f.get();
    for (int x : v) std::cout << x << " ";
});
p.set_value({1,2,3});  
t.join();



⭐ Summary: Passing vector in threads
| Method              | Syntax                    | Notes                 |
| ------------------- | ------------------------- | --------------------- |
| By value            | `t(print, v);`            | vector copied         |
| By reference        | `t(print, std::ref(v));`  | BEST                  |
| Using lambda        | `std::thread([&]{…});`    | simplest              |
| By move             | `t(print, std::move(v));` | ownership transfer    |
| By pointer          | `t(print, &v);`           | unsafe but legal      |
| Using shared_ptr    | `t(print, sp);`           | safe shared ownership |
| With future/promise | async-like                | advanced pattern      |

-----------------------------------------
✅ Part 2 — LIST OF ALL POSSIBLE WAYS TO PASS A VECTOR
-----------------------------------------
Here is the complete exhaustively list—every legal way in C++.

🔵 A) Pass by value
void fun(std::vector<int> v);

🔵 B) Pass by reference
void fun(std::vector<int>& v);

🔵 C) Pass by const reference
void fun(const std::vector<int>& v);

🔵 D) Pass by rvalue reference
void fun(std::vector<int>&& v);

🔵 E) Pass by pointer
void fun(std::vector<int>* v);

🔵 F) Pass by const pointer
void fun(const std::vector<int>* v);

🔵 G) Pass by unique_ptr
void fun(std::unique_ptr<std::vector<int>> v);

🔵 H) Pass by shared_ptr
void fun(std::shared_ptr<std::vector<int>> v);

🔵 I) Pass by weak_ptr
void fun(std::weak_ptr<std::vector<int>> w);

🔵 J) Pass using std::span (C++20)
void fun(std::span<int> v);

🔵 K) Pass by iterator range
template<class It>
void fun(It begin, It end);

🔵 L) Pass inside a struct/class
struct X {
    std::vector<int> v;
};

🔵 M) Pass via template type
template<typename T>
void fun(const std::vector<T>& v);

🔵 N) Pass via auto forwarding reference (universal reference)
template <typename T>
void fun(T&& v);    // could be vector&, const vector&, vector&&

🔵 O) Pass via initializer list
void fun(std::vector<int> v);

fun({1,2,3,4});

🔵 P) Pass via array-like view using std::array conversion
std::array<int,4> a = {1,2,3,4};
fun(std::vector<int>(a.begin(), a.end()));

🔵 Q) Pass via C-array → construct vector inside
void fun(const int* arr, size_t n);

🔵 R) Pass using function object / functor with operator()
struct F {
    void operator()(const std::vector<int>& v) {}
};

🔵 S) Pass using lambda capture
auto lambda = [&](auto& v){};
lambda(vec);

🔵 T) Pass using std::bind
auto f = std::bind(print, std::ref(v));
f();

🔵 U) Pass via optional
void fun(std::optional<std::vector<int>> v);

🔵 V) Pass using variant
void fun(std::variant<std::vector<int>, int> v);

🔵 W) Pass using any (type-erased)
void fun(std::any a);

🔵 X) Pass using reference_wrapper
void fun(std::reference_wrapper<std::vector<int>> v);

🔵 Y) Pass as global or static variable
std::vector<int> globalV;

🔵 Z) Pass using coroutine channels / generators (C++20/23)

(advanced)


/* ------------------------------------------------- */
🔵 A) Pass by value
void fun(std::vector<int> v);


✅ Pass by Value Example (vector is copied)
#include <iostream>
#include <vector>
using namespace std;

// Function receives a COPY of the vector
void fun(vector<int> v)
{
    cout << "Inside fun(), received vector: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";

    // Modify the vector
    v.push_back(100);
    cout << "Inside fun(), after modification: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
}

int main()
{
    vector<int> vec = {1, 2, 3, 4};

    cout << "Before calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";

    fun(vec);   // vector is copied here

    cout << "After calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";

    return 0;
}

✅ OUTPUT EXPLAINED
Before calling fun(), original vector: 1 2 3 4
Inside fun(), received vector: 1 2 3 4
Inside fun(), after modification: 1 2 3 4 100
After calling fun(), original vector: 1 2 3 4

Why the original vector did not change?
Because:
void fun(std::vector<int> v);
takes the vector by value, so a copy is created and modifications apply only inside the function.


/* ------------------------------------------------- */

🔵 B) Pass by reference
void fun(std::vector<int>& v);


✅ Pass by Reference Example (vector is NOT copied)
#include <iostream>
#include <vector>
using namespace std;
// Function receives vector BY REFERENCE (no copy)
void fun(vector<int>& v){
    cout << "Inside fun(), received vector: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
    // Modify the original vector
    v.push_back(100);
    cout << "Inside fun(), after modification: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
    cout << "Before calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
    fun(vec);   // passed by reference (no copy)
    cout << "After calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
  return 0;
}

✅ OUTPUT EXPLANATION
Before calling fun(), original vector: 1 2 3 4
Inside fun(), received vector: 1 2 3 4
Inside fun(), after modification: 1 2 3 4 100
After calling fun(), original vector: 1 2 3 4 100

Why does the original vector change?
Because:
void fun(std::vector<int>& v);
v is a reference, not a copy → modification affects the original vector in main().
/* ------------------------------------------------- */

🔵 C) Pass by const reference
void fun(const std::vector<int>& v);


✅ Pass by Const Reference Example (read-only, no copy)
#include <iostream>
#include <vector>
using namespace std;
// Function receives the vector BY CONST REFERENCE (read-only)
void fun(const vector<int>& v){
    cout << "Inside fun(), received vector: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";

    // v.push_back(100);  // ❌ ERROR: cannot modify const reference
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
    cout << "Before calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
    fun(vec);   // passed by const reference (efficient, no copy)
    cout << "After calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
  return 0;
}

✅ OUTPUT EXPLANATION
Before calling fun(), original vector: 1 2 3 4
Inside fun(), received vector: 1 2 3 4
After calling fun(), original vector: 1 2 3 4

Why the original vector stays unchanged?
Because:
void fun(const std::vector<int>& v);
const → function cannot modify the vector
& → vector is passed by reference, so no copy is made
This is the best method when you only need to read the vector.

/* ------------------------------------------------- */
🔵 D) Pass by rvalue reference
void fun(std::vector<int>&& v);


✅ D) Pass by Rvalue Reference (std::vector<int>&&)

➡️ Used when you want the function to take ownership of a temporary vector OR a moved vector.
➡️ Inside the function, the vector can be modified because it is not const.

⭐ Complete Code
#include <iostream>
#include <vector>
using namespace std;
// Function receives the vector as an RVALUE REFERENCE
void fun(vector<int>&& v){
    cout << "Inside fun(), received vector: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
    // Modify the moved vector
    v.push_back(999);
    cout << "Inside fun(), after modification: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
    cout << "Before calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
    // Call fun() by moving the vector
    fun(std::move(vec));   // vec becomes "moved-from"
    cout << "After calling fun(), original vector (moved-from): ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";  // typically empty or unspecified state
  return 0;
}

✅ OUTPUT EXPLANATION
Before calling fun(), original vector: 1 2 3 4
Inside fun(), received vector: 1 2 3 4
Inside fun(), after modification: 1 2 3 4 999
After calling fun(), original vector (moved-from):

Why does the original vector become empty?
Because:
fun(std::move(vec));
std::move(vec) turns vec into an rvalue
the vector is moved into the function
the function receives it as vector<int>&& and owns it
the original vec becomes moved-from (valid but unspecified state)

🧠 When to use vector&& ?
Use rvalue reference when:
✓ You want the function to take ownership of the vector
✓ The caller no longer needs the vector
✓ You want to avoid copying large data
✓ You want maximum performance

/* ------------------------------------------------- */

🔵 E) Pass by pointer
void fun(std::vector<int>* v);


✅ **E) Pass by Pointer
void fun(std::vector<int>* v);**

➡️ A pointer can be:
nullptr
point to a valid vector
explicitly show “may not exist”

➡️ Function can modify the original vector because it receives the address.

⭐ Complete Code
#include <iostream>
#include <vector>
using namespace std;
// Function receives a pointer to vector
void fun(vector<int>* v){
    if (v == nullptr) {
        cout << "Null pointer received!\n";
        return;
    }
    cout << "Inside fun(), received vector: ";
    for (int x : *v)
        cout << x << " ";
    cout << "\n";
    // Modify the original vector
    v->push_back(500);
    cout << "Inside fun(), after modification: ";
    for (int x : *v)
        cout << x << " ";
    cout << "\n";
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
    cout << "Before calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
    fun(&vec);   // pass address of vector
    cout << "After calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
  return 0;
}

✅ OUTPUT EXPLANATION
Before calling fun(), original vector: 1 2 3 4
Inside fun(), received vector: 1 2 3 4
Inside fun(), after modification: 1 2 3 4 500
After calling fun(), original vector: 1 2 3 4 500

Why does the original vector change?
Because:
fun(&vec);
We passed the address, so inside the function v points to the same vector.

You must dereference it:
(*v).push_back(...)
v->push_back(...)
Both are the same.

/* ------------------------------------------------- */

🔵 F) Pass by const pointer
void fun(const std::vector<int>* v);


✅ **F) Pass by Const Pointer

void fun(const std::vector<int>* v);**

✔ You pass the address of the vector
✔ Function cannot modify the vector (because of const)
✔ Function must check for nullptr

⭐ Complete Code (Pass by Const Pointer)
#include <iostream>
#include <vector>
using namespace std;
// Function receives a CONST pointer to a vector (read-only)
void fun(const vector<int>* v){
    if (v == nullptr) {
        cout << "Null pointer received!\n";
        return;
    }
    cout << "Inside fun(), received vector: ";
    for (int x : *v)
        cout << x << " ";
    cout << "\n";
    // v->push_back(100);   // ❌ ERROR: cannot modify because v is const
}
int main(){
    vector<int> vec = {1, 2, 3, 4};

    cout << "Before calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";

    fun(&vec);   // pass address of vector

    cout << "After calling fun(), original vector: ";
    for (int x : vec)
        cout << x << " ";
    cout << "\n";
  return 0;
}

✅ OUTPUT EXPLANATION
Before calling fun(), original vector: 1 2 3 4
Inside fun(), received vector: 1 2 3 4
After calling fun(), original vector: 1 2 3 4

Why the vector is unchanged?
Because the function argument:
const std::vector<int>* v

means:
pointer to a const vector
cannot modify the pointed object
but can read it safely
and pointer can be null (unlike references)

/* ------------------------------------------------- */

🔵 G) Pass by unique_ptr
void fun(std::unique_ptr<std::vector<int>> v);


G) Pass by unique_ptr
Signature:
void fun(std::unique_ptr<std::vector<int>> v);

✅ Full Working Example (Pass by unique_ptr)
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
// Function takes ownership of the unique_ptr
void fun(std::unique_ptr<std::vector<int>> v) {
    cout << "Inside fun(), received unique_ptr\n";
    // Modify vector
    v->push_back(999);
    // Print elements
    cout << "Values inside fun(): ";
    for (int x : *v) cout << x << " ";
    cout << endl;
    // When fun() ends, v is destroyed → vector is deleted automatically
}
int main() {
    // Create a unique_ptr
    std::unique_ptr<std::vector<int>> ptr =
        std::make_unique<std::vector<int>>(std::initializer_list<int>{1, 2, 3});

    cout << "Before calling fun(), ptr owns vector.\n";
    // Transfer ownership to fun()
    fun(std::move(ptr));   // mandatory: std::move
    // ptr becomes null after move
    if (!ptr)
        cout << "After fun(), ptr is NULL (ownership transferred).\n";
  return 0;
}

🔍 Understanding It
✔ unique_ptr cannot be copied

So this will NOT work:
fun(ptr);   // ❌ Error: cannot copy unique_ptr
✔ Must use std::move to transfer ownership
fun(std::move(ptr));  // ✔ OK

✔ After std::move, the original pointer becomes nullptr.
✔ The function receives full ownership and destroys memory automatically when it ends.
🧠 When to Use This?

Use pass-by-unique_ptr when:
A function must take ownership of the resource.
The original pointer must become invalid after call.
You want strong and safe RAII-based memory ownership.

/* ------------------------------------------------- */

🔵 H) Pass by shared_ptr
void fun(std::shared_ptr<std::vector<int>> v);


✅ H) Pass by shared_ptr
Signature:
void fun(std::shared_ptr<std::vector<int>> v);

⭐ Full Working Example (Pass by shared_ptr)
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
// Function receives a shared_ptr (shared ownership)
void fun(std::shared_ptr<std::vector<int>> v) {
    cout << "Inside fun(), use_count = " << v.use_count() << endl;
    // Modify vector
    v->push_back(500);
    // Print elements
    cout << "Values inside fun(): ";
    for (int x : *v) cout << x << " ";
    cout << endl;
}
int main() {
    // Create shared_ptr
    auto ptr = std::make_shared<std::vector<int>>(std::initializer_list<int>{1, 2, 3});
    cout << "Before calling fun(), use_count = " << ptr.use_count() << endl;
    // Shared ownership (copying shared_ptr)
    fun(ptr);
    cout << "After calling fun(), use_count = " << ptr.use_count() << endl;
    // Print again from main()
    cout << "Values in main(): ";
    for (int x : *ptr) cout << x << " ";
    cout << endl;
  return 0;
}

✔ Output Explanation (Conceptually)
Before calling fun(), use_count = 1
Inside fun(), use_count = 2
Values inside fun(): 1 2 3 500
After calling fun(), use_count = 1
Values in main(): 1 2 3 500

🔍 What This Demonstrates
✔ shared_ptr copies when passed — no std::move
fun(ptr);   // OK — shared ownership

✔ use_count increases inside function
Because a new shared_ptr copy is created.

✔ Both main() and fun() share the same vector
Changes inside fun() are visible in main().

✔ Memory is freed only when all shared_ptrs are destroyed
This ensures safe shared ownership.

/* ------------------------------------------------- */

🔵 I) Pass by weak_ptr
void fun(std::weak_ptr<std::vector<int>> w);


✅ I) Pass by weak_ptr
Signature:
void fun(std::weak_ptr<std::vector<int>> w);

Because weak_ptr does not own the object, we must convert it to shared_ptr using:
auto sp = w.lock();
and check if it is still valid.

⭐ Full Working Example (Pass by weak_ptr)
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
// Function receives a weak_ptr (non-owning)
void fun(std::weak_ptr<std::vector<int>> w) {
    // Convert to shared_ptr safely
    auto sp = w.lock();
    if (!sp) {
        cout << "Vector no longer exists!" << endl;
        return;
    }
    cout << "Inside fun(): weak_ptr successfully locked" << endl;
    // Modify vector
    sp->push_back(999);
    // Print elements
    cout << "Values inside fun(): ";
    for (int x : *sp) cout << x << " ";
    cout << endl;
}
int main() {
    // Create shared_ptr
    auto ptr = std::make_shared<std::vector<int>>(std::initializer_list<int>{10, 20, 30});
    // Create weak_ptr from shared_ptr
    std::weak_ptr<std::vector<int>> w = ptr;
    // Use weak_ptr
    fun(w);
    cout << "Values in main(): ";
    for (int x : *ptr) cout << x << " ";
    cout << endl;
    // Reset shared_ptr to show weak_ptr becoming expired
    ptr.reset();
    cout << "\nCalling fun() after vector is destroyed..." << endl;
    fun(w);   // Now weak_ptr is expired
  return 0;
}

🎯 Output Explanation (Conceptual)
Inside fun(): weak_ptr successfully locked
Values inside fun(): 10 20 30 999
Values in main(): 10 20 30 999

Calling fun() after vector is destroyed...
Vector no longer exists!

🔍 What This Demonstrates
✔ weak_ptr does NOT increase reference count
This avoids circular references.

✔ You must always do:
if (auto sp = w.lock()) { ... }

to safely use the object.
✔ Shows how weak_ptr becomes expired

After:
ptr.reset();
the object is destroyed.
✔ weak_ptr is used for observing, not owning

Common use cases:
Breaking circular references (shared_ptr cycles)
Cache systems
Observer/listener patterns

/* ------------------------------------------------- */

🔵 J) Pass using std::span (C++20)
void fun(std::span<int> v);

✅ Pass using std::span (C++20)
Signature:
void fun(std::span<int> v);
std::span is a non-owning view of a contiguous sequence, e.g.:
std::vector<T>
std::array<T, N>
raw array T[]
It does not copy elements and does not own memory.

⭐ Full Working Example (Pass vector using std::span)
#include <iostream>
#include <vector>
#include <span>     // C++20
using namespace std;
void fun(std::span<int> v) {
    cout << "Inside fun():\n";
    // Modify the span (modifies original vector)
    for (int& x : v) {
        x += 10;
    }
    // Print values
    cout << "Values inside fun(): ";
    for (int x : v) cout << x << " ";
    cout << endl;
}
int main() {
    vector<int> vec = {1, 2, 3, 4};
    // Pass vector directly to span
    fun(vec);
    cout << "Values in main(): ";
    for (int x : vec) cout << x << " ";
    cout << endl;
  return 0;
}
📌 Expected Output (Conceptual)
Inside fun():
Values inside fun(): 11 12 13 14
Values in main(): 11 12 13 14

🔍 Why std::span is awesome
✔ Best for read/write access without copying

Unlike:
pass by value → copies vector
pass by pointer → verbose
pass by ref → only works for vector

✔ span works with ANY contiguous data
int arr[] = {1,2,3};
fun(arr);

std::array<int,4> a = {4,5,6,7};
fun(a);

✔ span carries size information internally
No need to pass size separately.

✔ Zero overhead
Just a pointer + size → like a "safe pointer".

/* ------------------------------------------------- */

🔵 K) Pass by iterator range
template<class It>
void fun(It begin, It end);


✅ K) Pass by iterator range
Template function:
template<class It>
void fun(It begin, It end);

This is the most generic way to process any iterable container:
std::vector<T>
std::list<T>
std::deque<T>
std::array<T>
raw array (int*)
custom containers

⭐ Full Working Example (Iterator Range)
#include <iostream>
#include <vector>
#include <list>
using namespace std;
// Generic template: works for any iterator type
template<class It>
void fun(It begin, It end) {
    cout << "Inside fun(): ";
    // Print all values
    for (It it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
int main() {
    // Example 1 — vector
    vector<int> v = {10, 20, 30};
    fun(v.begin(), v.end());
    // Example 2 — list
    list<int> lst = {100, 200, 300};
    fun(lst.begin(), lst.end());
    // Example 3 — array
    int arr[] = {5, 6, 7, 8};
    fun(arr, arr + 4); // raw pointers act as iterators
  return 0;
}

📌 Expected Output
Inside fun(): 10 20 30 
Inside fun(): 100 200 300 
Inside fun(): 5 6 7 8 

🔍 Why iterator range passing is extremely powerful
✔ Works with ANY container
You are not limited to vector.

✔ Works with const and non-const iterators
fun(v.begin(), v.end());
fun(v.cbegin(), v.cend()); (read-only)

✔ Zero overhead
Iterators are lightweight wrappers over pointers.

✔ Allows partial ranges
Example:
fun(v.begin() + 1, v.end() - 1);
Processes only a slice.

/* ------------------------------------------------- */

🔵 L) Pass inside a struct/class
struct X {
    std::vector<int> v;
};



✅ L) Pass vector inside a struct/class
You defined:
struct X {
    std::vector<int> v;
};


Now let’s write:
A function that accepts X
Modify & print the vector
Show all 3 ways: pass-by-value, pass-by-reference, pass-by-const-ref
Demonstrate usage in main()

⭐ Full Working Example (Struct containing a vector)
#include <iostream>
#include <vector>
using namespace std;
struct X {
    std::vector<int> v;
};
// A) Pass struct by VALUE (copies the vector)
void funValue(X x) {
    cout << "funValue(): ";
    x.v.push_back(999);   // modifies only local copy
    for (int i : x.v) cout << i << " ";
    cout << endl;
}
// B) Pass struct by REFERENCE (modifies original)
void funRef(X& x) {
    cout << "funRef(): ";
    x.v.push_back(500);   // modifies original struct
    for (int i : x.v) cout << i << " ";
    cout << endl;
}
// C) Pass struct by CONST REFERENCE (read-only)
void funConstRef(const X& x) {
    cout << "funConstRef(): ";
    for (int i : x.v) cout << i << " ";
    cout << endl;
}
int main() {
    X obj;
    obj.v = {1, 2, 3};
    funValue(obj);      // vector copied
    funRef(obj);        // vector modified
    funConstRef(obj);   // read-only view
    cout << "After all calls, vector in main(): ";
    for (int i : obj.v) cout << i << " ";
    cout << endl;
  return 0;
}

📌 Expected Output (Conceptual)
funValue(): 1 2 3 999
funRef(): 1 2 3 500
funConstRef(): 1 2 3 500
After all calls, vector in main(): 1 2 3 500

🔍 Explanation
✔ funValue(X x)
Makes a copy of the struct → vector copied
Adds 999 only to the local copy

✔ funRef(X& x)
Works on the original struct → modifies real vector
Adds 500 to original

✔ funConstRef(const X& x)
Read-only: cannot modify vector
Best for performance when only reading

/* ------------------------------------------------- */

🔵 M) Pass via template type
template<typename T>
void fun(const std::vector<T>& v);


✅ M) Pass via template type
Function template:
template<typename T>
void fun(const std::vector<T>& v);

This allows the function to accept vectors of any type:
vector<int>
vector<double>
vector<string>
vector<MyClass>
vector<pair<int,int>>
etc.

⭐ Full Working Example (Template vector parameter)
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Generic template function for vector of any type
template<typename T>
void fun(const std::vector<T>& v) {
    cout << "fun(): ";
    for (const T& x : v) {
        cout << x << " ";
    }
    cout << endl;
}
int main() {
    // Example 1 — vector<int>
    vector<int> vi = {1, 2, 3};
    fun(vi);
    // Example 2 — vector<double>
    vector<double> vd = {1.1, 2.2, 3.3};
    fun(vd);
    // Example 3 — vector<string>
    vector<string> vs = {"hello", "world"};
    fun(vs);
  return 0;
}

📌 Expected Output
fun(): 1 2 3 
fun(): 1.1 2.2 3.3 
fun(): hello world 

🔍 Why pass-by-template is powerful?
✔ Accepts vector of any type
No need to overload function for each type.

✔ Uses const reference → no copying
Efficient for large vectors.

✔ Template works with user-defined types
Example:
struct Point { int x, y; };
vector<Point> p = {{1,2},{3,4}};
fun(p);

✔ Compiler generates only necessary instantiations
Ensures optimal performance.

/* ------------------------------------------------- */

🔵 N) Pass via auto forwarding reference (universal reference)
template <typename T>
void fun(T&& v);    // could be vector&, const vector&, vector&&



✅ N) Pass via auto forwarding reference (universal reference)
This template:
template <typename T>
void fun(T&& v);

can accept:
vector<int>& (lvalue reference)
const vector<int>& (const lvalue reference)
vector<int>&& (rvalue reference)
const vector<int>&& (rare but allowed)
This is called a forwarding reference (formerly "universal reference").

⭐ Full Working Example (Forwarding Reference)
#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;
template <typename T>
void fun(T&& v) {
    // Detect the type category at compile time
    if constexpr (std::is_lvalue_reference_v<T>) {
        cout << "fun(): received LVALUE reference\n";
    } else {
        cout << "fun(): received RVALUE reference\n";
    }
    // Print values (works for all vector types)
    cout << "Values: ";
    for (const auto& x : v) cout << x << " ";
    cout << endl;
}
int main() {
    vector<int> a = {1, 2, 3};
    cout << "Calling fun(a):\n";
    fun(a);        // lvalue → T = vector<int>&
    cout << "\nCalling fun(std::move(a)):\n";
    fun(std::move(a));  // rvalue → T = vector<int>
    cout << "\nCalling fun(vector<int>{10,20,30}):\n";
    fun(vector<int>{10,20,30});   // rvalue temporary
  return 0;
}

📌 Expected Output (Conceptual)
Calling fun(a):
fun(): received LVALUE reference
Values: 1 2 3 

Calling fun(std::move(a)):
fun(): received RVALUE reference
Values: 1 2 3 

Calling fun(vector<int>{10,20,30}):
fun(): received RVALUE reference
Values: 10 20 30 

🔍 Explanation of forwarding reference behavior
✔ For lvalues:
vector<int> v;
fun(v);

T = vector<int>&
T&& collapses to vector<int>&

✔ For rvalues:
fun(vector<int>{1,2,3});

T = vector<int>
T&& stays vector<int>&&

✔ Perfect forwarding is possible:
You can forward exactly what you received:
template <typename T>
void fun(T&& v) {
    other(std::forward<T>(v));
}

✔ Zero overhead
This avoids unnecessary copies and works with any type.

/* ------------------------------------------------- */

🔵 O) Pass via initializer list
void fun(std::vector<int> v);

fun({1,2,3,4});



✅ O) Pass via initializer list
You can pass a temporary std::vector<int> created automatically from:
fun({1, 2, 3, 4});
This works because {1,2,3,4} is implicitly converted to a temporary std::vector<int>.

⭐ Full Working Example
#include <iostream>
#include <vector>
using namespace std;
void fun(std::vector<int> v) {
    cout << "Inside fun(): ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    // Modify (does NOT affect caller because v is a copy)
    v.push_back(999);
    cout << "Modified inside fun(): ";
    for (int x : v) cout << x << " ";
    cout << endl;
}
int main() {
    // Pass initializer list directly
    fun({1, 2, 3, 4});
    // You can also use it with a vector variable
    vector<int> vec = {10, 20, 30};
    fun(vec);   // vector copied
  return 0;
}

📌 Expected Output
Inside fun(): 1 2 3 4 
Modified inside fun(): 1 2 3 4 999
Inside fun(): 10 20 30 
Modified inside fun(): 10 20 30 999

🔍 Key Points About Initializer List Passing
✔ {1,2,3,4} automatically creates a temporary vector

Compiler does:
vector<int> temp = {1,2,3,4};
fun(temp);

✔ Function receives vector by value
So vector data is copied.

✔ Modifications inside function do NOT affect caller.
✔ Only works when the function accepts:

vector<int>
const vector<int>&
vector<int>&&
std::span<int>
initializer_list<int>

/* ------------------------------------------------- */

🔵 P) Pass via array-like view using std::array conversion
std::array<int,4> a = {1,2,3,4};
fun(std::vector<int>(a.begin(), a.end()));



✅ P) Pass via array-like view using std::array → vector conversion
You stated:
std::array<int,4> a = {1,2,3,4};
fun(std::vector<int>(a.begin(), a.end()));
This creates a temporary vector from any array-like container and passes it to fun() by value.

⭐ Full Working Example
#include <iostream>
#include <vector>
#include <array>
using namespace std;
// fun receives vector by VALUE (copy)
void fun(std::vector<int> v) {
    cout << "Inside fun(): ";
    for (int x : v) cout << x << " ";
    cout << endl;
    // Modify (does NOT affect original array)
    v.push_back(100);
    cout << "Modified inside fun(): ";
    for (int x : v) cout << x << " ";
    cout << endl;
}
int main() {
    // std::array (fixed size)
    std::array<int, 4> a = {1, 2, 3, 4};
    // Convert std::array → vector and pass
    fun(std::vector<int>(a.begin(), a.end()));
    // Original array remains unchanged
    cout << "Values in main() array: ";
    for (int x : a) cout << x << " ";
    cout << endl;
  return 0;
}

📌 Expected Output
Inside fun(): 1 2 3 4 
Modified inside fun(): 1 2 3 4 100
Values in main() array: 1 2 3 4

🔍 Explanation
✔ Conversion happens here:
fun(std::vector<int>(a.begin(), a.end()));

This builds a temporary vector:
from the element range
then passes it by value

✔ std::array → std::vector conversion is common when:
You need a dynamic vector from a fixed-size array
You want to reuse a vector-only API
You want to create a vector slice from fixed data

✔ Modifications inside fun() do NOT affect the original std::array
Because a copy is made.

/* ------------------------------------------------- */
🔵 Q) Pass via C-array → construct vector inside
void fun(const int* arr, size_t n);



✅ Q) Pass via C-array → construct vector inside
Function:
void fun(const int* arr, size_t n);
You pass a raw C-array, and the function converts it into a std::vector<int> internally.

⭐ Full Working Example
#include <iostream>
#include <vector>
using namespace std;

// Function receives raw array + size
void fun(const int* arr, size_t n) {
    // Construct vector from raw array
    vector<int> v(arr, arr + n);

    cout << "Inside fun(): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Modify local vector (does NOT affect the C-array)
    v.push_back(999);

    cout << "Modified inside fun(): ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    // Raw C-style array
    int arr[] = {10, 20, 30, 40};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    // Pass C-array to function
    fun(arr, n);

    // Original C-array remains unchanged
    cout << "Values in main(): ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}

📌 Expected Output
Inside fun(): 10 20 30 40
Modified inside fun(): 10 20 30 40 999
Values in main(): 10 20 30 40

🔍 Explanation
✔ You pass:
fun(arr, n);

✔ Inside the function:
vector<int> v(arr, arr + n);

This constructs a vector from a raw pointer range.
✔ Modifying the vector does NOT affect the original raw array
Because a new vector is created.

✔ This method is useful when:
You have C APIs providing raw arrays
You are upgrading old code but want safety + convenience of std::vector
You want to wrap raw data into STL containers

/* ------------------------------------------------- */

🔵 R) Pass using function object / functor with operator()
struct F {
    void operator()(const std::vector<int>& v) {}
};



✅ Complete Code: Function Object / Functor Example
#include <iostream>
#include <vector>
using namespace std;
// Function object (Functor)
struct F {
    void operator()(const vector<int>& v) const {
        cout << "Functor called... values = ";
        for (int x : v) {
            cout << x << " ";
        }
        cout << "\n";
    }
};
// Function that accepts functor
void processVector(const vector<int>& v, F func) {
    func(v);   // calling functor
}
int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    F f;             // create functor object
    processVector(nums, f);   // pass functor to function

    return 0;
}

✅ How this works
1. Functor declaration
struct F {
    void operator()(const vector<int>& v) const {
        ...
    }
};

Overloading operator() makes the object behave like a function.
You can call it using:
F f;
f(v);

2. Passing functor to a function
void processVector(const vector<int>& v, F func) {
    func(v);  // calls F::operator()
}

3. Using the functor
F f;
processVector(nums, f);

/* ------------------------------------------------- */
🔵 S) Pass using lambda capture
auto lambda = [&](auto& v){};
lambda(vec);


✅ Complete Code: Pass Using Lambda Capture
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> vec = {10, 20, 30};
    int multiplier = 5;
    // Lambda with capture
    auto lambda = [&](auto& v) {
        cout << "Lambda called...\n";
        cout << "Captured multiplier = " << multiplier << "\n";
        cout << "Vector values (multiplied): ";
        for (auto& x : v) {
            cout << x * multiplier << " ";
        }
        cout << "\n";
    };
    lambda(vec);   // invoke lambda passing vec
  return 0;
}

✅ Explanation
1. Capture clause [&]
[&] means capture everything by reference.
So the lambda can use local variables (multiplier).

2. Generic lambda parameter
auto lambda = [&](auto& v) {
auto here allows any container, not just vector<int>.

3. Calling the lambda
lambda(vec);
Passes vec to the lambda.

/* ------------------------------------------------- */
🔵 T) Pass using std::bind
auto f = std::bind(print, std::ref(v));
f();



✅ Complete Code: Pass Using std::bind
#include <iostream>
#include <vector>
#include <functional>   // std::bind, std::ref
using namespace std;
void print(const vector<int>& v) {
    cout << "Printing vector: ";
    for (auto x : v)
        cout << x << " ";
    cout << "\n";
}
int main() {
    vector<int> v = {1, 2, 3, 4};
    // bind print(v) but pass v by reference
    auto f = std::bind(print, std::ref(v));
    // call the bound function
    f();
    // Modify vector to prove pass-by-reference
    v.push_back(5);
    f(); // prints updated vector
  return 0;
}

✔️ Output
Printing vector: 1 2 3 4 
Printing vector: 1 2 3 4 5

✔️ Explanation
1. std::bind(print, std::ref(v))
std::bind creates a callable object storing print(v).
std::ref(v) ensures the vector is passed by reference, not copied.

2. f()
Calls print(v) using the bound reference.

/* ------------------------------------------------- */
🔵 U) Pass via optional
void fun(std::optional<std::vector<int>> v);


✅ U) Pass via std::optional<std::vector<int>>
#include <iostream>
#include <vector>
#include <optional>
using namespace std;
void fun(std::optional<std::vector<int>> v) {
    if (!v.has_value()) {
        cout << "Optional is empty!\n";
        return;
    }
    cout << "Vector inside optional: ";
    for (int x : v.value())
        cout << x << " ";
    cout << "\n";
}
int main() {
    // Case 1: optional with vector
    optional<vector<int>> optVec = vector<int>{1, 2, 3, 4};
    fun(optVec);
    // Case 2: empty optional
    optional<vector<int>> empty;
    fun(empty);
  return 0;
}

✔️ Output
Vector inside optional: 1 2 3 4 
Optional is empty!

✔️ What this demonstrates
✔️ std::optional<std::vector<int>>
Represents either:
a vector present, or
no vector.

✔️ Useful when a vector argument is optional.

/* ------------------------------------------------- */
🔵 V) Pass using variant
void fun(std::variant<std::vector<int>, int> v);


✅ V) Pass using std::variant
#include <iostream>
#include <vector>
#include <variant>
using namespace std;
void fun(std::variant<std::vector<int>, int> v) {
    // Check which type is inside the variant
    if (std::holds_alternative<std::vector<int>>(v)) {
        const auto& vec = std::get<std::vector<int>>(v);
        cout << "Variant holds vector: ";
        for (int x : vec)
            cout << x << " ";
        cout << "\n";
    }
    else if (std::holds_alternative<int>(v)) {
        int value = std::get<int>(v);
        cout << "Variant holds int: " << value << "\n";
    }
}
int main() {
    vector<int> v = {1, 2, 3, 4};
    fun(v);      // variant stores vector
    fun(42);     // variant stores int
  return 0;
}

✔️ Output
Variant holds vector: 1 2 3 4 
Variant holds int: 42

✔️ Explanation
std::variant<std::vector<int>, int>
A type-safe union.
Can hold either:
a vector<int>, or
an int.
Inside fun(...):
holds_alternative<T> → checks which type is active.
std::get<T> → extracts the stored value.

/* ------------------------------------------------- */
🔵 W) Pass using any (type-erased)
void fun(std::any a);


✅ W) Pass using std::any
#include <iostream>
#include <vector>
#include <any>
using namespace std;
void fun(std::any a) {
    // Check if 'a' contains a vector<int>
    if (a.type() == typeid(vector<int>)) {
        const auto& v = std::any_cast<const vector<int>&>(a);

        cout << "std::any holds vector: ";
        for (int x : v)
            cout << x << " ";
        cout << "\n";
    }
    else if (a.type() == typeid(int)) {
        int x = std::any_cast<int>(a);
        cout << "std::any holds int: " << x << "\n";
    }
    else {
        cout << "std::any holds unknown type!\n";
    }
}
int main() {
    vector<int> v = {1, 2, 3, 4};
    fun(v);      // any stores vector<int>
    fun(10);     // any stores int
    fun(string("hello"));  // unknown type
  return 0;
}

✔️ Output
std::any holds vector: 1 2 3 4 
std::any holds int: 10
std::any holds unknown type!

✔️ Explanation
std::any

A type-erased container.
Can hold any type, including:
vector<int>
int
string
user-defined types
Type is checked at runtime using .type() and typeid(...).

You extract using:
std::any_cast<T>(a);
If the cast is wrong, it throws std::bad_any_cast.

/* ------------------------------------------------- */

🔵 X) Pass using reference_wrapper
void fun(std::reference_wrapper<std::vector<int>> v);


✅ X) Pass using std::reference_wrapper
#include <iostream>
#include <vector>
#include <functional>   // std::reference_wrapper
using namespace std;
void fun(std::reference_wrapper<std::vector<int>> vref){
    // Get actual vector
    vector<int>& v = vref.get();
    cout << "Vector via reference_wrapper: ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
    // Modify to prove it's a reference
    v.push_back(99);
}
int main(){
    vector<int> v = {1, 2, 3, 4};
    // Wrap vector reference
    std::reference_wrapper<vector<int>> refV(v);
    fun(refV);
    cout << "Vector after modification in fun(): ";
    for (int x : v)
        cout << x << " ";
    cout << "\n";
  return 0;
}

✔️ Output
Vector via reference_wrapper: 1 2 3 4 
Vector after modification in fun(): 1 2 3 4 99

✔️ Explanation
Why use std::reference_wrapper?
It is a copyable, assignable reference.

Useful where real references cannot be stored, such as:
in containers (vector<ref>)
in std::bind
in functional programming
type erasure scenarios

Access the real object:
vref.get()


/* ------------------------------------------------- */
🔵 Y) Pass as global or static variable
std::vector<int> globalV;



✅ Y) Pass as Global or Static Variable
✔️ Using a global vector
#include <iostream>
#include <vector>
using namespace std;
// Global vector (accessible everywhere)
vector<int> globalV = {1, 2, 3, 4};
void fun() {
    cout << "Inside fun(), global vector: ";
    for (int x : globalV)
        cout << x << " ";
    cout << "\n";
    // Modify global vector
    globalV.push_back(99);
}
int main() {
    cout << "Before fun(): ";
    for (int x : globalV)
        cout << x << " ";
    cout << "\n";
    fun();
    cout << "After fun(): ";
    for (int x : globalV)
        cout << x << " ";
    cout << "\n";
  return 0;
}

✔️ Output
Before fun(): 1 2 3 4 
Inside fun(), global vector: 1 2 3 4 
After fun(): 1 2 3 4 99

⭐ Also: Using a static vector inside a function
#include <iostream>
#include <vector>
using namespace std;
void useStaticVector() {
    static vector<int> st = {10, 20, 30};
    cout << "Static vector: ";
    for (int x : st)
        cout << x << " ";
    cout << "\n";
    st.push_back(40);
}
int main() {
    useStaticVector();
    useStaticVector();  // retains values between calls
  return 0;
}

✔️ Output
Static vector: 10 20 30 
Static vector: 10 20 30 40 

✔️ Summary
Passing using global/static:
Works without passing vector as a function parameter.
Vector is shared state, accessible anywhere.

Pros:
✔ Easy to use
✔ Lifetime is long
✔ No need to pass parameters

Cons:
✘ Harder to test
✘ Harder to manage dependencies
✘ Causes tight coupling
✘ Not thread-safe by default

/* ------------------------------------------------- */


Z) Pass using coroutine channels / generators (C++20/23)
(advanced)


a complete, minimal, working example showing how to pass a vector using C++20/C++23 coroutine generators.

C++20 does not include std::generator,
but C++23 does (in <generator>).

If your compiler doesn’t support <generator>,
I provide both C++23 and custom C++20 generator versions.

✅ (A) C++23 – Using std::generator (official)

✔ Easiest
✔ Most modern
✔ Real coroutine-based iteration
✔ Vector passed into generator

⭐ Complete Code (C++23)
#include <iostream>
#include <vector>
#include <generator>   // C++23

std::generator<int> generateVector(const std::vector<int>& v) {
    for (int x : v) {
        co_yield x;   // yield vector elements
    }
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    for (int x : generateVector(v)) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}

✔ Output
1 2 3 4 5

🧠 Explanation

std::generator<int> is a lazy coroutine.

co_yield sends each vector element one at a time.

The vector is passed into the coroutine through arguments.

---------------------------------------------------------
✅ (B) C++20 – Custom Generator Type
C++20 has coroutines, but no standard generator,
so we build a simple one.

⭐ Complete Code (C++20 Custom Generator)
#include <coroutine>
#include <iostream>
#include <vector>
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        Generator get_return_object() { 
            return Generator{ 
                std::coroutine_handle<promise_type>::from_promise(*this) 
            };
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void unhandled_exception() { std::exit(1); }
        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;
    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }
    ~Generator() {
        if (handle)
            handle.destroy();
    }
    struct iterator {
        std::coroutine_handle<promise_type> handle;
        iterator& operator++() {
            handle.resume();
            return *this;
        }
        const T& operator*() const { return handle.promise().current_value; }
        bool operator==(std::default_sentinel_t) const {
            return !handle || handle.done();
        }
    };
    iterator begin() {
        if (handle)
            handle.resume();
        return iterator{handle};
    }
    std::default_sentinel_t end() { return {}; }
};
Generator<int> generateVector(const std::vector<int>& v) {
    for (int x : v)
        co_yield x;
}
int main() {
    std::vector<int> v = {1, 2, 3, 4};
    for (int x : generateVector(v))
        std::cout << x << " ";
    std::cout << "\n";
  return 0;
}
✔ Output
1 2 3 4

🧠 What this demonstrates
✔ Passing vector into coroutine
Generator receives the vector by const reference:
Generator<int> generateVector(const std::vector<int>& v)

✔ Yield each element lazily
co_yield x;

✔ Consumer iterates like a normal range
for (int x : generateVector(v))

/* ------------------------------------------ */



🏆 COMPLETE SUMMARY TABLE (Everything at one place)
| Method                   | Example                  | Notes              |
| ------------------------ | ------------------------ | ------------------ |
| Value                    | `f(v)`                   | copy               |
| Reference                | `f(v)`                   | modifies original  |
| Const reference          | `f(v)`                   | read-only          |
| Rvalue ref               | `f(std::move(v))`        | take ownership     |
| Pointer                  | `f(&v)`                  | nullable           |
| Smart ptr                | `f(sp)`                  | shared ownership   |
| Span                     | `f(std::span<int>(v))`   | lightweight view   |
| Iterators                | `f(v.begin(), v.end())`  | generic            |
| Template universal       | `f(std::forward<T>(v));` | perfect forwarding |
| Lambda capture           | `[&]{ use(v); }`         | inline function    |
| Any / Variant / Optional | wrapped                  | advanced           |
| Thread passing           | `std::ref(v)`            | special case       |



#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <variant>
#include <any>
#include <functional>
#include <thread>
#include <span>
using namespace std;
// =========================================================
// 1. Pass by VALUE (copy)
// =========================================================
void byValue(vector<int> v) {
    cout << "byValue: ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 2. Pass by REFERENCE
// =========================================================
void byRef(vector<int>& v) {
    v.push_back(100);
    cout << "byRef (modified): ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 3. Pass by CONST REFERENCE
// =========================================================
void byConstRef(const vector<int>& v) {
    cout << "byConstRef: ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 4. Pass by RVALUE REFERENCE (move)
// =========================================================
void byRvalue(vector<int>&& v) {
    cout << "byRvalue (taking ownership): ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 5. Pass by POINTER
// =========================================================
void byPtr(vector<int>* v) {
    if (v) v->push_back(200);
    cout << "byPtr: ";
    for (auto x : *v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 6. Pass by CONST POINTER
// =========================================================
void byConstPtr(const vector<int>* v) {
    cout << "byConstPtr: ";
    for (auto x : *v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 7. Pass via unique_ptr
// =========================================================
void byUniquePtr(unique_ptr<vector<int>> v) {
    cout << "byUniquePtr: ";
    for (auto x : *v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 8. Pass via shared_ptr
// =========================================================
void bySharedPtr(shared_ptr<vector<int>> v) {
    cout << "bySharedPtr: ";
    for (auto x : *v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 9. Pass via weak_ptr
// =========================================================
void byWeakPtr(weak_ptr<vector<int>> w) {
    if (auto s = w.lock()) {
        cout << "byWeakPtr: ";
        for (auto x : *s) cout << x << " ";
        cout << "\n";
    }
}
// =========================================================
// 10. Pass via std::span
// =========================================================
void bySpan(span<int> v) {
    cout << "bySpan: ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 11. Iterators
// =========================================================
template <typename It>
void byIter(It b, It e) {
    cout << "byIter: ";
    for (auto it = b; it != e; ++it) cout << *it << " ";
    cout << "\n";
}
// =========================================================
// 12. Template universal forwarding (perfect forwarding)
// =========================================================
template <typename T>
void byUniversal(T&& v) {
    cout << "byUniversal: ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 13. Any / Variant / Optional
// =========================================================
void byAny(any a) {
    if (a.type() == typeid(vector<int>)) {
        cout << "byAny: ";
        for (auto x : any_cast<vector<int>>(a)) cout << x << " ";
        cout << "\n";
    }
}
void byVariant(variant<vector<int>, int> v) {
    if (holds_alternative<vector<int>>(v)) {
        cout << "byVariant: ";
        for (auto x : get<vector<int>>(v)) cout << x << " ";
        cout << "\n";
    }
}
void byOptional(optional<vector<int>> v) {
    if (v) {
        cout << "byOptional: ";
        for (auto x : *v) cout << x << " ";
        cout << "\n";
    }
}
// =========================================================
// 14. Lambda capture
// =========================================================
void lambdaPass(vector<int>& v) {
    auto lam = [&]() {
        cout << "lambda: ";
        for (int x : v) cout << x << " ";
        cout << "\n";
    };
    lam();
}
// =========================================================
// 15. Thread passing
// =========================================================
void threadFunc(vector<int>& v) {
    cout << "threadFunc: ";
    for (auto x : v) cout << x << " ";
    cout << "\n";
}
// =========================================================
// 16. reference_wrapper
// =========================================================
void byRefWrap(reference_wrapper<vector<int>> ref) {
    cout << "byRefWrap: ";
    for (auto x : ref.get()) cout << x << " ";
    cout << "\n";
}
// =========================================================
// MAIN: Demonstrate ALL methods
// =========================================================
int main() {
    vector<int> v = {1,2,3,4};

    byValue(v);
    byRef(v);
    byConstRef(v);
    byRvalue(vector<int>{10,20,30});
    byPtr(&v);
    byConstPtr(&v);

    byUniquePtr(make_unique<vector<int>>(vector<int>{7,8,9}));
    auto sp = make_shared<vector<int>>(v);
    bySharedPtr(sp);
    byWeakPtr(sp);

    bySpan(span<int>(v));

    byIter(v.begin(), v.end());

    byUniversal(v);

    byAny(v);
    byVariant(v);
    byOptional(v);

    lambdaPass(v);

    thread th(threadFunc, ref(v));
    th.join();

    byRefWrap(ref(v));
  return 0;
}
/*
byValue: 1 2 3 4 
byRef (modified): 1 2 3 4 100 
byConstRef: 1 2 3 4 100 
byRvalue (taking ownership): 10 20 30 
byPtr: 1 2 3 4 100 200 
byConstPtr: 1 2 3 4 100 200 
byUniquePtr: 7 8 9 
bySharedPtr: 1 2 3 4 100 200 
byWeakPtr: 1 2 3 4 100 200 
bySpan: 1 2 3 4 100 200 
byIter: 1 2 3 4 100 200 
byUniversal: 1 2 3 4 100 200 
byAny: 1 2 3 4 100 200 
byVariant: 1 2 3 4 100 200 
byOptional: 1 2 3 4 100 200 
lambda: 1 2 3 4 100 200 
threadFunc: 1 2 3 4 100 200 
byRefWrap: 1 2 3 4 100 200 
*/
