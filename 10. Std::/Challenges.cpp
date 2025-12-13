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