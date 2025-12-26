/* 
Question 20 : Template-Based Circular Queue

Implement a generic CircularQueue<T> with fixed capacity.
Provide enqueue, dequeue, isFull, isEmpty.
Add an iterator so the queue can be used in range-based for loops.

Sample Input:
q.enqueue(1);
q.enqueue(2);
for(int x : q) cout<<x<<" ";


Expected Output:
1 2
*/

//Template-Based Circular Queue
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class CircularQueue {
  private:
    std::vector<T> data;
    size_t head, tail, count;
    size_t capacity;

  public:
    CircularQueue(size_t cap) : data(cap), head(0), tail(0), count(0), capacity(cap) {}

    void enqueue(const T& value) {
        if (isFull()) throw std::runtime_error("Queue is full");
        data[tail] = value;
        tail = (tail + 1) % capacity;
        ++count;
    }

    T dequeue() {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        T val = data[head];
        head = (head + 1) % capacity;
        --count;
        return val;
    }

    bool isFull() const { return count == capacity; }
    bool isEmpty() const { return count == 0; }
    size_t size() const { return count; }

    // ------------------- Iterator -------------------
    class Iterator {
    private:
        const CircularQueue<T>* queue;
        size_t index;
        size_t iterated;

    public:
        Iterator(const CircularQueue<T>* q, size_t start, size_t iter) : queue(q), index(start), iterated(iter) {}

        T operator*() const { return queue->data[index]; }

        Iterator& operator++() {
            index = (index + 1) % queue->capacity;
            ++iterated;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return iterated != other.iterated; }
    };

    Iterator begin() const { return Iterator(this, head, 0); }
    Iterator end() const { return Iterator(this, tail, count); }
};
int main() {
    CircularQueue<int> q(5);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    std::cout << "Queue contents: ";
    for (int x : q) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    int removed = q.dequeue();
    std::cout << "Dequeued: " << removed << "\n";

    q.enqueue(4);
    q.enqueue(5);

    std::cout << "Queue after enqueueing more: ";
    for (int x : q) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
/* 
Queue contents: 1 2 3 
Dequeued: 1
Queue after enqueueing more: 2 3 4 5 
*/