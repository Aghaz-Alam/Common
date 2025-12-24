//File 5: IPayment.h 
//Demonstrates ISP + DIP
#pragma once
class IPayment {
  public:
    virtual bool pay(double amount) = 0;
    virtual ~IPayment() = default;
};

