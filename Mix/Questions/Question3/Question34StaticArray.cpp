/* 
34 — Implement Your Own Static Array (`StaticArray<T, N>`)

Implement a template class StaticArray<T, N> with a fixed-size internal array T data[N], supporting operator[] with out-of-bounds exception, 
size(), fill(T), find(const T&), numeric-only sum(), max(), min(), printAll(), custom iterators compatible with range-based for loops, 
and a specialization for bool that packs bits using uint64_t with set(), get(), and printBits().

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

*/

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <limits>
using namespace std;

// ===============================
//      Generic Template Class
// ===============================
template <typename T, size_t N>
class StaticArray {
  private:
    T data[N];

  public:
    // ---- Iterator support ----
    T* begin() { return data; }
    T* end() { return data + N; }
    const T* begin() const { return data; }
    const T* end() const { return data + N; }

    // ---- Operator [] with bounds check ----
    T& operator[](size_t index) {
        if (index >= N) throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= N) throw out_of_range("Index out of range");
        return data[index];
    }

    // ---- Get size ----
    constexpr size_t size() const { return N; }

    // ---- Fill all elements ----
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++)
            data[i] = value;
    }

    // ---- Find element ----
    int find(const T& value) const {
        for (size_t i = 0; i < N; i++)
            if (data[i] == value)
                return (int)i;
        return -1;
    }

    // ---- Sum (numeric types only) ----
    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type sum() const {
        U total = 0;
        for (size_t i = 0; i < N; i++)
            total += data[i];
        return total;
    }

    // ---- Max (numeric only) ----
    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type max() const {
        U m = numeric_limits<U>::lowest();
        for (size_t i = 0; i < N; i++)
            if (data[i] > m) m = data[i];
        return m;
    }

    // ---- Min (numeric only) ----
    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type min() const {
        U m = numeric_limits<U>::max();
        for (size_t i = 0; i < N; i++)
            if (data[i] < m) m = data[i];
        return m;
    }

    // ---- Print all ----
    void printAll() const {
        for (size_t i = 0; i < N; i++)
            cout << data[i] << " ";
        cout << endl;
    }
};

// =====================================
//   Specialization for bool type
//   Packed bits using uint64_t
// =====================================
template <size_t N>
class StaticArray<bool, N> {
  private:
    static constexpr size_t BLOCKS = (N + 63) / 64;
    uint64_t bits[BLOCKS] = {0};

  public:
    // Set a bool value
    void set(size_t index, bool value) {
        if (index >= N) throw out_of_range("Index out of range");
        size_t block = index / 64;
        size_t pos = index % 64;

        if (value)
            bits[block] |= (1ULL << pos);
        else
            bits[block] &= ~(1ULL << pos);
    }

    // Get a bool value
    bool get(size_t index) const {
        if (index >= N) throw out_of_range("Index out of range");
        size_t block = index / 64;
        size_t pos = index % 64;

        return (bits[block] >> pos) & 1ULL;
    }

    // Print bit sequence (LSB → left)
    void printBits() const {
        for (size_t i = 0; i < N; i++)
            cout << (get(i) ? '1' : '0');
        cout << endl;
    }
};

// ===============================
//            MAIN
// ===============================
int main() {
    StaticArray<int, 5> arr;
    arr.fill(3);
    arr[1] = 10;
    arr.printAll();

    cout << "Sum: " << arr.sum() << endl;
    cout << "Max: " << arr.max() << endl;
    cout << "Min: " << arr.min() << endl;

    // Range-based for loop using custom iterators
    for (auto& x : arr) {
        x += 1;
    }
    arr.printAll();

    // ---- Bool specialization ----
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