

//8️⃣ Matrix Addition

#include <iostream>
using namespace std;
int main(){
    int a[2][2]={{1,2},{3,4}};
    int b[2][2]={{5,6},{7,8}};
    cout << "Sum Matrix:\n";
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)
            cout << a[i][j]+b[i][j] << " ";
        cout << endl;
    }
    return 0;
}
/* 
Output:
6 8
10 12
*/



