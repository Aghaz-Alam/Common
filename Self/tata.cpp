/******************************************************************************

nput: nums = [12,10,10,30,12,12]
Output: true

Input: nums = [12,10, 12, 10]
Output: false

*******************************************************************************/
//Method: 1
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int main(){
    //int arr[] = {12,10,10,30,12,12};     //1
    int arr[] = {12,10, 12, 10};           //0
    int size = sizeof(arr)/sizeof(arr[0]);
    bool x = false;

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




//Method:2
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
int main(){
    //int arr[] = {12,10,10,30,12,12};     //true
    int arr[] = {12,10, 12, 10};           //false
    int size = sizeof(arr)/sizeof(arr[0]);

    unordered_map<int, int> freq;
    for(int i=0; i<size; i++){
        freq[arr[i]]++;
    }

    unordered_set<int> seen; 
    for(auto &x : freq){
        if(seen.count(x.second)){
            cout << "false";
            return 0;
        }
        seen.insert(x.second);
    }

    cout << "true";
    return 0;
}



/******************************************************************************

Input: nums = [0,10,0,30,12]
Output: [10,30,12,0,0]

*******************************************************************************/
//Method:1- In-place Optimal Logic (No extra vector)
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





//Method: 2- using another vector
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
































