#Basic Structure:
'''
#C++
#include <iostream>
using namespace std;
int main() {
    cout << "Hello";
    return 0;
}
'''

#Python
print("Hello")
'''
✔ No main()
✔ No headers
✔ No semicolons
'''



#Variables & Data Types

'''
C++
int a = 10;
float b = 2.5;
string name = "Aman";
'''

#Python
a = 10
b = 2.5
name = "Aman"

#📌 Python is dynamically typed


#Loops Conversion (VERY IMPORTANT)
#🔹 for loop
'''
C++
for(int i = 0; i < 5; i++) {
    cout << i;
}
'''
#Python
for i in range(5):
    print(i)

#📌 range(start, stop, step)



#🔹 while loop
'''
C++
int i = 1;
while(i <= 5) {
    cout << i;
    i++;
}
'''

#Python
i = 1
while i <= 5:
    print(i)
    i += 1



#Conditional Statements
'''
C++
if(a > b) {
    cout << "A is greater";
} else {
    cout << "B is greater";
}
'''

#Python
if a > b:
    print("A is greater")
else:
    print("B is greater")

'''
✔ No parentheses
✔ No braces
✔ Indentation matters
'''



#Input / Output
'''
C++
int x;
cin >> x;
'''

#Python
x = int(input())

#📌 Always convert input type in Python



#Arrays → Lists
'''
C++
int arr[5] = {1, 2, 3, 4, 5};
cout << arr[0];
'''

#Python
arr = [1, 2, 3, 4, 5]
print(arr[0])


#Example: Sum of Array Elements
'''
C++
int sum = 0;
for(int i = 0; i < n; i++) {
    sum += arr[i];
}
'''

#Python
total = 0
for x in arr:
    total += x

'''
✔ Cleaner
✔ Pythonic
'''

#Prime Number Check
'''
C++
bool prime = true;
int n = 7;

for(int i = 2; i < n; i++) {
    if(n % i == 0) {
        prime = false;
        break;
    }
}
'''

#Python
n = 7
prime = True

for i in range(2, n):
    if n % i == 0:
        prime = False
        break


#break / continue
'''
C++
for(int i = 1; i <= 10; i++) {
    if(i % 3 == 0) continue;
    cout << i << " ";
}
'''
#Python
for i in range(1, 11):
    if i % 3 == 0:
        continue
    print(i, end=" ")


#Functions
'''
C++
int add(int a, int b) {
    return a + b;
}
'''
#Python
def add(a, b):
    return a + b


#✔ No type declarations


#Common Conversion Mistakes ❌
'''
| C++ Habit | Python Fix  |
| --------- | ----------- |
| `i++`     | `i += 1`    |
| `{ }`     | Indentation |
| `;`       | ❌ Not used |
| `cin >>`  | `input()`   |
| `cout <<` | `print()`   |
'''


'''
C++ → Python LOGIC Conversion (Advanced)
🧠 1️⃣ Think in Patterns, Not Lines
Most C++ code fits into these logic patterns:

| C++ Pattern   | Python Equivalent |
| ------------- | ----------------- |
| Loop + index  | Direct iteration  |
| Array + size  | List              |
| STL algo      | Built-in function |
| Pointer       | Reference         |
| Manual memory | Automatic         |
'''




#Loop + Index → Direct Iteration
'''
C++ (index-based)
for(int i = 0; i < n; i++) {
    cout << arr[i] << " ";
}
'''
#Python (element-based)
for x in arr:
    print(x, end=" ")

'''
✔ Less bug-prone
✔ No index errors
'''


#Need Index? Use enumerate
'''
C++
for(int i = 0; i < n; i++) {
    cout << i << " " << arr[i];
}
'''
#Python
for i, val in enumerate(arr):
    print(i, val)





#STL Algorithms → Python Built-ins
#Find max
'''
C++
int mx = arr[0];
for(int i = 1; i < n; i++) {
    if(arr[i] > mx) mx = arr[i];
}
'''
#Python
mx = max(arr)



#Sort
'''
C++
sort(arr.begin(), arr.end());
'''
#Python
arr.sort()
# OR
sorted_arr = sorted(arr)




# Reverse Logic
'''
C++
reverse(arr.begin(), arr.end());
'''
#Python
arr.reverse()
# OR
arr[::-1]






# Searching
#Linear Search
'''
C++
bool found = false;
for(int i = 0; i < n; i++) {
    if(arr[i] == key) {
        found = true;
        break;
    }
}
'''
# Python
found = key in arr




# Counting Frequency
'''
C++
int cnt = 0;
for(int i = 0; i < n; i++) {
    if(arr[i] == x) cnt++;
}
'''
#Python
cnt = arr.count(x)





#Pointers → Python References
'''
C++
void change(int* p) {
    *p = 10;
}
'''
#Python
def change(lst):
    lst[0] = 10

#📌 Python passes object references




#2D-Arrays → Nested Lists
'''
C++
int a[2][3] = {{1,2,3},{4,5,6}};
'''
#Python
a = [
    [1, 2, 3],
    [4, 5, 6]
]


#Traversal:
for row in a:
    for val in row:
        print(val)




#Common Algorithms Conversion
#Fibonacci
'''
C++
int a = 0, b = 1;
for(int i = 0; i < n; i++) {
    cout << a << " ";
    int c = a + b;
    a = b;
    b = c;
}
'''

#Python
a, b = 0, 1
for _ in range(n):
    print(a, end=" ")
    a, b = b, a + b






#Reverse Number
'''
C++
int rev = 0;
while(n > 0) {
    rev = rev * 10 + n % 10;
    n /= 10;
}
'''
#Python
rev = 0
while n > 0:
    rev = rev * 10 + n % 10
    n //= 10





#Index-Driven Logic → Value-Driven Logic
'''
C++ mindset
for(int i = 0; i < n; i++) {
    if(arr[i] % 2 == 0)
        cout << arr[i];
}
'''
#Python mindset
for x in arr:
    if x % 2 == 0:
        print(x)

'''
✔ Index removed
✔ Logic unchanged
'''






#Nested Loops → Pythonic Patterns
'''
C++ (2D traversal)
for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
        cout << a[i][j];
    }
}
'''
#Python
for row in matrix:
    for val in row:
        print(val)







#Condition + Loop → Built-ins
'''
C++: Count evens
int cnt = 0;
for(int i = 0; i < n; i++) {
    if(arr[i] % 2 == 0) cnt++;
}
'''
#Python
cnt = sum(1 for x in arr if x % 2 == 0)

#📌 Python expresses intent, not mechanics








#if-else Ladders → Ternary
'''
C++
if(a > b)
    max = a;
else
    max = b;
'''
# Python
max_val = a if a > b else b






#Switch-Case → Dictionary
'''
C++
switch(x) {
    case 1: cout << "One"; break;
    case 2: cout << "Two"; break;
}
'''
#Python
options = {
    1: "One",
    2: "Two"
}
print(options.get(x, "Invalid"))







#Recursion Conversion
'''
C++: Factorial
int fact(int n) {
    if(n == 0) return 1;
    return n * fact(n - 1);
}
'''
#Python
def fact(n):
    if n == 0:
        return 1
    return n * fact(n - 1)

#📌 Same logic, cleaner syntax








#Pass by Value vs Reference
'''
C++
void f(int x) {
    x = 10;
}
'''
#✔ Original unchanged
# Python
def f(x):
    x = 10

#✔ Original unchanged (immutable)

# But with list (like pointer)
def f(lst):
    lst[0] = 99

#📌 Lists behave like C++ pointers











#Python Traps for C++ Programmers
#❌ Loop mistake
for i in range(len(arr)):
    print(arr[i])

#✔ Better
for x in arr:
    print(x)

#❌ Copy mistake
b = a   # NOT a copy

#✔ Correct
b = a.copy()







#“Loop + Flags” → Pythonic Truth Checks
'''
C++ style (flag variable)
bool found = false;
for(int i = 0; i < n; i++) {
    if(arr[i] == key) {
        found = true;
        break;
    }
}
'''
#Python style (no flag)
found = key in arr

#📌 Python lets you ask the question directly








# Manual Accumulators → Built-ins
'''
C++: Sum
int sum = 0;
for(int i = 0; i < n; i++) sum += arr[i];
'''
#Python
total = sum(arr)


'''
C++: Min / Max
int mn = arr[0], mx = arr[0];
'''
#Python
mn, mx = min(arr), max(arr)










# Nested Conditions → Short Expressions
'''
C++
if(a > b && a > c)
    max = a;
else if(b > c)
    max = b;
else
    max = c;
'''
# Python
max_val = max(a, b, c)










# Multiple Assignments (Huge Python Advantage)
'''
C++
int temp = a;
a = b;
b = temp;
'''
#Python
a, b = b, a













# Sliding Window Pattern
'''
C++: Sum of subarray of size k
int sum = 0;
for(int i = 0; i < k; i++) sum += arr[i];

for(int i = k; i < n; i++) {
    sum += arr[i] - arr[i-k];
}
'''
#Python
window_sum = sum(arr[:k])

for i in range(k, len(arr)):
    window_sum += arr[i] - arr[i-k]







# Frequency Count
'''
C++
map<int,int> mp;
for(int i = 0; i < n; i++)
    mp[arr[i]]++;
'''
# Python
from collections import Counter
freq = Counter(arr)








# Set Logic (Duplicates / Uniqueness)
'''
C++: Remove duplicates
set<int> s(arr, arr+n);
'''
#Python
unique = list(set(arr))

#📌 Order matters?
unique = list(dict.fromkeys(arr))










#String Logic Conversion
'''
C++: Reverse string
reverse(s.begin(), s.end());
'''
#Python
s = s[::-1]

'''
C++: Palindrome check
if(s == string(s.rbegin(), s.rend()))
'''
#Python
if s == s[::-1]:










# Common Python Surprises (for C++ devs)
#❌ Loop variable leaks
#❌ Surprise 1: Loop variable “leaks” (NOT an error)
for i in range(3):
    pass

print(i)   # prints 2


#Equivalent C++ (different behavior)
'''
for(int i = 0; i < 3; i++) {}
cout << i;   // ❌ ERROR: i not declared
'''

#Python equivalent
i = 0
for i in range(3):
    pass

print(i)   # 2


#But if we avoid initializing i before loop
i = None
for i in range(3):
    pass

print(i)   # 2


#❌ Surprise 2: Mutable default argument (REAL logical bug)
def f(x=[]):   # dangerous
    x.append(1)
    return x

print(f())
print(f())
'''
Output
[1]
[1, 1]
'''




#✔ Correct Way (No Bug)
def f(x=None):
    if x is None:
        x = []
    x.append(1)
    return x
'''
Output
[1]
[1]
'''


# Debugging Mindset Shift
'''
C++
cout << i;
'''
#Python
print(i)

# But Python also offers:
print(type(i))
print(len(arr))