/* 
Question 1 : 
Create a C++ program that simulates a basic banking system. 
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


//C++ Program — Banking System
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

/* ============================================================
   PERSON CLASS (Base Class)
   Demonstrates INHERITANCE & POLYMORPHISM
============================================================ */
class Person {
  protected:
    string name;
    string address;
    string contact;

  public:
    Person(string n, string add, string c)
        : name(n), address(add), contact(c) {}

    virtual void printDetails() const {
        cout << "Name: " << name
             << ", Address: " << address
             << ", Contact: " << contact << endl;
    }

    virtual ~Person() {}
};
/* ============================================================
   ACCOUNT CLASS
   Demonstrates ENCAPSULATION
============================================================ */
class Account {
  private:
    int accountNumber;
    string holderName;
    double balance;

  public:
    Account(int accNo, string name, double bal)
        : accountNumber(accNo), holderName(name), balance(bal) {}

    int getAccountNumber() const { return accountNumber; }
    string getHolderName() const { return holderName; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
    }

    void printAccount() const {
        cout << "Account Number: " << accountNumber
             << ", Holder: " << holderName
             << ", Balance: " << balance << endl;
    }
};


/* ============================================================
   CUSTOMER CLASS (Inherits from Person)
============================================================ */
class Customer : public Person {
  private:
    vector<Account*> accounts;     // customer can have multiple accounts

  public:
    Customer(string n, string add, string c)
        : Person(n, add, c) {}

    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }

    void printDetails() const override {
        cout << "Customer Name: " << name
             << ", Address: " << address
             << ", Contact: " << contact << endl;

        for (auto acc : accounts)
            acc->printAccount();
    }
};


/* ============================================================
   BANK CLASS
============================================================ */
class Bank {
  private:
    vector<unique_ptr<Account>> accounts;

  public:
    // Open new account
    Account* openAccount(int accNo, string name, double bal) {
        accounts.push_back(make_unique<Account>(accNo, name, bal));
        return accounts.back().get();  // return raw pointer to store in Customer
    }

    // Find account using account number
    Account* findAccount(int accNo) {
        for (auto& acc : accounts)
            if (acc->getAccountNumber() == accNo)
                return acc.get();
        return nullptr;
    }

    // Deposit amount
    void deposit(int accNo, double amount) {
        Account* acc = findAccount(accNo);
        if (acc) acc->deposit(amount);
    }

    // Withdraw amount
    void withdraw(int accNo, double amount) {
        Account* acc = findAccount(accNo);
        if (acc) acc->withdraw(amount);
    }

    // Print all accounts
    void printAllAccounts() const {
        cout << "All Accounts in the Bank:\n";
        for (const auto& acc : accounts)
            acc->printAccount();
        cout << endl;
    }

    // Find account with highest balance
    Account* highestBalanceAccount() {
        if (accounts.empty()) return nullptr;

        Account* maxAcc = accounts[0].get();
        for (auto& acc : accounts)
            if (acc->getBalance() > maxAcc->getBalance())
                maxAcc = acc.get();
        return maxAcc;
    }
};


/* ============================================================
   MAIN PROGRAM
============================================================ */
int main() {
    Bank bank;

    // Creating accounts
    Account* account1 = bank.openAccount(101, "Ravi", 1000.0);
    Account* account2 = bank.openAccount(102, "Rahul", 5000.0);

    // Creating customers
    Customer customer1("Ravi", "123 Main St", "Ravi@actevia.in");
    Customer customer2("Rahul", "456 Main st", "bob@actevia.in");

    // Linking accounts to customers
    customer1.addAccount(account1);
    customer2.addAccount(account2);

    // Print all accounts
    bank.printAllAccounts();

    // Print customer details
    cout << "Customer 1 Details:\n";
    customer1.printDetails();
    cout << endl;

    cout << "Customer 2 Details:\n";
    customer2.printDetails();
    cout << endl;

    // Display account with highest balance
    cout << "Account with the Highest Balance:\n";
    Account* maxAcc = bank.highestBalanceAccount();
    if (maxAcc)
        maxAcc->printAccount();

    return 0;
}
/* 
Output:
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