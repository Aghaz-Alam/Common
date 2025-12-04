
std::array, std::vector, std::stack, std::queue, std::dequeue, std::forward_list, std::list, std::set, std::unordered_set, std::map, std::unordered_map
- Template-based storage (string keys, generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices



/*
================================================================================
HINTS
================================================================================
- std::array vs std::vector vs std::stack vs std::queue vs std::dequeue vs std::forward_list vs std::list vs std::set vs std::unordered_set vs std::map vs std::unordered_map trade-offs
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
- Thread- with appropriate locking strategy
- Transaction support (begin, commit, rollback)  
- Advanced queries (get_all_keys, get_all_values, filtering)
- Unit tests demonstrating your approach
*/


