1️⃣ Type Traits in C++11
Example: std::is_integral, std::is_floating_point, std::is_pointer, std::is_same, std::remove_reference
#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    cout << boolalpha;

    cout << "is_integral<int>: " << is_integral<int>::value << endl;
    cout << "is_integral<double>: " << is_integral<double>::value << endl;

    cout << "is_pointer<int*>: " << is_pointer<int*>::value << endl;
    cout << "is_pointer<int>: " << is_pointer<int>::value << endl;

    cout << "is_same<int, int>: " << is_same<int, int>::value << endl;
    cout << "is_same<int, double>: " << is_same<int, double>::value << endl;

    cout << "remove_reference<int&>::type is int: " 
         << is_same<remove_reference<int&>::type, int>::value << endl;

    return 0;
}
/* 
Output:
is_integral<int>: true
is_integral<double>: false
is_pointer<int*>: true
is_pointer<int>: false
is_same<int, int>: true
is_same<int, double>: false
remove_reference<int&>::type is int: true
*/



2️⃣ Type Traits in C++14
Example: std::is_convertible, std::is_trivially_copyable, std::make_signed, std::make_unsigned
#include <iostream>
#include <type_traits>
#include <string>
using namespace std;

struct Base { virtual ~Base() {} };
struct Derived : public Base {};

int main() {
    cout << boolalpha;

    cout << "is_convertible<Derived*, Base*>: "
         << is_convertible<Derived*, Base*>::value << endl;
    cout << "is_convertible<Base*, Derived*>: "
         << is_convertible<Base*, Derived*>::value << endl;

    cout << "is_trivially_copyable<int>: "
         << is_trivially_copyable<int>::value << endl;
    cout << "is_trivially_copyable<string>: "
         << is_trivially_copyable<string>::value << endl;

    cout << "make_signed<unsigned int>::type is int: "
         << is_same<make_signed<unsigned int>::type, int>::value << endl;
    cout << "make_unsigned<int>::type is unsigned int: "
         << is_same<make_unsigned<int>::type, unsigned int>::value << endl;

    return 0;
}
/* 
Output:
is_convertible<Derived*, Base*>: true
is_convertible<Base*, Derived*>: false
is_trivially_copyable<int>: true
is_trivially_copyable<string>: false
make_signed<unsigned int>::type is int: true
make_unsigned<int>::type is unsigned int: true
*/



3️⃣ Type Traits in C++17
Example: std::is_invocable, std::is_nothrow_invocable, std::is_trivially_constructible, std::is_copy_constructible
#include <iostream>
#include <type_traits>
#include <functional>
#include <string>
using namespace std;

void foo() noexcept {}
void bar() { throw runtime_error("error"); }

int main() {
    cout << boolalpha;

    cout << "is_nothrow_invocable<void()>: "
         << is_nothrow_invocable<void()>::value << endl;
    cout << "is_nothrow_invocable<decltype(foo)>: "
         << is_nothrow_invocable<decltype(foo)>::value << endl;
    cout << "is_nothrow_invocable<decltype(bar)>: "
         << is_nothrow_invocable<decltype(bar)>::value << endl;

    cout << "is_invocable<function<void()>>: "
         << is_invocable<function<void()>>::value << endl;

    cout << "is_trivially_constructible<int>: "
         << is_trivially_constructible<int>::value << endl;

    cout << "is_copy_constructible<string>: "
         << is_copy_constructible<string>::value << endl;

    return 0;
}
/* 
Output:
is_nothrow_invocable<void()>: true
is_nothrow_invocable<decltype(foo)>: true
is_nothrow_invocable<decltype(bar)>: false
is_invocable<function<void()>>: true
is_trivially_constructible<int>: true
is_copy_constructible<string>: true
*/


4️⃣ Type Traits in C++20
Example: std::is_constant_evaluated, std::is_final, std::is_aggregate, std::remove_cvref
#include <iostream>
#include <type_traits>
using namespace std;

struct A {};
struct B final {};

int main() {
    cout << boolalpha;

    // Constant evaluation check
    constexpr int x = [](){
        if (is_constant_evaluated()) return 42;
        else return 0;
    }();
    cout << "x (constexpr check): " << x << endl;

    cout << "is_final<A>: " << is_final<A>::value << endl;
    cout << "is_final<B>: " << is_final<B>::value << endl;

    cout << "is_aggregate<A>: " << is_aggregate<A>::value << endl;

    cout << "remove_cvref<const volatile int&>::type is int: "
         << is_same<remove_cvref<const volatile int&>::type, int>::value << endl;

    return 0;
}
/* 
Output:
x (constexpr check): 42
is_final<A>: false
is_final<B>: true
is_aggregate<A>: true
remove_cvref<const volatile int&>::type is int: true
*/