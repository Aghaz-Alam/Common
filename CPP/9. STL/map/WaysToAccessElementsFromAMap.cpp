1. Using operator[]
The operator[] is the most common way to access or modify an element by its key. 
If the key exists, it returns a reference to the value associated with that key. 
If the key does not exist, it inserts a new element with that key and a default-constructed value (this can be costly if the key does not exist).

Syntax:
map[key];

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Access the value associated with key = 2
    cout << "Value for key 2: " << m[2] << endl;  // Output: Banana

    // If the key doesn't exist, it will be added with a default value
    cout << "Value for key 4 (doesn't exist yet): " << m[4] << endl;  // Output: (empty string)
    
    // Now the key 4 exists with the default value (empty string).
}
/* 
Output:

Value for key 2: Banana
Value for key 4 (doesn't exist yet): 
*/

2. Using find()
find() searches for a key in the map and returns an iterator to the element if it is found, or map.end() if the key is not present. 
It does not insert a new element if the key does not exist, unlike operator[].

Syntax:
map.find(key);

Example:
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Find the element with key = 2
    auto it = m.find(2);

    if (it != m.end()) {
        cout << "Found key 2: " << it->second << endl;  // Output: Banana
    } else {
        cout << "Key 2 not found!" << endl;
    }

    // Try to find a key that doesn't exist
    it = m.find(5);
    if (it == m.end()) {
        cout << "Key 5 not found!" << endl;  // Output: Key 5 not found!
    }
}
/* 
Output:

Found key 2: Banana
Key 5 not found!
*/



3. Using at()
The at() method is used to access an element by key, but unlike operator[], 
it throws an exception (std::out_of_range) if the key does not exist in the map. 

This makes at() a safer alternative when you want to ensure that the key exists before accessing it.

Syntax:
map.at(key);

Example:
#include <iostream>
#include <map>
#include <stdexcept>  // For std::out_of_range
using namespace std;

int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Access the value for key = 2
    try {
        cout << "Value for key 2: " << m.at(2) << endl;  // Output: Banana
    } catch (const std::out_of_range& e) {
        cout << e.what() << endl;
    }

    // Access a key that does not exist (will throw exception)
    try {
        cout << "Value for key 4: " << m.at(4) << endl;  // Throws exception
    } catch (const std::out_of_range& e) {
        cout << "Exception: " << e.what() << endl;  // Output: map::at: key not found
    }
}
/* 
Output:

Value for key 2: Banana
Exception: map::at: key not found
*/


4. Using Range-based for Loop
You can use a range-based for loop to iterate over all the elements of the map and access both the keys and values.

Syntax:
for (const auto& pair : map) {
    // Access pair.first (key) and pair.second (value)
}

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Iterate over all elements
    for (const auto& p : m) {
        cout << "Key: " << p.first << ", Value: " << p.second << endl;
    }
}
/* 
Output:

Key: 1, Value: Apple
Key: 2, Value: Banana
Key: 3, Value: Cherry
*/



5. Using Iterators
You can access the elements in a map using iterators. Maps support bidirectional iterators, so you can use them to traverse the map.

Syntax:
for (auto it = map.begin(); it != map.end(); ++it) {
    // Access it->first (key) and it->second (value)
}

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Iterate using an iterator
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << "Key: " << it->first << ", Value: " << it->second << endl;
    }
}
/* 
Output:

Key: 1, Value: Apple
Key: 2, Value: Banana
Key: 3, Value: Cherry
*/


6. Using count()
The count() function returns the number of elements with a specified key in the map. 
Since a std::map cannot have duplicate keys, this function will return 1 if the key exists, or 0 if it doesn't. 
It's useful for checking if a key is present before attempting to access it.

Syntax:
map.count(key);

Example:
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Check if key exists
    if (m.count(2)) {
        cout << "Key 2 exists!" << endl;  // Output: Key 2 exists!
    } else {
        cout << "Key 2 does not exist!" << endl;
    }

    // Check if key 4 exists
    if (m.count(4)) {
        cout << "Key 4 exists!" << endl;
    } else {
        cout << "Key 4 does not exist!" << endl;  // Output: Key 4 does not exist!
    }
}
/* 
Output:

Key 2 exists!
Key 4 does not exist!
*/


7. Using lower_bound() and upper_bound()
lower_bound() returns an iterator to the first element that is not less than the specified key 
(i.e., the first element greater than or equal to the given key).

upper_bound() returns an iterator to the first element that is greater than the specified key 
(i.e., the first element strictly greater than the key).

These methods are useful for performing range-based queries or finding elements that fall within a certain range.

Syntax:
auto it = map.lower_bound(key);  // Finds first element >= key
auto it = map.upper_bound(key);  // Finds first element > key

Example:
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};

    // Lower bound: first element >= key 2
    auto lb = m.lower_bound(2);
    cout << "Lower bound of 2: " << lb->first << " -> " << lb->second << endl;  // Output: 2 -> Banana

    // Upper bound: first element > key 2
    auto ub = m.upper_bound(2);
    cout << "Upper bound of 2: " << ub->first << " -> " << ub->second << endl;  // Output: 3 -> Cherry
}
/* 
Output:

Lower bound of 2: 2 -> Banana
Upper bound of 2: 3 -> Cherry
*/