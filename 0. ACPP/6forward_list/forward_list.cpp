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
#include "test_forwardliststore.h"
int main() {
    run_forwardliststore_tests<int>();
    return 0;
}
/* 
Running ForwardListStore Tests...
All ForwardListStore tests passed!
*/