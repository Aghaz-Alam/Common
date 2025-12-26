C++ THREADING & MULTI-THREADING CHALLENGES
1️⃣ Thread not joined or detached
🔍 Theory
A std::thread must be joined or detached before destruction.
Otherwise → std::terminate().

❌ Code
#include <iostream>
#include <thread>
using namespace std;
void work() {
    cout << "Working\n";
}
int main() {
    thread t(work);
}
/* 
❌ Output
terminate called
*/



2️⃣ Proper join()
🔍 Theory
join() blocks until thread finishes.

#include <iostream>
#include <thread>
using namespace std;
void work() {
    cout << "Working\n";
}
int main() {
    thread t(work);
    t.join();
    cout << "Done\n";
}
/* 
✅ Output
Working
Done
*/



3️⃣ Detached thread lifetime issue
🔍 Theory
Detached thread may outlive objects it accesses → UB.

#include <iostream>
#include <thread>
using namespace std;
void work(int* p) {
    cout << *p << "\n";
}
int main() {
    int x = 10;
    thread t(work, &x);
    t.detach();
}
/* 
⚠️ Output
10   (OR garbage / crash)

⚠️ Undefined Behavior
*/



4️⃣ Data race (no synchronization)
🔍 Theory
Concurrent write → data race = UB

#include <iostream>
#include <thread>
using namespace std;
int x = 0;
void inc() {
    for (int i = 0; i < 100000; i++)
        x++;
}
int main() {
    thread t1(inc);
    thread t2(inc);
    t1.join();
    t2.join();
    cout << x << "\n";
}
/* 
⚠️ Output
<non-deterministic>
*/



5️⃣ Fix data race using mutex
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int x = 0;
mutex m;
void inc() {
    for (int i = 0; i < 100000; i++) {
        lock_guard<mutex> lg(m);
        x++;
    }
}
int main() {
    thread t1(inc);
    thread t2(inc);
    t1.join();
    t2.join();
    cout << x << "\n";
}
/* 
✅ Output
200000
*/



6️⃣ Deadlock (classic)
🔍 Theory
Opposite lock order → deadlock

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex m1, m2;
void f1() {
    lock_guard<mutex> l1(m1);
    lock_guard<mutex> l2(m2);
}
void f2() {
    lock_guard<mutex> l2(m2);
    lock_guard<mutex> l1(m1);
}
int main() {
    thread t1(f1);
    thread t2(f2);
    t1.join();
    t2.join();
}
/* 
❌ Output
Program hangs (deadlock)
*/



7️⃣ Deadlock-free using std::lock
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex m1, m2;
void safe() {
    lock(m1, m2);
    lock_guard<mutex> l1(m1, adopt_lock);
    lock_guard<mutex> l2(m2, adopt_lock);
    cout << "Safe\n";
}
int main() {
    thread t1(safe);
    thread t2(safe);
    t1.join();
    t2.join();
}
/* 
✅ Output
Safe
Safe
*/


8️⃣ Condition variable misuse (missed wakeup)
🔍 Theory
Notify before wait → lost signal.

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
    cv.wait(lk);
    cout << "Worker\n";
}
int main() {
    thread t(worker);
    cv.notify_one();
    t.join();
}
/* 
❌ Output
Program hangs
*/





9️⃣ Correct condition variable usage
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
    cv.wait(lk, []{ return ready; });
    cout << "Worker\n";
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
✅ Output
Worker
*/




🔟 std::atomic vs mutex
🔍 Theory
Atomic avoids locks for simple ops.

#include <iostream>
#include <thread>
#include <atomic>
using namespace std;
atomic<int> x{0};
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
✅ Output
200000
*/



1️⃣1️⃣ False sharing
🔍 Theory
Different variables on same cache line → performance drop.

#include <iostream>
#include <thread>
using namespace std;
struct Data {
    int a;
    int b;
};
Data d;
void f1() { for(int i=0;i<1e7;i++) d.a++; }
void f2() { for(int i=0;i<1e7;i++) d.b++; }
int main() {
    thread t1(f1), t2(f2);
    t1.join(); t2.join();
}
/* 
⚠️ Output
Slow execution (no visible output)
*/




1️⃣2️⃣ Thread argument lifetime bug
#include <iostream>
#include <thread>
using namespace std;
void f(const string& s) {
    cout << s << "\n";
}
int main() {
    thread t(f, string("Hello"));
    t.detach();
}
/* 
⚠️ Output
Hello (OR crash)

⚠️ Dangling reference risk.
*/




1️⃣3️⃣ Exception escaping thread
🔍 Theory
Exception escaping thread → std::terminate.

#include <iostream>
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
❌ Output
terminate called
*/



1️⃣4️⃣ Handling exceptions inside thread
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
✅ Output
Handled
*/




1️⃣5️⃣ std::async scheduling ambiguity
#include <iostream>
#include <future>
using namespace std;
int f() {
    cout << "Run\n";
    return 1;
}
int main() {
    auto fut = async(f);
    cout << fut.get() << "\n";
}
/* 
⚠️ Output
Run
1

⚠️ Execution may be deferred or async
*/



1️⃣6️⃣ Thread-safe initialization (C++11)
#include <iostream>
#include <thread>
using namespace std;
int& get() {
    static int x = []{ cout << "Init\n"; return 10; }();
    return x;
}
void f() { get(); }
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
✅ Output
Init
*/



1️⃣7️⃣ Race in double-checked locking (classic bug)
#include <iostream>
#include <thread>
using namespace std;
int* p = nullptr;
void init() {
    if (!p)
        p = new int(10);
}
int main() {
    thread t1(init), t2(init);
    t1.join(); t2.join();
}
/* 
❌ Result
UB (race)
*/


1️⃣8️⃣ Thread-local storage
#include <iostream>
#include <thread>
using namespace std;
thread_local int x = 0;
void f() {
    x++;
    cout << x << "\n";
}
int main() {
    thread t1(f), t2(f);
    t1.join(); t2.join();
}
/* 
✅ Output
1
1
*/



1️⃣9️⃣ Busy wait vs condition variable
#include <iostream>
#include <thread>
using namespace std;
bool ready = false;
void f() {
    while (!ready) {}
    cout << "Go\n";
}
int main() {
    thread t(f);
    ready = true;
    t.join();
}
/* 
❌ Problem
🔥 CPU burn, race condition
*/



2️⃣0️⃣ RAII lock vs manual lock (exception safe)
#include <iostream>
#include <mutex>
using namespace std;
mutex m;
void f() {
    lock_guard<mutex> lg(m);
    throw 1;
}
int main() {
    try {
        f();
    } catch (...) {
        cout << "Safe\n";
    }
}
/* 
✅ Output
Safe
*/