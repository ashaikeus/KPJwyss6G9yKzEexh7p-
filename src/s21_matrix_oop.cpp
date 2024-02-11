#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
    matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(int n) : rows_(n), cols_(n) {
    if (n <= 0) throw std::length_error("Invalid size for a square matrix");
    matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(int r, int c) : rows_(r), cols_(c) {
    if (r <= 0 || c <= 0) throw std::length_error("Invalid size");
    matrix_ = new double[rows_ * cols_]{};
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.get_rows()), cols_(other.get_cols()) {
    if (rows_ <= 0 || cols_ <= 0) throw std::length_error("Invalid size");
    matrix_ = new double[rows_ * cols_]{};
    std::copy_n(other.matrix_, rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.get_rows()), cols_(other.get_cols()) {
    if (rows_ <= 0 || cols_ <= 0) throw std::length_error("Invalid size");
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
    if (number < 1) throw std::length_error("Invalid number of rows");
    else rows_ = number;
}

void S21Matrix::set_cols(int number) {
    if (number < 1) throw std::length_error("Invalid number of columns");
    else cols_ = number;
}

void S21Matrix::set_cell(int row, int col, double number) {
    matrix_[row * cols_ + col] = number;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) throw std::length_error("Invalid matrices");
    else if ((rows_ != other.get_rows()) || (cols_ != other.get_cols())) throw std::length_error("Invalid matrix size");
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] + other.matrix_[i * other.get_cols() + j];
            }
        }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) throw std::length_error("Invalid matrices");
    else if ((rows_ != other.get_rows()) || (cols_ != other.get_cols())) throw std::length_error("Invalid matrix size");
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] - other.matrix_[i * other.get_cols() + j];
            }
        }
}

void S21Matrix::MulNumber(const double num) {
    if (IsIncorrect()) throw std::length_error("Invalid matrix");
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] * num;
            }
        }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) throw std::length_error("Invalid matrices");
    else if ((cols_ != other.get_rows())) throw std::length_error("Invalid matrix size");
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

S21Matrix S21Matrix::Transpose() {
    S21Matrix result(cols_, rows_);
    if (IsIncorrect()) throw std::length_error("Invalid matrix");
    else {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                result.matrix_[j * cols_ + i] = (*this)(i, j);
            }
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    S21Matrix result(cols_, rows_);
    if (IsIncorrect()) throw std::length_error("Invalid matrix");
    else if (cols_ != rows_) throw std::length_error("Invalid matrix size");
    else if (cols_ == 1) result.matrix_[0] = (*this)(0, 0);
    else {
        S21Matrix temp(cols_, rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                temp.matrix_[i * cols_ + j] = (*this)(i, j);
            }
        }
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++) {
                S21Matrix minor(temp.GetMinorMatrix(i, j));
                double MinorDet = minor.Determinant();
                result.matrix_[i * cols_ + j] = pow(-1.0, i + j) * MinorDet;
            }
    }
    return result;
}

double S21Matrix::Determinant() {
    double result = 0.0 / 0.0;
    if (IsIncorrect()) throw std::length_error("Invalid matrix");
    else if (cols_ != rows_) throw std::length_error("Invalid matrix size");
    else {
        result = DetProcessing();
    }
    if (result < S21_EPS && result > -S21_EPS) result = 0.0;
    return result;
}

double S21Matrix::DetProcessing() {
    int sign = 1;
    double temp = 0.0;
    if (rows_ == 1) return (*this)(0, 0);
    else if (rows_ == 2) return ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
    else for (int j = 0; j < cols_; j++) {
        S21Matrix minor(GetMinorMatrix(0, j));
        temp += (*this)(0, j) * minor.DetProcessing() * sign;
        sign = -sign;
    }
    return temp;
}

S21Matrix S21Matrix::InverseMatrix() {
    return *this;
}

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
    if (r < 0 || c < 0 || r >= rows_ || c >= cols_) throw std::length_error("Index outside of matrix");
    return matrix_[r * cols_ + c];
}

bool S21Matrix::IsIncorrect() const {
    return !(cols_ > 0 && rows_ > 0);
}

S21Matrix S21Matrix::GetMinorMatrix(int avoidRow, int avoidCol) {
    S21Matrix result(rows_ - 1, cols_ - 1);
    bool rowSkip = false;
    bool colSkip = false;
    for (int r = 0; r < rows_ - 1; r++) {
        if (r == avoidRow) rowSkip = true;
        for (int c = 0; c < cols_ - 1; c++) {
            if (c == avoidCol) colSkip = true;
            result.set_cell(r, c, (*this)(r + rowSkip, c + colSkip));
        }
        colSkip = false;
    }
    return result;
}

void S21Matrix::Print() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << matrix_[i * cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}