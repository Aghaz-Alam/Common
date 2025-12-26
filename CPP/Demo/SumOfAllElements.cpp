

//7️⃣ Sum of All Elements

#include <iostream>
using namespace std;
int main(){
    int a[2][2]={{1,2},{3,4}};
    int sum=0;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++) sum+=a[i][j];
    cout << "Total sum = " << sum;
    return 0;
}
/* 
Output:
Total sum = 10
*/

