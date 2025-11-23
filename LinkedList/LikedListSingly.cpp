#include<iostream>
using namespace std;

// Node definition
struct Node{
    int data;
    Node* next;
};

// function to create node
Node* createNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert node at a specific position
Node* insertNode(Node* head, int data, int pos){
    Node* newNode = createNode(data);
    if(pos == 1){
        newNode->next = head;
        return newNode;
    }
    Node* temp = head;
    int count = 1;
    while(temp != nullptr && count < pos - 1){
        temp = temp->next;
        count++;
    }
    if(temp == nullptr){
        cout<<"Position is out of range!"<<endl;
        delete newNode;
        return head;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

// Function to delete a node at a specific position
Node* deleteNode(Node* head, int pos){
    if(head == nullptr){
        return nullptr;
    }

    Node* temp = head;

    // If head needs to be removed
    if(pos == 1){
        head = temp->next;
        delete temp;
        return head;
    }

    // Find the node preceding the one to be deleted
    for(int i = 1; temp != nullptr && i < pos - 1; i++){
        temp = temp->next;
    }

    // If position is more than number of nodes
    if(temp == nullptr || temp->next == nullptr){
        cout<<"Position is out of range!"<<endl;
        return head;
    }

    // Node temp->next is the node to be deleted.
    // Store pointer to the next of node to be deleted
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;

    delete nodeToDelete;

    return head;
}


// Function to reverse the list
Node* reverseList(Node* head){
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    while(curr != nullptr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// function to print the list
void printList(Node* head){
    while(head){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}

// insert at beginning
Node* insertAtBegining(Node* head, int data){
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// insert at end
Node* isertNodeAtEnd(Node* head, int data){
    Node* newNode = createNode(data);

    if (head == nullptr) {
        return newNode;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
    return head;
}

int main(){
    Node* head = nullptr; // Start with an empty list for demonstrating new functions

    cout<<"List after inserting at beginning (5, 4, 3, 2, 1): ";
    head = insertAtBegining(head, 1);
    head = insertAtBegining(head, 2);
    head = insertAtBegining(head, 3);
    head = insertAtBegining(head, 4);
    head = insertAtBegining(head, 5);
    printList(head);


    head = insertNode(head, 9, 3);
    cout<<"After insterting 9 at position 3: ";
    printList(head);


    cout<<"List after inserting at end (6, 7): ";
    head = isertNodeAtEnd(head, 6);
    head = isertNodeAtEnd(head, 7);
    printList(head);

    
    

    
    // Deleting the node at position 4 (which is 4)
    head = deleteNode(head, 4); 
    cout<<"After deleting node at position 4: ";
    printList(head);


    head = reverseList(head);
    cout<<"Reversed List: ";
    printList(head);

    // Memory cleanup
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
