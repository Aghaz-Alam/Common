✅ Threading & Concurrency in C++11 → C++20

C++ threading began heavily in C++11, expanded in C++14, improved in C++17, and got modern cancellation in C++20.

============================
⭐ C++11 THREADING FEATURES
============================
1️⃣ std::thread

Creates and manages a thread.

Example:
#include <iostream>
#include <thread>

void task() {
    std::cout << "Running in thread\n";
}

int main() {
    std::thread t(task);
    t.join();
}

2️⃣ std::mutex / std::lock_guard

Protect shared data.

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
int counter = 0;

void work() {
    std::lock_guard<std::mutex> lock(m);
    ++counter;
}

int main() {
    std::thread t1(work), t2(work);
    t1.join();
    t2.join();
    std::cout << counter << "\n";
}

3️⃣ std::unique_lock (flexible lock)
#include <mutex>
#include <thread>
#include <iostream>

std::mutex m;

void func() {
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Locked with unique_lock\n";
}
int main() {
    std::thread t(func);
    t.join();
}

4️⃣ std::condition_variable

Thread waiting + notifying.

#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

std::mutex m;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return ready; });
    std::cout << "Worker running...\n";
}

int main() {
    std::thread t(worker);

    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
    }
    cv.notify_one();
    t.join();
}

5️⃣ std::future / std::promise

Thread return value.

#include <future>
#include <iostream>

int compute() { return 42; }

int main() {
    std::future<int> f = std::async(std::launch::async, compute);
    std::cout << f.get();
}

6️⃣ std::async

Asynchronous task wrapper.

7️⃣ std::atomic

Lock-free types.

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> x{0};

void inc() { x++; }

int main() {
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
    std::cout << x << "\n";
}

8️⃣ std::call_once & std::once_flag

Run something once across threads.

#include <mutex>
#include <thread>
#include <iostream>

std::once_flag flag;

void init() {
    std::call_once(flag, []{ std::cout << "Initialized once\n"; });
}

int main() {
    std::thread t1(init), t2(init);
    t1.join(); t2.join();
}

============================
⭐ C++14 THREADING FEATURES
============================
✔ std::shared_timed_mutex

(precursor to shared_mutex)

#include <shared_mutex>
#include <thread>
#include <iostream>

std::shared_timed_mutex m;

void reader() {
    std::shared_lock lock(m);
    std::cout << "Reading...\n";
}

void writer() {
    std::unique_lock lock(m);
    std::cout << "Writing...\n";
}

int main() {
    std::thread t1(reader), t2(writer);
    t1.join(); t2.join();
}

============================
⭐ C++17 THREADING FEATURES
============================
1️⃣ std::shared_mutex

Multiple readers, single writer.

#include <shared_mutex>
#include <iostream>
#include <thread>

std::shared_mutex m;
int data = 0;

void reader() {
    std::shared_lock lock(m);
    std::cout << "read: " << data << "\n";
}

void writer() {
    std::unique_lock lock(m);
    data++;
}

int main() {
    std::thread t1(writer);
    std::thread t2(reader);
    t1.join();
    t2.join();
}

2️⃣ std::scoped_lock (Deadlock-free locking)
#include <mutex>
#include <thread>
#include <iostream>

std::mutex m1, m2;

void task() {
    std::scoped_lock lock(m1, m2);
    std::cout << "Both locked safely\n";
}

int main() {
    std::thread t(task);
    t.join();
}

3️⃣ Parallel Algorithms (<execution>)

std::execution::par uses multi-threading.

#include <execution>
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {5,4,3,2,1};
    std::sort(std::execution::par, v.begin(), v.end());

    for (int x : v) std::cout << x << " ";
}

============================
⭐ C++20 THREADING FEATURES
============================
1️⃣ std::jthread

Automatically joins

Supports stop_token cancellation

#include <iostream>
#include <thread>
#include <chrono>

void run(std::stop_token st) {
    while (!st.stop_requested()) {
        std::cout << "Working...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << "Cancelled!\n";
}

int main() {
    std::jthread jt(run);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    jt.request_stop();
}

2️⃣ std::stop_source / stop_token

Modern cooperative cancellation.

#include <thread>
#include <stop_token>
#include <iostream>

void work(std::stop_token st) {
    while (!st.stop_requested()) {
        std::cout << "Running...\n";
    }
}

int main() {
    std::stop_source ss;
    std::jthread t(work, ss.get_token());
    ss.request_stop();
}

3️⃣ std::latch

One-time countdown → synchronize threads.

#include <latch>
#include <thread>
#include <iostream>

std::latch done(3);

void worker(int id) {
    std::cout << "Worker " << id << " done\n";
    done.count_down();
}

int main() {
    std::thread t1(worker,1), t2(worker,2), t3(worker,3);
    done.wait();
    std::cout << "All workers finished!\n";

    t1.join(); t2.join(); t3.join();
}

4️⃣ std::barrier

Reusable barrier.

#include <barrier>
#include <thread>
#include <iostream>

std::barrier sync_point(3);

void task(int id) {
    std::cout << "Before barrier " << id << "\n";
    sync_point.arrive_and_wait();
    std::cout << "After barrier " << id << "\n";
}

int main() {
    std::thread t1(task,1), t2(task,2), t3(task,3);
    t1.join(); t2.join(); t3.join();
}

5️⃣ std::atomic_ref

Atomic operations on existing objects.

#include <atomic>
#include <iostream>

int main() {
    int x = 0;
    std::atomic_ref<int> ax(x);
    ax++;

    std::cout << x;
}

6️⃣ Semaphores

std::counting_semaphore, std::binary_semaphore

#include <semaphore>
#include <thread>
#include <iostream>

std::counting_semaphore<3> sem(3);

void work(int id) {
    sem.acquire();
    std::cout << "Working: " << id << "\n";
    sem.release();
}

int main() {
    std::thread t1(work,1), t2(work,2), t3(work,3), t4(work,4);
    t1.join(); t2.join(); t3.join(); t4.join();
}






1) std::thread (C++11)
// file: thread_example.cpp
// Compile: g++ -std=c++11 thread_example.cpp -pthread
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

2) std::mutex + std::lock_guard (C++11)
// file: mutex_lock_guard.cpp
// Compile: g++ -std=c++11 mutex_lock_guard.cpp -pthread
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
        // lock_guard unlocks on scope exit
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) threads.emplace_back(inc, 1000);
    for (auto &t : threads) t.join();
    std::cout << "counter = " << counter << "\n";
    return 0;
}

3) std::unique_lock (C++11) — flexible locking, can unlock/relock
// file: unique_lock_example.cpp
// Compile: g++ -std=c++11 unique_lock_example.cpp -pthread
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m;
int shared_data = 0;

void reader() {
    std::unique_lock<std::mutex> lk(m);
    std::cout << "Reader sees: " << shared_data << "\n";
    lk.unlock(); // explicit unlock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // can relock if needed
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

4) std::condition_variable (C++11)
// file: condvar_example.cpp
// Compile: g++ -std=c++11 condvar_example.cpp -pthread
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex m;
std::condition_variable cv;
std::queue<int> q;
bool finished = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            std::lock_guard<std::mutex> lg(m);
            q.push(i);
            std::cout << "Produced " << i << "\n";
        }
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    {
        std::lock_guard<std::mutex> lg(m);
        finished = true;
    }
    cv.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return !q.empty() || finished; });
        while (!q.empty()) {
            int v = q.front(); q.pop();
            std::cout << "Consumed " << v << "\n";
        }
        if (finished) break;
    }
    std::cout << "Consumer finished\n";
}

int main() {
    std::thread p(producer);
    std::thread c(consumer);
    p.join(); c.join();
    return 0;
}

5) std::future / std::promise and std::async (C++11)
// file: future_promise_async.cpp
// Compile: g++ -std=c++11 future_promise_async.cpp -pthread
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int compute(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return x * x;
}

int main() {
    // async returning a future
    std::future<int> fut = std::async(std::launch::async, compute, 7);
    std::cout << "Doing other work...\n";
    int result = fut.get(); // wait and obtain value
    std::cout << "Result from async: " << result << "\n";

    // promise -> future
    std::promise<std::string> prom;
    std::future<std::string> fstr = prom.get_future();

    std::thread producer([p = std::move(prom)]() mutable {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        p.set_value("Hello from promise");
    });

    std::cout << "Promise future says: " << fstr.get() << "\n";
    producer.join();
    return 0;
}

6) std::atomic (C++11) — lock-free counters
// file: atomic_example.cpp
// Compile: g++ -std=c++11 atomic_example.cpp -pthread
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::atomic<int> at_count{0};

void inc(int n) {
    for (int i = 0; i < n; ++i) ++at_count;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 8; ++i) threads.emplace_back(inc, 100000);
    for (auto &t : threads) t.join();
    std::cout << "Atomic counter = " << at_count.load() << "\n";
    return 0;
}

7) std::call_once & std::once_flag (C++11)
// file: call_once_example.cpp
// Compile: g++ -std=c++11 call_once_example.cpp -pthread
#include <iostream>
#include <thread>
#include <mutex>

std::once_flag init_flag;

void initialize() {
    std::call_once(init_flag, []() {
        std::cout << "One-time initialization running by thread " << std::this_thread::get_id() << "\n";
    });
}

int main() {
    std::thread t1(initialize), t2(initialize), t3(initialize);
    t1.join(); t2.join(); t3.join();
    return 0;
}

8) std::shared_timed_mutex / std::shared_mutex + std::shared_lock (C++14/C++17)
// file: shared_mutex_example.cpp
// Compile: g++ -std=c++17 shared_mutex_example.cpp -pthread
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex sm;
int data = 0;

void reader(int id) {
    std::shared_lock<std::shared_mutex> lock(sm);
    std::cout << "Reader " << id << " sees " << data << "\n";
}

void writer(int id) {
    std::unique_lock<std::shared_mutex> lock(sm);
    ++data;
    std::cout << "Writer " << id << " wrote " << data << "\n";
}

int main() {
    std::vector<std::thread> threads;
    threads.emplace_back(writer, 1);
    for (int i = 0; i < 3; ++i) threads.emplace_back(reader, i+1);
    for (auto &t : threads) t.join();
    return 0;
}

9) std::scoped_lock (C++17) — deadlock-free locking of multiple mutexes
// file: scoped_lock_example.cpp
// Compile: g++ -std=c++17 scoped_lock_example.cpp -pthread
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1, m2;
int x = 0, y = 0;

void task() {
    std::scoped_lock lock(m1, m2);
    ++x; ++y;
    std::cout << "Task updated x,y to " << x << "," << y << "\n";
}

int main() {
    std::thread t1(task), t2(task);
    t1.join(); t2.join();
    return 0;
}

10) Parallel algorithms with execution policies (C++17)
// file: parallel_sort_example.cpp
// Compile: g++ -std=c++17 -O2 parallel_sort_example.cpp -pthread
// Note: parallel execution requires a standard library implementation (libstdc++/libc++) that supports it.
#include <algorithm>
#include <execution>
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::vector<int> v(1'000'000);
    std::mt19937 rng(123);
    std::generate(v.begin(), v.end(), rng);

    std::sort(std::execution::par_unseq, v.begin(), v.end());
    std::cout << "Sorted first 5: " << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ", " << v[4] << "\n";
    return 0;
}


Note: availability/performance of parallel policies depends on library and platform.

11) std::jthread + cooperative cancellation via stop_token (C++20)
// file: jthread_stop_example.cpp
// Compile: g++ -std=c++20 jthread_stop_example.cpp -pthread
#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>

void worker(std::stop_token st) {
    while (!st.stop_requested()) {
        std::cout << "Working...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "Worker received stop request\n";
}

int main() {
    std::jthread jt(worker); // jt.get_stop_token() automatically passed if worker expects stop_token
    std::this_thread::sleep_for(std::chrono::seconds(1));
    jt.request_stop(); // politely ask worker to stop
    // jthread destructor joins automatically
    return 0;
}

12) std::stop_source & std::stop_token (C++20) — external cancellation
// file: stop_source_example.cpp
// Compile: g++ -std=c++20 stop_source_example.cpp -pthread
#include <iostream>
#include <thread>
#include <stop_token>
#include <chrono>

void background(std::stop_token st) {
    while (!st.stop_requested()) {
        std::cout << "Background task tick\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << "Background task stopping\n";
}

int main() {
    std::stop_source src;
    std::jthread jt(background, src.get_token());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    src.request_stop(); // signal stop to the background thread
    // jt will stop and join automatically
    return 0;
}

13) std::latch (C++20) — a one-shot countdown
// file: latch_example.cpp
// Compile: g++ -std=c++20 latch_example.cpp -pthread
#include <iostream>
#include <latch>
#include <thread>
#include <vector>

int main() {
    const int N = 3;
    std::latch done(N);
    std::vector<std::thread> workers;
    for (int i = 0; i < N; ++i) {
        workers.emplace_back([i, &done]() {
            std::cout << "Worker " << i << " starting work\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i+1)));
            std::cout << "Worker " << i << " done\n";
            done.count_down();
        });
    }

    done.wait(); // wait until the latch reaches zero
    std::cout << "All workers finished\n";
    for (auto &t : workers) t.join();
    return 0;
}

14) std::barrier (C++20) — reusable synchronization point
// file: barrier_example.cpp
// Compile: g++ -std=c++20 barrier_example.cpp -pthread
#include <iostream>
#include <barrier>
#include <thread>
#include <vector>

int main() {
    const int N = 3;
    std::barrier sync(N, [](){ std::cout << "Barrier callback: phase completed\n"; });

    std::vector<std::thread> threads;
    for (int i = 0; i < N; ++i) {
        threads.emplace_back([i, &sync](){
            std::cout << "Thread " << i << " before barrier\n";
            sync.arrive_and_wait();
            std::cout << "Thread " << i << " after barrier (phase 1)\n";
            // second phase
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i+1)));
            sync.arrive_and_wait();
            std::cout << "Thread " << i << " after barrier (phase 2)\n";
        });
    }

    for (auto &t : threads) t.join();
    return 0;
}

15) std::atomic_ref (C++20) — atomic operations on existing object
// file: atomic_ref_example.cpp
// Compile: g++ -std=c++20 atomic_ref_example.cpp -pthread
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

int main() {
    int value = 0;
    std::atomic_ref<int> aref(value);

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&aref](){
            for (int j = 0; j < 10000; ++j) ++aref;
        });
    }
    for (auto &t : threads) t.join();

    std::cout << "value (via atomic_ref) = " << value << "\n";
    return 0;
}

16) Semaphores: std::counting_semaphore & std::binary_semaphore (C++20)
// file: semaphore_example.cpp
// Compile: g++ -std=c++20 semaphore_example.cpp -pthread
#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::counting_semaphore<3> pool(3); // allow up to 3 concurrent users

void user(int id) {
    pool.acquire();
    std::cout << "User " << id << " entered critical section\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "User " << id << " leaving\n";
    pool.release();
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 8; ++i) threads.emplace_back(user, i);
    for (auto &t : threads) t.join();
    return 0;
}
