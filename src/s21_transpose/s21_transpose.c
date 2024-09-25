#include "s21_transpose.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int resulting_code = 0;
  if (correctness_of_the_matrix(A)) {
    resulting_code = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int row = 0; row < A->rows; row++) {
      for (int column = 0; column < A->columns; column++) {
        result->matrix[column][row] = A->matrix[row][column];
      }
    }
  }
  return resulting_code;
}
