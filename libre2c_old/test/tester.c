#include "zutest.h"
#include "retest.h"
#include "compare.h"

#include <stddef.h>
#include <stdlib.h>


zutest_suite all_unit_tests[] = {
	zutest_tests,
	re2c_tests,
	compare_tests,
	NULL
};


int main()
{
	run_unit_tests(all_unit_tests);
	exit(1);
}

