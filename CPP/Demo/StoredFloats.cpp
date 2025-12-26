/*=======================================
Write a class which is able to store any number of floats and have method which will return average of all stored floats,

Example of uses:
Average.avg;
avg.get_average(); //should return 0;
avg.push_back(3.0);
avg.push_back(9.0);
avg.get_average(); //should return 6.0 -> (3+9)/2;

========================================*/
#include <iostream>
#include <vector>
using namespace std;
class Average {
  private:
    vector<float> values;

  public:
    // Add a new value
    void push_back(float val) {
        values.push_back(val);
    }

    // Get the average of all stored values
    float get_average() const {
        if (values.empty())
            return 0.0f;

        float sum = 0.0f;
        for (float v : values)
            sum += v;

        return sum / values.size();
    }
};

int main() {
    Average avg;
    std::cout << avg.get_average() << std::endl; // 0
    avg.push_back(3.0f);
    avg.push_back(9.0f);

    std::cout << avg.get_average() << std::endl; // 6

    return 0;
}
/* 
0
6
*/




 
