// Singly Linked List (Complete Implementation) 
#include <iostream>
using namespace std;

// Node definition
struct Node {
    int data;
    Node* next;
};

// Create a new node
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Insert at beginning
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Insert at end
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr) return newNode;

    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Insert at a specific position
Node* insertAtPosition(Node* head, int data, int pos) {
    if (pos < 1) {
        cout << "Invalid position!" << endl;
        return head;
    }

    if (pos == 1)
        return insertAtBeginning(head, data);

    Node* newNode = createNode(data);
    Node* temp = head;
    int count = 1;

    while (temp != nullptr && count < pos - 1) {
        temp = temp->next;
        count++;
    }

    if (temp == nullptr) {
        cout << "Position out of range!" << endl;
        delete newNode;
        return head;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

// Delete from beginning
Node* deleteBeginning(Node* head) {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return nullptr;
    }

    Node* temp = head;
    head = head->next;
    delete temp;

    return head;
}

// Delete from end
Node* deleteEnd(Node* head) {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return nullptr;
    }

    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }

    Node* temp = head;
    while (temp->next->next != nullptr)
        temp = temp->next;

    delete temp->next;
    temp->next = nullptr;

    return head;
}

// Delete from a specific position
Node* deleteAtPosition(Node* head, int pos) {
    if (pos < 1 || head == nullptr) {
        cout << "Invalid position or empty list!" << endl;
        return head;
    }

    if (pos == 1)
        return deleteBeginning(head);

    Node* temp = head;

    for (int i = 1; temp != nullptr && i < pos - 1; i++)
        temp = temp->next;

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of range!" << endl;
        return head;
    }

    Node* delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;

    return head;
}

// Search an element
bool search(Node* head, int key) {
    int pos = 1;

    while (head != nullptr) {
        if (head->data == key) {
            cout << "Element " << key << " found at position " << pos << endl;
            return true;
        }
        head = head->next;
        pos++;
    }

    cout << "Element " << key << " NOT found!" << endl;
    return false;
}

// Reverse the list
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Print the list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;

    cout << "== INSERTION OPERATIONS ==\n";

    head = insertAtBeginning(head, 2);
    head = insertAtBeginning(head, 1);
    cout << "After inserting 1,2 at beginning: ";
    printList(head);

    head = insertAtEnd(head, 3);
    head = insertAtEnd(head, 4);
    cout << "After inserting 3,4 at end: ";
    printList(head);

    head = insertAtPosition(head, 9, 3);
    cout << "After inserting 9 at position 3: ";
    printList(head);

    cout << "\n== DELETION OPERATIONS ==\n";

    head = deleteBeginning(head);
    cout << "After deleting beginning: ";
    printList(head);

    head = deleteEnd(head);
    cout << "After deleting end: ";
    printList(head);

    head = deleteAtPosition(head, 2);
    cout << "After deleting position 2: ";
    printList(head);

    cout << "\n== SEARCH OPERATION ==\n";
    search(head, 9);
    search(head, 2);

    cout << "\n== REVERSE OPERATION ==\n";
    head = reverseList(head);
    cout << "After reversing: ";
    printList(head);

    // Cleanup
    while (head != nullptr)
        head = deleteBeginning(head);

    return 0;
}

/*
== INSERTION OPERATIONS ==
After inserting 1,2 at beginning: 1 2 
After inserting 3,4 at end: 1 2 3 4 
After inserting 9 at position 3: 1 2 9 3 4 

== DELETION OPERATIONS ==
After deleting beginning: 2 9 3 4 
After deleting end: 2 9 3 
After deleting position 2: 2 3 

== SEARCH OPERATION ==
Element 9 NOT found!
Element 2 found at position 1

== REVERSE OPERATION ==
After reversing: 3 2 
*/




// Singly Linked List (Complete Implementation)
#include <iostream>
using namespace std;

class SinglyLinkedList {
  private:
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };

    Node* head;   // Head pointer

  public:
    // Constructor
    SinglyLinkedList() : head(nullptr) {}

    // Destructor (free all nodes)
    ~SinglyLinkedList() {
        while (head != nullptr)
            deleteBeginning();
    }

    // ==========================
    // INSERTION METHODS
    // ==========================

    // Insert at beginning
    void insertAtBeginning(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    // Insert at a specific position
    void insertAtPosition(int data, int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (pos == 1) {
            insertAtBeginning(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr) {
            cout << "Position out of range!" << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // ==========================
    // DELETION METHODS
    // ==========================

    // Delete first node
    void deleteBeginning() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Delete last node
    void deleteEnd() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->next == nullptr) { // only one node
            delete head;
            head = nullptr;
            return;
        }

        Node* temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;

        delete temp->next;   // delete last
        temp->next = nullptr;
    }

    // Delete node at a specific position
    void deleteAtPosition(int pos) {
        if (pos < 1 || head == nullptr) {
            cout << "Invalid position or empty list!" << endl;
            return;
        }

        if (pos == 1) {
            deleteBeginning();
            return;
        }

        Node* temp = head;

        for (int i = 1; temp != nullptr && i < pos - 1; i++)
            temp = temp->next;

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position out of range!" << endl;
            return;
        }

        Node* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
    }

    // ==========================
    // SEARCH
    // ==========================

    bool search(int key) {
        Node* temp = head;
        int pos = 1;

        while (temp != nullptr) {
            if (temp->data == key) {
                cout << "Element " << key << " found at position " << pos << endl;
                return true;
            }
            temp = temp->next;
            pos++;
        }

        cout << "Element " << key << " NOT found!" << endl;
        return false;
    }

    // ==========================
    // REVERSE LIST
    // ==========================

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // ==========================
    // PRINT LIST
    // ==========================

    void print() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ================================
// MAIN — Testing All Operations
// ================================
int main() {
    SinglyLinkedList list;

    cout << "== INSERTION OPERATIONS ==\n";
    list.insertAtBeginning(2);
    list.insertAtBeginning(1);
    cout << "After inserting 1,2 at beginning: ";
    list.print();

    list.insertAtEnd(3);
    list.insertAtEnd(4);
    cout << "After inserting 3,4 at end: ";
    list.print();

    list.insertAtPosition(9, 3);
    cout << "After inserting 9 at position 3: ";
    list.print();

    cout << "\n== DELETION OPERATIONS ==\n";

    list.deleteBeginning();
    cout << "After deleting beginning: ";
    list.print();

    list.deleteEnd();
    cout << "After deleting end: ";
    list.print();

    list.deleteAtPosition(2);
    cout << "After deleting position 2: ";
    list.print();

    cout << "\n== SEARCH OPERATION ==\n";
    list.search(9);
    list.search(2);

    cout << "\n== REVERSE OPERATION ==\n";
    list.reverse();
    cout << "After reversing: ";
    list.print();

    return 0;
}
/*
== INSERTION OPERATIONS ==
After inserting 1,2 at beginning: 1 2 
After inserting 3,4 at end: 1 2 3 4 
After inserting 9 at position 3: 1 2 9 3 4 

== DELETION OPERATIONS ==
After deleting beginning: 2 9 3 4 
After deleting end: 2 9 3 
After deleting position 2: 2 3 

== SEARCH OPERATION ==
Element 9 NOT found!
Element 2 found at position 1

== REVERSE OPERATION ==
After reversing: 3 2 
*/




// Templated Singly Linked List (Complete Implementation)
#include <iostream>
using namespace std;
template <typename T>
class SinglyLinkedList {
  private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;   // Head pointer

  public:
    // Constructor
    SinglyLinkedList() : head(nullptr) {}

    // Destructor (delete all nodes)
    ~SinglyLinkedList() {
        while (head != nullptr)
            deleteBeginning();
    }

    // ==========================
    // INSERTION METHODS
    // ==========================

    // Insert at beginning
    void insertAtBeginning(const T& data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(const T& data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    // Insert at a specific position
    void insertAtPosition(const T& data, int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (pos == 1) {
            insertAtBeginning(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr) {
            cout << "Position out of range!" << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // ==========================
    // DELETION METHODS
    // ==========================

    // Delete first node
    void deleteBeginning() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Delete last node
    void deleteEnd() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }

        Node* temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;

        delete temp->next;
        temp->next = nullptr;
    }

    // Delete node at a specific position
    void deleteAtPosition(int pos) {
        if (pos < 1 || head == nullptr) {
            cout << "Invalid position or empty list!" << endl;
            return;
        }

        if (pos == 1) {
            deleteBeginning();
            return;
        }

        Node* temp = head;

        for (int i = 1; temp != nullptr && i < pos - 1; i++)
            temp = temp->next;

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position out of range!" << endl;
            return;
        }

        Node* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
    }

    // ==========================
    // SEARCH
    // ==========================

    bool search(const T& key) {
        Node* temp = head;
        int pos = 1;

        while (temp != nullptr) {
            if (temp->data == key) {
                cout << "Element " << key << " found at position " << pos << endl;
                return true;
            }
            temp = temp->next;
            pos++;
        }

        cout << "Element " << key << " NOT found!" << endl;
        return false;
    }

    // ==========================
    // REVERSE LIST
    // ==========================

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // ==========================
    // PRINT LIST
    // ==========================

    void print() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ================================
// MAIN — TESTING ALL OPERATIONS
// ================================
int main() {
    SinglyLinkedList<int> list;

    cout << "== INSERTION OPERATIONS ==\n";
    list.insertAtBeginning(2);
    list.insertAtBeginning(1);
    cout << "After inserting 1,2 at beginning: ";
    list.print();

    list.insertAtEnd(3);
    list.insertAtEnd(4);
    cout << "After inserting 3,4 at end: ";
    list.print();

    list.insertAtPosition(9, 3);
    cout << "After inserting 9 at position 3: ";
    list.print();

    cout << "\n== DELETION OPERATIONS ==\n";

    list.deleteBeginning();
    cout << "After deleting beginning: ";
    list.print();

    list.deleteEnd();
    cout << "After deleting end: ";
    list.print();

    list.deleteAtPosition(2);
    cout << "After deleting position 2: ";
    list.print();

    cout << "\n== SEARCH OPERATION ==\n";
    list.search(9);
    list.search(2);

    cout << "\n== REVERSE OPERATION ==\n";
    list.reverse();
    cout << "After reversing: ";
    list.print();

    return 0;
}
/*
== INSERTION OPERATIONS ==
After inserting 1,2 at beginning: 1 2 
After inserting 3,4 at end: 1 2 3 4 
After inserting 9 at position 3: 1 2 9 3 4 

== DELETION OPERATIONS ==
After deleting beginning: 2 9 3 4 
After deleting end: 2 9 3 
After deleting position 2: 2 3 

== SEARCH OPERATION ==
Element 9 NOT found!
Element 2 found at position 1

== REVERSE OPERATION ==
After reversing: 3 2 
*/
















// Templated Singly Linked List (Complete Implementation)
#include <iostream>
using namespace std;
template <typename T>
class SinglyLinkedList {
  private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;   // Head pointer

  public:
    // Constructor
    SinglyLinkedList() : head(nullptr) {}

    // Destructor (delete all nodes)
    ~SinglyLinkedList() {
        while (head != nullptr)
            deleteBeginning();
    }

    // ==========================
    // INSERTION METHODS
    // ==========================

    // Insert at beginning
    void insertAtBeginning(const T& data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(const T& data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    // Insert at a specific position
    void insertAtPosition(const T& data, int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (pos == 1) {
            insertAtBeginning(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* temp = head;
        int count = 1;

        while (temp != nullptr && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr) {
            cout << "Position out of range!" << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // ==========================
    // DELETION METHODS
    // ==========================

    // Delete first node
    void deleteBeginning() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Delete last node
    void deleteEnd() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }

        Node* temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;

        delete temp->next;
        temp->next = nullptr;
    }

    // Delete node at a specific position
    void deleteAtPosition(int pos) {
        if (pos < 1 || head == nullptr) {
            cout << "Invalid position or empty list!" << endl;
            return;
        }

        if (pos == 1) {
            deleteBeginning();
            return;
        }

        Node* temp = head;

        for (int i = 1; temp != nullptr && i < pos - 1; i++)
            temp = temp->next;

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position out of range!" << endl;
            return;
        }

        Node* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
    }

    // ==========================
    // SEARCH
    // ==========================

    bool search(const T& key) {
        Node* temp = head;
        int pos = 1;

        while (temp != nullptr) {
            if (temp->data == key) {
                cout << "Element " << key << " found at position " << pos << endl;
                return true;
            }
            temp = temp->next;
            pos++;
        }

        cout << "Element " << key << " NOT found!" << endl;
        return false;
    }

    // ==========================
    // REVERSE LIST
    // ==========================

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // ==========================
    // PRINT LIST
    // ==========================

    void print() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ================================
// MAIN — TESTING ALL OPERATIONS
// ================================
int main() {
    SinglyLinkedList<int> list;

    cout << "== INSERTION OPERATIONS ==\n";
    list.insertAtBeginning(2);
    list.insertAtBeginning(1);
    cout << "After inserting 1,2 at beginning: ";
    list.print();

    list.insertAtEnd(3);
    list.insertAtEnd(4);
    cout << "After inserting 3,4 at end: ";
    list.print();

    list.insertAtPosition(9, 3);
    cout << "After inserting 9 at position 3: ";
    list.print();

    cout << "\n== DELETION OPERATIONS ==\n";

    list.deleteBeginning();
    cout << "After deleting beginning: ";
    list.print();

    list.deleteEnd();
    cout << "After deleting end: ";
    list.print();

    list.deleteAtPosition(2);
    cout << "After deleting position 2: ";
    list.print();

    cout << "\n== SEARCH OPERATION ==\n";
    list.search(9);
    list.search(2);

    cout << "\n== REVERSE OPERATION ==\n";
    list.reverse();
    cout << "After reversing: ";
    list.print();

    return 0;
}
/*
== INSERTION OPERATIONS ==
After inserting 1,2 at beginning: 1 2 
After inserting 3,4 at end: 1 2 3 4 
After inserting 9 at position 3: 1 2 9 3 4 

== DELETION OPERATIONS ==
After deleting beginning: 2 9 3 4 
After deleting end: 2 9 3 
After deleting position 2: 2 3 

== SEARCH OPERATION ==
Element 9 NOT found!
Element 2 found at position 1

== REVERSE OPERATION ==
After reversing: 3 2 
*/


