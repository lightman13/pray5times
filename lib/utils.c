/* In the name of Allah */

#include "prayer_time.h"

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

int choose_method(char *optarg, struct prayer_struct *prayer_struct)
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
		/* In Makkah method, Isha prayer is 90 min
		 * after Maghrib. We convert 90 min in an
		 * angle*/
		prayer_struct->angle_isha = minute_to_angle(90);
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

double range_angle(double angle)
{
	angle = angle - 360 * floor(angle / 360);
	angle = angle < 0.0 ? angle + 360 : angle;

	return angle;
}

double range_hour(double hour)
{
	hour = hour - 24 * floor(hour / 24);
	hour = hour < 0.0 ? hour + 24 : hour;

	return hour;
}

double radian_to_degree(double radian)
{
	return (radian * 180) / M_PI;
}

double degree_to_radian(double degree)
{
	return (degree * M_PI) / 180;
}


double angle_to_hour(double angle)
{
	return angle / 15;
}

double minute_to_angle(double minute)
{
	return (minute * 15) / 60;
}

long int second_to_hour(long int second)
{
	return second / 60 / 60;
}

void get_float_time_parts(double time, int *hours, int *minutes)
{
        time = range_hour(time + 0.5/ 60);               // add 0.5 minutes to round
        *hours = floor(time);
        *minutes = floor((time - *hours) * 60);
}
