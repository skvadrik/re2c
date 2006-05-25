/** @file cparse.c
 *
 * This file simply prints the tokens returned by the comment scanner.
 * See \ref numscanmodular for a description of how this routine works.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libre2c/scan.h"
#include "libre2c/readfp.h"
#include "cscan.h"


const char *tokname[] = { "EOF", "LABEL", "DATA", "CPCOM",
	"COMBEG", "COMMENT", "COMEND", "NEWLINE"};


int main(int argc, char **argv)
{
    int tok;
    scanstate *ss;

	ss = readfp_open("comtest", BUFSIZ);
	if(!ss) {
		fprintf(stderr, "Could not create scanner.  Missing comtest file?\n");
		exit(1);
	}
	commentscan_attach(ss);

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

	readfp_close(ss);

    return 0;
}

// vi:syn=c
