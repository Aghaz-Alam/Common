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
#include "test_liststore.h"

int main() {
    run_liststore_tests<int>();
    return 0;
}
/* 
Running ListStore Tests...
All ListStore tests passed!
*/