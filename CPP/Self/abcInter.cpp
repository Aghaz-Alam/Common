#include<iostream>
#include<memory>
#include<string>
using namespace std;
class Engine{
    string type;
    public:
      Base(string t): type(t);
      ~Base()=default;
};
class Car{
    unique_ptr<Engine> engine;
    
};
int main(){
    unique_ptr<Base> p=make_unique<Base>();
    unique_ptr<Base> p1=std::move(p);
    
    
    
    shared_ptr<Base> sptr = make_shared<Base>();
    shared_ptr<Base>sptr1=sptr;
    cout<<use.count()<<endl;
    
    
    weak_ptr<Base> wpt= sptr;
    
    
}



//Raw pointers
int* a = new int[5];
delete[] a;

int b= new int(5);
delete b;

--------------------------------------------------
class Sample;
class Test{
    public:
      shared_ptr<Sample> s;
    
};
class Sample {
    public:
      weak_ptr<Test> t;
};
int main(){
  shared_ptr<Test> a = make_shared<Test >();
  shared_ptr<Sample> b = make_shared<Sample>();
  
  a->s=b;
  b->t=a;
    
}


const_cast;  ---
static_cast;  
dynamic_cast--   
reinterpret_cast;

Base *b = new Deried();  //upcasting 

Deried* d = dynamic_cast<Deried*>(b);  //downcasting    
if(d){
    cout<<"downcasting is succesfull"
}




mutable int a = 10;

void set() const{
    a=20;
    cout<<a<<endl;
}

int a=10;
[&a]()mutable{
    a=20;
    
}


shallow 
deep

int a=10;
int *p;

obj1    obj2
a        a

   p
   
   
   
   
 
 template<typename T>
class Unique{
   int *p;
  public:
   Unique(): p(nullptr);
   ~Unique(){
       delete p;
   }
   Unique(const Unique&)=delete;
   Unique& operator=(const Unique&)=delete;
   
   Unique(Unique&& obj){
       p=obj.p;
   }
   Unique& operator(Unique&& obj){
       
       
   }
   T& operator*(){
       return p;
   }
   T* operator->(){
       return p;
   }
   T release(){
       
   }
   
};
int main(){
    
}
 
 
 
 
 
multhreading

thread
mutex  mtx;
manual
mtx.lock();
mtx.unlock();


lock_guard<mutex>

g++ app.cpp -o app


gdb ./app

valgrind 

gtest 
ASSERT
E


stl

list 
class Node{
    
}




std::vector<T> ;



CAN 

4.9   







 
 
 
 
 
 
 
 
 
 
 
 



























