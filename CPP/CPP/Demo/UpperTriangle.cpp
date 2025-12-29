
//4️⃣ Upper Triangle

#include <iostream>
using namespace std;
int main(){
    int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    cout << "Upper Triangle:\n";
    for(int i=0;i<3;i++){
        for(int j=i;j<3;j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
  return 0;
}
/* 
Output:
1 2 3
5 6
9
*/



