std::queue
//Custom Queue Implementation Using a Dynamic Array without template 


//Queue without template  by making resize() function private
#include <iostream>
#include<stdexcept>
using namespace std;

class MyQueue{
  int* arr;
  int frontIndex;
  int rearIndex;
  int count;
  int cap;
 public:
  MyQueue():arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(){}
  
  ~MyQueue(){ delete[] arr; }
  
  void push(const int& val);
  void pop();
  int front() const;
  int back() const;
  bool empty() const ;
  int size() const;
  int capacity() const;
  void display() const;
 
private:
  void resize(){
      cap = (cap == 0) ? 1: cap*2;
      int* newArr = new int[cap];
      for(int i=0; i<count; i++){
          newArr[i] = arr[(frontIndex+i)%cap];
      }
      delete[] arr;
      arr = newArr;
      frontIndex =0;
      rearIndex = count;
  }
};  
  //insert at back
  void MyQueue::push(const int& val){
     if(count == cap) {
         resize();
     }
     
     arr[rearIndex] = val;
     rearIndex = (rearIndex +1) % cap;
     count ++;
     
  }
  
  //remove from front
  void MyQueue::pop(){
      if(count == 0) throw underflow_error("CQ is empty.");
      
      frontIndex = (frontIndex + 1) % cap;
      count --;
  }
  
  //get front element
  int MyQueue::front() const{
      if(count == 0) throw underflow_error("CQ is empty.");
      return arr[frontIndex];
  }
  
  //get rear element
  int MyQueue::back() const{
       if(count == 0) throw underflow_error("CQ is empty.");
      return arr[(rearIndex -1 +cap) % cap];
  }
  
  //queue is empty or not 
  bool MyQueue::empty() const {
    return count == 0;
  }
  
  //get the size
  int MyQueue::size() const {
     return count;
  }
  //get the capacity
  int MyQueue::capacity() const {
     return cap;
  }
  
  //Display queue elements
  void MyQueue::display() const {
      cout<<"Queue Elements: ";
      for(int i=0; i<count; i++){
          cout<<arr[(frontIndex +i) % cap]<<" ";
      }
      cout<<endl;
  }
  
int main() {
    MyQueue q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
   
    
    
    q.display();
    
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    cout<<"After pop: "<<endl;
    q.display();
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    if(q.empty()){
        cout<<"Queue is empty!"<<endl;
    }
    
    
    return 0;
}
/*
Queue Elements: 10 20 30 40 50 
Front ELement: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Queue Elements: 20 30 40 50 
Front ELement: 20
Rear Element: 50
Size: 4
Capacity: 8
Queue is empty!
*/


//Queue without template  by making resize() function public
#include <iostream>
#include<stdexcept>
using namespace std;

class MyQueue{
  int* arr;
  int frontIndex;
  int rearIndex;
  int count;
  int cap;
 public:
  MyQueue():arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(){}
  
  ~MyQueue(){ delete[] arr; }
  
  void resize();
  void push(const int& val);
  void pop();
  int front() const;
  int back() const;
  bool empty() const ;
  int size() const;
  int capacity() const;
  void display() const;
  
};  
  
  void MyQueue::resize(){
      cap = (cap == 0) ? 1: cap*2;
      int* newArr = new int[cap];
      for(int i=0; i<count; i++){
          newArr[i] = arr[(frontIndex+i)%cap];
      }
      delete[] arr;
      arr = newArr;
      frontIndex =0;
      rearIndex = count;
  }
  
  //insert at back
  void MyQueue::push(const int& val){
     if(count == cap) {
         resize();
     }
     
     arr[rearIndex] = val;
     rearIndex = (rearIndex +1) % cap;
     count ++;
     
  }
  
  //remove from front
  void MyQueue::pop(){
      if(count == 0) throw underflow_error("CQ is empty.");
      
      frontIndex = (frontIndex + 1) % cap;
      count --;
  }
  
  //get front element
  int MyQueue::front() const{
      if(count == 0) throw underflow_error("CQ is empty.");
      return arr[frontIndex];
  }
  
  //get rear element
  int MyQueue::back() const{
       if(count == 0) throw underflow_error("CQ is empty.");
      return arr[(rearIndex -1 +cap) % cap];
  }
  
  //queue is empty or not 
  bool MyQueue::empty() const {
    return count == 0;
  }
  
  //get the size
  int MyQueue::size() const {
     return count;
  }
  //get the capacity
  int MyQueue::capacity() const {
     return cap;
  }
  
  //Display queue elements
  void MyQueue::display() const {
      cout<<"Queue Elements: ";
      for(int i=0; i<count; i++){
          cout<<arr[(frontIndex +i) % cap]<<" ";
      }
      cout<<endl;
  }
  
int main() {
    MyQueue q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
   
    
    
    q.display();
    
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    cout<<"After pop: "<<endl;
    q.display();
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    if(q.empty()){
        cout<<"Queue is empty!"<<endl;
    }
    
    
    return 0;
}
/*
Queue Elements: 10 20 30 40 50 
Front ELement: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Queue Elements: 20 30 40 50 
Front ELement: 20
Rear Element: 50
Size: 4
Capacity: 8
Queue is empty!
*/



















//Circular queue with template by making resize() function private
#include <iostream>
#include<stdexcept>
using namespace std;

template<class T>
class MyQueue{
  T* arr;
  size_t frontIndex;
  size_t rearIndex;
  size_t count;
  size_t cap;
 public:
  MyQueue():arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(){}
  
  ~MyQueue(){ delete[] arr; }
  
  void push(const T& val);
  void pop();
  T front() const;
  T back() const;
  bool empty() const ;
  size_t size() const;
  size_t capacity() const;
  void display() const;
 
 private:   
  void resize(){
      cap = (cap == 0) ? 1: cap*2;
      T* newArr = new T[cap];
      for(size_t i=0; i<count; i++){
          newArr[i] = arr[(frontIndex+i)%cap];
      }
      delete[] arr;
      arr = newArr;
      frontIndex =0;
      rearIndex = count;
  }
  
};  
  //insert at back
  template<class T>
  void MyQueue<T>::push(const T& val){
     if(count == cap) {
         resize();
     }
     
     arr[rearIndex] = val;
     rearIndex = (rearIndex +1) % cap;
     count ++;
     
  }
  
  //remove from front
  template<class T>
  void MyQueue<T>::pop(){
      if(count == 0) throw underflow_error("CQ is empty.");
      
      frontIndex = (frontIndex + 1) % cap;
      count --;
  }
  
  //get front element
  template<class T>
  T MyQueue<T>::front() const{
      if(count == 0) throw underflow_error("CQ is empty.");
      return arr[frontIndex];
  }
  
  //get rear element
  template<class T>
  T MyQueue<T>::back() const{
       if(count == 0) throw underflow_error("CQ is empty.");
      return arr[(rearIndex -1 +cap) % cap];
  }
  
  //queue is empty or not 
  template<class T>
  bool MyQueue<T>::empty() const {
    return count == 0;
  }
  
  //get the size 
  template<class T>
  size_t MyQueue<T>::size() const {
     return count;
  }
  //get the capacity
  template<class T>
  size_t MyQueue<T>::capacity() const {
     return cap;
  }
  
  //Display queue elements
  template<class T>
  void MyQueue<T>::display() const {
      cout<<"Queue Elements: ";
      for(size_t i=0; i<count; i++){
          cout<<arr[(frontIndex +i) % cap]<<" ";
      }
      cout<<endl;
  }
  
int main() {
    MyQueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
   
    
    
    q.display();
    
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    cout<<"After pop: "<<endl;
    q.display();
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    if(q.empty()){
        cout<<"Queue is empty!"<<endl;
    }
    
    
    return 0;
}
/*
Queue Elements: 10 20 30 40 50 
Front ELement: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Queue Elements: 20 30 40 50 
Front ELement: 20
Rear Element: 50
Size: 4
Capacity: 8
Queue is empty!
*/




//Queue  using template  with resize() function public
#include <iostream>
#include<stdexcept>
using namespace std;

template<class T>
class MyQueue{
  T* arr;
  size_t frontIndex;
  size_t rearIndex;
  size_t count;
  size_t cap;
 public:
  MyQueue():arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(){}
  
  ~MyQueue(){ delete[] arr; }
  
  void resize();
  void push(const T& val);
  void pop();
  T front() const;
  T back() const;
  bool empty() const ;
  size_t size() const;
  size_t capacity() const;
  void display() const;
  
};  
  template<class T>
  void MyQueue<T>::resize(){
      cap = (cap == 0) ? 1: cap*2;
      T* newArr = new T[cap];
      for(size_t i=0; i<count; i++){
          newArr[i] = arr[(frontIndex+i)%cap];
      }
      delete[] arr;
      arr = newArr;
      frontIndex =0;
      rearIndex = count;
  }
  
  //insert at back
  template<class T>
  void MyQueue<T>::push(const T& val){
     if(count == cap) {
         resize();
     }
     
     arr[rearIndex] = val;
     rearIndex = (rearIndex +1) % cap;
     count ++;
     
  }
  
  //remove from front
  template<class T>
  void MyQueue<T>::pop(){
      if(count == 0) throw underflow_error("CQ is empty.");
      
      frontIndex = (frontIndex + 1) % cap;
      count --;
  }
  
  //get front element
  template<class T>
  T MyQueue<T>::front() const{
      if(count == 0) throw underflow_error("CQ is empty.");
      return arr[frontIndex];
  }
  
  //get rear element
  template<class T>
  T MyQueue<T>::back() const{
       if(count == 0) throw underflow_error("CQ is empty.");
      return arr[(rearIndex -1 +cap) % cap];
  }
  
  //queue is empty or not 
  template<class T>
  bool MyQueue<T>::empty() const {
    return count == 0;
  }
  
  //get the size 
  template<class T>
  size_t MyQueue<T>::size() const {
     return count;
  }
  //get the capacity
  template<class T>
  size_t MyQueue<T>::capacity() const {
     return cap;
  }
  
  //Display queue elements
  template<class T>
  void MyQueue<T>::display() const {
      cout<<"Queue Elements: ";
      for(size_t i=0; i<count; i++){
          cout<<arr[(frontIndex +i) % cap]<<" ";
      }
      cout<<endl;
  }
  
int main() {
    MyQueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
   
    
    
    q.display();
    
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    cout<<"After pop: "<<endl;
    q.display();
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    if(q.empty()){
        cout<<"Queue is empty!"<<endl;
    }
    
    
    return 0;
}
/*
Queue Elements: 10 20 30 40 50 
Front ELement: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Queue Elements: 20 30 40 50 
Front ELement: 20
Rear Element: 50
Size: 4
Capacity: 8
Queue is empty!
*/




















My Own Queue Implementation
/*
#include <iostream>
#include <stdexcept> // For exceptions
using namespace std;
class MyQueue {
  private:
    int* arr;   // Pointer to dynamic array (queue storage)
    int frontIndex;  // Index of the front element in the queue
    int rearIndex;   // Index of the rear element in the queue
    int cap;    // Capacity of the queue (size of the underlying array)
    int count;       // Number of elements in the queue

    // Private function to resize the underlying array when capacity is full
    void resize() {
        cap = (cap == 0) ? 1 : cap * 2;  // Double the capacity
        int* newArr = nullptr;
        try {
            newArr = new int[cap];  // Allocate new array with increased capacity
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            throw;  // Rethrow the exception
        }
        // Copy elements to the new array
        for (int i = 0; i < count; ++i) {
            newArr[i] = arr[(frontIndex + i) % cap];
        }
        delete[] arr;  // Free the old array
        arr = newArr;  // Point to the new array
        frontIndex = 0;  // Reset front index
        rearIndex = count; // Set rear index to count
    }

public:
    // Constructor
    MyQueue(): arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap() {}

    // Destructor to free allocated memory
    ~MyQueue() {
        delete[] arr;
    }

    // Enqueue an element into the queue
    void push(int value) {
        if (count == cap) {
            resize();  // Call the resize function if capacity is full
        }
        arr[rearIndex] = value;
        rearIndex = (rearIndex + 1) % cap;  // Circular increment
        count++;
    }

    // Dequeue an element from the queue
    void pop() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        frontIndex = (frontIndex + 1) % cap;  // Circular increment
        count--;
    }

    // Return the front element without removing it
    int front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[frontIndex];
    }

    // Return the rear element without removing it
    int back() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty!");
        }
        return arr[(rearIndex - 1 + cap) % cap];  // Get the last inserted element
    }

    // Check if the queue is empty
    bool empty() const {
        return count == 0;
    }

    // Get the size of the queue
    int size() const {
        return count;
    }

    // Get the capacity of the queue
    int capacity() const {
        return cap;
    }

    // Display the queue elements
    void Display() {
        for (int i = 0; i < count; ++i) {
            cout << arr[(frontIndex + i) % cap] << " ";  // Circular indexing
        }
    }
};

int main() {
    MyQueue q;  

    // Enqueue elements into the queue
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    
    cout << "Queue Elements are: ";
    q.Display();
    cout << endl;

    // Display the front and rear elements
    cout << "Front element: " << q.front() << endl;
    cout << "Rear element: " << q.back() << endl;

    // Dequeue elements
    q.pop();
    cout << "Queue Elements after pop: ";
    q.Display();
    cout << endl;
    cout << "Front element after pop: " << q.front() << endl;
    cout << "Rear element after pop: " << q.back() << endl;

    q.pop();
    q.pop();
    q.pop();
    q.pop();
    
    // Check if the queue is empty
    if (q.empty()) {
        cout << "Queue is empty" << endl;
    }

    return 0;
}
/*
Queue Elements are: 10 20 30 40 50 
Front element: 10
Rear element: 50
Queue Elements after pop: 20 30 40 50 
Front element after pop: 20
Rear element after pop: 50
Queue is empty
*/





//*
#include <iostream>
#include<stdexcept>
using namespace std;

template<class T>
class MyQueue{
  int* arr;
  int frontIndex;
  int rearIndex;
  int count;
  int cap;
 public:
  MyQueue():arr(nullptr), frontIndex(0), rearIndex(0), count(0), cap(){}
  
  ~MyQueue(){ delete[] arr; }
  
  void resize();
  void push(const int& val);
  void pop();
  int front() const;
  int back() const;
  bool empty() const ;
  int size() const;
  int capacity() const;
  void display() const;
  
};  
  template<class T>
  void MyQueue<T>::resize(){
      cap = (cap == 0) ? 1: cap*2;
      T* newArr = new T[cap];
      for(int i=0; i<count; i++){
          newArr[i] = arr[(frontIndex+i)%cap];
      }
      delete[] arr;
      arr = newArr;
      frontIndex =0;
      rearIndex = count;
  }
  
  //insert at back
  template<class T>
  void MyQueue<T>::push(const int& val){
     if(count == cap) {
         resize();
     }
     
     arr[rearIndex] = val;
     rearIndex = (rearIndex +1) % cap;
     count ++;
     
  }
  
  //remove from front
  template<class T>
  void MyQueue<T>::pop(){
      if(count == 0) throw underflow_error("CQ is empty.");
      
      frontIndex = (frontIndex + 1) % cap;
      count --;
  }
  
  //get front element
  template<class T>
  int MyQueue<T>::front() const{
      if(count == 0) throw underflow_error("CQ is empty.");
      return arr[frontIndex];
  }
  
  //get rear element
  template<class T>
  int MyQueue<T>::back() const{
       if(count == 0) throw underflow_error("CQ is empty.");
      return arr[(rearIndex -1 +cap) % cap];
  }
  
  //queue is empty or not 
  template<class T>
  bool MyQueue<T>::empty() const {
    return count == 0;
  }
  
  //get the size 
  template<class T>
  int MyQueue<T>::size() const {
     return count;
  }
  //get the capacity
  template<class T>
  int MyQueue<T>::capacity() const {
     return cap;
  }
  
  //Display queue elements
  template<class T>
  void MyQueue<T>::display() const {
      cout<<"Circular Queue Elements: ";
      for(int i=0; i<count; i++){
          cout<<arr[(frontIndex +i) % cap]<<" ";
      }
      cout<<endl;
  }
  
int main() {
    MyQueue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
   
    
    
    q.display();
    
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    cout<<"After pop: "<<endl;
    q.display();
    cout<<"Front ELement: "<<q.front()<<endl;
    cout<<"Rear Element: "<<q.back()<<endl;
    cout<<"Size: "<<q.size()<<endl;
    cout<<"Capacity: "<<q.capacity()<<endl;
    
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    if(q.empty()){
        cout<<"Queue is empty!"<<endl;
    }
    
    
    return 0;
}
/*
Circular Queue Elements: 10 20 30 40 50 
Front ELement: 10
Rear Element: 50
Size: 5
Capacity: 8
After pop: 
Circular Queue Elements: 20 30 40 50 
Front ELement: 20
Rear Element: 50
Size: 4
Capacity: 8
Queue is empty!
*/




















