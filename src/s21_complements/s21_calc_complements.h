#ifndef SRC_S21_COMPLEMENTS_S21_CALC_COMPLEMENTS_H_
#define SRC_S21_COMPLEMENTS_S21_CALC_COMPLEMENTS_H_

#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
double minor_of_matrix(matrix_t *m);
double determ_helper(matrix_t *m);
int reduce(matrix_t *A, int i_val, int j_val, matrix_t *minor);

#endif  // SRC_S21_COMPLEMENTS_S21_CALC_COMPLEMENTS_H_
