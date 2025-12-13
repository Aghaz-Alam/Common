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
    if (result.has_value()) {
        cout << "Found number: " << *result << endl;
    } else {
        cout << "Number not found!" << endl;
    }
}

✔ Explanation
optional<int> means the function might return an integer.
nullopt means “no result”.
No need for:
returning -1
returning NULL

output parameters
→ Much safer & clear.



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