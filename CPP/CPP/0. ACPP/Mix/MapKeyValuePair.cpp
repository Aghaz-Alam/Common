#include <iostream>
#include <unordered_map>
#include <optional>
#include <string>
#include <vector>
#include <functional>

using namespace std;

template<typename T>
class KeyValueDB {
   private:
    unordered_map<string, T> data;      // MAIN database
    unordered_map<string, T> backup;    // transaction snapshot
    bool in_txn = false;

   public:
    /* ================= BASIC OPS ================= */

    void set(const string& key, const T& value) {
        data[key] = value;
    }

    void set(const string& key, T&& value) {
        data[key] = std::move(value);
    }

    optional<T> get(const string& key) const {
        auto it = data.find(key);
        if (it == data.end())
            return nullopt;
        return it->second;
    }

    bool exists(const string& key) const {
        return data.count(key) > 0;
    }

    bool remove(const string& key) {
        return data.erase(key) > 0;
    }

    size_t size() const {
        return data.size();
    }

    void clear() {
        data.clear();
    }

    /* ================= BATCH OPS ================= */

    void set_many(const vector<pair<string, T>>& items) {
        for (const auto& [k, v] : items)
            data[k] = v;
    }

    unordered_map<string, optional<T>>
    get_many(const vector<string>& keys) const {
        unordered_map<string, optional<T>> result;
        for (const auto& key : keys)
            result[key] = get(key);
        return result;
    }

    size_t remove_many(const vector<string>& keys) {
        size_t count = 0;
        for (const auto& key : keys)
            count += data.erase(key);
        return count;
    }

    /* ================= TRANSACTIONS ================= */

    bool begin() {
        if (in_txn) return false;
        backup = data;      // snapshot
        in_txn = true;
        return true;
    }

    bool commit() {
        if (!in_txn) return false;
        backup.clear();     // keep current data
        in_txn = false;
        return true;
    }

    bool rollback() {
        if (!in_txn) return false;
        data = std::move(backup);  // 🔥 restore
        backup.clear();
        in_txn = false;
        return true;
    }

    bool in_transaction() const {
        return in_txn;
    }

    /* ================= ADVANCED QUERIES ================= */

    vector<string> get_all_keys() const {
        vector<string> keys;
        for (const auto& [k, _] : data)
            keys.push_back(k);
        return keys;
    }

    vector<T> get_all_values() const {
        vector<T> values;
        for (const auto& [_, v] : data)
            values.push_back(v);
        return values;
    }

    unordered_map<string, T>
    filter(function<bool(const string&, const T&)> predicate) const {
        unordered_map<string, T> result;
        for (const auto& [k, v] : data) {
            if (predicate(k, v))
                result.emplace(k, v);
        }
        return result;
    }
};
int main() {
    KeyValueDB<int> db;

    cout << "===== BASIC OPERATIONS =====\n";

    // set (lvalue)
    db.set("one", 1);
    db.set("two", 2);

    // set (rvalue)
    db.set("three", std::move(3));

    cout << "Size: " << db.size() << endl;

    // get
    auto val = db.get("two");
    if (val)
        cout << "Get 'two': " << *val << endl;

    // exists
    cout << "Exists 'one': " << db.exists("one") << endl;
    cout << "Exists 'four': " << db.exists("four") << endl;

    // remove
    db.remove("one");
    cout << "After removing 'one', exists: " << db.exists("one") << endl;

    cout << "\n===== BATCH OPERATIONS =====\n";

    // set_many
    db.set_many({
        {"four", 4},
        {"five", 5},
        {"six", 6}
    });

    cout << "Size after set_many: " << db.size() << endl;

    // get_many
    auto results = db.get_many({"two", "five", "ten"});
    for (auto& [k, v] : results) {
        if (v)
            cout << k << " -> " << *v << endl;
        else
            cout << k << " -> NOT FOUND\n";
    }

    // remove_many
    size_t removed = db.remove_many({"two", "six"});
    cout << "Removed count: " << removed << endl;
    cout << "Size after remove_many: " << db.size() << endl;

    cout << "\n===== TRANSACTIONS =====\n";

    cout << "Begin transaction: " << db.begin() << endl;
    cout << "In transaction: " << db.in_transaction() << endl;

    db.set("seven", 7);
    db.remove("four");

    cout << "Rolling back...\n";
    db.rollback();

    cout << "After rollback, exists 'seven': " << db.exists("seven") << endl;
    cout << "After rollback, exists 'four': " << db.exists("four") << endl;

    cout << "\nBegin transaction again\n";
    db.begin();
    db.set("eight", 8);
    db.commit();

    cout << "After commit, exists 'eight': " << db.exists("eight") << endl;
    cout << "In transaction: " << db.in_transaction() << endl;

    cout << "\n===== ADVANCED QUERIES =====\n";

    // get_all_keys
    auto keys = db.get_all_keys();
    cout << "All Keys:\n";
    for (auto& k : keys)
        cout << k << endl;

    // get_all_values
    auto values = db.get_all_values();
    cout << "All Values:\n";
    for (auto v : values)
        cout << v << endl;

    // filter
    auto even = db.filter([](const string&, int v) {
        return v % 2 == 0;
    });

    cout << "Filtered (Even Values):\n";
    for (auto& [k, v] : even)
        cout << k << " -> " << v << endl;

    cout << "\n===== CLEAR =====\n";

    db.clear();
    cout << "Size after clear: " << db.size() << endl;

    return 0;
}

/* 
===== BASIC OPERATIONS =====
Size: 3
Get 'two': 2
Exists 'one': 1
Exists 'four': 0
After removing 'one', exists: 0

===== BATCH OPERATIONS =====
Size after set_many: 5
two -> 2
five -> 5
ten -> NOT FOUND
Removed count: 2
Size after remove_many: 3

===== TRANSACTIONS =====
Begin transaction: 1
In transaction: 1
Rolling back...
After rollback, exists 'seven': 0
After rollback, exists 'four': 1

Begin transaction again
After commit, exists 'eight': 1
In transaction: 0

===== ADVANCED QUERIES =====
All Keys:
four
five
eight
All Values:
4
5
8
Filtered (Even Values):
four -> 4
eight -> 8

===== CLEAR =====
Size after clear: 0

 */
