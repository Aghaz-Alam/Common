/* --------------------------------------------------------*/
What is a Stack Trace?
What elements/pointers represent the call stack in C/C++?
How stack frames are arranged
A full C++ program that prints its stack trace

/* --------------------------------------------------------- */
What is a Stack Trace?
A stack trace is a list of active function calls showing how the program reached the current point.
A stack trace is a list of active function calls at a specific moment, showing how the program reached that point.

Example stack trace:
#0 crash()
#1 doWork()
#2 process()
#3 main()


It tells you:
Which function you are in
Which functions called it
Execution path at the moment the error happened
So a stack trace = backtrace of function calls.


/* -------------------------------------------------------- */

✔ What pointer represents the call stack?
Two main CPU registers:
Stack Pointer (SP/RSP) → points to top of stack
Frame Pointer (FP/RBP) → points to base of function frame and chains to previous frames
These form a linked list of stack frames, used to reconstruct the stack trace.


What element/pointer represents the call stack?
Every function has a stack frame, and the CPU stores two important registers:

⭐ CPU Registers Used for Stack Representation
✔️ 1. Stack Pointer (SP or RSP)
--> Points to the top of the current stack frame.
--> RSP → current top of stack

✔️ 2. Frame Pointer (FP or RBP)
-->Points to the base of the current function’s stack frame.
--> RBP → base of this functions frame


The frame pointer allows the program to walk BACKWARDS through stack frames:
[Saved old RBP] ← enables navigating to caller frame


How Stack Trace is Obtained?
Stack trace libraries walk frame by frame:

current RBP
    ↓
saved RBP of f2
    ↓
saved RBP of f1
    ↓
saved RBP of main


Each RBP points to the previous frame → forming a linked list of stack frames.


R = 64-bit “Register” (Extended Register)
On 64-bit x86 architecture (x86-64 / AMD64):
All general-purpose registers were extended from 32-bit to 64-bit.
Their names were prefixed with R to indicate 64-bit register.

Thus:
SP → Stack Pointer (32-bit)
ESP → Extended Stack Pointer (32-bit from the old 16-bit SP)
RSP → 64-bit Stack Pointer

And similarly:
BP → Base Pointer (16-bit)
EBP → Extended Base Pointer (32-bit)
RBP → 64-bit Base Pointer


/* --------------------------------------------------------------------*/
Diagram of Stack Frames

Assume calls:

main → f1 → f2 → f3


Stack (grows downward):

HIGH ADDRESSES
+-----------------------------+
| f3 stack frame              |
|  saved RBP (points to f2)   |
|  return address to f2       |
|  local variables            |
+-----------------------------+
| f2 stack frame              |
|  saved RBP (points to f1)   |
|  return address to f1       |
|  local variables            |
+-----------------------------+
| f1 stack frame              |
|  saved RBP (points to main) |
|  return address to main     |
|  local variables            |
+-----------------------------+
| main stack frame            |
+-----------------------------+
LOW ADDRESSES


This linked chain of saved RBP values is what allows stack trace libraries to reconstruct the call stack.

 /*------------------------------------------------------------------- */

 /*
//C++ Program: Print Stack Trace (Modern C++23)
#include <iostream>
#include <stacktrace>
#include <boost/stacktrace.hpp>
using namespace std;
void f3() {
    cout << "=== Stack Trace ===\n";
    cout << std::stacktrace::current() << "\n";
}
void f2() { f3(); }
void f1() { f2(); }
int main() {
    f1();
}
/* 
Output:
0: a.out : f3()
1: a.out : f2()
2: a.out : f1()
3: a.out : main
 */



/* ------------------------------------------------------------ */
//C++ Program Using Linux backtrace() API
//(works on all Linux systems)

#include <execinfo.h>
#include <iostream>
#include <cstdlib>

void printStack() {
    void* buffer[20];

    int size = backtrace(buffer, 20);
    char** symbols = backtrace_symbols(buffer, size);

    std::cout << "=== Stack Trace ===\n";
    for (int i = 0; i < size; ++i) {
        std::cout << symbols[i] << "\n";
    }

    free(symbols);
}

void f3() { printStack(); }
void f2() { f3(); }
void f1() { f2(); }

int main() {
    f1();
}
/*
Output:
./a.out(_Z5f3v+0x15)
./a.out(_Z5f2v+0x9)
./a.out(_Z5f1v+0x9)
./a.out(main+0x12)
./a.out(__libc_start_main+0xf5)
*/


/* ---------------------------------------------------- */
What is a Stack Trace in C++?
A stack trace (or backtrace) is a list of function calls that led to a particular point in the program.

Example of a stack trace:
#0  crash()
#1  processData()
#2  main()

It tells you where the program is and how it got there.
✔ How to get a stack trace in C++
A. C++23 — std::stacktrace (Modern Standard Way)
#include <stacktrace>
#include <iostream>
void f3() {
    std::cout << std::stacktrace::current() << "\n";
}
void f2() { f3(); }
void f1() { f2(); }
int main() {
    f1();
}

Prints:
0: ./a.out : f3()
1: ./a.out : f2()
2: ./a.out : f1()
3: ./a.out : main
...

B. Linux — Using backtrace() (glibc)
#include <execinfo.h>
#include <iostream>
void printTrace() {
    void* buffer[20];
    int size = backtrace(buffer, 20);
    char** symbols = backtrace_symbols(buffer, size);
    for (int i = 0; i < size; ++i)
        std::cout << symbols[i] << "\n";
}

C. Windows — Using CaptureStackBackTrace()
#include <windows.h>
#include <dbghelp.h>
void printStack() {
    void* trace[32];
    USHORT size = CaptureStackBackTrace(0, 32, trace, NULL);
}
/*------------------------------------------------------------*/




//A. 
#include <iostream>
#include <execinfo.h>   // backtrace, backtrace_symbols
#include <cstdlib>      // free
void print_stacktrace() {
    const int max_frames = 64;
    void* frames[max_frames];
    int frame_count = backtrace(frames, max_frames);
    char** symbols = backtrace_symbols(frames, frame_count);
    std::cout << "=== Stack Trace ===\n";
    for (int i = 0; i < frame_count; ++i) {
        std::cout << i << ": " << symbols[i] << "\n";
    }
    free(symbols); // allocated by backtrace_symbols()
}
void f3() {
    print_stacktrace();
}
void f2() { f3(); }
void f1() { f2(); }
int main() {
    f1();
  return 0;
}
/*
=== Stack Trace ===
0: /tmp/VF405Ps2h7/main.o() [0x40118c]
1: /tmp/VF405Ps2h7/main.o() [0x401231]
2: /tmp/VF405Ps2h7/main.o() [0x40123d]
3: /tmp/VF405Ps2h7/main.o() [0x401249]
4: /tmp/VF405Ps2h7/main.o() [0x401255]
5: /lib/x86_64-linux-gnu/libc.so.6(+0x2724a) [0x7b8ec062724a]
6: /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0x85) [0x7b8ec0627305]
7: /tmp/VF405Ps2h7/main.o() [0x4010a1]
*/


//B.
#include <execinfo.h>
#include <iostream>
#include <cstdlib>
void printTrace() {
    void* buffer[20];
    // capture stack addresses
    int size = backtrace(buffer, 20);
    // convert addresses to symbols (function names)
    char** symbols = backtrace_symbols(buffer, size);
    if (!symbols) {
        std::cerr << "Error: backtrace_symbols() failed\n";
        return;
    }
    std::cout << "=== Stack Trace ===\n";
    for (int i = 0; i < size; ++i) {
        std::cout << i << ": " << symbols[i] << "\n";
    }
    free(symbols); // must free!
}
void f3() {
    printTrace();
}
void f2() { f3(); }
void f1() { f2(); }
int main() {
    f1();
   return 0;
}
/*
=== Stack Trace ===
0: /tmp/iEwEvTlbA0/main.o() [0x401185]
1: /tmp/iEwEvTlbA0/main.o() [0x401241]
2: /tmp/iEwEvTlbA0/main.o() [0x40124d]
3: /tmp/iEwEvTlbA0/main.o() [0x401259]
4: /tmp/iEwEvTlbA0/main.o() [0x401265]
5: /lib/x86_64-linux-gnu/libc.so.6(+0x2724a) [0x7ef42c99424a]
6: /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0x85) [0x7ef42c994305]
7: /tmp/iEwEvTlbA0/main.o() [0x4010a1]
*/

//C. 
#include <execinfo.h>
#include <iostream>
#include <cstdlib>
void printStack() {
    void* trace[32];
    int frames = backtrace(trace, 32);
    char** symbols = backtrace_symbols(trace, frames);
    if (!symbols) {
        std::cout << "Failed to get symbols\n";
        return;
    }
    std::cout << "=== Stack Trace ===\n";
    for (int i = 0; i < frames; ++i) {
        std::cout << i << ": " << symbols[i] << "\n";
    }
    free(symbols);
}
void f3() { printStack(); }
void f2() { f3(); }
void f1() { f2(); }
int main() {
    f1();
  return 0;
}
/*
=== Stack Trace ===
0: /tmp/CL9x2XFwnn/main.o() [0x401185]
1: /tmp/CL9x2XFwnn/main.o() [0x401241]
2: /tmp/CL9x2XFwnn/main.o() [0x40124d]
3: /tmp/CL9x2XFwnn/main.o() [0x401259]
4: /tmp/CL9x2XFwnn/main.o() [0x401265]
5: /lib/x86_64-linux-gnu/libc.so.6(+0x2724a) [0x7c7a2b26024a]
6: /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0x85) [0x7c7a2b260305]
7: /tmp/CL9x2XFwnn/main.o() [0x4010a1]
*/




// stacktrace_cpp14.cpp
#include <iostream>
#include <execinfo.h>   // backtrace(), backtrace_symbols()
#include <cstdlib>      // free()
#include <unistd.h>
using namespace std;
void print_stacktrace() {
    const int max_frames = 50;
    void* frames[max_frames];

    int frame_count = backtrace(frames, max_frames);

    // Convert addresses into symbols
    char** symbols = backtrace_symbols(frames, frame_count);

    cout << "=== Stack Trace (C++14) ===\n";
    for (int i = 0; i < frame_count; ++i) {
        cout << i << ": " << symbols[i] << "\n";
    }

    free(symbols); // Must free malloc'ed symbols from glibc
}

void f3() {
    print_stacktrace();
}

void f2() {
    f3();
}

void f1() {
    f2();
}

int main() {
    f1();
    return 0;
}
/* 
=== Stack Trace (C++14) ===
0: ./stacktrace(+0x1225) [0x5a08cccc7225]
1: ./stacktrace(+0x1326) [0x5a08cccc7326]
2: ./stacktrace(+0x1336) [0x5a08cccc7336]
3: ./stacktrace(+0x1346) [0x5a08cccc7346]
4: ./stacktrace(+0x1356) [0x5a08cccc7356]
5: /lib/x86_64-linux-gnu/libc.so.6(+0x2a1ca) [0x713bb2e2a1ca]
6: /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0x8b) [0x713bb2e2a28b]
7: ./stacktrace(+0x1125) [0x5a08cccc7125]
*/