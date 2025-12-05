/* 
31. Library Management System

Problem: Implement classes Book, Member, and Library. Library maintains a collection of books and members. Members can borrow/return books. Use exceptions for unavailable books.

Sample Input:

Library lib;
lib.addBook(Book(101,"C++ Primer"));
lib.addBook(Book(102,"Effective C++"));
lib.addMember(Member(1,"Ravi"));

lib.borrowBook(1,101);
lib.borrowBook(1,102);
lib.returnBook(1,101);
lib.listBooks();


Expected Output:

Book 101: C++ Primer - Available
Book 102: Effective C++ - Borrowed by Member 1
*/


#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// ===================== Book =========================
class Book {
private:
    int id;
    string title;
    bool isBorrowed;
    int borrowedBy;   // member id

public:
    Book(int id, const string& title)
        : id(id), title(title), isBorrowed(false), borrowedBy(-1) {}

    int getId() const { return id; }
    string getTitle() const { return title; }

    bool available() const { return !isBorrowed; }
    int getBorrower() const { return borrowedBy; }

    void borrow(int memberId) {
        if (!available())
            throw runtime_error("Book already borrowed");

        isBorrowed = true;
        borrowedBy = memberId;
    }

    void returnBook() {
        if (available())
            throw runtime_error("Book was not borrowed");

        isBorrowed = false;
        borrowedBy = -1;
    }

    void printInfo() const {
        cout << "Book " << id << ": " << title << " - ";
        if (available())
            cout << "Available";
        else
            cout << "Borrowed by Member " << borrowedBy;
        cout << endl;
    }
};

// ===================== Member =========================
class Member {
private:
    int id;
    string name;

public:
    Member(int id, const string& name) : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }
};

// ===================== Library =========================
class Library {
private:
    vector<Book> books;
    vector<Member> members;

    // Helper to find book by ID
    Book& getBook(int id) {
        for (auto& b : books)
            if (b.getId() == id)
                return b;
        throw runtime_error("Book not found");
    }

    // Helper to find member by ID
    Member& getMember(int id) {
        for (auto& m : members)
            if (m.getId() == id)
                return m;
        throw runtime_error("Member not found");
    }

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addMember(const Member& member) {
        members.push_back(member);
    }

    void borrowBook(int memberId, int bookId) {
        Member& m = getMember(memberId);
        Book& b = getBook(bookId);
        b.borrow(m.getId());
    }

    void returnBook(int memberId, int bookId) {
        Member& m = getMember(memberId);
        Book& b = getBook(bookId);

        if (b.available() || b.getBorrower() != m.getId())
            throw runtime_error("This member didn't borrow this book");

        b.returnBook();
    }

    void listBooks() const {
        for (const auto& b : books)
            b.printInfo();
    }
};

// ===================== MAIN (Given Example) =========================
int main() {
    Library lib;

    lib.addBook(Book(101, "C++ Primer"));
    lib.addBook(Book(102, "Effective C++"));
    lib.addMember(Member(1, "Ravi"));

    lib.borrowBook(1, 101);
    lib.borrowBook(1, 102);
    lib.returnBook(1, 101);

    lib.listBooks();

    return 0;
}
/* 
Book 101: C++ Primer - Available
Book 102: Effective C++ - Borrowed by Member 1
*/