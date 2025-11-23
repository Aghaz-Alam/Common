multiple ways to insert data, depending on whether we want 
-to insert at the end, 
-at a specific position, 
-or from another container. 


1. Using push_back()
Adds an element at the end of the vector.

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    for (int val : v)
        std::cout << val << " ";  // Output: 10 20 30

    return 0;
}

2. Using emplace_back()
Constructs an element in place at the end, avoiding unnecessary copying (useful for objects).

#include <iostream>
#include <vector>
class Point {
  public:
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};
int main() {
    std::vector<Point> points;
    points.emplace_back(1, 2);  // Constructs Point(1,2) in place
    points.emplace_back(3, 4);

    for (auto& p : points)
        std::cout << "(" << p.x << "," << p.y << ") ";  // Output: (1,2) (3,4)

    return 0;
}

3. Using insert()
Allows insertion at any position, not just the end.

(a) Insert a single element at a specific position:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 4, 5};

    // Insert 3 at position 2 (0-based index)
    v.insert(v.begin() + 2, 3);

    for (int val : v)
        std::cout << val << " ";  // Output: 1 2 3 4 5

    return 0;
}


(b) Insert multiple copies of an element:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 5};

    // Insert three 3's at position 2
    v.insert(v.begin() + 2, 3, 3);

    for (int val : v)
        std::cout << val << " ";  // Output: 1 2 3 3 3 5

    return 0;
}

//insert 3 three times
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 5};

    // Insert three 3's at end
    v.insert(v.end(), 3, 3);

    for (int val : v)
        std::cout << val << " ";  // Output: 1 2 5 3 3 3 

    return 0;
}

(c) Insert a range of elements from another container:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    // Insert all elements of v2 at the end of v1
    v1.insert(v1.end(), v2.begin(), v2.end());

    for (int val : v1)
        std::cout << val << " ";  // Output: 1 2 3 4 5 6

    return 0;
}


// Insert all elements of v2 at position 2 of v1
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    // Insert all elements of v2 at position 2 of v1
    v1.insert(v1.begin()+2, v2.begin(), v2.end());

    for (int val : v1)
        std::cout << val << " ";  // Output: 1 2 4 5 6 3 

    return 0;
}


4. Using emplace()
Constructs an element in place at a specific position (like insert but avoids copy).

#include <iostream>
#include <vector>
class Point {
 public:
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

int main() {
    std::vector<Point> points;

    points.emplace_back(1, 2);  // end
    points.emplace(points.begin(), 0, 0);  // at beginning

    for (auto& p : points)
        std::cout << "(" << p.x << "," << p.y << ") ";  // Output: (0,0) (1,2)

    return 0;
}



5. Using assign()
Replaces all elements of the vector with new ones.

(a) Assign multiple copies of a value:
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.assign(5, 10);  // 5 elements, all 10

    for (int val : v)
        std::cout << val << " ";  // Output: 10 10 10 10 10

    return 0;
}

(b) Assign from a range of another container:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2;

    v2.assign(v1.begin(), v1.begin() + 3);  // Copy first 3 elements of v1

    for (int val : v2)
        std::cout << val << " ";  // Output: 1 2 3

   return 0;
}



6. Using resize() and Indexing
You can resize the vector and then insert values using indices.

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v;
    v.resize(3);       // Resize to 3 elements
    v[0] = 10;         // Insert via index
    v[1] = 20;
    v[2] = 30;

    for (int val : v)
        std::cout << val << " ";  // Output: 10 20 30

    return 0;
}





7. Using std::copy() with back_inserter
Useful to insert elements from another container.

#include <iostream>
#include <vector>
#include <algorithm>  // for std::copy
#include <iterator>   // for std::back_inserter

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    // Copy elements of v2 into v1 at the end
    std::copy(v2.begin(), v2.end(), std::back_inserter(v1));

    for (int val : v1)
        std::cout << val << " ";  // Output: 1 2 3 4 5 6

    return 0;
}
