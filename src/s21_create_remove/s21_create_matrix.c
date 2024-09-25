#include "s21_create.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int resulting_code = 0;
  if (rows <= 0 || columns <= 0) {
    resulting_code = INCORRECT_MATRIX;
  } else {
    result->matrix = malloc(rows * sizeof(double *));
    // if (result->matrix == s21_NULL) {
    //   fprintf(stderr, "Out Of Memory");
    //   exit(EXIT_FAILURE);
    // }

    for (int i = 0; i < rows; i++) {
      result->matrix[i] = malloc(columns * sizeof(double));
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0.0;
      }
    }
    result->rows = rows;
    result->columns = columns;
    resulting_code = OK;
  }
  return resulting_code;
}
