//Stack Implementation using dynamic array without template
#include <iostream>
#include <stdexcept>
using namespace std;
class Stack {
  private:
    int* arr;
    int topIndex;
    int cap;

  public:
    // Constructor
    Stack() : arr(nullptr), topIndex(-1), cap(0) {}

    // Destructor
    ~Stack() { delete[] arr; }
   
    void push(int value) {
        if(topIndex + 1 == cap){
           cap = (cap == 0) ? 1 : cap * 2; // Double the capacity or initialize to 1 if it's 0
          int* newArr = new int[cap];
          for (int i = 0; i <= topIndex; ++i) { // copy existing elements
                 newArr[i] = arr[i];
          }
          delete[] arr;
          arr = newArr;
        }
        arr[++topIndex] = value;
    }

    void pop() {
        if (topIndex == -1) throw underflow_error("Stack is empty!");
        --topIndex;
    }

    int top() const {
        if (topIndex == -1) throw underflow_error("Stack is empty!");
        return arr[topIndex];
    }

    bool empty() const { 
        return topIndex == -1; 
    }
    int size() const { 
        return topIndex + 1; 
    }
    int getCap() const { 
        return cap; 
    }
    void Display(){
        for (int i = 0; i <= topIndex; ++i) { 
            cout<<arr[i]<<" ";
        }
    }
};

int main() {
    Stack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);

    cout<<"Stack Elements: ";
    stack.Display();
    cout<<endl;
    
    cout << "Top element: " << stack.top() << endl; 
    
    stack.pop();
    cout << "Top element after pop: " << stack.top() << endl;
    cout << "Stack size: " << stack.size() << endl;
    cout << "Stack capacity: " << stack.getCap() << endl;

    while (!stack.empty()) 
        stack.pop();

    if (stack.empty()) 
        cout << "Stack is empty" << endl;

    return 0;
}
/*
Stack Elements: 10 20 30 40 
Top element: 40
Top element after pop: 30
Stack size: 3
Stack capacity: 4
Stack is empty
*/






//Stack Implementation using dynamic array with template

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
  private:
    T* arr;
    size_t topIndex;
    size_t cap;

  public:
    // Constructor
    Stack() : arr(nullptr), topIndex(0), cap(0) {}

    // Destructor
    ~Stack() { 
        delete[] arr; 
    }
   
    void push(T value) {
        if (topIndex == cap) {  // No space left
            cap = (cap == 0) ? 1 : cap * 2; // Double the capacity or initialize to 1 if it's 0
            T* newArr = new T[cap];
            for (size_t i = 0; i < topIndex; ++i) { // copy existing elements
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[topIndex++] = value;  // Insert the value and increment topIndex
    }

    void pop() {
        if (topIndex == 0) 
            throw underflow_error("Stack is empty!");
        
        --topIndex;  // Decrease topIndex to remove the top element
    }

    T top() const {
        if (topIndex == 0) 
             throw underflow_error("Stack is empty!");
             
        return arr[topIndex - 1];  // Return the top element without removing it
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
        for (size_t i = 0; i < topIndex; ++i) {
            cout << arr[i] << " ";
        }
    }
};
int main() {
    // Create a stack of integers
    Stack<int> stackInt;

    stackInt.push(10);
    stackInt.push(20);
    stackInt.push(30);
    stackInt.push(40);

    cout << "Integer Stack Elements: ";
    stackInt.Display();
    cout << endl;
    
    cout << "Top element (int): " << stackInt.top() << endl; 
    
    stackInt.pop();
    cout << "Top element after pop (int): " << stackInt.top() << endl;
    cout << "Stack size (int): " << stackInt.size() << endl;
    cout << "Stack capacity (int): " << stackInt.getCap() << endl;

    while (!stackInt.empty()) 
        stackInt.pop();

    if (stackInt.empty()) 
        cout << "Integer Stack is empty" << endl;

    // Create a stack of strings
    Stack<string> stackStr;

    stackStr.push("apple");
    stackStr.push("banana");
    stackStr.push("cherry");

    cout << "String Stack Elements: ";
    stackStr.Display();
    cout << endl;

    cout << "Top element (string): " << stackStr.top() << endl;

    stackStr.pop();
    cout << "Top element after pop (string): " << stackStr.top() << endl;
    cout << "Stack size (string): " << stackStr.size() << endl;
    cout << "Stack capacity (string): " << stackStr.getCap() << endl;

    while (!stackStr.empty()) 
        stackStr.pop();

    if (stackStr.empty()) 
        cout << "String Stack is empty" << endl;

    return 0;
}
/*
Integer Stack Elements: 10 20 30 40 
Top element (int): 40
Top element after pop (int): 30
Stack size (int): 3
Stack capacity (int): 4
Integer Stack is empty
String Stack Elements: apple banana cherry 
Top element (string): cherry
Top element after pop (string): banana
Stack size (string): 2
Stack capacity (string): 4
String Stack is empty
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