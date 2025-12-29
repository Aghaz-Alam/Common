/*=================================================================================*/
Phase 2: Arrays & Strings (2 weeks)
Goal: Foundation of all problems

Topics:
-->1D & 2D arrays
-->Sliding window
-->Two pointers
-->Prefix sum
-->Kadane’s algorithm
-->String manipulation

Practice problems:
-->Reverse array/string
-->Move zeros
-->Longest subarray
-->Max sum subarray
-->Anagrams
-->Palindrome check
/*=================================================================================*/

1️⃣ 1D & 2D Arrays
Concise Notes
1D array: Linear structure, index-based access.
2D array: Matrix, access via arr[i][j].
Operations: Traverse, search, update, sum, rotate, transpose.
Time Complexity: Access O(1), Traversal O(n) for 1D, O(n×m) for 2D.

Example 1: Reverse 1D Array
#include <iostream>
using namespace std;
void reverseArray(int arr[], int n) {
    int i = 0, j = n-1;
    while(i < j) {
        swap(arr[i], arr[j]);
        i++; j--;
    }
}
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;

    cout << "Original Array: ";
    for(int i=0; i<n; i++) cout << arr[i] << " ";
    cout << endl;

    reverseArray(arr, n);

    cout << "Reversed Array: ";
    for(int i=0; i<n; i++) cout << arr[i] << " ";
}
/*
Output:
Original Array: 1 2 3 4 5
Reversed Array: 5 4 3 2 1


Dry Run:
i=0,j=4 → swap 1 & 5 → [5 2 3 4 1]
i=1,j=3 → swap 2 & 4 → [5 4 3 2 1]
i=2,j=2 → stop
*/


Example 2: Sum of 2D Array
#include <iostream>
using namespace std;
int main() {
    int arr[2][3] = {{1,2,3}, {4,5,6}};
    int sum = 0;

    for(int i=0;i<2;i++)
        for(int j=0;j<3;j++)
            sum += arr[i][j];

    cout << "Sum of 2D Array: " << sum;
}
/*
Output:
Sum of 2D Array: 21

Dry Run:
i=0,j=0 → sum=1
i=0,j=1 → sum=3
...
i=1,j=2 → sum=21
*/




2️⃣ Sliding Window
Concise Notes
Technique to reduce O(n²) subarray problems to O(n).
Fixed window: Size k, move start and end pointers.
Variable window: Expand/contract based on conditions.
Common problems: max sum subarray, longest substring with condition.


Example: Max Sum Subarray of Size K
#include <iostream>
using namespace std;
int maxSumSubarray(int arr[], int n, int k) {
    int sum=0;
    for(int i=0;i<k;i++) sum += arr[i];

    int maxSum = sum;
    for(int i=k;i<n;i++) {
        sum += arr[i] - arr[i-k];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
int main() {
    int arr[] = {1,2,3,4,5};
    int k = 3;
    cout << "Max Sum of Subarray of size 3: " << maxSumSubarray(arr,5,k);
}
/*
Output:
Max Sum of Subarray of size 3: 12

Dry Run:
Initial sum = 1+2+3=6
i=3 → sum=6+4-1=9 → max=9
i=4 → sum=9+5-2=12 → max=12
*/



3️⃣ Two Pointers
Concise Notes
Maintain two indices/pointers to traverse array/string.
Common in sorted arrays or palindrome checks.
Reduces O(n²) problems to O(n).


Example: Move Zeros to End
#include <iostream>
using namespace std;
void moveZeros(int arr[], int n) {
    int j=0;
    for(int i=0;i<n;i++) {
        if(arr[i]!=0) swap(arr[i], arr[j++]);
    }
}
int main() {
    int arr[] = {0,1,0,3,12};
    int n=5;

    moveZeros(arr,n);

    for(int i=0;i<n;i++) cout << arr[i] << " ";
}
/*
Output:
1 3 12 0 0

Dry Run:
i=0,0 → skip
i=1,1 → swap(1,0) → [1,0,0,3,12], j=1
i=3 → swap(3,0) → [1,3,0,0,12], j=2
i=4 → swap(12,0) → [1,3,12,0,0]
*/





4️⃣ Prefix Sum
Concise Notes
Store cumulative sum to answer subarray queries quickly.
prefix[i] = arr[0]+...+arr[i]
Subarray sum [l,r] = prefix[r] - prefix[l-1] (if l>0)


Example: Prefix Sum Array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4};
    int n=4;
    int prefix[4];

    prefix[0] = arr[0];
    for(int i=1;i<n;i++) prefix[i] = prefix[i-1] + arr[i];

    for(int i=0;i<n;i++) cout << prefix[i] << " ";
}
/*
Output:
1 3 6 10

Dry Run:
prefix[0]=1
prefix[1]=1+2=3
prefix[2]=3+3=6
prefix[3]=6+4=10
*/




5️⃣ Kadane’s Algorithm
Concise Notes
Maximum sum subarray in O(n)
maxEndingHere = max(arr[i], maxEndingHere+arr[i])
maxSoFar = max(maxSoFar, maxEndingHere)

Example: Max Sum Subarray
#include <iostream>
using namespace std;
int kadane(int arr[], int n) {
    int maxEndingHere = arr[0], maxSoFar = arr[0];
    for(int i=1;i<n;i++) {
        maxEndingHere = max(arr[i], maxEndingHere+arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}
int main() {
    int arr[] = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Max Sum Subarray: " << kadane(arr,9);
}
/*
Output:
Max Sum Subarray: 6

Dry Run:
maxEndingHere = -2 → 1 → -2 → 4 → 3 → 5 → 6 → 1 → 5
maxSoFar = 6
*/



6️⃣ String Manipulation
Concise Notes
Strings: Array of chars, index-based access.
Common operations: reverse, palindrome, anagram check, substring.

Example 1: Reverse String
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "hello";
    int i=0, j=s.length()-1;
    while(i<j) swap(s[i++], s[j--]);
    cout << s;
}
/*
Output:
olleh

Dry Run:
swap h & o → 'oellh'
swap e & l → 'olleh'
*/



Example 2: Palindrome Check
#include <iostream>
#include <string>
using namespace std;
bool isPalindrome(string s) {
    int i=0, j=s.length()-1;
    while(i<j) {
        if(s[i++] != s[j--]) return false;
    }
    return true;
}
int main() {
    string s = "racecar";
    cout << (isPalindrome(s) ? "Yes" : "No");
}
/*
Output:
Yes

Dry Run:
r=r, a=a, c=c → palindrome
*/




Example 3: Check Anagram
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
bool isAnagram(string a, string b) {
    if(a.length()!=b.length()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a==b;
}
int main() {
    string a = "listen", b = "silent";
    cout << (isAnagram(a,b) ? "Yes" : "No");
}
/*
Output:
Yes
*/





1️⃣ 1D Arrays
Concise Notes
Linear structure, elements indexed from 0.
Common operations: traverse, reverse, sum, find min/max, rotate.
Access time: O(1), Traversal: O(n).


Example 1: Reverse Array
#include <iostream>
using namespace std;
void reverseArray(int arr[], int n) {
    int i=0, j=n-1;
    while(i<j) swap(arr[i++], arr[j--]);
}
int main() {
    int arr[] = {1,2,3,4,5};
    int n=5;

    cout << "Original Array: ";
    for(int i=0;i<n;i++) cout << arr[i] << " ";
    cout << endl;

    reverseArray(arr,n);

    cout << "Reversed Array: ";
    for(int i=0;i<n;i++) cout << arr[i] << " ";
}
/*
Output:
Original Array: 1 2 3 4 5
Reversed Array: 5 4 3 2 1


Dry Run:
i=0,j=4 → swap 1 & 5 → [5 2 3 4 1]
i=1,j=3 → swap 2 & 4 → [5 4 3 2 1]
i=2,j=2 → stop
*/




Example 2: Move Zeros to End
#include <iostream>
using namespace std;
void moveZeros(int arr[], int n) {
    int j=0;
    for(int i=0;i<n;i++) {
        if(arr[i]!=0) swap(arr[i], arr[j++]);
    }
}
int main() {
    int arr[] = {0,1,0,3,12};
    int n=5;

    moveZeros(arr,n);

    for(int i=0;i<n;i++) cout << arr[i] << " ";
}
/*
Output:
1 3 12 0 0

Dry Run:
i=0 → 0 → skip
i=1 → 1 → swap → [1 0 0 3 12], j=1
i=3 → 3 → swap → [1 3 0 0 12], j=2
i=4 → 12 → swap → [1 3 12 0 0]
*/



2️⃣ 2D Arrays
Concise Notes
Matrix structure: arr[row][col]
Operations: traverse, sum, transpose, rotate.
Access: O(1), Traverse: O(n×m)

Example: Sum of 2D Array
#include <iostream>
using namespace std;
int main() {
    int arr[2][3] = {{1,2,3},{4,5,6}};
    int sum=0;

    for(int i=0;i<2;i++)
        for(int j=0;j<3;j++)
            sum += arr[i][j];

    cout << "Sum of 2D Array: " << sum;
}
/*
Output:
Sum of 2D Array: 21

Dry Run:
i=0,j=0 → sum=1
i=0,j=1 → sum=3
...
i=1,j=2 → sum=21
*/




3️⃣ Sliding Window
Concise Notes
Reduce O(n²) subarray problems to O(n).
Fixed window: size k, move start/end pointers.
Variable window: expand/contract based on conditions.

Example: Max Sum Subarray of Size K
#include <iostream>
using namespace std;
int maxSumSubarray(int arr[], int n, int k) {
    int sum=0;
    for(int i=0;i<k;i++) sum += arr[i];

    int maxSum = sum;
    for(int i=k;i<n;i++) {
        sum += arr[i] - arr[i-k];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
int main() {
    int arr[] = {1,2,3,4,5};
    int k=3;
    cout << "Max Sum of Subarray of size 3: " << maxSumSubarray(arr,5,k);
}
/*
Output:
Max Sum of Subarray of size 3: 12

Dry Run:
Initial sum = 1+2+3=6
i=3 → sum=6+4-1=9 → max=9
i=4 → sum=9+5-2=12 → max=12
*/



4️⃣ Two Pointers
Concise Notes
Use two indices/pointers to traverse array/string.
Useful in sorted arrays or palindrome checks.
Reduces O(n²) problems to O(n).

Example: Two Pointers Palindrome Check
#include <iostream>
#include <string>
using namespace std;
bool isPalindrome(string s) {
    int i=0, j=s.length()-1;
    while(i<j) {
        if(s[i++] != s[j--]) return false;
    }
    return true;
}
int main() {
    string s = "racecar";
    cout << (isPalindrome(s) ? "Yes" : "No");
}
/*
Output:
Yes

Dry Run:
r=r, a=a, c=c → palindrome
*/

5️⃣ Prefix Sum
Concise Notes
Store cumulative sum to answer subarray sum queries in O(1).
prefix[i] = arr[0]+...+arr[i]
Subarray sum [l,r] = prefix[r]-prefix[l-1] (if l>0)

Example: Prefix Sum Array
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,3,4};
    int n=4;
    int prefix[4];

    prefix[0] = arr[0];
    for(int i=1;i<n;i++) prefix[i] = prefix[i-1] + arr[i];

    for(int i=0;i<n;i++) cout << prefix[i] << " ";
}
/*
Output:
1 3 6 10

Dry Run:
prefix[0]=1
prefix[1]=1+2=3
prefix[2]=3+3=6
prefix[3]=6+4=10
*/




6️⃣ Kadane’s Algorithm
Concise Notes
Maximum sum subarray in O(n)
maxEndingHere = max(arr[i], maxEndingHere+arr[i])
maxSoFar = max(maxSoFar, maxEndingHere)

Example: Max Sum Subarray
#include <iostream>
using namespace std;
int kadane(int arr[], int n) {
    int maxEndingHere = arr[0], maxSoFar = arr[0];
    for(int i=1;i<n;i++) {
        maxEndingHere = max(arr[i], maxEndingHere+arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}
int main() {
    int arr[] = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Max Sum Subarray: " << kadane(arr,9);
}
/*
Output:
Max Sum Subarray: 6

Dry Run:
maxEndingHere=-2 → 1 → -2 → 4 → 3 → 5 → 6 → 1 → 5
maxSoFar=6
*/




7️⃣ String Manipulation
Concise Notes
Strings: array of chars
Common operations: reverse, palindrome check, anagram, substring.

Example 1: Reverse String
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "hello";
    int i=0, j=s.length()-1;
    while(i<j) swap(s[i++], s[j--]);
    cout << s;
}
/*
Output:
olleh

Dry Run:
swap h & o → oellh
swap e & l → olleh
*/





Example 2: Anagram Check
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
bool isAnagram(string a, string b) {
    if(a.length()!=b.length()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a==b;
}
int main() {
    string a="listen", b="silent";
    cout << (isAnagram(a,b) ? "Yes" : "No");
}
/*
Output:
Yes
*/




1️⃣ Longest Subarray with Given Sum (Prefix Sum)
Concise Notes:
Used when subarray sum = K
Prefix sum + hashmap
Works with negative numbers
Time: O(n), Space: O(n)



Code
#include <iostream>
#include <unordered_map>
using namespace std;
int longestSubarray(int arr[], int n, int k) {
    unordered_map<int,int> mp;
    int sum = 0, maxLen = 0;

    for(int i=0;i<n;i++) {
        sum += arr[i];

        if(sum == k)
            maxLen = i + 1;

        if(mp.find(sum - k) != mp.end())
            maxLen = max(maxLen, i - mp[sum - k]);

        if(mp.find(sum) == mp.end())
            mp[sum] = i;
    }
    return maxLen;
}
int main() {
    int arr[] = {10, 5, 2, 7, 1, 9};
    cout << longestSubarray(arr, 6, 15);
}
/*
Output
4

Dry Run
Index: 0 → sum=10
Index: 1 → sum=15 → maxLen=2
Index: 3 → sum=24, sum-k=9 exists → length=4
*/



2️⃣ Longest Subarray of 0s and 1s (Equal Count)
Concise Notes:
Convert 0 → -1
Reduce to subarray sum = 0
Prefix sum + hashmap


Code
#include <iostream>
#include <unordered_map>
using namespace std;
int longest01(int arr[], int n) {
    unordered_map<int,int> mp;
    int sum = 0, maxLen = 0;

    for(int i=0;i<n;i++) {
        sum += (arr[i] == 0 ? -1 : 1);

        if(sum == 0)
            maxLen = i + 1;

        if(mp.find(sum) != mp.end())
            maxLen = max(maxLen, i - mp[sum]);
        else
            mp[sum] = i;
    }
    return maxLen;
}
int main() {
    int arr[] = {0,1,0,1,1,0};
    cout << longest01(arr, 6);
}
/*
Output
6

Dry Run
0 → -1
1 → 0 → maxLen=2
...
Total balanced subarray length = 6
*/




3️⃣ Two Sum (Two Pointers – Sorted Array)
Concise Notes:
Works only if array is sorted
Left + Right pointer
Time: O(n)


Code
#include <iostream>
using namespace std;
bool twoSum(int arr[], int n, int target) {
    int l = 0, r = n-1;

    while(l < r) {
        int sum = arr[l] + arr[r];
        if(sum == target) return true;
        else if(sum < target) l++;
        else r--;
    }
    return false;
}
int main() {
    int arr[] = {1,2,4,6,10};
    cout << (twoSum(arr,5,8) ? "Yes" : "No");
}
/*
Output
Yes

Dry Run
1+10=11 → r--
1+6=7 → l++
2+6=8 → found
*/




4️⃣ Longest Substring Without Repeating Characters
Concise Notes:
Sliding window + map
Window expands & shrinks
Time: O(n)




Code
#include <iostream>
#include <unordered_map>
using namespace std;
int longestUnique(string s) {
    unordered_map<char,int> mp;
    int l=0, maxLen=0;

    for(int r=0;r<s.length();r++) {
        if(mp.count(s[r]) && mp[s[r]] >= l)
            l = mp[s[r]] + 1;

        mp[s[r]] = r;
        maxLen = max(maxLen, r - l + 1);
    }
    return maxLen;
}
int main() {
    cout << longestUnique("abcabcbb");
}
/*
Output
3

Dry Run
abc → length=3
repeat a → move left pointer
*/



5️⃣ Rotate Array by K (Reversal Algorithm)
Concise Notes:
Reverse whole array
Reverse first k
Reverse remaining
Time: O(n), Space: O(1)


Code
#include <iostream>
using namespace std;
void reverse(int arr[], int l, int r) {
    while(l<r) swap(arr[l++], arr[r--]);
}
int main() {
    int arr[] = {1,2,3,4,5};
    int n=5, k=2;
    k = k % n;

    reverse(arr, 0, n-1);
    reverse(arr, 0, k-1);
    reverse(arr, k, n-1);

    for(int i=0;i<n;i++) cout << arr[i] << " ";
}
/*
Output
4 5 1 2 3

Dry Run
Reverse all → 5 4 3 2 1
Reverse first k → 4 5
Reverse rest → 1 2 3
*/


6️⃣ Check If One String Is Rotation of Another
Concise Notes:
Trick: s1+s1 contains s2
Time: O(n)


Code
#include <iostream>
using namespace std;
bool isRotation(string s1, string s2) {
    if(s1.length()!=s2.length()) return false;
    return (s1 + s1).find(s2) != string::npos;
}
int main() {
    cout << (isRotation("abcd","cdab") ? "Yes" : "No");
}
/*
Output
Yes
*/



7️⃣ Count Frequency of Characters
Concise Notes:
Use array of size 26
Works for lowercase alphabets
Time: O(n)

Code
#include <iostream>
using namespace std;
int main() {
    string s = "aabbc";
    int freq[26] = {0};

    for(char c : s)
        freq[c - 'a']++;

    for(int i=0;i<26;i++)
        if(freq[i] > 0)
            cout << char(i+'a') << " -> " << freq[i] << endl;
}
/*
Output
a -> 2
b -> 2
c -> 1
*/






1️⃣ Maximum Product Subarray
Concise Notes
Product flips sign with negatives
Track maxProduct & minProduct
Time: O(n)



Code
#include <iostream>
using namespace std;
int maxProduct(int arr[], int n) {
    int maxP = arr[0], minP = arr[0], ans = arr[0];

    for(int i=1;i<n;i++) {
        if(arr[i] < 0) swap(maxP, minP);

        maxP = max(arr[i], maxP * arr[i]);
        minP = min(arr[i], minP * arr[i]);

        ans = max(ans, maxP);
    }
    return ans;
}
int main() {
    int arr[] = {2,3,-2,4};
    cout << maxProduct(arr, 4);
}
/*
Output
6

Dry Run
2 → max=2
3 → max=6
-2 → swap → max=-2
4 → max=4 → ans=6
*/





2️⃣ Majority Element (> n/2 times) — Moore’s Voting
Concise Notes
Cancel out different elements
Two passes (candidate + verify)
Time: O(n)




Code
#include <iostream>
using namespace std;
int majority(int arr[], int n) {
    int count=0, candidate;

    for(int i=0;i<n;i++) {
        if(count==0) candidate=arr[i];
        count += (arr[i]==candidate) ? 1 : -1;
    }
    return candidate;
}
int main() {
    int arr[] = {2,2,1,1,2,2,2};
    cout << majority(arr, 7);
}
/*
Output
2

Dry Run
2 → count=1
1 → count=0
2 → count=1 → survives
*/




3️⃣ Stock Buy & Sell (Max Profit – Single Transaction)
Concise Notes
Track minimum price
Profit = price − minPrice
Time: O(n)



Code
#include <iostream>
using namespace std;
int maxProfit(int prices[], int n) {
    int minPrice = prices[0], profit = 0;

    for(int i=1;i<n;i++) {
        profit = max(profit, prices[i] - minPrice);
        minPrice = min(minPrice, prices[i]);
    }
    return profit;
}
int main() {
    int prices[] = {7,1,5,3,6,4};
    cout << maxProfit(prices, 6);
}
/*
Output
5

Dry Run
min=1
sell at 6 → profit=5
*/



4️⃣ Find Missing Number (1 to N)
Concise Notes
Use sum formula
Avoid overflow using long long
Time: O(n)


Code
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,2,4,5};
    int n = 5;
    int sum = n*(n+1)/2;

    for(int x : arr) sum -= x;
    cout << sum;
}
/*
Output
3

Dry Run
Expected sum = 15
Actual sum = 12
Missing = 3
*/






5️⃣ First Non-Repeating Character
Concise Notes
Frequency array
Second pass to preserve order
Time: O(n)


Code
#include <iostream>
using namespace std;
int main() {
    string s = "aabbcdde";
    int freq[26] = {0};

    for(char c : s) freq[c-'a']++;

    for(char c : s) {
        if(freq[c-'a'] == 1) {
            cout << c;
            break;
        }
    }
}
/*
Output
c
*/




6️⃣ Check Palindrome (Two Pointers)
Concise Notes
Compare left & right
Ignore case/special chars (optional)
Time: O(n)



Code
#include <iostream>
using namespace std;
bool isPalindrome(string s) {
    int l=0, r=s.size()-1;
    while(l<r)
        if(s[l++] != s[r--]) return false;
    return true;
}
int main() {
    cout << (isPalindrome("madam") ? "Yes" : "No");
}
/*
Output
Yes
*/





7️⃣ Subarray with Given Sum (Sliding Window – Positives Only)
Concise Notes
Only works for positive numbers
Expand → shrink window
Time: O(n)



Code
#include <iostream>
using namespace std;
bool subarraySum(int arr[], int n, int k) {
    int sum=0, l=0;

    for(int r=0;r<n;r++) {
        sum += arr[r];

        while(sum > k)
            sum -= arr[l++];

        if(sum == k) return true;
    }
    return false;
}
int main() {
    int arr[] = {1,4,20,3,10,5};
    cout << (subarraySum(arr,6,33) ? "Yes" : "No");
}
/*
Output
Yes
*/




8️⃣ Remove Duplicates from Sorted Array (In-Place)
Concise Notes
Two pointer overwrite
Space: O(1)
Time: O(n)




Code
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,1,2,2,3};
    int n=5, idx=1;

    for(int i=1;i<n;i++)
        if(arr[i] != arr[i-1])
            arr[idx++] = arr[i];

    for(int i=0;i<idx;i++)
        cout << arr[i] << " ";
}
/*
Output
1 2 3
*/




9️⃣ Count Subarrays with Sum K (Prefix Sum)
Concise Notes
Use hashmap
Handles negatives
Time: O(n)



Code
#include <iostream>
#include <unordered_map>
using namespace std;
int countSubarrays(int arr[], int n, int k) {
    unordered_map<int,int> mp;
    mp[0]=1;
    int sum=0, count=0;

    for(int i=0;i<n;i++) {
        sum += arr[i];
        count += mp[sum-k];
        mp[sum]++;
    }
    return count;
}
int main() {
    int arr[] = {1,1,1};
    cout << countSubarrays(arr,3,2);
}
/*
Output
2
*/





🔟 Reverse Words in a String
Concise Notes
Reverse whole string
Reverse individual words
Time: O(n)



Code
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    string s = "hello world";
    reverse(s.begin(), s.end());

    int start=0;
    for(int i=0;i<=s.size();i++) {
        if(i==s.size() || s[i]==' ') {
            reverse(s.begin()+start, s.begin()+i);
            start = i+1;
        }
    }
    cout << s;
}
/*
Output
world hello
*/






1️⃣ Trapping Rain Water
Concise Notes
Precompute leftMax & rightMax
Water = min(leftMax, rightMax) − height
Time: O(n), Space: O(n)


Code
#include <iostream>
using namespace std;
int trap(int h[], int n) {
    int lMax[n], rMax[n];
    lMax[0] = h[0];
    for(int i=1;i<n;i++)
        lMax[i] = max(lMax[i-1], h[i]);

    rMax[n-1] = h[n-1];
    for(int i=n-2;i>=0;i--)
        rMax[i] = max(rMax[i+1], h[i]);

    int water = 0;
    for(int i=0;i<n;i++)
        water += min(lMax[i], rMax[i]) - h[i];

    return water;
}
int main() {
    int h[] = {3,0,0,2,0,4};
    cout << trap(h,6);
}
/*
Output
10

Dry Run
Left max : 3 3 3 3 3 4
Right max: 4 4 4 4 4 4
Water at index 1 = 3 - 0 = 3
Total = 10
*/



2️⃣ Maximum Sum Rectangle in 2D Matrix
Concise Notes
Apply Kadane’s algorithm on columns
Fix left & right column
Time: O(n³)


Code
#include <iostream>
#include <climits>
using namespace std;
int kadane(int arr[], int n) {
    int maxSum=arr[0], curr=arr[0];
    for(int i=1;i<n;i++) {
        curr = max(arr[i], curr+arr[i]);
        maxSum = max(maxSum, curr);
    }
    return maxSum;
}
int main() {
    int mat[4][5] = {
        {1,2,-1,-4,-20},
        {-8,-3,4,2,1},
        {3,8,10,1,3},
        {-4,-1,1,7,-6}
    };

    int maxSum = INT_MIN;

    for(int l=0;l<5;l++) {
        int temp[4]={0};
        for(int r=l;r<5;r++) {
            for(int i=0;i<4;i++)
                temp[i] += mat[i][r];

            maxSum = max(maxSum, kadane(temp,4));
        }
    }

    cout << maxSum;
}
/*
Output
29
*/



3️⃣ Count Inversions (Array)
Concise Notes
Inversion: i < j && arr[i] > arr[j]
Modified Merge Sort
Time: O(n log n)


Code
#include <iostream>
using namespace std;
int merge(int arr[], int l, int m, int r) {
    int i=l, j=m+1, k=0, temp[r-l+1], inv=0;

    while(i<=m && j<=r) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            inv += (m - i + 1);
        }
    }
    while(i<=m) temp[k++] = arr[i++];
    while(j<=r) temp[k++] = arr[j++];

    for(int i=0;i<k;i++)
        arr[l+i] = temp[i];

    return inv;
}
int mergeSort(int arr[], int l, int r) {
    if(l>=r) return 0;
    int m = (l+r)/2;
    return mergeSort(arr,l,m) +
           mergeSort(arr,m+1,r) +
           merge(arr,l,m,r);
}
int main() {
    int arr[] = {2,4,1,3,5};
    cout << mergeSort(arr,0,4);
}
/*
Output
3

Dry Run
(2,1), (4,1), (4,3)
*/



4️⃣ Longest Palindromic Substring
Concise Notes
Expand around center
Odd & even length
Time: O(n²)


Code
#include <iostream>
using namespace std;
string expand(string s, int l, int r) {
    while(l>=0 && r<s.size() && s[l]==s[r]) {
        l--; r++;
    }
    return s.substr(l+1, r-l-1);
}
int main() {
    string s = "babad";
    string res="";

    for(int i=0;i<s.size();i++) {
        string odd = expand(s,i,i);
        string even = expand(s,i,i+1);
        res = (odd.size()>res.size())?odd:res;
        res = (even.size()>res.size())?even:res;
    }

    cout << res;
}
/*
Output
bab
*/




5️⃣ Minimum Window Substring
Concise Notes
Sliding window + frequency count
One of the hardest string problems
Time: O(n)


Code
#include <iostream>
#include <unordered_map>
using namespace std;
string minWindow(string s, string t) {
    unordered_map<char,int> mp;
    for(char c:t) mp[c]++;

    int l=0, count=t.size(), minLen=INT_MAX, start=0;

    for(int r=0;r<s.size();r++) {
        if(mp[s[r]]-- > 0) count--;

        while(count==0) {
            if(r-l+1 < minLen) {
                minLen = r-l+1;
                start = l;
            }
            if(++mp[s[l++]] > 0) count++;
        }
    }
    return minLen==INT_MAX ? "" : s.substr(start,minLen);
}
int main() {
    cout << minWindow("ADOBECODEBANC", "ABC");
}
/*
Output
BANC
*/



6️⃣ Set Matrix Zeroes (In-Place)
Concise Notes
Use first row & column as markers
Avoid extra space
Time: O(nm)



Code
#include <iostream>
using namespace std;
int main() {
    int mat[3][3] = {{1,1,1},{1,0,1},{1,1,1}};
    bool row=false, col=false;

    for(int i=0;i<3;i++)
        if(mat[i][0]==0) col=true;

    for(int j=0;j<3;j++)
        if(mat[0][j]==0) row=true;

    for(int i=1;i<3;i++)
        for(int j=1;j<3;j++)
            if(mat[i][j]==0)
                mat[i][0]=mat[0][j]=0;

    for(int i=1;i<3;i++)
        for(int j=1;j<3;j++)
            if(mat[i][0]==0 || mat[0][j]==0)
                mat[i][j]=0;

    if(row)
        for(int j=0;j<3;j++) mat[0][j]=0;

    if(col)
        for(int i=0;i<3;i++) mat[i][0]=0;

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
/*
Output
1 0 1
0 0 0
1 0 1
*/




7️⃣ Longest Consecutive Sequence
Concise Notes
Use unordered_set
Start counting only if x-1 not present
Time: O(n)


Code
#include <iostream>
#include <unordered_set>
using namespace std;
int main() {
    int arr[] = {100,4,200,1,3,2};
    unordered_set<int> s(arr, arr+6);

    int longest=0;

    for(int x : s) {
        if(!s.count(x-1)) {
            int curr=x, len=1;
            while(s.count(curr+1)) {
                curr++;
                len++;
            }
            longest = max(longest, len);
        }
    }
    cout << longest;
}
/*
Output
4
*/





1️⃣ Subarrays With XOR = K
Concise Notes
Similar to prefix-sum, but with XOR
Property: prefXor ^ k = previous
Time O(n) | Space O(n)

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int countXor(int arr[], int n, int k) {
    unordered_map<int,int> mp;
    int xr = 0, count = 0;
    mp[0] = 1;

    for(int i=0;i<n;i++) {
        xr ^= arr[i];
        count += mp[xr ^ k];
        mp[xr]++;
    }
    return count;
}
int main() {
    int arr[] = {4,2,2,6,4};
    cout << countXor(arr,5,6);
}
/*
Output
4

Dry Run
Prefix XORs: 4,6,4,2,6
Matches when (xr ^ k) seen earlier
*/


2️⃣ K-th Smallest Element (QuickSelect)
Concise Notes
Based on QuickSort partition
Average O(n), Worst O(n²)
In-place

Code
#include <iostream>
using namespace std;
int partition(int arr[], int l, int r) {
    int pivot = arr[r], i = l;
    for(int j=l;j<r;j++)
        if(arr[j] <= pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[r]);
    return i;
}
int quickSelect(int arr[], int l, int r, int k) {
    int p = partition(arr,l,r);
    if(p == k-1) return arr[p];
    else if(p > k-1) return quickSelect(arr,l,p-1,k);
    else return quickSelect(arr,p+1,r,k);
}
int main() {
    int arr[] = {7,10,4,3,20,15};
    cout << quickSelect(arr,0,5,3);
}
/*
Output
7
*/


3️⃣ Largest Rectangle in Histogram
Concise Notes
Use Monotonic Stack
For each bar, find nearest smaller left & right
Time O(n)

Code
#include <iostream>
#include <stack>
using namespace std;
int main() {
    int h[] = {2,1,5,6,2,3};
    int n=6;
    stack<int> st;
    int maxArea = 0;

    for(int i=0;i<=n;i++) {
        int curr = (i==n ? 0 : h[i]);
        while(!st.empty() && curr < h[st.top()]) {
            int height = h[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    cout << maxArea;
}
/*
Output
10
*/


4️⃣ Longest Substring with At Most K Distinct Characters
Concise Notes
Sliding window + hashmap
Shrink window when distinct > k
Time O(n)

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    string s="eceba";
    int k=2;
    unordered_map<char,int> mp;
    int l=0, ans=0;

    for(int r=0;r<s.size();r++) {
        mp[s[r]]++;
        while(mp.size() > k) {
            if(--mp[s[l]] == 0)
                mp.erase(s[l]);
            l++;
        }
        ans = max(ans, r-l+1);
    }
    cout << ans;
}
/*
Output
3
*/


5️⃣ Merge Overlapping Intervals
Concise Notes
Sort by start time
Merge if overlap
Time O(n log n)

Code
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<pair<int,int>> v = {{1,3},{2,6},{8,10},{15,18}};
    sort(v.begin(), v.end());

    vector<pair<int,int>> res;
    for(auto p : v) {
        if(res.empty() || res.back().second < p.first)
            res.push_back(p);
        else
            res.back().second = max(res.back().second, p.second);
    }

    for(auto p : res)
        cout << "[" << p.first << "," << p.second << "] ";
}
/*
Output
[1,6] [8,10] [15,18]
*/



6️⃣ Spiral Matrix Traversal
Concise Notes
Maintain 4 boundaries
Print layer by layer
Time O(nm)

Code
#include <iostream>
using namespace std;
int main() {
    int mat[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    int top=0,bottom=2,left=0,right=2;

    while(top<=bottom && left<=right) {
        for(int i=left;i<=right;i++)
            cout<<mat[top][i]<<" ";
        top++;

        for(int i=top;i<=bottom;i++)
            cout<<mat[i][right]<<" ";
        right--;

        for(int i=right;i>=left;i--)
            cout<<mat[bottom][i]<<" ";
        bottom--;

        for(int i=bottom;i>=top;i--)
            cout<<mat[i][left]<<" ";
        left++;
    }
}
/*
Output
1 2 3 6 9 8 7 4 5
*/


7️⃣ Find Duplicate Number (Floyd’s Cycle)
Concise Notes
Treat array as linked list
No extra space
Time O(n)

Code
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,3,4,2,2};
    int slow=arr[0], fast=arr[0];

    do {
        slow = arr[slow];
        fast = arr[arr[fast]];
    } while(slow != fast);

    slow = arr[0];
    while(slow != fast) {
        slow = arr[slow];
        fast = arr[fast];
    }
    cout << slow;
}
/*
Output
2
*/



8️⃣ Word Pattern Matching
Concise Notes
One-to-one mapping
Use two hashmaps
Time O(n)

Code
#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;
int main() {
    string pattern="abba", s="dog cat cat dog";
    unordered_map<char,string> mp1;
    unordered_map<string,char> mp2;
    stringstream ss(s);
    string word;
    int i=0;

    while(ss >> word) {
        if(mp1.count(pattern[i]) && mp1[pattern[i]]!=word)
            { cout<<"No"; return 0; }
        if(mp2.count(word) && mp2[word]!=pattern[i])
            { cout<<"No"; return 0; }
        mp1[pattern[i]] = word;
        mp2[word] = pattern[i];
        i++;
    }
    cout<<"Yes";
}
/*
Output
Yes
*/




1️⃣ Count Submatrices With Sum = K (2D Prefix + Hash)
Concise Notes
Fix top & bottom rows
Convert 2D → 1D subarray sum
Apply prefix sum + hashmap
Time: O(n²m)

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int mat[3][3] = {{1,-1,0},{0,1,-1},{1,1,1}};
    int k = 0, count = 0;

    for(int top=0;top<3;top++) {
        int temp[3] = {0};
        for(int bottom=top;bottom<3;bottom++) {
            unordered_map<int,int> mp;
            mp[0] = 1;
            int sum = 0;

            for(int col=0;col<3;col++) {
                temp[col] += mat[bottom][col];
                sum += temp[col];
                count += mp[sum - k];
                mp[sum]++;
            }
        }
    }
    cout << count;
}
/*
Output
5

Dry Run
Compress rows → reduce to subarray sum = K
Hash map counts valid prefixes
*/



2️⃣ Sliding Window Maximum (Deque)
Concise Notes
Maintain decreasing deque
Front = max element
Time: O(n)

Code
#include <iostream>
#include <deque>
using namespace std;
int main() {
    int arr[] = {1,3,-1,-3,5,3,6,7};
    int k = 3, n = 8;
    deque<int> dq;

    for(int i=0;i<n;i++) {
        while(!dq.empty() && dq.front() <= i-k)
            dq.pop_front();
        while(!dq.empty() && arr[dq.back()] <= arr[i])
            dq.pop_back();

        dq.push_back(i);
        if(i >= k-1)
            cout << arr[dq.front()] << " ";
    }
}
/*
Output
3 3 5 5 6 7
*/



3️⃣ Smallest Subarray With Sum ≥ K
Concise Notes
Sliding window (positives only)
Shrink window greedily
Time: O(n)

Code
#include <iostream>
using namespace std;
int main() {
    int arr[] = {2,3,1,2,4,3};
    int k = 7, n = 6;
    int sum = 0, l = 0, ans = n+1;

    for(int r=0;r<n;r++) {
        sum += arr[r];
        while(sum >= k) {
            ans = min(ans, r-l+1);
            sum -= arr[l++];
        }
    }
    cout << (ans==n+1 ? 0 : ans);
}
/*
Output
2
*/



4️⃣ Lexicographically Smallest String After K Swaps
Concise Notes
Greedy swapping
Choose smallest char within k range
Time: O(n²)

Code
#include <iostream>
using namespace std;
int main() {
    string s = "4321";
    int k = 4, n = s.size();

    for(int i=0;i<n && k>0;i++) {
        char minChar = s[i];
        int pos = i;

        for(int j=i+1;j<n && j-i<=k;j++) {
            if(s[j] < minChar) {
                minChar = s[j];
                pos = j;
            }
        }

        for(int j=pos;j>i;j--) {
            swap(s[j], s[j-1]);
            k--;
        }
    }
    cout << s;
}
/*
Output
1342
*/



5️⃣ Count Distinct Elements in Every Window
Concise Notes
Sliding window + hashmap
Add right, remove left
Time: O(n)

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int arr[] = {1,2,1,3,4,2,3};
    int k = 4, n = 7;
    unordered_map<int,int> mp;

    for(int i=0;i<k;i++)
        mp[arr[i]]++;

    cout << mp.size() << " ";

    for(int i=k;i<n;i++) {
        if(--mp[arr[i-k]] == 0)
            mp.erase(arr[i-k]);
        mp[arr[i]]++;
        cout << mp.size() << " ";
    }
}
/*
Output
3 4 4 3
*/



6️⃣ Check If Array Can Be Sorted by Reversing One Subarray
Concise Notes
Find first decreasing index
Reverse segment
Verify sorted
Time: O(n)

Code
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int arr[] = {1,2,5,4,3,6};
    int n = 6, l=0, r=n-1;

    while(l<n-1 && arr[l]<=arr[l+1]) l++;
    while(r>0 && arr[r]>=arr[r-1]) r--;

    reverse(arr+l, arr+r+1);

    cout << (is_sorted(arr, arr+n) ? "Yes" : "No");
}
/*
Output
Yes
*/



7️⃣ String Compression (In-Place)
Concise Notes
Use two pointers
Write char + count
Time: O(n)

Code
#include <iostream>
using namespace std;
int main() {
    string s="aabccc";
    int idx=0;

    for(int i=0;i<s.size();) {
        char c=s[i];
        int cnt=0;

        while(i<s.size() && s[i]==c) {
            i++; cnt++;
        }
        s[idx++] = c;
        if(cnt>1)
            s[idx++] = cnt+'0';
    }
    s.resize(idx);
    cout << s;
}
/*
Output
a2bc3
*/



8️⃣ Find All Anagram Indices (Sliding Window)
Concise Notes
Fixed window size
Compare frequency arrays
Time: O(n)

Code
#include <iostream>
#include <vector>
using namespace std;
int main() {
    string s="cbaebabacd", p="abc";
    int fs[26]={0}, fp[26]={0};

    for(char c:p) fp[c-'a']++;

    for(int i=0;i<s.size();i++) {
        fs[s[i]-'a']++;
        if(i>=p.size())
            fs[s[i-p.size()]-'a']--;

        if(fs==fp)
            cout << i-p.size()+1 << " ";
    }
}
/*
Output
0 6
*/





1️⃣ Maximum Sum Circular Subarray
Concise Notes

Two cases:

Normal Kadane

Circular = totalSum − minimum subarray

All-negative array is a trap

Time O(n)

Code
#include <iostream>
using namespace std;

int kadane(int arr[], int n) {
    int curr = arr[0], best = arr[0];
    for(int i=1;i<n;i++) {
        curr = max(arr[i], curr + arr[i]);
        best = max(best, curr);
    }
    return best;
}

int main() {
    int arr[] = {5,-3,5};
    int n = 3;

    int maxNormal = kadane(arr,n);
    int totalSum = 0;

    for(int i=0;i<n;i++) {
        totalSum += arr[i];
        arr[i] = -arr[i];
    }

    int maxCircular = totalSum + kadane(arr,n);
    cout << max(maxNormal, maxCircular);
}

Output
10

Dry Run
Normal max = 7
Circular = 10
Answer = 10

🔹 2️⃣ Shortest Unsorted Continuous Subarray
Concise Notes

Find first disorder from left & right

Track min & max inside range

Time O(n)

Code
#include <iostream>
using namespace std;

int main() {
    int arr[] = {2,6,4,8,10,9,15};
    int n=7;
    int l=0,r=n-1;

    while(l<n-1 && arr[l]<=arr[l+1]) l++;
    while(r>0 && arr[r]>=arr[r-1]) r--;

    int mn=arr[l], mx=arr[l];
    for(int i=l;i<=r;i++) {
        mn=min(mn,arr[i]);
        mx=max(mx,arr[i]);
    }

    while(l>0 && arr[l-1]>mn) l--;
    while(r<n-1 && arr[r+1]<mx) r++;

    cout << r-l+1;
}

Output
5

🔹 3️⃣ Find Peak Element (Binary Search)
Concise Notes

Peak: element greater than neighbors

Binary search works due to slope

Time O(log n)

Code
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1,2,3,1};
    int l=0,r=3;

    while(l<r) {
        int mid=(l+r)/2;
        if(arr[mid] < arr[mid+1])
            l = mid+1;
        else
            r = mid;
    }
    cout << l;
}
/*
Output
2
*/



4️⃣ Minimum Number of Platforms (Tricky Sorting)
Concise Notes
Sort arrival & departure separately
Two pointers
Time O(n log n)

Code
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[] = {900,940,950,1100,1500,1800};
    int dep[] = {910,1200,1120,1130,1900,2000};
    int n=6;

    sort(arr,arr+n);
    sort(dep,dep+n);

    int i=1,j=0, plat=1, res=1;

    while(i<n && j<n) {
        if(arr[i]<=dep[j]) {
            plat++;
            i++;
        } else {
            plat--;
            j++;
        }
        res = max(res, plat);
    }
    cout << res;
}
/*
Output
3
*/



5️⃣ Minimum Swaps to Group All 1s Together
Concise Notes
Sliding window of size = count(1s)
Find window with max 1s
Time O(n)

Code
#include <iostream>
using namespace std;
int main() {
    int arr[] = {1,0,1,0,1};
    int n=5, ones=0;

    for(int x:arr) if(x==1) ones++;

    int curr=0;
    for(int i=0;i<ones;i++) curr+=arr[i];

    int maxOnes = curr;

    for(int i=ones;i<n;i++) {
        curr += arr[i] - arr[i-ones];
        maxOnes = max(maxOnes, curr);
    }
    cout << ones - maxOnes;
}
/*
Output
1
*/




6️⃣ Rearrange Array Alternately (Positive-Negative)
Concise Notes
Maintain order
Extra array approach
Time O(n)

Code
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int arr[] = {1,-2,3,-4,-1,4};
    vector<int> pos, neg;

    for(int x:arr)
        (x>=0 ? pos : neg).push_back(x);

    int i=0,p=0,n=0;
    while(p<pos.size() && n<neg.size()) {
        arr[i++] = pos[p++];
        arr[i++] = neg[n++];
    }

    for(int x:arr) cout << x << " ";
}
/*
Output
1 -2 3 -4 4 -1
*/



7️⃣ Count Nice Subarrays (Exactly K Odd Numbers)
Concise Notes
Convert odd → 1, even → 0
Count subarrays with sum = K
Prefix sum trick
Time O(n)

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int arr[] = {1,1,2,1,1};
    int k=3, sum=0, count=0;
    unordered_map<int,int> mp;
    mp[0]=1;

    for(int i=0;i<5;i++) {
        sum += arr[i]%2;
        count += mp[sum-k];
        mp[sum]++;
    }
    cout << count;
}
/*
Output
2
*/




8️⃣ Longest Common Prefix (Strings)
Concise Notes
Compare char by char
Stop at mismatch
Time O(n*m)

Code
#include <iostream>
using namespace std;
int main() {
    string strs[] = {"flower","flow","flight"};
    string prefix = strs[0];

    for(int i=1;i<3;i++) {
        int j=0;
        while(j<prefix.size() && j<strs[i].size()
              && prefix[j]==strs[i][j])
            j++;
        prefix = prefix.substr(0,j);
    }
    cout << prefix;
}
/*
Output
fl
*/










