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
#include "test_dequestore.h"

int main() {
    run_dequestore_tests<int>();
    return 0;
}
/* 
Running DequeStore Tests...
All DequeStore tests passed!
*/
