#include<iostream>
#include<memory>
using namespace std;
class Base{
     int x;
    public:
      Base(int a):x(a){}
      void fun(){
          cout<<"Hello! "<<x<<endl;
      }
      void setX(int val){
           x=val;
      }
      int getX() const{
         return x;
      }
};
int main(){
    shared_ptr<Base> ptr = make_shared<Base>(10);
    ptr->fun();
    
    shared_ptr<Base> ptr1 = ptr;
    ptr1->setX(20);
    cout<<ptr1->getX()<<endl;
    ptr1->fun();
    
    cout<<"reference count: "<<ptr.use_count()<<endl;
    return 0;
}
/*
Hello! 10
20
Hello! 20
reference count: 2
*/
