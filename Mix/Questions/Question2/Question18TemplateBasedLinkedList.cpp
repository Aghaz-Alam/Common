/* 
Question 18-Template-Based Linked List

Build a singly linked list LinkedList<T> with insertFront(), insertBack(), and print().
Keep node creation and destruction safe.

Sample Input:
list.insertFront(1);
list.insertBack(2);
list.insertBack(3);
list.print();


Expected Output:
1 2 3
*/


//Template-Based LinkedList<T> (Safe, RAII, unique_ptr)
#include <iostream>
#include <memory>

template <typename T>
class LinkedList {
  private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    std::unique_ptr<Node> head = nullptr;

  public:
    LinkedList() = default;

    // Insert at beginning
    void insertFront(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    // Insert at end
    void insertBack(const T& value) {
        auto newNode = std::make_unique<Node>(value);

        if (!head) {
            head = std::move(newNode);
            return;
        }

        Node* curr = head.get();
        while (curr->next) {
            curr = curr->next.get();
        }

        curr->next = std::move(newNode);
    }

    // Print list
    void print() const {
        Node* curr = head.get();
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next.get();
        }
        std::cout << "\n";
    }
};
// ---------- SAMPLE TEST ----------
int main() {
    LinkedList<int> list;

    list.insertFront(1);
    list.insertBack(2);
    list.insertBack(3);

    list.print(); // Expected: 1 2 3

   return 0;
}
/* 
Expected Output
1 2 3
*/