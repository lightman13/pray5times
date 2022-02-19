/* In the name of Allah */

#include "prayer_time.h"

double convert_gregorian_to_julian(struct tm *tm)
{
	double A, B, C, E, F;
	double julian_date;

	A = (tm->tm_year + 1900) / 100;
	B = A / 4;
	C = (2 - A) + B;
	E = 365.25 * ((tm->tm_year +1900) + 4716);
	F = 30.6001 * (tm->tm_mon + 2);

	julian_date = (C + tm->tm_mday + E + F) - 1524.5;

	return julian_date;
}

int save_custom_date(char *optarg, struct prayer_struct *prayer_struct)
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
