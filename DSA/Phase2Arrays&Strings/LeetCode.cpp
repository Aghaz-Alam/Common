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




