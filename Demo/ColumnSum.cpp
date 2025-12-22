

//6️⃣ Column Sum

#include <iostream>
using namespace std;
int main(){
    int a[2][3]={{1,2,3},{4,5,6}};
        for(int j=0;j<3;j++){
            int sum=0;
            for(int i=0;i<2;i++) sum+=a[i][j];
            cout << "Column " << j+1 << " sum = " << sum << endl;
    }
    return 0;
}
/* 
Output:
Column 1 sum = 5
Column 2 sum = 7
Column 3 sum = 9
*/


