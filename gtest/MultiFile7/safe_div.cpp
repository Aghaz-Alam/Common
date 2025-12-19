//safe_div.cpp


#include "safe_div.hpp"
#include <cassert>

int divide(int a, int b) {
    assert(b != 0);
    return a / b;
}
