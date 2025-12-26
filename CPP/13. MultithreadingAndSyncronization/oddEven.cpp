#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class OddEven {
    int n;
    int currentNumber = 0;
    mutex m;
    condition_variable cv;

public:
    OddEven(int n) : n(n) {}

    void printOdd() {
        while (currentNumber <= n) {
            unique_lock<mutex> lock(m);

            cv.wait(lock, [&]() {
                return currentNumber % 2 == 1 || currentNumber > n;
            });

            if (currentNumber <= n) {
                cout << "Odd:  " << currentNumber << endl;
                currentNumber++;
            }

            cv.notify_all();
        }
    }

    void printEven() {
        while (currentNumber <= n) {
            unique_lock<mutex> lock(m);

            cv.wait(lock, [&]() {
                return currentNumber % 2 == 0 || currentNumber > n;
            });

            if (currentNumber <= n) {
                cout << "Even: " << currentNumber << endl;
                currentNumber++;
            }

            cv.notify_all();
        }
    }
};

int main() {
    OddEven obj(10);

    thread t1(&OddEven::printOdd, &obj);
    thread t2(&OddEven::printEven, &obj);

    t1.join();
    t2.join();

    return 0;
}
/* 
Even: 0
Odd:  1
Even: 2
Odd:  3
Even: 4
Odd:  5
Even: 6
Odd:  7
Even: 8
Odd:  9
Even: 10
*/