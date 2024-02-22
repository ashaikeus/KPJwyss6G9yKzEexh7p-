#include <iostream>
#include <algorithm>
#include <cmath>

#define S21_EPS 1e-6

class S21Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double *matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        S21Matrix();              // Default constructor
        ~S21Matrix();             // Destructor
        S21Matrix(int n);
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);

        bool EqMatrix(const S21Matrix& other);
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);

        bool IsIncorrect() const;
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        double DetProcessing();
        S21Matrix InverseMatrix();
        S21Matrix GetMinorMatrix(int row, int col);

        int getRows() const;
        int getCols() const;
        double getCell(int index) const;
        void setRows(int number);
        void setCols(int number);
        void setCell(int row, int col, double number);

        S21Matrix operator+(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator*(const double num);
        S21Matrix operator*(const S21Matrix& other);
        bool operator==(const S21Matrix& other);
        S21Matrix operator=(const S21Matrix& other);
        S21Matrix& operator+=(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);
        S21Matrix& operator*=(const double num);
        S21Matrix& operator*=(const S21Matrix& other);
        double operator()(int r, int c);

        void Print();
};