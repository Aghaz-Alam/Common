============================================
🔵 Program 1 — std::thread (C++11)
============================================
Program
#include <iostream>
#include <thread>

void worker(int id) {
    std::cout << "Worker " << id << " running in thread id " << std::this_thread::get_id() << "\n";
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    t1.join();
    t2.join();

    std::cout << "Main finished\n";
    return 0;
}
/* 
Realistic Output (threads may interleave differently)
Worker 1 running in thread id 140019187689216
Worker 2 running in thread id 140019179296512
Main finished

Clean Deterministic Output
Worker 1 running in thread id <id1>
Worker 2 running in thread id <id2>
Main finished


(IDs vary → use placeholders) 
*/

============================================
🔵 Program 2 — std::mutex + std::lock_guard (C++11)
============================================
Program
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;
int counter = 0;

void inc(int times) {
    for (int i = 0; i < times; ++i) {
        std::lock_guard<std::mutex> lg(mtx);
        ++counter;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) threads.emplace_back(inc, 1000);
    for (auto &t : threads) t.join();
    std::cout << "counter = " << counter << "\n";
    return 0;
}
/* 
Realistic Output
counter = 4000

Clean Deterministic Output
counter = 4000


(Always the same)
*/
============================================
🔵 Program 3 — std::unique_lock (C++11)
============================================
Program
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m;
int shared_data = 0;

void reader() {
    std::unique_lock<std::mutex> lk(m);
    std::cout << "Reader sees: " << shared_data << "\n";
    lk.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    lk.lock();
    std::cout << "Reader finished\n";
}

void writer() {
    std::unique_lock<std::mutex> lk(m);
    shared_data = 42;
    std::cout << "Writer updated shared_data\n";
}

int main() {
    std::thread t1(reader);
    std::thread t2(writer);
    t1.join(); t2.join();
    return 0;
}
/* 
Realistic Output (order depends on scheduling)
Reader sees: 0
Writer updated shared_data
Reader finished


(or writer may run first)

Clean Deterministic Output
Reader sees: 0
Writer updated shared_data
Reader finished
 */




✅ PROGRAM 5 — std::packaged_task (C++11)

Allows wrapping a callable so its result becomes a future.

Code
#include <iostream>
#include <future>
#include <thread>

int square(int x) {
    return x * x;
}

int main() {
    std::packaged_task<int(int)> task(square);
    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 12);
    t.join();

    std::cout << "Result = " << result.get() << "\n";
}
/* 
Realistic Output
Result = 144

Clean Output
Result = 144
*/




✅ PROGRAM 6 — std::promise + std::future (C++11)
Allows sending a value from one thread to another.

Code
#include <iostream>
#include <thread>
#include <future>

void producer(std::promise<int> p) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    p.set_value(50);
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t(producer, std::move(p));

    std::cout << "Waiting for value...\n";
    int value = f.get();

    std::cout << "Received: " << value << "\n";

    t.join();
}
/* 
Realistic Output
Waiting for value...
Received: 50

Clean Output
Waiting for value...
Received: 50
*/


✅ PROGRAM 7 — std::async with std::launch policies (C++11)
Demonstrates async, deferred, always async.

Code
#include <iostream>
#include <future>
#include <thread>

int compute() {
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    return 42;
}

int main() {
    auto f1 = std::async(std::launch::async, compute);
    auto f2 = std::async(std::launch::deferred, compute);

    std::cout << "f1 result = " << f1.get() << "\n";
    std::cout << "f2 result = " << f2.get() << "\n";

    return 0;
}
/* 
Realistic Output
f1 result = 42
f2 result = 42

Clean Output
f1 result = 42
f2 result = 42
*/



✅ PROGRAM 8 — std::shared_future (C++11)
Allows many threads to read the same future result.

Code
#include <iostream>
#include <future>
#include <thread>

int main() {
    std::promise<int> p;
    std::shared_future<int> sf = p.get_future().share();

    std::thread t1([sf]() { std::cout << "Thread 1 reads: " << sf.get() << "\n"; });
    std::thread t2([sf]() { std::cout << "Thread 2 reads: " << sf.get() << "\n"; });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    p.set_value(999);

    t1.join();
    t2.join();

    return 0;
}
/* 
Realistic Output

(Threads may print in any order)

Thread 1 reads: 999
Thread 2 reads: 999


OR

Thread 2 reads: 999
Thread 1 reads: 999

Clean Output
Thread 1 reads: 999
Thread 2 reads: 999
*/


✅ PROGRAM 9 — std::atomic<T> basics (C++11)
Lock-free counter.

Code
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 10000; i++) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; i++)
        threads.emplace_back(increment);

    for (auto &t : threads)
        t.join();

    std::cout << "Final counter = " << counter.load() << "\n";
}
/* 
Realistic Output

(May vary based on scheduling, but always correct)

Final counter = 100000

Clean Output
Final counter = 100000
*/




✅ PROGRAM 10 — std::atomic compare_exchange (C++11)
Demonstrates atomic CAS (Compare-And-Swap).

Code
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> value{0};

void try_update(int expected, int new_value) {
    if (value.compare_exchange_strong(expected, new_value)) {
        std::cout << "CAS SUCCESS: " << expected << " -> " << new_value << "\n";
    } else {
        std::cout << "CAS FAIL: expected " << expected 
                  << ", actual " << value.load() << "\n";
    }
}

int main() {
    std::thread t1(try_update, 0, 100);
    std::thread t2(try_update, 0, 200);

    t1.join();
    t2.join();

    std::cout << "Final value = " << value.load() << "\n";
}
/* 
Realistic Output

Thread order varies:

CAS SUCCESS: 0 -> 100
CAS FAIL: expected 0, actual 100
Final value = 100


OR

CAS SUCCESS: 0 -> 200
CAS FAIL: expected 0, actual 200
Final value = 200

Clean Output
CAS SUCCESS: 0 -> 100
CAS FAIL: expected 0, actual 100
Final value = 100
 */


✅ PROGRAM 11 — std::atomic_flag (spinlock) (C++11)
Code
#include <iostream>
#include <atomic>
#include <thread>

std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;

void lock() {
    while (lock_flag.test_and_set(std::memory_order_acquire));
}

void unlock() {
    lock_flag.clear(std::memory_order_release);
}

int counter = 0;

void increment() {
    for (int i = 0; i < 5000; i++) {
        lock();
        counter++;
        unlock();
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
Realistic Output
Counter = 10000

Clean Output
Counter = 10000
*/



✅ PROGRAM 12 — std::call_once (C++11)
Ensures a function runs only once across threads.

Code
#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag;

void init() {
    std::cout << "Initializing...\n";
}

void worker(int id) {
    std::call_once(flag, init);
    std::cout << "Worker " << id << " running\n";
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();
}
/* 
Realistic Output

Order varies, but “Initializing…” appears only once:

Initializing...
Worker 1 running
Worker 2 running
Worker 3 running


OR any interleaving, e.g.,

Worker 2 running
Initializing...
Worker 1 running
Worker 3 running

Clean Output
Initializing...
Worker 1 running
Worker 2 running
Worker 3 running
*/


✅ PROGRAM 13 — std::condition_variable_any (C++11)
Works with any lock type.

Code
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable_any cv;
bool ready = false;

void producer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::lock_guard<std::mutex> lg(m);
    ready = true;
    cv.notify_all();
}

void consumer(int id) {
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, []{ return ready; });
    std::cout << "Consumer " << id << " proceeding\n";
}

int main() {
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);
    std::thread p(producer);

    c1.join();
    c2.join();
    p.join();
}
/* 
Realistic Output

(Order of consumers varies)

Consumer 1 proceeding
Consumer 2 proceeding


OR

Consumer 2 proceeding
Consumer 1 proceeding

Clean Output
Consumer 1 proceeding
Consumer 2 proceeding
*/












✅ PROGRAM 14 — std::timed_mutex (C++11)

Allows timed locking attempts.

Code
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex tmutex;

void task(int id) {
    if (tmutex.try_lock_for(std::chrono::milliseconds(200))) {
        std::cout << "Thread " << id << " acquired lock\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        tmutex.unlock();
    } else {
        std::cout << "Thread " << id << " failed to acquire lock\n";
    }
}

int main() {
    std::thread t1(task, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::thread t2(task, 2);

    t1.join();
    t2.join();
}

Realistic Output

Thread 1 gets lock → Thread 2 times out:

Thread 1 acquired lock
Thread 2 failed to acquire lock

Clean Output
Thread 1 acquired lock
Thread 2 failed to acquire lock

✅ PROGRAM 15 — std::shared_mutex (C++14/C++17)

Multiple readers OR one writer.

Code
#include <iostream>
#include <shared_mutex>
#include <thread>

std::shared_mutex smutex;
int shared_data = 0;

void reader(int id) {
    smutex.lock_shared();
    std::cout << "Reader " << id << ": " << shared_data << "\n";
    smutex.unlock_shared();
}

void writer() {
    smutex.lock();
    shared_data++;
    std::cout << "Writer updated value to " << shared_data << "\n"; 
    smutex.unlock();
}

int main() {
    std::thread r1(reader, 1);
    std::thread r2(reader, 2);
    std::thread w(writer);

    r1.join();
    r2.join();
    w.join();
}

Realistic Output

Readers run first OR interleave, but writer updates once:

Reader 1: 0
Reader 2: 0
Writer updated value to 1

Clean Output
Reader 1: 0
Reader 2: 0
Writer updated value to 1

✅ PROGRAM 16 — std::scoped_lock (C++17)

Locks multiple mutexes safely (prevents deadlock).

Code
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1, m2;

void task(int id) {
    std::scoped_lock lock(m1, m2);
    std::cout << "Thread " << id << " acquired both locks\n";
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();
}

Realistic Output

Either thread may print first:

Thread 1 acquired both locks
Thread 2 acquired both locks

Clean Output
Thread 1 acquired both locks
Thread 2 acquired both locks

✅ PROGRAM 17 — std::barrier (C++20)

Threads wait until a phase completes.

Code
#include <iostream>
#include <barrier>
#include <thread>

std::barrier sync_point(3);

void worker(int id) {
    std::cout << "Thread " << id << " reached barrier\n";
    sync_point.arrive_and_wait();
    std::cout << "Thread " << id << " passed barrier\n";
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();
}

Realistic Output

Order varies until barrier; all pass together:

Thread 2 reached barrier
Thread 1 reached barrier
Thread 3 reached barrier
Thread 2 passed barrier
Thread 1 passed barrier
Thread 3 passed barrier

Clean Output
Thread 1 reached barrier
Thread 2 reached barrier
Thread 3 reached barrier
Thread 1 passed barrier
Thread 2 passed barrier
Thread 3 passed barrier

✅ PROGRAM 18 — std::latch (C++20)

One-time countdown synchronization.

Code
#include <iostream>
#include <latch>
#include <thread>

std::latch work_done(3);

void task(int id) {
    std::cout << "Worker " << id << " finished work\n";
    work_done.count_down();
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    work_done.wait();
    std::cout << "All workers finished. Proceeding...\n";

    t1.join();
    t2.join();
    t3.join();
}

Realistic Output

Order varies:

Worker 2 finished work
Worker 1 finished work
Worker 3 finished work
All workers finished. Proceeding...

Clean Output
Worker 1 finished work
Worker 2 finished work
Worker 3 finished work
All workers finished. Proceeding...
















19) std::jthread (C++20) — automatic join + cooperative cancellation
// file: jthread_example.cpp
// Compile: g++ -std=c++20 jthread_example.cpp -pthread
#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

void worker(std::stop_token st, int id) {
    int i = 0;
    while (!st.stop_requested() && i < 5) {
        std::cout << "worker " << id << " tick " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        ++i;
    }
    std::cout << "worker " << id << " exiting\n";
}

int main() {
    std::jthread t1(worker, 1);
    std::jthread t2(worker, 2);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    t2.request_stop(); // politely ask thread 2 to stop early

    // t1 and t2 destructors will join automatically
    return 0;
}


Realistic Output (timing/interleaving may vary)

worker 1 tick 0
worker 2 tick 0
worker 1 tick 1
worker 2 tick 1
worker 1 tick 2
worker 2 tick 2
worker 2 exiting
worker 1 tick 3
worker 1 tick 4
worker 1 exiting


Clean Deterministic Output

worker 1 tick 0
worker 2 tick 0
worker 1 tick 1
worker 2 tick 1
worker 1 tick 2
worker 2 tick 2
worker 2 exiting
worker 1 tick 3
worker 1 tick 4
worker 1 exiting

20) std::stop_source, std::stop_token, std::stop_callback (C++20) — cancellation + callbacks
// file: stop_callbacks_example.cpp
// Compile: g++ -std=c++20 stop_callbacks_example.cpp -pthread
#include <iostream>
#include <thread>
#include <stop_token>
#include <chrono>

void background(std::stop_token st) {
    std::stop_callback cb(st, [](){ std::cout << "stop_callback invoked in background thread\n"; });
    int i = 0;
    while (!st.stop_requested() && i < 10) {
        std::cout << "background tick " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
        ++i;
    }
    std::cout << "background exiting\n";
}

int main() {
    std::stop_source src;
    std::jthread t(background, src.get_token());

    std::this_thread::sleep_for(std::chrono::milliseconds(350));
    std::cout << "main requests stop\n";
    src.request_stop();

    // jthread joins on destruction
    return 0;
}


Realistic Output

background tick 0
background tick 1
background tick 2
main requests stop
stop_callback invoked in background thread
background exiting


Clean Deterministic Output

background tick 0
background tick 1
background tick 2
main requests stop
stop_callback invoked in background thread
background exiting

21) Minimal custom thread-pool with tasks + futures (safe, illustrative)
// file: thread_pool_example.cpp
// Compile: g++ -std=c++17 thread_pool_example.cpp -pthread
// (code uses only C++17 features so it compiles with -std=c++17)
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <functional>
#include <condition_variable>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t n) : stop_flag(false) {
        for (size_t i = 0; i < n; ++i) {
            workers.emplace_back([this, i](){
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lk(this->mtx);
                        this->cv.wait(lk, [this](){ return stop_flag || !tasks.empty(); });
                        if (stop_flag && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lk(mtx);
            stop_flag = true;
        }
        cv.notify_all();
        for (auto &w : workers) if (w.joinable()) w.join();
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using Ret = std::invoke_result_t<F, Args...>;
        auto task_ptr = std::make_shared<std::packaged_task<Ret()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<Ret> fut = task_ptr->get_future();
        {
            std::lock_guard<std::mutex> lk(mtx);
            tasks.emplace([task_ptr](){ (*task_ptr)(); });
        }
        cv.notify_one();
        return fut;
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop_flag;
};

int main() {
    ThreadPool pool(3);
    std::vector<std::future<int>> results;
    for (int i = 1; i <= 6; ++i) {
        results.emplace_back(pool.submit([i](){
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
            std::cout << "task " << i << " done\n";
            return i * i;
        }));
    }

    for (auto &f : results) {
        std::cout << "result: " << f.get() << "\n";
    }

    return 0;
}


Note: This is a simple educational pool — production pools should include task stealing, graceful resize, exception handling, etc.

Realistic Output (order of "task done" depends on scheduling and durations)

task 1 done
result: 1
task 2 done
result: 4
task 3 done
result: 9
task 4 done
result: 16
task 5 done
result: 25
task 6 done
result: 36


Clean Deterministic Output

task 1 done
task 2 done
task 3 done
task 4 done
task 5 done
task 6 done
result: 1
result: 4
result: 9
result: 16
result: 25
result: 36


(Depending on scheduling, result: lines may interleave with task X done lines; deterministic version shows all tasks then results for clarity.)

22) Parallel algorithms with execution policies (std::execution) (C++17)
// file: parallel_algorithms_example.cpp
// Compile: g++ -std=c++17 -O2 parallel_algorithms_example.cpp -pthread
// Note: parallel execution requires libstdc++/libc++ support for parallel policy.
#include <algorithm>
#include <execution>
#include <vector>
#include <iostream>
#include <numeric>

int main() {
    std::vector<int> v(100000);
    std::iota(v.begin(), v.end(), 1);

    long long sum = std::reduce(std::execution::par, v.begin(), v.end(), 0LL);
    std::cout << "sum = " << sum << "\n";

    std::sort(std::execution::par_unseq, v.begin(), v.end(), std::greater<int>());
    std::cout << "top 3: " << v[0] << ", " << v[1] << ", " << v[2] << "\n";
    return 0;
}


Realistic Output

sum = 5000050000
top 3: 100000, 99999, 99998


Clean Deterministic Output

sum = 5000050000
top 3: 100000, 99999, 99998

























