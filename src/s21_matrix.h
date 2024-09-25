#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#include "s21_adding_subtracting/s21_add_sub_header.h"
#include "s21_comparison/s21_eq_matrix.h"
#include "s21_complements/s21_calc_complements.h"
#include "s21_create_remove/s21_create.h"
#include "s21_inverse/s21_inverse_matrix.h"
#include "s21_multiplication/s21_mult.h"
#include "s21_transpose/s21_transpose.h"

#define s21_NULL (void *)0

typedef enum { OK, INCORRECT_MATRIX, CALCULATION_ERROR } resulting_code;

#endif  // SRC_S21_MATRIX_H_
