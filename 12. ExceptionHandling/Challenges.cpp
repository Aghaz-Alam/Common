🔹 Challenge 1: Catch order (Base vs Derived)
❓ What happens if base is caught first?
#include <iostream>
using namespace std;

class Base {};
class Derived : public Base {};

int main() {
    try {
        throw Derived();
    }
    catch (Base&) {
        cout << "Base caught\n";
    }
    catch (Derived&) {
        cout << "Derived caught\n";
    }
}
/* 
✅ Output
Base caught

💡 Rule
Catch order matters — base before derived blocks derived.
*/






🔹 Challenge 2: Catch by value vs reference
#include <iostream>
using namespace std;

class A {
public:
    virtual const char* name() const { return "A"; }
};

class B : public A {
public:
    const char* name() const override { return "B"; }
};

int main() {
    try {
        throw B();
    }
    catch (A a) {
        cout << a.name() << "\n";
    }
}
/* 
✅ Output
A

💡 Rule
Object slicing occurs when caught by value.
*/




🔹 Challenge 3: Correct polymorphic catch
#include <iostream>
using namespace std;

class A {
  public:
    virtual const char* name() const { return "A"; }
};

class B : public A {
  public:
    const char* name() const override { return "B"; }
};

int main() {
    try {
        throw B();
    }
    catch (const A& a) {
        cout << a.name() << "\n";
    }
}
/* 
✅ Output
B

💡 Rule
Always catch polymorphic types by reference.
*/





🔹 Challenge 4: Exception object lifetime
#include <iostream>
using namespace std;

struct X {
    X() { cout << "Ctor\n"; }
    X(const X&) { cout << "Copy\n"; }
    ~X() { cout << "Dtor\n"; }
};

int main() {
    try {
        throw X();
    }
    catch (X x) {
        cout << "Catch\n";
    }
}
/* 
✅ Output
Ctor
Copy
Catch
Dtor
Dtor

💡 Rule
Thrown object is copied into catch block → 2 destructors.
*/





🔹 Challenge 5: Rethrowing exception correctly
#include <iostream>
using namespace std;

int main() {
    try {
        try {
            throw 10;
        }
        catch (...) {
            cout << "Inner\n";
            throw;
        }
    }
    catch (int x) {
        cout << "Outer " << x << "\n";
    }
}
/* 
✅ Output
Inner
Outer 10

💡 Rule
throw; preserves original exception type.
*/





🔹 Challenge 6: Wrong rethrow (exception slicing)
#include <iostream>
using namespace std;

class A {};
class B : public A {};

int main() {
    try {
        try {
            throw B();
        }
        catch (A a) {
            throw a;
        }
    }
    catch (B&) {
        cout << "B\n";
    }
    catch (A&) {
        cout << "A\n";
    }
}
/* 
✅ Output
A

💡 Rule
Catching by value destroys derived info.
*/




🔹 Challenge 7: Exception in destructor (⚠️ dangerous)
#include <iostream>
using namespace std;

struct X {
    ~X() {
        cout << "Destructor\n";
        throw 1;
    }
};

int main() {
    try {
        X x;
        throw 2;
    }
    catch (...) {
        cout << "Caught\n";
    }
}
/* 
✅ Output
terminate called

💡 Rule
Throwing during stack unwinding ⇒ std::terminate()
*/





🔹 Challenge 8: noexcept function throws
#include <iostream>
using namespace std;

void f() noexcept {
    throw 10;
}

int main() {
    try {
        f();
    }
    catch (...) {
        cout << "Caught\n";
    }
}
/* 
✅ Output
terminate called

💡 Rule
Violating noexcept ⇒ immediate termination
*/




🔹 Challenge 9: Catching pointer exceptions
#include <iostream>
using namespace std;

int main() {
    try {
        throw new int(10);
    }
    catch (int* p) {
        cout << *p << "\n";
        delete p;
    }
}
/* 
✅ Output
10

💡 Rule
Throwing pointers is legal but dangerous design.
*/




🔹 Challenge 10: Function try block (constructor)
#include <iostream>
using namespace std;

struct A {
    A() try {
        throw 5;
    }
    catch (int x) {
        cout << "Ctor caught " << x << "\n";
        throw;
    }
};

int main() {
    try {
        A a;
    }
    catch (...) {
        cout << "Main caught\n";
    }
}
/* 
✅ Output
Ctor caught 5
Main caught

💡 Rule
Only way to catch constructor exceptions.
*/







20 UB Exception Prediction Problems
(Output OR “UB / terminate / unspecified” must be predicted)

⚠️ UB-1: Throw from destructor during stack unwinding
#include <iostream>
using namespace std;

struct A {
    ~A() {
        cout << "Dtor\n";
        throw 1;
    }
};

int main() {
    try {
        A a;
        throw 2;
    } catch (...) {
        cout << "Caught\n";
    }
}

❌ Result
terminate called

🔥 Reason

Destructor throws while another exception is active.




⚠️ UB-2: noexcept violation
#include <iostream>
using namespace std;

void f() noexcept {
    throw 10;
}

int main() {
    f();
}

❌ Result
terminate called






⚠️ UB-3: Delete through base without virtual destructor
#include <iostream>
using namespace std;

struct Base {
    ~Base() { cout << "Base dtor\n"; }
};

struct Derived : Base {
    ~Derived() { cout << "Derived dtor\n"; }
};

int main() {
    try {
        Base* b = new Derived;
        delete b;
    } catch (...) {}
}

❌ Result
UB (Derived destructor not called)






⚠️ UB-4: Double delete via exception path
#include <iostream>
using namespace std;

int main() {
    int* p = new int(5);
    try {
        delete p;
        throw 1;
    } catch (...) {
        delete p;
    }
}

❌ Result
UB (double free)





⚠️ UB-5: Rethrow sliced exception
#include <iostream>
using namespace std;

struct A {};
struct B : A {};

int main() {
    try {
        try {
            throw B();
        } catch (A a) {
            throw a;
        }
    } catch (B&) {
        cout << "B\n";
    } catch (A&) {
        cout << "A\n";
    }
}

✅ Output
A







⚠️ UB-6: Throw pointer to local variable
#include <iostream>
using namespace std;

int* f() {
    int x = 10;
    return &x;
}

int main() {
    int* p = f();
    cout << *p << "\n";
}

❌ Result
UB (dangling pointer)




⚠️ UB-7: Exception escapes destructor at program end
#include <iostream>
using namespace std;

struct A {
    ~A() { throw 1; }
};

A global;

int main() {}

❌ Result
terminate called





⚠️ UB-8: Catch wrong dynamic type by reference
#include <iostream>
using namespace std;

struct A {};
struct B : A {};

int main() {
    try {
        throw A();
    } catch (B&) {
        cout << "B\n";
    }
}

❌ Result
std::terminate (no matching handler)






⚠️ UB-9: Throwing from new handler incorrectly
#include <iostream>
#include <new>
using namespace std;

void handler() {
    throw 1;
}

int main() {
    set_new_handler(handler);
    try {
        while (true) new int[100000000];
    } catch (...) {
        cout << "Caught\n";
    }
}
/* 
❌ Result
terminate called

⚠️ UB-10: throw; without active exception
#include <iostream>
using namespace std;

int main() {
    throw;
}

❌ Result
terminate called
*/








PART-B 🔥
Exception + RAII + Smart Pointer Traps
Trap-1: unique_ptr + manual delete
#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> p(new int(5));
    delete p.get();
}

❌ Result
UB (double delete)






Trap-2: shared_ptr constructed twice
#include <iostream>
#include <memory>
using namespace std;

int main() {
    int* raw = new int(5);
    shared_ptr<int> p1(raw);
    shared_ptr<int> p2(raw);
}

❌ Result
UB (double free)

Trap-3: Exception before smart pointer ownership
#include <iostream>
#include <memory>
using namespace std;

void f() {
    int* p = new int(5);
    throw 1;
    unique_ptr<int> up(p);
}

int main() {
    try { f(); } catch (...) {}
}

❌ Result
Memory leak





PART-C 🔒
MISRA-Safe Exception Alternatives
✅ Rule

MISRA discourages exceptions → use error codes / status objects

MISRA-1: Error code
#include <iostream>
using namespace std;

bool divide(int a, int b, int& out) {
    if (b == 0) return false;
    out = a / b;
    return true;
}

int main() {
    int r;
    if (!divide(10, 0, r))
        cout << "Error\n";
}

✅ Output
Error





MISRA-2: Status enum
#include <iostream>
using namespace std;

enum class Status { OK, ERROR };

Status init() {
    return Status::ERROR;
}

int main() {
    if (init() != Status::OK)
        cout << "Fail\n";
}

✅ Output
Fail





MISRA-3: Optional (C++17 safe)
#include <iostream>
#include <optional>
using namespace std;

optional<int> get() {
    return nullopt;
}

int main() {
    if (!get())
        cout << "No value\n";
}

✅ Output
No value






PART-D ⚖️
Exception vs Error-Code Design
❌ Exception-based (unsafe in embedded)
#include <iostream>
using namespace std;

int f() {
    throw 1;
}

int main() {
    try {
        f();
    } catch (...) {
        cout << "Error\n";
    }
}



✅ Error-code-based (MISRA preferred)
#include <iostream>
using namespace std;

bool f(int& out) {
    return false;
}

int main() {
    int v;
    if (!f(v))
        cout << "Error\n";
}