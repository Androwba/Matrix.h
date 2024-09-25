#include "s21_inverse_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;
  double determinant = 0.0;
  memset(result, 0, sizeof(matrix_t));
  flag = s21_determinant(A, &determinant);
  if (fabs(determinant) < s21_EPS && flag == OK) {
    flag = CALCULATION_ERROR;
  } else if (flag == OK) {
    matrix_t comp_temp;
    s21_calc_complements(A, &comp_temp);
    matrix_t tran_temp;
    s21_transpose(&comp_temp, &tran_temp);
    s21_remove_matrix(&comp_temp);
    s21_mult_number(&tran_temp, 1.0 / determinant, result);
    s21_remove_matrix(&tran_temp);
  }
  return flag;
}
