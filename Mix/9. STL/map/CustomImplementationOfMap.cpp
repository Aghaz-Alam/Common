Custom Implementation of Map Using a Binary Search Tree (BST)
Steps to Implement:
Node Structure: Each node of the tree will store a key-value pair.
Tree Structure: The map will maintain the tree structure using standard binary search tree properties.
Insert: We need a function to insert key-value pairs into the tree.
Find: We need to search for a key and return the corresponding value.
Erase: We need a function to delete a node.
Traversal: We'll add an in-order traversal to display the map elements.


#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;

// Node structure for each element in the tree
template <typename KeyType, typename ValueType>
struct MapNode {
    KeyType key;
    ValueType value;
    std::unique_ptr<MapNode<KeyType, ValueType>> left;
    std::unique_ptr<MapNode<KeyType, ValueType>> right;

    MapNode(KeyType k, ValueType v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Custom Map implementation using a Binary Search Tree (BST)
template <typename KeyType, typename ValueType>
class CustomMap {
  private:
    std::unique_ptr<MapNode<KeyType, ValueType>> root;

    // Helper function for insertion
    void insert(std::unique_ptr<MapNode<KeyType, ValueType>>& node, KeyType key, ValueType value) {
        if (!node) {
            node = std::make_unique<MapNode<KeyType, ValueType>>(key, value);
            return;
        }

        if (key < node->key) {
            insert(node->left, key, value);
        } else if (key > node->key) {
            insert(node->right, key, value);
        } else {
            node->value = value;  // Update value if key already exists
        }
    }

    // Helper function for finding a key
    MapNode<KeyType, ValueType>* find(MapNode<KeyType, ValueType>* node, KeyType key) {
        if (!node) {
            return nullptr;
        }
        if (key < node->key) {
            return find(node->left.get(), key);
        } else if (key > node->key) {
            return find(node->right.get(), key);
        } else {
            return node;  // Key found
        }
    }

    // Helper function to find the minimum node (used for deleting nodes)
    MapNode<KeyType, ValueType>* findMin(MapNode<KeyType, ValueType>* node) {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    // Helper function to delete a node
    MapNode<KeyType, ValueType>* erase(MapNode<KeyType, ValueType>* node, KeyType key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left.reset(erase(node->left.get(), key));
        } else if (key > node->key) {
            node->right.reset(erase(node->right.get(), key));
        } else {
            // Node to be deleted
            if (!node->left) {
                return node->right.release();
            } else if (!node->right) {
                return node->left.release();
            } else {
                // Node with two children
                MapNode<KeyType, ValueType>* minNode = findMin(node->right.get());
                node->key = minNode->key;
                node->value = minNode->value;
                node->right.reset(erase(node->right.get(), minNode->key));
            }
        }
        return node;
    }

    // Helper function for in-order traversal
    void inorderTraversal(MapNode<KeyType, ValueType>* node) const {
        if (!node) return;
        inorderTraversal(node->left.get());
        cout << node->key << " -> " << node->value << endl;
        inorderTraversal(node->right.get());
    }

  public:
    // Constructor
    CustomMap() : root(nullptr) {}

    // Insert key-value pair into the map
    void insert(KeyType key, ValueType value) {
        insert(root, key, value);
    }

    // Find value by key
    ValueType& find(KeyType key) {
        MapNode<KeyType, ValueType>* node = find(root.get(), key);
        if (node) {
            return node->value;
        }
        throw std::out_of_range("Key not found");
    }

    // Erase key-value pair by key
    void erase(KeyType key) {
        root.reset(erase(root.get(), key));
    }

    // Print map (in-order traversal)
    void print() const {
        inorderTraversal(root.get());
    }
};

// Example usage
int main() {
    CustomMap<int, string> myMap;

    // Insert key-value pairs
    myMap.insert(1, "Apple");
    myMap.insert(2, "Banana");
    myMap.insert(3, "Cherry");
    myMap.insert(4, "Date");

    cout << "Map contents (in-order):\n";
    myMap.print();

    // Find value for key 2
    cout << "\nValue for key 2: " << myMap.find(2) << endl;

    // Erase key 2
    cout << "\nErasing key 2...\n";
    myMap.erase(2);

    cout << "\nMap contents after erase (in-order):\n";
    myMap.print();

    // Try to find erased key
    try {
        cout << "\nValue for key 2: " << myMap.find(2) << endl;
    } catch (const std::out_of_range& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

/* 
Explanation:
MapNode Class:
Each node contains a key, a value, and pointers to its left and right children (left and right).


CustomMap Class:
Insert Function: The insert function adds a new node to the tree, ensuring the binary search tree property is maintained. 
If a node with the same key already exists, it updates the value.


Find Function: The find function searches for a node by key. If the key is found, it returns a pointer to the corresponding node.

Erase Function: The erase function removes a node by key. It handles three cases:

The node has no children (leaf node).

The node has one child.

The node has two children (in which case, we find the smallest node in the right subtree, replace the node with it, and delete the minimum node).

In-Order Traversal: The print function performs an in-order traversal of the tree and prints all the key-value pairs.

Main Function:
Insert a few key-value pairs, print the map, delete a key, and show the map again.
Demonstrates both finding a key and throwing an exception when the key doesn't exist.


Output:
Map contents (in-order):
1 -> Apple
2 -> Banana
3 -> Cherry
4 -> Date

Value for key 2: Banana

Erasing key 2...

Map contents after erase (in-order):
1 -> Apple
3 -> Cherry
4 -> Date

Exception: Key not found


Improvement and Enhancements:
Balancing the Tree: This is a simple implementation using a basic Binary Search Tree (BST). 
In practice, a Red-Black Tree or AVL Tree would be used to ensure the tree remains balanced, 
which keeps insertion, deletion, and lookup operations at O(log n) time complexity.

Memory Management: The code uses std::unique_ptr to manage memory automatically, ensuring no memory leaks occur.

Exception Handling: We raise an exception if a key is not found when using the find() method, making it safer 
than using operator[] or manual searching.

Thread Safety: This implementation is not thread-safe. If you're working in a multi-threaded environment, 
you may need to add synchronization mechanisms (e.g., std::mutex) for thread safety.


This implementation provides a simple, unbalanced binary search tree-based map. 
If you're looking for a production-grade map implementation, you'll need to look into using Red-Black Trees or AVL Trees, 
which provide better guarantees for balanced performance.
*/





#include <iostream>
#include <stdexcept>

template <typename KeyType, typename ValueType>
struct MapNode {
    KeyType key;
    ValueType value;
    MapNode* next;

    MapNode(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

template <typename KeyType, typename ValueType>
class SimpleMap {
  private:
    MapNode<KeyType, ValueType>* head;

  public:
    SimpleMap() : head(nullptr) {}
    // Insert key-value pair
    void insert(KeyType key, ValueType value) {
        // Check if key already exists
        MapNode<KeyType, ValueType>* current = head;
        while (current) {
            if (current->key == key) {
                current->value = value;  // Update value if key exists
                return;
            }
            current = current->next;
        }
        // If key doesn't exist, add a new node at the beginning
        MapNode<KeyType, ValueType>* newNode = new MapNode<KeyType, ValueType>(key, value);
        newNode->next = head;
        head = newNode;
    }
    // Find value by key
    ValueType& find(KeyType key) {
        MapNode<KeyType, ValueType>* current = head;
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw std::out_of_range("Key not found");
    }
    // Erase key-value pair by key
    void erase(KeyType key) {
        MapNode<KeyType, ValueType>* current = head;
        MapNode<KeyType, ValueType>* prev = nullptr;
        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;  // Head is being deleted
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        throw std::out_of_range("Key not found");
    }
    // Print all elements in the map
    void print() const {
        MapNode<KeyType, ValueType>* current = head;
        while (current) {
            std::cout << current->key << " -> " << current->value << std::endl;
            current = current->next;
        }
    }
    // Destructor to clean up the memory
    ~SimpleMap() {
        MapNode<KeyType, ValueType>* current = head;
        while (current) {
            MapNode<KeyType, ValueType>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};
// Example usage
int main() {
    SimpleMap<int, std::string> map;

    // Insert key-value pairs
    map.insert(1, "Apple");
    map.insert(2, "Banana");
    map.insert(3, "Cherry");
    map.insert(4, "Date");

    std::cout << "Map contents:\n";
    map.print();

    // Find value for key 2
    try {
        std::cout << "\nValue for key 2: " << map.find(2) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Erase key 2
    try {
        map.erase(2);
        std::cout << "\nAfter erasing key 2:\n";
        map.print();
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Try to find erased key
    try {
        std::cout << "\nValue for key 2 after erase: " << map.find(2) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
/* 
Map contents:
4 -> Date
3 -> Cherry
2 -> Banana
1 -> Apple

Value for key 2: Banana

After erasing key 2:
4 -> Date
3 -> Cherry
1 -> Apple

Value for key 2 after erase: Exception: Key not found
*/