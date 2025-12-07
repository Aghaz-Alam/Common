C++ provides these main casts:
static_cast
const_cast
dynamic_cast
reinterpret_cast

C-style cast (NOT recommended)
std::bit_cast (C++20)
explicit conversions using user-defined operators (C++11+)
/* ========================================================================================================================================== */
✅ 1. static_cast
Used for safe, compile-time conversions such as:
numeric conversions
pointer upcast
void* → typed pointer
enums
user-defined conversions if allowed

✔ Program: Numeric + Pointer Upcast
#include <iostream>
using namespace std;

class Base {};
class Derived : public Base {};

int main() {
    double d = 10.75;
    int i = static_cast<int>(d);        // numeric conversion

    Derived derived;
    Base* b = static_cast<Base*>(&derived);   // upcast (safe)

    cout << "double d = " << d << "\n";
    cout << "int i = static_cast<int>(d) → " << i << "\n";
    cout << "Pointer upcast (Derived* → Base*) successful\n";
}
/* 
✔ Output
double d = 10.75
int i = static_cast<int>(d) → 10
Pointer upcast (Derived* → Base*) successful
*/











/* --------------------------------------------------------------------------------------- */
✅ 1. Numeric Conversions
(float → int, int → double, etc.)

✔ Program
#include <iostream>
using namespace std;
int main() {
    double d = 12.78;
    int i = static_cast<int>(d);   // truncate decimal part

    float f = static_cast<float>(i);  // int → float

    cout << "Original double d = " << d << "\n";
    cout << "int i = static_cast<int>(d) → " << i << "\n";
    cout << "float f = static_cast<float>(i) → " << f << "\n";
}
/* 
✔ Output
Original double d = 12.78
int i = static_cast<int>(d) → 12
float f = static_cast<float>(i) → 12
*/


✅ 2. Pointer Upcast
(Derived* → Base*) — always safe

✔ Program
#include <iostream>
using namespace std;
class Base {
  public:
    void show() { cout << "Base class\n"; }
};
class Derived : public Base {
  public:
    void display() { cout << "Derived class\n"; }
};
int main() {
    Derived d;

    // Upcast: Derived* → Base*
    Base* b = static_cast<Base*>(&d);

    b->show();       // OK
    // b->display(); // ERROR: Base has no display()

    cout << "Upcast successful.\n";
}
/* 
✔ Output
Base class
Upcast successful.
*/


✅ 3. void → Typed Pointer*
Used when dealing with generic memory, C APIs, raw buffers.

✔ Program
#include <iostream>
using namespace std;
int main() {
    int x = 50;

    void* vp = &x;   // store address in void pointer

    // Convert back to typed pointer
    int* ip = static_cast<int*>(vp);

    cout << "Value through typed pointer = " << *ip << "\n";
}
/* 
✔ Output
Value through typed pointer = 50
*/


✅ 4. Enum Conversions
Both enum → int and int → enum.

✔ Program
#include <iostream>
using namespace std;
enum Color { RED = 1, GREEN = 2, BLUE = 3 };
int main() {
    Color c = GREEN;

    // Enum → int
    int val = static_cast<int>(c);

    // int → Enum
    Color c2 = static_cast<Color>(3);

    cout << "Enum GREEN as int = " << val << "\n";
    cout << "Integer 3 as Color = " << c2 << "\n";
}
/* 
✔ Output
Enum GREEN as int = 2
Integer 3 as Color = 3
*/



✅ 5. User-Defined Conversions (Using Constructor or operator)
If class has appropriate constructor or conversion operator.

✔ Program
#include <iostream>
using namespace std;
class Distance {
    double meters;
  public:
    Distance(double m) : meters(m) {}

    // Conversion to double
    explicit operator double() const {
        return meters;
    }
};
int main() {
    Distance d(42.5);

    // Calls explicit operator double()
    double x = static_cast<double>(d);

    cout << "Converted Distance → double = " << x << "\n";
}
/* 
✔ Output
Converted Distance → double = 42.5
*/
/* --------------------------------------------------------------------------------------- */
/* ========================================================================================================================================= */
✅ 2. const_cast
Used to:
Remove or add const
Needed when APIs expect non-const though data is mutable
⚠ You must not modify an object that was originally const.

✔ Program: Removing constness
#include <iostream>
using namespace std;
void modify(int* p) {
    *p = 200;
}
int main() {
    const int x = 100;
    // Remove constness (dangerous!)
    int* px = const_cast<int*>(&x);
    modify(px);
    cout << "After modification attempt, x = " << x << "\n";
}
/* 
✔ Output (UNDEFINED BEHAVIOR)
After modification attempt, x = 100
*/

⚠ WHY?
Because modifying a truly const object is UB.
Use const_cast only when the original object is non-const.




/* ----------------------------------------------------------- */
✔ 1. Removing const (const → non-const)
✔ 2. Adding const (non-const → const)
✔ 3. Correct usage (original object is non-const)
✔ 4. Undefined behavior (original object was const — modifying is illegal)

Each has its own program + output.

✅ 1. Removing constness (const → non-const)
This is the most common use of const_cast.

⚠ If the original object was const, modifying it is undefined behavior.
✔ Program (Removing constness — but SAFE because original object is non-const)
#include <iostream>
using namespace std;
void api_modify(int* p) {
    *p = 999;   // API expects non-const
}
int main() {
    int x = 100;           // NOT const originally
    const int* cx = &x;    // pointer-to-const

    int* px = const_cast<int*>(cx);  // remove constness

    api_modify(px);

    cout << "x after modification = " << x << "\n";
}
/* 
✔ Output
x after modification = 999

This works because x was never const originally.
*/



❌ 2. Removing constness and modifying original-const object (ILLEGAL)
This is undefined behavior.

✔ Program (Removing const from a real const — WRONG)
#include <iostream>
using namespace std;
int main() {
    const int x = 50;

    int* px = const_cast<int*>(&x);  // remove constness

    *px = 200;   // ❌ MODIFYING A CONST VARIABLE → UB

    cout << "x = " << x << "\n"; // unpredictable output
}
/* 
✔ Possible Output (implementation dependent)
x = 50

Or program may crash, or show 200, or behave randomly.
This is undefined behavior.
*/


✅ 3. Adding constness (non-const → const)
This is safe and often used when passing to APIs that expect const.

✔ Program (Adding const)
#include <iostream>
using namespace std;
void print_value(const int* p) {
    cout << "Value = " << *p << "\n";
}
int main() {
    int x = 300;

    int* px = &x;

    // Add constness
    const int* cpx = const_cast<const int*>(px);

    print_value(cpx);

    // Still can modify using original pointer
    *px = 400;

    print_value(cpx);
}
/* 
✔ Output
Value = 300
Value = 400

This works because adding constness simply prevents modification through cpx.
*/




✅ 4. Correct usage: Removing constness to call an old API
This is the valid intended use of const_cast.

✔ Program
#include <iostream>
using namespace std;

// Old C API that needs non-const pointer
void old_api_set(int* p) {
    *p = 555;
}
void safe_wrapper(const int* p) {
    old_api_set(const_cast<int*>(p));   // Allowed because original object is non-const
}
int main() {
    int value = 123;
    safe_wrapper(&value);
    cout << "value = " << value << "\n";
}
/* 
✔ Output
value = 555
*/
/* ----------------------------------------------------------- */
/* ========================================================================================================================================= */


✅ 3. dynamic_cast
Used for:
Safe downcasting in polymorphic classes (virtual functions)
Returns nullptr for invalid pointer cast
Throws std::bad_cast for invalid reference cast

✔ Program: Safe Downcast
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {}     // MUST be polymorphic
};
class Derived : public Base {};
int main() {
    Base* b1 = new Derived; // actually Derived
    Base* b2 = new Base;    // actually Base

    Derived* d1 = dynamic_cast<Derived*>(b1);  // OK
    Derived* d2 = dynamic_cast<Derived*>(b2);  // fails → nullptr

    cout << "d1 = " << (d1 ? "Success" : "Fail") << "\n";
    cout << "d2 = " << (d2 ? "Success" : "Fail") << "\n";

    delete b1;
    delete b2;
}
/* 
✔ Output
d1 = Success
d2 = Fail
*/



/* ----------------------------------------------------------- */
✔ 1. Safe downcasting (pointer version)
✔ 2. Returning nullptr when cast fails
✔ 3. Throwing std::bad_cast when reference cast fails
✔ 4. Upcasting works but unnecessary
✔ 5. Using dynamic_cast with multiple inheritance (bonus)

✅ 1. Safe Downcasting (pointer)
Casting Base* → Derived* safely.
Requires at least one virtual function to make the class polymorphic.


✔ Program — Successful Downcast
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {}   // MUST be polymorphic
};
class Derived : public Base {
  public:
    void show() { cout << "Derived object\n"; }
};
int main() {
    Base* b = new Derived;   // Actually pointing to Derived

    Derived* d = dynamic_cast<Derived*>(b);

    if (d)
        d->show();
    else
        cout << "Cast failed!\n";

    delete b;
}
/* 
✔ Output
Derived object
*/


✅ 2. Fails and returns nullptr (invalid pointer cast)
✔ Program — Downcast Failure
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {}
};
class Derived : public Base {};
class Other : public Base {};

int main() {
    Base* b = new Other;   // NOT a Derived

    Derived* d = dynamic_cast<Derived*>(b);

    if (d)
        cout << "Cast succeeded\n";
    else
        cout << "Cast failed (nullptr returned)\n";

    delete b;
}
/* 
✔ Output
Cast failed (nullptr returned)
*/


✅ 3. Reference dynamic_cast throws std::bad_cast on failure
✔ Program — Reference Cast Failure
#include <iostream>
#include <typeinfo>
using namespace std;
class Base {
  public:
    virtual ~Base() {}
};

class Derived : public Base {};
class Other : public Base {};
int main() {
    Other o;
    Base& b = o;   // Base ref referring to Other

    try {
        // Invalid cast: Base → Derived
        Derived& d = dynamic_cast<Derived&>(b);
        cout << "Cast succeeded!\n";
    }
    catch (const bad_cast& e) {
        cout << "Exception thrown: " << e.what() << "\n";
    }
}
/* 
✔ Output
Exception thrown: std::bad_cast
*/


✅ 4. Upcasting with dynamic_cast (allowed but unnecessary)
Upcasting (Derived* → Base*) always succeeds, but static_cast is preferred.

✔ Program — Upcast
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {}
};
class Derived : public Base {};
int main() {
    Derived d;
    Derived* pd = &d;

    Base* pb = dynamic_cast<Base*>(pd);   // Always succeeds

    if (pb)
        cout << "Upcast successful\n";
    else
        cout << "Upcast failed\n";
}
/* 
✔ Output
Upcast successful
*/



✅ 5. BONUS: Multiple Inheritance example (pointer)
✔ Program — dynamic_cast across multiple inheritance
#include <iostream>
using namespace std;

class A { public: virtual ~A() {} };
class B { public: virtual ~B() {} };

class C : public A, public B {};

int main() {
    C c;
    A* pa = &c;

    // Cast A* → B* through most-derived object
    B* pb = dynamic_cast<B*>(pa);

    if (pb)
        cout << "Cast A* → B* succeeded\n";
    else
        cout << "Cast failed\n";
}
/* 
✔ Output
Cast A* → B* succeeded
*/
/* ----------------------------------------------------------- */
/* ========================================================================================================================================= */

✅ 4. reinterpret_cast
Used for:
Low-level, unsafe conversions
Pointer-to-integer
Integer-to-pointer
Converting unrelated pointers
⚠ Breaks type safety → use sparingly.

✔ Program: Pointer reinterpretation
#include <iostream>
using namespace std;
int main() {
    int x = 100;

    // int* → char*
    char* p = reinterpret_cast<char*>(&x);

    cout << "First byte of x = " << static_cast<int>(*p) << "\n";

    // pointer to integer
    uintptr_t address = reinterpret_cast<uintptr_t>(p);

    cout << "Pointer as integer = " << address << "\n";
}
/* 
✔ Output (system-dependent)
First byte of x = 100
Pointer as integer = 140734583296700
*/


✅ 5. C-style cast (BAD PRACTICE)
Equivalent to trying these in order:
const_cast, then static_cast, then reinterpret_cast, then compiler extensions.

✔ Program
#include <iostream>
using namespace std;
int main() {
    double d = 9.9;

    int i = (int)d;   // C-style cast

    cout << "i = " << i << "\n";
}
/* 
✔ Output
i = 9
*/

⚠ Avoid because it’s unclear and dangerous.




✅ 6. std::bit_cast (C++20)
Used for bitwise reinterpretation between same-size types.
Safe and well-defined compared to reinterpret_cast.

✔ Program: Convert float ↔ uint32_t
#include <iostream>
#include <bit>
#include <cstdint>
using namespace std;
int main() {
    float f = 3.14f;

    uint32_t bits = std::bit_cast<uint32_t>(f);
    float f2 = std::bit_cast<float>(bits);

    cout << "Original float: " << f << "\n";
    cout << "Bit pattern: " << bits << "\n";
    cout << "Reconstructed float: " << f2 << "\n";
}
/* 
✔ Output (bit pattern may vary)
Original float: 3.14
Bit pattern: 1078523331
Reconstructed float: 3.14
*/




✅ 7. User-defined conversion operators (C++11–C++20)
These enable implicit/explicit casting using class methods.

✔ Program: explicit conversion
#include <iostream>
using namespace std;
class Meter {
    double m;
  public:
    Meter(double x): m(x) {}
    
    explicit operator double() const {   // explicit cast
        return m;
    }
};
int main() {
    Meter dist(12.5);

    double x = static_cast<double>(dist);   // must use static_cast
    cout << "Distance = " << x << " meters\n";
}
/* 
✔ Output
Distance = 12.5 meters
*/