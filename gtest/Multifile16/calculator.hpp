//calculator.hpp

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "adder.hpp"

class Calculator {
public:
    int compute();

private:
    Adder adder;   // dependency
};

#endif
