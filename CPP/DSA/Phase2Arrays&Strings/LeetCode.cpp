1️⃣ Trapping Rain Water (LC 42)
Idea

Two pointers + maxLeft / maxRight

Trap

❌ Prefix/suffix arrays waste space
❌ Wrong pointer movement

Code
#include <iostream>
using namespace std;

int main() {
    int a[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int n=12, l=0, r=n-1, lm=0, rm=0, ans=0;

    while(l<r){
        if(a[l]<a[r]){
            lm=max(lm,a[l]);
            ans+=lm-a[l++];
        } else {
            rm=max(rm,a[r]);
            ans+=rm-a[r--];
        }
    }
    cout<<ans;
}

Output
6

2️⃣ Largest Rectangle in Histogram (LC 84)
Idea

Monotonic increasing stack

Code
#include <iostream>
#include <stack>
using namespace std;

int main() {
    int h[] = {2,1,5,6,2,3};
    int n=6;
    stack<int> st;
    int ans=0;

    for(int i=0;i<=n;i++){
        int cur = (i==n?0:h[i]);
        while(!st.empty() && cur<h[st.top()]){
            int ht=h[st.top()]; st.pop();
            int w = st.empty()? i : i-st.top()-1;
            ans=max(ans,ht*w);
        }
        st.push(i);
    }
    cout<<ans;
}

Output
10





3️⃣ Sliding Window Maximum (LC 239)
Idea
Deque stores useful indices

Code
#include <iostream>
#include <deque>
using namespace std;
int main() {
    int a[]={1,3,-1,-3,5,3,6,7};
    int n=8,k=3;
    deque<int> dq;

    for(int i=0;i<n;i++){
        if(!dq.empty() && dq.front()==i-k) dq.pop_front();
        while(!dq.empty() && a[dq.back()]<a[i]) dq.pop_back();
        dq.push_back(i);
        if(i>=k-1) cout<<a[dq.front()]<<" ";
    }
}
/*
Output
3 3 5 5 6 7
*/



4️⃣ Maximum Product Subarray (LC 152)
Trap
Negative flips min ↔ max

Code
#include <iostream>
using namespace std;
int main() {
    int a[]={2,3,-2,4};
    int n=4;
    int mx=a[0], mn=a[0], ans=a[0];

    for(int i=1;i<n;i++){
        if(a[i]<0) swap(mx,mn);
        mx=max(a[i],mx*a[i]);
        mn=min(a[i],mn*a[i]);
        ans=max(ans,mx);
    }
    cout<<ans;
}
/*
Output
6
*/




5️⃣ Median of Two Sorted Arrays (LC 4)
Idea
Binary search on smaller array

Code
#include <iostream>
#include <climits>
using namespace std;
int main(){
    int A[]={1,3}, B[]={2};
    int m=2,n=1;
    if(m>n) return main();

    int l=0,r=m;
    while(l<=r){
        int cut1=(l+r)/2;
        int cut2=(m+n+1)/2-cut1;

        int l1=cut1?A[cut1-1]:INT_MIN;
        int l2=cut2?B[cut2-1]:INT_MIN;
        int r1=cut1<m?A[cut1]:INT_MAX;
        int r2=cut2<n?B[cut2]:INT_MAX;

        if(l1<=r2 && l2<=r1){
            cout<<max(l1,l2);
            return 0;
        } else if(l1>r2) r=cut1-1;
        else l=cut1+1;
    }
}
/*
Output
2
*/



6️⃣ Subarray Sum Equals K (LC 560)
Idea
Prefix sum + hashmap

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int a[]={1,1,1};
    int n=3,k=2,sum=0,ans=0;
    unordered_map<int,int> mp;
    mp[0]=1;

    for(int i=0;i<n;i++){
        sum+=a[i];
        ans+=mp[sum-k];
        mp[sum]++;
    }
    cout<<ans;
}
/*
Output
2
*/




7️⃣ Longest Consecutive Sequence (LC 128)
Idea
HashSet start detection

Code
#include <iostream>
#include <unordered_set>
using namespace std;
int main(){
    int a[]={100,4,200,1,3,2};
    unordered_set<int> s(a,a+6);
    int ans=0;

    for(int x:s){
        if(!s.count(x-1)){
            int len=1;
            while(s.count(x+len)) len++;
            ans=max(ans,len);
        }
    }
    cout<<ans;
}
/*
Output
4
*/




8️⃣ Minimum Window Substring (LC 76)
Trap
Valid count logic

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main(){
    string s="ADOBECODEBANC", t="ABC";
    unordered_map<char,int> need;
    for(char c:t) need[c]++;

    int l=0,count=t.size(),start=0,len=1e9;
    for(int r=0;r<s.size();r++){
        if(need[s[r]]-- > 0) count--;
        while(count==0){
            if(r-l+1<len) len=r-l+1,start=l;
            if(++need[s[l++]]>0) count++;
        }
    }
    cout<<s.substr(start,len);
}
/*
Output
BANC
*/





9️⃣ Container With Most Water (LC 11)
Code
#include <iostream>
using namespace std;
int main(){
    int h[]={1,8,6,2,5,4,8,3,7};
    int l=0,r=8,ans=0;
    while(l<r){
        ans=max(ans,min(h[l],h[r])*(r-l));
        if(h[l]<h[r]) l++;
        else r--;
    }
    cout<<ans;
}
/*
Output
49
*/





🔟 First Missing Positive (LC 41)
Code
#include <iostream>
using namespace std;
int main(){
    int a[]={3,4,-1,1};
    int n=4;
    for(int i=0;i<n;i++)
        while(a[i]>=1 && a[i]<=n && a[a[i]-1]!=a[i])
            swap(a[i],a[a[i]-1]);

    for(int i=0;i<n;i++)
        if(a[i]!=i+1){
            cout<<i+1;
            return 0;
        }
    cout<<n+1;
}
/*
Output
2
*/



1️⃣ Count of Range Sum (LC 327) — HARD
Idea
Prefix sum + modified merge sort

Code
#include <iostream>
#include <vector>
using namespace std;
int mergeCount(vector<long long>& pre, int l, int r, int low, int high) {
    if(r-l<=1) return 0;
    int m=(l+r)/2;
    int cnt=mergeCount(pre,l,m,low,high)+mergeCount(pre,m,r,low,high);

    int i=m,j=m;
    for(int left=l;left<m;left++){
        while(i<r && pre[i]-pre[left]<low) i++;
        while(j<r && pre[j]-pre[left]<=high) j++;
        cnt+=j-i;
    }
    inplace_merge(pre.begin()+l,pre.begin()+m,pre.begin()+r);
    return cnt;
}
int main() {
    vector<int> nums={-2,5,-1};
    int lower=-2, upper=2;
    vector<long long> pre(nums.size()+1,0);
    for(int i=0;i<nums.size();i++)
        pre[i+1]=pre[i]+nums[i];

    cout<<mergeCount(pre,0,pre.size(),lower,upper);
}
/* 
Output
3
*/



2️⃣ Maximal Rectangle (LC 85)
Idea
Histogram per row + stack

Code
#include <iostream>
#include <stack>
using namespace std;
int largest(int h[], int n) {
    stack<int> st;
    int ans=0;
    for(int i=0;i<=n;i++){
        int cur=(i==n?0:h[i]);
        while(!st.empty() && cur<h[st.top()]){
            int ht=h[st.top()]; st.pop();
            int w=st.empty()?i:i-st.top()-1;
            ans=max(ans,ht*w);
        }
        st.push(i);
    }
    return ans;
}
int main(){
    char m[4][5]={{'1','0','1','0','0'},
                 {'1','0','1','1','1'},
                 {'1','1','1','1','1'},
                 {'1','0','0','1','0'}};
    int h[5]={0};
    int ans=0;

    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++)
            h[j]=(m[i][j]=='1')?h[j]+1:0;
        ans=max(ans,largest(h,5));
    }
    cout<<ans;
}
/* 
Output
6
*/





3️⃣ Shortest Subarray with Sum ≥ K (LC 862)
Idea
Prefix sum + monotonic deque

Code
#include <iostream>
#include <deque>
using namespace std;
int main(){
    int a[]={2,-1,2};
    int n=3,k=3;
    long long pre[4]={0};
    for(int i=0;i<n;i++) pre[i+1]=pre[i]+a[i];

    deque<int> dq;
    int ans=1e9;
    for(int i=0;i<=n;i++){
        while(!dq.empty() && pre[i]-pre[dq.front()]>=k){
            ans=min(ans,i-dq.front());
            dq.pop_front();
        }
        while(!dq.empty() && pre[i]<=pre[dq.back()])
            dq.pop_back();
        dq.push_back(i);
    }
    cout<<(ans==1e9?-1:ans);
}
/* 
Output
3
*/



4️⃣ Split Array Largest Sum (LC 410)
Idea
Binary search on answer

Code
#include <iostream>
using namespace std;
bool can(int a[], int n, int k, int mx){
    int cnt=1,sum=0;
    for(int i=0;i<n;i++){
        if(sum+a[i]>mx){
            cnt++; sum=0;
        }
        sum+=a[i];
    }
    return cnt<=k;
}
int main(){
    int a[]={7,2,5,10,8};
    int n=5,k=2;
    int l=10,r=32,ans=0;

    while(l<=r){
        int m=(l+r)/2;
        if(can(a,n,k,m)){
            ans=m; r=m-1;
        } else l=m+1;
    }
    cout<<ans;
}
/* 
Output
18
*/




5️⃣ Subarrays with K Different Integers (LC 992)
Idea
AtMost(K) − AtMost(K−1)

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int atMost(int a[], int n, int k){
    unordered_map<int,int> mp;
    int l=0,res=0;
    for(int r=0;r<n;r++){
        if(mp[a[r]]++==0) k--;
        while(k<0){
            if(--mp[a[l++]]==0) k++;
        }
        res+=r-l+1;
    }
    return res;
}
int main(){
    int a[]={1,2,1,2,3};
    int n=5,k=2;
    cout<<atMost(a,n,k)-atMost(a,n,k-1);
}
/* 
Output
7
*/



6️⃣ Sliding Window Median (LC 480)
Idea
Two multisets

Code
#include <iostream>
#include <set>
using namespace std;
int main(){
    int a[]={1,3,-1,-3,5,3,6,7};
    int n=8,k=3;
    multiset<int> lo,hi;

    auto rebalance=[&](){
        while(lo.size()>hi.size()+1){ hi.insert(*lo.rbegin()); lo.erase(prev(lo.end())); }
        while(hi.size()>lo.size()){ lo.insert(*hi.begin()); hi.erase(hi.begin()); }
    };

    for(int i=0;i<n;i++){
        if(lo.empty()||a[i]<=*lo.rbegin()) lo.insert(a[i]);
        else hi.insert(a[i]);
        rebalance();

        if(i>=k){
            if(lo.find(a[i-k])!=lo.end()) lo.erase(lo.find(a[i-k]));
            else hi.erase(hi.find(a[i-k]));
            rebalance();
        }
        if(i>=k-1)
            cout<<*lo.rbegin()<<" ";
    }
}
/* 
Output
1 -1 -1 3 5 6
*/


7️⃣ Longest Duplicate Substring (LC 1044)
Idea
Binary search + rolling hash

Core Idea (Why this works)

Any duplicate substring of length L → checkable using hashing

If a duplicate exists for length L, it must exist for all < L

So the answer is monotonic → use Binary Search on length

✅ Steps

Binary search substring length len

For each len, check if any substring repeats

Use rolling hash to compare substrings in O(1)

Track max valid length

💻 Complete C++ Code (with main())
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestDupSubstring(string s) {
        int n = s.size();
        const long long mod = (1LL << 61) - 1;
        const long long base = 26;

        vector<long long> power(n + 1, 1), hash(n + 1, 0);

        for (int i = 0; i < n; i++) {
            power[i + 1] = (power[i] * base) % mod;
            hash[i + 1] = (hash[i] * base + (s[i] - 'a')) % mod;
        }

        auto getHash = [&](int l, int r) {
            return (hash[r] - (hash[l] * power[r - l]) % mod + mod) % mod;
        };

        int start = -1, maxLen = 0;
        int low = 1, high = n - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            unordered_map<long long, vector<int>> seen;
            bool found = false;

            for (int i = 0; i + mid <= n; i++) {
                long long h = getHash(i, i + mid);
                if (seen.count(h)) {
                    start = i;
                    maxLen = mid;
                    found = true;
                    break;
                }
                seen[h].push_back(i);
            }

            if (found) low = mid + 1;
            else high = mid - 1;
        }

        return maxLen == 0 ? "" : s.substr(start, maxLen);
    }
};

int main() {
    Solution sol;
    string s = "banana";
    cout << sol.longestDupSubstring(s) << endl;
    return 0;
}
/* 
Output (example)
ana
*/

🔍 Dry Run (Input: "banana")
Binary Search Range
low = 1, high = 5



🔁 mid = 3
Substrings of length 3:
ban → hash1
ana → hash2
nan → hash3
ana → hash2  ✅ duplicate found

✔ Valid → store "ana"
➡ move right
low = 4




🔁 mid = 4
Substrings:
bana
anan
nana

❌ No duplicates
➡ move left
high = 3

🏁 End
maxLen = 3
start = index of "ana"
✅ Answer = "ana"



⏱ Complexity
Time: O(n log n)
Space: O(n)






8️⃣ Minimum Number of Refueling Stops (LC 871)
Idea
Max heap greedy

/* 
Output
2
*/


9️⃣ Merge Intervals (LC 56) — tricky edge cases
/* 
Output
[1,6] [8,10] [15,18]
*/




🔟 Reverse Pairs (LC 493)
Idea
Merge sort inversion trick

/* 
Output
2
*/




