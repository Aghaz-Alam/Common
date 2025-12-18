//Function Objec (functor)
//*
#include<iostream>
using namespace std;
class Test{
   public:
    int operator()(int val){
        return val*val;
    }
};
int main(){
    Test t;
    cout<<t(10)<<endl;
  return 0;
}
/*
100
*/



//1️⃣ Functor with internal state

//Unlike function pointers, functors can store data.
/*
#include <iostream>
using namespace std;
class Multiplier {
    int factor;
  public:
    Multiplier(int f) : factor(f) {}
    int operator()(int x) {
        return x * factor;
    }
};

int main() {
    Multiplier m2(2);
    Multiplier m5(5);

    cout << m2(10) << endl; // 20
    cout << m5(10) << endl; // 50
}
/*
20
50
*/



//2️⃣ Functor as callback
/*
#include <iostream>
using namespace std;
class Add {
  public:
    int operator()(int a, int b) {
        return a + b;
    }
};

void compute(int x, int y, Add op) {
    cout << op(x, y) << endl;
}

int main() {
    Add add;
    compute(3, 4, add);
}
/*
7
*/



//3️⃣ Functor vs function pointer (side by side)
/*
#include <iostream>
using namespace std;

// Functor
class Square {
  public:
    int operator()(int x) {
        return x * x;
    }
};

// Function
int square(int x) {
    return x * x;
}

int main() {
    Square f;
    int (*fp)(int) = square;

    cout << f(5) << endl;   // functor
    cout << fp(5) << endl;  // function pointer
}
/*
25 
25

📌 Functor can hold state, function pointer cannot.
*/


//4️⃣ Functor used in STL (sort comparator)
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Descending {
  public:
    bool operator()(int a, int b) {
        return a > b;
    }
};

int main() {
    vector<int> v = {3, 1, 4, 2};

    sort(v.begin(), v.end(), Descending());

    for (int x : v)
        cout << x << " ";
}
/*
Output
4 3 2 1
*/



//Ascending
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Ascending {
  public:
    bool operator()(int a, int b) {
        return a < b;
    }
};

int main() {
    vector<int> v = {3, 1, 4, 2};

    sort(v.begin(), v.end(), Ascending());

    for (int x : v)
        cout << x << " ";
}
/*
Output
1 2 3 4
*/


// 5️⃣ Functor with const operator()
// Best practice for STL algorithms
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class IsEven {
  public:
    bool operator()(int x) const {   // ✔ const call operator
        return x % 2 == 0;
    }
};

int main() {
    vector<int> v{1, 2, 3, 4, 5, 6};

    int cnt = count_if(v.begin(), v.end(), IsEven());
    cout << "Even count = " << cnt << endl;
}
/*
Even count = 3
*/




// 5️⃣ Functor with const operator()
// Best practice for STL algorithms
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class IsEven {
  public:
    bool operator()(int x) const {   // ✔ const call operator
        return x % 2 == 0;
    }
};

class IsOdd {
  public:
    bool operator()(int x) const {   // ✔ const call operator
        return x % 2 == 1;
    }
};

int main() {
    vector<int> v{1, 2, 3, 4, 5, 6, 7};

    int cntEven = count_if(v.begin(), v.end(), IsEven());
    cout << "Even count = " << cntEven << endl;
    
    
    int cntOdd = count_if(v.begin(), v.end(), IsOdd());
    cout << "Odd count = " << cntOdd << endl;
}
/*
Even count = 3
*/



//6️⃣ Template functor (generic)
/*
#include <iostream>
using namespace std;
template<typename T>
class MaxValue {
  public:
    T operator()(T a, T b) {
        return (a > b) ? a : b;
    }
};

int main() {
    MaxValue<int> mi;
    MaxValue<double> md;

    cout << mi(3, 7) << endl;
    cout << md(4.5, 2.3) << endl;
}
/*
7
4.5
*/



//7️⃣ Functor with overloaded operator()
/*
#include <iostream>
using namespace std;
class Printer {
  public:
    void operator()(int x) {
        cout << "int: " << x << endl;
    }
    void operator()(double x) {
        cout << "double: " << x << endl;
    }
};
int main() {
    Printer p;
    p(10);
    p(3.14);
}
/*
int: 10
double: 3.14
*/



//8️⃣ Functor used like strategy pattern
/*
#include <iostream>
using namespace std;

class Add {
  public:
    int operator()(int a, int b) { return a + b; }
};

class Multiply {
  public:
    int operator()(int a, int b) { return a * b; }
};

void execute(int x, int y, auto op) {
    cout << op(x, y) << endl;
}

int main() {
    execute(3, 4, Add());
    execute(3, 4, Multiply());
}
/*
7
12
*/


//9️⃣ Functor vs Lambda (equivalent)
/*
#include <iostream>
using namespace std;
class Square {
  public:
    int operator()(int x) {
        return x * x;
    }
};
int main() {
    Square f;
    auto lambda = [](int x) { return x * x; };

    cout << f(6) << endl;
    cout << lambda(6) << endl;
}
/*
36
36

📌 Lambda = compiler-generated functor
*/





//🔟 Real-world logging functor
/*
#include <iostream>
using namespace std;
class Logger {
  public:
    void operator()(const string& msg) const {
        cout << "[LOG] " << msg << endl;
    }
};

int main() {
    Logger log;
    log("Application started");
    log("Processing data");
}
/*
[LOG] Application started
[LOG] Processing data
*/


