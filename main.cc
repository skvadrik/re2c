/* $Id$ */
#include <fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "globals.h"
#include "parser.h"
#include "dfa.h"
#include "version.h"

char *fileName;
bool sFlag = false;
bool bFlag = false;
unsigned int oline = 1;

using namespace std;

int main(unsigned argc, char *argv[])
{
    fileName = NULL;
    if (argc == 1) {
		goto usage;
	}
    while(--argc > 1) {
		char *p = *++argv;
		if (*p != '-' || *(p+1) == '\0') {
			goto usage;
		}
		while (*++p != '\0') {
		    switch(*p){
		    case 'e':
				xlat = asc2ebc;
				talx = ebc2asc;
				break;
		    case 's':
				sFlag = true;
				break;
		    case 'b':
				sFlag = true;
				bFlag = true;
				break;
			case '-':
				if (!strcmp(p, "-version")) {
					goto version;
				}
				goto usage;
		    default:
				goto usage;
		    }
		}
    }
    fileName = *++argv;
    if (!strcmp(fileName, "--version")) {
    	goto version;
    }
    int fd;
    if (fileName[0] == '-' && fileName[1] == '\0') {
		fileName = "<stdin>";
		fd = 0;
    } else {
		if ((fd = open(fileName, O_RDONLY)) < 0) {
		    cerr << "can't open " << fileName << "\n";
		    return 1;
		}
    }
    parse(fd, cout);
    return 0;

usage:
    cerr << "usage: re2c [-esb] name\n";
    return 2;

version:
    cerr << "re2c " << RE2C_VERSION << "\n";
    return 2;
}
