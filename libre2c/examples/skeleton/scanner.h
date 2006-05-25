/** @file scanner.h
 *
 * This file defines the interface to your scanner.
 */

struct scanstate;


/** These are the tokens that your scanner recognizes. */

// 1. Add the tokens that your scanner recognizes here:
enum modnumscan_tokens {
	EOFTOK,	 // re2c scanners always return 0 when they hit the EOF.
	TOKEN1,  //   ADD ...
	TOKEN2,  //   YOUR ...
	TOKEN3,  //   TOKENS ...
	TOKEN4,  //   HERE.
};


// 2. Rename this function (i.e. zipcode_scanner_attach)
scanstate* scanner_attach(scanstate *ss);

