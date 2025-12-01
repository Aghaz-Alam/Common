Normal template usage

// c++11-decltype
#include <iostream>
using namespace std;
template <typename T1, typename T2>
auto Add(T1 x, T2 y) -> decltype(x + y) {
    return x + y;
}
int main() {
    cout << "Addition of 3 and 7.5f is: " << Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << Add(3.5, 7) << endl;
    cout << "Addition of 'A' and 'E' is: " << Add(char('A'), char('E')) << endl;  //A=65, B=69   ===A+B=65+69=134
    cout << "Addition of Hello and World is: " << Add(string("Hello "), string("World!")) << endl; //Hello World
    
   return 0;
}
/* 
Output:
Addition of 3 and 7.5f is: 10.5
Addition of 3.5f and 7.5 is: 11
Addition of 3.5 and 7 is: 10.5
Addition of 'A' and 'E' is: 134
Addition of Hello and World is: Hello World!
*/


// c++14-auto-return-type
#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
auto Add(T1 x, T2 y) {
    return x + y;   // C++14 deduces return type automatically
}

int main() {
    cout << "Addition of 3 and 7.5f is: " << Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << Add(3.5, 7) << endl;

    cout << "Addition of 'A' and 'E' is: " << Add(char('A'), char('E')) << endl;  // 65 + 69 = 134

    cout << "Addition of Hello and World is: " << Add(string("Hello "), string("World!")) << endl;

    return 0;
}
/*
Addition of 3 and 7.5f is: 10.5
Addition of 3.5f and 7.5 is: 11
Addition of 3.5 and 7 is: 10.5
Addition of 'A' and 'E' is: 134
Addition of Hello and World is: Hello World!
*/





// Variadic Templates  c++11 And C++14 same
#include <iostream>
using namespace std;
// Base case
void print() {
    cout << "Empty Function! " << endl;
}

// Variadic template function: processes one argument and recursively calls itself
template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first<< endl;
    print(rest...); // Pack expansion: calls print with the remaining arguments
}

int main() {
    print(1, 2.5, "Hello", 'A'); 
}
/*
Output;
1
2.5
Hello
A
Empty Function! 
*/




// Variadic Templates - C++17
#include <iostream>
using namespace std;

template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first << endl;

    if constexpr (sizeof...(rest) > 0) {   // C++17 feature
        print(rest...);
    } else {
        cout << "Empty Function!" << endl;
    }
}

int main() {
    print(1, 2.5, "Hello", 'A');
}

/*
Output;
1
2.5
Hello
A
Empty Function! 
*/


//C++17
#include <iostream>
using namespace std;
template <typename... Args>
void print(Args... args) {
    // Print each argument followed by newline
    ((cout << args << endl), ...);

    cout << "Empty Function!" << endl;
}

int main() {
    print(1, 2.5, "Hello", 'A');
}
/*
1
2.5
Hello
A
Empty Function!
*/
