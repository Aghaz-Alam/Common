#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}  
};

class List {
    Node* head;
    Node* tail;

  public:
    List() : head(nullptr), tail(nullptr) {}

    // Method to create and insert a node at the front of the list (push_front)
    void push_front(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;  // If list is empty, make the new node the head and tail
        } else {
            newNode->next = head;   // Link the new node to the current head
            head->prev = newNode;   // Link the current head's prev to the new node
            head = newNode;         // Update the head to the new node
        }
    }

    // Method to create and insert a node at the end of the list (push_back)
    void push_back(int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;  // If list is empty, make the new node the head and tail
        } else {
            newNode->prev = tail;   // Link the new node's prev to the current tail
            tail->next = newNode;   // Link the current tail's next to the new node
            tail = newNode;         // Update the tail to the new node
        }
    }

    // Method to insert a node at a specific position
    void insertNode(int val, int pos) {
        Node* newNode = new Node(val);
        if (pos == 0) {
            // Insert at the beginning
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;  // Update the previous pointer of the original head
            }
            head = newNode;
            if (head->next == nullptr) {
                tail = head;  // If it's the only node, both head and tail point to it
            }
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
                if (temp->next != nullptr) {
                    temp->next->prev = newNode;  // Update the previous pointer of the node after the new node
                }
                temp->next = newNode;
                newNode->prev = temp;
                if (newNode->next == nullptr) {
                    tail = newNode;  // Update the tail if we inserted at the end
                }
            }
        }
    }

    // Method to reverse the linked list
    void reverseList() {
        Node* temp = nullptr;
        Node* current = head;

        while (current != nullptr) {
            temp = current->prev;  // Swap the prev and next pointers
            current->prev = current->next;
            current->next = temp;
            current = current->prev;  // Move to the next node (which is now prev)
        }

        if (temp != nullptr) {
            head = temp->prev;  // Update the head to the new first element
        }
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
            if (head != nullptr) {
                head->prev = nullptr;  // Update the previous pointer of the new head
            }
            delete temp;
            return;
        }

        // Otherwise, find the node to delete
        Node* temp = head;
        while (temp != nullptr && temp->data != val) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value not found!" << endl;
        } else {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;  // Update the next pointer of the previous node
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;  // Update the prev pointer of the next node
            }
            if (temp == tail) {
                tail = temp->prev;  // If deleting the tail, update the tail pointer
            }
            delete temp;
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
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_back(50);

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






#include<iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}  
};

template<typename T>
class List {
    Node<T>* head;
    Node<T>* tail;

  public:
    List() : head(nullptr), tail(nullptr) {}

    // Method to create and insert a node at the front of the list (push_front)
    void push_front(T val) {
        Node<T>* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;  // If list is empty, make the new node the head and tail
        } else {
            newNode->next = head;   // Link the new node to the current head
            head->prev = newNode;   // Link the current head's prev to the new node
            head = newNode;         // Update the head to the new node
        }
    }

    // Method to create and insert a node at the end of the list (push_back)
    void push_back(T val) {
        Node<T>* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;  // If list is empty, make the new node the head and tail
        } else {
            newNode->prev = tail;   // Link the new node's prev to the current tail
            tail->next = newNode;   // Link the current tail's next to the new node
            tail = newNode;         // Update the tail to the new node
        }
    }

    // Method to insert a node at a specific position
    void insertNode(T val, size_t pos) {
        Node<T>* newNode = new Node(val);
        if (pos == 0) {
            // Insert at the beginning
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;  // Update the previous pointer of the original head
            }
            head = newNode;
            if (head->next == nullptr) {
                tail = head;  // If it's the only node, both head and tail point to it
            }
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
                if (temp->next != nullptr) {
                    temp->next->prev = newNode;  // Update the previous pointer of the node after the new node
                }
                temp->next = newNode;
                newNode->prev = temp;
                if (newNode->next == nullptr) {
                    tail = newNode;  // Update the tail if we inserted at the end
                }
            }
        }
    }

    // Method to reverse the linked list
    void reverseList() {
        Node<T>* temp = nullptr;
        Node<T>* current = head;

        while (current != nullptr) {
            temp = current->prev;  // Swap the prev and next pointers
            current->prev = current->next;
            current->next = temp;
            current = current->prev;  // Move to the next node (which is now prev)
        }

        if (temp != nullptr) {
            head = temp->prev;  // Update the head to the new first element
        }
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
            if (head != nullptr) {
                head->prev = nullptr;  // Update the previous pointer of the new head
            }
            delete temp;
            return;
        }

        // Otherwise, find the node to delete
        Node<T>* temp = head;
        while (temp != nullptr && temp->data != val) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value not found!" << endl;
        } else {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;  // Update the next pointer of the previous node
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;  // Update the prev pointer of the next node
            }
            if (temp == tail) {
                tail = temp->prev;  // If deleting the tail, update the tail pointer
            }
            delete temp;
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
    List <int> l;

    // Creating nodes and adding to the list
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_back(50);

    cout << "Original List: ";
    l.display();

    // Inserting a node at position 2
    l.insertNode(25, 2);
    cout << "After inserting 25 at position 2: "<<endl;
    l.display();

    // Deleting a node with value 30
    l.deleteNode(30);
    cout << "After deleting 30: ";
    l.display();

    // Reversing the list
    l.reverseList();
    cout << "After reversing the list: ";
    l.display();


    List <string> lStr;

    // Creating nodes and adding to the list
    lStr.push_back("Apple");
    lStr.push_back("Banana");
    lStr.push_back("Carrot");
    lStr.push_back("Dosa");
    lStr.push_back("Egg");

    cout << "Original List: ";
    lStr.display();

    // Inserting a node at position 2
    lStr.insertNode("Samosa", 2);
    cout << "After inserting Samosa at position 2: "<<endl;
    lStr.display();

    // Deleting a node with value "Dosa"
    lStr.deleteNode("Dosa");
    cout << "After deleting Dosa: ";
    lStr.display();

    // Reversing the list
    lStr.reverseList();
    cout << "After reversing the list: ";
    lStr.display();

    return 0;
}
/*
Original List: 10 20 30 40 50 
After inserting 25 at position 2: 
10 20 25 30 40 50 
After deleting 30: 10 20 25 40 50 
After reversing the list: 50 40 25 20 10 
Original List: Apple Banana Carrot Dosa Egg 
After inserting Samosa at position 2: 
Apple Banana Samosa Carrot Dosa Egg 
After deleting Dosa: Apple Banana Samosa Carrot Egg 
After reversing the list: Egg Carrot Samosa Banana Apple 
*/