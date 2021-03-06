#include "tests_suite.h"

int main(void)
{
	int no_failed = 0;
	const char *filename = "results.tap";

	Suite *s;
	SRunner *runner;

	s = utils_suite();
	runner = srunner_create(s);
	srunner_set_tap(runner, filename);
	srunner_add_suite(runner, date_suite());
	srunner_add_suite(runner, sun_position_suite());
	srunner_add_suite(runner, cal_prayer_suite());

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
