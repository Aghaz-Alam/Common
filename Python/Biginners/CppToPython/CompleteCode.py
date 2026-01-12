#1️⃣ Basic Structure
'''
C++
#include <iostream>
using namespace std;
int main() {
    cout << "Hello World";
    return 0;
}
'''
# Python
def main():
    print("Hello World")

if __name__ == "__main__":
    main()

'''
🖥 Output
Hello World
'''




# Variables & Data Types
'''
C++
#include <iostream>
using namespace std;
int main() {
    int a = 10;
    float b = 2.5;
    string name = "Aman";

    cout << a << " " << b << " " << name;
    return 0;
}
'''
#Python
def main():
    a = 10
    b = 2.5
    name = "Aman"
    print(a, b, name)

if __name__ == "__main__":
    main()

'''
🖥 Output
10 2.5 Aman
'''



#for Loop
'''
C++
#include <iostream>
using namespace std;
int main() {
    for(int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    return 0;
}
'''
# Python
def main():
    for i in range(5):
        print(i, end=" ")

if __name__ == "__main__":
    main()

'''
🖥 Output
0 1 2 3 4
'''







# while Loop
'''
C++
#include <iostream>
using namespace std;
int main() {
    int i = 1;
    while(i <= 5) {
        cout << i << " ";
        i++;
    }
    return 0;
}
'''
# Python
def main():
    i = 1
    while i <= 5:
        print(i, end=" ")
        i += 1

if __name__ == "__main__":
    main()

'''
🖥 Output
1 2 3 4 5
'''








# Conditional Statements
'''
C++
#include <iostream>
using namespace std;
int main() {
    int a = 10, b = 5;

    if(a > b) {
        cout << "A is greater";
    } else {
        cout << "B is greater";
    }
    return 0;
}
'''
# Python
def main():
    a, b = 10, 5
    if a > b:
        print("A is greater")
    else:
        print("B is greater")

if __name__ == "__main__":
    main()

'''
🖥 Output
A is greater
'''






# Input / Output
'''
C++
#include <iostream>
using namespace std;
int main() {
    int x;
    cin >> x;
    cout << x;
    return 0;
}
'''
#Python
def main():
    x = int(input())
    print(x)

if __name__ == "__main__":
    main()

'''
🖥 Input
7

🖥 Output
7
'''





# Arrays → Lists
'''
C++
#include <iostream>
using namespace std;
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    cout << arr[0];
    return 0;
}
'''
# Python
def main():
    arr = [1, 2, 3, 4, 5]
    print(arr[0])

if __name__ == "__main__":
    main()

'''
🖥 Output
1
'''






# Sum of Array Elements
'''
C++
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4,5};
    int sum = 0;

    for(int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    cout << sum;
    return 0;
}
'''
# Python
def main():
    arr = [1,2,3,4,5]
    total = 0
    for x in arr:
        total += x
    print(total)

if __name__ == "__main__":
    main()

'''
🖥 Output
15
'''










# Prime Number Check
'''
C++
#include <iostream>
using namespace std;
int main() {
    int n = 7;
    bool prime = true;

    for(int i = 2; i < n; i++) {
        if(n % i == 0) {
            prime = false;
            break;
        }
    }

    cout << (prime ? "Prime" : "Not Prime");
    return 0;
}
'''
# Python
def main():
    n = 7
    prime = True

    for i in range(2, n):
        if n % i == 0:
            prime = False
            break

    print("Prime" if prime else "Not Prime")

if __name__ == "__main__":
    main()

'''
🖥 Output
Prime
'''









# break / continue
'''
C++
#include <iostream>
using namespace std;
int main() {
    for(int i = 1; i <= 10; i++) {
        if(i % 3 == 0)
            continue;
        cout << i << " ";
    }
    return 0;
}
'''
# Python
def main():
    for i in range(1, 11):
        if i % 3 == 0:
            continue
        print(i, end=" ")

if __name__ == "__main__":
    main()

'''
🖥 Output
1 2 4 5 7 8 10
'''














# Functions
'''
C++
#include <iostream>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int main() {
    cout << add(3, 4);
    return 0;
}
'''

#Python
def add(a, b):
    return a + b

def main():
    print(add(3, 4))

if __name__ == "__main__":
    main()

'''
🖥 Output
7
'''











#BASIC PROGRAMS
#(Syntax, control flow, collections)
#1️⃣ Variables & Constants
'''
C++
#include <iostream>
using namespace std;
int main() {
    const int x = 10;
    cout << x;
    return 0;
}
'''
#Python
def main():
    x = 10   # convention: constants in CAPS
    print(x)

if __name__ == "__main__":
    main()
'''
🖥 Output
10
'''



#2️⃣ Arrays / Lists Traversal
'''
C++
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3};
    for(int i = 0; i < 3; i++)
        cout << arr[i] << " ";
    return 0;
}
'''
# Python
def main():
    arr = [1,2,3]
    for x in arr:
        print(x, end=" ")

if __name__ == "__main__":
    main()
'''
🖥 Output
1 2 3
'''


#3️⃣ String Handling
'''
C++
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "Hello";
    cout << s.length();
    return 0;
}
'''
# Python
def main():
    s = "Hello"
    print(len(s))

if __name__ == "__main__":
    main()

'''
🖥 Output
5
'''



#🟡 INTERMEDIATE PROGRAMS
#(STL, functions, classes, memory models)

#4️⃣ Vector vs List
'''
C++
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1,2,3};
    v.push_back(4);
    for(int x : v)
        cout << x << " ";
    return 0;
}
'''
#Python
def main():
    v = [1,2,3]
    v.append(4)
    for x in v:
        print(x, end=" ")

if __name__ == "__main__":
    main()
'''
🖥 Output
1 2 3 4
'''

#5️⃣ Map vs Dictionary
'''
C++
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int,string> mp;
    mp[1] = "One";
    cout << mp[1];
    return 0;
}
'''
#Python
def main():
    mp = {1: "One"}
    print(mp[1])

if __name__ == "__main__":
    main()
'''
🖥 Output
One
'''

#6️⃣ Function Overloading → Default Arguments
'''
C++
#include <iostream>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int add(int a, int b, int c) {
    return a + b + c;
}
int main() {
    cout << add(1,2) << " " << add(1,2,3);
    return 0;
}
'''
# Python
def add(a, b, c=0):
    return a + b + c

def main():
    print(add(1,2), add(1,2,3))

if __name__ == "__main__":
    main()
'''
🖥 Output
3 6
'''



#7️⃣ Class & Object
'''
C++
#include <iostream>
using namespace std;
class Person {
public:
    string name;
    void greet() {
        cout << "Hello " << name;
    }
};
int main() {
    Person p;
    p.name = "Aman";
    p.greet();
    return 0;
}
'''
# Python
class Person:
    def __init__(self, name):
        self.name = name

    def greet(self):
        print("Hello", self.name)

def main():
    p = Person("Aman")
    p.greet()

if __name__ == "__main__":
    main()

'''
🖥 Output
Hello Aman
'''

#🔵 ADVANCED PROGRAMS
#(Modern C++, algorithms, memory, concurrency concepts)

#8️⃣ Lambda Functions
'''
C++
#include <iostream>
using namespace std;
int main() {
    auto add = [](int a, int b) {
        return a + b;
    };
    cout << add(3,4);
    return 0;
}
'''
# Python
def main():
    add = lambda a, b: a + b
    print(add(3,4))

if __name__ == "__main__":
    main()
'''
🖥 Output
7
'''

#9️⃣ Smart Pointers → Automatic Memory
'''
C++
#include <iostream>
#include <memory>
using namespace std;
int main() {
    unique_ptr<int> p = make_unique<int>(10);
    cout << *p;
    return 0;
}
'''
# Python
def main():
    p = 10
    print(p)

if __name__ == "__main__":
    main()
'''
🖥 Output
10
'''

# 🔟 STL Algorithm → Python Built-in
'''
C++
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int arr[] = {1,2,3,4};
    cout << count(arr, arr+4, 2);
    return 0;
}
'''
# Python
def main():
    arr = [1,2,3,4]
    print(arr.count(2))

if __name__ == "__main__":
    main()

'''
🖥 Output
1
'''


# 1️⃣1️⃣ Exception Handling
'''
C++
#include <iostream>
using namespace std;
int main() {
    try {
        throw 10;
    } catch(int e) {
        cout << e;
    }
    return 0;
}
'''
# Python
def main():
    try:
        raise Exception(10)
    except Exception as e:
        print(e)

if __name__ == "__main__":
    main()
'''
🖥 Output
10
'''


# 1️⃣2️⃣ Multithreading (Conceptual)
'''
C++
#include <iostream>
#include <thread>
using namespace std;
void task() {
    cout << "Hello from thread";
}
int main() {
    thread t(task);
    t.join();
    return 0;
}
'''
# Python
import threading
def task():
    print("Hello from thread")

def main():
    t = threading.Thread(target=task)
    t.start()
    t.join()

if __name__ == "__main__":
    main()
'''
🖥 Output
Hello from thread
'''






# ❌ Surprise 14: Immutable integers modified via list
def modify(lst):
    lst[0] += 100   # modifies the first element of the list    
def main():
    n = [1, 2, 3]   # list containing an integer
    modify(n)
    print(n)    
if __name__ == "__main__":
    main()      

'''
🖥 Output
[101, 2, 3]
🧠 Reason: 
In Python, lists are mutable objects. 
When you pass a list to a function, you're passing a reference to the same list object in memory. 
Modifying an element of the list inside the function modifies the original list.
'''





#❌ Surprise 22: Dictionary insertion order
def main():
    d = {}
    d['a'] = 1
    d['b'] = 2
    d['c'] = 3

    for key in d:
        print(key, end=" ")     
if __name__ == "__main__":
    main()  
''' 
🖥 Output
a b c   
🧠 Reason:  
➡ Python 3.7+ maintains insertion order in dictionaries
'''






#📌 Python passes object references 
def modify(lst):
    lst[0] += 100   # modifies the first element of the list    
def main():
    n = [1, 2, 3]   # list containing an integer
    modify(n)
    print(n)    
if __name__ == "__main__":
    main()  
'''
🖥 Output
[101, 2, 3]
🧠 Reason:
In Python, lists are mutable objects. When you pass a list to a function, you're passing a reference to the same list object in memory. Modifying an element of the list inside the function modifies the original list.
''' 



#📌 C++ passes by value (copies)    
def modify(n):
    n += 100   # modifies local copy    
def main():
    n = 1
    modify(n)
    print(n)    
if __name__ == "__main__":
    main()  
''' 
🖥 Output
1
🧠 Reason:
In C++, when you pass a variable to a function, it's passed by value, meaning a copy is made. Modifying the copy inside the function doesn't affect the original variable.
''' 





#2D-Arrays → Nested Lists
''' 
C++
#include <iostream>
using namespace std;
int main() {
    int arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
'''
# Python
def main():
    matrix = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ]

    for row in matrix:
        for val in row:
            print(val, end=" ")
        print()     
if __name__ == "__main__":
    main()  

'''
🖥 Output   
1 2 3
4 5 6
7 8 9
''' 



#Common Algorithms Conversion
#Fibonacci
'''         
C++ 
#include <iostream>
using namespace std;
int main() {
    int n = 10; 
    int a = 0, b = 1;   
    for(int i = 0; i < n; i++) {
        cout << a << " ";
        int c = a + b;
        a = b;
        b = c;
    }
    return 0;   
}
'''
#Python
def main():
    n = 10
    a, b = 0, 1
    for _ in range(n):
        print(a, end=" ")
        a, b = b, a + b 
if __name__ == "__main__":
    main()  
''' 
🖥 Output   
0 1 1 2 3 5 8 13 21 34 
'''



