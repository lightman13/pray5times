/* In the name of Allah */

#include "prayer_time.h"

time_t calculate_duhr_prayer(long int timezone, struct prayer_struct *prayer_struct, double equa_of_time)
{
	int hours;
	int minutes;

	prayer_struct->prayer.duhr = 12 + timezone - prayer_struct->longitude / 15 - equa_of_time;

	log_info("Duhr before %lf\n", prayer_struct->prayer.duhr);

	prayer_struct->prayer.duhr = range_hour(prayer_struct->prayer.duhr);

	get_float_time_parts(prayer_struct->prayer.duhr, &hours, &minutes);
	log_info("Duhr: %d:%d\n", hours, minutes);

	return 0;
}

void calculate_fajr_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double T;
	double num;
	double deno;
	int hours;
	int minutes;

	num = -sin(degree_to_radian(12)) - sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);
	log_info("num: %lf\n", num);
	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);
	log_info("deno: %lf\n", deno);
	T = acos(num / deno);

	T = radian_to_degree(T);

	log_info("T: %lf\n", T);
	T = T / 15;

	log_info("T: %lf\n", T);
	prayer_struct->prayer.fajr = prayer_struct->prayer.duhr - T;

	get_float_time_parts(prayer_struct->prayer.fajr, &hours, &minutes);
	log_info("Fajr: %d:%d\n", hours, minutes);
}

void calculate_isha_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double T;
	double num;
	double deno;
	int hours;
	int minutes;

	num = -sin(degree_to_radian(12)) - sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);
	log_info("num: %lf\n", num);
	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);
	log_info("deno: %lf\n", deno);
	T = acos(num / deno);

	T = radian_to_degree(T);

	log_info("T: %lf\n", T);
	T = T / 15;

	log_info("T: %lf\n", T);
	prayer_struct->prayer.isha = prayer_struct->prayer.duhr + T;

	get_float_time_parts(prayer_struct->prayer.isha, &hours, &minutes);
	log_info("Isha: %d:%d\n", hours, minutes);
}

void calculate_maghrib_prayer(struct prayer_struct *prayer_struct, double declination_sun)
{
	double T;
	double num;
	double deno;
	int hours;
	int minutes;

	num = -sin(degree_to_radian(0.833)) - sin(degree_to_radian(prayer_struct->latitude)) * sin(declination_sun);
	log_info("num: %lf\n", num);
	deno = cos(degree_to_radian(prayer_struct->latitude)) * cos(declination_sun);
	log_info("deno: %lf\n", deno);
	T = acos(num / deno);

	T = radian_to_degree(T);

	log_info("T: %lf\n", T);
	T = T / 15;

	log_info("T: %lf\n", T);
	prayer_struct->prayer.maghrib = prayer_struct->prayer.duhr + T;

	get_float_time_parts(prayer_struct->prayer.maghrib, &hours, &minutes);
	log_info("Maghrib: %d:%d\n", hours, minutes);
}
