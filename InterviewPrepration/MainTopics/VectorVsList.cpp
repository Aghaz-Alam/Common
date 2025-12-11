what is difference between vector and list

vector:
--> dynamic contiguous array. 
--> Best default choice. 
--> Excellent random access, 
--> excellent cache locality, 
--> low memory overhead. 
--> push_back amortized O(1). 
--> Inserting/removing in the middle is O(n) because elements must be moved.

list:
--> oubly-linked list. 
--> Nodes scattered in memory, 
--> each node stores pointers to prev/next. 
--> O(1) insert/remove if you already have the iterator to the position. 
--> No random access. Larger memory overhead and poor cache locality.


Quick complexity & properties table
| Property                                |  std::vector`                                                                   | std::list` |
| --------------------------------------- | ------------------------------------------------------------------------------: | -------------------------------------------------------------------: |
| Memory layout                           | contiguous array                                                                |  non-contiguous nodes                                                |
| Random access (`operator[]`)            | O(1)                                                                            |  Not available                                                       |
| Insert/erase at known iterator (middle) | O(n) (shift)                                                                    |  O(1)                                                                |
| Insert/erase at end                     | amortized O(1) / O(1) (pop_back)                                                |  O(1)                                                                |
| Traversal cost                          | cheap (cache-friendly)                                                          |  relatively expensive (pointer hops)                                 |
| Memory overhead per element             | low                                                                             |  high (2 pointers + node allocator overhead)                         |
| Iterator invalidation                   | push_back may reallocate (invalidates), insert/erase invalidates after position |  erase invalidates only erased iterator; other iterators remain valid |
| Sorting                                 | std::sort` on vector (very fast)                                                |  `list::sort` (mergesort), stable, no extra buffer required           |
| Special ops                             | contiguous memory (useful for &data[0], algorithms, I/O)                        |  splice/merge in O(1), stable node transfers                         |



Iterator invalidation — key practical rule
vector
--> push_back can reallocate and invalidate all iterators, references, pointers.
--> insert/erase at positions invalidate iterators at/after the position (and references).

list
--> erase(it) invalidates only it. All other iterators remain valid.
--> splice, push_back, push_front do not invalidate iterators to other elements.


Scenario-by-scenario (detailed)
/* --------------------------------------------------- */
Scenario A — Fast random access (indexing frequently)
Use vector.
Reason: vector provides operator[] and pointer arithmetic in O(1). 
        Accessing elements 1000s of times will be orders of magnitude faster due to contiguous layout and CPU cache hits.

list cannot do random access; advance() is O(n) so indexing is very slow.

Example
// vector: O(1) random access
int get_third(const std::vector<int>& v) {
    return v[2];
}
/* --------------------------------------------------- */
Scenario B — Mostly push_back / push_front and iteration
---> If you only append at the end and then iterate, vector is usually still better (cache locality).
---> If you frequently push_front and cannot tolerate O(n) shifts, deque is better than list and vector; 
---> list allows O(1) push_front but deque gives random access unlike list.



/* --------------------------------------------------- */
Scenario C — Many insertions/deletions in the middle, and you already have iterators

Use list.
--> If your algorithm maintains iterators/pointers to insertion points and repeatedly inserts/removes at them, 
    list’s O(1) insert/erase is unbeatable.

--> Example: maintaining a queue of tasks where you insert/remove adjacent to known positions frequently and you need stable iterators to elements.

Code example
std::list<int> l = {1,2,3,4};
auto it = std::next(l.begin(), 2); // points to 3
l.insert(it, 99); // O(1)
l.erase(it);      // O(1), only invalidates 'it'


But watch out: if you pick positions by index (e.g., insert at position 500 by counting from begin()), advance() costs O(n) and list loses its advantage. 
In that case vector + insert (which shifts memory) or another structure (like a balanced tree) might be better.
/* --------------------------------------------------- */
Scenario D — Insert by index (e.g., insert at position i often)
---> vector: shifting elements is O(n), but the data is contiguous. If access by index is frequent, vector might still be better.
---> list: to get to index i you must traverse O(i) steps — also O(n). 
     So list does not help if you choose insertion points by index rather than by an iterator you already have.



/* --------------------------------------------------- */
Scenario E — Frequent random deletes when you donot have iterators (delete by value)
---> unordered_set or unordered_map are often better than both vector and list for delete-by-key operations.
---> If you must remove by value from a sequence and order matters, 
     list::remove is O(n) but avoids shifting; 
     vector erase is O(n) and shifts elements (memmove). 
---> Both are O(n) but vector may be faster in practice because memmove is fast and cache-friendly.



/* --------------------------------------------------- */
Scenario F — Splicing/merging whole sequences

Use list.
list::splice moves nodes from one list to another in O(1) by rewiring pointers — no element moves, no allocations (if same allocator).

vector can't splice efficiently; you'd have to copy/move every element (O(n)).
Code
std::list<int> a = {1,2,3}, b = {4,5};
a.splice(a.end(), b); // move all nodes from b to end of a, O(1)



/* --------------------------------------------------- */
Scenario G — Sorting large sequence
---> vector: std::sort is usually fastest in practice (uses random-access, great cache locality).

---> list: list::sort() uses mergesort in-place (stable, no external buffer) and is good when moving nodes is cheaper than copying elements. 
     But for simple types, sorting a vector is usually faster.



/* --------------------------------------------------- */
Scenario H — Memory-sensitive and pointer-stable requirements
---> list has higher per-element overhead (2 pointers + allocator overhead), so memory footprint is larger; vector is compact.
---> list preserves pointer/iterator validity for other elements during many operations — useful when external code holds pointers to elements.

Real-world performance note
---> Even if algorithmic complexities suggest list wins for middle insertion, vector often performs better in real-world cases
     for moderate data sizes because:
---> Contiguous storage gives strong cache locality and CPU prefetching.
---> Modern memmove and std::move are fast; shifting blocks is often faster than chasing pointers across memory.
---> So donot choose list just because it looks good on paper — profile or reason about actual access patterns and sizes.




/* ------------------------------------------------------------------------------------------------------------------------------- */

Real-world performance note
Even if algorithmic complexities suggest list wins for middle insertion, vector often performs better in real-world cases for moderate data sizes because:
---> Contiguous storage gives strong cache locality and CPU prefetching.
---> Modern memmove and std::move are fast; shifting blocks is often faster than chasing pointers across memory.
---> So donot choose list just because it looks good on paper — profile or reason about actual access patterns and sizes.


/* ------------------------------------------------------------------------------------------------------------------------------------- */

When to pick which — quick checklist
Pick std::vector when:
---> You need random access.
---> You mostly append or iterate.
---> You care about memory compactness and performance.
---> You intend to use algorithms requiring contiguous memory (e.g., std::sort, std::binary_search, serialization).

Pick std::list when:
---> You have a lot of insertions/deletions at known positions via iterators, and you must keep iterators/pointers to elements valid across mutations.
---> You need O(1) splice/merge operations.
---> You require stable iterators (except erased ones).

Consider alternatives:
---> std::deque for efficient push_front/push_back + random access (middle operations still O(n)).
---> std::forward_list for singly-linked list if memory is tight and only forward traversal is needed.
---> std::set/std::map or hashed containers for search/delete-by-key patterns.
---> Sequence containers + index structures or custom data structures (rope, gap buffer, balanced trees) for specialized requirements 
     like many middle inserts by index (e.g., text editor).


/* -------------------------------------------------------------------------------------------------------------------------------------- */
Short illustrative comparisons (code + comment)

Random read-heavy:
std::vector<int> v(1000000, 1);
int x = v[500000]; // O(1) very fast (cache-friendly)


Many middle inserts at known position:
std::list<int> l = {/*...*/};
auto it = /* some iterator you already hold */;
l.insert(it, value); // O(1) — ideal when you already have the iterator


Splice two lists quickly:
std::list<int> a = {1,2}, b = {3,4};
a.splice(a.end(), b); // O(1) — b is now empty


Insert at position by index (vector likely better for locality):
// To insert at index i in vector:
v.insert(v.begin() + i, value); // O(n) shift — but memmove is fast

// To insert at index i in list:
auto it = std::next(l.begin(), i); // O(i) traversal + O(1) insert => O(n)
