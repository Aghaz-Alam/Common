std::optional 
std::enable if

std::function




//std::optional 
The std::optional class template was introduced in C++17 as part of the standard library. 
It is a type that may or may not contain a value, essentially wrapping an object with the possibility of being "empty" (i.e., containing no value).

Since std::optional is not available in C++11 and C++14, I will demonstrate the following:

C++11: Simulate std::optional behavior using pointers, std::unique_ptr, or custom wrappers.

C++14: Same as C++11, since std::optional isn’t part of the C++14 standard, 
but improvements like generalized lambda captures can help with some patterns.

C++17: Directly use std::optional from the standard library.



1. Simulating std::optional in C++11 / C++14
Since std::optional is not available in C++11 or C++14, we can simulate it using pointers 
(e.g., std::unique_ptr) or by implementing a custom Optional class.

C++11 / C++14 (using std::unique_ptr)
#include <iostream>
#include <memory>  // For std::unique_ptr
// Simulate std::optional using std::unique_ptr
std::unique_ptr<int> get_optional_value(bool provide_value) {
    if (provide_value) {
        return std::make_unique<int>(42);  // Return an optional containing the value
    }
    return nullptr;  // Return an empty "optional" (nullptr)
}
int main() {
    auto value = get_optional_value(true);
    if (value) {
        std::cout << "Got value: " << *value << std::endl;  // Dereference the value
    } else {
        std::cout << "No value\n";
    }

    value = get_optional_value(false);
    if (value) {
        std::cout << "Got value: " << *value << std::endl;
    } else {
        std::cout << "No value\n";  // Will be printed
    }

   return 0;
}



C++11 / C++14 (using custom Optional wrapper)
We can implement a basic Optional class template to simulate std::optional.

#include <iostream>
#include <memory>  // For nullptr
template <typename T>
class Optional {
  public:
    Optional() : has_value(false) {}

    Optional(T value) : has_value(true), value(value) {}

    bool has_value() const {
        return has_value;
    }

    T& value() {
        if (!has_value) {
            throw std::runtime_error("No value");
        }
        return value;
    }

    const T& value() const {
        if (!has_value) {
            throw std::runtime_error("No value");
        }
        return value;
    }

  private:
    bool has_value;
    T value;
};
int main() {
    Optional<int> opt1(42);
    if (opt1.has_value()) {
        std::cout << "Optional contains: " << opt1.value() << std::endl;
    }

    Optional<int> opt2;
    if (!opt2.has_value()) {
        std::cout << "Optional is empty\n";  // Will be printed
    }

   return 0;
}





2. Using std::optional in C++17
In C++17, std::optional was introduced to the standard library. Here is how you can use it.

Basic Example: Using std::optional
#include <iostream>
#include <optional>  // For std::optional

std::optional<int> get_optional_value(bool provide_value) {
    if (provide_value) {
        return 42;  // Return an optional containing the value
    }
    return std::nullopt;  // Return an empty optional
}

int main() {
    auto value = get_optional_value(true);
    if (value) {
        std::cout << "Got value: " << value.value() << std::endl;
    } else {
        std::cout << "No value\n";
    }

    value = get_optional_value(false);
    if (value) {
        std::cout << "Got value: " << value.value() << std::endl;
    } else {
        std::cout << "No value\n";  // Will be printed
    }

   return 0;
}



Example: Using std::optional with std::nullopt

std::nullopt is used to represent the "empty" state of an std::optional.

#include <iostream>
#include <optional>  // For std::optional and std::nullopt

std::optional<int> get_optional_value(bool provide_value) {
    if (provide_value) {
        return 42;
    }
    return std::nullopt;  // Explicitly returning no value
}

int main() {
    auto value = get_optional_value(true);
    if (value.has_value()) {
        std::cout << "Optional contains: " << value.value() << std::endl;
    } else {
        std::cout << "No value\n";
    }

    value = get_optional_value(false);
    if (value.has_value()) {
        std::cout << "Optional contains: " << value.value() << std::endl;
    } else {
        std::cout << "No value\n";  // Will be printed
    }

    return 0;
}

Example: Using std::optional with default values

You can use value_or() to return a default value when the optional is empty.

#include <iostream>
#include <optional>  // For std::optional

std::optional<int> get_optional_value(bool provide_value) {
    if (provide_value) {
        return 42;
    }
    return std::nullopt;  // Empty optional
}

int main() {
    std::optional<int> value = get_optional_value(true);
    std::cout << "Value or default: " << value.value_or(0) << std::endl;  // 42

    value = get_optional_value(false);
    std::cout << "Value or default: " << value.value_or(0) << std::endl;  // 0

    return 0;
}

Example: Using std::optional with a function that returns it

You can return std::optional from functions to represent the absence or presence of a value.

#include <iostream>
#include <optional>

std::optional<int> find_value(bool found) {
    if (found) {
        return 42;  // Value found
    }
    return std::nullopt;  // Value not found
}

int main() {
    std::optional<int> result = find_value(true);
    if (result) {
        std::cout << "Found: " << *result << std::endl;  // 42
    } else {
        std::cout << "Not found\n";
    }

    result = find_value(false);
    if (result) {
        std::cout << "Found: " << *result << std::endl;
    } else {
        std::cout << "Not found\n";  // Not found
    }

    return 0;
}




Example: Using std::optional with complex types
std::optional works with complex types too, like classes or structs.

#include <iostream>
#include <optional>
#include <string>
struct Person {
    std::string name;
    int age;

    Person(std::string n, int a) : name(n), age(a) {}
};
std::optional<Person> get_person(bool provide_person) {
    if (provide_person) {
        return Person("Alice", 30);
    }
    return std::nullopt;
}
int main() {
    auto person = get_person(true);
    if (person) {
        std::cout << "Name: " << person->name << ", Age: " << person->age << std::endl;
    } else {
        std::cout << "No person data\n";
    }

    person = get_person(false);
    if (person) {
        std::cout << "Name: " << person->name << ", Age: " << person->age << std::endl;
    } else {
        std::cout << "No person data\n";  // Will be printed
    }

  return 0;
}




//std::optional
std::optional was introduced in C++17. It is used to represent optional values — values that may or may not be present.
C++11 / C++14: There is no native std::optional in these versions, but you can simulate it using pointers or custom wrappers.
C++17: std::optional is fully supported.
C++11 / C++14 (using pointers or custom wrapper)
Since std::optional is not available, we simulate its behavior using pointers (or std::unique_ptr for a safer, non-nullable representation).

Example:
#include <iostream>
#include <memory>  // For std::unique_ptr

// Simulating std::optional using std::unique_ptr
std::unique_ptr<int> get_optional_value(bool provide_value) {
    if (provide_value) {
        return std::make_unique<int>(42);
    }
    return nullptr;
}
int main() {
    auto value = get_optional_value(true);
    if (value) {
        std::cout << "Got value: " << *value << std::endl;
    } else {
        std::cout << "No value\n";
    }

    value = get_optional_value(false);
    if (value) {
        std::cout << "Got value: " << *value << std::endl;
    } else {
        std::cout << "No value\n";
    }

   return 0;
}


ummary of std::optional Usage Across C++ Versions:
C++11 / C++14: std::optional is not available. You can simulate it using pointers (like std::unique_ptr) or by writing a custom wrapper class 
like Optional.

C++17: Use the std::optional class directly. It provides a convenient, type-safe way to represent optional values, 
and includes functions like value_or, has_value, value, and the use of std::nullopt.


Important Notes for C++17+:
std::optional can hold any type and is particularly useful when you need a value that might or might not be present.
std::nullopt is used to represent an empty optional.
value_or() is useful for providing a default value if the optional is empty.



/*--------------------------------------------------------------------------------------------*/