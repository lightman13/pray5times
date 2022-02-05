/* In the name of Allah */

#include "prayer_time.h"

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
