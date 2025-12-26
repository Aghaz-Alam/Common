/* ---------------- */
input: {1,2,3,4,5}
output: {5,4,3,2,1}
(reverse array)
/* -------------- */

//Using two-pointer swap (in-place, vector)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {1,2,3,4,5};
    int left = 0, right = nums.size() - 1;

    while(left < right) {
        swap(nums[left], nums[right]);
        left++;
        right--;
    }

    for(int x : nums)
        cout << x << " ";
}

//5 4 3 2 1 



//Using std::reverse (vector)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1,2,3,4,5};

    reverse(nums.begin(), nums.end());

    for(int x : nums)
        cout << x << " ";
}
//5 4 3 2 1 


//Using raw array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int left = 0, right = n-1;

    while(left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
}
//5 4 3 2 1 


//Using recursion
#include <iostream>
using namespace std;

void reverseArray(int arr[], int left, int right) {
    if(left >= right) return;
    swap(arr[left], arr[right]);
    reverseArray(arr, left+1, right-1);
}

int main() {
    int arr[] = {1,2,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    reverseArray(arr, 0, n-1);

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
}
//5 4 3 2 1 


//Using std::for_each + lambda (vector)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1,2,3,4,5};

    int n = nums.size();
    for_each(nums.begin(), nums.begin() + n/2, [&](int &x) {
        swap(x, nums[n - 1 - (&x - &nums[0])]);
    });

    for(int x : nums)
        cout << x << " ";
}
//5 4 3 2 1 


//C++17 structured binding + lambda (vector)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1,2,3,4,5};

    int n = nums.size();
    auto swap_lambda = [&](int i){ swap(nums[i], nums[n-1-i]); };
    for(int i=0; i<n/2; i++) swap_lambda(i);

    for(int x : nums) cout << x << " ";
}
//5 4 3 2 1 

