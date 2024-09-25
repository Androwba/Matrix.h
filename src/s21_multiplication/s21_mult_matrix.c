#include "s21_mult.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int resulting_code = 0;
  if (correctness_of_the_matrix(A) || correctness_of_the_matrix(B)) {
    resulting_code = INCORRECT_MATRIX;
  } else if (A->rows > 0 && B->columns > 0 && A->columns == B->rows) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else {
    resulting_code = CALCULATION_ERROR;
  }
  return resulting_code;
}
