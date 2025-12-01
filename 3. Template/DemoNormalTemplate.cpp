Normal template usage


//1. static_cast char 
#include <iostream>
using namespace std;
// Generic function template
template <typename T> 
auto Add(T x, T y) -> (x + y) {
    return x + y;
}
int main() {
    cout << "Addition of 3 and 7 is: " << Add(3, 7) << endl;
    cout << "Addition of 3.5 and 7.5 is: " << Add(3.5, 7.5) << endl;
    cout << "Addition of 'g' and 'e' is: " << Add('g', 'e') << endl;  

    // If you want integer value of char addition
    cout << "Integer sum of 'g' and 'e' is: " << static_cast<int>(Add('g','e')) << endl;
   return 0;
}
/* 
Addition of 3 and 7 is: 10
Addition of 3.5 and 7.5 is: 11
Addition of 'g' and 'e' is: ì  (char corresponding to 204)
Integer sum of 'g' and 'e' is: 204
*/





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


// c++11-decltype with class
#include <iostream>
using namespace std;
class Calculator {
  public:
    // Templated member function
    template <typename T1, typename T2>
    auto Add(T1 x, T2 y) -> decltype(x + y) {
        return x + y;
    }
};
int main() {
    Calculator calc;
    cout << "Addition of 3 and 7.5f is: " << calc.Add(3, 7.5f) << endl;
    cout << "Addition of 3.5f and 7.5 is: " << calc.Add(3.5f, 7.5) << endl;
    cout << "Addition of 3.5 and 7 is: " << calc.Add(3.5, 7) << endl;
    cout << "Addition of 'g' and 'e' is: " << calc.Add(char('g'), char('e')) << endl;

    return 0;
}



#include <iostream>
using namespace std;
template <typename T>
auto myMax(T x, T y) -> decltype((x > y) ? x : y) {
    return (x > y) ? x : y;
}
int main() {
    cout << "Max of 3 and 7 is: " << myMax(3, 7) << endl;
    cout << "Max of 3.5 and 7.5 is: " << myMax(3.5, 7.5) << endl;
    cout << "Max of 'g' and 'e' is: " << myMax('g', 'e') << endl;
   return 0;
}
/* 
Max of 3 and 7 is: 7
Max of 3.5 and 7.5 is: 7.5
Max of 'g' and 'e' is: g
*/


