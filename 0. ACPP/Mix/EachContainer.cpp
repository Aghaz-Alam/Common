/* 
std::array, std::vector, std::stack, std::queue, std::dequeue, std::forward_list, std::list, std::set, std::unordered_set, std::map, std::unordered_map
- Template-based storage (string keys, generic values)
- Standard operations: set, get, remove, exists, size, clear
- Proper error handling for invalid operations
- Consider performance implications of your design choices
- Ensure const-correctness and modern C++ practices
 */


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


// 11 separate standalone programs with main()
// Program 1: std::array
#include <iostream>
#include <array>
#include <optional>
#include <string>
using namespace std;

template<typename T, size_t N>
class ArrayStore {
    pair<string, T> data[N];
    size_t sz = 0;

  public:
    // Set or update value
    template<typename U>
    bool set(const string& key, U&& val) {
        for(size_t i = 0; i < sz; i++)
            if(data[i].first == key) {
                data[i].second = forward<U>(val);
                return true;
            }
        if(sz >= N) return false;
        data[sz++] = {key, forward<U>(val)};
        return true;
    }

    // Get value
    optional<T> get(const string& key) const {
        for(size_t i = 0; i < sz; i++)
            if(data[i].first == key)
                return data[i].second;
        return nullopt;
    }

    // Remove key
    bool remove(const string& key) {
        for(size_t i = 0; i < sz; i++)
            if(data[i].first == key) {
                data[i] = data[sz - 1];
                sz--;
                return true;
            }
        return false;
    }

    // Exists?
    bool exists(const string& key) const {
        return get(key).has_value();
    }

    // Size
    size_t size() const {
        return sz;
    }

    // Clear
    void clear() {
        sz = 0;
    }
};

int main() {
    ArrayStore<int, 5> store;

    // 1. set()
    cout << "Setting values...\n";
    store.set("a", 10);
    store.set("b", 20);
    store.set("c", 30);

    // 2. get()
    cout << "Get a: " << *store.get("a") << "\n";
    cout << "Get b: " << *store.get("b") << "\n";

    // 3. exists()
    cout << "Exists c? " << (store.exists("c") ? "yes" : "no") << "\n";
    cout << "Exists z? " << (store.exists("z") ? "yes" : "no") << "\n";

    // 4. size()
    cout << "Current size: " << store.size() << "\n";

    // 5. remove()
    cout << "Removing b...\n";
    store.remove("b");
    cout << "Exists b? " << (store.exists("b") ? "yes" : "no") << "\n";
    cout << "Size after removal: " << store.size() << "\n";

    // 6. update existing key
    cout << "Updating a...\n";
    store.set("a", 999);
    cout << "Get a: " << *store.get("a") << "\n";

    // 7. clear()
    cout << "Clearing all data...\n";
    store.clear();
    cout << "Size after clear: " << store.size() << "\n";

    return 0;
}

/*
EXPECTED OUTPUT:

Setting values...
Get a: 10
Get b: 20
Exists c? yes
Exists z? no
Current size: 3
Removing b...
Exists b? no
Size after removal: 2
Updating a...
Get a: 999
Clearing all data...
Size after clear: 0
*/


// Program 2: std::vector
#include <iostream>
#include <vector>
#include <optional>
#include <string>
using namespace std;

template<typename T>
class VectorStore {
    vector<pair<string, T>> v;

public:
    // Set or update value
    template<typename U>
    bool set(const string& key, U&& val) {
        for (auto& a : v)
            if (a.first == key) {
                a.second = forward<U>(val);
                return true;
            }
        v.emplace_back(key, forward<U>(val));
        return true;
    }

    // Get a value
    optional<T> get(const string& key) const {
        for (const auto& a : v)
            if (a.first == key)
                return a.second;
        return nullopt;
    }

    // Remove a key
    bool remove(const string& key) {
        for (size_t i = 0; i < v.size(); i++)
            if (v[i].first == key) {
                v[i] = v.back();
                v.pop_back();
                return true;
            }
        return false;
    }

    bool exists(const string& key) const {
        return get(key).has_value();
    }

    size_t size() const {
        return v.size();
    }

    void clear() {
        v.clear();
    }
};

int main() {
    VectorStore<int> store;

    // 1. set()
    cout << "Setting values...\n";
    store.set("x", 10);
    store.set("y", 20);
    store.set("z", 30);

    // 2. get()
    cout << "Get x: " << *store.get("x") << "\n";
    cout << "Get y: " << *store.get("y") << "\n";

    // 3. exists()
    cout << "Exists z? " << (store.exists("z") ? "yes" : "no") << "\n";
    cout << "Exists k? " << (store.exists("k") ? "yes" : "no") << "\n";

    // 4. size()
    cout << "Current size: " << store.size() << "\n";

    // 5. remove()
    cout << "Removing y...\n";
    store.remove("y");
    cout << "Exists y? " << (store.exists("y") ? "yes" : "no") << "\n";
    cout << "Size after removal: " << store.size() << "\n";

    // 6. update existing key
    cout << "Updating x...\n";
    store.set("x", 999);
    cout << "Get x: " << *store.get("x") << "\n";

    // 7. clear()
    cout << "Clearing all data...\n";
    store.clear();
    cout << "Size after clear: " << store.size() << "\n";

    return 0;
}

/*
EXPECTED OUTPUT:

Setting values...
Get x: 10
Get y: 20
Exists z? yes
Exists k? no
Current size: 3
Removing y...
Exists y? no
Size after removal: 2
Updating x...
Get x: 999
Clearing all data...
Size after clear: 0
*/


// Program 3: std::stack
#include <iostream>
#include <stack>
#include <optional>
#include <string>
using namespace std;

template<typename T>
class StackStore {
    stack<pair<string, T>> st;

  public:

    // Insert always pushes new pair (LIFO)
    template<typename U>
    void set(const string& key, U&& value) {
        st.push({key, forward<U>(value)});
    }

    // Get by copying stack (since stack can't iterate)
    optional<T> get(const string& key) const {
        auto temp = st;
        while (!temp.empty()) {
            if (temp.top().first == key)
                return temp.top().second;
            temp.pop();
        }
        return nullopt;
    }

    // Check if exists
    bool exists(const string& key) const {
        return get(key).has_value();
    }

    // Remove a key by rebuilding stack
    bool remove(const string& key) {
        stack<pair<string, T>> temp, rebuilt;
        bool found = false;

        // Reverse order by moving to temp
        while (!st.empty()) {
            temp.push(st.top());
            st.pop();
        }

        // Rebuild stack skipping the key
        while (!temp.empty()) {
            if (temp.top().first == key) {
                found = true;
            } else {
                rebuilt.push(temp.top());
            }
            temp.pop();
        }

        st = rebuilt;
        return found;
    }

    // Size
    size_t size() const {
        return st.size();
    }

    // Clear everything
    void clear() {
        while (!st.empty())
            st.pop();
    }
};

// ---------------------- MAIN ----------------------
int main() {
    StackStore<int> store;

    // 1. set()
    cout << "Pushing values...\n";
    store.set("a", 10);
    store.set("b", 20);
    store.set("c", 30);

    // 2. get()
    cout << "Get b: " << *store.get("b") << "\n";

    // 3. exists()
    cout << "Exists c? " << (store.exists("c") ? "yes" : "no") << "\n";
    cout << "Exists z? " << (store.exists("z") ? "yes" : "no") << "\n";

    // 4. size()
    cout << "Size: " << store.size() << "\n";

    // 5. remove()
    cout << "Removing b...\n";
    store.remove("b");
    cout << "Exists b? " << (store.exists("b") ? "yes" : "no") << "\n";

    // 6. clear()
    cout << "Clearing stack...\n";
    store.clear();
    cout << "Size after clear: " << store.size() << "\n";

    return 0;
}
/*
EXPECTED OUTPUT:

Pushing values...
Get b: 20
Exists c? yes
Exists z? no
Size: 3
Removing b...
Exists b? no
Clearing stack...
Size after clear: 0
*/

// Program 4: std::queue
#include <iostream>
#include <queue>
#include <optional>
#include <string>
using namespace std;

template<typename T>
class QueueStore {
    queue<pair<string, T>> q;

public:

    // Insert at back (FIFO)
    template<typename U>
    void set(const string& key, U&& value) {
        q.emplace(key, forward<U>(value));
    }

    // Search by copying the queue
    optional<T> get(const string& key) const {
        auto temp = q;
        while (!temp.empty()) {
            if (temp.front().first == key)
                return temp.front().second;
            temp.pop();
        }
        return nullopt;
    }

    // Check existence
    bool exists(const string& key) const {
        return get(key).has_value();
    }

    // Remove a key by rebuilding queue
    bool remove(const string& key) {
        queue<pair<string, T>> rebuilt;
        bool found = false;

        while (!q.empty()) {
            if (q.front().first == key) {
                found = true;     // skip this entry
            } else {
                rebuilt.push(q.front());
            }
            q.pop();
        }
        q = move(rebuilt);
        return found;
    }

    // Queue size
    size_t size() const {
        return q.size();
    }

    // Clear queue
    void clear() {
        while (!q.empty())
            q.pop();
    }
};

// ---------------------- MAIN ----------------------

int main() {
    QueueStore<int> store;

    // 1. set()
    cout << "Enqueue values...\n";
    store.set("a", 10);
    store.set("b", 20);
    store.set("c", 30);

    // 2. get()
    cout << "Get b: " << *store.get("b") << "\n";

    // 3. exists()
    cout << "Exists c? " << (store.exists("c") ? "yes" : "no") << "\n";
    cout << "Exists z? " << (store.exists("z") ? "yes" : "no") << "\n";

    // 4. size()
    cout << "Current size: " << store.size() << "\n";

    // 5. remove()
    cout << "Removing b...\n";
    store.remove("b");
    cout << "Exists b? " << (store.exists("b") ? "yes" : "no") << "\n";
    cout << "Size after removal: " << store.size() << "\n";

    // 6. update existing key (just inserts duplicate; queue FIFO)
    store.set("a", 999);
    cout << "Get new 'a': " << *store.get("a") << "\n";

    // 7. clear()
    cout << "Clearing queue...\n";
    store.clear();
    cout << "Size after clear: " << store.size() << "\n";

    return 0;
}

/*
EXPECTED OUTPUT:

Enqueue values...
Get b: 20
Exists c? yes
Exists z? no
Current size: 3
Removing b...
Exists b? no
Size after removal: 2
Get new 'a': 999
Clearing queue...
Size after clear: 0

*/

// Program 5: std::deque
#include <iostream>
#include <deque>
#include <optional>
#include <string>
using namespace std;

template<typename T>
class DequeStore {
    deque<pair<string, T>> d;

public:

    // Insert or update
    template<typename U>
    bool set(const string& key, U&& value) {
        for (auto& a : d)
            if (a.first == key) {
                a.second = forward<U>(value);
                return true;
            }
        d.emplace_back(key, forward<U>(value));
        return true;
    }

    // Get
    optional<T> get(const string& key) const {
        for (const auto& a : d)
            if (a.first == key)
                return a.second;
        return nullopt;
    }

    // Exists
    bool exists(const string& key) const {
        return get(key).has_value();
    }

    // Remove by linear search
    bool remove(const string& key) {
        for (auto it = d.begin(); it != d.end(); ++it) {
            if (it->first == key) {
                d.erase(it);
                return true;
            }
        }
        return false;
    }

    // Size
    size_t size() const {
        return d.size();
    }

    // Clear
    void clear() {
        d.clear();
    }
};

// ------------------------ MAIN ------------------------

int main() {
    DequeStore<int> store;

    // 1. set()
    cout << "Inserting values...\n";
    store.set("x", 10);
    store.set("y", 20);
    store.set("z", 30);

    // 2. get()
    cout << "Get y: " << *store.get("y") << "\n";

    // 3. exists()
    cout << "Exists z? " << (store.exists("z") ? "yes" : "no") << "\n";
    cout << "Exists k? " << (store.exists("k") ? "yes" : "no") << "\n";

    // 4. size()
    cout << "Size: " << store.size() << "\n";

    // 5. remove()
    cout << "Removing y...\n";
    store.remove("y");
    cout << "Exists y? " << (store.exists("y") ? "yes" : "no") << "\n";
    cout << "Size after removal: " << store.size() << "\n";

    // 6. update existing key
    cout << "Updating x...\n";
    store.set("x", 999);
    cout << "Get x: " << *store.get("x") << "\n";

    // 7. clear()
    cout << "Clearing deque...\n";
    store.clear();
    cout << "Size after clear: " << store.size() << "\n";

    return 0;
}
/*
EXPECTED OUTPUT:

Inserting values...
Get y: 20
Exists z? yes
Exists k? no
Size: 3
Removing y...
Exists y? no
Size after removal: 2
Updating x...
Get x: 999
Clearing deque...
Size after clear: 0
*/


// Program 6: std::forward_list
#include <iostream>
#include <forward_list>
#include <optional>
#include <string>
using namespace std;
template<typename T>
class FLStore {
    forward_list<pair<string, T>> f;
  public:
    // Insert or update
    template<typename U>
    bool set(const string& key, U&& value) {
        for (auto& a : f)
            if (a.first == key) {
                a.second = forward<U>(value);
                return true;
            }
        f.emplace_front(key, forward<U>(value));
        return true;
    }

    // Get
    optional<T> get(const string& key) const {
        for (const auto& a : f)
            if (a.first == key)
                return a.second;
        return nullopt;
    }

    // Exists
    bool exists(const string& key) const {
        return get(key).has_value();
    }

    // Remove using erase_after with previous iterator
    bool remove(const string& key) {
        auto prev = f.before_begin();
        for (auto cur = f.begin(); cur != f.end(); ++cur) {
            if (cur->first == key) {
                f.erase_after(prev);
                return true;
            }
            ++prev;
        }
        return false;
    }

    // Size (manual)
    size_t size() const {
        size_t cnt = 0;
        for (const auto& a : f) cnt++;
        return cnt;
    }

    // Clear
    void clear() {
        f.clear();
    }
};
int main() {
    FLStore<int> store;
    // 1. set()
    cout << "Inserting values...\n";
    store.set("a", 10);
    store.set("b", 20);
    store.set("c", 30);

    // 2. get()
    cout << "Get b: " << *store.get("b") << "\n";

    // 3. exists()
    cout << "Exists c? " << (store.exists("c") ? "yes" : "no") << "\n";
    cout << "Exists x? " << (store.exists("x") ? "yes" : "no") << "\n";

    // 4. size()
    cout << "Size: " << store.size() << "\n";

    // 5. remove()
    cout << "Removing b...\n";
    store.remove("b");
    cout << "Exists b? " << (store.exists("b") ? "yes" : "no") << "\n";
    cout << "Size after removal: " << store.size() << "\n";

    // 6. update existing key
    cout << "Updating a...\n";
    store.set("a", 999);
    cout << "Get updated a: " << *store.get("a") << "\n";

    // 7. clear()
    cout << "Clearing...\n";
    store.clear();
    cout << "Size after clear: " << store.size() << "\n";

    return 0;
}
/*
EXPECTED OUTPUT:

Inserting values...
Get b: 20
Exists c? yes
Exists x? no
Size: 3
Removing b...
Exists b? no
Size after removal: 2
Updating a...
Get updated a: 999
Clearing...
Size after clear: 0
*/


// Program 7: std::list
#include <iostream>
#include <list>
#include <optional>
#include <string>
using namespace std;

template<typename T>
class ListStore{
    list<pair<string,T>> L;
  public:

    // insert or update
    template<typename U>
    bool set(const string& k, U&& v){
        for (auto &a : L)
            if (a.first == k){
                a.second = forward<U>(v);
                return true;
            }
        L.emplace_back(k, forward<U>(v));
        return true;
    }

    // read key
    optional<T> get(const string& k) const{
        for (auto &a : L)
            if (a.first == k)
                return a.second;
        return nullopt;
    }

    // extra: show all
    void printAll() const{
        cout << "Current ListStore: ";
        for (auto &p : L)
            cout << "[" << p.first << ":" << p.second << "] ";
        cout << "\n";
    }
};

int main(){ 
    ListStore<int> s; 
    
    // insert
    s.set("n", 88);
    s.set("x", 55);

    // update existing key
    s.set("n", 100);

    // get
    cout << "Value of n: " << *s.get("n") << "\n";
    cout << "Value of x: " << *s.get("x") << "\n";

    // print entire store
    s.printAll();
}

/*
EXPECTED OUTPUT:
Value of n: 100
Value of x: 55
Current ListStore: [n:100] [x:55]
*/



// Program 8: std::set
#include <iostream>
#include <set>
#include <optional>
#include <string>
using namespace std;
// comparator based only on key
template<typename T>
struct Cmp {
    bool operator()(const pair<string,T>& a, const pair<string,T>& b) const {
        return a.first < b.first;
    }
};
template<typename T>
class SetStore {
    set<pair<string,T>, Cmp<T>> S;
  public:
    // insert or update
    template<typename U>
    bool Set(const string& k, U&& v) {
        auto it = S.lower_bound({k, T{}});
        if (it != S.end() && it->first == k)
            S.erase(it);                 // erase old value
        S.insert({k, forward<U>(v)});     // insert new
        return true;
    }

    // lookup
    optional<T> Get(const string& k) const {
        auto it = S.lower_bound({k, T{}});
        if (it != S.end() && it->first == k)
            return it->second;
        return nullopt;
    }

    // extra: print all
    void printAll() const {
        cout << "SetStore content: ";
        for (auto &p : S) cout << "[" << p.first << ":" << p.second << "] ";
        cout << "\n";
    }
};
int main() {
    SetStore<int> s;
    // insert
    s.Set("x", 111);
    s.Set("a", 10);

    // update existing key
    s.Set("x", 500);

    // get values
    cout << "Value of x: " << *s.Get("x") << "\n";
    cout << "Value of a: " << *s.Get("a") << "\n";

    // print full store
    s.printAll();
}
/*
EXPECTED OUTPUT:
Value of x: 500
Value of a: 10
SetStore content: [a:10] [x:500]
*/





// Program 9: std::unordered_set
#include <iostream>
#include <unordered_set>
#include <optional>
#include <string>
using namespace std;

// Hash functor (hash only by key)
template<typename T>
struct PH {
    size_t operator()(const pair<string,T>& p) const {
        return hash<string>{}(p.first);
    }
};

// Equality functor (compare only key)
template<typename T>
struct PE {
    bool operator()(const pair<string,T>& a, const pair<string,T>& b) const {
        return a.first == b.first;
    }
};

template<typename T>
class USetStore {
    unordered_set<pair<string,T>, PH<T>, PE<T>> U;

  public:
    // insert or update
    template<typename Uv>
    bool set(const string& k, Uv&& v) {
        auto it = U.find({k, T{}});
        if (it != U.end())
            U.erase(it);
        U.insert({k, forward<Uv>(v)});
        return true;
    }

    // lookup
    optional<T> get(const string& k) const {
        auto it = U.find({k, T{}});
        if (it != U.end())
            return it->second;
        return nullopt;
    }

    // check exists
    bool exists(const string& k) const {
        return U.find({k, T{}}) != U.end();
    }

    // remove
    bool remove(const string& k) {
        auto it = U.find({k, T{}});
        if (it != U.end()) {
            U.erase(it);
            return true;
        }
        return false;
    }

    size_t size() const { return U.size(); }

    void clear() { U.clear(); }
};

int main() {
    USetStore<int> s;

    // set values
    s.set("key", 321);
    s.set("alpha", 11);
    s.set("beta", 22);

    // get values
    cout << "key = " << *s.get("key") << "\n";
    cout << "alpha = " << *s.get("alpha") << "\n";

    // exists?
    cout << "Does 'beta' exist? " << (s.exists("beta") ? "YES" : "NO") << "\n";

    // remove
    s.remove("alpha");

    // size
    cout << "Size after removal = " << s.size() << "\n";

    // clear
    s.clear();
    cout << "Size after clear = " << s.size() << "\n";
}

/*
EXPECTED OUTPUT (order may vary due to hashing):

key = 321
alpha = 11
Does 'beta' exist? YES
Size after removal = 2
Size after clear = 0
*/





// Program 10: std::map
#include <iostream>
#include <map>
#include <optional>
#include <string>
using namespace std;

template<typename T>
class MapStore {
    map<string, T> M;

public:
    // insert or update
    template<typename U>
    bool set(const string& k, U&& v) {
        M[k] = forward<U>(v);
        return true;
    }

    // lookup
    optional<T> get(const string& k) const {
        auto it = M.find(k);
        if (it != M.end())
            return it->second;
        return nullopt;
    }

    // exists
    bool exists(const string& k) const {
        return M.find(k) != M.end();
    }

    // remove
    bool remove(const string& k) {
        return M.erase(k) > 0;
    }

    // size
    size_t size() const {
        return M.size();
    }

    // clear
    void clear() {
        M.clear();
    }

    // print
    void printAll() const {
        cout << "MapStore content: ";
        for (auto& p : M)
            cout << "[" << p.first << ":" << p.second << "] ";
        cout << "\n";
    }
};

int main() {
    MapStore<int> s;

    // set values
    s.set("id", 55);
    s.set("age", 20);
    s.set("score", 90);

    // get values
    cout << "id = " << *s.get("id") << "\n";
    cout << "age = " << *s.get("age") << "\n";

    // exists?
    cout << "Does 'score' exist? " << (s.exists("score") ? "YES" : "NO") << "\n";

    // remove
    s.remove("age");

    // size
    cout << "Size after removal = " << s.size() << "\n";

    // print
    s.printAll();

    // clear
    s.clear();
    cout << "Size after clear = " << s.size() << "\n";
}

/*
EXPECTED OUTPUT:
id = 55
age = 20
Does 'score' exist? YES
Size after removal = 2
MapStore content: [id:55] [score:90]
Size after clear = 0
*/





// Program 11: std::unordered_map
#include <iostream>
#include <unordered_map>
#include <optional>
#include <string>
using namespace std;
template<typename T>
class UMapStore {
    unordered_map<string, T> M;

  public:
    // insert or update
    template<typename U>
    bool set(const string& k, U&& v) {
        M[k] = forward<U>(v);
        return true;
    }

    // lookup
    optional<T> get(const string& k) const {
        auto it = M.find(k);
        if (it != M.end())
            return it->second;
        return nullopt;
    }

    // exists?
    bool exists(const string& k) const {
        return M.find(k) != M.end();
    }

    // remove
    bool remove(const string& k) {
        return M.erase(k) > 0;
    }

    // size
    size_t size() const {
        return M.size();
    }

    // clear
    void clear() {
        M.clear();
    }

    // print
    void printAll() const {
        cout << "UMapStore content: ";
        for (auto& p : M)
            cout << "[" << p.first << ":" << p.second << "] ";
        cout << "\n";
    }
};
int main() {
    UMapStore<int> s;

    // insert
    s.set("a", 909);
    s.set("b", 100);
    s.set("c", 50);

    // get values
    cout << "a = " << *s.get("a") << "\n";
    cout << "b = " << *s.get("b") << "\n";

    // exists?
    cout << "Does key 'c' exist? " << (s.exists("c") ? "YES" : "NO") << "\n";

    // remove
    s.remove("b");

    // size
    cout << "Size = " << s.size() << "\n";

    // print contents
    s.printAll();

    // clear
    s.clear();
    cout << "Size after clear = " << s.size() << "\n";
}
/*
EXPECTED OUTPUT (order may vary due to hashing):
a = 909
b = 100
Does key 'c' exist? YES
Size = 2
UMapStore content: [a:909] [c:50]
Size after clear = 0
*/

