/** @file main.c
 *
 * This file is inteded to be a skeleton project where you can
 * just fill in the blanks.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libre2c/scan.h"
#include "libre2c/readfp.h"
#include "scanner.h"

#ifndef BUFSIZ
#define BUFSIZ 8192
#endif



/** This routine is called once for each token in the input file. */

void process_token(const char *filename, int lineno,
		int tokno, const char *tokstart, int toklen)
{
	// tokstart is not null terminated.  The length of the string
	// in tokstart is given by toklen.


	// ADD YOUR CODE HERE TO PROCESS THE TOKENS
	printf("%s:%03d\t%d\t%.*s\n", filename, lineno, tokno,
			toklen < 40 ? toklen : 40, tokstart);
}


/** Opens and scans the file named on the command line. */

int main(int argc, char **argv)
{
	const char *filename;
    scanstate scanner, *ss = &scanner;
	char buffer[BUFSIZ];

    int token;
	FILE *fp;

	filename = argv[1];
	if(filename == NULL) {
		fprintf(stderr, "You must supply the file to open!\n");
		exit(1);
	}

	fp = fopen(filename, "r");
	if(!fp) {
		fprintf(stderr, "Could not open file %s\n", filename);
		exit(1);
	}

	// Create the scanner
	scanstate_init(ss, buffer, sizeof(buffer));
	readfp_attach(ss, fp);		// attach the readproc
	scanner_attach(ss);			// attach the scanner


    do {
        token = scan_next_token(ss);
		if(token < 0) {
			printf("Scanner's readproc returned an error: %d\n", token);
			break;
		}

		process_token(filename, ss->line, token,
				scan_token_start(ss), scan_token_length(ss));
    } while(token);


	// No need to deallocate the scanner because everything
	// was allocated on the stack.

	fclose(fp);

    return 0;
}

// vi:syn=c
