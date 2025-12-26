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