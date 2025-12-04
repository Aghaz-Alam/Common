//✅ 1. std::array — Fixed-size sequential container
#include <array>
#include <stdexcept>
#include <iostream>
#include <string>
#include <exception>
template<typename T, std::size_t N>
class ArrayStore {
    std::array<T, N> data{};
  public:
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= N) throw std::out_of_range("Array index out of range");
        data[index] = std::forward<U>(value);
    }

    const T& get(std::size_t index) const {
        if (index >= N) throw std::out_of_range("Array index out of range");
        return data[index];
    }

    void remove(std::size_t index) {
        if (index >= N) throw std::out_of_range("Array index out of range");
        data[index] = T{};
    }

    bool exists(std::size_t index) const {
        if (index >= N) return false;
        return true;
    }

    std::size_t size() const { return N; }
    void clear() { data = {}; }
};

#include "test_arraystore.h"
int main() {
    run_all_arraystore_tests<int, 5>();
    return 0;
}
/* 
Output:
Running ArrayStore Unit Tests...
All ArrayStore tests passed successfully!
*/