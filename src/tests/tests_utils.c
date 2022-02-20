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

START_TEST(test_angle_to_hour) {
	double result;
	extern double angle_to_hour(double);

	result = angle_to_hour(30);
	ck_assert_double_eq(result, 2);
} END_TEST

START_TEST(test_second_to_hour) {
	double result;
	extern long int second_to_hour(long int);

	result = second_to_hour(3600);
	ck_assert_int_eq(result, 1);
} END_TEST

START_TEST(test_minute_to_angle) {
	double result;
	extern double minute_to_angle(double);

	result = minute_to_angle(90);
	ck_assert_double_eq(result, 22.5);
} END_TEST

START_TEST(test_choose_method_uoif) {
	double result;
	char optarg[] = "UOIF";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_int_eq(prayer.angle_fajr, 12);
	ck_assert_int_eq(prayer.angle_isha, 12);
} END_TEST

START_TEST(test_choose_method_mwl) {
	double result;
	char optarg[] = "MWL";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_int_eq(prayer.angle_fajr, 18);
	ck_assert_int_eq(prayer.angle_isha, 17);
} END_TEST

START_TEST(test_choose_method_isna) {
	double result;
	char optarg[] = "ISNA";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_int_eq(prayer.angle_fajr, 15);
	ck_assert_int_eq(prayer.angle_isha, 15);
} END_TEST

START_TEST(test_choose_method_egas) {
	double result;
	char optarg[] = "EGAS";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_float_eq(prayer.angle_fajr, 19.5);
	ck_assert_float_eq(prayer.angle_isha, 17.5);
} END_TEST

START_TEST(test_choose_method_uisk) {
	double result;
	char optarg[] = "UISK";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_int_eq(prayer.angle_fajr, 18);
	ck_assert_int_eq(prayer.angle_isha, 18);
} END_TEST

START_TEST(test_choose_method_igut) {
	double result;
	char optarg[] = "IGUT";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_float_eq(prayer.angle_fajr, 17.5);
	ck_assert_int_eq(prayer.angle_isha, 14);
} END_TEST

START_TEST(test_choose_method_uqum) {
	double result;
	char optarg[] = "UQUM";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);
	extern double minute_to_angle(double);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 0);
	ck_assert_float_eq(prayer.angle_fajr, 18.5);
	ck_assert_int_eq(prayer.angle_isha, minute_to_angle(90));
} END_TEST

START_TEST(test_choose_method_bad) {
	double result;
	char optarg[] = "FOO";
	struct prayer_struct prayer = {0};
	extern int choose_method(char *optarg,
			struct prayer_struct *prayer_struct);

	result = choose_method(optarg, &prayer);
	ck_assert_int_eq(result, 1);
} END_TEST

Suite *utils_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Utils");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_degree_to_radian);
	tcase_add_test(tc_core, test_radian_to_degree);
	tcase_add_test(tc_core, test_angle_to_hour);
	tcase_add_test(tc_core, test_second_to_hour);
	tcase_add_test(tc_core, test_minute_to_angle);
	tcase_add_test(tc_core, test_choose_method_uoif);
	tcase_add_test(tc_core, test_choose_method_mwl);
	tcase_add_test(tc_core, test_choose_method_isna);
	tcase_add_test(tc_core, test_choose_method_egas);
	tcase_add_test(tc_core, test_choose_method_uisk);
	tcase_add_test(tc_core, test_choose_method_igut);
	tcase_add_test(tc_core, test_choose_method_uqum);
	tcase_add_test(tc_core, test_choose_method_bad);
	suite_add_tcase(s, tc_core);

	return s;
}
