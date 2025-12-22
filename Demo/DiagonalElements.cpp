
//2️⃣ Diagonal Elements (Square Matrix)

#include <iostream>
using namespace std;
int main(){
    int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    cout << "Diagonal elements:\n";
    for(int i=0;i<3;i++)
        cout << a[i][i] << " ";
    return 0;
}
/* 
Output:
1 5 9
*/

