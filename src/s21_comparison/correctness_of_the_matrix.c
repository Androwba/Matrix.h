#include "s21_eq_matrix.h"

int correctness_of_the_matrix(matrix_t *A) {
  int resulting_code = 0;
  if (A == s21_NULL || (A->rows < 1 || A->columns < 1)) {
    resulting_code = INCORRECT_MATRIX;
  } else {
    resulting_code = OK;
  }
  return resulting_code;
}
