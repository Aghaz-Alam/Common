Tuple in C++

A tuple in C++ is a fixed-size collection of elements that can hold multiple heterogeneous (different types of) values.
Tuples are part of the C++ Standard Library (STL) and are provided through the std::tuple class, 
which allows you to store multiple elements of different types in a single object. 

It is often used when you need to return multiple values from a function or store a collection of values of different types together.



Key Characteristics of a Tuple in C++:
Heterogeneous: A tuple can store elements of different types. Unlike arrays or vectors, which typically hold elements of the same type, 
a tuple can hold any combination of data types, including primitive types, objects, or other containers.


Fixed Size: The size of a tuple is fixed once it is defined. You cannot change the size dynamically as you can with a std::vector. 
However, you can access individual elements through indices or by using type-based access.


Indexed Access: You can access the elements of a tuple using std::get<T> (where T is the index or type) or via std::get<index>(tuple).
Type-Safe: Each element in a tuple is accessed using its type or index. C++ performs type-checking at compile time, so it is type-safe.
Supports Multiple Types: You can store various types of data (e.g., int, double, std::string) in the same tuple.



Basics of std::tuple in C++ STL
Definition of a Tuple:
To define a tuple, you use the std::tuple class template:
std::tuple<int, double, std::string> myTuple;
This defines a tuple that can hold an int, a double, and a std::string.

Initialization of a Tuple:
You can initialize a tuple using curly braces {} or by directly passing values to the constructor.
std::tuple<int, double, std::string> myTuple(42, 3.14, "Hello");
// or
std::tuple<int, double, std::string> myTuple = std::make_tuple(42, 3.14, "Hello");



Accessing Elements of a Tuple:
Using std::get<index>:
You can access elements of a tuple using std::get<index> where index is the position of the element in the tuple (zero-based index).

std::cout << std::get<0>(myTuple) << std::endl;  // Output: 42 (int)
std::cout << std::get<1>(myTuple) << std::endl;  // Output: 3.14 (double)
std::cout << std::get<2>(myTuple) << std::endl;  // Output: Hello (std::string)




Using std::get<Type>:
You can also access tuple elements by type, which is useful when you do not know the exact index.

std::cout << std::get<int>(myTuple) << std::endl;    // Output: 42 (int)
std::cout << std::get<double>(myTuple) << std::endl;  // Output: 3.14 (double)




Using Structured Bindings (C++17 and later):
C++17 introduced structured bindings that allow you to unpack the tuple elements directly into individual variables.

auto [a, b, c] = myTuple;
std::cout << a << " " << b << " " << c << std::endl;  // Output: 42 3.14 Hello



Modifying Tuple Elements:

You cannot directly modify elements of a tuple by index (like you can with arrays or vectors). 
However, you can modify a tuple element through std::get<index> if the element type is mutable.

std::get<0>(myTuple) = 100;  // Modifying the first element (int)
std::cout << std::get<0>(myTuple) << std::endl;  // Output: 100



Tuple Size:
You can obtain the number of elements in the tuple using std::tuple_size:
std::cout << "Tuple size: " << std::tuple_size<decltype(myTuple)>::value << std::endl;



Swapping Tuples:
You can swap the contents of two tuples using std::swap:

std::tuple<int, double> tuple1(1, 3.14);
std::tuple<int, double> tuple2(10, 6.28);
std::swap(tuple1, tuple2);




Creating Tuples:
You can create tuples using std::make_tuple:
auto myTuple = std::make_tuple(10, 3.14, "Hello");

Tuple Comparison:
Tuples can be compared using the standard comparison operators (==, !=, <, >, etc.), 
and the comparison is done lexicographically (element by element):

std::tuple<int, double> t1(1, 2.5);
std::tuple<int, double> t2(1, 3.5);
if (t1 < t2) {
    std::cout << "t1 is less than t2" << std::endl;
}


Example Program:
#include <iostream>
#include <tuple>
using namespace std;
int main() {
    // Initialize tuple
    tuple<int, double, string> myTuple(42, 3.14, "Hello");

    // Access elements using index
    cout << "First element: " << get<0>(myTuple) << endl;
    cout << "Second element: " << get<1>(myTuple) << endl;
    cout << "Third element: " << get<2>(myTuple) << endl;

    // Access elements using type
    cout << "First element (type): " << get<int>(myTuple) << endl;
    cout << "Second element (type): " << get<double>(myTuple) << endl;

    // Modify an element
    get<0>(myTuple) = 100;
    cout << "Modified first element: " << get<0>(myTuple) << endl;

    // Structured bindings (C++17 and later)
    auto [a, b, c] = myTuple;
    cout << "Using structured bindings: " << a << ", " << b << ", " << c << endl;

    return 0;
}
/* 
Output:
First element: 42
Second element: 3.14
Third element: Hello
First element (type): 42
Second element (type): 3.14
Modified first element: 100
Using structured bindings: 100, 3.14, Hello
*/




Internal Implementation of std::tuple using Arrays in C++
Key Features of Our Custom Tuple-Like Class
Fixed Size: The number of elements in the "tuple" is fixed at compile time, just like the std::tuple.
Heterogeneous Types: We will use template specialization to handle elements of different types.
Type-Safe Access: We'll provide access to tuple elements using template metaprogramming.


#include <iostream>
#include <stdexcept>
#include <string>
#include <memory> // For std::make_unique
#include <tuple>
using namespace std;

// Our custom tuple implementation
template <typename... Types>
class custom_tuple {
  private:
    // Array of unique_ptrs for each element type in the tuple
    std::tuple<std::unique_ptr<Types>...> data;

  public:
    // Constructor that initializes the tuple elements
    custom_tuple(Types&&... args) {
        // Initialize elements directly using a fold expression
        data = std::make_tuple(std::make_unique<Types>(std::forward<Types>(args))...);
    }

    // Get element by index
    template <std::size_t Index>
    auto& get() {
        return *std::get<Index>(data);  // Access the element by index
    }

    // Get element by index (const version)
    template <std::size_t Index>
    const auto& get() const {
        return *std::get<Index>(data);  // Access the element by index
    }
};

// Example usage of custom_tuple
int main() {
    // Create a custom_tuple with different types
    custom_tuple<int, double, std::string> myTuple(42, 3.14, "Hello");

    // Accessing elements by index
    cout << "First element: " << myTuple.get<0>() << endl;  // Output: 42
    cout << "Second element: " << myTuple.get<1>() << endl; // Output: 3.14
    cout << "Third element: " << myTuple.get<2>() << endl;  // Output: Hello

    return 0;
}
/*
First element: 42
Second element: 3.14
Third element: Hello


Explanation of Changes:

Tuple of Unique Pointers:
We use std::tuple<std::unique_ptr<Types>...> to store each type as a std::unique_ptr<T>. 
This is much cleaner and allows the get function to return the element by dereferencing the std::unique_ptr.

Constructor:
The constructor initializes each element of the tuple with the corresponding type using std::make_unique<Types>(std::forward<Types>(args))....

Accessing Elements:
The get function now uses std::get<Index>(data) to retrieve the correct element and returns the value by dereferencing the std::unique_ptr.
*/
