/* In the name of Allah */

#include "prayer_time.h"

time_t calculate_duhr_prayer(long int timezone, struct compute_time *compute_time, double equa_of_time)
{
	double duhr;
	int hours;
	int minutes;

	duhr = 12 + timezone - compute_time->longitude / 15 - equa_of_time;

	duhr = range_hour(duhr);

	get_float_time_parts(duhr, &hours, &minutes);
	fprintf(stdout, "%d:%d\n", hours, minutes);

	return 0;
}
