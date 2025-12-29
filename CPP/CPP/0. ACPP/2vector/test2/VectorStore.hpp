#pragma once
#include <vector>
#include <stdexcept>
#include <utility>

template<typename T>
class VectorStore {
    std::vector<T> data;

public:
    // Set a value at index; auto-resize if needed
    template<typename U>
    void set(std::size_t index, U&& value) {
        if (index >= data.size()) data.resize(index + 1);
        data[index] = std::forward<U>(value);
    }

    // Get value at index; throws if out-of-range
    const T& get(std::size_t index) const {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Remove element at index; shifts elements left
    void remove(std::size_t index) {
        if (index >= data.size()) throw std::out_of_range("Index out of range");
        data.erase(data.begin() + index);
    }

    // Check existence of index
    bool exists(std::size_t index) const { return index < data.size(); }

    // Number of elements
    std::size_t size() const { return data.size(); }

    // Clear container
    void clear() { data.clear(); }
};
