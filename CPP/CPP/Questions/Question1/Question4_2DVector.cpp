/* 
2DVector

Question 4: Given a vector of integers, write a C++ function to find the maximum and minimum elements in the vector 
without using any built-in functions like std::max_element or std::min_element. 

This program will calculate the sum of all elements in the 2D vector and display the result, which in this example, 
would be 45 (1+2+3+4+5+6+7+8+9).

Sample Input : nums = {23, 12, 56, 9, 45, 37};
Expected output : Maximum Element: 56
		          Minimum Element: 9

*/



#include <iostream>
#include <vector>
using namespace std;
// Function to find max and min without using built-in functions
void findMaxMin(const vector<int>& nums, int& maxVal, int& minVal) {
    if (nums.empty()) return;
    maxVal = nums[0];
    minVal = nums[0];
    for (int num : nums) {
        if (num > maxVal) maxVal = num;
        if (num < minVal) minVal = num;
    }
}
// Function to calculate total sum of a 2D vector
int sum2DVector(const vector<vector<int>>& mat) {
    int sum = 0;
    for (const auto& row : mat) {
        for (int val : row) {
            sum += val;
        }
    }
    return sum;
}
int main() {
    // Example input vector
    vector<int> nums = {23, 12, 56, 9, 45, 37};
    int maxVal, minVal;
    findMaxMin(nums, maxVal, minVal);
    cout << "Maximum Element: " << maxVal << endl;
    cout << "Minimum Element: " << minVal << endl;
    // Example 2D vector
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int totalSum = sum2DVector(matrix);
    cout << "Sum of 2D Vector: " << totalSum << endl;
  return 0;
}
/*
Maximum Element: 56
Minimum Element: 9
Sum of 2D Vector: 45
*/