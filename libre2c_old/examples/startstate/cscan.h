/** @file cscan.h
 *
 * This file defines the interface to the numscanner.
 */

struct scanstate;


/** These are the tokens that the numscan scanner recognizes. */
enum commentscan_tokens {
	EOFTOK,	///< re2c scanners always return 0 when they hit the EOF.
	LABEL, ///< a number is a consecutive string of digits.
	DATA, ///< a string is anything that isn't a number or a newline.
	CPCOMMENT, ///< A C++ comment: //(.*)$

	COMBEG, ///< the start of a comment, "/*"
	COMMENT, ///< data inside a comment
	COMEND, ///< the ending clause of a comment

	NEWLINE, ///< a single newline, returned in either state
};


/** This prepares the given scanstate to be a numscanner */
scanstate* commentscan_attach(scanstate *ss);

