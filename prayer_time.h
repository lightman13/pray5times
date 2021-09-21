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

struct calc_param {
	double julian_date;

	/* Ecliptique longitude */
	double lambda;

	/* Mean anomaly */
	double M;

	/* Eccentricity of the Earth's orbit */
	double e;

	/* Sun's equation of the center */
	double C;

	/* Sun's true longitude */
	double true_long;

	/* Nutation in obliquity */
	double epsilon;

	/* Right ascension */
	double alpha;

	/* Longitude of the ascending node of the Moon's
	 * mean orbit on the ecliptic */
	double omega;

	double l_sun;

	double l_moon;

	/* Nutation in longitude */
	double phi;

	/* True anomaly */
	double v;
};

/* Prototypes */

int compute_equation_of_time(double *equa_of_time, struct calc_param *param);
int compute_declination_sun(double *declination_sun, struct calc_param *param);
time_t calculate_duhr_prayer(long int timezone, struct compute_time *compute_time, double equa_of_time);
long int second_to_hour(long int second);
double angle_to_hour(double angle);
double degree_to_radian(double degree);
double radian_to_degree(double radian);
double range_hour(double hour);
double range_angle(double angle);
void get_float_time_parts(double time, int *hours, int *minutes);
void calculate_fajr_prayer(struct compute_time *compute_time, double declination_sun);
void calculate_isha_prayer(struct compute_time *compute_time, double declination_sun);
void calculate_maghrib_prayer(struct compute_time *compute_time, double declination_sun);
