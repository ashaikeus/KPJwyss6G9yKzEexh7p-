#include "s21_matrix_oop.h"

int main() {
  S21Matrix A;
  S21Matrix B(2, 2);
  for (int i = 0; i < B.get_rows(); i++) {
    for (int j = 0; j < B.get_cols(); j++) {
      B.set_cell(i, j, i * B.get_cols() + j);
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

  S21Matrix H(5, 5);
  for (int i = 0; i < H.get_rows(); i++) {
    for (int j = 0; j < H.get_cols(); j++) {
      H.set_cell(i, j, 0);
    }
  }
  H.set_cell(0, 0, 1);
  H.set_cell(1, 1, 3);
  H.set_cell(2, 2, -2);
  H.set_cell(3, 3, 1);
  H.set_cell(4, 4, 1);
  H.Print();
  std::cout << H.Determinant() << std::endl;
  (H.InverseMatrix()).Print();

  return 0;
}