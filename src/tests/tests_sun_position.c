#include "tests_suite.h"

/* Compute equation of time for 21th
 * February 2022 */
START_TEST(test_compute_equa_of_time) {
	double equa_of_time;
	struct calc_param param = {0};
	extern int compute_equation_of_time(double *equa_of_time,
			struct calc_param *param);

	/* Julian date for 21th February 2022 */
	param.julian_date = 2459629.800300;
	compute_equation_of_time(&equa_of_time, &param);
	ck_assert_double_eq_tol(equa_of_time, -0.230979, 0.000001);
} END_TEST

Suite *sun_position_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Sun Position");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_compute_equa_of_time);
	suite_add_tcase(s, tc_core);

	return s;
}
