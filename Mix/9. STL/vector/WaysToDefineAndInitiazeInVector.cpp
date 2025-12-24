vector
various methods to define and initialize a vector in C++:

1. Default Constructor (Empty Vector)
You can define a vector without any elements using the default constructor. 
The vector starts with a size of 0.

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v;  // Empty vector, no elements
    std::cout << "Size: " << v.size() << std::endl;
  return 0;
}




2. Constructor with Size (Fixed Size, Default Initialization)
You can define a vector with a fixed size, where all elements are initialized to zero 
(for basic types like int) or the default constructor for user-defined types.

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v(5);  // Vector with 5 elements, each initialized to 0
    std::cout << "Size: " << v.size() << ", First Element: " << v[0] << std::endl;
  return 0;
}





3. Constructor with Size and Default Value
You can initialize a vector with a fixed size and a specific value for all elements. 
This is useful when you want every element in the vector to have the same initial value.

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v(5, 10);  // Vector with 5 elements, each initialized to 10
    std::cout << "Size: " << v.size() << ", First Element: " << v[0] << std::endl;
  return 0;
}




4. Initializer List (Direct List Initialization)
You can define and initialize a vector with an initializer list. 
This allows you to directly specify the values of the vector when defining it.

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};  // Vector initialized with values 1, 2, 3, 4, 5
    std::cout << "Size: " << v.size() << ", First Element: " << v[0] << std::endl;
    return 0;
}





5. Using std::vector with a User-Defined Type (Class or Struct)
You can initialize a vector of objects (like structs or classes) in a similar way to how you initialize vectors of basic types. 
If the user-defined type has a constructor, the vector will use that constructor to initialize each element.

Example with Struct:
#include <iostream>
#include <vector>
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};
int main() {
    std::vector<Point> points = {Point(1, 2), Point(3, 4), Point(5, 6)};  // Vector of Points
    std::cout << "First Point: (" << points[0].x << ", " << points[0].y << ")" << std::endl;
    return 0;
}

Example with Class:
#include <iostream>
#include <vector>

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    std::vector<Point> points = {Point(1, 2), Point(3, 4), Point(5, 6)};  // Vector of Point objects
    std::cout << "First Point: (" << points[0].x << ", " << points[0].y << ")" << std::endl;
    return 0;
}




6. Using std::fill() to Initialize Vector
If you have an existing vector, you can fill it with a specific value using the std::fill() algorithm.

#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    std::vector<int> v(5);  // Vector of size 5
    std::fill(v.begin(), v.end(), 20);  // Fill all elements with the value 20

    for (int val : v) {
        std::cout << val << " ";  // Output: 20 20 20 20 20
    }
    std::cout << std::endl;
    return 0;
}





7. Using assign() Method
You can use the assign() method to replace the current contents of the vector with a specific number of copies of a value or a range of values.

#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.assign(5, 100);  // Assign 5 elements, each initialized to 100

    for (int val : v) {
        std::cout << val << " ";  // Output: 100 100 100 100 100
    }
    std::cout << std::endl;
    return 0;
}




8. Using std::vector with Iterators (Copy Constructor / Range Constructor)
You can initialize a vector by copying a range of elements from another container or vector using iterators. This is useful when you want to initialize a vector with a subset or all elements of another collection.

//copy constructor
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};  //copy constructor
    std::vector<int> v2(v1);  

    for (int val : v2) {
        std::cout << val << " ";  // Output: 1 2 3 4 5
    }
    std::cout << std::endl;
    return 0;
}


// Range Constructor
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2(v1.begin(), v1.end());  // Range Constructor, Copy entire range from v1 to v2

    for (int val : v2) {
        std::cout << val << " ";  // Output: 1 2 3 4 5
    }
    std::cout << std::endl;
    return 0;
}

//using move constructor
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2(std::move(v1));  // using move constructor

    for (int val : v2) {
        std::cout << val << " ";  // Output: 1 2 3 4 5
    }
    std::cout << std::endl;
    return 0;
}


//using std::array, or C-Array
#include <iostream>
#include <vector>
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> v2(arr, arr+5);  // using move constructor

    for (int val : v2) {
        std::cout << val << " ";  // Output: 1 2 3 4 5
    }
    std::cout << std::endl;
    return 0;
}



9. Array of Vectors
An array of vectors is a fixed-size array where each element is a std::vector. 
This means that the array has a constant size, but each vector within the array can grow or shrink dynamically.

Example of an Array of Vectors:
#include <iostream>
#include <vector>

int main() {
    // Define an array of 3 vectors
    std::vector<int> arr[3];

    // Inserting values into each vector
    arr[0].push_back(1);
    arr[0].push_back(2);

    arr[1].push_back(3);
    arr[1].push_back(4);
    arr[1].push_back(5);

    arr[2].push_back(6);

    // Display the contents of the array of vectors
    for (int i = 0; i < 3; ++i) {
        std::cout << "Vector " << i << ": ";
        for (int val : arr[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
/*
Explanation:
We declare an array of 3 std::vector<int>s: std::vector<int> arr[3];. 
This means arr has 3 elements, each of which is a vector.
Each vector can hold a different number of elements. For example, arr[0] has 2 elements, arr[1] has 3 elements, and arr[2] has 1 element.
You can insert elements into each vector using push_back(), and access each vector by its index (e.g., arr[0], arr[1]).

Output:
Vector 0: 1 2 
Vector 1: 3 4 5 
Vector 2: 6 
*/




9. Vector of Vectors
A vector of vectors is a dynamic structure where the outer vector holds other vectors as its elements. 
Unlike an array of vectors, the size of the vector of vectors can be changed dynamically, both for the outer vector and for the inner vectors.

Example of a Vector of Vectors:
#include <iostream>
#include <vector>

int main() {
    // Define a vector of vectors (2D vector)
    std::vector<std::vector<int>> vecOfVec;

    // Add vectors to the outer vector
    vecOfVec.push_back({1, 2});
    vecOfVec.push_back({3, 4, 5});
    vecOfVec.push_back({6});

    // Display the contents of the vector of vectors
    for (int i = 0; i < vecOfVec.size(); ++i) {
        std::cout << "Vector " << i << ": ";
        for (int val : vecOfVec[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
/* 
Explanation:
Here, vecOfVec is a vector of vectors. Each element of the outer vector is itself a std::vector<int>.
We use push_back() to add inner vectors to the outer vector. 
For example, {1, 2}, {3, 4, 5}, and {6} are pushed as inner vectors.

You can dynamically resize the outer vector and the inner vectors, 
which gives you more flexibility compared to the fixed-size array of vectors.

Output:
Vector 0: 1 2 
Vector 1: 3 4 5 
Vector 2: 6
*/

//Vector of Vectors (2D Vector)
You can define a vector of vectors, which is useful for representing 2D matrices or grids.

#include <iostream>
#include <vector>
int main() {
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

10. Dynamic Allocation (Using new or std::allocator)
While not common for simple use cases, you can dynamically allocate memory for vectors, especially when dealing with very large datasets.

#include <iostream>
#include <vector>
int main() {
    std::vector<int>* pVector = new std::vector<int>(5, 100);  // Dynamically allocated vector

    for (int val : *pVector) {
        std::cout << val << " ";  // Output: 100 100 100 100 100
    }
    std::cout << std::endl;

    delete pVector;  // Clean up dynamically allocated memory
    return 0;
}


