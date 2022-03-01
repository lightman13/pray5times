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

/* Calculate Fajr the 21th February 2022
 * at Grenoble France with method UOIF
 */
START_TEST(test_calculate_fajr_prayer) {
	struct prayer_struct prayer = {0};
	double declination_sun;
	extern void calculate_fajr_prayer(struct prayer_struct *prayer_struct,
			double);

	prayer.latitude = 45.20350804593916;
	prayer.angle_fajr = 12;
	prayer.prayer.duhr = 12.850572;
	declination_sun = -0.195128;

	calculate_fajr_prayer(&prayer, declination_sun);
	ck_assert_double_eq_tol(prayer.prayer.fajr, 6.46129, 0.00001);
} END_TEST

/* Calculate Isha the 21th February 2022
 * at Grenoble France with method UOIF
 */
START_TEST(test_calculate_isha_prayer) {
	struct prayer_struct prayer = {0};
	double declination_sun;
	extern void calculate_isha_prayer(struct prayer_struct *prayer_struct,
			double);

	prayer.latitude = 45.20350804593916;
	prayer.angle_isha = 12;
	prayer.prayer.duhr = 12.850572;
	declination_sun = -0.195128;

	calculate_isha_prayer(&prayer, declination_sun);
	ck_assert_double_eq_tol(prayer.prayer.isha, 19.239855, 0.00001);
} END_TEST

/* Calculate Maghrib the 21th February 2022
 * at Grenoble France with method UOIF
 */
START_TEST(test_calculate_maghrib_prayer) {
	struct prayer_struct prayer = {0};
	double declination_sun;
	extern void calculate_maghrib_prayer(struct prayer_struct *prayer_struct,
			double);

	prayer.latitude = 45.20350804593916;
	prayer.prayer.duhr = 12.850572;
	declination_sun = -0.195128;

	calculate_maghrib_prayer(&prayer, declination_sun);
	ck_assert_double_eq_tol(prayer.prayer.maghrib, 18.166944, 0.00001);
} END_TEST

Suite *cal_prayer_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Cal_prayer");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_calculate_duhr_prayer);
	tcase_add_test(tc_core, test_calculate_fajr_prayer);
	tcase_add_test(tc_core, test_calculate_isha_prayer);
	tcase_add_test(tc_core, test_calculate_maghrib_prayer);
	suite_add_tcase(s, tc_core);

	return s;
}
