#pragma once
#include <unordered_set>
#include <stdexcept>
#include <utility>

template<typename T>
class UnorderedSetStore {
    std::unordered_set<T> st;

  public:
    // ------------------------------------------------------
    // Insert — perfect forwarding
    // ------------------------------------------------------
    template<typename U>
    void set(U&& value) {
        st.insert(std::forward<U>(value));
    }

    // ------------------------------------------------------
    // Check existence — C++11 compatible
    // ------------------------------------------------------
    bool exists(const T& value) const {
        return st.find(value) != st.end();
    }

    // ------------------------------------------------------
    // get(value) — returns the stored value or throws
    // ------------------------------------------------------
    const T& get(const T& value) const {
        auto it = st.find(value);
        if (it == st.end())
            throw std::out_of_range("UnorderedSetStore::get() - key not found");
        return *it;
    }

    // ------------------------------------------------------
    // get() — return any element (first in bucket order)
    // ------------------------------------------------------
    const T& get() const {
        if (st.empty())
            throw std::runtime_error("UnorderedSetStore is empty");
        return *st.begin();  // not ordered, but valid
    }

    // ------------------------------------------------------
    // Remove a value
    // ------------------------------------------------------
    void remove(const T& value) {
        st.erase(value);
    }

    // ------------------------------------------------------
    // Utilities
    // ------------------------------------------------------
    std::size_t size() const { return st.size(); }
    void clear() { st.clear(); }
};
