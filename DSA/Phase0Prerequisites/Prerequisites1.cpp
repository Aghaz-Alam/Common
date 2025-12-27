1️⃣ Lambda Capture LIFETIME TRAPS
🔴 Trap 1: Capturing local variable by reference and returning lambda
❓ What happens?
#include <iostream>
#include <functional>
using namespace std;
function<void()> makeLambda() {
    int x = 10;

    return [&x]() {
        cout << x << endl;
    };
}
int main() {
    auto f = makeLambda();
    f();   // ❌ Undefined Behavior
}

🖥 Output
Garbage value / crash / unpredictable

💥 WHY?

x is local to makeLambda
After function returns → x is destroyed
Lambda holds a dangling reference

📌 Interview Rule
Never capture local variables by reference if lambda outlives the scope.




✅ FIX 1: Capture by VALUE
#include <iostream>
#include <functional>
using namespace std;
function<void()> makeLambda() {
    int x = 10;

    return [x]() {
        cout << x << endl;
    };
}
int main() {
    auto f = makeLambda();
    f();
}

🖥 Output
10

✔ Value capture copies data → lifetime safe





🔴 Trap 2: Capturing this pointer
#include <iostream>
#include <functional>
using namespace std;
class A {
  public:
    int x = 10;

    function<void()> getLambda() {
        return [this]() {
            cout << x << endl;
        };
    }
};
int main() {
    function<void()> f;
    {
        A obj;
        f = obj.getLambda();
    }   // obj destroyed here

    f();   // ❌ UB
}

🖥 Output
Crash / garbage

💥 WHY?
Lambda captures this
Object destroyed
this becomes dangling pointer





✅ FIX 2: Capture by VALUE (C++17)
#include <iostream>
#include <functional>
using namespace std;
class A {
  public:
    int x = 10;

    function<void()> getLambda() {
        return [*this]() {
            cout << x << endl;
        };
    }
};
int main() {
    function<void()> f;
    {
        A obj;
        f = obj.getLambda();
    }

    f();
}

🖥 Output
10

📌 [*this] → captures a copy of the object




🔴 Trap 3: Lambda capturing pointer to temporary
#include <iostream>
using namespace std;
int* getPtr() {
    int x = 10;
    return &x;   // ❌
}
int main() {
    auto lam = [p = getPtr()]() {
        cout << *p << endl;
    };

    lam();   // ❌ UB
}

📌 Capturing a pointer does NOT extend lifetime.





2️⃣ PERFECT FORWARDING PITFALLS (VERY IMPORTANT)
🔹 Perfect Forwarding Goal
Preserve lvalue / rvalue nature of arguments.

🔴 Trap 1: Missing std::forward
#include <iostream>
using namespace std;
void process(int& x) {
    cout << "lvalue\n";
}
void process(int&& x) {
    cout << "rvalue\n";
}
template<typename T>
void wrapper(T x) {
    process(x);   // ❌ ALWAYS lvalue
}
int main() {
    wrapper(10);
}

🖥 Output
lvalue

💥 WHY?
x is a named variable
Named variables are always lvalues




✅ FIX 1: Use std::forward
#include <iostream>
using namespace std;
void process(int& x) {
    cout << "lvalue\n";
}
void process(int&& x) {
    cout << "rvalue\n";
}
template<typename T>
void wrapper(T&& x) {
    process(std::forward<T>(x));
}
int main() {
    wrapper(10);
}

🖥 Output
rvalue





🔴 Trap 2: Using std::move instead of std::forward
template<typename T>
void wrapper(T&& x) {
    process(std::move(x));  // ❌ forces rvalue
}

❌ Problem
Converts lvalue → rvalue
Breaks semantics
Causes accidental moves

📌 Interview Rule
Use std::forward in templates, not std::move.




🔴 Trap 3: Forwarding const object
#include <iostream>
using namespace std;
void process(int&& x) {
    cout << "rvalue\n";
}

int main() {
    const int x = 10;
    process(std::move(x));  // ❌ error
}

💥 WHY?
std::move(x) → const int&&
Cannot bind to int&&
📌 const kills move semantics

🔴 Trap 4: Forwarding reference misconception
template<typename T>
void foo(T&& x);   // forwarding reference
void bar(int&& x); // rvalue reference

📌 T&& is forwarding reference only if T is template type



🔥 ULTIMATE INTERVIEW TRAP
template<typename T>
void foo(T&& x) {
    auto lam = [&]() {
        process(std::forward<T>(x));  // ❌ WRONG
    };
}

💥 WHY?
x captured by reference
Forwarding category lost
Can cause dangling reference



✅ CORRECT VERSION
template<typename T>
void foo(T&& x) {
    auto lam = [x = std::forward<T>(x)]() {
        process(x);
    };
}

🧠 FINAL INTERVIEW MEMORY SHEET
Lambda Lifetimes
❌ Reference capture + escaping lambda = UB
❌ Capturing this without lifetime guarantee
✅ Capture by value

✅ Use [*this] (C++17)
Perfect Forwarding
Use T&& + std::forward
Never use std::move in forwarding
const disables move
Named variables are lvalues

🏁 INTERVIEW GOLD LINE
Most modern C++ bugs are lifetime bugs hidden behind lambdas and forwarding references.