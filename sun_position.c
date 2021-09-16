/* In the name of Allah */

#include "prayer_time.h"

int compute_equation_of_time(double julian_date, double *equa_of_time)
{
	double M, C, lambda, e;
	double true_long;
	double v;
	double alpha;
	double epsilon;
	double phi;
	double omega;
	double l_sun;
	double l_moon;

	/* Compute equation of time */

	julian_date = (julian_date - 2451545.0) / 36525;
	//julian_date = -0.07218343600;
	//julian_date = -0.127296372348;

	/* Calcul de la longitude écliptique */
	lambda = 280.4665 + 36000.76983 * julian_date + 0.0003032 * pow(julian_date, 2);

	lambda = range_angle(lambda);

	fprintf(stdout, "lambda %lf\n", lambda);	

	/* Calcul de l'anomalie moyenne */
	M = 357.5291 + 35999.05029 * julian_date + 0.0001537 * pow(julian_date, 2);

	M = range_angle(M);
	fprintf(stdout, "M %lf\n", M);	
	/* Calcul de l'eccentritcity of the Earth's orbit */
	e = 0.016708634 - 0.000042037 * julian_date - 0.0000001267 * pow(julian_date, 2);
	fprintf(stdout, "e %lf\n", e);	

	/* Calcul de l'ellipticité de la tajectoire */
	C = (1.914602 - 0.004817 * julian_date - 0.000014 * pow(julian_date, 2)) * sin(degree_to_radian(M)) + 
	    (0.019993 - 0.000101 * julian_date) * sin(degree_to_radian(2 *  M)) +
	    0.000289 * sin(degree_to_radian(3 * M));

	fprintf(stdout, "C = %lf\n", C);

	/* Sun's true longitude */ 
	true_long = lambda + C;

	fprintf(stdout, "true_log %lf\n", true_long);	
	/* True anomaly */
	v = M + C;

	epsilon = 23.439 - 0.00000036 * julian_date;

	fprintf(stdout, "epsilon %lf\n", epsilon);	

	alpha = atan2(cos(degree_to_radian(epsilon)) * sin(degree_to_radian(true_long)),
			cos(degree_to_radian(true_long)));

	alpha = radian_to_degree(alpha);

	alpha = range_angle(alpha);
	fprintf(stdout, "Right ascension %lf\n", alpha);

	lambda = 280.4665 + 36000.76983 * julian_date + 0.0003032 * pow(julian_date, 2) + 
		(pow(julian_date, 3) / 49931) - (pow(julian_date, 4)  / 15300) - 
		(pow(julian_date, 5) / 2000000);

	lambda = range_angle(lambda);
	fprintf(stdout, "lambda %lf\n", lambda);	

	omega = 125.04452 - 1934.136261 * julian_date + 0.0020708 * pow(julian_date, 2) + 
		pow(julian_date, 3) / 450000;
	omega = range_angle(omega);
	fprintf(stdout, "omega %lf\n", omega);

	l_sun = 280.4665+36000.7698*julian_date;
	l_moon = 218.3165 + 481267.8813 * julian_date; 

	l_sun= range_angle(l_sun);
	l_moon = range_angle(l_moon);

	phi = -17.20 * sin(degree_to_radian(omega)) - 1.32 * sin(degree_to_radian(2 * l_sun)) -
		0.23 * sin(degree_to_radian(2*l_moon)) + 0.21 * sin(degree_to_radian(2 * omega));

	fprintf(stdout, "phi %lf\n", phi);
	phi = phi / 3600;
	fprintf(stdout, "phi %lf\n", phi);
	
	*equa_of_time = lambda - 0.0057183 - alpha + phi * cos(degree_to_radian(epsilon)) ;

	fprintf(stdout, "equa_time %lf\n", *equa_of_time);	
	*equa_of_time = *equa_of_time / 15;

	/* End of computation of equation of time */

	return 0;
}

int compute_declination_sun(double julian_date, double *declination_sun)
{
	return 0;
}
