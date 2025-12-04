1. STL / C++ Advanced Questions

Map vs Unordered_Map: Explain time complexities in detail, including worst-case scenarios.

Stable vs Unstable algorithms in STL: How sort differs from stable_sort.

Iterator invalidation: When do iterators get invalidated for vector, list, map, unordered_map?

Emplace vs Insert: Why emplace can be faster than insert in certain cases.

Lambda captures & mutable lambdas: Differences, pitfalls in multi-threading.

Custom comparators in STL containers: Implement set or priority_queue with a complex comparator.

Merge two maps/unordered_maps efficiently: Without iterating through all keys manually.

Find top-K elements using STL efficiently: Compare nth_element vs priority_queue.

2. Algorithm / Data Structure Tricky Questions

Sliding Window + Hashing: Longest substring with at most K distinct characters.

Two-pointer tricks: Move zeros to end, partition array with custom predicate (stable).

Prefix sum tricks: Subarray sum equals K in O(n).

In-place algorithms: Reverse words in a string, rotate array without extra space.

Linked list manipulations: Detect cycle, find cycle length, flatten multilevel lists.

Binary search variants: Find peak element, first/last occurrence, square root in O(log n).

Matrix problems: Rotate 2D matrix 90 degrees in place, spiral order, submatrix sum queries.

Graph algorithms: Detect cycle in directed graph using DFS, topological sort, union-find optimizations.

3. Tricky Logical / Coding Puzzles

Swap two numbers without using a temporary variable (classic, but can extend with constraints).

Move all negative numbers to the front while maintaining relative order (stable).

Count occurrences of each character in a string without extra maps (bit manipulation or array trick).

Given an array, find the first repeating element in O(n) using minimal extra space.

Maximum sum subarray of size at least K in O(n).

Interleaving two arrays like {1,2,3} and {7,8,9} → {7,1,8,2,9,3}.

Find majority element (> n/2 times) in O(n) and O(1) space (Boyer–Moore).

Rearrange an array in max-min form in O(n) without extra space.

4. Bit Manipulation & Math Tricks

Check if a number is a power of 2, 4, 8 using bit tricks.

Count set bits in O(log n) or O(1) using lookup table.

Find missing number in array of 1..n using XOR.

Swap even and odd bits in a number.

Multiply/divide by powers of 2 using bit shifts.

Find the only non-repeating element where every other element repeats k times.

5. System Design / Conceptual Tricky Questions

Difference between stack, heap, and static memory in detail.

Move semantics in C++11/14/17: When are objects copied vs moved?

Explain inline variables, constexpr, and consteval differences.

Multi-threading pitfalls: race conditions, deadlocks, and avoiding iterator invalidation.

Explain why unordered_map might perform worse than map in certain scenarios.











1. Frequency Counting in Array (Map/Unordered_map)

Input: arr = [1,2,2,3,1,4]
Output: 1:2 2:2 3:1 4:1

Hint: Use unordered_map to count frequencies.

Optimal Solution (C++ STL):

unordered_map<int,int> freq;
for(int x : arr) freq[x]++;
for(auto &[k,v]: freq) cout << k << ":" << v << " ";

2. First Unique Character in String

Input: "leetcode"
Output: 0 (index of 'l')

Hint: Use unordered_map<char,int> to count, then traverse string to find first with count 1.

3. Move Zeros to End (Stable)

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]

Hint: Use stable_partition or two-pointer approach.

4. Move Negatives to Front (Stable)

Input: [1,-2,3,-4,5]
Output: [-2,-4,1,3,5]

Hint: stable_partition with predicate x<0.

5. Top K Frequent Elements

Input: [1,1,1,2,2,3], K=2
Output: [1,2]

Hint: Use unordered_map + priority_queue (min-heap of size K).

6. Reverse Words in String

Input: "the sky is blue"
Output: "blue is sky the"

Hint: Split words, reverse vector, join.

7. Longest Substring Without Repeating Characters

Input: "abcabcbb"
Output: 3

Hint: Sliding window + unordered_set or map.

8. Find Missing Number in 1..n

Input: [1,2,4,5,6]
Output: 3

Hint: Use sum formula or XOR trick.

9. Majority Element (> n/2 times)

Input: [3,3,4,2,3]
Output: 3

Hint: Boyer–Moore Voting Algorithm (O(n), O(1) space).

10. Rearrange Array Max-Min Form

Input: [1,2,3,4,5,6]
Output: [6,1,5,2,4,3]

Hint: Two-pointer approach from ends.

11. Swap Adjacent Elements in Pairs

Input: [1,2,3,4,5,6]
Output: [2,1,4,3,6,5]

Hint: Loop with step 2, swap i and i+1.

12. Interleave Arrays

Input: [1,2,3] and [7,8,9]
Output: [7,1,8,2,9,3]

13. Count Subarrays with Sum = K

Input: [1,2,3], K=3
Output: 2

Hint: Prefix sum + unordered_map storing previous sums.

14. Detect Cycle in Linked List

Input: 1->2->3->4->2...
Output: true

Hint: Use Floyds Tortoise and Hare.

15. Reverse a Linked List in Groups of K

Input: 1->2->3->4->5, K=2
Output: 2->1->4->3->5

Hint: Recursive or iterative reversal.

16. Find First Repeating Element

Input: [10,5,3,4,3,5,6]
Output: 5

Hint: unordered_map to track first index of repetition.

17. Rotate Array Right by K Steps (In-place)

Input: [1,2,3,4,5,6,7], K=3
Output: [5,6,7,1,2,3,4]

Hint: Reverse whole array, reverse first K, then remaining.

18. Merge Two Sorted Arrays (In-place if possible)

Input: [1,3,5], [2,4,6]
Output: [1,2,3,4,5,6]

Hint: Two-pointer approach.

19. Count Distinct Elements in Every Window of Size K

Input: [1,2,1,3,4,2,3], K=4
Output: [3,4,4,3]

Hint: Sliding window + unordered_map.

20. Maximum Subarray Sum (Kadane’s Algorithm)

Input: [-2,1,-3,4,-1,2,1,-5,4]
Output: 6

21. Longest Palindromic Substring

Input: "babad"
Output: "bab" or "aba"

Hint: Expand around center.

22. Custom Comparator in Priority Queue

Input: [1,2,3,4,5]
Output: Max heap by even first then value.

Hint: Lambda in priority_queue<int, vector<int>, decltype(cmp)>.

23. Count Set Bits in Integer

Input: 9
Output: 2

Hint: Brian Kernighan’s algorithm.

24. Swap Two Numbers Without Temp Variable

Input: a=5, b=3
Output: a=3, b=5

Hint: Use XOR or arithmetic trick.

25. Power of 2 Check

Input: 16
Output: true

Hint: n & (n-1) == 0.

26. Largest Rectangle in Histogram (Stack)

Input: [2,1,5,6,2,3]
Output: 10

Hint: Use monotonic stack.

27. Sliding Window Maximum

Input: [1,3,-1,-3,5,3,6,7], K=3
Output: [3,3,5,5,6,7]

Hint: deque storing indices.

28. Check Unique Frequencies

Input: [1,2,2,1,1,3]
Output: true

Hint: Count frequencies and check uniqueness using unordered_set.

29. Smallest Window in String Containing All Characters of Another String

Input: S="ADOBECODEBANC", T="ABC"
Output: "BANC"

Hint: Sliding window + hash map.

30. Longest Consecutive Sequence

Input: [100,4,200,1,3,2]
Output: 4 (1,2,3,4)

Hint: Use unordered_set and check sequence starts.















#include <bits/stdc++.h>
using namespace std;

// 1. Frequency Counting in Array
void freqCountArray() {
    vector<int> arr = {1,2,2,3,1,4};
    unordered_map<int,int> freq;
    for(int x : arr) freq[x]++;
    cout << "Frequency: ";
    for(auto &[k,v]: freq) cout << k << ":" << v << " ";
    cout << endl;
}

// 2. First Unique Character in String
void firstUniqueChar() {
    string s = "leetcode";
    unordered_map<char,int> freq;
    for(char c : s) freq[c]++;
    for(int i=0;i<s.size();i++){
        if(freq[s[i]]==1){ cout << "First Unique Index: " << i << endl; break;}
    }
}

// 3. Move Zeros to End (Stable)
void moveZeros() {
    vector<int> nums = {0,1,0,3,12};
    stable_partition(nums.begin(), nums.end(), [](int x){return x!=0;});
    cout << "Move Zeros: "; for(int x: nums) cout<<x<<" "; cout<<endl;
}

// 4. Move Negatives to Front (Stable)
void moveNegatives() {
    vector<int> nums = {1,-2,3,-4,5};
    stable_partition(nums.begin(), nums.end(), [](int x){return x<0;});
    cout << "Negatives Front: "; for(int x: nums) cout<<x<<" "; cout<<endl;
}

// 5. Top K Frequent Elements
void topKFrequent() {
    vector<int> nums = {1,1,1,2,2,3}; int k=2;
    unordered_map<int,int> freq;
    for(int x: nums) freq[x]++;
    priority_queue<pair<int,int>> pq;
    for(auto &[num,f]: freq) pq.push({f,num});
    cout << "Top K Frequent: ";
    for(int i=0;i<k;i++){ cout<<pq.top().second<<" "; pq.pop();}
    cout<<endl;
}

// 6. Reverse Words in String
void reverseWords() {
    string s = "the sky is blue"; 
    stringstream ss(s); string word; vector<string> words;
    while(ss>>word) words.push_back(word);
    reverse(words.begin(), words.end());
    cout << "Reversed Words: ";
    for(int i=0;i<words.size();i++){ cout<<words[i]; if(i<words.size()-1) cout<<" ";} cout<<endl;
}

// 7. Longest Substring Without Repeating Characters
void longestUniqueSubstring() {
    string s = "abcabcbb";
    unordered_map<char,int> lastIndex;
    int start=0,maxLen=0;
    for(int i=0;i<s.size();i++){
        if(lastIndex.count(s[i]) && lastIndex[s[i]]>=start) start=lastIndex[s[i]]+1;
        maxLen = max(maxLen,i-start+1);
        lastIndex[s[i]] = i;
    }
    cout << "Longest Unique Substring Length: " << maxLen << endl;
}

// 8. Find Missing Number 1..n
void missingNumber() {
    vector<int> nums = {1,2,4,5,6};
    int n=nums.size()+1, totalSum = n*(n+1)/2, sum=accumulate(nums.begin(), nums.end(), 0);
    cout << "Missing Number: " << totalSum - sum << endl;
}

// 9. Majority Element
void majorityElement() {
    vector<int> nums = {3,3,4,2,3};
    int count=0, candidate=0;
    for(int num: nums){
        if(count==0) candidate=num;
        count += (num==candidate)?1:-1;
    }
    cout << "Majority Element: " << candidate << endl;
}

// 10. Rearrange Array Max-Min Form
void rearrangeMaxMin() {
    vector<int> nums = {1,2,3,4,5,6};
    vector<int> res; int l=0,r=nums.size()-1;
    while(l<=r){ if(l!=r) {res.push_back(nums[r--]); res.push_back(nums[l++]);} else res.push_back(nums[l++]);}
    cout << "Max-Min: "; for(int x: res) cout<<x<<" "; cout<<endl;
}

// 11. Swap Adjacent Elements in Pairs
void swapAdjacent() {
    vector<int> nums = {1,2,3,4,5,6};
    for(int i=0;i+1<nums.size();i+=2) swap(nums[i],nums[i+1]);
    cout << "Swap Adjacent: "; for(int x: nums) cout<<x<<" "; cout<<endl;
}

// 12. Interleave Arrays
void interleaveArrays() {
    vector<int> a = {1,2,3}, b = {7,8,9}, res;
    for(int i=0;i<a.size();i++){ res.push_back(b[i]); res.push_back(a[i]);}
    cout << "Interleaved: "; for(int x: res) cout<<x<<" "; cout<<endl;
}

// 13. Count Subarrays with Sum = K
void subarraySumK() {
    vector<int> nums = {1,2,3}; int K=3;
    unordered_map<int,int> prefix{{0,1}}; int sum=0,count=0;
    for(int x: nums){ sum+=x; if(prefix.count(sum-K)) count+=prefix[sum-K]; prefix[sum]++; }
    cout << "Subarrays with Sum=K: " << count << endl;
}

// 14. Detect Cycle in Linked List
struct ListNode{int val; ListNode* next; ListNode(int x):val(x),next(NULL){}};
bool hasCycle(ListNode* head){
    ListNode *slow=head,*fast=head;
    while(fast && fast->next){ slow=slow->next; fast=fast->next->next; if(slow==fast) return true;}
    return false;
}

// 15. Reverse Linked List in Groups of K
ListNode* reverseKGroup(ListNode* head,int k){
    ListNode *cur=head; int count=0;
    while(cur && count!=k){ cur=cur->next; count++; }
    if(count<k) return head;
    ListNode *prev=NULL,*curr=head,*next;
    for(int i=0;i<k;i++){ next=curr->next; curr->next=prev; prev=curr; curr=next;}
    head->next=reverseKGroup(curr,k);
    return prev;
}

// 16. First Repeating Element
void firstRepeating() {
    vector<int> nums = {10,5,3,4,3,5,6};
    unordered_map<int,int> freq;
    for(int x: nums) freq[x]++;
    for(int x: nums){ if(freq[x]>1){ cout << "First Repeating: " << x << endl; break;}}
}

// 17. Rotate Array Right by K Steps
void rotateArray() {
    vector<int> nums = {1,2,3,4,5,6,7}; int k=3;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin()+k);
    reverse(nums.begin()+k, nums.end());
    cout << "Rotated Array: "; for(int x: nums) cout<<x<<" "; cout<<endl;
}

// 18. Merge Two Sorted Arrays
void mergeSorted() {
    vector<int> a={1,3,5}, b={2,4,6};
    vector<int> res(a.size()+b.size()); merge(a.begin(),a.end(),b.begin(),b.end(),res.begin());
    cout << "Merged: "; for(int x: res) cout<<x<<" "; cout<<endl;
}

// 19. Distinct Elements in Every Window of Size K
void distinctInWindow() {
    vector<int> nums={1,2,1,3,4,2,3}; int k=4;
    unordered_map<int,int> freq; vector<int> res;
    for(int i=0;i<nums.size();i++){
        freq[nums[i]]++;
        if(i>=k) { if(--freq[nums[i-k]]==0) freq.erase(nums[i-k]); }
        if(i>=k-1) res.push_back(freq.size());
    }
    cout << "Distinct in Window: "; for(int x: res) cout<<x<<" "; cout<<endl;
}

// 20. Maximum Subarray Sum (Kadane)
void maxSubarraySum() {
    vector<int> nums={-2,1,-3,4,-1,2,1,-5,4};
    int maxSoFar=nums[0], maxEnding=nums[0];
    for(int i=1;i<nums.size();i++){ maxEnding=max(nums[i], maxEnding+nums[i]); maxSoFar=max(maxSoFar,maxEnding);}
    cout << "Max Subarray Sum: " << maxSoFar << endl;
}

// 21. Longest Palindromic Substring
void longestPalindrome() {
    string s="babad", res="";
    int maxLen=0;
    for(int i=0;i<s.size();i++){
        // Odd length
        int l=i,r=i; while(l>=0 && r<s.size() && s[l]==s[r]) l--, r++;
        if(r-l-1>maxLen){ maxLen=r-l-1; res=s.substr(l+1,r-l-1);}
        // Even length
        l=i,r=i+1; while(l>=0 && r<s.size() && s[l]==s[r]) l--, r++;
        if(r-l-1>maxLen){ maxLen=r-l-1; res=s.substr(l+1,r-l-1);}
    }
    cout << "Longest Palindrome: " << res << endl;
}

// 22. Custom Comparator in Priority Queue
void customPQ() {
    vector<int> nums={1,2,3,4,5};
    auto cmp = [](int a,int b){ return (a%2==0 && b%2!=0) ? false : (a%2!=0 && b%2==0) ? true : a>b;};
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    for(int x: nums) pq.push(x);
    cout << "Custom PQ: "; while(!pq.empty()){ cout<<pq.top()<<" "; pq.pop();} cout<<endl;
}

// 23. Count Set Bits
void countSetBits() {
    int n=9, count=0;
    while(n){ n&=(n-1); count++; }
    cout << "Set Bits: " << count << endl;
}

// 24. Swap Two Numbers Without Temp
void swapWithoutTemp() {
    int a=5,b=3; a=a^b; b=a^b; a=a^b;
    cout << "Swapped: a="<<a<<" b="<<b<<endl;
}

// 25. Power of 2 Check
void powerOfTwo() {
    int n=16;
    cout << n << " is Power of 2? " << ((n>0 && (n&(n-1))==0)?"Yes":"No") << endl;
}

// 26. Largest Rectangle in Histogram (Monotonic Stack)
void largestRectangle() {
    vector<int> h={2,1,5,6,2,3}; stack<int> st; int maxArea=0,hsize=h.size();
    for(int i=0;i<=hsize;i++){
        int cur=i==hsize?0:h[i];
        while(!st.empty() && h[st.top()]>=cur){
            int height=h[st.top()]; st.pop();
            int width=st.empty()?i:i-st.top()-1;
            maxArea=max(maxArea,height*width);
        }
        st.push(i);
    }
    cout << "Largest Rectangle: " << maxArea << endl;
}

// 27. Sliding Window Maximum
void slidingWindowMax() {
    vector<int> nums={1,3,-1,-3,5,3,6,7}; int k=3;
    deque<int> dq; vector<int> res;
    for(int i=0;i<nums.size();i++){
        while(!dq.empty() && dq.front()<=i-k) dq.pop_front();
        while(!dq.empty() && nums[dq.back()]<nums[i]) dq.pop_back();
        dq.push_back(i);
        if(i>=k-1) res.push_back(nums[dq.front()]);
    }
    cout << "Sliding Window Max: "; for(int x: res) cout<<x<<" "; cout<<endl;
}

// 28. Check Unique Frequencies
void uniqueFrequencies() {
    vector<int> nums={1,2,2,1,1,3};
    unordered_map<int,int> freq; for(int x: nums) freq[x]++;
    unordered_set<int> s; bool unique=true;
    for(auto &[k,v]: freq){ if(s.count(v)){ unique=false; break;} s.insert(v);}
    cout << "Unique Frequencies? " << (unique?"Yes":"No") << endl;
}

// 29. Smallest Window Containing All Characters
void minWindowSubstring() {
    string S="ADOBECODEBANC", T="ABC"; unordered_map<char,int> need, window;
    for(char c:T) need[c]++;
    int left=0,right=0,valid=0,start=0,len=INT_MAX;
    while(right<S.size()){
        char c=S[right]; right++;
        if(need.count(c)){ window[c]++; if(window[c]==need[c]) valid++; }
        while(valid==need.size()){
            if(right-left<len){ start=left; len=right-left; }
            char d=S[left]; left++;
            if(need.count(d)){ if(window[d]==need[d]) valid--; window[d]--; }
        }
    }
    cout << "Min Window: " << (len==INT_MAX?"":S.substr(start,len)) << endl;
}

// 30. Longest Consecutive Sequence
void longestConsecutive() {
    vector<int> nums={100,4,200,1,3,2};
    unordered_set<int> s(nums.begin(), nums.end()); int maxLen=0;
    for(int num: nums){
        if(!s.count(num-1)){
            int curNum=num,len=1;
            while(s.count(curNum+1)){ curNum++; len++; }
            maxLen=max(maxLen,len);
        }
    }
    cout << "Longest Consecutive Sequence: " << maxLen << endl;
}

int main(){
    freqCountArray();
    firstUniqueChar();
    moveZeros();
    moveNegatives();
    topKFrequent();
    reverseWords();
    longestUniqueSubstring();
    missingNumber();
    majorityElement();
    rearrangeMaxMin();
    swapAdjacent();
    interleaveArrays();
    subarraySumK();
    // Linked List cycle/reversal requires setup
    firstRepeating();
    rotateArray();
    mergeSorted();
    distinctInWindow();
    maxSubarraySum();
    longestPalindrome();
    customPQ();
    countSetBits();
    swapWithoutTemp();
    powerOfTwo();
    largestRectangle();
    slidingWindowMax();
    uniqueFrequencies();
    minWindowSubstring();
    longestConsecutive();
    return 0;
}

/*
Output: 
Frequency: 4:1 3:1 2:2 1:2 
First Unique Index: 0
Move Zeros: 1 3 12 0 0 
Negatives Front: -2 -4 1 3 5 
Top K Frequent: 1 2 
Reversed Words: blue is sky the
Longest Unique Substring Length: 3
Missing Number: 3
Majority Element: 3
Max-Min: 6 1 5 2 4 3 
Swap Adjacent: 2 1 4 3 6 5 
Interleaved: 7 1 8 2 9 3 
Subarrays with Sum=K: 2
First Repeating: 5
Rotated Array: 5 6 7 1 2 3 4 
Merged: 1 2 3 4 5 6 
Distinct in Window: 3 4 4 3 
Max Subarray Sum: 6
Longest Palindrome: bab
Custom PQ: 2 4 1 3 5 
Set Bits: 2
Swapped: a=3 b=5
16 is Power of 2? Yes
Largest Rectangle: 10
Sliding Window Max: 3 3 5 5 6 7 
Unique Frequencies? Yes
Min Window: BANC
Longest Consecutive Sequence: 4
*/