/* In the name of Allah */

#include "prayer_time.h"

const char *usage= "Usage: prayer_time -h -l [latitude] -L [longitude] -d [date]

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

static int calculate_time(struct prayer_struct *prayer_struct, struct calc_param *param)
{
	double equa_of_time;
	double declination_sun;
	time_t t = time(NULL);
	long int timezone;
	struct tm *tm;

	if (prayer_struct->tm_custom.tm_year != 0) {
		param->julian_date = convert_gregorian_to_julian(&(prayer_struct->tm_custom));
	} else {
		tm = localtime(&t);

		timezone = second_to_hour(tm->tm_gmtoff);

		log_info("Date: %d-%02d-%02d\n", tm->tm_year, tm->tm_mon + 1, tm->tm_mday);

		log_info("Timezone : %ld\n", timezone);

		param->julian_date = convert_gregorian_to_julian(tm);

		log_info("Julian_Date: %lf\n", param->julian_date);
	}

	compute_equation_of_time(&equa_of_time, param);

	compute_declination_sun(&declination_sun, param);

	log_info("Equation of time : %lf\n", equa_of_time);
	log_info("Declination of sun : %lf\n", declination_sun);

	calculate_duhr_prayer(timezone, prayer_struct, equa_of_time);

	calculate_fajr_prayer(prayer_struct, declination_sun);
	calculate_isha_prayer(prayer_struct, declination_sun);
	calculate_maghrib_prayer(prayer_struct, declination_sun);
	calculate_asr_prayer(prayer_struct, declination_sun);

	return 0;
}

int main(int argc, char **argv)
{
	int c;
	int rc;
	int i;
	char *sep = "-";
	char *res;
	char *date[3];
	struct prayer_struct prayer_struct = {0};
	struct calc_param *param;

	while((c = getopt(argc, argv, "d:hl:L:")) != -1) {
		switch(c) {
			case 'd':
				for (i = 0; i < 3 ; i++) {
					date[i] = malloc(4);

					if (date[i] == NULL) {
						log_error("Memory allocation failed\n");
						goto free_error;
					}
				}

				res = strtok(optarg, sep);
				memcpy(date[0], res, strlen(res));

				i = 1;
				while (res != NULL) {
					res = strtok(NULL, sep);
					if (res != NULL)
						memcpy(date[i], res, strlen(res));
					i++;
				};

				prayer_struct.tm_custom.tm_mday = atoi(date[0]);
				prayer_struct.tm_custom.tm_mon = atoi(date[1]);
				prayer_struct.tm_custom.tm_year = atoi(date[2]);

				for (i = 0; i < 3; i++) {
					free(date[i]);
				}
				break;
			case 'l':
				prayer_struct.latitude = atof(optarg);
				log_info("Latitude: %f\n", prayer_struct.latitude);
				break;
			case 'L':
				prayer_struct.longitude = atof(optarg);
				log_info("Longitude: %f\n", prayer_struct.longitude);
				break;

			case 'h':
				log_info("%s\n", usage);
				break;

			default:
				log_error("%s\n", usage);
				break;
		}
	}

	if (prayer_struct.longitude == 0 || prayer_struct.latitude == 0) {
		log_error("You need to specify both latitude and longitude\n");
		return 1;
	}

	param = calloc(1, sizeof(struct calc_param));
	if (param == NULL)
		return 1;

	rc = calculate_time(&prayer_struct, param);
	if (rc != 0)
		return 1;

	free(param);

	return 0;

free_error:
	for (i = 0; i < 3; i++) {
		if (date[i] != NULL)
			free(date[i]);
	}

	return 1;
}
