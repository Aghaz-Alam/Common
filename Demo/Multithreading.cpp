//execution of one thread to the other
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include <atomic>
using namespace std;
mutex mtx;
condition_variable cv;
//int result = 0;  // global value
atomic<int> result{0};  // atomic variable
void Add(int x, int y) {
    lock_guard<mutex> lock(mtx);
    result = x + y; 
    cout << result << endl;
    cv.notify_one();  
}
void Compute() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []{ return result != 0; });  
    cout << result << endl;
}
int main() {
    thread t1(Add, 5, 6); 
    thread t2(Compute); 
    
    t1.join();
    t2.join();

   return 0;
}
/*
11
11
*/




//execution of one thread to the other
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
using namespace std;

mutex mtx;
condition_variable cv;
atomic<int> result{0};

void Add(int& x, int& y) {
    lock_guard<mutex> lock(mtx);
    result = x + y; 
    cout << "Add: " << result << endl;
    cv.notify_one();  
}

void Compute() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return result != 0; });  
    cout << "Compute: " << result << endl;
}

int main() {
    int a = 5, b = 6;
    thread t1(Add, std::ref(a), std::ref(b));  //functor, function pointer, lambda, class member fun, static fun.
    thread t2(Compute); 
    
    t1.join();
    t2.join();

    return 0;
}










//void return type
#include <iostream>
#include <thread>
using namespace std;

void Add(int x, int y) {
    cout<<"Sum= " << x + y;
}

int main() {
    thread t1(Add, 5, 6);  
    t1.join();

    return 0;
}
//Sum: 11







//void return type 
#include <iostream>
#include <thread>
using namespace std;

void Add(int x, int y, int &result) {
    result = x + y;
}

int main() {
    int result = 0;
    thread t1(Add, 5, 6, std::ref(result));  
    t1.join();

    cout << "Sum: " << result << endl;
    return 0;
}
//Sum: 11






////int return type with future and promise
#include <iostream>
#include <thread>
#include <future>
using namespace std;

int Add(int x, int y) {
    return x + y;
}

int main() {
    // Create a promise and get its future
    promise<int> prom;
    future<int> fut = prom.get_future();

    // Start a thread that sets the promise value
    thread t1([&prom]() {
        int result = Add(5, 6);
        prom.set_value(result);
    });

    // Wait and get the result
    cout << "Result: " << fut.get() << endl;

    t1.join();
}
/*
Result: 11
*/



//int return type with future 
#include <iostream>
#include <future> // For std::async and std::future
#include <thread>

int Add(int x, int y) {
    return x + y;
}

int main() {
   std::future<int> future_result = std::async(std::launch::async, Add, 5, 6);
   int result = future_result.get(); 
   std::cout << "Result: " << result << std::endl; 
  return 0;
}
//Result: 11

 

//int return type with future 
#include <iostream>
#include <future>
using namespace std;

int Add(int x, int y) {
    return x + y;
}

int main() {
    // Launch Add asynchronously
    future<int> fut = async(Add, 5, 6);

    // Get result (waits for completion)
    cout << "Result: " << fut.get() << endl;
}
//Result: 11

















/* --------------------------------------------------------------------------------- */
1. Function Pointer: The thread can take a function pointer and its arguments:

#include <iostream>
#include <thread>
using namespace std;
void Add(int x, int y) {
    cout << "Function pointer sum = " << x + y << endl;
}
int main() {
    thread t1(Add, 5, 6);  // passing function pointer
    t1.join();

    return 0;
}
/* 
✅ Output:
Function pointer sum = 11

Explanation: Add is a global function. Thread automatically passes 5 and 6 as arguments.
*/



2. Functor (Function Object):  A functor is any object that overloads operator(). Threads can execute it like a function.

#include <iostream>
#include <thread>
using namespace std;
class Adder {
  public:
    void operator()(int x, int y) {
        cout << "Functor sum = " << x + y << endl;
    }
};

int main() {
    Adder adder;
    thread t2(adder, 5, 6);  // passing functor
    t2.join();

    return 0;
}
/* 
✅ Output:

Functor sum = 11

Explanation: The Adder object acts like a callable function.
*/



3. Lambda Function: We can use lambda expressions directly in threads:

#include <iostream>
#include <thread>
using namespace std;
int main() {
    thread t3([](int x, int y){
        cout << "Lambda sum = " << x + y << endl;
    }, 5, 6);  // passing lambda function
    t3.join();

   return 0;
}
/* 
✅ Output:

Lambda sum = 11

Explanation: Lambdas are anonymous functions. They’re convenient for short tasks.
*/


4. Class Member Function: For non-static member functions, we need to pass an object pointer/reference as the first argument:

#include <iostream>
#include <thread>
using namespace std;
class Calculator {
  public:
    void Add(int x, int y) {
        cout << "Member function sum = " << x + y << endl;
    }
};

int main() {
    Calculator calc;
    thread t4(&Calculator::Add, &calc, 5, 6);  // object pointer passed
    t4.join();


    Calculator* p = new Calculator();
    thread t5(&Calculator::Add, p, 5, 6);
    t5.join()


    return 0;
}
/* 
✅ Output:

Member function sum = 11


Explanation:
&Calculator::Add is the member function pointer.
&calc tells the thread which object to call it on.
Then the remaining arguments 5 and 6 are passed to the function.



We pass:
&Calculator::Add
because member functions are NOT normal functions.
They need an object to run on, and they use a hidden this pointer.
So we must pass a pointer to the member function, not the function itself.





we pass &calc (address of object)?
A non-static member function has the hidden parameter:
this → pointer to the object


So this function:
void Add(int x, int y);


Is actually compiled like:
void Add(Calculator* this, int x, int y);


So when you start a thread with:
thread t4(&Calculator::Add, &calc, 5, 6);


C++ needs:
1) a pointer to the member function
2) a pointer to the object (this)
3) the remaining arguments (5, 6)
4) If you don’t provide the object’s address, the compiler doesn’t know what object to call the function on.







Understanding the Difference: Normal Function vs Member Function
✔ Normal function pointer:
  void Add(int, int);

  Its pointer type is:
  void (*)(int, int);

  We can pass the function directly:
  thread t(Add, 5, 6);


❌ Member functions are different

  A member function has an implicit parameter:
  void Add(int x, int y);

  is actually:
  void Add(Calculator* this, int x, int y);

  So the pointer type is:
  void (Calculator::*)(int, int)

  This type is not the same as a normal function pointer.



The thread MUST know:
--> Which member function to call → &Calculator::Add
--> Which object to call it on → &calc
--> The remaining arguments → 5, 6

So this is exactly why we write:
thread t(&Calculator::Add, &calc, 5, 6);





What does &Calculator::Add represent?
It is a pointer-to-member-function.
It does not contain:
--> any object
--> any this pointer
--> any values
It only represents “this is the function to call”.
We can think of it as a pointer to the method definition, not a function.




How the thread internally expands our call
When we do:
thread t(&Calculator::Add, &calc, 5, 6);

Thread executes something like:
(calc.*(&Calculator::Add))(5, 6);

This is the syntax for calling a pointer-to-member function.






✔ Example breakdown
&Calculator::Add     → points to the member function
&calc                → provides the "this" pointer
5, 6                 → arguments for the function


This is exactly how C++ differentiates:
*/


//Referenc or pointer
#include <iostream>
#include <thread>
using namespace std;
class Calculator {
  public:
    void Add(int x, int y) {
        cout << "Member function sum = " << x + y << endl;
    }
};

int main() {
    Calculator calc;
    //1. reference: &calc (address of object)
    thread t3(&Calculator::Add, &calc, 5, 6);  // object pointer passed
    t3.join();
    //OR
    //2. reference: //std::ref()
    thread t4(&Calculator::Add, ref(calc), 5, 6);  //std::ref()
    t4.join();

    //pointer
    Calculator* p = new Calculator();
    thread t5(&Calculator::Add, p, 5, 6);
    t5.join();


    return 0;
}
/* 
✅ Output:
Member function sum = 11
Member function sum = 11
Member function sum = 11
*/






5. Static Member Function: Static member functions behave like normal global functions, so we do not need an object:

#include <iostream>
#include <thread>
using namespace std;
class Calculator {
 public:
    static void Add(int x, int y) {
        cout << "Static member function sum = " << x + y << endl;
    }
};
int main() {
    thread t5(&Calculator::Add, 5, 6);  // static function
    t5.join();

  return 0;
}
/* 
✅ Output:

Static member function sum = 11

Explanation: Static functions belong to the class, not an object, so they can be called directly.
*/
/* --------------------------------------------------------------------------------  */