//File 7: CoffeeMachine.h
//Demonstrates SRP, OCP, DIP
#pragma once
#include "Coffee.h"
#include "ILogger.h"
#include "IPayment.h"
class CoffeeMachine {
  private:
    ILogger& logger;        // DIP
    IPayment& payment;      // DIP

  public:
    CoffeeMachine(ILogger& log, IPayment& pay)
        : logger(log), payment(pay) {}

    void prepareCoffee(const Coffee& c) {  // Uses polymorphism
        logger.log("Preparing " + c.name());

        if (payment.pay(c.price()))
            logger.log(c.name() + " is ready!");
        else
            logger.log("Payment failed!");
    }
};
/* 
✔ DIP: Depends on abstractions (ILogger, IPayment)
✔ OCP: Add new loggers, payments, or coffee types
✔ LSP: Any Coffee subclass works
*/