/* In the name of Allah */

#include "prayer_time.h"

time_t calculate_duhr_prayer(long int timezone, struct compute_time *compute_time, double equa_of_time)
{
	double duhr;
	int hours;
	int minutes;

	duhr = 12 + timezone - compute_time->longitude / 15 - equa_of_time;

	fprintf(stdout, "Duhr before %lf\n", duhr);

	duhr = range_hour(duhr);

	get_float_time_parts(duhr, &hours, &minutes);
	fprintf(stdout, "Duhr: %d:%d\n", hours, minutes);

	return 0;
}

void calculate_fajr_prayer(struct compute_time *compute_time, double declination_sun)
{
	double fajr;
	double T;
	double num;
	double deno;
	int hours;
	int minutes;

	num = -sin(degree_to_radian(12)) - sin(degree_to_radian(compute_time->latitude)) * sin(declination_sun);
	fprintf(stdout, "num: %lf\n", num);
	deno = cos(degree_to_radian(compute_time->latitude)) * cos(declination_sun);
	fprintf(stdout, "deno: %lf\n", deno);
	T = acos(num / deno);

	T = radian_to_degree(T);

	fprintf(stdout, "T: %lf\n", T);
	T = T / 15;

	fprintf(stdout, "T: %lf\n", T);
	fajr = 13.512210 - T;

	get_float_time_parts(fajr, &hours, &minutes);
	fprintf(stdout, "Fajr: %d:%d\n", hours, minutes);
}

void calculate_isha_prayer(struct compute_time *compute_time, double declination_sun)
{
	double isha;
	double T;
	double num;
	double deno;
	int hours;
	int minutes;

	num = -sin(degree_to_radian(12)) - sin(degree_to_radian(compute_time->latitude)) * sin(declination_sun);
	fprintf(stdout, "num: %lf\n", num);
	deno = cos(degree_to_radian(compute_time->latitude)) * cos(declination_sun);
	fprintf(stdout, "deno: %lf\n", deno);
	T = acos(num / deno);

	T = radian_to_degree(T);

	fprintf(stdout, "T: %lf\n", T);
	T = T / 15;

	fprintf(stdout, "T: %lf\n", T);
	isha = 13.512210 + T;

	get_float_time_parts(isha, &hours, &minutes);
	fprintf(stdout, "Isha: %d:%d\n", hours, minutes);
}

void calculate_maghrib_prayer(struct compute_time *compute_time, double declination_sun)
{
	double maghrib;
	double T;
	double num;
	double deno;
	int hours;
	int minutes;

	num = -sin(degree_to_radian(0.833)) - sin(degree_to_radian(compute_time->latitude)) * sin(declination_sun);
	fprintf(stdout, "num: %lf\n", num);
	deno = cos(degree_to_radian(compute_time->latitude)) * cos(declination_sun);
	fprintf(stdout, "deno: %lf\n", deno);
	T = acos(num / deno);

	T = radian_to_degree(T);

	fprintf(stdout, "T: %lf\n", T);
	T = T / 15;

	fprintf(stdout, "T: %lf\n", T);
	maghrib = 13.512210 + T;

	get_float_time_parts(maghrib, &hours, &minutes);
	fprintf(stdout, "Maghrib: %d:%d\n", hours, minutes);
}
