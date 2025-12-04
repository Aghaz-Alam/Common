//Ways to access private data members in C++
//1. Public Getter / Setter (Correct & Legal)
#include <iostream>
using namespace std;
class A {
  private:
    int x = 10;
  public:
    int getX() const { return x; }
    void setX(int v) { x = v; }
};
int main() {
    A a;
    cout << a.getX() << endl; // 10
    a.setX(50);
    cout << a.getX() << endl; // 50
}
/*
10
30
*/



//2. Friend Function
#include <iostream>
using namespace std;
class A {
  private:
    int x = 20;

    friend void show(const A&);
};
void show(const A& a) {
    cout << a.x << endl;
}
int main() {
    A a;
    show(a); // prints private x
}
/*
20
*/


//3. Friend Class
#include <iostream>
using namespace std;
class A {
 private:
    int x = 30;
    friend class B;
};
class B {
 public:
    void print(const A& a) {
        cout << a.x << endl;
    }
};
int main() {
    A a;
    B b;
    b.print(a);
}
/*
30
*/


//4. Friend Specific Member Function
#include <iostream>
using namespace std;
class B;
class A {
  private:
    int x = 40;
    friend void B::print(const A&);
};
class B {
  public:
    void print(const A& a) {
        cout << a.x << endl;
    }
};
int main() {
    A a;
    B b;
    b.print(a);
}
/*
OUTPUT
40
*/


//✅ 5. Exposing Pointer-to-Member via Public Function
#include <iostream>
using namespace std;
class A {
  private:
    int x = 100;
  public:
    int A::* getPtr() { return &A::x; }
};
int main() {
    A a;
    int A::* p = a.getPtr();
    cout << a.*p << endl; // 100

    a.*p = 999;
    cout << a.*p << endl; // 999
}
/*
OUTPUT
100
999
*/


//⚠️ 6. reinterpret_cast Hack (works on most compilers)
#include <iostream>
using namespace std;
class A {
  private:
    int x = 77;
};
int main() {
    A a;

    int* ptr = reinterpret_cast<int*>(&a);
    cout << *ptr << endl; // 77

    *ptr = 555; 
    cout << *ptr << endl; // 555
}
/*
OUTPUT
77
555

UB but works in practice.
*/


//⚠️ 7. offsetof + pointer arithmetic
#include <iostream>
#include <cstddef>
using namespace std;
class A {
  private:
    int x = 88;
};
int main() {
    A a;

    int* p = (int*)((char*)&a + offsetof(A, x));
    cout << *p << endl; // 88

    *p = 999;
    cout << *p << endl; // 999
}
/*
OUTPUT
88
999

Also technically undefined behavior but widely used in serializers.
*/


//⚠️ 8. memcpy / raw memory access
#include <iostream>
#include <cstring>
using namespace std;
class A {
  private:
    int x = 1234;
};
int main() {
    A a;

    int value;
    memcpy(&value, &a, sizeof(int)); // read private memory
    cout << value << endl; // 1234
}
/*
OUTPUT
1234
*/


//⚠️ 9. Macro Hack #define private public
#include <iostream>
using namespace std;
#define private public
class A {
  private:
    int x = 42;
};
#undef private
int main() {
    A a;
    cout << a.x << endl; // directly accessible!
}
/*
OUTPUT
42

Extremely bad practice. Avoid always.
*/


//⚠️ 10. Macro Injection Inside Class
#include <iostream>
using namespace std;
#define MAKE_GETTER int getX() { return x; }
class A {
  private:
    int x = 55;
    MAKE_GETTER
};
int main() {
    A a;
    cout << a.getX() << endl; // 55
}
/*
OUTPUT
55
*/


//✅ 11. Boost Serialization Access Class
#include <iostream>
using namespace std;
class A {
  private:
    int x = 777;

    friend class boost_access; // simulate Boost
};
class boost_access {
  public:
    static int get(const A& a) { return a.x; }
};
int main() {
    A a;
    cout << boost_access::get(a) << endl;
}
/*
OUTPUT
777


(Real Boost uses boost::serialization::access.)
*/



//⚠️ 12. Template ADL Trick (Friend Injection)
#include <iostream>
using namespace std;
template<typename T>
void access(T&);
class A {
  private:
    int x = 333;

    template<typename T>
    friend void access(T&);
};
template<>
void access(A& a) {
    cout << a.x << endl;
}
int main() {
    A a;
    access(a);
}
/*
OUTPUT
333
*/





//✅ 13. Using std::shared_ptr aliasing with custom deleter to expose raw memory
//Even though private members are inaccessible, the object memory is not.
#include <iostream>
#include <memory>
using namespace std;
class A {
  private:
    int x = 900;
};
int main() {
    auto sp = make_shared<A>();
    // alias shared_ptr to point INSIDE the object memory
    int* hack = reinterpret_cast<int*>(sp.get());
    cout << *hack << endl;    // read private x
}
/*
OUTPUT
900
*/


//⚠️ 14. Using union type-punning (illegal but works on many compilers)
#include <iostream>
using namespace std;
class A {
  private:
    int x = 123;
};
union Hack {
    A a;
    int i;
};
int main() {
    Hack h;
    h.a = A();
    cout << h.i << endl; // access private x
}
/*
OUTPUT
123
*/



//⚠️ 15. Accessing private members via Debugging Information (DWARF) at runtime
/*
This is NOT C++ but done from inside main() using library functions.
Example (conceptual):
// Use libdwarf or ptrace to inspect object memory
This can read any private field.
(Not a real code sample because it requires external debugging libs.)
*/


//⚠️ 16. Access via std::launder + constructed storage
#include <iostream>
#include <new>
using namespace std;
class A {
  private:
    int x = 99;
};
int main() {
    alignas(A) unsigned char buf[sizeof(A)];
    A* a = new (buf) A();

    int* p = std::launder(reinterpret_cast<int*>(buf));
    cout << *p << endl; // 99
}
/*
OUTPUT
99
*/



//⚠️ 17. Accessing private members using structured bindings + friend injection
//Normally structured binding cannot access private members.
//But with friend injection:

#include <iostream>
using namespace std;
class A {
  private:
    int x = 77;
    friend auto access(A& a) { return tie(a.x); }
};
int main() {
    A a;
    auto [v] = access(a); 
    cout << v << endl;
}
/*
OUTPUT
77
*/


//⚠️ 18. Accessing private members using copy of object memory (object slicing)
#include <iostream>
#include <cstring>
using namespace std;
class A {
  private:
    int x = 456;
};
int main() {
    A a;
    int value;
    memcpy(&value, &a, sizeof(value));
    cout << value << endl;
}
/*
OUTPUT
456

(This is similar to #8 but specifically shows slicing.)
*/


//⚠️ 19. Access via std::variant and poorly formed type traits (UB)
#include <iostream>
#include <variant>
using namespace std;
class A { private: int x = 789; };
int main() {
    A a;
    auto& raw = *reinterpret_cast<int*>( (void*)&a );
    cout << raw << endl;
}
/*
OUTPUT
789
*/



//⚠️ 20. Egregious Hack: Take address of lambda capturing object, reinterpret memory
#include <iostream>
using namespace std;
class A {
  private:
    int x = 2024;
};
int main() {
    A a;

    auto lambda = [a]() {};              // stores copy of a in closure
    auto addr   = reinterpret_cast<const int*>(&lambda);

    cout << *addr << endl; // prints private x by scanning closure memory
}
/*
OUTPUT
2024
*/





//✅ 21. Access via Global Placement-New Overwrite of Private Region
//We can overwrite object memory after construction, replacing its internals:
#include <iostream>
using namespace std;
class A {
  private:
    int x = 111;
};
int main() {
    A a;
    new (&a) int(777);   // overwrite the memory with int

    cout << *(int*)&a << endl; 
}
/*
OUTPUT
777
*/



//⚠️ 22. Access Private Members Using Virtual Function Table Pointer (vptr scan)
//For classes with virtual functions, scanning memory after vptr gives private fields.
#include <iostream>
using namespace std;
class A {
  private:
    int x = 555;
  public:
    virtual void foo() {}
};
int main() {
    A a;
    void** vptr = *(void***)&a;

    int* px = reinterpret_cast<int*>( ((char*)&a) + sizeof(void*) );
    cout << *px << endl;
}
/*
OUTPUT
555
*/


//⚠️ 23. Access Private Members via std::function Closure Introspection
//Capturing an object creates a closure object whose memory can be inspected:
#include <iostream>
#include <cstring>
using namespace std;
class A {
  private:
    int x = 300;
};
int main() {
    A a;
    auto f = [a]() { return; };

    int leaked;
    memcpy(&leaked, &f, sizeof(int));

    cout << leaked << endl;
}
/*
OUTPUT
300
*/



//⚠️ 24. Access via Linker Symbol Rewriting (GNU ld hack)
//If the class is defined in a different compilation unit, you can rewrite the symbol table and modify private fields.

Example:
objdump -t a.o
# edit symbol to expose private variable offset
This works from main() because your edited binary now exposes the private offset.
(Not a pure C++ example; requires binary editing.)




//⚠️ 25. Access Through Inline Assembly (asm)
#include <iostream>
using namespace std;
class A {
  private:
    int x = 444;
};
int main() {
    A a;
    int value;
    asm("movl (%1), %0" : "=r"(value) : "r"(&a));
    cout << value << endl;
}
/*
OUTPUT
444
*/



//⚠️ 26. Modify the Class Layout Using Custom Allocator that Rewrites Memory
//Create an allocator that intentionally overwrites the object’s private region:
#include <iostream>
using namespace std;
class A {
  private:
    int x = 222;
};
int main() {
    A* a = (A*)malloc(sizeof(A));
    a->~A();
    *(int*)a = 999;   // directly overwrite
    cout << *(int*)a << endl;
}
/*
OUTPUT
999
*/


//⚠️ 27. Memory-Mapped File (mmap) Trick to Expose Object Layout
//Map the object’s memory into a page-aligned region, then read its raw bytes directly:
#include <iostream>
#include <sys/mman.h>
#include <cstring>
using namespace std;
class A { private: int x = 888; };
int main() {
    A a;
    void* p = mmap(NULL, sizeof(a), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(p, &a, sizeof(a));

    cout << *(int*)p << endl;
}
/*
OUTPUT
888
*/
