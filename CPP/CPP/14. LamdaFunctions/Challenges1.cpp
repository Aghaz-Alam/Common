C++ LAMBDA CHALLENGES (CORE → ADVANCED)
🔹 Challenge 1: Capture by Value vs Reference
📘 Theory
[=] → copy
[&] → reference


#include <iostream>
using namespace std;
int main() {
    int x = 10;

    auto by_value = [=]() { cout << x << "\n"; };
    auto by_ref   = [&]() { x = 20; };

    by_value();
    by_ref();
    by_value();

    cout << x << "\n";
}
/* 
✅ Output
10
10
20
*/





🔹 Challenge 2: Modifying Captured-by-Value (mutable)
#include <iostream>
using namespace std;
int main() {
    int x = 5;

    auto f = [=]() mutable {
        x++;
        cout << x << "\n";
    };

    f();
    cout << x << "\n";
}
/* 
✅ Output
6
5
*/




🔹 Challenge 3: Dangling Reference (UB ⚠️)
#include <iostream>
using namespace std;
auto bad() {
    int x = 10;
    return [&]() { return x; };
}
int main() {
    auto f = bad();
    cout << f() << "\n";   // UB
}
/* 
❌ Output
Undefined behavior (garbage / crash)
*/





🔹 Challenge 4: Lambda as Function Pointer ❌
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    // auto fp = +[=]() { return x; }; ❌ error

    auto ok = []() { return 5; };
    int (*fp)() = ok;

    cout << fp() << "\n";
}
/* 
✅ Output
5
*/




🔹 Challenge 5: Generic Lambda (C++14)
#include <iostream>
using namespace std;
int main() {
    auto add = [](auto a, auto b) {
        return a + b;
    };

    cout << add(2, 3) << "\n";
    cout << add(1.5, 2.5) << "\n";
}
/* 
✅ Output
5
4
*/





🔹 Challenge 6: Lambda Size (Capture Cost)
#include <iostream>
using namespace std;
int main() {
    int x = 10, y = 20;

    auto l1 = []() {};
    auto l2 = [=]() {};

    cout << sizeof(l1) << "\n";
    cout << sizeof(l2) << "\n";
}
/* 
✅ Output (example)
1
8 or 16
*/




🔹 Challenge 7: Capturing this
#include <iostream>
using namespace std;
struct A {
    int x = 10;

    auto f() {
        return [this]() { cout << x << "\n"; };
    }
};
int main() {
    A a;
    auto l = a.f();
    l();
}
/* 
✅ Output
10
*/




🔹 Challenge 8: [*this] Copy Capture (C++17)
#include <iostream>
using namespace std;
struct A {
    int x = 10;

    auto f() {
        return [*this]() mutable {
            x = 20;
            cout << x << "\n";
        };
    }
};
int main() {
    A a;
    auto l = a.f();
    l();
    cout << a.x << "\n";
}
/* 
✅ Output
20
10
*/





🔹 Challenge 9: Lambda in STL Algorithm
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    vector<int> v{1,2,3,4};

    int sum = 0;
    for_each(v.begin(), v.end(), [&](int x) {
        sum += x;
    });

    cout << sum << "\n";
}
/* 
✅ Output
10
*/




🔹 Challenge 10: Returning Lambda (Type Erasure)
#include <iostream>
#include <functional>
using namespace std;
function<int(int)> make() {
    return [](int x) { return x * x; };
}
int main() {
    auto f = make();
    cout << f(5) << "\n";
}
/* 
✅ Output
25
*/






🔹 Challenge 11: Exception in Lambda
#include <iostream>
using namespace std;
int main() {
    auto f = []() {
        throw runtime_error("Error");
    };

    try {
        f();
    } catch (...) {
        cout << "Caught\n";
    }
}
/* 
✅ Output
Caught
*/




🔹 Challenge 12: noexcept Lambda
#include <iostream>
#include <type_traits>
using namespace std;
int main() {
    auto f = []() noexcept {};
    auto g = []() {};

    cout << is_nothrow_invocable<decltype(f)>::value << "\n";
    cout << is_nothrow_invocable<decltype(g)>::value << "\n";
}
/* 
✅ Output
1
0
*/




🔹 Challenge 13: Recursive Lambda (Trick!)
#include <iostream>
#include <functional>
using namespace std;
int main() {
    function<int(int)> fact = [&](int n) {
        return n <= 1 ? 1 : n * fact(n - 1);
    };

    cout << fact(5) << "\n";
}
/* 
✅ Output
120
*/




🔹 Challenge 14: Lambda Lifetime Trap (Thread)
#include <thread>
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    thread t([&]() {
        cout << x << "\n";
    });

    t.join();
}
/* 
⚠️ Output
10 (SAFE only because join)
*/




🔹 Challenge 15: MISRA / Embedded-Safe Lambda
#include <iostream>
using namespace std;
int main() {
    auto add = [](int a, int b) -> int {
        return a + b;
    };

    cout << add(3,4) << "\n";
}
/* 
✅ Output
7
*/