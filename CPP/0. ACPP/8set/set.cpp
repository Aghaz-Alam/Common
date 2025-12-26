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
        return st.find(value) != st.end();
    }

    void remove(const T& value) {
        st.erase(value);
    }

    // Get specific value
    const T& get(const T& value) const {
        auto it = st.find(value);
        if (it == st.end())
            throw std::runtime_error("Value not found in SetStore");
        return *it;
    }

    // Get smallest element
    const T& get() const {
        if (st.empty())
            throw std::runtime_error("Set is empty");
        return *st.begin();
    }

    std::size_t size() const { return st.size(); }

    void clear() { st.clear(); }
};

#include "test_setstore.h"

int main() {
    run_setstore_tests<int>();
    return 0;
}
/* 
Running SetStore Tests...
All SetStore tests passed!
*/