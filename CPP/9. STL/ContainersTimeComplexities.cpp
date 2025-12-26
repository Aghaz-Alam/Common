✅ STL Containers- Time Complexity: each container + common operations + complexity + explanation.

1. std::array<T, N>
A fixed-size static array.

| Operation           | Complexity |
| ------------------- | ---------- |
| Access `arr[i]`     | **O(1)**   |
| Update `arr[i] = x` | **O(1)**   |

✔ No insert/erase (size fixed)
✔ No dynamic allocations


//Memory Model Diagram
std::array — Fixed Static Layout
Stack / Global Memory
+---------+---------+---------+---------+---------+
| arr[0]  | arr[1]  | arr[2]  | arr[3]  | arr[4]  |
+---------+---------+---------+---------+---------+

✔ Stored contiguously
✔ Fixed size at compile time
✔ No heap dynamic allocation


/* ============================================================================================================ */

2. std::vector<T>
Dynamic contiguous array.

| Operation     | Average            | Worst-case           | Notes                 |
| ------------- | ------------------ | -------------------- | --------------------- |
| `push_back()` | **O(1)** amortized | O(N) on reallocation | Doubling reallocation |
| `pop_back()`  | **O(1)**           | O(1)                 |                       |
| `operator[]`  | **O(1)**           | O(1)                 |                       |
| `insert(pos)` | O(N)               | O(N)                 | Move elements         |
| `erase(pos)`  | O(N)               | O(N)                 | Shift elements        |
| `size()`      | O(amortized1)               | O(1)                 |                       |
| `reserve(n)`  | O(N)               | —                    | Copies elements       |

👉 Yes, vector “knows” that push_back is  O(1).
Because it uses geometric growth (usually ×2).



//Memory Model Diagram
std::vector — Dynamic Contiguous Array
Heap:
+---------+---------+---------+---------+--------+
| v[0]    | v[1]    | v[2]    | v[3]    |  ...   |
+---------+---------+---------+---------+--------+
              ↑ size
                              ↑ capacity (extra space)


✔ Contiguous → fast random access
✔ Auto-grows (capacity doubles → O(1) amortized push_back)


Note:
vector::push_back() = O(1) amortized
occasional reallocation → O(N) but rare
overall → almost always O(1)

/* ============================================================================================================ */

3. std::deque<T>
Double-ended segmented array.

| Operation              | Complexity |
| ---------------------- | ---------- |
| push_front/push_back   | **O(1)**   |
| pop_front/pop_back     | **O(1)**   |
| random access          | **O(1)**   |
| insert/erase in middle | O(N)       |



//Memory Model Diagram
std::deque — Segmented Blocks
Index Table:
+-----+-----+-----+
| B0  | B1  | B2  |
+-----+-----+-----+
    |     |     |
Blocks (each block is contiguous)
+----+----+----+----+
|0 1 |2 3 |4 5 |6 7 |
+----+----+----+----+


✔ Random access O(1)
✔ Fast push_front + push_back
✘ Memory not contiguous

/* ============================================================================================================ */

4. std::list<T>
Doubly linked list.

| Operation              | Complexity |
| ---------------------- | ---------- |
| insert at position     | **O(1)**   |
| erase at position      | **O(1)**   |
| push_front / push_back | O(1)       |
| pop_front / pop_back   | O(1)       |
| search                 | **O(N)**   |
| splice                 | **O(1)**   |



//Memory Model Diagram
std::list — Doubly Linked Nodes
+------+     +------+     +------+
|prev|*---->|prev|*---->|prev|*--->NULL
| 10  |     | 20  |     | 30  |
|*----|<----*|next|<----*|next|
+------+     +------+     +------+


✔ Insert/delete anywhere O(1)
✘ Search O(N)
✘ Not cache-friendly

/* ============================================================================================================ */

5. std::forward_list<T>
| Operation    | Complexity |
| ------------ | ---------- |
| insert_after | **O(1)**   |
| erase_after  | **O(1)**   |
| push_front   | **O(1)**   |
| search       | **O(N)**   |


//Memory Model Diagram
std::forward_list — Singly Linked
HEAD → [10|*] → [20|*] → [30|NULL]

✔ Minimal memory
✔ Insert after → O(1)
✘ No back pointer

Note:
list and forward_list have O(1) insert/delete
Because they only adjust pointers.
/* ============================================================================================================ */

6. std::stack<T>
Adapter (usually uses vector or deque).

| Operation | Complexity         |
| --------- | ------------------ |
| push      | **O(1)** amortized |
| pop       | **O(1)**           |
| top       | **O(1)**           |

Depends on underlying container:
default: deque → O(1)
with vector → O(1) amortized


//Memory Model Diagram
std::stack / std::queue — Container Adapters
stack → uses vector | deque | list underneath
queue → uses deque underneath

/* ============================================================================================================ */

7. std::queue<T>
Adapter (uses deque by default).

| Operation  | Complexity |
| ---------- | ---------- |
| push       | O(1)       |
| pop        | O(1)       |
| front/back | O(1)       |



//Memory Model Diagram
std::stack / std::queue — Container Adapters
stack → uses vector | deque | list underneath
queue → uses deque underneath

/* ----------------------------------------------- */
Note:
deque is NOT fully contiguous
But provides O(1) random access using multiple blocks.
/* ============================================================================================================ */

8. std::priority_queue<T>
Binary heap.

| Operation | Complexity   |
| --------- | ------------ |
| push      | **O(log N)** |
| pop       | **O(log N)** |
| top       | **O(1)**     |


Note:
priority_queue = heap
push/pop → O(log N)
/* ============================================================================================================ */

9. std::set<T> (balanced Red-Black tree)
Ordered, unique elements.

| Operation   | Complexity   |
| ----------- | ------------ |
| insert      | **O(log N)** |
| erase       | **O(log N)** |
| find        | **O(log N)** |
| lower_bound | **O(log N)** |
| traversal   | **O(N)**     |


//Memory Model Diagram
std::set / std::map — Red-Black Tree
         (20,B)
        /       \
    (10,R)     (30,R)


✔ Always balanced
✔ All operations O(log N)

Note:
set/map are always O(log N)
Because they are implemented using Red-Black Trees (balanced BST).

/* ============================================================================================================ */

10. std::map<K, V> (ordered RB-tree)
| Operation  | Complexity |
| ---------- | ---------- |
| insert     | O(log N)   |
| erase      | O(log N)   |
| operator[] | O(log N)   |
| find       | O(log N)   |


//Memory Model Diagram
std::set / std::map — Red-Black Tree
         (20,B)
        /       \
    (10,R)     (30,R)


✔ Always balanced
✔ All operations O(log N)


Note:
set/map are always O(log N)
Because they are implemented using Red-Black Trees (balanced BST).


unordered_set/map average O(1)
But worst-case O(N) due to hashing collisions.
/* ============================================================================================================ */

11. std::unordered_set<T>
Hash table.

| Operation | Average  | Worst-case |
| --------- | -------- | ---------- |
| insert    | **O(1)** | O(N)       |
| erase     | **O(1)** | O(N)       |
| find      | **O(1)** | O(N)       |
| rehash    | O(N)     | —          |

Worst-case is O(N) due to collisions chaining.


//Memory Model Diagram
std::unordered_set / std::unordered_map — Hash Table
Buckets:
0 →  [--]
1 →  [15] → [85] → nullptr
2 →  [--]
3 →  [25] → nullptr


✔ O(1) average insert/find
✘ Worst case O(N) (when many keys collide)

Note:
unordered_set/map average O(1)
But worst-case O(N) due to hashing collisions.
/* ============================================================================================================ */

12. std::unordered_map<K,V>
Same as unordered_set, but key-value pairs.

| Operation  | Avg  | Worst |
| ---------- | ---- | ----- |
| insert     | O(1) | O(N)  |
| erase      | O(1) | O(N)  |
| find       | O(1) | O(N)  |
| operator[] | O(1) | O(N)  |


Do inbuilt STL functions change time complexity?
NO — time complexities do not change.



//Memory Model Diagram
std::unordered_set / std::unordered_map — Hash Table
Buckets:
0 →  [--]
1 →  [15] → [85] → nullptr
2 →  [--]
3 →  [25] → nullptr


✔ O(1) average insert/find
✘ Worst case O(N) (when many keys collide)

/* ============================================================================================================ */
Every STL container has well-defined complexity guarantees given by the C++ standard.

Examples:
🔹 std::vector::push_back()
   ->Amortized O(1)
   ->Worst-case O(N) on reallocation

🔹 std::set::insert()
   ->Always O(log N) because tree height = log N

🔹 std::unordered_map::find()
   ->Average O(1)
   ->Worst O(N) due to chaining

🔹 std::list::insert()
   ->Always O(1) because inserting node requires no shifting


/* ============================================================================================================ */

Why do complexities stay fixed?
Because:
STL containers follow strict complexity requirements defined in the C++ Standard.
Implementations (libstdc++, libc++, MSVC STL) must obey them.
Even if algorithms or optimizations change, asymptotic complexity does not change.


/* ============================================================================================================ */
Summary Table (Cheat Sheet)
| Container             | Access   | Insert      | Erase     | Search   |
| --------------------- | -------- | ----------- | --------- | -------- |
| **vector**            | O(1)     | O(1)* amort | O(N)      | O(N)     |
| **deque**             | O(1)     | O(1) ends   | O(1) ends | O(N)     |
| **list**              | O(N)**   | O(1)        | O(1)      | O(N)     |
| **forward_list**      | O(N)     | O(1)        | O(1)      | O(N)     |
| **set/map**           | O(log N) | O(log N)    | O(log N)  | O(log N) |
| **unordered_set/map** | O(1)*    | O(1)*       | O(1)*     | O(1)*    |
/* ============================================================================================================ */




STL Containers — Time Complexity

Sequence Containers
| Container        | Access   | Insert          | Delete          | Search |
| ---------------- | -------- | --------------- | --------------- | ------ |
| **array**        | O(1)     | ✘               | ✘               | O(N)   |
| **vector**       | **O(1)** | O(1)* amort     | O(N)            | O(N)   |
| **deque**        | O(1)     | O(1) front/back | O(1) front/back | O(N)   |
| **list**         | O(N)     | **O(1)**        | **O(1)**        | O(N)   |
| **forward_list** | O(N)     | O(1)            | O(1)            | O(N)   |

/* ----------------------------------------------------------------------- */
Associative Containers (Ordered — Red-Black Tree)
| Container          | Insert       | Find         | Delete   |
| ------------------ | ------------ | ------------ | -------- |
| **set / multiset** | **O(log N)** | **O(log N)** | O(log N) |
| **map / multimap** | **O(log N)** | **O(log N)** | O(log N) |

/* ---------------------------------------------------------------------- */
Unordered Containers (Hash Table)
| Container             | Avg Insert | Worst Insert | Avg Find | Worst Find |
| --------------------- | ---------- | ------------ | -------- | ---------- |
| **unordered_set/map** | **O(1)**   | **O(N)**     | **O(1)** | **O(N)**   |

✔ Fast but not sorted
✔ Collisions → worst case O(N)

/* ---------------------------------------------------------------------- */
Container Adapters
| Container          | push         | pop          | top/front/back |
| ------------------ | ------------ | ------------ | -------------- |
| **stack**          | O(1)         | O(1)         | O(1)           |
| **queue**          | O(1)         | O(1)         | O(1)           |
| **priority_queue** | **O(log N)** | **O(log N)** | O(1)           |

/* ============================================================================================================= */
Note:
Random access exists only for:
✔ array
✔ vector
✔ deque
✘ NOT for list, forward_list, set, map, unordered_set, unordered_map


/* ------------------------------------------------------------- */

/* =============================================================================================================== */
                                SECTION 1 — Containers & Time Complexities
/* =============================================================================================================== */
1. What is the difference between vector and array?
Answer:
array → fixed size, compile-time, stack or global memory
vector → dynamic size, heap allocation, automatic resizing
Both provide O(1) random access.


2. Why is vector::push_back() O(1) amortized?
Answer:
Because vector uses geometric growth (usually ×2).
Most push_back() operations do nothing but place the element.
Rarely, reallocation → O(N).
Average → O(1).


3. Which containers provide O(1) random access?
✔ array
✔ vector
✔ deque
❌ NOT: list, forward_list, set, map, unordered_map, unordered_set


4. Which STL container provides O(1) insertion at the beginning?
deque
list
forward_list
vector cannot do it (O(N)).


5. Difference between list and forward_list?
list: doubly linked → can go forward & backward
forward_list: singly linked → forward only, lighter
Complexity: Insert/Delete → O(1) for both.


6. Why is list slower than vector despite O(1) insert/delete?
Answer:
Because of:
Poor cache locality
Memory fragmentation
Pointer chasing
Allocating each node on heap
Vector = contiguous memory → much faster in practice.


7. set / map time complexities?
All operations: O(log N)
Because implemented using Red-Black Trees.


8. unordered_map average vs worst case?
Average: O(1) (hash lookup)
Worst: O(N) (hash collisions, bucket chaining)


9. Why is unordered_map faster than map?
unordered_map = hash table → O(1) average
map = tree → O(log N)


10. When will unordered_map be slower than map?
Many collisions
Poor custom hash
Rehashing cost
Iterator invalidation during rehash

/* =============================================================================================================== */
                                SECTION 2 — Memory & Internals
/* =============================================================================================================== */

11. How does vector grow internally?
Geometric growth (typically ×2 capacity).
On reallocation:
new memory block allocated
old elements copied/moved
old memory freed


12. What causes vector iterators to invalidate?
On reallocation
On insert/erase in the middle
push_back() invalidates iterators only if capacity increases.


13. Which containers never invalidate iterators?
list
forward_list
(Except iterator pointing to erased element.)


14. Why doesn’t deque store elements contiguously?
Because supporting push_front with contiguous memory is hard.
Deque uses segmented memory blocks + central index.


15. Why can’t list support random access?
Because nodes are not contiguous, require pointer chasing → O(N).


16. Where does priority_queue store elements?
In a binary heap stored inside a vector.


17. Why is set ordered but unordered_set not?
set = Red-Black Tree
unordered_set = Hash table
Hash tables destroy ordering.



/* =============================================================================================================== */
                                SECTION 3 — Iterators & Algorithms
/* =============================================================================================================== */

18. Types of iterators in C++?
| Iterator Type | Example Containers   |
| ------------- | -------------------- |
| Input         | istream_iterator     |
| Output        | ostream_iterator     |
| Forward       | forward_list         |
| Bidirectional | list, set, map       |
| Random Access | vector, deque, array |


19. Why are algorithms not part of containers?
Because algorithms operate on iterators, which make them generic.
E.g., sort(), find(), reverse(), etc.


20. Can you sort a list using std::sort()?
No.
list has bidirectional iterators, but sort() needs random access.
Use: list.sort().


21. What is the complexity of std::sort()?
Average: O(N log N)
Worst case: O(N log N) (introsort → hybrid of quicksort + heapsort)


22. Can we use binary_search on vector after push_back()?
Only if:
vector remains sorted
push_back() inserted element in correct sorted position
Otherwise binary_search gives undefined results.


/* =============================================================================================================== */
                                SECTION 4 — Maps, Hashing & Comparison
/* =============================================================================================================== */

23. Difference between map::operator[] and map::at()?

operator[]: inserts a new key if not found

at(): throws exception if key not found

24. Why unordered_map does not support key ordering?

Because hashing destroys any ordering information.

25. How does unordered_map resolve collisions?

Using separate chaining (linked lists or bucket arrays).

26. What is load factor in unordered_map?
load_factor = size / number_of_buckets


High load factor → slow operations → rehash.

27. What is rehashing?

Resizing the bucket array + reassigning keys.
Time: O(N).

28. When should you use map instead of unordered_map?

When ordering is required

When you need slow worst-case guarantees

When keys are custom complex types with no good hash

29. Can unordered_map use custom hash?

Yes:

unordered_map<Key, Value, MyHash, MyEqual> mp;



/* =============================================================================================================== */
                                SECTION 5 — Tricky / Advanced Questions
/* =============================================================================================================== */
30. Why is vector faster than list for most workloads?
Because:
contiguous memory ⇒ cache-friendly
fewer allocations
fewer pointers
better prefetching
Even O(N) insert shifts are often faster than O(1) linked list insert.



31. Does vector shrink its capacity automatically?
No.
Even after erase/clear, capacity remains the same.
Use:
v.shrink_to_fit();




32. Why is list removal slower in practice?
Although O(1), each node access is a slow pointer dereference.
Poor CPU cache locality.



33. Difference between erase() in list and vector?
list.erase(it) → O(1)
vector.erase(it) → O(N) (shift elements)



34. Does map store elements contiguously?
No.
Each node is on the heap (tree structure).



35. Why can’t we use std::sort on set/map?
They are not random access containers.
Also, set/map are ALWAYS sorted internally.



36. Which STL containers store elements sorted?
set
multiset
map
multimap
Implementations guarantee ordered traversal.



37. Which containers support binary search algorithms?
Algorithms require sorted + random access:
vector
array
deque (but rarely used)



38. What happens if unordered_map rehashes while iterating?
Iterator becomes invalid.
Only erase() of current element is safe.



39. Why is priority_queue not iterable in sorted order?
Because it stores data in heap-order, not sorted order.
If you want sorted traversal:
Use multiset instead.



40. What is the best STL container for LRU Cache?
Combination:
unordered_map  → O(1) lookup
list           → O(1) erase/move

Industry-standard LRU implementation.



/* =============================================================================================================== */
                                SECTION 1 — Vector & Array Problems
/* =============================================================================================================== */
1. Reverse a vector
reverse(v.begin(), v.end());



2. Check if array is sorted
is_sorted(v.begin(), v.end());



3. Rotate vector by k
rotate(v.begin(), v.begin() + k, v.end());



4. Remove duplicates from a sorted vector
v.erase(unique(v.begin(), v.end()), v.end());



5. Find max & min in vector
auto mx = *max_element(v.begin(), v.end());
auto mn = *min_element(v.begin(), v.end());



6. Frequency of elements
unordered_map<int,int> freq;
for(int x : v) freq[x]++;



7. Sort vector of pairs by second value
sort(v.begin(), v.end(), [](auto &a, auto &b){
    return a.second < b.second;
});



8. Custom comparator sort (descending)
sort(v.begin(), v.end(), greater<int>());



/* -------------std::vetor---------------- */
Q1. Reverse a vector without using reverse()
for (int i=0, j=v.size()-1; i<j; i++, j--)
    swap(v[i], v[j]);


    
Q2. Remove all even numbers
v.erase(remove_if(v.begin(), v.end(),
                  [](int x){ return x%2==0; }),
        v.end());



Q3. Find frequency of each number
unordered_map<int,int> mp;
for(int x : v) mp[x]++;



Q4. Sort vector descending
sort(v.begin(), v.end(), greater<int>());



Q5. Check if vector is palindrome
v == vector<int>(v.rbegin(), v.rend());



Q6. Remove duplicates from sorted vector
v.erase(unique(v.begin(), v.end()), v.end());



Q7. Rotate vector by k
rotate(v.begin(), v.begin()+k, v.end());



Q8. Vector → Set
set<int> s(v.begin(), v.end());



Q9. Find 2nd largest
nth_element(v.begin(), v.end()-2, v.end());
int ans = *(v.end()-2);



Q10. Find all indices of an element
vector<int> idx;
for(int i=0;i<v.size();i++)
    if(v[i] == key) idx.push_back(i);



Q11. Count elements greater than x
int cnt = count_if(v.begin(), v.end(), [&](int t){ return t > x; });



Q12. Sum of vector
int sum = accumulate(v.begin(), v.end(), 0);



Q13. Stable partition (even left, odd right)
stable_partition(v.begin(), v.end(), [](int x){return x%2==0;});



Q14. Find Kth smallest
nth_element(v.begin(), v.begin()+k-1, v.end());



Q15. Insert element at position
v.insert(v.begin()+pos, x);


/* =============================================================================================================== */
                                SECTION 2 — Set / Map Problems
/* =============================================================================================================== */
9. Print unique sorted elements
set<int> s(v.begin(), v.end());



10. Count occurrences using map
map<int,int> mp;
for(int x: v) mp[x]++;



11. Find lower_bound & upper_bound
auto it = s.lower_bound(k);
auto jt = s.upper_bound(k);



12. Find the first greater element
auto it = s.upper_bound(x);



13. Erase by key and iterate
s.erase(key);
for (auto &x : s) cout << x;



14. Find floor of x in set
auto it = s.upper_bound(x);
if(it == s.begin()) return -1;
--it;
return *it;



15. Merge two sets
set<int> r;
r.insert(a.begin(), a.end());
r.insert(b.begin(), b.end());


/* -------------------std::ordered_set-------------------- */

Q1. Insert and check existence
if(s.count(x)) ...



Q2. Find floor value
auto it = s.upper_bound(x);
if(it == s.begin()) return -1;
return *(--it);



Q3. Find ceil value
auto it = s.lower_bound(x);



Q4. Remove element
s.erase(x);



Q5. Print sorted unique
for (int x : s) cout << x;



Q6. Convert set → vector
vector<int> v(s.begin(), s.end());



Q7. Union of two sets
set<int> ans;
ans.insert(a.begin(), a.end());
ans.insert(b.begin(), b.end());



Q8. Intersection
for (int x : a) 
    if (b.count(x)) ans.insert(x);



Q9. Find closest element
Use lower_bound() + neighbor check.



Q10. Largest and smallest element
*begin(s);  
*prev(s.end());


/* -------------------------std::map------------------- */

Q1. Count characters
map<char,int> mp;
for(char c : s) mp[c]++;



Q2. Print map sorted by keys
for (auto &p : mp)
    cout << p.first << " " << p.second;



    Q3. Find lower_bound / upper_bound
mp.lower_bound(key);
mp.upper_bound(key);



Q4. Check presence
if (mp.count(key)) ...



Q5. Insert if key not present
mp.insert({k, v});



Q6. Update value
mp[k] = newVal;



Q7. Map to vector of pairs
vector<pair<int,int>> v(mp.begin(), mp.end());



Q8. Erase by key
mp.erase(key);



Q9. First element in map
auto it = mp.begin();



Q10. Last element in map
auto it = prev(mp.end());

/* =============================================================================================================== */
                                SECTION 3 — Unordered Map / Set Problems (Highly used in coding rounds!)
/* =============================================================================================================== */
16. Two Sum
unordered_map<int,int> mp;
for(int i=0;i<n;i++){
    if(mp.count(target - v[i])) return {mp[target-v[i]], i};
    mp[v[i]] = i;
}



17. Longest subarray with zero sum
unordered_map<int,int> mp;
mp[0] = -1;
int sum = 0, ans = 0;
for(int i=0;i<n;i++){
    sum += v[i];
    if(mp.count(sum)) ans = max(ans, i - mp[sum]);
    else mp[sum] = i;
}



18. Count distinct elements
unordered_set<int> s(v.begin(), v.end());



19. First repeating element
unordered_set<int> seen;
for(int x : v)
    if(!seen.insert(x).second) return x;



20. Majority element
unordered_map<int,int> mp;
for(int x : v) if(++mp[x] > n/2) return x;

/* -------------- unordered_map -------------------------*/
Q1. Two Sum
for(int i=0;i<n;i++){
    if(mp.count(target-v[i])) return {mp[target-v[i]], i};
    mp[v[i]] = i;
}



Q2. Longest subarray with zero sum
unordered_map<int,int> mp;
mp[0] = -1;



Q3. First non-repeating character
for(char c:s) if(mp[c]==1) return c;



Q4. Check if all chars are unique
unordered_set<char> st(s.begin(), s.end());



Q5. Majority element
for(int x:v) if(++mp[x] > n/2) return x;



Q6. Check if arrays are anagrams
unordered_map<char,int> mp;



Q7. Frequency sort
Use map + custom sort.



Q8. Intersection of 2 arrays
if (s.count(x)) ans.push_back(x);



Q9. Duplicate detection
if (!st.insert(x).second) return true;



Q10. Group anagrams
unordered_map<string, vector<string>> mp;

/* =============================================================================================================== */
                                SECTION 4 — Priority Queue Problems(heap-based questions)
/* =============================================================================================================== */

21. K largest elements
priority_queue<int> pq(v.begin(), v.end());



22. K smallest elements
priority_queue<int> pq;            // max-heap
for(int x : v){
    pq.push(x);
    if(pq.size() > k) pq.pop();
}



23. Find median of a stream
Use 2 heaps:
maxHeap = left
minHeap = right
Classic.



24. Merge K sorted arrays
Use min-heap:
priority_queue <pair<int,pair<int,int>>, vector<...>, greater<...>> pq;



25. Sort a nearly sorted array (k-sorted array)
priority_queue<int,vector<int>,greater<int>> pq;


/* -------------------PRIORITY_QUEUE (Heap)---------------- */

Q1. K largest elements
priority_queue<int> pq(v.begin(), v.end());



Q2. K smallest elements
priority_queue<int> pq;



Q3. Max heap and Min heap
priority_queue<int> maxH;
priority_queue<int, vector<int>, greater<int>> minH;



Q4. Sort using heap
while(!pq.empty()) { ans.push_back(pq.top()); pq.pop(); }



Q5. K closest numbers
Use min-heap on absolute diff.



Q6. Merge K sorted lists
Store {value, listIndex, elementIndex} in minHeap.



Q7. Median of stream
Use two heaps.



Q8. Check if max-heap
is_heap(v.begin(), v.end());



Q9. Convert vector → heap
make_heap(v.begin(), v.end());



Q10. Pop largest element
pop_heap(v.begin(), v.end());
v.pop_back();

/* =============================================================================================================== */
                                SECTION 5 — List / Forward List Problems
/* =============================================================================================================== */

26. Remove all occurrences from list
lst.remove(x);



27. Sort a list
lst.sort();



28. Merge two sorted lists
l1.merge(l2);



29. Reverse a list
lst.reverse();



30. Unique consecutive removal on list
lst.unique();


/* -----------------------List------------------- */
Q1. Insert in middle
auto it = next(lst.begin(), pos);
lst.insert(it, x);



Q2. Remove all occurrences
lst.remove(x);



Q3. Sort list
lst.sort();



Q4. Merge two sorted lists
l1.merge(l2);



Q5. Reverse list
lst.reverse();



Q6. Remove consecutive duplicates
lst.unique();



Q7. Iterate and erase
for(auto it = lst.begin(); it != lst.end(); )
    if(*it < 0) it = lst.erase(it);
    else ++it;



Q8. Splice one list into another
l1.splice(pos, l2);



Q9. Remove odd numbers
lst.remove_if([](int x){ return x%2 != 0; });



Q10. Convert list → vector
vector<int> v(lst.begin(), lst.end());


/* =============================================================================================================== */
                                SECTION 6 — Algorithm Problems (Most Important)
/* =============================================================================================================== */

31. Check if two strings are anagrams
sort(a.begin(), a.end());
sort(b.begin(), b.end());
return a == b;



32. Partition vector based on condition
partition(v.begin(), v.end(), [](int x){ return x%2==0; });



33. Upper bound / lower bound on vector
lower_bound(v.begin(), v.end(), k);
upper_bound(v.begin(), v.end(), k);



34. Remove all zeros
v.erase(remove(v.begin(), v.end(), 0), v.end());



35. Counting with count_if
int cnt = count_if(v.begin(), v.end(), [](int x){return x%2==0;});



36. Binary search
binary_search(v.begin(), v.end(), target);

/* =============================================================================================================== */
                                SECTION 7 — Iterator Problems
/* =============================================================================================================== */

37. Iterate a map in sorted key order
for (auto &p : mp) cout << p.first << p.second;



38. Reverse iterate vector
for(auto it = v.rbegin(); it != v.rend(); it++)
    cout << *it;



39. Delete while iterating (list)
for(auto it = lst.begin(); it != lst.end(); ){
    if(*it < 0) it = lst.erase(it);
    else ++it;
}



40. Convert set to vector
vector<int> v(s.begin(), s.end());


/* -------------------ITERATORS------------ */

Q1. Reverse iterate a vector
for(auto it = v.rbegin(); it != v.rend(); it++)



Q2. Iterate map
for(auto &p : mp)
    cout << p.first << p.second;



Q3. Delete while iterating (list)
✔ Already shown above.


Q4. Distance between iterators
int d = distance(it1, it2);



Q5. Advance iterator
advance(it, 3);



Q6. next() and prev()
auto it2 = next(it);
auto it3 = prev(it);



Q7. Backward iteration using prev()
for(auto it = prev(v.end()); ; it--)



Q8. Iterator to middle
auto mid = next(v.begin(), v.size()/2);



Q9. Find element using find()
auto it = find(v.begin(), v.end(), x);



Q10. Count using iterator
count(v.begin(), v.end(), x);



/* =============================================================================================================== */
                                 SECTION 8 — Mixed STL Coding Problems(Asked in real interviews)
/* =============================================================================================================== */

41. LRU Cache
Use:
unordered_map + list



42. LFU Cache
Use:
unordered_map + set or multiset



43. Sliding Window Maximum
Use:
deque (monotonic queue)



44. Find duplicate in array (one extra space allowed)
unordered_set<int> s;
for(int x: v)
    if(!s.insert(x).second) return x;



45. Top K frequent elements
unordered_map + priority_queue.



46. Intersection of two arrays
unordered_set<int> s(a.begin(), a.end());
vector<int> ans;
for(int x: b) if(s.count(x)) ans.push_back(x);



47. Union of two arrays
unordered_set<int> s(a.begin(), a.end());
s.insert(b.begin(), b.end());



48. Find first non-repeating element
unordered_map<char,int> mp;
for(char c: s) mp[c]++;
for(char c: s) if(mp[c]==1) return c;



49. Frequency sort
unordered_map<int,int> mp;
sort(v.begin(), v.end(), [&](int a, int b){
    if (mp[a] == mp[b]) return a < b;
    return mp[a] < mp[b];
});



50. Group Anagrams
unordered_map<string, vector<string>> mp;
for (auto &s : strs){
    string t = s;
    sort(t.begin(), t.end());
    mp[t].push_back(s);
}


/* =========================================================================================================================== */
/* ------------ALGORITHMS------------------ */

Q1. Check sorted
is_sorted(v.begin(), v.end());



Q2. Binary search
binary_search(v.begin(), v.end(), key);



Q3. next_permutation
next_permutation(s.begin(), s.end());



Q4. Partition vector
partition(v.begin(), v.end(), [](int x){return x%2==0;});



Q5. Max element
*max_element(v.begin(), v.end());



Q6. Sum
accumulate(v.begin(), v.end(), 0);



Q7. Remove an element
v.erase(remove(v.begin(), v.end(), x), v.end());



Q8. Count occurrences
count(v.begin(), v.end(), x);



Q9. transform() (square each element)
transform(v.begin(), v.end(), v.begin(), [](int x){return x*x;});



Q10. unique()
v.erase(unique(v.begin(), v.end()), v.end());



Q11. nth_element()
nth_element(v.begin(), v.begin()+k, v.end());



Q12. Find mismatch between 2 vectors
mismatch(a.begin(), a.end(), b.begin());



Q13. Find first element satisfying condition
find_if(v.begin(), v.end(), [](int x){return x>10;});



Q14. Stable sort
stable_sort(v.begin(), v.end());



Q15. Reverse a string
reverse(s.begin(), s.end());

/* ===================================================================================================================== */
                                       Coding Questions on STL
/* ===================================================================================================================== */
Coding Q1 — Remove duplicates from vector (keep order)
Answer:
vector<int> removeDup(vector<int>& v) {
    unordered_set<int> seen;
    vector<int> out;

    for (int x : v)
        if (!seen.count(x)) {
            seen.insert(x);
            out.push_back(x);
        }

    return out;
}


/* -------------------------------------- */
Coding Q2 — Frequency of characters using map
Answer:
map<char,int> freq;
for(char c: s) freq[c]++;
for(auto &p : freq)
    cout << p.first << " = " << p.second << endl;


/* -------------------------------------- */
Coding Q3 — Find 2-sum using unordered_map
Answer:
vector<int> twoSum(vector<int>& v, int target){
    unordered_map<int,int> mp;

    for(int i=0;i<v.size();i++){
        int need = target - v[i];
        if(mp.count(need))
            return {mp[need], i};
        mp[v[i]] = i;
    }
    return {};
}


/* -------------------------------------- */
Coding Q4 — Top K largest elements using priority_queue
Answer:
priority_queue<int> pq(v.begin(), v.end());
while(k-- && !pq.empty()){
    cout << pq.top() << " ";
    pq.pop();
}


/* -------------------------------------- */
Coding Q5 — Sort list + remove negative numbers
Answer:
li.remove_if([](int x){ return x < 0; });
li.sort();


/* -------------------------------------- */
Coding Q6 — Iterators: print vector in reverse
Answer:
for(auto it = v.rbegin(); it != v.rend(); it++)
    cout << *it << " ";


/* -------------------------------------- */
Coding Q7 — Using algorithms: partition even/odd
Answer:
partition(v.begin(), v.end(), [](int x){
    return x % 2 == 0;
});


/* -------------------------------------- */
Coding Q8 — Find 1st unique element using unordered_map
Answer:
unordered_map<int,int> freq;
for(int x: v) freq[x]++;
for(int x: v)
    if(freq[x] == 1) return x;


/* -------------------------------------- */
Coding Q9 — Custom sort using comparator
Answer
sort(v.begin(), v.end(), [](int a, int b){
    if (a%2 == b%2) return a < b;
    return a%2 < b%2;   // even first
});

/* -------------------------------------- */
Coding Q10 — LRU Cache (STL based)
Answer:
class LRUCache {
    int cap;
    list<int> dq;
    unordered_map<int, list<int>::iterator> mp;

  public:
    LRUCache(int c) : cap(c) {}

    void refer(int x){
        if (!mp.count(x)) {
            if(dq.size() == cap){
                mp.erase(dq.back());
                dq.pop_back();
            }
        } else dq.erase(mp[x]);

        dq.push_front(x);
        mp[x] = dq.begin();
    }
};


/* ====================================================================================================== */
                                   STL Quick Revision Cheat Sheet
/* ====================================================================================================== */
Vector
Dynamic array
Fast: O(1) push_back amortized
Bad at: insertion/deletion middle (O(n))
Iterators invalidated on reallocation


Deque
Double-ended vector
O(1) push_front & push_back
Random access supported


List
Doubly linked list
No random access
Insert/erase O(1)



Forward List
Singly linked list
FASTEST insertion
Lightweight



Set
Balanced BST (RB-tree)
Sorted keys
All ops O(log n)



Map
Balanced BST
Key + Value
Ordered traversal



Unordered Set / Map
Hash table
Average O(1), worst O(n)
No order



Priority Queue
Heap
push/pop: O(log n)



Stack / Queue
ADAPTERS over deque



Algorithms (must know)
sort(), stable_sort()
reverse()
max_element()
binary_search()
lower_bound()
upper_bound()
unique()
accumulate()
/* ======================================================================================================= */