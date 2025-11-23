several ways to access the elements of a std::vector

1. Using Indexing ([])
You can access elements by directly using the index operator. Indexing starts from 0, just like arrays.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Access elements using the index operator []
    std::cout << "Element at index 0: " << v[0] << std::endl;  //10
    std::cout << "Element at index 2: " << v[2] << std::endl;  //30

    return 0;
}
/* 
Notes:
No bounds checking: If you access an invalid index, it will result in undefined behavior.
Use this when you're confident the index is valid.
*/



2. Using .at() Method
The .at() method allows you to access vector elements with bounds checking, which means it throws an exception (std::out_of_range) 
if the index is invalid.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    try {
        // Access element using .at() with bounds checking
        std::cout << "Element at index 1: " << v.at(1) << std::endl;
        std::cout << "Element at index 5: " << v.at(5) << std::endl;  // Throws exception
    }
    catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
/* 
Notes:
Bounds checking: Throws an exception if you try to access an out-of-bounds element.
Useful if you are working with user input or unpredictable indices.
 */


3. Using Iterator (begin(), end())
Iterators are a more flexible and powerful way to access elements of a vector. 
They allow you to traverse the vector without explicitly using indices.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Using an iterator to access elements
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";  // Dereference the iterator to get the value
    }

    return 0;
}
/* 
Notes:
begin() returns an iterator to the first element.
end() returns an iterator to one past the last element.
Iterators are more general and can be used for other STL containers, making your code more reusable.
*/




4. Using Range-Based For Loop (C++11 and above)
The range-based for loop provides a concise and readable way to access all elements in a vector. 
This is the most modern and convenient way to iterate over a container in C++.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Using range-based for loop to access elements
    for (int val : v) {
        std::cout << val << " ";
    }

    return 0;
}
/* 
Notes:
Simpler and cleaner: No need to manually handle iterators or indices.
Readonly: In this form, you can’t modify the vector elements unless you use a reference (see next).

With Reference to Modify Elements:
for (int& val : v) {
    val += 5;  // Modify elements directly
}
*/




5. Using Reverse Iterator (rbegin(), rend())
If you need to iterate over the vector in reverse order, you can use reverse iterators (rbegin() and rend()).

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Using reverse iterator to access elements
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
/* 
Notes:
rbegin() returns a reverse iterator pointing to the last element.
rend() returns a reverse iterator pointing to one past the first element.
*/


6. Using front() and back() Methods
front() returns a reference to the first element of the vector.
back() returns a reference to the last element of the vector.

Example:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Access the first element
    std::cout << "First element: " << v.front() << std::endl;

    // Access the last element
    std::cout << "Last element: " << v.back() << std::endl;

    return 0;
}
/* 
Notes:
front() and back() provide easy access to the first and last elements, respectively.
If the vector is empty, calling these methods will result in undefined behavior, so be sure to check that the vector is not empty before using them.
*/


7. Using data() Method
The data() method provides direct access to the underlying array of the vector, allowing you to work with raw pointers. 
This is useful when interacting with low-level APIs or performing memory-intensive operations.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Access the underlying array using data()
    int* ptr = v.data();

    // Access elements like a regular array
    std::cout << "First element: " << ptr[0] << std::endl;
    std::cout << "Second element: " << ptr[1] << std::endl;

    return 0;
}
/* 
Notes:
Returns a pointer to the underlying array.
You can access elements using pointer arithmetic, similar to arrays. 
*/