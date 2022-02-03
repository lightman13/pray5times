/* In the name of Allah */

#include "prayer_time.h"

int compute_equation_of_time(double *equa_of_time , struct calc_param *param)
{
	/* Compute equation of time */

	param->julian_date = (param->julian_date - 2451545.0) / 36525;

	/* Calcul de la longitude écliptique */
	param->lambda = 280.4665 + 36000.76983 * param->julian_date + 0.0003032 * pow(param->julian_date, 2);

	param->lambda = range_angle(param->lambda);

#ifdef DEBUG
	log_info("lambda %lf\n", param->lambda);
#endif

	/* Calcul de l'anomalie moyenne */
	param->M = 357.5291 + 35999.05029 * param->julian_date + 0.0001537 * pow(param->julian_date, 2);

	param->M = range_angle(param->M);

#ifdef DEBUG
	log_info("M %lf\n", param->M);
#endif
	/* Calcul de l'eccentritcity of the Earth's orbit */
	param->e = 0.016708634 - 0.000042037 * param->julian_date - 0.0000001267 * pow(param->julian_date, 2);

#ifdef DEBUG
	log_info("e %lf\n", param->e);
#endif

	/* Calcul de l'ellipticité de la tajectoire */
	param->C = (1.914602 - 0.004817 * param->julian_date - 0.000014 * pow(param->julian_date, 2)) * sin(degree_to_radian(param->M)) +
		   (0.019993 - 0.000101 * param->julian_date) * sin(degree_to_radian(2 *  param->M)) +
		   0.000289 * sin(degree_to_radian(3 * param->M));

#ifdef DEBUG
	log_info("C = %lf\n", param->C);
#endif

	/* Sun's true longitude */
	param->true_long = param->lambda + param->C;

#ifdef DEBUG
	log_info("true_log %lf\n", param->true_long);
#endif

	/* True anomaly */
	param->v = param->M + param->C;

	param->epsilon = 23.439 - 0.00000036 * param->julian_date;

#ifdef DEBUG
	log_info("epsilon %lf\n", param->epsilon);
#endif

	param->alpha = atan2(cos(degree_to_radian(param->epsilon)) * sin(degree_to_radian(param->true_long)),
			cos(degree_to_radian(param->true_long)));

	param->alpha = radian_to_degree(param->alpha);

	param->alpha = range_angle(param->alpha);

#ifdef DEBUG
	log_info( "Right ascension %lf\n", param->alpha);
#endif

	param->lambda = 280.4665 + 36000.76983 * param->julian_date + 0.0003032 * pow(param->julian_date, 2) +
			(pow(param->julian_date, 3) / 49931) - (pow(param->julian_date, 4)  / 15300) -
			(pow(param->julian_date, 5) / 2000000);

	param->lambda = range_angle(param->lambda);

#ifdef DEBUG
	log_info("lambda %lf\n", param->lambda);
#endif

	param->omega = 125.04452 - 1934.136261 * param->julian_date + 0.0020708 * pow(param->julian_date, 2) +
		       pow(param->julian_date, 3) / 450000;
	param->omega = range_angle(param->omega);

#ifdef DEBUG
	log_info("omega %lf\n", param->omega);
#endif

	param->l_sun = 280.4665+36000.7698 * param->julian_date;
	param->l_moon = 218.3165 + 481267.8813 * param->julian_date;

	param->l_sun= range_angle(param->l_sun);
	param->l_moon = range_angle(param->l_moon);

	param->phi = -17.20 * sin(degree_to_radian(param->omega)) - 1.32 * sin(degree_to_radian(2 * param->l_sun)) -
		0.23 * sin(degree_to_radian(2*param->l_moon)) + 0.21 * sin(degree_to_radian(2 * param->omega));

#ifdef DEBUG
	log_info("phi %lf\n", param->phi);
#endif

	param->phi = param->phi / 3600;

#ifdef DEBUG
	log_info("phi %lf\n", param->phi);
#endif

	*equa_of_time = param->lambda - 0.0057183 - param->alpha + param->phi * cos(degree_to_radian(param->epsilon)) ;

#ifdef DEBUG
	log_info("equa_time %lf\n", *equa_of_time);
#endif

	*equa_of_time = *equa_of_time / 15;

	/* End of computation of equation of time */

	return 0;
}

int compute_declination_sun(double *declination_sun, struct calc_param *param)
{
	*declination_sun = sin(degree_to_radian(param->epsilon)) * sin(degree_to_radian(param->true_long));

	return 0;
}
