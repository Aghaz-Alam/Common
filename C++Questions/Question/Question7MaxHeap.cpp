/* 
Heap

Question 7: Implement a max heap data structure in C++ with basic operations like insertion and extraction of the maximum element

Sample input :  myHeap.insert(3);
    		myHeap.insert(100);
    		myHeap.insert(8);
    		myHeap.insert(5);
    		myHeap.insert(200);

Expected output : 200
		          100

*/

#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    // Heapify Up (for insertion)
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Heapify Down (for extracting max)
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            }
            else break;
        }
    }

public:
    // Insert new value into heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Extract max element
    int extractMax() {
        if (heap.empty()) {
            cout << "Heap is empty!\n";
            return -1;
        }

        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        heapifyDown(0);

        return maxVal;
    }
};

int main() {
    MaxHeap myHeap;

    myHeap.insert(3);
    myHeap.insert(100);
    myHeap.insert(8);
    myHeap.insert(5);
    myHeap.insert(200);

    cout << myHeap.extractMax() << endl; // 200
    cout << myHeap.extractMax() << endl; // 100

    return 0;
}
/* 
200
100
*/