/* zutest.h
 * Scott Bronson
 * 6 Mar 2006
 *
 * Version 0.61, 30 Apr 2006
 */


/* @file zutest.h
 *
 * This file contains the declarations and all the Assert macros
 * required to use Zutest in your own applications.
 *
 * Zutest is a ground-up rewrite of Asim Jalis's "CuTest" library.
 * It is released under the MIT License.
 *
 * To compile Zutest to run its own unit tests, do this:
 * 
 * <pre>
 * 	$ cc -DZUTEST_MAIN zutest.c -o zutest
 * 	$ ./zutest
 * 	4 tests run, 4 successes (132 assertions).
 * </pre>
 *
 * If your non-gcc compiler complains about a missing __func__ macro,
 * add -D__func__='"test"' to the compile command line.
 *
 * See ::zutest_tests for instructions on how to add zutest's
 * built-in unit tests to your application's test suite.
 */


#ifndef ZUTEST_H
#define ZUTEST_H

// Note that Fail can't increment zutest_assertions (the number of assertions
// that have been made).  You might want to increment zutest_assertions 
// manually if you care about this number.  Normally you won't.
#define Fail(...) zutest_fail(__FILE__, __LINE__, __func__, __VA_ARGS__)


// If the expression returns false, it is printed in the failure message.
#define Assert(x) do { zutest_assertions++; \
		if(!(x)) { Fail(#x); } } while(0)
// If the expression returns false, the given format string is printed.
#define AssertFmt(x,...) do { zutest_assertions++; \
		if(!(x)) { Fail(__VA_ARGS__); } } while(0)


// On failure the expression is printed followed by the format string.
#define AssertExp(ex,...) AssertFmt(ex,#ex __VA_ARGS__)
// Like AssertExp but enforces a type while performing the comparison.
#define AssertExpType(x,y,op,type,fmt) \
	AssertExp((type)x op (type)y," failed because "#x"=="fmt" and "#y"=="fmt"!",\
			(type)x,(type)y)

// Same as above but all 8 digits are printed
// If you give me a 64 bit computer, I will give you 16 digits!
#define AssertHexOp(x,y,op) AssertExpType(x,y,op,long,"0x%lX")


// These work with integers
#define AssertEq(x,y) AssertOp(x,y,==)
#define AssertNe(x,y) AssertOp(x,y,!=)
#define AssertGt(x,y) AssertOp(x,y,>)
#define AssertGe(x,y) AssertOp(x,y,>=)
#define AssertLt(x,y) AssertOp(x,y,<)
#define AssertLe(x,y) AssertOp(x,y,<=)

#define AssertZero(x) AssertEq(x,0)
#define AssertNonzero(x) Assert(x)
#define AssertNonZero(x) AssertNonzero(x)
#define AssertPositive(x) AssertGt(x,0);
#define AssertNegative(x) AssertLt(x,0);

#define AssertIntEq(x,y) AssertOp(x,y,==)
#define AssertIntNe(x,y) AssertOp(x,y,!=)
#define AssertIntGt(x,y) AssertOp(x,y,>)
#define AssertIntGe(x,y) AssertOp(x,y,>=)
#define AssertIntLt(x,y) AssertOp(x,y,<)
#define AssertIntLe(x,y) AssertOp(x,y,<=)
#define AssertOp(x,y,op) AssertExpType(x,y,op,long,"%ld")

// Same as above but the values in the error report
// are printed in hex rather than decimal.
#define AssertEqHex(x,y) AssertHexOp(x,y,==)
#define AssertNeHex(x,y) AssertHexOp(x,y,!=)
#define AssertGtHex(x,y) AssertHexOp(x,y,>)
#define AssertGeHex(x,y) AssertHexOp(x,y,>=)
#define AssertLtHex(x,y) AssertHexOp(x,y,<)
#define AssertLeHex(x,y) AssertHexOp(x,y,<=)


#define AssertPtr(p)  AssertFmt(p != NULL, \
		#p" != NULL but "#p"==0x%08lX!", (unsigned long)p)
#define AssertNull(p) AssertFmt(p == NULL, \
		#p" == NULL but "#p"==0x%08lX!", (unsigned long)p)
#define AssertNonNull(p) AssertPtr(p)

#define AssertPtrNull(p) AssertNull(p)
#define AssertPtrNonNull(p) AssertNonNull(p)
#define AssertPtrEq(x,y) AssertPtrOp(x,y,==)
#define AssertPtrNe(x,y) AssertPtrOp(x,y,!=)
#define AssertPtrGt(x,y) AssertPtrOp(x,y,>)
#define AssertPtrGe(x,y) AssertPtrOp(x,y,>=)
#define AssertPtrLt(x,y) AssertPtrOp(x,y,<)
#define AssertPtrLe(x,y) AssertPtrOp(x,y,<=)
#define AssertPtrOp(x,y,op) AssertExpType(x,y,op,unsigned long,"0x%lX")

// These work with floats and doubles
#define AssertFloatEq(x,y) AssertFloatOp(x,y,==)
#define AssertFloatNe(x,y) AssertFloatOp(x,y,!=)
#define AssertFloatGt(x,y) AssertFloatOp(x,y,>)
#define AssertFloatGe(x,y) AssertFloatOp(x,y,>=)
#define AssertFloatLt(x,y) AssertFloatOp(x,y,<)
#define AssertFloatLe(x,y) AssertFloatOp(x,y,<=)

// Dbl is implemented the same as Float internally.
// We just provide a Dbl and Double names so that the programmer can
// use whatever name she prefers and the macro can exactly equal the type.
#define AssertDblEq(x,y) AssertFloatOp(x,y,==)
#define AssertDblNe(x,y) AssertFloatOp(x,y,!=)
#define AssertDblGt(x,y) AssertFloatOp(x,y,>)
#define AssertDblGe(x,y) AssertFloatOp(x,y,>=)
#define AssertDblLt(x,y) AssertFloatOp(x,y,<)
#define AssertDblLe(x,y) AssertFloatOp(x,y,<=)

#define AssertDoubleEq(x,y) AssertFloatOp(x,y,==)
#define AssertDoubleNe(x,y) AssertFloatOp(x,y,!=)
#define AssertDoubleGt(x,y) AssertFloatOp(x,y,>)
#define AssertDoubleGe(x,y) AssertFloatOp(x,y,>=)
#define AssertDoubleLt(x,y) AssertFloatOp(x,y,<)
#define AssertDoubleLe(x,y) AssertFloatOp(x,y,<=)
#define AssertFloatOp(x,y,op) AssertExpType(x,y,op,double,"%lf")

// These work with strings
#define AssertStrEq(x,y) AssertStrOp(x,y,EQ,==)
#define AssertStrNe(x,y) AssertStrOp(x,y,NE,!=)
#define AssertStrGt(x,y) AssertStrOp(x,y,GT,>)
#define AssertStrGe(x,y) AssertStrOp(x,y,GE,>=)
#define AssertStrLt(x,y) AssertStrOp(x,y,LT,<)
#define AssertStrLe(x,y) AssertStrOp(x,y,LE,<=)
#define AssertStrOp(x,y,opn,op) AssertFmt(strcmp(x,y) op 0, \
	#x" "#opn" "#y" but "#x" is \"%s\" and "#y" is \"%s\"!",x,y)


/** Keeps track of how many assertions have been made.
 * This needs to be updated manually each time an assertion
 * is made.  The Zutest built-in assertion macros all
 * update this variable properly.
 */

extern int zutest_assertions;


/** A single test
 *
 * This routine is called to run the test.  If it returns, the test
 * succeeds.  If zutest_fail() is called (either directly or indirectly
 * via an Assert macro), then the test fails.
 */
typedef void (*zutest_proc)();


/** A suite of tests
 *
 * A zutest_suite is simply a list of tests.  Generally, each .c file
 * in your project will include a test suite that ensures all the tests
 * contained in the .c file are run.  A suite is just a NULL-terminated
 * list of tests.
 */
typedef zutest_proc *zutest_suite;


/** A suite of test suites
 *
 * Zutests runs through each test suite in your project, running all the
 * tests in each suite.  A suite of suites is just a NULL-terminated list
 * of suites.  This is the topmost data structure used by zutest.
 */
typedef zutest_suite *zutest_suites;


/** Fails the current test.
 *
 * This function may only be called from a ::zutest_proc.
 *
 * If none of the built-in Assert macros fit your fancy, you can do the
 * check on your own and call zutest_fail in the event that it fails.
 * 
 * Example:
 * 
 * <pre>
 * if(my_error) {
 *    zutest_fail(__FILE__, __LINE__, __func__, "Error Message %d", 1);
 * }
 * </pre>
 *
 * But, really, it's easier just to call the Fail() macro.
 */

void zutest_fail(const char *file, int line, const char *func,
		const char *msg, ...);


/** Runs all the tests in a suite. */
void run_zutest_suite(const zutest_suite suite);
/** Runs all the tests in all the suites passed in. */
void run_zutest_suites(const zutest_suites suites);

void print_zutest_results();


/** 
 *
 * Call this on the very first line of your application.  If the user
 * ran your program with the first arg of "--run-unit-tests", this will
 * run the tests and exit.  Otherwise your program will run as normal.
 * If you would rather create a dedicated executable, just call
 * run_zutest_suites() directly.
 */

void unit_test_check(int argc, char **argv, const zutest_suites suites);

/**
 *
 * This runs all the unit tests supplied and then exits.  Use this
 * if you want to handle the arguments yourself.
 */

void run_unit_tests(const zutest_suites suites);


/** Zutest's built-in test suite.
 *
 * This allows you to add the Zutest unit test suite to your application's
 * test suites.  This way, you can ensure that Zutest's unit tests pass
 * before running your application's.  This is for the especially pedantic. :)
 *
 * Unfortunately, there is one test that cannot be run if you do this:
 * ensuring that zutest properly handles empty test suites.
 * Other than this one test, adding zutest_tests
 * to your application's test suite is equivalent to causing zutest to
 * compile and run its unit tests as described in zutest.h.
 */

extern zutest_proc zutest_tests[];

#endif
