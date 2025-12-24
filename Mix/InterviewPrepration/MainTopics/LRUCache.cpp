#include <iostream>
#include <map>
#include <list>
using namespace std;

class LRUCache {
public:
    map<int, int> mymap;        // key → value
    list<int> ls;               // maintains usage order (front = most recent)
    int cp;                     // capacity

    // --- Constructor ---
    LRUCache(int capacity) {
        cp = capacity;          // store capacity
        mymap.clear();          // clear map initially
        ls.clear();             // clear list initially
    }

    // --- Get operation ---
    int get(int key) {
        // key not found
        if (mymap.find(key) == mymap.end())
            return -1;

        // key exists → update LRU order
        ls.remove(key);         // remove old position in list
        ls.push_front(key);     // insert at front (most recently used)

        return mymap[key];      // return value
    }

    // --- Put operation ---
    void put(int key, int value) {

        // key NOT present in cache
        if (mymap.find(key) == mymap.end()) {

            // cache full → remove LRU element
            if (ls.size() == cp) {
                int last = ls.back();   // last → least recently used
                ls.pop_back();          // remove from list
                mymap.erase(last);      // remove from map
            }

            // insert new key-value
            mymap[key] = value;
            ls.push_front(key);         // most recent goes to front
        }
        else {
            // key exists → update value + move to front
            ls.remove(key);
            mymap[key] = value;
            ls.push_front(key);
        }
    }
};

int main() {
    LRUCache cache(2);   // capacity = 2

    cache.put(1, 1);     // cache = {1}
    cache.put(2, 2);     // cache = {2,1}
    cout << cache.get(1) << endl;  // returns 1 → cache = {1,2}

    cache.put(3, 3);     // LRU is key=2 → removed → cache = {3,1}
    cout << cache.get(2) << endl;  // returns -1 (not found)

    cache.put(4, 4);     // LRU is key=1 → removed → cache = {4,3}
    cout << cache.get(1) << endl;  // returns -1
    cout << cache.get(3) << endl;  // returns 3
    cout << cache.get(4) << endl;  // returns 4

    return 0;
}
/* 



✅ Line-by-Line Explanation
Class Variables
map<int, int> mymap;
--->Stores key → value
--->Allows fast lookup of values
--->But does NOT track order of usage

list<int> ls;
--->Stores keys only
--->Front of list = most recently used (MRU)
--->Back of list = least recently used (LRU)
--->Easy to remove back O(1)

int cp;
--->Stores maximum allowed elements (capacity)

Constructor
LRUCache(int capacity) {
    cp = capacity;
    mymap.clear();
    ls.clear();
}
--->Sets capacity
--->Ensures both data structures are empty

GET Operation
int get(int key) {
--->Called when user fetches a key


if (mymap.find(key) == mymap.end())
    return -1;

If key not found → return -1

ls.remove(key);
ls.push_front(key);

--->Move key to front, because it is now most recently used

return mymap[key];
--->Return the value stored in map


PUT Operation
if (mymap.find(key) == mymap.end()) {
--->If key is new

if (ls.size() == cp) {
--->Cache full → need eviction

int last = ls.back();
ls.pop_back();
mymap.erase(last);
--->Remove least recently used (LRU) key


mymap[key] = value;
ls.push_front(key);
--->Insert new key-value
--->Mark key as most recently used

PUT for existing key
else {
    ls.remove(key);
    mymap[key] = value;
    ls.push_front(key);
}


--->If key already present:
    Remove old position in list
    Update value
    Move key to front (most recent)



main()
Step-by-step Output
| Code       | Cache State (MRU → LRU) | Output |
| ---------- | ----------------------- | ------ |
| `put(1,1)` | {1}                     |        |
| `put(2,2)` | {2,1}                   |        |
| `get(1)`   | {1,2}                   | 1      |
| `put(3,3)` | removes 2 → {3,1}       |        |
| `get(2)`   | {3,1}                   | -1     |
| `put(4,4)` | removes 1 → {4,3}       |        |
| `get(1)`   | {4,3}                   | -1     |
| `get(3)`   | {3,4}                   | 3      |
| `get(4)`   | {4,3}                   | 4      |

*/










LRU CACHE (unordered_map + list):
This version stores key-value pairs in a list and uses unordered_map to map key → iterator.
✔ get() → O(1)
✔ put() → O(1)
✔ No list.remove(key) (O(n)) — Instead erase using iterator (O(1))

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
class LRUCache {
  private:
    int capacity;
    // Doubly linked list: stores {key, value}
    list<pair<int, int>> lru;

    // Map: key → iterator of list node
    unordered_map<int, list<pair<int, int>>::iterator> mp;

  public:
    // Constructor
    LRUCache(int cap) : capacity(cap) {}

    // Get the value of the key
    int get(int key) {
        // Key not found
        if (mp.find(key) == mp.end())
            return -1;

        // Move this node to the front (most recently used)
        auto it = mp[key];
        int value = it->second;

        // Erase old position and push to front
        lru.erase(it);
        lru.push_front({key, value});
        mp[key] = lru.begin();

        return value;
    }

    // Insert or update a key-value pair
    void put(int key, int value) {
        // If key already exists → update and move to front
        if (mp.find(key) != mp.end()) {
            auto it = mp[key];
            lru.erase(it);
            lru.push_front({key, value});
            mp[key] = lru.begin();
            return;
        }

        // If cache is full → remove LRU item (from back)
        if (lru.size() == capacity) {
            auto last = lru.back();  // (key,value)
            mp.erase(last.first);    // remove key from map
            lru.pop_back();          // remove node from list
        }

        // Insert new entry at front
        lru.push_front({key, value});
        mp[key] = lru.begin();
    }
};
int main() {
    LRUCache cache(2);

    cache.put(1, 1);     // Cache: {1}
    cache.put(2, 2);     // Cache: {2,1}

    cout << cache.get(1) << endl; // Output: 1, Cache: {1,2}

    cache.put(3, 3);     // Removes key=2, Cache: {3,1}
    cout << cache.get(2) << endl; // Output: -1

    cache.put(4, 4);     // Removes key=1, Cache: {4,3}

    cout << cache.get(1) << endl; // Output: -1
    cout << cache.get(3) << endl; // Output: 3
    cout << cache.get(4) << endl; // Output: 4

  return 0;
}
/* 
DETAILED EXPLANATION
1️⃣ Data Structures
✔ Doubly Linked List
list<pair<int, int>> lru;

->Maintains usage order:
   =>Front = Most Recently Used (MRU)
   =>Back = Least Recently Used (LRU)
->Each node holds: {key, value}

✔ Hash Map
    unordered_map<int, list<pair<int,int>>::iterator> mp;

Maps:
    key → iterator pointing to the node inside list

✔ Allows O(1) erase
✔ Allows O(1) movement

2️⃣ Constructor
LRUCache(int cap) : capacity(cap) {}
-->Stores capacity.

3️⃣ GET Operation
if (mp.find(key) == mp.end())
    return -1;
Key not found → return -1.
auto it = mp[key];
int value = it->second;

Access the list node holding (key,value)
lru.erase(it);
lru.push_front({key, value});
mp[key] = lru.begin();


Move node to front → most recent.
✔ O(1) erase
✔ O(1) push_front

4️⃣ PUT Operation
✔ Case 1: Key already exists
auto it = mp[key];
lru.erase(it);
lru.push_front({key, value});
mp[key] = lru.begin();

Erase old position → insert to front.

✔ Case 2: Cache full → Evict LRU
if (lru.size() == capacity) {
    auto last = lru.back();   // LRU key
    mp.erase(last.first);     // remove from map
    lru.pop_back();           // remove from list
}

✔ Insert new key
lru.push_front({key, value});
mp[key] = lru.begin();

📊 Time Complexity
| Operation            | Complexity |
| -------------------- | ---------- |
| `get(key)`           | **O(1)**   |
| `put(key,value)`     | **O(1)**   |
| Erasing via iterator | **O(1)**   |
| Moving nodes         | **O(1)**   |
*/
