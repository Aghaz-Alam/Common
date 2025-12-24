#include <iostream>
#include "TupleStore.hpp"
#include "test_tuple.h"

int main() {
    // Run all unit tests
    run_tuplestore_tests();

    // Demo usage
    TupleStore<int, double, std::string> ts;
    ts.set<0>(100);
    ts.set<1>(9.81);
    ts.set<2>("TupleStore demo");

    std::cout << "Tuple values:\n";
    std::cout << "Index 0: " << ts.get<0>() << "\n";
    std::cout << "Index 1: " << ts.get<1>() << "\n";
    std::cout << "Index 2: " << ts.get<2>() << "\n";

    // Remove and clear
    ts.remove<1>();
    std::cout << "After remove index 1: " << ts.get<1>() << "\n";

    ts.clear();
    std::cout << "After clear:\n";
    std::cout << "Index 0: " << ts.get<0>() << ", Index 1: " << ts.get<1>() << ", Index 2: " << ts.get<2>() << "\n";

    return 0;
}
/* 
Running TupleStore Tests...
All TupleStore tests passed!

Tuple values:
Index 0: 100
Index 1: 9.81
Index 2: TupleStore demo
After remove index 1: 0
After clear:
Index 0: 0, Index 1: 0, Index 2: 
*/