/*=======================================
Write a class which is able to store any number of floats and have method which will return average of all stored floats,

Example of uses:
Average.avg;
avg.get_average(); //should return 0;
avg.push_back(3.0);
avg.push_back(9.0);
avg.get_average(); //should return 6.0 -> (3+9)/2;

========================================*/
#include <iostream>
#include <vector>
using namespace std;
class Average {
  private:
    vector<float> values;

  public:
    // Add a new value
    void push_back(float val) {
        values.push_back(val);
    }

    // Get the average of all stored values
    float get_average() const {
        if (values.empty())
            return 0.0f;

        float sum = 0.0f;
        for (float v : values)
            sum += v;

        return sum / values.size();
    }
};

int main() {
    Average avg;
    std::cout << avg.get_average() << std::endl; // 0
    avg.push_back(3.0f);
    avg.push_back(9.0f);

    std::cout << avg.get_average() << std::endl; // 6

    return 0;
}
/* 
0
6
*/




 
//Matrix Operations
1️⃣ Matrix Transpose

#include <iostream>
using namespace std;
int main() {
int a[2][3] = {{1,2,3},{4,5,6}};
cout << "Transpose:\n";
for(int j=0;j<3;j++){
    for(int i=0;i<2;i++)
        cout << a[i][j] << " ";
    cout << endl;
}
return 0;
}
/* 
Output:
1 4
2 5
3 6
*/


2️⃣ Diagonal Elements (Square Matrix)

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

3️⃣ Lower Triangle

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


4️⃣ Upper Triangle

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



5️⃣ Row Sum

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






6️⃣ Column Sum

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



7️⃣ Sum of All Elements

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


8️⃣ Matrix Addition

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




9️⃣ Matrix Multiplication

#include <iostream>
using namespace std;
int main(){
    int a[2][2]={{1,2},{3,4}};
    int b[2][2]={{5,6},{7,8}};
    int c[2][2]={0};


    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                c[i][j]+=a[i][k]*b[k][j];


    cout << "Product Matrix:\n";
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)
            cout << c[i][j] << " ";
        cout << endl;
    }
    return 0;
}
/* 
Output:
19 22
43 50
*/



🔟 Diagonal Sum
#include <iostream>
using namespace std;
int main(){
    int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    int sum=0;
    for(int i=0;i<3;i++) sum+=a[i][i];
    cout << "Diagonal sum = " << sum;
    return 0;
}
/* 
Diagonal sum = 15
*/