/* 
26. File-based Key-Value Store (Persistence, concurrency)

Problem: Build a simple persistent key-value store class KVStore with methods put(key, value), get(key), remove(key) and crash-safe persistence.

Requirements / Features:
Use append-only log file. Implement compaction to shrink file.
Support concurrency using a file lock or mutex.
Provide a CLI to put, get, delete.
*/



Design Overview
kvstore.log — append-only file (WAL)
Every write appends a record:
PUT key length value length key value
DEL key length key

In-memory unordered_map<string, string> index
Loaded at startup by replaying log
Compaction rewrites only active keys
Thread-safe using std::mutex


//C++ Program
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

class KVStore {
private:
    std::string filename;
    std::unordered_map<std::string, std::string> db;
    std::mutex mtx;

public:
    explicit KVStore(const std::string& file = "kvstore.log")
        : filename(file) 
    {
        loadFromLog();
    }

    // -------------------------------------------
    // Load append-only log into memory
    // -------------------------------------------
    void loadFromLog() {
        std::ifstream in(filename, std::ios::binary);
        if (!in) return; // file doesn't exist yet

        while (in) {
            char type;
            in.read(&type, 1);
            if (!in) break;

            if (type == 'P') {     // PUT
                uint32_t klen, vlen;
                in.read(reinterpret_cast<char*>(&klen), sizeof(klen));
                in.read(reinterpret_cast<char*>(&vlen), sizeof(vlen));

                std::string key(klen, '\0');
                std::string value(vlen, '\0');

                in.read(&key[0], klen);
                in.read(&value[0], vlen);

                db[key] = value;
            } 
            else if (type == 'D') {  // DELETE
                uint32_t klen;
                in.read(reinterpret_cast<char*>(&klen), sizeof(klen));
                std::string key(klen, '\0');
                in.read(&key[0], klen);

                db.erase(key);
            }
        }
    }

    // -------------------------------------------
    // Put operation (thread-safe, append-only)
    // -------------------------------------------
    void put(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(mtx);

        std::ofstream out(filename, std::ios::binary | std::ios::app);
        if (!out) throw std::runtime_error("Cannot open log file");

        char type = 'P';
        uint32_t klen = key.size();
        uint32_t vlen = value.size();

        out.write(&type, 1);
        out.write(reinterpret_cast<char*>(&klen), sizeof(klen));
        out.write(reinterpret_cast<char*>(&vlen), sizeof(vlen));
        out.write(key.data(), klen);
        out.write(value.data(), vlen);
        out.flush();

        db[key] = value;  // update memory
    }

    // -------------------------------------------
    // Get operation
    // -------------------------------------------
    std::string get(const std::string& key) {
        std::lock_guard<std::mutex> lock(mtx);
        if (db.count(key) == 0) throw std::runtime_error("Key not found");
        return db[key];
    }

    // -------------------------------------------
    // Remove operation
    // -------------------------------------------
    void remove(const std::string& key) {
        std::lock_guard<std::mutex> lock(mtx);

        if (db.count(key) == 0) return;

        std::ofstream out(filename, std::ios::binary | std::ios::app);
        if (!out) throw std::runtime_error("Cannot open log file");

        char type = 'D';
        uint32_t klen = key.size();

        out.write(&type, 1);
        out.write(reinterpret_cast<char*>(&klen), sizeof(klen));
        out.write(key.data(), klen);
        out.flush();

        db.erase(key);
    }

    // -------------------------------------------
    // Compact log (remove deleted / overwritten keys)
    // -------------------------------------------
    void compact() {
        std::lock_guard<std::mutex> lock(mtx);

        std::string tmpFile = filename + ".tmp";
        std::ofstream out(tmpFile, std::ios::binary);
        if (!out) throw std::runtime_error("Cannot open temporary file");

        for (auto& p : db) {
            char type = 'P';
            uint32_t klen = p.first.size();
            uint32_t vlen = p.second.size();

            out.write(&type, 1);
            out.write(reinterpret_cast<char*>(&klen), sizeof(klen));
            out.write(reinterpret_cast<char*>(&vlen), sizeof(vlen));
            out.write(p.first.data(), klen);
            out.write(p.second.data(), vlen);
        }
        out.close();

        std::remove(filename.c_str());
        std::rename(tmpFile.c_str(), filename.c_str());
    }
};



// ------------------------------------------------------------
// Simple CLI wrapper
// Commands:
//   put key value
//   get key
//   del key
//   compact
//   exit
// ------------------------------------------------------------
int main() {
    KVStore store("kvstore.log");

    std::cout << "KVStore CLI\n"
              << "Commands: put <k> <v> | get <k> | del <k> | compact | exit\n";

    while (true) {
        std::string cmd;
        std::cout << "> ";
        if (!(std::cin >> cmd)) break;

        try {
            if (cmd == "put") {
                std::string k, v;
                std::cin >> k >> v;
                store.put(k, v);
                std::cout << "OK\n";
            }
            else if (cmd == "get") {
                std::string k;
                std::cin >> k;
                std::cout << store.get(k) << "\n";
            }
            else if (cmd == "del") {
                std::string k;
                std::cin >> k;
                store.remove(k);
                std::cout << "OK\n";
            }
            else if (cmd == "compact") {
                store.compact();
                std::cout << "Compacted.\n";
            }
            else if (cmd == "exit") break;
            else {
                std::cout << "Unknown command\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}
/* 
✅ How it Works
Append-only writes
Each write is appended to kvstore.log
Safe even if program crashes midway (previous data remains)
Crash-safe
No in-place modification
Replay on startup rebuilds the state
Concurrency

A mutex protects:
index map
file writes
Compaction
Writes only current valid keys to a new file
Replaces old log
*/



/* 
✅ Sample CLI Session + Output
User Input
put name Alice
put lang C++
get name
put name Bob
get name
del lang
get lang
compact
exit

🎯 Actual Output Produced by Your Program
KVStore CLI
Commands: put <k> <v> | get <k> | del <k> | compact | exit
> put name Alice
OK
> put lang C++
OK
> get name
Alice
> put name Bob
OK
> get name
Bob
> del lang
OK
> get lang
Error: Key not found
> compact
Compacted.
> exit

🔍 Explanation of What Happened
1. put name Alice
Appends "Alice" for key "name" to the log → prints OK

2. put lang C++
Saves another key-value → prints OK

3. get name
Returns "Alice"

4. put name Bob
Overwrites "Alice" in memory (but old versions still exist on disk) → prints OK

5. get name
Now returns "Bob"

6. del lang
Deletes "lang" key → prints OK

7. get lang
It no longer exists → prints:
Error: Key not found

8. compact
Rewrites file with only active keys:
name → Bob

Prints:
Compacted.
*/