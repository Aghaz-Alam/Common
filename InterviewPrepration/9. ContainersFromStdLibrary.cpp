C++ containers from std library 


✅ C++ Standard Library Containers (from <vector>, <map>, etc.)
C++ STL containers are grouped into 4 main categories:
/* --------------------------------------------------------------------------------------------------- */
1. Sequence Containers
/* ------------------Maintain elements in linear order.----------------------- */
✔ 1.1 std::vector
Dynamic array (contiguous memory)
Fast random access: O(1)
Insert/remove at end: O(1) amortized
Insert/remove in middle: O(n)
Best default choice

vector<int> v = {1, 2, 3};
v.push_back(4);
cout << v[2];       // 3


/* ---------------Complete code------------------- */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Creating and initializing a vector
    vector<int> v = {1, 2, 3};

    // Insert at end (O(1) amortized)
    v.push_back(4);

    // Random access (O(1))
    cout << "Element at index 2: " << v[2] << endl;

    // Print complete vector
    cout << "Vector elements: ";
    for (int x : v)
        cout << x << " ";

    return 0;
}
/*
Element at index 2: 3
Vector elements: 1 2 3 4 
*/
/* ----------------------------------------- */

✔ 1.2 std::deque
Double-ended queue
Fast insertion/removal at both ends: O(1)
Not contiguous like vector
Good for queues, BFS

deque<int> dq;
dq.push_front(1);
dq.push_back(2);

/* -------------complete the code---------- */
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> dq;

    // Insert at both ends (O(1))
    dq.push_front(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);

    // Access elements
    cout << "Front element: " << dq.front() << endl;
    cout << "Back element: " << dq.back() << endl;

    // Print complete deque
    cout << "Deque elements: ";
    for (int x : dq)
        cout << x << " ";

    // Removing from both ends
    dq.pop_front();
    dq.pop_back();

    cout << "\nAfter pop operations: ";
    for (int x : dq)
        cout << x << " ";

    return 0;
}
/*
Front element: 0
Back element: 3
Deque elements: 0 1 2 3 
After pop operations: 1 2 
*/

/* ----------------------------------------- */
✔ 1.3 std::list
Doubly-linked list
Insert/remove anywhere: O(1)
Slow traversal, no random access
Use when many middle insertions

list<int> l = {1,2,3};
l.insert(next(l.begin(),1), 10);

/* ------complet the code--------*/
#include <iostream>
#include <list>
using namespace std;

int main() {
    // Initialize list
    list<int> l = {1, 2, 3};

    // Insert 10 at the 2nd position (middle insert, O(1))
    auto it = next(l.begin(), 1); // points to element '2'
    l.insert(it, 10);             // list becomes: 1, 10, 2, 3

    // Print all elements
    cout << "List elements: ";
    for (int x : l)
        cout << x << " ";

    // Remove an element (also O(1))
    it = next(l.begin(), 2); // points to '2'
    l.erase(it);

    cout << "\nAfter erase: ";
    for (int x : l)
        cout << x << " ";

    return 0;
}
/*
List elements: 1 10 2 3 
After erase: 1 10 3 

*/

/* ----------------------------------------- */
✔ 1.4 std::forward_list
Singly linked list
Light-weight; only forward iteration

/* ----------------------------------------- */
✔ 1.5 std::array
Fixed-size array wrapper
Stack allocation
Size known at compile-time
array<int, 3> a = {1,2,3};



/* -------------------------------------------------------------------------------------------------------- */
2. Associative Containers (Ordered)

Automatically sorted (usually balanced Red-Black Trees)

✔ 2.1 std::set
Unique keys
Sorted
Search/insert/delete: O(log n)
set<int> s = {3,1,2};

/* ----------------------------------------- */
✔ 2.2 std::multiset
Allows duplicate keys


/* ----------------------------------------- */
✔ 2.3 std::map
Key-value pairs
Sorted by keys
Unique keys

map<int,string> m;
m[1] = "A";
m[4] = "B";


/* ----------------------------------------- */
✔ 2.4 std::multimap
Key-value
Duplicate keys allowed


/* ------------------------------------------------------------------------------------------------ */
3. Unordered Containers (Hash-based)
Implement hash tables.
/* ----------------------------------------- */
✔ 3.1 std::unordered_set
Unique keys
Average per-op: O(1)
Worst-case: O(n)

/* ----------------------------------------- */
✔ 3.2 std::unordered_multiset
Duplicates allowed

/* ----------------------------------------- */
✔ 3.3 std::unordered_map
Key-value
Average: O(1)

unordered_map<string,int> mp;
mp["Aghaz"] = 10;

/* ----------------------------------------- */
✔ 3.4 std::unordered_multimap
Hash map with duplicate keys
/* ----------------------------------------------------------------------------------------------------- */
4. Container Adaptors
Provide restricted interfaces built on top of other containers.
/* ----------------------------------------- */
✔ 4.1 std::stack
LIFO
Usually backed by deque

stack<int> st;
st.push(10);
st.top();

/* ----------------------------------------- */
✔ 4.2 std::queue
FIFO
Backed by deque

/* ----------------------------------------- */
✔ 4.3 std::priority_queue
Max-heap by default
Allows efficient max/min retrieval

priority_queue<int> pq;
pq.push(5);
pq.push(1);
pq.push(10);  // top = 10

/* ----------------------------------------- */
Summery Table:
| Container      | Structure          | Ordered? | Unique? | Avg Complexity     |
| -------------- | ------------------ | -------- | ------- | ------------------ |
| vector         | Dynamic array      | No       | —       | O(1) access        |
| deque          | Segmented array    | No       | —       | O(1) ends          |
| list           | Doubly linked list | No       | —       | O(1) insert/delete |
| set            | RB-tree            | Yes      | Yes     | O(log n)           |
| map            | RB-tree            | Yes      | Yes     | O(log n)           |
| unordered_set  | Hash table         | No       | Yes     | O(1)               |
| unordered_map  | Hash table         | No       | Yes     | O(1)               |
| stack          | Adapter            | No       | —       | O(1)               |
| queue          | Adapter            | No       | —       | O(1)               |
| priority_queue | Heap               | No       | —       | O(log n)           |
/* ------------------------------------------------------------------------------------------------------------------------------------------- */

Which container to use when?
➤ Fast random access? → vector
➤ Insert at middle frequently? → list
➤ Sorted data needed? → set, map
➤ Fast lookup by key? → unordered_map
➤ LIFO/FIFO? → stack / queue
➤ Find min or max quickly? → priority_queue

✅ 1. Fast Random Access → std::vector
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    // Random access (O(1))
    cout << "Element at index 2 = " << v[2] << endl;

    // Insert at end (O(1) amortized) //The average cost per operation over many operations, even if some individual operations are expensive.
    v.push_back(60);

    cout << "After push_back: ";
    for (int x : v) cout << x << " ";
    return 0;
}
/* 
Element at index 2 = 30
After push_back: 10 20 30 40 50 60 
*/

✅ 2. Insert in Middle Frequently → std::list
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {1, 2, 3, 4};

    // Insert in the middle (O(1))
    auto it = l.begin();
    advance(it, 2);   // Move iterator to 3rd element
    l.insert(it, 99); // Insert before '3'

    cout << "List after insertion: ";
    for (int x : l) cout << x << " ";
    return 0;
}
/* 
List after insertion: 1 2 99 3 4 
*/


✅ 3. Sorted Data Needed → std::set and std::map
✔ Example using std::set (auto-sorted)
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    s.insert(30);
    s.insert(10);
    s.insert(20);     // Auto-sorted (10, 20, 30)

    cout << "Sorted set: ";
    for (int x : s) cout << x << " ";
    return 0;
}
/* 
Sorted set: 10 20 30 
*/

✔ Example using std::map (sorted by keys)
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> mp;

    mp[3] = "Three";
    mp[1] = "One";
    mp[2] = "Two";  // Sorted by key: 1,2,3

    cout << "Sorted map:\n";
    for (auto &p : mp)
        cout << p.first << " -> " << p.second << endl;

    return 0;
}
/* 
Sorted map:
1 -> One
2 -> Two
3 -> Three
*/

✅ 4. Fast Lookup by Key → std::unordered_map
(Uses hash table → O(1) average lookup)

#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    unordered_map<string, int> freq;

    freq["apple"] = 3;
    freq["banana"] = 5;
    freq["mango"] = 2;

    // Fast lookup (O(1))
    cout << "Frequency of banana = " << freq["banana"] << endl;

    return 0;
}
/* 
Frequency of banana = 5
*/


✅ 5. LIFO / FIFO → std::stack and std::queue
✔ LIFO → std::stack
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> st;

    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Stack top = " << st.top() << endl;

    st.pop();
    cout << "After pop, top = " << st.top() << endl;

    return 0;
}
/* 
Stack top = 30
After pop, top = 20
*/


✔ FIFO → std::queue
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;

    q.push(100);
    q.push(200);
    q.push(300);

    cout << "Front = " << q.front() << endl;

    q.pop();
    cout << "After pop, front = " << q.front() << endl;

    return 0;
}
/* 
Front = 100
After pop, front = 200
*/

✅ 6. Find Min or Max Quickly → std::priority_queue
(Default: max-heap)

#include <iostream>
#include <queue>
using namespace std;
int main() {
    priority_queue<int> pq;

    pq.push(5);
    pq.push(20);
    pq.push(10);

    cout << "Max element = " << pq.top() << endl;

    pq.pop();
    cout << "After pop, new max = " << pq.top() << endl;

    return 0;
}
/* 
Max element = 20
After pop, new max = 10
*/