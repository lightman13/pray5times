/* In the name of Allah */

#include "prayer_time.h"

const char *usage= "Usage: prayer_time -h -l [latitude] -L [longitude] -d [date]"
		    " -t [timezone] -m [method]";

/* Muslim World league */
const char *method_mwl = "MWL";
/* Islamic Society of North America */
const char *method_isna = "ISNA";
/* Egyptian General Authority of Survey */
const char *method_egas = "EGAS";
/* Umm al-qura University, Makkah */
const char *method_uqum = "UQUM";
/* University of islamic Sciences, Karachi */
const char *method_uisk = "UISK";
/* Institute of Geophysics, University of Teheran */
const char *method_igut = "IGUT";
/* Union of islamics organisations of France */
const char *method_uoif = "UOIF";

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
		timezone = prayer_struct->tm_custom.tm_gmtoff;
		param->julian_date = convert_gregorian_to_julian(&(prayer_struct->tm_custom));
	} else {
		tm = localtime(&t);

		timezone = second_to_hour(tm->tm_gmtoff);

		param->julian_date = convert_gregorian_to_julian(tm);
	}

	compute_equation_of_time(&equa_of_time, param);

	compute_declination_sun(&declination_sun, param);

	calculate_duhr_prayer(timezone, prayer_struct, equa_of_time);

	calculate_fajr_prayer(prayer_struct, declination_sun);
	calculate_isha_prayer(prayer_struct, declination_sun);
	calculate_maghrib_prayer(prayer_struct, declination_sun);
	calculate_asr_prayer(prayer_struct, declination_sun);

	print_prayer_time(prayer_struct);

	return 0;
}

static int choose_method(char *optarg, struct prayer_struct *prayer_struct)
{
	if (!strcmp(optarg, method_uoif)) {
		prayer_struct->angle_fajr = 12;
		prayer_struct->angle_isha = 12;
	} else if (!strcmp(optarg, method_mwl)) {
		prayer_struct->angle_fajr = 18;
		prayer_struct->angle_isha = 17;
	} else if (!strcmp(optarg, method_isna)) {
		prayer_struct->angle_fajr = 15;
		prayer_struct->angle_isha = 15;
	} else if (!strcmp(optarg, method_egas)) {
		prayer_struct->angle_fajr = 19.5;
		prayer_struct->angle_isha = 17.5;
	} else if (!strcmp(optarg, method_uqum)) {
		prayer_struct->angle_fajr = 18.5;
		/* TODO There is no angle for isha in
		 * Makkah method. Find way to add 90 min
		 * after maghrib*/
		prayer_struct->angle_isha = 17;
	} else if (!strcmp(optarg, method_uisk)) {
		prayer_struct->angle_fajr = 18;
		prayer_struct->angle_isha = 18;
	} else if (!strcmp(optarg, method_igut)) {
		prayer_struct->angle_fajr = 17.5;
		prayer_struct->angle_isha = 14;
	} else {
		log_error("%s method doesn't exist\n", optarg);
		return 1;
	}

	return 0;
}

static int save_custom_date(char *optarg, struct prayer_struct *prayer_struct)
{
	int i;
	char *date[3];
	char *sep = "-";
	char *res;

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

	/* We have to substract 1 for month variable and 1900
	 * for year variable to be consistent with the struct
	 * tm in time.h
	 */
	prayer_struct->tm_custom.tm_mday = atoi(date[2]);
	prayer_struct->tm_custom.tm_mon = atoi(date[1]) - 1 ;
	prayer_struct->tm_custom.tm_year = atoi(date[0]) - 1900;

	for (i = 0; i < 3; i++) {
		free(date[i]);
	}

	return 0;

free_error:
	for (i = 0; i < 3; i++) {
		if (date[i] != NULL)
			free(date[i]);
	}

	return 1;
}

int main(int argc, char **argv)
{
	int c;
	int rc;
	struct prayer_struct prayer_struct = {0};
	struct calc_param *param;

	/* Initialize UOIF method by default */
	prayer_struct.angle_fajr = 12;
	prayer_struct.angle_isha = 12;

	while((c = getopt(argc, argv, "d:hl:L:m:t:")) != -1) {
		switch(c) {
			case 'd':
				rc = save_custom_date(optarg, &prayer_struct);
				if (rc)
					return 1;
				break;
			case 'l':
				prayer_struct.latitude = atof(optarg);
				break;
			case 'L':
				prayer_struct.longitude = atof(optarg);
				break;

			case 'h':
				log_info("%s\n", usage);
				return 0;

			case 'm':
				rc = choose_method(optarg, &prayer_struct);
				if (rc)
					return 1;
				break;

			case 't':
				prayer_struct.tm_custom.tm_gmtoff = atoi(optarg);
				break;
			default:
				log_error("%s\n", usage);
				return 1;
		}
	}

	if (prayer_struct.longitude == 0 || prayer_struct.latitude == 0) {
		log_error("You need to specify both latitude and longitude\n");
		return 1;
	}

	param = calloc(1, sizeof(struct calc_param));
	if (param == NULL) {
		log_error("Failed to allocate memory\n");
		return 1;
	}

	rc = calculate_time(&prayer_struct, param);
	if (rc != 0)
		return 1;

	free(param);

	return 0;


}
