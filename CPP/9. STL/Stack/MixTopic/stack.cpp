Key Characteristics of a Stack:
LIFO (Last In, First Out): The most recently added element is the first to be removed.
Push Operation: Adds an element to the top of the stack.
Pop Operation: Removes the element from the top of the stack.
Top Operation: Returns the element at the top without removing it.
Empty Check: Checks if the stack is empty.


//Creating a Stack:
#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> stack; // stack of integers
    // Add elements to the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Access the top element
    cout << "Top element: " << stack.top() << endl; // Output: 30

    // Remove elements from the stack
    stack.pop();
    cout << "Top element after pop: " << stack.top() << endl; // Output: 20

    // Check if the stack is empty
    if (stack.empty()) {
        cout << "Stack is empty." << endl;
    } 
    else {
        cout << "Stack is not empty." << endl; // Output: Stack is not empty.
    }

    // Get the size of the stack
    cout << "Stack size: " << stack.size() << endl; // Output: 2

    return 0;
}
/*
Output:
Top element: 30
Top element after pop: 20
Stack is not empty.
Stack size: 2
*/



Important Methods of std::stack:
push(const T& value): Adds an element to the top of the stack.
Example:
stack.push(10); // Adds 10 to the stack


pop(): Removes the element at the top of the stack.
Example:
stack.pop(); // Removes the top element


top(): Returns the element at the top of the stack without removing it.
Example:
std::cout << "Top element: " << stack.top() << std::endl;


empty(): Returns true if the stack is empty, false otherwise.
Example:
if (stack.empty()) {
    std::cout << "Stack is empty" << std::endl;
}


size(): Returns the number of elements in the stack.
Example:
std::cout << "Stack size: " << stack.size() << std::endl;





#include <iostream>
#include <stdexcept>
class MyStack {
  private:
    int* arr;     // Pointer to the array that will hold the stack elements
    int n;        // Current size of the stack (number of elements in stack)
    int cap;      // Capacity of the stack (size of the array)

  public:
    // Constructor
    MyStack() : arr(nullptr), n(0), cap(0) {}

    // Destructor
    ~MyStack() {
        delete[] arr;
    }

    // Push an element onto the stack
    void push(int val) {
        if (n == cap) {
            // If the stack is full, double the capacity
            cap = (cap == 0) ? 1 : cap * 2;
            int* newarr = new int[cap];
            
            // Copy existing elements to the new array
            for (int i = 0; i < n; i++) {
                newarr[i] = arr[i];
            }
            delete[] arr;  // Delete the old array
            arr = newarr;  // Update arr to point to the new array
        }
        
        // Add the new element at the end (top of the stack)
        arr[n++] = val;
    }

    // Pop the element from the top of the stack
    void pop() {
        if (n == 0) {
            throw std::out_of_range("pop called on an empty stack");
        }
        n--;  // Decrease the size of the stack
    }

    // Get the element at the top of the stack
    int top() const {
        if (n == 0) {
            throw std::out_of_range("top called on an empty stack");
        }
        return arr[n - 1];
    }

    // Check if the stack is empty
    bool empty() const {
        return n == 0;
    }

    // Get the size of the stack
    int size() const {
        return n;
    }

    // Get the capacity of the stack
    int capacity() const {
        return cap;
    }
};

int main() {
    MyStack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);

    std::cout << "Stack size: " << stack.size() << std::endl;
    std::cout << "Stack capacity: " << stack.capacity() << std::endl;

    std::cout << "Top element: " << stack.top() << std::endl;

    std::cout << "Popping elements: ";
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;

    try {
        // Trying to pop from an empty stack (this should throw an error)
        stack.pop();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}



//Example of Using std::stack in C++:
#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> stack; // Create an empty stack of integers

    // Push elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Output the top element of the stack
    cout << "Top element: " << stack.top() << endl; // Output: 30

    // Pop an element from the stack
    stack.pop(); // Removes 30

    // Output the new top element after popping
    cout << "Top element after pop: " << stack.top() << endl; // Output: 20

    // Check if the stack is empty
    if (!stack.empty()) {
        cout << "Stack is not empty" << endl; // Output: Stack is not empty
    }

    // Print the size of the stack
    cout << "Size of stack: " << stack.size() << endl; // Output: 2

    // Pop all elements
    stack.pop(); // Removes 20
    stack.pop(); // Removes 10

    // Check if the stack is empty
    if (stack.empty()) {
        cout << "Stack is empty" << endl; // Output: Stack is empty
    }

   return 0;
}
/*
Output:
Top element: 30
Top element after pop: 20
Stack is not empty
Size of stack: 2
Stack is empty
*/




Custom Stack Implementation Using std::vector:
#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;
class Stack {
  private:
    int* data;          // Pointer to dynamic array (stack storage)
    int topIndex;       // Index of the top element in the stack
    int capacity;       // Capacity of the stack (size of the underlying array)

    // Resize the array when the stack is full
    void resize(int newCapacity) {
        int* newData = new int[newCapacity];  // Allocate new array with increased capacity
        for (int i = 0; i < capacity; ++i) {
            newData[i] = data[i];  // Copy elements from old array to new array
        }
        delete[] data;  // Free the old array
        data = newData;  // Point to the new array
        capacity = newCapacity;  // Update the capacity
    }

  public:
    // Constructor
    Stack(int initialCapacity = 10) : topIndex(-1), capacity(initialCapacity) {
        data = new int[capacity];  // Allocate memory for the array
    }

    // Destructor to free allocated memory
    ~Stack() {
        delete[] data;
    }

    // Push an element onto the stack
    void push(int value) {
        if (topIndex + 1 == capacity) {
            resize(capacity * 2);  // Double the capacity if the stack is full
        }
        data[++topIndex] = value;  // Add the element to the stack
    }

    // Pop an element from the stack
    void pop() {
        if (topIndex == -1) {
            throw std::underflow_error("Stack is empty!");
        }
        --topIndex;  // Remove the element from the top of the stack
    }

    // Return the top element without removing it
    int top() const {
        if (topIndex == -1) {
            throw std::underflow_error("Stack is empty!");
        }
        return data[topIndex];
    }

    // Check if the stack is empty
    bool empty() const {
        return topIndex == -1;
    }

    // Get the size of the stack
    int size() const {
        return topIndex + 1;
    }

    // Get the capacity of the stack
    int getCapacity() const {
        return capacity;
    }
};

int main() {
    Stack stack;  // Create a stack with default initial capacity (10)

    // Push elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);

    // Display the top element
    cout << "Top element: " << stack.top() << endl; // Output: 40

    // Pop an element
    stack.pop();

    // Display the top element after popping
    cout << "Top element after pop: " << stack.top() << endl; // Output: 30

    // Display stack size and capacity
    cout << "Stack size: " << stack.size() << endl;      // Output: 3
    cout << "Stack capacity: " << stack.getCapacity() << endl; // Output: 10

    // Check if stack is empty
    if (!stack.empty()) {
        cout << "Stack is not empty" << endl; // Output: Stack is not empty
    }

    // Pop all elements
    stack.pop();
    stack.pop();
    stack.pop();

    // Check if the stack is empty
    if (stack.empty()) {
        cout << "Stack is empty" << endl; // Output: Stack is empty
    }

    return 0;
}
/*
Top element: 40
Top element after pop: 30
Stack size: 3
Stack capacity: 10
Stack is not empty
Stack is empty
*/




Custom Stack Implementation Using std::vector:
#include <iostream>
#include <vector>
#include <stdexcept> // For exceptions

class Stack {
private:
    std::vector<int> data; // underlying container for stack

public:
    // Push an element onto the stack
    void push(const int& value) {
        data.push_back(value);
    }

    // Pop an element from the stack
    void pop() {
        if (data.empty()) {
            throw std::underflow_error("Stack is empty!");
        }
        data.pop_back();
    }

    // Return the top element without removing it
    int top() const {
        if (data.empty()) {
            throw std::underflow_error("Stack is empty!");
        }
        return data.back();
    }

    // Check if the stack is empty
    bool empty() const {
        return data.empty();
    }

    // Get the size of the stack
    int size() const {
        return data.size();
    }
};

int main() {
    Stack stack;

    // Push elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Display top element
    cout << "Top element: " << stack.top() << endl; // Output: 30

    // Pop an element
    stack.pop();

    // Display top element again
    cout << "Top element after pop: " << stack.top() << endl; // Output: 20

    // Check if stack is empty
    if (!stack.empty()) {
        cout << "Stack is not empty" << endl; // Output: Stack is not empty
    }

    // Get the stack size
    cout << "Stack size: " << stack.size() << endl; // Output: 2

    return 0;
}
/*
Output:
Top element: 30
Top element after pop: 20
Stack is not empty
Stack size: 2
*/













