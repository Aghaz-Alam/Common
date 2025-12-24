/* 
Question 8: Linked List Implementation

Write a C++ class that implements a singly linked list data structure. Include methods for inserting a node at the beginning and the end of the linked list and displaying the elements in the list.

Sample input:
    	     myList.insertAtBeginning(1);
    	     myList.insertAtEnd(3);
    	     myList.insertAtBeginning(2);

Expected result : 2 1 3
*/


#include <iostream>
using namespace std;
class LinkedList {
  private:
    // Node structure
    struct Node {
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };
    Node* head;
    
  public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    // Display the list
    void display() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor (to free memory)
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    LinkedList myList;

    myList.insertAtBeginning(1);
    myList.insertAtEnd(3);
    myList.insertAtBeginning(2);

    // Expected Output: 2 1 3
    myList.display();

    return 0;
}
/*
2 1 3 
*/