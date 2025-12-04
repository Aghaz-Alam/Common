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

#include "test_queuestore.h"

int main() {
    run_queuestore_tests<int>();
    return 0;
}
/* 
Running QueueStore Tests...
All QueueStore tests passed!
*/