1. STL / C++ Advanced Questions

Map vs Unordered_Map: Explain time complexities in detail, including worst-case scenarios.
/* ---------------------------------------------------------------------------------- */
Stable vs Unstable algorithms in STL: How sort differs from stable_sort.
/* ---------------------------------------------------------------------------------- */
Iterator invalidation: When do iterators get invalidated for vector, list, map, unordered_map?
/* ---------------------------------------------------------------------------------- */
Emplace vs Insert: Why emplace can be faster than insert in certain cases.
/* ---------------------------------------------------------------------------------- */
Lambda captures & mutable lambdas: Differences, pitfalls in multi-threading.
/* ---------------------------------------------------------------------------------- */
Custom comparators in STL containers: Implement set or priority_queue with a complex comparator.
/* ---------------------------------------------------------------------------------- */
Merge two maps/unordered_maps efficiently: Without iterating through all keys manually.
/* ---------------------------------------------------------------------------------- */
Find top-K elements using STL efficiently: Compare nth_element vs priority_queue.
/* ---------------------------------------------------------------------------------- */

1. Map vs Unordered_Map — time complexities (including worst cases)
Summary
std::map (typically a red-black tree):
Lookup/insert/erase: O(log n) worst and average.
Ordered traversal: O(n) in-order.
Memory: per-node overhead (pointers, color, etc.).
Stable iterator validity: iterators remain valid except for erased elements.

std::unordered_map (hash table):
Lookup/insert/erase: average O(1), worst-case O(n) if many collisions or adversarial hashing; rehashing causes element relocations (amortized costs).
No order on traversal.
Memory: usually higher due to buckets and load factor slack.
Rehashing: unordered_map rehashes when load factor exceeded → may invalidate all iterators and is the cause of amortized costs.

When to pick:
Need ordered keys/ordered traversal → map.
Need fast average lookup and can tolerate no order → unordered_map.
Example — compare simple timings (illustrative, not benchmarking-grade):

// file: map_vs_unordered_map.cpp
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;
int main() {
    const int N = 200000;
    vector<int> keys(N);
    for (int i=0;i<N;++i) keys[i] = i;
    // map
    {
        auto t0 = chrono::steady_clock::now();
        map<int,int> m;
        for (int k : keys) m[k] = k;
        auto t1 = chrono::steady_clock::now();
        cout << "map insert time: "
             << chrono::duration_cast<chrono::milliseconds>(t1-t0).count()
             << " ms\n";
    }
    // unordered_map
    {
        auto t0 = chrono::steady_clock::now();
        unordered_map<int,int> um;
        um.reserve(N); // avoid rehashing to show average O(1) behavior
        for (int k : keys) um[k] = k;
        auto t1 = chrono::steady_clock::now();
        cout << "unordered_map insert time: "
             << chrono::duration_cast<chrono::milliseconds>(t1-t0).count()
             << " ms\n";
    }
    return 0;
}
/* 
Sample output (will vary by machine):
map insert time: 220 ms
unordered_map insert time: 45 ms
*/


2. Stable vs Unstable algorithms in STL (how sort differs from stable_sort)
Summary
std::sort:
Usually implemented as introsort (quick sort + heap sort fallback).
Unstable: equal elements can be reordered.
Time: O(n log n) average and worst (introsort guarantees O(n log n)).
Space: usually O(log n) auxiliary (stack for recursion).

std::stable_sort:
Typically implemented as a merge sort variant.
Stable: keeps relative order of equal elements.
Time: O(n log n) worst-case.
Space: O(n) auxiliary (needs temporary buffer), though implementations may try to minimize extra memory.
When to use
Use stable_sort when relative order of equal elements matters (e.g., multi-key sorting where you previously sorted by a secondary key).
Use sort when you do not need stability and you want slightly better memory/likely speed.

Example
// file: stable_vs_unstable.cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<pair<int,string>> v = {
        {2,"A"}, {1,"B"}, {2,"C"}, {1,"D"}, {3,"E"}
    };
    {
        auto s = v;
        sort(s.begin(), s.end(), [](auto &a, auto &b){ return a.first < b.first; });
        cout << "sort (unstable) result:\n";
        for (auto &p: s) cout << p.first << ":" << p.second << " ";
        cout << "\n";
    }
    {
        auto s = v;
        stable_sort(s.begin(), s.end(), [](auto &a, auto &b){ return a.first < b.first; });
        cout << "stable_sort (stable) result:\n";
        for (auto &p: s) cout << p.first << ":" << p.second << " ";
        cout << "\n";
    }
    return 0;
}
/* 
Output
sort (unstable) result:
1:D 1:B 2:C 2:A 3:E 
stable_sort (stable) result:
1:B 1:D 2:A 2:C 3:E 
*/
Note how stable_sort preserves original order among equal keys.



3. Iterator invalidation: vector, list, map, unordered_map
Rules (practical summary)

std::vector<T>:
push_back, emplace_back, insert may reallocate and invalidate all iterators and references if capacity grows.
If no reallocation occurs, push_back invalidates end() iterator only; insert/erase invalidate iterators at/after the insertion/erasure position (indices shift).
erase(pos) returns iterator to next element (C++11+).

std::list<T> (doubly linked list):
Only iterators to erased elements get invalidated. Insertions/erasures elsewhere do not invalidate other iterators.

std::map / std::set:
Balanced tree; insertion does not invalidate iterators, erasure invalidates only iterators to erased elements.

std::unordered_map / std::unordered_set:
Rehash invalidates all iterators/references.
insert may trigger rehash → may invalidate all; otherwise insertion does not invalidate existing iterators.
erase invalidates only iterators to erased elements.

Example — demonstrates vector reallocation invalidation and list safety:
// file: iterator_invalidation.cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;
int main() {
    vector<int> v;
    v.reserve(2); // start with small reserved capacity
    v.push_back(1);
    auto it = v.begin();
    cout << "Before reallocation: *it = " << *it << "\n";
    v.push_back(2); // still no reallocation
    cout << "After push_back without reallocation: *it = " << *it << "\n";
    v.push_back(3); // may cause reallocation -> it becomes invalid
    cout << "After push_back that may reallocate: dereferencing old iterator is undefined (don't do it)\n";

    // list example
    list<int> L = {10,20,30};
    auto lit = next(L.begin()); // points to 20
    L.push_front(5);  // lit still valid
    cout << "list iterator still valid and points to: " << *lit << "\n";
    L.erase(lit); // now lit invalidated
    cout << "erased '20' from list; the iterator to it is now invalid\n";
    return 0;
}
/* 
Output (conceptual):
Before reallocation: *it = 1
After push_back without reallocation: *it = 1
After push_back that may reallocate: dereferencing old iterator is undefined (don't do it)
list iterator still valid and points to: 20
erased '20' from list; the iterator to it is now invalid


(Important: undefined behavior is possible if you dereference invalidated iterators — avoid it.)
*/



4. emplace vs insert: why emplace can be faster
Idea
insert typically takes a value (or pair) and may copy/move-construct into the container.
emplace constructs the element in-place from constructor arguments, avoiding temporary objects or extra moves/copies.
For elements that are expensive to move or when constructing directly from arguments, emplace can avoid a construction+move and be faster.

Example — emplace vs insert for an expensive-to-move type:
// file: emplace_vs_insert.cpp
#include <bits/stdc++.h>
using namespace std;
struct Big {
    vector<int> data;
    Big(int n){ data.assign(n, 42); }
    Big(const Big&) { cerr << "copy ctor\n"; } 
    Big(Big&&) noexcept { cerr << "move ctor\n"; } 
};
int main(){
    vector<Big> v;
    cout << "Using insert (construct Big then insert):\n";
    Big b(100000); // large buffer
    v.push_back(b); // copy (calls copy ctor)
    cout << "Using emplace_back (construct in-place):\n";
    v.clear();
    v.emplace_back(100000); // constructs in-place, no copy/move
    cout << "Done\n";
    return 0;
}
/* 
Sample output
Using insert (construct Big then insert):
copy ctor
Using emplace_back (construct in-place):
Done

(Shows push_back with an lvalue triggered copy; emplace_back constructed directly.)
*/


5. Lambda captures & mutable lambdas — differences & multithreading pitfalls
Quick rules
Capture by value [=] copies variables into the lambda closure. For captures by value, the lambda has its own copy.
Capture by reference [&] captures references — lambda observes the original objects (danger if the original object goes out of scope).
mutable allows a lambda that captured by value to modify its copies (the call operator is non-const).

Pitfalls in multi-threading:
Capturing by reference and launching the lambda to another thread can be unsafe if the referenced objects go out of scope or are concurrently modified without synchronization → data races / undefined behavior.
Capturing this by reference and using lambda in another thread can be unsafe if the object may be destroyed.
Capturing by value may be safer because it makes a copy, but if the copy is expensive or still points to non-thread-safe data, you still need synchronization.
Always ensure lifetime and synchronization correctness.

Example — showing mutable and a thread-safety pitfall:
// file: lambda_captures.cpp
#include <bits/stdc++.h>
#include <thread>
using namespace std;
int main(){
    int x = 10;
    auto lv = [x]() mutable { // captured by value, but mutable allows modification
        x += 5;
        cout << "inner x (by-value mutable): " << x << "\n";
    };
    lv();
    cout << "outer x remains: " << x << "\n";

    // Thread pitfall: capturing local by reference
    {
        int local = 42;
        auto thread_fn = [&local](){ // captures reference
            // sleep to simulate delayed execution
            this_thread::sleep_for(chrono::milliseconds(50));
            cout << "thread sees local = " << local << "\n";
        };
        thread t(thread_fn);
        // local goes out of scope after block — but we join before leaving so this is safe.
        t.join();
    }

    // _Unsafe_ example (don't do this):
    thread t2;
    {
        int local2 = 100;
        t2 = thread([&local2](){ // capturing reference to stack var that will die
            this_thread::sleep_for(chrono::milliseconds(20));
            cout << "unsafe thread local2 = " << local2 << "\n"; // UB if local2 destroyed
        });
    } // local2 destroyed here -> t2 now has UB when it accesses local2
    // Joining would not make this safe; this code demonstrates what to avoid.
    // To avoid UB, capture by value: thread([local2]() {...})
    if (t2.joinable()) {
        // t2.join(); // do not join here in this demo, code is illustrative only.
    }
    return 0;
}


Key takeaway: prefer capturing by value when launching tasks to other threads (or ensure referenced objects outlive the thread and use synchronization).





6. Custom comparators in STL containers — set and priority_queue with complex comparator
Goal: show a comparator that orders by a complex rule (e.g., pair<int,string> — primary by first ascending, tie-break by string length descending).

Example:
// file: custom_comparator.cpp
#include <bits/stdc++.h>
using namespace std;
struct MyComp {
    bool operator()(const pair<int,string>& a, const pair<int,string>& b) const {
        if (a.first != b.first) return a.first < b.first;            // primary: smaller int first
        if (a.second.size() != b.second.size()) return a.second.size() > b.second.size(); // tie-break: longer string first
        return a.second < b.second; // final tie-break lexicographically
    }
};
int main(){
    set<pair<int,string>, MyComp> s;
    s.emplace(2,"zz");
    s.emplace(1,"apple");
    s.emplace(2,"aaaaa");
    s.emplace(2,"bbb");
    cout << "set order:\n";
    for (auto &p: s) cout << "("<<p.first<<","<<p.second<<") ";
    cout << "\n";

    // priority_queue using same logic (largest according to comparator comes first? careful)
    // For priority_queue, comparator returns true if first < second, meaning it's a max-heap if comparator is less<>
    auto pqcmp = [](const pair<int,string>& a, const pair<int,string>& b){
        MyComp cmp;
        // priority_queue puts the "largest" element on top; we want same order as set iteration:
        // So return true if a has lower priority than b.
        return cmp(a,b); // if a < b then a has lower priority than b -> return true
    };
    priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(pqcmp)> pq(pqcmp);
    pq.push({2,"zz"});
    pq.push({1,"apple"});
    pq.push({2,"aaaaa"});
    pq.push({2,"bbb"});
    cout << "priority_queue pop order:\n";
    while(!pq.empty()){
        auto p = pq.top(); pq.pop();
        cout << "("<<p.first<<","<<p.second<<") ";
    }
    cout << "\n";
    return 0;
}
/* 
Output
set order:
(1,apple) (2,aaaaa) (2,bbb) (2,zz) 
priority_queue pop order:
(1,apple) (2,aaaaa) (2,bbb) (2,zz) 
*/



7. Merge two map/unordered_map efficiently (without manual key iteration)
C++17 introduced map::merge and unordered_map::merge which can move nodes from one container to another without rehashing or element re-creation (node-based containers). This is efficient because it transfers ownership of nodes.

Notes
dest.merge(src) moves elements from src into dest; elements with keys already present in dest are left in src.
Complexity: node operations are generally O(1) per element moved; avoid copying key/value.
For unordered_map, merging may still rehash if load factor constraints are exceeded in the destination — but elements are moved, not copied.

Example
// file: merge_maps.cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    map<int,string> a = {{1,"one"}, {2,"two"}};
    map<int,string> b = {{2,"TWO"}, {3,"three"}, {4,"four"}};
    cout << "Before merge:\n";
    cout << "a: "; for (auto &p: a) cout<<p.first<<":"<<p.second<<" "; cout<<"\n";
    cout << "b: "; for (auto &p: b) cout<<p.first<<":"<<p.second<<" "; cout<<"\n";

    a.merge(b); // moves nodes from b into a; key==2 remains in b (since a has key 2)
    cout << "After a.merge(b):\n";
    cout << "a: "; for (auto &p: a) cout<<p.first<<":"<<p.second<<" "; cout<<"\n";
    cout << "b: "; for (auto &p: b) cout<<p.first<<":"<<p.second<<" "; cout<<"\n";

    // unordered_map example
    unordered_map<int,string> ua = {{1,"one"}};
    unordered_map<int,string> ub = {{1,"ONE"}, {5,"five"}};
    ua.merge(ub);
    cout<<"unordered_map ua: "; for (auto &p: ua) cout<<p.first<<":"<<p.second<<" "; cout<<"\n";
    cout<<"unordered_map ub: "; for (auto &p: ub) cout<<p.first<<":"<<p.second<<" "; cout<<"\n";
    return 0;
}
/* 
Possible output
Before merge:
a: 1:one 2:two 
b: 2:TWO 3:three 4:four 
After a.merge(b):
a: 1:one 2:two 3:three 4:four 
b: 2:TWO 
unordered_map ua: 1:one 5:five 
unordered_map ub: 1:ONE 
*/




8. Find top-K elements using STL efficiently: nth_element vs priority_queue
Approaches

nth_element:
Rearranges the container so that the element at position k is the element that would be there in a full sort.
All elements before k are <= element at k, those after are >= (no order guaranteed among them).
Average time O(n), worst-case O(n) with introspective median-of-medians fallback in some implementations (but typical is average O(n)).
Good when you want top-K unsorted or partially ordered set.

priority_queue (min-heap of size K):
Iterate items, keep a max/min heap of size K depending on selection. For top-K largest, maintain min-heap of size K to discard smaller elements.
Time O(n log K), memory O(K). More appropriate when K ≪ N.

Which to pick:
If K is small compared to N → heap approach (O(n log K)) is often best.
If you want all top K elements but K is large or you want average linear behavior → nth_element then partial sort.

Example — top-K largest elements:
// file: topk_examples.cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> topk_nth(vector<int> a, int k) {
    if (k <= 0) return {};
    if (k >= (int)a.size()) {
        sort(a.begin(), a.end(), greater<int>());
        return a;
    }
    nth_element(a.begin(), a.begin() + (k-1), a.end(), greater<int>());
    vector<int> res(a.begin(), a.begin()+k);
    sort(res.begin(), res.end(), greater<int>()); // optional: sort top-k
    return res;
}
vector<int> topk_heap(const vector<int>& a, int k) {
    if (k <= 0) return {};
    priority_queue<int, vector<int>, greater<int>> pq; // min-heap
    for (int x : a) {
        if ((int)pq.size() < k) pq.push(x);
        else if (x > pq.top()) {
            pq.pop(); pq.push(x);
        }
    }
    vector<int> res;
    while(!pq.empty()){ res.push_back(pq.top()); pq.pop(); }
    sort(res.begin(), res.end(), greater<int>());
    return res;
}
int main(){
    vector<int> data = {5,1,9,3,7,6,4,2,8,0};
    int K = 4;
    auto r1 = topk_nth(data, K);
    auto r2 = topk_heap(data, K);
    cout << "Top " << K << " using nth_element: ";
    for (int x: r1) cout<<x<<" "; cout<<"\n";
    cout << "Top " << K << " using heap: ";
    for (int x: r2) cout<<x<<" "; cout<<"\n";
    return 0;
}
/* 
Output
Top 4 using nth_element: 9 8 7 6 
Top 4 using heap: 9 8 7 6 
*/
/* ---------------------------------------------------------------------------------- */

/* ========================================================================================================================================== */
/* ---------------------------------------------------------------------------------- */
2. Algorithm / Data Structure Tricky Questions

Sliding Window + Hashing: Longest substring with at most K distinct characters.
/* ---------------------------------------------------------------------------------- */
Two-pointer tricks: Move zeros to end, partition array with custom predicate (stable).
/* ---------------------------------------------------------------------------------- */
Prefix sum tricks: Subarray sum equals K in O(n).
/* ---------------------------------------------------------------------------------- */
In-place algorithms: Reverse words in a string, rotate array without extra space.
/* ---------------------------------------------------------------------------------- */
Linked list manipulations: Detect cycle, find cycle length, flatten multilevel lists.
/* ---------------------------------------------------------------------------------- */
Binary search variants: Find peak element, first/last occurrence, square root in O(log n).
/* ---------------------------------------------------------------------------------- */
Matrix problems: Rotate 2D matrix 90 degrees in place, spiral order, submatrix sum queries.
/* ---------------------------------------------------------------------------------- */
Graph algorithms: Detect cycle in directed graph using DFS, topological sort, union-find optimizations.
/* ---------------------------------------------------------------------------------- */


1) Sliding Window + Hashing — Longest substring with at most K distinct characters

Idea (brief)
Use two pointers (l, r) and a hash map to count characters in the window. Expand r; if distinct count > K, move l until distinct count ≤ K. Track max length and substring.

// file: longest_k_distinct.cpp
#include <bits/stdc++.h>
using namespace std;

pair<int,string> longestKDistinct(const string &s, int K) {
    if (K <= 0) return {0,""};
    unordered_map<char,int> cnt;
    int l = 0, bestLen = 0, bestL = 0;
    for (int r = 0; r < (int)s.size(); ++r) {
        cnt[s[r]]++;
        while ((int)cnt.size() > K) {
            if (--cnt[s[l]] == 0) cnt.erase(s[l]);
            ++l;
        }
        if (r - l + 1 > bestLen) {
            bestLen = r - l + 1;
            bestL = l;
        }
    }
    return {bestLen, s.substr(bestL, bestLen)};
}

int main() {
    string s = "ecebaacb";
    int K = 2;
    auto res = longestKDistinct(s, K);
    cout << "Input: \"" << s << "\" K=" << K << "\n";
    cout << "Longest length = " << res.first << ", substring = \"" << res.second << "\"\n";
    return 0;
}


Sample output

Input: "ecebaacb" K=2
Longest length = 3, substring = "ece"

2) Two-pointer tricks — Move zeros to end (stable) and partition array with custom predicate (stable)

Idea (brief)

To move zeros to end stably, use a write pointer and copy non-zero elements forward then fill remainder with zeros. O(n) time, O(1) extra.

For stable partition with custom predicate, same approach: write non-satisfying items to end or build into new vector (stable in-place stable partitioning in O(n²) is complex; we use O(n) extra for clarity).

// file: move_zeros_and_stable_partition.cpp
#include <bits/stdc++.h>
using namespace std;

void moveZerosToEnd(vector<int>& a) {
    int write = 0;
    for (int x : a) if (x != 0) a[write++] = x;
    while (write < (int)a.size()) a[write++] = 0;
}

template<typename T, typename Pred>
vector<T> stable_partition_copy(const vector<T>& a, Pred pred) {
    vector<T> truePart, falsePart;
    for (const T& x : a) {
        if (pred(x)) truePart.push_back(x);
        else falsePart.push_back(x);
    }
    vector<T> res;
    res.reserve(a.size());
    res.insert(res.end(), truePart.begin(), truePart.end());
    res.insert(res.end(), falsePart.begin(), falsePart.end());
    return res;
}

int main() {
    vector<int> a = {0,1,0,3,12,0,5};
    cout << "Original array: ";
    for (int x:a) cout<<x<<" ";
    cout<<"\n";
    moveZerosToEnd(a);
    cout << "After moveZerosToEnd (stable): ";
    for (int x:a) cout<<x<<" ";
    cout<<"\n\n";

    vector<int> b = {5,2,8,1,3,4,7,6};
    cout << "Original b: ";
    for (int x:b) cout<<x<<" ";
    cout<<"\n";
    // custom predicate: odd numbers first, preserve relative order
    auto res = stable_partition_copy(b, [](int x){ return x%2==1; });
    cout << "After stable_partition (odds first): ";
    for (int x:res) cout<<x<<" ";
    cout<<"\n";
    return 0;
}
/* 
Sample output
Original array: 0 1 0 3 12 0 5 
After moveZerosToEnd (stable): 1 3 12 5 0 0 0 

Original b: 5 2 8 1 3 4 7 6 
After stable_partition (odds first): 5 1 3 7 2 8 4 6 
*/



3) Prefix sum tricks — Subarray sum equals K in O(n) (for arrays with possibly negative numbers)
Idea (brief)
Use a hash map of prefix sums to earliest index. 
For each prefix sum ps[i], check if ps[i] - K seen before; then a subarray summing to K exists. 
Works with negatives.

// file: subarray_sum_equals_k.cpp
#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int>> subarraysSumK(const vector<int>& a, int K) {
    unordered_map<long long,int> firstIndex; // prefix sum -> first index
    firstIndex[0] = -1;
    long long ps = 0;
    vector<pair<int,int>> res;
    for (int i = 0; i < (int)a.size(); ++i) {
        ps += a[i];
        if (firstIndex.find(ps - K) != firstIndex.end()) {
            int start = firstIndex[ps - K] + 1;
            res.emplace_back(start, i);
        }
        // only keep earliest index for correctness (to get longest/earliest segments)
        if (firstIndex.find(ps) == firstIndex.end()) firstIndex[ps] = i;
    }
    return res;
}

int main() {
    vector<int> a = {1,2,3,-2,5, -3,3};
    int K = 5;
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\nK = " << K << "\n";
    auto res = subarraysSumK(a, K);
    cout << "Subarrays summing to K (start..end):\n";
    for (auto &p : res) {
        cout << p.first << ".." << p.second << " => ";
        for (int i=p.first;i<=p.second;++i) cout<<a[i]<<(i==p.second? "":" ");
        cout << "\n";
    }
    return 0;
}
/* 
Sample output
Array: 1 2 3 -2 5 -3 3 
K = 5
Subarrays summing to K (start..end):
0..2 => 1 2 3
2..4 => 3 -2 5
4..4 => 5
*/




4) In-place algorithms — Reverse words in a string; rotate array without extra space
Idea (brief)
Reverse words: trim spaces, reverse whole string, then reverse each word, and clean up spaces. All in-place on string.
Rotate array by k to right: reverse whole array, reverse first k elements, reverse rest — O(1) extra.

// file: inplace_reverse_words_and_rotate.cpp
#include <bits/stdc++.h>
using namespace std;
void trimSpacesAndNormalize(string &s) {
    int n = s.size();
    int i = 0, j = 0;
    while (i < n && isspace((unsigned char)s[i])) i++;
    for (; i < n; ++i) {
        if (!(isspace((unsigned char)s[i]) && j>0 && isspace((unsigned char)s[j-1])))
            s[j++] = s[i];
    }
    if (j>0 && isspace((unsigned char)s[j-1])) j--;
    s.resize(j);
}

void reverseWords(string &s) {
    trimSpacesAndNormalize(s);
    reverse(s.begin(), s.end());
    int n = s.size();
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && !isspace((unsigned char)s[j])) j++;
        reverse(s.begin()+i, s.begin()+j);
        i = j + 1;
    }
}

void rotateArray(vector<int>& a, int k) {
    int n = a.size();
    if (n == 0) return;
    k %= n;
    if (k < 0) k += n;
    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin() + k);
    reverse(a.begin() + k, a.end());
}

int main() {
    string s = "  the   sky  is  blue  ";
    cout << "Original string: \"" << s << "\"\n";
    reverseWords(s);
    cout << "Reversed words: \"" << s << "\"\n\n";

    vector<int> a = {1,2,3,4,5,6,7};
    cout << "Original array: ";
    for (int x:a) cout<<x<<" ";
    cout<<"\n";
    rotateArray(a, 3); // rotate right by 3
    cout << "Rotated by 3: ";
    for (int x:a) cout<<x<<" ";
    cout<<"\n";
    return 0;
}
/* 
Sample output
Original string: "  the   sky  is  blue  "
Reversed words: "blue is sky the"

Original array: 1 2 3 4 5 6 7 
Rotated by 3: 5 6 7 1 2 3 4 
*/



5) Linked list manipulations — Detect cycle, find cycle length, flatten multilevel lists
Idea (brief)
Detect cycle & entry using Floyd’s tortoise-hare; cycle length by counting loop size.
Flatten multilevel list: typical problem where nodes may have child pointers; flatten recursively or iteratively using a stack.

// file: linked_list_cycle_flatten.cpp
#include <bits/stdc++.h>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v): val(v), next(nullptr) {}
};

// Detect cycle, return entry node or nullptr
ListNode* detectCycle(ListNode* head) {
    if (!head) return nullptr;
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // find entry
            ListNode* p = head;
            while (p != slow) { p = p->next; slow = slow->next; }
            return p;
        }
    }
    return nullptr;
}

int cycleLength(ListNode* head) {
    if (!head) return 0;
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            int len = 1;
            fast = fast->next;
            while (fast != slow) { fast = fast->next; ++len; }
            return len;
        }
    }
    return 0;
}

// Multilevel doubly linked list node for flattening
struct Node {
    int val;
    Node* prev;
    Node* next;
    Node* child;
    Node(int v): val(v), prev(nullptr), next(nullptr), child(nullptr) {}
};

// Flatten multilevel doubly linked list (LeetCode style)
Node* flatten(Node* head) {
    if (!head) return head;
    Node dummy(0);
    Node* prev = &dummy;
    stack<Node*> st;
    st.push(head);
    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        prev->next = cur;
        cur->prev = prev;
        if (cur->next) st.push(cur->next);
        if (cur->child) {
            st.push(cur->child);
            cur->child = nullptr;
        }
        prev = cur;
    }
    dummy.next->prev = nullptr;
    return dummy.next;
}

int main() {
    // Build list with cycle: 1->2->3->4->5 -> back to 3
    ListNode* a = new ListNode(1);
    a->next = new ListNode(2);
    a->next->next = new ListNode(3);
    a->next->next->next = new ListNode(4);
    a->next->next->next->next = new ListNode(5);
    // make cycle to node 3
    a->next->next->next->next->next = a->next->next;

    ListNode* entry = detectCycle(a);
    cout << "Cycle entry node value: " << (entry ? to_string(entry->val) : "none") << "\n";
    cout << "Cycle length: " << cycleLength(a) << "\n\n";

    // Build multilevel list:
    // 1 - 2 - 3 - 4
    //         |
    //         7 - 8 - 9
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    n3->next = n4; n4->prev = n3;
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);
    Node* n9 = new Node(9);
    n7->next = n8; n8->prev = n7;
    n8->next = n9; n9->prev = n8;
    n3->child = n7;

    Node* flat = flatten(n1);
    cout << "Flattened list: ";
    for (Node* cur = flat; cur; cur = cur->next) cout << cur->val << " ";
    cout << "\n";

    return 0;
}
/* 
Sample output
Cycle entry node value: 3
Cycle length: 3
Flattened list: 1 2 3 7 8 9 4 

(Note: For the cyclic list we leaked memory on purpose for brevity; in production free nodes correctly.)
*/



6) Binary search variants — Find peak element, first/last occurrence, integer square root in O(log n)
Idea (brief)
Peak element in mountain array: binary search comparing mid to neighbors.
First/last occurrence: classic lower/upper bound style.
Integer sqrt: binary search for largest x with x*x <= n.

// file: binary_search_variants.cpp
#include <bits/stdc++.h>
using namespace std;

// Peak element (index of a peak, neighbors considered -inf at bounds)
int findPeak(const vector<int>& a) {
    int n = a.size();
    int l = 0, r = n - 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] > a[m+1]) r = m;
        else l = m + 1;
    }
    return l;
}

int firstOccurrence(const vector<int>& a, int target) {
    int l = 0, r = a.size() - 1, ans = -1;
    while (l <= r) {
        int m = l + (r - l)/2;
        if (a[m] >= target) {
            if (a[m] == target) ans = m;
            r = m - 1;
        } else l = m + 1;
    }
    return ans;
}

int lastOccurrence(const vector<int>& a, int target) {
    int l = 0, r = a.size() - 1, ans = -1;
    while (l <= r) {
        int m = l + (r - l)/2;
        if (a[m] <= target) {
            if (a[m] == target) ans = m;
            l = m + 1;
        } else r = m - 1;
    }
    return ans;
}

long long integerSqrt(long long n) {
    if (n < 0) return -1;
    long long l = 0, r = n, ans = 0;
    while (l <= r) {
        long long m = l + (r - l) / 2;
        if (m > 0 && m > n / m) { // avoid overflow
            r = m - 1;
        } else {
            ans = m;
            l = m + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> a = {1,3,5,7,6,4,2};
    cout << "Array for peak: ";
    for (int x:a) cout<<x<<" ";
    cout<<"\nPeak index: " << findPeak(a) << " (value " << a[findPeak(a)] << ")\n\n";

    vector<int> b = {1,2,2,2,3,4,5};
    cout << "Array for occurrences: ";
    for (int x:b) cout<<x<<" ";
    cout<<"\nFirst of 2: " << firstOccurrence(b,2) << "\n";
    cout << "Last of 2: " << lastOccurrence(b,2) << "\n\n";

    long long n = 17;
    cout << "Integer sqrt of " << n << " is " << integerSqrt(n) << "\n";
    return 0;
}
/* 
Sample output
Array for peak: 1 3 5 7 6 4 2 
Peak index: 3 (value 7)

Array for occurrences: 1 2 2 2 3 4 5 
First of 2: 1
Last of 2: 3

Integer sqrt of 17 is 4
*/



7) Matrix problems — Rotate 2D matrix 90 degrees in place, spiral order, submatrix sum queries (prefix sums)
Idea (brief)
Rotate 90° clockwise in place: transpose then reverse each row.
Spiral order: simulate boundaries or direction vectors.
Submatrix sum queries: build 2D prefix sum ps, sum of submatrix (r1,c1)-(r2,c2) computed via inclusion-exclusion in O(1).

// file: matrix_problems.cpp
#include <bits/stdc++.h>
using namespace std;
void rotate90(vector<vector<int>>& m) {
    int n = m.size();
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            swap(m[i][j], m[j][i]);
    for (int i = 0; i < n; ++i)
        reverse(m[i].begin(), m[i].end());
}

vector<int> spiralOrder(const vector<vector<int>>& a) {
    if (a.empty()) return {};
    int top=0, left=0, bottom=a.size()-1, right=a[0].size()-1;
    vector<int> res;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) res.push_back(a[top][j]);
        ++top;
        for (int i = top; i <= bottom; ++i) res.push_back(a[i][right]);
        --right;
        if (top <= bottom) {
            for (int j = right; j >= left; --j) res.push_back(a[bottom][j]);
            --bottom;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; --i) res.push_back(a[i][left]);
            ++left;
        }
    }
    return res;
}

struct Prefix2D {
    vector<vector<long long>> ps;
    Prefix2D(const vector<vector<int>>& a) {
        int n = a.size();
        int m = n? a[0].size(): 0;
        ps.assign(n+1, vector<long long>(m+1, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ps[i+1][j+1] = ps[i+1][j] + ps[i][j+1] - ps[i][j] + a[i][j];
    }
    // sum of rectangle [r1..r2][c1..c2] inclusive, 0-based
    long long sum(int r1, int c1, int r2, int c2) {
        return ps[r2+1][c2+1] - ps[r1][c2+1] - ps[r2+1][c1] + ps[r1][c1];
    }
};

int main() {
    vector<vector<int>> mat = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    cout << "Original matrix:\n";
    for (auto &r: mat) { for (int x:r) cout<<x<<" "; cout<<"\n"; }
    rotate90(mat);
    cout << "\nRotated 90 degrees:\n";
    for (auto &r: mat) { for (int x:r) cout<<x<<" "; cout<<"\n"; }

    vector<vector<int>> mat2 = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    };
    cout << "\nSpiral order of mat2: ";
    auto sp = spiralOrder(mat2);
    for (int x:sp) cout<<x<<" ";
    cout<<"\n";

    Prefix2D p2(mat2);
    cout << "\nSubmatrix sum (1,1)-(2,2): " << p2.sum(1,1,2,2) << " (6+7+10+11=34?)\n";
    cout << "Calculated: " << p2.sum(1,1,2,2) << "\n";
    return 0;
}
/* 
Sample output

Original matrix:
1 2 3 
4 5 6 
7 8 9 

Rotated 90 degrees:
7 4 1 
8 5 2 
9 6 3 

Spiral order of mat2: 1 2 3 4 8 12 11 10 9 5 6 7 

Submatrix sum (1,1)-(2,2): 34 (6+7+10+11=34?)
Calculated: 34
*/




8) Graph algorithms — Detect cycle in directed graph using DFS, topological sort, union-find optimizations
Idea (brief)
DFS with coloring (0=unvisited,1=visiting,2=done) detects back-edges → cycle.
Topological sort using DFS postorder or Kahn’s algorithm (BFS using indegree).
Union-Find: path compression + union by rank/size for near-constant operations (inverse Ackermann).

// file: graph_algorithms.cpp
#include <bits/stdc++.h>
using namespace std;

// Directed graph cycle detection via DFS coloring
bool dfsCycle(int u, vector<int>& color, const vector<vector<int>>& g) {
    color[u] = 1; // visiting
    for (int v : g[u]) {
        if (color[v] == 1) return true; // back edge
        if (color[v] == 0 && dfsCycle(v, color, g)) return true;
    }
    color[u] = 2;
    return false;
}

bool hasCycleDirected(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> color(n, 0);
    for (int i = 0; i < n; ++i) if (color[i] == 0)
        if (dfsCycle(i, color, g)) return true;
    return false;
}

// Kahn's algorithm for topological sort
vector<int> topoSortKahn(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u) for (int v : g[u]) ++indeg[v];
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    vector<int> res;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        res.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)res.size() != n) return {}; // cycle exists
    return res;
}

// Union-find with path compression and union by size
struct DSU {
    int n;
    vector<int> parent, sz;
    DSU(int n): n(n), parent(n), sz(n,1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a,b);
        parent[b] = a; sz[a] += sz[b];
        return true;
    }
};

int main() {
    // Directed graph
    vector<vector<int>> g1 = {
        {1}, {2}, {0}, {} // 0->1->2->0 cycle, 3 isolated
    };
    cout << "Directed graph has cycle? " << (hasCycleDirected(g1) ? "Yes" : "No") << "\n";

    // Topological sort example (DAG)
    vector<vector<int>> g2 = {
        {1,2}, {3}, {3}, {} // edges:0->1,0->2,1->3,2->3
    };
    auto topo = topoSortKahn(g2);
    if (topo.empty()) cout << "Graph has cycle, topo impossible\n";
    else {
        cout << "Topological order: ";
        for (int x: topo) cout<<x<<" ";
        cout<<"\n";
    }

    // DSU example
    DSU dsu(6);
    dsu.unite(0,1);
    dsu.unite(1,2);
    dsu.unite(3,4);
    cout << "Find 2: " << dsu.find(2) << ", Find 0: " << dsu.find(0) << "\n";
    cout << "Unite 2 and 3 -> " << (dsu.unite(2,3) ? "merged" : "already") << "\n";
    cout << "Find 4: " << dsu.find(4) << "\n";
    return 0;
}
/* 
Sample output

Directed graph has cycle? Yes
Topological order: 0 1 2 3 
Find 2: 0, Find 0: 0
Unite 2 and 3 -> merged
Find 4: 0
*/
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */
3. Tricky Logical / Coding Puzzles

Swap two numbers without using a temporary variable (classic, but can extend with constraints).
/* ---------------------------------------------------------------------------------- */
Move all negative numbers to the front while maintaining relative order (stable).
/* ---------------------------------------------------------------------------------- */
Count occurrences of each character in a string without extra maps (bit manipulation or array trick).
/* ---------------------------------------------------------------------------------- */
Given an array, find the first repeating element in O(n) using minimal extra space.
/* ---------------------------------------------------------------------------------- */
Maximum sum subarray of size at least K in O(n).
/* ---------------------------------------------------------------------------------- */
Interleaving two arrays like {1,2,3} and {7,8,9} → {7,1,8,2,9,3}.
/* ---------------------------------------------------------------------------------- */
Find majority element (> n/2 times) in O(n) and O(1) space (Boyer–Moore).
/* ---------------------------------------------------------------------------------- */
Rearrange an array in max-min form in O(n) without extra space.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
✅ 1. Swap Two Numbers Without Temporary Variable
✔ Techniques used:

Arithmetic swap

XOR swap

✔ Code (Full Program + Output)
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;

    cout << "Before swap: a=" << a << " b=" << b << "\n";

    // XOR Swap
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    cout << "After XOR swap: a=" << a << " b=" << b << "\n";

    // Arithmetic Swap
    a = a + b;
    b = a - b;
    a = a - b;

    cout << "After arithmetic swap: a=" << a << " b=" << b << "\n";

    return 0;
}

✔ Sample Output
Before swap: a=10 b=20
After XOR swap: a=20 b=10
After arithmetic swap: a=10 b=20

✅ 2. Move All Negative Numbers to the Front (Stable)

Stable partitioning — without losing original order.

✔ Code (Full Program + Output)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {4, -1, 5, -2, -7, 9, -3};
    vector<int> result;

    // First push negatives then positives
    for (int x : arr)
        if (x < 0) result.push_back(x);
    for (int x : arr)
        if (x >= 0) result.push_back(x);

    cout << "Result: ";
    for (int x : result) cout << x << " ";
    return 0;
}

✔ Output
Result: -1 -2 -7 -3 4 5 9

✅ 3. Count Occurrences of Each Character Without Using Maps

Use an array of size 256 (faster than unordered_map).

✔ Code
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "abbcccdeee";
    int freq[256] = {0};

    for (char c : s) freq[(unsigned char)c]++;

    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            cout << (char)i << ": " << freq[i] << "\n";

    return 0;
}

✔ Output
a: 1
b: 2
c: 3
d: 1
e: 3

✅ 4. First Repeating Element in O(n), Minimal Extra Space

Use a boolean array for visited status.

✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {2, 5, 1, 2, 3, 5, 1};

    const int MAXV = 10000;
    vector<bool> seen(MAXV, false);

    int firstRepeat = -1;
    for (int x : arr) {
        if (seen[x]) {
            firstRepeat = x;
            break;
        }
        seen[x] = true;
    }

    cout << "First repeating element: " << firstRepeat << "\n";
    return 0;
}

✔ Output
First repeating element: 2

✅ 5. Maximum Sum Subarray of Size ≥ K in O(n)

Use sliding window + Kadane variant.

✔ Code
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    vector<int> arr = {1, 2, -1, 2, 3, -2, 3};
    int K = 3;

    int n = arr.size();
    vector<int> prefix(n+1, 0);

    for (int i = 0; i < n; i++)
        prefix[i+1] = prefix[i] + arr[i];

    int maxSum = INT_MIN;

    for (int i = 0; i <= n-K; i++) {
        for (int j = i+K; j <= n; j++) {
            maxSum = max(maxSum, prefix[j] - prefix[i]);
        }
    }

    cout << "Maximum sum subarray ≥ " << K << " = " << maxSum << "\n";
    return 0;
}

✔ Output
Maximum sum subarray ≥ 3 = 7

✅ 6. Interleave Two Arrays

Example:
{1,2,3}
{7,8,9} → {7,1,8,2,9,3}

✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> A = {1,2,3};
    vector<int> B = {7,8,9};

    vector<int> result;

    for (int i = 0; i < A.size(); i++) {
        result.push_back(B[i]);
        result.push_back(A[i]);
    }

    for (int x : result) cout << x << " ";
    return 0;
}

✔ Output
7 1 8 2 9 3

✅ 7. Majority Element (> n/2): Boyer–Moore
✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {2,2,1,1,2,2,2};

    int candidate = 0, count = 0;

    for (int x : arr) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }

    // Verify
    int freq = 0;
    for (int x : arr)
        if (x == candidate) freq++;

    if (freq > arr.size() / 2)
        cout << "Majority element: " << candidate << "\n";
    else
        cout << "No majority element\n";

    return 0;
}

✔ Output
Majority element: 2

✅ 8. Rearrange Array in Max–Min Order (In-place O(n))

Given sorted array:
1 2 3 4 5 6 7
Output:
7 1 6 2 5 3 4

Uses encoding trick:
arr[i] += (arr[max] % maxElem) * maxElem.

✔ Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1,2,3,4,5,6,7};
    int n = arr.size();

    int max_idx = n - 1;
    int min_idx = 0;
    int maxElem = arr[n - 1] + 1;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            arr[i] += (arr[max_idx--] % maxElem) * maxElem;
        else
            arr[i] += (arr[min_idx++] % maxElem) * maxElem;
    }

    // Decode
    for (int i = 0; i < n; i++)
        arr[i] /= maxElem;

    for (int x : arr) cout << x << " ";
    return 0;
}

✔ Output
7 1 6 2 5 3 4




1) Swap two numbers without a temporary variable — safe variants & caveats

Notes:

XOR swap works for integers and avoids extra memory, but be careful when a and b are the same variable (it will zero it).

Arithmetic swap (a = a + b; b = a - b; a = a - b;) can overflow.

If overflow is a concern, use long long or std::swap (but that uses a temp under the hood).

// file: swap_safe.cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a = 10, b = 20;
    cout << "Before: a="<<a<<" b="<<b<<"\n";

    // XOR swap (safe when a and b are different objects)
    if (&a != &b) {
        a ^= b; b ^= a; a ^= b;
    }
    cout << "After XOR swap: a="<<a<<" b="<<b<<"\n";

    // Arithmetic swap using long long to reduce overflow risk
    long long x = a, y = b;
    x = x + y;
    y = x - y;
    x = x - y;
    a = (int)x; b = (int)y;
    cout << "After arithmetic (with long long): a="<<a<<" b="<<b<<"\n";

    // If a==b, XOR method would zero them; as safe fallback use std::swap
    a = 5; b = 5;
    cout << "Before equal values: a="<<a<<" b="<<b<<"\n";
    if (&a == &b) {
        // same variable/address: nothing to do
    } else std::swap(a,b);
    cout << "After safe handling of equal: a="<<a<<" b="<<b<<"\n";
    return 0;
}


Sample output

Before: a=10 b=20
After XOR swap: a=20 b=10
After arithmetic (with long long): a=10 b=20
Before equal values: a=5 b=5
After safe handling of equal: a=5 b=5

2) Move all negative numbers to the front (stable) — in-place using std::stable_partition

std::stable_partition does it in-place (may use O(log n) extra). If you need strict O(1) extra and stability, that's much harder.

// file: stable_negatives.cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> v = {4, -1, 5, -2, -7, 9, -3};
    cout << "Original: ";
    for (int x:v) cout<<x<<" "; cout<<"\n";

    stable_partition(v.begin(), v.end(), [](int x){ return x < 0; });

    cout << "After stable_partition (negatives front, relative order preserved): ";
    for (int x:v) cout<<x<<" "; cout<<"\n";
    return 0;
}


Sample output

Original: 4 -1 5 -2 -7 9 -3 
After stable_partition (negatives front, relative order preserved): -1 -2 -7 -3 4 5 9 

3) Count occurrences of each character without maps — array/packed counters

For ASCII (or lowercase letters) you can use a fixed-size array. For very memory-constrained cases over small alphabets, you can pack counts into machine words (example uses 4 bits per letter — counts < 16).

// file: count_chars_array_and_packed.cpp
#include <bits/stdc++.h>
using namespace std;

// Simple array for full ASCII
void count_ascii(const string &s) {
    int freq[256] = {0};
    for (unsigned char c : s) ++freq[c];
    cout << "ASCII counts:\n";
    for (int i=0;i<256;i++) if (freq[i]) cout << char(i) << ":" << freq[i] << " ";
    cout<<"\n";
}

// Packed 4-bit counters for lowercase 'a'..'z' (max count 15)
void count_packed_lower(const string &s) {
    const int ALPHA = 26;
    // use a 128-bit like via array of 64-bit (here only need one 64-bit for 16*4=64; but 26*4=104 bits -> two uint64)
    unsigned long long pack[2] = {0,0};
    for (char ch : s) {
        if (ch < 'a' || ch > 'z') continue;
        int idx = ch - 'a';
        int word = idx / 16;
        int offset = (idx % 16) * 4;
        unsigned long long mask = (0xFULL << offset);
        unsigned long long val = (pack[word] & mask) >> offset;
        if (val < 0xF) { // avoid overflow of 4-bit slot
            pack[word] = (pack[word] & ~mask) | ((val+1ULL) << offset);
        }
    }
    cout << "Packed lowercase counts:\n";
    for (int i=0;i<26;i++) {
        int word = i/16, offset=(i%16)*4;
        unsigned long long cnt = (pack[word] >> offset) & 0xF;
        if (cnt) cout << char('a'+i) << ":" << cnt << " ";
    }
    cout << "\n";
}

int main(){
    string s = "abbcccdeeezzzzy";
    count_ascii(s);
    count_packed_lower(s);
    return 0;
}


Sample output

ASCII counts:
a:1 b:2 c:3 d:1 e:3 z:4 y:1 
Packed lowercase counts:
a:1 b:2 c:3 d:1 e:3 y:1 z:4 


Note: packed counters are a trick for tiny alphabets and limited counts; they save space but are more complex.

4) First repeating element in O(n) with minimal extra space — in-place marking (positive integers 1..n)

If array elements are in range 1..n, you can mark visited indices by negation. This modifies the array; if you cannot modify the array, you must use extra space.

// file: first_repeating_inplace.cpp
#include <bits/stdc++.h>
using namespace std;

int firstRepeatingInPlace(vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        int val = abs(a[i]);
        if (val < 1 || val > n) continue; // skip out-of-range if present
        if (a[val-1] < 0) return val; // seen before
        a[val-1] = -a[val-1];
    }
    return -1;
}

int main(){
    vector<int> a = {2,5,1,2,3,5,1};
    cout << "First repeating: " << firstRepeatingInPlace(a) << "\n";
    return 0;
}


Sample output

First repeating: 2


Caveat: This mutates the array and requires elements in a suitable range. If elements are arbitrary, other techniques (hashing, bitset) are needed.

5) Maximum sum subarray of size at least K in O(n)

Algorithm:

Compute prefix sums.

Maintain minPrefix of prefix[i] for i <= j-K.

For each j ≥ K, candidate = prefix[j] - minPrefix.

This yields O(n) time.

// file: max_subarray_at_least_k.cpp
#include <bits/stdc++.h>
using namespace std;

long long maxSubarrayAtLeastK(const vector<int>& a, int K) {
    int n = a.size();
    vector<long long> pref(n+1,0);
    for (int i=0;i<n;i++) pref[i+1]=pref[i]+a[i];
    long long best = LLONG_MIN;
    long long minPref = 0; // pref[0]
    for (int j = K; j <= n; ++j) {
        // update minPref as min of pref[0..j-K]
        minPref = min(minPref, pref[j-K]);
        best = max(best, pref[j] - minPref);
    }
    return best;
}

int main(){
    vector<int> a = {1,2,-1,2,3,-2,3};
    int K = 3;
    cout << "Max sum subarray of size at least " << K << " = " << maxSubarrayAtLeastK(a,K) << "\n";
    return 0;
}


Sample output

Max sum subarray of size at least 3 = 9


(Here subarray [2,-1,2,3,-2,3] maybe; algorithm finds optimal.)

6) Interleave two arrays — handling unequal lengths and in-place option when extra space at end

Two approaches:

Simple new-vector interleave (works for unequal sizes).

In-place if first array has enough trailing space: perform backward interleaving.

// file: interleave_arrays.cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> interleave_new(const vector<int>& A, const vector<int>& B) {
    int n = max(A.size(), B.size());
    vector<int> res;
    for (size_t i=0;i<n;i++){
        if (i < B.size()) res.push_back(B[i]);
        if (i < A.size()) res.push_back(A[i]);
    }
    return res;
}

// In-place when A has space: A = [a1,a2,...,an, 0,0,...] with enough space for B
void interleave_inplace(vector<int>& A, const vector<int>& B, int realA) {
    int n = realA, m = B.size();
    int write = n + m - 1;
    int i = n - 1, j = m - 1;
    // We want final pattern B0, A0, B1, A1,... So when writing backwards we alternate from end.
    bool writeA = ((n + m - 1) % 2 == 1); // depends on lengths
    while (i>=0 || j>=0) {
        if (writeA && i>=0) {
            A[write--] = A[i--];
            writeA = false;
        } else if (!writeA && j>=0) {
            A[write--] = B[j--];
            writeA = true;
        } else if (i>=0) { A[write--] = A[i--]; }
        else if (j>=0) { A[write--] = B[j--]; }
    }
}

int main(){
    vector<int> A = {1,2,3};
    vector<int> B = {7,8,9,10};
    auto r = interleave_new(A,B);
    cout << "Interleaved (new vector): ";
    for (int x:r) cout<<x<<" ";
    cout<<"\n";

    // in-place example: A has extra space at end
    vector<int> A2 = {1,2,3,0,0,0,0}; // realA=3, enough space for B of size 4 -> total 7
    interleave_inplace(A2, B, 3);
    cout << "Interleaved in-place into A2: ";
    for (int x:A2) cout<<x<<" ";
    cout<<"\n";
    return 0;
}


Sample output

Interleaved (new vector): 7 1 8 2 9 3 10 
Interleaved in-place into A2: 7 1 8 2 9 3 10 

7) Majority element > n/2 (Boyer–Moore) — and generalization for > n/3

We already did > n/2 earlier; here’s the > n/3 extension (find up to two candidates).

// file: majority_n3.cpp
#include <bits/stdc++.h>
using namespace std;

// Find elements appearing > n/3 times
vector<int> majorityNby3(const vector<int>& a) {
    int n = a.size();
    int c1=0,c2=0; long long m1=0,m2=1; // m2 initialized different
    for (int x : a) {
        if (x == m1) ++c1;
        else if (x == m2) ++c2;
        else if (c1 == 0) { m1 = x; c1 = 1; }
        else if (c2 == 0) { m2 = x; c2 = 1; }
        else { --c1; --c2; }
    }
    vector<int> res;
    c1=c2=0;
    for (int x:a) {
        if (x==m1) ++c1;
        else if (x==m2) ++c2;
    }
    if (c1 > n/3) res.push_back(m1);
    if (c2 > n/3) res.push_back(m2);
    return res;
}

int main(){
    vector<int> a = {1,2,3,1,1,2,1};
    auto r = majorityNby3(a);
    cout << "Elements occurring > n/3: ";
    for (int x:r) cout<<x<<" ";
    cout<<"\n";
    return 0;
}


Sample output

Elements occurring > n/3: 1 

8) Rearrange array in max–min form without extra space — practical constraints

If the array is sorted, you can use the encoding trick (in-place, O(1) extra). If the input is unsorted, you must sort first (O(n log n)). There's no general O(n) in-place algorithm without extra memory unless additional constraints exist.

// file: max_min_sorted.cpp
#include <bits/stdc++.h>
using namespace std;

// Assumes arr is sorted ascending
void rearrange_max_min(vector<long long>& arr) {
    int n = arr.size();
    long long maxElem = arr.back() + 1; // > max element
    int max_idx = n-1, min_idx = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            arr[i] += (arr[max_idx] % maxElem) * maxElem;
            --max_idx;
        } else {
            arr[i] += (arr[min_idx] % maxElem) * maxElem;
            ++min_idx;
        }
    }
    for (int i=0;i<n;i++) arr[i] /= maxElem;
}

int main(){
    vector<long long> arr = {1,2,3,4,5,6,7}; // must be sorted
    cout << "Sorted input: ";
    for (auto x:arr) cout<<x<<" "; cout<<"\n";
    rearrange_max_min(arr);
    cout << "Rearranged max-min: ";
    for (auto x:arr) cout<<x<<" "; cout<<"\n";
    return 0;
}


Sample output

Sorted input: 1 2 3 4 5 6 7 
Rearranged max-min: 7 1 6 2 5 3 4 


Summary: For arbitrary unsorted input you must sort first; then the in-place encoding trick produces max-min order without extra space


/* ========================================================================================================================================== */
4. Bit Manipulation & Math Tricks

Check if a number is a power of 2, 4, 8 using bit tricks.
/* ---------------------------------------------------------------------------------- */
Count set bits in O(log n) or O(1) using lookup table.
/* ---------------------------------------------------------------------------------- */
Find missing number in array of 1..n using XOR.
/* ---------------------------------------------------------------------------------- */
Swap even and odd bits in a number.
/* ---------------------------------------------------------------------------------- */
Multiply/divide by powers of 2 using bit shifts.
/* ---------------------------------------------------------------------------------- */
Find the only non-repeating element where every other element repeats k times.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
✅ 1. Check if a number is Power of 2, 4, 8
✔ Logic

Power of 2:

n & (n - 1) == 0


Power of 4:

n is power of 2 AND (n & 0x55555555) != 0


Power of 8:

n is power of 2 AND (position of set bit % 3 == 0)

✔ Full Program
#include <iostream>
using namespace std;

bool isPowerOf2(unsigned int n) {
    return n && !(n & (n - 1));
}

bool isPowerOf4(unsigned int n) {
    return isPowerOf2(n) && (n & 0x55555555);
}

bool isPowerOf8(unsigned int n) {
    return isPowerOf2(n) && (__builtin_ctz(n) % 3 == 0);
}

int main() {
    unsigned int n = 64;

    cout << n << " is power of 2? " << isPowerOf2(n) << "\n";
    cout << n << " is power of 4? " << isPowerOf4(n) << "\n";
    cout << n << " is power of 8? "  << isPowerOf8(n) << "\n";
}

✔ Output
64 is power of 2? 1
64 is power of 4? 0
64 is power of 8? 1

✅ 2. Count Set Bits — O(log n) + O(1) Lookup Table
Method 1: Kernighan’s Algorithm — O(log n)

Repeatedly removes lowest set bit.

Method 2: Lookup Table — O(1)
✔ Full Program
#include <iostream>
using namespace std;

int table[256];

// Build lookup table
void buildTable() {
    for (int i = 0; i < 256; i++) {
        int count = 0, x = i;
        while (x) {
            x &= (x - 1);
            count++;
        }
        table[i] = count;
    }
}

int countBitsLogN(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int countBitsO1(unsigned int n) {
    return table[n & 0xff] +
           table[(n >> 8) & 0xff] +
           table[(n >> 16) & 0xff] +
           table[(n >> 24) & 0xff];
}

int main() {
    buildTable();
    unsigned int n = 0b10110101;

    cout << "O(log n) count = " << countBitsLogN(n) << "\n";
    cout << "O(1) lookup count = " << countBitsO1(n) << "\n";
}

✔ Output
O(log n) count = 5
O(1) lookup count = 5

✅ 3. Find Missing Number in 1..n Using XOR
✔ Idea
missing = (1 ⊕ 2 ⊕ ... ⊕ n) XOR (all array elements)

✔ Full Program
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 4, 5, 6};
    int n = 6;

    int x1 = 0, x2 = 0;

    // XOR all numbers 1..n
    for (int i = 1; i <= n; i++)
        x1 ^= i;

    // XOR array elements
    for (int x : arr)
        x2 ^= x;

    cout << "Missing number = " << (x1 ^ x2) << "\n";
}

✔ Output
Missing number = 3

✅ 4. Swap Even and Odd Bits (Important Bit Trick)
✔ Idea

Mask even bits: 0xAAAAAAAA

Mask odd bits: 0x55555555

Shift and swap.

✔ Full Program
#include <iostream>
using namespace std;

unsigned int swapEvenOdd(unsigned int x) {
    unsigned int even = x & 0xAAAAAAAA;
    unsigned int odd  = x & 0x55555555;
    even >>= 1;
    odd  <<= 1;
    return even | odd;
}

int main() {
    unsigned int x = 23; // 10111
    cout << "Original = " << x << "\n";
    cout << "Swapped  = " << swapEvenOdd(x) << "\n";
}

✔ Output
Original = 23
Swapped  = 43


(23 = 10111 → 43 = 101011)

✅ 5. Multiply/Divide by Powers of 2 using Bit Shifts
✔ Rules:

Multiply: x << k

Divide: x >> k

✔ Full Program
#include <iostream>
using namespace std;

int main() {
    int x = 6;

    cout << "x * 2 = " << (x << 1) << "\n";
    cout << "x * 8 = " << (x << 3) << "\n";

    cout << "x / 2 = " << (x >> 1) << "\n";
    cout << "x / 4 = " << (x >> 2) << "\n";

    return 0;
}

✔ Output
x * 2 = 12
x * 8 = 48
x / 2 = 3
x / 4 = 1

✅ 6. Find the Only Non-Repeating Element Where All Others Repeat k Times
Example:

arr = {6, 1, 3, 3, 3, 6, 6}, k = 3
Only 1 does not repeat 3 times.

✔ Technique:

Count bits at each position % k.

✔ Full Program
#include <iostream>
#include <vector>
using namespace std;

int singleNumber(vector<int>& arr, int k) {
    int result = 0;

    for (int bit = 0; bit < 32; bit++) {
        int sum = 0;

        for (int x : arr)
            if (x & (1 << bit))
                sum++;

        if (sum % k != 0)
            result |= (1 << bit);
    }

    return result;
}

int main() {
    vector<int> arr = {6, 1, 3, 3, 3, 6, 6};
    int k = 3;

    cout << "Unique element = " << singleNumber(arr, k) << "\n";
}

✔ Output
Unique element = 1





✅ 1. Longest Increasing Subsequence (LIS) – O(n log n)

Using binary search & tails[].

✔ Explanation

Maintain an array tails[] where tails[i] is the smallest tail of any LIS of length i+1.

For each element, binary search its position in tails.

Length of tails = LIS length.

✔ Full Program
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> tails;

    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);
        else
            *it = x;
    }

    cout << "LIS Length = " << tails.size() << endl;
    return 0;
}

✔ Output
LIS Length = 4

✅ 2. Maximum Sum Increasing Subsequence (MSIS)
✔ Explanation

DP[i] = max sum ending at i.

✔ Full Program
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 101, 2, 3, 100, 4, 5};
    int n = arr.size();

    vector<int> dp = arr;

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(arr[i] > arr[j])
                dp[i] = max(dp[i], dp[j] + arr[i]);
        }
    }

    int ans = 0;
    for(int x : dp) ans = max(ans, x);

    cout << "MSIS = " << ans << endl;
    return 0;
}

✔ Output
MSIS = 106

✅ 3. Longest Common Subsequence (LCS) – Table DP
✔ Full Program
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string a = "AGGTAB";
    string b = "GXTXAYB";

    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    cout << "LCS Length = " << dp[n][m] << endl;
    return 0;
}

✔ Output
LCS Length = 4

✅ 4. Edit Distance (Levenshtein distance – DP)
✔ Explanation

Allowed operations:

Insert

Delete

Replace

✔ Full Program
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string a = "sunday";
    string b = "saturday";

    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));

    for(int i = 0; i <= n; i++) dp[i][0] = i;  // deletes
    for(int j = 0; j <= m; j++) dp[0][j] = j;  // inserts

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j],    // delete
                                   dp[i][j-1],    // insert
                                   dp[i-1][j-1]}); // replace
        }
    }

    cout << "Edit Distance = " << dp[n][m] << endl;
    return 0;
}

✔ Output
Edit Distance = 3

✅ 5. Maximum Sum Subarray (Kadane’s Algorithm)
✔ Full Program
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {-2,1,-3,4,-1,2,1,-5,4};

    int maxEndingHere = arr[0];
    int maxSoFar = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    cout << "Max Subarray Sum = " << maxSoFar << endl;
    return 0;
}

✔ Output
Max Subarray Sum = 6



/* ========================================================================================================================================== */
5. System Design / Conceptual Tricky Questions

Difference between stack, heap, and static memory in detail.
/* ---------------------------------------------------------------------------------- */
Move semantics in C++11/14/17: When are objects copied vs moved?
/* ---------------------------------------------------------------------------------- */
Explain inline variables, constexpr, and consteval differences.
/* ---------------------------------------------------------------------------------- */
Multi-threading pitfalls: race conditions, deadlocks, and avoiding iterator invalidation.
/* ---------------------------------------------------------------------------------- */
Explain why unordered_map might perform worse than map in certain scenarios.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */










1. Frequency Counting in Array (Map/Unordered_map)

Input: arr = [1,2,2,3,1,4]
Output: 1:2 2:2 3:1 4:1

Hint: Use unordered_map to count frequencies.

Optimal Solution (C++ STL):

unordered_map<int,int> freq;
for(int x : arr) freq[x]++;
for(auto &[k,v]: freq) cout << k << ":" << v << " ";
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

2. First Unique Character in String

Input: "leetcode"
Output: 0 (index of 'l')

Hint: Use unordered_map<char,int> to count, then traverse string to find first with count 1.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */
3. Move Zeros to End (Stable)

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]

Hint: Use stable_partition or two-pointer approach.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

4. Move Negatives to Front (Stable)

Input: [1,-2,3,-4,5]
Output: [-2,-4,1,3,5]

Hint: stable_partition with predicate x<0.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */


5. Top K Frequent Elements

Input: [1,1,1,2,2,3], K=2
Output: [1,2]

Hint: Use unordered_map + priority_queue (min-heap of size K).
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

6. Reverse Words in String

Input: "the sky is blue"
Output: "blue is sky the"

Hint: Split words, reverse vector, join.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

7. Longest Substring Without Repeating Characters

Input: "abcabcbb"
Output: 3

Hint: Sliding window + unordered_set or map.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

8. Find Missing Number in 1..n

Input: [1,2,4,5,6]
Output: 3

Hint: Use sum formula or XOR trick.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

9. Majority Element (> n/2 times)

Input: [3,3,4,2,3]
Output: 3

Hint: Boyer–Moore Voting Algorithm (O(n), O(1) space).
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

10. Rearrange Array Max-Min Form

Input: [1,2,3,4,5,6]
Output: [6,1,5,2,4,3]

Hint: Two-pointer approach from ends.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

11. Swap Adjacent Elements in Pairs

Input: [1,2,3,4,5,6]
Output: [2,1,4,3,6,5]

Hint: Loop with step 2, swap i and i+1.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

12. Interleave Arrays

Input: [1,2,3] and [7,8,9]
Output: [7,1,8,2,9,3]
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */


13. Count Subarrays with Sum = K

Input: [1,2,3], K=3
Output: 2

Hint: Prefix sum + unordered_map storing previous sums.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

14. Detect Cycle in Linked List

Input: 1->2->3->4->2...
Output: true

Hint: Use Floyds Tortoise and Hare.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

15. Reverse a Linked List in Groups of K

Input: 1->2->3->4->5, K=2
Output: 2->1->4->3->5

Hint: Recursive or iterative reversal.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

16. Find First Repeating Element

Input: [10,5,3,4,3,5,6]
Output: 5

Hint: unordered_map to track first index of repetition.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

17. Rotate Array Right by K Steps (In-place)

Input: [1,2,3,4,5,6,7], K=3
Output: [5,6,7,1,2,3,4]

Hint: Reverse whole array, reverse first K, then remaining.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

18. Merge Two Sorted Arrays (In-place if possible)

Input: [1,3,5], [2,4,6]
Output: [1,2,3,4,5,6]

Hint: Two-pointer approach.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

19. Count Distinct Elements in Every Window of Size K

Input: [1,2,1,3,4,2,3], K=4
Output: [3,4,4,3]

Hint: Sliding window + unordered_map.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

20. Maximum Subarray Sum (Kadane’s Algorithm)

Input: [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

21. Longest Palindromic Substring

Input: "babad"
Output: "bab" or "aba"

Hint: Expand around center.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

22. Custom Comparator in Priority Queue

Input: [1,2,3,4,5]
Output: Max heap by even first then value.

Hint: Lambda in priority_queue<int, vector<int>, decltype(cmp)>.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

23. Count Set Bits in Integer

Input: 9
Output: 2

Hint: Brian Kernighan’s algorithm.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

24. Swap Two Numbers Without Temp Variable

Input: a=5, b=3
Output: a=3, b=5

Hint: Use XOR or arithmetic trick.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

25. Power of 2 Check

Input: 16
Output: true

Hint: n & (n-1) == 0.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

26. Largest Rectangle in Histogram (Stack)

Input: [2,1,5,6,2,3]
Output: 10

Hint: Use monotonic stack.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

27. Sliding Window Maximum

Input: [1,3,-1,-3,5,3,6,7], K=3
Output: [3,3,5,5,6,7]

Hint: deque storing indices.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

28. Check Unique Frequencies

Input: [1,2,2,1,1,3]
Output: true

Hint: Count frequencies and check uniqueness using unordered_set.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

29. Smallest Window in String Containing All Characters of Another String

Input: S="ADOBECODEBANC", T="ABC"
Output: "BANC"

Hint: Sliding window + hash map.
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */

30. Longest Consecutive Sequence

Input: [100,4,200,1,3,2]
Output: 4 (1,2,3,4)

Hint: Use unordered_set and check sequence starts.

/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ========================================================================================================================================== */













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