#include "s21_calc_complements.h"

double determ_helper(matrix_t *m) {
  double value = 0;
  if (m->rows == 2 && m->columns == 2) {
    value = minor_of_matrix(m);
  } else {
    for (int j = 0; j < m->columns; j++) {
      matrix_t tmp;
      s21_create_matrix(m->rows - 1, m->columns - 1, &tmp);
      reduce(m, 0, j, &tmp);
      int x = j % 2 == 0 ? 1 : -1;
      if (tmp.rows == 2) {
        value += x * m->matrix[0][j] * minor_of_matrix(&tmp);
      } else {
        value += x * m->matrix[0][j] * determ_helper(&tmp);
      }
      s21_remove_matrix(&tmp);
    }
  }
  return value;
}
