20 UB MULTITHREADING PREDICTION PROBLEMS (C++)
⚠️ UB-1: Data race on global variable
🔍 Theory
Concurrent write without synchronization → data race = UB

#include <iostream>
#include <thread>
using namespace std;
int x = 0;
void f() { 
    x++; 
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
    cout << x << "\n";
}
/* 
❌ Result
Undefined Behavior (any value)
*/




⚠️ UB-2: Read–write race
#include <iostream>
#include <thread>
using namespace std;
int x = 0;
void writer() { x = 10; }
void reader() { cout << x << "\n"; }
int main() {
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
❌ Result
UB (may print 0, 10, garbage)
*/





⚠️ UB-3: Non-atomic increment
#include <iostream>
#include <thread>
using namespace std;
int x = 0;
void inc() {
    for (int i = 0; i < 100000; i++)
        x++;
}
int main() {
    thread t1(inc), t2(inc);
    t1.join(); t2.join();
    cout << x << "\n";
}
/* 
❌ Result
UB (lost updates)
*/




⚠️ UB-4: Detached thread accessing local variable
#include <iostream>
#include <thread>
using namespace std;
void f(int* p) {
    cout << *p << "\n";
}
int main() {
    int x = 5;
    thread t(f, &x);
    t.detach();
}
/* 
❌ Result
UB (dangling pointer)
*/





⚠️ UB-5: Thread object destroyed without join/detach
#include <thread>
using namespace std;
void f() {}
int main() {
    thread t(f);
}
/* 
❌ Result
std::terminate()
*/




⚠️ UB-6: Double locking same mutex (non-recursive)
#include <mutex>
using namespace std;
mutex m;
int main() {
    m.lock();
    m.lock();
}
/* 
❌ Result
Deadlock / UB
*/




⚠️ UB-7: Unlock mutex not owned by thread
#include <mutex>
#include <thread>
using namespace std;
mutex m;
void f() {
    m.unlock();
}
int main() {
    m.lock();
    thread t(f);
    t.join();
}
/* 
❌ Result
UB
*/




⚠️ UB-8: Destroying locked mutex
#include <mutex>
using namespace std;
int main() {
    mutex m;
    m.lock();
}
/* 
❌ Result
UB
*/




⚠️ UB-9: Condition variable without mutex
#include <condition_variable>
using namespace std;
condition_variable cv;
int main() {
    cv.wait(*(unique_lock<mutex>*)nullptr);
}
/* 
❌ Result
UB
*/




⚠️ UB-10: Notify without happens-before
#include <thread>
#include <condition_variable>
using namespace std;
bool ready = false;
condition_variable cv;
mutex m;
void worker() {
    unique_lock<mutex> lk(m);
    cv.wait(lk, []{ return ready; });
}
int main() {
    ready = true;   // no lock
    cv.notify_one();
    thread t(worker);
    t.join();
}
/* 
❌ Result
UB / hang
*/



⚠️ UB-11: Race on pointer initialization
#include <thread>
using namespace std;
int* p = nullptr;
void f() {
    if (!p)
        p = new int(5);
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
❌ Result
UB (double allocation / leak)
*/







⚠️ UB-12: Publishing partially constructed object
#include <thread>
using namespace std;
struct A {
    int x;
    A() : x(42) {}
};
A* p;
void writer() {
    p = new A;
}
void reader() {
    if (p)
        p->x;
}
int main() {
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
❌ Result
UB (no synchronization)
*/



⚠️ UB-13: Race on std::string
#include <string>
#include <thread>
using namespace std;

string s;

void w() { s = "hello"; }
void r() { auto x = s; }

int main() {
    thread t1(w), t2(r);
    t1.join(); t2.join();
}
/* 
❌ Result
UB
*/




⚠️ UB-14: Accessing vector concurrently
#include <vector>
#include <thread>
using namespace std;
vector<int> v;
void f() { 
    v.push_back(1); 
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
❌ Result
UB (reallocation race)
*/





⚠️ UB-15: Race on function-local static (pre-C++11)
#include <thread>
using namespace std;
int& get() {
    static int x = 0;
    return x;
}
void f() { 
    get(); 
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
❌ Result
UB in pre-C++11
*/





⚠️ UB-16: Exception escaping thread
#include <thread>
using namespace std;
void f() {
    throw 1;
}
int main() {
    thread t(f);
    t.join();
}
/* 
❌ Result
std::terminate()
*/



⚠️ UB-17: Destroying condition_variable while waiting
#include <thread>
#include <condition_variable>
using namespace std;
condition_variable* cv = new condition_variable;
mutex m;
void f() {
    unique_lock<mutex> lk(m);
    cv->wait(lk);
}
int main() {
    thread t(f);
    delete cv;
    t.join();
}
/* 
❌ Result
UB
*/




⚠️ UB-18: Using volatile for synchronization
#include <thread>
using namespace std;
volatile bool ready = false;
void f() {
    while (!ready) {}
}
int main() {
    thread t(f);
    ready = true;
    t.join();
}
/* 
❌ Result
UB (volatile ≠ atomic)
*/





⚠️ UB-19: Destroying object while another thread uses it
#include <thread>
using namespace std;
struct A { 
    int x; 
};
A* p = new A{5};
void f() {
    p->x = 10;
}
int main() {
    thread t(f);
    delete p;
    t.join();
}
/* 
❌ Result
UB (use-after-free)
*/




⚠️ UB-20: Atomic misuse (non-atomic compound op)
#include <atomic>
#include <thread>
using namespace std;
atomic<int> x{0};
void f() {
    int y = x;
    x = y + 1;
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
❌ Result
UB-like logic error (lost update)
*/



















✅ 20 FIXED MULTITHREADING PROGRAMS (Correct Synchronization)
✅ FIX-1: Atomic increment (no data race)
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
atomic<int> x{0};
void inc() { 
    x.fetch_add(1); 
}
int main() {
    thread t1(inc), t2(inc);
    t1.join(); t2.join();
    cout << x << "\n";
}
/* 
Output
2
*/


✅ FIX-2: Mutex-protected read/write
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int x = 0;
mutex m;
void writer() {
    lock_guard<mutex> lg(m);
    x = 10;
}
void reader() {
 
    lock_guard<mutex> lg(m);
    cout << x << "\n";
}
int main() {
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
Output
10
*/




✅ FIX-3: Safe counter with mutex
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int x = 0;
mutex m;
void inc() {
    for (int i = 0; i < 100000; ++i) {
        lock_guard<mutex> lg(m);
        ++x;
    }
}
int main() {
    thread t1(inc), t2(inc);
    t1.join(); t2.join();
    cout << x << "\n";
}
/* 
Output
200000
*/




✅ FIX-4: Join thread before scope ends
#include <iostream>
#include <thread>
using namespace std;
void f(int v) { 
    cout << v << "\n"; 
}
int main() {
    int x = 5;
    thread t(f, x);
    t.join();
}
/* 
Output
5
*/




✅ FIX-5: Always join or detach
#include <iostream>
#include <thread>
using namespace std;
void f() { 
    cout << "OK\n"; 
}
int main() {
    thread t(f);
    t.join();
}
/* 
Output
OK
*/




✅ FIX-6: Recursive mutex for re-locking
#include <iostream>
#include <mutex>
using namespace std;
recursive_mutex m;
void f(int n) {
    if (n == 0) return;
    lock_guard<recursive_mutex> lg(m);
    f(n - 1);
}
int main() {
    f(3);
    cout << "Done\n";
}
/* 
Output
Done
*/



✅ FIX-7: Unlock only by owning thread
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex m;
void f() {
    lock_guard<mutex> lg(m);
    cout << "Locked\n";
}
int main() {
    thread t(f);
    t.join();
}
/* 
Output
Locked
*/



✅ FIX-8: Proper mutex lifetime
#include <iostream>
#include <mutex>
using namespace std;
int main() {
    mutex m;
    {
        lock_guard<mutex> lg(m);
        cout << "Safe\n";
    }
}
/* 
Output
Safe
*/




✅ FIX-9: Correct condition_variable usage
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
mutex m;
condition_variable cv;
bool ready = false;
void worker() {
    unique_lock<mutex> lk(m);
    cv.wait(lk, [] { return ready; });
    cout << "Go\n";
}
int main() {
    thread t(worker);
    {
        lock_guard<mutex> lg(m);
        ready = true;
    }
    cv.notify_one();
    t.join();
}
/* 
Output
Go
*/



✅ FIX-10: Proper happens-before with CV
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
mutex m;
condition_variable cv;
bool ready = false;
int main() {
    thread t([&]{
        unique_lock<mutex> lk(m);
        cv.wait(lk, [&]{ return ready; });
        cout << "Ready\n";
    });

    {
        lock_guard<mutex> lg(m);
        ready = true;
    }
    cv.notify_one();
    t.join();
}
/* 
Output
Ready
*/




✅ FIX-11: Safe singleton initialization
#include <iostream>
#include <thread>
using namespace std;
int& get() {
    static int x = 10; // thread-safe since C++11
    return x;
}
void f() { 
    cout << get() << "\n"; 
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
Output
10
10
*/



✅ FIX-12: Publish object with mutex
#include <thread>
#include <mutex>
using namespace std;
struct A { 
    int x; 
};
A* p = nullptr;
mutex m;
void writer() {
    lock_guard<mutex> lg(m);
    p = new A{42};
}
void reader() {
    lock_guard<mutex> lg(m);
    if (p) { /* safe */ }
}
int main() {
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
Output
(no output, but safe)
*/



✅ FIX-13: Protect std::string
#include <string>
#include <thread>
#include <mutex>
using namespace std;
string s;
mutex m;
void w() { 
    lock_guard<mutex> lg(m); 
    s = "hello"; 
}
void r() { 
    lock_guard<mutex> lg(m); 
    auto x = s; 
}
int main() {
    thread t1(w), t2(r);
    t1.join(); t2.join();
}
/* 
Output
(no output, safe)
*/




✅ FIX-14: Protect vector
#include <vector>
#include <thread>
#include <mutex>
using namespace std;
vector<int> v;
mutex m;
void f() {
    lock_guard<mutex> lg(m);
    v.push_back(1);
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
Output
(no output, safe)
*/




✅ FIX-15: Thread-safe static init (C++11+)
#include <iostream>
#include <thread>
using namespace std;
int& get() {
    static int x = []{ cout << "Init\n"; return 5; }();
    return x;
}
void f() { 
    get(); 
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
Output
Init
*/




✅ FIX-16: Catch exceptions inside thread
#include <iostream>
#include <thread>
using namespace std;
void f() {
    try {
        throw 1;
    } catch (...) {
        cout << "Handled\n";
    }
}
int main() {
    thread t(f);
    t.join();
}
/* 
Output
Handled
*/



✅ FIX-17: Safe condition_variable lifetime
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;
condition_variable cv;
mutex m;
bool done = false;
void f() {
    unique_lock<mutex> lk(m);
    cv.wait(lk, []{ return done; });
}
int main() {
    thread t(f);
    {
        lock_guard<mutex> lg(m);
        done = true;
    }
    cv.notify_one();
    t.join();
}
/* 
Output
(no output, safe)
*/



✅ FIX-18: Use atomic instead of volatile
#include <atomic>
#include <thread>
using namespace std;
atomic<bool> ready{false};
void f() {
    while (!ready.load()) {}
}
int main() {
    thread t(f);
    ready.store(true);
    t.join();
}
/* 
Output
(no output, safe)
*/




✅ FIX-19: Lifetime management with join
#include <thread>
using namespace std;
struct A { 
    int x; 
};

int main() {
    A a{5};
    thread t([&]{ a.x = 10; });
    t.join();
}
/* 
Output
(no output, safe)
*/



✅ FIX-20: Correct atomic increment
#include <atomic>
#include <thread>
#include <iostream>
using namespace std;
atomic<int> x{0};
void f() {
    x.fetch_add(1, memory_order_relaxed);
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
    cout << x << "\n";
}
/* 
Output
Copy code
2
*/




















🧠 1) MEMORY ORDERING
(relaxed / acquire / release)

🔹 Program 1: memory_order_relaxed (NO ordering guarantee)
📘 Theory
Atomicity ✔
Ordering ❌
Visibility ❌
Used for counters, statistics


#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
atomic<int> data{0};
atomic<bool> ready{false};
void producer() {
    data.store(42, memory_order_relaxed);
    ready.store(true, memory_order_relaxed);
}
void consumer() {
    while (!ready.load(memory_order_relaxed)) {}
    cout << data.load(memory_order_relaxed) << "\n";
}
int main() {
    thread t1(producer), t2(consumer);
    t1.join(); t2.join();
}
/* 
⚠️ Output
42   (OR stale / undefined value on weak architectures)

🔥 Key
No happens-before relationship
*/



🔹 Program 2: release / acquire (CORRECT producer-consumer)
📘 Theory
release publishes writes
acquire observes them
Establishes happens-before

#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
atomic<int> data{0};
atomic<bool> ready{false};
void producer() {
    data.store(42, memory_order_relaxed);
    ready.store(true, memory_order_release);
}
void consumer() {
    while (!ready.load(memory_order_acquire)) {}
    cout << data.load(memory_order_relaxed) << "\n";
}
int main() {
    thread t1(producer), t2(consumer);
    t1.join(); t2.join();
}
/* 
✅ Output
42

🔥 Key
Acquire synchronizes with Release
*/




🔹 Program 3: memory_order_seq_cst (strongest)
📘 Theory
Total global order
Simplest
Slowest

#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
atomic<int> x{0}, y{0};
void f() {
    x.store(1);
    cout << y.load() << "\n";
}
void g() {
    y.store(1);
    cout << x.load() << "\n";
}
int main() {
    thread t1(f), t2(g);
    t1.join(); t2.join();
}
/* 
✅ Output
0 or 1 (but NOT both 0)
*/



🧠 2) LOCK-FREE PITFALLS
🔹 Program 4: Lock-free ≠ wait-free
📘 Theory
Lock-free: some thread progresses
Starvation possible

#include <atomic>
#include <thread>
#include <iostream>
using namespace std;
atomic<int> x{0};
void f() {
    for (;;) {
        int expected = 0;
        if (x.compare_exchange_weak(expected, 1))
            break;
    }
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
    cout << x << "\n";
}
/* 
⚠️ Output
1   (one thread may spin long)
*/




🔹 Program 5: ABA problem (classic lock-free bug)
📘 Theory
Pointer value same ≠ same object

#include <atomic>
#include <iostream>
using namespace std;
atomic<int*> p;
int main() {
    int a = 1, b = 2;
    p.store(&a);

    int* old = &a;
    p.store(&b);
    p.store(&a); // ABA

    cout << (*p.load()) << "\n";
}
/* 
⚠️ Output
1 (but object identity changed!)

🔥 Fix
Use version counters / hazard pointers
*/




🔹 Program 6: compare_exchange_weak misuse
#include <atomic>
#include <iostream>
using namespace std;

int main() {
    atomic<int> x{0};
    int expected = 1;

    x.compare_exchange_weak(expected, 2);

    cout << x << "\n";
}
/* 
⚠️ Output
0

🔥 Key
expected must match current value

🧠 3) RTOS / MISRA-SAFE CONCURRENCY
MISRA discourages:
❌ Exceptions
❌ Detached threads
❌ Dynamic allocation
❌ Busy waiting
*/



🔹 Program 7: Mutex + error code (MISRA-safe)
#include <mutex>
#include <iostream>
using namespace std;
mutex m;
int shared = 0;
bool update(int v) {
    lock_guard<mutex> lg(m);
    shared = v;
    return true;
}
int main() {
    if (update(10))
        cout << shared << "\n";
}
/* 
✅ Output
10
*/



🔹 Program 8: Atomic flag instead of condition_variable
📘 RTOS-friendly
No blocking kernel primitives

#include <atomic>
#include <thread>
#include <iostream>
using namespace std;
atomic<bool> ready{false};
void worker() {
    while (!ready.load(memory_order_acquire)) {}
    cout << "Run\n";
}
int main() {
    thread t(worker);
    ready.store(true, memory_order_release);
    t.join();
}
/* 
✅ Output
Run
*/



🔹 Program 9: Static allocation only (MISRA)
#include <thread>
#include <iostream>
using namespace std;
int shared = 0;
void f() {
    shared = 5;
}
int main() {
    thread t(f);
    t.join();
    cout << shared << "\n";
}
/* 
✅ Output
5
*/






🧠 4) HOW COMPILERS EXPLOIT UB IN THREADS
🔹 Program 10: Compiler assumes no data race
📘 Theory
If data race exists → compiler may reorder freely

#include <thread>
#include <iostream>
using namespace std;
bool done = false;
void worker() {
    while (!done) {}
    cout << "Done\n";
}
int main() {
    thread t(worker);
    done = true;
    t.join();
}
/* 
❌ Result
Program may hang forever

🔥 Reason
Compiler assumes done never changes
*/





🔹 Program 11: Reordering breaks logic
#include <thread>
#include <iostream>
using namespace std;
int x = 0;
bool ready = false;
void writer() {
    x = 42;
    ready = true;
}
void reader() {
    if (ready)
        cout << x << "\n";
}
int main() {
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
❌ Output
May print 0
*/




🔹 Program 12: Fixed using atomics
#include <atomic>
#include <thread>
#include <iostream>
using namespace std;
atomic<int> x{0};
atomic<bool> ready{false};
void writer() {
    x.store(42, memory_order_relaxed);
    ready.store(true, memory_order_release);
}
void reader() {
    if (ready.load(memory_order_acquire))
        cout << x.load(memory_order_relaxed) << "\n";
}
int main() {
    thread t1(writer), t2(reader);
    t1.join(); t2.join();
}
/* 
✅ Output
42
*/






Lock-Free Stack (Correct, Minimal)
⚠️ This version is lock-free but NOT ABA-safe
(Still perfect for interviews)

✅ Code
#include <atomic>
#include <thread>
#include <iostream>
using namespace std;
struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};
class LockFreeStack {
    atomic<Node*> head;

  public:
    LockFreeStack() : head(nullptr) {}

    void push(int v) {
        Node* new_node = new Node(v);
        new_node->next = head.load(memory_order_relaxed);

        while (!head.compare_exchange_weak(
            new_node->next,
            new_node,
            memory_order_release,
            memory_order_relaxed)) {
        }
    }

    bool pop(int& result) {
        Node* old_head = head.load(memory_order_relaxed);

        while (old_head &&
               !head.compare_exchange_weak(
                   old_head,
                   old_head->next,
                   memory_order_acquire,
                   memory_order_relaxed)) {
        }

        if (!old_head)
            return false;

        result = old_head->value;
        delete old_head;
        return true;
    }
};

int main() {
    LockFreeStack s;

    thread t1([&] {
        for (int i = 0; i < 5; ++i)
            s.push(i);
    });

    thread t2([&] {
        int x;
        for (int i = 0; i < 5; ++i) {
            while (!s.pop(x)) {}
            cout << x << " ";
        }
    });

    t1.join();
    t2.join();
}
/* 
✅ Output (example)
4 3 2 1 0

(order may vary)
*/