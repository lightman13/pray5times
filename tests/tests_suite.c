#include <check.h>
#include <stdlib.h>
#include "../prayer_time.h"

START_TEST(test_degree_to_radian) {
	double result;
	extern double degree_to_radian(double);

	result = degree_to_radian(10);
	ck_assert_double_eq_tol(result, 0.174533, 0.001);

} END_TEST

Suite *utils_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Utils");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_degree_to_radian);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	int no_failed = 0;

	Suite *s;
	SRunner *runner;

	s = utils_suite();
	runner = srunner_create(s);

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
