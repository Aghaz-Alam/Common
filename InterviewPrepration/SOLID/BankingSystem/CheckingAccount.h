//📁 CheckingAccount.h
#pragma once
#include "Account.h"
class CheckingAccount : public Account {
  private:
    double balance{};
  public:
    explicit CheckingAccount(double initial = 0) : balance(initial) {}

    double getBalance() const override { return balance; }
    void deposit(double amt) override { balance += amt; }

    bool withdraw(double amt) override {
        balance -= amt; // overdraft allowed
        return true;
    }
};
