#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
template<typename T>
class VectorStore {
    std::vector<T> data;
  public:
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= data.size()) data.resize(index + 1);
        data[index] = std::forward<U>(value);
    }

    const T& get(std::size_t index) const {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void remove(std::size_t index) {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        data.erase(data.begin() + index);
    }

    bool exists(std::size_t index) const {
        return index < data.size();
    }

    std::size_t size() const { return data.size(); }
    void clear() { data.clear(); }
};

#include "test_vectorstore.h"

int main() {
    run_vectorstore_tests<int>();
    return 0;
}
/* 
Running VectorStore Tests...
All VectorStore tests passed!
*/

