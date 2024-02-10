#include "s21_matrix_oop.h"

int main() {
    S21Matrix A;
    S21Matrix B(2, 2);
    for (int i = 0; i < B.get_rows(); i++) {
        for (int j = 0; j < B.get_cols(); j++) {
            B.set_cell(i * B.get_cols() + j, i + j);
        }
    }
    S21Matrix C(B);
    C.Print();
    B.Print();
    S21Matrix D(B + B);
    D.Print();
    B.Print();
    S21Matrix E(B * 5);
    E.Print();
    S21Matrix F = B * E;
    F.Print();
    S21Matrix G;
    bool ageq = A == G;
    bool afeq = A == F;
    std::cout << ageq << std::endl;
    std::cout << afeq << std::endl;
    B *= 999;
    B.Print();
    B *= B;
    B.Print();
    return 0;
}