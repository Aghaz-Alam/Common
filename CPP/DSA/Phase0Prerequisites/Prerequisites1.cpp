1️⃣ Lambda Capture LIFETIME TRAPS
🔴 Trap 1: Capturing local variable by reference and returning lambda
❓ What happens?
#include <iostream>
#include <functional>
using namespace std;
function<void()> makeLambda() {
    int x = 10;

    return [&x]() {
        cout << x << endl;
    };
}
int main() {
    auto f = makeLambda();
    f();   // ❌ Undefined Behavior
}

🖥 Output
Garbage value / crash / unpredictable

💥 WHY?

x is local to makeLambda
After function returns → x is destroyed
Lambda holds a dangling reference

📌 Interview Rule
Never capture local variables by reference if lambda outlives the scope.




✅ FIX 1: Capture by VALUE
#include <iostream>
#include <functional>
using namespace std;
function<void()> makeLambda() {
    int x = 10;

    return [x]() {
        cout << x << endl;
    };
}
int main() {
    auto f = makeLambda();
    f();
}

🖥 Output
10

✔ Value capture copies data → lifetime safe





🔴 Trap 2: Capturing this pointer
#include <iostream>
#include <functional>
using namespace std;
class A {
  public:
    int x = 10;

    function<void()> getLambda() {
        return [this]() {
            cout << x << endl;
        };
    }
};
int main() {
    function<void()> f;
    {
        A obj;
        f = obj.getLambda();
    }   // obj destroyed here

    f();   // ❌ UB
}

🖥 Output
Crash / garbage

💥 WHY?
Lambda captures this
Object destroyed
this becomes dangling pointer





✅ FIX 2: Capture by VALUE (C++17)
#include <iostream>
#include <functional>
using namespace std;
class A {
  public:
    int x = 10;

    function<void()> getLambda() {
        return [*this]() {
            cout << x << endl;
        };
    }
};
int main() {
    function<void()> f;
    {
        A obj;
        f = obj.getLambda();
    }

    f();
}

🖥 Output
10

📌 [*this] → captures a copy of the object




🔴 Trap 3: Lambda capturing pointer to temporary
#include <iostream>
using namespace std;
int* getPtr() {
    int x = 10;
    return &x;   // ❌
}
int main() {
    auto lam = [p = getPtr()]() {
        cout << *p << endl;
    };

    lam();   // ❌ UB
}

📌 Capturing a pointer does NOT extend lifetime.





2️⃣ PERFECT FORWARDING PITFALLS (VERY IMPORTANT)
🔹 Perfect Forwarding Goal
Preserve lvalue / rvalue nature of arguments.

🔴 Trap 1: Missing std::forward
#include <iostream>
using namespace std;
void process(int& x) {
    cout << "lvalue\n";
}
void process(int&& x) {
    cout << "rvalue\n";
}
template<typename T>
void wrapper(T x) {
    process(x);   // ❌ ALWAYS lvalue
}
int main() {
    wrapper(10);
}

🖥 Output
lvalue

💥 WHY?
x is a named variable
Named variables are always lvalues




✅ FIX 1: Use std::forward
#include <iostream>
using namespace std;
void process(int& x) {
    cout << "lvalue\n";
}
void process(int&& x) {
    cout << "rvalue\n";
}
template<typename T>
void wrapper(T&& x) {
    process(std::forward<T>(x));
}
int main() {
    wrapper(10);
}

🖥 Output
rvalue





🔴 Trap 2: Using std::move instead of std::forward
template<typename T>
void wrapper(T&& x) {
    process(std::move(x));  // ❌ forces rvalue
}

❌ Problem
Converts lvalue → rvalue
Breaks semantics
Causes accidental moves

📌 Interview Rule
Use std::forward in templates, not std::move.




🔴 Trap 3: Forwarding const object
#include <iostream>
using namespace std;
void process(int&& x) {
    cout << "rvalue\n";
}

int main() {
    const int x = 10;
    process(std::move(x));  // ❌ error
}

💥 WHY?
std::move(x) → const int&&
Cannot bind to int&&
📌 const kills move semantics

🔴 Trap 4: Forwarding reference misconception
template<typename T>
void foo(T&& x);   // forwarding reference
void bar(int&& x); // rvalue reference

📌 T&& is forwarding reference only if T is template type



🔥 ULTIMATE INTERVIEW TRAP
template<typename T>
void foo(T&& x) {
    auto lam = [&]() {
        process(std::forward<T>(x));  // ❌ WRONG
    };
}

💥 WHY?
x captured by reference
Forwarding category lost
Can cause dangling reference



✅ CORRECT VERSION
template<typename T>
void foo(T&& x) {
    auto lam = [x = std::forward<T>(x)]() {
        process(x);
    };
}

🧠 FINAL INTERVIEW MEMORY SHEET
Lambda Lifetimes
❌ Reference capture + escaping lambda = UB
❌ Capturing this without lifetime guarantee
✅ Capture by value

✅ Use [*this] (C++17)
Perfect Forwarding
Use T&& + std::forward
Never use std::move in forwarding
const disables move
Named variables are lvalues

🏁 INTERVIEW GOLD LINE
Most modern C++ bugs are lifetime bugs hidden behind lambdas and forwarding references.







1️⃣ auto&& — THE BLACK MAGIC TYPE
❓ What does auto&& mean?
👉 It is a universal / forwarding reference.

🔴 Trap Code
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    auto&& a = x;     // lvalue
    auto&& b = 20;    // rvalue

    a = 30;

    cout << x << endl;
    cout << b << endl;
}
/*
🖥 Output
30
20

💥 WHY?
Expression	Type
x	lvalue → int&
20	rvalue → int&&
📌 auto&& adapts to value category.

🎯 Interview Rule
auto&& binds to anything and preserves value category.
*/




2️⃣ decltype(auto) — RETURN TYPE TRAP
🔴 Trap
#include <iostream>
using namespace std;
int x = 10;
decltype(auto) get() {
    return x;   // returns int& (NOT int)
}
int main() {
    auto y = get();
    y = 20;

    cout << x << endl;
}
/*
🖥 Output
10

❗ Surprising?
auto drops references
decltype(auto) preserves them

🔴 EVEN WORSE TRAP
decltype(auto) bad() {
    int x = 10;
    return (x);   // ❌ returns int&
}

📌 Returning reference to local → UB
*/




3️⃣ Temporary Lifetime Extension TRAP
🔴 Looks Safe, Is NOT
#include <iostream>
using namespace std;
const int& ref = 10;
int main() {
    cout << ref << endl;
}
/*
🖥 Output
10

✔ Lifetime extended → OK

❌ BUT THIS IS NOT
int main() {
    const int& r = (int)10;
}

📌 Cast breaks lifetime extension guarantee.
*/





4️⃣ mutable vs const_cast (REAL DIFFERENCE)
❓ Which is safe?
✅ mutable
#include <iostream>
using namespace std;
class A {
    mutable int cache = 0;
  public:
    int get() const {
        cache++;
        return cache;
    }
};
int main() {
    const A obj;
    cout << obj.get() << endl;
    cout << obj.get() << endl;
}
/*
🖥 Output
1
2

✔ Safe
✔ Logical constness

❌ const_cast TRAP
const int x = 10;
int& y = const_cast<int&>(x);
y = 20;   // ❌ UB

🎯 Interview Rule
Prefer mutable for logical constness.
const_cast is for legacy APIs only.
*/




5️⃣ Iterator Invalidations (SILENT KILLER)
🔴 Trap
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1,2,3};

    auto it = v.begin();
    v.push_back(4);   // ❌ invalidates iterator

    cout << *it << endl;
}
/*
🖥 Output
Undefined Behavior

🎯 Interview Rule
Container	Invalidation
vector	insert → invalidates
list	safe
map	safe
*/




6️⃣ Copy Elision vs Move (C++17 TRAP)
#include <iostream>
using namespace std;
struct A {
    A() { cout << "Ctor\n"; }
    A(const A&) { cout << "Copy\n"; }
    A(A&&) { cout << "Move\n"; }
};
A make() {
    return A();
}
int main() {
    A a = make();
}
/*
🖥 Output (C++17)
Ctor

✔ Copy & Move elided
✔ Guaranteed copy elision
*/



7️⃣ Overload Resolution Trap
void f(int);
void f(int&);
int main() {
    int x = 10;
    f(x);   // ❌ ambiguous
}
/*
📌 Reference overloads often create ambiguity.
*/




8️⃣ Boolean Conversion Trap
struct A {
    operator bool() const { return true; }
};
int main() {
    A a;
    if(a) cout << "True\n";
}
/*
✔ Works
❌ But dangerous in arithmetic contexts

✅ SAFE WAY
explicit operator bool() const;
*/



9️⃣ Exception Safety — Strong vs Basic
void push(vector<int>& v, int x) {
    v.push_back(x); // strong guarantee
}

But:
v.resize(v.size()+1); // may leave partially modified state

📌 Interview expects exception guarantees knowledge



🔥 FINAL INTERVIEW MASTER RULES
auto&& preserves value category
decltype(auto) preserves references
Lifetime > type correctness
mutable > const_cast
Iterator invalidation is silent UB
C++17 removes many moves
Lambdas hide lifetime bugs

🧠 Ultimate Interview Line
Modern C++ bugs are mostly invisible lifetime and ownership bugs.







🔥 1️⃣ Most Dangerous auto Trap (Reference Lost)
#include <iostream>
using namespace std;
int& getRef() {
    static int x = 10;
    return x;
}
int main() {
    auto a = getRef();      // ❌ reference dropped
    auto& b = getRef();     // ✅ reference preserved

    a = 20;
    b = 30;

    cout << getRef() << endl;
}
/*
🖥 Output
30

💥 WHY?
Variable	Type
a	int (copy)
b	int&

📌 auto never deduces references unless explicitly asked.
*/




🔥 2️⃣ decltype vs decltype(auto) TRAP
#include <iostream>
using namespace std;
int x = 10;
decltype(x) f1() { return x; }        // int
decltype(auto) f2() { return (x); }   // int&
int main() {
    f1() = 20;    // ❌ error (temporary)
    f2() = 30;    // ✅ modifies x

    cout << x << endl;
}
/*
🖥 Output
30

📌 Parentheses change everything.
*/





🔥 3️⃣ Reference Collapsing NIGHTMARE
#include <iostream>
using namespace std;
template<typename T>
void test(T&& x) {
    cout << "Inside\n";
}
int main() {
    int a = 10;
    test(a);      // T = int& → T&& → int&
    test(20);     // T = int → T&& → int&&
}
/*
🖥 Output
Inside
Inside

📌 T&& is forwarding reference only in templates.
*/



🔥 4️⃣ std::move DOES NOT MOVE
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "Hello";
    string t = std::move(s);

    cout << "s = [" << s << "]\n";
    cout << "t = [" << t << "]\n";
}
/*
🖥 Output (implementation dependent)
s = []
t = [Hello]

📌 std::move only casts, move happens in constructor.
*/




🔥 5️⃣ const + std::move = NO MOVE
#include <iostream>
#include <string>
using namespace std;
int main() {
    const string s = "Hello";
    string t = std::move(s);   // ❌ copy, not move

    cout << t << endl;
}
/*
🖥 Output
Hello

📌 const disables move semantics.
*/




🔥 6️⃣ Lambda Capture VALUE but MODIFY (mutable)
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    auto lam = [x]() mutable {
        x += 5;
        cout << x << endl;
    };

    lam();
    lam();

    cout << x << endl;
}
/*
🖥 Output
15
20
10

📌 Captured copy is modified, original unchanged.
*/




🔥 7️⃣ Temporary Lifetime EXTENDED (BUT NOT ALWAYS)
#include <iostream>
using namespace std;
int main() {
    const int& r = 10;
    cout << r << endl;
}
/*
🖥 Output
10

✔ Lifetime extended
❌ TRAP VERSION
int main() {
    const int* p = &10;   // ❌ error
}

📌 Only references extend lifetime, not pointers.
*/




🔥 8️⃣ Dangling Reference via initializer_list
#include <iostream>
using namespace std;
const int& get(const initializer_list<int>& l) {
    return *l.begin();   // ❌ dangling
}
int main() {
    const int& r = get({1,2,3});
    cout << r << endl;
}
/*
🖥 Output
Undefined Behavior

📌 initializer_list is temporary.
*/




🔥 9️⃣ Virtual Call in Constructor TRAP
#include <iostream>
using namespace std;
class Base {
  public:
    Base() { foo(); }
    virtual void foo() { cout << "Base\n"; }
};
class Derived : public Base {
  public:
    void foo() override { cout << "Derived\n"; }
};
int main() {
    Derived d;
}
/*
🖥 Output
Base

📌 Virtual dispatch disabled in constructors.
*/





🔥 10️⃣ Order of Evaluation TRAP
#include <iostream>
using namespace std;
int i = 0;
int f() { return i++; }
int g() { return i++; }
int main() {
    cout << f() << g() << endl;
}
/*
🖥 Output
01 OR 10

📌 Order of evaluation is unspecified.
*/


🧠 INTERVIEW MASTER RULES (MEMORIZE)
auto drops references
decltype(auto) preserves references
std::move ≠ move
const kills move
Lambdas hide lifetime bugs
Temporaries extend only via references
Virtual calls don't work in constructors
Order of evaluation is dangerous

🏆 FINAL INTERVIEW KILLER LINE
If code looks simple but behavior is complex, it's probably testing lifetime or value category.






🔥 1️⃣ sizeof TRAPS (ARRAY vs POINTER)
#include <iostream>
using namespace std;
void foo(int arr[]) {
    cout << sizeof(arr) << endl;
}
int main() {
    int a[10];
    cout << sizeof(a) << endl;
    foo(a);
}
/*
🖥 Output (64-bit)
40
8

💥 WHY?
In function parameters, arrays decay to pointers
sizeof(arr) inside function = size of pointer

📌 Interview Rule
Arrays never survive function calls.
*/





🔥 2️⃣ const with auto TRAP
#include <iostream>
using namespace std;
int main() {
    const int x = 10;

    auto a = x;       // int
    const auto b = x; // const int

    cout << a << " " << b << endl;
}
/*
🖥 Output
10 10

📌 auto drops top-level const
*/






🔥 3️⃣ constexpr FUNCTION TRAP
#include <iostream>
using namespace std;
constexpr int f(int x) {
    return x * 2;
}
int main() {
    int a = 10;
    constexpr int b = f(5); // OK
    int c = f(a);           // runtime

    cout << b << " " << c << endl;
}
/*
🖥 Output
10 20

📌 constexpr allows compile-time, not forces it.
*/



🔥 4️⃣ friend BREAKS ENCAPSULATION
#include <iostream>
using namespace std;
class A {
    int x = 10;
    friend void show(A&);
};
void show(A& a) {
    cout << a.x << endl;
}
int main() {
    A obj;
    show(obj);
}
/*
🖥 Output
10

📌 Used sparingly — often criticized in interviews.
*/





🔥 5️⃣ mutable DATA MEMBER TRAP
#include <iostream>
using namespace std;
class Cache {
    mutable int count = 0;
  public:
    int get() const {
        return ++count;
    }
};
int main() {
    const Cache c;
    cout << c.get() << endl;
    cout << c.get() << endl;
}
/*
🖥 Output
1
2

📌 Enables logical constness
*/





🔥 6️⃣ std::vector<bool> SPECIALIZATION TRAP
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<bool> v = {true, false};

    auto x = v[0];
    x = false;

    cout << v[0] << endl;
}
/*
🖥 Output
1

📌 vector<bool> stores bits, not bools
📌 v[0] returns proxy object
*/






🔥 7️⃣ Range-for LOOP COPY TRAP
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1,2,3};

    for(auto x : v)
        x += 10;

    for(auto x : v)
        cout << x << " ";
}
/*
🖥 Output
1 2 3

✅ FIX
for(auto& x : v)
    x += 10;
*/






🔥 8️⃣ Default Argument VIRTUAL TRAP
#include <iostream>
using namespace std;
class Base {
  public:
    virtual void show(int x = 10) {
        cout << x << endl;
    }
};
class Derived : public Base {
  public:
    void show(int x = 20) override {
        cout << x << endl;
    }
};
int main() {
    Base* b = new Derived();
    b->show();
}
/*
🖥 Output
10

📌 Default arguments are statically bound
*/




🔥 9️⃣ explicit CONSTRUCTOR TRAP
#include <iostream>
using namespace std;
class A {
  public:
    A(int x) {}
};
void foo(A a) {}
int main() {
    foo(10);  // implicit conversion
}

❌ Dangerous
✅ FIX
explicit A(int x) {}






🔥 🔟 Post-Increment COST TRAP
#include <iostream>
using namespace std;
class A {
  public:
    A operator++(int) {
        A temp = *this;
        return temp;
    }
};
int main() {
    A a;
    a++;
}

📌 Post-increment creates copy
📌 Prefer pre-increment




🧠 PHASE-0++ INTERVIEW CHECKLIST
✔ auto / decltype traps
✔ lifetime rules
✔ reference collapsing
✔ const correctness
✔ STL oddities
✔ virtual + default args
✔ value vs reference semantics

🏆 FINAL INTERVIEW LINE
If you don’t think about lifetime, reference, and const — your code is already wrong.









🔥 1️⃣ Name Hiding (NOT Overriding)
❌ Trap
#include <iostream>
using namespace std;
class Base {
  public:
    void show(int x) {
        cout << "Base int\n";
    }
};
class Derived : public Base {
  public:
    void show(double x) {
        cout << "Derived double\n";
    }
};
int main() {
    Derived d;
    d.show(10);   // ❌ which one?
}
/*
🖥 Output
Derived double

💥 WHY?
Derived show(double) hides ALL Base::show
Base overloads are not visible

✅ FIX
class Derived : public Base {
  public:
    using Base::show;
    void show(double x) {
        cout << "Derived double\n";
    }
};

📌 Interview Rule
Name hiding ≠ overriding
*/


🔥 2️⃣ Object Slicing (Classic Trap)
#include <iostream>
using namespace std;
class Base {
 public:
    virtual void show() {
        cout << "Base\n";
    }
};
class Derived : public Base {
  public:
    void show() override {
        cout << "Derived\n";
    }
};
int main() {
    Base b = Derived();  // ❌ slicing
    b.show();
}
/*
🖥 Output
Base

💥 WHY?
Derived part is sliced off
Polymorphism requires references or pointers
*/




🔥 3️⃣ Returning Reference to Temporary
#include <iostream>
using namespace std;
const int& foo() {
    return 10;   // ❌ dangling
}
int main() {
    cout << foo() << endl;
}
/*
🖥 Output
Undefined Behavior

📌 Lifetime extension works only when binding directly, not via return.
*/




🔥 4️⃣ std::initializer_list Preference Trap
#include <iostream>
using namespace std;
class A {
  public:
    A(int x) { cout << "int\n"; }
    A(initializer_list<int>) { cout << "init_list\n"; }
};
int main() {
    A a1(10);
    A a2{10};
}
/*
🖥 Output
int
init_list

📌 {} prefers initializer_list
*/






🔥 5️⃣ Copy vs Move Constructor Preference
#include <iostream>
using namespace std;
class A {
  public:
    A() {}
    A(const A&) { cout << "Copy\n"; }
    A(A&&) { cout << "Move\n"; }
};
A make() {
    A a;
    return a;
}
int main() {
    A obj = make();
}
/*
🖥 Output (C++17)
(no output)

📌 Guaranteed copy elision
📌 Copy/Move not called
*/




🔥 6️⃣ const After Function (Member Constness)
#include <iostream>
using namespace std;
class A {
    int x = 10;
  public:
    int get() { return x; }
    int get() const { return x; }
};
int main() {
    const A a;
    cout << a.get() << endl;
}
/*
🖥 Output
10

📌 const object calls const function
*/






🔥 7️⃣ Pointer Arithmetic Trap
#include <iostream>
using namespace std;
int main() {
    int a[3] = {1,2,3};

    cout << *(a + 1) << endl;
    cout << *(1 + a) << endl;
}
/*
🖥 Output
2
2

📌 a[b] == *(a+b) == *(b+a)
*/




🔥 8️⃣ Overloading on Return Type ❌
int foo();
double foo();  // ❌ invalid

📌 Return type not part of function signature





🔥 9️⃣ sizeof on Empty Class
#include <iostream>
using namespace std;
class A {};
int main() {
    cout << sizeof(A) << endl;
}
/*
🖥 Output
1

📌 Objects must have unique addresses
*/





🔥 🔟 delete vs delete[]
#include <iostream>
using namespace std;
int main() {
    int* p = new int[3];
    delete p;     // ❌ UB
}
/*
📌 Must match allocation type
*/





🔥 1️⃣1️⃣ Static Member Shared Across Objects
#include <iostream>
using namespace std;
class A {
  public:
    static int x;
};
int A::x = 0;
int main() {
    A a, b;
    a.x = 10;
    cout << b.x << endl;
}
/*
🖥 Output
10

📌 Static members belong to class
*/



🔥 1️⃣2️⃣ volatile Is NOT Thread Safety
volatile int flag = 0;

📌 Prevents optimization
📌 Does NOT ensure atomicity




🧠 PHASE-0 FINAL INTERVIEW TAKEAWAYS
{} changes overload resolution
auto drops references
const affects overloads
Copy elision hides constructors
Object slicing kills polymorphism
Lifetime bugs compile fine
Name hiding ≠ overriding

🏆 ULTIMATE INTERVIEW LINE
C++ fails silently — if you don’t reason about lifetime, ownership, and constness, the compiler won’t save you.











🔥 1️⃣ Temporary Object Destruction Order (VERY TRICKY)
#include <iostream>
using namespace std;
struct A {
    A()  { cout << "A "; }
    ~A() { cout << "~A "; }
};
int main() {
    cout << "Start ";
    A();
    cout << " End";
}
/*
🖥 Output
Start A ~A  End

💥 WHY?
A() creates a temporary object
Temporary is destroyed at end of full expression

📌 Interview Rule
Temporaries die at the semicolon, not end of scope.
*/





🔥 2️⃣ Reference Binding Priority Trap
#include <iostream>
using namespace std;
void f(int& x) { cout << "lvalue\n"; }
void f(const int& x) { cout << "const lvalue\n"; }
void f(int&& x) { cout << "rvalue\n"; }
int main() {
    int a = 10;
    const int b = 20;

    f(a);
    f(b);
    f(30);
}
/*
🖥 Output
lvalue
const lvalue
rvalue

📌 Overload resolution prefers most specific match
*/






🔥 3️⃣ std::initializer_list Lifetime Trap
#include <iostream>
using namespace std;
void print(initializer_list<int> l) {
    cout << *l.begin() << endl;
}
int main() {
    print({10, 20, 30});
}
/*
🖥 Output
10

✔ Safe here
❌ NOT safe if returned or stored
*/







🔥 4️⃣ auto with Braces TRAP
#include <iostream>
#include <typeinfo>
using namespace std;
int main() {
    auto a = 10;
    auto b{10};

    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
}
/*
🖥 Output (GCC)
i
i

✔ In single element → int

❌ MULTI ELEMENT TRAP
auto c = {1, 2, 3};   // initializer_list<int>

📌 {} changes type deduction rules
*/






🔥 5️⃣ Dangling Pointer via string::c_str()
#include <iostream>
#include <string>
using namespace std;
const char* get() {
    string s = "Hello";
    return s.c_str();   // ❌ dangling
}
int main() {
    cout << get() << endl;
}
/*
🖥 Output
Garbage / crash

📌 c_str() pointer valid only while string exists
*/





🔥 6️⃣ std::move + Self Assignment Trap
#include <iostream>
using namespace std;
struct A {
    int* p;
    A() { p = new int(10); }

    A& operator=(A&& other) {
        delete p;
        p = other.p;
        other.p = nullptr;
        return *this;
    }

    ~A() { delete p; }
};
int main() {
    A a;
    a = std::move(a);   // ❌ self-move
}

📌 Self-move assignment must be guarded





🔥 7️⃣ Boolean Conversion Ambiguity
#include <iostream>
using namespace std;
struct A {
    operator bool() const { return true; }
};
int main() {
    A a;
    cout << (a + 1) << endl;   // ❌ unexpected
}
/*
💥 WHY?
a converts to bool
bool converts to int

📌 Fix
explicit operator bool() const;
*/





🔥 8️⃣ Function Pointer vs Function Reference
#include <iostream>
using namespace std;
void foo() { cout << "foo\n"; }
int main() {
    void (*p)() = foo;
    void (&r)() = foo;

    p();
    r();
}
/*
🖥 Output
foo
foo

📌 References cannot be reseated, pointers can.
*/




🔥 9️⃣ const Data Member Initialization Trap
#include <iostream>
using namespace std;
class A {
    const int x;
  public:
    A(int v) : x(v) {}
};
int main() {
    A a(10);
}

📌 const members must be initialized in initializer list






🔥 🔟 Evaluation Order in Constructor Initializer List
#include <iostream>
using namespace std;
class A {
    int x;
    int y;
  public:
    A() : y(20), x(y) {
        cout << x << " " << y << endl;
    }
};
int main() {
    A a;
}
/*
🖥 Output
0 20   (or garbage)

💥 WHY?
Members initialized in declaration order
NOT initializer list order
*/





🔥 1️⃣1️⃣ Static Initialization Order Fiasco (Intro)
#include <iostream>
using namespace std;
int x = y;
int y = 10;
int main() {
    cout << x << endl;
}
/*
🖥 Output
0

📌 Global variables initialize top-to-bottom
*/





🔥 1️⃣2️⃣ Pointer Comparison Trap
#include <iostream>
using namespace std;
int main() {
    int a, b;

    cout << (&a < &b) << endl;  // ❌ meaningless
}

📌 Pointer comparison only valid within same array





🧠 PHASE-0 ADVANCED SUMMARY (MEMORIZE)
Temporaries die fast
{} changes overload & type deduction
auto drops const/reference
Lifetime > syntax correctness
Initialization order matters
std::move doesn’t move
Self-move is a real bug

🏆 INTERVIEW CLOSING LINE
C++ lets incorrect logic compile perfectly — understanding object lifetime is the real skill.





1️⃣ Narrowing Conversion (C++11) — ❌ MISRA VIOLATION
#include <iostream>
using namespace std;
int main() {
    double d = 3.7;
    int x = d;        // ❌ narrowing (allowed but unsafe)
    cout << x << endl;
}
/*
🖥 Output
3

❌ MISRA

Implicit narrowing = loss of precision
✅ SAFE (MISRA-style)
int x = static_cast<int>(d);

📌 MISRA prefers explicit casts only
*/





2️⃣ Uniform Initialization Prevents Narrowing (C++11)
#include <iostream>
using namespace std;
int main() {
    // int x{3.7};   // ❌ compile error
    int x{3};       // OK
    cout << x << endl;
}
/*
🖥 Output
3

📌 {} blocks narrowing → MISRA-preferred
*/






3️⃣ nullptr vs NULL (MISRA CORE RULE)
#include <iostream>
using namespace std;
void f(int)  { cout << "int\n"; }
void f(int*) { cout << "ptr\n"; }
int main() {
    // f(NULL);     // ❌ ambiguous / unsafe
    f(nullptr);     // ✅ safe
}
/*
🖥 Output
ptr

📌 MISRA: NULL forbidden, use nullptr
*/





4️⃣ enum class vs enum (Type Safety)
#include <iostream>
using namespace std;
enum Color { RED, BLUE };
enum class SafeColor { RED, BLUE };
int main() {
    int x = RED;              // ❌ implicit
    // int y = SafeColor::RED; // ❌ compile error

    cout << x << endl;
}
/*
🖥 Output
0

📌 MISRA: use enum class only
*/




5️⃣ explicit Constructors (MISRA REQUIRED)
#include <iostream>
using namespace std;
class Speed {
    int v;
  public:
    explicit Speed(int x) : v(x) {}
};
void drive(Speed s) {}
int main() {
    // drive(100);   // ❌ implicit conversion blocked
    drive(Speed(100));
}

📌 Prevents accidental implicit conversions





6️⃣ noexcept (C++11 → C++23) — Safety Critical
#include <iostream>
using namespace std;
void safeFunc() noexcept {
    cout << "Safe\n";
}
int main() {
    safeFunc();
}
/*
🖥 Output
Safe

📌 MISRA:
Destructors → noexcept
Move constructors → noexcept
*/





7️⃣ Destructor Throwing — ❌ MISRA VIOLATION
#include <iostream>
using namespace std;
class A {
  public:
    ~A() noexcept(false) {
        throw 1;   // ❌ catastrophic
    }
};
int main() {
    try {
        A a;
    } catch(...) {
        cout << "Caught\n";
    }
}
/*
📌 Throwing from destructor during stack unwinding = terminate
MISRA: Destructors must not throw
*/




8️⃣ std::array vs C-Array (MISRA SAFE)
#include <iostream>
#include <array>
using namespace std;
int main() {
    array<int,3> a = {1,2,3};
    cout << a.size() << endl;
}
/*
🖥 Output
3

📌 Bounds known at compile-time
📌 Safer than raw arrays
*/





9️⃣ Range-for by Value ❌ (Hidden Copy)
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1,2,3};

    for (auto x : v) {
        x += 10;   // modifies copy
    }

    for (auto x : v)
        cout << x << " ";
}
/*
🖥 Output
1 2 3

✅ MISRA-STYLE FIX
for (auto& x : v)
*/





🔟 volatile is NOT thread-safe (MISRA WARNING)
#include <iostream>
using namespace std;
volatile int flag = 0;
int main() {
    flag = 1;
    cout << flag << endl;
}
/*
📌 volatile:
❌ no atomicity
❌ no synchronization
MISRA: Use atomics, not volatile.
*/






1️⃣1️⃣ std::move on const (MISRA TRAP)
#include <iostream>
#include <string>
using namespace std;
int main() {
    const string s = "ADAS";
    string t = std::move(s);   // ❌ copy, not move
    cout << t << endl;
}
/*
🖥 Output
ADAS

📌 MISRA: Moving const objects is meaningless
*/





1️⃣2️⃣ = delete (C++11) — MISRA GOLD
#include <iostream>
using namespace std;
class NoCopy {
  public:
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};
int main() {
    NoCopy a;
    // NoCopy b = a;  // ❌ compile error
}

📌 Explicitly prevents misuse







1️⃣3️⃣ = default vs Custom (Consistency)
class A {
public:
    A() = default;
    ~A() = default;
};
/*
📌 MISRA: Prefer compiler-generated defaults
*/





1️⃣4️⃣ [[nodiscard]] (C++17) — MISRA-LIKE RULE
#include <iostream>
using namespace std;
[[nodiscard]] int compute() {
    return 42;
}
int main() {
    compute();   // ❌ warning
}
/*
📌 Prevents ignoring critical return values
*/





1️⃣5️⃣ std::span (C++20) — MISRA ARRAY SAFETY
#include <iostream>
#include <span>
using namespace std;
void print(span<int> s) {
    cout << s.size() << endl;
}
int main() {
    int a[] = {1,2,3};
    print(a);
}
/*
🖥 Output
3

📌 Safe view, no ownership, bounds known
*/