#include <stdarg.h>
#include <stdio.h>
#include <string>

#include "config.h"
#include "src/conf/msg.h"

namespace re2c {

void error (const char * fmt, ...)
{
	fprintf (stderr, "re2c: error: ");

	va_list args;
	va_start (args, fmt);
	vfprintf (stderr, fmt, args);
	va_end (args);

	fprintf (stderr, "\n");
}

void error_encoding ()
{
	error ("only one of switches -e, -w, -x, -u and -8 must be set");
}

void error_arg (const char * option)
{
	error ("expected argument to option %s", option);
}

void warning_start (uint32_t line, bool error)
{
	static const char * msg = error ? "error" : "warning";
	fprintf (stderr, "re2c: %s: line %u: ", msg, line);
}

void warning_end (const char * type, bool error)
{
	if (type != NULL)
	{
		const char * prefix = error ? "error-" : "";
		fprintf (stderr, " [-W%s%s]", prefix, type);
	}
	fprintf (stderr, "\n");
}

void warning (const char * type, uint32_t line, bool error, const char * fmt, ...)
{
	warning_start (line, error);

	va_list args;
	va_start (args, fmt);
	vfprintf (stderr, fmt, args);
	va_end (args);

	warning_end (type, error);
}

void usage ()
{
	fprintf (stderr,
	"usage: re2c [-bcdDefFghirsuvVwx18] [-o of] [-t th] file\n"
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
	"-e     --ecb            Generate a parser that supports EBCDIC. The generated code\n"
	"                        can deal with any character up to 0xFF. In this mode re2c\n"
	"                        assumes that input character size is 1 byte. This switch is\n"
	"                        incompatible with -w, -u, -x and -8\n"
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
	"\n"
	"-s     --nested-ifs     Generate nested ifs for some switches. Many compilers\n"
	"                        need this assist to generate better code.\n"
	"\n"
	"-t th  --type-header=th Generate a type header file (th) with type definitions.\n"
	"\n"
	"-u     --unicode        Generate a parser that supports UTF-32. The generated code\n"
	"                        can deal with any valid Unicode character up to 0x10FFFF.\n"
	"                        In this mode re2c assumes that input character size is 4 bytes.\n"
	"                        This switch is incompatible with -e, -w, -x and -8. It implies -s.\n"
	"\n"
	"-v     --version        Show version information.\n"
	"\n"
	"-V     --vernum         Show version as one number.\n"
	"\n"
	"-w     --wide-chars     Generate a parser that supports UCS-2. The generated code can\n"
	"                        deal with any valid Unicode character up to 0xFFFF. In this mode\n"
	"                        re2c assumes that input character size is 2 bytes. This switch is\n"
	"                        incompatible with -e, -x, -u and -8. It implies -s."
	"\n"
	"-x     --utf-16         Generate a parser that supports UTF-16. The generated code can\n"
	"                        deal with any valid Unicode character up to 0x10FFFF. In this mode\n"
	"                        re2c assumes that input character size is 2 bytes. This switch is\n"
	"                        incompatible with -e, -w, -u and -8. It implies -s."
	"\n"
	"-8     --utf-8          Generate a parser that supports UTF-8. The generated code can\n"
	"                        deal with any valid Unicode character up to 0x10FFFF. In this mode\n"
	"                        re2c assumes that input character size is 1 byte. This switch is\n"
	"                        incompatible with -e, -w, -x and -u."
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
	"\n"
	"--encoding-policy ep    Specify what re2c should do when given bad code unit.\n"
	"                        ep can be one of the following: fail, substitute, ignore.\n"
	"\n"
	"--input i               Specify re2c input API.\n"
	"                        i can be one of the following: default, custom.\n"
	"\n"
	"--skeleton              Instead of embedding re2c-generated code into C/C++ source,\n"
	"                        generate a self-contained program for the same DFA.\n"
	"                        Most useful for correctness and performance testing.\n"
	"\n"
	"--empty-class policy    What to do if user inputs empty character class. policy can be\n"
	"                        one of the following: 'match-empty' (match empty input, default),\n"
	"                        'match-none' (fail to match on any input), 'error' (compilation\n"
	"                        error). Note that there are various ways to construct empty class,\n"
	"                        e.g: [], [^\\x00-\\xFF], [\\x00-\\xFF]\\[\\x00-\\xFF].\n"
	"\n"
	"-1     --single-pass    Deprecated and does nothing (single pass is by default now).\n"
	);
}
 
void vernum ()
{
	std::string vernum (PACKAGE_VERSION);
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

	printf ("%s\n", vernum.c_str ());
}

void version ()
{
	printf ("re2c %s\n", PACKAGE_VERSION);
}

std::string incond (const std::string & cond)
{
	std::string s;
	if (!cond.empty ())
	{
		s += "in condition '";
		s += cond;
		s += "' ";
	}
	return s;
}

} // namespace re2c
