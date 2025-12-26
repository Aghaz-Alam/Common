//String class implementation
#include <iostream>
using namespace std;
class String {
  private:
    char* data;

    // Utility function to calculate length of C-style string
    int stringLength(const char* str) const {
        int len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }

    // Utility function to copy string
    void stringCopy(char* dest, const char* src) const {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    // Utility function to concatenate strings
    void stringConcat(char* dest, const char* src1, const char* src2) const {
        int i = 0, j = 0;
        while (src1[i] != '\0') {
            dest[i] = src1[i];
            i++;
        }
        while (src2[j] != '\0') {
            dest[i] = src2[j];
            i++;
            j++;
        }
        dest[i] = '\0';
    }

  public:
    // Default constructor
    String() {
        data = new char[1];
        data[0] = '\0';
    }

    // Constructor from C-style string
    String(const char* str) {
        if (str) {
            int len = stringLength(str);
            data = new char[len + 1];
            stringCopy(data, str);
        } else {
            data = new char[1];
            data[0] = '\0';
        }
    }

    // Copy constructor
    String(const String& other) {
        int len = stringLength(other.data);
        data = new char[len + 1];
        stringCopy(data, other.data);
    }

    // Assignment operator
    String& operator=(const String& other) {
        if (this == &other) return *this;

        delete[] data;
        int len = stringLength(other.data);
        data = new char[len + 1];
        stringCopy(data, other.data);

        return *this;
    }

    // Destructor
    ~String() {
        delete[] data;
    }

    // Length of string
    int length() const {
        return stringLength(data);
    }

    // Concatenate two strings
    String operator+(const String& other) const {
        int len1 = stringLength(data);
        int len2 = stringLength(other.data);
        char* temp = new char[len1 + len2 + 1];
        stringConcat(temp, data, other.data);
        String result(temp);
        delete[] temp;
        return result;
    }

    // Print string
    void print() const {
        int i = 0;
        while (data[i] != '\0') {
            std::cout << data[i];
            i++;
        }
        std::cout << std::endl;
    }

    // Overload [] operator
    char& operator[](int index) {
        return data[index];
    }

    const char& operator[](int index) const {
        return data[index];
    }
};

int main() {
    String s1("Hello");
    String s2(" World");
    String s3 = s1 + s2;

    s1.print(); // Hello
    s2.print(); // World
    s3.print(); // Hello World

    std::cout << "Length of s3: " << s3.length() << std::endl;
    std::cout << "Character at index 4 of s3: " << s3[4] << std::endl;

    return 0;
}
/*
Hello
 World
Hello World
Length of s3: 11
Character at index 4 of s3: o
*/

