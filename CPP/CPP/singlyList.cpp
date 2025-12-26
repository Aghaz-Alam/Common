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


