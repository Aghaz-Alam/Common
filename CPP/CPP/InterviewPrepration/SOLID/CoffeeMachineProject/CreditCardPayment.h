//File 6: CreditCardPayment.h
//Implementation for credit card: CreditCardPayment.h
#pragma once
#include "IPayment.h"
#include <iostream>

class CreditCardPayment : public IPayment {
public:
    bool pay(double amount) override {
        std::cout << "Paid $" << amount << " with Credit Card\n";
        return true;
    }
};
