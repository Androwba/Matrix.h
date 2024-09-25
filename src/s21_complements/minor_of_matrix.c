#include "s21_calc_complements.h"

double minor_of_matrix(matrix_t *m) {
  return m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0];
}
