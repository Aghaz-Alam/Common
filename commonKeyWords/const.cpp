The const keyword in C++ is widely used for declaring constant variables, constant methods, and for specifying immutability in various contexts. 
It can be applied in several different places in C++ to enforce constancy and immutability. 

Below is a detailed breakdown of const usage in C++ across different versions (C++11, C++14, and C++17), 
including common use cases with example code.




1. const with Variables
   A const variable is a variable whose value cannot be modified after it is initialized. It is often used to define constants.

   C++11, C++14, and C++17 (no changes)
   The behavior of const variables remains the same across C++11, C++14, and C++17.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
int main() {
    const int x = 10;  // Constant integer variable
    // x = 20;  // Error: Cannot modify a constant variable

    cout << "x: " << x << endl;   //x: 10
    return 0;
}
/* 
In this example, x is a constant variable, and trying to modify it will result in a compilation error.
*/





2. const with Methods (Const Methods)
   A const method is a method that does not modify any member variables of the class. 
   This is enforced by appending const to the method declaration.

   C++11, C++14, and C++17 (no changes)
   The syntax and behavior of const member functions are the same across these versions.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
class MyClass {
  public:
    int value;

    MyClass(int val) : value(val) {}

    void printValue() const {  // Const member function
        cout << "Value: " << value << std::endl;
    }

    void modifyValue() {
        value = 20;  // This works because it's a non-const method
    }
};

int main() {
    MyClass obj(10);
    obj.printValue();  // Allowed: printValue() is const
    // obj.modifyValue();  // Error: Cannot call modifyValue() on const object

    const MyClass obj2(30);
    obj2.printValue();  // Allowed: printValue() is const
    // obj2.modifyValue();  // Error: Cannot call modifyValue() on const object
    return 0;
}
/*
Value: 10
Value: 30



Explanation: printValue() is a constant method, which means it cannot modify any non-static member variables of the class.
If you try to call a non-const method (modifyValue()) on a const object, it will result in a compilation error.
*/








3. const with Pointers
   const can be used in combination with pointers to indicate that the pointer or the data being pointed to is constant (immutable).

   C++11, C++14, and C++17 (no changes)
   The syntax and behavior of const pointers are the same across C++11, C++14, and C++17.

//Example (C++11, C++14, C++17):
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    const int* ptr1 = &x;  // Pointer to const int (data is constant)
    // *ptr1 = 20;  // Error: Cannot modify the data through ptr1

    int* const ptr2 = &x;  // Constant pointer (pointer is constant)
    *ptr2 = 20;  // Allowed: Can modify the data
    // ptr2 = &y;  // Error: Cannot change the pointer itself

    std::cout << "x: " << x << std::endl;
    return 0;
}
/* 
x: 20


Explanation:
ptr1 is a pointer to a const int, so the data cannot be modified through this pointer.
ptr2 is a constant pointer, meaning the pointer cannot be changed to point to another address, but the data it points to can be modified.
 */




4. const with Arrays

When you declare an array with const, it means the elements of the array cannot be modified.

C++11, C++14, and C++17 (no changes)

The syntax for const arrays remains the same.

Example (C++11, C++14, C++17):

#include <iostream>

int main() {
    const int arr[] = {1, 2, 3};  // Array of constant integers
    // arr[0] = 10;  // Error: Cannot modify a constant array element

    std::cout << "arr[0]: " << arr[0] << std::endl;
    return 0;
}


Explanation: The array elements are const, meaning they cannot be modified. However, the array itself is not a constant pointer, so you could reassign the pointer.

5. const with References

A const reference is a reference to a constant value, meaning you cannot modify the referenced value through the reference.

C++11, C++14, and C++17 (no changes)

The behavior of const references remains the same across these versions.

Example (C++11, C++14, C++17):

#include <iostream>

int main() {
    int x = 10;
    const int& ref = x;  // Reference to const int
    // ref = 20;  // Error: Cannot modify a const reference

    std::cout << "ref: " << ref << std::endl;
    return 0;
}


Explanation: ref is a constant reference, so you cannot modify the value of x through ref.

6. const with Templates (C++11 and later)

In C++11 and later, you can use const in template arguments to ensure the argument is constant.

C++11, C++14, and C++17 (no changes)

The use of const in template arguments is the same across these versions.

Example (C++11, C++14, C++17):

#include <iostream>

template <typename T>
void printConst(const T& val) {  // Constant reference parameter
    std::cout << "Value: " << val << std::endl;
}

int main() {
    const int x = 100;
    printConst(x);  // Passed as a const reference

    return 0;
}


Explanation: In the template function printConst, the argument val is passed as a constant reference, meaning it cannot be modified inside the function.

7. const with Lambdas (C++11 and later)

In C++11 and beyond, you can declare a lambda expression that does not modify its captured variables by marking it as const.

C++11, C++14, and C++17 (no changes)

The ability to specify const on lambda captures remains the same across C++11, C++14, and C++17.

Example (C++11, C++14, C++17):

#include <iostream>

int main() {
    int x = 10;
    auto lambda = [x]() mutable {  // `mutable` allows modification of captured variable
        x += 5;
        std::cout << "Lambda captured x: " << x << std::endl;
    };
    lambda();

    std::cout << "x outside lambda: " << x << std::endl;  // x remains unchanged outside the lambda
    return 0;
}


Explanation: The mutable keyword allows the lambda to modify the captured variable, even if it is captured by value.

If you capture by reference and use const, the lambda cannot modify the captured variable.

8. const with Type Aliases (C++11 and later)

In C++11 and later, const can also be applied to type aliases to specify that the alias refers to a constant type.

C++11, C++14, and C++17 (no changes)

The use of const in type aliases remains the same.

Example (C++11, C++14, C++17):

#include <iostream>

int main() {
    const int* ptr;  // Pointer to constant integer
    ptr = new int(5);
    std::cout << "*ptr: " << *ptr << std::endl;

    delete ptr;
    return 0;
}

9. const with Default Arguments (C++11 and later)

You can also use const with default function arguments to enforce immutability of the default argument.

C++11, C++14, and C++17 (no changes)

The usage of const with default arguments is consistent across C++11, C++14, and C++17.

Example (C++11, C++14, C++17):

#include <iostream>

void printMessage(const std::string& message = "Default Message") {
    std::cout << message << std::endl;
}

int main() {
    printMessage();  // Uses default message
    printMessage("Hello, World!");  // Uses provided message
    return 0;
}


Explanation: The parameter message is a constant reference, ensuring that the argument cannot be modified within the function.

Summary of const usage:

const variables: Values cannot be modified after initialization (C++11, C++14, C++17).

const methods: Methods that cannot modify the class's member variables (C++11, C++14, C++17).

const pointers: Indicate that the data or the pointer itself is constant (C++11, C++14, C++17).

const arrays: Elements of the array cannot be modified (C++11, C++14, C++17).

const references: Prevent modification of the referenced value (C++11, C++14, C++17).

const templates: Ensure constant arguments (C++11, C++14, C++17).

const with lambdas: Lambdas can capture variables as constant (C++11 and later).

const with type aliases: Ensures the alias refers to a constant type (C++11 and later).

const with default arguments: Enforces immutability of default arguments (C++11 and later).