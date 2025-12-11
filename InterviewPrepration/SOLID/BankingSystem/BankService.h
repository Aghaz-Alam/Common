//📁 BankService.h
#pragma once
#include "Account.h"
#include "ILogger.h"
class BankService {
  private:
    ILogger& logger;
  public:
    BankService(ILogger& log) : logger(log) {}

    void transfer(Account& from, Account& to, double amt) {
        logger.log("Attempting transfer of $" + std::to_string(amt));

        if (from.withdraw(amt)) {
            to.deposit(amt);
            logger.log("Transfer successful.");
        } else {
            logger.log("Transfer FAILED. Insufficient funds.");
        }
    }
};