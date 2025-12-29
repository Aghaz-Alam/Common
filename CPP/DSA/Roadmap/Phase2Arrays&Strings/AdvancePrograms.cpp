1️⃣ Circular Array = Kadane Trick
🔹 Concept
Maximum subarray sum in a circular array can be:
Normal subarray (no wrap) → Kadane
Wrap-around subarray →
totalSum − minimum subarray sum

⚠️ TRAP
❌ Applying circular formula blindly
❌ All elements negative → circular result becomes 0 (WRONG)

✅ Correct Code
#include <iostream>
using namespace std;
int kadane(int a[], int n) {
    int curr = a[0], best = a[0];
    for(int i=1;i<n;i++) {
        curr = max(a[i], curr + a[i]);
        best = max(best, curr);
    }
    return best;
}
int main() {
    int a[] = {5,-3,5};
    int n = 3;

    int normalMax = kadane(a,n);
    int totalSum = 0;

    for(int i=0;i<n;i++) {
        totalSum += a[i];
        a[i] = -a[i];
    }

    int circularMax = totalSum + kadane(a,n);
    cout << max(normalMax, circularMax);
}
/*
🧠 Dry Run
Array: 5 -3 5
Normal Kadane = 7
Min subarray = -3
Circular sum = 7 - (-3) = 10
Answer = 10
*/


2️⃣ Sorting + Two Pointers Beats Brute Force
🔹 Concept
Instead of O(n²) checking pairs:
Sort array
Move left/right pointers intelligently

⚠️ TRAP
❌ Forgetting to sort
❌ Using two pointers on unsorted array

✅ Correct Code (Two Sum)
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int a[] = {8,4,1,6};
    int n=4, target=10;

    sort(a,a+n);

    int l=0, r=n-1;
    while(l<r) {
        int sum = a[l]+a[r];
        if(sum==target) {
            cout<<"Yes";
            return 0;
        }
        else if(sum<target) l++;
        else r--;
    }
    cout<<"No";
}
/*
🧠 Dry Run
Sorted: 1 4 6 8
1+8=9 → l++
4+8=12 → r--
4+6=10 → FOUND
*/




3️⃣ Binary Search Beyond Searching
🔹 Concept
Binary search works on monotonic conditions, not just sorted arrays.

Used for:
Peak element
Minimum in rotated array
First bad version
Answer space search

⚠️ TRAP
❌ Thinking binary search only finds exact elements
❌ Missing mid+1 / mid-1 bounds

✅ Correct Code (Find Peak Element)
#include <iostream>
using namespace std;
int main() {
    int a[] = {1,2,3,1};
    int l=0, r=3;

    while(l<r) {
        int mid = (l+r)/2;
        if(a[mid] < a[mid+1])
            l = mid + 1;
        else
            r = mid;
    }
    cout << l;
}
/*
🧠 Dry Run
1 2 3 1
mid=1 → 2<3 → move right
mid=2 → 3>1 → peak found at index 2
*/



4️⃣ Prefix Sum = Universal Weapon
🔹 Concept
Prefix sum converts:
Subarray problems → subtraction
Count problems → hashmap

Used for:
Subarray sum = K
XOR problems
Balanced 0s & 1s
Nice subarrays

⚠️ TRAP
❌ Forgetting mp[0] = 1
❌ Overwriting prefix before counting

✅ Correct Code (Subarrays Sum = K)
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int a[] = {1,2,3};
    int k=3, sum=0, count=0;
    unordered_map<int,int> mp;
    mp[0]=1;

    for(int i=0;i<3;i++) {
        sum += a[i];
        count += mp[sum-k];
        mp[sum]++;
    }
    cout << count;
}
/*
🧠 Dry Run
Prefix sums: 1,3,6
sum-k matches earlier prefix
Subarrays: [1,2], [3]
Answer = 2
*/






1️⃣ Longest Subarray With Equal 0s, 1s, 2s
Concept
Convert to prefix differences
Track (count1-count0, count2-count1) pair
Hashmap of pair → first index

⚠️ TRAP
❌ Treating it like 0/1 problem
❌ Forgetting pair key, not single sum

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int a[] = {0,1,2,0,1,2,1,0};
    int n = 8;
    unordered_map<string,int> mp;

    int c0=0,c1=0,c2=0, ans=0;
    mp["0#0"] = -1;

    for(int i=0;i<n;i++) {
        if(a[i]==0) c0++;
        else if(a[i]==1) c1++;
        else c2++;

        string key = to_string(c1-c0)+"#"+to_string(c2-c1);
        if(mp.count(key))
            ans = max(ans, i - mp[key]);
        else
            mp[key] = i;
    }
    cout << ans;
}
/*
Output
6

Dry Run
Prefix states repeat → balanced segment
0 1 2 0 1 2 → length 6
*/



2️⃣ Count Subarrays With Product < K
Concept

Sliding window
Multiply right, divide left
Works only for positive numbers

⚠️ TRAP
❌ Using prefix product (overflow)
❌ Forgetting k <= 1 edge case

Code
#include <iostream>
using namespace std;
int main() {
    int a[] = {10,5,2,6};
    int n=4, k=100;
    if(k<=1) { cout<<0; return 0; }

    long long prod=1;
    int l=0, ans=0;

    for(int r=0;r<n;r++) {
        prod *= a[r];
        while(prod >= k)
            prod /= a[l++];
        ans += (r-l+1);
    }
    cout << ans;
}
/*
Output
8

Dry Run
Valid windows counted dynamically
*/


3️⃣ First Missing Positive (O(1) Space)
Concept
Place each number at index num-1
Ignore negatives & >n
Answer = first index mismatch

⚠️ TRAP
❌ Sorting (O(n log n))
❌ Extra array (space violation)

Code
#include <iostream>
using namespace std;
int main() {
    int a[] = {3,4,-1,1};
    int n=4;

    for(int i=0;i<n;i++) {
        while(a[i]>=1 && a[i]<=n && a[a[i]-1]!=a[i])
            swap(a[i], a[a[i]-1]);
    }

    for(int i=0;i<n;i++)
        if(a[i]!=i+1) {
            cout << i+1;
            return 0;
        }
    cout << n+1;
}
/*
Output
2
*/



4️⃣ Longest Subarray With At Most K Zeros
Concept
Sliding window
Count zeros
Shrink when zeros > k

⚠️ TRAP
❌ Confusing “exactly k” vs “at most k”

Code
#include <iostream>
using namespace std;
int main() {
    int a[] = {1,1,0,0,1,1,0,1};
    int k=2, n=8;
    int zero=0, l=0, ans=0;

    for(int r=0;r<n;r++) {
        if(a[r]==0) zero++;
        while(zero > k)
            if(a[l++]==0) zero--;
        ans = max(ans, r-l+1);
    }
    cout << ans;
}
/*
Output
6
*/



5️⃣ Maximum Length Subarray With Sum 0
Concept
Prefix sum
Same sum repeats → zero subarray

⚠️ TRAP
❌ Overwriting prefix index
❌ Missing sum == 0 case

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int a[] = {1,-1,3,-3,4};
    int n=5, sum=0, ans=0;
    unordered_map<int,int> mp;

    for(int i=0;i<n;i++) {
        sum += a[i];
        if(sum==0) ans=i+1;
        if(mp.count(sum))
            ans=max(ans,i-mp[sum]);
        else
            mp[sum]=i;
    }
    cout << ans;
}
/*
Output
4
*/


6️⃣ Split Array Into Equal Sum Parts (3 Parts)
Concept
Total sum must be divisible by 3
Track prefix sums

⚠️ TRAP
❌ Using greedy split without validation

Code
#include <iostream>
using namespace std;
int main() {
    int a[] = {1,2,3,0,3};
    int n=5, sum=0;
    for(int x:a) sum+=x;
    if(sum%3!=0) { cout<<"No"; return 0; }

    int part=sum/3, curr=0, cnt=0;
    for(int i=0;i<n;i++) {
        curr+=a[i];
        if(curr==part) {
            cnt++;
            curr=0;
        }
    }
    cout << (cnt>=3 ? "Yes":"No");
}
/*
Output
Yes
*/




7️⃣ Longest Substring With Exactly K Distinct Characters
Concept
Sliding window
Count when map size == k

⚠️ TRAP
❌ Writing “at most k” logic

Code
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    string s="aabacbebebe";
    int k=3;
    unordered_map<char,int> mp;
    int l=0, ans=-1;

    for(int r=0;r<s.size();r++) {
        mp[s[r]]++;
        while(mp.size()>k) {
            if(--mp[s[l]]==0)
                mp.erase(s[l]);
            l++;
        }
        if(mp.size()==k)
            ans=max(ans,r-l+1);
    }
    cout << ans;
}
/*
Output
7
*/



8️⃣ Rearrange Array to Index = Value
Concept
Place arr[i] at index arr[i]
Ignore -1
O(1) extra space

⚠️ TRAP
❌ Extra array
❌ Infinite swap loop

Code
#include <iostream>
using namespace std;
int main() {
    int a[] = {-1,2,1,-1,4};
    int n=5;

    for(int i=0;i<n;i++) {
        while(a[i]!=-1 && a[i]!=i)
            swap(a[i], a[a[i]]);
    }

    for(int x:a) cout<<x<<" ";
}
/*
Output
-1 1 2 -1 4
*/






🔥 PART-1: “TELL OUTPUT” — 20 TRAP QUESTIONS (Arrays / Strings)
👉 Rule: DO NOT RUN.
👉 Goal: Detect hidden behavior, order of execution, off-by-one, overflow, logic traps.



//Q1
int a[] = {1,2,3,4};
cout << a[1] + *(a+2);
/*
✅ Output: 5
🧠 a[1]=2, *(a+2)=3
*/


//Q2
int a[] = {1,2,3,4};
cout << *a + 1;
/*
✅ Output: 2
🧠 *a = 1
*/


//Q3
int a[] = {1,2,3};
cout << sizeof(a)/sizeof(a[0]);
/*
✅ Output: 3
⚠️ Works only inside same scope
*/


//Q4
int a[] = {1,2,3};
cout << sizeof(a);
/*
✅ Output: 12 (on 32-bit int)
*/


//Q5
int x = 5;
cout << x++ + ++x;
/*
⚠️ Undefined behavior
❌ Never answer numerically in interviews
*/


//Q6
int a[] = {1,2,3,4,5};
cout << *(a + 3);
/*
✅ Output: 4
*/


//Q7
char s[] = "abc";
cout << sizeof(s);
/*
✅ Output: 4
🧠 includes '\0'
*/



//Q8
string s = "abc";
cout << sizeof(s);

/*
✅ Output: implementation-dependent (usually 24 or 32)
*/


//Q9
int a[] = {1,2,3};
cout << *(a++);
/*
❌ Compilation error
🧠 array name not modifiable
*/



//Q10
int a[] = {1,2,3};
int* p = a;
cout << *p++ << " " << *p;

/*
✅ Output: 1 2
*/



//Q11
int i = 0;
while(i < 5)
    cout << i++;

/*
✅ Output: 01234
*/


//Q12
int a[] = {1,2,3,4};
for(int i=0;i<4;i++)
    a[i] = a[a[i]-1];
cout << a[0];

/*
⚠️ Trap: modified during loop
✅ Output: 1
*/


//Q13
int x = 10;
cout << (x & 1);
/*
✅ Output: 0
*/



//Q14
int a[] = {0,1,0,1};
int sum = 0;
for(int i=0;i<4;i++)
    sum += (a[i]==0 ? -1 : 1);
cout << sum;
/*
✅ Output: 0
*/



//Q15
int a[] = {1,2,3};
cout << a[3];
/*
⚠️ Garbage value (undefined access)
*/


//Q16
cout << ("abc" == "abc");
/*
❌ Output: 0
🧠 pointer comparison
*/



//Q17
string a="abc", b="abc";
cout << (a==b);
/*
✅ Output: 1
*/


//Q18
int a=5;
cout << a+++a;

❌ Compilation error



//Q19
int x = 1;
cout << (x<<2);
/*
✅ Output: 4
*/



//Q20
int a[] = {1,2,3};
cout << &a[1] - &a[0];
/*
✅ Output: 1
*/





🔥 PART-2: BINARY SEARCH ON ANSWER (ADVANCED)
Binary search on ANSWER SPACE, not array.


1️⃣ Minimum Capacity to Ship Packages
Idea
Answer range = [max(weight), sum(weights)]
Check feasibility

Code
bool canShip(int a[], int n, int days, int cap) {
    int curr=0, d=1;
    for(int i=0;i<n;i++) {
        if(curr + a[i] > cap) {
            d++;
            curr = 0;
        }
        curr += a[i];
    }
    return d <= days;
}
int main() {
    int a[] = {1,2,3,1,1};
    int n=5, days=4;
    int l=3, r=8, ans=0;

    while(l<=r) {
        int mid = (l+r)/2;
        if(canShip(a,n,days,mid)) {
            ans=mid;
            r=mid-1;
        } else l=mid+1;
    }
    cout<<ans;
}
/*
✅ Output: 3
*/


2️⃣ Koko Eating Bananas
Idea
Speed range: 1 → max(pile)
Monotonic function


3️⃣ Aggressive Cows
Idea
Binary search on minimum distance
Greedy placement



4️⃣ Allocate Books
Idea
Minimize maximum pages
Same pattern as ship packages



5️⃣ Minimum Days to Make Bouquets
Idea
Binary search on days
Count consecutive bloomed flowers

📌 Golden Rule
If answer space is sorted → binary search applies
*/



🔥 PART-3: STACK-BASED ARRAY TRAPS
1️⃣ Next Greater Element
int a[] = {4,5,2,10};
/*
Correct Output
5 10 10 -1

⚠️ Trap: brute force is O(n²)
*/


2️⃣ Stock Span Problem
Prices = {100,80,60,70,60,75,85}
/*
Output
1 1 1 2 1 4 6
*/


3️⃣ Largest Rectangle in Histogram
Heights = {2,1,5,6,2,3}
/*
Output
10

⚠️ Trap: left & right smaller indexes
*/

4️⃣ Daily Temperatures
{73,74,75,71,69,72,76,73}
/*
Output
1 1 4 2 1 1 0 0
*/


5️⃣ Remove K Digits
num = "1432219", k=3
/*
Output
1219

⚠️ Trap: remove larger previous digit
*/



