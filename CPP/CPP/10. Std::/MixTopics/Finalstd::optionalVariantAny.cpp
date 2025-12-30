C++17: More compile-time, fewer heap allocations
C++17 encourages stack or static allocations by enabling more compile-time evaluation.

✔ Relevant improvements
1. std::optional, std::variant, std::any
---> These types avoid heap allocation unless necessary.
/* ---------------------------- */
✅ 1. std::optional — Represent “maybe value / maybe no value”
Why do we need std::optional?
Before C++17, we returned:
---> sentinel values (like -1, 0, NULL)
---> error codes
---> bool + output parameter
---> This was unsafe or unclear.

std::optional<T> represents:
---> A value of type T, OR nothing.

Use cases
---> Function might return a value OR not (search, find, parse)
---> Avoid returning pointers or special error values
---> Cleaner & safer code

✅ Example Program: Using std::optional for find()
#include <iostream>
#include <optional>
#include <vector>
using namespace std;
optional<int> findNumber(const vector<int>& data, int target) {
    for (int x : data) {
        if (x == target)
            return x;  // found → return value
    }
    return nullopt;  // not found
}
int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    auto result = findNumber(nums, 3);
    if (result.has_value()) {                          //result.has_value()
        cout << "Found number: " << *result << endl;
    } else {
        cout << "Number not found!" << endl;
    }
}
/* 
Output:
Found number: 3

✔ Explanation
optional<int> means the function might return an integer.
nullopt means “no result”.
No need for:
returning -1
returning NULL

output parameters
→ Much safer & clear.
 */


//result and result.has_value() ---both are same
#include <iostream>
#include <optional>
#include <vector>
using namespace std;
optional<int> findNumber(const vector<int>& data, int target) {
    for (int x : data) {
        if (x == target)
            return x;  // found → return value
    }
    return nullopt;  // not found
}
int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    auto result = findNumber(nums, 3);
    if (result) {             //result.has_value() or result both works 
        cout << "Found number: " << *result << endl;
    } else {
        cout << "Number not found!" << endl;
    }
}
/*
Output:
Found number: 3
*/


//result and result.has_value() ---both are same
#include<iostream>
#include<optional>
#include<vector>
using namespace std;
optional<int> findNumber(const vector<int>& v, int target){
    for(int x: v){
        if(x == target)
            return x;                       //return optional<int>(x);
    }
    return nullopt;                         //nullopt means “no value”
}
int main(){
    vector<int> v = {1,2,3,4,5};
    auto result = findNumber(v, 4);         //optional<int> result;
    if(result){                            //result.has_value()
        cout<<"Number found: "<<*result<<endl;  //result is an optional object, *result accesses the contained value
    }
    else{
        cout<<"Number not found!"<<endl;
    }
  return 0;
}
/* 
umber found: 4
 */



/* ======================================================= */
1️⃣ SEARCH use-case 
🔍 Search in a container (element may or may not exist)
✅ Program: Using std::optional for search()
#include <iostream>
#include <optional>
#include <vector>
using namespace std;
optional<int> searchElement(const vector<int>& arr, int key) {
    for (int x : arr) {
        if (x == key)
            return x;   // found
    }
    return nullopt;      // not found
}
int main() {
    vector<int> data = {10, 20, 30, 40};
    auto result = searchElement(data, 25);

    if (result)
        cout << "Element found: " << *result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
/* 
🖥 Output
Element not found

✔ Explanation
optional<int> → function may return an int or nothing
nullopt → explicitly represents absence of value
Caller must check before using the result

❌ Old bad approach
return -1;   // what if -1 is valid?
*/

/* ======================================================= */
2️⃣ FIND use-case
🔎 Find index of an element
✅ Program: Using std::optional for find()
#include <iostream>
#include <optional>
#include <vector>
using namespace std;
optional<size_t> findIndex(const vector<int>& arr, int key) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == key)
            return i;    // index found
    }
    return nullopt;      // index not found
}
int main() {
    vector<int> nums = {5, 15, 25, 35};

    auto idx = findIndex(nums, 25);

    if (idx)                                    //idx or idx.has_value() ---both are the same
        cout << "Found at index: " << idx.value() << endl;
    else
        cout << "Value not found" << endl;

    return 0;
}
/* 
🖥 Output
Found at index: 2

✔ Explanation
Index may not exist, so optional<size_t> is perfect
.value() or *idx safely accesses value after check

❌ Avoid
return -1; // invalid index, unsafe


✅ Correct ways to access value
*idx                 // direct (unsafe if empty)
idx.value()          // throws exception if empty
idx.value_or(-1)     // safe default

*/


/* ======================================================= */
3️⃣ PARSE use-case
🧾 Parse string → int (conversion may fail)
✅ Program: Using std::optional for parse()
#include <iostream>
#include <optional>
#include <string>
using namespace std;
optional<int> parseInt(const string& s) {
    try {
        return stoi(s);   // success
    } catch (...) {
        return nullopt;   // parse failed
    }
}
int main() {
    string input = "123x";

    auto value = parseInt(input);

    if (value)
        cout << "Parsed value: " << *value << endl;
    else
        cout << "Invalid integer string" << endl;

    return 0;
}
/* 
🖥 Output
Invalid integer string

✔ Explanation
Parsing can fail → optional expresses that possibility
No exceptions leaking to caller
Cleaner than error codes

❌ Old style
int x;
bool ok = parse(x);   // output parameter 😖
*/
/* ===================================================================================================================== */

✅ 2. std::variant — A type-safe union (store one of many types)
Why do we need std::variant?
Before C++17, we used:
---> unions (unsafe, no type checking)
---> class hierarchies
---> void pointers (unsafe)
---> std::variant lets a variable hold one of multiple types, checked at runtime.

Use cases
---> Number/string hybrid values (JSON, settings)
---> Representing states: Loading, Success, Error
---> Replaces unsafe unions

✅ Example Program: Calculator input (int OR double OR string)
#include <iostream>
#include <variant>
#include <string>
using namespace std;
void printValue(const variant<int, double, string>& v) {
    visit([](auto&& arg) {
        cout << "Value: " << arg << endl;
    }, v);
}
int main() {
    variant<int, double, string> value;
    value = 10;
    printValue(value);

    value = 3.14;
    printValue(value);

    value = "Hello Variant!";
    printValue(value);
}

✔ Explanation
---> The variable value can store:
---> int OR double OR string
---> visit() automatically calls correct function depending on the stored type.
---> Safe, checked at compile-time.



✅ 3. std::any — Store any type at runtime
Why do we need std::any?
---> Sometimes you don’t know the type until runtime.
---> It is like a “type-safe void pointer”.
---> Unlike variant, it can store any type (not fixed list).

Use cases
---> Plugin systems
---> Mixed-type containers
---> Runtime type inspection
---> When variant types are not known at compile-time

✅ Example Program: Mixed-type storage using std::any
#include <iostream>
#include <any>
#include <string>
using namespace std;
int main() {
    any data;

    data = 42;
    cout << "Stored int: " << any_cast<int>(data) << endl;

    data = string("Hello any!");
    cout << "Stored string: " << any_cast<string>(data) << endl;

    // Safe type checking
    if (data.type() == typeid(string)) {
        cout << "data currently holds a string" << endl;
    }
}

✔ Explanation
---> any can hold any type.
---> any_cast throws exception if type mismatched.
---> More flexible than variant but less type-safe.
/* ---------------------------- */
#include <iostream>
#include <any>
#include <string>
using namespace std;
int main() {
    any data;

    data = 42;
    cout << "Stored int: " << any_cast<int>(data) << endl;

    data = 4.2;
    cout << "Stored double: " << any_cast<double>(data) << endl;

    data = 4.2f;
    cout << "Stored float: " << any_cast<float>(data) << endl;

    data = string("Hello any!");
    cout << "Stored string: " << any_cast<string>(data) << endl;

    // Safe type checking
    if (data.type() == typeid(string)) {
        cout << "data currently holds a string" << endl;
    }
}
/* 
Stored int: 42
Stored double: 4.2
Stored float: 4.2
Stored string: Hello any!
data currently holds a string
*/