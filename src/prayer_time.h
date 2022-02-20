/* In the name of Allah */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define log_info(...)	do { fprintf(stdout, __VA_ARGS__); } while(0);
#define log_error(...)	do { fprintf(stderr, __VA_ARGS__); } while(0);

struct prayer {
	double fajr;
	double duhr;
	double asr;
	double maghrib;
	double isha;
};

struct prayer_struct {
	struct prayer prayer;
	struct tm tm_custom;
	float latitude;
	float longitude;
	float angle_fajr;
	float angle_isha;
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
void calculate_duhr_prayer(long int timezone, struct prayer_struct *prayer_struct, double equa_of_time);
long int second_to_hour(long int second);
double angle_to_hour(double angle);
double degree_to_radian(double degree);
double radian_to_degree(double radian);
double range_hour(double hour);
double range_angle(double angle);
void get_float_time_parts(double time, int *hours, int *minutes);
void calculate_fajr_prayer(struct prayer_struct *prayer_struct, double declination_sun);
void calculate_isha_prayer(struct prayer_struct *prayer_struct, double declination_sun);
void calculate_maghrib_prayer(struct prayer_struct *prayer_struct, double declination_sun);
void calculate_asr_prayer(struct prayer_struct *prayer_struct, double declination_sun);
void print_prayer_time(struct prayer_struct *prayer_struct);
double minute_to_angle(double minute);
double convert_gregorian_to_julian(struct tm *tm);
int calculate_time(struct prayer_struct *prayer_struct, struct calc_param *param);
int choose_method(char *optarg, struct prayer_struct *prayer_struct);
int save_custom_date(char *optarg, struct prayer_struct *prayer_struct);
