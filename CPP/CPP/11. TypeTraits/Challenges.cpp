Challenge 1: Reference & cv-qualification trap
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;

    using T = const int&;

    std::cout << std::is_same<T, int>::value << "\n";
    std::cout << std::is_same<std::remove_reference<T>::type, int>::value << "\n";
    std::cout << std::is_same<std::remove_cv<std::remove_reference<T>::type>::type, int>::value << "\n";
}
/* 
✅ Output
false
false
true

💡 Insight

remove_reference does not remove const.
You must chain traits.
*/




🔹 Challenge 2: Pointer vs array decay confusion
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;

    int arr[5];

    std::cout << std::is_pointer<decltype(arr)>::value << "\n";
    std::cout << std::is_array<decltype(arr)>::value << "\n";
    std::cout << std::is_pointer<decltype(&arr[0])>::value << "\n";
}
/* 
✅ Output
false
true
true

💡 Insight
Arrays do not decay unless passed to functions.
*/




🔹 Challenge 3: Trivial vs non-trivial destructor
#include <iostream>
#include <type_traits>

struct A {
    int x;
};

struct B {
    ~B() {}
};

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_trivially_destructible<A>::value << "\n";
    std::cout << std::is_trivially_destructible<B>::value << "\n";
}
/* 
✅ Output
true
false

💡 Insight
User-defined destructor kills triviality.
*/





🔹 Challenge 4: is_convertible vs constructors
#include <iostream>
#include <type_traits>

struct X {
    explicit X(int) {}
};

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_convertible<int, X>::value << "\n";
    std::cout << std::is_constructible<X, int>::value << "\n";
}
/* 
✅ Output
false
true

💡 Insight
explicit constructors are not implicit conversions.
*/




🔹 Challenge 5: noexcept lies detector
#include <iostream>
#include <type_traits>

void f() noexcept {}
void g() {}

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_nothrow_invocable<decltype(f)>::value << "\n";
    std::cout << std::is_nothrow_invocable<decltype(g)>::value << "\n";
}
/* 
✅ Output
true
false

💡 Insight
Trait checks function signature, not implementation.
*/






🔹 Challenge 6: SFINAE via enable_if
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print(T) {
    std::cout << "Integral\n";
}

template<typename T>
typename std::enable_if<!std::is_integral<T>::value>::type
print(T) {
    std::cout << "Non-integral\n";
}

int main() {
    print(10);
    print(3.14);
}
/* 
✅ Output
Integral
Non-integral

💡 Insight
Classic C++11 SFINAE dispatch.
*/





🔹 Challenge 7: is_base_of vs pointers
#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_base_of<Base, Derived>::value << "\n";
    std::cout << std::is_base_of<Base*, Derived*>::value << "\n";
}
/* 
✅ Output
true
false

💡 Insight
is_base_of works on types, not pointers.
*/




🔹 Challenge 8: Move constructible but not copyable
#include <iostream>
#include <type_traits>
struct A {
    A() = default;
    A(const A&) = delete;
    A(A&&) = default;
};
int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_copy_constructible<A>::value << "\n";
    std::cout << std::is_move_constructible<A>::value << "\n";
}
/* 
✅ Output
false
true

💡 Insight
Important for modern RAII & ownership types.
*/






🔹 Challenge 9: Callable detection (C++17)
#include <iostream>
#include <type_traits>

struct Fun {
    void operator()(int) {}
};

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_invocable<Fun, int>::value << "\n";
    std::cout << std::is_invocable<Fun, double>::value << "\n";
    std::cout << std::is_invocable<Fun>::value << "\n";
}
/* 
✅ Output
true
true
false

💡 Insight
Implicit conversions are allowed for arguments.
*/




🔹 Challenge 10: decltype(auto) + traits mind-bender
#include <iostream>
#include <type_traits>

int x = 10;

decltype(auto) f1() { return x; }
decltype(auto) f2() { return (x); }

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_reference<decltype(f1())>::value << "\n";
    std::cout << std::is_reference<decltype(f2())>::value << "\n";
}
/* 
✅ Output
false
true

💡 Insight
Parentheses change value category.
*/