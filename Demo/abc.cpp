// #include <iostream>
// using namespace std;
// int main() {
//     int arr[3] = {10, 20, 30};

//     int* p = arr;
//     p++;  // OK: move to next element
//     cout << *p << endl;

//     //int& r = arr[0];
//     // r++;         // increments VALUE, not reference
//     // &r++;        // ERROR: reference arithmetic invalid  //doubt to get next element


//     for (int i = 0; i < 3; i++) {
//         int& r = arr[i];
//        cout << r << endl;
//     }
// }


// #include<iostream>
// using namespace std;
// int main(){
//     int x=10, y=20;
//     //4.4 Capture All by Value
//      //auto lam = [=]() { cout << x <<"\t"<< y<<endl; };   10  20
//      //lam();

//     //4.5 Capture All by Reference
//     //auto lam = [&]() { x++; y++; };
//     //lam();
//     //cout<<x<<"\t"<<y<<endl;   //11 21

//     //4.6 Mixed Captures
//     auto lam = [x, &y]() { cout << x <<"\n"<< y<<endl; };
//     lam();
//     cout<<x<<"\n"<<y<<endl;      //doubt to print x

// }



#include <iostream>
#include <mutex>
#include <thread>
std::mutex m;
void task() {
    {
        std::lock_guard<std::mutex> lock(m);  
        std::cout << "Mutex locked inside scope\n";
    } // scope ends → mutex automatically unlocked

    std::cout << "Mutex automatically released\n";
}
int main() {
    std::thread t(task);
    t.join();
}