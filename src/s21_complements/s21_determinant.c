#include "s21_calc_complements.h"

int s21_determinant(matrix_t *A, double *result) {
  int resulting_code = correctness_of_the_matrix(A);
  if (A->rows == 1 && A->columns == 1) {
    *result = A->matrix[0][0];
  } else if (!resulting_code && A->columns == A->rows) {
    *result = determ_helper(A);
  } else if (!resulting_code &&
             (A->columns > A->rows || A->columns < A->rows)) {
    resulting_code = 2;
  }
  return resulting_code;
}
