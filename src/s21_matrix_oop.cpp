#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
    matrix_ = new double[rows_ * cols_]{};
    Initialize();
}

S21Matrix::S21Matrix(int n) : rows_(n), cols_(n) {
    if (n <= 0) throw std::length_error("Invalid size for a square matrix");
    matrix_ = new double[rows_ * cols_]{};
    Initialize();
}

S21Matrix::S21Matrix(int r, int c) : rows_(r), cols_(c) {
    if (r <= 0 || c <= 0) throw std::length_error("Invalid size");
    matrix_ = new double[rows_ * cols_]{};
    Initialize();
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.getRows()), cols_(other.getCols()), matrix_(other.matrix_) {
    if (rows_ <= 0 || cols_ <= 0) throw std::length_error("Invalid size");
    matrix_ = new double[rows_ * cols_]{};
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            setCell(i, j, other.getCell(i * cols_ + j));
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.getRows()), cols_(other.getCols()), matrix_(other.matrix_) {
    if (rows_ <= 0 || cols_ <= 0) throw std::length_error("Invalid size");
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    cols_ = 0;
    rows_ = 0;
    delete[] matrix_;
    matrix_ = nullptr;
}

void S21Matrix::Initialize() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            (*this).setCell(i, j, 0);
        }
    }
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

double S21Matrix::getCell(int index) const { 
    if (index < 0 || index >= rows_ * cols_) throw std::length_error("Invalid index");
    return matrix_[index]; }

void S21Matrix::setRows(int number) { 
    if (number < 1) throw std::length_error("Invalid number of rows");
    S21Matrix newMatrix(number, getCols());
    for (int i = 0; i < number && i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            newMatrix.setCell(i, j, (*this)(i, j));
        }
    }
    (*this) = newMatrix;
}

void S21Matrix::setCols(int number) {
    if (number < 1) throw std::length_error("Invalid number of columns");
    S21Matrix newMatrix(getRows(), number);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < number && j < cols_; j++) {
            newMatrix.setCell(i, j, (*this)(i, j));
        }
    }
    (*this) = newMatrix;
}

void S21Matrix::setCell(int row, int col, double number) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) matrix_[row * cols_ + col] = number;
    else {
        std::cout << "row: " << row << ", col: " << col << std::endl;
        throw std::length_error("Invalid index");
    }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) throw std::length_error("Invalid matrices");
    else if ((rows_ != other.getRows()) || (cols_ != other.getCols())) throw std::length_error("Different matrix dimensions");
    else {
        for (int i = 0; i < rows_ && i < other.getRows(); i++)
            for (int j = 0; j < cols_ && j < other.getCols(); j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] + other.matrix_[i * other.getCols() + j];
            }
        }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (IsIncorrect() || other.IsIncorrect()) throw std::length_error("Invalid matrices");
    else if ((rows_ != other.getRows()) || (cols_ != other.getCols())) throw std::length_error("Different matrix dimensions");
    else {
        for (int i = 0; i < rows_ && i < other.getRows(); i++)
            for (int j = 0; j < cols_ && j < other.getCols(); j++) {
                matrix_[i * cols_ + j] = matrix_[i * cols_ + j] - other.matrix_[i * other.getCols() + j];
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
    else if ((cols_ != other.getRows())) throw std::length_error("The number of columns of the first matrix is not equal to the number of rows of the second matrix");
    else {
        S21Matrix result(rows_, other.getCols());
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < other.getCols(); j++) {
                for (int k = 0; k < other.getRows(); k++) {
                    result.matrix_[i * other.getCols() + j] += matrix_[i * cols_ + k] * other.getCell(k * other.getCols() + j);
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
                result.setCell(j, i, (*this)(i, j));
            }
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    S21Matrix result(cols_, rows_);
    if (IsIncorrect()) throw std::length_error("Invalid matrix");
    else if (cols_ != rows_) throw std::length_error("The matrix is not square");
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
    else if (cols_ != rows_) throw std::length_error("The matrix is not square");
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
    int det = Determinant();
    if (IsIncorrect()) throw std::length_error("Invalid matrix");
    else if (fabs(det) < S21_EPS) throw std::length_error("Can't inverse: determinant equals 0");
    else if (cols_ != rows_) throw std::length_error("Can't inverse: matrix is not square");

    S21Matrix result(rows_, cols_);
    if (rows_ == 1)
        result.setCell(0, 0, 1.0 / (*this)(0, 0));
    else {
        S21Matrix temp(rows_, cols_);
        result = CalcComplements();
        result = result.Transpose();
        result.MulNumber(1.0 / det);
    }
    return result;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool ret = true;
    if ((rows_ != other.getRows()) || (cols_ != other.getCols()))
        ret = false;
    else
        for (int i = 0; i < rows_ && ret; i++)
        for (int j = 0; j < cols_ && ret; j++) {
            if (fabs((*this)(i, j) - other.getCell(i * cols_ + j)) > S21_EPS) ret = false;
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

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        if (matrix_ != nullptr) {
            delete[] matrix_;
        }
        rows_ = other.getRows();
        cols_ = other.getCols();
        matrix_ = new double[rows_ * cols_]{};
        for (int i = 0; i < rows_ && i < other.getRows(); i++)
            for (int j = 0; j < cols_ && j < other.getCols(); j++) {
                (*this).setCell(i, j, other.getCell(i * cols_ + j));
            }
        }
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
    else return matrix_[r * cols_ + c];
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
            result.setCell(r, c, (*this)(r + rowSkip, c + colSkip));
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