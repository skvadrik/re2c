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

file_info sourceFileInfo;
file_info outputFileInfo;
file_info headerFileInfo;

bool bFlag = false;
bool cFlag = false;
bool dFlag = false;
bool DFlag = false;
bool eFlag = false;
bool fFlag = false;
bool FFlag = false;
bool gFlag = false;
bool iFlag = false;
bool rFlag = false;
bool sFlag = false;
bool tFlag = false;
bool uFlag = false;
bool wFlag = false;

bool bNoGenerationDate = false;

bool bSinglePass = false;
bool bFirstPass  = true;
bool bLastPass   = false;
bool bUsedYYBitmap  = false;

bool bUsedYYAccept  = false;
bool bUsedYYMaxFill = false;
bool bUsedYYMarker  = true;

bool bEmitYYCh       = true;
bool bUseStartLabel  = false;
bool bUseStateNext   = false;
bool bUseYYFill      = true;
bool bUseYYFillParam = true;
bool bUseYYFillCheck = true;
bool bUseYYFillNaked = false;
bool bUseYYSetConditionParam = true;
bool bUseYYGetConditionNaked = false;
bool bUseYYSetStateParam = true;
bool bUseYYSetStateNaked = false;
bool bUseYYGetStateNaked = false;

std::string startLabelName;
std::string labelPrefix("yy");
std::string condPrefix("yyc_");
std::string condEnumPrefix("yyc");
std::string condDivider("/* *********************************** */");
std::string condDividerParam("@@");
std::string condGoto("goto @@;");
std::string condGotoParam("@@");
std::string yychConversion("");
std::string yyFillLength("@@");
std::string yySetConditionParam("@@");
std::string yySetStateParam("@@");
std::string yySetupRule("");
uint maxFill = 1;
uint next_label = 0;
uint cGotoThreshold = 9;

uint topIndent = 0;
std::string indString("\t");
bool yybmHexTable = false;
bool bUseStateAbort = false;
bool bWroteGetState = false;
bool bWroteCondCheck = false;
bool bCaseInsensitive = false;
bool bCaseInverted = false;
bool bTypesDone = false;

uint nRealChars = 256;

uint next_fill_index = 0;
uint last_fill_index = 0;
std::set<uint> vUsedLabels;
CodeNames mapCodeName;
std::string typesInline;

free_list<RegExp*> RegExp::vFreeList;
free_list<Range*>  Range::vFreeList;

using namespace std;

static char *opt_arg = NULL;
static int opt_ind = 1;

static const mbo_opt_struct OPTIONS[] =
{
	mbo_opt_struct('?', 0, "help"),
	mbo_opt_struct('b', 0, "bit-vectors"),
	mbo_opt_struct('c', 0, "start-conditions"),
	mbo_opt_struct('d', 0, "debug-output"),
	mbo_opt_struct('D', 0, "emit-dot"),
	mbo_opt_struct('e', 0, "ecb"),
	mbo_opt_struct('f', 0, "storable-state"),
	mbo_opt_struct('F', 0, "flex-syntax"),
	mbo_opt_struct('g', 0, "computed-gotos"),
	mbo_opt_struct('h', 0, "help"),
	mbo_opt_struct('i', 0, "no-debug-info"),
	mbo_opt_struct('o', 1, "output"),
	mbo_opt_struct('r', 0, "reusable"),
	mbo_opt_struct('s', 0, "nested-ifs"),
	mbo_opt_struct('t', 1, "type-header"),
	mbo_opt_struct('u', 0, "unicode"),
	mbo_opt_struct('v', 0, "version"),
	mbo_opt_struct('V', 0, "vernum"),
	mbo_opt_struct('w', 0, "wide-chars"),
	mbo_opt_struct('1', 0, "single-pass"),
	mbo_opt_struct(10,  0, "no-generation-date"),
	mbo_opt_struct(11,  0, "case-insensitive"),
	mbo_opt_struct(12,  0, "case-inverted"),
	mbo_opt_struct('-', 0, NULL) /* end of args */
};

static void usage()
{
	std::cerr << "usage: re2c [-bcdDefFghirsuvVw1] [-o of] [-t th] file\n"
	"\n"
	"-? -h  --help           Display this info.\n"
	"\n"
	"-b     --bit-vectors    Implies -s. Use bit vectors as well in the attempt to\n"
	"                        coax better code out of the compiler. Most useful for\n"
	"                        specifications with more than a few keywords (e.g. for\n"
	"                        most programming languages).\n"
	"\n"
	"-c     --conditions     Require start conditions.\n"
	"\n"
	"-d     --debug-output   Creates a parser that dumps information during\n"
	"                        about the current position and in which state the\n"
	"                        parser is.\n"
	"\n"
	"-D     --emit-dot       Emit a Graphviz dot view of the DFA graph\n"
	"\n"
	"-e     --ecb            Cross-compile from an ASCII platform to an EBCDIC one.\n"
	"                        This cannot be combined with -w, -u or -r.\n"
	"\n"
	"-f     --storable-state Generate a scanner that supports storable states.\n"
	"\n"
	"-F     --flex-syntax    Partial support for flex syntax.\n"
	"\n"
	"-g     --computed-gotos Implies -b. Generate computed goto code (only useable\n"
	"                        with gcc).\n"
	"\n"
	"-i     --no-debug-info  Do not generate '#line' info (usefull for versioning).\n"
	"\n"
	"-o of  --output=of      Specify the output file (of) instead of stdout\n"
	"\n"
	"-r     --reusable       Allow reuse of scanner definitions.\n"
	"                        This cannot be used together with -e switch.\n"
	"\n"
	"-s     --nested-ifs     Generate nested ifs for some switches. Many compilers\n"
	"                        need this assist to generate better code.\n"
	"\n"
	"-t th  --type-header=th Generate a type header file (th) with type definitions.\n"
	"\n"
	"-u     --unicode        Implies -w but supports the full Unicode character set.\n"
	"                        This cannot be used together with -e switch.\n"
	"\n"
	"-v     --version        Show version information.\n"
	"\n"
	"-V     --vernum         Show version as one number.\n"
	"\n"
	"-w     --wide-chars     Create a parser that supports wide chars (UCS-2). This\n"
	"                        implies -s and cannot be used together with -e switch.\n"
	"\n"
	"-1     --single-pass    Force single pass generation, this cannot be combined\n"
	"                        with -f and disables YYMAXFILL generation prior to last\n"
	"                        re2c block.\n"
	"\n"
	"--no-generation-date    Suppress date output in the generated output so that it\n"
	"                        only shows the re2c version.\n"
	"\n"
	"--case-insensitive      All strings are case insensitive, so all \"-expressions\n"
	"                        are treated in the same way '-expressions are.\n"
	"\n"
	"--case-inverted         Invert the meaning of single and double quoted strings.\n"
	"                        With this switch single quotes are case sensitive and\n"
	"                        double quotes are case insensitive.\n"
	;
}

} // end namespace re2c

using namespace re2c;

int main(int argc, char *argv[])
{
	int c;
	const char *sourceFileName = 0;
	const char *outputFileName = 0;
	const char *headerFileName = 0;

	if (argc == 1)
	{
		usage();
		return 2;
	}

	while ((c = mbo_getopt(argc, argv, OPTIONS, &opt_arg, &opt_ind, 1)) != -1)
	{
		switch (c)
		{

			case 'b':
			bFlag = true;
			sFlag = true;
			break;

			case 'c':
			cFlag = true;
			break;

			case 'e':
			xlat = asc2ebc;
			talx = ebc2asc;
			eFlag = true;
			break;

			case 'd':
			dFlag = true;
			break;

			case 'D':
			DFlag = true;
			iFlag = true;
			break;

			case 'f':
			fFlag = true;
			break;

			case 'F':
			FFlag = true;
			break;

			case 'g':
			gFlag = true;
			bFlag = true;
			sFlag = true;
			break;

			case 'i':
			iFlag = true;
			break;

			case 'o':
			outputFileName = opt_arg;
			break;

			case 'r':
			rFlag = true;
			break;

			case 's':
			sFlag = true;
			break;

			case 't':
			tFlag = true;
			headerFileName = opt_arg;
			break;
			
			case '1':
			bSinglePass = true;
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
			nRealChars = (1<<16); /* 0x10000 */
			sFlag = true;
			wFlag = true;
			break;

			case 'u':
			nRealChars = 0x110000; /* 17 times w-Flag */
			sFlag = true;
			uFlag = true;
			break;
	  
			default:
			case 'h':
			case '?':
			usage();
			return 2;

			case 10:
			bNoGenerationDate = true;
			break;

			case 11:
			bCaseInsensitive = true;
			break;

			case 12:
			bCaseInverted = true;
			break;
		}
	}

	if ((bFlag || fFlag) && bSinglePass) {
		std::cerr << "re2c: error: Cannot combine -1 and -b or -f switch\n";
		return 1;
	}
	if (!cFlag && headerFileName)
	{
		std::cerr << "re2c: error: Can only output a header file when using -c switch\n";
		return 2;
	}

	if (rFlag && eFlag)
	{
		std::cerr << "re2c: error: Cannot combine -e with -r switch\n";
		return 2;
	}
	if (wFlag && eFlag)
	{
		std::cerr << "re2c: error: Cannot combine -e with -w or -u switch\n";
		return 2;
	}
	if (wFlag && uFlag)
	{
		std::cerr << "re2c: error: Cannot combine -u with -w switch\n";
		return 2;
	}

	if (dFlag && DFlag)
	{
		std::cerr << "re2c: error: Cannot combine -d with -D switch\n";
		return 2;
	}

	if (uFlag)
	{
		wFlag = true;
	}

	if (argc == opt_ind + 1)
	{
		sourceFileName = argv[opt_ind];
	}
	else
	{
		std::cerr << "Unexpected argument: " << argv[argc-1] << "\n\n";
		usage();
		return 2;
	}

	// set up the source stream
	re2c::ifstream_lc source;

	if (sourceFileName[0] == '-' && sourceFileName[1] == '\0')
	{
		if (fFlag)
		{
			std::cerr << "re2c: error: multiple /*!re2c stdin is not acceptable when -f is specified\n";
			return 1;
		}
		sourceFileName = "<stdin>";
		source.open(stdin);
	}
	else if (!source.open(sourceFileName).is_open())
	{
		cerr << "re2c: error: cannot open " << sourceFileName << "\n";
		return 1;
	}

	// set up the output stream
	re2c::ofstream_lc output;
	re2c::ofstream_lc header;

	if (outputFileName == 0 || (sourceFileName[0] == '-' && sourceFileName[1] == '\0'))
	{
		outputFileName = "<stdout>";
		output.open(stdout);
	}
	else if (!output.open(outputFileName).is_open())
	{
		cerr << "re2c: error: cannot open " << outputFileName << "\n";
		return 1;
	}
	if (headerFileName)
	{
		if (!header.open(headerFileName).is_open())
		{
			cerr << "re2c: error: cannot open " << headerFileName << "\n";
			return 1;
		}
		headerFileInfo = file_info(headerFileName, &header);
	}
	Scanner scanner(source, output);
	sourceFileInfo = file_info(sourceFileName, &scanner);
	outputFileInfo = file_info(outputFileName, &output);

	if (!bSinglePass)
	{
		bUsedYYMarker = false;

		re2c::ifstream_lc null_source;
		
		if (!null_source.open(sourceFileName).is_open())
		{
			cerr << "re2c: error: cannot re-open " << sourceFileName << "\n";
			return 1;
		}

		null_stream  null_dev;
		Scanner null_scanner(null_source, null_dev);
		parse(null_scanner, null_dev, NULL);
		next_label = 0;
		next_fill_index = 0;
		bWroteGetState = false;
		bWroteCondCheck = false;
		bUsedYYMaxFill = false;
		bFirstPass = false;
		sourceFileInfo.set_fname(sourceFileName);
	}

	bLastPass = true;
	parse(scanner, output, header.is_open() ? &header : NULL);
	return 0;
}
