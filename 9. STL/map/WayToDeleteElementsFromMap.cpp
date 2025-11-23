1. Using erase(key)
You can use erase() with a key to remove an element from the map. 
If the key exists in the map, it removes the key-value pair. If the key does not exist, the map remains unchanged.

Syntax:
map.erase(key);

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Remove the element with key = 2
    m.erase(2);

    // Iterate and print the map
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
3 -> Cherry
*/


2. Using erase(iterator)
You can use erase() with an iterator to remove the element at the position indicated by the iterator.

Syntax:
map.erase(iterator);

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Create an iterator pointing to the element with key = 2
    auto it = m.find(2);

    // Erase the element using the iterator
    if (it != m.end()) {
        m.erase(it);
    }

    // Iterate and print the map
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
3 -> Cherry
*/


3. Using erase(iterator_first, iterator_last) (Range erase)
You can use erase() with a range of iterators to remove multiple elements from the map. 
The range is defined by two iterators: the first and the last. 
The elements in the range [iterator_first, iterator_last) will be erased.

Syntax:
map.erase(iterator_first, iterator_last);

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}, {4, "Date"}};

    // Create an iterator range from key 2 to key 4 (not inclusive of key 4)
    auto it_first = m.find(2);
    auto it_last = m.find(4);

    // Erase the range
    m.erase(it_first, it_last);

    // Iterate and print the map
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
4 -> Date

In this example, the elements with keys 2 and 3 were removed.
*/


4. Using clear()
You can use clear() to remove all elements from the map. After calling clear(), the map becomes empty, and its size becomes zero.

Syntax:
map.clear();

Example:
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Remove all elements
    m.clear();

    // Check if the map is empty
    if (m.empty()) {
        cout << "The map is empty." << endl;
    }
}
/* 
Output:

The map is empty.
*/


5. Removing Elements Using Conditional Logic
While erase works for direct removal by key or iterator, you may sometimes want to remove elements based on a condition. 
You can do this by iterating over the map and erasing elements that meet the condition.

Example: Remove elements with value "Banana":
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Iterate and erase elements that meet a condition
    for (auto it = m.begin(); it != m.end(); ) {
        if (it->second == "Banana") {
            it = m.erase(it);  // Erase and get the next iterator
        } else {
            ++it;  // Otherwise, move to the next element
        }
    }

    // Iterate and print the map
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
3 -> Cherry
*/



6. Erasing Elements with Custom Condition Using Lambda Functions (C++11 and Later)
If you are using C++11 or later, you can also use a lambda function to conditionally erase elements based on a custom predicate.

Example: Remove all elements where the value contains the letter "a":
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Remove elements where the value contains the letter "a"
    for (auto it = m.begin(); it != m.end(); ) {
        if (it->second.find('a') != string::npos) {
            it = m.erase(it);  // Erase and get the next iterator
        } else {
            ++it;
        }
    }

    // Iterate and print the map
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

3 -> Cherry
*/


7. Removing Elements Using std::remove_if with Iterators
You can use std::remove_if in conjunction with a maps iterators to erase elements that match a particular condition. 
However, std::remove_if works with containers that support random access iterators, so it is not directly usable with 
std::map since it uses bidirectional iterators. 
For this, you would still iterate manually or use erase() with the appropriate condition.

Summary of Methods to Delete Elements from a std::map:
erase(key): Removes the element with the specified key.
erase(iterator): Removes the element at the position indicated by the iterator.
erase(iterator_first, iterator_last): Removes a range of elements specified by iterators.
clear(): Removes all elements from the map.
Conditional removal (iteration): Iterate through the map and erase elements based on a condition.
Conditional removal with lambda functions (C++11 and later): Use a lambda to define the condition for removal and iterate over the map.
Using std::remove_if: While not directly applicable to std::map, it can be used with iterators in conjunction with the erase method for 
conditional removals.



