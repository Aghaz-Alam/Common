✔️ What std::clamp Does

--> It takes a value and two bounds (low and high).
--> If the value is below the lower bound, it returns the lower bound. 
--> If it is above the upper bound, it returns the upper bound. 
--> Otherwise, it returns the value itself.

Function Signature
template< class T >
constexpr const T& clamp( const T& v, const T& lo, const T& hi );


Important Rules
1. lo must be ≤ hi.
2. v, lo, and hi must be comparable with < (i.e., support operator<).
3. If v equals a bound, that bound may be returned (reference semantics).

✔️ Simple Example
#include <algorithm>
#include <iostream>
int main() {
    int value = 15;
    int clamped = std::clamp(value, 0, 10);
    std::cout << clamped << "\n"; // 10
}
/*
10
*/




#include <iostream>
#include <algorithm>  // for std::clamp
// This represents the signature of std::clamp:
//
// template< class T >
// constexpr const T& clamp( const T& v, const T& lo, const T& hi );
//
// (We do NOT re-implement it because std::clamp already exists in <algorithm>)

int main() {
    int value = 15;

    // Clamp value between 0 and 10
    const int& result = std::clamp(value, 0, 10);

    std::cout << "Original value = " << value << "\n";
    std::cout << "Clamped result = " << result << "\n";

    return 0;
}
/*
Original value = 15
Clamped result = 10
*/


📘 Generic Example With Floating Point
double x = -1.5;
double y = std::clamp(x, 0.0, 1.0);  // y = 0.0

How It Works Internally
Equivalent to:

return (v < lo) ? lo : (hi < v) ? hi : v;

/* ------------------------------- */
#include <iostream>
#include <algorithm>  // for std::clamp

int main() {
    double x = -1.5;

    // Using std::clamp
    double y = std::clamp(x, 0.0, 1.0);

    std::cout << "Using std::clamp: y = " << y << "\n";

    // Equivalent logic using ternary operator
    double y_equiv = (x < 0.0) ? 0.0 : (1.0 < x) ? 1.0 : x;

    std::cout << "Using ternary operator: y_equiv = " << y_equiv << "\n";

    return 0;
}
/*
Using std::clamp: y = 0
Using ternary operator: y_equiv = 0
*/
/* ------------------------------- */

/* -------------- */
return (v < lo) ? lo : (hi < v) ? hi : v;
This is equivalent to:

If v is less than lo, return lo.

Else, if v is greater than hi, return hi.

Else, return v.
/* -------------- */



⭐ Using std::clamp with Custom Types
You can use it with user-defined types if they have operator<:

struct Point {
    int x;
    bool operator<(const Point& other) const { return x < other.x; }
};

Point p{5};
Point result = std::clamp(p, Point{0}, Point{3}); // → Point{3}


/* ------------------------ */
#include <iostream>
#include <algorithm>  // for std::clamp
struct Point {
    int x;

    // Define comparison operator so std::clamp can compare Points
    bool operator<(const Point& other) const {
        return x < other.x;
    }
};
int main() {
    Point p{5};
    // Clamp p between Point{0} and Point{3}
    Point result = std::clamp(p, Point{0}, Point{3});
    std::cout << "Original p.x = " << p.x << "\n";
    std::cout << "Clamped result.x = " << result.x << "\n";
    return 0;
}
/*
Output: C++17

Original p.x = 5
Clamped result.x = 3
*/
/* ------------------------- */

🔍 Common Use Cases
-> Keeping values within a physical range (e.g., joystick input)
-> Limiting colors or pixel values (0–255)
-> Input validation
-> Normalizing parameters