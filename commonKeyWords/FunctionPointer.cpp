
//Function pointer
//*
#include<iostream>
#include<thread>
using namespace std;
int fun(int val){
    return val*val;
}
int main(){
    auto (*f)(int) = fun;
    cout<<f(10)<<endl;
}
/*
100
*/





//1️⃣ Basic function pointer
/*
#include <iostream>
using namespace std;
void greet() {
    cout << "Hello\n";
}

int main() {
    void (*fp)() = greet;   // function pointer
    fp();                   // call via pointer
}
/*
Hello
*/




//2️⃣ Function pointer with parameters
/*
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int (*f)(int, int) = add;
    cout << f(3, 4) << endl;
}
/*
7
*/



//3️⃣ Using typedef (cleaner syntax)
/*
#include <iostream>
using namespace std;

typedef int (*Operation)(int, int);

int multiply(int a, int b) {
    return a * b;
}

int main() {
    Operation op = multiply;
    cout << op(4, 5) << endl;
}
/*
20
*/




//4️⃣ Using using (modern C++)
/*
#include <iostream>
using namespace std;

using Operation = int(*)(int, int);

int subtract(int a, int b) {
    return a - b;
}

int main() {
    Operation op = subtract;
    cout << op(10, 3) << endl;
}
/*
7
*/



//5️⃣ Passing function pointer as argument (Callback)   VVI
/*
#include <iostream>
using namespace std;

int add(int a, int b) { 
    return a + b; 
}

int mul(int a, int b) { 
    return a * b; 
}

void calculate(int x, int y, int (*func)(int, int)) {
    cout << func(x, y) << endl;
}

int main() {
    calculate(3, 4, add);
    calculate(3, 4, mul);
}
/*
7
12
*/


//📌 Very important in systems programming & APIs.

//6️⃣ Function pointer array (menu-driven programs)
/*
#include <iostream>
using namespace std;

int add(int a, int b) { 
    return a + b;
}
int sub(int a, int b) { 
    return a - b;
}
int mul(int a, int b) { 
    return a * b;
}

int main() {
    int (*ops[])(int, int) = { add, sub, mul };

    cout << ops[0](5, 2) << endl; // add
    cout << ops[1](5, 2) << endl; // sub
    cout << ops[2](5, 2) << endl; // mul
}
/*
7
3 
10 
*/




//7️⃣ Function pointer vs Lambda
/*
#include <iostream>
using namespace std;

int main() {
    int (*fp)(int, int) = [](int a, int b) {
        return a + b;
    };

    cout << fp(2, 3) << endl;
}
/*
5


//⚠️ Works only for lambdas without captures.
*/




//8️⃣ Function pointer as class member parameter--Static method
/*
#include <iostream>
using namespace std;

class Calculator {
  public:
    static int add(int a, int b) {
        return a + b;
    }
};

int main() {
    int (*fp)(int, int) = Calculator::add;
    cout << fp(7, 8) << endl;
}
/*
15
*/


// Function pointer as class member parameter--Non Static method
/*
#include <iostream>
using namespace std;
class Calculator {
  public:
    int add(int a, int b) {
        return a + b;
    }
};
int main() {
    Calculator c;

    // pointer to member function
    int (Calculator::*fp)(int, int) = &Calculator::add;

    // call using object
    cout << (c.*fp)(7, 8) << endl;
}
/*
15
*/



//9️⃣ Function pointer returning another function pointer
/*
#include <iostream>
using namespace std;

int add(int a, int b) { 
     return a + b;
}
int mul(int a, int b) { 
     return a * b;
}

using Op = int(*)(int, int);

Op getOperation(char ch) {
    if (ch == '+') return add;
    return mul;
}

int main() {
    Op op = getOperation('+');
    cout << op(3, 4) << endl;
}
/*
7
*/



//🔟 Function pointer vs std::function (comparison)
/*
#include <iostream>
#include <functional>
using namespace std;

int add(int a, int b) { 
    return a + b;
}

int main() {
    function<int(int,int)> f = add;
    cout << f(4, 6) << endl;
}
/*
10
*/