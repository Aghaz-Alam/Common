Challenge 1 — std::span (API safety)
❓ Task
Write a function that prints an array without losing size.

✅ Solution
#include <iostream>
#include <span>
using namespace std;
void print(span<const int> s) {
    for (int x : s) cout << x << " ";
    cout << endl;
}
int main() {
    int a[] = {1, 2, 3, 4};
    print(a);
  return 0;
}
/* 
Output
1 2 3 4

✔ No heap
✔ Size preserved
✔ MISRA-friendly
*/


🧠 Challenge 2 — std::optional (explicit absence)
❓ Task
Return a value only if valid.

✅ Solution
#include <iostream>
#include <optional>
using namespace std;
optional<int> divide(int a, int b) {
    if (b == 0) return nullopt;
    return a / b;
}
int main() {
    auto r = divide(10, 2);
    if (r) cout << *r << endl;

    auto e = divide(10, 0);
    cout << e.has_value() << endl;
  return 0;
}
/* 
Output
5
0

✔ No nullptr
✔ No heap
✔ Clear semantics
*/


🧠 Challenge 3 — std::variant (type-safe union)
❓ Task
Store either int or string and print safely.

✅ Solution
#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<int, string> v = "ECU";

    visit([](auto&& x) {
        cout << x << endl;
    }, v);
  return 0;
}
/* 
Output
ECU

✔ One active type
✔ No UB
✔ Stack only
*/


🧠 Challenge 4 — std::forward (perfect forwarding)
❓ Task
Preserve lvalue/rvalue intent.

✅ Solution
#include <iostream>
#include <utility>
using namespace std;
void sink(int&)  { cout << "lvalue\n"; }
void sink(int&&) { cout << "rvalue\n"; }
template<typename T>
void f(T&& x) {
    sink(forward<T>(x));
}
int main() {
    int a = 10;
    f(a);
    f(20);
  return 0;
}
/* 
Output
lvalue
rvalue

✔ Correct overload
✔ No performance loss
*/


🧠 Challenge 5 — std::unique_ptr (ownership)
❓ Task
Transfer ownership safely.

✅ Solution
#include <iostream>
#include <memory>
using namespace std;
unique_ptr<int> make() {
    return make_unique<int>(42);
}
int main() {
    unique_ptr<int> p = make();
    cout << *p << endl;
  return 0;
}
/* 
Output
42

✔ Single owner
✔ Deterministic destruction
*/



🧠 Challenge 6 — std::ranges (C++20)
❓ Task
Filter even numbers and double them.

✅ Solution
#include <iostream>
#include <vector>
#include <ranges>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4,5};

    auto r = v | views::filter([](int x){ return x % 2 == 0; }) | views::transform([](int x){ return x * 2; });

    for (int x : r) cout << x << " ";
  return 0;
}
/* 
Output
4 8

✔ Lazy
✔ No temporary containers
*/



🧠 Challenge 7 — std::atomic (lock-free counter)
❓ Task
Increment safely without mutex.

✅ Solution
#include <iostream>
#include <atomic>
using namespace std;
int main() {
    atomic<int> counter{0};

    counter++;
    counter++;

    cout << counter.load() << endl;
  return 0;
}
/* 
Output
2

✔ Lock-free
✔ Deterministic
*/



🧠 Challenge 8 — std::bit_cast (safe reinterpret)
❓ Task
Convert bits safely (no UB).

✅ Solution
#include <iostream>
#include <bit>
#include <cstdint>
using namespace std;
int main() {
    uint32_t bits = 0x40400000; // 3.0f
    float f = bit_cast<float>(bits);
    cout << f << endl;
  return 0;
}
/* 
Output
3

✔ No aliasing UB
✔ MISRA replacement for reinterpret_cast
*/















1. std::move does NOT move
❓ Theory
Why does std::move not move anything?

Code
#include <iostream>
#include <utility>
using namespace std;
int main() {
    int a = 10;
    int b = move(a);
    cout << a << " " << b << endl;
}
/* 
Output
10 10

🧠 Insight: std::move is just a cast, not an operation.
*/



🔥 2. Named rvalue reference is an lvalue
❓ Theory
Why does this call lvalue overload?

Code
#include <iostream>
using namespace std;

void f(int&)  { cout << "lvalue\n"; }
void f(int&&) { cout << "rvalue\n"; }

int main() {
    int&& x = 10;
    f(x);
}
/* 
Output
lvalue

🧠 Named variables are always lvalues.
*/




🔥 3. Perfect forwarding failure
❓ Theory
What breaks here?

Code
#include <iostream>
#include <utility>
using namespace std;

void sink(int&)  { cout << "lvalue\n"; }
void sink(int&&) { cout << "rvalue\n"; }

template<typename T>
void f(T&& x) {
    sink(x);   // ❌
}
int main() {
    f(10);
}
/* 
Output
lvalue

🧠 Missing std::forward<T>.
*/





🔥 4. sizeof(std::optional<T>)
❓ Theory
Why is this bigger than T?

Code
#include <iostream>
#include <optional>
using namespace std;
int main() {
    cout << sizeof(int) << endl;
    cout << sizeof(optional<int>) << endl;
}
/* 
Output (typical)
4
8

🧠 Engagement flag + padding.
*/


🔥 5. std::variant always engaged
❓ Theory
What is printed?

Code
#include <iostream>
#include <variant>
using namespace std;
int main() {
    variant<int, double> v;
    cout << v.index() << endl;
  return 0;
}
/* 
Output
0

🧠 Default-constructs first alternative.
*/



🔥 6. std::span dangling bug
❓ Theory
Is this safe?

Code:
#include <span>
#include <iostream>
using namespace std;
span<int> make() {
    int a[] = {1,2,3};
    return a;
}
int main() {
    auto s = make();
    cout << s[0] << endl;
  return 0;
}
/* 
Output
(undefined behavior)

🧠 span does NOT extend lifetime.
*/





🔥 7. shared_ptr cycle leak
❓ Theory
Why is destructor never called?

Code:
#include <memory>
#include <iostream>
using namespace std;
struct A {
    shared_ptr<A> other;
    ~A(){ cout<<"destroyed\n"; }
};
int main() {
    auto a = make_shared<A>();
    auto b = make_shared<A>();
    a->other = b;
    b->other = a;
  return 0;
}
/* 
Output
(no output)

🧠 Reference cycle → leak.
*/




🔥 8. weak_ptr fix
Code:
#include <memory>
#include <iostream>
using namespace std;
struct A {
    weak_ptr<A> other;
    ~A(){ cout<<"destroyed\n"; }
};
int main() {
    auto a = make_shared<A>();
    auto b = make_shared<A>();
    a->other = b;
    b->other = a;
  return 0;
}
/* 
Output
destroyed
destroyed

🧠 weak_ptr breaks cycles.
*/





🔥 9. std::function heap trap
❓ Theory
Why is this dangerous in embedded?

Code
#include <functional>
#include <iostream>
using namespace std;
int main() {
    function<void()> f = []{
        int x[1000];
        cout << "run\n";
    };
    f();
  return 0;
}
/* 
Output
run

🧠 Lambda too large → heap allocation.
*/




🔥 10. std::bind argument confusion
Code:
#include <iostream>
#include <functional>
using namespace std;
int sub(int a,int b){
    return a-b;
}
int main(){
    auto f = bind(sub,_2,_1);
    cout << f(3,10) << endl;
  return 0;
}
/* 
Output
7

🧠 Hard to reason → MISRA discourages.
*/




🔥 11. std::any runtime failure
Code
#include <any>
#include <iostream>
using namespace std;
int main(){
    any a = 10;
    try {
        cout << any_cast<double>(a);
    } catch(...) {
        cout << "bad cast";
    }
  return 0;
}
/* 
Output
bad cast

🧠 No compile-time safety.
*/





🔥 12. std::bit_cast vs reinterpret_cast
Code:
#include <iostream>
#include <bit>
#include <cstdint>
using namespace std;
int main(){
    uint32_t u = 0x3F800000;
    float f = bit_cast<float>(u);
    cout << f << endl;
  return 0;
}
/* 
Output
1

🧠 No aliasing UB.
*/





🔥 13. std::atomic is not always lock-free
Code:
#include <atomic>
#include <iostream>
using namespace std;
int main(){
    atomic<long double> a;
    cout << a.is_lock_free() << endl;
  return 0;
}
/* 
Output
0

🧠 Platform dependent.
*/





🔥 14. std::async scheduling trap
Code:
#include <future>
#include <iostream>
using namespace std;
int work(){
    cout<<"work\n";
    return 1;
}
int main(){
    auto f = async(work);
    cout << "done\n";
    cout << f.get();
  return 0;
}
/* 
Output (order unspecified)
work
done
1

🧠 Deferred vs thread = nondeterministic.
*/





🔥 15. std::array passed by value
❓ Theory
Is this expensive?

Code
#include <array>
#include <iostream>
using namespace std;
void f(array<int,100> a){
    cout << a[0] << endl;
}
int main(){
    array<int,100> a{};
    f(a);
  return 0;
}
/* 
Output
0

🧠 Copies entire array.
*/



🔥 16. enable_if overload control
Code:
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
enable_if_t<is_integral_v<T>>
f(T){ cout<<"int\n"; }

template<typename T>
enable_if_t<!is_integral_v<T>>
f(T){ cout<<"non-int\n"; }

int main(){
    f(10);
    f(3.14);
  return 0;
}
/* 
Output
int
non-int

🧠 SFINAE selection.
*/




🔥 17. constexpr container trap
Code
#include <vector>
#include <iostream>
using namespace std;
int main(){
    constexpr int x = 10;
    vector<int> v(x);
    cout << v.size() << endl;
  return 0;
}
/* 
Output
10

🧠 constexpr ≠ compile-time allocation.
*/





🔥 18. std::launder necessity
❓ Theory
Why is this required?

Code
#include <new>
#include <iostream>
using namespace std;
int main(){
    alignas(int) char buf[sizeof(int)];
    int* p = new(buf) int(10);
    cout << *std::launder(p) << endl;
  return 0;
}
/* 
Output
10

🧠 Object lifetime rules.
*/


🔥 19. ranges dangling view
Code
#include <vector>
#include <ranges>
#include <iostream>
using namespace std;
auto make(){
    vector<int> v = {1,2,3};
    return v | views::filter([](int x){return x>1;});
}
int main(){
    auto r = make();
    for(int x: r) cout<<x;
  return 0;
}
/* 
Output
(undefined behavior)

🧠 Views don’t own data.
*/


🔥 20. unique_ptr misuse
❓ Theory
What happens?

Code
#include <memory>
#include <iostream>
using namespace std;
int main(){
    unique_ptr<int> p(new int(5));
    unique_ptr<int> q = p; // ❌
  return 0;
}
/* 
Output
(compilation error)

🧠 Unique ownership enforced at compile time.
*/












1. Use-after-free
#include <iostream>
using namespace std;
int main() {
    int* p = new int(10);
    delete p;
    cout << *p << endl;   // UB
}
/* 
📤 Output (possible)
10

☠️ Accessing freed memory.
*/




🔥 2. Dereferencing null pointer
#include <iostream>
using namespace std;

int main() {
    int* p = nullptr;
    cout << *p << endl;   // UB
}
/* 
📤 Output
(segmentation fault)

☠️ Null dereference.
*/





🔥 3. Returning reference to local
#include <iostream>
using namespace std;

int& f() {
    int x = 10;
    return x;   // UB
}
int main() {
    cout << f() << endl;
}
/* 
📤 Output
10

☠️ Dangling reference.
*/



🔥 4. Signed integer overflow
#include <iostream>
using namespace std;

int main() {
    int x = 2147483647;
    x += 1;   // UB
    cout << x << endl;
}
/* 
📤 Output
-2147483648

☠️ Signed overflow is UB.
*/




🔥 5. Out-of-bounds array access
#include <iostream>
using namespace std;

int main() {
    int a[3] = {1,2,3};
    cout << a[3] << endl;   // UB
}
/* 
📤 Output
0

☠️ Access past array end.
*/





🔥 6. Modifying string literal
#include <iostream>
using namespace std;

int main() {
    char* s = (char*)"hello";
    s[0] = 'H';   // UB
    cout << s << endl;
}
/* 
📤 Output
(segmentation fault)

☠️ String literals are read-only.
*/





🔥 7. Strict aliasing violation
#include <iostream>
using namespace std;

int main() {
    int x = 0x3F800000;
    float* f = (float*)&x;   // UB
    cout << *f << endl;
}
/* 
📤 Output
1

☠️ Violates aliasing rules (bit_cast required).
*/




🔥 8. Double delete
#include <iostream>
using namespace std;

int main() {
    int* p = new int(5);
    delete p;
    delete p;   // UB
}
/* 
📤 Output
(heap corruption)

☠️ Double free.
*/




🔥 9. Reading uninitialized variable
#include <iostream>
using namespace std;
int main() {
    int x;
    cout << x << endl;   // UB
}
/* 
📤 Output
32767

☠️ Indeterminate value.
*/




🔥 10. Iterator invalidation
#include <vector>
#include <iostream>
using namespace std;
int main() {
    vector<int> v = {1,2,3};
    auto it = v.begin();
    v.push_back(4);
    cout << *it << endl;   // UB
}
/* 
📤 Output
1

☠️ Iterator invalidated.
*/




🔥 11. Using moved-from object (non-specified)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "hello";
    string t = move(s);
    cout << s << endl;   // UB-like (unspecified)
}
/* 
📤 Output
(empty)

☠️ State unspecified (not strictly UB, but unsafe).
*/





🔥 12. Calling virtual function in destructor
#include <iostream>
using namespace std;

struct A {
    virtual void f() { cout<<"A\n"; }
    virtual ~A() { f(); }   // UB
};

struct B : A {
    void f() override { cout<<"B\n"; }
};

int main() {
    A* p = new B;
    delete p;
}
/* 
📤 Output
A

☠️ Object already partially destroyed.
*/




🔥 13. Data race
#include <thread>
#include <iostream>
using namespace std;

int x = 0;

void f() { x++; }

int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
    cout << x << endl;
}
/* 
📤 Output
1

☠️ Data race = UB.
*/




🔥 14. Dangling std::string_view
#include <string_view>
#include <iostream>
using namespace std;

string_view make() {
    string s = "hello";
    return s;   // UB
}

int main() {
    cout << make() << endl;
}
/* 
📤 Output
hello

☠️ View outlives data.
*/




🔥 15. Misaligned access
#include <iostream>
using namespace std;
int main() {
    char buf[sizeof(int)];
    int* p = (int*)(buf + 1);  // UB
    cout << *p << endl;
}
/* 
📤 Output
(segfault on ARM)

☠️ Alignment violation.
*/



🔥 16. delete non-heap object
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int* p = &x;
    delete p;   // UB
}
/* 
📤 Output
(crash)

☠️ Deleting stack memory.
*/




🔥 17. Multiple mutable references
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int& a = x;
    int& b = x;
    a = 5;
    b = 7;
    cout << x << endl;
}
/* 
📤 Output
7

☠️ Safe here — BUT modifying via aliasing can cause UB with optimization.
*/




🔥 18. memcpy non-trivial type
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main() {
    string a = "hello";
    string b;
    memcpy(&b, &a, sizeof(string));  // UB
    cout << b << endl;
}
/* 
📤 Output
hello

☠️ Violates object lifetime.
*/




🔥 19. Overlapping memcpy
#include <iostream>
#include <cstring>
using namespace std;
int main() {
    char s[] = "abcdef";
    memcpy(s+1, s, 4);   // UB
    cout << s << endl;
}
/* 
📤 Output
aabcd

☠️ Must use memmove.
*/



🔥 20. Access inactive union member
#include <iostream>
using namespace std;
union U {
    int i;
    float f;
};
int main() {
    U u;
    u.i = 0x3F800000;
    cout << u.f << endl;   // UB
}
/* 
📤 Output
1

☠️ No active member tracking (std::variant fixes this).
 */