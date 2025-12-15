🛡️ “FIX THIS UB” — SAFE & MISRA-COMPLIANT VERSIONS
✅ FIX #1 — Use-After-Free
❌ UB
int* p = new int(10);
delete p;
std::cout << *p;

✅ SAFE (MISRA)
#include <memory>
#include <iostream>
int main() {
    std::unique_ptr<int> p = std::make_unique<int>(10);
    std::cout << *p;
}
/* 
✔ RAII
✔ No dangling pointers
✔ MISRA-friendly
*/




✅ FIX #2 — Dangling Reference
❌ UB
int& foo() {
    int x = 10;
    return x;
}

✅ SAFE
int foo() {
    return 10;
}

✔ Never return references to locals







✅ FIX #3 — Strict Aliasing Violation
❌ UB
float f = 1.0f;
int* p = (int*)&f;

✅ SAFE (bit_cast C++20)
#include <bit>
#include <cstdint>
int main() {
    float f = 1.0f;
    uint32_t bits = std::bit_cast<uint32_t>(f);
}

✔ Defined
✔ MISRA-acceptable type-safe reinterpretation






✅ FIX #4 — Uninitialized Read
❌ UB
int x;
std::cout << x;

✅ SAFE
int x = 0;
std::cout << x;

✔ MISRA Rule 9.x: initialization required







✅ FIX #5 — Signed Integer Overflow
❌ UB
int x = INT_MAX;
x += 1;

✅ SAFE
#include <limits>
#include <iostream>
int main() {
    int x = std::numeric_limits<int>::max();
    if (x < std::numeric_limits<int>::max()) {
        x++;
    }
}
✔ Explicit bounds check
✔ No UB





✅ FIX #6 — Placement New + std::launder
❌ UB
A* p = new (buf) A{1};
p->~A();
new (buf) A{2};
std::cout << p->x;

✅ SAFE
#include <new>
#include <iostream>

int main() {
    alignas(int) unsigned char buf[sizeof(int)];
    int* p = new (buf) int(1);
    p->~int();
    p = std::launder(new (buf) int(2));
    std::cout << *p;
}

✔ Correct lifetime handling
✔ MISRA-safe if placement new is allowed






✅ FIX #7 — Inactive Union Member
❌ UB
union U { int i; float f; };
U u; u.i = 42; std::cout << u.f;

✅ SAFE
#include <variant>
#include <iostream>
int main() {
    std::variant<int, float> v = 42;
    std::cout << std::get<int>(v);
}

✔ Type-safe
✔ MISRA prefers tagged unions





✅ FIX #8 — Modifying String Literal
❌ UB
char* p = "hello";
p[0] = 'H';

✅ SAFE
#include <array>
int main() {
    std::array<char, 6> s = {'h','e','l','l','o','\0'};
    s[0] = 'H';
}

✔ No writable string literal






✅ FIX #9 — Mismatched delete
❌ UB
int* p = new int[5];
delete p;

✅ SAFE
#include <vector>
int main() {
    std::vector<int> v(5);
}

✔ No manual delete
✔ MISRA recommended container





✅ FIX #10 — Base Pointer Delete
❌ UB
struct B { ~B() {} };
struct D : B {};
delete basePtr;

✅ SAFE
struct B {
    virtual ~B() = default;
};
✔ Polymorphic base MUST have virtual destructor






🧵 THREADING UB — FIXED
✅ FIX #11 — Data Race
❌ UB
int x = 0;
std::thread t1([]{x++;});
std::thread t2([]{x++;});

✅ SAFE
#include <atomic>
#include <thread>
#include <iostream>
std::atomic<int> x{0};
int main() {
    std::thread t1([]{ x.fetch_add(1); });
    std::thread t2([]{ x.fetch_add(1); });
    t1.join(); t2.join();
    std::cout << x;
}

✔ Defined memory order
✔ MISRA allows atomics





✅ FIX #12 — Publication Safety
❌ UB
int* p;
void writer() { p = new int(42); }

✅ SAFE
#include <atomic>
std::atomic<int*> p{nullptr};
void writer() {
    p.store(new int(42), std::memory_order_release);
}
void reader() {
    int* q = p.load(std::memory_order_acquire);
}
✔ Proper happens-before







✅ FIX #13 — Detached Thread Lifetime
❌ UB
std::thread([&]{ x++; }).detach();

✅ SAFE
std::thread t([&]{ x++; });
t.join();

✔ MISRA: threads must be joined or owned







✅ FIX #14 — Vector Reallocation Invalidation
❌ UB
int* p = &v[0];
v.push_back(4);

✅ SAFE
v.reserve(10);
int* p = &v[0];
v.push_back(4);

✔ Explicit capacity management



✅ FIX #15 — reinterpret_cast Function Pointer
❌ UB
void (*p)(double) = (void(*)(double))f;

✅ SAFE
void f(double d) {}

int main() {
    f(3.14);
}

✔ No function pointer casting (MISRA banned)