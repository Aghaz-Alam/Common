1️⃣ std::is_integral (C++11)
#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_integral<int>::value << "\n";
    std::cout << std::is_integral<double>::value << "\n";
}
Explanation:
Checks if type is integer.
Output:
true
false


2️⃣ std::is_floating_point (C++11)
#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_floating_point<float>::value << "\n";
    std::cout << std::is_floating_point<int>::value << "\n";
}
Output:
true
false


3️⃣ std::is_arithmetic (C++11)
#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic<int>::value << "\n";
    std::cout << std::is_arithmetic<double>::value << "\n";
    std::cout << std::is_arithmetic<std::string>::value << "\n";
}
Output:
true
true
false


4️⃣ std::is_pointer (C++11)
#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pointer<int*>::value << "\n";
    std::cout << std::is_pointer<int>::value << "\n";
}
Output:
true
false



5️⃣ std::is_array (C++11)
#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_array<int[5]>::value << "\n";
    std::cout << std::is_array<int>::value << "\n";
}
Output:
true
false
r { Red, Blue };
int m


6️⃣ std::is_class (C++11)
#include <iostream>
#include <type_traits>
struct MyClass {};
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_class<MyClass>::value << "\n";
    std::cout << std::is_class<int>::value << "\n";
}
Output:
true
false



7️⃣ std::is_enum (C++11)
#include <iostream>
#include <type_traits>
enum Color { Red, Blue };
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_enum<Color>::value << "\n";
    std::cout << std::is_enum<int>::value << "\n";
}
Output:
true
false



8️⃣ std::is_same (C++11)
#include <iostream>
#include <type_traits>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_same<int, int>::value << "\n";
    std::cout << std::is_same<int, long>::value << "\n";
}
Output:
true
false



9️⃣ std::is_base_of (C++11)
#include <iostream>
#include <type_traits>
struct Base {};
struct Derived : Base {};
struct Other {};
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_base_of<Base, Derived>::value << "\n";
    std::cout << std::is_base_of<Base, Other>::value << "\n";
}
Output:
true
false



🔟 std::is_convertible (C++11)
#include <iostream>
#include <type_traits>
#include <string>
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_convertible<int, double>::value << "\n";
    std::cout << std::is_convertible<std::string, int>::value << "\n";
}

Output:
true
false




Program 1 — std::is_signed & std::enable_if
✔ Purpose

Enable a function only for signed types.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_signed<T>::value, void>::type
checkType(T) {
    std::cout << "Signed type!\n";
}

template <typename T>
typename std::enable_if<!std::is_signed<T>::value, void>::type
checkType(T) {
    std::cout << "Not a signed type!\n";
}

int main() {
    checkType(-5);       // int -> signed
    checkType(10u);      // unsigned int -> not signed
}

▶ OUTPUT
Signed type!
Not a signed type!

Program 2 — std::is_unsigned
✔ Purpose

Allow a function only for unsigned types.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type
onlyUnsigned(T) {
    std::cout << "This is an unsigned type.\n";
}

int main() {
    onlyUnsigned(12u);   // OK
    // onlyUnsigned(12); // ERROR (signed)
}

▶ OUTPUT
This is an unsigned type.

Program 3 — std::is_pointer
✔ Purpose

Enable function only for pointer types.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_pointer<T>::value, void>::type
show(T) {
    std::cout << "Pointer detected!\n";
}

int main() {
    int x = 5;
    int* p = &x;
    show(p);     // OK
}

▶ OUTPUT
Pointer detected!

Program 4 — std::is_array
✔ Purpose

Enable function only for array types.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_array<T>::value, void>::type
printArrayInfo(T&) {
    std::cout << "This is an array.\n";
}

int main() {
    int arr[5];
    printArrayInfo(arr);
}

▶ OUTPUT
This is an array.

Program 5 — std::is_enum
✔ Purpose

Detect if T is enum.

▶ CODE
#include <iostream>
#include <type_traits>

enum Color { Red, Green, Blue };

template <typename T>
typename std::enable_if<std::is_enum<T>::value, void>::type
checkEnum(T) {
    std::cout << "Enum type detected!\n";
}

int main() {
    checkEnum(Red);
}

▶ OUTPUT
Enum type detected!

Program 6 — std::is_class
✔ Purpose

Enable function only for class types.

▶ CODE
#include <iostream>
#include <type_traits>

class MyClass {};

template <typename T>
typename std::enable_if<std::is_class<T>::value, void>::type
process(T) {
    std::cout << "Class type detected!\n";
}

int main() {
    MyClass obj;
    process(obj);
}

▶ OUTPUT
Class type detected!

Program 7 — std::is_same
✔ Purpose

Enable only if T is exactly int.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_same<T, int>::value, void>::type
onlyInt(T) {
    std::cout << "This is an INT type.\n";
}

int main() {
    onlyInt(10);   // OK
    // onlyInt(3.14); // ERROR
}

▶ OUTPUT
This is an INT type.

Program 8 — std::is_const
✔ Purpose

Enable only for const types.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_const<T>::value, void>::type
checkConst(T&) {
    std::cout << "Const type detected!\n";
}

int main() {
    const int x = 10;
    checkConst(x);
}

▶ OUTPUT
Const type detected!

Program 9 — std::is_reference
✔ Purpose

Enable only for references.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_reference<T>::value, void>::type
testRef(T) {
    std::cout << "Reference detected!\n";
}

int main() {
    int a = 42;
    int& r = a;
    testRef(r);
}

▶ OUTPUT
Reference detected!

Program 10 — std::is_void
✔ Purpose

Enable only when T is void.

▶ CODE
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_void<T>::value, void>::type
foo() {
    std::cout << "Void type detected!\n";
}

int main() {
    foo<void>();
}

▶ OUTPUT
Void type detected!




1️⃣ std::is_member_pointer
#include <iostream>
#include <type_traits>

struct A { int x; void func() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_pointer<int A::*>::value << "\n";
    std::cout << std::is_member_pointer<void (A::*)()>::value << "\n";
    std::cout << std::is_member_pointer<int*>::value << "\n";
}

Output:
true
true
false

22️⃣ std::is_member_object_pointer
#include <iostream>
#include <type_traits>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_object_pointer<int A::*>::value << "\n";
    std::cout << std::is_member_object_pointer<void(A::*)()>::value << "\n";
}

Output:
true
false

23️⃣ std::is_member_function_pointer
#include <iostream>
#include <type_traits>

struct A { void f(){} int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_function_pointer<void(A::*)()>::value << "\n";
    std::cout << std::is_member_function_pointer<int A::*>::value << "\n";
}

Output:
true
false

24️⃣ std::is_signed
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_signed<int>::value << "\n";
    std::cout << std::is_signed<unsigned int>::value << "\n";
}

Output:
true
false

25️⃣ std::is_unsigned
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_unsigned<unsigned short>::value << "\n";
    std::cout << std::is_unsigned<int>::value << "\n";
}

Output:
true
false

26️⃣ std::is_empty
#include <iostream>
#include <type_traits>

struct Empty {};
struct NotEmpty { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_empty<Empty>::value << "\n";
    std::cout << std::is_empty<NotEmpty>::value << "\n";
}

Output:
true
false

27️⃣ std::is_literal_type (C++11)
#include <iostream>
#include <type_traits>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_literal_type<int>::value << "\n";
    std::cout << std::is_literal_type<A>::value << "\n";
}

Output:
true
true

28️⃣ std::is_constructible
#include <iostream>
#include <type_traits>
#include <string>

struct A { A(int){} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_constructible<A, int>::value << "\n";
    std::cout << std::is_constructible<A, std::string>::value << "\n";
}

Output:
true
false

29️⃣ std::is_default_constructible
#include <iostream>
#include <type_traits>

struct A { A(){} };
struct B { B(int){} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_default_constructible<A>::value << "\n";
    std::cout << std::is_default_constructible<B>::value << "\n";
}

Output:
true
false

30️⃣ std::is_copy_constructible
#include <iostream>
#include <type_traits>

struct A { };
struct B {
    B(const B&) = delete;   // not copyable
};

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_copy_constructible<A>::value << "\n";
    std::cout << std::is_copy_constructible<B>::value << "\n";
}

Output:
true
false



Program 1 — Using std::is_reference
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_reference<T>::value>::type
check(T) {
    std::cout << "T is a reference type\n";
}

template<typename T>
typename std::enable_if<!std::is_reference<T>::value>::type
check(T) {
    std::cout << "T is NOT a reference type\n";
}

int main() {
    int x = 10;
    check<int&>(x);
    check<int>(x);
}

Output
T is a reference type
T is NOT a reference type

⭐ Program 2 — Using std::is_lvalue_reference
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_lvalue_reference<T>::value>::type
test(T) {
    std::cout << "T is an lvalue reference\n";
}

template<typename T>
typename std::enable_if<!std::is_lvalue_reference<T>::value>::type
test(T) {
    std::cout << "T is NOT an lvalue reference\n";
}

int main() {
    int a = 5;
    test<int&>(a);
    test<int&&>(5);
}

Output
T is an lvalue reference
T is NOT an lvalue reference

⭐ Program 3 — Using std::is_rvalue_reference
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_rvalue_reference<T>::value>::type
checkRef(T&&) {
    std::cout << "T is an rvalue reference\n";
}

template<typename T>
typename std::enable_if<!std::is_rvalue_reference<T>::value>::type
checkRef(T&&) {
    std::cout << "T is NOT an rvalue reference\n";
}

int main() {
    checkRef<int&&>(10);
    int x = 3;
    checkRef<int&>(x);
}

Output
T is an rvalue reference
T is NOT an rvalue reference

⭐ Program 4 — Using std::is_array
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_array<T>::value>::type
checkArr(T&) {
    std::cout << "T is an array type\n";
}

template<typename T>
typename std::enable_if<!std::is_array<T>::value>::type
checkArr(T&) {
    std::cout << "T is NOT an array type\n";
}

int main() {
    int arr[5];
    int x = 10;

    checkArr(arr);
    checkArr(x);
}

Output
T is an array type
T is NOT an array type

⭐ Program 5 — Using std::is_pointer
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_pointer<T>::value>::type
checkPtr(T) {
    std::cout << "T is a pointer\n";
}

template<typename T>
typename std::enable_if<!std::is_pointer<T>::value>::type
checkPtr(T) {
    std::cout << "T is NOT a pointer\n";
}

int main() {
    int x = 10;
    int* p = &x;

    checkPtr(p);
    checkPtr(x);
}

Output
T is a pointer
T is NOT a pointer

⭐ Program 6 — Using std::is_member_pointer
#include <iostream>
#include <type_traits>

class Demo {
public:
    int value;
};

template<typename T>
typename std::enable_if<std::is_member_pointer<T>::value>::type
checkMember(T) {
    std::cout << "T is a member pointer\n";
}

template<typename T>
typename std::enable_if<!std::is_member_pointer<T>::value>::type
checkMember(T) {
    std::cout << "T is NOT a member pointer\n";
}

int main() {
    int Demo::* mp = &Demo::value;
    int x = 10;

    checkMember(mp);
    checkMember(x);
}

Output
T is a member pointer
T is NOT a member pointer





⭐ 1. std::is_pointer with std::enable_if
✔ Program
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_pointer<T>::value, void>::type
check(T) {
    std::cout << "Pointer type\n";
}

template<typename T>
typename std::enable_if<!std::is_pointer<T>::value, void>::type
check(T) {
    std::cout << "Not a pointer type\n";
}

int main() {
    int a = 10;
    int* p = &a;

    check(a);   // not pointer
    check(p);   // pointer
}

✔ Output
Not a pointer type
Pointer type

⭐ 2. std::is_reference
✔ Program
#include <iostream>
#include <type_traits>

template<typename T>
void test(T&) {
    std::cout << "L-value reference\n";
}

template<typename T>
typename std::enable_if<std::is_reference<T>::value, void>::type
check() {
    std::cout << "Reference type\n";
}

template<typename T>
typename std::enable_if<!std::is_reference<T>::value, void>::type
check() {
    std::cout << "Not a reference type\n";
}

int main() {
    check<int&>();   // reference
    check<int>();    // not reference
}

✔ Output
Reference type
Not a reference type

⭐ 3. std::is_const
✔ Program
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_const<T>::value, void>::type
show() {
    std::cout << "Const type\n";
}

template<typename T>
typename std::enable_if<!std::is_const<T>::value, void>::type
show() {
    std::cout << "Non-const type\n";
}

int main() {
    show<const int>();
    show<int>();
}

✔ Output
Const type
Non-const type

⭐ 4. std::is_signed / std::is_unsigned
✔ Program
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_signed<T>::value, void>::type
check() {
    std::cout << "Signed type\n";
}

template<typename T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type
check() {
    std::cout << "Unsigned type\n";
}

int main() {
    check<int>();       // signed
    check<unsigned>();  // unsigned
}

✔ Output
Signed type
Unsigned type

⭐ 5. std::is_array
✔ Program
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_array<T>::value, void>::type
check() {
    std::cout << "Array type\n";
}

template<typename T>
typename std::enable_if<!std::is_array<T>::value, void>::type
check() {
    std::cout << "Not an array type\n";
}

int main() {
    check<int[5]>();
    check<int>();
}

✔ Output
Array type
Not an array type

⭐ 6. std::is_class
✔ Program
#include <iostream>
#include <type_traits>

struct MyClass {};

template<typename T>
typename std::enable_if<std::is_class<T>::value, void>::type
check() {
    std::cout << "Class type\n";
}

template<typename T>
typename std::enable_if<!std::is_class<T>::value, void>::type
check() {
    std::cout << "Not a class type\n";
}

int main() {
    check<MyClass>();
    check<int>();
}

✔ Output
Class type
Not a class type

⭐ 7. std::is_enum
✔ Program
#include <iostream>
#include <type_traits>

enum Color { RED, GREEN, BLUE };

template<typename T>
typename std::enable_if<std::is_enum<T>::value, void>::type
check() {
    std::cout << "Enum type\n";
}

template<typename T>
typename std::enable_if<!std::is_enum<T>::value, void>::type
check() {
    std::cout << "Not an enum type\n";
}

int main() {
    check<Color>();
    check<int>();
}

✔ Output
Enum type
Not an enum type



PROGRAM 1 – std::is_same<T, U>

✔ Enables a function only if two types are exactly the same.

Code
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_same<T, int>::value, void>::type
checkType() {
    std::cout << "T is exactly int\n";
}

template<typename T>
typename std::enable_if<!std::is_same<T, int>::value, void>::type
checkType() {
    std::cout << "T is NOT int\n";
}

int main() {
    checkType<int>();     // matches is_same == true
    checkType<float>();   // matches is_same == false
}

Output
T is exactly int
T is NOT int

PROGRAM 2 – std::is_const

✔ Enables overload if the type is const.

Code
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_const<T>::value, void>::type
print() {
    std::cout << "T is const\n";
}

template<typename T>
typename std::enable_if<!std::is_const<T>::value, void>::type
print() {
    std::cout << "T is NOT const\n";
}

int main() {
    print<const int>();  
    print<int>();        
}

Output
T is const
T is NOT const

PROGRAM 3 – std::is_volatile

✔ Volatile detection using enable_if.

Code
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_volatile<T>::value, void>::type
checkVolatile() {
    std::cout << "T is volatile\n";
}

template<typename T>
typename std::enable_if<!std::is_volatile<T>::value, void>::type
checkVolatile() {
    std::cout << "T is NOT volatile\n";
}

int main() {
    checkVolatile<volatile int>();
    checkVolatile<int>();
}

Output
T is volatile
T is NOT volatile

PROGRAM 4 – std::is_signed

✔ Only enables function when type is signed.

Code
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_signed<T>::value, void>::type
checkSign() {
    std::cout << "T is signed\n";
}

template<typename T>
typename std::enable_if<!std::is_signed<T>::value, void>::type
checkSign() {
    std::cout << "T is NOT signed\n";
}

int main() {
    checkSign<int>();     // signed
    checkSign<unsigned>(); // unsigned
}

Output
T is signed
T is NOT signed

PROGRAM 5 – std::is_unsigned

✔ Opposite of signed.

Code
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type
showUnsigned() {
    std::cout << "T is unsigned\n";
}

template<typename T>
typename std::enable_if<!std::is_unsigned<T>::value, void>::type
showUnsigned() {
    std::cout << "T is NOT unsigned\n";
}

int main() {
    showUnsigned<unsigned int>();
    showUnsigned<int>();
}

Output
T is unsigned
T is NOT unsigned

PROGRAM 6 – std::is_pointer

✔ Detect if a type is a pointer.

Code
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_pointer<T>::value, void>::type
checkPtr() {
    std::cout << "T is a pointer\n";
}

template<typename T>
typename std::enable_if<!std::is_pointer<T>::value, void>::type
checkPtr() {
    std::cout << "T is NOT a pointer\n";
}

int main() {
    checkPtr<int*>();  
    checkPtr<int>();   
}

Output
T is a pointer
T is NOT a pointer




C++11 Batch-2 (Traits 11–20)

1️⃣ std::is_lvalue_reference

#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_lvalue_reference<int&>::value << "\n";
    std::cout << std::is_lvalue_reference<int>::value << "\n";
}


Output:

true
false


2️⃣ std::is_rvalue_reference

#include <iostream>
#include <type_traits>

int main() {
    int&& r = 5;
    std::cout << std::boolalpha;
    std::cout << std::is_rvalue_reference<decltype(r)>::value << "\n";
    std::cout << std::is_rvalue_reference<int>::value << "\n";
}


Output:

true
false


3️⃣ std::is_member_function_pointer

#include <iostream>
#include <type_traits>

struct A { void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_function_pointer<decltype(&A::f)>::value << "\n";
    std::cout << std::is_member_function_pointer<int>::value << "\n";
}


Output:

true
false


4️⃣ std::is_member_object_pointer

#include <iostream>
#include <type_traits>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_object_pointer<decltype(&A::x)>::value << "\n";
    std::cout << std::is_member_object_pointer<int>::value << "\n";
}


Output:

true
false


5️⃣ std::is_union

#include <iostream>
#include <type_traits>

union U { int a; double b; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_union<U>::value << "\n";
    std::cout << std::is_union<int>::value << "\n";
}


Output:

true
false


6️⃣ std::is_function

#include <iostream>
#include <type_traits>

void func() {}

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_function<decltype(func)>::value << "\n";
    std::cout << std::is_function<int>::value << "\n";
}


Output:

true
false


7️⃣ std::is_const

#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_const<const int>::value << "\n";
    std::cout << std::is_const<int>::value << "\n";
}


Output:

true
false


8️⃣ std::is_volatile

#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_volatile<volatile int>::value << "\n";
    std::cout << std::is_volatile<int>::value << "\n";
}


Output:

true
false


9️⃣ std::is_signed

#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_signed<int>::value << "\n";
    std::cout << std::is_signed<unsigned int>::value << "\n";
}


Output:

true
false


🔟 std::is_unsigned

#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_unsigned<unsigned int>::value << "\n";
    std::cout << std::is_unsigned<int>::value << "\n";
}


Output:

true
false



/* ----------------------------------------------------------------------------------------------------------------------------------------- */
C++14 Batch-1 (Traits 1–10)
1️⃣ std::is_integral (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_integral<int>::value << "\n";      // true
    std::cout << std::is_integral<double>::value << "\n";   // false
}


Explanation: Checks if type is integer.

Output:

true
false

2️⃣ std::is_floating_point (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_floating_point<float>::value << "\n";  // true
    std::cout << std::is_floating_point<int>::value << "\n";    // false
}

3️⃣ std::is_arithmetic (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic<int>::value << "\n";       // true
    std::cout << std::is_arithmetic<double>::value << "\n";    // true
    std::cout << std::is_arithmetic<std::string>::value << "\n"; // false
}

4️⃣ std::is_pointer (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int* p = nullptr;
    std::cout << std::boolalpha;
    std::cout << std::is_pointer<decltype(p)>::value << "\n"; // true
    std::cout << std::is_pointer<int>::value << "\n";         // false
}

5️⃣ std::is_array (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_array<int[5]>::value << "\n";   // true
    std::cout << std::is_array<int>::value << "\n";      // false
}

6️⃣ std::is_class (C++14)
#include <iostream>
#include <type_traits>

struct MyClass {};

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_class<MyClass>::value << "\n"; // true
    std::cout << std::is_class<int>::value << "\n";     // false
}

7️⃣ std::is_enum (C++14)
#include <iostream>
#include <type_traits>

enum Color { Red, Blue };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_enum<Color>::value << "\n"; // true
    std::cout << std::is_enum<int>::value << "\n";   // false
}

8️⃣ std::is_same (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_same<int,int>::value << "\n";  // true
    std::cout << std::is_same<int,long>::value << "\n"; // false
}

9️⃣ std::is_base_of (C++14)
#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};
struct Other {};

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_base_of<Base, Derived>::value << "\n"; // true
    std::cout << std::is_base_of<Base, Other>::value << "\n";   // false
}

🔟 std::is_convertible (C++14)
#include <iostream>
#include <type_traits>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_convertible<int,double>::value << "\n";      // true
    std::cout << std::is_convertible<std::string,int>::value << "\n"; // false
}










C++14 Batch-2 (Traits 11–20)
1️⃣ std::is_lvalue_reference (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_lvalue_reference<int&>::value << "\n"; // true
    std::cout << std::is_lvalue_reference<int>::value << "\n";  // false
}

2️⃣ std::is_rvalue_reference (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int&& r = 5;
    std::cout << std::boolalpha;
    std::cout << std::is_rvalue_reference<decltype(r)>::value << "\n"; // true
    std::cout << std::is_rvalue_reference<int>::value << "\n";         // false
}

3️⃣ std::is_member_function_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_function_pointer<decltype(&A::f)>::value << "\n"; // true
    std::cout << std::is_member_function_pointer<int>::value << "\n";            // false
}

4️⃣ std::is_member_object_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_object_pointer<decltype(&A::x)>::value << "\n"; // true
    std::cout << std::is_member_object_pointer<int>::value << "\n";            // false
}

5️⃣ std::is_union (C++14)
#include <iostream>
#include <type_traits>

union U { int a; double b; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_union<U>::value << "\n";  // true
    std::cout << std::is_union<int>::value << "\n"; // false
}

6️⃣ std::is_function (C++14)
#include <iostream>
#include <type_traits>

void func() {}

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_function<decltype(func)>::value << "\n"; // true
    std::cout << std::is_function<int>::value << "\n";            // false
}

7️⃣ std::is_const (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_const<const int>::value << "\n"; // true
    std::cout << std::is_const<int>::value << "\n";       // false
}

8️⃣ std::is_volatile (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_volatile<volatile int>::value << "\n"; // true
    std::cout << std::is_volatile<int>::value << "\n";          // false
}

9️⃣ std::is_signed (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_signed<int>::value << "\n";          // true
    std::cout << std::is_signed<unsigned int>::value << "\n"; // false
}

🔟 std::is_unsigned (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_unsigned<unsigned int>::value << "\n"; // true
    std::cout << std::is_unsigned<int>::value << "\n";          // false
}






C++14 Batch-3 (Traits 21–30)
1️⃣ std::is_default_constructible (C++14)
#include <iostream>
#include <type_traits>

struct A { A() {} };
struct B { B(int) {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_default_constructible<A>::value << "\n"; // true
    std::cout << std::is_default_constructible<B>::value << "\n"; // false
}

2️⃣ std::is_copy_constructible (C++14)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B(const B&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_copy_constructible<A>::value << "\n"; // true
    std::cout << std::is_copy_constructible<B>::value << "\n"; // false
}

3️⃣ std::is_move_constructible (C++14)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B(B&&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_move_constructible<A>::value << "\n"; // true
    std::cout << std::is_move_constructible<B>::value << "\n"; // false
}

4️⃣ std::is_copy_assignable (C++14)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B& operator=(const B&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_copy_assignable<A>::value << "\n"; // true
    std::cout << std::is_copy_assignable<B>::value << "\n"; // false
}

5️⃣ std::is_move_assignable (C++14)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B& operator=(B&&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_move_assignable<A>::value << "\n"; // true
    std::cout << std::is_move_assignable<B>::value << "\n"; // false
}

6️⃣ std::is_destructible (C++14)
#include <iostream>
#include <type_traits>

struct A {};
struct B { ~B() = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_destructible<A>::value << "\n"; // true
    std::cout << std::is_destructible<B>::value << "\n"; // false
}

7️⃣ std::is_trivially_destructible (C++14)
#include <iostream>
#include <type_traits>

struct A {};          // trivial destructor
struct B { ~B() {} }; // non-trivial destructor

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_destructible<A>::value << "\n"; // true
    std::cout << std::is_trivially_destructible<B>::value << "\n"; // false
}

8️⃣ std::is_trivial (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; };  // trivial
struct B { B() {} int y; }; // non-trivial (user constructor)

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivial<A>::value << "\n"; // true
    std::cout << std::is_trivial<B>::value << "\n"; // false
}

9️⃣ std::is_standard_layout (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; double y; }; // standard layout
struct B { virtual void f() {} }; // not standard layout

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_standard_layout<A>::value << "\n"; // true
    std::cout << std::is_standard_layout<B>::value << "\n"; // false
}

🔟 std::is_pod (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; double y; }; // POD
struct B { B() {} int y; };    // not POD

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pod<A>::value << "\n"; // true
    std::cout << std::is_pod<B>::value << "\n"; // false
}




C++14 Batch-4 (Traits 31–40)
1️⃣ std::is_empty (C++14)
#include <iostream>
#include <type_traits>

struct A {};        // empty
struct B { int x; }; // not empty

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_empty<A>::value << "\n"; // true
    std::cout << std::is_empty<B>::value << "\n"; // false
}

2️⃣ std::is_polymorphic (C++14)
#include <iostream>
#include <type_traits>

struct A {};             // not polymorphic
struct B { virtual void f() {} }; // polymorphic

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_polymorphic<A>::value << "\n"; // false
    std::cout << std::is_polymorphic<B>::value << "\n"; // true
}

3️⃣ std::is_abstract (C++14)
#include <iostream>
#include <type_traits>

struct A { virtual void f() = 0; }; // abstract
struct B { void f() {} };           // concrete

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_abstract<A>::value << "\n"; // true
    std::cout << std::is_abstract<B>::value << "\n"; // false
}

4️⃣ std::is_final (C++14)
#include <iostream>
#include <type_traits>

struct A final {}; // final
struct B {};       // not final

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_final<A>::value << "\n"; // true
    std::cout << std::is_final<B>::value << "\n"; // false
}

5️⃣ std::is_member_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_pointer<decltype(&A::x)>::value << "\n"; // true
    std::cout << std::is_member_pointer<decltype(&A::f)>::value << "\n"; // true
    std::cout << std::is_member_pointer<int>::value << "\n";            // false
}

6️⃣ std::is_function (C++14)
#include <iostream>
#include <type_traits>

void func() {}

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_function<decltype(func)>::value << "\n"; // true
    std::cout << std::is_function<int>::value << "\n";            // false
}

7️⃣ std::is_pointer (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int* p = nullptr;
    std::cout << std::boolalpha;
    std::cout << std::is_pointer<decltype(p)>::value << "\n"; // true
    std::cout << std::is_pointer<int>::value << "\n";         // false
}

8️⃣ std::is_member_function_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_function_pointer<decltype(&A::f)>::value << "\n"; // true
    std::cout << std::is_member_function_pointer<int>::value << "\n";            // false
}

9️⃣ std::is_member_object_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_object_pointer<decltype(&A::x)>::value << "\n"; // true
    std::cout << std::is_member_object_pointer<int>::value << "\n";            // false
}

🔟 std::is_same (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_same<int,int>::value << "\n";  // true
    std::cout << std::is_same<int,long>::value << "\n"; // false
}




C++14 Batch-5 (Traits 41–50)
1️⃣ std::is_const (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_const<const int>::value << "\n"; // true
    std::cout << std::is_const<int>::value << "\n";       // false
}

2️⃣ std::is_volatile (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_volatile<volatile int>::value << "\n"; // true
    std::cout << std::is_volatile<int>::value << "\n";          // false
}

3️⃣ std::is_cv (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_const<const int>::value || std::is_volatile<volatile int>::value << "\n"; // true
    std::cout << std::is_const<int>::value || std::is_volatile<int>::value << "\n";               // false
}

4️⃣ std::is_arithmetic (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic<int>::value << "\n";       // true
    std::cout << std::is_arithmetic<double>::value << "\n";    // true
    std::cout << std::is_arithmetic<std::string>::value << "\n"; // false
}

5️⃣ std::is_fundamental (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_fundamental<int>::value << "\n";      // true
    std::cout << std::is_fundamental<double>::value << "\n";   // true
    std::cout << std::is_fundamental<std::string>::value << "\n"; // false
}

6️⃣ std::is_scalar (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_scalar<int>::value << "\n";       // true
    std::cout << std::is_scalar<double>::value << "\n";    // true
    std::cout << std::is_scalar<std::string>::value << "\n"; // false
}

7️⃣ std::is_object (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_object<int>::value << "\n";          // true
    std::cout << std::is_object<double>::value << "\n";       // true
    std::cout << std::is_object<void>::value << "\n";         // false
}

8️⃣ std::is_compound (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_compound<int*>::value << "\n";    // true (pointer)
    std::cout << std::is_compound<int>::value << "\n";     // false
}

9️⃣ std::is_reference (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_reference<int&>::value << "\n";  // true
    std::cout << std::is_reference<int>::value << "\n";   // false
}

🔟 std::is_member_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_pointer<decltype(&A::x)>::value << "\n"; // true
    std::cout << std::is_member_pointer<decltype(&A::f)>::value << "\n"; // true
    std::cout << std::is_member_pointer<int>::value << "\n";            // false
}





C++14 Batch-6 (Traits 51–60)
1️⃣ std::is_constructible (C++14)
#include <iostream>
#include <type_traits>

struct A { A(int) {} };
struct B { B() = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_constructible<A,int>::value << "\n"; // true
    std::cout << std::is_constructible<B>::value << "\n";     // false
}

2️⃣ std::is_trivial (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; };        // trivial
struct B { B() {} int y; }; // non-trivial

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivial<A>::value << "\n"; // true
    std::cout << std::is_trivial<B>::value << "\n"; // false
}

3️⃣ std::is_standard_layout (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; double y; };   // standard layout
struct B { virtual void f() {}; }; // not standard layout

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_standard_layout<A>::value << "\n"; // true
    std::cout << std::is_standard_layout<B>::value << "\n"; // false
}

4️⃣ std::is_pod (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; double y; }; // POD
struct B { B() {} int y; };    // not POD

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pod<A>::value << "\n"; // true
    std::cout << std::is_pod<B>::value << "\n"; // false
}

5️⃣ std::is_empty (C++14)
#include <iostream>
#include <type_traits>

struct A {};        // empty
struct B { int x; }; // not empty

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_empty<A>::value << "\n"; // true
    std::cout << std::is_empty<B>::value << "\n"; // false
}

6️⃣ std::is_polymorphic (C++14)
#include <iostream>
#include <type_traits>

struct A {};             // not polymorphic
struct B { virtual void f() {} }; // polymorphic

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_polymorphic<A>::value << "\n"; // false
    std::cout << std::is_polymorphic<B>::value << "\n"; // true
}

7️⃣ std::is_abstract (C++14)
#include <iostream>
#include <type_traits>

struct A { virtual void f() = 0; }; // abstract
struct B { void f() {} };           // concrete

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_abstract<A>::value << "\n"; // true
    std::cout << std::is_abstract<B>::value << "\n"; // false
}

8️⃣ std::is_final (C++14)
#include <iostream>
#include <type_traits>

struct A final {}; // final
struct B {};       // not final

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_final<A>::value << "\n"; // true
    std::cout << std::is_final<B>::value << "\n"; // false
}

9️⃣ std::is_member_pointer (C++14)
#include <iostream>
#include <type_traits>

struct A { int x; void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_pointer<decltype(&A::x)>::value << "\n"; // true
    std::cout << std::is_member_pointer<decltype(&A::f)>::value << "\n"; // true
    std::cout << std::is_member_pointer<int>::value << "\n";            // false
}

🔟 std::is_convertible (C++14)
#include <iostream>
#include <type_traits>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_convertible<int,double>::value << "\n";      // true
    std::cout << std::is_convertible<std::string,int>::value << "\n"; // false
}




C++14 Batch-7 (Traits 61–70)
1️⃣ std::is_void (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_void<void>::value << "\n";  // true
    std::cout << std::is_void<int>::value << "\n";   // false
}

2️⃣ std::is_null_pointer (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::nullptr_t n = nullptr;
    std::cout << std::boolalpha;
    std::cout << std::is_null_pointer<decltype(n)>::value << "\n"; // true
    std::cout << std::is_null_pointer<int>::value << "\n";         // false
}

3️⃣ std::is_fundamental (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_fundamental<int>::value << "\n";       // true
    std::cout << std::is_fundamental<double>::value << "\n";    // true
    std::cout << std::is_fundamental<std::string>::value << "\n"; // false
}

4️⃣ std::is_arithmetic (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic<int>::value << "\n";       // true
    std::cout << std::is_arithmetic<double>::value << "\n";    // true
    std::cout << std::is_arithmetic<std::string>::value << "\n"; // false
}

5️⃣ std::is_scalar (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_scalar<int>::value << "\n";        // true
    std::cout << std::is_scalar<double>::value << "\n";     // true
    std::cout << std::is_scalar<std::string>::value << "\n"; // false
}

6️⃣ std::is_object (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_object<int>::value << "\n";     // true
    std::cout << std::is_object<double>::value << "\n";  // true
    std::cout << std::is_object<void>::value << "\n";    // false
}

7️⃣ std::is_compound (C++14)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_compound<int*>::value << "\n";  // true
    std::cout << std::is_compound<int>::value << "\n";   // false
}

8️⃣ std::is_reference (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_reference<int&>::value << "\n"; // true
    std::cout << std::is_reference<int>::value << "\n";  // false
}

9️⃣ std::is_lvalue_reference (C++14)
#include <iostream>
#include <type_traits>

int x = 0;
std::cout << std::boolalpha;
int main() {
    std::cout << std::is_lvalue_reference<decltype(x)>::value << "\n"; // true
    std::cout << std::is_lvalue_reference<int>::value << "\n";         // false
}

🔟 std::is_rvalue_reference (C++14)
#include <iostream>
#include <type_traits>

int main() {
    int&& r = 5;
    std::cout << std::boolalpha;
    std::cout << std::is_rvalue_reference<decltype(r)>::value << "\n"; // true
    std::cout << std::is_rvalue_reference<int>::value << "\n";         // false
}



/* ------------------------------------------------------------------------------------------------------------------- */

C++17 Batch-1 (Traits 1–10)
1️⃣ std::is_integral_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_integral_v<int> << "\n";       // true
    std::cout << std::is_integral_v<double> << "\n";    // false
}


Explanation: _v is shorthand for .value.

2️⃣ std::is_floating_point_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_floating_point_v<float> << "\n";  // true
    std::cout << std::is_floating_point_v<int> << "\n";    // false
}

3️⃣ std::is_arithmetic_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic_v<int> << "\n";        // true
    std::cout << std::is_arithmetic_v<double> << "\n";     // true
    std::cout << std::is_arithmetic_v<std::string> << "\n";// false
}

4️⃣ std::is_pointer_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int* p = nullptr;
    std::cout << std::boolalpha;
    std::cout << std::is_pointer_v<decltype(p)> << "\n"; // true
    std::cout << std::is_pointer_v<int> << "\n";         // false
}

5️⃣ std::is_array_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_array_v<int[5]> << "\n"; // true
    std::cout << std::is_array_v<int> << "\n";    // false
}

6️⃣ std::is_class_v (C++17)
#include <iostream>
#include <type_traits>

struct MyClass {};

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_class_v<MyClass> << "\n"; // true
    std::cout << std::is_class_v<int> << "\n";     // false
}

7️⃣ std::is_enum_v (C++17)
#include <iostream>
#include <type_traits>

enum Color { Red, Blue };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_enum_v<Color> << "\n"; // true
    std::cout << std::is_enum_v<int> << "\n";   // false
}

8️⃣ std::is_same_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_same_v<int,int> << "\n";  // true
    std::cout << std::is_same_v<int,long> << "\n"; // false
}

9️⃣ std::is_base_of_v (C++17)
#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};
struct Other {};

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_base_of_v<Base, Derived> << "\n"; // true
    std::cout << std::is_base_of_v<Base, Other> << "\n";   // false
}

🔟 std::is_convertible_v (C++17)
#include <iostream>
#include <type_traits>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_convertible_v<int,double> << "\n";      // true
    std::cout << std::is_convertible_v<std::string,int> << "\n"; // false
}


C++17 Batch-2 (Traits 11–20)
1️⃣ std::is_lvalue_reference_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_lvalue_reference_v<int&> << "\n"; // true
    std::cout << std::is_lvalue_reference_v<int> << "\n";  // false
}

2️⃣ std::is_rvalue_reference_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int&& r = 5;
    std::cout << std::boolalpha;
    std::cout << std::is_rvalue_reference_v<decltype(r)> << "\n"; // true
    std::cout << std::is_rvalue_reference_v<int> << "\n";         // false
}

3️⃣ std::is_member_function_pointer_v (C++17)
#include <iostream>
#include <type_traits>

struct A { void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_function_pointer_v<decltype(&A::f)> << "\n"; // true
    std::cout << std::is_member_function_pointer_v<int> << "\n";            // false
}

4️⃣ std::is_member_object_pointer_v (C++17)
#include <iostream>
#include <type_traits>

struct A { int x; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_object_pointer_v<decltype(&A::x)> << "\n"; // true
    std::cout << std::is_member_object_pointer_v<int> << "\n";            // false
}

5️⃣ std::is_void_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_void_v<void> << "\n";  // true
    std::cout << std::is_void_v<int> << "\n";   // false
}

6️⃣ std::is_null_pointer_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::nullptr_t n = nullptr;
    std::cout << std::boolalpha;
    std::cout << std::is_null_pointer_v<decltype(n)> << "\n"; // true
    std::cout << std::is_null_pointer_v<int> << "\n";         // false
}

7️⃣ std::void_t (C++17) Example
#include <iostream>
#include <type_traits>

// Detection idiom using void_t
template<typename, typename = std::void_t<>>
struct has_type_member : std::false_type {};

template<typename T>
struct has_type_member<T, std::void_t<typename T::type>> : std::true_type {};

struct A { using type = int; };
struct B {};

int main() {
    std::cout << std::boolalpha;
    std::cout << has_type_member<A>::value << "\n"; // true
    std::cout << has_type_member<B>::value << "\n"; // false
}


Explanation: void_t simplifies SFINAE-based detection of types or members.

8️⃣ std::is_const_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_const_v<const int> << "\n"; // true
    std::cout << std::is_const_v<int> << "\n";       // false
}

9️⃣ std::is_volatile_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_volatile_v<volatile int> << "\n"; // true
    std::cout << std::is_volatile_v<int> << "\n";          // false
}

🔟 std::is_reference_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_reference_v<int&> << "\n";  // true
    std::cout << std::is_reference_v<int&&> << "\n"; // true
    std::cout << std::is_reference_v<int> << "\n";   // false
}



C++17 Batch-3 (Traits 21–30)
1️⃣ std::is_trivial_v (C++17)
#include <iostream>
#include <type_traits>

struct A { int x; };        // trivial
struct B { B() {} int y; }; // non-trivial

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivial_v<A> << "\n"; // true
    std::cout << std::is_trivial_v<B> << "\n"; // false
}

2️⃣ std::is_trivially_copyable_v (C++17)
#include <iostream>
#include <type_traits>

struct A { int x; };          // trivially copyable
struct B { B() {} int y; };   // non-trivially copyable

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_copyable_v<A> << "\n"; // true
    std::cout << std::is_trivially_copyable_v<B> << "\n"; // false
}

3️⃣ std::is_trivially_destructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};          // trivial destructor
struct B { ~B() {} }; // non-trivial destructor

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_destructible_v<A> << "\n"; // true
    std::cout << std::is_trivially_destructible_v<B> << "\n"; // false
}

4️⃣ std::is_standard_layout_v (C++17)
#include <iostream>
#include <type_traits>

struct A { int x; double y; };   // standard layout
struct B { virtual void f() {}; }; // not standard layout

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_standard_layout_v<A> << "\n"; // true
    std::cout << std::is_standard_layout_v<B> << "\n"; // false
}

5️⃣ std::is_pod_v (C++17)
#include <iostream>
#include <type_traits>

struct A { int x; double y; }; // POD
struct B { B() {} int y; };    // not POD

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pod_v<A> << "\n"; // true
    std::cout << std::is_pod_v<B> << "\n"; // false
}

6️⃣ std::is_empty_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};        // empty
struct B { int x; }; // not empty

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_empty_v<A> << "\n"; // true
    std::cout << std::is_empty_v<B> << "\n"; // false
}

7️⃣ std::is_polymorphic_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};             // not polymorphic
struct B { virtual void f() {} }; // polymorphic

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_polymorphic_v<A> << "\n"; // false
    std::cout << std::is_polymorphic_v<B> << "\n"; // true
}

8️⃣ std::is_abstract_v (C++17)
#include <iostream>
#include <type_traits>

struct A { virtual void f() = 0; }; // abstract
struct B { void f() {} };           // concrete

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_abstract_v<A> << "\n"; // true
    std::cout << std::is_abstract_v<B> << "\n"; // false
}

9️⃣ std::is_final_v (C++17)
#include <iostream>
#include <type_traits>

struct A final {}; // final
struct B {};       // not final

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_final_v<A> << "\n"; // true
    std::cout << std::is_final_v<B> << "\n"; // false
}

🔟 std::enable_if_t Example (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_integral_v<T>, void> print(T val) {
    std::cout << "Integral: " << val << "\n";
}

int main() {
    print(10);   // works (int is integral)
    // print(3.14); // error (double is not integral)
}


Explanation: enable_if_t simplifies SFINAE for return type constraints.


C++17 Batch-4 (Traits 31–40)
1️⃣ std::is_constructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A { A(int) {} };
struct B { B() = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_constructible_v<A,int> << "\n"; // true
    std::cout << std::is_constructible_v<B> << "\n";     // false
}

2️⃣ std::is_default_constructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A { A() {} };
struct B { B(int) {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_default_constructible_v<A> << "\n"; // true
    std::cout << std::is_default_constructible_v<B> << "\n"; // false
}

3️⃣ std::is_copy_constructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B(const B&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_copy_constructible_v<A> << "\n"; // true
    std::cout << std::is_copy_constructible_v<B> << "\n"; // false
}

4️⃣ std::is_move_constructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B(B&&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_move_constructible_v<A> << "\n"; // true
    std::cout << std::is_move_constructible_v<B> << "\n"; // false
}

5️⃣ std::is_assignable_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B& operator=(int) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_assignable_v<A&, A> << "\n"; // true
    std::cout << std::is_assignable_v<B&, int> << "\n"; // false
}

6️⃣ std::is_copy_assignable_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B& operator=(const B&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_copy_assignable_v<A> << "\n"; // true
    std::cout << std::is_copy_assignable_v<B> << "\n"; // false
}

7️⃣ std::is_move_assignable_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};
struct B { B& operator=(B&&) = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_move_assignable_v<A> << "\n"; // true
    std::cout << std::is_move_assignable_v<B> << "\n"; // false
}

8️⃣ std::is_destructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};
struct B { ~B() = delete; };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_destructible_v<A> << "\n"; // true
    std::cout << std::is_destructible_v<B> << "\n"; // false
}

9️⃣ std::is_trivially_destructible_v (C++17)
#include <iostream>
#include <type_traits>

struct A {};          // trivial destructor
struct B { ~B() {} }; // non-trivial destructor

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_destructible_v<A> << "\n"; // true
    std::cout << std::is_trivially_destructible_v<B> << "\n"; // false
}

🔟 std::enable_if_t Example (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void> print(T val) {
    std::cout << "Floating point: " << val << "\n";
}

int main() {
    print(3.14);   // works (double is floating point)
    // print(10);  // error (int is not floating point)
}


Explanation: enable_if_t is modern shorthand for typename std::enable_if<...>::type.





C++17 Batch-5 (Traits 41–50)
1️⃣ std::is_base_of_v (C++17)
#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};
struct Other {};

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_base_of_v<Base, Derived> << "\n"; // true
    std::cout << std::is_base_of_v<Base, Other> << "\n";   // false
}

2️⃣ std::is_same_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_same_v<int,int> << "\n";  // true
    std::cout << std::is_same_v<int,long> << "\n"; // false
}

3️⃣ std::is_convertible_v (C++17)
#include <iostream>
#include <type_traits>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_convertible_v<int,double> << "\n";      // true
    std::cout << std::is_convertible_v<std::string,int> << "\n"; // false
}

4️⃣ std::is_arithmetic_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic_v<int> << "\n";        // true
    std::cout << std::is_arithmetic_v<double> << "\n";     // true
    std::cout << std::is_arithmetic_v<std::string> << "\n";// false
}

5️⃣ std::is_fundamental_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_fundamental_v<int> << "\n";       // true
    std::cout << std::is_fundamental_v<double> << "\n";    // true
    std::cout << std::is_fundamental_v<std::string> << "\n"; // false
}

6️⃣ std::is_scalar_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_scalar_v<int> << "\n";        // true
    std::cout << std::is_scalar_v<double> << "\n";     // true
    std::cout << std::is_scalar_v<std::string> << "\n"; // false
}

7️⃣ std::is_object_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_object_v<int> << "\n";       // true
    std::cout << std::is_object_v<double> << "\n";    // true
    std::cout << std::is_object_v<void> << "\n";      // false
}

8️⃣ std::is_compound_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_compound_v<int*> << "\n"; // true
    std::cout << std::is_compound_v<int> << "\n";  // false
}

9️⃣ std::void_t Example (C++17 SFINAE)
#include <iostream>
#include <type_traits>

// Detection idiom
template<typename, typename = std::void_t<>>
struct has_value_type : std::false_type {};

template<typename T>
struct has_value_type<T, std::void_t<typename T::value_type>> : std::true_type {};

struct A { using value_type = int; };
struct B {};

int main() {
    std::cout << std::boolalpha;
    std::cout << has_value_type<A>::value << "\n"; // true
    std::cout << has_value_type<B>::value << "\n"; // false
}

🔟 std::enable_if_t Example (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, void> print(T val) {
    std::cout << "Arithmetic: " << val << "\n";
}

int main() {
    print(10);   // works (int)
    print(3.14); // works (double)
    // print("hi"); // error (const char* not arithmetic)
}


✅ C++17 Batch-5 Completed (Traits 41–50)



C++17 Batch-6 (Traits 51–60)
1️⃣ std::is_pointer_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int* p = nullptr;
    std::cout << std::boolalpha;
    std::cout << std::is_pointer_v<decltype(p)> << "\n"; // true
    std::cout << std::is_pointer_v<int> << "\n";         // false
}

2️⃣ std::is_array_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_array_v<int[5]> << "\n"; // true
    std::cout << std::is_array_v<int> << "\n";    // false
}

3️⃣ std::is_reference_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_reference_v<int&> << "\n";  // true
    std::cout << std::is_reference_v<int&&> << "\n"; // true
    std::cout << std::is_reference_v<int> << "\n";   // false
}

4️⃣ std::is_lvalue_reference_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int x = 0;
    std::cout << std::boolalpha;
    std::cout << std::is_lvalue_reference_v<int&> << "\n"; // true
    std::cout << std::is_lvalue_reference_v<int&&> << "\n"; // false
}

5️⃣ std::is_rvalue_reference_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    int&& r = 5;
    std::cout << std::boolalpha;
    std::cout << std::is_rvalue_reference_v<decltype(r)> << "\n"; // true
    std::cout << std::is_rvalue_reference_v<int&> << "\n";        // false
}

6️⃣ std::is_member_pointer_v (C++17)
#include <iostream>
#include <type_traits>

struct A { int x; void f() {} };

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_member_pointer_v<decltype(&A::x)> << "\n"; // true
    std::cout << std::is_member_pointer_v<decltype(&A::f)> << "\n"; // true
    std::cout << std::is_member_pointer_v<int> << "\n";            // false
}

7️⃣ std::is_const_v (C++17)
#include <iostream>
#include <type_traits>

std::cout << std::boolalpha;

int main() {
    std::cout << std::is_const_v<const int> << "\n"; // true
    std::cout << std::is_const_v<int> << "\n";       // false
}

8️⃣ std::is_volatile_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_volatile_v<volatile int> << "\n"; // true
    std::cout << std::is_volatile_v<int> << "\n";          // false
}

9️⃣ std::is_cv_v (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
constexpr bool is_cv_v = std::is_const_v<T> || std::is_volatile_v<T>;

int main() {
    std::cout << std::boolalpha;
    std::cout << is_cv_v<const int> << "\n";       // true
    std::cout << is_cv_v<volatile int> << "\n";    // true
    std::cout << is_cv_v<int> << "\n";             // false
}

🔟 std::enable_if_t with reference/pointer (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_pointer_v<T>, void> print(T val) {
    std::cout << "Pointer detected\n";
}

int main() {
    int x = 0;
    int* p = &x;
    print(p);   // works
    // print(x); // error, not a pointer
}

C++17 Batch-7 (Traits 61–70)
1️⃣ std::is_arithmetic_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_arithmetic_v<int> << "\n";        // true
    std::cout << std::is_arithmetic_v<double> << "\n";     // true
    std::cout << std::is_arithmetic_v<std::string> << "\n";// false
}

2️⃣ std::is_fundamental_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_fundamental_v<int> << "\n";       // true
    std::cout << std::is_fundamental_v<double> << "\n";    // true
    std::cout << std::is_fundamental_v<std::string> << "\n"; // false
}

3️⃣ std::is_scalar_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_scalar_v<int> << "\n";        // true
    std::cout << std::is_scalar_v<double> << "\n";     // true
    std::cout << std::is_scalar_v<std::string> << "\n";// false
}

4️⃣ std::is_object_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_object_v<int> << "\n";       // true
    std::cout << std::is_object_v<double> << "\n";    // true
    std::cout << std::is_object_v<void> << "\n";      // false
}

5️⃣ std::is_compound_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_compound_v<int*> << "\n"; // true
    std::cout << std::is_compound_v<int> << "\n";  // false
}

6️⃣ std::void_t Advanced Example (C++17)
#include <iostream>
#include <type_traits>

// Detect if T has member type "iterator"
template<typename, typename = std::void_t<>>
struct has_iterator : std::false_type {};

template<typename T>
struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << has_iterator<std::vector<int>>::value << "\n"; // true
    std::cout << has_iterator<int>::value << "\n";              // false
}

7️⃣ std::enable_if_t Combined Traits (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_integral_v<T> && !std::is_const_v<T>, void> print(T val) {
    std::cout << "Non-const integral: " << val << "\n";
}

int main() {
    int a = 10;
    const int b = 20;
    print(a);    // works
    // print(b); // error (const)
}

8️⃣ std::is_floating_point_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_floating_point_v<float> << "\n";  // true
    std::cout << std::is_floating_point_v<int> << "\n";    // false
}

9️⃣ std::is_signed_v / std::is_unsigned_v (C++17)
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_signed_v<int> << "\n";   // true
    std::cout << std::is_unsigned_v<unsigned int> << "\n"; // true
}

🔟 std::enable_if_t with Floating Point (C++17)
#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void> print(T val) {
    std::cout << "Floating point: " << val << "\n";
}

int main() {
    print(3.14);   // works
    // print(10);  // error, int is not floating point
}



/* -------------------------------------------------------------------------------------------------- */

C++20 Batch-1 (Traits & Concepts 1–10)
1️⃣ std::integral Concept (C++20)
#include <iostream>
#include <concepts>

template<std::integral T>
void print(T val) {
    std::cout << "Integral: " << val << "\n";
}

int main() {
    print(10);     // works (int is integral)
    // print(3.14); // error (double not integral)
}


Explanation: Concept std::integral replaces enable_if for integral types.

2️⃣ std::floating_point Concept (C++20)
#include <iostream>
#include <concepts>

template<std::floating_point T>
void print(T val) {
    std::cout << "Floating point: " << val << "\n";
}

int main() {
    print(3.14);   // works (double)
    // print(10);  // error (int)
}

3️⃣ std::same_as Concept (C++20)
#include <iostream>
#include <concepts>

template<typename T, typename U>
requires std::same_as<T,U>
void check_same(T, U) {
    std::cout << "Same types\n";
}

int main() {
    check_same(10, 20);       // works (int,int)
    // check_same(10, 3.14);  // error (int,double)
}

4️⃣ std::derived_from Concept (C++20)
#include <iostream>
#include <concepts>

struct Base {};
struct Derived : Base {};
struct Other {};

template<typename T>
requires std::derived_from<T, Base>
void check_derived(T) {
    std::cout << "Derived from Base\n";
}

int main() {
    check_derived(Derived{}); // works
    // check_derived(Other{}); // error
}

5️⃣ std::is_constant_evaluated (C++20)
#include <iostream>
#include <type_traits>

constexpr int foo() {
    if (std::is_constant_evaluated()) {
        return 1;
    } else {
        return 2;
    }
}

int main() {
    constexpr int a = foo(); // evaluated at compile-time -> 1
    int b = foo();           // evaluated at run-time -> 2
    std::cout << a << " " << b << "\n";
}

6️⃣ requires clause (C++20)
#include <iostream>

template<typename T>
requires std::integral<T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(10, 20) << "\n"; // works
    // std::cout << add(3.14, 2.71);  // error, not integral
}

7️⃣ if consteval (C++20)
#include <iostream>

constexpr int foo(bool compile_time) {
    if consteval {
        return 1; // evaluated at compile-time
    } else {
        return 2; // evaluated at run-time
    }
}

int main() {
    constexpr int a = foo(true); // compile-time -> 1
    int b = foo(false);          // run-time -> 2
    std::cout << a << " " << b << "\n";
}

8️⃣ Concept + enable_if replacement (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::floating_point<T>
void print(T val) {
    std::cout << "Floating point value: " << val << "\n";
}

int main() {
    print(3.14);   // works
    // print(10);  // error
}

9️⃣ std::integral + auto (C++20)
#include <iostream>
#include <concepts>

void print_integral(std::integral auto val) {
    std::cout << "Integral: " << val << "\n";
}

int main() {
    print_integral(10);     // works
    // print_integral(3.14); // error
}

🔟 std::floating_point + auto (C++20)
#include <iostream>
#include <concepts>

void print_fp(std::floating_point auto val) {
    std::cout << "Floating point: " << val << "\n";
}

int main() {
    print_fp(3.14);   // works
    // print_fp(10);   // error
}


C++20 Batch-2 (Traits & Concepts 11–20)
1️⃣ std::same_as Concept (C++20)
#include <iostream>
#include <concepts>

template<typename T, typename U>
requires std::same_as<T,U>
void check_same(T, U) {
    std::cout << "Same types\n";
}

int main() {
    check_same(10, 20);       // works (int,int)
    // check_same(10, 3.14);  // error (int,double)
}

2️⃣ std::derived_from Concept (C++20)
#include <iostream>
#include <concepts>

struct Base {};
struct Derived : Base {};
struct Other {};

template<typename T>
requires std::derived_from<T, Base>
void check_derived(T) {
    std::cout << "Derived from Base\n";
}

int main() {
    check_derived(Derived{}); // works
    // check_derived(Other{}); // error
}

3️⃣ std::convertible_to Concept (C++20)
#include <iostream>
#include <concepts>

template<typename T, typename U>
requires std::convertible_to<T,U>
void convert(T val) {
    U u = val;
    std::cout << u << "\n";
}

int main() {
    convert<int,double>(10);   // works
    // convert<double,int>(3.14); // also works
    // convert<std::string,int>("10"); // error
}

4️⃣ requires clause with multiple constraints (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::integral<T> && std::signed_integral<T>
void print(T val) {
    std::cout << "Signed integral: " << val << "\n";
}

int main() {
    print(10);        // works
    // print(unsigned(10)); // error
}

5️⃣ if consteval Example (C++20)
#include <iostream>

constexpr int foo(bool compile_time) {
    if consteval {
        return 1; // compile-time
    } else {
        return 2; // run-time
    }
}

int main() {
    constexpr int a = foo(true); // compile-time
    int b = foo(false);          // run-time
    std::cout << a << " " << b << "\n"; // 1 2
}

6️⃣ consteval Function Example (C++20)
#include <iostream>

consteval int square(int x) {
    return x * x;
}

int main() {
    constexpr int a = square(5); // compile-time
    std::cout << a << "\n";      // 25
    // int b = square(10);       // also allowed, must be compile-time
}

7️⃣ Concepts with auto parameters (C++20)
#include <iostream>
#include <concepts>

void add(std::integral auto a, std::integral auto b) {
    std::cout << "Sum: " << (a + b) << "\n";
}

int main() {
    add(10, 20);   // works
    // add(3.14, 2.71); // error
}

8️⃣ Multiple Concepts in requires clause (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::integral<T> && std::signed_integral<T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    std::cout << multiply(5, 6) << "\n"; // works
    // std::cout << multiply(unsigned(5), 6); // error
}

9️⃣ Concept + if consteval (C++20)
#include <iostream>
#include <concepts>

constexpr int foo(std::integral auto val) {
    if consteval {
        return val * 2; // compile-time
    } else {
        return val * 3; // run-time
    }
}

int main() {
    constexpr int a = foo(5); // 10
    int b = foo(6);           // 18
    std::cout << a << " " << b << "\n";
}

🔟 Concept + convertible_to (C++20)
#include <iostream>
#include <concepts>

template<std::convertible_to<int> T>
void print(T val) {
    std::cout << "Convertible to int: " << val << "\n";
}

int main() {
    print(10);   // works
    print('A');  // works (char -> int)
    // print(3.14); // error (double to int conversion not allowed in this context)
}



C++20 Batch-3 (Traits & Concepts 21–30)
1️⃣ Combined Concept: Integral + Signed (C++20)
#include <iostream>
#include <concepts>

template<std::integral T>
requires std::signed_integral<T>
void print_signed(T val) {
    std::cout << "Signed integral: " << val << "\n";
}

int main() {
    print_signed(10);       // works
    // print_signed(unsigned(10)); // error
}

2️⃣ Combined Concept: Floating Point + Const (C++20)
#include <iostream>
#include <concepts>

template<std::floating_point T>
void print_const(const T val) {
    std::cout << "Const floating point: " << val << "\n";
}

int main() {
    print_const(3.14);   // works
    // print_const("3.14"); // error
}

3️⃣ Concepts with multiple type parameters (C++20)
#include <iostream>
#include <concepts>

template<std::integral T, std::integral U>
void add(T a, U b) {
    std::cout << "Sum: " << (a + b) << "\n";
}

int main() {
    add(10, 20);       // works
    // add(3.14, 10);  // error, 3.14 not integral
}

4️⃣ Using requires clause for type relationships (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::derived_from<T, struct Base>
void check_derived(T) {
    std::cout << "Derived from Base\n";
}

struct Base {};
struct Derived : Base {};
struct Other {};

int main() {
    check_derived(Derived{}); // works
    // check_derived(Other{}); // error
}

5️⃣ consteval function (C++20)
#include <iostream>

consteval int multiply_by_two(int x) {
    return x * 2;
}

int main() {
    constexpr int a = multiply_by_two(5); // compile-time
    std::cout << a << "\n";              // 10
}

6️⃣ if consteval inside function (C++20)
#include <iostream>

constexpr int process(int x) {
    if consteval {
        return x * 2; // compile-time
    } else {
        return x * 3; // run-time
    }
}

int main() {
    constexpr int a = process(5); // 10
    int b = process(6);           // 18
    std::cout << a << " " << b << "\n";
}

7️⃣ Concept as SFINAE replacement (C++20)
#include <iostream>
#include <concepts>

template<std::integral T>
void print_integral(T val) {
    std::cout << "Integral: " << val << "\n";
}

int main() {
    print_integral(10);     // works
    // print_integral(3.14); // error
}

8️⃣ Concept + auto parameter (C++20)
#include <iostream>
#include <concepts>

void print_fp(std::floating_point auto val) {
    std::cout << "Floating point: " << val << "\n";
}

int main() {
    print_fp(3.14);   // works
    // print_fp(10);   // error
}

9️⃣ Concept with convertible_to (C++20)
#include <iostream>
#include <concepts>

template<std::convertible_to<int> T>
void print_int_convertible(T val) {
    std::cout << "Convertible to int: " << val << "\n";
}

int main() {
    print_int_convertible(10);  // works
    print_int_convertible('A'); // works
    // print_int_convertible(3.14); // error
}

🔟 Combined requires clause for multiple constraints (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::integral<T> && std::signed_integral<T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    std::cout << multiply(5, 6) << "\n"; // 30
    // multiply(unsigned(5), 6); // error
}




C++20 Batch-4 (Traits & Concepts 31–40)
1️⃣ consteval Function Example (C++20)
#include <iostream>

consteval int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr int f5 = factorial(5); // compile-time
    std::cout << f5 << "\n";         // 120
}


Explanation: consteval ensures function is always evaluated at compile-time.

2️⃣ constinit Variable Example (C++20)
#include <iostream>

constinit int global_counter = 0; // guaranteed initialization at compile-time

int main() {
    global_counter += 5;
    std::cout << global_counter << "\n"; // 5
}


Explanation: constinit ensures global or static variable is initialized at compile-time but can be modified at runtime.

3️⃣ requires Expression (C++20)
#include <iostream>

template<typename T>
concept HasSize = requires(T a) {
    { a.size() } -> std::convertible_to<std::size_t>;
};

#include <vector>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasSize<std::vector<int>> << "\n"; // true
    std::cout << HasSize<int> << "\n";              // false
}


Explanation: Checks if type T has a size() member returning something convertible to std::size_t.

4️⃣ SFINAE Replacement using Concepts (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::integral<T> && std::signed_integral<T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(10, 20) << "\n"; // works
    // add(unsigned(10), 20); // error
}


Explanation: requires replaces traditional enable_if usage.

5️⃣ Combined Type Trait Check (C++20)
#include <iostream>
#include <concepts>

template<typename T>
concept ArithmeticType = std::integral<T> || std::floating_point<T>;

template<ArithmeticType T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    std::cout << multiply(5, 6) << "\n";    // integral
    std::cout << multiply(2.5, 4.0) << "\n";// floating point
    // multiply("hi", "there"); // error
}


Explanation: Combines multiple concepts for flexible compile-time constraints.

6️⃣ Detection Idiom using requires (C++20)
#include <iostream>

template<typename T>
concept HasBegin = requires(T a) {
    { a.begin() };
};

#include <vector>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasBegin<std::vector<int>> << "\n"; // true
    std::cout << HasBegin<int> << "\n";              // false
}


Explanation: Detects if a type supports .begin() method using requires.

7️⃣ consteval + requires (C++20)
#include <iostream>
#include <concepts>

consteval int twice(std::integral auto val) {
    return val * 2;
}

int main() {
    constexpr int a = twice(5); // 10, compile-time
    std::cout << a << "\n";
}

8️⃣ consteval + floating_point (C++20)
#include <iostream>
#include <concepts>

consteval double triple(std::floating_point auto val) {
    return val * 3;
}

int main() {
    constexpr double a = triple(3.0); // compile-time
    std::cout << a << "\n";           // 9.0
}

9️⃣ Concept + requires with member functions (C++20)
#include <iostream>

template<typename T>
concept HasPushBack = requires(T a, typename T::value_type v) {
    { a.push_back(v) };
};

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasPushBack<std::vector<int>> << "\n"; // true
    std::cout << HasPushBack<std::list<int>> << "\n";   // true
    std::cout << HasPushBack<int> << "\n";              // false
}

🔟 Concept + consteval + SFINAE replacement (C++20)
#include <iostream>
#include <concepts>

consteval int sum(std::integral auto a, std::integral auto b) {
    return a + b;
}

int main() {
    constexpr int result = sum(5, 10); // compile-time
    std::cout << result << "\n";       // 15
}




C++20 Batch-5 (Traits & Concepts 41–50)
1️⃣ same_as + convertible_to (C++20)
#include <iostream>
#include <concepts>

template<typename T, typename U>
requires std::same_as<T,U> && std::convertible_to<T,U>
void check(T val1, U val2) {
    std::cout << "Same and convertible\n";
}

int main() {
    check(10, 20);       // works
    // check(10, 3.14);  // error (int vs double)
}

2️⃣ derived_from + same_as (C++20)
#include <iostream>
#include <concepts>

struct Base {};
struct Derived : Base {};

template<typename T>
requires std::derived_from<T, Base> && std::same_as<T, Derived>
void check(T) {
    std::cout << "Derived from Base and exact Derived\n";
}

int main() {
    check(Derived{}); // works
    // check(Base{}); // error
}

3️⃣ detect member type using requires (C++20)
#include <iostream>

template<typename T>
concept HasValueType = requires { typename T::value_type; };

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasValueType<std::vector<int>> << "\n"; // true
    std::cout << HasValueType<int> << "\n";              // false
}

4️⃣ detect member function using requires (C++20)
#include <iostream>

template<typename T>
concept HasSizeMethod = requires(T a) {
    { a.size() } -> std::convertible_to<std::size_t>;
};

#include <vector>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasSizeMethod<std::vector<int>> << "\n"; // true
    std::cout << HasSizeMethod<int> << "\n";              // false
}

5️⃣ constexpr algorithm with concepts (C++20)
#include <iostream>
#include <concepts>
#include <array>

template<std::integral T, size_t N>
constexpr T sum(const std::array<T,N>& arr) {
    T result = 0;
    for (T v : arr) result += v;
    return result;
}

int main() {
    constexpr std::array<int,5> arr = {1,2,3,4,5};
    constexpr int s = sum(arr); // compile-time
    std::cout << s << "\n";     // 15
}

6️⃣ consteval function with concepts (C++20)
#include <iostream>
#include <concepts>

consteval int square(std::integral auto val) {
    return val * val;
}

int main() {
    constexpr int a = square(5); // 25
    std::cout << a << "\n";
}

7️⃣ requires expression for operator+ (C++20)
#include <iostream>

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << Addable<int> << "\n";     // true
    std::cout << Addable<std::string> << "\n"; // true
    std::cout << Addable<void*> << "\n";   // false
}

8️⃣ concepts with auto parameters (C++20)
#include <iostream>
#include <concepts>

void multiply(std::integral auto a, std::integral auto b) {
    std::cout << "Product: " << a * b << "\n";
}

int main() {
    multiply(5, 6);       // works
    // multiply(5.0, 6.0); // error
}

9️⃣ combined concepts using logical operators (C++20)
#include <iostream>
#include <concepts>

template<typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

template<Arithmetic T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(5,6) << "\n";       // integral
    std::cout << add(3.5,2.5) << "\n";   // floating point
    // add("hi","there"); // error
}

🔟 concept + detection idiom + requires (C++20)
#include <iostream>

template<typename T>
concept HasPushBack = requires(T a, typename T::value_type v) {
    { a.push_back(v) };
};

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasPushBack<std::vector<int>> << "\n"; // true
    std::cout << HasPushBack<std::list<int>> << "\n";   // true
    std::cout << HasPushBack<int> << "\n";              // false
}





C++20 Batch-6 (Traits & Concepts 51–60)
1️⃣ consteval function with integral constraint
#include <iostream>
#include <concepts>

consteval int triple(std::integral auto val) {
    return val * 3;
}

int main() {
    constexpr int a = triple(5); // 15
    std::cout << a << "\n";
    // triple(3.14); // error: double not integral
}

2️⃣ constinit variable with constraint
#include <iostream>
#include <concepts>

constinit int counter = 0; // compile-time init

int main() {
    counter += 10;
    std::cout << counter << "\n"; // 10
}

3️⃣ detect member pointer using requires (C++20)
#include <iostream>

struct A { int x; void f() {} };

template<typename T>
concept HasMemberPointer = requires(T a) {
    { &T::x };
};

int main() {
    std::cout << std::boolalpha;
    std::cout << HasMemberPointer<A> << "\n"; // true
    // std::cout << HasMemberPointer<int> << "\n"; // false
}

4️⃣ SFINAE replacement using concepts + requires (C++20)
#include <iostream>
#include <concepts>

template<typename T>
requires std::integral<T> && std::signed_integral<T>
T subtract(T a, T b) {
    return a - b;
}

int main() {
    std::cout << subtract(20, 5) << "\n"; // 15
    // subtract(unsigned(20), 5); // error
}

5️⃣ constexpr algorithm with constraints (C++20)
#include <iostream>
#include <concepts>
#include <array>

template<std::integral T, size_t N>
constexpr T sum(const std::array<T,N>& arr) {
    T result = 0;
    for (T v : arr) result += v;
    return result;
}

int main() {
    constexpr std::array<int,5> arr = {1,2,3,4,5};
    constexpr int s = sum(arr); // compile-time
    std::cout << s << "\n";     // 15
}

6️⃣ detect if type has push_back (C++20)
#include <iostream>

template<typename T>
concept HasPushBack = requires(T a, typename T::value_type v) {
    { a.push_back(v) };
};

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasPushBack<std::vector<int>> << "\n"; // true
    std::cout << HasPushBack<std::list<int>> << "\n";   // true
    std::cout << HasPushBack<int> << "\n";              // false
}

7️⃣ consteval function with floating point concept
#include <iostream>
#include <concepts>

consteval double half(std::floating_point auto val) {
    return val / 2.0;
}

int main() {
    constexpr double a = half(10.0); // 5.0
    std::cout << a << "\n";
    // half(10); // error: int not floating_point
}

8️⃣ requires expression to check operator+ (C++20)
#include <iostream>

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << Addable<int> << "\n";     // true
    std::cout << Addable<std::string> << "\n"; // true
    std::cout << Addable<void*> << "\n";   // false
}

9️⃣ combined concepts for arithmetic types (C++20)
#include <iostream>
#include <concepts>

template<typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

template<Arithmetic T>
T divide(T a, T b) {
    return a / b;
}

int main() {
    std::cout << divide(10, 2) << "\n";    // integral
    std::cout << divide(7.5, 2.5) << "\n"; // floating point
    // divide("hi","there"); // error
}

🔟 consteval + SFINAE replacement (C++20)
#include <iostream>
#include <concepts>

consteval int sum(std::integral auto a, std::integral auto b) {
    return a + b;
}

int main() {
    constexpr int result = sum(5, 10); // 15
    std::cout << result << "\n";
}





C++20 Batch-7 (Traits & Concepts 61–70)
1️⃣ Detect if type has a nested type alias (C++20)
#include <iostream>

template<typename T>
concept HasValueType = requires { typename T::value_type; };

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasValueType<std::vector<int>> << "\n"; // true
    std::cout << HasValueType<int> << "\n";              // false
}

2️⃣ Detect member pointer (C++20)
#include <iostream>

struct A { int x; void f() {} };

template<typename T>
concept HasMemberPointer = requires(T a) {
    { &T::x };
};

int main() {
    std::cout << std::boolalpha;
    std::cout << HasMemberPointer<A> << "\n"; // true
    // std::cout << HasMemberPointer<int> << "\n"; // false
}

3️⃣ Detect member function using requires (C++20)
#include <iostream>

template<typename T>
concept HasSizeMethod = requires(T a) {
    { a.size() } -> std::convertible_to<std::size_t>;
};

#include <vector>
#include <string>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasSizeMethod<std::vector<int>> << "\n"; // true
    std::cout << HasSizeMethod<std::string> << "\n";      // true
    std::cout << HasSizeMethod<int> << "\n";              // false
}

4️⃣ Constexpr algorithm with concept constraint (C++20)
#include <iostream>
#include <concepts>
#include <array>

template<std::integral T, size_t N>
constexpr T product(const std::array<T,N>& arr) {
    T result = 1;
    for (T v : arr) result *= v;
    return result;
}

int main() {
    constexpr std::array<int,4> arr = {1,2,3,4};
    constexpr int prod = product(arr);
    std::cout << prod << "\n"; // 24
}

5️⃣ consteval function with floating point (C++20)
#include <iostream>
#include <concepts>

consteval double cube(std::floating_point auto val) {
    return val * val * val;
}

int main() {
    constexpr double a = cube(2.0); // 8.0
    std::cout << a << "\n";
    // cube(10); // error: int not floating_point
}

6️⃣ constinit variable with constraint (C++20)
#include <iostream>
#include <concepts>

constinit int counter = 0; // guaranteed compile-time initialization

int main() {
    counter += 15;
    std::cout << counter << "\n"; // 15
}

7️⃣ Complex requires expression (C++20)
#include <iostream>

template<typename T>
concept AddableAndMultipliable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << AddableAndMultipliable<int> << "\n";       // true
    std::cout << AddableAndMultipliable<std::string> << "\n";// false, string can't multiply
}

8️⃣ Concept + detection idiom: push_back (C++20)
#include <iostream>

template<typename T>
concept HasPushBack = requires(T a, typename T::value_type v) {
    { a.push_back(v) };
};

#include <vector>
#include <list>

int main() {
    std::cout << std::boolalpha;
    std::cout << HasPushBack<std::vector<int>> << "\n"; // true
    std::cout << HasPushBack<std::list<int>> << "\n";   // true
    std::cout << HasPushBack<int> << "\n";              // false
}

9️⃣ Consteval function + integral concept (C++20)
#include <iostream>
#include <concepts>

consteval int doubleValue(std::integral auto val) {
    return val * 2;
}

int main() {
    constexpr int a = doubleValue(7); // 14
    std::cout << a << "\n";
}

🔟 Constexpr algorithm + combined concept (C++20)
#include <iostream>
#include <concepts>
#include <array>

template<typename T, size_t N>
requires std::integral<T> || std::floating_point<T>
constexpr T sumArray(const std::array<T,N>& arr) {
    T result = 0;
    for (T v : arr) result += v;
    return result;
}

int main() {
    constexpr std::array<int,3> arr1 = {1,2,3};
    constexpr std::array<double,3> arr2 = {1.5, 2.5, 3.0};
    std::cout << sumArray(arr1) << "\n"; // 6
    std::cout << sumArray(arr2) << "\n"; // 7.0
}



