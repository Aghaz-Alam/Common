/* 
22. Template-based Matrix class (Templates, operator overloading)

Problem: Implement a generic Matrix<T> template class representing 2D matrices of arbitrary numeric type.

Requirements / Features:
Template class Matrix<T> with data stored in a flat std::vector<T>.
-Implement constructors:
Default constructor
Parameterized constructor (rows, cols)
- Overload the operators:
+ for matrix addition
- for matrix subtraction
* for matrix multiplication
- Provide a print() method to display matrix elements.
- Use simple element access via operator() (without bounds checking).

Sample Input Scenario:
Create two 2x2 matrices A and B using the parameterized constructor.
Fill their elements.
Multiply the matrices.

Expected Output:
Display matrix A
Display matrix B
Display the resulting matrix after multiplication


Sample Code : 
Matrix<int> A(2, 2);
Matrix<int> B(2, 2);

// Fill matrix A
A(0,0) = 1; A(0,1) = 2;
A(1,0) = 3; A(1,1) = 4;

// Fill matrix B
B(0,0) = 5; B(0,1) = 6;
B(1,0) = 7; B(1,1) = 8;

cout << "Matrix A:" << endl;
A.print();

cout << "Matrix B:" << endl;
B.print();

// Multiply A * B
Matrix<int> C = A * B;
cout << "Matrix A * B:" << endl;
C.print();

Expected Output : 
Matrix A:
1 2
3 4
Matrix B:
5 6
7 8
Matrix A * B:
19 22
43 50

*/


#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class Matrix {
  private:
    size_t rows, cols;
    vector<T> data;

  public:
    // Default constructor
    Matrix() : rows(0), cols(0) {}

    // Parameterized constructor
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c) {}

    // Element access without bounds checking
    T& operator()(size_t r, size_t c) {
        return data[r * cols + c];
    }

    const T& operator()(size_t r, size_t c) const {
        return data[r * cols + c];
    }

    // Matrix addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < other.cols; j++) {
                result(i, j) = 0;
                for (size_t k = 0; k < cols; k++) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }

        return result;
    }

    // Print matrix
    void print() const {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                cout << (*this)(i, j) << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Matrix<int> A(2, 2);
    Matrix<int> B(2, 2);

    // Fill matrix A
    A(0,0) = 1; A(0,1) = 2;
    A(1,0) = 3; A(1,1) = 4;

    // Fill matrix B
    B(0,0) = 5; B(0,1) = 6;
    B(1,0) = 7; B(1,1) = 8;

    cout << "Matrix A:" << endl;
    A.print();

    cout << "Matrix B:" << endl;
    B.print();

    // Multiply A * B
    Matrix<int> C = A * B;

    cout << "Matrix A * B:" << endl;
    C.print();

  return 0;
}
/*
Matrix A:
1 2
3 4
Matrix B:
5 6
7 8
Matrix A * B:
19 22
43 50
*/