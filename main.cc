/* $Id$ */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "globals.h"
#include "parser.h"
#include "dfa.h"
#include "mbo_getopt.h"

char *fileName;
bool sFlag = false;
bool bFlag = false;
unsigned int oline = 1;

using namespace std;

static char *opt_arg = NULL;
static int opt_ind = 1;

static const mbo_opt_struct OPTIONS[] = {
	{'?', 0, "help"},
	{'b', 0, "bit-vectors"},
	{'e', 0, "ecb"},
	{'h', 0, "help"},
	{'s', 0, "nested-ifs"},
	{'v', 0, "version"}
};

int main(int argc, char *argv[])
{
	int c;
    fileName = NULL;
    outputFileName = NULL;

    if (argc == 1) {
		goto usage;
	}

	while ((c = mbo_getopt(argc, argv, OPTIONS, &opt_arg, &opt_ind, 0))!=-1) {
		switch (c) {
	    case '?':
			goto usage;
	    case 'b':
			sFlag = true;
			bFlag = true;
			break;
	    case 'e':
			xlat = asc2ebc;
			talx = ebc2asc;
			break;
	    case 'h':
			goto usage;
		case 'f':
			outputFileName = opt_arg;
			break;
	    case 's':
			sFlag = true;
			break;
		case 'v':
			goto version;
		default:
			goto usage;
		}
	}

	if (argc == opt_ind + 1)
	{
		fileName = argv[opt_ind];
	}
	else
	{
		goto usage;
	}

    int fd;
    if (fileName[0] == '-' && fileName[1] == '\0')
    {
		fileName = "<stdin>";
		fd = 0;
    }
    else
    {
		if ((fd = open(fileName, O_RDONLY)) < 0)
		{
		    cerr << "can't open " << fileName << "\n";
		    return 1;
		}
    }
   	parse(fd, cout);
    return 0;

usage:
    cerr << "usage: re2c [-esbvh] file\n";
    return 2;

version:
    cerr << "re2c " << PACKAGE_VERSION << "\n";
    return 2;
}
