/** @file modnumscanner.re
 *
 * This shows how to create a modular scanner.  Modular scanners
 * typicalliy consist of a single public routine to prepare a
 * scanner.  After that, tokens are retrieved using scan_next_token().
 *
 * This file needs to be processed by re2c, http://re2c.org
 */

#include "libre2c/scan.h"
#include "modnumscanner.h"


/**
 * This routine defines the scanner itself.
 */

static int modnumscan_start(scanstate *ss)
{
	scanner_enter(ss);

/*!re2c
[0-9]+    { return NUMBER;  }
[^0-9\n]+ { return STRING; }
[\n]	  { ss->line++; return NEWLINE; }
*/
}


/**
 * This routine turns the given scanstate structure into a numscanner.
 */

scanstate* modnumscan_attach(scanstate *ss)
{
	if(ss) {
		ss->state = modnumscan_start;
		ss->line = 1;
	}

	return ss;
}


/** \page nscm Numscan Modular Example

\section numscanmodular Numscan Modular

In this example, we'll take the scanner that we built in
\ref numscancoupled and make it modular.

This example consists of three files:
- modnumscanner.h
- modnumscanner.re
- modnumparser.c

\section nsmheader 1. Create the Header File

The header file defines all the tokens that the scanner uses.

<pre>
	enum modnumscan_tokens {
		EOFTOK, ///< re2c scanners always return 0 when they hit the EOF.
		NUMBER, ///< a number is a consecutive string of digits.
		STRING, ///< a string is anything that isn't a number or a newline.
		NEWLINE, ///< a single newline (so tokens don't span multiple lines).
	};
</pre>

It also declares the routine used to attach the scanner to a
::scanstate structure.

<pre>
	struct scanstate;
	scanstate* modnumscan_attach(scanstate *ss);
</pre>

Notably absent is any sort of routine to actually return tokens.
Instead, you call scan_next_token().  This
allows the scanner to define its own \ref startstates.

\section nsmscanner 2. Create the Scanner

The scanner is contained in an .re file.  First, we need to
include scan.h and the header file for our scanner.

<pre>
	# include "libre2c/scan.h"
	# include "modnumscanner.h"
</pre>

The scanner itself is exactly the same as the one we created
in \ref numscancoupled.

<pre>
	static int modnumscan_start(scanstate *ss)
	{
		scanner_enter(ss);

		/-!re2c
		[0-9]+    { return NUMBER;  }
		[^0-9\\n]+ { return STRING; }
		[\\n]	  { ss->line++; return NEWLINE; }
		-/
	}
</pre>

Finally, we need to define the routine that attaches this scanner
to the scanstate.  The scanstate::state field contains the entrypoint
for the scanner.  The simplest attach routine just sets ss->state
to its entrypoint.  Read \ref linenos for a discussion of line numbers.
Although this scanner is too simple to need it, it could also use the
scanstate::scanref field for whatever it wants.

<pre>
	scanstate* modnumscan_attach(scanstate *ss)
	{
		if(ss) {
			ss->state = modnumscan_start;
			ss->line = 1;
		}

		return ss;
	}
</pre>

There.  Our scanner is complete.  To summarize, you just needed to:
- Create a header file containing the token definitions and attach routine prototype(s).
- Create a .re file containing the definitions of the re2c scanner and the attach routine(s).

\section nsmparser 3. Create the Parser

Our parser will read data from stdin.  It first allocates the scan
buffer and the scanner on the stack.  ss is just a convenience variable
so that later, if we decide to dynamically allocate the scanstate using
a function such as readfp_open(), we don't have to change all our
dereferences from . to ->.

<pre>
    char buffer[4096];
	scanstate scanner, *ss=&scanner;
</pre>

First we initialize the scanstate, telling it what scan buffer to use.
Then we attach a reader (readfp offers good portability) and the
scanner that we created in the previous step.

<pre>
	scanstate_init(ss, buffer, sizeof(buffer));
	readfp_attach(ss, stdin);
	modnumscan_attach(ss);
</pre>

Scanning is exactly the same as the \ref numscancoupled example.

<pre>
    do {
        tok = scan_next_token(ss);
        if(tok < 0) { ... }
		// process the token
    } while(tok);
</pre>

And we're done.  Because we allocated everything on the stack and
didn't open any files, there's nothing to clena up.  If we had
used readfp_open to open the file and allocate a scanner, however,
we would need to call readfp_close() here.

*/

// vi:syn=c

