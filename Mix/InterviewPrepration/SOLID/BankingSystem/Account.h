//📁 Account.h
#pragma once
class Account {
  public:
    virtual double getBalance() const = 0;
    virtual void deposit(double amt) = 0;
    virtual bool withdraw(double amt) = 0;
    virtual ~Account() = default;
};