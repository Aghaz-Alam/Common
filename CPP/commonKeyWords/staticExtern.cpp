//static vs extern in C++
1️⃣ Basic dea (One-Line Difference)
static restricts visibility (internal linkage), while extern extends visibility (external linkage).

2️⃣ Meaning of static and extern
🔹 static
Limits the scope of a variable/function
Prevents access from other source files
Used for encapsulation

🔹 extern
Declares a variable/function defined elsewhere
Used to share data across files

3️⃣ Key Differences Table (Interview Favorite)
| Feature                     | `static`            | `extern`              |
| --------------------------- | ------------------- | --------------------- |
| Purpose                     | Restrict visibility | Share variables       |
| Linkage                     | Internal linkage    | External linkage      |
| Scope                       | File / Block        | Global (across files) |
| Lifetime                    | Entire program      | Entire program        |
| Memory                      | Data segment        | Data segment          |
| Initialization              | Once                | Once                  |
| Default value               | Zero                | Zero                  |
| Multiple definitions        | Allowed (per file)  | Not allowed           |
| Used in multi-file programs | Yes (for hiding)    | Yes (for sharing)     |



4️⃣ Static Variable Example (Single File)
#include <iostream>
using namespace std;
static int x = 10;  // File-level static
void show() {
    x++;
    cout << "x = " << x << endl;
}
int main() {
    show();
    show();
    return 0;
}
/* 
🔹 Output
x = 11
x = 12

🔹 Explanation
x is visible only in this file
Retains value between function calls
*/

5️⃣ Extern Variable Example (Multi-File)
//🔹 File 1: file1.cpp
#include <iostream>
using namespace std;
int x = 100;   // Definition
void display() {
    cout << "x = " << x << endl;
}



//🔹 File 2: file2.cpp
#include <iostream>
using namespace std;
extern int x;   // Declaration
void display();
int main() {
    display();
    x += 50;
    display();
    return 0;
}
/* 
🔹 Output
x = 100
x = 150
*/
🔹 Explanation
extern tells compiler variable exists elsewhere
Same memory shared across files
Only one definition allowed

6️⃣ Static vs Extern (Multi-File Conflict Example)
❌ Without static (Problem)
// file1.cpp
int x = 10;

// file2.cpp
int x = 20;

❌ Linker Error: Multiple definitions of x

✅ With static (Solution)
// file1.cpp
static int x = 10;
// file2.cpp
static int x = 20;

✔ No conflict
✔ Each file has its own copy

7️⃣ Memory & Linkage Diagram
Data Segment
----------------------------------
static x (file1 only)
static x (file2 only)
extern x (shared)
----------------------------------

8️⃣ Static vs Extern Functions
🔹 Static Function (Hidden)
static void fun() {
    cout << "Static function" << endl;
}


✔ Accessible only in same file
✔ Used for helper functions

🔹 Extern Function (Shared)
extern void fun();


✔ Accessible across files
✔ Default behavior of functions is extern

9️⃣ Interview Questions & Answers ⭐
❓ Q1: What problem does extern solve?
Answer:
It allows multiple source files to share the same global variable or function.

❓ Q2: Why is static preferred over global variables?
Answer:
Because it limits scope, prevents name clashes, and improves code safety.

❓ Q3: Can extern variables be initialized?
Answer:
✔ Yes, but only in one file

extern int x;  // declaration
int x = 10;    // definition

❓ Q4: Where are static and extern variables stored?
Answer:
✔ Data segment (not stack)

❓ Q5: What happens if extern variable is defined twice?

Answer:
❌ Linker error (multiple definition)



❓ Q6: Difference between declaration and definition?
| Declaration     | Definition       |
| --------------- | ---------------- |
| Tells compiler  | Allocates memory |
| `extern int x;` | `int x = 10;`    |


10️⃣ When to Use What (Practical Rule)
✅ Use static when:
You want file-level encapsulation
Avoid name clashes
Writing libraries

✅ Use extern when:
Sharing variables/functions across files
Working on large projects

11️⃣ One-Line Interview Summary ⭐⭐⭐
static hides identifiers within a file, while extern exposes identifiers across files by sharing the same memory location.