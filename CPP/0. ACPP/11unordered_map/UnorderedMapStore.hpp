#pragma once
#include <unordered_map>
#include <stdexcept>
#include <utility>

template<typename K, typename V>
class UnorderedMapStore {
    std::unordered_map<K, V> mp;

public:
    // ------------------------------------------------------
    // Insert or update using perfect forwarding
    // ------------------------------------------------------
    template<typename Key, typename Val>
    void set(Key&& k, Val&& v) {
        mp[std::forward<Key>(k)] = std::forward<Val>(v);
    }

    // ------------------------------------------------------
    // Retrieve value by key (throws if not found)
    // ------------------------------------------------------
    const V& get(const K& key) const {
        auto it = mp.find(key);
        if (it == mp.end())
            throw std::runtime_error("UnorderedMapStore::get() - key not found");
        return it->second;
    }

    // ------------------------------------------------------
    // Remove key
    // ------------------------------------------------------
    void remove(const K& key) {
        mp.erase(key);
    }

    // ------------------------------------------------------
    // Check existence (C++11-compatible)
    // ------------------------------------------------------
    bool exists(const K& key) const {
        return mp.find(key) != mp.end();
    }

    // ------------------------------------------------------
    // Utilities
    // ------------------------------------------------------
    std::size_t size() const { return mp.size(); }
    void clear() { mp.clear(); }
};
