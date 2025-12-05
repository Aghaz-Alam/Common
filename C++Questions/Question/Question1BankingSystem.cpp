/* 
Question 1 : Create a C++ program that simulates a basic banking system. 
             The program should have the following classes: Bank, Account, and Customer.

i)Bank class should have the following functionalities:

Maintain a collection of Account objects.
Allow opening new accounts.
Allow depositing and withdrawing money from accounts.
Provide a method to find the account with the highest balance.
Print a list of all accounts.

ii)Account class should have the following functionalities:

Store account number, account holder's name, and balance.
Allow depositing and withdrawing money from the account.
Print the account details.

iii)Customer class should have the following functionalities:

Store customer information, such as name, address, and contact details.
Maintain a list of accounts for each customer.

Note : Classes and objects.
Encapsulation: Properly set access specifiers for class members.
Inheritance: Consider having an appropriate hierarchy for the classes if applicable.
Polymorphism: Implement any necessary virtual functions or use function overriding.

Sample Input :
		Account account1(101, "Ravi", 1000.0);
    		Account account2(102, "Rahul", 5000.0);

		Customer customer1("Ravi", "123 Main St", "Ravi@actevia.in");
		Customer customer2("Rahul", "456 Main st", "Rahul@actevia.in");

Expected Output : 
		All Accounts in the Bank:
		Account Number: 101, Holder: Ravi, Balance: 1000
		Account Number: 102, Holder: Rahul, Balance: 5000

		Customer 1 Details:
		Customer Name: Ravi, Address: 123 Main St, Contact: Ravi@actevia.in
		Account Number: 101, Holder: Ravi, Balance: 1000

		Customer 2 Details:
		Customer Name: Rahul, Address: 456 Main st, Contact: bob@actevia.in
		Account Number: 102, Holder: Rahul, Balance: 5000

		Account with the Highest Balance:
		Account Number: 102, Holder: Rahul, Balance: 5000
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================
// Account class
// ============================
class Account {
private:
    int accountNumber;
    string holderName;
    double balance;

public:
    Account(int accNo, const string& name, double bal)
        : accountNumber(accNo), holderName(name), balance(bal) {}

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient balance or invalid amount." << endl;
    }

    // Print account details
    void print() const {
        cout << "Account Number: " << accountNumber
             << ", Holder: " << holderName
             << ", Balance: " << balance << endl;
    }

    double getBalance() const { return balance; }
    int getAccountNumber() const { return accountNumber; }
    string getHolderName() const { return holderName; }
};

// ============================
// Customer class
// ============================
class Customer {
private:
    string name;
    string address;
    string contact;
    vector<Account> accounts;

public:
    Customer(const string& n, const string& addr, const string& cont)
        : name(n), address(addr), contact(cont) {}

    void addAccount(const Account& acc) {
        accounts.push_back(acc);
    }

    void print() const {
        cout << "Customer Name: " << name
             << ", Address: " << address
             << ", Contact: " << contact << endl;
        for (const auto& acc : accounts)
            acc.print();
        cout << endl;
    }

    vector<Account>& getAccounts() { return accounts; }
};

// ============================
// Bank class
// ============================
class Bank {
private:
    vector<Account> accounts;

public:
    // Open new account
    void openAccount(const Account& acc) {
        accounts.push_back(acc);
    }

    // Deposit money to an account
    void deposit(int accNo, double amount) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNo) {
                acc.deposit(amount);
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    // Withdraw money from an account
    void withdraw(int accNo, double amount) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNo) {
                acc.withdraw(amount);
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    // Print all accounts
    void printAllAccounts() const {
        cout << "All Accounts in the Bank:" << endl;
        for (const auto& acc : accounts)
            acc.print();
        cout << endl;
    }

    // Find account with highest balance
    Account getHighestBalanceAccount() const {
        if (accounts.empty())
            throw runtime_error("No accounts in bank.");

        const Account* highest = &accounts[0];
        for (const auto& acc : accounts) {
            if (acc.getBalance() > highest->getBalance())
                highest = &acc;
        }
        return *highest;
    }
};

// ============================
// MAIN
// ============================
int main() {
    // Create accounts
    Account account1(101, "Ravi", 1000.0);
    Account account2(102, "Rahul", 5000.0);

    // Create customers and assign accounts
    Customer customer1("Ravi", "123 Main St", "Ravi@actevia.in");
    customer1.addAccount(account1);

    Customer customer2("Rahul", "456 Main st", "Rahul@actevia.in");
    customer2.addAccount(account2);

    // Create bank and open accounts
    Bank bank;
    bank.openAccount(account1);
    bank.openAccount(account2);

    // Print all accounts in the bank
    bank.printAllAccounts();

    // Print customer details
    cout << "Customer 1 Details:" << endl;
    customer1.print();

    cout << "Customer 2 Details:" << endl;
    customer2.print();

    // Print account with highest balance
    cout << "Account with the Highest Balance:" << endl;
    Account highest = bank.getHighestBalanceAccount();
    highest.print();

    return 0;
}
/* 
All Accounts in the Bank:
Account Number: 101, Holder: Ravi, Balance: 1000
Account Number: 102, Holder: Rahul, Balance: 5000

Customer 1 Details:
Customer Name: Ravi, Address: 123 Main St, Contact: Ravi@actevia.in
Account Number: 101, Holder: Ravi, Balance: 1000

Customer 2 Details:
Customer Name: Rahul, Address: 456 Main st, Contact: Rahul@actevia.in
Account Number: 102, Holder: Rahul, Balance: 5000

Account with the Highest Balance:
Account Number: 102, Holder: Rahul, Balance: 5000
*/