File handling in C++ allows us to read from and write to files. 
C++ provides a library called <fstream> that contains classes to handle files:
--> ofstream → for writing to files (output file stream)
--> ifstream → for reading from files (input file stream)
--> fstream → for both reading and writing (file stream)

File modes
| Mode          | Meaning                                    |
| ------------- | ------------------------------------------ |
| `ios::in`     | Open for reading                           |
| `ios::out`    | Open for writing                           |
| `ios::app`    | Append to the end of file                  |
| `ios::trunc`  | Truncate the file (default for `ofstream`) |
| `ios::binary` | Open in binary mode                        |


//Writing to a file (ofstream)
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ofstream outFile("example.txt"); // open file for writing

    if (!outFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    outFile << "Hello, world!" << endl;
    outFile << "Writing to a file in C++ is easy." << endl;

    outFile.close(); // always close the file
    cout << "Data written successfully." << endl;

    return 0;
}
/*
Data written successfully.

//example.txt
Hello, world!
Writing to a file in C++ is easy.


✅ Notes:
If the file doesn’t exist, it will be created.
If the file exists, its contents are overwritten.
*/



////Reading from a file (ifstream)
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream inFile("example.txt"); // open file for reading

    if (!inFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string str;
    while (getline(inFile, str)) { // read line by line
        cout << str << endl;
    }

    inFile.close();
    return 0;
}
/*
Hello, world!
Writing to a file in C++ is easy.


✅ Notes:
getline() reads a line until a newline character \n.
*/


//Reading and writing using fstream
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // --- Writing to a file ---
    ofstream outFile("example.txt"); // open file for writing

    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    outFile << "Hello, world!" << endl;
    outFile << "Writing to a file in C++ is easy." << endl;

    outFile.close(); // always close the file
    cout << "Data written successfully." << endl;

    // --- Reading from the same file ---
    ifstream inFile("example.txt"); // open file for reading

    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return 1;
    }

    cout << "\nReading from file:\n";
    string line;
    while (getline(inFile, line)) { // read line by line
        cout << line << endl;
    }

    inFile.close(); // close the file
    return 0;
}
/*
Data written successfully.

Reading from file:
Hello, world!
Writing to a file in C++ is easy.
*/




//Write to and read from a file
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    fstream file("example.txt", ios::out | ios::in | ios::trunc); 
    // ios::out -> writing
    // ios::in  -> reading
    // ios::trunc -> clears the file if it exists

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // --- Writing to the file ---
    file << "Hello, world!" << endl;
    file << "Writing to a file in C++ using fstream is easy." << endl;

    // After writing, move the file pointer back to the beginning for reading
    file.seekg(0);

    cout << "Data written successfully.\n\nReading from file:\n";

    // --- Reading from the same file ---
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close(); // close the file
    return 0;
}
/*
Data written successfully.

Reading from file:
Hello, world!
Writing to a file in C++ using fstream is easy.


//example.txt
//Hello, world!
//Writing to a file in C++ using fstream is easy.

*/





//Reading and writing using fstream
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    fstream file("example.txt", ios::in | ios::out | ios::app); 
    // ios::in → read, ios::out → write, ios::app → append

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    file << "\nAppending a new line."; // write

    file.seekg(0); // go back to beginning for reading
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    return 0;
}

/*
Hello, world!
Writing to a file in C++ is easy.

Appending a new line.
*/