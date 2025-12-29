/* 
HashTable Insertion, Deletion, Search

Question 6: Implement a hash table data structure in C++ with basic operations like insertion, deletion, and search.

Sample input : myHashTable.insert(1);
    	       myHashTable.insert(2);
    	       myHashTable.insert(3);
               myHashTable.insert(4);
               myHashTable.insert(5);
               myHashTable.insert(6);
    
	      searching for element 5 : myHashTable.search(5);
	      searching for element 11 : myHashTable.search(11);

Expected result : Searching element 5 is present in the HashTable
		  Searching element 11 is not present in the HashTable 
*/


#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashTable {
private:
    vector<list<int>> table;   // array of lists (separate chaining)
    int size;

    // Hash function
    int hashFunction(int key) const {
        return key % size;
    }

public:
    // Constructor
    HashTable(int tableSize = 10) {
        size = tableSize;
        table.resize(size);
    }

    // Insert an element
    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    // Search an element
    bool search(int key) {
        int index = hashFunction(key);

        for (int x : table[index]) {
            if (x == key)
                return true;
        }
        return false;
    }

    // Delete an element
    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }
};

int main() {
    HashTable myHashTable(10);

    // Sample inputs
    myHashTable.insert(1);
    myHashTable.insert(2);
    myHashTable.insert(3);
    myHashTable.insert(4);
    myHashTable.insert(5);
    myHashTable.insert(6);

    // Searching
    if (myHashTable.search(5))
        cout << "Searching element 5 is present in the HashTable\n";
    else
        cout << "Searching element 5 is not present in the HashTable\n";

    if (myHashTable.search(11))
        cout << "Searching element 11 is present in the HashTable\n";
    else
        cout << "Searching element 11 is not present in the HashTable\n";

    return 0;
}
/* 
Searching element 5 is present in the HashTable
Searching element 11 is not present in the HashTable
*/