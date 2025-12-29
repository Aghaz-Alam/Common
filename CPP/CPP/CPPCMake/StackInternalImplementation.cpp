//Stack Implementation using dynamic array with template with grow and shrink 
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

template <typename T>
class MyStack {
 private:
    T* arr;
    size_t topIndex;
    size_t cap;

    // -------- Resize exactly like vector --------
    void resize(size_t newCap) {
        if (newCap < topIndex) newCap = topIndex;

        if (newCap == 0) newCap = 1;

        T* newArr = new T[newCap];

        for (size_t i = 0; i < topIndex; ++i){
            newArr[i] = std::move(arr[i]);
        }
        delete[] arr;
        arr = newArr;
        cap = newCap;
    }

  public:
    MyStack() : arr(nullptr), topIndex(0), cap(0) {}
    ~MyStack() { 
        delete[] arr;
    }

    // -------- L-value push --------
    void push(const T& value) {
        if (topIndex == cap){
             resize(cap == 0 ? 1 : cap * 2);
        }
        arr[topIndex++] = value;
    }

    // -------- R-value push --------
    void push(T&& val) {
        if (topIndex == cap){
            resize(cap == 0 ? 1 : cap * 2);
        }
        
        arr[topIndex++] = std::move(val);
    }

    // -------- pop --------
    void pop() {
        if (topIndex == 0) throw underflow_error("Stack is empty!");

        topIndex--;

        if (topIndex > 0 && topIndex == cap / 4){
            resize(cap / 2);   // auto shrink
        }
    }

    // -------- top --------
    T top() const {
        if (topIndex == 0) throw underflow_error("Stack is empty!");

        return arr[topIndex - 1];
    }

    bool empty() const { 
        return topIndex == 0;
    }
    size_t size() const { 
        return topIndex;
    }
    size_t getCap() const { 
        return cap;
    }

    void Display() const {
        for (size_t i = 0; i < topIndex; ++i)
            cout << arr[i] << " ";
    }
};

int main() {
    try {
        MyStack<int> stk;

        cout << "===== R-VALUE PUSH TESTS =====\n";
        stk.push(10);
        stk.push(20);
        stk.push(30);
        stk.push(40);

        cout << "Stack Elements: ";
        stk.Display();
        cout << endl;

        cout << "===== L-VALUE PUSH TESTS =====\n";
        int a = 50, b = 60;
        stk.push(a);
        stk.push(b);

        cout << "Stack Elements: ";
        stk.Display();
        cout << endl;

        cout << "===== FORCED R-VALUE USING std::move =====\n";
        stk.push(std::move(a));   // rvalue
        cout << "Stack Elements: ";
        stk.Display();
        cout << endl;

        cout << "Top element: " << stk.top() << endl;

        stk.pop();
        cout << "Top after pop: " << stk.top() << endl;
        cout << "Size: " << stk.size() << endl;
        cout << "Capacity: " << stk.getCap() << endl;

        cout << "\n===== POP ALL =====\n";
        while (!stk.empty()){
            stk.pop();
        }
        cout << "Stack empty now.\n";

        cout << "Trying to pop from empty stack...\n";
        stk.pop();   // underflow

    }
    catch (const underflow_error& e) {
        cout << "Underflow Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "General Exception: " << e.what() << endl;
    }

    return 0;
}
/*
===== R-VALUE PUSH TESTS =====
Stack Elements: 10 20 30 40 

===== L-VALUE PUSH TESTS =====
Stack Elements: 10 20 30 40 50 60 

===== FORCED R-VALUE USING std::move =====
Stack Elements: 10 20 30 40 50 60 50 

Top element: 50
Top after pop: 60
Size: 6
Capacity: 8

===== POP ALL =====
Stack empty now.

Trying to pop from empty stack...
Underflow Error: Stack is empty!
dell@dell-Latitude-5420:~/Music/Self/Common/9. STL/Stack$ g++ StackInternalImplementation.cpp -o stk
dell@dell-Latitude-5420:~/Music/Self/Common/9. STL/Stack$ ./stk 
===== R-VALUE PUSH TESTS =====
Stack Elements: 10 20 30 40 

===== L-VALUE PUSH TESTS =====
Stack Elements: 10 20 30 40 50 60 

===== FORCED R-VALUE USING std::move =====
Stack Elements: 10 20 30 40 50 60 50 
Top element: 50
Top after pop: 60
Size: 6
Capacity: 8

===== POP ALL =====
Stack empty now.
Trying to pop from empty stack...
Underflow Error: Stack is empty!
*/


