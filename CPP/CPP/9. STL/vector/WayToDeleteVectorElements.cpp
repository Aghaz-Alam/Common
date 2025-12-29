Various Ways To Delete Vector Elements

1. Using pop_back()
The pop_back() method removes the last element from the vector. 
It doesn’t return the removed element and reduces the vector’s size by one.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Remove the last element
    v.pop_back();

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 20 30
    }

    return 0;
}
/* 
Notes:
Removes only the last element.
Does not throw an exception when the vector is empty.
O(1) time complexity.
*/



2. Using erase()
The erase() method is used to remove a specific element or a range of elements from the vector.

(a) Remove a single element by iterator:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Remove element at position 2 (third element)
    v.erase(v.begin() + 2);

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 20 40
    }

    return 0;
}



(b) Remove a range of elements:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    // Remove elements from position 1 to 3 (inclusive of position 1, exclusive of position 4)
    v.erase(v.begin() + 1, v.begin() + 4);

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 50
    }

    return 0;
}
/* 
Notes:
erase() removes elements and shifts the remaining elements to fill the gap.
The iterator can be used to specify a specific element or range of elements.
O(n) time complexity for both single element and range removal (because of the shifting of elements).
*/

//OR
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    // Remove elements from position 1 to 3 (inclusive of position 1, exclusive of position 4)
    v.erase(v.begin() + 1, v.end() - 1);

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 50
    }

    return 0;
}



3. Using clear()
The clear() method removes all elements from the vector, effectively making it empty. 
It does not change the capacity of the vector.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Remove all elements
    v.clear();

    std::cout << "Vector size after clear: " << v.size() << std::endl;  // Output: 0

    return 0;
}
/* 
Notes:
O(n) time complexity because it calls the destructor on each element.
After calling clear(), the size of vector becomes 0, but its capacity remains unchanged.
Use shrink_to_fit() if you want to reduce the capacity.
 */


4. Using erase() with remove() or remove_if() (for removing by value)
When you want to remove specific values (not by position), the erase() method can be combined with std::remove() or std::remove_if() 
to efficiently remove all occurrences of a value from the vector. 
This technique is often referred to as the erase-remove idiom.


(a) Remove all occurrences of a specific value (remove()):
#include <iostream>
#include <vector>
#include <algorithm>  // for std::remove
int main() {
    std::vector<int> v = {10, 20, 30, 20, 40};

    // Remove all elements with the value 20
    v.erase(std::remove(v.begin(), v.end(), 20), v.end());

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 30 40
    }

   return 0;
}


(b) Remove elements based on a condition (remove_if()):
#include <iostream>
#include <vector>
#include <algorithm>  // for std::remove_if
int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    // Remove all elements greater than 30
    v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x > 30; }), v.end());

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 20 30
    }

    return 0;
}
/* 
Notes:
std::remove() and std::remove_if() don’t actually remove the elements but move them to the end of the vector. 
The erase() method is needed to remove the "removed" elements from the container.
O(n) time complexity (for both remove and erase combined).
*/



5. Using swap() with an Empty Vector
This method is a trick for efficiently clearing a vector and reducing its capacity to zero. 
It works by swapping the vector with an empty vector, effectively discarding all the elements and reducing its capacity.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};
    // Swap with an empty vector to clear and free memory
    std::vector<int>().swap(v);
    std::cout << "Vector size after swap: " << v.size() << std::endl;  // Output: 0

   return 0;
}
/* 
Notes:
This method releases memory (since it swaps with an empty vector), which reduces the capacity of the vectors to 0.
O(1) time complexity for clearing and releasing memory.
*/



6. Using resize() (for removing elements from the end)
The resize() method can be used to shrink the vector by resizing it to a smaller size, effectively removing the elements beyond the new size.

Example:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30, 40};

    // Resize the vector to remove the last two elements
    v.resize(2);

    for (int val : v) {
        std::cout << val << " ";  // Output: 10 20
    }

    return 0;
}
/* 
Notes:

O(n) time complexity because the vector elements are destroyed when resizing.

This method only works for removing elements from the end of the vector. 
*/