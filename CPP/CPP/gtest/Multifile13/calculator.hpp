//calculator.hpp

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

class CalculatorTestHelper;

class Calculator {
private:
    int add(int a, int b);
    friend class CalculatorTestHelper;
};

#endif
