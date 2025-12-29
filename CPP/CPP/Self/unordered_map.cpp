//using unordered_map
/*
  Implement a Key-Value Database Class with the following:
  
  - Template-based storage (string keys, generic values)
  - Standard operations: set, get, remove, exists, size, clear
  - Proper error handling for invalid operations
  - Consider performance implications of your design choices
  - Ensure const-correctness and modern C++ practices
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
using namespace std;
template<typename T>
class KeyValueDB {
  private:
    unordered_map<string, T> data;  // faster hash map

  public:
    // Insert / update a key-value pair
    void set(const string& key, const T& val) {
        data[key] = val;
    }

    // Get value (throws if key not found)
    const T& get(const string& key) const {
        auto it = data.find(key);
        if (it == data.end()) {
            throw runtime_error("Key not found: " + key);
        }
        return it->second;
    }

    // Remove a key (throws if missing)
    void remove(const string& key) {
        auto it = data.find(key);
        if (it == data.end()) {
            throw runtime_error("Cannot remove - key not found: " + key);
        }
        data.erase(it);
    }

    // Check if key exists
    bool exists(const string& key) const {
        return data.find(key) != data.end();
    }

    // Number of key-value pairs
    size_t size() const {
        return data.size();
    }

    // Clear all entries
    void clear() {
        data.clear();
    }
};

int main() {
    KeyValueDB<int> db;

    db.set("Aman", 25);
    db.set("Madan", 30);

    cout << "Aman = " << db.get("Aman") << endl;
    cout << "Madan = " << db.get("Madan") << endl;

    cout << "Exists(Madan)? " << (db.exists("Madan") ? "Yes" : "No") << endl;

    db.remove("Aman");

    cout << "Size after removal: " << db.size() << endl;

    try {
        db.get("Aman"); // should throw
    } 
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    db.clear();
    cout << "Size after clear = " << db.size() << endl;

    return 0;
}
/* 
Aman = 25
Madan = 30
Exists(Madan)? Yes
Size after removal: 1
Error: Key not found: Aman
Size after clear = 0
*/


/*
================================================================================
HINTS
================================================================================
- std::unordered_map vs std::map trade-offs
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/











//using vector
/*
  Implement a Key-Value Database Class with the following:
  - Template-based storage (string keys, generic values)
  - Standard operations: set, get, remove, exists, size, clear
  - Proper error handling for invalid operations
  - Consider performance implications of your design choices
  - Ensure const-correctness and modern C++ practices
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;
template<typename T>
class KeyValueDB {
  private:
    vector<pair<string, T>> data;  // store key-value pairs manually

    // Helper: find index of key, or return -1
    int findIndex(const string& key) const {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].first == key)
                return static_cast<int>(i);
        }
        return -1;
    }

  public:
    // Insert or update
    void set(const string& key, const T& val) {
        int idx = findIndex(key);
        if (idx != -1) {
            data[idx].second = val;   // update
        } else {
            data.push_back({key, val});  // insert new
        }
    }

    // Access with checking
    const T& get(const string& key) const {
        int idx = findIndex(key);
        if (idx == -1)
            throw runtime_error("Key not found: " + key);
        return data[idx].second;
    }

    // Remove entry
    void remove(const string& key) {
        int idx = findIndex(key);
        if (idx == -1)
            throw runtime_error("Cannot remove - key not found: " + key);

        data.erase(data.begin() + idx);
    }

    // Check exists
    bool exists(const string& key) const {
        return findIndex(key) != -1;
    }

    // Size
    size_t size() const {
        return data.size();
    }

    // Clear all
    void clear() {
        data.clear();
    }
};

int main() {
    KeyValueDB<int> db;

    db.set("Aman", 25);
    db.set("Madan", 30);

    cout << "Aman = " << db.get("Aman") << endl;
    cout << "Madan = " << db.get("Madan") << endl;

    cout << "Exists(Madan)? " << (db.exists("Madan") ? "Yes" : "No") << endl;

    db.remove("Aman");

    cout << "Size after removal: " << db.size() << endl;

    try {
        db.get("Aman"); // should throw
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    db.clear();
    cout << "Size after clear = " << db.size() << endl;

    return 0;
}
/*
Aman = 25
Madan = 30
Exists(Madan)? Yes
Size after removal: 1
Error: Key not found: Aman
Size after clear = 0
*/


/*
================================================================================
HINTS
================================================================================
- std::unordered_map vs std::map trade-offs
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/












