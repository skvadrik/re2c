/** @file modnumparser.c
 *
 * This file demonstrates how to parse tokens from a modular scanner.
 * It's very much like numscan-coupled except:
 * - does not contain its scanner -- it attaches it
 * - reads data from a file rather than a memory block
 * - uses a dynamically-allocated scanstate
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libre2c/scan.h"
#include "libre2c/readfp.h"
#include "modnumscanner.h"


const char *tokname[] = { "EOF", "NUM", "STR", "NEWLINE"};


int main(int argc, char **argv)
{
    int tok;
	char buffer[4096];
    scanstate scanner, *ss=&scanner;

	scanstate_init(ss, buffer, sizeof(buffer));
	readfp_attach(ss, stdin);
	modnumscan_attach(ss);

	// Pull all the tokens from the scanner
    do {
        tok = scan_next_token(ss);
		if(tok < 0) {
			printf("Scanner returned an error: %d\n", tok);
			break;
		}

        printf("%2d: %-12s", ss->line, tokname[tok]);
		if(tok != NEWLINE) {
			// don't want to actually print the text of the newline
			// token -- it makes the output ugly.
			printf("<<%.*s>>", scan_token_length(ss),
					scan_token_start(ss));
		}
		printf("\n");
    } while(tok);

	// you only call readfp_close if you previously called readfp_open.
	// We didn't, so there's nothing to deallocate.

    return 0;
}

// vi:syn=c
