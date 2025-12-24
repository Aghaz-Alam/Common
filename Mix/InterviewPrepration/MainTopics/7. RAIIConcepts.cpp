RAII concept - 
name examples from std:: for RAII

/* ------------------------------------------ */
RAII means:
---> Constructor = Acquire resource
---> Destructor = Release resource
---> Cleanup guaranteed (even in exceptions)


✅ 1. Constructor = Acquire Resource
Concept:
-->  the object is created, it automatically acquires a resource (like opening a file or allocating memory).
--> Example: File opened in constructor
#include <iostream>
#include <fstream>
class Logger {
    std::ofstream file;
  public:
    Logger() {
        file.open("log.txt");   // Resource acquired
        std::cout << "File opened in constructor\n";
    }

    ~Logger() {
        std::cout << "Destructor called\n";
    }
};
int main() {
    Logger log; // Constructor automatically opens file
}

What this shows:
✔ Resource acquisition happens automatically when object is created.



✅ 2. Destructor = Release Resource
Concept:
--> When the object goes out of scope, its destructor automatically releases the resource.
--> Example: File closed in destructor
#include <iostream>
#include <fstream>
class Logger {
    std::ofstream file;
  public:
    Logger() {
        file.open("data.txt");
    }

    ~Logger() {
        file.close();           // Resource released
        std::cout << "File closed in destructor\n";
    }
};
int main() {
    {
        Logger log;   // File opened
    }                 // Destructor automatically closes file
}

What this shows:
✔ Resource cleanup happens automatically on scope exit.
✔ No need to manually call close() in user code.



✅ 3. Cleanup Guaranteed (Even in Exceptions)
Concept:
--> If an exception is thrown, destructors still run → resource is safely released.
--> Example: RAII object cleans up during exception
#include <iostream>
#include <fstream>
class FileHandler {
    std::ofstream file;
  public:
    FileHandler() {
        file.open("output.txt");
        std::cout << "File opened\n";
    }

    ~FileHandler() {
        file.close();
        std::cout << "File closed (even if exception happened)\n";
    }
};
int riskyFunction() {
    FileHandler fh;     // Resource acquired
    throw std::runtime_error("Something went wrong!");
}
int main() {
    try {
        riskyFunction();
    }
    catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}
What this shows:
✔ Destructor runs even when an exception occurs
✔ Resource is still released
✔ No leaks, no forgotten cleanup, no corrupted state


/* ------------------------------------------ */
WHY RAII IS IMPORTANT
RAII ensures:
✔ Automatic cleanup
---> No memory/resource leaks.

✔ Exception safety
---> Destructor runs even if an exception occurs.

✔ Scoped resource management
---> Resources last exactly as long as objects.

✔ No need for manual .close() or free()



✅ 1. Automatic Cleanup
      No memory/resource leaks

❌ Without RAII (leak possible)
#include <iostream>
void foo() {
    int* p = new int(10);   // allocated
    // forgot delete → memory leak
}
int main() { 
    foo(); 
}

✅ With RAII (no leak)
#include <iostream>
#include <memory>
void foo() {
    std::unique_ptr<int> p = std::make_unique<int>(10);  
    // automatically cleaned up when foo() ends
    std::cout << *p << "\n";
}
int main() {
    foo();
}  // memory freed here automatically

✔ unique_ptr deletes memory automatically
✔ No memory leak possible



✅ 2. Exception Safety
      Destructor runs even if an exception occurs
#include <iostream>
#include <fstream>
class File {
    std::ofstream f;
  public:
    File() {
        f.open("demo.txt");
        std::cout << "File opened\n";
    }
    ~File() {
        f.close();
        std::cout << "File closed (even after exception)\n";
    }
};
void risky() {
    File file;  // RAII object
    throw std::runtime_error("Error occurred!");
}
int main() {
    try {
        risky();
    }
    catch (const std::exception &e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
}

✔ File is closed even though an exception is thrown
✔ RAII makes cleanup exception-safe



✅ 3. Scoped Resource Management
      Resources last exactly as long as the object’s scope
#include <iostream>
#include <mutex>
#include <thread>
std::mutex m;
void task() {
    {
        std::lock_guard<std::mutex> lock(m);  
        std::cout << "Mutex locked inside scope\n";
    } // scope ends → mutex automatically unlocked

    std::cout << "Mutex automatically released\n";
}
int main() {
    std::thread t(task);
    t.join();
}

✔ Lock exists only within the block
✔ Automatically released when leaving scope
✔ Prevents deadlocks




✅ 4. No need for manual .close() or free()
RAII objects naturally clean themselves
#include <iostream>
#include <fstream>
void writeData() {
    std::ofstream file("data.txt");  // RAII acquisition
    file << "Hello RAII!\n";
    // No file.close() needed
}
int main() {
    writeData();
    std::cout << "Program ended without calling file.close()\n";
}

✔ file.close() not required
✔ Destructor closes file automatically

/* ------------------------------------------ */
std:: Examples:
---> Memory → unique_ptr, vector, string
---> File → fstream
---> Locks → lock_guard, scoped_lock
---> Threads → jthread
---> Buffers → stringstream

/* ------------------------------------------ */
We use RAII for:
---> Memory
---> Files
---> Mutexes
---> Threads
---> Network resources
---> Any resource needing deterministic cleanup



/* ------------------------------------------ */
COMMON SCENARIOS WHERE WE USE RAII
✔ Memory allocation
---> Prefer smart pointers to raw new/delete.

✔ File operations
---> std::ifstream, std::ofstream.

✔ Mutex locking
---> Use std::lock_guard.

✔ Thread lifecycle
---> Use std::jthread or RAII wrappers.

✔ Temporary resource acquisitions
---> State switching, formatting, env vars.

✔ Strong exception safety
---> When a function may throw.




✅ 1. Memory Allocation (Prefer smart pointers)
Using std::unique_ptr instead of raw new/delete
#include <iostream>
#include <memory>
int main() {
    std::unique_ptr<int> p = std::make_unique<int>(42); // acquire memory
    std::cout << "Value = " << *p << "\n";
} // memory freed automatically

✔ No delete needed
✔ No memory leaks
✔ Automatic cleanup


✅ 2. File Operations (std::ifstream / std::ofstream)
#include <iostream>
#include <fstream>
int main() {
    std::ofstream file("output.txt");  // file opened (RAII)

    if (file) {
        file << "Writing with RAII...\n";
    }

} // file automatically closed

✔ No need for file.close()
✔ File closed even if exceptions occur



✅ 3. Mutex Locking (std::lock_guard)
#include <iostream>
#include <mutex>
#include <thread>
std::mutex m;
void work() {
    std::lock_guard<std::mutex> lock(m); // mutex locked
    std::cout << "Thread safe operation\n";
} // mutex unlocked automatically
int main() {
    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();
}

✔ Prevents forgetting unlock()
✔ Exception-proof locking
✔ No deadlocks due to missing unlock



✅ 4. Thread Lifecycle (std::jthread)
Automatically joins when destroyed.
#include <iostream>
#include <thread>
int main() {
    std::jthread worker([]{
        std::cout << "Worker thread running...\n";
    });  
    // no need to call join()
} // worker.join() happens automatically

✔ Clean thread lifecycle
✔ No risk of forgetting join()



✅ 5. Temporary Resource Acquisition (State switching / formatting)
Example: temporary formatting using RAII
#include <iostream>
#include <iomanip>
class FormatGuard {
    std::ostream& os;
    std::ios_base::fmtflags oldFlags;
  public:
    FormatGuard(std::ostream& s) : os(s), oldFlags(s.flags()) { }
    ~FormatGuard() { os.flags(oldFlags); } // restore state
};
int main() {
    std::cout << "Normal: " << 255 << "\n";

    {
        FormatGuard guard(std::cout);  // save old state
        std::cout << std::hex << 255 << "\n"; // hex format
    } // state automatically restored

    std::cout << "Back to decimal: " << 255 << "\n";
}

✔ Temporarily modifies stream state
✔ Automatically restores it



✅ 6. Strong Exception Safety (RAII ensures cleanup even when throwing)
#include <iostream>
#include <fstream>
class File {
    std::ofstream f;
  public:
    File() {
        f.open("exception_test.txt");
        std::cout << "File opened\n";
    }
    ~File() {
        f.close();
        std::cout << "File closed safely\n";
    }
};
void risky() {
    File file;     // RAII resource
    throw std::runtime_error("Oops! Something went wrong.");
}
int main() {
    try {
        risky();
    }
    catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
}

✔ Destructor runs during unwinding
✔ File always closes
✔ No resource leaks

/* ------------------------------------------ */
Types of RAII Objects
These are not official “types,” but common categories:


1. Memory Management RAII
Examples:
std::unique_ptr
std::shared_ptr
std::vector
std::string

Example using smart pointers
void foo() {
    std::unique_ptr<int> p = std::make_unique<int>(10); // memory acquired
} // memory automatically deleted



2. Resource Handle RAII
For OS/system resources.
Examples:
std::fstream (file handle)
std::thread / std::jthread
Network sockets (custom RAII)
Database connections (custom RAII)
std::fstream f("log.txt", std::ios::out);

Destructor → calls close().



3. Lock & Concurrency RAII
Examples:
std::lock_guard<std::mutex>
std::unique_lock<std::mutex>
std::scoped_lock

Example
std::mutex m;
void safe() {
    std::lock_guard<std::mutex> lock(m); // lock acquired
    // critical section
} // lock automatically released

No deadlock due to missing unlock.



4. Temporary State Management RAII
Examples:
std::ios_base::fmtflags modifications
std::locale settings
std::basic_stringbuf
These automatically restore state.



5. Thread Management RAII
C++20 introduces:
std::jthread
Automatically joins thread in destructor.
void run() {
    std::jthread worker([]{ 
        // work
    });  // auto-joined
}


/* ------------------------------------------ */

Classic Examples of RAII in std:: Library
| Resource Type      | std:: Example                                       | What it Manages               |
| ------------------ | --------------------------------------------------- | ----------------------------- |
| Memory             | `std::unique_ptr`, `std::shared_ptr`, `std::vector` | Heap memory                   |
| File handles       | `std::fstream`                                      | Open/close file               |
| Mutex locks        | `std::lock_guard`, `std::unique_lock`               | Acquire/release mutex         |
| Threads            | `std::jthread`                                      | Auto join on destruction      |
| I/O Stream Buffers | `std::ostringstream`, etc.                          | Manage buffers                |
| Smart pointers     | All smart pointers                                  | Reference counting / deletion |
| Dynamic arrays     | `std::array`, `std::string`                         | Internal memory buffer        |


✅ 1. Memory RAII
Examples used:
--> std::unique_ptr
--> std::shared_ptr
--> std::vector

#include <iostream>
#include <memory>
#include <vector>
int main() {
    // unique_ptr → owns memory exclusively
    std::unique_ptr<int> up = std::make_unique<int>(10);
    std::cout << "unique_ptr value = " << *up << "\n";

    // shared_ptr → reference counted memory
    std::shared_ptr<int> sp1 = std::make_shared<int>(20);
    std::shared_ptr<int> sp2 = sp1;
    std::cout << "shared_ptr count = " << sp1.use_count() << "\n";

    // vector → RAII-managed dynamic array
    std::vector<int> vec = {1, 2, 3, 4};
    vec.push_back(5);

    std::cout << "vector size = " << vec.size() << "\n";
}

Cleanup:
✔ memory freed automatically
✔ no delete required



✅ 2. File Handles RAII
Example used:
--> std::fstream

#include <fstream>
#include <iostream>
int main() {
    std::fstream file("demo.txt", std::ios::out);
    if (file) {
        file << "Hello RAII file handling!";
    }
}  // file automatically closed here

Cleanup:
✔ file handle closed in destructor




✅ 3. Mutex Locks RAII
Examples used:
std::lock_guard
std::unique_lock

#include <iostream>
#include <mutex>
#include <thread>
std::mutex m;
void useLockGuard() {
    std::lock_guard<std::mutex> lock(m);
    std::cout << "Inside lock_guard block\n";
}
void useUniqueLock() {
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Inside unique_lock block\n";
    // lock can be manually unlocked if needed
    lock.unlock();
}
int main() {
    std::thread t1(useLockGuard);
    std::thread t2(useUniqueLock);

    t1.join();
    t2.join();
}

Cleanup:
✔ mutex released automatically



✅ 4. Thread RAII
Example used:
std::jthread (C++20)

#include <iostream>
#include <thread>
int main() {
    std::jthread worker([]{
        std::cout << "Worker thread running...\n";
    });
    // jthread auto-joins in destructor
}

Cleanup:
✔ thread automatically joined on destruction


✅ 5. I/O Stream Buffers RAII
Example used:
std::ostringstream

#include <iostream>
#include <sstream>
int main() {
    std::ostringstream oss;
    oss << "Value = " << 42;

    std::cout << oss.str() << "\n";
}

Cleanup:
✔ string buffer memory handled automatically



✅ 6. Smart Pointers RAII
Examples used:
All smart pointers
--> std::unique_ptr
--> std::shared_ptr
--> std::weak_ptr

Complete Example:
#include <iostream>
#include <memory>
int main() {
    // unique_ptr
    std::unique_ptr<int> up = std::make_unique<int>(100);

    // shared_ptr and weak_ptr
    std::shared_ptr<int> sp = std::make_shared<int>(200);
    std::weak_ptr<int> wp = sp;

    std::cout << "unique_ptr = " << *up << "\n";
    std::cout << "shared_ptr = " << *sp << "\n";

    if (auto locked = wp.lock()) {
        std::cout << "weak_ptr locked value = " << *locked << "\n";
    }
}

Cleanup:
✔ unique_ptr deletes
✔ shared_ptr decrements ref count
✔ weak_ptr observes only



✅ 7. Dynamic Arrays RAII
Examples used:
--> std::array
--> std::string

#include <iostream>
#include <array>
#include <string>
int main() {
    // array → fixed size, stack-allocated RAII wrapper
    std::array<int, 4> arr = {10, 20, 30, 40};
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    // string → dynamic internal buffer with RAII
    std::string name = "RAII Example";
    name += " in C++";
    std::cout << name << "\n";
}

Cleanup:
✔ no need for free()
✔ automatic buffer lifetime management
/* ------------------------------------------ */

HOW RAII Works — Simple Example
❌ Without RAII (C-like approach)
FILE* file = fopen("data.txt", "r");
if (!file) return;
... // use file
fclose(file); // must remember to close

If an exception occurs → resource leak.



✅ With RAII (C++ style)
#include <fstream>
void readFile() {
    std::ifstream file("data.txt"); // file opened here

    std::string line;
    std::getline(file, line);

} // file automatically closed here

No matter what happens—return, break, exception—the file is closed.

/* ---------------------------------------- */
1. What RAII Guarantees in an Object with vptr/vtable
---> A RAII object can acquire resources in its constructor and release them in its destructor.

But with virtual functions and vptr, the rules are:
During base class constructor
---> vptr points to Base::vtable
---> Virtual dispatch acts as if object is a Base

uring derived class constructor
---> First Base is constructed
---> Then Derived constructor runs
---> vptr is updated to Derived::vtable

During destruction
---> Order reverses
---> First vptr is set to Derived::vtable
---> As soon as Derived destructor begins, vptr switches to Base::vtable
---> Base destructor runs last

Therefore:
❗ Virtual dispatch NEVER calls derived functions during base construction
❗ Virtual dispatch NEVER calls derived functions during derived destruction
This protects partially constructed objects.




2. Timeline Diagram — Construction Sequence
For a class hierarchy:

class Base {
  public:
    Base()  { /* vptr -> Base::vtable */ }
    virtual ~Base() {}
    virtual void foo() {}
};

class Derived: public Base {  
  public:
    Derived() { /* vptr -> Derived::vtable */ }
    ~Derived() {}
    void foo() override {}
};

Construction timeline
[Memory allocated]
Base::Base()
    vptr = &Base::vtable
    call Base initialization

Derived::Derived()
    vptr = &Derived::vtable
    call Derived initialization

Object ready


3. Timeline Diagram — Destruction Sequence
Derived::~Derived()
    vptr = &Base::vtable     <--- Immediately switches!
    release Derived resources

Base::~Base()
    call base cleanup
    vptr destroyed

So once the Derived destructor starts, the object is already treated as Base.



4. RAII + Virtual Dispatch Example
Example of a dangerous pattern:
class Base {
  public:
    Base() {
        foo();  // ❌ virtual call in constructor
    }
    virtual ~Base() {
        foo();  // ❌ virtual call in destructor
    }

    virtual void foo() {
        std::cout << "Base::foo\n";
    }
};

class Derived: public Base {
  public:
    Derived() {
        // Acquire RAII resources
    }
    ~Derived() {
        // Release RAII resources
    }

    void foo() override {
        std::cout << "Derived::foo\n";
    }
};

Output:
Base::foo  (constructor phase)
Base::foo  (destructor phase)


Why?
---> During Base constructor → vptr = Base::vtable → Base::foo
---> During Derived destructor → vptr already reverted to Base::vtable → Base::foo

5. How RAII Behaves in This Scenario
---> RAII follows these rules:

✔ Resources are acquired when the constructor finishes
This means:
---> When Base() is running, Derived resources are not yet acquired
---> When Derived() starts, Base resources already acquired

✔ Resources are released as soon as destructors begin executing
---> Derived RAII resources are released first
---> Then Base RAII resources




6. RAII Example Using vptr Lifetime
Let’s see how this works with real resource management.

class Base {
  protected:
    std::ofstream file;   // RAII resource
  public:
    Base() : file("log.txt")   // acquire
    {
        // vptr = Base::vtable
    }

    virtual ~Base() {
        // vptr = Base::vtable (still)
        // file closed automatically here (RAII)
    }
};

class Derived: public Base {
    std::unique_ptr<int> mem;  // RAII resource
  public:
    Derived() : mem(std::make_unique<int>(5))
    {
        // vptr = Derived::vtable
    }

    ~Derived() {
        // vptr reset to Base::vtable
        // mem released here
    }
};

Resource release order:
Derived::~Derived()
    release mem
    vptr -> Base::vtable
Base::~Base()
    release file




7. Important Rules for RAII with Inheritance
Rule 1: Never call virtual functions in constructors/destructors
Reason:
---> Object is only partially formed
---> vptr points to base vtable


Rule 2: RAII resources that depend on Derived must not be used in Base constructor
---> Derived has not yet acquired them.

Rule 3: Prefer composition over inheritance for RAII
RAII often works best when resource-owning classes have:
---> No inheritance
---> No virtual destructors
---> No vptr complications

Rule 4: Always make destructors virtual when using inheritance
Otherwise:
---> Base* b = new Derived();
---> delete b; // undefined behavior if no virtual destructor




8. Memory Layout Visualization
For a derived object:

-------------------------
| vptr -> Derived::vtbl |
-------------------------
| Base subobject         |
-------------------------
| Derived members        |
-------------------------


During construction:
Base phase:
    vptr -> Base::vtable

Derived phase:
    vptr -> Derived::vtable


During destruction:
Derived::~Derived():
    vptr -> Base::vtable

Base::~Base():
    vptr destroyed



9. How RAII + vptr Guarantees Safety
RAII ensures:
---> Even if an exception occurs in Derived constructor → Base destructor still runs → resource released safely

Destruction order matches construction order in reverse
vptr ensures:
---> Virtual dispatch aligns with initialized state
---> No call to unintended Derived portions during incomplete state





10. Summary Table
| Stage                     | vptr points to | RAII State             | Notes                    |
| ------------------------- | -------------- | ---------------------- | ------------------------ |
| Base constructor          | Base vtable    | Derived RAII not ready | No Derived virtual calls |
| Derived constructor       | Derived vtable | All RAII ready         | Safe state               |
| Derived destructor starts | Base vtable    | Derived RAII released  | Virtual calls go to Base |
| Base destructor           | (same)         | Base RAII released     | Last cleanup             |


--> During the Base constructor, the object’s vptr points to the Base vtable, and the Derived part is not yet initialized, 
    so no Derived virtual functions can be called at this stage.
--> Once the Derived constructor begins, the vptr is updated to point to the Derived vtable, and 
    all RAII resources for both Base and Derived are fully initialized, making this the first safe state where the complete object exists.
--> When the Derived destructor starts executing, the vptr is immediately switched back to the Base vtable, 
    and the Derived RAII resources are released, meaning any virtual calls made during this phase will dispatch to Base versions, 
    not Derived.
--> Finally, during the Base destructor, the vptr remains pointing to the Base vtable, and the Base-level RAII resources are released, 
    performing the last stage of cleanup in the object’s lifetime.