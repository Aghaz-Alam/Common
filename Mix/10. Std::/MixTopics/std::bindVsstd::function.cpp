2. C++11 — std::function, std::bind, and Lambdas
C++11 introduced callable wrappers and lambda expressions, 
which revolutionized callbacks and replaced raw function pointers in most code.


a) Using std::function
std::function can store any callable object — functions, 
lambdas, functors, or even member functions (when bound).

#include <iostream>
#include <functional>
using namespace std;
void Greet() {
    cout << "Hello from std::function!\n";
}
int main() {
    std::function<void()> callback = Greet;
    callback(); // call it
  return 0;
}




b) Using Lambdas
#include <iostream>
#include <functional>
using namespace std;
int main() {
    std::function<void(int)> print = [](int x) {
        cout << "Square of " << x << " is " << x * x << endl;
    };

    print(5);
  return 0;
}
/*
Output:
Square of 5 is 25
*/





c) Using std::bind
std::bind allows you to bind arguments to functions and create partial applications.
#include <iostream>
#include <functional>
using namespace std;
void Multiply(int a, int b) {
    cout << "Result: " << a * b << endl;
}
int main() {
    auto times2 = std::bind(Multiply, std::placeholders::_1, 2);
    times2(5); // Equivalent to Multiply(5, 2)
  return 0;
}
/*
Output:
Result: 10
*/

C++11 Summary
✅ Introduced lambdas for inline callbacks.
✅ Introduced std::function (type-safe callable wrapper).
✅ Introduced std::bind for argument binding.

