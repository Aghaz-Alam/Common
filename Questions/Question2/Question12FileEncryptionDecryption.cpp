/* 
Question 12: File Encryption & Decryption

Write a C++ program to encrypt and decrypt a text file using a simple substitution cipher.

Requirements:
Create functions encrypt() and decrypt().
Read from and write to a file.
Demonstrate with sample text file content.

Sample Input:
Hello World

Expected Output (Encrypted):
Khoor Zruog

Expected Output (Decrypted):
Hello World
*/

C++ Program: File Encryption & Decryption (Shift = 3)
✔ encrypt(): reads a file → encrypts → writes to another file
✔ decrypt(): reads encrypted file → decrypts → writes to another file
✔ Demonstrated with sample text: "Hello World" → "Khoor Zruog"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string encryptText(const string &text, int shift) {
    string result = text;
    for (char &c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        }
    }
    return result;
}

string decryptText(const string &text, int shift) {
    return encryptText(text, 26 - shift); // reverse shift
}

void encryptFile(const string &inputFile, const string &outputFile, int shift) {
    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in || !out) {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        out << encryptText(line, shift) << "\n";
    }
}

void decryptFile(const string &inputFile, const string &outputFile, int shift) {
    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in || !out) {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        out << decryptText(line, shift) << "\n";
    }
}

int main() {
    // Create a sample file
    ofstream sample("input.txt");
    sample << "Hello World";
    sample.close();

    int shift = 3; // Caesar cipher shift

    encryptFile("input.txt", "encrypted.txt", shift);
    decryptFile("encrypted.txt", "decrypted.txt", shift);

    // Display results
    ifstream enc("encrypted.txt");
    ifstream dec("decrypted.txt");

    string encryptedText, decryptedText;
    getline(enc, encryptedText);
    getline(dec, decryptedText);

    cout << "Encrypted: " << encryptedText << endl;
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}
/* 
Sample Output:
Encrypted: Khoor Zruog
Decrypted: Hello World
*/