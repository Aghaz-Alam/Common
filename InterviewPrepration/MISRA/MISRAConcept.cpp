✅ What is MISRA in C++?
MISRA stands for Motor Industry Software Reliability Association.
MISRA C++ is a set of rules that define how C++ should be written to ensure:

✔ Safety — avoid undefined/unsafe behavior
✔ Reliability — predictable behavior in embedded systems
✔ Portability — consistent across compilers and hardware
✔ Maintainability — readable, consistent code
The standard restricts some C++ features that are complex or error-prone.


Where MISRA is used?
MISRA C++ is used in industries where software failure can cause harm:
-->Automotive ECUs (Engine, ABS, ADAS)
-->Aerospace software
-->Medical devices
-->Industrial control systems
-->Defense systems


Why MISRA is needed?
C++ has many advanced features (templates, multiple inheritance, operator overloading, RTTI), but in embedded safety-critical software:
❌ Some features can lead to undefined behavior
❌ Some are hard for static analysis tools
❌ Some features increase binary size
❌ Some reduce predictability
MISRA creates restrictions to reduce risks.


MISRA C++ Versions
| Version            | Notes                      |
| ------------------ | -------------------------- |
| **MISRA C++ 2008** | Most widely adopted        |
| **MISRA C++ 2023** | Latest; modern C++17 rules |


Examples of MISRA Rules

Below are some real MISRA-style rules:

1️⃣ No dynamic memory allocation in embedded systems
❌ new and delete often forbidden (risk of fragmentation)
int* p = new int(5);  // MISRA violation
✔ Use static or stack memory
int a = 5;

2️⃣ Do not use multiple inheritance
class A {};
class B {};
class C : public A, public B {}; // MISRA prohibits this

3️⃣ Avoid implicit type conversions
int x = 3.14;   // Narrowing conversion → MISRA violation

4️⃣ Explicit initialization always required
int x;  // uninitialized → MISRA violation
✔ Correct:
int x = 0;

5️⃣ Avoid exceptions in embedded systems
throw std::runtime_error("error");  // MISRA discourages this
Often replaced with error codes or safe handlers.

6️⃣ Avoid using reinterpret_cast
Very dangerous in embedded memory-mapped registers.

7️⃣ Enforce deterministic behavior
No reliance on:
undefined behavior
unspecified order of evaluation
unbounded recursion




How MISRA is enforced?
Companies use static analysis tools:
CppCheck
Clang-Tidy MISRA
LDRA
Polyspace
QAC++
Parasoft
These tools scan code and report MISRA rule violations.



MISRA Categories
| Category        | Meaning                                     |
| --------------- | ------------------------------------------- |
| **Required**    | Must obey — violation = defect              |
| **Advisory**    | Should obey — violation needs justification |
| **Decidable**   | Can be checked automatically                |
| **Undecidable** | Requires manual review                      |


Example: MISRA-Compliant Code
#include <cstdint>
class MotorController {
  private:
    std::uint16_t speed;
  public:
    MotorController() : speed(0U) {}
    void setSpeed(std::uint16_t value) {
        if (value <= 100U) {
            speed = value;
        }
    }
    std::uint16_t getSpeed() const {
        return speed;
    }
};

✔ No dynamic allocation
✔ No implicit casts
✔ Fully initialized
✔ Safe integer 



Summary (Easy)
MISRA C++ = Safety rules for writing C++ in critical systems.
Avoid dangerous features
Promote deterministic behavior
Ensure reliability and maintainability
Enforced by static analysis tools