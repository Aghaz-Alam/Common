//Fixed Size Queue
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T, size_t N>
class queue {
    T arr[N];
    size_t frontInd;
    size_t rearInd;
    
  public:
    queue() : frontInd(0), rearInd(0) {}

    void push(const T& val) {
        if (rearInd == N)
            throw overflow_error("Queue is full!");

        arr[rearInd++] = val;
    }

    void pop() {
        if (frontInd == rearInd)
            throw underflow_error("Queue is empty!");

        frontInd++;
    }

    T& front() {
        if (frontInd == rearInd)
            throw underflow_error("Queue is empty!");

        return arr[frontInd];
    }

    T& back() {
        if (frontInd == rearInd)
            throw underflow_error("Queue is empty!");

        return arr[rearInd - 1];
    }

    void Display() {
        cout << "Elements: ";
        for (size_t i = frontInd; i < rearInd; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    try {
        queue<int, 5> q;

        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);

        q.Display();

        cout << "Front: " << q.front() << endl;
        cout << "Back: " << q.back() << endl;

        cout << "pop: ";
        q.pop();
        q.Display();

        cout << "Front: " << q.front() << endl;
        cout << "Back: " << q.back() << endl;

        // --------- TEST 1: Overflow test ----------
        cout << "\nTesting overflow...\n";
        try {
            q.push(60);   // Queue already full initially, so this should throw
        }
        catch (const exception& e) {
            cout << "Caught overflow: " << e.what() << endl;
        }

        // --------- Empty the queue ----------
        cout << "\nEmptying the queue...\n";
        q.pop(); // 20 removed
        q.pop(); // 30 removed
        q.pop(); // 40 removed
        q.pop(); // 50 removed

        // --------- TEST 2: Underflow test ----------
        cout << "\nTesting underflow...\n";
        try {
            q.pop();     // Now queue is empty → should throw
        }
        catch (const exception& e) {
            cout << "Caught underflow: " << e.what() << endl;
        }

        // --------- TEST 3: front() on empty ----------
        cout << "\nTesting front() on empty queue...\n";
        try {
            q.front();
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << endl;
        }

        // --------- TEST 4: back() on empty ----------
        cout << "\nTesting back() on empty queue...\n";
        try {
            q.back();
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << endl;
        }

    } catch (const exception& e) {
        cout << "Unexpected Error: " << e.what() << endl;
    }

    return 0;
}
/*
Elements: 10 20 30 40 50 
Front: 10
Back: 50
pop: Elements: 20 30 40 50 
Front: 20
Back: 50

Testing overflow...
Caught overflow: Queue is full!

Emptying the queue...

Testing underflow...
Caught underflow: Queue is empty!

Testing front() on empty queue...
Caught: Queue is empty!

Testing back() on empty queue...
Caught: Queue is empty!
*/


