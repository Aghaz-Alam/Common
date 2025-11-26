//Stack Implementation using dynamic array without template
#include <iostream>
#include <stdexcept>
using namespace std;

class MyStack {
private:
    int* arr;
    size_t topIndex;
    size_t cap;

public:
    // Constructor
    MyStack(); 

    // Destructor
    ~MyStack();

    void push(const int& value);   // L-value version
    void push(int&& value);        // R-value version
    void pop();
    int top() const;
    bool empty() const;
    size_t size() const;
    size_t getCap() const;
    void Display() const;

private:
    void resize();
};

// Constructor
MyStack::MyStack(): arr(nullptr), topIndex(0), cap(0) {}

// Destructor
MyStack::~MyStack(){delete[] arr; }

void MyStack::resize() {
    cap = (cap == 0) ? 1 : cap * 2;

    int* newArr = new int[cap];
    for (size_t i = 0; i < topIndex; ++i)
        newArr[i] = arr[i];

    delete[] arr;
    arr = newArr;
}

// L-VALUE PUSH
void MyStack::push(const int& value) {
    if (topIndex == cap){
        resize();
    }
    arr[topIndex++] = value;
}

// R-VALUE PUSH
void MyStack::push(int&& value){ 
    if(topIndex == cap ){
        resize();
    }
    arr[topIndex++] = std::move(value);
}

void MyStack::pop() {
    if (topIndex == 0)
        throw underflow_error("Stack is empty!");
    --topIndex;
}

int MyStack::top() const {
    if (topIndex == 0)
        throw underflow_error("Stack is empty!");
    return arr[topIndex - 1];
}

bool MyStack::empty() const {
    return topIndex == 0;
}

size_t MyStack::size() const {
    return topIndex;
}

size_t MyStack::getCap() const {
    return cap;
}

void MyStack::Display() const {
    for (size_t i = 0; i < topIndex; ++i)
        cout << arr[i] << " ";
}

int main() {
    try {
        MyStack stk;

        cout << "Demonstrate L-value push" << endl;
        int a = 10;     // a is lvalue
        int b = 20;     // b is lvalue

        stk.push(a);        // L-value overload called
        stk.push(b);        // L-value overload called
        
        cout << "Stack Elements with L-value: ";
        stk.Display();
        cout << endl;

        cout << "\nDemonstrate R-value push" << endl;
        stk.push(30);       // R-value overload called
        stk.push(40 + 10);  // R-value overload called (expression result is rvalue)

        cout << "Stack Elements with R-value: ";
        stk.Display();
        cout << endl;

        cout << "Top element: " << stk.top() << endl;

        stk.pop();
        cout << "Top after pop: " << stk.top() << endl;

        cout << "Stack size: " << stk.size() << endl;
        cout << "Stack capacity: " << stk.getCap() << endl;

        cout << "Clearing stack..." << endl;
        while (!stk.empty())
            stk.pop();

        cout << "Trying to pop from empty stack..." << endl;
        stk.pop();  // will throw

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
Demonstrate L-value push
Stack Elements with L-value: 10 20 

Demonstrate R-value push
Stack Elements with R-value: 10 20 30 50 
Top element: 50
Top after pop: 30
Stack size: 3
Stack capacity: 4
Clearing stack...
Trying to pop from empty stack...
Underflow Error: Stack is empty!
*/




// Stack Implementation using FIXED SIZE array (no dynamic memory)
#include <iostream>
#include <stdexcept>
using namespace std;

class MyStack {
private:
    static const size_t cap = 5;   // FIXED SIZE STACK
    int arr[cap];
    size_t topIndex;

public:
    // Constructor
    MyStack() : topIndex(0) {}

    // Destructor
    ~MyStack() {}

    void push(const int& value);   // L-value version
    void push(int&& value);        // R-value version
    void pop();
    int top() const;
    bool empty() const;
    size_t size() const;
    size_t getCap() const { return cap; }
    void Display() const;
};

// L-VALUE PUSH
void MyStack::push(const int& value) {
    if (topIndex == cap)
        throw overflow_error("Stack overflow! No more space.");

    arr[topIndex++] = value;
}

// R-VALUE PUSH
void MyStack::push(int&& value) {
    if (topIndex == cap)
        throw overflow_error("Stack overflow! No more space.");

    arr[topIndex++] = std::move(value);
}

void MyStack::pop() {
    if (topIndex == 0)
        throw underflow_error("Stack is empty!");
    --topIndex;
}

int MyStack::top() const {
    if (topIndex == 0)
        throw underflow_error("Stack is empty!");
    return arr[topIndex - 1];
}

bool MyStack::empty() const {
    return topIndex == 0;
}

size_t MyStack::size() const {
    return topIndex;
}

void MyStack::Display() const {
    for (size_t i = 0; i < topIndex; ++i)
        cout << arr[i] << " ";
}

int main() {
    try {
        MyStack stk;

        cout << "Demonstrate L-value push" << endl;
        int a = 10;     // lvalue
        int b = 20;     // lvalue

        stk.push(a);    
        stk.push(b);

        cout << "Stack Elements with L-value: ";
        stk.Display();
        cout << endl;

        cout << "\nDemonstrate R-value push" << endl;
        stk.push(30);      
        stk.push(40 + 10);

        cout << "Stack Elements with R-value: ";
        stk.Display();
        cout << endl;

        cout << "Top element: " << stk.top() << endl;

        stk.pop();
        cout << "Top after pop: " << stk.top() << endl;

        cout << "Stack size: " << stk.size() << endl;
        cout << "Stack capacity: " << stk.getCap() << endl;

        cout << "\nTrying to push beyond capacity..." << endl;
        stk.push(99);   // This will succeed (5th element)

        stk.push(100);  // This will throw overflow_error

    }
    catch (const overflow_error& e) {
        cout << "Overflow Error: " << e.what() << endl;
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
Demonstrate L-value push
Stack Elements with L-value: 10 20 

Demonstrate R-value push
Stack Elements with R-value: 10 20 30 50 
Top element: 50
Top after pop: 30
Stack size: 3
Stack capacity: 5

Trying to push beyond capacity...
*/



//Stack Implementation using dynamic array with template
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class MyStack {
  private:
    T* arr;
    size_t topIndex;
    size_t cap;
    void resize();

  public:
    MyStack();
    ~MyStack();

    void push(const T& value);  // l-value push
    void push(T&& val);         // r-value push

    void pop();
    T top() const;
    bool empty() const;
    size_t size() const;
    size_t getCap() const;
    void Display() const;
};

// Constructor
template <typename T>
MyStack<T>::MyStack(): arr(nullptr), topIndex(0), cap(0) {}

// Destructor
template <typename T>
MyStack<T>::~MyStack(){ delete[] arr; }

template <typename T>
void MyStack<T>::resize() {
    cap = (cap == 0) ? 1 : cap * 2;

    T* newArr = new T[cap];   // <-- FIXED: must be T*, not int*

    for (size_t i = 0; i < topIndex; ++i)
        newArr[i] = arr[i];

    delete[] arr;
    arr = newArr;
}

template <typename T>
void MyStack<T>::push(const T& value) {
    if (topIndex == cap)
        resize();

    cout << "(l-value push) ";
    arr[topIndex++] = value;
}

template <typename T>
void MyStack<T>::push(T&& val) {
    if (topIndex == cap)
        resize();

    cout << "(r-value push) ";
    arr[topIndex++] = std::move(val);   
}

template <typename T>
void MyStack<T>::pop() {
    if (topIndex == 0) throw underflow_error("Stack is empty!");

    --topIndex;
}

template <typename T>
T MyStack<T>::top() const {
    if (topIndex == 0) throw underflow_error("Stack is empty!");

    return arr[topIndex - 1];
}

template <typename T>
bool MyStack<T>::empty() const {
    return topIndex == 0;
}

template <typename T>
size_t MyStack<T>::size() const {
    return topIndex;
}

template <typename T>
size_t MyStack<T>::getCap() const {
    return cap;
}

template <typename T>
void MyStack<T>::Display() const {
    for (size_t i = 0; i < topIndex; ++i)
        cout << arr[i] << " ";
}

int main() {
    try {
        MyStack<int> stackInt;

        cout << "===== R-VALUE PUSH TESTS =====\n";
        stackInt.push(10);   // r-value
        stackInt.push(20);   // r-value
        stackInt.push(30);   // r-value
        stackInt.push(40);   // r-value

        cout << "\nStack Elements: ";
        stackInt.Display();
        cout << endl;

        cout << "\n===== L-VALUE PUSH TESTS =====\n";
        int a = 50;
        int b = 60;
        stackInt.push(a);   // l-value
        stackInt.push(b);   // l-value

        cout << "\nStack Elements: ";
        stackInt.Display();
        cout << endl;

        cout << "\n===== FORCED R-VALUE USING std::move =====\n";
        stackInt.push(std::move(a));  // r-value
        cout << "\nStack Elements: ";
        stackInt.Display();
        cout << endl;


        cout << "\nTop element: " << stackInt.top() << endl;

        stackInt.pop();
        cout << "Top after pop: " << stackInt.top() << endl;
        cout << "Size: " << stackInt.size() << endl;
        cout << "Capacity: " << stackInt.getCap() << endl;

        while (!stackInt.empty())
            stackInt.pop();

        cout << "\nTrying to pop from empty stack...\n";
        stackInt.pop();   // underflow

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
(r-value push) (r-value push) (r-value push) (r-value push) 
Stack Elements: 10 20 30 40 

===== L-VALUE PUSH TESTS =====
(l-value push) (l-value push) 
Stack Elements: 10 20 30 40 50 60 

===== FORCED R-VALUE USING std::move =====
(r-value push) 
Stack Elements: 10 20 30 40 50 60 50 

Top element: 50
Top after pop: 60
Size: 6
Capacity: 8

Trying to pop from empty stack...
Underflow Error: Stack is empty!
*/



//Fixed-Size Template Stack (With L-value & R-value)
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T, size_t CAP>
class MyStack {
private:
    T arr[CAP];      // FIXED SIZE array
    size_t topIndex;

public:
    MyStack() : topIndex(0) {}
    ~MyStack() {}

    void push(const T& value);   // L-value push
    void push(T&& value);        // R-value push
    void pop();
    T top() const;
    bool empty() const;
    size_t size() const;
    size_t capacity() const { return CAP; }
    void Display() const;
};

// -------------------- PUSH (L-value) --------------------
template <typename T, size_t CAP>
void MyStack<T, CAP>::push(const T& value) {
    if (topIndex == CAP)
        throw overflow_error("Stack overflow! No space left.");

    cout << "(l-value push) ";
    arr[topIndex++] = value;
}

// -------------------- PUSH (R-value) --------------------
template <typename T, size_t CAP>
void MyStack<T, CAP>::push(T&& value) {
    if (topIndex == CAP)
        throw overflow_error("Stack overflow! No space left.");

    cout << "(r-value push) ";
    arr[topIndex++] = std::move(value);
}

// -------------------- POP --------------------
template <typename T, size_t CAP>
void MyStack<T, CAP>::pop() {
    if (topIndex == 0)
        throw underflow_error("Stack is empty!");
    --topIndex;
}

// -------------------- TOP --------------------
template <typename T, size_t CAP>
T MyStack<T, CAP>::top() const {
    if (topIndex == 0)
        throw underflow_error("Stack is empty!");
    return arr[topIndex - 1];
}

template <typename T, size_t CAP>
bool MyStack<T, CAP>::empty() const {
    return topIndex == 0;
}

template <typename T, size_t CAP>
size_t MyStack<T, CAP>::size() const {
    return topIndex;
}

template <typename T, size_t CAP>
void MyStack<T, CAP>::Display() const {
    for (size_t i = 0; i < topIndex; ++i)
        cout << arr[i] << " ";
}

// ================== MAIN ==================
int main() {
    try {
        MyStack<int, 7> stackInt;   // FIXED capacity = 7

        cout << "===== R-VALUE PUSH TESTS =====\n";
        stackInt.push(10);
        stackInt.push(20);
        stackInt.push(30);
        stackInt.push(40);

        cout << "\nStack Elements: ";
        stackInt.Display();
        cout << endl;

        cout << "\n===== L-VALUE PUSH TESTS =====\n";
        int a = 50;
        int b = 60;
        stackInt.push(a);   // l-value
        stackInt.push(b);   // l-value

        cout << "\nStack Elements: ";
        stackInt.Display();
        cout << endl;

        cout << "\n===== FORCED R-VALUE USING std::move =====\n";
        stackInt.push(std::move(a));   // r-value

        cout << "\nStack Elements: ";
        stackInt.Display();
        cout << endl;

        cout << "\nTop element: " << stackInt.top() << endl;

        stackInt.pop();
        cout << "Top after pop: " << stackInt.top() << endl;
        cout << "Size: " << stackInt.size() << endl;
        cout << "Capacity: " << stackInt.capacity() << endl;

        cout << "\nTrying to push beyond capacity...\n";
        stackInt.push(999);  // Overflow → will throw

    }
    catch (const overflow_error& e) {
        cout << "Overflow Error: " << e.what() << endl;
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
(r-value push) (r-value push) (r-value push) (r-value push) 
Stack Elements: 10 20 30 40 

===== L-VALUE PUSH TESTS =====
(l-value push) (l-value push) 
Stack Elements: 10 20 30 40 50 60 

===== FORCED R-VALUE USING std::move =====
(r-value push) 
Stack Elements: 10 20 30 40 50 60 50 

Top element: 50
Top after pop: 60
Size: 6
Capacity: 7

Trying to push beyond capacity...
(r-value push) 
*/




//Stack implementation using Template with Rule 5
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

    void resize();

public:
    // Default Constructor
    MyStack();

    // Copy Constructor
    MyStack(const MyStack& other);

    // Move Constructor
    MyStack(MyStack&& other) noexcept;

    // Copy Assignment
    MyStack& operator=(const MyStack& other);

    // Move Assignment
    MyStack& operator=(MyStack&& other) noexcept;

    // Destructor
    ~MyStack();

    // Push overloads
    void push(const T& value);   // l-value
    void push(T&& value);        // r-value

    void pop();
    const T& top() const;

    bool empty() const { return topIndex == 0; }
    size_t size() const { return topIndex; }
    size_t getCap() const { return cap; }

    void clear();
    void Display() const;
};

template <typename T>
MyStack<T>::MyStack() : arr(nullptr), topIndex(0), cap(0) {}

// Copy Constructor
template <typename T>
MyStack<T>::MyStack(const MyStack& other)
    : arr(new T[other.cap]), topIndex(other.topIndex), cap(other.cap)
{
    for (size_t i = 0; i < topIndex; i++)
        arr[i] = other.arr[i];
}

// Move Constructor
template <typename T>
MyStack<T>::MyStack(MyStack&& other) noexcept
    : arr(other.arr), topIndex(other.topIndex), cap(other.cap)
{
    other.arr = nullptr;
    other.topIndex = 0;
    other.cap = 0;
}

// Copy Assignment
template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this == &other)
        return *this;

    delete[] arr;

    cap = other.cap;
    topIndex = other.topIndex;

    arr = new T[cap];
    for (size_t i = 0; i < topIndex; i++)
        arr[i] = other.arr[i];

    return *this;
}

// Move Assignment
template <typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& other) noexcept {
    if (this == &other)
        return *this;

    delete[] arr;

    arr = other.arr;
    topIndex = other.topIndex;
    cap = other.cap;

    other.arr = nullptr;
    other.topIndex = 0;
    other.cap = 0;

    return *this;
}

template <typename T>
MyStack<T>::~MyStack() {
    delete[] arr;
}

template <typename T>
void MyStack<T>::resize() {
    size_t newCap = (cap == 0) ? 1 : cap * 2;
    T* newArr = new T[newCap];

    for (size_t i = 0; i < topIndex; i++)
        newArr[i] = std::move(arr[i]);

    delete[] arr;
    arr = newArr;
    cap = newCap;
}

// Push (copy) – l-value
template <typename T>
void MyStack<T>::push(const T& value) {
    if (topIndex == cap)
        resize();

    cout << "(l-value push) ";
    arr[topIndex++] = value;
}

// Push (move) – r-value
template <typename T>
void MyStack<T>::push(T&& value) {
    if (topIndex == cap)
        resize();

    cout << "(r-value push) ";
    arr[topIndex++] = std::move(value);
}

template <typename T>
void MyStack<T>::pop() {
    if (empty())
        throw underflow_error("Stack underflow: cannot pop from empty stack");
    --topIndex;
}

template <typename T>
const T& MyStack<T>::top() const {
    if (empty())
        throw underflow_error("Stack underflow: cannot access top of empty stack");
    return arr[topIndex - 1];
}

template <typename T>
void MyStack<T>::clear() {
    topIndex = 0;
}

template <typename T>
void MyStack<T>::Display() const {
    if (empty()) {
        cout << "[empty stack]\n";
        return;
    }
    cout << "[ ";
    for (size_t i = 0; i < topIndex; i++)
        cout << arr[i] << " ";
    cout << "]";
}

int main() {
    try {
        cout << "===== R-VALUE PUSH TEST =====\n";
        MyStack<int> stk;
        stk.push(10);        // 10 → r-value literal
        stk.push(20);        // 20 → r-value literal
        stk.push(30);
        stk.push(40);
        cout << "\nStack: ";
        stk.Display();
        cout << "\n";


        cout << "\n===== L-VALUE PUSH TEST =====\n";
        int a = 50;
        int b = 60;
        stk.push(a);   // l-value
        stk.push(b);   // l-value
        cout << "Stack: ";
        stk.Display();
        cout << "\n";


        cout << "\n===== FORCING R-VALUE USING std::move =====\n";
        stk.push(std::move(a)); // forced r-value
        cout << "Stack: ";
        stk.Display();
        cout << "\n";


        cout << "\n===== COPY CONSTRUCTOR TEST =====\n";
        MyStack<int> stkCopy(stk);
        cout << "Copied: ";
        stkCopy.Display();
        cout << "\n";


        cout << "\n===== COPY ASSIGNMENT TEST =====\n";
        MyStack<int> stkCopyAssign;
        stkCopyAssign = stk;
        cout << "Copy Assigned: ";
        stkCopyAssign.Display();
        cout << "\n";


        cout << "\n===== MOVE CONSTRUCTOR TEST =====\n";
        MyStack<int> stkMoved(std::move(stk));
        cout << "Moved-From (stk): ";
        stk.Display();
        cout << "\nMoved-To: ";
        stkMoved.Display();
        cout << "\n";


        cout << "\n===== MOVE ASSIGNMENT TEST =====\n";
        MyStack<int> stkMoveAssign;
        stkMoveAssign = std::move(stkMoved);
        cout << "Moved-From: ";
        stkMoved.Display();
        cout << "\nMoved-To: ";
        stkMoveAssign.Display();
        cout << "\n";


        cout << "\n===== UNDERFLOW TEST =====\n";
        stkMoveAssign.clear();
        cout << "Trying pop on empty stack...\n";
        stkMoveAssign.pop();

    }
    catch (const underflow_error& e) {
        cout << "Underflow Error Caught: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "General Exception: " << e.what() << endl;
    }

    return 0;
}
/*
===== R-VALUE PUSH TEST =====
Stack: [ 10 20 30 40 ]

===== L-VALUE PUSH TEST =====
[ 10 20 30 40 40 50 ]
===== FORCING R-VALUE USING std::move =====
[ 10 20 30 40 40 50 40 ]
====== TEST COPY CONSTRUCTOR ======
Copied Stack: [ 10 20 30 40 40 50 40 ]

====== TEST COPY ASSIGNMENT ======
Copy Assigned Stack: [ 10 20 30 40 40 50 40 ]

====== TEST MOVE CONSTRUCTOR ======
Moved-From Stack (should be empty): [empty stack]

Moved-To Stack: [ 10 20 30 40 40 50 40 ]

====== TEST MOVE ASSIGNMENT ======
Moved-From Stack (should be empty): [empty stack]

Moved-To Stack: [ 10 20 30 40 40 50 40 ]

====== STANDARD OPERATIONS ======
Top of stkMoveAssign: 40
After pop: [ 10 20 30 40 40 50 ]
Clearing stack...
Trying to pop from empty stack...
Underflow Error Caught: Stack underflow: cannot pop from empty stack
*/




















//self
#include<iostream>
#include<stdexcept>
using namespace std;
class MyStack{
  int* arr;
  int topIndex;
  int cap;
 public:
  MyStack(): arr(nullptr), topIndex(-1), cap(0){}
  ~MyStack(){ delete[] arr;}
  void push(const int& val);
  void pop();
  int top() const;
  int size() const;
  int capacity() const;
  bool empty() const;
  void display() const;
};

void MyStack::push(const int& val){
      if(topIndex+1 ==cap){
          cap = (cap == 0)? 1: cap*2;
          int* newArr = new int[cap];
          for(int i=0; i<=topIndex; i++){
              newArr[i] = arr[i];
          }
          delete[] arr;
          arr = newArr;
      }
      arr[++topIndex] = val;
  }
  void MyStack::pop(){
      if(topIndex == -1) throw underflow_error("Stack is empty!");
      
      --topIndex;
  }
  int MyStack::top() const{
      if(topIndex == -1) throw underflow_error("Stack is empty!");
      
      return arr[topIndex];
  }
  
  int MyStack::size() const{
      return topIndex + 1;
  }
  int MyStack::capacity() const{
      return cap;
  }
  bool MyStack::empty() const{
      return topIndex == -1;
  }
  void MyStack::display() const{
      for(int i=0; i<=topIndex; i++){
          cout<<arr[i]<<" ";
      }
      cout<<endl;
  }
  int main(){
      MyStack st;
      st.push(10);
      st.push(20);
      st.push(30);
      st.push(40);
      
      cout<<"Stack Elements: ";
      st.display();
      cout<<"Top Eelment: "<<st.top()<<endl;
      cout<<"Size: "<<st.size()<<endl;
      cout<<"Capacity: "<<st.capacity()<<endl;
      
      st.pop();
      cout<<"Stack Elements after pop: ";
      st.display();
      
      cout<<"Top Eelment: "<<st.top()<<endl;
      cout<<"Size: "<<st.size()<<endl;
      cout<<"Capacity: "<<st.capacity()<<endl;
      if(st.empty()){
          cout<<"stack is empty!";
      }
      
     return 0;
  }
  /*
  Stack Elements: 10 20 30 40 
Top Eelment: 40
Size: 4
Capacity: 4
Stack Elements after pop: 10 20 30 
Top Eelment: 30
Size: 3
Capacity: 4
  */








  #include<iostream>
#include<stdexcept>
using namespace std;
template<class T>
class MyStack{
  T* arr;
  size_t topIndex;
  size_t cap;
 public:
  MyStack(): arr(nullptr), topIndex(0), cap(0){}
  ~MyStack(){ delete[] arr;}
  void push(const T& val);
  void pop();
  T top() const;
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  void display() const;
};

template<class T>
void MyStack<T>::push(const T& val){
      if(topIndex ==cap){
          cap = (cap == 0)? 1: cap*2;
          T* newArr = new T[cap];
          for(size_t i=0; i<topIndex; i++){
              newArr[i] = arr[i];
          }
          delete[] arr;
          arr = newArr;
      }
      arr[topIndex++] = val;
}
template<class T>
void MyStack<T>::pop(){
      if(topIndex == 0) throw underflow_error("Stack is empty!");
      
      --topIndex;
 }
 template<class T>
 T MyStack<T>::top() const{
      if(topIndex == 0) throw underflow_error("Stack is empty!");
      
      return arr[topIndex-1];
  }
  template<class T>
  size_t MyStack<T>::size() const{
      return topIndex;
  }
  template<class T>
  size_t MyStack<T>::capacity() const{
      return cap;
  }
  template<class T>
  bool MyStack<T>::empty() const{
      return topIndex == 0;
  }
  template<class T>
  void MyStack<T>::display() const{
      for(size_t i=0; i<topIndex; i++){
          cout<<arr[i]<<" ";
      }
      cout<<endl;
  }
  int main(){
      MyStack<int> st;
      st.push(10);
      st.push(20);
      st.push(30);
      st.push(40);
      
      cout<<"Stack Elements: ";
      st.display();
      cout<<"Top Eelment: "<<st.top()<<endl;
      cout<<"Size: "<<st.size()<<endl;
      cout<<"Capacity: "<<st.capacity()<<endl;
      
      st.pop();
      cout<<"Stack Elements after pop: ";
      st.display();
      
      cout<<"Top Eelment: "<<st.top()<<endl;
      cout<<"Size: "<<st.size()<<endl;
      cout<<"Capacity: "<<st.capacity()<<endl;
      if(st.empty()){
          cout<<"stack is empty!";
      }
      
     return 0;
  }
  /*
  Stack Elements: 10 20 30 40 
Top Eelment: 40
Size: 4
Capacity: 4
Stack Elements after pop: 10 20 30 
Top Eelment: 30
Size: 3
Capacity: 4
  */