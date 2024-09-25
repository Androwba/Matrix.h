#include <check.h>

#include "s21_matrix.h"

START_TEST(create_1) {
  int rows = 3;
  int columns = 3;
  int resulting_code = OK;
  matrix_t result;

  int check = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(rows, result.rows);
  ck_assert_int_eq(columns, result.columns);
  ck_assert_int_eq(resulting_code, check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_2) {
  int rows = 10;
  int columns = 0;
  int resulting_code = INCORRECT_MATRIX;
  matrix_t result;

  int check = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(resulting_code, check);
}
END_TEST

START_TEST(create_3) {
  int rows = 01;
  int columns = 0;
  int resulting_code = INCORRECT_MATRIX;
  matrix_t result;

  int check = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(resulting_code, check);
}
END_TEST

START_TEST(create_4) {
  int rows = -1;
  int columns = 7;
  int resulting_code = INCORRECT_MATRIX;
  matrix_t result;

  int check = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(resulting_code, check);
}
END_TEST

START_TEST(create_5) {
  int rows = 99;
  int columns = 500;
  int resulting_code = OK;
  matrix_t result;

  int check = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(rows, result.rows);
  ck_assert_int_eq(columns, result.columns);
  ck_assert_int_eq(resulting_code, check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_6) {
  int rows = 0;
  int columns = 0;
  int resulting_code = INCORRECT_MATRIX;
  matrix_t result;

  int check = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(resulting_code, check);
}
END_TEST

// -----------------------------------------------------------------------EQ_MATRIX-----------------------------------------------------------------------

START_TEST(eq_matrix_1) {
  matrix_t test1, test2;

  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(5, 5, &test2);
  test1.matrix[0][0] = 1;
  int code = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(code, FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  code = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// -----------------------------------------------------------------------SUB_MATRIX-----------------------------------------------------------------------

START_TEST(sub_matrix_1) {
  matrix_t m1;
  matrix_t m2;
  matrix_t origin;
  matrix_t r;
  int check_origin = 0;
  int check_1 = s21_create_matrix(3, 3, &m1);
  int check_2 = s21_create_matrix(3, 3, &m2);
  int check_3 = s21_create_matrix(3, 3, &origin);
  m1.matrix[0][0] = 0.1;
  m1.matrix[0][1] = 0.2;
  m1.matrix[0][2] = 0.3;
  m1.matrix[1][0] = 0.4;
  m1.matrix[1][1] = 0.5;
  m1.matrix[1][2] = 0.6;
  m1.matrix[2][0] = 0.7;
  m1.matrix[2][1] = 0.8;
  m1.matrix[2][2] = 0.9;
  m2.matrix[0][0] = 1.0;
  m2.matrix[0][1] = 2.0;
  m2.matrix[0][2] = 3.0;
  m2.matrix[1][0] = 4.0;
  m2.matrix[1][1] = 5.0;
  m2.matrix[1][2] = 6.0;
  m2.matrix[2][0] = 7.0;
  m2.matrix[2][1] = 8.0;
  m2.matrix[2][2] = 9.0;
  origin.matrix[0][0] = -0.9;
  origin.matrix[0][1] = -1.8;
  origin.matrix[0][2] = -2.7;
  origin.matrix[1][0] = -3.6;
  origin.matrix[1][1] = -4.5;
  origin.matrix[1][2] = -5.4;
  origin.matrix[2][0] = -6.3;
  origin.matrix[2][1] = -7.2;
  origin.matrix[2][2] = -8.1;
  int result = s21_sub_matrix(&m1, &m2, &r);
  ck_assert_int_eq(check_1, check_origin);
  ck_assert_int_eq(check_2, check_origin);
  ck_assert_int_eq(check_3, check_origin);
  ck_assert_int_eq(result, check_origin);
  for (int i = 0; i < r.rows; i++) {
    for (int j = 0; j < r.columns; j++) {
      ck_assert_double_eq_tol(origin.matrix[i][j], r.matrix[i][j], 1);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&r);
  s21_remove_matrix(&origin);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t test1, test2, result1, result2;
  int code1, code2;

  s21_create_matrix(1, 1, &test1);
  test1.rows = -1;

  s21_create_matrix(1, 1, &test2);

  code1 = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, INCORRECT_MATRIX);

  test1.rows = 1;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  code1 = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  s21_create_matrix(1, 1, &result2);
  test1.matrix[0][0] = 1;
  test2.matrix[0][0] = 1;
  code1 = s21_sub_matrix(&test1, &test2, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

// -----------------------------------------------------------------------SUM_MATRIX-----------------------------------------------------------------------

START_TEST(sum_matrix_1) {
  matrix_t result, B, A;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  B.matrix[0][0] = 3;
  B.matrix[0][1] = 3;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 3;
  int check = s21_sum_matrix(&A, &B, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      ck_assert_int_eq(result.matrix[i][j], 4);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t test1, test2, result1, result2;

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  s21_create_matrix(1, 1, &result2);

  test1.matrix[0][0] = 1;
  int code1 = s21_sum_matrix(&test1, &test2, &result1);

  result2.matrix[0][0] = 1;
  int code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, OK);
  ck_assert_int_eq(code2, SUCCESS);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  s21_create_matrix(1, 1, &test1);
  test1.rows = -1;
  s21_create_matrix(1, 1, &test2);

  code1 = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, INCORRECT_MATRIX);

  test1.rows = 1;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  code1 = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

// -----------------------------------------------------------------------MULT_NUMBER-----------------------------------------------------------------------

START_TEST(mult_number_1) {
  matrix_t test1, result1, result2;
  int number = 5;
  s21_create_matrix(1, 1, &test1);
  test1.matrix[0][0] = 1;
  s21_create_matrix(1, 1, &result2);
  result2.matrix[0][0] = 5;
  int code1 = s21_mult_number(&test1, number, &result1);
  int code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  test1.rows = -1;
  code1 = s21_mult_number(&test1, number, &result1);
  ck_assert_int_eq(code1, 1);
}
END_TEST

// -----------------------------------------------------------------------MULT_MATRIX-----------------------------------------------------------------------

START_TEST(mult_matrix_1) {
  matrix_t test1, test2, result1, result2;
  int code1, code2;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(1, 2, &test2);
  code1 = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(2, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  s21_create_matrix(2, 2, &result2);
  test1.matrix[0][0] = 2;
  test1.matrix[1][0] = 4;
  test2.matrix[0][0] = 1;
  test2.matrix[0][1] = 3;
  result2.matrix[0][0] = 2;
  result2.matrix[0][1] = 6;
  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = 12;
  code1 = s21_mult_matrix(&test1, &test2, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  test1.rows = -1;
  code1 = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 1);
}
END_TEST

// -----------------------------------------------------------------------TRANSPOSE-----------------------------------------------------------------------

START_TEST(transpose) {
  matrix_t test1, result1, result2;
  int code1, code2;

  s21_create_matrix(2, 2, &test1);
  test1.rows = -1;
  code1 = s21_transpose(&test1, &result1);
  ck_assert_int_eq(code1, INCORRECT_MATRIX);
  test1.rows = 2;
  s21_remove_matrix(&test1);

  s21_create_matrix(2, 2, &test1);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 2;
  test1.matrix[1][0] = 3;
  test1.matrix[1][1] = 4;
  s21_create_matrix(2, 2, &result2);
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = 3;
  result2.matrix[1][0] = 2;
  result2.matrix[1][1] = 4;

  code1 = s21_transpose(&test1, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, OK);
  ck_assert_int_eq(code2, SUCCESS);

  s21_remove_matrix(&test1);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

// --------------------------------------------------------------------CALC_COMPLEMENTS---------------------------------------------------------------------

START_TEST(calc_complements) {
  matrix_t test, result1, result2;
  int code1 = 0, code2 = 0;

  s21_create_matrix(2, 4, &test);
  s21_create_matrix(2, 2, &result1);
  code1 = s21_calc_complements(&test, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test);

  test.rows = -1;
  code1 = s21_calc_complements(&test, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(1, 1, &test);
  s21_create_matrix(1, 1, &result2);
  test.matrix[0][0] = 5;
  result2.matrix[0][0] = 1;
  code1 = s21_calc_complements(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 2);
  ck_assert_int_eq(code2, FAILURE);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  s21_create_matrix(3, 3, &test);
  s21_create_matrix(3, 3, &result2);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  result2.matrix[0][0] = 0;
  result2.matrix[0][1] = 10;
  result2.matrix[0][2] = -20;
  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = -14;
  result2.matrix[1][2] = 8;
  result2.matrix[2][0] = -8;
  result2.matrix[2][1] = -2;
  result2.matrix[2][2] = 4;
  code1 = s21_calc_complements(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

// ----------------------------------------------------------------------DETERMINANT-------------------------------------------------------------------------

START_TEST(incorr_mat) {
  matrix_t test;
  double result;
  s21_create_matrix(1, 1, &test);
  test.rows = -1;
  int res_code = s21_determinant(&test, &result);
  ck_assert_int_eq(res_code, INCORRECT_MATRIX);
  test.rows = 1;
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(not_square) {
  matrix_t test;
  double result;
  s21_create_matrix(2, 4, &test);
  int res_code = s21_determinant(&test, &result);
  ck_assert_int_eq(res_code, CALCULATION_ERROR);
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(normal_square_mat) {
  matrix_t test;
  double result;
  s21_create_matrix(1, 1, &test);
  test.matrix[0][0] = 1.0;
  int res_code = s21_determinant(&test, &result);
  ck_assert_int_eq(res_code, OK);
  ck_assert(result == 1.0);
  s21_remove_matrix(&test);

  s21_create_matrix(2, 2, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[1][0] = 3;
  test.matrix[1][1] = 4;
  res_code = s21_determinant(&test, &result);
  ck_assert_int_eq(res_code, OK);
  ck_assert(result == -2.0);
  s21_remove_matrix(&test);

  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 4;
  test.matrix[1][1] = 5;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 7;
  test.matrix[2][1] = 8;
  test.matrix[2][2] = 9;
  res_code = s21_determinant(&test, &result);
  ck_assert_int_eq(res_code, OK);
  ck_assert(result == 0);
  s21_remove_matrix(&test);

  s21_create_matrix(4, 4, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[0][3] = 4;
  test.matrix[1][0] = 5;
  test.matrix[1][1] = 6;
  test.matrix[1][2] = 7;
  test.matrix[1][3] = 8;
  test.matrix[2][0] = 9;
  test.matrix[2][1] = 10;
  test.matrix[2][2] = 11;
  test.matrix[2][3] = 12;
  test.matrix[3][0] = 13;
  test.matrix[3][1] = 14;
  test.matrix[3][2] = 15;
  test.matrix[3][3] = 16;
  res_code = s21_determinant(&test, &result);
  ck_assert_int_eq(res_code, OK);
  ck_assert(result == 0);
  s21_remove_matrix(&test);
}
END_TEST

// --------------------------------------------------------------------INVERSE_MATRIX------------------------------------------------------------------------

START_TEST(inverse_matrix) {
  matrix_t test, result1, result2;
  int code1 = 0, code2 = 0;

  s21_create_matrix(1, 1, &test);
  code1 = s21_inverse_matrix(&test, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test);

  test.rows = -1;
  code1 = s21_inverse_matrix(&test, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(2, 2, &test);
  s21_create_matrix(2, 2, &result2);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[1][0] = -1;
  test.matrix[1][1] = 2;
  result2.matrix[0][0] = 0.5;
  result2.matrix[0][1] = -0.5;
  result2.matrix[1][0] = 0.25;
  result2.matrix[1][1] = 0.25;

  code1 = s21_inverse_matrix(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  s21_create_matrix(3, 3, &test);
  s21_create_matrix(3, 3, &result2);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 5;
  test.matrix[0][2] = 7;
  test.matrix[1][0] = 6;
  test.matrix[1][1] = 3;
  test.matrix[1][2] = 4;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = -2;
  test.matrix[2][2] = -3;
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = -1;
  result2.matrix[0][2] = 1;
  result2.matrix[1][0] = -38;
  result2.matrix[1][1] = 41;
  result2.matrix[1][2] = -34;
  result2.matrix[2][0] = 27;
  result2.matrix[2][1] = -29;
  result2.matrix[2][2] = 24;
  code1 = s21_inverse_matrix(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

Suite *suite_creator(void) {
  Suite *suite;
  suite = suite_create("Matrix Tests");

  TCase *tc_create_remove = tcase_create("Create_Remove");
  tcase_add_test(tc_create_remove, create_1);
  tcase_add_test(tc_create_remove, create_2);
  tcase_add_test(tc_create_remove, create_3);
  tcase_add_test(tc_create_remove, create_4);
  tcase_add_test(tc_create_remove, create_5);
  tcase_add_test(tc_create_remove, create_6);
  suite_add_tcase(suite, tc_create_remove);

  TCase *tc_eq = tcase_create("s21_eq_matrix_test");
  tcase_add_test(tc_eq, eq_matrix_1);
  tcase_add_test(tc_eq, eq_matrix_2);
  suite_add_tcase(suite, tc_eq);

  TCase *tc_sum = tcase_create("s21_sum_matrix_test");

  tcase_add_test(tc_sum, sum_matrix_1);
  tcase_add_test(tc_sum, sum_matrix_2);
  suite_add_tcase(suite, tc_sum);

  TCase *tc_sub = tcase_create("s21_sub_matrix_test");
  tcase_add_test(tc_sub, sub_matrix_1);
  tcase_add_test(tc_sub, sub_matrix_2);
  suite_add_tcase(suite, tc_sub);

  TCase *tc_num = tcase_create("s21_mult_number_test");
  tcase_add_test(tc_num, mult_number_1);
  suite_add_tcase(suite, tc_num);

  TCase *tc_m_mat = tcase_create("s21_mult_matrix_test");
  tcase_add_test(tc_m_mat, mult_matrix_1);
  suite_add_tcase(suite, tc_m_mat);

  TCase *tc_trans = tcase_create("s21_transpose_matrix_test");
  tcase_add_test(tc_trans, transpose);
  suite_add_tcase(suite, tc_trans);

  TCase *tc_calc = tcase_create("s21_calc_complements_test");
  tcase_add_test(tc_calc, calc_complements);
  suite_add_tcase(suite, tc_calc);

  TCase *tc_determ = tcase_create("s21_determinant_test");
  tcase_add_test(tc_determ, incorr_mat);
  tcase_add_test(tc_determ, not_square);
  tcase_add_test(tc_determ, normal_square_mat);
  suite_add_tcase(suite, tc_determ);

  TCase *tc_inverse = tcase_create("s21_inverse_matrix_test");
  tcase_add_test(tc_inverse, inverse_matrix);
  suite_add_tcase(suite, tc_inverse);

  return suite;
}

int main(void) {
  Suite *suite;
  SRunner *srunner;

  suite = suite_creator();
  srunner = srunner_create(suite);

  srunner_run_all(srunner, CK_VERBOSE);  // shows successful tests in Term
  int failed_count = srunner_ntests_failed(srunner);  //  NORMAL does not
  srunner_free(srunner);

  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
