/* In the name of Allah */

#include <prayer_time.h>

const char *usage= "Usage: pray5times -h -l [latitude] -L [longitude] -d [date]"
		    " -t [timezone] -m [method]";

int calculate_time(struct prayer_struct *prayer_struct, struct calc_param *param)
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
