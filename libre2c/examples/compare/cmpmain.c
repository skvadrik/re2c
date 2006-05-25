/** @file cmpmain.c
 *
 * This file demonstrates how to use the comparison scanner.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libre2c/scan.h"
#include "libre2c/readfp.h"
#include "compare.h"


/** Performs the actual comparison.
 */

compare_result compare(FILE *fp1, FILE *fp2, int brief)
{
	// NOTE!!
	// This code is meant to be simple so I take shortcuts like
	// exiting without cleaning up.  Sorry.

	char buf1[39], buf2[8];		// these sizes are totally arbitrary
    scanstate ssrec, *ss=&ssrec;
	int n, cont;

	scanstate_init(ss, buf1, sizeof(buf1));
	readfp_attach(ss, fp1);
	compare_attach(ss);

    do {
		n = fread(buf2, 1, sizeof(buf2), fp2);
		if(n <= 0) {
			if(ferror(fp2)) {
				fprintf(stderr, "Error reading second file.\n");
				exit(17);
			}
			if(feof(fp2)) {
				break;
			}
		}

		cont = compare_continue(ss, buf2, n);
		if(cont < 0) {
			fprintf(stderr, "Error reading first file.\n");
			exit(17);
		}
    } while(cont == 0);

	return brief ? compare_check(ss) : compare_check_newlines(ss);
}


/** Exercises the compare scanner.
 *
 * This program sort of like diff --brief.  It just compares two files.
 *
 * Exit code is:
 * - 0: the files were the same
 * - 1: they differed.
 *
 * If you don't specify -b then you also get these codes:
 * - 2: First file has 1 more newline than the second file
 * - 3: Second file has 1 more newline than the first file.
 *
 * See compare_attach() and test_tiny_buffer().
 */

int main(int argc, char **argv)
{
	compare_result result;
	FILE *fp1, *fp2;
	int brief = 0;

	// Check for the brief argument:
	if(argv[1] && (!strcmp(argv[1],"-b") || !strcmp(argv[1],"--brief"))) {
		brief = 1;
		argc--, argv++;
	}
	// Ensure we have the right number of arguments.
	if(argc != 3) {
		fprintf(stderr, "You must specify two files to compare.\n");
		exit(13);
	}
	

	// Open the first file unless it's - in which case we use stdin
	fp1 = (strcmp(argv[1],"-") ? fopen(argv[1], "r") : stdin);
	if(!fp1) {
		fprintf(stderr, "Could not open %s\n", argv[2]);
		exit(15);
	}

	// Open the second file unless it's - in which case we use stdin
	fp2 = (strcmp(argv[2],"-") ? fopen(argv[2], "r") : stdin);
	if(!fp2) {
		fprintf(stderr, "Could not open %s\n", argv[2]);
		exit(16);
	}

	// do the check
	result = compare(fp1, fp2, brief);

	if(fp1 != stdin) fclose(fp1);
	if(fp2 != stdin) fclose(fp2);

	// determine the result
	switch(result) {
		case cmp_full_match:
			printf("Files are identical.\n");
			return 0;
		case cmp_no_match:
		case cmp_ss_has_more_data:
			printf("Files differ.\n");
			return 1;
		case cmp_ptr_has_extra_nl:
		case cmp_ptr_has_more_nls:
			printf("Second file has 1 more newline than the first file.\n");
			return 2;
		case cmp_ss_has_extra_nl:
			printf("First file has 1 more newline than the second file.\n");
			return 3;
		default:
			fprintf(stderr, "Unknown comparison code: %d??\n", (int)result);
			exit(19);
	}

	fprintf(stderr, "How the heck did this get executed?\n");
	exit(20);
}

