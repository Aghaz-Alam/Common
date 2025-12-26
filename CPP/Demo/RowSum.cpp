
//5️⃣ Row Sum

#include <iostream>
using namespace std;
int main(){
    int a[2][3]={{1,2,3},{4,5,6}};
    for(int i=0;i<2;i++){
        int sum=0;
        for(int j=0;j<3;j++) sum+=a[i][j];
        cout << "Row " << i+1 << " sum = " << sum << endl;
    }
    return 0;
}
/* 
Output:
Row 1 sum = 6
Row 2 sum = 15
*/





