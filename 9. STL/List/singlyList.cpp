#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}  
};

class List {
    Node* head;

  public:
    List() : head(nullptr) {}

    // Method to create and insert a node at the end of the list
    void createNode(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;  // If list is empty, make the new node the head
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {  // Traverse till the last node
                temp = temp->next;
            }
            temp->next = newNode;  // Link the last node to the new node
        }
    }

    // Method to insert a node at a specific position
    void insertNode(int val, int pos) {
        Node* newNode = new Node(val);
        if (pos == 0) {
            // Insert at the beginning
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            int index = 0;
            while (temp != nullptr && index < pos - 1) {
                temp = temp->next;
                index++;
            }
            if (temp == nullptr) {
                cout << "Position out of bounds!" << endl;
            } else {
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    // Method to reverse the linked list
    void reverseList() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        
        while (current != nullptr) {
            next = current->next;  // Store next node
            current->next = prev;  // Reverse the current node's pointer
            prev = current;        // Move prev and current one step forward
            current = next;
        }
        head = prev;  // Update head to the new first element
    }

    // Method to delete a node with a specific value
    void deleteNode(int val) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        // If the node to delete is the head node
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Otherwise, find the node to delete
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != val) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Value not found!" << endl;
        } else {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    // Method to display the list
    void display() const {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor to free memory when the list is no longer needed
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    List l;

    // Creating nodes and adding to the list
    l.createNode(10);
    l.createNode(20);
    l.createNode(30);
    l.createNode(40);
    l.createNode(50);

    cout << "Original List: ";
    l.display();

    // Inserting a node at position 2
    l.insertNode(25, 2);
    cout << "After inserting 25 at position 2: ";
    l.display();

    // Deleting a node with value 30
    l.deleteNode(30);
    cout << "After deleting 30: ";
    l.display();

    // Reversing the list
    l.reverseList();
    cout << "After reversing the list: ";
    l.display();

    return 0;
}
/*
Original List: 10 20 30 40 50 
After inserting 25 at position 2: 10 20 25 30 40 50 
After deleting 30: 10 20 25 40 50 
After reversing the list: 50 40 25 20 10 
*/





#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}  
};

template <typename T>
class List {
    Node<T>* head;

  public:
    // Constructor
    List() : head(nullptr) {}

    // Method to create and insert a node at the end of the list
    void createNode(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;  // If list is empty, make the new node the head
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {  // Traverse till the last node
                temp = temp->next;
            }
            temp->next = newNode;  // Link the last node to the new node
        }
    }

    // Method to insert a node at a specific position
    void insertNode(T val, int pos) {
        Node<T>* newNode = new Node<T>(val);
        if (pos == 0) {
            // Insert at the beginning
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* temp = head;
            int index = 0;
            while (temp != nullptr && index < pos - 1) {
                temp = temp->next;
                index++;
            }
            if (temp == nullptr) {
                cout << "Position out of bounds!" << endl;
            } else {
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    // Method to reverse the linked list
    void reverseList() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        
        while (current != nullptr) {
            next = current->next;  // Store next node
            current->next = prev;  // Reverse the current node's pointer
            prev = current;        // Move prev and current one step forward
            current = next;
        }
        head = prev;  // Update head to the new first element
    }

    // Method to delete a node with a specific value
    void deleteNode(T val) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        // If the node to delete is the head node
        if (head->data == val) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Otherwise, find the node to delete
        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != val) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Value not found!" << endl;
        } else {
            Node<T>* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    // Method to display the list
    void display() const {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor to free memory when the list is no longer needed
    ~List() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    // Create a generic list for integers
    List<int> intList;

    // Creating nodes and adding to the list
    intList.createNode(10);
    intList.createNode(20);
    intList.createNode(30);
    intList.createNode(40);
    intList.createNode(50);

    cout << "Original List (int): ";
    intList.display();

    // Inserting a node at position 2
    intList.insertNode(25, 2);
    cout << "After inserting 25 at position 2: ";
    intList.display();

    // Deleting a node with value 30
    intList.deleteNode(30);
    cout << "After deleting 30: ";
    intList.display();

    // Reversing the list
    intList.reverseList();
    cout << "After reversing the list: ";
    intList.display();

    // Create a generic list for strings
    List<string> strList;

    // Creating nodes and adding to the list
    strList.createNode("apple");
    strList.createNode("banana");
    strList.createNode("cherry");

    cout << "Original List (string): ";
    strList.display();

    // Inserting a node at position 1
    strList.insertNode("orange", 1);
    cout << "After inserting 'orange' at position 1: ";
    strList.display();

    // Deleting a node with value "banana"
    strList.deleteNode("banana");
    cout << "After deleting 'banana': ";
    strList.display();

    // Reversing the list
    strList.reverseList();
    cout << "After reversing the list: ";
    strList.display();

    return 0;
}
/*
Original List (int): 10 20 30 40 50 
After inserting 25 at position 2: 10 20 25 30 40 50 
After deleting 30: 10 20 25 40 50 
After reversing the list: 50 40 25 20 10 
Original List (string): apple banana cherry 
After inserting 'orange' at position 1: apple orange banana cherry 
After deleting 'banana': apple orange cherry 
After reversing the list: cherry orange apple 
*/