/* 
2DVector

Question 4: Given a vector of integers, write a C++ function to find the maximum and minimum elements in the vector without using any built-in functions like std::max_element or std::min_element. This program will calculate the sum of all elements in the 2D vector and display the result, which in this example, would be 45 (1+2+3+4+5+6+7+8+9).

Sample Input : nums = {23, 12, 56, 9, 45, 37};

Expected output : Maximum Element: 56
		  Minimum Element: 9

*/

#include <iostream>
#include <vector>
using namespace std;

// Function to find maximum element
int findMax(const vector<int>& nums) {
    if (nums.empty()) throw runtime_error("Vector is empty");
    int maxVal = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    return maxVal;
}

// Function to find minimum element
int findMin(const vector<int>& nums) {
    if (nums.empty()) throw runtime_error("Vector is empty");
    int minVal = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] < minVal) minVal = nums[i];
    }
    return minVal;
}

// Function to calculate sum of 2D vector
int sum2DVector(const vector<vector<int>>& matrix) {
    int total = 0;
    for (const auto& row : matrix)
        for (int val : row)
            total += val;
    return total;
}

// ====================
// MAIN
// ====================
int main() {
    // Sample 1D vector
    vector<int> nums = {23, 12, 56, 9, 45, 37};

    cout << "Maximum Element: " << findMax(nums) << endl;
    cout << "Minimum Element: " << findMin(nums) << endl;

    // Sample 2D vector
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Sum of 2D vector: " << sum2DVector(matrix) << endl;

    return 0;
}
/* 
Maximum Element: 56
Minimum Element: 9
Sum of 2D vector: 45
*/