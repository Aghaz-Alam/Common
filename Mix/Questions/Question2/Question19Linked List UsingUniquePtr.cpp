/* 
Question-19 : Linked List Using UniquePtr 
Implement a singly linked list using unique_ptr for nodes.
Support push, pop, traversal.
Add an in-place reverse() function using pointer manipulation.

Sample Input:
list.push(1);
list.push(2);
list.reverse();


Expected Output:
2 1
*/

//Singly Linked List with std::unique_ptr
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class LinkedList {
  private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::unique_ptr<Node> head;

  public:
    LinkedList() : head(nullptr) {}

    // Push to front
    void push(T val) {
        auto newNode = std::make_unique<Node>(val);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    // Pop from front
    T pop() {
        if (!head) throw std::runtime_error("List is empty");
        T val = head->data;
        head = std::move(head->next);
        return val;
    }

    // Traverse and print
    void print() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << "\n";
    }

    // In-place reverse
    void reverse() {
        std::unique_ptr<Node> prev = nullptr;
        while (head) {
            std::unique_ptr<Node> next = std::move(head->next);
            head->next = std::move(prev);
            prev = std::move(head);
            head = std::move(next);
        }
        head = std::move(prev);
    }
};
int main() {
    LinkedList<int> list;

    list.push(1);
    list.push(2);
    list.push(3);

    std::cout << "Original list: ";
    list.print();

    list.reverse();
    std::cout << "Reversed list: ";
    list.print();

    int val = list.pop();
    std::cout << "Popped: " << val << "\n";

    std::cout << "Final list: ";
    list.print();

    return 0;
}
/* 
Original list: 3 2 1 
Reversed list: 1 2 3 
Popped: 1
Final list: 2 3 
*/



//Singly Linked List with std::shared_ptr
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class LinkedList {
  private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::shared_ptr<Node> head;

  public:
    LinkedList() : head(nullptr) {}

    // Push to front
    void push(T val) {
        auto newNode = std::make_shared<Node>(val);
        newNode->next = head;
        head = newNode;
    }

    // Pop from front
    T pop() {
        if (!head) throw std::runtime_error("List is empty");
        T val = head->data;
        head = head->next;
        return val;
    }

    // Traverse and print
    void print() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << "\n";
    }

    // In-place reverse
    void reverse() {
        std::shared_ptr<Node> prev = nullptr;
        while (head) {
            std::shared_ptr<Node> next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        head = prev;
    }
};
int main() {
    LinkedList<int> list;

    list.push(1);
    list.push(2);
    list.push(3);

    std::cout << "Original list: ";
    list.print();

    list.reverse();
    std::cout << "Reversed list: ";
    list.print();

    int val = list.pop();
    std::cout << "Popped: " << val << "\n";

    std::cout << "Final list: ";
    list.print();

    return 0;
}
/* 
Original list: 3 2 1 
Reversed list: 1 2 3 
Popped: 1
Final list: 2 3 
*/