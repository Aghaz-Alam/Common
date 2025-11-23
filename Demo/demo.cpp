// #include<iostream>
// #
// using namespace std;
// int main(){
//     std::function x =[](int x, int y){
//         return x+y;
//     }
//     cout<<x(10,30);
// }

// cerr
// clog



#include <iostream>
#include <string>
#include <cctype> // Required for isalpha()
using namespace std;
int main() {
    char ch[] = "Hello you are a programmer";
    string vowels = "AEIOUaeiou"; 
    int vcount = 0;
    int ccount = 0;

    for (int i = 0; ch[i] != '\0'; ++i) {
        
        if (std::isalpha(ch[i])) {
            if (vowels.find(ch[i]) == std::string::npos) {
                ccount++;
            } else {
                vcount++;
            }
        }
    }
    cout << "Original String: " << ch << endl;
    cout << "Vowel Count:     " << vcount << endl;
    cout << "Consonant Count: " << ccount << endl;

    return 0;
}
/*
Output:
dell@dell-Latitude-5420:~/Music$ ./demo 
Original String: Hello you are a programmer
Vowel Count:     10
Consonant Count: 12
*/




// Function Overriding and valling 
#include <iostream>
#include<memory>
using namespace std;
class Base{
  public:
    virtual void fun(){
        cout<<"Test1!";
    }
};
class Derived: public Base {
    public:
      void fun() override{
              cout<<"Test2!"<<endl;
      }
};
int main() {
   Derived  d;
   Base &b1 = d;
   b1.fun();
   
   Base* b2 = &d;
   b2->fun();
   
   
   Base* b3 = new Derived();
   b3->fun();
   delete b3;
   
   
   unique_ptr<Base> b4 = make_unique<Derived>();
   b4->fun();
   
   
   shared_ptr<Base> b5 = make_shared<Derived>();
   b5->fun();

  return 0;
}
/*
Test2!
Test2!
Test2!
Test2!
Test2!
*/









