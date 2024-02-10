#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
    matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(int n) : rows_(n), cols_(n) {
    if (n <= 0) std::cout << "Invalid size for a square matrix" << std::endl;
    matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(int r, int c) : rows_(r), cols_(c) {
    if (r <= 0 || c <= 0) std::cout << "Invalid size" << std::endl;
    matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.get_rows()), cols_(other.get_cols()) {
    matrix_ = new double[rows_ * cols_]{};
    std::copy_n(other.matrix_, rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    matrix_ = new double[rows_ * cols_]{};
    std::copy_n(other.matrix_, rows_ * cols_, matrix_);
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    cols_ = 0;
    rows_ = 0;
    delete[] matrix_;
}

int S21Matrix::get_rows() const { return rows_; }

int S21Matrix::get_cols() const { return cols_; }

double S21Matrix::get_cell(int index) const { return matrix_[index]; }

void S21Matrix::set_rows(int number) { 
    if (number < 1) std::cout << "Invalid number of rows" << std::endl;
    else rows_ = number;
}

void S21Matrix::set_cols(int number) {
    if (number < 1) std::cout << "Invalid number of columns" << std::endl;
    else cols_ = number;
}

void S21Matrix::set_cell(int index, double number) {
    matrix_[index] = number;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) std::cout << "Invalid matrices" << std::endl;
    else if ((rows_ != other.get_rows()) || (cols_ != other.get_cols())) std::cout << "Invalid matrix size" << std::endl;
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] + other.matrix_[i * other.get_cols() + j];
            }
        }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) std::cout << "Invalid matrices" << std::endl;
    else if ((rows_ != other.get_rows()) || (cols_ != other.get_cols())) std::cout << "Invalid matrix size" << std::endl;
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] - other.matrix_[i * other.get_cols() + j];
            }
        }
}

void S21Matrix::MulNumber(const double num) {
    if (IsIncorrect()) std::cout << "Invalid matrix" << std::endl;
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] * num;
            }
        }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) std::cout << "Invalid matrices" << std::endl;
    else if ((cols_ != other.get_rows())) std::cout << "Invalid matrix size" << std::endl;
    else {
        S21Matrix result(rows_, other.get_cols());
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < other.get_cols(); j++) {
                for (int k = 0; k < other.get_rows(); k++) {
                    result.matrix_[i * cols_ + j] += matrix_[i * cols_ + k] * other.get_cell(k * other.get_cols() + j);
                }
            }
        }
        *this = result;
    }
}

// S21Matrix S21Matrix::Transpose();
// S21Matrix S21Matrix::CalcComplements();
// double S21Matrix::Determinant();
// S21Matrix S21Matrix::InverseMatrix();

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool ret = true;
    if ((rows_ != other.get_rows()) || (cols_ != other.get_cols()))
        ret = false;
    else
        for (int i = 0; i < rows_ && ret; i++)
        for (int j = 0; j < cols_ && ret; j++) {
            if (fabs((*this)(i, j) - other.get_cell(i * cols_ + j)) > S21_EPS) ret = false;
        }
    return ret;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result = *this;
    result.SumMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result = *this;
    result.SubMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result = *this;
    result.MulNumber(num);
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result = *this;
    result.MulMatrix(other);
    return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return EqMatrix(other);
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
    rows_ = other.get_rows();
    cols_ = other.get_cols();
    std::copy_n(other.matrix_, rows_ * cols_, matrix_);
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
    MulNumber(num);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

double S21Matrix::operator()(int r, int c) {
    if (r < 0 || c < 0 || r >= rows_ || c >= cols_) std::cout << "Index outside of matrix" << std::endl;
    return matrix_[r * cols_ + c];
}

bool S21Matrix::IsIncorrect() const {
    return !(cols_ > 0 && rows_ > 0);
}

// void S21Matrix::GetMinorMatrix(const S21Matrix& M, int row, int col, S21Matrix& result) {
//     result = S21Matrix(M->rows - 1, M->columns - 1);
//     for (int r = 0, i = 0; r < M->rows - 1; r++) {
//         for (int c = 0, j = 0; c < M->columns - 1; c++) {
//             if (r == row) i = 1;
//             if (c == col) j = 1;
//             result->matrix[r][c] = M->matrix[r + i][c + j];
//         }
//     }
// }

// double S21Matrix::DetProcessing(const S21Matrix& A) {
//   int sign = 1;
//   double temp = 0.0;
//   if (rows_ == 1) return A->matrix[0][0];
//   if (rows_ == 2)
//     return (A->matrix[0][0] * A->matrix[1][1]) -
//            (A->matrix[1][0] * A->matrix[0][1]);
//   for (int j = 0; j < A->columns; j++) {
//     matrix_t minored = {0};
//     GetMinorMatrix(A, 0, j, &minored);
//     temp += A->matrix[0][j] * DetProcessing(&minored) * sign;
//     s21_remove_matrix(&minored);
//     sign = -sign;
//   }
//   return temp;
// }

void S21Matrix::Print() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << matrix_[i * cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}