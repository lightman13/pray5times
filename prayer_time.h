/* In the name of Allah */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct compute_time {
	float latitude;
	float longitude;
	int calc_method;
};

/* Prototypes */

int compute_equation_of_time(double julian_date, double *equa_of_time);
int compute_declination_sun(double julian_date, double *declination_sun);
time_t calculate_duhr_prayer(long int timezone, struct compute_time *compute_time, double equa_of_time);
long int second_to_hour(long int second);
double angle_to_hour(double angle);
double degree_to_radian(double degree);
double radian_to_degree(double radian);
double range_hour(double hour);
double range_angle(double angle);
void get_float_time_parts(double time, int *hours, int *minutes);
