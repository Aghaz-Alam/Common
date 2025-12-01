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
class KeyValueDB{
    //implement class
     map<string, T> stored_data;
    public:
     void set(const string& key, const T& val){
           stored_data[key] = val;
     }           
     T& get(const string& key) const{
        auto it = data.find(key);
     }
      
     T remove(const string& key){
        data.erase(key);  
     }
     size_t size() const{
        return data.size();
     }
     size_t clear() const{
        data.clear();
     }
};




int main(int argc, char** argv)
{

    // Basic usage example - design the API as you see fit
    // ... demonstrate your API
    return 0;
}

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

