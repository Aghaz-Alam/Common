/*
#include <iostream>
using namespace std;
int main() {
    int maxLength = 20; 
    char* str = new char[maxLength]; 
    
    std::cout << "Enter a string: ";
    
    std::cin.getline(str, maxLength); 
    std::cout << "You entered: " << str << std::endl;

    delete[] str;

    return 0;
}
/*
Output:
Enter a string: Hello World
You entered: Hello World
*/



//VVI
#include <iostream>
#include <cstring> // For strlen
using namespace std;
int main() {
    cout << "Enter a string: ";

    string input;
    getline(cin, input);

    int length = input.length();
    char* str = new char[length + 1]; // +1 for the null terminator

    strcpy(str, input.c_str());

    cout << "You entered: " << str << endl;

    // Clean up memory
    delete[] str;

    return 0;
}
/*
Enter a string: Hello World
You entered: Hello World
*/



#include <iostream>
#include <cstring> // For strlen
#include <memory>  // For std::unique_ptr
using namespace std;

int main() {
    cout << "Enter a string: ";
    string input;
    getline(cin, input);

    int length = input.length();

    unique_ptr<char[]> str(new char[length + 1]);  // +1 for the null terminator
    strcpy(str.get(), input.c_str()); // Use get() to access the raw pointer
    cout << "You entered: " << str.get() << endl;  // Use get() to access the raw pointer


    return 0;
}
/*
Enter a string: Hello World
You entered: Hello World
*/