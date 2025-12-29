#include<iostream>
using namespace std;
int fun1(const int& n){
   return n*(n+1)/2;
}

int fun2(const int& n){
    int sum = 0;
    for(int i=0; i<=n; i++){
       sum +=i;
    }
    return sum;
}

int fun3(const int& n){
    int sum=0;
    for(int i=0; i<=n; i++){
        for(int j=1; j<=i; j++){
            sum++;
        }
    }
    return sum;
}

int main(){
    int n=5;
    cout<<fun1(n)<<endl;
    cout<<fun2(n)<<endl;
    cout<<fun3(n)<<endl;

  return 0;
}
/*
15
15
15
*/