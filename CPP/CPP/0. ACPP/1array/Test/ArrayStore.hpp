#pragma once
#include <array>
#include <stdexcept>
#include <utility>

template<typename T, std::size_t N>
class ArrayStore {
    std::array<T, N> data{};

public:
    // Set value at index
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= N) throw std::out_of_range("Array index out of range");
        data[index] = std::forward<U>(value);
    }

    // Get value at index
    const T& get(std::size_t index) const {
        if (index >= N) throw std::out_of_range("Array index out of range");
        return data[index];
    }

    // Remove value at index (reset to default)
    void remove(std::size_t index) {
        if (index >= N) throw std::out_of_range("Array index out of range");
        data[index] = T{};
    }

    // Check if index is valid
    bool exists(std::size_t index) const {
        return index < N;
    }

    // Return fixed size
    std::size_t size() const { return N; }

    // Clear array (reset all elements)
    void clear() { data.fill(T{}); }
};
