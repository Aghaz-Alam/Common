/* 
25. Balanced Parentheses with Template-based Stack (Templates, STL)

Problem: Write a template Stack<T> class with basic operations, then use it to check balanced parentheses (including (), {}, []) for an input string.

Requirements / Features:
Template stack implemented from scratch (dynamic array or linked list).
Support push, pop, top, empty.
Use it to validate input strings; report the first mismatched position (index) if invalid.

Sample Input: {[()()]} -> valid; ([)] -> mismatch at index X.
*/


#include <iostream>
#include <stdexcept>
#include <string>

// =======================================================
// Template Stack<T> (Dynamic Array Implementation)
// =======================================================
template <typename T>
class Stack {
private:
    T* data;
    size_t capacity;
    size_t topIndex;

    void resize() {
        size_t newCap = capacity * 2;
        T* newData = new T[newCap];
        for (size_t i = 0; i < topIndex; i++)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    Stack(size_t cap = 10) : capacity(cap), topIndex(0) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (topIndex == capacity)
            resize();
        data[topIndex++] = value;
    }

    void pop() {
        if (empty())
            throw std::runtime_error("Pop from empty stack");
        topIndex--;
    }

    T& top() {
        if (empty())
            throw std::runtime_error("Top from empty stack");
        return data[topIndex - 1];
    }

    bool empty() const {
        return topIndex == 0;
    }
};

// =======================================================
// Balanced Parentheses Checker
// =======================================================
bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

std::pair<bool, int> checkBalanced(const std::string& s) {
    Stack<char> st;

    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (st.empty())
                return {false, i};  // closing without opening

            char top = st.top();
            st.pop();

            if (!isMatching(top, c))
                return {false, i};  // mismatch
        }
    }

    if (!st.empty())
        return {false, (int)s.size()}; // extra openings

    return {true, -1};
}

// =======================================================
// Main (Demonstration)
// =======================================================
int main() {
    std::string s;

    std::cout << "Enter expression: ";
    std::cin >> s;

    auto result = checkBalanced(s);

    if (result.first)
        std::cout << "Balanced\n";
    else
        std::cout << "Mismatch at index " << result.second << "\n";

    return 0;
}
/* 
✅ Sample Tests
Input
{[()()]}

Output
Balanced

Input
([)]

Output
Mismatch at index 2

(At index 2 you have ) but expected ].)

Input
(((()))

Output
Mismatch at index 7

Extra ( at the end.
*/