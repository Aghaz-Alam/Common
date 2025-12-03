/* ----------------------------- */
input: {2,4,1,3,6,7}
output: {2,4,6,7,1,3}
(move even to front, odd to back)
/* ------------------------------ */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {2,4,1,3,6,7};

    int left = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] % 2 == 0) {        // even number
            swap(nums[i], nums[left]);
            left++;
        }
    }

    // Print result
    for(int x : nums)
        cout << x << " ";
}
//2 4 6 3 1 7 


#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {2,4,1,3,6,7};
    
    vector<int> evens, odds;

    for(int x : nums) {
        if(x % 2 == 0)
            evens.push_back(x);
        else
            odds.push_back(x);
    }

    // Merge back
    evens.insert(evens.end(), odds.begin(), odds.end());

    // Print
    for(int x : evens)
        cout << x << " ";
}
//2 4 6 3 1 7 




#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {2,4,1,3,6,7};

    int insertPos = 0;  // where next even should go

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] % 2 == 0) {      // even number
            int evenVal = nums[i];

            // Shift elements right to keep order stable
            int j = i;
            while (j > insertPos) {
                nums[j] = nums[j - 1];
                j--;
            }

            nums[insertPos] = evenVal;
            insertPos++;  // next even slot
        }
    }

    // Print result
    for (int x : nums)
        cout << x << " ";
}
//2 4 6 3 1 7 








#include <iostream>
#include <vector>
using namespace std;

// Stable in-place: evens first, odds later
void stableEvenFirst(vector<int>& nums) {
    int insertPos = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] % 2 == 0) {      // even
            int val = nums[i];
            int j = i;

            // shift all previous odds right by 1
            while (j > insertPos) {
                nums[j] = nums[j - 1];
                j--;
            }

            nums[insertPos] = val;
            insertPos++;
        }
    }
}
int main() {
    vector<int> v = {2,4,1,3,6,7};
    stableEvenFirst(v);

    for (int x : v) cout << x << " ";
}
//2 4 6 1 3 7 







#include <iostream>
#include <vector>
#include <functional>
using namespace std;

// Template stable in-place partition
template <typename T, typename Pred>
void stablePartitionInPlace(vector<T>& arr, Pred predicate) {
    int insertPos = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (predicate(arr[i])) {
            T val = arr[i];
            int j = i;

            // shift to maintain stability
            while (j > insertPos) {
                arr[j] = arr[j - 1];
                j--;
            }

            arr[insertPos] = val;
            insertPos++;
        }
    }
}

bool isEven(int x) { return x % 2 == 0; }

int main() {
    vector<int> nums = {2,4,1,3,6,7};

    stablePartitionInPlace(nums, isEven);

    for (int x : nums) cout << x << " ";
}
//2 4 6 1 3 7 



//Lambda Version (Stable + In-Place Template)
#include <iostream>
#include <vector>
using namespace std;

template <typename T, typename Pred>
void stablePartitionInPlace(vector<T>& arr, Pred predicate) {
    int insertPos = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (predicate(arr[i])) {
            T val = arr[i];
            int j = i;
            while (j > insertPos) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[insertPos] = val;
            insertPos++;
        }
    }
}

int main() {
    vector<int> v = {2,4,1,3,6,7};

    // Lambda for even numbers
    stablePartitionInPlace(v, [](int x){ return x % 2 == 0; });

    for (int x : v) cout << x << " ";
}

//2 4 6 1 3 7 





//Using STL stable_partition() (Fastest, O(n), stable)  even first
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {2,4,1,3,6,7};

    // stable_partition automatically preserves order
    stable_partition(v.begin(), v.end(),[](int x){ return x % 2 == 0; }   // even first
    );

    for (int x : v) cout << x << " ";
}
//2 4 6 1 3 7 


//Using STL stable_partition() (Fastest, O(n), stable) --odd first
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {2,4,1,3,6,7};

    // stable_partition automatically preserves order
    stable_partition(v.begin(), v.end(),[](int x){ return x % 2 != 0; }   // odd first
    );

    for (int x : v) cout << x << " ";
}
//1 3 7 2 4 6 




#include <iostream>
#include <vector>
using namespace std;

// Generic stable in-place partition template
template <typename T, typename Pred>
void stablePartitionInPlace(vector<T>& arr, Pred predicate) {
    int insertPos = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (predicate(arr[i])) {        // element satisfies predicate
            T val = arr[i];
            int j = i;

            // shift elements to the right to maintain stability
            while (j > insertPos) {
                arr[j] = arr[j - 1];
                j--;
            }

            arr[insertPos] = val;
            insertPos++;
        }
    }
}

int main() {
    vector<int> v = {2,4,1,3,6,7};

    // Odds first
    stablePartitionInPlace(v, [](int x){ return x % 2 != 0; });

    // Print
    for (int x : v)
        cout << x << " ";
}

//1 3 7 2 4 6 