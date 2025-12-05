/* 
Question 14: Template Class for Stack

Implement a generic stack class using C++ templates.

Requirements:
Implement push(), pop(), top(), and isEmpty() methods.
Demonstrate usage with int and string data types.

Sample Input:
Stack<int> s;
s.push(10);
s.push(20);


Expected Output:
Top element: 20
Popped element: 20
Top element after pop: 10
*/


Template Class for Stack
Includes:
✔ Generic Stack<T>
✔ push(), pop(), top(), isEmpty()
✔ Demonstration with int and std::string
✔ Exception handling for empty stack

#include <iostream>
#include <vector>
#include <stdexcept>
template <typename T>
class Stack {
  private:
    std::vector<T> data;

  public:
    // Check if stack is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Push an element
    void push(const T& value) {
        data.push_back(value);
    }

    // Pop an element
    T pop() {
        if (isEmpty())
            throw std::runtime_error("Stack is empty");

        T value = data.back();
        data.pop_back();
        return value;
    }

    // Get top element
    T top() const {
        if (isEmpty())
            throw std::runtime_error("Stack is empty");

        return data.back();
    }
};

// ---------------------------------------------------
// Demonstration
// ---------------------------------------------------
int main() {
    try {
        Stack<int> s;
        s.push(10);
        s.push(20);

        std::cout << "Top element: " << s.top() << std::endl;

        std::cout << "Popped element: " << s.pop() << std::endl;

        std::cout << "Top element after pop: " << s.top() << std::endl;

        // Using string stack
        Stack<std::string> strStack;
        strStack.push("Hello");
        strStack.push("World");

        std::cout << "String Stack Top: " << strStack.top() << std::endl;
        std::cout << "String Stack Pop: " << strStack.pop() << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
  return 0;
}
/* 
Expected Output:
Top element: 20
Popped element: 20
Top element after pop: 10
String Stack Top: World
String Stack Pop: World
*/