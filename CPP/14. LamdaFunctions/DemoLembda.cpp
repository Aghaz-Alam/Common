1. Lambda Capture Modes (Deep Examples)
1.1 Capture by Value (copy)
#include <iostream>
int main() {
    int x = 10;

    auto f = [x]() { 
        std::cout << "Inside lambda: x = " << x << "\n";
    };

    x = 20; // external change does NOT affect lambda

    f();
}

Output
Inside lambda: x = 10

1.2 Capture by Reference
#include <iostream>
int main() {
    int x = 10;

    auto f = [&x]() { 
        std::cout << "Inside lambda: x = " << x << "\n";
    };

    x = 20; // external change DOES affect lambda

    f();
}

Output
Inside lambda: x = 20

1.3 Capture All by Value [=]
#include <iostream>
int main() {
    int a = 5, b = 7;

    auto f = [=]() {
        std::cout << a + b << "\n"; // both copied
    };

    a = 50; b = 70;

    f();
}

Output
12

1.4 Capture All by Reference [&]
#include <iostream>
int main() {
    int a = 5, b = 7;

    auto f = [&]() {
        std::cout << a + b << "\n"; 
    };

    a = 50; b = 70;

    f();
}

Output
120

1.5 Mixed Captures
#include <iostream>
int main() {
    int a = 10, b = 20;

    auto f = [a, &b]() {
        std::cout << "a = " << a << ", b = " << b << "\n";
    };

    b = 100; // affects lambda
    a = 50;  // does NOT affect lambda

    f();
}

Output
a = 10, b = 100

2. Mutable Lambdas (modify captured-by-value)

Normally captured-by-value variables are read-only.

mutable allows changing the lambda’s internal copy.

Example
#include <iostream>
int main() {
    int x = 10;

    auto f = [x]() mutable {
        x += 5; 
        std::cout << "Inside lambda: " << x << "\n";
    };

    f();
    std::cout << "Outside: " << x << "\n";
}

Output
Inside lambda: 15
Outside: 10

3. Generic Lambdas (C++14 → C++20)

C++14 allowed auto in lambda parameters.

C++14 Example
#include <iostream>

int main() {
    auto add = [](auto a, auto b) {
        return a + b;
    };

    std::cout << add(2, 3) << "\n";
    std::cout << add(2.5, 3.1) << "\n";
}

Output
5
5.6

4. Generic Lambdas + C++20 Concepts
#include <iostream>
#include <concepts>

int main() {
    auto add = [](std::integral auto a, std::integral auto b) {
        return a + b;
    };

    std::cout << add(10, 20) << "\n";
}

Output
30

5. Lambda Type Deduction with auto Return (C++14–C++20)
#include <iostream>
int main() {
    auto square = [](auto x) {
        return x * x;
    };

    std::cout << square(5) << "\n";
    std::cout << square(2.5) << "\n";
}

Output
25
6.25

6. Capturing this (C++11–C++20)
#include <iostream>

class A {
    int value = 42;
public:
    void show() {
        auto f = [this]() {
            std::cout << value << "\n";
        };
        f();
    }
};

int main() {
    A a;
    a.show();
}

Output
42

7. Default Capture + Extra (C++14–C++20)
#include <iostream>
int main() {
    int x = 10, y = 20, z = 30;

    auto f = [=, &y]() {
        std::cout << x << " " << y << " " << z << "\n";
    };

    y = 200;

    f();
}

Output
10 200 30

8. Lambda as Function Object — Under the Hood

A lambda:

[x](int a) { return a + x; }


Is transformed into:

struct Closure {
    int x;

    int operator()(int a) const {
        return a + x;
    }
};

9. Lambdas with std::function
#include <iostream>
#include <functional>

int main() {
    std::function<int(int)> f = [](int x) { return x * 2; };

    std::cout << f(5) << "\n";
}

Output
10

10. Returning Lambdas
#include <iostream>

auto makeAdder(int x) {
    return [x](int y) {
        return x + y;
    };
}

int main() {
    auto adder = makeAdder(10);
    std::cout << adder(20) << "\n";
}

Output
30





✅ 1. Lambda + STL Algorithms
✔ Using lambdas with std::sort, std::for_each, std::transform
PROGRAM 1: Lambdas + STL Algorithms
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {5, 1, 4, 2, 3};

    // Sort descending
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });

    std::cout << "Sorted: ";
    std::for_each(v.begin(), v.end(), [](int x) {
        std::cout << x << " ";
    });
    std::cout << "\n";

    // Transform: square each element
    std::transform(v.begin(), v.end(), v.begin(), [](int x) {
        return x * x;
    });

    std::cout << "Squared: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

Output
Sorted: 5 4 3 2 1
Squared: 25 16 9 4 1

✅ 2. Recursive Lambdas (C++14 idiom)

C++14 allows auto in lambda parameters → enables recursion via std::function or Y-combinator.

PROGRAM 2: Recursive Lambda (Factorial)
#include <iostream>
#include <functional>

int main() {
    std::function<int(int)> fact = [&](int n) {
        return (n <= 1) ? 1 : n * fact(n - 1);
    };

    std::cout << fact(5) << "\n";
}

Output
120

PROGRAM 3: Recursive Lambda (Fibonacci - Efficient)

Using “self lambda” C++14 trick.

#include <iostream>

int main() {
    auto fib = [](auto self, int n) -> int {
        if (n <= 1) return n;
        return self(self, n-1) + self(self, n-2);
    };

    std::cout << fib(fib, 10) << "\n";
}

Output
55

✅ 3. Lambda Templates (C++20)

C++20: lambdas can have template parameters directly.

PROGRAM 4: Template Lambda
#include <iostream>

int main() {
    auto add = []<typename T>(T a, T b) {
        return a + b;
    };

    std::cout << add(3, 4) << "\n";
    std::cout << add(1.5, 2.1) << "\n";
}

Output
7
3.6

✅ 4. Lambda in Multithreading (C++11–C++20)
PROGRAM 5: Thread Using Lambda
#include <iostream>
#include <thread>

int main() {
    int x = 10;

    std::thread t([&]() {
        std::cout << "Inside thread: x = " << x << "\n";
    });

    t.join();
}

Output
Inside thread: x = 10

✅ 5. Lambda + Coroutines (C++20)

Lambdas can produce co_return, co_yield when returning coroutine-aware types.

Here: simple generator via coroutine + lambda wrapper.

PROGRAM 6: Lambda Returning Coroutine
#include <iostream>
#include <coroutine>
#include <vector>

struct Generator {
    struct promise_type {
        int current;
        std::suspend_always yield_value(int value) {
            current = value;
            return {};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void return_void() {}
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> h;
    ~Generator() { if (h) h.destroy(); }

    bool next() {
        if (!h.done()) {
            h.resume();
            return !h.done();
        }
        return false;
    }
    int value() const { return h.promise().current; }
};

int main() {
    auto genLambda = []() -> Generator {
        co_yield 10;
        co_yield 20;
        co_yield 30;
    };

    auto g = genLambda();

    while (g.next()) {
        std::cout << g.value() << "\n";
    }
}

Output
10
20
30

✅ 6. Capture Move Semantics ([x = std::move(v)])
PROGRAM 7: Move Capture
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1,2,3};

    auto f = [x = std::move(v)]() {
        std::cout << "Captured vector: ";
        for (int i : x) std::cout << i << " ";
        std::cout << "\n";
    };

    f(); // vector moved inside lambda
}

Output
Captured vector: 1 2 3

✅ 7. Lambda Performance & Object Layout (C++11–C++20)

Lambdas without captures are empty objects (size = 1 byte).
With captures → size increases.

PROGRAM 8: Lambda Object Sizes
#include <iostream>

int main() {
    auto empty = []() { return 1; };
    int a = 10;
    auto capture1 = [a]() { return a; };
    int b = 20;
    auto capture2 = [a, b]() { return a + b; };

    std::cout << "Size of empty lambda: " << sizeof(empty) << "\n";
    std::cout << "Size of lambda with 1 capture: " << sizeof(capture1) << "\n";
    std::cout << "Size of lambda with 2 captures: " << sizeof(capture2) << "\n";
}

Output (may vary)
Size of empty lambda: 1
Size of lambda with 1 capture: 4
Size of lambda with 2 captures: 8

✅ 8. Immutable vs Mutable Functors (Mutable Lambdas)
PROGRAM 9: Mutable Lambda vs Non-Mutable
#include <iostream>

int main() {
    int x = 10;

    auto normal = [x]() {
        // x++;  // ERROR: cannot modify captured-by-value
        return x;
    };

    auto mutableLambda = [x]() mutable {
        x++;  // OK: modifies internal copy
        return x;
    };

    std::cout << "Normal: " << normal() << "\n";
    std::cout << "Mutable lambda: " << mutableLambda() << "\n";
}

Output
Normal: 10
Mutable lambda: 11







✅ 1. Lambda + Ranges (C++20)

Use lambdas inside std::ranges pipelines.

✔ PROGRAM 1: Sorting, Filtering, Transforming with Ranges
#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> v = {1, 5, 10, 2, 9, 3};

    // Filter even numbers, then multiply by 3
    auto view = v
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 3; });

    std::cout << "Even * 3: ";
    for (int x : view)
        std::cout << x << " ";
    std::cout << "\n";

    // Sort using ranges + lambda
    std::ranges::sort(v, [](int a, int b) { return a > b; });

    std::cout << "Sorted descending: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

Output
Even * 3: 30 6 
Sorted descending: 10 9 5 3 2 1

✅ 2. Lambda + Module Interface (C++20 Modules)

We define a module exporting a lambda and call it from main.

✔ PROGRAM 2: C++20 Lambda inside Module
math_tools.ixx
export module math_tools;

export auto add = [](int a, int b) {
    return a + b;
};

export auto square = [](int x) {
    return x * x;
};

main.cpp
import math_tools;
#include <iostream>

int main() {
    std::cout << "Add: " << add(3, 4) << "\n";
    std::cout << "Square: " << square(5) << "\n";
}

Output
Add: 7
Square: 25

✅ 3. Lambda + constexpr (C++17–C++20)

Lambdas can be evaluated at compile-time if marked constexpr.

✔ PROGRAM 3: constexpr Lambda
#include <iostream>

int main() {
    constexpr auto sq = [](int x) { return x * x; };

    constexpr int val = sq(6);

    std::cout << "Compile-time square: " << val << "\n";
}

Output
Compile-time square: 36

✔ PROGRAM 3B: constexpr + template lambdas
#include <iostream>

int main() {
    constexpr auto maxVal = []<typename T>(T a, T b) {
        return (a > b) ? a : b;
    };

    constexpr int a = maxVal(10, 20);
    constexpr double b = maxVal(3.4, 1.2);

    std::cout << a << " " << b << "\n";
}

Output
20 3.4

✅ 4. Lambda Overloads (C++20)

C++20 allows overload sets using lambda composition or generic lambdas.

✔ PROGRAM 4: Overloaded Lambda (using struct)
#include <iostream>
#include <variant>

struct Overload {
    auto operator()(int x) const { return "int"; }
    auto operator()(double x) const { return "double"; }
    auto operator()(const std::string& x) const { return "string"; }
};

int main() {
    std::variant<int, double, std::string> v = 3.14;

    std::cout << std::visit(Overload{}, v) << "\n";
}

Output
double

✔ PROGRAM 4B: Overload Using C++20 Lambda + Template
#include <iostream>
#include <variant>

auto overloaded = []<typename T>(T x) {
    if constexpr (std::is_same_v<T, int>) return "int";
    else if constexpr (std::is_same_v<T, double>) return "double";
    else return "other";
};

int main() {
    std::cout << overloaded(42) << "\n";
    std::cout << overloaded(3.14) << "\n";
    std::cout << overloaded("hello") << "\n";
}

Output
int
double
other

✅ 5. Stateful Functors vs Lambdas

A functor stores state in a class; lambda stores captures in closure object.

✔ PROGRAM 5A: Stateful Functor
#include <iostream>

struct CounterFunctor {
    int count = 0;

    int operator()(int x) {
        return x + (++count);
    }
};

int main() {
    CounterFunctor cf;

    std::cout << cf(10) << "\n"; // adds 1
    std::cout << cf(10) << "\n"; // adds 2
    std::cout << cf(10) << "\n"; // adds 3
}

Output
11
12
13

✔ PROGRAM 5B: Equivalent Lambda (Stateful via mutable)
#include <iostream>

int main() {
    auto lambdaCounter = [count = 0](int x) mutable {
        return x + (++count);
    };

    std::cout << lambdaCounter(10) << "\n"; 
    std::cout << lambdaCounter(10) << "\n";
    std::cout << lambdaCounter(10) << "\n";
}

Output
11
12
13

✔ PROGRAM 5C: Comparing sizes
#include <iostream>

struct Functor { int a = 10; };

int main() {
    Functor f;
    auto lambda = [a = 10]() {};

    std::cout << "Functor size: " << sizeof(f) << "\n";
    std::cout << "Lambda size: "  << sizeof(lambda) << "\n";
}

Possible Output
Functor size: 4
Lambda size: 4


Both store an int → same size.





1) std::function performance comparison

Compare: direct call, std::function invoking a lambda, function pointer. 
Timings use a tight loop; use -O2 when compiling for realistic numbers.

// file: func_performance.cpp
// Compile: g++ -std=c++17 func_performance.cpp -O2 -march=native -o func_performance
#include <bits/stdc++.h>
using namespace std;
using clk = chrono::high_resolution_clock;

inline int direct_add(int a, int b) { return a + b; }

int main() {
    const int N = 50'000'000;
    volatile int sink = 0;

    // 1) direct inline lambda
    auto lambda = [](int x, int y) { return x + y; };
    {
        auto t0 = clk::now();
        int s = 0;
        for (int i = 0; i < N; ++i) s += lambda(i, i);
        sink = s;
        auto t1 = clk::now();
        cout << "lambda direct: "
             << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " ms\n";
    }

    // 2) function pointer
    int (*fptr)(int,int) = direct_add;
    {
        auto t0 = clk::now();
        int s = 0;
        for (int i = 0; i < N; ++i) s += fptr(i, i);
        sink = s;
        auto t1 = clk::now();
        cout << "function pointer: "
             << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " ms\n";
    }

    // 3) std::function
    function<int(int,int)> sf = lambda;
    {
        auto t0 = clk::now();
        int s = 0;
        for (int i = 0; i < N; ++i) s += sf(i, i);
        sink = s;
        auto t1 = clk::now();
        cout << "std::function: "
             << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " ms\n";
    }

    // Print sink to avoid optimizing away
    cout << "sink = " << sink << "\n";
    return 0;
}


Sample output (will vary by machine; typical ordering)

lambda direct: 120 ms
function pointer: 140 ms
std::function: 350 ms
sink = 6350000000


Notes: std::function adds type-erasure overhead. For hot inner loops prefer direct lambda/function pointer or templates.

2) std::packaged_task and std::async with lambdas

Show use of packaged_task + future and std::async launching lambdas.

// file: async_packaged_task.cpp
// Compile: g++ -std=c++17 async_packaged_task.cpp -O2 -pthread -o async_packaged_task
#include <bits/stdc++.h>
using namespace std;

int main() {
    // packaged_task example
    packaged_task<int(int,int)> task([](int a,int b){
        this_thread::sleep_for(chrono::milliseconds(50)); // simulate work
        return a + b;
    });
    future<int> fut = task.get_future();
    // run task on separate thread
    thread t(move(task), 3, 4);
    cout << "packaged_task launched\n";
    cout << "packaged_task result = " << fut.get() << "\n";
    t.join();

    // std::async example
    auto fut2 = async(launch::async, [](int a,int b){
        this_thread::sleep_for(chrono::milliseconds(50));
        return a * b;
    }, 6, 7);
    cout << "async launched\n";
    cout << "async result = " << fut2.get() << "\n";

    return 0;
}


Sample output

packaged_task launched
packaged_task result = 7
async launched
async result = 42


Notes: packaged_task gives manual control of where to run the task; std::async decides policy (use launch::async or launch::deferred).

3) std::bind vs modern lambda captures

Show differences: readability, ability to capture move-only objects, and type-safety.

// file: bind_vs_lambda.cpp
// Compile: g++ -std=c++17 bind_vs_lambda.cpp -O2 -o bind_vs_lambda
#include <bits/stdc++.h>
using namespace std;

int add(int a, int b) { return a + b; }

int main() {
    // std::bind example (placeholders)
    using namespace placeholders;
    auto bound = bind(add, 10, _1); // sets first arg to 10
    cout << "bind(10,_1) with 5 => " << bound(5) << "\n";

    // lambda equivalent
    auto lambda = [](int x){ return add(10, x); };
    cout << "lambda(5) => " << lambda(5) << "\n";

    // move-only capture: std::bind can't capture move-only directly; lambda can
    auto ptr = make_unique<int>(123);
    // auto b2 = bind([](unique_ptr<int> p){ return *p; }, std::move(ptr)); // ill-formed
    auto l2 = [p = move(ptr)](){ return *p; }; // perfect: lambda move-capture
    cout << "move-captured unique_ptr value via lambda: " << l2() << "\n";

    // placeholders with additional args
    auto b3 = bind(add, _2, _1);
    cout << "bind with swapped placeholders: b3(3,4) => " << b3(3,4) << "\n";

    return 0;
}


Sample output

bind(10,_1) with 5 => 15
lambda(5) => 15
move-captured unique_ptr value via lambda: 123
bind with swapped placeholders: b3(3,4) => 7


Notes: Prefer lambdas: clearer, supports move captures, less error-prone. std::bind remains useful for some adapter patterns.

4) Lambda ABI: closure layout & inspection

We can not inspect compiler ABI internals precisely, but we can observe closure object size and compare addresses of captured members 
via reinterpret_cast and memcpy to examine layout in a portable-safe way (read-only view). 
We'll demonstrate: empty lambda size, lambda with captures, and that captured values are stored inside the closure object.

// file: lambda_abi_inspect.cpp
// Compile: g++ -std=c++17 lambda_abi_inspect.cpp -O2 -o lambda_abi_inspect
#include <bits/stdc++.h>
using namespace std;

struct RawView {
    const void* ptr;
    size_t size;
};

int main() {
    int a = 0x11223344;
    double d = 3.1415;
    auto L = [a, d]() { return a + (int)d; }; // closure holds both

    cout << "sizeof(lambda) = " << sizeof(L) << " bytes\n";

    // View raw bytes of closure object
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&L);
    cout << "raw bytes (first 32 bytes): ";
    for (size_t i = 0; i < min<size_t>(sizeof(L), 32); ++i)
        printf("%02x ", p[i]);
    cout << "\n";

    // Extract first 4 bytes as int (likely holds 'a' on little-endian)
    int extracted_int = 0;
    if (sizeof(L) >= sizeof(int)) {
        memcpy(&extracted_int, &L, sizeof(int));
        printf("extracted int (likely a) = 0x%08x = %d\n", extracted_int, extracted_int);
    }
    // Note: layout is implementation-defined (compiler arranges captured members).
    // This demo shows captures are stored inside closure object.
    cout << "Invoking lambda -> " << L() << "\n";
    return 0;
}


Sample output (x86_64 little-endian, GCC — exact bytes may differ)

sizeof(lambda) = 16 bytes
raw bytes (first 32 bytes): 44 33 22 11 58 39 0f 40 00 00 00 00 00 00 00 00 
extracted int (likely a) = 0x11223344 = 287454020
Invoking lambda -> 287454023


Notes: Closure layout (ordering, padding) is implementation-defined. 
This program demonstrates that captured values are embedded in the closure object.

5) Lambda + SIMD-style / parallel execution (std::execution)

Use std::transform with std::execution::par_unseq to let the implementation vectorize/parallelize the lambda. 
Requires a C++17/20 standard library with parallel algorithms (libstdc++ with Parallel Mode or MSVC). 
If your toolchain does not support par_unseq, fallback to par.

// file: lambda_parallel.cpp
// Compile: g++ -std=c++17 -O3 -march=native lambda_parallel.cpp -lstdc++ -fopenmp -o lambda_parallel
// Note: actual parallel execution support depends on your standard library build.
// On GCC libstdc++ you may need -ltbb or link with parallel mode; behavior varies.
#include <bits/stdc++.h>
#include <execution>
using namespace std;

int main() {
    const size_t N = 10'000'000;
    vector<float> a(N), b(N);
    for (size_t i=0;i<N;++i) { a[i] = i * 0.5f; }

    // element-wise operation (SIMD-friendly)
    auto start = chrono::high_resolution_clock::now();
    // sequential
    transform(a.begin(), a.end(), b.begin(), [](float x){ return x * x + 1.0f; });
    auto mid = chrono::high_resolution_clock::now();

    // parallel (may auto-vectorize and use threads)
    vector<float> b2(N);
    transform(execution::par_unseq, a.begin(), a.end(), b2.begin(), [](float x){ return x * x + 1.0f; });
    auto end = chrono::high_resolution_clock::now();

    cout << "seq ms: " << chrono::duration_cast<chrono::milliseconds>(mid - start).count() << "\n";
    cout << "par_unseq ms: " << chrono::duration_cast<chrono::milliseconds>(end - mid).count() << "\n";

    // sanity:
    cout << "sample: " << b[12345] << " vs " << b2[12345] << "\n";
    return 0;
}
/* 
Sample output (highly toolchain- and machine-dependent)
seq ms: 210 ms
par_unseq ms: 60 ms
sample: 76296960 vs 76296960
*/

Notes & Caveats:
std::execution::par_unseq allows parallel + vectorized execution; correctness requires the lambda to be free of data races and side-effects.
Real speedup depends on hardware, compiler, and runtime support (TBB, OpenMP, libstdc++ parallel mode).
If your standard library lacks parallel algorithm support, compile may fail — try replacing par_unseq with par or just transform sequentially.


