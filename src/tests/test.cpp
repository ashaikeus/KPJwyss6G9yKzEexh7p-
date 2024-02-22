#include "../s21_matrix_oop.h"
#include "gtest/gtest.h"


TEST(MatrixConstructorSuite, BasicTest) {
  S21Matrix testMatrix;
  EXPECT_EQ(testMatrix.getCols(), 2);
  EXPECT_EQ(testMatrix.getRows(), 2);
}

TEST(MatrixConstructorSuite, NormalTest) {
  S21Matrix testMatrix(3, 5);
  EXPECT_EQ(testMatrix.getCols(), 5);
  EXPECT_EQ(testMatrix.getRows(), 3);
}

TEST(MatrixConstructorSuite, MoveTest) {
  S21Matrix testMatrix(3, 5);
  S21Matrix testMatrix2(std::move(testMatrix));
  EXPECT_EQ(testMatrix.getCols(), 0);
  EXPECT_EQ(testMatrix.getRows(), 0);
}

TEST(MatrixConstructorSuite, ErrorTest) {
  ASSERT_ANY_THROW(S21Matrix m(-1, -1));
}

TEST(MatrixConstructorSuite, SetRowsTest) {
  S21Matrix testMatrix;
  testMatrix.setCell(1, 1, 3);

  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 3.0);

  testMatrix.setRows(3);
  EXPECT_EQ(testMatrix.getRows(), 3);

  // EXPECT_DOUBLE_EQ(testMatrix(1, 1), 3.0);
  // EXPECT_DOUBLE_EQ(testMatrix(2, 1), 0.0);
}

TEST(MatrixConstructorSuite, SetWrongTest) {
  S21Matrix testMatrix(5, 5);
  ASSERT_ANY_THROW(testMatrix.setCols(-5));
  ASSERT_ANY_THROW(testMatrix.setRows(-2));
  ASSERT_ANY_THROW(testMatrix.setRows(0));
}

TEST(MatrixArithmeticSuite, EqualTest) {
  S21Matrix testMatrix;
  S21Matrix testMatrix2;
  EXPECT_TRUE(testMatrix.EqMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, NotEqualTest) {
  S21Matrix testMatrix;
  S21Matrix testMatrix2;
  testMatrix.setCell(1, 1, 12);
  EXPECT_FALSE(testMatrix == testMatrix2);
}

TEST(MatrixArithmeticSuite, NotEqualColCountTest) {
  S21Matrix testMatrix(2, 2);
  S21Matrix testMatrix2(2, 3);
  EXPECT_FALSE(testMatrix.EqMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, SumTest) {
  S21Matrix testMatrix(2, 2);
  S21Matrix testMatrix2(2, 2);

  for (int i = 0; i < testMatrix.getRows() && i < testMatrix.getCols(); i++) {
    testMatrix.setCell(i, i, 3);
    testMatrix2.setCell(i, i, 4);
  }

  testMatrix.SumMatrix(testMatrix2);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 7);

  testMatrix.setCols(5);
  ASSERT_ANY_THROW(testMatrix.SumMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, SubTest) {
  S21Matrix testMatrix(2, 2);
  S21Matrix testMatrix2(2, 2);

  for (int i = 0; i < testMatrix.getRows() && i < testMatrix.getCols(); i++) {
    testMatrix.setCell(i, i, 3);
    testMatrix2.setCell(i, i, 4);
  }

  testMatrix.SubMatrix(testMatrix2);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), -1);

  testMatrix.setCols(5);
  ASSERT_ANY_THROW(testMatrix.SubMatrix(testMatrix2));
}

TEST(MatrixArithmeticSuite, MulNumberTest) {
  S21Matrix testMatrix(3, 3);

  testMatrix.setCell(1, 1, 3);

  testMatrix.MulNumber(6);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 18);
}

TEST(MatrixArithmeticSuite, MulMatrixTest) {
  S21Matrix testMatrix(3, 2);
  S21Matrix testMatrix2(2, 3);

  for (int i = 0; i < testMatrix.getRows(); i++) {
    for (int j = 0; j < testMatrix.getCols(); j++) {
      testMatrix.setCell(i, j, 3);
      testMatrix2.setCell(j, i, 4);
    }
  }

  testMatrix.MulMatrix(testMatrix2);
  EXPECT_DOUBLE_EQ(testMatrix(1, 1), 24);
}

TEST(MatrixArithmeticSuite, MulMatrixErrorTest) {
  S21Matrix testMatrix(2, 4);
  S21Matrix testMatrix2(3, 2);
  ASSERT_ANY_THROW(testMatrix.MulMatrix(testMatrix2));
}

TEST(MatrixFunctionSuite, TransposeTest) {
  S21Matrix testMatrix(2, 3);
  testMatrix.setCell(0, 2, 3);
  S21Matrix result(testMatrix.Transpose());

  EXPECT_EQ(result.getRows(), 3);
  EXPECT_EQ(result.getCols(), 2);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
}

TEST(MatrixFunctionSuite, DeterminantNormalTest) {
  S21Matrix testMatrix(1, 1);
  testMatrix.setCell(0, 0, 1);
  double myDet = testMatrix.Determinant();
  EXPECT_DOUBLE_EQ(myDet, 1.0);

  testMatrix.setRows(3);
  testMatrix.setCols(3);
  for (int i = 0; i < testMatrix.getRows(); i++) {
    for (int j = 0; j < testMatrix.getCols(); j++) {
      testMatrix.setCell(i, j, 3);
    }
  }
  myDet = testMatrix.Determinant();
  EXPECT_DOUBLE_EQ(myDet, 0.0);

  testMatrix.setCell(0, 0, -0.00345);
  testMatrix.setCell(2, 2, 47);
  myDet = testMatrix.Determinant();
  EXPECT_DOUBLE_EQ(myDet, -396.4554);
}

TEST(MatrixFunctionSuite, DeterminantNotSquareTest) {
  S21Matrix testMatrix(3, 2);
  ASSERT_ANY_THROW(testMatrix.Determinant());
}

TEST(MatrixFunctionSuite, CalcComplementsErrorTest) {
  S21Matrix testMatrix(1, 2);
  EXPECT_ANY_THROW(testMatrix.CalcComplements());
}

TEST(MatrixFunctionSuite, CalcComplementsTest) {
  S21Matrix testMatrix;
  S21Matrix testMatrix2;
  S21Matrix testMatrix3;

  testMatrix.setCell(0, 0, 1);
  testMatrix.setCell(0, 1, 2);
  testMatrix.setCell(1, 0, 3);
  testMatrix.setCell(1, 1, 4);

  testMatrix3.setCell(0, 0, 4);
  testMatrix3.setCell(0, 1, -3);
  testMatrix3.setCell(1, 0, -2);
  testMatrix3.setCell(1, 1, 1);

  testMatrix2 = testMatrix.CalcComplements();
  EXPECT_TRUE(testMatrix2.EqMatrix(testMatrix3));
}

TEST(MatrixFunctionSuite, CalcComplements2Test) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);
  S21Matrix testMatrix3(3, 3);

  testMatrix.setCell(0, 0, 1);
  testMatrix.setCell(0, 1, 2);
  testMatrix.setCell(0, 2, 3);
  testMatrix.setCell(1, 0, 0);
  testMatrix.setCell(1, 1, 4);
  testMatrix.setCell(1, 2, 2);
  testMatrix.setCell(2, 0, 5);
  testMatrix.setCell(2, 1, 2);
  testMatrix.setCell(2, 2, 1);

  testMatrix3.setCell(0, 0, 0);
  testMatrix3.setCell(0, 1, 10);
  testMatrix3.setCell(0, 2, -20);
  testMatrix3.setCell(1, 0, 4);
  testMatrix3.setCell(1, 1, -14);
  testMatrix3.setCell(1, 2, 8);
  testMatrix3.setCell(2, 0, -8);
  testMatrix3.setCell(2, 1, -2);
  testMatrix3.setCell(2, 2, 4);

  testMatrix2 = testMatrix.CalcComplements();
  EXPECT_TRUE(testMatrix2.EqMatrix(testMatrix3));
}

TEST(MatrixFunctionSuite, InverseMatrixErrorTest) {
  S21Matrix testMatrix(3, 3);
  EXPECT_ANY_THROW(testMatrix.InverseMatrix());
}

TEST(MatrixFunctionSuite, InverseMatrixBasicTest) {
  S21Matrix testMatrix(1, 1);
  testMatrix.setCell(0, 0, 2);
  testMatrix = testMatrix.InverseMatrix();
  EXPECT_DOUBLE_EQ(testMatrix(0, 0), 1.0 / 2.0);
}

TEST(MatrixFunctionSuite, InverseMatrixNormalTest) {
  S21Matrix testMatrix(3, 3);
  double array[9]{2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
  double arrayResult[9]{1.0, -1.0, 1.0, -38.0, 41.0, -34.0, 27.0, -29.0, 24.0};

  for (int i = 0; i < testMatrix.getRows(); i++) {
    for (int j = 0; j < testMatrix.getCols(); j++) {
      testMatrix.setCell(i, j, array[i * 3 + j]);
    }
  }
  testMatrix = testMatrix.InverseMatrix();
  for (int i = 0; i < testMatrix.getRows(); i++) {
    for (int j = 0; j < testMatrix.getCols(); j++) {
      EXPECT_DOUBLE_EQ(testMatrix(i, j), arrayResult[i * 3 + j]);
    }
  }
}

TEST(MatrixOperatorSuite, BracesOutOfIndexTest) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);

  ASSERT_ANY_THROW(testMatrix(4, 4));
}

TEST(MatrixOperatorSuite, PlusMinusTest) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);
  for (int i = 0; i < testMatrix.getRows(); i++) {
    for (int j = 0; j < testMatrix.getCols(); j++) {
      testMatrix.setCell(i, j, 3);
      testMatrix2.setCell(i, j, 4);
    }
  }
  S21Matrix resultMatrix = testMatrix + testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 7.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 7.0);

  resultMatrix += testMatrix;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 10.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 10.0);
  EXPECT_DOUBLE_EQ(testMatrix(2, 2), 3.0);
  EXPECT_DOUBLE_EQ(testMatrix2(2, 2), 4.0);

  resultMatrix = testMatrix - testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), -1.0);

  resultMatrix -= testMatrix;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), -4.0);
}

TEST(MatrixOperatorSuite, MultiplicationTest) {
  S21Matrix testMatrix(3, 3);
  S21Matrix testMatrix2(3, 3);
  for (int i = 0; i < testMatrix.getRows(); i++) {
    for (int j = 0; j < testMatrix.getCols(); j++) {
      testMatrix.setCell(i, j, 3);
      testMatrix2.setCell(i, j, 4);
    }
  }
  S21Matrix resultMatrix = testMatrix * -2.0;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), -6.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), -6.0);

  resultMatrix *= -(1.0 / 2.0);
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 3.0);

  for (int i = 0; i < testMatrix2.getRows(); i++) {
    for (int j = 0; j < testMatrix2.getCols(); j++) {
      testMatrix2.setCell(i, j, 3);
    }
  }
  resultMatrix = testMatrix * testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 27.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 27.0);

  testMatrix.setCols(2);
  testMatrix2.setRows(2);
  resultMatrix = testMatrix * testMatrix2;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 18.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 2), 18.0);


  for (int i = 0; i < resultMatrix.getRows(); i++) {
    for (int j = 0; j < resultMatrix.getCols(); j++) {
      resultMatrix.setCell(i, j, 4);
    }
  }
  resultMatrix *= testMatrix;
  EXPECT_DOUBLE_EQ(resultMatrix(0, 0), 36.0);
  EXPECT_DOUBLE_EQ(resultMatrix(2, 1), 36.0);
}

int main() {
  testing::InitGoogleTest();
  testing::GTEST_FLAG(filter) = "MatrixConstructorSuite*";
  return RUN_ALL_TESTS();
}