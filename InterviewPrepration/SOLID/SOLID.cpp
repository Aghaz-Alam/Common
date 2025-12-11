SOLID Principles in C++ (Explained with Examples)
SOLID is a set of five object-oriented design principles that help you write clean, maintainable, flexible code.

SOLID stands for:
S — Single Responsibility Principle (SRP)
O — Open/Closed Principle (OCP)
L — Liskov Substitution Principle (LSP)
I — Interface Segregation Principle (ISP)
D — Dependency Inversion Principle (DIP)



1️⃣ Single Responsibility Principle (SRP)
A class should have ONE and ONLY ONE reason to change.
❌ Bad: One class does too many things
class Report {
public:
    string generate() { return "data"; }
    void saveToFile(const string& data) {
        // file handling
    }
};

This class:
-->Generates data
-->Saves data to file
   = Two responsibilities → SRP violated

✔ Good: Split responsibilities
class ReportGenerator {
  public:
    string generate() { return "data"; }
};
class FileSaver {
  public:
    void save(const string& data) {
        // save to file
    }
};


