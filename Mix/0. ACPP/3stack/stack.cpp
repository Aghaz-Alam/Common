
#include <stack>
#include <stdexcept>
template<typename T>
class StackStore {
    std::stack<T> st;
  public:
    template<typename U>
    void set(U&& value) { st.push(std::forward<U>(value)); }

    const T& get() const {
        if (st.empty()) throw std::runtime_error("Stack is empty");
        return st.top();
    }

    void remove() {
        if (st.empty()) throw std::runtime_error("Stack is empty");
        st.pop();
    }

    bool exists() const { return !st.empty(); }
    std::size_t size() const { return st.size(); }
    void clear() { while (!st.empty()) st.pop(); }
};

#include "test_stackstore.h"

int main() {
    run_stackstore_tests<int>();
    return 0;
}
/* 
Running StackStore Tests...
All StackStore tests passed!
*/