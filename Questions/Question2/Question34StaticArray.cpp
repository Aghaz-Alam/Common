
34 — Implement Your Own Static Array (`StaticArray<T, N>`)

Implement a template class StaticArray<T, N> with a fixed-size internal array T data[N], 
supporting operator[] with out-of-bounds exception, size(), fill(T), find(const T&), numeric-only sum(), max(), min(), printAll(), 
custom iterators compatible with range-based for loops, and a specialization for bool that packs bits using uint64_t with set(), get(), 
and printBits().

Sample Input:

StaticArray<int, 5> arr;
arr.fill(3);
arr[1] = 10;
arr.printAll();
cout << "Sum: " << arr.sum() << endl;
cout << "Max: " << arr.max() << endl;
cout << "Min: " << arr.min() << endl;

for(auto& x : arr) {
    x += 1;
}
arr.printAll();

// Specialization for bool
StaticArray<bool, 10> b;
b.set(3, true);
b.set(7, true);
b.printBits();


Expected Output

3 10 3 3 3
Sum: 22
Max: 10
Min: 3
4 11 4 4 4
0001000010


#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <limits>
using namespace std;

// =========================================================
// GENERAL TEMPLATE
// =========================================================
template<typename T, size_t N>
class StaticArray {
private:
    T data[N];

public:
    // Iterator implementation
    class Iterator {
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    // Access with bounds checking
    T& operator[](size_t index) {
        if (index >= N)
            throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= N)
            throw out_of_range("Index out of range");
        return data[index];
    }

    // Fill all elements
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++)
            data[i] = value;
    }

    // Find an element → returns index or -1
    int find(const T& value) const {
        for (size_t i = 0; i < N; i++)
            if (data[i] == value)
                return (int)i;
        return -1;
    }

    // Size
    constexpr size_t size() const { return N; }

    // Numeric-only sum()
    template<typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type
    sum() const {
        U s = 0;
        for (size_t i = 0; i < N; i++) s += data[i];
        return s;
    }

    // max()
    template<typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type
    max() const {
        U mx = numeric_limits<U>::lowest();
        for (size_t i = 0; i < N; i++)
            if (data[i] > mx) mx = data[i];
        return mx;
    }

    // min()
    template<typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type
    min() const {
        U mn = numeric_limits<U>::max();
        for (size_t i = 0; i < N; i++)
            if (data[i] < mn) mn = data[i];
        return mn;
    }

    // Print all
    void printAll() const {
        for (size_t i = 0; i < N; i++)
            cout << data[i] << " ";
        cout << endl;
    }

    // Iterators
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + N); }
};


// =========================================================
// SPECIALIZATION FOR bool
// =========================================================
template<size_t N>
class StaticArray<bool, N> {
private:
    static constexpr size_t BLOCK_SIZE = 64;
    static constexpr size_t BLOCK_COUNT = (N + 63) / 64;
    uint64_t blocks[BLOCK_COUNT] = {0};

public:
    // Set bit
    void set(size_t index, bool value) {
        if (index >= N)
            throw out_of_range("Index out of range");
        size_t block = index / 64;
        size_t bit   = index % 64;

        if (value)
            blocks[block] |= (1ULL << bit);
        else
            blocks[block] &= ~(1ULL << bit);
    }

    // Get bit
    bool get(size_t index) const {
        if (index >= N)
            throw out_of_range("Index out of range");
        size_t block = index / 64;
        size_t bit   = index % 64;

        return (blocks[block] >> bit) & 1ULL;
    }

    // Print bit string
    void printBits() const {
        for (size_t i = 0; i < N; i++)
            cout << (get(i) ? '1' : '0');
        cout << endl;
    }
};


// =========================================================
// MAIN (Tests given in the problem)
// =========================================================
int main() {
    StaticArray<int, 5> arr;
    arr.fill(3);
    arr[1] = 10;
    arr.printAll();

    cout << "Sum: " << arr.sum() << endl;
    cout << "Max: " << arr.max() << endl;
    cout << "Min: " << arr.min() << endl;

    for (auto& x : arr) {
        x += 1;
    }
    arr.printAll();

    // Specialization for bool
    StaticArray<bool, 10> b;
    b.set(3, true);
    b.set(7, true);
    b.printBits();

    return 0;
}
/*
3 10 3 3 3
Sum: 22
Max: 10
Min: 3
4 11 4 4 4
0001000010
*/