/** @file modnumscanner.h
 *
 * This file defines the interface to the numscanner.
 */

struct scanstate;


/** These are the tokens that the numscan scanner recognizes. */
enum modnumscan_tokens {
	EOFTOK,	///< re2c scanners always return 0 when they hit the EOF.
	NUMBER, ///< a number is a consecutive string of digits.
	STRING, ///< a string is anything that isn't a number or a newline.
	NEWLINE, ///< a single newline (so tokens don't span multiple lines).
};


/** This prepares the given scanstate to be a numscanner */
scanstate* modnumscan_attach(scanstate *ss);

