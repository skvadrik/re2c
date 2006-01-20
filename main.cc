/* $Id$ */
#ifdef HAVE_CONFIG_H
#include "config.h"
#elif defined(_WIN32)
#include "config_w32.h"
#endif

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "parser.h"
#include "dfa.h"
#include "mbo_getopt.h"

namespace re2c
{

const char *fileName = 0;
const char *outputFileName = 0;
bool bFlag = false;
bool dFlag = false;
bool eFlag = false;
bool iFlag = false;
bool sFlag = false;
bool wFlag = false;
bool bUsedYYAccept = false;
bool bUsedCtxMarker= false;
bool bUseStartLabel= true;
std::string startLabelName;
unsigned int oline = 1;
uint maxFill = 1;

uint topIndent = 0;
std::string indString("\t");
bool yybmHexTable = false;

uint nRealChars = 256;

int vFillIndexes = -1;
std::set<uint> vUsedLabels;

using namespace std;

static char *opt_arg = NULL;
static int opt_ind = 1;

static const mbo_opt_struct OPTIONS[] =
{
	mbo_opt_struct('?', 0, "help"),
	mbo_opt_struct('b', 0, "bit-vectors"),
	mbo_opt_struct('d', 0, "debug-output"),
	mbo_opt_struct('e', 0, "ecb"),
	mbo_opt_struct('f', 0, "storable-state"),
	mbo_opt_struct('h', 0, "help"),
	mbo_opt_struct('i', 0, "no-debug-info"),
	mbo_opt_struct('o', 1, "output"),
	mbo_opt_struct('s', 0, "nested-ifs"),
	mbo_opt_struct('v', 0, "version"),
	mbo_opt_struct('V', 0, "vernum"),
	mbo_opt_struct('w', 0, "wide-chars"),      
	mbo_opt_struct('-', 0, NULL) /* end of args */
};

static void usage()
{
	cerr << "usage: re2c [-esbvhd] file\n"
	"\n"
	"-? -h  --help           Display this info.\n"
	"\n"
	"-b     --bit-vectors    Implies -s. Use bit vectors as well in the attempt to\n"
	"                        coax better code out of the compiler. Most useful for\n"
	"                        specifications with more than a few keywords (e.g. for\n"
	"                        most programming languages).\n"
	"\n"
	"-d     --debug-output   Creates a parser that dumps information during\n"
	"                        about the current position and in which state the\n"
	"                        parser is.\n"
	"\n"
	"-e     --ecb            Cross-compile from an ASCII platform to\n"
	"                        an EBCDIC one.\n"
	"\n"
	"-f     --storable-state Generate a scanner with support for storable state\n"
	"\n"
	"-i     --no-debug-info  Do not generate '#line' info (usefull for versioning).\n"
	"\n"
	"-o     --output=output  Specify the output file instead of stdout\n"
	"                        This cannot be used together with -e switch.\n"
	"\n"
	"-s     --nested-ifs     Generate nested ifs for some switches. Many compilers\n"
	"                        need this assist to generate better code.\n"
	"\n"
	"-v     --version        Show version information.\n"
	"-V     --vernum         Show version as one number.\n"
	"\n"
	"-w     --wide-chars     Create a parser that supports wide chars (UCS-2). This\n"
	"                        implies -s and cannot be used together with -e switch.\n"
	;
}

} // end namespace re2c

using namespace re2c;

int main(int argc, char *argv[])
{
	int c;
	fileName = NULL;

	if (argc == 1)
	{
		usage();
		return 2;
	}

	while ((c = mbo_getopt(argc, argv, OPTIONS, &opt_arg, &opt_ind, 0)) != -1)
	{
		switch (c)
		{

			case 'b':
			sFlag = true;
			bFlag = true;
			break;

			case 'e':
			xlat = asc2ebc;
			talx = ebc2asc;
			eFlag = true;
			break;

			case 's':
			sFlag = true;
			break;

			case 'd':
			dFlag = true;
			break;

			case 'f':
			vFillIndexes = 0;
			break;

			case 'i':
			iFlag = true;
			break;

			case 'o':
			outputFileName = opt_arg;
			break;

			case 'v':
			cout << "re2c " << PACKAGE_VERSION << "\n";
			return 2;

			case 'V': {
				string vernum(PACKAGE_VERSION);

				if (vernum[1] == '.')
				{
					vernum.insert(0, "0");
				}
				vernum.erase(2, 1);
				if (vernum[3] == '.')
				{
					vernum.insert(2, "0");
				}
				vernum.erase(4, 1);
				if (vernum.length() < 6 || vernum[5] < '0' || vernum[5] > '9')
				{
					vernum.insert(4, "0");
				}
				vernum.resize(6);
				cout << vernum << endl;
				return 2;
			}
			
			case 'w':
			nRealChars = (1<<16);
			sFlag = true;
			wFlag = true;
			break;
	  
			case 'h':
			case '?':
			default:
			usage();
			return 2;
		}
	}

	if (wFlag && eFlag)
	{
		usage();
		return 2;
	}
	else if (argc == opt_ind + 1)
	{
		fileName = argv[opt_ind];
	}
	else
	{
		usage();
		return 2;
	}

	// set up the input stream
	//istream* input = 0;
	basic_istream<char> *input = 0;

	ifstream inputFile;

	if (fileName[0] == '-' && fileName[1] == '\0')
	{
		fileName = "<stdin>";
		input = &cin;
	}
	else
	{
		inputFile.open(fileName);

		if (!inputFile)
		{
			cerr << "can't open " << fileName << "\n";
			return 1;
		}

		input = &inputFile;
	}

	// set up the output stream
	ostream* output = 0;

	ofstream outputFile;

	if (outputFileName == 0 || (fileName[0] == '-' && fileName[1] == '\0'))
	{
		outputFileName = "<stdout>";
		output = &cout;
	}
	else
	{
		outputFile.open(outputFileName);

		if (!outputFile)
		{
			cerr << "can't open " << outputFileName << "\n";
			return 1;
		}

		output = &outputFile;
		
		int len = strlen(outputFileName);
		char *tmp = (char*)malloc((len+1)*2);
		char *dst = tmp;

		for (const char *src = outputFileName; *src; ++src)
		{
			if (*src == '\\')
			{
				*dst++ = *src;
			}
			*dst++ = *src;
		}
		*dst = '\0';
		
		outputFileName = tmp;
	}

	parse(*input, *output);
	return 0;

}

