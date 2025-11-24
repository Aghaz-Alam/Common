✅ What is std::packaged_task?
std::packaged_task wraps any function or callable object so that its result can be retrieved asynchronously via a future (std::future).

It connects a function → to a future result.
✔ You give it a function
✔ It returns a std::future
✔ When the function executes, the result becomes available through the future

✅ Simple Example
#include <iostream>
#include <future>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int main() {
    packaged_task<int(int,int)> task(add);
    future<int> f = task.get_future();
    task(10, 20);  // execute the function
    cout << "Result = " << f.get() << endl;
}
Output:
Result = 30

✅ Example with Thread
#include <iostream>
#include <future>
#include <thread>
using namespace std;
int slowTask(int x) {
    this_thread::sleep_for(1s);
    return x * 2;
}
int main() {
    packaged_task<int(int)> task(slowTask);
    future<int> f = task.get_future();
    thread t(move(task), 10);  // execute task asynchronously
    t.join();
    cout << "Result = " << f.get() << endl;
}

🎯 When to Use std::packaged_task?
Use it when:
✔ You want to run a function asynchronously
✔ You want to retrieve the result using std::future
✔ You want to send a function/task into a thread pool or worker thread

🔎 Why not just use std::async?
std::async directly runs and gives a future.
std::packaged_task is used when:
You need manual control of when the function runs
You want to store tasks in a queue
You want to build thread pools

👍 Real Use Case: Thread Pool
queue<packaged_task<void()>> tasks;
mutex m;
void worker() {
    while(true) {
        packaged_task<void()> task;
        {
            lock_guard<mutex> lock(m);
            if(tasks.empty()) break;
            task = move(tasks.front());
            tasks.pop();
        }
        task();
    }
}


This is how real thread pools are built.


This demonstrates:

submitting tasks to a queue

worker threads picking tasks

returning results via future

graceful shutdown

✅ Complete Example Using std::packaged_task
#include <iostream>
#include <queue>
#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

using namespace std;

queue<packaged_task<void()>> tasks;
mutex m;
condition_variable cv;
bool stop = false;    // used to shut down workers

// -----------------------------------------------------
// Worker Thread Function
// -----------------------------------------------------
void worker() {
    while (true) {
        packaged_task<void()> task;

        {
            unique_lock<mutex> lock(m);

            // Wait until there is a task or shutdown signal
            cv.wait(lock, [] { return !tasks.empty() || stop; });

            if (stop && tasks.empty())
                return;     // shutdown gracefully

            task = move(tasks.front());
            tasks.pop();
        }

        task(); // execute the task outside the lock
    }
}

// -----------------------------------------------------
// Helper: Submit any callable with any return type
// -----------------------------------------------------
template <typename Func, typename... Args>
auto submit(Func&& f, Args&&... args)
{
    using ReturnType = invoke_result_t<Func, Args...>;

    // Create packaged_task that takes no args (bind arguments)
    packaged_task<ReturnType()> task(
        bind(forward<Func>(f), forward<Args>(args)...)
    );

    future<ReturnType> fut = task.get_future();

    {
        lock_guard<mutex> lock(m);
        tasks.emplace(move(task));
    }
    cv.notify_one();

    return fut;
}

// -----------------------------------------------------
// Main: Example Usage
// -----------------------------------------------------
int main() {
    // Start workers
    vector<thread> workers;
    for (int i = 0; i < 3; i++)
        workers.emplace_back(worker);

    // Submit tasks and get futures
    auto f1 = submit([] { 
        cout << "Task 1 running\n"; 
        return 10; 
    });

    auto f2 = submit([](int x) { 
        cout << "Task 2 running\n"; 
        return x * 2; 
    }, 15);

    auto f3 = submit([] { 
        cout << "Task 3 running\n"; 
        return string("Hello from thread"); 
    });

    // Get results
    cout << "Result 1 = " << f1.get() << endl;
    cout << "Result 2 = " << f2.get() << endl;
    cout << "Result 3 = " << f3.get() << endl;

    // Stop workers
    {
        lock_guard<mutex> lock(m);
        stop = true;
    }

    cv.notify_all();

    for (auto& w : workers)
        w.join();

    cout << "All workers stopped.\n";
    return 0;
}

✅ Output (example)
Task 1 running
Task 2 running
Task 3 running
Result 1 = 10
Result 2 = 30
Result 3 = Hello from thread
All workers stopped.

⭐ Explanation of Key Parts
1. submit() function

Accepts any callable → wraps it into packaged_task → pushes to queue → returns future.

2. Worker threads

Wait on the condition_variable until there is a task.

3. task()

Executes the stored function.

4. Returning results

Each task has a future returned from packaged_task.