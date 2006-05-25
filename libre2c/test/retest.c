// This file contains unit tests that test the re2c library itself.

#include "retest.h"
#include "libre2c/scan.h"
#include <stddef.h>


static ssize_t test_last_readproc(scanstate *ss)
{
	if(ss->readref) {
		Fail("readproc was called after returning an error!");
		return -2;	// should not be executed.
	}

	ss->readref = test_last_readproc;
	return -1;
}


static int test_last_scanner(scanstate *ss)
{
	scanner_enter(ss);
	YYFILL(1);
	Fail("Readproc should have returned an error!");
	return -3;
}


/**
 * This test ensures that an error value is latched when encountered
 * and that the readproc isn't called anymore.
 */

static void test_last_read()
{
	scanstate state, *ss=&state;

	scanstate_init(ss, NULL, 0);
	ss->readref = NULL;
	ss->read = test_last_readproc;	// attach reader
	ss->state = test_last_scanner;	// attach scanner

	AssertEq(scan_next_token(ss), -1);
	AssertEq(scan_next_token(ss), -1);
	AssertEq(scan_next_token(ss), -1);
	AssertEq(scan_next_token(ss), -1);

	// error value appears latched and readproc was only called
	// once (otherwise the readproc would have failed).
}


zutest_proc re2c_tests[] = {
	test_last_read,
	NULL
};

