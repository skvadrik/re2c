/* numscan.re
 * Scott Bronson
 * 27 Dec 2004
 */

/** @file numscan.re
 *
 * Example that demonstrates how to scan data from a string constant.
 *
 * In this example, a simple scanner is embedded directly in the file that
 * uses it.  See modnumscan.re to see how the scanner can be factored
 * out so that any file may use it.
 *
 * This file needs to be processed by re2c, http://re2c.org
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libre2c/scan.h"
#include "libre2c/readmem.h"


const char *data = "Zero=0000\none=1 two is 22222222\netc.\n";

/** These are the tokens that the numscan scanner recognizes. */
enum numscan_tokens {
	EOFTOK,	///< re2c scanners always return 0 when they hit the EOF.
	NUMBER, ///< a number is a consecutive string of digits.
	STRING, ///< a string is anything that isn't a number or a newline.
	NEWLINE, ///< a single newline (so tokens don't span multiple lines).
};
const char *tokname[] = { "EOF", "NUM", "STR", "NEWLINE"};


/** This is the re2c scanner. */

int numscan(scanstate *ss)
{
	scanner_enter(ss);

/*!re2c
[0-9]+    { return NUMBER;  }
[^0-9\n]+ { return STRING; }
[\n]	  { ss->line++; return NEWLINE; }
*/
}


int main()
{
    scanstate ss;
    int tok;

	// Initialize the scanner to read from this string constant.
    readmem_init_str(&ss, data);
	ss.line = 1;

	// Pull all the tokens from the scanner
    do {
        tok = numscan(&ss);
		if(tok < 0) {
			printf("Scanner returned an error: %d\n", tok);
			break;
		}

        printf("%2d: %-12s",ss.line, tokname[tok]);
		if(tok != NEWLINE) {
			// don't want to actually print the text of the newline
			// token -- it makes the output ugly.
			printf("<<%.*s>>", scan_token_length(&ss),
				scan_token_start(&ss));
		}
		printf("\n");
    } while(tok);

	// Because we allocated everything on the stack, there's
	// nothing to free.

    return 0;
}



/** \page nscp Numscan Coupled Example
   
\section numscancoupled Numscan Coupled

In this example, we'll build a scanner and hook it up to scan from
a C string.  The next tutorial, \ref numscanmodular
will turn this oversimplified example into a full-blown re2c scanner
and parser.

You can read the complete example in numscan.re (click on the source code link).

\section nsccreate 1. Write the Scanner

Here is the re2c code that we'll use.  It groups contiguous
number characters and contiguous non-number characters.

<pre>
	[0-9]+    { return NUMBER;  }
	[^0-9\\n]+ { return STRING; }
	[\\n]      { return NEWLINE; }
</pre>

To turn this re2c code into a scanner, put it in a ::scanproc function and
insert a call to scanner_enter() at the beginning.  It's that easy.

<pre>
	int numscan(scanstate *ss)
	{
		scanner_enter(ss);

		/-!re2c
		[0-9]+    { return NUMBER;  }
		[^0-9\\n]+ { return STRING; }
		[\\n]      { return NEWLINE; }
		-/
	}
</pre>

\section nscsetup 2. Set Up the Scanner

The ::scanstate data structure stores all state for a single scan run.
We'll store it as an automatic variable:

<pre>
	void main()
	{
		scanstate ss;
</pre>

Now we need to decide how to feed the scanner with data.
The re2c library uses ::readproc routines to do this.
In this example we'll use readmem.h to scan from a C string constant.
Normally we would initialize the scanstate and then attach
the desired readproc:

<pre>
		scanstate_init(&ss, NULL, 0);
		readmem_attach(&ss, data, strlen(data));
</pre>

However, scanning from a string constant is a common enough task that
the re2c library includes a
macro that combines this into a single call:

<pre>
		readmem_init_str(&ss, data);
</pre>

\section nscuse 3. Use the Scanner

Simply call the scanner until it returns either 0 indicating EOF
or a negative number indicating an error.
The meaning of the error depends on the readproc being used.

<pre>
		do {
			tok = numscan(&ss);
			if(tok < 0) {
				printf("Scanner returned an error: %d\n", tok);
				break;
			}
</pre>

Now we need to do something with the tokens.
This example just prints them out:

<pre>
		printf("%2d: %-12s", ss.line, tokname[tok]);
		if(tok != NEWLINE) {
			// don't want to actually print the text of the newline
			// token because it makes the output look ugly.
			printf("<<%.*s>>", token_length(&ss), token_start(&ss));
		}
		printf("\n");

	} while(tok);
</pre>

Now read \ref numscanmodular to see how to split the monolithic
scanner/parser we just built into a modular scanner and a parser
that calls it.

*/

// vi:syn=c
