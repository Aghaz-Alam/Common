//Fixed Sized Array
#include<iostream>
using namespace std;

namespace myArray{
template<typename T, size_t N>
class array{
     T arr[N];
    public:
      array()=default;
      void fill(const T& val){
          for(size_t i=0; i<N; i++)
              arr[i] = val;
      }
      
      T& operator[](size_t index) {
          if(index>=N) throw out_of_range("Index is out of range!");
          
          return arr[index];
      }
      
      T& at(size_t index) {
          if(index>=N) throw out_of_range("Index is out of range!");
          
          return arr[index];
      }
      
      size_t size() const{
          return N;
      }
      
      T* data(){
          return arr;
      }
      
      T* begin(){
          return arr;
      }
      
      T* end(){
          return arr+N;
      }
      
      void display() const{
          for(size_t i=0; i<N; i++){
              cout<<arr[i]<<" ";
          }
          cout<<endl;
      }
};
}
int main(){
    myArray::array<int, 5> arr;
    arr.fill(10);
    cout<<"Array Elements: ";
    arr.display();
    
    cout<<"Size: "<< arr.size()<<endl;
    
    arr[2]=20;
    cout<<"Array elements after modification: ";
    for(int x: arr){
        cout<<x<<" ";
    }
    cout<<endl;
    
    cout<<"Using operator[]: "<<arr[2]<<endl;
    cout<<"Using at(): "<<arr.at(2)<<endl;
    
    cout<<"Usig data(): ";
    int *p = arr.data();
    for(size_t i= 0; i<arr.size(); i++){
        cout<<*(p+i)<<" ";
    }
    cout<<endl;
    
    cout<<"Using begin/end: ";
    for(auto it=arr.begin(); it!=arr.end(); it++){
        cout<<*it<<" ";
    }
  
   try{
    cout<<"\nTest for out of range using operator[]: ";
    arr[10]=100;
   }
   catch(const exception& e){
      cout<<"Error: "<<e.what()<<endl;
   }
    
   try{
    cout<<"Test for out of range using at(): "<<arr.at(10)<<endl;
   }
    catch(const exception& e){
      cout<<"Error: "<<e.what()<<endl;
   }
 
  return 0;
}
/*
Size: 5
Array elements after modification: 10 10 20 10 10 
Using operator[]: 20
Using at(): 20
Usig data(): 10 10 20 10 10 
Using begin/end: 10 10 20 10 10 
Test for out of range using operator[]: Error: Index is out of range!
Test for out of range using at(): Error: Index is out of range!
*/


