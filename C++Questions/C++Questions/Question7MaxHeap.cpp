/* Heap

Question 7: Implement a max heap data structure in C++ with basic operations like insertion and extraction of the maximum element

Sample input : 
		myHeap.insert(3);
    	myHeap.insert(100);
    	myHeap.insert(8);
    	myHeap.insert(5);
    	myHeap.insert(200);

Expected output : 
		200
		100
*/

#include <iostream>
#include <vector>
using namespace std;
class MaxHeap {
  private:
    vector<int> heap;

    // Moves the newly inserted element up to maintain heap property
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

    // Moves the root element down to maintain heap property
    void heapifyDown(int index) {
        int size = heap.size();

        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left] > heap[largest])
                largest = left;

            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

  public:
    // Insert a value into heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return the maximum element (root)
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

    // Expected Output: 200 100
    cout << myHeap.extractMax() << endl;
    cout << myHeap.extractMax() << endl;

    return 0;
}
/*
200
100
*/