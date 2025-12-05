/* 
Question 16: File Line Counter

Write a C++ program to read a text file and count the number of lines, words, and characters.

Requirements:
Accept file name as input.
Display counts clearly.
Handle file not found exception.

Sample Input (file.txt):
Hello World
This is a test file.


Expected Output:
Lines: 2
Words: 7
Characters: 29
*/

//File Line Counter
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::string filename;
    std::cout << "Enter file name: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file!" << std::endl;
        return 1;
    }

    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;

    std::string line;

    while (std::getline(file, line)) {
        lineCount++;

        // Count characters in this line + newline
        charCount += line.size() + 1;  

        // Count words
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
            wordCount++;
    }

    std::cout << "Lines: " << lineCount << std::endl;
    std::cout << "Words: " << wordCount << std::endl;
    std::cout << "Characters: " << charCount << std::endl;

    return 0;
}
/* 
Sample Input (file.txt)
Hello World
This is a test file.

Expected Output
Lines: 2
Words: 7
Characters: 29
*/