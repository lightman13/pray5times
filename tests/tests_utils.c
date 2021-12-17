#include "tests_suite.h"

START_TEST(test_degree_to_radian) {
	double result;
	extern double degree_to_radian(double);

	result = degree_to_radian(10);
	ck_assert_double_eq_tol(result, 0.174533, 0.001);

} END_TEST

START_TEST(test_radian_to_degree) {
	double result;
	extern double radian_to_degree(double);

	result = radian_to_degree(0.5);
	ck_assert_double_eq_tol(result, 28.64, 0.01);
} END_TEST

Suite *utils_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Utils");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_degree_to_radian);
	tcase_add_test(tc_core, test_radian_to_degree);
	suite_add_tcase(s, tc_core);

	return s;
}
