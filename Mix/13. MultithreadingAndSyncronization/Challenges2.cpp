🔴 4. Lock Contention & Scalability
Mutex becomes bottleneck under high thread counts
Priority inversion
Convoying effect
Oversubscription (more threads than cores)

Lock Contention & Scalability (C++)
✅ Complete Code
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::mutex mtx;
int shared_resource = 0;

void worker(int id) {
    auto start = std::chrono::steady_clock::now();

    mtx.lock();  // Critical section start (contention point)
    std::cout << "Thread " << id << " acquired lock\n";

    // Simulate long work while holding lock (bad design)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    shared_resource++;

    mtx.unlock(); // Critical section end

    auto end = std::chrono::steady_clock::now();
    std::cout << "Thread " << id << " released lock after "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
    const int THREAD_COUNT = 8; // Oversubscription on 4-core CPU
    std::vector<std::thread> threads;

    std::cout << "Starting " << THREAD_COUNT << " threads\n";

    for (int i = 0; i < THREAD_COUNT; i++) {
        threads.emplace_back(worker, i);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Final shared_resource value = "
              << shared_resource << std::endl;

    return 0;
}
/* 
Output:
Starting 8 threads
Thread 0 acquired lock
Thread 0 released lock after 100 ms
Thread 3 acquired lock
Thread 3 released lock after 201 ms
Thread 6 acquired lock
Thread 6 released lock after 302 ms
Thread 1 acquired lock
Thread 1 released lock after 403 ms
Thread 5 acquired lock
Thread 5 released lock after 504 ms
Thread 2 acquired lock
Thread 2 released lock after 605 ms
Thread 7 acquired lock
Thread 7 released lock after 706 ms
Thread 4 acquired lock
Thread 4 released lock after 807 ms
Final shared_resource value = 8
*/



Mutex Contention & Scalability
Code (C++17)
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::mutex mtx;
int shared_counter = 0;

void worker(int id) {
    for (int i = 0; i < 3; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        mtx.lock(); // contention point
        std::cout << "Thread " << id << " acquired lock\n";

        // Simulate work while holding the lock (bad for scalability)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        shared_counter++;

        mtx.unlock();

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Thread " << id
                  << " released lock (wait+work = "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms)\n";
    }
}

int main() {
    const int num_threads = 8; // Oversubscription on a 4-core CPU
    std::vector<std::thread> threads;

    std::cout << "Starting " << num_threads << " threads\n";

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << shared_counter << "\n";
    return 0;
}
/* 
Compile & run:

g++ -std=c++17 -O2 mutex_demo.cpp -pthread
./a.out

Sample Output (abridged)
Starting 8 threads
Thread 0 acquired lock
Thread 0 released lock (wait+work = 101 ms)
Thread 3 acquired lock
Thread 3 released lock (wait+work = 201 ms)
Thread 5 acquired lock
Thread 5 released lock (wait+work = 302 ms)
Thread 1 acquired lock
Thread 1 released lock (wait+work = 403 ms)
...
Final counter value: 24

*/


🔴 5. Deadlocks (Advanced Forms)
Circular wait across multiple subsystems
Lock order inversion
Recursive deadlocks

Interaction between:
Mutexes
Condition variables
Futures
Deadlocks caused by exception paths

/* ------------------------------- */

1️⃣ Circular Wait Across Multiple Subsystems
Code
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex dbMutex;
std::mutex logMutex;

void subsystemA() {
    std::lock_guard<std::mutex> lock1(dbMutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(logMutex);
    std::cout << "Subsystem A finished\n";
}

void subsystemB() {
    std::lock_guard<std::mutex> lock1(logMutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(dbMutex);
    std::cout << "Subsystem B finished\n";
}

int main() {
    std::thread t1(subsystemA);
    std::thread t2(subsystemB);

    t1.join();
    t2.join();
}
/* 
Output / Behavior
(no output – program hangs forever)

Explanation
A holds dbMutex, waits for logMutex
B holds logMutex, waits for dbMutex
Circular wait → deadlock
*/




2️⃣ Lock Order Inversion
Code
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1;
std::mutex m2;

void thread1() {
    std::lock_guard<std::mutex> l1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> l2(m2);
    std::cout << "Thread 1 completed\n";
}

void thread2() {
    std::lock_guard<std::mutex> l1(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> l2(m1);
    std::cout << "Thread 2 completed\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();
}
/* 
Output
(no output – deadlock)

Explanation
Same locks, different acquisition order
Classic lock order inversion
*/



3️⃣ Recursive Deadlock (Self-deadlock)
Code
#include <iostream>
#include <mutex>

std::mutex mtx;

void recursiveFunction(int depth) {
    mtx.lock();   // Deadlocks on second call
    std::cout << "Depth: " << depth << "\n";

    if (depth > 0)
        recursiveFunction(depth - 1);

    mtx.unlock();
}

int main() {
    recursiveFunction(1);
}
/* 
Output
Depth: 1
(program hangs)

Explanation
std::mutex is non-recursive
Same thread tries to lock twice → deadlock
*/



4️⃣ Mutex + Condition Variable Deadlock
Code
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waiter() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    std::cout << "Waiter proceeds\n";
}

void notifier() {
    std::lock_guard<std::mutex> lock(mtx);
    // BUG: notify never happens
}

int main() {
    std::thread t1(waiter);
    std::thread t2(notifier);

    t1.join();
    t2.join();
}
/* 
Output
(no output – waiter blocked forever)

Explanation
cv.notify_*() never called
Condition variable wait never satisfied
*/




5️⃣ Futures Deadlock (Thread Waiting on Itself)
Code
#include <iostream>
#include <future>

int main() {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread t([&]() {
        std::cout << "Waiting for future...\n";
        std::cout << future.get() << "\n"; // Deadlock
        promise.set_value(42);
    });

    t.join();
}
/* 
Output
Waiting for future...
(program hangs)

Explanation
Thread waits on a future
Same thread supposed to fulfill it
Self-deadlock
*/





6️⃣ Deadlock Caused by Exception Path
Code
#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx;
void faultyFunction() {
    mtx.lock();
    std::cout << "Lock acquired\n";
    throw std::runtime_error("Error occurred");
    mtx.unlock(); // Never reached
}
void worker() {
    try {
        faultyFunction();
    } catch (...) {
        std::cout << "Exception caught\n";
    }
}
int main() {
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();
}
/* 
Output
Lock acquired
Exception caught
(program hangs)

Explanation
Mutex not released due to exception
Second thread blocks forever
Fix: std::lock_guard / RAII
*/

/* ========================================================================== */



🔴 6. Livelock
Threads keep responding to each other but make no progress
Often caused by retry-based lock-free code
Much harder to detect than deadlocks







🔴 8. Atomic Operations Pitfalls
Incorrect atomic granularity
Mixed atomic & non-atomic access

False assumptions about atomicity of:
double
struct
Performance cost of atomics under contention






🔴 9. Thread Lifetime Management
Detached threads accessing destroyed objects
Thread leaks
Joining vs detaching mistakes
Destruction order issues at program shutdown






🔴 10. Exception Safety Across Threads
Exceptions escaping threads → std::terminate

Propagating exceptions safely using:
std::promise
std::future
Resource leaks when thread creation partially fails





🔴 11. Condition Variable Misuse
Spurious wakeups
Missed notifications
Incorrect predicate logic
Lost wakeups due to timing windows





🔴 12. Memory Allocation & Multithreading
Heap contention
Fragmentation under parallel allocation
False sharing in allocators

Need for:
Thread-local allocators
Custom memory pools






🔴 13. Thread Affinity & NUMA
NUMA locality issues
Memory allocated on one node, accessed on another
Thread migration costs
OS scheduler unpredictability






🔴 14. Priority & Real-Time Constraints
No native thread priority guarantees in standard C++
Priority inversion without priority inheritance
Real-time deadlines missed due to OS scheduling





🔴 15. Asynchronous Design Complexity
Callback hell
State explosion
Hard-to-reason control flow
Mixing async with blocking code






🔴 16. Debugging & Testing Difficulties
Non-deterministic bugs
Heisenbugs
Bugs disappear under debugger or logging
Reproducing timing-dependent failures





🔴 17. Tooling Limitations
Data race detectors (TSAN) false positives
Limited visibility into hardware reorderings
Platform-specific behavior differences





🔴 18. Mixing C++ Threads with OS / Libraries
Using C APIs with unknown thread-safety guarantees
Signal handling with threads
Fork + threads issues
Third-party libraries that are not thread-safe





🔴 19. Parallel Algorithm Design
Decomposition of work
Load balancing
Granularity control
Avoiding excessive synchronization




🔴 20. Performance vs Correctness Trade-offs
Locks are correct but slow
Lock-free is fast but fragile
Choosing correct abstraction level:
Threads
Tasks
Thread pools
Coroutines







PART 1: Data Races & Undefined Behavior (Beyond the Obvious)
We’ll cover three complete programs:

1️⃣ Plain data race
2️⃣ Hidden race via reference member
3️⃣ “Works on x86, breaks on ARM” via reordering

Each program:
✔ Full compilable code
✔ main() included
✔ Explanation of possible output
✔ Why it’s undefined behavior



Data Races & Undefined Behavior (Beyond the Obvious)
Races that occur only under specific CPU reorderings

Hidden races through:
Reference members
Lazy initialization
Static local variables
“Works on my machine” failures due to weak memory models (ARM, PowerPC)




1. Plain Data Race (Looks Harmless, Is UB)
❌ Code (Incorrect)
#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 1'000'000; ++i) {
        counter++;   // data race
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter = " << counter << "\n";
}

🔍 Possible Output
Counter = 2000000   (sometimes)
Counter = 1738421   (often)
Counter = random    (UB)

❗ Why This Is Broken

counter++ is read–modify–write

Two threads access it without synchronization

Undefined Behavior per C++ memory model

Even if it “works” on your machine, it is invalid C++.

🧪 2. Hidden Data Race via Reference Member (Very Common Bug)
❌ Code (Incorrect)
#include <iostream>
#include <thread>

struct Wrapper {
    int& ref;
    void increment() {
        ref++;   // race hidden behind reference
    }
};

int main() {
    int value = 0;
    Wrapper w{value};

    std::thread t1([&] {
        for (int i = 0; i < 100000; ++i)
            w.increment();
    });

    std::thread t2([&] {
        for (int i = 0; i < 100000; ++i)
            w.increment();
    });

    t1.join();
    t2.join();

    std::cout << "Value = " << value << "\n";
}

🔍 Possible Output
Value = 200000   (sometimes)
Value = less than 200000

❗ Why This Is Dangerous

Reference hides shared state

Looks “object-oriented” and safe

Still a plain data race

Reference members do not add synchronization.

🧪 3. Reordering Bug (Works on x86, Breaks on ARM)
❌ Code (Incorrect)
#include <iostream>
#include <thread>

int data = 0;
bool ready = false;

void producer() {
    data = 42;
    ready = true;   // no memory ordering
}

void consumer() {
    while (!ready) { }
    std::cout << "Data = " << data << "\n";
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}

🔍 Possible Output
Data = 42   (x86 most of the time)
Data = 0    (ARM / weak memory models)

❗ Why This Happens

Compiler/CPU can reorder writes

ready = true becomes visible before data = 42

No happens-before relationship

This is a classic “works on my machine” bug

✅ Correct Version (Using Atomics)
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> ready{false};
int data = 0;

void producer() {
    data = 42;
    ready.store(true, std::memory_order_release);
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) { }
    std::cout << "Data = " << data << "\n";
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}

✔ Now guaranteed correct














PART 2: Memory Model Complexity (C++ Atomics Done Wrong & Right)
We’ll cover 3 complete programs:

1️⃣ memory_order_relaxed bug
2️⃣ Correct acquire / release usage
3️⃣ ABA problem (classic lock-free failure)

Each includes:
Full code
main()
What output may happen
Why it fails or works



Memory Model Complexity
Understanding C++ memory ordering
memory_order_relaxed
acquire / release
consume (mostly broken in practice)
Correct use of atomic fences
Compiler vs CPU reordering
ABA problem in lock-free algorithms



1. memory_order_relaxed — Atomic but Still Broken
❌ Code (Incorrect)
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> data{0};
std::atomic<bool> ready{false};

void producer() {
    data.store(42, std::memory_order_relaxed);
    ready.store(true, std::memory_order_relaxed);
}

void consumer() {
    while (!ready.load(std::memory_order_relaxed)) {}
    std::cout << "Data = " << data.load(std::memory_order_relaxed) << "\n";
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}

🔍 Possible Output
Data = 42
Data = 0

❗ Why This Fails

Atomics prevent data races, but not ordering

relaxed allows reordering

Consumer may see ready == true before data == 42

Atomic ≠ synchronized

🧪 2. Correct acquire / release Synchronization
✅ Code (Correct)
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> ready{false};
int data = 0;

void producer() {
    data = 42;
    ready.store(true, std::memory_order_release);
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) {}
    std::cout << "Data = " << data << "\n";
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}

🔍 Guaranteed Output
Data = 42

🧠 Why This Works

release prevents prior writes from moving after

acquire prevents later reads from moving before

Creates happens-before

🧪 3. ABA Problem (Lock-Free Bug That Atomics Don’t Fix)
❌ Code (Incorrect Lock-Free Stack)
#include <atomic>
#include <thread>
#include <iostream>

struct Node {
    int value;
    Node* next;
};

std::atomic<Node*> head{nullptr};

void push(Node* n) {
    n->next = head.load();
    while (!head.compare_exchange_weak(n->next, n)) {}
}

void pop() {
    Node* old_head = head.load();
    while (old_head &&
           !head.compare_exchange_weak(old_head, old_head->next)) {}
}

int main() {
    Node a{1, nullptr};
    Node b{2, nullptr};

    push(&a);
    push(&b);

    // Thread 1
    std::thread t1([] {
        pop();  // removes b
        pop();  // removes a
    });

    // Thread 2
    std::thread t2([] {
        push(new Node{3, nullptr});
    });

    t1.join();
    t2.join();

    std::cout << "Finished\n";
}

❗ What Goes Wrong (ABA)

Thread A reads head = A

Thread B pops A → pops B → pushes A again

Thread A thinks nothing changed (A == A)

CAS succeeds incorrectly

🔥 Result

Use-after-free

Corrupted stack

Random crashes

Atomics do not prevent ABA









PART 3: False Sharing (Correct Code, Terrible Performance)
False sharing causes massive slowdowns without breaking correctness — which is why it’s so dangerous.

We’ll cover 3 complete programs:

1️⃣ False sharing bug
2️⃣ Fix using padding
3️⃣ Fix using alignas

All code is:
Correct C++
Compilable
Same logic, different performance




False Sharing
Threads modifying different variables that share the same cache line
Performance degradation without correctness issues

Requires:
Cache line padding
alignas(64)
Hard to detect without profiling





1. False Sharing (Looks Fine, Runs Slow)
❌ Code (Performance Bug)
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

struct Counters {
    int a;
    int b;
};

Counters counters;

void incA() {
    for (int i = 0; i < 100'000'000; ++i)
        counters.a++;
}

void incB() {
    for (int i = 0; i < 100'000'000; ++i)
        counters.b++;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(incA);
    std::thread t2(incB);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "a=" << counters.a
              << " b=" << counters.b
              << " time=" << diff.count() << "s\n";
}

🔍 Output
a=100000000 b=100000000 time=2.3s   (example)

❗ What’s Wrong

a and b are on same cache line

Two cores invalidate each other constantly

Correct results, terrible performance

This is cache-line ping-pong

🧪 2. Fix #1 — Manual Padding
✅ Code (Faster)
#include <iostream>
#include <thread>
#include <chrono>

struct Counters {
    int a;
    char pad[64];   // separate cache line
    int b;
};

Counters counters;

void incA() {
    for (int i = 0; i < 100'000'000; ++i)
        counters.a++;
}

void incB() {
    for (int i = 0; i < 100'000'000; ++i)
        counters.b++;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(incA);
    std::thread t2(incB);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "a=" << counters.a
              << " b=" << counters.b
              << " time=" << diff.count() << "s\n";
}

🔍 Output
a=100000000 b=100000000 time=0.7s

🧪 3. Fix #2 — alignas(64) (Correct & Portable)
✅ Code (Best Practice)
#include <iostream>
#include <thread>
#include <chrono>

struct Counters {
    alignas(64) int a;
    alignas(64) int b;
};

Counters counters;

void incA() {
    for (int i = 0; i < 100'000'000; ++i)
        counters.a++;
}

void incB() {
    for (int i = 0; i < 100'000'000; ++i)
        counters.b++;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(incA);
    std::thread t2(incB);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "a=" << counters.a
              << " b=" << counters.b
              << " time=" << diff.count() << "s\n";
}

🔍 Output
a=100000000 b=100000000 time=0.6s

🧠 Why False Sharing Is Evil

❌ No wrong answers

❌ No crashes

❌ No warnings

❌ Sanitizers don’t catch it

✔ Only visible in profilers









Part 4: Deadlocks & Livelocks (Advanced Forms)
We’ll cover 3 complete programs:

1️⃣ Classic deadlock (lock order inversion)
2️⃣ Deadlock via exception path
3️⃣ Livelock (threads run but make no progress)

Each example:
Compiles
Has main()
Shows real failure modes



1. Classic Deadlock (Lock Order Inversion)
❌ Code (Deadlocks)
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void threadA() {
    std::lock_guard<std::mutex> l1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> l2(m2);
    std::cout << "Thread A done\n";
}

void threadB() {
    std::lock_guard<std::mutex> l1(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> l2(m1);
    std::cout << "Thread B done\n";
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();
}

🔍 Output
(no output — program hangs forever)

❗ Why It Deadlocks

Thread A holds m1, waits for m2

Thread B holds m2, waits for m1

Circular wait condition

✅ Correct Fix — std::lock
void threadA() {
    std::lock(m1, m2);
    std::lock_guard<std::mutex> l1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> l2(m2, std::adopt_lock);
    std::cout << "Thread A done\n";
}

🧪 2. Deadlock via Exception Path (Very Subtle)
❌ Code (Deadlocks)
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;

void dangerous() {
    m.lock();
    throw std::runtime_error("boom");
    m.unlock(); // never reached
}

int main() {
    try {
        dangerous();
    } catch (...) {}

    std::cout << "Trying to lock again...\n";
    m.lock();  // deadlock
    std::cout << "Never reached\n";
}

🔍 Output
Trying to lock again...
(program hangs)

❗ Why It Deadlocks

Exception skips unlock

Mutex permanently locked

✅ Correct Fix — RAII
void safe() {
    std::lock_guard<std::mutex> lock(m);
    throw std::runtime_error("boom");
}

🧪 3. Livelock (Threads Run, But No Progress)
❌ Code (Livelock)
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> readyA{false};
std::atomic<bool> readyB{false};

void threadA() {
    while (true) {
        if (!readyB.load()) {
            readyA.store(true);
        } else {
            readyA.store(false);
        }
    }
}

void threadB() {
    while (true) {
        if (!readyA.load()) {
            readyB.store(true);
        } else {
            readyB.store(false);
        }
    }
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();
}

🔍 Output
(no output, CPU at 100%)

❗ Why This Is Livelock

Threads keep reacting to each other

No blocking

No forward progress

Deadlock = threads stop
Livelock = threads spin forever










Part 5: Lock-Free & Wait-Free Programming (Real Failures & Reality)

We’ll cover 3 complete programs:

1️⃣ Correct CAS loop (lock-free increment)
2️⃣ Broken lock-free stack (ABA in practice)
3️⃣ Safe lock-free stack using tagged pointer



Lock-Free & Wait-Free Programming
Designing correct lock-free data structures

Memory reclamation problems:
Hazard pointers
Epoch-based reclamation
RCU
Proving correctness is extremely difficult
Subtle ABA bugs





🧪 1. Correct Lock-Free CAS Loop (Baseline)
✅ Code (Correct Lock-Free Counter)
#include <iostream>
#include <thread>
#include <atomic>
std::atomic<int> counter{0};
void increment() {
    for (int i = 0; i < 1'000'000; ++i) {
        int old = counter.load(std::memory_order_relaxed);
        while (!counter.compare_exchange_weak(
            old, old + 1,
            std::memory_order_release,
            std::memory_order_relaxed)) {
            // retry with updated 'old'
        }
    }
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter = " << counter << "\n";
}
/* 
🔍 Output
Counter = 2000000

🧠 Why This Works
CAS retries on contention
No locks
Lock-free (system makes progress)
*/




🧪 2. Broken Lock-Free Stack (ABA Bug)
❌ Code (Incorrect)
#include <atomic>
#include <thread>
#include <iostream>
struct Node {
    int value;
    Node* next;
};
std::atomic<Node*> head{nullptr};
void push(Node* n) {
    n->next = head.load(std::memory_order_relaxed);
    while (!head.compare_exchange_weak(
        n->next, n,
        std::memory_order_release,
        std::memory_order_relaxed)) {}
}
Node* pop() {
    Node* old = head.load(std::memory_order_relaxed);
    while (old &&
           !head.compare_exchange_weak(
               old, old->next,
               std::memory_order_acquire,
               std::memory_order_relaxed)) {}
    return old;
}
int main() {
    Node a{1, nullptr};
    Node b{2, nullptr};

    push(&a);
    push(&b);

    std::thread t1([] {
        Node* n1 = pop();
        Node* n2 = pop();
        delete n1;  // undefined if ABA occurs
        delete n2;
    });

    std::thread t2([] {
        push(new Node{3, nullptr});
    });

    t1.join();
    t2.join();

    std::cout << "Finished\n";
}
/* 
🔥 What Can Happen
Use-after-free
Corrupted list
Random crash

❗ Why CAS Fails Here
Pointer value goes A → B → A
CAS thinks nothing changed
Lifetime already invalid
Atomics do not track object lifetime
*/



🧪 3. Fix ABA with Tagged Pointer (Simplified)
✅ Code (Safer Lock-Free Stack)
#include <atomic>
#include <thread>
#include <iostream>
#include <cstdint>
struct Node {
    int value;
    Node* next;
};
struct TaggedPtr {
    Node* ptr;
    uint64_t tag;
};
std::atomic<TaggedPtr> head;
void push(Node* n) {
    TaggedPtr old = head.load();
    TaggedPtr neu;
    do {
        n->next = old.ptr;
        neu = {n, old.tag + 1};
    } while (!head.compare_exchange_weak(old, neu));
}
int main() {
    head.store({nullptr, 0});

    Node* n1 = new Node{1, nullptr};
    Node* n2 = new Node{2, nullptr};

    push(n1);
    push(n2);

    std::cout << "Tagged push completed\n";
}
/* 
🔍 Output
Tagged push completed

🧠 Why This Helps
Tag changes on every modification
ABA detected even if pointer matches
Still not trivial to make fully safe

⚠️ Note:
Real systems use:
Hazard pointers
Epoch-based reclamation
RCU
Tagged pointers alone are not enough for full safety.
*/