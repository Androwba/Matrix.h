#include "s21_calc_complements.h"

int reduce(matrix_t *A, int i_val, int j_val, matrix_t *minor) {
  int a = 0, b = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i_val != i) {
      for (int j = 0; j < A->columns; j++) {
        if (j_val != j) {
          minor->matrix[a][b] = A->matrix[i][j];
          b++;
        }
      }
      b = 0;
      a++;
    }
  }
  return 0;
}
