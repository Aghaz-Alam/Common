RECURSION + COMPLEXITY TRAPS (C++)
🔴 TRAP 1: Single recursion (looks scary, but O(n))
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
4 3 2 1

Dry Run
fun(4) → prints 4 → fun(3)
fun(3) → prints 3 → fun(2)
fun(2) → prints 2 → fun(1)
fun(1) → prints 1 → fun(0)

Complexity
Time: O(n)
Space: O(n) (recursion stack)
*/





🔴 TRAP 2: Two recursive calls (Exponential)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n - 1);
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
3 2 2

Dry Run
fun(3)
 ├─ prints 3
 ├─ fun(2) → prints 2
 └─ fun(2) → prints 2

Complexity
Time: O(2ⁿ)
Space: O(n)
*/






🔴 TRAP 3: Recursion + loop (Quadratic)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
* * * * 
* * * 
* * 
* 

Dry Run
Level 4 → 4 prints
Level 3 → 3 prints
Level 2 → 2 prints
Level 1 → 1 print

Complexity
Time: O(n²)
Space: O(n)
*/




🔴 TRAP 4: Divide recursion (Logarithmic)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
}
int main() {
    fun(16);
}
/*
Output
16 8 4 2

Dry Run
16 → 8 → 4 → 2 → stop

Complexity
Time: O(log n)
Space: O(log n)
*/




🔴 TRAP 5: Divide + two calls (n log n)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n / 2);
    fun(n / 2);
}
int main() {
    fun(4);
}
/*
Output
* * * * 
* * 
* * 

Dry Run
Level 4 → 4 prints
Level 2 → 2 + 2 prints

Complexity
Time: O(n log n)
Space: O(log n)
*/





🔴 TRAP 6: Post-order recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(4);
}
/*
Output
1 2 3 4

Dry Run
Calls go down first → print while returning

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 7: Tail recursion (still O(n))
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
3 2 1

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 8: Fibonacci (classic interview trap)
Code
#include <iostream>
using namespace std;
int fib(int n) {
    if(n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
int main() {
    cout << fib(5);
}
/*
Output
5

Dry Run
Repeated subproblems

Complexity
Time: O(2ⁿ)
Space: O(n)
*/




🔴 TRAP 9: Recursive loop inside recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        fun(n - 1);
}
int main() {
    fun(3);
}
/*
Dry Run (Structure)
fun(3)
 ├─ fun(2)
 │   ├─ fun(1)
 │   └─ fun(1)
 └─ fun(2)
     ├─ fun(1)
     └─ fun(1)

Complexity
Time: O(n!)
Space: O(n)
*/





🔴 TRAP 10: Print + divide + linear recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n - 1);
    fun(n / 2);
}
int main() {
    fun(5);
}
/*
Output
5 4 3 2

Complexity
Time: O(n)
Space: O(n)
*/


🏆 MASTER FORMULA (REMEMBER THIS)
| Pattern          | Time       |
| ---------------- | ---------- |
| 1 recursive call | O(n)       |
| 2 same calls     | O(2ⁿ)      |
| n/2 call         | O(log n)   |
| loop + recursion | multiply   |
| divide + 2 calls | O(n log n) |




🔴 TRAP 11: Print before & after recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 1 2 3

Dry Run
fun(3) → print 3
  fun(2) → print 2
    fun(1) → print 1
      fun(0) → return
    print 1
  print 2
print 3

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 12: Two different recursive calls
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n - 1);
    fun(n - 2);
}
int main() {
    fun(4);
}
/*
Output
4 3 2 2

Dry Run
fun(4)
 ├─ prints 4
 ├─ fun(3) → prints 3
 │    ├─ fun(2) → prints 2
 │    └─ fun(1)
 └─ fun(2) → prints 2

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 13: Hidden infinite recursion avoided by base case
Code
#include <iostream>
using namespace std;
void fun(int n) {
    cout << n << " ";
    if(n == 0) return;
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
3 2 1 0

Dry Run
Print happens before base check

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 14: Log recursion with extra work
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
    cout << n << " ";
}
int main() {
    fun(8);
}
/*
Output
8 4 2 2 4 8

Dry Run
8 → 4 → 2 → return
Print while returning

Complexity
Time: O(log n)
Space: O(log n)
*/





🔴 TRAP 15: Nested recursion call
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    fun(fun(n - 1));
    cout << n << " ";
}
int main() {
    fun(3);
}
/*
Output
1 2 3

Dry Run
fun(3)
 └─ fun(fun(2))
      └─ fun(fun(1))
           └─ fun(fun(0))

Complexity
Time: Very high (super-linear)
Space: O(n)
📌 Interview note: Nested recursion is dangerous & unpredictable.
*/







🔴 TRAP 16: Loop + double recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        fun(n - 1);
}
int main() {
    fun(3);
}
/*
Dry Run Structure
fun(3)
 ├─ fun(2)
 │   ├─ fun(1)
 │   └─ fun(1)
 ├─ fun(2)
 │   ├─ fun(1)
 │   └─ fun(1)
 └─ fun(2)
     ├─ fun(1)
     └─ fun(1)

Complexity
Time: O(n!)
Space: O(n)
*/





🔴 TRAP 17: Post-order log recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n / 2);
    cout << n << " ";
}
int main() {
    fun(16);
}
/*
Output
2 4 8 16

Complexity
Time: O(log n)
Space: O(log n)
*/





🔴 TRAP 18: Recursion + constant loop
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < 5; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
* * * * * * * * * * * * * * *

Complexity
Time: O(n)
Space: O(n)
📌 Constant loops don’t affect complexity.
*/





🔴 TRAP 19: Tail + divide recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
}
int main() {
    fun(10);
}
/*
Output
10 5 2

Complexity
Time: O(log n)
Space: O(log n)
*/





🔴 TRAP 20: Misleading multiple prints
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n * n << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 1 4 9

Complexity
Time: O(n)
Space: O(n)
*/



🔴 TRAP 21: Double print + single recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(2);
}
/*
Output
2 1 1 2

Dry Run
fun(2) → print 2
  fun(1) → print 1
    fun(0) → return
  print 1
print 2

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 22: Two recursive calls with different sizes
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
4 2 1 3 1 2 1

Dry Run
fun(4)
 ├─ print 4
 ├─ fun(2)
 │    ├─ print 2
 │    ├─ fun(1)
 │    └─ fun(1)
 └─ fun(3)
      ├─ print 3
      ├─ fun(1)
      └─ fun(2)

Complexity
Time: O(2ⁿ) (dominated by n-1 branch)
Space: O(n)
*/





🔴 TRAP 23: Recursion inside loop (linear)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < 1; i++)
        fun(n - 1);
}
int main() {
    fun(5);
}
/*
Dry Run
Loop runs once → behaves like single recursion

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 24: Loop depends on recursion depth
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
3 3 3 2 2 1

Dry Run
Level 3 → 3 prints
Level 2 → 2 prints
Level 1 → 1 print

Complexity
Time: O(n²)
Space: O(n)
*/





🔴 TRAP 25: Two recursive calls but log depth
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n / 2);
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Dry Run Tree
8
├─4
│ ├─2
│ └─2
└─4
  ├─2
  └─2

Complexity
Time: O(n)
Space: O(log n)
📌 Many think O(2ⁿ) ❌ — actually O(n)
*/





🔴 TRAP 26: Print only at base case
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) {
        cout << "X ";
        return;
    }
    fun(n - 1);
}
int main() {
    fun(5);
}
/*
Output
X

Dry Run
All calls collapse to one base print

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 27: Multiple prints without extra calls
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
3 3 2 2 1 1

Complexity
Time: O(n)
Space: O(n)
📌 Prints don’t change complexity.
*/




🔴 TRAP 28: Recursion + logarithmic loop
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = n; i > 1; i /= 2)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
* * * * * * * *

Dry Run
Each level → O(log n)
Total → n * log n

Complexity
Time: O(n log n)
Space: O(n)
*/






🔴 TRAP 29: Recursion only on even numbers
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    if(n % 2 == 0)
        fun(n - 2);
    else
        fun(n - 1);
}
int main() {
    fun(6);
}
/*
Output
6 4 2

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 30: Return-based recursion
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n == 1) return 1;
    return fun(n - 1);
}
int main() {
    cout << fun(5);
}
/*
Output
1

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 31: Pre + In + Post behavior combined
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << "A" << n << " ";
    fun(n - 1);
    cout << "B" << n << " ";
    fun(n - 1);
    cout << "C" << n << " ";
}
int main() {
    fun(2);
}
/*
Output
A2 A1 B1 C1 B2 A1 B1 C1 C2

Dry Run
fun(2)
 ├─ A2
 ├─ fun(1)
 │    ├─ A1
 │    ├─ fun(0)
 │    ├─ B1
 │    ├─ fun(0)
 │    └─ C1
 ├─ B2
 ├─ fun(1) → same as above
 └─ C2

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 32: Hidden linear behavior
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n / 2);
    fun(n / 2);
}
int main() {
    fun(16);
}
/*
Dry Run
Total calls ≈ n

Complexity
Time: O(n)
Space: O(log n)
📌 Most people wrongly answer O(2ⁿ) ❌
*/






🔴 TRAP 33: Linear + log recursion combined
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n / 2);
}
int main() {
    fun(5);
}
/*
Dry Run
Dominated by fun(n - 1)

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 34: Loop with recursive call inside (factorial growth)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        fun(n - 1);
}
int main() {
    fun(4);
}
/*
Dry Run
T(n) = n * T(n-1)

Complexity
Time: O(n!)
Space: O(n)
*/





🔴 TRAP 35: Recursive call in loop with divide
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        fun(n / 2);
}
int main() {
    fun(8);
}
/*
Dry Run
T(n) = n * T(n/2)

Complexity
Time: O(n log n)
Space: O(log n)
*/







🔴 TRAP 36: Print only on unwind (reverse order)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(4);
}
/*
Output
1 2 3 4

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 37: Conditional recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    if(n % 2 == 0)
        fun(n / 2);
    else
        fun(n - 1);
}
int main() {
    fun(10);
}
/*
Output
10 5 4 2 1

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 38: Double recursion with print at base
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) {
        cout << "* ";
        return;
    }
    fun(n - 1);
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
* * * * * * * *

Dry Run
2ⁿ base calls

Complexity
Time: O(2ⁿ)
Space: O(n)
*/







🔴 TRAP 39: Misleading logarithmic loop + recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 1; i < n; i *= 2)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Complexity
Time: O(n log n)
Space: O(n)
*/






🔴 TRAP 40: Recursive return dependency
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n == 0) return 0;
    return fun(n - 1) + 1;
}
int main() {
    cout << fun(5);
}
/*
Output
5

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 41: Nested recursion (McCarthy-style behavior)
Code
#include <iostream>
using namespace 
int fun(int n) {
    if(n > 100)
        return n - 10;
    return fun(fun(n + 11));
}
int main() {
    cout << fun(95);
}
/*
Output
91

Dry Run (Conceptual)
fun(95)
 → fun(fun(106))
 → fun(96)
 → fun(fun(107))
 → ...
 → eventually returns 91

Complexity
Time: Very high (but bounded)
Space: O(n)
📌 Famous McCarthy 91 function
*/





🔴 TRAP 42: Print only at deepest level
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) {
        cout << "X ";
        return;
    }
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
X

Dry Run
fun(4) → fun(3) → fun(2) → fun(1) → fun(0) → print once

Complexity
Time: O(n)
Space: O(n)
*/



🔴 TRAP 43: Print depth value using static variable
Code
#include <iostream>
using namespace std;
void fun(int n) {
    static int depth = 0;
    if(n == 0) return;
    depth++;
    cout << depth << " ";
    fun(n - 1);
    depth--;
}
int main() {
    fun(3);
}
/*
Output
1 2 3

Dry Run
depth increments on call, decrements on return

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 44: Two recursive calls, but only one prints
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(3);
}
/*
Output
2 2 3

Dry Run
Printing happens after both recursive calls

Complexity
Time: O(2ⁿ)
Space: O(n)
*/







🔴 TRAP 45: Recursion + static accumulator
Code
#include <iostream>
using namespace std;
int fun(int n) {
    static int sum = 0;
    if(n == 0) return sum;
    sum += n;
    return fun(n - 1);
}
int main() {
    cout << fun(4);
}
/*
Output
10

Dry Run
sum = 4 → 7 → 9 → 10

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 46: Mixed tail and non-tail recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    fun(n - 1);
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(2);
}
/*
Output
1 1 2 1 1

Dry Run
In-order traversal style

Complexity
Time: O(2ⁿ)
Space: O(n)
*/







🔴 TRAP 47: Recursion controlled by return value
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return 1;
    return fun(n - 1) && fun(n - 2);
}
int main() {
    cout << fun(4);
}
/*
Output
1

Dry Run
Both calls must be evaluated

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 48: Recursion + while loop
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    int i = n;
    while(i > 0) {
        cout << "* ";
        i--;
    }
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
* * * * * *

Complexity
Time: O(n²)
Space: O(n)
*/






🔴 TRAP 49: Divide recursion but linear work after return
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n / 2);
    for(int i = 0; i < n; i++)
        cout << "* ";
}
int main() {
    fun(4);
}
/*
Dry Run
Work: n + n/2 + n/4 + ...

Complexity
Time: O(n)
Space: O(log n)
*/






🔴 TRAP 50: Mutual recursion
Code
#include <iostream>
using namespace std;
void funB(int n);
void funA(int n) {
    if(n == 0) return;
    cout << "A" << n << " ";
    funB(n - 1);
}
void funB(int n) {
    if(n == 0) return;
    cout << "B" << n << " ";
    funA(n - 1);
}
int main() {
    funA(3);
}
/*
Output
A3 B2 A1

Dry Run
Functions call each other alternately

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 51: Print order depends on call stack
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(2);
}
/*
Output
2 1 1 2 1 1

Dry Run
fun(2)
 ├─ print 2
 ├─ fun(1)
 │    ├─ print 1
 │    ├─ fun(0)
 │    ├─ print 1
 │    └─ fun(0)
 ├─ print 2
 └─ fun(1) → same as above

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 52: Recursion with decreasing loop size
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Dry Run
Level 8 → 8 prints
Level 4 → 4 prints
Level 2 → 2 prints

Output
* * * * * * * * * * * * * *

Complexity
Time: O(n)
Space: O(log n)
*/




🔴 TRAP 53: Log recursion inside linear recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n / 2);
}
int main() {
    fun(6);
}
/*
Dry Run
fun(n-1) dominates

Complexity
Time: O(n)
Space: O(n)
📌 Many answer O(n log n) ❌
*/




🔴 TRAP 54: Loop + divide recursion (misleading!)
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        cout << i << " ";
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Dry Run
Work = n + n/2 + n/4 + ...

Complexity
Time: O(n)
Space: O(log n)
*/





🔴 TRAP 55: Return-based recursion chain
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n == 0) return 1;
    return n * fun(n - 1);
}
int main() {
    cout << fun(4);
}
/*
Output
24

Dry Run
4 * 3 * 2 * 1

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 56: Conditional recursion stopping early
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    if(n > 3)
        fun(n - 3);
}
int main() {
    fun(10);
}
/*
Output
10 7 4

Complexity
Time: O(n)
Space: O(n)
*/









🔴 TRAP 57: Two recursive calls but unequal sizes
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n - 2);
}
int main() {
    fun(5);
}
/*
Dry Run
Same as Fibonacci recursion

Complexity
Time: O(2ⁿ)
Space: O(n)
*/






🔴 TRAP 58: Recursion + static counter
Code
#include <iostream>
using namespace std;
void fun(int n) {
    static int count = 0;
    if(n == 0) return;
    count++;
    cout << count << " ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
1 2 3

Dry Run
Static variable retains value across calls

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 59: Mutual recursion with early exit
Code
#include <iostream>
using namespace std;
void B(int n);
void A(int n) {
    if(n <= 0) return;
    cout << "A" << n << " ";
    B(n - 2);
}
void B(int n) {
    if(n <= 0) return;
    cout << "B" << n << " ";
    A(n - 1);
}
int main() {
    A(4);
}
/*
Output
A4 B2 A1

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 60: Divide recursion with post-processing
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n / 2);
    cout << n << " ";
}
int main() {
    fun(16);
}
/*
Output
2 4 8 16

Complexity
Time: O(log n)
Space: O(log n)
*/




🔴 TRAP 71: Recursion with multiple base cases
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) {
        cout << "X ";
        return;
    }
    if(n == 2) {
        cout << "Y ";
        return;
    }
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
4 3 Y

Dry Run
fun(4) → print 4 → fun(3)
fun(3) → print 3 → fun(2)
fun(2) → base case → print Y → return

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 72: Tail recursion vs non-tail confusion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(3);
}
/*
Output
1 2 3

Dry Run
Print happens after recursion → postorder

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 73: Nested recursion with arithmetic inside call
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return 1;
    return fun(n - 1) + fun(n - 2);
}
int main() {
    cout << fun(5);
}
/*
Output
8

Dry Run
fun(5) = fun(4) + fun(3)
fun(4) = fun(3) + fun(2)
fun(3) = fun(2) + fun(1)

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 74: Recursion with static array accumulation
Code
#include <iostream>
using namespace std;
void fun(int n) {
    static int arr[100];
    static int idx = 0;
    if(n == 0) return;
    arr[idx++] = n;
    fun(n - 1);
    for(int i = 0; i < idx; i++)
        cout << arr[i] << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 3 2 1 3 2 1

Dry Run
Static array keeps values across all calls
Print loop happens at every return

Complexity
Time: O(n²)
Space: O(n)
*/




🔴 TRAP 75: Mutual recursion with decreasing steps
Code
#include <iostream>
using namespace std;
void B(int n);
void A(int n) {
    if(n <= 0) return;
    cout << "A" << n << " ";
    B(n - 2);
}
void B(int n) {
    if(n <= 0) return;
    cout << "B" << n << " ";
    A(n - 1);
}
int main() {
    A(5);
}
/*
Output
A5 B3 A2 B1

Dry Run
Functions call each other alternately until n <= 0

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 76: Recursion with loop decreasing geometrically
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    for(int i = n; i > 0; i /= 2)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(8);
}
/*
Dry Run
Level 8 → 8,4,2,1?
Actually, prints: 8→4→2→1? Actually, i /=2 → 4 prints, 2 prints, 1 prints

Output
* * * * * * * * * * * * * *

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 77: Recursion with conditional recursion only on certain numbers
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    if(n % 2 == 0)
        fun(n / 2);
}
int main() {
    fun(10);
}
/*
Output
10 5 2 1

Dry Run
10 → even → 5
5 → odd → no recursion
2 → even → 1

Complexity
Time: O(log n)
Space: O(log n)
*/




🔴 TRAP 78: Recursion with multiple recursive calls in expressions
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return n;
    return fun(n - 1) + fun(n - 1);
}
int main() {
    cout << fun(4);
}
/*
Dry Run
T(n) = 2 * T(n-1)

Output
8

Complexity
Time: O(2ⁿ)
Space: O(n)
*/




🔴 TRAP 79: Recursion with decrement and post-processing
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(5);
}
/*
Output
2 3 4 5

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 80: Recursion with multiple prints in different order
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n*2 << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 2 4 6

Dry Run
Print before → preorder
Print after → postorder with arithmetic

Complexity
Time: O(n)
Space: O(n)
*/











🔴 TRAP 71: Recursion with multiple base cases
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) {
        cout << "X ";
        return;
    }
    if(n == 2) {
        cout << "Y ";
        return;
    }
    cout << n << " ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
4 3 Y

Dry Run
fun(4) → print 4 → fun(3)
fun(3) → print 3 → fun(2)
fun(2) → base case → print Y → return

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 72: Tail recursion vs non-tail confusion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(3);
}
/*
Output
1 2 3

Dry Run
Print happens after recursion → postorder

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 73: Nested recursion with arithmetic inside call
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return 1;
    return fun(n - 1) + fun(n - 2);
}
int main() {
    cout << fun(5);
}
/*
Output
8

Dry Run
fun(5) = fun(4) + fun(3)
fun(4) = fun(3) + fun(2)
fun(3) = fun(2) + fun(1)

Complexity
Time: O(2ⁿ)
Space: O(n)
*/




🔴 TRAP 74: Recursion with static array accumulation
Code
#include <iostream>
using namespace std;
void fun(int n) {
    static int arr[100];
    static int idx = 0;
    if(n == 0) return;
    arr[idx++] = n;
    fun(n - 1);
    for(int i = 0; i < idx; i++)
        cout << arr[i] << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 3 2 1 3 2 1

Dry Run
Static array keeps values across all calls
Print loop happens at every return

Complexity
Time: O(n²)
Space: O(n)
*/




🔴 TRAP 75: Mutual recursion with decreasing steps
Code
#include <iostream>
using namespace std;
void B(int n);
void A(int n) {
    if(n <= 0) return;
    cout << "A" << n << " ";
    B(n - 2);
}
void B(int n) {
    if(n <= 0) return;
    cout << "B" << n << " ";
    A(n - 1);
}
int main() {
    A(5);
}
/*
Output
A5 B3 A2 B1

Dry Run
Functions call each other alternately until n <= 0

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 76: Recursion with loop decreasing geometrically
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    for(int i = n; i > 0; i /= 2)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(8);
}
/*
Dry Run
Level 8 → 8,4,2,1?
Actually, prints: 8→4→2→1? Actually, i /=2 → 4 prints, 2 prints, 1 prints

Output
* * * * * * * * * * * * * *

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 77: Recursion with conditional recursion only on certain numbers
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    if(n % 2 == 0)
        fun(n / 2);
}
int main() {
    fun(10);
}
/*
Output
10 5 2 1

Dry Run
10 → even → 5
5 → odd → no recursion
2 → even → 1

Complexity
Time: O(log n)
Space: O(log n)
*/




🔴 TRAP 78: Recursion with multiple recursive calls in expressions
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return n;
    return fun(n - 1) + fun(n - 1);
}
int main() {
    cout << fun(4);
}
/*
Dry Run
T(n) = 2 * T(n-1)

Output
8

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 79: Recursion with decrement and post-processing
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    cout << n << " ";
}
int main() {
    fun(5);
}
/*
Output
2 3 4 5

Complexity
Time: O(n)
Space: O(n)
*/






🔴 TRAP 80: Recursion with multiple prints in different order
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n*2 << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 2 4 6

Dry Run
Print before → preorder
Print after → postorder with arithmetic

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 91: Recursion with decrement inside multiple recursive calls
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    fun(n - 1);
    fun(n - 2);
    cout << n << " ";
}
int main() {
    fun(4);
}
/*
Output
1 2 3 4

Dry Run
fun(4)
 ├─ fun(3)
 │   ├─ fun(2)
 │   │  ├─ fun(1)
 │   │  └─ fun(0)
 │   └─ fun(1)
 └─ fun(2)

Complexity
Time: O(2ⁿ)
Space: O(n)
*/



🔴 TRAP 92: Recursion with nested pre/post prints and arithmetic
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n * n << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 1 4 9

Dry Run
Pre-recursion → print n
Post-recursion → print n²

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 93: Mutual recursion with decrement by 1 and 3
Code
#include <iostream>
using namespace std;
void B(int n);
void A(int n) {
    if(n <= 0) return;
    cout << "A" << n << " ";
    B(n - 3);
}
void B(int n) {
    if(n <= 0) return;
    cout << "B" << n << " ";
    A(n - 1);
}
int main() {
    A(6);
}
/*
Output
A6 B3 A2

Dry Run
A6 → B3 → A2 → stop

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 94: Recursion with loop decreasing geometrically
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    for(int i = n; i > 0; i /= 2)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(8);
}
/*
Output
* * * * * * * * * * * * * *

Dry Run
i = 8 → 4 → 2 → 1
Then recursion with n-1

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 95: Recursion with multiple returns combined
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return n;
    return fun(n - 1) + fun(n - 1);
}
int main() {
    cout << fun(3);
}
/*
Output
4

Dry Run
fun(3) = fun(2) + fun(2) = 2 + 2

Complexity
Time: O(2ⁿ)
Space: O(n)
*/




🔴 TRAP 96: Recursion with arithmetic expressions inside
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return n;
    return fun(n - 1) + n;
}
int main() {
    cout << fun(4);
}
/*
Output
10

Dry Run
fun(4) = fun(3) + 4
fun(3) = fun(2) + 3
fun(2) = fun(1) + 2
fun(1) = 1

Complexity
Time: O(n)
Space: O(n)
*/





🔴 TRAP 97: Recursion with conditional recursion
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    if(n % 2 == 0) fun(n / 2);
}
int main() {
    fun(10);
}
/*
Output
10 5 2 1

Dry Run
10 → even → 5
5 → odd → skip recursion
2 → even → 1

Complexity
Time: O(log n)
Space: O(log n)
*/




🔴 TRAP 98: Recursion with pre & post prints + multiplication
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    fun(n - 1);
    cout << n*3 << " ";
}
int main() {
    fun(3);
}
/*
Output
3 2 1 3 6 9

Complexity
Time: O(n)
Space: O(n)
*/




🔴 TRAP 99: Recursion with double call inside expressions
Code
#include <iostream>
using namespace std;
int fun(int n) {
    if(n <= 1) return 1;
    return fun(n - 1) + fun(n - 1);
}
int main() {
    cout << fun(4);
}
/*
Output
8

Complexity
Time: O(2ⁿ)
Space: O(n)
*/





🔴 TRAP 100: Recursion with nested loops and decrement
Code
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
* * * * * * * * * * *

Dry Run
Level 4 → 4 prints
Level 3 → 3 prints
Level 2 → 2 prints
Level 1 → 1 print

Complexity
Time: O(n²)
Space: O(n)
*/