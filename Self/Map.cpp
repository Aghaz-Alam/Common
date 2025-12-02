/*
  Implement a Key-Value Database Class with the following:
  
  - Template-based storage (string keys, generic values)
  - Standard operations: set, get, remove, exists, size, clear
  - Proper error handling for invalid operations
  - Consider performance implications of your design choices
  - Ensure const-correctness and modern C++ practices
  
  Example behavior:
*/

// TODO: Implement KeyValueDB
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;
template<typename T>
class KeyValueDB {
  private:
    map<string, T> data;   // ordered map; you can switch to unordered_map if needed

  public:
    // Set or update a value
    void set(const string& key, const T& val) {
        data[key] = val;
    }

    // Access with error checking
    const T& get(const string& key) const {
        auto it = data.find(key);
        if (it == data.end()) {
            throw runtime_error("Key not found: " + key);
        }
        return it->second;
    }

    // Remove a key; throw if not found
    void remove(const string& key) {
        auto it = data.find(key);
        if (it == data.end()) {
            throw runtime_error("Cannot remove - key not found: " + key);
        }
        data.erase(it);
    }

    // Check if key exists (no exception)
    bool exists(const string& key) const {
        return data.find(key) != data.end();
    }

    // Number of stored key-value pairs
    size_t size() const {
        return data.size();
    }

    // Clear all items
    void clear() {
        data.clear();
    }
};

// -------------------------------------------
// Example usage
// -------------------------------------------
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
        db.get("Aman");  // should throw
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

/*
================================================================================
EXTRA TASKS
================================================================================
Consider implementing:
- Persistence (save/load to file)
- Multiple key types (template<typename K, typename V>)
- Batch operations (set_many, get_many, remove_many)
- Iterator support for range-based loops
- TTL (Time To Live) for auto-expiring entries
- Thread-safety with appropriate locking strategy
- Transaction support (begin, commit, rollback)  
- Advanced queries (get_all_keys, get_all_values, filtering)
- Unit tests demonstrating your approach
*/

