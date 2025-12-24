1. Basic std::string Usage (C++11 onwards)
Example 1: Basic operations
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Basic string declaration
    string str1 = "Hello";
    string str2("World");

    // Concatenation
    string str3 = str1 + " " + str2;

    // Access individual characters
    cout << "First character of str3: " << str3[0] << endl;

    // Length of the string
    cout << "Length of str3: " << str3.size() << endl;

    // Iterating over a string
    cout << "Characters in str3: ";
    for (char c : str3) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}

Output:
First character of str3: H
Length of str3: 11
Characters in str3: H e l l o   W o r l d 


Explanation:
std::string is part of <string> and can be declared via assignment or constructor.
Concatenation uses +.
Access characters with [] or at().
size() or length() gives the number of characters.
Range-based for loop works for iteration.
















2. String Initialization in C++11
C++11 introduced uniform initialization {}.

#include <iostream>
#include <string>
using namespace std;

int main() {
    string str1{"Hello"};       // Uniform initialization
    string str2{"World", 3};    // First 3 characters from "World"

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;

    return 0;
}


Output:

str1: Hello
str2: Wor


Explanation:
You can initialize using curly braces {}.
Second example shows partial copy initialization.













3. String Operations
Append
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello";
    s.append(" World");  // Append string
    cout << s << endl;

    s += "!";            // Another way to append
    cout << s << endl;

    return 0;
}


Output:

Hello World
Hello World!



















Insert
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello World";
    s.insert(5, ","); // Insert "," at position 5
    cout << s << endl;

    return 0;
}
/* 
Output:
Hello, World
*/








Replace
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "Hello World";
    s.replace(6, 5, "C++"); // Replace 5 characters starting from index 6
    cout << s << endl;

    return 0;
}
/* 
Output:
Hello C++
*/
















Erase
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "Hello, World!";
    s.erase(5, 1); // Remove comma
    cout << s << endl;

    return 0;
}
/* 
Output:
Hello World!
*/
















Substring (substr)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello World";
    string sub = s.substr(6, 5); // Get 5 characters starting from index 6
    cout << "Substring: " << sub << endl;

    return 0;
}
/* 
Output:
Substring: World
*/



Find
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello World";
    size_t pos = s.find("World");
    if (pos != string::npos) {
        cout << "'World' found at position: " << pos << endl;
    } else {
        cout << "'World' not found" << endl;
    }

    return 0;
}
/* 
Output:
'World' found at position: 6
*/



//std::string::npos is a special constant used to indicate “not found.”
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello World";
    size_t pos = text.find("World");

    if (pos != string::npos) {
        cout << "\"World\" found at index: " << pos << endl;
    } else {
        cout << "\"World\" not found\n";
    }

    // Try finding something not present
    size_t pos2 = text.find("XYZ");

    if (pos2 == string::npos) {
        cout << "\"XYZ\" not found (npos returned)\n";
    }

    return 0;
}
/* 
Output:
"World" found at index: 6
"XYZ" not found (npos returned)
*/









4. String Literals (C++14)
C++14 introduced user-defined literals for strings.

#include <iostream>
#include <string>
using namespace std;
using namespace std::literals; // enables ""s

int main() {
    auto s = "Hello World"s; // creates std::string
    cout << s << endl;
    cout << "Length: " << s.size() << endl;

    return 0;
}
/* 
Output:
Hello World
Length: 11


Explanation:
"Hello"s creates std::string directly without explicit constructor.
*/















5. std::string_view (C++17)
Efficient, non-owning view of a string.

#include <iostream>
#include <string_view>
using namespace std;

int main() {
    string_view sv = "Hello World"; // points to literal
    cout << "View: " << sv << endl;
    cout << "Size: " << sv.size() << endl;

    sv.remove_prefix(6); // Remove first 6 characters
    cout << "After remove_prefix: " << sv << endl;

    sv.remove_suffix(1); // Remove last character
    cout << "After remove_suffix: " << sv << endl;

    return 0;
}
/* 
Output:
View: Hello World
Size: 11
After remove_prefix: World
After remove_suffix: Worl


Explanation:
std::string_view avoids copying.
Efficient for read-only string operations.
*/
















6. std::format (C++20)
Python-style formatting for strings.

#include <iostream>
#include <format>
using namespace std;

int main() {
    int age = 25;
    string name = "Alice";

    string msg = format("Name: {}, Age: {}", name, age);
    cout << msg << endl;

    return 0;
}
/* 
Output:
Name: Alice, Age: 25


Explanation:
std::format uses {} as placeholders.
Safer and more readable than sprintf.
*/













7. New String Functions (C++20)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello C++20";

    // Check prefix, suffix, contains
    cout << boolalpha;
    cout << "Starts with 'Hello'? " << s.starts_with("Hello") << endl;
    cout << "Ends with 'C++20'? " << s.ends_with("C++20") << endl;
    cout << "Contains 'C++'? " << s.contains("C++") << endl;

    return 0;
}
/* 
Output:
Starts with 'Hello'? true
Ends with 'C++20'? true
Contains 'C++'? true


Explanation:
starts_with, ends_with, contains make string checks very intuitive. 
*/