#include "s21_calc_complements.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int resulting_code = correctness_of_the_matrix(A);
  if (resulting_code == OK && A->rows >= 2 && A->columns >= 2 &&
      A->columns == A->rows) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        matrix_t m;
        s21_create_matrix(A->rows - 1, A->columns - 1, &m);
        reduce(A, i, j, &m);
        if (m.rows >= 2 && m.columns >= 2) {
          result->matrix[i][j] = determ_helper(&m) * pow(-1, i + j);
        } else if (m.rows == 1 && m.columns == 1) {
          result->matrix[i][j] = m.matrix[0][0] * pow(-1, i + j);
        }
        s21_remove_matrix(&m);
      }
    }
  } else if ((resulting_code == OK && (A->rows < 2 || A->columns < 2)) ||
             (A->columns != A->rows && resulting_code == OK)) {
    resulting_code = CALCULATION_ERROR;
  }
  return resulting_code;
}
