/** @file scanner.re
 *
 * This file is a skeleton where you can simply fill in your re2c
 * code and produce a working modular re2c scanner.
 */

#include "libre2c/scan.h"
#include "scanner.h"


/** Replace the re2c code in this file with your own scanner */

static int scanner_start(scanstate *ss)
{
	scanner_enter(ss);

// 1. FILL IN YOUR SCANNER HERE:
/*!re2c
[0-9]+    { return TOKEN1;  }
[^0-9\n]+ { return TOKEN2; }
[\n]      { ss->line++; return TOKEN3; }
*/
}


// 2. Rename this function as you did in the header file.
scanstate* scanner_attach(scanstate *ss)
{
	if(ss) {
		ss->state = scanner_start;
		ss->line = 1;
	}

	return ss;
}

