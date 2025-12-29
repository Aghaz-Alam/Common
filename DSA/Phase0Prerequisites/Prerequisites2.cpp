🔥 1️⃣ constexpr VARIABLE vs const VARIABLE (SUBTLE)
#include <iostream>
using namespace std;
int main() {
    const int a = 10;
    constexpr int b = 20;

    int arr1[a];   // ❌ may fail (compiler dependent)
    int arr2[b];   // ✅ always OK

    cout << arr2[0] << endl;
}
/*
🖥 Output
0

💥 WHY?
const → may be runtime
constexpr → guaranteed compile-time

📌 Interview Rule
constexpr is stronger than const
*/




🔥 2️⃣ static LOCAL VARIABLE LIFETIME TRAP
#include <iostream>
using namespace std;
void counter() {
    static int x = 0;
    x++;
    cout << x << endl;
}
int main() {
    counter();
    counter();
    counter();
}
/*
🖥 Output
1
2
3

💥 WHY?
static local variables live for entire program
Initialized once

📌 MISRA: Allowed but must be justified
*/




🔥 3️⃣ inline DOES NOT MEAN INLINE
#include <iostream>
using namespace std;
inline void foo() {
    cout << "Hello\n";
}
int main() {
    foo();
}
/*
🖥 Output
Hello

💥 WHY?
inline is a linkage hint
Compiler may still not inline

📌 Interview Trick:
inline ≠ performance guarantee
*/




🔥 4️⃣ static_cast vs reinterpret_cast (DANGEROUS)
#include <iostream>
using namespace std;
int main() {
    int x = 65;
    char* p = reinterpret_cast<char*>(&x);

    cout << *p << endl;
}
/*
🖥 Output
A   (platform dependent)

💥 WHY?
Reads raw memory
Endianness dependent
📌 MISRA: reinterpret_cast forbidden
*/



🔥 5️⃣ delete this TRAP (YES, IT COMPILES)
#include <iostream>
using namespace std;
class A {
  public:
    void destroy() {
        delete this;
    }
};
int main() {
    A* a = new A();
    a->destroy();
    // a->destroy();  // ❌ double delete UB
}
/*
📌 MISRA: Strictly forbidden
*/



🔥 6️⃣ sizeof FUNCTION PARAMETER PACK TRAP
#include <iostream>
using namespace std;
template<typename T>
void foo(T arr[]) {
    cout << sizeof(arr) << endl;
}
int main() {
    int a[5];
    foo(a);
}
/*
🖥 Output (64-bit)
8

📌 Arrays decay to pointers
*/



🔥 7️⃣ Virtual Destructor TRAP (VERY IMPORTANT)
#include <iostream>
using namespace std;
class Base {
  public:
    ~Base() { cout << "Base\n"; }
};
class Derived : public Base {
  public:
    ~Derived() { cout << "Derived\n"; }
};
int main() {
    Base* b = new Derived();
    delete b;   // ❌ UB
}
/*
🖥 Output
Base

💥 WHY?
Derived destructor not called
Resource leak

✅ FIX
virtual ~Base() {}

📌 Interview MUST-KNOW
*/



🔥 8️⃣ this POINTER CONSTNESS
#include <iostream>
using namespace std;

class A {
    int x = 10;
public:
    void set(int v) { x = v; }
    void print() const {
        // x = 20; ❌
        cout << x << endl;
    }
};

int main() {
    const A a;
    a.print();
}
/*
🖥 Output
10

📌 this becomes const A* inside const function
*/


🔥 9️⃣ Overloading on const OBJECT
#include <iostream>
using namespace std;
class A {
  public:
    void show() { cout << "non-const\n"; }
    void show() const { cout << "const\n"; }
};
int main() {
    A a;
    const A b;

    a.show();
    b.show();
}
/*
🖥 Output
non-const
const
*/



🔥 🔟 Global OBJECT Initialization Order (FAMOUS TRAP)
#include <iostream>
using namespace std;
int y = 10;
int x = y;
int main() {
    cout << x << endl;
}
/*
🖥 Output
10

✔ same translation unit
❌ Different files → undefined order
📌 MISRA: Avoid global objects with dependencies
*/



🔥 1️⃣1️⃣ std::exchange (C++14) — SAFE SWAP
#include <iostream>
#include <utility>
using namespace std;

int main() {
    int x = 10;
    int old = exchange(x, 20);

    cout << old << " " << x << endl;
}
/*
🖥 Output
10 20

📌 Useful for state updates
*/




🔥 1️⃣2️⃣ [[maybe_unused]] (C++17)
#include <iostream>
using namespace std;
int main() {
    [[maybe_unused]] int x = 10;
    cout << "Done\n";
}
/*
🖥 Output
Done

📌 Avoids warnings in safety code
*/



🔥 1️⃣3️⃣ consteval (C++20) — STRONGER THAN constexpr
#include <iostream>
using namespace std;
consteval int square(int x) {
    return x * x;
}
int main() {
    constexpr int v = square(5);
    cout << v << endl;
}
/*
🖥 Output
25

📌 MUST be evaluated at compile-time
📌 MISRA-friendly for determinism
*/




🔥 1️⃣4️⃣ requires (C++20) — CONSTRAINTS
#include <iostream>
using namespace std;
template<typename T>
requires is_integral_v<T>
T add(T a, T b) {
    return a + b;
}
int main() {
    cout << add(3,4) << endl;
}
/*
🖥 Output
7

📌 Safer templates → fewer misuse bugs
*/



🧠 PHASE-0 MASTER TAKEAWAYS
constexpr > const
reinterpret_cast = danger
virtual destructors are mandatory
lifetime > syntax correctness
globals are risky
C++20/23 improve safety if used correctly

🏁 FINAL INTERVIEW LINE
Phase-0 mastery is about proving your code cannot misbehave — not just that it compiles.