
//Fixed Sized Circular Queue
#include<iostream>
#include<stdexcept>
using namespace std;
template<typename T, size_t N>
class queue{
    T arr[N];
    size_t frontInd;
    size_t rearInd;
    size_t count;
  public:
    queue():frontInd(0), rearInd(0), count(0){};

    void push(const T& val){
        if(count == N) throw overflow_error("queue is full!");
        
        arr[rearInd] = val;
        rearInd = (rearInd+1)% N;
        count++;
    }

    void pop(){
        if(count == 0) throw underflow_error("queue is empty!");
        
         frontInd = (frontInd+1)%N;
        count--;
    }

    T& front(){
        return arr[frontInd];
    }

    T& back(){
        return arr[(rearInd-1+N)%N];
    }

    void Display(){
        cout<<"Elements: ";
        for(size_t i=0; i<count; i++){
            cout<<arr[(frontInd+i) % N]<<" ";
        }
        cout<<endl;
    }
};
int main(){
    try{
        queue<int, 5> q;

        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);

        q.Display();

        cout<<"Front: "<<q.front()<<endl;
        cout<<"Back: "<<q.back()<<endl;

        cout<<"pop: ";
        q.pop();
        q.Display();

        cout<<"Front: "<<q.front()<<endl;
        cout<<"Back: "<<q.back()<<endl;

    }
    catch(const exception& e){
        cout<<"Error: "<<e.what()<<endl;
    }
  return 0;
}
/* 
Elements: 10 20 30 40 50 
Front: 10
Back: 50
pop: Elements: 20 30 40 50 
Front: 20
Back: 50
*/




