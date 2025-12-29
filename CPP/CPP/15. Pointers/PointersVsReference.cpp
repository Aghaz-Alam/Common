1️⃣ Pointers vs References

References (&)

Must be initialized when declared.

Cannot be reseated (cannot refer to another object later).

Cannot be nullptr.

Syntax is simpler, safer, ideal for function parameters and return types when you want guaranteed non-null access.

Pointers (*)

Can be null, can be reseated.

Required for dynamic allocation (new/delete) or optional objects.

Needed when you want to manage ownership manually.

Example:

void increment(int& ref) { ref++; }      // Reference: safe, cannot be null
void incrementPtr(int* ptr) {            // Pointer: can be null
    if(ptr) (*ptr)++;
}

int main() {
    int x = 5;
    increment(x);      // x = 6
    incrementPtr(&x);  // x = 7
}


✅ Rule of Thumb:

Use references if the object is guaranteed to exist.

Use pointers if nullability or reassignment is required.

2️⃣ Smart Pointers for Resource Safety

Modern C++ encourages smart pointers to avoid manual memory management:
| Smart Pointer     | Use Case                                                                          |
| ----------------- | --------------------------------------------------------------------------------- |
| `std::unique_ptr` | Exclusive ownership, automatic deletion when out of scope.                        |
| `std::shared_ptr` | Shared ownership, reference-counted.                                              |
| `std::weak_ptr`   | Breaks cycles in `shared_ptr` graphs; observes object without extending lifetime. |


Example:

#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> uptr = std::make_unique<int>(42);
    std::cout << *uptr << "\n"; // 42

    std::shared_ptr<int> sptr1 = std::make_shared<int>(100);
    std::shared_ptr<int> sptr2 = sptr1; // shared ownership
    std::cout << *sptr2 << "\n"; // 100
}


✅ Smart pointers automatically delete the resource and prevent leaks.

3️⃣ Avoid Dangling Pointers and References

A dangling pointer/reference occurs when the memory it points to is freed or goes out of scope.

Bad example:

int* dangling() {
    int x = 10;
    return &x; // ❌ x will be destroyed after function returns
}


Safe approach:

Use smart pointers (std::unique_ptr / std::shared_ptr).

Avoid returning references/pointers to local variables.

4️⃣ std::move and Rvalue References for Performance

Rvalue references (&&) allow move semantics, avoiding expensive copies for large objects.

Example:

#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1 = {1,2,3,4};
    std::vector<int> v2 = std::move(v1); // efficient, no copy
    std::cout << v2.size(); // 4
    std::cout << v1.size(); // 0, v1 is now empty
}


✅ Use std::move when you want to transfer ownership of resources.

5️⃣ std::span for Safe Array/View Handling

std::span (C++20) is a non-owning view of a contiguous sequence (array, vector, etc.). It provides safe access without copying.

Example:

#include <span>
#include <vector>
#include <iostream>

void printElements(std::span<int> s) {
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int> v = {1,2,3,4,5};
    printElements(v); // works safely
}


✅ Advantages:

No raw pointers needed.

Knows size automatically.

Safer than passing T* + size.

Summary Table
Example:

#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> uptr = std::make_unique<int>(42);
    std::cout << *uptr << "\n"; // 42

    std::shared_ptr<int> sptr1 = std::make_shared<int>(100);
    std::shared_ptr<int> sptr2 = sptr1; // shared ownership
    std::cout << *sptr2 << "\n"; // 100
}


✅ Smart pointers automatically delete the resource and prevent leaks.

3️⃣ Avoid Dangling Pointers and References

A dangling pointer/reference occurs when the memory it points to is freed or goes out of scope.

Bad example:

int* dangling() {
    int x = 10;
    return &x; // ❌ x will be destroyed after function returns
}


Safe approach:

Use smart pointers (std::unique_ptr / std::shared_ptr).

Avoid returning references/pointers to local variables.

4️⃣ std::move and Rvalue References for Performance

Rvalue references (&&) allow move semantics, avoiding expensive copies for large objects.

Example:

#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1 = {1,2,3,4};
    std::vector<int> v2 = std::move(v1); // efficient, no copy
    std::cout << v2.size(); // 4
    std::cout << v1.size(); // 0, v1 is now empty
}


✅ Use std::move when you want to transfer ownership of resources.

5️⃣ std::span for Safe Array/View Handling

std::span (C++20) is a non-owning view of a contiguous sequence (array, vector, etc.). It provides safe access without copying.

Example:

#include <span>
#include <vector>
#include <iostream>

void printElements(std::span<int> s) {
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int> v = {1,2,3,4,5};
    printElements(v); // works safely
}


✅ Advantages:

No raw pointers needed.

Knows size automatically.

Safer than passing T* + size.

Summary Table
| Feature                  | When to Use                                                      |
| ------------------------ | ---------------------------------------------------------------- |
| Reference (`&`)          | Guaranteed non-null, simpler syntax, function parameters/returns |
| Pointer (`*`)            | Optional or dynamic objects, need reassignment or nullability    |
| Smart pointers           | Resource ownership management, prevent leaks/dangling            |
| Rvalue references (`&&`) | Move semantics, avoid expensive copies                           |
| `std::span`              | Safe, lightweight view over arrays or vectors                    |
