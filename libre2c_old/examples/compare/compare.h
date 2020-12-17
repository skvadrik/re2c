/* compare.h
 * Scott Bronson
 * 31 Dec 2004
 *
 * This file, like re2c, is released into the public domain.
 */

#include "libre2c/scan.h"


/**
 * Unless you get a return value of cmp_full_match, the streams
 * were not exactly equal.
 *
 * As with everything else, equality is not absolute.  There are
 * a number of codes that 
 */

typedef enum {
	cmp_in_progress = -1,	///< internal state; will never be returned.
	cmp_full_match = 0,		///< data matches exactly
	cmp_no_match,			///< data doesn't match at all
	cmp_ptr_has_extra_nl,	///< ss doesn't end in a newline, ptr ends in a single newline, otherwise they are identical.
	cmp_ptr_has_more_nls,	///< ss ends in a newline, ptr ends in one more newline than ss, otherwise they are identical.
	cmp_ss_has_extra_nl,	///< ss exactly matches ptr, except that ss has an extra newline.
	cmp_ss_has_more_data	///< ptr and ss matched up to now but we haven't seen the EOF on ss so we can't be sure the two files are exactly equal.
} compare_result;


/** Sets the scanner up to be a comparison scanner.
 * @param the scanner to attach the comparison engine to.
 */

void compare_attach(scanstate *ss);

/** Feeds data to the comparison.
 *
 *  The comparison scanner compares the data that you pass in
 *  with the data supplied by its readproc.
 *
 *  @param ss the comparison scanner set up by compare_attach().
 *  @param ptr A pointer to the next block of data to compare.
 *  @param len The size in bytes of the data pointed to by ptr.
 *  @returns 0 if the match is in progress, 1 if the files didn't
 *  match, or a negative number if the readproc fails.
 */

int compare_continue(scanstate *ss, const char *ptr, size_t len);

/** Final check to see if the files were equal.
 *
 * This tells the scanner that we have no more data to feed it.
 *
 * @returns cmp_no_match, cmp_full_match, or cmp_ss_has_more_data.
 * cmp_ss_has_more_data is returned if you call compare continue
 * but there is more data in the scan buffer (i.e. the stream
 * attached to the readproc hasn't yet hit EOF).  Of course, if
 * the second stream is at EOF but compare_continue returns
 * cmp_ss_has_more_data, this means that the two streams do
 * not match.
 *
 * There is no harm
 * to calling compare_check() multiple times.  It will just
 * keep returning cmp_ss_has_more_data until the first stream
 * hits eof.
 */

compare_result compare_check(scanstate *ss);


/** Like compare_check() but checks for newline status too.
 *
 * compare_check_newlines()
 * determines if the files would have been equal except
 * for trailing newlines.
 *
 * If one file has a trailing newline and the other doesn't,
 * compare_check() will report the files as being differnt.
 * However, many programs need to know if the files WOULD
 * HAVE matched if the trailing newlines didn't matter.
 * Thus the compare_check_newlines() routine.
  
   @returns one of:
	- cmp_full_match -- see compare_continue()
	- cmp_no_match -- see compare_continue()
	- cmp_ptr_has_extra_nl --  the first stream (attached to the readproc) doesn't end in a newline, but the second stream ends in a single newline.  Except for that, they are identical.
	- cmp_ptr_has_more_nls -- the first stream ends in a newline AND the second stream ends in one more newline than ss.  Otheriwse they are identical.
	- cmp_ss_has_extra_nl -- the first stream exactly matches ptr, except that it has one extra newline that the second stream doesn't.
	- cmp_ss_has_more_data -- the first stream is not yet at EOF.

 */

compare_result compare_check_newlines(scanstate *ss);


#ifdef ZUTEST
#include "zutest.h"
extern zutest_proc compare_tests[];
#endif
