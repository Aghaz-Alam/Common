/* 
HashTable-Insertion, Deletion, Search

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
    vector<list<int>> table;
    int capacity;

    // Hash function
    int hashFunction(int key) {
        return key % capacity;
    }
  public:
    // Constructor
    HashTable(int size = 10) {
        capacity = size;
        table.resize(capacity);
    }
    // Insert key
    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }
    // Search key
    bool search(int key) {
        int index = hashFunction(key);

        for (int val : table[index]) {
            if (val == key)
                return true;
        }
        return false;
    }
    // Delete key
    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }
    // Display HashTable (optional)
    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            for (int val : table[i]) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};
/* ============================================================
   MAIN — DEMO
============================================================ */
int main() {
    HashTable myHashTable;
    
    // Insert elements
    myHashTable.insert(1);
    myHashTable.insert(2);
    myHashTable.insert(3);
    myHashTable.insert(4);
    myHashTable.insert(5);
    myHashTable.insert(6);

    // Searching
    if (myHashTable.search(5))
        cout << "Searching element 5 is present in the HashTable" << endl;
    else
        cout << "Searching element 5 is not present in the HashTable" << endl;

    if (myHashTable.search(11))
        cout << "Searching element 11 is present in the HashTable" << endl;
    else
        cout << "Searching element 11 is not present in the HashTable" << endl;

  return 0;
}
/*
Searching element 5 is present in the HashTable
Searching element 11 is not present in the HashTable
*/