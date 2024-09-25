#include "s21_add_sub_header.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int resulting_code = 0;
  if (correctness_of_the_matrix(A) != OK ||
      correctness_of_the_matrix(B) != OK) {
    resulting_code = INCORRECT_MATRIX;
  } else if (A->columns == B->columns && A->rows == B->rows) {
    resulting_code = s21_create_matrix(A->rows, A->columns, result);
    if (resulting_code == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    resulting_code = CALCULATION_ERROR;
  }
  return resulting_code;
}
