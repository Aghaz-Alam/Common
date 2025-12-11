//📁 SavingsAccount.h
#pragma once
#include "Account.h"
class SavingsAccount : public Account {
  private:
    double balance{};
  public:
    explicit SavingsAccount(double initial = 0) : balance(initial) {}

    double getBalance() const override { return balance; }
    void deposit(double amt) override { balance += amt; }

    bool withdraw(double amt) override {
        if (balance >= amt) {
            balance -= amt;
            return true;
        }
        return false;
    }
};
