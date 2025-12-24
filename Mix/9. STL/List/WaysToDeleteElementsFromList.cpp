various Ways To delete Elements from the  List in C++
1. pop_back()
Deletes the last element of the list.
This operation does not require specifying an iterator or a position; it simply removes the last element.

std::list<int> lst = {10, 20, 30};
lst.pop_back();  // Removes 30

// lst: {10, 20}




2. pop_front()
Deletes the first element of the list.
Like pop_back(), this removes the first element without requiring an iterator.

std::list<int> lst = {10, 20, 30};
lst.pop_front();  // Removes 10

// lst: {20, 30}



3. remove()
Removes all occurrences of a specific value from the list.
This function searches the entire list for the specified value and removes every occurrence.

std::list<int> lst = {10, 20, 30, 20, 40};
lst.remove(20);  // Removes all occurrences of 20

// lst: {10, 30, 40}



4. remove_if()
Removes elements that satisfy a given condition (specified by a predicate).
This method uses a lambda function or a function pointer to determine which elements to remove.

std::list<int> lst = {10, 15, 20, 25, 30};
lst.remove_if([](int x) { return x % 2 == 0; });  // Removes even numbers

// lst: {15, 25}



5. erase()
Removes a specific element at a given position or a range of elements.
The position is specified using an iterator.

Remove a single element:
std::list<int> lst = {10, 20, 30, 40};
auto it = lst.begin();
std::advance(it, 2);  // Move iterator to the third element (30)
lst.erase(it);        // Removes 30

// lst: {10, 20, 40}


Remove a range of elements:
std::list<int> lst = {10, 20, 30, 40, 50};
auto it1 = lst.begin();
std::advance(it1, 1);  // Move iterator to second element (20)
auto it2 = it1;
std::advance(it2, 2);  // Move iterator to fourth element (40)

lst.erase(it1, it2);  // Removes elements from 20 to 40 (inclusive)

// lst: {10, 50}



6. clear()
Removes all elements from the list, leaving it empty.
After calling clear(), the list is empty, but it still exists (it can be reused).

std::list<int> lst = {10, 20, 30, 40};
lst.clear();  // Removes all elements

// lst is now empty


7. splice() (with a range)
Although splice() is typically used to move elements between lists, it can be used in combination with erase() to delete elements from a list.
std::list<int> lst1 = {10, 20, 30, 40};
std::list<int> lst2 = {50, 60};

// Remove elements from lst1 by splicing them into an empty list
lst2.splice(lst2.end(), lst1, lst1.begin(), lst1.end());

// lst1 is now empty, lst2 contains all elements from lst1

Summary of Deletion Methods
| Method            | Description                                                              |
| ----------------- | ------------------------------------------------------------------------ |
| **`pop_back()`**  | Removes the last element of the list.                                    |
| **`pop_front()`** | Removes the first element of the list.                                   |
| **`remove()`**    | Removes all occurrences of a specific value.                             |
| **`remove_if()`** | Removes elements that satisfy a given condition (predicate).             |
| **`erase()`**     | Removes a specific element or a range of elements.                       |
| **`clear()`**     | Removes all elements from the list.                                      |
| **`splice()`**    | Moves elements from another list into this list (can be used to delete). |

Example Program Using Different Deletion Methods
#include <iostream>
#include <list>

int main() {
    // 1. Using pop_back() and pop_front()
    std::list<int> lst1 = {10, 20, 30};
    lst1.pop_back();  // Removes 30
    lst1.pop_front(); // Removes 10
    
    std::cout << "lst1 after pop_back() and pop_front(): ";
    for (int val : lst1) {
        std::cout << val << " ";  // Output: 20
    }
    std::cout << std::endl;

    // 2. Using remove()
    std::list<int> lst2 = {10, 20, 30, 20, 40};
    lst2.remove(20);  // Removes all occurrences of 20

    std::cout << "lst2 after remove(): ";
    for (int val : lst2) {
        std::cout << val << " ";  // Output: 10 30 40
    }
    std::cout << std::endl;

    // 3. Using remove_if()
    std::list<int> lst3 = {10, 15, 20, 25, 30};
    lst3.remove_if([](int x) { return x % 2 == 0; });  // Removes even numbers

    std::cout << "lst3 after remove_if(): ";
    for (int val : lst3) {
        std::cout << val << " ";  // Output: 15 25
    }
    std::cout << std::endl;

    // 4. Using erase()
    std::list<int> lst4 = {10, 20, 30, 40};
    auto it = lst4.begin();
    std::advance(it, 2);  // Move iterator to the third element (30)
    lst4.erase(it);  // Removes 30

    std::cout << "lst4 after erase(): ";
    for (int val : lst4) {
        std::cout << val << " ";  // Output: 10 20 40
    }
    std::cout << std::endl;

    // 5. Using clear()
    std::list<int> lst5 = {1, 2, 3, 4};
    lst5.clear();  // Removes all elements

    std::cout << "lst5 after clear(): ";
    for (int val : lst5) {
        std::cout << val << " ";  // No output, as lst5 is empty
    }
    std::cout << std::endl;

    return 0;
}

Output:
lst1 after pop_back() and pop_front(): 20 
lst2 after remove(): 10 30 40 
lst3 after remove_if(): 15 25 
lst4 after erase(): 10 20 40 
lst5 after clear(): 
