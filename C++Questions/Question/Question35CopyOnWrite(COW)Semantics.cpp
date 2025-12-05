/* 
35.Implement a Copy-On-Write String Class (CowString)

Design a custom string class CowString that implements copy-on-write (COW) semantics. The goal is to make copying strings cheap by sharing the underlying data until a modification occurs, at which point a deep copy is performed.

Requirements
Constructors
Default constructor → creates an empty string
Constructor from const char*

Copy Constructor / Assignment
Copies the string without duplicating the underlying data (shallow copy)
Maintain a reference count for shared data

Destructor
Properly release memory when no references remain

Member Functions
size() → returns the length of the string
substr(int start, int len) → returns a new CowString with the specified substring

operator[]
Const version → read-only access
Non-const version → triggers a deep copy if the string is shared, then allows modification

Copy-On-Write Behavior
Multiple CowString objects can share the same data initially
Modifying any shared string triggers a deep copy to ensure other objects remain unchanged

Example Usage
CowString s1("hello");
CowString s2 = s1;   // Shallow copy (data shared)
s2[0] = 'H';         // Triggers deep copy for s2

std::cout << "s1: " << s1 << std::endl;
std::cout << "s2: " << s2 << std::endl;

Expected Output
s1: hello
s2: Hello
*/


#include <iostream>
#include <cstring>
using namespace std;

class CowString {
private:
    struct StringData {
        char* data;
        int refCount;

        StringData(const char* str) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
            refCount = 1;
        }

        ~StringData() {
            delete[] data;
        }
    };

    StringData* sd;

    // Ensures unique ownership (deep copy) when modification happens
    void ensureUnique() {
        if (sd->refCount > 1) {
            // Perform deep copy
            sd->refCount--;
            sd = new StringData(sd->data);
        }
    }

public:
    // Default constructor
    CowString() {
        sd = new StringData("");
    }

    // Constructor from const char*
    CowString(const char* str) {
        sd = new StringData(str);
    }

    // Copy constructor (shallow copy)
    CowString(const CowString& other) {
        sd = other.sd;
        sd->refCount++;
    }

    // Assignment operator (shallow copy)
    CowString& operator=(const CowString& other) {
        if (this != &other) {
            if (--sd->refCount == 0) {
                delete sd;
            }
            sd = other.sd;
            sd->refCount++;
        }
        return *this;
    }

    // Destructor
    ~CowString() {
        if (--sd->refCount == 0) {
            delete sd;
        }
    }

    // Size of the string
    int size() const {
        return strlen(sd->data);
    }

    // Read-only operator[]
    char operator[](int index) const {
        return sd->data[index];
    }

    // Non-const operator[] (triggers deep copy)
    char& operator[](int index) {
        ensureUnique();
        return sd->data[index];
    }

    // Substring operation (returns a new COW string)
    CowString substr(int start, int len) const {
        char* temp = new char[len + 1];
        strncpy(temp, sd->data + start, len);
        temp[len] = '\0';

        CowString result(temp);
        delete[] temp;
        return result;
    }

    // Output stream operator
    friend ostream& operator<<(ostream& os, const CowString& s) {
        os << s.sd->data;
        return os;
    }
};

// =============================
//       TEST / MAIN
// =============================
int main() {
    CowString s1("hello");
    CowString s2 = s1;   // Shallow copy

    s2[0] = 'H';         // Deep copy triggered

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    // Substring test
    CowString sub = s1.substr(1, 3);
    cout << "Substring of s1 (1,3): " << sub << endl;

    return 0;
}
/* 
s1: hello
s2: Hello
Substring of s1 (1,3): ell
*/