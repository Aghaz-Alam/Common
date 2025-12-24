std::array, std::vector, std::stack, std::queue, std::dequeue, std::forward_list, std::list, std::set, std::unordered_set, std::map, std::unordered_map
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices



/*
================================================================================
HINTS
================================================================================
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
- Multiple key types (template<typename V>)
- Batch operations (set_many, get_many, remove_many)
- Iterator support for range-based loops
- TTL (Time To Live) for auto-expiring entries
- Thread- with appropriate locking strategy
- Transaction support (begin, commit, rollback)  
- Advanced queries (get_all_values, filtering)
- Unit tests demonstrating your approach
*/















✅ 1. std::array — Fixed-size sequential container
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices



/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <array>
#include <stdexcept>
#include <iostream>
#include <string>
#include <exception>
template<typename T, std::size_t N>
class ArrayStore {
    std::array<T, N> data{};
  public:
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= N) throw std::out_of_range("Array index out of range");
        data[index] = std::forward<U>(value);
    }

    const T& get(std::size_t index) const {
        if (index >= N) throw std::out_of_range("Array index out of range");
        return data[index];
    }

    void remove(std::size_t index) {
        if (index >= N) throw std::out_of_range("Array index out of range");
        data[index] = T{};
    }

    bool exists(std::size_t index) const {
        if (index >= N) return false;
        return true;
    }

    std::size_t size() const { return N; }
    void clear() { data = {}; }
};

// Include your ArrayStore class definition here

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "ArrayStore<T, N> Demonstration\n";
    std::cout << "==============================\n\n";

    ArrayStore<int, 5> arr;

    try {
        std::cout << "[1] Setting initial values...\n";
        arr.set(0, 10);
        arr.set(1, 20);
        arr.set(2, 30);
        std::cout << "Values set: {10, 20, 30, 0, 0}\n\n";

        std::cout << "[2] Reading values:\n";
        std::cout << "  arr.get(0) = " << arr.get(0) << "\n";
        std::cout << "  arr.get(1) = " << arr.get(1) << "\n";
        std::cout << "  arr.get(2) = " << arr.get(2) << "\n\n";

        std::cout << "[3] Checking exists:\n";
        std::cout << "  exists(0): " << std::boolalpha << arr.exists(0) << "\n";
        std::cout << "  exists(3): " << std::boolalpha << arr.exists(3) << "\n";
        std::cout << "  exists(5): " << std::boolalpha << arr.exists(5) << "\n\n";

        std::cout << "[4] Removing index 1...\n";
        arr.remove(1);
        std::cout << "  arr.get(1) = " << arr.get(1) << " (should be default value)\n\n";

        std::cout << "[5] Size of ArrayStore: " << arr.size() << "\n\n";

        std::cout << "[6] Clearing array...\n";
        arr.clear();
        std::cout << "  arr.get(0) after clear = " << arr.get(0) << "\n\n";

        std::cout << "[7] Exception demonstration (expected)...\n";
        std::cout << "  Attempting arr.get(10):\n";
        std::cout << arr.get(10) << "\n";  // triggers exception

    } catch (const std::exception& ex) {
        std::cerr << "  [Exception Caught]: " << ex.what() << "\n";
    }

    std::cout << "\nDemo complete.\n";
    return 0;
}
/*
==============================
ArrayStore<T, N> Demonstration
==============================

[1] Setting initial values...
Values set: {10, 20, 30, 0, 0}

[2] Reading values:
  arr.get(0) = 10
  arr.get(1) = 20
  arr.get(2) = 30

[3] Checking exists:
  exists(0): true
  exists(3): true
  exists(5): false

[4] Removing index 1...
  arr.get(1) = 0 (should be default value)

[5] Size of ArrayStore: 5

[6] Clearing array...
  arr.get(0) after clear = 0

[7] Exception demonstration (expected)...
  Attempting arr.get(10):
  [Exception Caught]: Array index out of range

Demo complete.
*/



✅ 2. std::vector — Dynamic array
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices



/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
template<typename T>
class VectorStore {
    std::vector<T> data;
  public:
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= data.size()) data.resize(index + 1);
        data[index] = std::forward<U>(value);
    }

    const T& get(std::size_t index) const {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void remove(std::size_t index) {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        data.erase(data.begin() + index);
    }

    bool exists(std::size_t index) const {
        return index < data.size();
    }

    std::size_t size() const { return data.size(); }
    void clear() { data.clear(); }
};

// include the VectorStore class here
int main(int argc, char** argv){
    std::cout << "==============================\n";
    std::cout << "VectorStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    VectorStore<int> vec;

    try {
        std::cout << "[1] Setting values...\n";
        vec.set(0, 10);
        vec.set(1, 20);
        vec.set(5, 99);   // shows auto-resize behavior
        std::cout << "  Values set: {10,20,0,0,0,99}\n\n";

        std::cout << "[2] Getting values...\n";
        std::cout << "  vec.get(0) = " << vec.get(0) << "\n";
        std::cout << "  vec.get(1) = " << vec.get(1) << "\n";
        std::cout << "  vec.get(5) = " << vec.get(5) << "\n\n";

        std::cout << "[3] Checking exists...\n";
        std::cout << "  exists(1): " << std::boolalpha << vec.exists(1) << "\n";
        std::cout << "  exists(10): " << std::boolalpha << vec.exists(10) << "\n\n";

        std::cout << "[4] Removing element at index 1...\n";
        vec.remove(1);
        std::cout << "  vec.get(1) is now: " << vec.get(1) << " (previous 20 removed)\n\n";

        std::cout << "[5] Size = " << vec.size() << "\n\n";

        std::cout << "[6] Clearing container...\n";
        vec.clear();
        std::cout << "  Size after clear = " << vec.size() << "\n\n";

        std::cout << "[7] Exception demonstration...\n";
        std::cout << "  Attempting vec.get(100):\n";
        std::cout << vec.get(100) << "\n";   // will throw

    } catch(const std::exception& ex) {
        std::cerr << "  [EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}
/* 
==============================
VectorStore<T> Demonstration
==============================

[1] Setting values...
  Values set: {10,20,0,0,0,99}

[2] Getting values...
  vec.get(0) = 10
  vec.get(1) = 20
  vec.get(5) = 99

[3] Checking exists...
  exists(1): true
  exists(10): false

[4] Removing element at index 1...
  vec.get(1) is now: 0 (previous 20 removed)

[5] Size = 5

[6] Clearing container...
  Size after clear = 0

[7] Exception demonstration...
  Attempting vec.get(100):
  [EXCEPTION]: Index out of range
Demo complete.
*/



✅ 3. std::stack — LIFO container
Stack has no indexing; only top access.

- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <stack>
#include <stdexcept>
template<typename T>
class StackStore {
    std::stack<T> st;
  public:
    template<typename U>
    void set(U&& value) { st.push(std::forward<U>(value)); }

    const T& get() const {
        if (st.empty()) throw std::runtime_error("Stack is empty");
        return st.top();
    }

    void remove() {
        if (st.empty()) throw std::runtime_error("Stack is empty");
        st.pop();
    }

    bool exists() const { return !st.empty(); }
    std::size_t size() const { return st.size(); }
    void clear() { while (!st.empty()) st.pop(); }
};
#include <iostream>
#include <string>
#include <exception>

// Include your StackStore class definition here

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "StackStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    StackStore<int> stack;

    try {
        std::cout << "[1] Pushing values onto stack...\n";
        stack.set(10);
        stack.set(20);
        stack.set(30);
        std::cout << "  Pushed 10, 20, 30\n\n";

        std::cout << "[2] Top element:\n";
        std::cout << "  stack.get() = " << stack.get() << "\n\n";

        std::cout << "[3] Stack exists? " << std::boolalpha << stack.exists() << "\n";
        std::cout << "  Stack size: " << stack.size() << "\n\n";

        std::cout << "[4] Popping top element...\n";
        stack.remove();
        std::cout << "  New top = " << stack.get() << "\n";
        std::cout << "  New size = " << stack.size() << "\n\n";

        std::cout << "[5] Clearing stack...\n";
        stack.clear();
        std::cout << "  Exists after clear? " << stack.exists() << "\n";
        std::cout << "  Size after clear = " << stack.size() << "\n\n";

        std::cout << "[6] Exception demonstration (expected)...\n";
        std::cout << "  Attempting stack.get() on empty stack:\n";
        std::cout << stack.get() << "\n";  // triggers exception

    } catch(const std::exception& ex) {
        std::cerr << "  [EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}
/*
==============================
StackStore<T> Demonstration
==============================

[1] Pushing values onto stack...
  Pushed 10, 20, 30

[2] Top element:
  stack.get() = 30

[3] Stack exists? true
  Stack size: 3

[4] Popping top element...
  New top = 20
  New size = 2

[5] Clearing stack...
  Exists after clear? false
  Size after clear = 0

[6] Exception demonstration (expected)...
  Attempting stack.get() on empty stack:
  [EXCEPTION]: Stack is empty
Demo complete.
*/



✅ 4. std::queue — FIFO container
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <queue>
#include <stdexcept>

template<typename T>
class QueueStore {
    std::queue<T> q;
public:
    template<typename U>
    void set(U&& value) { q.push(std::forward<U>(value)); }

    const T& get() const {
        if (q.empty()) throw std::runtime_error("Queue empty");
        return q.front();
    }

    void remove() {
        if (q.empty()) throw std::runtime_error("Queue empty");
        q.pop();
    }

    bool exists() const { return !q.empty(); }
    std::size_t size() const { return q.size(); }
    void clear() { while (!q.empty()) q.pop(); }
};

#include <iostream>
#include <exception>

// Include QueueStore definition here

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "QueueStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    QueueStore<int> queue;

    try {
        std::cout << "[1] Enqueueing values...\n";
        queue.set(10);
        queue.set(20);
        queue.set(30);
        std::cout << "  Enqueued 10, 20, 30\n\n";

        std::cout << "[2] Front element:\n";
        std::cout << "  queue.get() = " << queue.get() << "\n\n";

        std::cout << "[3] Queue exists? " << std::boolalpha << queue.exists() << "\n";
        std::cout << "  Queue size: " << queue.size() << "\n\n";

        std::cout << "[4] Dequeue front element...\n";
        queue.remove();
        std::cout << "  New front = " << queue.get() << "\n";
        std::cout << "  New size = " << queue.size() << "\n\n";

        std::cout << "[5] Clearing queue...\n";
        queue.clear();
        std::cout << "  Exists after clear? " << queue.exists() << "\n";
        std::cout << "  Size after clear = " << queue.size() << "\n\n";

        std::cout << "[6] Exception demonstration (expected)...\n";
        std::cout << "  Attempting queue.get() on empty queue:\n";
        std::cout << queue.get() << "\n";  // triggers exception

    } catch(const std::exception& ex) {
        std::cerr << "  [EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}




✅ 5. std::deque — Double-ended queue
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <deque>
#include <stdexcept>

template<typename T>
class DequeStore {
    std::deque<T> dq;
public:
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= dq.size()) dq.resize(index + 1);
        dq[index] = std::forward<U>(value);
    }

    const T& get(std::size_t index) const {
        if (index >= dq.size()) throw std::out_of_range("Index out of range");
        return dq[index];
    }

    void remove(std::size_t index) {
        if (index >= dq.size()) throw std::out_of_range("Index out of range");
        dq.erase(dq.begin() + index);
    }

    bool exists(std::size_t index) const { return index < dq.size(); }
    std::size_t size() const { return dq.size(); }
    void clear() { dq.clear(); }
};
#include <iostream>
#include <exception>

// Include your DequeStore class definition here

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "DequeStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    DequeStore<int> dq;

    try {
        std::cout << "[1] Setting values...\n";
        dq.set(0, 10);
        dq.set(1, 20);
        dq.set(3, 50); // auto-resize
        std::cout << "  Values set: indices 0=10, 1=20, 2=0, 3=50\n\n";

        std::cout << "[2] Getting values...\n";
        std::cout << "  dq.get(0) = " << dq.get(0) << "\n";
        std::cout << "  dq.get(1) = " << dq.get(1) << "\n";
        std::cout << "  dq.get(3) = " << dq.get(3) << "\n\n";

        std::cout << "[3] Checking exists...\n";
        std::cout << "  exists(2): " << std::boolalpha << dq.exists(2) << "\n";
        std::cout << "  exists(5): " << std::boolalpha << dq.exists(5) << "\n\n";

        std::cout << "[4] Removing index 1...\n";
        dq.remove(1);
        std::cout << "  dq.get(1) now = " << dq.get(1) << " (was 20 removed)\n";
        std::cout << "  Size = " << dq.size() << "\n\n";

        std::cout << "[5] Clearing deque...\n";
        dq.clear();
        std::cout << "  Size after clear = " << dq.size() << "\n";
        std::cout << "  exists(0) after clear? " << dq.exists(0) << "\n\n";

        std::cout << "[6] Exception demonstration (expected)...\n";
        std::cout << "  Attempting dq.get(10):\n";
        std::cout << dq.get(10) << "\n"; // triggers exception

    } catch(const std::exception& ex) {
        std::cerr << "  [EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}
/*
==============================
DequeStore<T> Demonstration
==============================

[1] Setting values...
  Values set: indices 0=10, 1=20, 2=0, 3=50

[2] Getting values...
  dq.get(0) = 10
  dq.get(1) = 20
  dq.get(3) = 50

[3] Checking exists...
  exists(2): true
  exists(5): false

[4] Removing index 1...
  dq.get(1) now = 0 (was 20 removed)
  Size = 3

[5] Clearing deque...
  Size after clear = 0
  exists(0) after clear? false

[6] Exception demonstration (expected)...
  Attempting dq.get(10):
  [EXCEPTION]: Index out of range
Demo complete.
*/





✅ 6. std::forward_list — Singly linked list
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <forward_list>
#include <stdexcept>

template<typename T>
class ForwardListStore {
    std::forward_list<T> fl;
public:
    template<typename U>
    void set(U&& value) {
        fl.push_front(std::forward<U>(value));
    }

    const T& get() const {
        if (fl.empty()) throw std::runtime_error("Forward list empty");
        return fl.front();
    }

    void remove() {
        if (fl.empty()) throw std::runtime_error("Forward list empty");
        fl.pop_front();
    }

    bool exists() const { return !fl.empty(); }
    
    std::size_t size() const {
        return std::distance(fl.begin(), fl.end());
    }

    void clear() { fl.clear(); }
};
#include <iostream>
#include <exception>

// include ForwardListStore definition here

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "ForwardListStore<T> Demo\n";
    std::cout << "==============================\n\n";

    ForwardListStore<int> fl;

    try {
        std::cout << "[1] Pushing values using set()...\n";
        fl.set(10);   // pushes at front
        fl.set(20);
        fl.set(30);
        std::cout << "  Stored values: (front is 30 now)\n\n";

        std::cout << "[2] Reading front element using get()...\n";
        std::cout << "  fl.get() = " << fl.get() << "\n\n";

        std::cout << "[3] Size check...\n";
        std::cout << "  size = " << fl.size() << "\n\n";

        std::cout << "[4] Exists check...\n";
        std::cout << "  exists = " << std::boolalpha << fl.exists() << "\n\n";

        std::cout << "[5] Removing front element...\n";
        fl.remove(); // removes 30
        std::cout << "  new front = " << fl.get() << " (was 20 now)\n";
        std::cout << "  size = " << fl.size() << "\n\n";

        std::cout << "[6] Clearing list...\n";
        fl.clear();
        std::cout << "  size = " << fl.size() << "\n";
        std::cout << "  exists = " << fl.exists() << "\n\n";

        std::cout << "[7] Exception demonstration (expected)...\n";
        std::cout << "  Attempting fl.get():\n";
        std::cout << fl.get() << "\n";  // triggers exception

    } catch (const std::exception& ex) {
        std::cerr << "  [EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}
/* 
==============================
ForwardListStore<T> Demo
==============================

[1] Pushing values using set()...
  Stored values: (front is 30 now)

[2] Reading front element using get()...
  fl.get() = 30

[3] Size check...
  size = 3

[4] Exists check...
  exists = true

[5] Removing front element...
  new front = 20 (was 20 now)
  size = 2

[6] Clearing list...
  size = 0
  exists = false

[7] Exception demonstration (expected)...
  Attempting fl.get():
  [EXCEPTION]: Forward list empty
Demo complete.
*/




✅ 7. std::list — Doubly linked list
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <list>
#include <stdexcept>

template<typename T>
class ListStore {
    std::list<T> ls;
public:
    template<typename U>
    void set(U&& value) { ls.push_back(std::forward<U>(value)); }

    const T& get() const {
        if (ls.empty()) throw std::runtime_error("List empty");
        return ls.front();
    }

    void remove() {
        if (ls.empty()) throw std::runtime_error("List empty");
        ls.pop_front();
    }

    bool exists() const { return !ls.empty(); }
    std::size_t size() const { return ls.size(); }
    void clear() { ls.clear(); }
};
#include <iostream>
#include <exception>

// Include ListStore class definition here

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "ListStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    ListStore<int> ls;

    try {
        std::cout << "[1] Inserting values using set()...\n";
        ls.set(10);
        ls.set(20);
        ls.set(30);
        std::cout << "  Values inserted: 10, 20, 30 (front = 10)\n\n";

        std::cout << "[2] Reading first element using get()...\n";
        std::cout << "  ls.get() = " << ls.get() << "\n\n";

        std::cout << "[3] Size check...\n";
        std::cout << "  size = " << ls.size() << "\n\n";

        std::cout << "[4] Exists check...\n";
        std::cout << "  exists = " << std::boolalpha << ls.exists() << "\n\n";

        std::cout << "[5] Removing front element...\n";
        ls.remove();  // removes 10
        std::cout << "  new front = " << ls.get() << " (was 20 now)\n";
        std::cout << "  size = " << ls.size() << "\n\n";

        std::cout << "[6] Clearing list...\n";
        ls.clear();
        std::cout << "  size after clear = " << ls.size() << "\n";
        std::cout << "  exists after clear = " << ls.exists() << "\n\n";

        std::cout << "[7] Exception demonstration (expected)...\n";
        std::cout << "  Attempting ls.get():\n";
        std::cout << ls.get() << "\n";  // triggers exception

    } catch (const std::exception& ex) {
        std::cerr << "  [EXCEPTION]: " << ex.what() << "\n";
    }

    std::cout << "Demo complete.\n";
    return 0;
}
/* 
==============================
ListStore<T> Demonstration
==============================

[1] Inserting values using set()...
  Values inserted: 10, 20, 30 (front = 10)

[2] Reading first element using get()...
  ls.get() = 10

[3] Size check...
  size = 3

[4] Exists check...
  exists = true

[5] Removing front element...
  new front = 20 (was 20 now)
  size = 2

[6] Clearing list...
  size after clear = 0
  exists after clear = false

[7] Exception demonstration (expected)...
  Attempting ls.get():
  [EXCEPTION]: List empty
Demo complete.
*/




✅ 8. std::set — Sorted unique keys
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

#include <iostream>
#include <set>
#include <stdexcept>

template<typename T>
class SetStore {
    std::set<T> st;

public:
    template<typename U>
    void set(U&& value) {
        st.insert(std::forward<U>(value));
    }

    bool exists(const T& value) const {
        return st.find(value) != st.end();   // C++11-compatible
    }

    void remove(const T& value) {
        st.erase(value);
    }

    const T& get(const T& value) const {
        auto it = st.find(value);
        if (it == st.end())
            throw std::runtime_error("Value not found in SetStore");
        return *it;
    }

    const T& get() const {
        if (st.empty())
            throw std::runtime_error("Set is empty");
        return *st.begin();  // smallest element
    }

    std::size_t size() const { return st.size(); }
    void clear() { st.clear(); }
};


// =============================================================================
// Demonstration Program
// =============================================================================

int main(int argc, char** argv)
{
    std::cout << "==============================\n";
    std::cout << "SetStore<T> Demonstration\n";
    std::cout << "==============================\n\n";

    SetStore<int> ss;

    std::cout << "[1] Inserting values...\n";
    ss.set(10);
    ss.set(5);
    ss.set(20);
    ss.set(10); // duplicate ignored
    std::cout << "  Inserted values: 10, 5, 20, (10 ignored)\n\n";

    std::cout << "[2] Checking existence...\n";
    std::cout << "  exists(10) = " << std::boolalpha << ss.exists(10) << "\n";
    std::cout << "  exists(50) = " << ss.exists(50) << "\n\n";

    std::cout << "[3] Getting values...\n";
    try {
        std::cout << "  get(20) -> " << ss.get(20) << "\n";
        std::cout << "  get() smallest -> " << ss.get() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "  ERROR: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "[4] Set size...\n";
    std::cout << "  size = " << ss.size() << "\n\n";

    std::cout << "[5] Removing values...\n";
    ss.remove(5);
    std::cout << "  Removed 5\n";
    std::cout << "  exists(5) = " << ss.exists(5) << "\n";
    std::cout << "  size = " << ss.size() << "\n\n";

    std::cout << "[6] Clearing set...\n";
    ss.clear();
    std::cout << "  size = " << ss.size() << "\n";
    std::cout << "  exists(10) = " << ss.exists(10) << "\n\n";

    std::cout << "Demo complete.\n";
    return 0;
}
/*
==============================
SetStore<T> Demonstration
==============================

[1] Inserting values...
  Inserted values: 10, 5, 20, (10 ignored)

[2] Checking existence...
  exists(10) = true
  exists(50) = false

[3] Getting values...
  get(20) -> 20
  get() smallest -> 5

[4] Set size...
  size = 3

[5] Removing values...
  Removed 5
  exists(5) = false
  size = 2

[6] Clearing set...
  size = 0
  exists(10) = false

Demo complete.
*/



✅ 9. std::unordered_set — Hash-based unique keys
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/
#include <unordered_set>
#include <stdexcept>
#include <utility>
template<typename T>
class UnorderedSetStore {
    std::unordered_set<T> st;
  public:
    // Insert using perfect forwarding
    template<typename U>
    void set(U&& value) {
        st.insert(std::forward<U>(value));
    }

    // C++11-compatible exists()
    bool exists(const T& value) const {
        return st.find(value) != st.end();
    }

    // get(value) — return reference if exists, else throw
    const T& get(const T& value) const {
        auto it = st.find(value);
        if (it == st.end())
            throw std::runtime_error("Value not found in UnorderedSetStore");
        return *it;
    }

    // Optional: get() → return any element (first in bucket order)
    const T& get() const {
        if (st.empty())
            throw std::runtime_error("UnorderedSetStore is empty");
        return *st.begin();   // not ordered, but valid
    }

    // Remove a value
    void remove(const T& value) {
        st.erase(value);
    }

    // Utility functions
    std::size_t size() const { return st.size(); }
    void clear() { st.clear(); }
};
#include <iostream>

int main(int argc, char** argv)
{
    UnorderedSetStore<int> store;

    std::cout << "Inserting values...\n";
    store.set(10);
    store.set(20);
    store.set(10);  // duplicate ignored

    std::cout << "exists(10) = " << std::boolalpha << store.exists(10) << "\n";
    std::cout << "exists(99) = " << store.exists(99) << "\n";

    try {
        std::cout << "get(20) = " << store.get(20) << "\n";
        std::cout << "get() (any element) = " << store.get() << "\n";
        std::cout << "get(30) = " << store.get(30) << "\n";  // throws
    }
    catch (const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << "\n";
    }

    store.remove(10);
    std::cout << "Size after remove: " << store.size() << "\n";

    store.clear();
    std::cout << "Size after clear: " << store.size() << "\n";

    return 0;
}
/* 
Inserting values...
exists(10) = true
exists(99) = false
get(20) = 20
get() (any element) = 20
get(30) = Exception: Value not found in UnorderedSetStore
Size after remove: 1
Size after clear: 0
*/

✅ 10. std::map — Sorted key–value storage
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/

Method 1
#include <map>
#include <iostream>
#include <string>
#include <stdexcept>
template<typename K, typename V>
class MapStore {
    std::map<K, V> mp;
public:
    template<typename Key, typename Val>
    void set(Key&& k, Val&& v) {
        mp[std::forward<Key>(k)] = std::forward<Val>(v);
    }

    const V& get(const K& key) const {
        auto it = mp.find(key);
        if (it == mp.end()) throw std::runtime_error("Key not found");
        return it->second;
    }

    void remove(const K& key) { mp.erase(key); }

    bool exists(const K& key) const { return mp.contains(key); }

    std::size_t size() const { return mp.size(); }
    void clear() { mp.clear(); }
};


int main() {
    MapStore<std::string, int> store;

    // Insert key-value pairs
    store.set("age", 28);
    store.set("score", 88);
    store.set("level", 2);

    // Access values
    try {
        std::cout << "Age: " << store.get("age") << "\n";
        std::cout << "Score: " << store.get("score") << "\n";
        std::cout << "Level: " << store.get("level") << "\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Check existence
    std::cout << "Does 'level' exist? " << (store.exists("level") ? "Yes" : "No") << "\n";
    std::cout << "Does 'rank' exist? " << (store.exists("rank") ? "Yes" : "No") << "\n";

    // Remove a key
    store.remove("level");
    std::cout << "After removing 'level', size: " << store.size() << "\n";

    // Attempt to access removed key
    try {
        store.get("level");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Print all remaining key-value pairs
    std::cout << "Remaining key-value pairs:\n";
    for (const auto& key : {"age", "score", "level"}) {
        if (store.exists(key)) {
            std::cout << key << " : " << store.get(key) << "\n";
        }
    }

    // Clear all entries
    store.clear();
    std::cout << "After clearing, size: " << store.size() << "\n";

    return 0;
}
/*
Age: 28
Score: 88
Level: 2
Does 'level' exist? Yes
Does 'rank' exist? No
After removing 'level', size: 2
Error: Key not found
Remaining key-value pairs:
age : 28
score : 88
After clearing, size: 0
*/



//method 2:
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

template<typename K, typename V>
class MapStore {
    std::map<K, V> mp;

public:
    // Insert or update a key-value pair (perfect forwarding)
    template<typename Key, typename Val>
    void set(Key&& k, Val&& v) {
        mp[std::forward<Key>(k)] = std::forward<Val>(v);
    }

    // Get a value by key (const-correct)
    const V& get(const K& key) const {
        auto it = mp.find(key);
        if (it == mp.end())
            throw std::runtime_error("Key not found: " + key); // Fixed
        return it->second;
    }

    // Remove a key-value pair by key
    void remove(const K& key) {
        auto count = mp.erase(key);
        if (count == 0)
            throw std::runtime_error("Key not found, cannot remove: " + key); // Fixed
    }

    // Check if a key exists
    bool exists(const K& key) const { return mp.contains(key); }

    // Get the number of elements
    std::size_t size() const { return mp.size(); }

    // Clear the map
    void clear() { mp.clear(); }

    // Optional: print all key-value pairs
    void printAll() const {
        for (const auto& [k, v] : mp)
            std::cout << k << " : " << v << "\n";
    }
};

int main() {
    MapStore<std::string, int> store;

    store.set("age", 25);
    store.set("score", 90);
    store.set("level", 5);

    std::cout << "Age: " << store.get("age") << "\n";
    std::cout << "Score: " << store.get("score") << "\n";

    std::cout << "Does 'level' exist? " << (store.exists("level") ? "Yes" : "No") << "\n";

    store.remove("level");
    std::cout << "After removing 'level', size: " << store.size() << "\n";

    store.printAll();

    store.clear();
    std::cout << "After clearing, size: " << store.size() << "\n";

    return 0;
}
/*
Age: 25
Score: 90
Does 'level' exist? Yes
After removing 'level', size: 2
age : 25
score : 90
After clearing, size: 0
*/




✅ 11. std::unordered_map — Hash table key–value
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>

template<typename K, typename V>
class UnorderedMapStore {
    std::unordered_map<K, V> mp;
  public:
    template<typename Key, typename Val>
    void set(Key&& k, Val&& v) {
        mp[std::forward<Key>(k)] = std::forward<Val>(v);
    }

    const V& get(const K& key) const {
        auto it = mp.find(key);
        if (it == mp.end()) throw std::runtime_error("Key not found");
        return it->second;
    }

    void remove(const K& key) { mp.erase(key); }

    bool exists(const K& key) const { return mp.contains(key); }

    std::size_t size() const { return mp.size(); }
    void clear() { mp.clear(); }
};
int main() {
    UnorderedMapStore<std::string, int> store;

    // Insert values
    store.set("age", 30);
    store.set("score", 95);
    store.set("level", 3);

    // Access values
    try {
        std::cout << "Age: " << store.get("age") << "\n";
        std::cout << "Score: " << store.get("score") << "\n";
        std::cout << "Level: " << store.get("level") << "\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Check existence
    std::cout << "Does 'level' exist? " << (store.exists("level") ? "Yes" : "No") << "\n";
    std::cout << "Does 'rank' exist? " << (store.exists("rank") ? "Yes" : "No") << "\n";

    // Remove a key
    store.remove("level");
    std::cout << "After removing 'level', size: " << store.size() << "\n";

    // Attempt to get a removed key (demonstrates error handling)
    try {
        store.get("level");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Print all remaining key-value pairs
    std::cout << "All key-value pairs:\n";
    for (const auto& key : {"age", "score", "level"}) {
        if (store.exists(key)) {
            std::cout << key << " : " << store.get(key) << "\n";
        }
    }

    // Clear the map
    store.clear();
    std::cout << "After clearing, size: " << store.size() << "\n";

    return 0;
}
/*
Age: 30
Score: 95
Level: 3
Does 'level' exist? Yes
Does 'rank' exist? No
After removing 'level', size: 2
Error: Key not found
All key-value pairs:
age : 30
score : 95
After clearing, size: 0
*/



//Method 2:
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>

template<typename K, typename V>
class UnorderedMapStore {
    std::unordered_map<K, V> mp;

  public:
    // Insert or update a key-value pair (perfect forwarding)
    template<typename Key, typename Val>
    void set(Key&& k, Val&& v) {
        mp[std::forward<Key>(k)] = std::forward<Val>(v);
    }

    // Get a value by key (const-correct)
    const V& get(const K& key) const {
        auto it = mp.find(key);
        if (it == mp.end())
            throw std::runtime_error("Key not found: " + toString(key));
        return it->second;
    }

    // Remove a key-value pair by key
    void remove(const K& key) {
        auto count = mp.erase(key);
        if (count == 0)
            throw std::runtime_error("Key not found, cannot remove: " + toString(key));
    }

    // Check if a key exists
    bool exists(const K& key) const { return mp.contains(key); }

    // Get the number of elements
    std::size_t size() const { return mp.size(); }

    // Clear the map
    void clear() { mp.clear(); }

    // Optional: print all key-value pairs
    void printAll() const {
        for (const auto& [k, v] : mp)
            std::cout << toString(k) << " : " << v << "\n";
    }

 private:
    // Helper function to convert key to string (works for string and numeric types)
    template<typename T>
    std::string toString(const T& val) const {
        if constexpr (std::is_convertible_v<T, std::string>)
            return val;
        else
            return std::to_string(val);
    }
};

int main() {
    UnorderedMapStore<std::string, int> store;

    // Insert values
    store.set("age", 25);
    store.set("score", 90);
    store.set("level", 5);

    // Access values
    std::cout << "Age: " << store.get("age") << "\n";
    std::cout << "Score: " << store.get("score") << "\n";

    // Check existence
    std::cout << "Does 'level' exist? " << (store.exists("level") ? "Yes" : "No") << "\n";

    // Remove a key
    store.remove("level");
    std::cout << "After removing 'level', size: " << store.size() << "\n";

    // Print all key-value pairs
    store.printAll();

    // Clear the map
    store.clear();
    std::cout << "After clearing, size: " << store.size() << "\n";

    return 0;
}
/*
Age: 25
Score: 90
Does 'level' exist? Yes
After removing 'level', size: 2
score : 90
age : 25
After clearing, size: 0
*/





✅ 12. std::tuple
- Template-based storage (generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices

/*
================================================================================
HINTS
================================================================================
- Template for value types: template<typename T>
- Exception handling strategy
- Consider move semantics and perfect forwarding
- const-correctness for read operations
*/
Method 1:

#include <tuple>
#include <stdexcept>
#include <utility>
#include <cstddef>
#include <iostream>
template<typename... Ts>
class TupleStore {
    std::tuple<Ts...> data;
    static constexpr std::size_t N = sizeof...(Ts);

 public:
    // ------------------------------------------------------
    // Set element at compile-time index I
    // ------------------------------------------------------
    template<std::size_t I, typename U>
    void set(U&& value) {
        static_assert(I < N, "Tuple index out of range");
        std::get<I>(data) = std::forward<U>(value);
    }

    // ------------------------------------------------------
    // Get element at compile-time index I
    // ------------------------------------------------------
    template<std::size_t I>
    const auto& get() const {
        static_assert(I < N, "Tuple index out of range");
        return std::get<I>(data);
    }

    // ------------------------------------------------------
    // Remove element (reset to default value)
    // ------------------------------------------------------
    template<std::size_t I>
    void remove() {
        static_assert(I < N, "Tuple index out of range");
        std::get<I>(data) = typename std::tuple_element<I, std::tuple<Ts...>>::type{};
    }

    // ------------------------------------------------------
    // Check if index exists (always true if valid)
    // ------------------------------------------------------
    template<std::size_t I>
    bool exists() const {
        static_assert(I < N, "Tuple index out of range");
        return true;
    }

    // ------------------------------------------------------
    // Get total size of the tuple
    // ------------------------------------------------------
    static constexpr std::size_t size() { return N; }

    // ------------------------------------------------------
    // Clear all elements
    // ------------------------------------------------------
    void clear() {
        clear_impl(std::make_index_sequence<N>{});
    }

 private:
    template<std::size_t... Is>
    void clear_impl(std::index_sequence<Is...>) {
        ((std::get<Is>(data) = typename std::tuple_element<Is, std::tuple<Ts...>>::type{}), ...);
    }
};


int main() {
    

    // Demo usage
    TupleStore<int, double, std::string> ts;
    ts.set<0>(100);
    ts.set<1>(9.81);
    ts.set<2>("TupleStore demo");

    std::cout << "Tuple values:\n";
    std::cout << "Index 0: " << ts.get<0>() << "\n";
    std::cout << "Index 1: " << ts.get<1>() << "\n";
    std::cout << "Index 2: " << ts.get<2>() << "\n";

    // Remove and clear
    ts.remove<1>();
    std::cout << "After remove index 1: " << ts.get<1>() << "\n";

    ts.clear();
    std::cout << "After clear:\n";
    std::cout << "Index 0: " << ts.get<0>() << ", Index 1: " << ts.get<1>() << ", Index 2: " << ts.get<2>() << "\n";

    return 0;
}
/* 
Tuple values:
Index 0: 100
Index 1: 9.81
Index 2: TupleStore demo
After remove index 1: 0
After clear:
Index 0: 0, Index 1: 0, Index 2: 
*/


Method 2
#include <tuple>
#include <stdexcept>
#include <utility>
#include <cstddef>
#include <iostream>
#include <string>

template<typename... Ts>
class TupleStore {
    std::tuple<Ts...> data;
    static constexpr std::size_t N = sizeof...(Ts);

public:
    // ------------------------------------------------------
    // Set element at compile-time index I
    // ------------------------------------------------------
    template<std::size_t I, typename U>
    void set(U&& value) {
        static_assert(I < N, "Tuple index out of range");
        std::get<I>(data) = std::forward<U>(value);
    }

    // ------------------------------------------------------
    // Get element at compile-time index I
    // ------------------------------------------------------
    template<std::size_t I>
    const auto& get() const {
        static_assert(I < N, "Tuple index out of range");
        return std::get<I>(data);
    }

    // ------------------------------------------------------
    // Remove element (reset to default value)
    // ------------------------------------------------------
    template<std::size_t I>
    void remove() {
        static_assert(I < N, "Tuple index out of range");
        std::get<I>(data) = typename std::tuple_element<I, std::tuple<Ts...>>::type{};
    }

    // ------------------------------------------------------
    // Check if index exists (always true if valid)
    // ------------------------------------------------------
    template<std::size_t I>
    bool exists() const {
        static_assert(I < N, "Tuple index out of range");
        return true;
    }

    // ------------------------------------------------------
    // Get total size of the tuple
    // ------------------------------------------------------
    static constexpr std::size_t size() { return N; }

    // ------------------------------------------------------
    // Clear all elements (direct fold expression)
    // ------------------------------------------------------
    void clear() {
        ((std::get<Ts>(data) = Ts{}), ...);  // simplified fold expression
    }
};

int main() {
    // Create a TupleStore with int, double, and std::string
    TupleStore<int, double, std::string> ts;

    // Set values
    ts.set<0>(42);
    ts.set<1>(3.14);
    ts.set<2>("Hello TupleStore");

    // Get and print values
    std::cout << "Tuple values:\n";
    std::cout << "Index 0: " << ts.get<0>() << "\n";
    std::cout << "Index 1: " << ts.get<1>() << "\n";
    std::cout << "Index 2: " << ts.get<2>() << "\n";

    // Remove element at index 1
    ts.remove<1>();
    std::cout << "\nAfter removing index 1:\n";
    std::cout << "Index 0: " << ts.get<0>() << "\n";
    std::cout << "Index 1: " << ts.get<1>() << "\n";
    std::cout << "Index 2: " << ts.get<2>() << "\n";

    // Check existence (always true if index is valid)
    std::cout << "\nCheck existence:\n";
    std::cout << "Index 0 exists? " << (ts.exists<0>() ? "Yes" : "No") << "\n";
    std::cout << "Index 1 exists? " << (ts.exists<1>() ? "Yes" : "No") << "\n";
    std::cout << "Index 2 exists? " << (ts.exists<2>() ? "Yes" : "No") << "\n";

    // Clear all elements
    ts.clear();
    std::cout << "\nAfter clear:\n";
    std::cout << "Index 0: " << ts.get<0>() << "\n";
    std::cout << "Index 1: " << ts.get<1>() << "\n";
    std::cout << "Index 2: " << ts.get<2>() << "\n";

    // Print total size
    std::cout << "\nTuple size: " << ts.size() << "\n";

    return 0;
}
/*
Tuple values:
Index 0: 42
Index 1: 3.14
Index 2: Hello TupleStore

After removing index 1:
Index 0: 42
Index 1: 0
Index 2: Hello TupleStore

Check existence:
Index 0 exists? Yes
Index 1 exists? Yes
Index 2 exists? Yes

After clear:
Index 0: 0
Index 1: 0
Index 2: 

Tuple size: 3
*/