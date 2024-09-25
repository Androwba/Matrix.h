#include "s21_mult.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int resulting_code = correctness_of_the_matrix(A);
  if (resulting_code == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return resulting_code;
}
