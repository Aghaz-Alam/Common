//Global Variable vs Static Variable in C++
/* 
1️⃣ Global Variable
🔹 Definition
A global variable is declared outside all functions and classes.
It is accessible throughout the program (after its declaration).

🔹 Syntax
int x = 10;   // Global variable

🔹 Characteristics of Global Variables
| Feature         | Description                                    |
| --------------- | ---------------------------------------------- |
| Scope           | Entire program (all files if `extern` is used) |
| Lifetime        | Entire program execution                       |
| Default Value   | Zero (if not initialized)                      |
| Memory Location | Data Segment                                   |
| Accessibility   | Can be accessed by any function                |
| Risk            | Can be modified accidentally (less safe)       |

 */
//🔹 Example: Global Variable
#include <iostream>
using namespace std;
int g = 10;   // Global variable
void show() {
    g = g + 5;
    cout << "Inside show(): g = " << g << endl;
}
int main() {
    cout << "In main before show(): g = " << g << endl;
    show();
    cout << "In main after show(): g = " << g << endl;
  return 0;
}
/* 
🔹 Output
In main before show(): g = 10
Inside show(): g = 15
In main after show(): g = 15

🔹 Explanation
g is accessible everywhere
Changes in one function affect all others
Value persists throughout program execution
*/



/* 
2️⃣ Static Variable
🔹 Definition
A static variable preserves its value between function calls and has limited scope depending on where it is declared.

🔹 Types of Static Variables
Static local variable
Static global variable (file scope)
Static class member (advanced topic)

3️⃣ Static Local Variable
🔹 Syntax
static int x = 0;

🔹 Characteristics of Static Local Variables
| Feature         | Description                  |
| --------------- | ---------------------------- |
| Scope           | Only within the function     |
| Lifetime        | Entire program execution     |
| Default Value   | Zero                         |
| Memory Location | Data Segment                 |
| Value Retention | Yes (between function calls) |
| Safety          | Safer than globals           |
*/


//🔹 Example: Static Local Variable
/*
#include <iostream>
using namespace std;
void counter() {
    static int count = 0;  // Static variable
    count++;
    cout << "Count = " << count << endl;
}
int main() {
    counter();
    counter();
    counter();
    return 0;
}
/* 
🔹 Output
Count = 1
Count = 2
Count = 3

🔹 Explanation
count is initialized only once
Value is preserved across function calls
Scope is restricted to counter()
*/

/* 

//4️⃣ Global vs Static (Local) Variable — Key Differences
| Feature         | Global Variable       | Static Variable            |
| --------------- | --------------------- | -------------------------- |
| Declaration     | Outside all functions | Inside function / file     |
| Scope           | Entire program        | Limited (function or file) |
| Lifetime        | Entire program        | Entire program             |
| Memory          | Data segment          | Data segment               |
| Value retention | Always                | Yes (for static local)     |
| Safety          | Low                   | Higher                     |
| Initialization  | Once                  | Once                       |
| Access Control  | No restriction        | Restricted                 |

 */


/*
 //5️⃣ Static Global Variable (File Scope)
🔹 Definition
A global variable declared with static keyword becomes file-private.

🔹 Example
static int x = 50;  // Accessible only in this file

✔ Prevents name clashes in large projects
✔ Used in multi-file programs

6️⃣ Memory Diagram (Conceptual)
Data Segment
------------
Global Variables
Static Variables

Stack
------------
Local Variables

Heap
------------
Dynamic Memory

7️⃣ Interview Perspective (VERY IMPORTANT)
🔹 Common Interview Questions & Answers
❓ Q1: What is the main difference between global and static variables?

Answer:

Global variables have global scope

Static variables have restricted scope

Both have program-long lifetime

❓ Q2: Why are static variables preferred over global variables?

Answer:

Prevent accidental modification

Better encapsulation

Reduce namespace pollution

Safer and more maintainable code

❓ Q3: Are static variables stored in stack?

Answer:
❌ No
✔ Stored in data segment, not stack

❓ Q4: Can static variables be accessed outside a function?

Answer:
❌ Static local → NO
✔ Static global → Only within same file

❓ Q5: What happens if static variable is not initialized?

Answer:

Automatically initialized to zero

❓ Q6: Can static variables be destroyed?

Answer:

Destroyed only when program ends

8️⃣ When to Use What?
✅ Use Global Variables When:

Configuration constants

Rarely modified shared data

Small programs

✅ Use Static Variables When:

Counting function calls

Caching values

Encapsulation is required

Large projects

9️⃣ One-Line Interview Summary ⭐
Global variables have global scope and lifetime, 
while static variables have restricted scope but the same lifetime, making static variables safer and more controlled.

*/