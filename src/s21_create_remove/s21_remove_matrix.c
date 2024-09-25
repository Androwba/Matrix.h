#include "s21_create.h"

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
  }
}
