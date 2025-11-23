Ways to Define and Initialize std::map:

1. Default Declaration:
This creates an empty std::map, where both the keys and values are default-initialized.

#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;  // Declare an empty map with int as key and string as value
}



2. Initialization with Values (Using insert):
You can use the insert method to add elements to the map.

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



3. Initialization with {} (List Initialization):
You can directly initialize a std::map using an initializer list.

#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {
        {1, "Apple"},
        {2, "Banana"},
        {3, "Cherry"}
    };

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


4. Initialization with Range Constructor:
You can initialize a std::map from another container (like a std::vector) using the range constructor.

#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    vector<pair<int, string>> v = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};
    map<int, string> m(v.begin(), v.end());  // Initialize map from vector of pairs

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


5. Using operator[]:
You can use the operator[] to both insert and access elements. If the key does not exist, 
it will insert the key with a default value for the value type.

#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m;
    
    // Insert using operator[]
    m[1] = "Apple";
    m[2] = "Banana";
    m[3] = "Cherry";

    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }

    // Modifying an existing key
    m[2] = "Blueberry";  // Change value of key 2

    cout << "\nAfter modification:\n";
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
3 -> Cherry

After modification:
1 -> Apple
2 -> Blueberry
3 -> Cherry
*/


6. Using emplace:
emplace constructs the element in place, avoiding unnecessary copies or moves. 
This is a more efficient way of adding elements than using insert or operator[] in some cases.

#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m;
    
    // Using emplace
    m.emplace(1, "Apple");
    m.emplace(2, "Banana");
    m.emplace(3, "Cherry");

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



7. Using insert_or_assign:
Introduced in C++17, insert_or_assign inserts the key-value pair if the key is not found, 
or updates the value associated with the key if it already exists.

#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m;
    
    // Using insert_or_assign
    m.insert_or_assign(1, "Apple");
    m.insert_or_assign(2, "Banana");
    m.insert_or_assign(3, "Cherry");

    // Modifying the value of an existing key
    m.insert_or_assign(2, "Blueberry");

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


Summary of Initialization Methods:
Default constructor: map<int, string> m;
Insert method: m.insert({1, "Apple"});
List initialization: map<int, string> m = {{1, "Apple"}, {2, "Banana"}};
Range constructor: map<int, string> m(v.begin(), v.end());
Operator[]: m[1] = "Apple";
Emplace method: m.emplace(1, "Apple");
Insert or assign (C++17): m.insert_or_assign(1, "Apple");



Common Operations with std::map:
Insertion: insert, emplace, operator[], insert_or_assign
Search: Use find to search for a key, which returns an iterator.
Accessing elements: Use operator[] or at() for access.
Iterating: You can iterate over a map using a range-based for loop, or traditional iterator methods.

Example: Iterating over a std::map:
#include <iostream>
#include <map>
using namespace std;
int main() {
    map<int, string> m = {{1, "Apple"}, {2, "Banana"}, {3, "Cherry"}};
    
    // Iterating with range-based for loop
    for (const auto& p : m) {
        cout << p.first << " -> " << p.second << endl;
    }

    // Iterating with an iterator
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " -> " << it->second << endl;
    }
}
/* 
Output:

1 -> Apple
2 -> Banana
3 -> Cherry 
*/







