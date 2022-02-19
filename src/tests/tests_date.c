#include "tests_suite.h"

/* Test the 1st January 1999 */
START_TEST(test_julian_date) {
	double result;
	struct tm tm = {0};
	extern double convert_gregorian_to_julian(struct tm *tm);

	tm.tm_year = 99;
	tm.tm_mon = 0;
	tm.tm_mday = 1;
	result = convert_gregorian_to_julian(&tm);
	ck_assert_double_eq_tol(result, 2451179.5, 0.3);

} END_TEST

/* Test the 27st January 1987 */
START_TEST(test_julian_date_2) {
	double result;
	struct tm tm = {0};
	extern double convert_gregorian_to_julian(struct tm *tm);

	tm.tm_year = 87;
	tm.tm_mon = 0;
	tm.tm_mday = 27;
	result = convert_gregorian_to_julian(&tm);
	ck_assert_double_eq_tol(result, 2446822.5, 0.3);

} END_TEST

Suite *date_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Date");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_julian_date);
	tcase_add_test(tc_core, test_julian_date_2);
	suite_add_tcase(s, tc_core);

	return s;
}
