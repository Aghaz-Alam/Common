
//📁 main.cpp
#include <iostream>
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "ConsoleLogger.h"
#include "BankService.h"
int main() {
    ConsoleLogger logger;
    BankService bank(logger);

    SavingsAccount savings(100);
    CheckingAccount checking(20);

    bank.transfer(savings, checking, 50);
    bank.transfer(savings, checking, 100);

    std::cout << "Savings balance: " << savings.getBalance() << "\n";
    std::cout << "Checking balance: " << checking.getBalance() << "\n";
}
/*
OUTPUT
[LOG] Attempting transfer of $50.000000
[LOG] Transfer successful.
[LOG] Attempting transfer of $100.000000
[LOG] Transfer FAILED. Insufficient funds.
Savings balance: 50
Checking balance: 70
*/


//g++ -std=c++17 main.cpp -o solid