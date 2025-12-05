/* 
17. Banking System (Encapsulation + Classes)

Problem Statement:
Write a program to simulate a simple banking system using classes.
Implement an Account class with deposit(), withdraw(), and printDetails() functions.
Implement a Customer class holding details of the customer and a list of accounts.
The program must identify the account with the highest balance.
Ensure proper data hiding and encapsulation.

Sample Input:
Account a1(101, "Ravi", 1000);
Account a2(102, "Rahul", 5000);

Expected Output:
Account Number: 101, Holder: Ravi, Balance: 1000
Account Number: 102, Holder: Rahul, Balance: 5000
Highest Balance: 5000 (Account 102)
*/

//Banking System (Encapsulation + Classes)
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Account {
private:
    int accountNumber;
    std::string holderName;
    double balance;

public:
    Account(int accNo, const std::string& name, double bal)
        : accountNumber(accNo), holderName(name), balance(bal) {}

    // Encapsulated getters
    int getAccountNumber() const { return accountNumber; }
    const std::string& getHolderName() const { return holderName; }
    double getBalance() const { return balance; }

    // Behaviors
    void deposit(double amount) {
        if (amount <= 0) throw std::runtime_error("Invalid deposit amount");
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) throw std::runtime_error("Invalid withdrawal amount");
        if (amount > balance) throw std::runtime_error("Insufficient funds");
        balance -= amount;
    }

    void printDetails() const {
        std::cout << "Account Number: " << accountNumber
                  << ", Holder: " << holderName
                  << ", Balance: " << balance << std::endl;
    }
};


class Customer {
private:
    std::string name;
    std::vector<Account> accounts;  // Customer owns multiple accounts

public:
    Customer(const std::string& n) : name(n) {}

    void addAccount(const Account& acc) {
        accounts.push_back(acc);
    }

    // Find account with the highest balance
    const Account& highestBalanceAccount() const {
        if (accounts.empty())
            throw std::runtime_error("No accounts available");

        const Account* maxAcc = &accounts[0];
        for (const auto& acc : accounts) {
            if (acc.getBalance() > maxAcc->getBalance())
                maxAcc = &acc;
        }
        return *maxAcc;
    }

    void printAllAccounts() const {
        for (const auto& acc : accounts)
            acc.printDetails();
    }
};


// ------------------ MAIN FUNCTION ------------------

int main() {
    Account a1(101, "Ravi", 1000);
    Account a2(102, "Rahul", 5000);

    Customer customer("Bank_Users");
    customer.addAccount(a1);
    customer.addAccount(a2);

    // Print details of all accounts
    customer.printAllAccounts();

    // Print highest account
    const Account& maxAcc = customer.highestBalanceAccount();
    std::cout << "Highest Balance: " << maxAcc.getBalance()
              << " (Account " << maxAcc.getAccountNumber() << ")\n";

    return 0;
}
/* 
Expected Output
Account Number: 101, Holder: Ravi, Balance: 1000
Account Number: 102, Holder: Rahul, Balance: 5000
Highest Balance: 5000 (Account 102)
*/