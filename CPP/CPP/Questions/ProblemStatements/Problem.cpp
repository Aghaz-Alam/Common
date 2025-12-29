/* 
1 — Implement Your Own Static Array (StaticArray<T, N>)

Problem Statement:
Implement a template class StaticArray<T, N> with a fixed-size internal array T data[N], supporting:
operator[] with bounds checking
size(), fill(T), find(const T&)
Numeric-only sum(), max(), min()
printAll()
Custom iterators compatible with range-based for loops
Specialization for bool with bit-packing (uint64_t) supporting set(), get(), printBits()

Sample Input:
StaticArray<int, 5> arr;
arr.fill(3);
arr[1] = 10;
arr.printAll();
cout << "Sum: " << arr.sum() << endl;
cout << "Max: " << arr.max() << endl;
cout << "Min: " << arr.min() << endl;

for(auto& x : arr) x += 1;
arr.printAll();

// Specialization for bool
StaticArray<bool, 10> b;
b.set(3, true);
b.set(7, true);
b.printBits();


Expected Output:
3 10 3 3 3
Sum: 22
Max: 10
Min: 3
4 11 4 4 4
0001000010
*/

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <cstdint>
using namespace std;

// ====================================================
// 1. Primary template for general T
// ====================================================
template <typename T, size_t N>
class StaticArray {
private:
    T data[N];

public:
    // Iterator implementation
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end()   { return Iterator(data + N); }

    // Size
    constexpr size_t size() const { return N; }

    // Bounds-checked access
    T& operator[](size_t index) {
        if (index >= N) throw out_of_range("Index out of range");
        return data[index];
    }
    const T& operator[](size_t index) const {
        if (index >= N) throw out_of_range("Index out of range");
        return data[index];
    }

    // Fill entire array
    void fill(const T& val) {
        for (size_t i = 0; i < N; ++i) data[i] = val;
    }

    // Find value
    int find(const T& val) const {
        for (size_t i = 0; i < N; ++i)
            if (data[i] == val) return (int)i;
        return -1;
    }

    // Only for numeric types: sum, max, min
    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type sum() const {
        U s = 0;
        for (size_t i = 0; i < N; ++i) s += data[i];
        return s;
    }

    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type max() const {
        U m = data[0];
        for (size_t i = 1; i < N; ++i)
            if (data[i] > m) m = data[i];
        return m;
    }

    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type min() const {
        U m = data[0];
        for (size_t i = 1; i < N; ++i)
            if (data[i] < m) m = data[i];
        return m;
    }

    // Print all values
    void printAll() const {
        for (size_t i = 0; i < N; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};


// ====================================================
// 2. Specialization for bool with bit packing
// ====================================================
template <size_t N>
class StaticArray<bool, N> {
private:
    static constexpr size_t BITS = 64;
    static constexpr size_t BLOCKS = (N + BITS - 1) / BITS;

    uint64_t data[BLOCKS] = {};

    void checkIndex(size_t index) const {
        if (index >= N) throw out_of_range("Index out of range");
    }

public:
    StaticArray() {
        for (size_t i = 0; i < BLOCKS; ++i) data[i] = 0;
    }

    void set(size_t index, bool value) {
        checkIndex(index);
        size_t block = index / BITS;
        size_t bit   = index % BITS;

        if (value)
            data[block] |= (1ULL << bit);
        else
            data[block] &= ~(1ULL << bit);
    }

    bool get(size_t index) const {
        checkIndex(index);
        size_t block = index / BITS;
        size_t bit   = index % BITS;
        return (data[block] >> bit) & 1ULL;
    }

    void printBits() const {
        for (size_t i = 0; i < N; ++i)
            cout << (get(i) ? '1' : '0');
        cout << endl;
    }
};


// ====================================================
// MAIN — Demonstration
// ====================================================
int main() {

    StaticArray<int, 5> arr;
    arr.fill(3);
    arr[1] = 10;
    arr.printAll();

    cout << "Sum: " << arr.sum() << endl;
    cout << "Max: " << arr.max() << endl;
    cout << "Min: " << arr.min() << endl;

    // Range-based for loop using iterators
    for (auto &x : arr) x += 1;
    arr.printAll();

    // Bool specialization
    StaticArray<bool, 10> b;
    b.set(3, true);
    b.set(7, true);
    b.printBits();

    return 0;
}
/* 
Expected Output: 
3 10 3 3 3
Sum: 22
Max: 10
Min: 3
4 11 4 4 4
0001000010
*/


/*================================================================================*/

/* 
2 — Dynamic Vector (MyVector<T>)
Problem Statement:
Implement a template class MyVector<T> with dynamic resizing, supporting:
push_back(T), pop_back()
operator[] with bounds checking
size(), capacity(), reserve()
Numeric-only sum(), max(), min()
printAll()
Custom iterators compatible with range-based for loops

Sample Input:
MyVector<int> v;
v.push_back(5);
v.push_back(10);
v.push_back(3);
v.printAll();
cout << "Sum: " << v.sum() << endl;
v[1] = 20;
for(auto& x : v) x += 1;
v.printAll();


Expected Output:
5 10 3
Sum: 18
6 21 4
*/

#include <iostream>
#include <stdexcept>
#include <type_traits>
using namespace std;

template <typename T>
class MyVector {
  private:
    T* data;
    size_t used;
    size_t cap;
    void reallocate(size_t newCap) {
        T* newData = new T[newCap];
        for (size_t i = 0; i < used; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        cap = newCap;
    }

  public:
    // -------- Iterator --------
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };
    Iterator begin() { return Iterator(data); }
    Iterator end()   { return Iterator(data + used); }

    // -------- Constructors --------
    MyVector() : data(nullptr), used(0), cap(0) {}

    ~MyVector() {
        delete[] data;
    }

    // -------- Capacity --------
    size_t size() const { return used; }
    size_t capacity() const { return cap; }

    void reserve(size_t newCap) {
        if (newCap > cap) reallocate(newCap);
    }

    // -------- Element Access --------
    T& operator[](size_t index) {
        if (index >= used) throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= used) throw out_of_range("Index out of range");
        return data[index];
    }

    // -------- Modifiers --------
    void push_back(const T& value) {
        if (used == cap) reserve(cap == 0 ? 2 : cap * 2);
        data[used++] = value;
    }

    void pop_back() {
        if (used == 0) throw out_of_range("pop_back on empty vector");
        --used;
    }

    // -------- Numeric operations --------
    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type sum() const {
        U s = 0;
        for (size_t i = 0; i < used; ++i)
            s += data[i];
        return s;
    }

    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type max() const {
        U m = data[0];
        for (size_t i = 1; i < used; ++i)
            if (data[i] > m) m = data[i];
        return m;
    }

    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type min() const {
        U m = data[0];
        for (size_t i = 1; i < used; ++i)
            if (data[i] < m) m = data[i];
        return m;
    }

    // -------- Print --------
    void printAll() const {
        for (size_t i = 0; i < used; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};


// ==========================================================
// Main — Demonstration
// ==========================================================
int main() {
    MyVector<int> v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(3);

    v.printAll();
    cout << "Sum: " << v.sum() << endl;

    v[1] = 20;

    for (auto& x : v) x += 1;

    v.printAll();

    return 0;
}
/* 
Expected Output
5 10 3
Sum: 18
6 21 4
*/


/*================================================================================*/

/* 
3 — Bank Account System
Problem Statement:
Implement classes BankAccount (base), SavingsAccount, CheckingAccount with:
deposit(double), withdraw(double) with exceptions
calculateInterest() for savings account
printDetails()
Bank class stores accounts in std::vector<std::shared_ptr<BankAccount>> and supports totalBalance()

Sample Input:
Bank bank;
auto s = std::make_shared<SavingsAccount>("Alice", 1001, 5000, 0.05);
auto c = std::make_shared<CheckingAccount>("Bob", 1002, 3000);
bank.addAccount(s);
bank.addAccount(c);
bank.printAllAccounts();
cout << "Total Balance: " << bank.totalBalance() << endl;


Expected Output:
SavingsAccount: Alice, ID: 1001, Balance: 5000, Interest: 250
CheckingAccount: Bob, ID: 1002, Balance: 3000
Total Balance: 8000
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
using namespace std;

// =====================================================
// Base Class: BankAccount
// =====================================================
class BankAccount {
protected:
    string holder;
    int id;
    double balance;

public:
    BankAccount(string name, int accId, double bal)
        : holder(name), id(accId), balance(bal) {}

    virtual ~BankAccount() = default;

    virtual void deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Invalid deposit amount");
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) throw invalid_argument("Invalid withdraw amount");
        if (amount > balance) throw runtime_error("Insufficient funds");
        balance -= amount;
    }

    double getBalance() const { return balance; }

    virtual void printDetails() const = 0;
};

// =====================================================
// SavingsAccount
// =====================================================
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string name, int accId, double bal, double rate)
        : BankAccount(name, accId, bal), interestRate(rate) {}

    double calculateInterest() const {
        return balance * interestRate;
    }

    void printDetails() const override {
        cout << "SavingsAccount: " << holder
             << ", ID: " << id
             << ", Balance: " << balance
             << ", Interest: " << calculateInterest()
             << endl;
    }
};

// =====================================================
// CheckingAccount
// =====================================================
class CheckingAccount : public BankAccount {
public:
    CheckingAccount(string name, int accId, double bal)
        : BankAccount(name, accId, bal) {}

    void printDetails() const override {
        cout << "CheckingAccount: " << holder
             << ", ID: " << id
             << ", Balance: " << balance
             << endl;
    }
};

// =====================================================
// Bank Class Managing Accounts
// =====================================================
class Bank {
private:
    vector<shared_ptr<BankAccount>> accounts;

public:
    void addAccount(shared_ptr<BankAccount> acc) {
        accounts.push_back(acc);
    }

    double totalBalance() const {
        double sum = 0;
        for (const auto& acc : accounts)
            sum += acc->getBalance();
        return sum;
    }

    void printAllAccounts() const {
        for (const auto& acc : accounts)
            acc->printDetails();
    }
};

// =====================================================
// Main – Demonstration
// =====================================================
int main() {
    Bank bank;

    auto s = make_shared<SavingsAccount>("Alice", 1001, 5000, 0.05);
    auto c = make_shared<CheckingAccount>("Bob", 1002, 3000);

    bank.addAccount(s);
    bank.addAccount(c);

    bank.printAllAccounts();
    cout << "Total Balance: " << bank.totalBalance() << endl;

    return 0;
}
/* 
Expected Output
SavingsAccount: Alice, ID: 1001, Balance: 5000, Interest: 250
CheckingAccount: Bob, ID: 1002, Balance: 3000
Total Balance: 8000
*/
/*================================================================================*/
/* 
4 — Employee / Payroll System
Problem Statement:
Implement Employee (base), Manager, Engineer, Intern with:
Virtual calculateSalary()
PayrollSystem storing std::vector<std::shared_ptr<Employee>>
printPayroll(), totalSalary(), findHighestPaid()

Sample Input:
PayrollSystem payroll;
auto m = std::make_shared<Manager>("Alice", 1001, 80000, 0.1);
auto e = std::make_shared<Engineer>("Bob", 1002, 60000, 10, 50);
auto i = std::make_shared<Intern>("Charlie", 1003, 1500);
payroll.addEmployee(m);
payroll.addEmployee(e);
payroll.addEmployee(i);
payroll.printPayroll();
cout << "Total Salary: " << payroll.totalSalary() << endl;


Expected Output:
Employee: Alice, ID: 1001, Salary: 88000
Employee: Bob, ID: 1002, Salary: 60500
Employee: Charlie, ID: 1003, Salary: 1500
Total Salary: 150000
*/
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>
using namespace std;

// ===============================
// Base Class: Employee
// ===============================
class Employee {
protected:
    string name;
    int id;
public:
    Employee(string n, int i) : name(n), id(i) {}
    virtual ~Employee() = default;

    virtual double calculateSalary() const = 0;

    virtual void printDetails() const {
        cout << "Employee: " << name
             << ", ID: " << id
             << ", Salary: " << calculateSalary();
    }
};

// ===============================
// Manager Class
// ===============================
class Manager : public Employee {
    double baseSalary;
    double bonusRate;
public:
    Manager(string n, int i, double base, double bonus)
        : Employee(n, i), baseSalary(base), bonusRate(bonus) {}

    double calculateSalary() const override {
        return baseSalary + baseSalary * bonusRate;
    }
};

// ===============================
// Engineer Class
// ===============================
class Engineer : public Employee {
    double baseSalary;
    double overtimeHours;
    double overtimeRate;
public:
    Engineer(string n, int i, double base, double hours, double rate)
        : Employee(n, i),
          baseSalary(base),
          overtimeHours(hours),
          overtimeRate(rate) {}

    double calculateSalary() const override {
        return baseSalary + overtimeHours * overtimeRate;
    }
};

// ===============================
// Intern Class
// ===============================
class Intern : public Employee {
    double stipend;
public:
    Intern(string n, int i, double s)
        : Employee(n, i), stipend(s) {}

    double calculateSalary() const override {
        return stipend;
    }
};

// ===============================
// PayrollSystem Class
// ===============================
class PayrollSystem {
    vector<shared_ptr<Employee>> employees;

public:
    void addEmployee(shared_ptr<Employee> e) {
        employees.push_back(e);
    }

    void printPayroll() const {
        for (auto& emp : employees) {
            emp->printDetails();
            cout << endl;
        }
    }

    double totalSalary() const {
        double total = 0;
        for (auto& emp : employees)
            total += emp->calculateSalary();
        return total;
    }

    shared_ptr<Employee> findHighestPaid() const {
        if (employees.empty()) return nullptr;

        auto highest = employees[0];
        for (auto& emp : employees) {
            if (emp->calculateSalary() > highest->calculateSalary())
                highest = emp;
        }
        return highest;
    }
};

// ===============================
// Main Example
// ===============================
int main() {
    PayrollSystem payroll;

    auto m = make_shared<Manager>("Alice", 1001, 80000, 0.1);
    auto e = make_shared<Engineer>("Bob", 1002, 60000, 10, 50);
    auto i = make_shared<Intern>("Charlie", 1003, 1500);

    payroll.addEmployee(m);
    payroll.addEmployee(e);
    payroll.addEmployee(i);

    payroll.printPayroll();

    cout << "Total Salary: " << payroll.totalSalary() << endl;

    return 0;
}
/* 
Matches Expected Output Exactly
Employee: Alice, ID: 1001, Salary: 88000
Employee: Bob, ID: 1002, Salary: 60500
Employee: Charlie, ID: 1003, Salary: 1500
Total Salary: 150000
*/



/*================================================================================*/

/* 
5 — Media Player System

Problem Statement:
Implement Media (base), Audio, Video with virtual play(), pause(), stop() and MediaLibrary storing std::vector<std::shared_ptr<Media>>.

Sample Input:

MediaLibrary library;
auto a = std::make_shared<Audio>("Song1", 180);
auto v = std::make_shared<Video>("Movie1", 7200);
library.addMedia(a);
library.addMedia(v);
library.playAll();


Expected Output:

Playing Audio: Song1, Duration: 180
Playing Video: Movie1, Duration: 7200
*/
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// ===================================================
// Base Class: Media
// ===================================================
class Media {
protected:
    string title;
    int duration; // in seconds
public:
    Media(const string& t, int d) : title(t), duration(d) {}
    virtual ~Media() = default;

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

// ===================================================
// Audio Class
// ===================================================
class Audio : public Media {
public:
    Audio(const string& t, int d) : Media(t, d) {}

    void play() override {
        cout << "Playing Audio: " << title << ", Duration: " << duration << endl;
    }

    void pause() override {
        cout << "Pausing Audio: " << title << endl;
    }

    void stop() override {
        cout << "Stopping Audio: " << title << endl;
    }
};

// ===================================================
// Video Class
// ===================================================
class Video : public Media {
public:
    Video(const string& t, int d) : Media(t, d) {}

    void play() override {
        cout << "Playing Video: " << title << ", Duration: " << duration << endl;
    }

    void pause() override {
        cout << "Pausing Video: " << title << endl;
    }

    void stop() override {
        cout << "Stopping Video: " << title << endl;
    }
};

// ===================================================
// MediaLibrary Class
// ===================================================
class MediaLibrary {
    vector<shared_ptr<Media>> mediaList;

public:
    void addMedia(shared_ptr<Media> m) {
        mediaList.push_back(m);
    }

    void playAll() {
        for (auto& m : mediaList)
            m->play();
    }

    void pauseAll() {
        for (auto& m : mediaList)
            m->pause();
    }

    void stopAll() {
        for (auto& m : mediaList)
            m->stop();
    }
};

// ===================================================
// Main Demonstration
// ===================================================
int main() {
    MediaLibrary library;

    auto a = make_shared<Audio>("Song1", 180);
    auto v = make_shared<Video>("Movie1", 7200);

    library.addMedia(a);
    library.addMedia(v);

    library.playAll();

    return 0;
}
/* 
Expected Output
Playing Audio: Song1, Duration: 180
Playing Video: Movie1, Duration: 7200
*/


/*================================================================================*/
/* 
6 — Library Management System

Problem Statement:
Implement Book, Member, Library with:

borrowBook(memberID, bookID), returnBook()

printAllBooks(), printMemberDetails()

Use std::vector + smart pointers

Sample Input:

Library lib;
auto book1 = std::make_shared<Book>("C++ Primer", 101);
auto member1 = std::make_shared<Member>("Alice", 1);
lib.addBook(book1);
lib.addMember(member1);
lib.borrowBook(1, 101);
lib.printAllBooks();
lib.printMemberDetails(1);


Expected Output:

Book: C++ Primer, ID: 101, Status: Borrowed
Member: Alice, ID: 1, Borrowed Books: 101
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
using namespace std;

// =====================
// Book Class
// =====================
class Book {
private:
    string title;
    int id;
    bool borrowed;

public:
    Book(const string& t, int i) : title(t), id(i), borrowed(false) {}

    int getID() const { return id; }
    string getTitle() const { return title; }
    bool isBorrowed() const { return borrowed; }

    void borrow() {
        if (borrowed) throw runtime_error("Book already borrowed");
        borrowed = true;
    }

    void returnBook() { borrowed = false; }

    void print() const {
        cout << "Book: " << title
             << ", ID: " << id
             << ", Status: " << (borrowed ? "Borrowed" : "Available")
             << endl;
    }
};

// =====================
// Member Class
// =====================
class Member {
private:
    string name;
    int id;
    vector<int> borrowedBooks;

public:
    Member(const string& n, int i) : name(n), id(i) {}

    int getID() const { return id; }
    string getName() const { return name; }

    void borrowBook(int bookID) { borrowedBooks.push_back(bookID); }

    void returnBook(int bookID) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookID), borrowedBooks.end());
    }

    void printDetails() const {
        cout << "Member: " << name
             << ", ID: " << id
             << ", Borrowed Books: ";
        if (borrowedBooks.empty()) cout << "None";
        else {
            for (size_t i = 0; i < borrowedBooks.size(); ++i) {
                cout << borrowedBooks[i];
                if (i != borrowedBooks.size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }
};

// =====================
// Library Class
// =====================
class Library {
private:
    vector<shared_ptr<Book>> books;
    vector<shared_ptr<Member>> members;

    shared_ptr<Book> findBook(int bookID) {
        for (auto& b : books)
            if (b->getID() == bookID) return b;
        throw runtime_error("Book not found");
    }

    shared_ptr<Member> findMember(int memberID) {
        for (auto& m : members)
            if (m->getID() == memberID) return m;
        throw runtime_error("Member not found");
    }

public:
    void addBook(shared_ptr<Book> b) { books.push_back(b); }
    void addMember(shared_ptr<Member> m) { members.push_back(m); }

    void borrowBook(int memberID, int bookID) {
        auto m = findMember(memberID);
        auto b = findBook(bookID);
        b->borrow();
        m->borrowBook(bookID);
    }

    void returnBook(int memberID, int bookID) {
        auto m = findMember(memberID);
        auto b = findBook(bookID);
        b->returnBook();
        m->returnBook(bookID);
    }

    void printAllBooks() const {
        for (auto& b : books) b->print();
    }

    void printMemberDetails(int memberID) const {
        for (auto& m : members)
            if (m->getID() == memberID) {
                m->printDetails();
                return;
            }
        cout << "Member not found" << endl;
    }
};

// =====================
// Main Demonstration
// =====================
int main() {
    Library lib;

    auto book1 = make_shared<Book>("C++ Primer", 101);
    auto member1 = make_shared<Member>("Alice", 1);

    lib.addBook(book1);
    lib.addMember(member1);

    lib.borrowBook(1, 101);

    lib.printAllBooks();
    lib.printMemberDetails(1);

    return 0;
}
/* 
Expected Output
Book: C++ Primer, ID: 101, Status: Borrowed
Member: Alice, ID: 1, Borrowed Books: 101
*/
/*================================================================================*/
/* 
7 — Smart Pointer Wrapper

Problem Statement:
Implement UniquePtr<T> supporting:

Move constructor and assignment

Dereference * and ->

Automatic deletion in destructor

Sample Input:

UniquePtr<int> p1(new int(10));
cout << *p1 << endl;
UniquePtr<int> p2 = std::move(p1);


Expected Output:

10
*/


#include <iostream>
#include <utility>
using namespace std;

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~UniquePtr() {
        delete ptr;
    }

    // Delete copy constructor and copy assignment
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Dereference operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Get raw pointer
    T* get() const { return ptr; }

    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Reset pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// =====================
// Main Demonstration
// =====================
int main() {
    UniquePtr<int> p1(new int(10));
    cout << *p1 << endl;

    UniquePtr<int> p2 = std::move(p1);
    if (p1.get() == nullptr) cout << "p1 is nullptr after move" << endl;

    cout << *p2 << endl;

    return 0;
}
/* 
Expected Output
10
p1 is nullptr after move
10
*/

/*================================================================================*/
/* 
8 — LRU Cache

Problem Statement:
Implement a template LRU cache LRUCache<Key, Value>:

put(key, value), get(key)

Maintain capacity

Use std::unordered_map + std::list

printCache() for debugging

Sample Input:

LRUCache<int, string> cache(3);
cache.put(1, "A");
cache.put(2, "B");
cache.put(3, "C");
cache.get(2);
cache.put(4, "D");
cache.printCache();


Expected Output:

4:D 2:B 3:C
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

template <typename Key, typename Value>
class LRUCache {
private:
    size_t capacity;

    // Doubly-linked list to maintain usage order (front = most recent)
    list<pair<Key, Value>> cacheList;

    // Map key -> iterator in list
    unordered_map<Key, typename list<pair<Key, Value>>::iterator> cacheMap;

public:
    LRUCache(size_t cap) : capacity(cap) {}

    void put(const Key& key, const Value& value) {
        // If key exists, update value and move to front
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            it->second->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return;
        }

        // Evict least recently used if full
        if (cacheList.size() >= capacity) {
            auto last = cacheList.back();
            cacheMap.erase(last.first);
            cacheList.pop_back();
        }

        // Insert new element at front
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }

    Value get(const Key& key) {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
            throw runtime_error("Key not found");

        // Move accessed element to front
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second;
    }

    void printCache() const {
        for (auto& kv : cacheList) {
            cout << kv.first << ":" << kv.second << " ";
        }
        cout << endl;
    }
};

// =====================
// Main Demonstration
// =====================
int main() {
    LRUCache<int, string> cache(3);

    cache.put(1, "A");
    cache.put(2, "B");
    cache.put(3, "C");

    cache.get(2);       // access key 2, now MRU order: 2,3,1

    cache.put(4, "D");  // evicts LRU (1)

    cache.printCache(); // Expected: 4:D 2:B 3:C

    return 0;
}
/* 
Expected Output
4:D 2:B 3:C
*/


/*================================================================================*/
/* 
9 — Custom Stack

Problem Statement:
Implement Stack<T> with:

push(), pop(), top(), size()

Throw exception on empty pop() or top()

Support range-based iteration

Sample Input:

Stack<int> s;
s.push(10);
s.push(20);
cout << s.top() << endl;
s.pop();
s.printAll();


Expected Output:

20
10
*/



#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    vector<T> data;

public:
    // Push element onto stack
    void push(const T& val) {
        data.push_back(val);
    }

    // Pop element from stack
    void pop() {
        if (data.empty())
            throw runtime_error("Stack is empty");
        data.pop_back();
    }

    // Return top element
    T& top() {
        if (data.empty())
            throw runtime_error("Stack is empty");
        return data.back();
    }

    const T& top() const {
        if (data.empty())
            throw runtime_error("Stack is empty");
        return data.back();
    }

    // Stack size
    size_t size() const {
        return data.size();
    }

    // Check if empty
    bool empty() const {
        return data.empty();
    }

    // Range-based iteration support
    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin(); }
    typename vector<T>::const_iterator end() const { return data.end(); }

    // Print all elements (from bottom to top)
    void printAll() const {
        for (auto& x : data)
            cout << x << " ";
        cout << endl;
    }
};

// =====================
// Main Demonstration
// =====================
int main() {
    Stack<int> s;

    s.push(10);
    s.push(20);

    cout << s.top() << endl; // 20

    s.pop();

    s.printAll();            // 10

    // Range-based for loop demo
    for (auto& val : s) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
/* 
Expected Output
20
10
10
*/

/*================================================================================*/
/* 
10 — Custom Queue

Problem Statement:
Implement Queue<T> with:

enqueue(), dequeue(), front(), size()

Exception safety

Iterators for range-based loops

Sample Input:

Queue<int> q;
q.enqueue(1);
q.enqueue(2);
cout << q.front() << endl;
q.dequeue();
q.printAll();


Expected Output:

1
2
*/



#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    vector<T> data;
    size_t frontIndex = 0; // points to current front element

public:
    // Enqueue element
    void enqueue(const T& val) {
        data.push_back(val);
    }

    // Dequeue element
    void dequeue() {
        if (empty())
            throw runtime_error("Queue is empty");
        frontIndex++;
        // Optional: shrink vector if too much unused space
        if (frontIndex > data.size() / 2) {
            data.erase(data.begin(), data.begin() + frontIndex);
            frontIndex = 0;
        }
    }

    // Access front element
    T& front() {
        if (empty())
            throw runtime_error("Queue is empty");
        return data[frontIndex];
    }

    const T& front() const {
        if (empty())
            throw runtime_error("Queue is empty");
        return data[frontIndex];
    }

    // Queue size
    size_t size() const {
        return data.size() - frontIndex;
    }

    bool empty() const {
        return size() == 0;
    }

    // Iterators for range-based for loop
    typename vector<T>::iterator begin() { return data.begin() + frontIndex; }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin() + frontIndex; }
    typename vector<T>::const_iterator end() const { return data.end(); }

    // Print all elements
    void printAll() const {
        for (auto it = begin(); it != end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
};

// =====================
// Main Demonstration
// =====================
int main() {
    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);

    cout << q.front() << endl; // 1

    q.dequeue();

    q.printAll();              // 2

    // Range-based for loop demo
    for (auto& val : q)
        cout << val << " ";
    cout << endl;

    return 0;
}
/* 
Expected Output
1
2
2
*/
/*================================================================================*/

/* 
2 — Dynamic Vector (MyVector<T>)

Problem Statement:
Implement a template class MyVector<T> with dynamic resizing, supporting:

push_back(T), pop_back()

operator[] with bounds checking

size(), capacity(), reserve()

Numeric-only sum(), max(), min()

printAll()

Custom iterators for range-based for loops

Sample Input:

MyVector<int> v;
v.push_back(5);
v.push_back(10);
v.push_back(3);
v.printAll();
cout << "Sum: " << v.sum() << endl;
v[1] = 20;
for(auto& x : v) x += 1;
v.printAll();


Expected Output:

5 10 3
Sum: 18
6 21 4
*/



#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <algorithm>
using namespace std;

template <typename T>
class MyVector {
private:
    T* data;
    size_t sz;
    size_t cap;

    void resize(size_t newCap) {
        T* newData = new T[newCap];
        for (size_t i = 0; i < sz; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    // Constructor
    MyVector() : data(nullptr), sz(0), cap(0) {}

    // Destructor
    ~MyVector() { delete[] data; }

    // Copy constructor
    MyVector(const MyVector& other) : data(new T[other.cap]), sz(other.sz), cap(other.cap) {
        for (size_t i = 0; i < sz; i++) data[i] = other.data[i];
    }

    // Copy assignment
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            sz = other.sz;
            cap = other.cap;
            data = new T[cap];
            for (size_t i = 0; i < sz; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // Size & Capacity
    size_t size() const { return sz; }
    size_t capacity() const { return cap; }

    void reserve(size_t newCap) {
        if (newCap > cap) resize(newCap);
    }

    // Element access with bounds checking
    T& operator[](size_t index) {
        if (index >= sz) throw out_of_range("Index out of bounds");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sz) throw out_of_range("Index out of bounds");
        return data[index];
    }

    // Push back
    void push_back(const T& val) {
        if (sz == cap) resize(cap == 0 ? 1 : cap * 2);
        data[sz++] = val;
    }

    // Pop back
    void pop_back() {
        if (sz == 0) throw runtime_error("Vector is empty");
        sz--;
    }

    // Numeric-only operations
    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type sum() const {
        U s = 0;
        for (size_t i = 0; i < sz; i++) s += data[i];
        return s;
    }

    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type max() const {
        if (sz == 0) throw runtime_error("Vector is empty");
        return *max_element(data, data + sz);
    }

    template <typename U = T>
    typename enable_if<is_arithmetic<U>::value, U>::type min() const {
        if (sz == 0) throw runtime_error("Vector is empty");
        return *min_element(data, data + sz);
    }

    // Print all elements
    void printAll() const {
        for (size_t i = 0; i < sz; i++) cout << data[i] << " ";
        cout << endl;
    }

    // Iterators
    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }
};

// =====================
// Main Demonstration
// =====================
int main() {
    MyVector<int> v;

    v.push_back(5);
    v.push_back(10);
    v.push_back(3);

    v.printAll();               // 5 10 3
    cout << "Sum: " << v.sum() << endl; // 18

    v[1] = 20;

    for (auto& x : v) x += 1;  // increment each element

    v.printAll();               // 6 21 4

    return 0;
}
/* 
Expected Output
5 10 3
Sum: 18
6 21 4
*/

/*================================================================================*/
/* 
3 — Bank Account System

Problem Statement:
Implement classes BankAccount (base), SavingsAccount, CheckingAccount with:

deposit(double), withdraw(double) with exceptions

calculateInterest() for SavingsAccount

printDetails()

Bank class stores accounts in std::vector<std::shared_ptr<BankAccount>> and supports totalBalance()

Sample Input:

Bank bank;
auto s = std::make_shared<SavingsAccount>("Alice", 1001, 5000, 0.05);
auto c = std::make_shared<CheckingAccount>("Bob", 1002, 3000);
bank.addAccount(s);
bank.addAccount(c);
bank.printAllAccounts();
cout << "Total Balance: " << bank.totalBalance() << endl;


Expected Output:

SavingsAccount: Alice, ID: 1001, Balance: 5000, Interest: 250
CheckingAccount: Bob, ID: 1002, Balance: 3000
Total Balance: 8000
*/

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

// --------------------------
// Base Class: BankAccount
// --------------------------
class BankAccount {
protected:
    string holderName;
    int accountID;
    double balance;

public:
    BankAccount(const string& name, int id, double bal)
        : holderName(name), accountID(id), balance(bal) {}

    virtual ~BankAccount() = default;

    virtual void deposit(double amount) {
        if (amount < 0) throw runtime_error("Cannot deposit negative amount");
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount < 0) throw runtime_error("Cannot withdraw negative amount");
        if (amount > balance) throw runtime_error("Insufficient balance");
        balance -= amount;
    }

    virtual void printDetails() const = 0;

    double getBalance() const { return balance; }
};

// --------------------------
// Derived Class: SavingsAccount
// --------------------------
class SavingsAccount : public BankAccount {
    double interestRate; // e.g., 0.05 for 5%
public:
    SavingsAccount(const string& name, int id, double bal, double rate)
        : BankAccount(name, id, bal), interestRate(rate) {}

    double calculateInterest() const {
        return balance * interestRate;
    }

    void printDetails() const override {
        cout << "SavingsAccount: " << holderName
             << ", ID: " << accountID
             << ", Balance: " << balance
             << ", Interest: " << calculateInterest() << endl;
    }
};

// --------------------------
// Derived Class: CheckingAccount
// --------------------------
class CheckingAccount : public BankAccount {
public:
    CheckingAccount(const string& name, int id, double bal)
        : BankAccount(name, id, bal) {}

    void printDetails() const override {
        cout << "CheckingAccount: " << holderName
             << ", ID: " << accountID
             << ", Balance: " << balance << endl;
    }
};

// --------------------------
// Bank Class
// --------------------------
class Bank {
    vector<shared_ptr<BankAccount>> accounts;

public:
    void addAccount(shared_ptr<BankAccount> account) {
        accounts.push_back(account);
    }

    void printAllAccounts() const {
        for (auto& acc : accounts)
            acc->printDetails();
    }

    double totalBalance() const {
        double total = 0;
        for (auto& acc : accounts)
            total += acc->getBalance();
        return total;
    }
};

// --------------------------
// Main Demonstration
// --------------------------
int main() {
    Bank bank;

    auto s = make_shared<SavingsAccount>("Alice", 1001, 5000, 0.05);
    auto c = make_shared<CheckingAccount>("Bob", 1002, 3000);

    bank.addAccount(s);
    bank.addAccount(c);

    bank.printAllAccounts();

    cout << "Total Balance: " << bank.totalBalance() << endl;

    return 0;
}
/* 
Expected Output
SavingsAccount: Alice, ID: 1001, Balance: 5000, Interest: 250
CheckingAccount: Bob, ID: 1002, Balance: 3000
Total Balance: 8000
*/


/*================================================================================*/
/* 
4 — Employee / Payroll System

Problem Statement:
Implement Employee (base), Manager, Engineer, Intern with:

Virtual calculateSalary()

PayrollSystem stores employees in std::vector<std::shared_ptr<Employee>>

printPayroll(), totalSalary(), findHighestPaid()

Sample Input:

PayrollSystem payroll;
auto m = std::make_shared<Manager>("Alice", 1001, 80000, 0.1);
auto e = std::make_shared<Engineer>("Bob", 1002, 60000, 10, 50);
auto i = std::make_shared<Intern>("Charlie", 1003, 1500);
payroll.addEmployee(m);
payroll.addEmployee(e);
payroll.addEmployee(i);
payroll.printPayroll();
cout << "Total Salary: " << payroll.totalSalary() << endl;


Expected Output:

Employee: Alice, ID: 1001, Salary: 88000
Employee: Bob, ID: 1002, Salary: 60500
Employee: Charlie, ID: 1003, Salary: 1500
Total Salary: 150000
*/


#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

// --------------------------
// Base Class: Employee
// --------------------------
class Employee {
protected:
    string name;
    int id;
public:
    Employee(const string& n, int i) : name(n), id(i) {}
    virtual ~Employee() = default;

    virtual double calculateSalary() const = 0;

    void print() const {
        cout << "Employee: " << name << ", ID: " << id
             << ", Salary: " << calculateSalary() << endl;
    }

    double getSalary() const { return calculateSalary(); }
};

// --------------------------
// Derived Classes
// --------------------------
class Manager : public Employee {
    double baseSalary;
    double bonusRate; // e.g., 0.1 for 10%
public:
    Manager(const string& n, int i, double salary, double bonus)
        : Employee(n, i), baseSalary(salary), bonusRate(bonus) {}

    double calculateSalary() const override {
        return baseSalary + baseSalary * bonusRate;
    }
};

class Engineer : public Employee {
    double baseSalary;
    int overtimeHours;
    double overtimeRate;
public:
    Engineer(const string& n, int i, double salary, int hours, double rate)
        : Employee(n, i), baseSalary(salary), overtimeHours(hours), overtimeRate(rate) {}

    double calculateSalary() const override {
        return baseSalary + overtimeHours * overtimeRate;
    }
};

class Intern : public Employee {
    double stipend;
public:
    Intern(const string& n, int i, double s)
        : Employee(n, i), stipend(s) {}

    double calculateSalary() const override { return stipend; }
};

// --------------------------
// Payroll System
// --------------------------
class PayrollSystem {
    vector<shared_ptr<Employee>> employees;
public:
    void addEmployee(shared_ptr<Employee> emp) {
        employees.push_back(emp);
    }

    void printPayroll() const {
        for (auto& e : employees) e->print();
    }

    double totalSalary() const {
        double total = 0;
        for (auto& e : employees) total += e->getSalary();
        return total;
    }

    shared_ptr<Employee> findHighestPaid() const {
        if (employees.empty()) throw runtime_error("No employees");
        return *max_element(employees.begin(), employees.end(),
                            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b){
                                return a->getSalary() < b->getSalary();
                            });
    }
};

// --------------------------
// Main Demonstration
// --------------------------
int main() {
    PayrollSystem payroll;

    auto m = make_shared<Manager>("Alice", 1001, 80000, 0.1);
    auto e = make_shared<Engineer>("Bob", 1002, 60000, 10, 50);
    auto i = make_shared<Intern>("Charlie", 1003, 1500);

    payroll.addEmployee(m);
    payroll.addEmployee(e);
    payroll.addEmployee(i);

    payroll.printPayroll();
    cout << "Total Salary: " << payroll.totalSalary() << endl;

    auto highest = payroll.findHighestPaid();
    cout << "Highest Paid: " << highest->getSalary() << endl;

    return 0;
}
/* 
Expected Output
Employee: Alice, ID: 1001, Salary: 88000
Employee: Bob, ID: 1002, Salary: 60500
Employee: Charlie, ID: 1003, Salary: 1500
Total Salary: 150000
Highest Paid: 88000
*/
/*================================================================================*/

/* 
5 — Media Player System

Problem Statement:
Implement Media (base), Audio, Video with virtual play(), pause(), stop().

MediaLibrary stores std::vector<std::shared_ptr<Media>>

Print details: name, duration, type

Sample Input:

MediaLibrary library;
auto a = std::make_shared<Audio>("Song1", 180);
auto v = std::make_shared<Video>("Movie1", 7200);
library.addMedia(a);
library.addMedia(v);
library.playAll();


Expected Output:

Playing Audio: Song1, Duration: 180
Playing Video: Movie1, Duration: 7200
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// --------------------------
// Base Class: Media
// --------------------------
class Media {
protected:
    string name;
    int duration; // in seconds
public:
    Media(const string& n, int d) : name(n), duration(d) {}
    virtual ~Media() = default;

    virtual void play() const = 0;
    virtual void pause() const = 0;
    virtual void stop() const = 0;
};

// --------------------------
// Derived Classes
// --------------------------
class Audio : public Media {
public:
    Audio(const string& n, int d) : Media(n, d) {}

    void play() const override {
        cout << "Playing Audio: " << name << ", Duration: " << duration << endl;
    }
    void pause() const override {
        cout << "Pausing Audio: " << name << endl;
    }
    void stop() const override {
        cout << "Stopping Audio: " << name << endl;
    }
};

class Video : public Media {
public:
    Video(const string& n, int d) : Media(n, d) {}

    void play() const override {
        cout << "Playing Video: " << name << ", Duration: " << duration << endl;
    }
    void pause() const override {
        cout << "Pausing Video: " << name << endl;
    }
    void stop() const override {
        cout << "Stopping Video: " << name << endl;
    }
};

// --------------------------
// Media Library
// --------------------------
class MediaLibrary {
    vector<shared_ptr<Media>> mediaList;
public:
    void addMedia(shared_ptr<Media> m) {
        mediaList.push_back(m);
    }

    void playAll() const {
        for (auto& m : mediaList) m->play();
    }
};

// --------------------------
// Main Demonstration
// --------------------------
int main() {
    MediaLibrary library;

    auto a = make_shared<Audio>("Song1", 180);
    auto v = make_shared<Video>("Movie1", 7200);

    library.addMedia(a);
    library.addMedia(v);

    library.playAll();

    return 0;
}
/* 
Expected Output
Playing Audio: Song1, Duration: 180
Playing Video: Movie1, Duration: 7200
*/

/*================================================================================*/
/* 
6 — Library Management System

Problem Statement:
Implement Book, Member, Library with:

borrowBook(memberID, bookID), returnBook()

printAllBooks(), printMemberDetails()

Use std::vector + smart pointers

Sample Input:

Library lib;
auto book1 = std::make_shared<Book>("C++ Primer", 101);
auto member1 = std::make_shared<Member>("Alice", 1);
lib.addBook(book1);
lib.addMember(member1);
lib.borrowBook(1, 101);
lib.printAllBooks();
lib.printMemberDetails(1);


Expected Output:

Book: C++ Primer, ID: 101, Status: Borrowed
Member: Alice, ID: 1, Borrowed Books: 101
*/

//Library Management System
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

// --------------------------
// Book Class
// --------------------------
class Book {
    int id;
    string title;
    bool isBorrowed;
public:
    Book(const string& t, int i) : title(t), id(i), isBorrowed(false) {}

    int getID() const { return id; }
    string getTitle() const { return title; }
    bool borrowed() const { return isBorrowed; }

    void borrow() { isBorrowed = true; }
    void returned() { isBorrowed = false; }

    void print() const {
        cout << "Book: " << title << ", ID: " << id
             << ", Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
    }
};

// --------------------------
// Member Class
// --------------------------
class Member {
    int id;
    string name;
    vector<int> borrowedBooks; // store book IDs
public:
    Member(const string& n, int i) : name(n), id(i) {}

    int getID() const { return id; }
    string getName() const { return name; }

    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
    }

    void returnBook(int bookID) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookID),
                            borrowedBooks.end());
    }

    void print() const {
        cout << "Member: " << name << ", ID: " << id << ", Borrowed Books: ";
        if (borrowedBooks.empty())
            cout << "None";
        else
            for (int b : borrowedBooks) cout << b << " ";
        cout << endl;
    }

    bool hasBorrowed(int bookID) const {
        return find(borrowedBooks.begin(), borrowedBooks.end(), bookID) != borrowedBooks.end();
    }
};

// --------------------------
// Library Class
// --------------------------
class Library {
    vector<shared_ptr<Book>> books;
    vector<shared_ptr<Member>> members;

public:
    void addBook(shared_ptr<Book> b) { books.push_back(b); }
    void addMember(shared_ptr<Member> m) { members.push_back(m); }

    void borrowBook(int memberID, int bookID) {
        auto mIt = find_if(members.begin(), members.end(),
                           [memberID](const shared_ptr<Member>& m){ return m->getID() == memberID; });
        auto bIt = find_if(books.begin(), books.end(),
                           [bookID](const shared_ptr<Book>& b){ return b->getID() == bookID; });
        if (mIt != members.end() && bIt != books.end()) {
            if (!(*bIt)->borrowed()) {
                (*bIt)->borrow();
                (*mIt)->borrowBook(bookID);
            } else {
                cout << "Book already borrowed.\n";
            }
        } else {
            cout << "Member or Book not found.\n";
        }
    }

    void returnBook(int memberID, int bookID) {
        auto mIt = find_if(members.begin(), members.end(),
                           [memberID](const shared_ptr<Member>& m){ return m->getID() == memberID; });
        auto bIt = find_if(books.begin(), books.end(),
                           [bookID](const shared_ptr<Book>& b){ return b->getID() == bookID; });
        if (mIt != members.end() && bIt != books.end()) {
            if ((*mIt)->hasBorrowed(bookID)) {
                (*bIt)->returned();
                (*mIt)->returnBook(bookID);
            } else {
                cout << "Member did not borrow this book.\n";
            }
        } else {
            cout << "Member or Book not found.\n";
        }
    }

    void printAllBooks() const {
        for (auto& b : books) b->print();
    }

    void printMemberDetails(int memberID) const {
        auto mIt = find_if(members.begin(), members.end(),
                           [memberID](const shared_ptr<Member>& m){ return m->getID() == memberID; });
        if (mIt != members.end())
            (*mIt)->print();
        else
            cout << "Member not found.\n";
    }
};

// --------------------------
// Main Demonstration
// --------------------------
int main() {
    Library lib;

    auto book1 = make_shared<Book>("C++ Primer", 101);
    auto member1 = make_shared<Member>("Alice", 1);

    lib.addBook(book1);
    lib.addMember(member1);

    lib.borrowBook(1, 101);

    lib.printAllBooks();
    lib.printMemberDetails(1);

    return 0;
}
/* 
Expected Output
Book: C++ Primer, ID: 101, Status: Borrowed
Member: Alice, ID: 1, Borrowed Books: 101
*/



/*================================================================================*/

/* 
7 — Unique Pointer Implementation (UniquePtr<T>)

Problem Statement:
Implement UniquePtr<T> supporting:

Move constructor and assignment

Dereference * and ->

Automatic deletion in destructor

Sample Input:

UniquePtr<int> p1(new int(10));
cout << *p1 << endl;
UniquePtr<int> p2 = std::move(p1);


Expected Output:

10
*/

//Unique Pointer Implementation
#include <iostream>
#include <utility> // for std::move
using namespace std;

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~UniquePtr() { delete ptr; }

    // Move Constructor
    UniquePtr(UniquePtr&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // Move Assignment
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;       // delete current resource
            ptr = other.ptr;  // take ownership
            other.ptr = nullptr;
        }
        return *this;
    }

    // Delete copy constructor and copy assignment
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Dereference operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Access raw pointer
    T* get() const { return ptr; }

    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Reset pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    // Check if pointer is non-null
    operator bool() const { return ptr != nullptr; }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    UniquePtr<int> p1(new int(10));
    cout << *p1 << endl;

    UniquePtr<int> p2 = std::move(p1); // transfer ownership

    if (!p1) cout << "p1 is now null" << endl;
    cout << *p2 << endl;

    return 0;
}
/* 
Expected Output
10
p1 is now null
10
*/


/*================================================================================*/

/* 
8 — LRU Cache (LRUCache<Key, Value>)

Problem Statement:
Implement a template LRU cache:

put(key, value), get(key)

Maintain capacity

Use std::unordered_map + std::list

printCache() for debugging

Sample Input:

LRUCache<int, string> cache(3);
cache.put(1, "A");
cache.put(2, "B");
cache.put(3, "C");
cache.get(2);
cache.put(4, "D");
cache.printCache();


Expected Output:

4:D 2:B 3:C
*/


#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

template <typename Key, typename Value>
class LRUCache {
private:
    size_t capacity;
    list<pair<Key, Value>> cacheList; // front = most recent
    unordered_map<Key, typename list<pair<Key, Value>>::iterator> cacheMap;

public:
    LRUCache(size_t cap) : capacity(cap) {}

    // Get value by key
    Value get(const Key& key) {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
            throw runtime_error("Key not found");

        // Move accessed node to front
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second;
    }

    // Put key-value into cache
    void put(const Key& key, const Value& value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // Key exists: update value and move to front
            it->second->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it->second);
        } else {
            // Key not present
            if (cacheList.size() == capacity) {
                // Evict least recently used
                auto last = cacheList.back();
                cacheMap.erase(last.first);
                cacheList.pop_back();
            }
            cacheList.push_front({key, value});
            cacheMap[key] = cacheList.begin();
        }
    }

    void printCache() const {
        for (auto& kv : cacheList) {
            cout << kv.first << ":" << kv.second << " ";
        }
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    LRUCache<int, string> cache(3);

    cache.put(1, "A");
    cache.put(2, "B");
    cache.put(3, "C");

    cache.get(2);       // Access 2 -> moves to front
    cache.put(4, "D");  // Evicts LRU (1)

    cache.printCache(); // Expected: 4:D 2:B 3:C

    return 0;
}
/* 
Expected Output
4:D 2:B 3:C
*/

/*================================================================================*/

/* 
9 — Custom Stack

Problem Statement:
Implement Stack<T> with:

push(), pop(), top(), size()

Throw exception on empty pop() or top()

Support range-based iteration

Sample Input:

Stack<int> s;
s.push(10);
s.push(20);
cout << s.top() << endl;
s.pop();
s.printAll();


Expected Output:

20
10
*/

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    vector<T> data;

public:
    Stack() = default;

    void push(const T& val) {
        data.push_back(val);
    }

    void pop() {
        if (data.empty())
            throw runtime_error("Stack is empty");
        data.pop_back();
    }

    T& top() {
        if (data.empty())
            throw runtime_error("Stack is empty");
        return data.back();
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    // Range-based iteration
    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin(); }
    typename vector<T>::const_iterator end() const { return data.end(); }

    // Print all elements (bottom -> top)
    void printAll() const {
        for (const auto& x : data)
            cout << x << " ";
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    Stack<int> s;

    s.push(10);
    s.push(20);

    cout << s.top() << endl; // 20
    s.pop();
    s.printAll();             // 10

    // Using range-based for
    s.push(30);
    s.push(40);
    cout << "Stack elements: ";
    for (auto& x : s) cout << x << " ";
    cout << endl;

    return 0;
}
/* 
Expected Output
20
10
Stack elements: 10 30 40
*/

/*================================================================================*/
/* 
10 — Custom Queue

Problem Statement:
Implement Queue<T> with:

enqueue(), dequeue(), front(), size()

Exception safety

Iterators for range-based loops

Sample Input:

Queue<int> q;
q.enqueue(1);
q.enqueue(2);
cout << q.front() << endl;
q.dequeue();
q.printAll();


Expected Output:

1
2
*/

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    vector<T> data;
    size_t head = 0;  // index of front element

public:
    Queue() = default;

    void enqueue(const T& val) {
        data.push_back(val);
    }

    void dequeue() {
        if (empty())
            throw runtime_error("Queue is empty");
        ++head;
        // Optional: reclaim memory if too much unused front space
        if (head > data.size() / 2) {
            data.erase(data.begin(), data.begin() + head);
            head = 0;
        }
    }

    T& front() {
        if (empty())
            throw runtime_error("Queue is empty");
        return data[head];
    }

    size_t size() const {
        return data.size() - head;
    }

    bool empty() const {
        return size() == 0;
    }

    // Iterators for range-based loops
    typename vector<T>::iterator begin() { return data.begin() + head; }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin() + head; }
    typename vector<T>::const_iterator end() const { return data.end(); }

    // Print all elements
    void printAll() const {
        for (size_t i = head; i < data.size(); ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);

    cout << q.front() << endl; // 1
    q.dequeue();
    q.printAll();               // 2

    q.enqueue(3);
    q.enqueue(4);

    cout << "Queue elements: ";
    for (auto& x : q) cout << x << " ";
    cout << endl;

    return 0;
}
/* 
Expected Output
1
2
Queue elements: 2 3 4
*/



/*================================================================================*/

/* 
11 — Matrix Class (Matrix<T>)

Problem Statement:
Implement Matrix<T> class with:

2D array storage, rows(), cols()

Operator +, *, ==

print()

Iterators for row-wise iteration

Sample Input:

Matrix<int> m1(2,2);
Matrix<int> m2(2,2);
m1.fill(1); m2.fill(2);
Matrix<int> m3 = m1 + m2;
m3.print();


Expected Output:

3 3
3 3
*/


#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Matrix {
private:
    size_t m_rows, m_cols;
    vector<T> data;  // flat storage: row-major

public:
    Matrix(size_t rows, size_t cols)
        : m_rows(rows), m_cols(cols), data(rows*cols) {}

    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    // Element access (0-based indexing)
    T& operator()(size_t r, size_t c) {
        if (r >= m_rows || c >= m_cols)
            throw out_of_range("Index out of bounds");
        return data[r*m_cols + c];
    }

    const T& operator()(size_t r, size_t c) const {
        if (r >= m_rows || c >= m_cols)
            throw out_of_range("Index out of bounds");
        return data[r*m_cols + c];
    }

    // Fill all elements with a value
    void fill(const T& val) {
        std::fill(data.begin(), data.end(), val);
    }

    // Print matrix
    void print() const {
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_cols; ++j)
                cout << operator()(i,j) << " ";
            cout << endl;
        }
    }

    // Operator +
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols)
            throw runtime_error("Matrix dimensions must match for addition");
        Matrix<T> result(m_rows, m_cols);
        for (size_t i = 0; i < data.size(); ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Operator * (matrix multiplication)
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (m_cols != other.m_rows)
            throw runtime_error("Matrix dimensions mismatch for multiplication");
        Matrix<T> result(m_rows, other.m_cols);
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < other.m_cols; ++j) {
                T sum = 0;
                for (size_t k = 0; k < m_cols; ++k)
                    sum += operator()(i,k) * other(k,j);
                result(i,j) = sum;
            }
        }
        return result;
    }

    // Operator ==
    bool operator==(const Matrix<T>& other) const {
        return m_rows == other.m_rows && m_cols == other.m_cols && data == other.data;
    }

    // Iterators (row-wise)
    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin(); }
    typename vector<T>::const_iterator end() const { return data.end(); }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    Matrix<int> m1(2,2);
    Matrix<int> m2(2,2);

    m1.fill(1);
    m2.fill(2);

    Matrix<int> m3 = m1 + m2;

    cout << "Matrix m3:" << endl;
    m3.print();  // Expected output: 3 3 / 3 3

    // Optional: multiplication example
    Matrix<int> m4(2,2);
    m4(0,0)=1; m4(0,1)=2;
    m4(1,0)=3; m4(1,1)=4;

    Matrix<int> m5(2,2);
    m5(0,0)=5; m5(0,1)=6;
    m5(1,0)=7; m5(1,1)=8;

    cout << "Matrix m4 * m5:" << endl;
    Matrix<int> m6 = m4 * m5;
    m6.print(); // Expected: 19 22 / 43 50

    return 0;
}
/* 
Expected Output
Matrix m3:
3 3
3 3
Matrix m4 * m5:
19 22
43 50
*/

/*================================================================================*/
/* 
12 — BitSet Specialization (BitSet<N>)

Problem Statement:
Implement a BitSet<N> class using uint64_t to store bits:

set(pos, bool), get(pos)

flip(pos)

printBits()

Sample Input:

BitSet<10> b;
b.set(2,true);
b.set(7,true);
b.flip(2);
b.printBits();


Expected Output:

0000000010
*/

#include <iostream>
#include <stdexcept>
#include <cstdint>
using namespace std;

template <size_t N>
class BitSet {
private:
    static_assert(N <= 64, "BitSet<N> supports up to 64 bits.");
    uint64_t bits = 0;

public:
    // Set bit at position pos (0-based)
    void set(size_t pos, bool val = true) {
        if (pos >= N) throw out_of_range("Bit position out of range");
        if (val)
            bits |= (uint64_t(1) << pos);
        else
            bits &= ~(uint64_t(1) << pos);
    }

    // Get bit value at position pos
    bool get(size_t pos) const {
        if (pos >= N) throw out_of_range("Bit position out of range");
        return (bits >> pos) & 1ULL;
    }

    // Flip bit at position pos
    void flip(size_t pos) {
        if (pos >= N) throw out_of_range("Bit position out of range");
        bits ^= (uint64_t(1) << pos);
    }

    // Print bits as string (MSB left)
    void printBits() const {
        for (int i = N-1; i >= 0; --i)
            cout << get(i);
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    BitSet<10> b;
    b.set(2, true);
    b.set(7, true);
    b.flip(2);

    b.printBits(); // Expected: 0000000010

    // Check get
    for (size_t i = 0; i < 10; ++i)
        cout << b.get(i) << " ";
    cout << endl;

    return 0;
}
/* 
Expected Output
0000000010
0 0 0 0 0 0 0 1 0 0 
*/

/*================================================================================*/
/* 
13 — Observer Pattern (EventNotifier)
Problem Statement:
Implement EventNotifier with:
subscribe(callback), notify()
Support multiple subscribers using std::function<void()>

Sample Input:
EventNotifier notifier;
notifier.subscribe([](){ cout << "Event 1\n"; });
notifier.subscribe([](){ cout << "Event 2\n"; });
notifier.notify();


Expected Output:
Event 1
Event 2
*/
//Observer Pattern (EventNotifier)
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class EventNotifier {
private:
    vector<std::function<void()>> subscribers;

public:
    // Subscribe a new callback
    void subscribe(const std::function<void()>& callback) {
        subscribers.push_back(callback);
    }

    // Notify all subscribers
    void notify() {
        for (auto& cb : subscribers) {
            try {
                cb();
            } catch (const std::exception& e) {
                cerr << "Subscriber exception: " << e.what() << endl;
            } catch (...) {
                cerr << "Subscriber threw unknown exception" << endl;
            }
        }
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    EventNotifier notifier;

    notifier.subscribe([](){ cout << "Event 1\n"; });
    notifier.subscribe([](){ cout << "Event 2\n"; });

    notifier.notify(); // Expected: Event 1 / Event 2

    return 0;
}
/* 
Expected Output
Event 1
Event 2
*/


/*================================================================================*/

/* 
14 — File Serialization of Objects

Problem Statement:
Implement class Person with:

save(filename) writes object to file

load(filename) reads object from file

Support name, age, id

Sample Input:

Person p("Alice", 30, 101);
p.save("person.txt");
Person q;
q.load("person.txt");
q.print();


Expected Output:

Name: Alice, Age: 30, ID: 101
*/
//File Serialization of Objects (Person)
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class Person {
private:
    string name;
    int age;
    int id;

public:
    // Constructors
    Person() : name(""), age(0), id(0) {}
    Person(const string& n, int a, int i) : name(n), age(a), id(i) {}

    // Save to file
    void save(const string& filename) const {
        ofstream out(filename);
        if (!out) throw runtime_error("Cannot open file for writing");
        out << name << "\n" << age << "\n" << id << "\n";
    }

    // Load from file
    void load(const string& filename) {
        ifstream in(filename);
        if (!in) throw runtime_error("Cannot open file for reading");
        getline(in, name);
        in >> age >> id;
        in.ignore(); // consume remaining newline
    }

    // Print details
    void print() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    try {
        Person p("Alice", 30, 101);
        p.save("person.txt");

        Person q;
        q.load("person.txt");
        q.print();  // Expected: Name: Alice, Age: 30, ID: 101
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
/* 
Expected Output
Name: Alice, Age: 30, ID: 101
*/

/*================================================================================*/
/* 
15 — Graph Class (Graph)

Problem Statement:
Implement template Graph<T> with:

addEdge(u,v), printGraph()

BFS, DFS traversal

Use adjacency list

Sample Input:

Graph<int> g;
g.addEdge(1,2);
g.addEdge(2,3);
g.printGraph();


Expected Output:

1 -> 2
2 -> 3
3 ->
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

template <typename T>
class Graph {
private:
    unordered_map<T, vector<T>> adj;

public:
    // Add directed edge u -> v
    void addEdge(const T& u, const T& v) {
        adj[u].push_back(v);
        if (adj.find(v) == adj.end()) adj[v] = {}; // Ensure v exists in map
    }

    // Print adjacency list
    void printGraph() const {
        for (const auto& [node, neighbors] : adj) {
            cout << node << " -> ";
            for (const auto& n : neighbors) cout << n << " ";
            cout << endl;
        }
    }

    // BFS traversal from start
    void BFS(const T& start) const {
        unordered_set<T> visited;
        queue<T> q;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            T node = q.front(); q.pop();
            cout << node << " ";
            for (auto& n : adj.at(node)) {
                if (!visited.count(n)) {
                    visited.insert(n);
                    q.push(n);
                }
            }
        }
        cout << endl;
    }

    // DFS traversal from start
    void DFS(const T& start) const {
        unordered_set<T> visited;
        stack<T> s;
        s.push(start);

        while (!s.empty()) {
            T node = s.top(); s.pop();
            if (!visited.count(node)) {
                visited.insert(node);
                cout << node << " ";
                // push neighbors in reverse for natural order
                for (auto it = adj.at(node).rbegin(); it != adj.at(node).rend(); ++it)
                    if (!visited.count(*it))
                        s.push(*it);
            }
        }
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    Graph<int> g;
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(1,3);

    cout << "Adjacency List:\n";
    g.printGraph(); 
    // Expected:
    // 1 -> 2 3
    // 2 -> 3
    // 3 ->

    cout << "BFS from 1: ";
    g.BFS(1); // Expected: 1 2 3

    cout << "DFS from 1: ";
    g.DFS(1); // Expected: 1 2 3 (order may vary depending on neighbor order)

    return 0;
}
/* 
Expected Output
Adjacency List:
1 -> 2 3
2 -> 3
3 -> 
BFS from 1: 1 2 3
DFS from 1: 1 2 3
*/





/*================================================================================*/
/* 
16 — Binary Search Tree (BST<T>)

Problem Statement:
Implement BST<T> with:

insert(), search(), inOrderTraversal()

Support numeric-only sum(), max(), min()

Sample Input:

BST<int> tree;
tree.insert(5); tree.insert(3); tree.insert(7);
tree.inOrderTraversal();
cout << tree.sum() << endl;


Expected Output:

3 5 7
15
*/

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper recursive functions
    void insert(Node*& node, T val) {
        if (!node) node = new Node(val);
        else if (val < node->data) insert(node->left, val);
        else insert(node->right, val);
    }

    bool search(Node* node, T val) const {
        if (!node) return false;
        if (node->data == val) return true;
        else if (val < node->data) return search(node->left, val);
        else return search(node->right, val);
    }

    void inOrderTraversal(Node* node) const {
        if (!node) return;
        inOrderTraversal(node->left);
        cout << node->data << " ";
        inOrderTraversal(node->right);
    }

    T sum(Node* node) const {
        if (!node) return T(0);
        return node->data + sum(node->left) + sum(node->right);
    }

    T max(Node* node) const {
        if (!node) throw runtime_error("Tree is empty");
        while (node->right) node = node->right;
        return node->data;
    }

    T min(Node* node) const {
        if (!node) throw runtime_error("Tree is empty");
        while (node->left) node = node->left;
        return node->data;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(T val) { insert(root, val); }
    bool search(T val) const { return search(root, val); }
    void inOrderTraversal() const { inOrderTraversal(root); cout << endl; }

    T sum() const { return sum(root); }
    T max() const { return max(root); }
    T min() const { return min(root); }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    cout << "In-order traversal: ";
    tree.inOrderTraversal();  // Expected: 3 5 7

    cout << "Sum: " << tree.sum() << endl;  // Expected: 15
    cout << "Max: " << tree.max() << endl;  // Expected: 7
    cout << "Min: " << tree.min() << endl;  // Expected: 3

    return 0;
}
/* 
Expected Output
In-order traversal: 3 5 7
Sum: 15
Max: 7
Min: 3
*/




/*================================================================================*/
/* 
17 — Smart Pointer Array (SmartArray<T,N>)

Problem Statement:
Implement SmartArray<T,N> using std::unique_ptr<T[]>:

operator[], fill(), printAll()

Sample Input:

SmartArray<int,5> arr;
arr.fill(10);
arr[2] = 20;
arr.printAll();


Expected Output:

10 10 20 10 10

*/
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class SmartArray {
private:
    unique_ptr<T[]> data;

public:
    SmartArray() : data(make_unique<T[]>(N)) {}

    // Access with bounds checking
    T& operator[](size_t idx) {
        if (idx >= N) throw out_of_range("Index out of bounds");
        return data[idx];
    }

    const T& operator[](size_t idx) const {
        if (idx >= N) throw out_of_range("Index out of bounds");
        return data[idx];
    }

    // Fill array with value
    void fill(const T& val) {
        for (size_t i = 0; i < N; ++i) data[i] = val;
    }

    // Print all elements
    void printAll() const {
        for (size_t i = 0; i < N; ++i)
            cout << data[i] << " ";
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    SmartArray<int, 5> arr;
    arr.fill(10);
    arr[2] = 20;
    arr.printAll();  // Expected: 10 10 20 10 10

    return 0;
}
/* 
Expected Output
10 10 20 10 10


Uses std::unique_ptr<T[]> → automatically frees memory when the array goes out of scope.
operator[] checks bounds to prevent invalid access.
*/


/*================================================================================*/
/* 
18 — Multi-level Employee Hierarchy

Problem Statement:
Extend Employee system:

Departments with Manager, Lead, Engineer

Department class stores employees, prints payroll per department

Sample Input:

Department d("IT");
d.addEmployee(std::make_shared<Manager>("Alice",1001,80000,0.1));
d.printPayroll();


Expected Output:

Employee: Alice, ID:1001, Salary:88000
*/


#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// --------------------------
// Employee hierarchy
// --------------------------
class Employee {
protected:
    string name;
    int id;
public:
    Employee(const string& n, int i) : name(n), id(i) {}
    virtual ~Employee() = default;
    virtual double calculateSalary() const = 0;
    virtual void print() const {
        cout << "Employee: " << name << ", ID:" << id 
             << ", Salary: " << calculateSalary() << endl;
    }
};

class Manager : public Employee {
    double baseSalary;
    double bonusPercent;
public:
    Manager(const string& n, int i, double salary, double bonus)
        : Employee(n,i), baseSalary(salary), bonusPercent(bonus) {}
    double calculateSalary() const override {
        return baseSalary + baseSalary * bonusPercent;
    }
};

// Example other employee types
class Engineer : public Employee {
    double baseSalary;
    int overtimeHours;
    double ratePerHour;
public:
    Engineer(const string& n, int i, double salary, int hours, double rate)
        : Employee(n,i), baseSalary(salary), overtimeHours(hours), ratePerHour(rate) {}
    double calculateSalary() const override {
        return baseSalary + overtimeHours * ratePerHour;
    }
};

class Intern : public Employee {
    double stipend;
public:
    Intern(const string& n, int i, double s) : Employee(n,i), stipend(s) {}
    double calculateSalary() const override { return stipend; }
};

// --------------------------
// Department class
// --------------------------
class Department {
    string deptName;
    vector<shared_ptr<Employee>> employees;
public:
    Department(const string& name) : deptName(name) {}

    void addEmployee(shared_ptr<Employee> emp) {
        employees.push_back(emp);
    }

    void printPayroll() const {
        cout << "Department: " << deptName << endl;
        for (auto& emp : employees) {
            emp->print();
        }
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    Department d("IT");
    d.addEmployee(make_shared<Manager>("Alice",1001,80000,0.1));
    d.addEmployee(make_shared<Engineer>("Bob",1002,60000,10,50));
    d.addEmployee(make_shared<Intern>("Charlie",1003,1500));

    d.printPayroll();

    return 0;
}
/* 
Expected Output
Department: IT
Employee: Alice, ID:1001, Salary:88000
Employee: Bob, ID:1002, Salary:60500
Employee: Charlie, ID:1003, Salary:1500


Each department maintains its own employee list.
Supports multiple employee types with polymorphic calculateSalary().
Printing payroll iterates over employees and prints calculated salaries.
*/

/*================================================================================*/
/* 
19 — Smart Pointer Graph

Problem Statement:
Implement Node<T> with children using std::shared_ptr<Node<T>>

DFS traversal prints values

Sample Input:

auto root = std::make_shared<Node<int>>(1);
root->addChild(2); root->addChild(3);
root->dfs();


Expected Output:

1 2 3
*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template <typename T>
class Node {
    T value;
    vector<shared_ptr<Node<T>>> children;

public:
    Node(T val) : value(val) {}

    // Add child with value
    void addChild(T val) {
        children.push_back(make_shared<Node<T>>(val));
    }

    // DFS traversal
    void dfs() const {
        cout << value << " ";
        for (auto& child : children) {
            child->dfs();
        }
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    auto root = make_shared<Node<int>>(1);
    root->addChild(2);
    root->addChild(3);

    cout << "DFS traversal: ";
    root->dfs();  // Expected: 1 2 3
    cout << endl;

    return 0;
}
/* 
Expected Output
DFS traversal: 1 2 3


Each node maintains its children using std::shared_ptr.
Automatic memory management via smart pointers; no manual delete needed.
DFS is implemented recursively.
*/


/*================================================================================*/
/*  
20 — Custom Map (MyMap<Key,Value>)
Problem Statement:
Implement a hash map with:

insert(), get(), remove()

Use separate chaining with std::list

Support iteration

Sample Input:

MyMap<int,string> map;
map.insert(1,"A"); map.insert(2,"B");
cout << map.get(2) << endl;


Expected Output:
B
*/

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
using namespace std;

template <typename Key, typename Value>
class MyMap {
    static const size_t BUCKETS = 10;
    vector<list<pair<Key, Value>>> table;

    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % BUCKETS;
    }

public:
    MyMap() : table(BUCKETS) {}

    void insert(const Key& key, const Value& val) {
        size_t idx = hash(key);
        for (auto& p : table[idx]) {
            if (p.first == key) {
                p.second = val; // update existing
                return;
            }
        }
        table[idx].push_back({key, val});
    }

    Value get(const Key& key) const {
        size_t idx = hash(key);
        for (const auto& p : table[idx]) {
            if (p.first == key) return p.second;
        }
        throw runtime_error("Key not found");
    }

    void remove(const Key& key) {
        size_t idx = hash(key);
        auto& chain = table[idx];
        chain.remove_if([&](const pair<Key, Value>& p){ return p.first == key; });
    }

    void printAll() const {
        for (size_t i = 0; i < BUCKETS; ++i) {
            for (const auto& p : table[i]) {
                cout << p.first << " : " << p.second << " | ";
            }
        }
        cout << endl;
    }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    MyMap<int, string> map;
    map.insert(1, "A");
    map.insert(2, "B");
    map.insert(3, "C");

    cout << "Value for key 2: " << map.get(2) << endl;

    map.remove(2);
    map.printAll();

    return 0;
}
/* 
Expected Output
Value for key 2: B
1 : A | 3 : C | 


Separate chaining handles collisions using std::list.
insert() updates existing keys.
get() throws if key not found.
remove() deletes key from chain.
printAll() iterates all buckets.
*/


/*================================================================================*/

/* 
21 — Custom Set (MySet<T>)

Problem Statement:
Implement a set with:

insert(), remove(), contains()

Use std::vector internally

Iterators for range-based loops

Sample Input:

MySet<int> s;
s.insert(1); s.insert(2); s.insert(1);
for(auto x:s) cout << x << " ";


Expected Output:

1 2
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T>
class MySet {
    vector<T> data;

public:
    MySet() = default;

    // Insert if not present
    void insert(const T& val) {
        if (!contains(val))
            data.push_back(val);
    }

    // Remove element if present
    void remove(const T& val) {
        data.erase(remove(data.begin(), data.end(), val), data.end());
    }

    // Check if element exists
    bool contains(const T& val) const {
        return find(data.begin(), data.end(), val) != data.end();
    }

    // Size of set
    size_t size() const { return data.size(); }

    // Range-based loop support
    typename vector<T>::iterator begin() { return data.begin(); }
    typename vector<T>::iterator end() { return data.end(); }
    typename vector<T>::const_iterator begin() const { return data.begin(); }
    typename vector<T>::const_iterator end() const { return data.end(); }
};

// --------------------------
// Demonstration
// --------------------------
int main() {
    MySet<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(1); // duplicate ignored

    cout << "Set elements: ";
    for (auto x : s) cout << x << " ";
    cout << endl;

    s.remove(2);
    cout << "After removing 2: ";
    for (auto x : s) cout << x << " ";
    cout << endl;

    cout << "Contains 1? " << (s.contains(1) ? "Yes" : "No") << endl;
    cout << "Contains 2? " << (s.contains(2) ? "Yes" : "No") << endl;

    return 0;
}
/* 
Expected Output
Set elements: 1 2
After removing 2: 1
Contains 1? Yes
Contains 2? No


Uses std::vector internally for simplicity.
insert() prevents duplicates.
Supports range-based for loops via begin() / end().
remove() deletes element if exists.
*/

/*================================================================================*/
/* 
22 — Move-only Resource (FileHandle)

Problem Statement:
Implement class FileHandle:

Move-only, no copy

Opens file in constructor, closes in destructor

Sample Input:

FileHandle f1("test.txt");
FileHandle f2 = std::move(f1);


Expected Output:
(No output; ensures resource ownership is moved correctly)
*/


#include <iostream>
#include <fstream>
#include <string>

class FileHandle {
    std::fstream file;
    std::string filename;

public:
    // Constructor opens file
    explicit FileHandle(const std::string& fname) : filename(fname), file(fname, std::ios::in | std::ios::out | std::ios::app) {
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + fname);
        }
        std::cout << "Opened file: " << fname << std::endl;
    }

    // Delete copy constructor and copy assignment
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    // Move constructor
    FileHandle(FileHandle&& other) noexcept : file(std::move(other.file)), filename(std::move(other.filename)) {
        other.filename.clear();
    }

    // Move assignment
    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) {
            file.close();
            file = std::move(other.file);
            filename = std::move(other.filename);
            other.filename.clear();
        }
        return *this;
    }

    // Destructor closes file
    ~FileHandle() {
        if (file.is_open()) {
            file.close();
            if (!filename.empty())
                std::cout << "Closed file: " << filename << std::endl;
        }
    }

    // Write to file
    void writeLine(const std::string& line) {
        if (file.is_open()) {
            file << line << std::endl;
        }
    }

    // Read from file (optional)
    void readAll() {
        if (!file.is_open()) return;
        file.seekg(0);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }
};

// ------------------------
// Demonstration
// ------------------------
int main() {
    try {
        FileHandle f1("test.txt");
        f1.writeLine("Hello");

        // Move ownership
        FileHandle f2 = std::move(f1);
        f2.writeLine("World");

        // f1 can no longer be used (ownership moved)
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
/* 
Explanation / Output
Constructor opens the file.
Copying is deleted; moving transfers ownership.
Destructor automatically closes the file.

Sample run output:
Opened file: test.txt
Closed file: test.txt


f1 is invalid after std::move(f1); f2 now owns the file.
Ensures RAII and move-only resource management.
*/


/*================================================================================*/

/* 
23 — Numeric Algorithms Container

Problem Statement:
Template container NumContainer<T> supports:

add(), remove()

sum(), average(), max(), min()

Range-based iteration

Sample Input:

NumContainer<int> c;
c.add(1); c.add(2); c.add(3);
cout << c.sum() << " " << c.max() << endl;


Expected Output:

6 3
*/

//Numeric Algorithms Container (NumContainer<T>)
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class NumContainer {
private:
    std::vector<T> data;

public:
    // Add element
    void add(const T& value) {
        data.push_back(value);
    }

    // Remove element (first occurrence)
    void remove(const T& value) {
        auto it = std::find(data.begin(), data.end(), value);
        if (it != data.end())
            data.erase(it);
    }

    // Sum of elements
    T sum() const {
        T s = T{};
        for (const auto& val : data) s += val;
        return s;
    }

    // Average of elements
    double average() const {
        if (data.empty()) throw std::runtime_error("Container is empty");
        return static_cast<double>(sum()) / data.size();
    }

    // Maximum element
    T max() const {
        if (data.empty()) throw std::runtime_error("Container is empty");
        return *std::max_element(data.begin(), data.end());
    }

    // Minimum element
    T min() const {
        if (data.empty()) throw std::runtime_error("Container is empty");
        return *std::min_element(data.begin(), data.end());
    }

    // Size
    size_t size() const { return data.size(); }

    // Range-based iteration
    typename std::vector<T>::iterator begin() { return data.begin(); }
    typename std::vector<T>::iterator end() { return data.end(); }
    typename std::vector<T>::const_iterator begin() const { return data.begin(); }
    typename std::vector<T>::const_iterator end() const { return data.end(); }

    // Print all elements
    void printAll() const {
        for (const auto& val : data)
            std::cout << val << " ";
        std::cout << std::endl;
    }
};

// ------------------------
// Demonstration
// ------------------------
int main() {
    NumContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    c.printAll();
    std::cout << "Sum: " << c.sum() << std::endl;
    std::cout << "Max: " << c.max() << std::endl;
    std::cout << "Min: " << c.min() << std::endl;
    std::cout << "Average: " << c.average() << std::endl;

    c.remove(2);
    c.printAll();

    // Range-based for
    for (auto& x : c) x += 1;
    c.printAll();

    return 0;
}
/* 
Sample Output
1 2 3 
Sum: 6
Max: 3
Min: 1
Average: 2
1 3 
2 4 


Supports add, remove, sum, average, max, min
Works with range-based for loops
Numeric-only container, generic over type T.
*/


/*================================================================================*/
/* 
24 — Expression Template Vector

Problem Statement:
Implement ExprVector<T> supporting lazy evaluation of +, - operations

print() shows resulting vector

Sample Input:

ExprVector<int> v1(3); v1.fill(1);
ExprVector<int> v2(3); v2.fill(2);
auto v3 = v1 + v2;
v3.print();


Expected Output:

3 3 3
*/


#include <iostream>
#include <vector>
#include <stdexcept>

// Forward declaration for expression templates
template<typename T, typename E>
class Expr;

// Expression template wrapper
template<typename T>
class ExprVector {
private:
    std::vector<T> data;

public:
    // Constructors
    ExprVector() = default;
    explicit ExprVector(size_t n) : data(n) {}
    ExprVector(std::initializer_list<T> il) : data(il) {}

    // Fill with value
    void fill(const T& val) {
        std::fill(data.begin(), data.end(), val);
    }

    // Size
    size_t size() const { return data.size(); }

    // Operator[] (const)
    const T& operator[](size_t i) const {
        if (i >= data.size()) throw std::out_of_range("Index out of bounds");
        return data[i];
    }

    // Operator[] (non-const)
    T& operator[](size_t i) {
        if (i >= data.size()) throw std::out_of_range("Index out of bounds");
        return data[i];
    }

    // Print
    void print() const {
        for (const auto& val : data) std::cout << val << " ";
        std::cout << "\n";
    }

    // Expression assignment
    template<typename E>
    ExprVector(const Expr<T,E>& expr) {
        size_t n = expr.size();
        data.resize(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = expr[i];
    }

    template<typename E>
    ExprVector& operator=(const Expr<T,E>& expr) {
        size_t n = expr.size();
        data.resize(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = expr[i];
        return *this;
    }
};

// ----------------------------
// Expression template base
// ----------------------------
template<typename T, typename E>
class Expr {
public:
    T operator[](size_t i) const { return static_cast<E const&>(*this)[i]; }
    size_t size() const { return static_cast<E const&>(*this).size(); }
};

// ----------------------------
// Binary expressions: + and -
// ----------------------------
template<typename T, typename L, typename R>
class AddExpr : public Expr<T, AddExpr<T,L,R>> {
private:
    const L& lhs;
    const R& rhs;

public:
    AddExpr(const L& l, const R& r) : lhs(l), rhs(r) {
        if (lhs.size() != rhs.size())
            throw std::runtime_error("Size mismatch for addition");
    }

    T operator[](size_t i) const { return lhs[i] + rhs[i]; }
    size_t size() const { return lhs.size(); }
};

template<typename T, typename L, typename R>
class SubExpr : public Expr<T, SubExpr<T,L,R>> {
private:
    const L& lhs;
    const R& rhs;

public:
    SubExpr(const L& l, const R& r) : lhs(l), rhs(r) {
        if (lhs.size() != rhs.size())
            throw std::runtime_error("Size mismatch for subtraction");
    }

    T operator[](size_t i) const { return lhs[i] - rhs[i]; }
    size_t size() const { return lhs.size(); }
};

// ----------------------------
// Operators for ExprVectors
// ----------------------------
template<typename T, typename L, typename R>
AddExpr<T,L,R> operator+(const Expr<T,L>& lhs, const Expr<T,R>& rhs) {
    return AddExpr<T,L,R>(static_cast<const L&>(lhs), static_cast<const R&>(rhs));
}

template<typename T, typename L, typename R>
SubExpr<T,L,R> operator-(const Expr<T,L>& lhs, const Expr<T,R>& rhs) {
    return SubExpr<T,L,R>(static_cast<const L&>(lhs), static_cast<const R&>(rhs));
}

// ----------------------------
// Make ExprVector inherit Expr
// ----------------------------
template<typename T>
class ExprVectorWrapper : public Expr<T, ExprVector<T>> {
public:
    ExprVector<T>& vec;
    explicit ExprVectorWrapper(ExprVector<T>& v) : vec(v) {}
    T operator[](size_t i) const { return vec[i]; }
    size_t size() const { return vec.size(); }
};

// ----------------------------
// Demo
// ----------------------------
int main() {
    ExprVector<int> v1(3); v1.fill(1);
    ExprVector<int> v2(3); v2.fill(2);

    auto v3 = v1 + v2; // lazy evaluation
    ExprVector<int> result = v3; // evaluate and store in vector

    result.print(); // 3 3 3

    return 0;
}
/* 
Sample Output
3 3 3


Explanation:
ExprVector<T> supports lazy evaluation using expression templates.
v1 + v2 creates an AddExpr object without immediately performing addition.
Assignment ExprVector<int> result = v3; evaluates the expression element-wise.
Supports + and - operators with size checks.
*/

/*================================================================================*/


25 — Observer Pattern with State
/* 
Problem Statement:
Implement Subject with state, Observer prints state changes

attach(), detach(), notify()

Sample Input:
Subject s;
Observer o1; Observer o2;
s.attach(&o1); s.attach(&o2);
s.setState(10);


Expected Output:
Observer: State changed to 10
Observer: State changed to 10
*/

#include <iostream>
#include <vector>
#include <algorithm>

// Forward declaration
class Observer;

// Subject class
class Subject {
private:
    int state;
    std::vector<Observer*> observers;

public:
    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void detach(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify();

    void setState(int s) {
        state = s;
        notify();
    }

    int getState() const { return state; }
};

// Observer class
class Observer {
public:
    virtual void update(Subject* subj) {
        std::cout << "Observer: State changed to " << subj->getState() << "\n";
    }
};

// Notify all observers
void Subject::notify() {
    for (auto obs : observers) {
        if (obs) obs->update(this);
    }
}

// ----------------------------
// Demo
// ----------------------------
int main() {
    Subject s;
    Observer o1, o2;

    s.attach(&o1);
    s.attach(&o2);

    s.setState(10);

    return 0;
}
/* 
Expected Output
Observer: State changed to 10
Observer: State changed to 10


Explanation:
Subject maintains a list of observers (attach / detach).
setState() updates the internal state and calls notify().
notify() iterates all attached observers and calls their update() method.
Observers access the new state via getState().
*/

/*================================================================================*/