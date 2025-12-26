/* 
32.Template-based Priority Queue

Problem:
Create a template PriorityQueue<T> using a heap internally. Support push, pop, top, size. Throw exception when popping empty queue.

Sample Input:
PriorityQueue<int> pq;
pq.push(5); pq.push(2); pq.push(9);
std::cout << pq.pop() << " " << pq.pop() << std::endl;


Expected Output:
9 5
*/


#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class PriorityQueue {
private:
    vector<T> heap;   // max-heap

    // Move element up
    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

    // Move element down
    void heapifyDown(size_t index) {
        size_t n = heap.size();
        while (true) {
            size_t left = index * 2 + 1;
            size_t right = index * 2 + 2;
            size_t largest = index;

            if (left < n && heap[left] > heap[largest])
                largest = left;

            if (right < n && heap[right] > heap[largest])
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else break;
        }
    }

public:
    // Insert element
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return highest priority
    T pop() {
        if (heap.empty())
            throw out_of_range("PriorityQueue is empty!");

        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return root;
    }

    // View highest priority
    const T& top() const {
        if (heap.empty())
            throw out_of_range("PriorityQueue is empty!");
        return heap[0];
    }

    size_t size() const { return heap.size(); }

    bool empty() const { return heap.empty(); }
};

// =================== TEST (as given in the problem) ===================
int main() {
    PriorityQueue<int> pq;
    pq.push(5);
    pq.push(2);
    pq.push(9);

    cout << pq.pop() << " " << pq.pop() << endl;  // Expected: 9 5
    return 0;
}
/* 
9 5
*/