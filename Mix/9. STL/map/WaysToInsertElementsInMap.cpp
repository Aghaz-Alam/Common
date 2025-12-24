multiple ways to insert elements into a std::map

1. Using insert()
The insert() method allows you to insert a key-value pair into the map. It returns a std::pair<iterator, bool>:
The iterator points to the inserted element.
The bool value is true if the insertion was successful, or false if the element already exists (i.e., the key is already in the map).

Syntax:
map.insert({key, value});  // using initializer list

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    m.insert({1, "Apple"});
    m.insert({2, "Banana"});
    m.insert({3, "Cherry"});
    
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
3 -> Cherry
*/


2. Using operator[]
The operator[] can be used to insert a new element. 
If the key does not already exist, the operator creates a new key-value pair. 
If the key exists, the operator updates the value associated with that key.

Syntax:
map[key] = value;


Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    m[1] = "Apple";    // Insert
    m[2] = "Banana";   // Insert
    m[3] = "Cherry";   // Insert
    
    // Modifying an existing key
    m[2] = "Blueberry"; // Modify value for key 2
    
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Blueberry
3 -> Cherry
*/



3. Using emplace()
The emplace() method allows you to insert an element directly into the container without creating a temporary pair. 
It constructs the key-value pair in place, which is typically more efficient than insert() because it avoids unnecessary copies or moves.

Syntax:
map.emplace(key, value);

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    m.emplace(1, "Apple");   // Insert
    m.emplace(2, "Banana");  // Insert
    m.emplace(3, "Cherry");  // Insert

    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
3 -> Cherry
*/


4. Using insert_or_assign() (C++17 and later)

In C++17, the insert_or_assign() method was introduced. 
It works similarly to insert(), but if the key already exists, it updates the value instead of failing to insert. 
If the key does not exist, it inserts the key-value pair.


Syntax:
map.insert_or_assign(key, value);


Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    
    // Insert new elements
    m.insert_or_assign(1, "Apple");
    m.insert_or_assign(2, "Banana");
    
    // Modify existing element
    m.insert_or_assign(2, "Blueberry");  // This will update the value for key 2
    
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Blueberry
*/


5. Using emplace_hint()
emplace_hint() allows you to insert a new element at a specific position in the map, 
which can be more efficient when you already know where the element should be inserted. 

You provide an iterator to the position where the new element should be inserted. The map will insert the element before this position.

Syntax:
map.emplace_hint(iterator, key, value);


Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    m.emplace(1, "Apple");   // Insert at default position
    m.emplace(3, "Cherry");  // Insert at default position
    
    // Insert with a hint
    auto it = m.find(1);  // Get iterator to element with key 1
    m.emplace_hint(it, 2, "Banana");  // Insert hint before key 1
    
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
3 -> Cherry
*/


6. Using insert() with a pair (for more complex types)
Inserting std::pair directly into the map is useful for cases where the key and value are constructed separately or 
when you are working with more complex types.

Syntax:
map.insert(std::make_pair(key, value));

Example:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    
    // Insert using make_pair
    m.insert(make_pair(1, "Apple"));
    m.insert(make_pair(2, "Banana"));
    
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
*/


7. Using insert() with an Iterator Range (Copying from another container)
You can insert elements into a std::map from another container (such as a std::vector, std::list, or another std::map) using iterators.

Syntax:
map.insert(first_iterator, last_iterator);

Example:
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {
    map<int, string> m;
    vector<pair<int, string>> v = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};
    
    // Insert elements from vector using iterator range
    m.insert(v.begin(), v.end());
    
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
3 -> Cherry
*/