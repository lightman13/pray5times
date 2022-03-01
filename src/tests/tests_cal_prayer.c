#include "tests_suite.h"

/* Calculate Duhr the 21th February 2022
 * at Grenoble France.
 */
START_TEST(test_calculate_duhr_prayer) {
	struct prayer_struct prayer = {0};
	long int timezone = 1;
	double equa_of_time;
	extern void calculate_duhr_prayer(long int, struct prayer_struct
			*prayer_struct, double);

	prayer.longitude = 5.706105365754465; 
	equa_of_time = -0.230979;
	calculate_duhr_prayer(timezone, &prayer, equa_of_time);
	ck_assert_double_eq_tol(prayer.prayer.duhr, 12.850572, 0.000001);

} END_TEST

Suite *cal_prayer_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Cal_prayer");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_calculate_duhr_prayer);
	suite_add_tcase(s, tc_core);

	return s;
}
