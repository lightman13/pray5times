/* In the name of Allah */

#include "prayer_time.h"

const char *usage= "Usage: prayer_time -h -l [latitude] -L [longitude]";

static double convert_gregorian_to_julian(struct tm *tm)
{
	int A, B, C, E, F;
	double julian_date;

	A = (tm->tm_year + 1900) / 100;
	B = A / 4;
	C = (2 - A) + B;
	E = 365.25 * ((tm->tm_year +1900) + 4716);
	F = 30.6001 * (tm->tm_mon + 2);

	julian_date = (C + tm->tm_mday + E + F) - 1524.5;

	return julian_date;
}

static int calculate_time(struct compute_time *compute_time, struct calc_param *param)
{
	double equa_of_time;
	double declination_sun;
	time_t t = time(NULL);
	long int timezone;
	struct tm *tm;

	tm = localtime(&t);

	timezone = second_to_hour(tm->tm_gmtoff);

	fprintf(stdout, "Date: %d-%02d-%02d\n", tm->tm_year, tm->tm_mon + 1, tm->tm_mday);

	fprintf(stdout, "Timezone : %ld\n", timezone);

	param->julian_date = convert_gregorian_to_julian(tm);

	fprintf(stdout, "Julian_Date: %lf\n", param->julian_date);

	compute_equation_of_time(&equa_of_time, param);

	compute_declination_sun(&declination_sun, param);

	fprintf(stdout, "Equation of time : %lf\n", equa_of_time);
	fprintf(stdout, "Declination of sun : %lf\n", declination_sun);

	calculate_duhr_prayer(timezone, compute_time, equa_of_time);

	calculate_fajr_prayer(compute_time, declination_sun);

	return 0;
}

int main(int argc, char **argv)
{
	int c;
	int rc;
	struct compute_time compute_time = {0};
	struct calc_param *param;

	while((c = getopt(argc, argv, "hl:L:")) != -1) {
		switch(c) {
			case 'l':
				compute_time.latitude = atof(optarg);
				fprintf(stdout, "Latitude: %f\n", compute_time.latitude);
				break;
			case 'L':
				compute_time.longitude = atof(optarg);
				fprintf(stdout, "Longitude: %f\n", compute_time.longitude);
				break;

			case 'h':
				fprintf(stdout, "%s\n", usage);
				break;

			default:
				fprintf(stderr, "%s\n", usage);
				break;
		}
	}

	if (compute_time.longitude == 0 || compute_time.latitude == 0) {
		fprintf(stderr, "You need to specify both latitude and longitude\n");
		return 1;
	}

	param = calloc(1, sizeof(struct calc_param));
	if (param == NULL)
		return 1;

	rc = calculate_time(&compute_time, param);
	if (rc != 0)
		return 1;

	free(param);

	return 0;
}
