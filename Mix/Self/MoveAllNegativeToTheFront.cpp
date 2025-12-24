/* --------------------------- */
input: {1,-1,3,-5,7}
output: {-1,-5,1,3,7}
(move all negatives to front)
/* ---------------------------- */

//Method 1 — Using Extra Array (Simple & Clear)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {1, -1, 3, -5, 7};
    vector<int> result;

    // First push negatives
    for(int x : nums)
        if(x < 0)
            result.push_back(x);

    // Then push non-negatives
    for(int x : nums)
        if(x >= 0)
            result.push_back(x);

    // Print output
    for(int x : result)
        cout << x << " ";
}
//-1 -5 1 3 7 





//Method 2 — In-place Stable (Uses Two Vectors Internally)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1, -1, 3, -5, 7};

    stable_partition(nums.begin(), nums.end(), [](int x){ return x < 0; });

    for(int x : nums)
        cout << x << " ";
}
//-1 -5 1 3 7 


//Method 3
#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> nums = {1, -1, 3, -5, 7};
    vector<int> orig = nums;      // keep original values
    int index = 0;

    // Move negatives to front (iterate original)
    for (int x : orig) {
        if (x < 0) nums[index++] = x;
    }

    // Move positives next (iterate original)
    for (int x : orig) {
        if (x >= 0) nums[index++] = x;
    }

    // Print
    for (int x : nums)
        cout << x << " ";
    cout << '\n';
}
//-1 -5 1 3 7 


//Method: 4
#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> nums = {1, -1, 3, -5, 7};

    int start = 0;   // position where next negative should be placed

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] < 0)
            swap(nums[i], nums[start++]);
    }

    // Print result
    for (int x : nums)
        cout << x << " ";
    cout << "\n";

    return 0;
}
//-1 -5 1 3 7 



