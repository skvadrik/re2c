/** @file cscan.re
 *
 * Example: how to use start states to switch the state of your scanner.
 *
 * The technique demonstrated in this file, implementing start states
 * by manipulating the scanner's entrypoint, is but one method
 * of implementing start states.  The re2c manpage shows another
 * technique.
 *
 * This file needs to be processed by re2c, http://re2c.org
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libre2c/scan.h"
#include "cscan.h"

// forward declaration
static int comment(scanstate *ss);


/**
 * This is the entrypoint for the scanner.  It recognizes all
 * data and C++ comments.  When it recognizes a C comment, it
 * switches to the "comment" state.
 */

static int initial(scanstate *ss)
{
	scanner_enter(ss);

	// unfortunately doxygen eats the re2c declarations
	// because it uses the same block delimiter.
/*!re2c
"//"[^\n]* / [\n]	{ return CPCOMMENT; }
[/][*]				{ ss->state = comment; return COMBEG; }
[^/\n]+				{ return DATA; }
"/"/[^/*]			{ return DATA; }
[\n]	  			{ ss->line++; return NEWLINE; }
*/
}


/**
 * This is the entrypoint for the "comment" state.  It returns
 * COMMENT tokens until it finds the end of the comment.
 */

static int comment(scanstate *ss)
{
	scanner_enter(ss);

	// unfortunately doxygen eats the re2c declarations
	// because it uses the same block delimiter.
/*!re2c
[*][/]				{ ss->state = initial; return COMEND; }
[^*\n]+				{ return COMMENT; }
"*"/[^/]			{ return COMMENT; }
[\n]	  			{ ss->line++; return NEWLINE; }
*/
}


/**
 * This routine turns the given scanstate structure into a comment scanner.
 */

scanstate* commentscan_attach(scanstate *ss)
{
	if(ss) {
		ss->state = initial;
		ss->line = 1;
	}

	return ss;
}


/** \page sspage Start States

\section startstates Comment Matcher

This example demonstrates how to use start states in your
re2c scanners.  It creates a scanner that looks
for C comments.  This scanner has two states:
- the initial state that parses all non-comment data.  When it sees
  slash-star, it switches to:
- the comment state that parses the contents of a C-style comment.

The source code to this example can be found in:
- cscan.re
- cscan.h
- cparse.c

A scanner with start states is just like any other modular scanner
(see \ref numscanmodular), except that it has multiple entrypoints.
Each entrypoint corresponds to a state.

<pre>
	# include "re2c/scan.h"
	# include "cscan.h"

	// forward declaration
	static int comment(scanstate *ss);
</pre>

Our comment scanner 
has two states: the initial state, and the comment state.
The scanner starts in the initial state.  When it notices
slash-star indicating the start of a comment, it returns the COMBEG
token and switches to the comment state.

<pre>
	static int initial(scanstate *ss)
	{
		scanner_enter(ss);

		/-!re2c
		"//"[^\\n]* / [\\n]   { return CPCOMMENT; }
		[/][*]              { ss->state = comment; return COMBEG; }
		[^/\\n]+             { return DATA; }
		"/"/[^\057*]           { return DATA; }
		[\\n]                { ss->line++; return NEWLINE; }
		-/
	}
</pre>

You can switch your scanner's state at any time, but you would typically
do it right before you return the token.  The next time the scanner is
called, it is called through the new scanproc.

The scanner is in the comment state while it is scanning a comment.

<pre>
	static int comment(scanstate *ss)
	{
		scanner_enter(ss);

		/-!re2c
		[*][/]          { ss->state = initial; return COMEND; }
		[^*\\n]+         { return COMMENT; }
		"*"/[^/]        { return COMMENT; }
		[\\n]            { ss->line++; return NEWLINE; }
		-/
	}
</pre>

Finally, we attach the scanner as we always do.

<pre>
	scanstate* commentscan_attach(scanstate *ss)
	{
		if(ss) {
			ss->state = initial;
			ss->line = 1;
		}

		return ss;
	}
</pre>

People familiar with Lex may want to define BEGIN(x) (ss->state=(x))
to make this feel more Lexish.

The technique described here is but one way of implementing start
states.  The re2c manpage shows another way to emulate start states
using goto statements.

*/

// vi:syn=c

