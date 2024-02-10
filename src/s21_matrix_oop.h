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

        int get_rows() const;
        int get_cols() const;
        double get_cell(int index) const;
        void set_rows(int number);
        void set_cols(int number);
        void set_cell(int index, double number);

        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);

        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();

        bool EqMatrix(const S21Matrix& other);

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

        bool IsIncorrect() const;
        // void GetMinorMatrix(const S21Matrix& M, int row, int col, S21Matrix& result);
        // double DetProcessing(const S21Matrix& A);

        void Print();
};