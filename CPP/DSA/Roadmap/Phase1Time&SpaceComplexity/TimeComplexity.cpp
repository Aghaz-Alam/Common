1. Why Time & Space Complexity?
Measures efficiency, not execution speed
Independent of machine, compiler, OS
Helps compare algorithms, not implementations

/*=====================================*/
2. Asymptotic Notations

2.1 Big-O (Worst Case)
➡ Upper bound
➡ Maximum time an algorithm can take
f(n) ≤ C · g(n)  for n ≥ n0
Example
Linear Search → O(n)

/*=====================================*/

2.2 Big-Ω (Best Case)
➡ Lower bound
➡ Minimum time required
f(n) ≥ C · g(n)
Example:
Best case of Linear Search → Ω(1)
/*=====================================*/

2.3 Big-Θ (Average / Tight Bound)
➡ Exact bound
➡ Both upper and lower bound
C1·g(n) ≤ f(n) ≤ C2·g(n)
Example:
Binary Search → Θ(log n)

/*=====================================*/

3. Best / Average / Worst Case
| Case    | Meaning             |
| ------- | ------------------- |
| Best    | Minimum operations  |
| Average | Expected operations |
| Worst   | Maximum operations  |

/*=====================================*/

Example: Linear Search
#include <iostream>
using namespace std;
int linearSearch(int arr[], int n, int key) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == key)
            return i;
    }
    return -1;
}
int main() {
    int arr[] = {1,2,3,4,5};
    cout << linearSearch(arr, 5, 5);
    return 0;
}
/*
⏱ Complexity
Best → O(1)
Average → O(n)
Worst → O(n)

🖥 Output
4
*/
/*=====================================*/

4. Common Time Complexities

4.1 O(1) – Constant Time
➡ Independent of input size

#include <iostream>
using namespace std;
int main() {
    int a = 10;
    cout << a * a;
    return 0;
}
/*
🖥 Output:
100
*/
/*=====================================*/

4.2 O(log n) – Logarithmic Time
➡ Input size halves each step
➡ Binary Search

#include <iostream>
using namespace std;
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == key) return mid;
        else if(arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int main() {
    int arr[] = {1,3,5,7,9};
    cout << binarySearch(arr, 5, 7);
}
/*
🖥 Output:
3
*/
/*=====================================*/

4.3 O(n) – Linear Time
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4,5};
    int sum = 0;
    for(int i = 0; i < 5; i++)
        sum += arr[i];

    cout << sum;
}
/*
🖥 Output:
15
*/
/*=====================================*/

4.4 O(n log n)
➡ Divide & Conquer
➡ Merge Sort, Quick Sort (avg)

#include <iostream>
using namespace std;
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];

    for(int i=0;i<n1;i++) L[i] = arr[l+i];
    for(int j=0;j<n2;j++) R[j] = arr[m+1+j];

    int i=0,j=0,k=l;
    while(i<n1 && j<n2)
        arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
int main() {
    int arr[] = {5,4,3,2,1};
    mergeSort(arr, 0, 4);
    for(int i=0;i<5;i++)
        cout << arr[i] << " ";
}
/*
🖥 Output:
1 2 3 4 5
*/
/*=====================================*/

4.5 O(n²) – Quadratic Time
➡ Nested loops

#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3};
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++)
            cout << arr[i] << arr[j] << " ";
        cout << endl;
    }
}
/*
🖥 Output:
11 12 13
21 22 23
31 32 33
*/
/*=====================================*/

5. Space Complexity
➡ Memory used by algorithm

Includes:
Input space
Auxiliary space
Recursion stack
/*=====================================*/
5.1 O(1) Space
int a = 10, b = 20;
/*=====================================*/
5.2 O(n) Space
int arr[100];
/*=====================================*/
6. Recursion Stack Space
Example: Factorial
#include <iostream>
using namespace std;
int fact(int n) {
    if(n == 0) return 1;
    return n * fact(n - 1);
}
int main() {
    cout << fact(5);
}
/*
🖥 Output:
120
*/
Complexity
Time → O(n)
Space → O(n) (recursion stack)
/*=====================================*/
7. Practice: Loop Analysis
Example 1
for(int i=1;i<=n;i*=2)

➡ O(log n)
/*=====================================*/
Example 2
for(int i=0;i<n;i++)
    for(int j=0;j<i;j++)

➡ O(n²)
/*=====================================*/
Example 3
for(int i=0;i<n;i++)
    cout << i;

➡ O(n)
/*=====================================*/
📘 SET-1: COMPLEXITY PRACTICE (1–20)
🟢 EASY LEVEL
1️⃣ Print a constant
#include <iostream>
using namespace std;
int main() {
    cout << 10;
    return 0;
}
/*
Output
10

Time: O(1)
Space: O(1)
*/






2️⃣ Print first element of array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {5, 10, 15};
    cout << arr[0];
}
/*
Output
5

Time: O(1)
Space: O(1)
*/








3️⃣ Sum of two numbers
#include <iostream>
using namespace std;
int main() {
    int a = 5, b = 7;
    cout << a + b;
}
/*
Output
12

Time: O(1)
Space: O(1)
*/








4️⃣ Print numbers from 1 to n
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    for(int i = 1; i <= n; i++)
        cout << i << " ";
}
/*
Output
1 2 3 4 5

Time: O(n)
Space: O(1)
*/





5️⃣ Count elements in array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4};
    int count = 0;
    for(int i = 0; i < 4; i++)
        count++;

    cout << count;
}
/*
Output
4

Time: O(n)
Space: O(1)
*/




6️⃣ Find maximum element
#include <iostream>
using namespace std;
int main() {
    int arr[] = {3, 7, 2, 9, 5};
    int maxVal = arr[0];

    for(int i = 1; i < 5; i++)
        if(arr[i] > maxVal)
            maxVal = arr[i];

    cout << maxVal;
}
/*
Output
9

Time: O(n)
Space: O(1)
*/





7️⃣ Check even or odd
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    if(n % 2 == 0)
        cout << "Even";
    else
        cout << "Odd";
}
/*
Output
Even

Time: O(1)
Space: O(1)
*/






8️⃣ Sum of array elements
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4};
    int sum = 0;

    for(int i = 0; i < 4; i++)
        sum += arr[i];

    cout << sum;
}
/*
Output
10

Time: O(n)
Space: O(1)
*/







9️⃣ Linear Search
#include <iostream>
using namespace std;
int main() {
    int arr[] = {2,4,6,8,10};
    int key = 6;

    for(int i = 0; i < 5; i++) {
        if(arr[i] == key) {
            cout << "Found";
            return 0;
        }
    }
    cout << "Not Found";
}
/*
Output
Found

Time:
Best: O(1)

Worst: O(n)
Space: O(1)
*/





🔟 Reverse array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4};
    int n = 4;

    for(int i = n-1; i >= 0; i--)
        cout << arr[i] << " ";
}
/*
Output
4 3 2 1

Time: O(n)
Space: O(1)
*/







🟡 MEDIUM LEVEL
1️⃣1️⃣ Nested loop (n²)
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cout << i << j << " ";
}
/*
Output
00 01 02 10 11 12 20 21 22

Time: O(n²)
Space: O(1)
*/






1️⃣2️⃣ Triangular loop
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++)
            cout << "* ";
        cout << endl;
    }
}
/*
Output
*
* *
* * *
* * * *

Time: O(n²)
Space: O(1)
*/






1️⃣3️⃣ Binary Search
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,3,5,7,9};
    int low = 0, high = 4, key = 7;

    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == key) {
            cout << "Found";
            return 0;
        }
        else if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    cout << "Not Found";
}
/*
Output
Found

Time: O(log n)
Space: O(1)
*/




*1️⃣4️⃣ Loop with i = 2
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i <= n; i *= 2)
        cout << i << " ";
}
/*
Output
1 2 4 8 16

Time: O(log n)
Space: O(1)
*/






1️⃣5️⃣ Nested different sizes
#include <iostream>
using namespace std;
int main() {
    int n = 3, m = 4;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * *

Time: O(n × m)
Space: O(1)
*/






1️⃣6️⃣ Recursive countdown
#include <iostream>
using namespace std;
void print(int n) {
    if(n == 0) return;
    cout << n << " ";
    print(n - 1);
}
int main() {
    print(5);
}
/*
Output
5 4 3 2 1

Time: O(n)
Space: O(n) (stack)
*/





1️⃣7️⃣ Factorial
#include <iostream>
using namespace std;
int fact(int n) {
    if(n == 0) return 1;
    return n * fact(n - 1);
}
int main() {
    cout << fact(5);
}
/*
Output
120

Time: O(n)
Space: O(n)
*/





1️⃣8️⃣ Two independent loops
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 0; i < n; i++)
        cout << "A ";

    for(int i = 0; i < n; i++)
        cout << "B ";
}
/*
Output
A A A B B B

Time: O(n)
Space: O(1)
*/








1️⃣9️⃣ Loop inside log loop
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 1; i <= n; i *= 2) {
        for(int j = 0; j < n; j++)
            cout << "* ";
    }
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n log n)
Space: O(1)
*/





2️⃣0️⃣ Fibonacci (recursive)
#include <iostream>
using namespace std;
int fib(int n) {
    if(n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
int main() {
    cout << fib(5);
}
/*
Output
5

Time: O(2ⁿ)
Space: O(n)
*/



📘 SET-2: COMPLEXITY PRACTICE (21–40)
🟢 EASY → MEDIUM
2️⃣1️⃣ Loop runs n/2 times
#include <iostream>
using namespace std;
int main() {
    int n = 10;
    for(int i = 0; i < n; i += 2)
        cout << i << " ";
}
/*
Output
0 2 4 6 8

Time: O(n)
Space: O(1)
*/






2️⃣2️⃣ Loop runs n/3 times
#include <iostream>
using namespace std;
int main() {
    int n = 12;
    for(int i = 0; i < n; i += 3)
        cout << i << " ";
}
/*
Output
0 3 6 9

Time: O(n)
Space: O(1)
*/






2️⃣3️⃣ Reverse loop
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    for(int i = n; i > 0; i--)
        cout << i << " ";
}
/*
Output
5 4 3 2 1

Time: O(n)
Space: O(1)
*/






2️⃣4️⃣ Loop with break
#include <iostream>
using namespace std;
int main() {
    int n = 10;
    for(int i = 0; i < n; i++) {
        if(i == 3) break;
        cout << i << " ";
    }
}
/*
Output
0 1 2

Time:
Best: O(1)
Worst: O(n)
Space: O(1)
*/






2️⃣5️⃣ Loop with continue
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    for(int i = 0; i < n; i++) {
        if(i == 2) continue;
        cout << i << " ";
    }
}
/*
Output
0 1 3 4

Time: O(n)
Space: O(1)
*/






2️⃣6️⃣ Nested loop with dependent bounds
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * *

Time: O(n²)
Space: O(1)
*/




2️⃣7️⃣ Nested loop decreasing
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = n; i > 0; i--)
        for(int j = 0; j < i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * *

Time: O(n²)
Space: O(1)
*/





2️⃣8️⃣ Triple nested loop
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * * * * * * * * * * * * *

Time: O(n³)
Space: O(1)
*/






2️⃣9️⃣ Log loop with division
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    while(n > 1) {
        cout << n << " ";
        n /= 2;
    }
}
/*
Output
16 8 4 2

Time: O(log n)
Space: O(1)
*/





3️⃣0️⃣ Log loop with multiplication
#include <iostream>
using namespace std;
int main() {
    int i = 1, n = 32;
    while(i < n) {
        cout << i << " ";
        i *= 2;
    }
}
/*
Output
1 2 4 8 16

Time: O(log n)
Space: O(1)
*/







🟡 MEDIUM (INTERVIEW FAVORITES)
3️⃣1️⃣ Loop inside log loop
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 1; i <= n; i *= 2)
        for(int j = 0; j < n; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n log n)
Space: O(1)
*/





3️⃣2️⃣ Two log loops
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i < n; i *= 2)
        for(int j = 1; j < n; j *= 2)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(log² n)
Space: O(1)
*/




3️⃣3️⃣ Loop + recursion
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
* * * * * *

Time: O(n²)
Space: O(n)
*/




3️⃣4️⃣ Recursive binary
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

Time: O(log n)
Space: O(log n)
*/




3️⃣5️⃣ Recursive + loop
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
Output
* * * * * * * * * * * *

Time: O(n)
Space: O(log n)
*/





3️⃣6️⃣ Fibonacci iterative
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    int a = 0, b = 1;

    for(int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    cout << b;
}
/*
Output
5

Time: O(n)
Space: O(1)
*/





3️⃣7️⃣ Array copy
#include <iostream>
using namespace std;
int main() {
    int a[] = {1,2,3,4};
    int b[4];

    for(int i = 0; i < 4; i++)
        b[i] = a[i];

    cout << b[2];
}
/*
Output
3

Time: O(n)
Space: O(n)
*/





3️⃣8️⃣ Two arrays nested
#include <iostream>
using namespace std;
int main() {
    int a = 3, b = 4;
    for(int i = 0; i < a; i++)
        for(int j = 0; j < b; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * *

Time: O(a × b)
Space: O(1)
*/






3️⃣9️⃣ Recursion with two calls
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
(no output)

Time: O(2ⁿ)
Space: O(n)
*/



4️⃣0️⃣ Nested loop + constant work
#include <iostream>
using namespace std;

int main() {
    int n = 3;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cout << "X ";
}
/*
Output
X X X X X X X X X

Time: O(n²)
Space: O(1)
*/





📘 SET-3: COMPLEXITY PRACTICE (41–60)
🟡 MEDIUM → HARD
4️⃣1️⃣ Loop runs n + log n
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 0; i < n; i++)
        cout << "A ";
    for(int i = 1; i < n; i *= 2)
        cout << "B ";
}
/*
Output
A A A A A A A A B B B

Time: O(n)
Space: O(1)
*/




4️⃣2️⃣ Loop runs n/2 + n/3
#include <iostream>
using namespace std;
int main() {
    int n = 12;
    for(int i = 0; i < n; i += 2)
        cout << "A ";
    for(int i = 0; i < n; i += 3)
        cout << "B ";
}
/*
Output
A A A A A A B B B B

Time: O(n)
Space: O(1)
*/





4️⃣3️⃣ Nested loop + break
#include <iostream>
using namespace std;

int main() {
    int n = 5;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(j == 2) break;
            cout << "* ";
        }
    }
}
/*
Output
* * * * * * * * * *

Time: O(n²)
Space: O(1)
*/






4️⃣4️⃣ Log loop + constant work
#include <iostream>
using namespace std;
int main() {
    int n = 32;
    for(int i = 1; i < n; i *= 2)
        cout << "X ";
}
/*
Output
X X X X X

Time: O(log n)
Space: O(1)
*/



4️⃣5️⃣ Recursion with subtraction
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    cout << n << " ";
    fun(n - 2);
}
int main() {
    fun(10);
}
/*
Output
10 8 6 4 2

Time: O(n)
Space: O(n)
*/





4️⃣6️⃣ Recursion with division
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
}
int main() {
    fun(64);
}
/*
Output
64 32 16 8 4 2

Time: O(log n)
Space: O(log n)
*/




4️⃣7️⃣ Loop + recursion
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
* * * * * *

Time: O(n²)
Space: O(n)
*/




4️⃣8️⃣ Two recursive calls
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

Time: O(2ⁿ)
Space: O(n)
*/




4️⃣9️⃣ Recursive + loop
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
* * * * * * * *
* * * *
* *

Time: O(n)
Space: O(log n)
*/





5️⃣0️⃣ Recursion tree
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
Output
(no output)

Time: O(n)
Space: O(log n)
*/



🟠 HARD INTERVIEW TRAPS
5️⃣1️⃣ Loop + exponential recursion
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n - 1);
}
int main() {
    for(int i = 0; i < 3; i++)
        fun(3);
}
/*
Output
(no output)

Time: O(2ⁿ)
Space: O(n)
*/





5️⃣2️⃣ Mixed n + n log n
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 0; i < n; i++)
        cout << "A ";
    for(int i = 1; i < n; i *= 2)
        for(int j = 0; j < n; j++)
            cout << "B ";
}
/*
Output
A A A A A A A A B B B B B B B B B B B B B B B B

Time: O(n log n)
Space: O(1)
*/




5️⃣3️⃣ Decreasing loop
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = n; i > 1; i /= 2)
        cout << i << " ";
}
/*
Output
16 8 4 2

Time: O(log n)
Space: O(1)
*/





5️⃣4️⃣ Loop with square root
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i * i <= n; i++)
        cout << i << " ";
}
/*
Output
1 2 3 4

Time: O(√n)
Space: O(1)
*/





5️⃣5️⃣ Double loop with sqrt
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i * i <= n; i++)
        for(int j = 0; j < n; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n√n)
Space: O(1)
*/




5️⃣6️⃣ Recursive square root
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
8 4 4 2 2

Time: O(n)
Space: O(log n)
*/



5️⃣7️⃣ Recursion with constant
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
}
int main() {
    fun(5);
}
/*
Output
(no output)

Time: O(n)
Space: O(n)
*/




5️⃣8️⃣ Nested dependent bounds
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * *

Time: O(n²)
Space: O(1)
*/






5️⃣9️⃣ Loop with power
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 1; i <= (1 << n); i++)
        cout << i << " ";
}
/*
Output
1 2 3 4 5 6 7 8

Time: O(2ⁿ)
Space: O(1)
*/





6️⃣0️⃣ Recursive power
#include <iostream>
using namespace std;
int power(int n) {
    if(n == 0) return 1;
    return 2 * power(n - 1);
}
int main() {
    cout << power(3);
}
/*
Output
8

Time: O(n)
Space: O(n)
*/


📘 SET-4: COMPLEXITY PRACTICE (61–80)
🔴 HARD LEVEL (INTERVIEW CORE)
6️⃣1️⃣ Loop with doubling inner work
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 1; i <= n; i *= 2)
        for(int j = 0; j < i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * *

Time: O(n)
Space: O(1)
*/





6️⃣2️⃣ Loop with halving
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = n; i > 0; i /= 2)
        for(int j = 0; j < i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n)
Space: O(1)
*/





6️⃣3️⃣ Triple mixed loop
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i * i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n³)
Space: O(1)
*/





6️⃣4️⃣ Loop with square bound
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i * i; j++)
            if(j % i == 0)
                cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n²)
Space: O(1)
*/




6️⃣5️⃣ Amortized push_back idea
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v;
    for(int i = 0; i < 8; i++)
        v.push_back(i);

    cout << v.size();
}
/*
Output
8

Time: O(n) total → O(1) amortized
Space: O(n)
*/






6️⃣6️⃣ Loop with constant inner work
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 5; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * * * * * * * * * * *

Time: O(n)
Space: O(1)
*/






6️⃣7️⃣ STL-like traversal
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1,2,3,4,5};
    for(int x : v)
        cout << x << " ";
}
/*
Output
1 2 3 4 5

Time: O(n)
Space: O(1)
*/




6️⃣8️⃣ Map insertion
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int,int> m;
    m[3] = 10;
    m[1] = 20;
    m[2] = 30;

    cout << m[2];
}
/*
Output
30

Time: O(log n)
Space: O(n)
*/





6️⃣9️⃣ Nested STL traversal
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> a = {1,2,3};
    vector<int> b = {4,5};

    for(int x : a)
        for(int y : b)
            cout << x << y << " ";
}
/*
Output
14 15 24 25 34 35

Time: O(n × m)
Space: O(1)
*/





7️⃣0️⃣ While loop with sqrt
#include <iostream>
using namespace std;
int main() {
    int n = 100;
    int i = 1;
    while(i * i <= n) {
        cout << i << " ";
        i++;
    }
}
/*
Output
1 2 3 4 5 6 7 8 9 10

Time: O(√n)
Space: O(1)
*/





🔴 VERY HARD
7️⃣1️⃣ Recursive + two loops
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    for(int j = 0; j < n; j++)
        cout << "# ";
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
* * * * * * * * # # # # # # # #
* * * * # # # #
* * # #

Time: O(n)
Space: O(log n)
*/





7️⃣2️⃣ Binary recursion + constant
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
8 4 4 2 2

Time: O(n)
Space: O(log n)
*/





7️⃣3️⃣ Loop with exponential jump
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 1; i <= (1 << n); i++)
        cout << "* ";
}
/*
Output
* * * * * * * *

Time: O(2ⁿ)
Space: O(1)
*/




7️⃣4️⃣ Loop + recursion combo
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

Time: O(n²)
Space: O(n)
*/





7️⃣5️⃣ Multiple independent loops
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    for(int i = 0; i < n; i++)
        cout << "A ";
    for(int i = 0; i < n * n; i++)
        cout << "B ";
}
/*
Output
A A A A A B B B B B B B B B B B B B B B B B B B B

Time: O(n²)
Space: O(1)
*/




7️⃣6️⃣ Nested + log
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j *= 2)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n log n)
Space: O(1)
*/



7️⃣7️⃣ Recursion depth only
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
}
int main() {
    fun(6);
}
/*
Output
(no output)

Time: O(n)
Space: O(n)
*/




7️⃣8️⃣ Loop with constant condition
#include <iostream>
using namespace std;
int main() {
    int n = 100;
    for(int i = 0; i < n; i++)
        if(i == 50)
            cout << "X";
}
/*
Output
X

Time: O(n)
Space: O(1)
*/




7️⃣9️⃣ Nested loop with continue
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(j == 2) continue;
            cout << "* ";
        }
}
/*
Output
* * * * * * * * * * * * *

Time: O(n²)
Space: O(1)
*/




8️⃣0️⃣ Loop with recursion inside
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
}
int main() {
    for(int i = 0; i < 5; i++)
        fun(5);
}
/*
Output
(no output)

Time: O(n²)
Space: O(n)
*/







📘 SET-5: COMPLEXITY PRACTICE (81–100)
🔥 VERY HARD / FINAL MASTERY
8️⃣1️⃣ Loop with geometric series
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i <= n; i *= 2)
        for(int j = 0; j < i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n)
Space: O(1)
*/



8️⃣2️⃣ Nested decreasing + increasing
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = n; i > 0; i--)
        for(int j = 0; j < i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * *

Time: O(n²)
Space: O(1)
*/




8️⃣3️⃣ Loop inside recursion
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    fun(3);
}
/*
Output
* * *
* *
*

Time: O(n²)
Space: O(n)
*/



8️⃣4️⃣ Two recursive calls + linear work
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
    fun(8);
}
/*
Output
* * * * * * * *
* * * *
* * * *
* *
* *

Time: O(n log n)
Space: O(log n)
*/




8️⃣5️⃣ Pure binary recursion
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    fun(n - 1);
    fun(n - 1);
}
int main() {
    fun(4);
}
/*
Output
(no output)

Time: O(2ⁿ)
Space: O(n)
*/





8️⃣6️⃣ Loop with power jump
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 1; i <= (1 << n); i++)
        cout << i << " ";
}
/*
Output
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

Time: O(2ⁿ)
Space: O(1)
*/





8️⃣7️⃣ Master theorem (T(n)=2T(n/2)+n)
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
8 4 4 2 2

Time: O(n)
Space: O(log n)
*/




8️⃣8️⃣ Master theorem (T(n)=T(n/2)+n)
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
* * * * * * * *
* * * *
* *

Time: O(n)
Space: O(log n)
*/



8️⃣9️⃣ Log recursion + constant
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
}
int main() {
    fun(32);
}
/*
Output
32 16 8 4 2

Time: O(log n)
Space: O(log n)
*/





9️⃣0️⃣ Loop + recursion + loop
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << "* ";
    fun(n - 1);
}
int main() {
    for(int i = 0; i < 3; i++)
        fun(3);
}
/*
Output
* * *
* *
*
* * *
* *
*
* * *
* *
*

Time: O(n²)
Space: O(n)
*/




9️⃣1️⃣ Amortized vector growth
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v;
    for(int i = 0; i < 100; i++)
        v.push_back(i);

    cout << v.size();
}
/*
Output
100

Time: O(n) total → O(1) amortized
Space: O(n)
*/




9️⃣2️⃣ Nested log
#include <iostream>
using namespace std;
int main() {
    int n = 32;
    for(int i = 1; i < n; i *= 2)
        for(int j = 1; j < n; j *= 2)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(log² n)
Space: O(1)
*/





9️⃣3️⃣ Loop + sqrt
#include <iostream>
using namespace std;
int main() {
    int n = 25;
    for(int i = 1; i * i <= n; i++)
        cout << i << " ";
}
/*
Output
1 2 3 4 5

Time: O(√n)
Space: O(1)
*/







9️⃣4️⃣ Loop + recursion exponential
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
    fun(n - 1);
}
int main() {
    for(int i = 0; i < 3; i++)
        fun(3);
}
/*
Output
(no output)

Time: O(2ⁿ)
Space: O(n)
*/




9️⃣5️⃣ Constant inside exponential
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 0; i < (1 << n); i++)
        cout << "X ";
}
/*
Output
X X X X X X X X

Time: O(2ⁿ)
Space: O(1)
*/



9️⃣6️⃣ Recursive depth + constant
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    fun(n - 1);
}
int main() {
    fun(10);
}
/*
Output
(no output)

Time: O(n)
Space: O(n)
*/



9️⃣7️⃣ Multiple independent complexities
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 0; i < n; i++)
        cout << "A ";
    for(int i = 0; i < n * n; i++)
        cout << "B ";
    for(int i = 1; i < n; i *= 2)
        cout << "C ";
}
/*
Output
A A A A B B B B B B B B B B B B C C

Time: O(n²)
Space: O(1)
*/



9️⃣8️⃣ Nested + recursion
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

Time: O(n²)
Space: O(n)
*/


9️⃣9️⃣ Final trap: n + n log n
#include <iostream>
using namespace std;

int main() {
    int n = 8;
    for(int i = 0; i < n; i++)
        cout << "A ";
    for(int i = 1; i < n; i *= 2)
        for(int j = 0; j < n; j++)
            cout << "B ";
}
/*
Output
A A A A A A A A B B B B B B B B B B B B B B B B

Time: O(n log n)
Space: O(1)
*/





1️⃣0️⃣0️⃣ FINAL BOSS — Full combo
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
    fun(8);
}
/*
Output
* * * * * * * *
* * * *
* * * *
* *
* *

Time: O(n log n)
Space: O(log n)
*/









/*=======================================================================*/

📊 COMPLEXITY GROUPED PRACTICE (C++)
🔵 1. O(1) — Constant Time
Rule
No loops
Fixed number of operations
Independent of input size


Example 1: Print a value
#include <iostream>
using namespace std;
int main() {
    cout << 42;
}
/*
Output
42

Time: O(1)
Space: O(1)
*/


Example 2: Access array element
#include <iostream>
using namespace std;
int main() {
    int arr[] = {10,20,30};
    cout << arr[1];
}
/*
Output
20

Time: O(1)
Space: O(1)
*/


Example 3: Arithmetic
#include <iostream>
using namespace std;
int main() {
    int a = 5, b = 7;
    cout << a * b;
}
/*
Output
35

Time: O(1)
Space: O(1)
*/


/*=======================================================================*/

🟢 2. O(log n) — Logarithmic Time
Rule
Input reduces by half
i *= 2, i /= 2
Binary Search


Example 1: Binary Search
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,3,5,7,9};
    int low = 0, high = 4, key = 7;

    while(low <= high) {
        int mid = (low + high) / 2;
        if(arr[mid] == key) {
            cout << "Found";
            return 0;
        }
        if(arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
}
/*
Output
Found

Time: O(log n)
Space: O(1)
*/


Example 2: Doubling loop
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    for(int i = 1; i <= n; i *= 2)
        cout << i << " ";
}
/*
Output
1 2 4 8 16

Time: O(log n)
Space: O(1)
*/


Example 3: Recursive halving
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    cout << n << " ";
    fun(n / 2);
}
int main() {
    fun(32);
}
/*
Output
32 16 8 4 2

Time: O(log n)
Space: O(log n)
*/


/*=======================================================================*/

🟡 3. O(n) — Linear Time
Rule
Single loop
Recursion depth n
Sequential scan


Example 1: Print array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4,5};
    for(int i = 0; i < 5; i++)
        cout << arr[i] << " ";
}
/*
Output
1 2 3 4 5

Time: O(n)
Space: O(1)
*/


Example 2: Linear search
#include <iostream>
using namespace std;
int main() {
    int arr[] = {3,6,9,12};
    int key = 9;

    for(int i = 0; i < 4; i++) {
        if(arr[i] == key) {
            cout << "Found";
            return 0;
        }
    }
}
/*
Output
Found

Time: O(n)
Space: O(1)
*/


Example 3: Recursive countdown
#include <iostream>
using namespace std;
void print(int n) {
    if(n == 0) return;
    cout << n << " ";
    print(n - 1);
}
int main() {
    print(5);
}
/*
Output
5 4 3 2 1

Time: O(n)
Space: O(n)
*/



/*=======================================================================*/

🟠 4. O(n log n)
Rule
Loop + log loop
Divide & conquer
Merge Sort–like behavior




Example 1: Loop + log
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 1; i <= n; i *= 2)
        for(int j = 0; j < n; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * * * * * * * *

Time: O(n log n)
Space: O(1)
*/



Example 2: Recursive divide + linear
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
    fun(8);
}
/*
Output
* * * * * * * *
* * * *
* * * *
* *
* *

Time: O(n log n)
Space: O(log n)
*/



/*=======================================================================*/

🔴 5. O(n²) — Quadratic Time
Rule
Nested loops
Loop + recursion
Triangular patterns


Example 1: Nested loops
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cout << i << j << " ";
}
/*
Output
00 01 02 10 11 12 20 21 22

Time: O(n²)
Space: O(1)
*/



Example 2: Triangular loop
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            cout << "* ";
}
/*
Output
* * * * * * * * * *

Time: O(n²)
Space: O(1)
*/



Example 3: Loop + recursion
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

Time: O(n²)
Space: O(n)
*/


/*=======================================================================*/

🟦 O(1) — Constant Time
Program 1: Swap two numbers
#include <iostream>
using namespace std;
int main() {
    int a = 5, b = 10;
    int temp = a;
    a = b;
    b = temp;
    cout << a << " " << b;
}
/*
Output
10 5

Time: O(1)
Space: O(1)
*/


Program 2: Check even or odd
#include <iostream>
using namespace std;
int main() {
    int n = 7;
    if(n % 2 == 0)
        cout << "Even";
    else
        cout << "Odd";
}
/*
Output
Odd

Time: O(1)
Space: O(1)
*/

/*=======================================================================*/

🟩 O(log n) — Logarithmic Time
Program 3: Count bits
#include <iostream>
using namespace std;
int main() {
    int n = 16;
    int count = 0;
    while(n > 0) {
        n >>= 1;
        count++;
    }
    cout << count;
}
/*
Output
5

Time: O(log n)
Space: O(1)
*/


Program 4: Reduce by half
#include <iostream>
using namespace std;
int main() {
    int n = 50;
    while(n > 1) {
        cout << n << " ";
        n = n / 2;
    }
}
/*
Output
50 25 12 6 3

Time: O(log n)
Space: O(1)
*/

/*=======================================================================*/

🟨 O(n) — Linear Time
Program 5: Sum of array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {2,4,6,8};
    int sum = 0;
    for(int i = 0; i < 4; i++)
        sum += arr[i];
    cout << sum;
}
/*
Output
20

Time: O(n)
Space: O(1)
*/



Program 6: Reverse print
#include <iostream>
using namespace std;
int main() {
    int n = 5;
    for(int i = n; i >= 1; i--)
        cout << i << " ";
}
/*
Output
5 4 3 2 1

Time: O(n)
Space: O(1)
*/



Program 7: Recursive sum
#include <iostream>
using namespace std;
int sum(int n) {
    if(n == 0) return 0;
    return n + sum(n - 1);
}
int main() {
    cout << sum(4);
}
/*
Output
10

Time: O(n)
Space: O(n)
*/


/*=======================================================================*/

🟧 O(n log n)
Program 8: Nested log + linear
#include <iostream>
using namespace std;
int main() {
    int n = 8;
    for(int i = 1; i <= n; i *= 2)
        for(int j = 0; j < n; j++)
            cout << "*";
}
/*
Output
****************

Time: O(n log n)
Space: O(1)
*/




Program 9: Divide & loop
#include <iostream>
using namespace std;
void fun(int n) {
    if(n <= 1) return;
    for(int i = 0; i < n; i++)
        cout << "*";
    fun(n / 2);
}
int main() {
    fun(8);
}
/*
Output
************

Time: O(n log n)
Space: O(log n)
*/


/*=======================================================================*/

🟥 O(n²) — Quadratic
Program 10: Pair printing
#include <iostream>
using namespace std;
int main() {
    int n = 3;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cout << "(" << i << "," << j << ") ";
}
/*
Output
(1,1) (1,2) (1,3) (2,1) (2,2) (2,3) (3,1) (3,2) (3,3)

Time: O(n²)
Space: O(1)
*/


Program 11: Triangular numbers
#include <iostream>
using namespace std;
int main() {
    int n = 4;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            cout << "*";
}
/*
Output
**********

Time: O(n²)
Space: O(1)
*/


Program 12: Recursive quadratic
#include <iostream>
using namespace std;
void fun(int n) {
    if(n == 0) return;
    for(int i = 0; i < n; i++)
        cout << "*";
    fun(n - 1);
}
int main() {
    fun(5);
}
/*
Output
***************

Time: O(n²)
Space: O(n)
*/
/*=======================================================================*/





