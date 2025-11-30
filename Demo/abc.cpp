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



// #include <iostream>
// #include <mutex>
// #include <thread>
// std::mutex m;
// void task() {
//     {
//         std::lock_guard<std::mutex> lock(m);  
//         std::cout << "Mutex locked inside scope\n";
//     } // scope ends → mutex automatically unlocked

//     std::cout << "Mutex automatically released\n";
// }
// int main() {
//     std::thread t(task);
//     t.join();
// }




#include <iostream>
#include <stdexcept>
using namespace std;
template <typename T, size_t N>
class MyArray {
  private:
    T arr[N];

  public:
    T& operator[](size_t index) { return arr[index]; }

    T& at(size_t index) {
        if (index >= N) throw out_of_range("Index out of range");
        return arr[index];
    }

    constexpr size_t size() const { return N; }
    constexpr size_t capacity() const { return N; }
};

int main() {
    MyArray<int, 5> arr;

    // Fill array manually
    for(int i=0; i<5; i++){
        arr[i] = i;
    }

    // You cannot pop_back in fixed array
    cout << "Size: " << arr.size() << endl;
    cout << "Capacity: " << arr.capacity() << endl;

    arr[2] = 100;
    for(int i=0; i<arr.size(); i++){
        cout << arr[i] << " ";
    } 
    cout << endl;

    // Access element safely
    try {
        cout << "Element at index 2: " << arr.at(2) << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    return 0;
}



//Missing elements
#include <iostream>
#include <map>
using namespace std;
int main(){
     int arr[] = { 3, 5, 7, 8};
     int n = sizeof(arr)/sizeof(arr[0]);
     
     map<int, int> m;
     int first = arr[0], last = arr[0];
     for(int i=0; i<n; i++){
        if(arr[i]<first)  first = arr[i];
        
        if(arr[i]>last) last = arr[i];
        
         m[arr[i]]++;
     }
     
     for(int i=1; i<last; i++){
         if(m.find(i)==m.end())
             cout<<i<<endl; 
         
     }
    return 0;
}
/*
1
2
4
6
*/