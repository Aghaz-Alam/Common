
//3️⃣ Lower Triangle

#include <iostream>
using namespace std;
int main(){
  int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
     cout << "Lower Triangle:\n";
      for(int i=0;i<3;i++){
        for(int j=0;j<=i;j++)
            cout << a[i][j] << " ";
        cout << endl;
      }
  return 0;
}
/* 
Output:
1
4 5
7 8 9
*/


