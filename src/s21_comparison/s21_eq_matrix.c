#include "s21_eq_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > s21_EPS) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}