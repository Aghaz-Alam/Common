/* 
33 — Implement Your Own String Class (MyString)
Design a custom string class that mimics some of the core features of std::string.

Requirements
Private Members
char* data — dynamically allocated storage
size_t length — length of the string

Constructors / Destructor
Default constructor (empty string)
Constructor from C-string (const char*)
Copy constructor (deep copy)
Move constructor
Destructor (free memory properly)

Member Functions
size() → returns the length
c_str() → returns const char*
substring(int start, int len) → returns a new MyString object
toUpper() → returns a new MyString with all uppercase
toLower() → returns a new MyString with all lowercase

Operator Overloads
operator+ → concatenate two MyString objects
operator== → compare two strings
operator[] → read-only access (throws exception if out of bounds)

Static Member
countInstances() → returns the number of currently alive MyString objects

Exception Handling
Throw exception on null input or out-of-bounds index

Sample Input
MyString s1("Hello");
MyString s2("World");
MyString s3 = s1 + MyString(" ") + s2;

MyString sub = s3.substring(0, 5);

MyString upper = s3.toUpper();
MyString lower = s3.toLower();

cout << s3[1] << endl;
cout << sub.c_str() << endl;
cout << upper.c_str() << endl;
cout << lower.c_str() << endl;

cout << "MyString instances: " << MyString::countInstances() << endl;

Expected Output
e
Hello
HELLO WORLD
hello world
MyString instances: 5
*/


#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cctype>
using namespace std;

class MyString {
private:
    char* data;
    size_t length;
    static size_t instanceCount;

public:
    // ----------- Constructors & Destructor -----------
    MyString() : data(nullptr), length(0) {
        data = new char[1];
        data[0] = '\0';
        instanceCount++;
    }

    MyString(const char* str) {
        if (!str) throw invalid_argument("Null C-string passed");

        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);

        instanceCount++;
    }

    // Copy constructor (deep copy)
    MyString(const MyString& other) : length(other.length) {
        data = new char[length + 1];
        strcpy(data, other.data);

        instanceCount++;
    }

    // Move constructor
    MyString(MyString&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
        instanceCount++;
    }

    // Destructor
    ~MyString() {
        delete[] data;
        instanceCount--;
    }

    // ----------- Basic Functions -----------
    size_t size() const { return length; }

    const char* c_str() const { return data; }

    // substring(start, len)
    MyString substring(int start, int len) const {
        if (start < 0 || start >= (int)length || len < 0 || start + len > (int)length)
            throw out_of_range("Invalid substring range");

        char* temp = new char[len + 1];
        strncpy(temp, data + start, len);
        temp[len] = '\0';

        MyString result(temp);
        delete[] temp;
        return result;
    }

    // toUpper()
    MyString toUpper() const {
        MyString result(*this);
        for (size_t i = 0; i < length; i++)
            result.data[i] = toupper(result.data[i]);
        return result;
    }

    // toLower()
    MyString toLower() const {
        MyString result(*this);
        for (size_t i = 0; i < length; i++)
            result.data[i] = tolower(result.data[i]);
        return result;
    }

    // ----------- Operators -----------

    // Concatenate
    MyString operator+(const MyString& rhs) const {
        size_t newLen = length + rhs.length;

        char* temp = new char[newLen + 1];
        strcpy(temp, data);
        strcat(temp, rhs.data);

        MyString result(temp);
        delete[] temp;
        return result;
    }

    // Compare
    bool operator==(const MyString& rhs) const {
        return strcmp(data, rhs.data) == 0;
    }

    // Read-only index
    char operator[](size_t index) const {
        if (index >= length)
            throw out_of_range("Index out of range");
        return data[index];
    }

    // Static instance count
    static size_t countInstances() {
        return instanceCount;
    }
};

// Initialize static variable
size_t MyString::instanceCount = 0;


// =========================================================
// MAIN (Tests given in the problem)
// =========================================================
int main() {
    MyString s1("Hello");
    MyString s2("World");
    MyString s3 = s1 + MyString(" ") + s2;

    MyString sub = s3.substring(0, 5);

    MyString upper = s3.toUpper();
    MyString lower = s3.toLower();

    cout << s3[1] << endl;
    cout << sub.c_str() << endl;
    cout << upper.c_str() << endl;
    cout << lower.c_str() << endl;

    cout << "MyString instances: " << MyString::countInstances() << endl;

    return 0;
}
/* 
e
Hello
HELLO WORLD
hello world
MyString instances: 5
*/