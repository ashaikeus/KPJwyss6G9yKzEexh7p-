#include "s21_matrix_oop.h"

int main() {
    S21Matrix A;
    S21Matrix B(2, 2);
    for (int i = 0; i < B.get_rows(); i++) {
        for (int j = 0; j < B.get_cols(); j++) {
            B.set_cell(i * B.get_cols() + j, i * B.get_cols() + j);
        }
    }
    // S21Matrix C(B);
    // C.Print();
    // B.Print();
    // S21Matrix D(B + B);
    // D.Print();
    // B.Print();
    // S21Matrix E(B * 5);
    // E.Print();
    // S21Matrix F = B * E;
    // F.Print();
    // S21Matrix G;
    // bool ageq = A == G;
    // bool afeq = A == F;
    // std::cout << ageq << std::endl;
    // std::cout << afeq << std::endl;
    // B *= 999;
    // B.Print();
    // B *= B;
    // B.Print();
    
    B.Print();
    B.Transpose();
    B.Print();

    std::cout << B.Determinant() << std::endl;

    S21Matrix H(3, 3);
    for (int i = 0; i < H.get_rows(); i++) {
        for (int j = 0; j < H.get_cols(); j++) {
            H.set_cell(i * H.get_cols() + j, i * H.get_cols() + j + 1);
        }
    }
    H.set_cell(8, 0);
    H.Print();
    std::cout << H.Determinant() << std::endl;

    return 0;
}