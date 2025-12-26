STL
- vector, map, tuple and using them


STL in C++ - Detailed Explanation of Components
The Standard Template Library (STL) in C++ is made up of three main components:
--> Containers
--> Algorithms
--> Iterators


Let us go through each component in detail, listing the different types under each category.

1) Containers
--> Containers are data structures that store objects and data. 
--> STL provides several types of containers to handle different use cases. 
--> Containers are divided into the following categories:

A) Sequence Containers
--> Sequence containers store elements in a linear sequence and provide fast access to elements based on their position.

a) std::vector:
--> A dynamic array that can grow or shrink automatically as elements are added or removed. Provides fast random access to elements.
    Time complexity: Access O(1), Insertion/Deletion at the end O(1), Insertion/Deletion at the middle O(n).

b) std::deque (Double-ended Queue):
--> A sequence container that allows fast insertion and deletion at both the front and back.
    Time complexity: Access O(1), Insertion/Deletion at both ends O(1), but not as efficient as vector for random access in the middle.

c) std::list (Doubly Linked List):
--> A container that allows fast insertion and deletion at both ends or in the middle, but does not provide fast random access.
    Time complexity: Access O(n), Insertion/Deletion O(1) at the ends, O(n) in the middle.

d) std::array:
--> A fixed-size array that provides a safe, C++-style interface to traditional C-style arrays.
    Time complexity: Access O(1), fixed size, no resizing capability.




B) Associative Containers
--> These containers store elements in a way that allows fast lookup, insertion, and deletion by key. 
--> The elements are automatically sorted based on the key.

a) std::set:
--> A collection of unique elements that are automatically sorted. 
    Typically implemented as a balanced binary tree (e.g., Red-Black Tree).
    Time complexity: Access/Insertion/Deletion O(log n).

b) std::map:
--> A collection of key-value pairs, where each key is unique and automatically sorted.
    Time complexity: Access/Insertion/Deletion O(log n).

c) std::multiset:
--> Similar to std::set, but allows duplicate values. It stores elements in sorted order.
    Time complexity: Access/Insertion/Deletion O(log n).

d) std::multimap:
--> Similar to std::map, but allows multiple elements with the same key. It stores key-value pairs in sorted order.
    Time complexity: Access/Insertion/Deletion O(log n).

e) Unordered Containers
--> These containers store elements using hash tables (instead of balanced trees), providing faster average-time complexity for lookups, insertions, and deletions.

f) std::unordered_set:
--> A collection of unique elements, but unlike set, the elements are not sorted. It uses hashing for faster access.
    Time complexity: Access/Insertion/Deletion O(1) on average, but can degrade to O(n) in rare cases.

g) std::unordered_map:
--> A collection of key-value pairs, with unique keys, that uses hashing to provide fast access.
    Time complexity: Access/Insertion/Deletion O(1) on average.

h) std::unordered_multiset:
--> A collection of elements where duplicates are allowed, and it uses hashing for faster access.
    Time complexity: Access/Insertion/Deletion O(1) on average.

i) std::unordered_multimap:
--> A collection of key-value pairs where multiple elements can have the same key, using hashing for fast access.
    Time complexity: Access/Insertion/Deletion O(1) on average.





2) Algorithms
--> Algorithms in STL are a collection of functions that operate on containers or data structures. 
    These algorithms are generally designed to perform operations like sorting, searching, and manipulating the data within containers.


Here are some commonly used categories of algorithms:
Non-modifying Sequence Algorithms:
--> std::for_each(): Applies a function to each element in a container.
--> std::count(): Counts the occurrences of a specific value in a container.
--> std::find(): Searches for a value in a container.
--> std::equal(): Compares two containers for equality.


Modifying Sequence Algorithms:
--> std::sort(): Sorts a range of elements.
--> std::reverse(): Reverses the order of elements in a range.
--> std::insert(): Inserts a new element into a container.
--> std::replace(): Replaces occurrences of a value with another value.


Sorting Algorithms:
--> std::sort(): Sorts elements in ascending order by default.
--> std::stable_sort(): A stable version of std::sort(), which preserves the order of equal elements.



Searching Algorithms:
--> std::binary_search(): Checks whether an element exists in a sorted container using binary search.
--> std::find(): Searches for an element in a container.



Set Algorithms (for associative containers like set, map):
--> std::set_union(): Computes the union of two sets.
--> std::set_intersection(): Computes the intersection of two sets.
--> std::set_difference(): Computes the difference between two sets.



Numeric Algorithms:
--> std::accumulate(): Computes the sum of elements in a container.
--> std::partial_sum(): Computes the running sum of elements.
--> std::inner_product(): Computes the inner product of two sequences.





3) Iterators
--> Iterators are objects that act like pointers, allowing you to traverse and access the elements of containers. 
    They abstract away the underlying container type, providing a consistent way to iterate over elements.


There are several types of iterators in STL:
--> Input Iterator: Allows reading elements from the container.
--> Output Iterator: Allows writing elements to the container.
--> Forward Iterator: Allows both reading and writing, and can only move forward.
--> Bidirectional Iterator: Allows moving both forward and backward through the container.
--> Random Access Iterator: Allows moving freely to any position in the container (similar to array indexing).


Each container provides its own set of iterators. Here’s how iterators are typically used:
--> begin(): Returns an iterator pointing to the first element of the container.
--> end(): Returns an iterator pointing to one past the last element (the "end" of the container).
--> rbegin() and rend(): Return reverse iterators (used to iterate from the end of the container).
--> advance(): Moves an iterator forward by a specified number of steps.



For example:
std::vector<int> vec = {1, 2, 3, 4, 5};
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " "; // Dereference to access the value
}




Summary of Containers in STL
--> Here is a summarized list of all the container types and their categorization:

Sequence Containers:
--> std::vector
--> std::deque
--> std::list
--> std::array


Associative Containers:
--> std::set
--> std::map
--> std::multiset
--> std::multimap


Unordered Containers:
--> std::unordered_set
--> std::unordered_map
--> std::unordered_multiset
--> std::unordered_multimap








What is STL in C++?
-> STL stands for Standard Template Library in C++. 
-> It is a collection of template classes and functions that provide general-purpose, reusable software components. 
-> These components are designed to help programmers solve common problems related to data structures, algorithms, 
   and iterators in a more efficient and standardized manner.


The STL is part of the C++ Standard Library, and it consists of the following key components:
-> Containers: Data structures that store objects or data.

Examples: vector, list, deque, set, map, unordered_map, etc.
=> Algorithms: Functions that perform operations on containers (such as searching, sorting, and manipulating data).
   Examples: sort(), find(), binary_search(), etc.

=> Iterators: Objects that allow access to container elements in a linear sequence.
   Examples: begin(), end(), advance(), etc.

=> Function Objects (Functors): Objects that can be treated as functions, which can be used to customize certain operations like sorting and searching.
   Examples: Custom comparison function objects.


What is the Use of STL?
-> The primary use of STL is to simplify the development of C++ programs by providing ready-made, efficient, 
   and flexible data structures and algorithms. 
-> It allows developers to focus on the high-level logic of their program instead of reinventing common data structures and algorithms.



STL offers the following benefits:
-> Code Reusability: Since STL provides standardized, generic implementations of data structures and algorithms, 
   developers can reuse these components in their own programs.

-> Performance: STL is highly optimized for performance, making it an efficient choice for building software that needs to handle 
   large datasets or perform intensive computations.

-> Generics: STL uses C++ templates, allowing it to work with any data type. This allows for greater flexibility since you do not 
   need to write separate code for different types of data.

-> Abstraction: STL abstracts away the low-level implementation details, letting developers focus on problem-solving rather 
   than the complexities of data structure implementation.




Why Do We Use STL?
Convenience and Time-Saving:
-> The STL provides a set of powerful tools that can save time and effort during development. 
-> Instead of implementing common data structures like linked lists, trees, or hash maps from scratch, 
-> we can just use STL containers like std::vector, std::list, std::map, etc.  
-> Additionally, algorithms like sorting (std::sort) and searching (std::binary_search) are already optimized and available for use.



Efficiency:
-> STL containers and algorithms are optimized for performance. They are implemented with a focus on speed and memory efficiency, 
   and they provide worst-case time complexities that are often very competitive. 
-> For example, std::vector uses dynamic resizing, and std::map is based on balanced trees to provide efficient insertion and lookup.


Flexibility with Templates:
-> STL is template-based, meaning that you can use it with any data type. 
-> This is important because it provides a way to write generic code that works with different types of objects, 
   reducing code duplication and increasing reusability. 
-> For instance, the same std::sort function can be used to sort arrays of int, double, std::string, or custom objects, 
   provided they support comparison.



Standardization:
-> STL components are part of the C++ Standard Library, which means they are well-tested, reliable, and portable across different compilers 
   and platforms. 
-> By using STL, you are following C++ best practices and ensuring that your code is maintainable and compatible with future versions of the language.





Maintainability:
-> The STL components are highly modular and abstracted, which makes your code easier to maintain. 
-> Using STL can often lead to more readable, concise, and clean code, since it eliminates the need to re-implement common data structures 
   and algorithms.





Interoperability:
-> STL containers work seamlessly with other parts of the C++ Standard Library. 
-> For example, STL iterators allow you to work with any container in a uniform way, and STL algorithms can operate on containers through iterators. 
-> This interoperability makes it easier to combine various parts of the C++ Standard Library in your application.






Detailed Explanation of Key Components in STL

Containers:
-> Containers store collections of objects. 

Some of the most commonly used containers in STL are:

vector: 
-> A dynamic array that can grow or shrink as elements are added or removed. 
-> It allows random access to elements and is generally efficient for operations at the end of the sequence.


list: 
-> A doubly linked list that allows efficient insertion and deletion of elements at both ends and in the middle, 
   but it does not allow random access.


deque: 
-> A double-ended queue that allows fast insertion and deletion at both ends, though it is slower than vector for random access.


set: 
-> A collection of unique elements, typically implemented as a balanced binary search tree. Elements are ordered automatically.



map: 
->  A collection of key-value pairs, where each key is unique, and the elements are ordered by key. 
->  It is typically implemented as a balanced binary search tree.



unordered_map: 
-> A hash table-based map that offers faster average-time complexity for lookups compared to map, though the elements are not ordered.




Algorithms:
-> STL provides a wide range of algorithms that work on containers and iterators. 

Some common algorithms include:
-> Sorting: std::sort(), which can sort data in ascending or descending order.
-> Searching: std::find(), std::binary_search() for finding elements.
-> Transforming: std::transform() to apply a function to all elements.
-> Manipulation: std::reverse(), std::shuffle() for manipulating container data.
-> Counting: std::count(), std::count_if() to count elements based on a condition.



Iterators:
-> Iterators are pointers-like objects used to access elements in a container. 
-> They are the key to the STL’s flexibility, as they abstract away the underlying container implementation. 

Common types of iterators include:
-> begin() and end(): Returns iterators to the first and one-past-the-last elements of the container.
-> advance(): Moves an iterator forward by a specified number of steps.
-> insert() and erase(): Used to add or remove elements in containers.


Function Objects (Functors):
-> These are objects that can be used like functions. 
-> They are especially useful when you need custom behavior in STL algorithms. 
-> A function object is an object of a class that defines the operator(). 
-> For example, to sort a vector of std::pair objects based on the second element, you might create a custom comparator functor.


Conclusion
-> In summary, the STL in C++ provides a collection of tools that make it easier, faster, 
    and more efficient to work with data structures and algorithms.
-> It saves time by offering reusable components, boosts performance with optimized implementations, and increases code clarity and maintainability. 
-> By using STL, C++ developers can focus more on solving their specific problems rather than worrying about the details of implementing 
    data structures and algorithms from scratch.






