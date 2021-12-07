/* In the name of Allah */

#include "prayer_time.h"

time_t calculate_duhr_prayer(long int timezone, struct prayer_struct *prayer_struct, double equa_of_time)
{
	prayer_struct->prayer.duhr = 12 + timezone - prayer_struct->longitude / 15 - equa_of_time;

#ifdef TEST_DEBUG
	log_info("Duhr before %lf\n", prayer_struct->prayer.duhr);
#endif

	prayer_struct->prayer.duhr = range_hour(prayer_struct->prayer.duhr);

	return 0;
}

void calculate_fajr_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double T;
	double num;
	double deno;

	num = -sin(degree_to_radian(12)) - sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);

#ifdef DEBUG
	log_info("num: %lf\n", num);
#endif

	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);

#ifdef DEBUG
	log_info("deno: %lf\n", deno);
#endif

	T = acos(num / deno);

	T = radian_to_degree(T);

#ifdef DEBUG
	log_info("T: %lf\n", T);
#endif

	T = angle_to_hour(T);

#ifdef DEBUG
	log_info("T: %lf\n", T);
#endif

	prayer_struct->prayer.fajr = prayer_struct->prayer.duhr - T;
}

void calculate_isha_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double T;
	double num;
	double deno;

	num = -sin(degree_to_radian(12)) - sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);

#ifdef DEBUG
	log_info("num: %lf\n", num);
#endif

	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);

#ifdef DEBUG
	log_info("deno: %lf\n", deno);
#endif

	T = acos(num / deno);

	T = radian_to_degree(T);

#ifdef DEBUG
	log_info("T: %lf\n", T);
#endif

	T = angle_to_hour(T);

#ifdef DEBUG
	log_info("T: %lf\n", T);
#endif

	prayer_struct->prayer.isha = prayer_struct->prayer.duhr + T;
}

void calculate_maghrib_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double T;
	double num;
	double deno;

	num = -sin(degree_to_radian(0.833)) - sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);

#ifdef DEBUG
	log_info("num: %lf\n", num);
#endif

	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);

#ifdef DEBUG
	log_info("deno: %lf\n", deno);
#endif

	T = acos(num / deno);

	T = radian_to_degree(T);

#ifdef DEBUG
	log_info("T: %lf\n", T);
#endif

	T = angle_to_hour(T);

#ifdef DEBUG
	log_info("T: %lf\n", T);
#endif

	prayer_struct->prayer.maghrib = prayer_struct->prayer.duhr + T;
}

void calculate_asr_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double A;
	double num;
	double deno;

	num = sin(atan(1 / (1 + tan(degree_to_radian(prayer_struct->latitude) - declination_sun)))) -
		sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);

	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);

	A = acos(num / deno);

	A = radian_to_degree(A);

	A = angle_to_hour(A);

	prayer_struct->prayer.asr = prayer_struct->prayer.duhr + A;
}

void print_prayer_time(struct prayer_struct *prayer_struct)
{
	int hours;
	int minutes;

	/* Fajr */
	get_float_time_parts(prayer_struct->prayer.fajr, &hours, &minutes);
	log_info("Fajr: %d:%02d\n", hours, minutes);

	/* Duhr */
	get_float_time_parts(prayer_struct->prayer.duhr, &hours, &minutes);
	log_info("Duhr: %d:%02d\n", hours, minutes);

	/* Asr */
	get_float_time_parts(prayer_struct->prayer.asr, &hours, &minutes);
	log_info("Asr: %d:%02d\n", hours, minutes);

	/* Maghrib */
	get_float_time_parts(prayer_struct->prayer.maghrib, &hours, &minutes);
	log_info("Maghrib: %d:%02d\n", hours, minutes);

	/* Icha */
	get_float_time_parts(prayer_struct->prayer.isha, &hours, &minutes);
	log_info("Isha: %d:%02d\n", hours, minutes);
}
