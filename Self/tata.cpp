Question: 1
Input: nums = [12,10,10,30,12,12]
Output: true

Input: nums = [12,10, 12, 10]
Output: false



Question: 2
Input: nums = [0,10,0,30,12]
Output: [10,30,12,0,0]


Quetion: 3
input: {1,2,3,4,5,6,7};
output: {7,1,6,2,5,4,3};

Question: 4
input: {1,2,3,4,5,6};
output: {2,1,4,3,6,5};


/* *****************************************************************************

nput: nums = [12,10,10,30,12,12]
Output: true

Input: nums = [12,10, 12, 10]
Output: false

*******************************************************************************/
//Method: 1 --array, unordered_map, vector
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int main(){
    //int arr[] = {12,10,10,30,12,12};     //1
    int arr[] = {12,10, 12, 10};           //0
    int size = sizeof(arr)/sizeof(arr[0]);
    
    unordered_map<int, int> freq;

    // Count frequencies
    for(int i=0; i<size; i++){
        freq[arr[i]]++;
    }

    // Extract unique keys from freq map
    vector<int> keys;
    for(auto &p : freq){
        keys.push_back(p.first);
    }

    // Compare frequencies of unique elements
    for(int i=0; i<keys.size(); i++){
        for(int j=i+1; j<keys.size(); j++){
            if(freq[keys[i]] == freq[keys[j]]){
                cout << false;   // duplicate frequencies
                return 0;
            }
        }
    }

    cout << true;   // all frequencies unique
    return 0;
}


//method: 2- using array and unordered_map and bruit force
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    //int arr[] = {12,10,10,30,12,12};   // true
    int arr[] = {12,10,12,10};           // false
    int size = sizeof(arr) / sizeof(arr[0]);

    unordered_map<int, int> freq;

    // Count frequencies
    for (int i = 0; i < size; i++) {
        freq[arr[i]]++;
    }

    // Compare frequency values without using any extra container
    for (auto it1 = freq.begin(); it1 != freq.end(); ++it1) {
        for (auto it2 = next(it1); it2 != freq.end(); ++it2) {
            if (it1->second == it2->second) {
                cout << false;
                return 0;
            }
        }
    }

    cout << true;
    return 0;
}



//Method:2-- array, unordered_map, unordered_set
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
int main() {
    //int arr[] = {12,10,10,30,12,12};   // Example → Output: true
    int arr[] = {12,10,12,10};           // Example → Output: false
    int size = sizeof(arr) / sizeof(arr[0]);

    // Step 1: Count frequency of each element
    unordered_map<int, int> freq;
    for (int i = 0; i < size; i++) {
        freq[arr[i]]++;   // Increment count of element arr[i]
    }

    // Step 2: Check if all frequencies are unique
    unordered_set<int> seen; // Stores already observed frequencies

    for (auto &x : freq) {

        // If this frequency is already present, it means two elements
        // have the same occurrence count → not unique
        if (seen.count(x.second)) {
            cout << "false";   // Found duplicate frequency
            return 0;          // Exit the program
        }

        // Insert this new frequency into the set
        seen.insert(x.second);
    }

    // If we reach here, all frequencies were unique
    cout << "true";
    return 0;
}




/******************************************************************************

Input: nums = [0,10,0,30,12]
Output: [10,30,12,0,0]

*******************************************************************************/
//Method:1- In-place Optimal Logic (No extra vector)  ---In-place two-pass (optimal)
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> nums = {0,10,0,30,12};
    int index = 0;

    // Move non-zero to front
    for(int x : nums) {
        if(x != 0)
            nums[index++] = x;
    }

    // Fill rest with zeros
    while(index < nums.size())
        nums[index++] = 0;

    // Print
    for(int x : nums)
        cout << x << " ";
}
//10 30 12 0 0 




//Method: 2- using another vector --Extra vector
#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> nums = {0,10,0,30,12};
    vector<int> result;
    
    // First add non-zero elements
    for(int x : nums){
        if(x != 0)
            result.push_back(x);
    }

    // Then add zeros
    for(int x : nums){
        if(x == 0)
            result.push_back(x);
    }

    // Output
    for(int x : result){
        cout << x << " ";
    }

    return 0;
}
//10 30 12 0 0 



//Method-3: Two-Pointers (Swap Technique) — Single Pass
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {0,10,0,30,12};
    int j = 0;

    for(int i = 0; i < nums.size(); i++){
        if(nums[i] != 0){
            swap(nums[i], nums[j]);
            j++;
        }
    }

    for(int x : nums)
        cout << x << " ";
}
//10 30 12 0 0 



// Method-4: Partitioning (similar to QuickSort partition)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {0,10,0,30,12};
    
    int pivot = 0;  
    int j = 0;

    for(int i = 0; i < nums.size(); i++){
        if(nums[i] != pivot){
            swap(nums[i], nums[j]);
            j++;
        }
    }

    for(int x : nums)
        cout << x << " ";
}
//10 30 12 0 0 


//Method-5: Stable Partition (C++ STL Algorithm)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {0,10,0,30,12};

    stable_partition(nums.begin(), nums.end(), [](int x){ return x != 0; });

    for(int x : nums)
        cout << x << " ";
}

//10 30 12 0 0 
/*  
✔ Notes
stable_partition keeps order of non-zeros
Uses extra memory internally → not strictly in-place
Very clean one-line solution
*/



//Method-6: Counting Zeros
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> nums = {0,10,0,30,12};

    int zeroCount = 0;
    for(int x : nums)
        if(x == 0) zeroCount++;

    int idx = 0;
    for(int x : nums)
        if(x != 0) nums[idx++] = x;

    while(zeroCount--)
        nums[idx++] = 0;

    for(int x : nums)
        cout << x << " ";
}
//10 30 12 0 0 








/*----------------------------------------------------------------*/

/*
input: {1,2,3,4,5,6,7};
output: {7,1,6,2,5,4,3};
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> input = {1,2,3,4,5,6,7};
    int n = input.size();

    vector<int> output;

    int start = 0, end = n - 1;

    while(start <= end) {
        if(end >= start)
            output.push_back(input[end--]);
        if(start <= end)
            output.push_back(input[start++]);
    }

    // Print result
    for(int x : output)
        cout << x << " ";

    return 0;
}



/*----------------------------------------------------------------*/

/*
input: {1,2,3,4,5,6};
output: {2,1,4,3,6,5};
*/

#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> input = {1,2,3,4,5,6};
    int n = input.size();
    int k=2;
    
    for(int i=0; i<n; i+=k){
        int start = i, end = min(i+k-1 , n-1);
        
        while(start<end){
           swap(input[start], input[end]);
           start++;
           end--;
        }
    }
    
    for(auto &x: input){
        cout<<x<<" ";
    }
    cout<<endl;
}




















