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

START_TEST(test_save_custom_date) {
	int result;
	char optarg[] = "2022-02-19";
	struct prayer_struct prayer = {0};
	extern int save_custom_date(char *optarg,
			struct prayer_struct *prayer_struct);

	result = save_custom_date(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_int_eq(prayer.tm_custom.tm_mday, 19);
	ck_assert_int_eq(prayer.tm_custom.tm_mon, 1);
	ck_assert_int_eq(prayer.tm_custom.tm_year, 122);

} END_TEST

Suite *date_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Date");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_julian_date);
	tcase_add_test(tc_core, test_julian_date_2);
	tcase_add_test(tc_core, test_save_custom_date);
	suite_add_tcase(s, tc_core);

	return s;
}
