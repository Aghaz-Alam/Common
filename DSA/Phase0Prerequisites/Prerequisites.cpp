



1️⃣ Variables, Loops, Conditions
📌 Notes
Variables store data
Loops repeat logic
Conditions control decision flow
Foundation of all algorithms

✅ Code
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    int sum = 0;

    for(int i = 1; i <= n; i++) {
        if(i % 2 == 0) {
            sum += i;
        }
    }

    cout << "Sum of even numbers: " << sum << endl;
    return 0;
}
/*
🖥 Output
Sum of even numbers: 6
*/



2️⃣ Functions
📌 Notes
Break logic into reusable blocks
Improves readability & testing
Pass values or references

✅ Code
#include <iostream>
using namespace std;
int add(int a, int b) {
    return a + b;
}

int main() {
    cout << "Sum: " << add(10, 20) << endl;
    return 0;
}
/*
🖥 Output
Sum: 30
*/




3️⃣ Arrays & Strings
📌 Notes
Arrays store contiguous elements
Strings are character arrays
Index-based access (0-based)

✅ Code
#include <iostream>
#include <string>
using namespace std;
int main() {
    int arr[5] = {1,2,3,4,5};
    string name = "C++";

    for(int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }

    cout << "\nLanguage: " << name << endl;
    return 0;
}
/*
🖥 Output
1 2 3 4 5
Language: C++
*/




4️⃣ Pointers & References 🔑 (VERY IMPORTANT)
📌 Notes
Pointer stores address
Reference is an alias
Core for linked lists, trees, memory

✅ Code
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int* ptr = &x;
    int& ref = x;

    *ptr = 20;
    ref = 30;

    cout << "x: " << x << endl;
    return 0;
}
/*
🖥 Output
x: 30
*/



5️⃣ struct
📌 Notes
Groups different data types
Used in competitive programming
Lightweight data containers

✅ Code
#include <iostream>
using namespace std;

struct Student {
    int id;
    float marks;
};

int main() {
    Student s = {101, 89.5};
    cout << s.id << " " << s.marks << endl;
    return 0;
}
/*
🖥 Output
101 89.5
*/




6️⃣ class & Basic OOP
📌 Notes
Encapsulation = data + methods
Constructor initializes object
Destructor cleans resources

✅ Code
#include <iostream>
using namespace std;
class Car {
  private:
    int speed;

  public:
    Car(int s) {
        speed = s;
        cout << "Constructor called\n";
    }

    void showSpeed() {
        cout << "Speed: " << speed << endl;
    }

    ~Car() {
        cout << "Destructor called\n";
    }
};

int main() {
    Car c(120);
    c.showSpeed();
    return 0;
}
/*
🖥 Output
Constructor called
Speed: 120
Destructor called
*/




7️⃣ vector (Dynamic Array)
📌 Notes
Resizable array
Preferred over raw arrays
O(1) access

✅ Code
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {10, 20, 30};
    v.push_back(40);

    for(int x : v)
        cout << x << " ";

    return 0;
}
/*
🖥 Output
10 20 30 40
*/



8️⃣ pair
📌 Notes
Stores two related values
Used in maps, graphs, DP

✅ Code
#include <iostream>
#include <utility>
using namespace std;
int main() {
    pair<int, string> p = {1, "One"};
    cout << p.first << " " << p.second << endl;
    return 0;
}
/*
🖥 Output
1 One
*/






9️⃣ auto & const
📌 Notes
auto → compiler deduces type
const → prevents modification
Cleaner & safer code

✅ Code
#include <iostream>
using namespace std;

int main() {
    const int x = 10;
    auto y = 20;

    cout << x << " " << y << endl;
    return 0;
}
/*
🖥 Output
10 20
*/




🔟 Fast I/O (cin / cout)
📌 Notes
Essential for large inputs
Used in competitive programming

✅ Code
#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
/*
🖥 Input
5 7

🖥 Output
12
*/





1️⃣1️⃣ Pass by Reference
📌 Notes
Avoids copying
Enables modification
Critical for performance

✅ Code
#include <iostream>
using namespace std;
void increment(int &x) {
    x++;
}
int main() {
    int a = 10;
    increment(a);
    cout << a << endl;
    return 0;
}
/*
🖥 Output
11
*/






1️⃣ Swap Two Numbers (Value vs Reference)
🔍 Interview checks
Pass by value vs reference
Function behavior


❌ Wrong (Pass by Value)
#include <iostream>
using namespace std;
void swapVal(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}
int main() {
    int x = 5, y = 10;
    swapVal(x, y);
    cout << x << " " << y << endl;
    return 0;
}
/*
🖥 Output
5 10
*/






✅ Correct (Pass by Reference)
#include <iostream>
using namespace std;
void swapRef(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
int main() {
    int x = 5, y = 10;
    swapRef(x, y);
    cout << x << " " << y << endl;
    return 0;
}
/*
🖥 Output
10 5
*/




2️⃣ Reverse an Array (Without STL)
🔍 Interview checks
Indexing
Loop logic
In-place modification

#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4,5};
    int n = 5;

    for(int i = 0; i < n/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
/*
🖥 Output
5 4 3 2 1
*/




3️⃣ Count Frequency of Characters (String)
🔍 Interview checks
Arrays / strings
ASCII knowledge
Optimization thinking

#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "interview";
    int freq[26] = {0};

    for(char c : s) {
        freq[c - 'a']++;
    }

    for(int i = 0; i < 26; i++) {
        if(freq[i] > 0)
            cout << char(i + 'a') << ": " << freq[i] << endl;
    }
    return 0;
}
/*
🖥 Output
i: 2
n: 1
t: 1
e: 2
r: 1
v: 1
w: 1
*/




4️⃣ Pointer Arithmetic
🔍 Interview checks
Pointer basics
Memory traversal

#include <iostream>
using namespace std;

int main() {
    int arr[] = {10,20,30};
    int* p = arr;

    cout << *p << endl;
    p++;
    cout << *p << endl;
    p++;
    cout << *p << endl;

    return 0;
}
/*
🖥 Output
10
20
30
*/












5️⃣ Difference Between struct and class
🔍 Interview checks
Access specifiers
OOP basics

#include <iostream>
using namespace std;
struct A {
    int x;
};
class B {
    int y;
  public:
    B(int v) { y = v; }
    void show() { cout << y << endl; }
};
int main() {
    A a;
    a.x = 10;
    cout << a.x << endl;

    B b(20);
    b.show();
    return 0;
}
/*
🖥 Output
10
20
*/




6️⃣ Find Maximum Using vector
🔍 Interview checks
STL usage
Looping

#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {4, 1, 9, 3};
    int maxVal = v[0];

    for(int x : v) {
        if(x > maxVal)
            maxVal = x;
    }

    cout << maxVal << endl;
    return 0;
}
/*
🖥 Output
9
*/




7️⃣ auto Type Deduction Trap
🔍 Interview checks
Type inference awareness

#include <iostream>
using namespace std;
int main() {
    auto x = 10;
    auto y = 10.5;

    cout << x << endl;
    cout << y << endl;
    return 0;
}
/*
🖥 Output
10
10.5
*/





8️⃣ Constructor & Destructor Order
🔍 Interview checks
Object lifetime
Stack behavior

#include <iostream>
using namespace std;
class Test {
  public:
    Test() { cout << "Constructor\n"; }
    ~Test() { cout << "Destructor\n"; }
};
int main() {
    Test t1;
    Test t2;
    return 0;
}
/*
🖥 Output
Constructor
Constructor
Destructor
Destructor
*/








9️⃣ Pass Array to Function
🔍 Interview checks
Array decay to pointer
Reference behavior

#include <iostream>
using namespace std;

void update(int arr[], int n) {
    arr[0] = 100;
}
int main() {
    int arr[] = {1,2,3};
    update(arr, 3);

    for(int i = 0; i < 3; i++)
        cout << arr[i] << " ";

    return 0;
}
/*
🖥 Output
100 2 3
*/






🔟 Fast I/O Interview Pattern
🔍 Interview checks
Competitive programming readiness

#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int sum = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
    }

    cout << sum << endl;
    return 0;
}
/*
🖥 Input
5
1 2 3 4 5

🖥 Output
15
*/



/*

*/


1️⃣ Swap Without Temporary Variable
Concept Tested
Arithmetic operations
Understanding memory

#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 10;
    
    a = a + b;
    b = a - b;
    a = a - b;
    
    cout << "a: " << a << ", b: " << b << endl;
    return 0;
}
/*
Output
a: 10, b: 5
*/





/*

*/





2️⃣ Pointer to Pointer
Concept Tested

Multi-level pointers

Memory addresses

#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int* p = &x;
    int** pp = &p;

    cout << x << endl;      // value
    cout << *p << endl;     // dereference pointer
    cout << **pp << endl;   // dereference pointer to pointer
    return 0;
}
/*
Output
10
10
10
*/









3️⃣ Vector Operations (STL)
Concept Tested

Dynamic array

Iterators

STL familiarity

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};
    v.push_back(4);
    v.pop_back(); // removes last element

    for(auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    return 0;
}

// Output
// 1 2 3


/*
Output
1 2 3
*/



4️⃣ String Manipulation (STL + Loops)
Concept Tested

Traversal

STL size(), indexing

Reverse without STL

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "hello";

    for(int i = s.size() - 1; i >= 0; i--)
        cout << s[i];
    cout << endl;
    return 0;
}
/*
Output
olleh
*/





5️⃣ Const Pointer vs Pointer to Const
Concept Tested
const placement
Memory protection

#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;

    const int* ptr1 = &x; // pointer to const (cannot modify value)
    int* const ptr2 = &x; // const pointer (cannot change address)

    cout << *ptr1 << " " << *ptr2 << endl;

    // *ptr1 = 15; // error
    // ptr2 = &y;  // error

    return 0;
}
/*
Output
10 10
*/




6️⃣ Class with Static Members
Concept Tested

OOP basics

Memory sharing across objects

#include <iostream>
using namespace std;

class Counter {
public:
    static int count;
    Counter() { count++; }
};

int Counter::count = 0;

int main() {
    Counter c1, c2, c3;
    cout << Counter::count << endl;
    return 0;
}
/*
Output
3
*/





7️⃣ Inline Functions
Concept Tested
Performance optimization
Function replacement in compile-time

#include <iostream>
using namespace std;
inline int square(int x) {
    return x * x;
}
int main() {
    cout << square(5) << endl;
    return 0;
}
/*
Output
25
*/



8️⃣ Dynamic Memory Allocation
Concept Tested
new and delete
Heap allocation

#include <iostream>
using namespace std;
int main() {
    int* ptr = new int(100);
    cout << *ptr << endl;
    delete ptr;
    return 0;
}
/*
Output
100
*/




9️⃣ Array Passing by Reference (Fixed Size)
Concept Tested
Prevents decay to pointer
Compile-time size knowledge

#include <iostream>
using namespace std;

void printArray(int (&arr)[5]) { // reference to array of size 5
    for(int x : arr)
        cout << x << " ";
    cout << endl;
}

int main() {
    int arr[5] = {1,2,3,4,5};
    printArray(arr);
    return 0;
}
/*
Output
1 2 3 4 5
*/




10️⃣ Ternary Operator & Short-Circuit
Concept Tested
Conditional logic
Compact expressions

#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;
    int maxVal = (x > y) ? x : y;
    cout << "Max: " << maxVal << endl;
    return 0;
}
/*
Output
Max: 20
*/




1️⃣ Predict the Output (Scope & Lifetime)
🔍 Tests
Variable scope
Shadowing

#include <iostream>
using namespace std;

int x = 100;

int main() {
    int x = 10;
    {
        int x = 5;
        cout << x << endl;
    }
    cout << x << endl;
    return 0;
}
/*
🖥 Output
5
10

👉 Global x is hidden by local x
*/




2️⃣ Reference Must Be Initialized
🔍 Tests
Reference rules

#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int &ref = a;

    ref = 20;
    cout << a << endl;
    return 0;
}
/*
🖥 Output
20

📌 Interview rule:
Reference cannot be null and cannot be reassigned.
*/




3️⃣ Pointer vs Reference (Difference Demo)
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;

    int* p = &a;
    int& r = a;

    p = &b;   // allowed
    // r = b; // modifies a, not rebinding

    cout << *p << " " << r << endl;
    return 0;
}
/*
🖥 Output
20 10
*/







4️⃣ Array Size Trick Interviewers Love
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1,2,3,4,5};

    cout << sizeof(arr) << endl;
    cout << sizeof(arr)/sizeof(arr[0]) << endl;
    return 0;
}
/*
🖥 Output (Platform dependent)
20
5

📌 Why?
sizeof(int) = 4 bytes
*/








5️⃣ sizeof Pointer vs Array
#include <iostream>
using namespace std;

void fun(int arr[]) {
    cout << sizeof(arr) << endl;
}

int main() {
    int arr[5];
    cout << sizeof(arr) << endl;
    fun(arr);
    return 0;
}
/*
🖥 Output (64-bit system)
20
8

📌 Key interview concept:
Arrays decay to pointers when passed to functions.
*/






6️⃣ Const in Function Parameters (Very Common)
#include <iostream>
using namespace std;

void print(const int& x) {
    // x = 10; // ERROR
    cout << x << endl;
}

int main() {
    int a = 5;
    print(a);
    return 0;
}
/*
🖥 Output
5

👉 Improves safety + performance
*/






7️⃣ Default Function Arguments
#include <iostream>
using namespace std;

void greet(string name = "Guest") {
    cout << "Hello " << name << endl;
}

int main() {
    greet();
    greet("Aman");
    return 0;
}
/*
🖥 Output
Hello Guest
Hello Aman
*/







8️⃣ Function Overloading
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int main() {
    cout << add(2,3) << endl;
    cout << add(2.5,3.5) << endl;
    return 0;
}
/*
🖥 Output
5
6

📌 Compile-time polymorphism
*/




9️⃣ Static Local Variable (Favourite Interview Question)
#include <iostream>
using namespace std;

void counter() {
    static int count = 0;
    count++;
    cout << count << endl;
}

int main() {
    counter();
    counter();
    counter();
    return 0;
}
/*
🖥 Output
1
2
3

📌 Value persists across function calls.
*/




🔟 Vector Capacity vs Size
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;

    v.push_back(10);
    v.push_back(20);

    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    return 0;
}
/*
🖥 Output (capacity may vary)
Size: 2
Capacity: 2

📌 Capacity grows exponentially
*/





1️⃣1️⃣ Range-Based Loop (Interview Expectation)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3};

    for(int &x : v) {
        x *= 2;
    }

    for(int x : v)
        cout << x << " ";
    return 0;
}
/*
🖥 Output
2 4 6
*/




1️⃣2️⃣ new[] vs delete[] (Memory Safety)
#include <iostream>
using namespace std;

int main() {
    int* arr = new int[3]{1,2,3};

    for(int i = 0; i < 3; i++)
        cout << arr[i] << " ";

    delete[] arr;
    return 0;
}
/*
🖥 Output
1 2 3


📌 Interview rule:
new[] → delete[]
new → delete
*/



1️⃣3️⃣ Why using namespace std; is Avoided (Concept)
#include <iostream>
int main() {
    std::cout << "Hello C++" << std::endl;
    return 0;
}
/*
📌 Avoids name conflicts in large projects.
*/




1️⃣ Lvalue vs Rvalue (VERY IMPORTANT)
🔍 Interview checks
Understanding of expressions
Foundation for move semantics

📌 Concept
lvalue → has memory address
rvalue → temporary value

#include <iostream>
using namespace std;

int main() {
    int a = 10;   // a is lvalue
    int b = a;    // a used as rvalue

    // 10 = a;    // ERROR (rvalue on left)

    cout << a << " " << b << endl;
    return 0;
}
/*
🖥 Output
10 10
*/





2️⃣ Rvalue References (&&) – Intro
🔍 Interview checks
Modern C++ awareness
Move semantics readiness

#include <iostream>
using namespace std;

void show(int& x) {
    cout << "Lvalue reference\n";
}

void show(int&& x) {
    cout << "Rvalue reference\n";
}

int main() {
    int a = 10;
    show(a);
    show(20);
    return 0;
}
/*
🖥 Output
Lvalue reference
Rvalue reference
*/


//Advanced concepts on perfect forwarding
#include <iostream>
#include<utility>
using namespace std;

void show(int& x) {
    cout << "Lvalue reference: "<<x<<endl;
}

void show(int&& x) {
    cout << "Rvalue reference: "<<x<<endl;
}
/* 
//Methode: 1 Normal Template
template<typename T>
void Test(T&& val){
    show(std::forward<T>(val));
}
*/

//Methode: 2 Variadic Template
template<typename... Args>
void Test(Args&&... args){
    show(std::forward<Args>(args)...);
}


int main() {
    int a = 10;
    Test(a);
    Test(20);
    return 0;
}
/*
🖥 Output
Lvalue reference: 10
Rvalue reference: 20
*/



3️⃣ Move Semantics (Basic)
🔍 Interview checks
Performance optimization
Copy vs move

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1 = {1,2,3};
    vector<int> v2 = move(v1);

    cout << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;
    return 0;
}
/*
🖥 Output
v1 size: 0
v2 size: 3

📌 Ownership transferred, no deep copy.
*/






4️⃣ Rule of 3 (Classic Interview Favorite)
🔍 Interview checks
Memory management
Object lifecycle

#include <iostream>
using namespace std;
class Test {
    int val;
    int* ptr;

  public:
    // Constructor
    Test(int x) : val(x), ptr(new int(x * 10)) {}

    // Copy Constructor (deep copy)
    Test(const Test& t) : val(t.val), ptr(new int(*t.ptr)) {}

    // Copy Assignment Operator (deep copy)
    Test& operator=(const Test& t) {
        if (this != &t) {
            delete ptr;
            val = t.val;
            ptr = new int(*t.ptr);
        }
        return *this;
    }

    // Destructor
    ~Test() {
        delete ptr;
    }

    void show() const {
        cout << val << endl;
        if (ptr)
            cout << *ptr << endl;
    }
};
int main() {
    Test t1(10);
    Test t2 = t1;
    t2.show();
    return 0;
}
/* 
10
100
 */




5️⃣ Rule of 5 (Modern Extension)
📌 Concept
If class manages resources, define:
Destructor
Copy constructor
Copy assignment
Move constructor
Move assignment

#include <iostream>
using namespace std;
class Test {
    int val;     // normal variable
    int* ptr;    // heap resource

  public:
    // 1️⃣ Constructor
    Test(int x) : val(x), ptr(new int(x * 10)) {
        cout << "Constructor\n";
    }

    // 2️⃣ Copy Constructor
    Test(const Test& t) : val(t.val), ptr(new int(*t.ptr)) {
        cout << "Copy Constructor\n";
    }

    // 3️⃣ Copy Assignment Operator
    Test& operator=(const Test& t) {
        cout << "Copy Assignment\n";
        if (this != &t) {
            delete ptr;
            val = t.val;
            ptr = new int(*t.ptr);
        }
        return *this;
    }

    // 4️⃣ Move Constructor
    Test(Test&& t) noexcept : val(t.val), ptr(t.ptr) {
        cout << "Move Constructor\n";
        t.ptr = nullptr;   // important!
    }

    // 5️⃣ Move Assignment Operator
    Test& operator=(Test&& t) noexcept {
        cout << "Move Assignment\n";
        if (this != &t) {
            delete ptr;
            val = t.val;
            ptr = t.ptr;
            t.ptr = nullptr;
        }
        return *this;
    }

    // Destructor
    ~Test() {
        delete ptr;
        cout << "Destructor\n";
    }

    void show() const {
        cout << val << endl;
        if (ptr)
            cout << *ptr << endl;
    }
};

int main() {
    Test t1(10);          // Constructor
    Test t2 = t1;         // Copy Constructor

    Test t3(20);
    t3 = t1;              // Copy Assignment

    Test t4 = move(t1);   // Move Constructor

    Test t5(30);
    t5 = move(t3);        // Move Assignment

    t2.show();
    t4.show();
    t5.show();

    return 0;
}
/* 
Constructor
Copy Constructor
Constructor
Copy Assignment
Move Constructor
Constructor
Move Assignment
10
100
10
100
10
100
Destructor
Destructor
Destructor
Destructor
Destructor
 */






6️⃣ Shallow Copy vs Deep Copy
🔍 Interview checks
Pointer understanding

#include <iostream>
using namespace std;

class Demo {
 public:
    int* x;
    Demo(int v) {
        x = new int(v);
    }
};

int main() {
    Demo d1(10);
    Demo d2 = d1;   // shallow copy

    *d2.x = 20;

    cout << *d1.x << endl;
    return 0;
}
/*
🖥 Output
20

📌 Both objects share same memory → dangerous
*/







7️⃣ explicit Keyword
🔍 Interview checks
Implicit conversion control

#include <iostream>
using namespace std;

class Test {
  public:
    explicit Test(int x) {
        cout << x << endl;
    }
};

int main() {
    Test t1(10);
    // Test t2 = 20; // ERROR due to explicit
    return 0;
}
/*
🖥 Output
10
*/







8️⃣ mutable Keyword
🔍 Interview checks
const correctness depth

#include <iostream>
using namespace std;

class Demo {
  public:
    mutable int count = 0;

    void increment() const {
        count++;
    }
};

int main() {
    const Demo d;
    d.increment();
    cout << d.count << endl;
    return 0;
}
/*
🖥 Output
1
*/








9️⃣ constexpr vs const
🔍 Interview checks
Compile-time vs runtime

#include <iostream>
using namespace std;

constexpr int square(int x) {
    return x * x;
}
int main() {
    //compile-time
    constexpr int val = square(5);
    cout << val << endl;            //Evaluation happens at compile time

    //run-time
    int res = 5;
    cout<<square(res)<<endl;        //Evaluation happens at run time
    return 0;
}
/*
🖥 Output
25
25

📌 The function can be evaluated at compile time, if the arguments are compile-time constants.

Explanation:
- square(5) is evaluated at compile time because the argument is a compile-time constant.
- square(res) is evaluated at run time because res is a normal variable.
- constexpr means the function CAN be evaluated at compile time when possible.
*/


/*=====================================================================================*/
1️⃣ const vs constexpr 
🔹 const
Value cannot be modified
May be known at runtime or compile-time
Used for read-only variables
const int x = 10;   // may or may not be compile-time

🔹 constexpr
Value must be known at compile-time
Used for performance + safety
Evaluated during compilation if possible
constexpr int y = 10; // always compile-time

📌 Example
#include <iostream>
using namespace std;

int getValue() { return 10; }

int main() {
    const int a = getValue();      // runtime
    constexpr int b = 10;          // compile-time

    cout << a << " " << b << endl;
}
/*
🖥 Output
10 10
*/




2️⃣ constexpr Constructors (ADVANCED)
📌 Rule
Constructor must be simple
No dynamic allocation
Enables compile-time object creation

✅ Example
#include <iostream>
using namespace std;
class Point {
  public:
    int x, y;

    constexpr Point(int a, int b) : x(a), y(b) {}
};
int main() {
    constexpr Point p(3, 4);
    cout << p.x << " " << p.y << endl;
}
/*
🖥 Output
3 4

📌 Interview Note
Used in embedded systems, math libraries, compile-time geometry
*/





3️⃣ constexpr with Arrays & Templates
🔹 Array Size (VERY COMMON)
constexpr int size = 5;
int arr[size];   // valid


❌ This may fail:
const int size = getValue(); // runtime
🔹 constexpr + Template (DSA GOLD)
#include <iostream>
using namespace std;
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};
int main() {
    cout << Factorial<5>::value << endl;
}
/*
🖥 Output
120

📌 Used in:
Competitive programming
Compile-time optimizations
Metaprogramming
*/



4️⃣ REAL DSA USE OF constexpr
🔹 Mod, limits, directions
constexpr int MOD = 1e9 + 7;
constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

🔹 Why interviewers like this?
✔ No runtime cost
✔ Prevents accidental modification
✔ Cleaner code
/*=====================================================================================*/




🔟 Lambda Expressions (Basic)
🔍 Interview checks
STL readiness
Functional programming

#include <iostream>
using namespace std;

int main() {
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << add(3, 4) << endl;
    return 0;
}
/*
🖥 Output
7
*/







1️⃣1️⃣ Capture Clause in Lambda
#include <iostream>
using namespace std;

int main() {
    int x = 10;

    auto lambda = [x]() {
        cout << x << endl;
    };

    lambda();
    return 0;
}
/*
🖥 Output
10
*/





1️⃣2️⃣ nullptr vs NULL
🔍 Interview checks
Type safety

#include <iostream>
using namespace std;

void fun(int* p) {
    if(p == nullptr)
        cout << "Null pointer\n";
}

int main() {
    fun(nullptr);
    return 0;
}
/*
🖥 Output
Null pointer
*/



/*==========================================================================================*/

1️⃣ What is NULL?
📌 Definition
NULL is a macro

Traditionally defined as:
#define NULL 0
or
#define NULL ((void*)0)   // in C

📌 Meaning
Just integer zero

❌ Not type-safe
Exists mainly for C compatibility




2️⃣ What is nullptr?
📌 Definition
Introduced in C++11
nullptr is a keyword
Has its own type: std::nullptr_t

📌 Meaning
Represents only a null pointer

✅ Type-safe
Cannot convert to integers accidentally

3️⃣ WHY nullptr WAS INTRODUCED (Interview MUST)
Problem with NULL
#include <iostream>
using namespace std;
void fun(int x) {
    cout << "Integer version\n";
}
void fun(int* p) {
    cout << "Pointer version\n";
}
int main() {
    fun(NULL);
    return 0;
}

❌ Output
Integer version

❌ Why this is WRONG
NULL → treated as 0
0 matches int, not int*
Pointer overload is NOT called


4️⃣ SAME CODE USING nullptr (Correct Way)
#include <iostream>
using namespace std;
void fun(int x) {
    cout << "Integer version\n";
}
void fun(int* p) {
    cout << "Pointer version\n";
}
int main() {
    fun(nullptr);
    return 0;
}

✅ Output
Pointer version

✅ Why this is CORRECT
nullptr has pointer type
Cannot convert to int
Correct overload chosen



5️⃣ Another Dangerous Case with NULL
#include <iostream>
using namespace std;
int main() {
    int* p = NULL;
    if (p == 0)
        cout << "Null\n";
    return 0;
}
⚠ This compiles, but:
0 is integer, not pointer
Confusing and unsafe



6️⃣ Same Code with nullptr (BEST PRACTICE)
#include <iostream>
using namespace std;
int main() {
    int* p = nullptr;
    if (p == nullptr)
        cout << "Null\n";
    return 0;
}
✅ Output
Null

7️⃣ Template & Generic Code (IMPORTANT)
❌ Using NULL in Templates
template<typename T>
void check(T val) {
    if (val == NULL)
        cout << "NULL\n";
}

🚫 This is unsafe and may break.


✅ Using nullptr in Templates
#include <iostream>
using namespace std;
template<typename T>
void check(T val) {
    if (val == nullptr)
        cout << "nullptr\n";
}
int main() {
    int* p = nullptr;
    check(p);
    return 0;
}

Output
nullptr



8️⃣ WHEN TO USE WHAT (VERY IMPORTANT)
✅ Use nullptr when:
✔ Working in C++ (C++11 and later)
✔ Writing modern C++ code
✔ Using function overloading
✔ Writing templates / generic code
✔ Comparing or initializing pointers

int* p = nullptr;
fun(nullptr);

⚠ Use NULL only when:
✔ Maintaining legacy C code
✔ Interfacing with old C libraries
✔ Writing code that must compile in C and C++

int* p = NULL;   // Legacy code only

9️⃣ INTERVIEW ONE-LINER (MEMORIZE THIS)
NULL is an integer constant, not type-safe; nullptr is a keyword representing a null pointer and is type-safe. 
Always prefer nullptr in modern C++.

/*==========================================================================================*/



1️⃣3️⃣ Type Casting (C++ Style)
🔍 Interview checks
Safe casting

#include <iostream>
using namespace std;

int main() {
    double x = 10.7;
    int y = static_cast<int>(x);

    cout << y << endl;
    return 0;
}
/*
🖥 Output
10
*/

/*==========================================================================================*/
Type Casting in C++:

1️⃣ C-STYLE TYPE CASTING
📌 Syntax
(type)expression

📌 Example Program
#include <iostream>
using namespace std;
int main() {
    double x = 10.7;

    int y = (int)x;   // C-style casting

    cout << y << endl;
    return 0;
}
/*
🖥 Output
10
*/

⚠ Why C-style cast is DANGEROUS
✔ Performs multiple conversions silently
✔ Removes const
✔ Can reinterpret memory
✔ Hard to detect bugs
✔ Compiler cannot warn properly

📌 Internally, this cast can behave like:
static_cast
const_cast
reinterpret_cast
OR combination of all ❌



2️⃣ C++ STYLE CASTING (SAFE & EXPLICIT)
C++ provides 4 explicit casts.


2.1️⃣ static_cast (MOST COMMON)
📌 Used for:
✔ Primitive type conversion
✔ Related types (upcasting)
✔ Compile-time safe


✅ Example
#include <iostream>
using namespace std;
int main() {
    double x = 10.7;
    int y = static_cast<int>(x);

    cout << y << endl;
    return 0;
}
/*
🖥 Output
10

🔍 Interview Note
Checked at compile-time
Cannot cast unrelated pointers
*/




2.2️⃣ const_cast (REMOVE CONST)
📌 Used for:
✔ Removing const / volatile
✔ Mostly with legacy APIs

⚠ Example
#include <iostream>
using namespace std;
void modify(int* p) {
    *p = 20;
}
int main() {
    const int x = 10;

    int* p = const_cast<int*>(&x);
    modify(p);

    cout << x << endl;
    return 0;
}
/*
🖥 Output (Undefined Behavior)
20  (may vary)

⚠ Interview warning
Modifying truly const data → Undefined Behavior
*/

/*=================================================================================*/
❓ What is const_cast?
📌 Purpose
Add or remove const / volatile
❌ Cannot change type
❌ Cannot make unsafe memory writable

⚠ Golden Rule (MEMORIZE)
Removing const is safe ONLY if the original object was NOT declared const.




1️⃣ ADDING CONSTANTNESS (SAFE)
✅ When used?
To prevent modification
Improve API safety
Very common in interviews

✅ Correct Example: Add const
#include <iostream>
using namespace std;
void print(const int* p) {   // const added
    cout << *p << endl;
}
int main() {
    int x = 10;
    print(&x);              // implicit conversion to const int*
    return 0;
}
/*
🖥 Output
10

📌 Explanation
Non-const → const is always allowed
Ensures function does not modify data
Safe and recommended
*/




2️⃣ REMOVING CONSTANTNESS (SAFE CASE)
✅ Valid ONLY when original object is NON-CONST
✅ Correct Example: Remove const safely
#include <iostream>
using namespace std;

void modify(int* p) {
    *p = 20;
}

int main() {
    int x = 10;                 // NOT const originally

    const int* cp = &x;         // add const
    int* p = const_cast<int*>(cp);  // remove const safely

    modify(p);

    cout << x << endl;
    return 0;
}
/*
🖥 Output
20

📌 Why this is SAFE
✔ Original object (x) is non-const
✔ const was added temporarily
✔ Removing it restores original mutability
*/






3️⃣ REMOVING CONSTANTNESS (UNSAFE ❌)
🚫 WRONG & UNDEFINED BEHAVIOR
#include <iostream>
using namespace std;
void modify(int* p) {
    *p = 20;
}
int main() {
    const int x = 10;          // truly const object

    int* p = const_cast<int*>(&x);
    modify(p);                 // ❌ UB

    cout << x << endl;
    return 0;
}
/*
⚠ Output
20 / 10 / crash / garbage (undefined)

❌ Why this is WRONG
Object is stored in read-only memory
Compiler may optimize assuming immutability
Writing causes Undefined Behavior
*/





4️⃣ LEGIT REAL-WORLD USE CASE (INTERVIEW GOLD)
📌 Legacy API expects non-const pointer
#include <iostream>
using namespace std;
void legacyAPI(int* p) {
    cout << *p << endl;
}
int main() {
    int x = 10;
    const int* cp = &x;

    legacyAPI(const_cast<int*>(cp)); // safe
    return 0;
}
/*
🖥 Output
10

✔ Data not modified
✔ Original object not const
✔ Valid interview example
*/



mutable vs const_cast
🔹 mutable
Allows modification inside const object
Safe & intentional

class Counter {
    mutable int count;
  public:
    Counter() : count(0) {}

    void increment() const {
        count++;   // allowed
    }

    int get() const { return count; }
};
/*
🖥 Output
Safe modification

🔹 const_cast
Removes constness
Can cause Undefined Behavior
*/


/*----------------------------------*/
Const Correctness – INTERVIEW PROBLEMS
❓ Problem 1: Why this fails?
void print(int* p);
int main() {
    const int x = 10;
    print(&x);   // ❌ error
}

✅ Fix
void print(const int* p);




❓ Problem 2: Which is correct?
int* const p;   // const pointer
const int* p;   // pointer to const

✅ Answer
const int* p;   // preferred





❓ Problem 3: Function const correctness
class A {
  public:
    int get() { return x; }  // ❌
};

✅ Correct
int get() const { return x; }

/*------------------------------------*/
🔹 Problem 1: Passing const object to function
❌ Why this FAILS
void print(int* p);
int main() {
    const int x = 10;
    print(&x);   // ❌ error
}

❌ Reason
x is const int
&x → const int*
Cannot convert const int* → int* (would allow modification)


✅ Correct & Complete Code
#include <iostream>
using namespace std;
void print(const int* p) {   // pointer to const
    cout << *p << endl;
}
int main() {
    const int x = 10;
    print(&x);
    return 0;
}
/*
🖥 Output
10

📌 Interview Explanation
Function promises not to modify data
Works for both const and non-const objects
Preferred API design
*/






🔹 Problem 2: int* const vs const int*
🔍 Case 1: int* const (CONST POINTER)
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int y = 20;

    int* const p = &x;   // const pointer

    *p = 15;             // ✅ allowed
    // p = &y;           // ❌ error

    cout << x << endl;
    return 0;
}
/*
🖥 Output
15
*/

🔍 Case 2: const int* (POINTER TO CONST) ✅ PREFERRED
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int y = 20;

    const int* p = &x;   // pointer to const

    // *p = 15;          // ❌ error
    p = &y;              // ✅ allowed

    cout << *p << endl;
    return 0;
}
/*
🖥 Output
20

📌 Interview Conclusion
Prefer const int* because it protects data from accidental modification and supports const correctness.
*/




🔹 Problem 3: Function const correctness in classes
❌ Why this is WRONG
class A {
  public:
    int get() { return x; }  // ❌
};

❌ Cannot be called on const objects
❌ Breaks const correctness

✅ Correct & Complete Code
#include <iostream>
using namespace std;
class A {
    int x;
  public:
    A(int v) : x(v) {}

    int get() const {    // const member function
        return x;
    }
};
int main() {
    const A obj(10);
    cout << obj.get() << endl;
  return 0;
}
/*
🖥 Output
10

📌 Interview Explanation
const after function means:
This function does not modify object state
Allows calling function on const objects
Enables compiler optimizations
*/







/*=================================================================================*/


2.3️⃣ dynamic_cast (RUNTIME CHECK)
📌 Used for:
✔ Polymorphism
✔ Downcasting
✔ Runtime type checking

⚠ Requires:
At least one virtual function

✅ Example
#include <iostream>
using namespace std;
class Base {
  public:
    virtual ~Base() {}
};
class Derived : public Base {};
int main() {
    Base* b = new Derived();

    Derived* d = dynamic_cast<Derived*>(b);

    if (d)
        cout << "Cast successful\n";
    else
        cout << "Cast failed\n";

    delete b;
    return 0;
}
/*
🖥 Output
Cast successful

🔍 Interview Note
Returns nullptr if cast fails
Slight runtime cost
*/




2.4️⃣ reinterpret_cast (MOST DANGEROUS)
📌 Used for:
✔ Low-level memory manipulation
✔ Hardware, OS, drivers


⚠ Example
#include <iostream>
using namespace std;
int main() {
    int x = 65;

    char* c = reinterpret_cast<char*>(&x);

    cout << *c << endl;
    return 0;
}
/*
🖥 Output (System dependent)
A   or garbage


⚠ Interview Warning
No safety checks
Avoid unless absolutely required
*/
/*==========================================================================================*/





1️⃣4️⃣ enum class (Scoped Enum)
#include <iostream>
using namespace std;

enum class Color { Red, Green, Blue };

int main() {
    Color c = Color::Red;
    cout << static_cast<int>(c) << endl;
    return 0;
}
/*
🖥 Output
0
*/






1️⃣ const Placement TRAP (Very Common)
❓ Predict Output
#include <iostream>
using namespace std;
void fun(const int*& p) {
    static int y = 20;
    p = &y;
}
int main() {
    int x = 10;
    const int* p = &x;

    fun(p);
    cout << *p << endl;
}
/*
🖥 Output
20

🔍 Explanation
const int*& → reference to pointer-to-const
Pointer itself is modified
Data remains const
Interviewers test pointer vs data constness
*/
/*================================================*/
1️⃣ const int* const — Double Const Trap
❓ Predict Output
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int y = 20;

    const int* const p = &x;

    // *p = 30;    // ❌ error
    // p = &y;     // ❌ error

    cout << *p << endl;
}
/*
🖥 Output
10

🔍 Explanation
Left const → data is const
Right const → pointer is const
Nothing can be modified
📌 Rule
Read right-to-left: p is a const pointer to const int


//-------------------------------------
1️⃣ LEFT CONST → DATA IS CONST
(const int* p)
📌 Meaning
Pointer can change
Data cannot change

✅ Program Code
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int y = 20;

    const int* p = &x;   // left const → data is const

    // *p = 15;          // ❌ ERROR: data is const
    p = &y;              // ✅ pointer can change

    cout << *p << endl;
    return 0;
}

🖥 Output
20

🔍 Detailed Explanation
const int* p means
👉 p points to a const int
You promise not to modify data through p
But pointer itself is free to point elsewhere

📌 Interview One-liner
Pointer to const is preferred because it protects data from accidental modification.

2️⃣ RIGHT CONST → POINTER IS CONST
(int* const p)
📌 Meaning
Pointer cannot change
Data can change

✅ Program Code
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int y = 20;

    int* const p = &x;   // right const → pointer is const

    *p = 15;             // ✅ data can change
    // p = &y;           // ❌ ERROR: pointer is const

    cout << x << endl;
    return 0;
}

🖥 Output
15

🔍 Detailed Explanation
int* const p means
👉 p is a const pointer to int
Pointer address is fixed
But data at that address is modifiable

📌 Interview One-liner
Const pointer ensures pointer stability, not data protection.




3️⃣ BOTH SIDES CONST (BONUS – VERY COMMON)
(const int* const p)
✅ Program Code
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    const int* const p = &x;

    // *p = 20;   // ❌
    // p = &x;    // ❌

    cout << *p << endl;
    return 0;
}

🖥 Output
10

🔍 Explanation
Pointer cannot change
Data cannot change
Maximum safety




MEMORY TRICK (INTERVIEW GOLD)
👉 Start reading from variable name
const int* p;

p → pointer
*p → int
const int → data is const



🏁 FINAL INTERVIEW VERDICT
Left const protects data, right const protects the pointer. 
Reading declarations from right to left removes all confusion.

*/




2️⃣ const int*& (EXTREMELY TRICKY)
#include <iostream>
using namespace std;
void fun(const int*& p) {
    static int z = 50;
    p = &z;
}
int main() {
    int x = 10;
    const int* p = &x;

    fun(p);
    cout << *p << endl;
}
/*
🖥 Output
50

🔍 Explanation
const int*& → reference to pointer
Pointer changes, not data
Common interview pitfall
*/




3️⃣ int* const& (Compare Carefully)
#include <iostream>
using namespace std;
void fun(int* const& p) {
    *p = 40;      // allowed
    // p = nullptr; // ❌ error
}
int main() {
    int x = 10;
    int* p = &x;

    fun(p);
    cout << x << endl;
}
/*
🖥 Output
40
*/







1️⃣ Reference + const TRAPS (VERY IMPORTANT)
🔹 Trap 1: const int& binding to temporary
❓ Predict Output
#include <iostream>
using namespace std;
int main() {
    const int& r = 10;   // binds to temporary
    cout << r << endl;
}
/*
🖥 Output
10

🔍 Explanation
const reference can bind to temporary
Lifetime of temporary is extended
❌ int& r = 10; → illegal
📌 Interview one-liner
Only const references can bind to temporaries.
*/




🔹 Trap 2: Reference cannot be reseated
#include <iostream>
using namespace std;
int main() {
    int x = 10, y = 20;
    int& r = x;

    r = y;     // assigns value, NOT rebinding
    cout << x << endl;
}
/*
🖥 Output
20

🔍 Explanation
References are aliases
r = y → x = y
Cannot rebind references
*/




🔹 Trap 3: const int& vs int&
#include <iostream>
using namespace std;
void fun(const int& r) {
    // r++;  // ❌ error
}
int main() {
    int x = 10;
    fun(x);
}
/*
🖥 Output
(no output)

📌 Used to avoid copying while preventing modification.
*/




2️⃣ Function Parameter const PUZZLES (INTERVIEW FAVORITE)
🔹 Puzzle 1: Why this fails?
void print(int*& p) {}
int main() {
    int x = 10;
    const int* p = &x;
    // print(p);  // ❌ error
}

❌ Reason
int*& allows modifying pointer to non-const int
const int* cannot convert to int*




🔹 Puzzle 2: Correct version
#include <iostream>
using namespace std;
void print(const int*& p) {
    static int y = 20;
    p = &y;
}
int main() {
    int x = 10;
    const int* p = &x;

    print(p);
    cout << *p << endl;
}
/*
🖥 Output
20

🔍 Explanation
Pointer changes
Data remains const
Extremely common interview trap
*/



🔹 Puzzle 3: Pass-by-value vs pass-by-const-ref
#include <iostream>
using namespace std;
void foo(const int& x) {
    cout << x << endl;
}
int main() {
    foo(10);
}
/*
🖥 Output
10

📌 Why const-ref?
Avoids copy
Accepts literals & temporaries
*/





3️⃣ STL ITERATOR const ISSUES (VERY IMPORTANT)
🔹 Trap 1: iterator vs const_iterator
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3};

    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        *it += 10;
    }

    for(int x : v)
        cout << x << " ";
}
/*
🖥 Output
11 12 13
*/




🔹 Trap 2: Using const_iterator
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3};

    for(vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        // *it += 10;  // ❌ error
        cout << *it << " ";
    }
}
/*
🖥 Output
1 2 3

🔍 Explanation
const_iterator → read-only access
Preferred when not modifying container
*/




🔹 Trap 3: const vector vs iterator type 🔥
#include <iostream>
#include <vector>
using namespace std;
int main() {
    const vector<int> v = {1, 2, 3};

    // vector<int>::iterator it = v.begin(); // ❌ error
    vector<int>::const_iterator it = v.begin(); // ✅

    cout << *it << endl;
}
/*
🖥 Output
1

📌 Rule
Const container → only const_iterators allowed
*/




🔹 Trap 4: auto with iterators (MODERN C++)
#include <iostream>
#include <vector>
using namespace std;
int main() {
    const vector<int> v = {1, 2, 3};

    auto it = v.begin();   // deduced as const_iterator
    cout << *it << endl;
}
/*
🖥 Output
1

📌 auto respects container constness
*/


🔥 INTERVIEW MASTER RULES (SAVE THESE)
📌 Reference
References cannot be reseated
const& binds to temporaries
Use const& to avoid copies

📌 Function Parameters
Prefer const T&
Use T* const& or const T*& carefully
Understand who can change pointer vs data

📌 STL
iterator → read/write
const_iterator → read-only
Const container → only const_iterators

🏁 FINAL INTERVIEW VERDICT
Const correctness with references, function parameters, and STL iterators ensures safety, clarity, 
and better optimization. Most C++ bugs and interview traps come from misunderstanding these rules.
/*================================================*/


2️⃣ mutable + const Function (Logical Constness)
#include <iostream>
using namespace std;
class Cache {
    mutable int hits;
  public:
    Cache() : hits(0) {}

    int getValue() const {
        hits++;
        return 100;
    }

    int getHits() const {
        return hits;
    }
};
int main() {
    const Cache c;
    c.getValue();
    c.getValue();

    cout << c.getHits() << endl;
}
/*
🖥 Output
2

🔍 Concept
✔ mutable allows modification inside const function
✔ Used for caching, logging
✔ Preferred over const_cast
*/






3️⃣ constexpr vs Runtime Evaluation
#include <iostream>
using namespace std;
constexpr int square(int x) {
    return x * x;
}
int main() {
    int a = 5;
    constexpr int b = square(5);
    int c = square(a);

    cout << b << " " << c << endl;
}
/*
🖥 Output
25 25

🔍 Interview Trap
square(5) → compile-time
square(a) → runtime
Same function, different evaluation time
*/





4️⃣ Rule of 5 – Move Constructor Trigger
#include <iostream>
using namespace std;
class Test {
    int* ptr;
  public:
    Test(int x) {
        ptr = new int(x);
    }

    Test(Test&& t) noexcept {
        ptr = t.ptr;
        t.ptr = nullptr;
    }

    ~Test() {
        delete ptr;
    }

    void show() {
        if(ptr) cout << *ptr << endl;
    }
};
int main() {
    Test t1(10);
    Test t2 = std::move(t1);

    t2.show();
}
/*
🖥 Output
10

🔍 Concept
✔ Resource transfer
✔ Prevents deep copy
✔ std::move ≠ move itself
*/




5️⃣ auto TYPE DEDUCTION TRAP
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    int& r = x;

    auto a = r;
    auto& b = r;

    a = 20;
    b = 30;

    cout << x << endl;
}
/*
🖥 Output
30

🔍 Explanation
auto a → copy
auto& b → reference
Interviewers test reference stripping
*/




6️⃣ nullptr Overload Resolution
#include <iostream>
using namespace std;
void fun(int) {
    cout << "int\n";
}
void fun(int*) {
    cout << "pointer\n";
}
int main() {
    fun(nullptr);
}
/*
🖥 Output
pointer

🔍 Concept
✔ nullptr is pointer type
✔ Avoids ambiguity of NULL
*/





7️⃣ sizeof Array vs Pointer TRAP
#include <iostream>
using namespace std;
void fun(int arr[]) {
    cout << sizeof(arr) << endl;
}
int main() {
    int arr[5];
    cout << sizeof(arr) << endl;
    fun(arr);
}
/*
🖥 Output (64-bit)
20
8

🔍 Explanation
Array decays to pointer in function
Classic interview trap
*/




8️⃣ Dangling Reference (Very Tricky)
#include <iostream>
using namespace std;
int& fun() {
    static int x = 10;
    return x;
}
int main() {
    int& r = fun();
    r = 20;
    cout << r << endl;
}
/*
🖥 Output
20

🔍 Why safe?
✔ static lifetime
❌ Without static → UB
*/





9️⃣ explicit Constructor Trap
#include <iostream>
using namespace std;
class Test {
  public:
    explicit Test(int x) {
        cout << x << endl;
    }
};
int main() {
    // Test t = 10;   // ❌ error
    Test t(10);       // ✅
}
/*
🖥 Output
10

🔍 Interview Point
Prevents implicit conversions
Avoids subtle bugs
*/




1️⃣ Lambda Capture const TRAPS
🔹 Trap 1: Value capture is const by default
❓ Predict Output
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    auto lam = [x]() {
        // x += 5;   // ❌ error
        cout << x << endl;
    };

    lam();
}
/*
🖥 Output
10

🔍 Explanation
[x] → capture by value
Lambda call operator is const by default
Captured variables are read-only

📌 Interview One-liner
Value-captured variables are treated as const inside lambda.
*/





🔹 Trap 2: mutable lambda
✅ Correct way to modify value capture
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    auto lam = [x]() mutable {
        x += 5;
        cout << x << endl;
    };

    lam();
    cout << x << endl;
}
/*
🖥 Output
15
10

🔍 Explanation
mutable removes const from lambda call operator
Modifies copy, not original variable
*/




🔹 Trap 3: Reference capture ignores const trap
#include <iostream>
using namespace std;
int main() {
    int x = 10;

    auto lam = [&x]() {
        x += 5;
    };

    lam();
    cout << x << endl;
}
/*
🖥 Output
15

📌 Reference capture allows modification of original variable.
*/




🔹 Trap 4: Mixed capture (= with reference override)
#include <iostream>
using namespace std;
int main() {
    int x = 10, y = 20;

    auto lam = [=, &y]() {
        // x += 5;  // ❌ error
        y += 5;
        cout << x << " " << y << endl;
    };

    lam();
}
/*
🖥 Output
10 25
*/



2️⃣ std::move + const ISSUES (VERY IMPORTANT)
🔹 Key Interview Rule
std::move does NOT move anything — it only casts to rvalue.


🔹 Trap 1: Moving from const object
#include <iostream>
#include <string>
using namespace std;
int main() {
    const string s = "Hello";

    string t = std::move(s);

    cout << t << endl;
}
/*
🖥 Output
Hello

🔍 Explanation
s is const
Move constructor requires non-const rvalue
Copy constructor is used instead

📌 Interview One-liner
You cannot move from a const object.
*/




🔹 Trap 2: const T&& is useless
#include <iostream>
using namespace std;
void foo(const int&& x) {
    // x = 10; // ❌ error
    cout << x << endl;
}

int main() {
    foo(5);
}
/*
🖥 Output
5

📌 const T&& prevents moving → useless in practice
*/




🔹 Trap 3: std::move with vector element
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<string> v = {"one", "two"};

    const string& s = v[0];
    string t = std::move(s);

    cout << t << endl;
}
/*
🖥 Output
one

🔍 Explanation
s is const reference
Move disabled → copy happens
*/




🔹 Trap 4: Correct moving (non-const)
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<string> v = {"one", "two"};

    string s = std::move(v[0]);

    cout << s << endl;
    cout << v[0].empty() << endl;
}
/*
🖥 Output (implementation-dependent)
one
1

📌 Moved-from object is valid but unspecified
*/




🔥 LAMBDA + MOVE COMBINED TRAP (INTERVIEW GOLD)
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "Hello";

    auto lam = [x = std::move(s)]() {
        cout << x << endl;
    };

    cout << s << endl;
    lam();
}
/*
🖥 Output (typical)
(empty)
Hello

📌 init-capture moves ownership into lambda
*/


🧠 INTERVIEW MEMORY RULES (SAVE THESE)
Lambda:
Value capture → const by default
Use mutable to modify
Reference capture modifies original


std::move:
std::move ≠ move
Cannot move from const
Move constructor needs non-const rvalue
const T&& is useless

🏁 FINAL INTERVIEW VERDICT
Most lambda and move bugs come from misunderstanding constness. 
Lambdas are const by default, and std::move only enables moving if the object is non-const.










