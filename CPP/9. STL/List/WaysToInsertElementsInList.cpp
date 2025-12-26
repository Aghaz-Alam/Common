ways to insert elements in a std::list in C++:

1. push_back()
Inserts an element at the end of the list.
This is one of the most common ways to add elements to a list.

std::list<int> lst;
lst.push_back(10);  // Insert 10 at the end
lst.push_back(20);  // Insert 20 at the end
lst.push_back(30);  // Insert 30 at the end

// lst: {10, 20, 30}



2. push_front()
Inserts an element at the beginning of the list.
This operation adds the element to the front (head) of the list.

std::list<int> lst;
lst.push_front(10);  // Insert 10 at the front
lst.push_front(20);  // Insert 20 at the front

// lst: {20, 10}



3. insert()
Inserts an element at a specific position in the list.
You can specify the position using an iterator, and you can insert either a single element or multiple elements.

Inserting a single element:
std::list<int> lst = {10, 20, 30};
auto it = lst.begin();
++it;  // Move iterator to point to the second element (20)
lst.insert(it, 15);  // Insert 15 before 20

// lst: {10, 15, 20, 30}

Inserting multiple elements:
You can also insert a range of elements (e.g., another list or an array) at a specific position.
std::list<int> lst = {1, 2, 3};
std::list<int> toInsert = {4, 5, 6};

// Insert elements from toInsert before the second element of lst
auto it = lst.begin();
std::advance(it, 1);  // Move iterator to second position
lst.insert(it, toInsert.begin(), toInsert.end());

// lst: {1, 4, 5, 6, 2, 3}

Inserting multiple copies of an element:
std::list<int> lst = {1, 2, 3};
auto it = lst.begin();
lst.insert(it, 3, 100);  // Insert 3 copies of 100 before the first element

// lst: {100, 100, 100, 1, 2, 3}



4. emplace_back()
Inserts an element at the end of the list, but in a more efficient way by constructing the element in place.
Useful when you want to avoid unnecessary copying or moving of the element.

std::list<int> lst;
lst.emplace_back(10);  // Directly constructs the element at the end

// lst: {10}



5. emplace_front()
Inserts an element at the front of the list, directly constructing the element in place.
std::list<int> lst;
lst.emplace_front(20);  // Directly constructs the element at the front

// lst: {20}



6. emplace()
Inserts an element at a specific position in the list, constructing it in place.
Similar to insert(), but more efficient as it avoids copying or moving the element.
std::list<int> lst = {10, 20, 30};
auto it = lst.begin();
++it;  // Move iterator to second element (20)
lst.emplace(it, 15);  // Directly constructs 15 before 20

// lst: {10, 15, 20, 30}



7. splice()
Transfers elements from another list to this list at a specific position.
This is useful when you want to move multiple elements from one list to another.
Splicing entire list:
std::list<int> lst1 = {1, 2, 3};
std::list<int> lst2 = {4, 5, 6};

// Splice lst2 at the end of lst1
lst1.splice(lst1.end(), lst2);

// lst1: {1, 2, 3, 4, 5, 6}
// lst2: {} (empty)

Splicing at a specific position:
std::list<int> lst1 = {1, 2, 3};
std::list<int> lst2 = {4, 5, 6};

// Splice lst2 before the second element of lst1
auto it = lst1.begin();
std::advance(it, 1);  // Move iterator to the second element (2)
lst1.splice(it, lst2);

// lst1: {1, 4, 5, 6, 2, 3}
// lst2: {} (empty)

Splicing a single element:
std::list<int> lst1 = {1, 2, 3};
std::list<int> lst2 = {4, 5, 6};

auto it = lst2.begin();
lst1.splice(lst1.end(), lst2, it);  // Splice the first element of lst2 (4) into lst1

// lst1: {1, 2, 3, 4}
// lst2: {5, 6}