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
	fprintf (stdout,
	"usage: re2c [-bcdDefFghirsuvVwx18] [-o of] [-t th] file\n"
    /* MANWIDTH=88 PAGER=cat man re2c  | sed -n '/^OPTIONS/,/^INTERFACE/ p' |tail -n+2|head -n-1|sed 's/       //' |
       c_doublequote */
"\n"
"-? -h --help\n"
"       Display this info\n"
"\n"
"-b --bit-vectors\n"
"       Implies -s. Use bit vectors as well to try to coax better code  out  of\n"
"       the  compiler. Most useful for specifications with more than a few key\xe2\x80\x90\n"
"       words (e.g., for most programming languages).\n"
"\n"
"-c --conditions\n"
"       Used for (f)lex-like condition support.\n"
"\n"
"-d --debug-output\n"
"       Creates a parser that dumps information about the current position  and\n"
"       the state the parser is in.  This is useful for debugging parser issues\n"
"       and states. If you use this switch, you need to define a YYDEBUG macro,\n"
"       which  will be called like a function with two parameters: void YYDEBUG\n"
"       (int state, char current).  The first parameter receives the  state  or\n"
"       -1 and the second parameter receives the input at the current cursor.\n"
"\n"
"-D --emit-dot\n"
"       Emit  Graphviz  dot  data,  which  can then be processed with e.g., dot\n"
"       -Tpng input.dot > output.png.  Please  note  that  scanners  with  many\n"
"       states may crash dot.\n"
"\n"
"-e --ecb\n"
"       Generate  a  parser  that  supports EBCDIC. The generated code can deal\n"
"       with any character up to 0xFF. In this  mode,  re2c  assumes  an  input\n"
"       character  size of 1 byte. This switch is incompatible with -w, -x, -u,\n"
"       and -8.\n"
"\n"
"-f --storable-state\n"
"       Generate a scanner with support for storable state.\n"
"\n"
"-F --flex-syntax\n"
"       Partial support for flex syntax. When this flag is active, named  defi\xe2\x80\x90\n"
"       nitions  must  be surrounded by curly braces and can be defined without\n"
"       an equal sign  and  the  terminating  semicolon.   Instead,  names  are\n"
"       treated as direct double quoted strings.\n"
"\n"
"-g --computed-gotos\n"
"       Generate  a scanner that utilizes GCC's computed-goto feature. That is,\n"
"       re2c generates jump tables whenever a decision is of certain complexity\n"
"       (e.g.,  a  lot  of if conditions would be otherwise necessary). This is\n"
"       only usable with compilers that support this feature.  Note  that  this\n"
"       implies  -b  and  that the complexity threshold can be configured using\n"
"       the cgoto:threshold inplace configuration.\n"
"\n"
"-i --no-debug-info\n"
"       Do not output #line information. This is useful when you want use a CMS\n"
"       tool  with  re2c's output. You might want to do this if you do not want\n"
"       to impose re2c as a build requirement for your source.\n"
"\n"
"-o OUTPUT --output=OUTPUT\n"
"       Specify the OUTPUT file.\n"
"\n"
"-r --reusable\n"
"       Allows  reuse  of  scanner  definitions  with  /*!use:re2c   */   after\n"
"       /*!rules:re2c  */.   In  this mode, no /*!re2c */ block and exactly one\n"
"       /*!rules:re2c */ must be present.  The rules  are  saved  and  used  by\n"
"       every  /*!use:re2c  */  block  that  follows.  These blocks can contain\n"
"       inplace   configurations,   especially   re2c:flags:e,    re2c:flags:w,\n"
"       re2c:flags:x,  re2c:flags:u, and re2c:flags:8.  That way it is possible\n"
"       to create the same  scanner  multiple  times  for  different  character\n"
"       types, different input mechanisms, or different output mechanisms.  The\n"
"       /*!use:re2c */ blocks can also contain additional rules  that  will  be\n"
"       appended to the set of rules in /*!rules:re2c */.\n"
"\n"
"-s --nested-ifs\n"
"       Generate  nested ifs for some switches. Many compilers need this assist\n"
"       to generate better code.\n"
"\n"
"-t HEADER --type-header=HEADER\n"
"       Create a HEADER file that contains types for the (f)lex-like  condition\n"
"       support. This can only be activated when -c is in use.\n"
"\n"
"-u --unicode\n"
"       Generate  a  parser  that  supports UTF-32. The generated code can deal\n"
"       with any valid Unicode character up to 0x10FFFF.  In  this  mode,  re2c\n"
"       assumes an input character size of 4 bytes. This switch is incompatible\n"
"       with -e, -w, -x, and -8. This implies -s.\n"
"\n"
"-v --version\n"
"       Show version information.\n"
"\n"
"-V --vernum\n"
"       Show the version as a number in the MMmmpp (Majorm, minor, patch)  for\xe2\x80\x90\n"
"       mat.\n"
"\n"
"-w --wide-chars\n"
"       Generate a parser that supports UCS-2. The generated code can deal with\n"
"       any valid Unicode character up to 0xFFFF.  In this mode,  re2c  assumes\n"
"       an  input  character  size of 2 bytes. This switch is incompatible with\n"
"       -e, -x, -u, and -8. This implies -s.\n"
"\n"
"-x --utf-16\n"
"       Generate a parser that supports UTF-16. The  generated  code  can  deal\n"
"       with  any  valid  Unicode  character up to 0x10FFFF. In this mode, re2c\n"
"       assumes an input character size of 2 bytes. This switch is incompatible\n"
"       with -e, -w, -u, and -8. This implies -s.\n"
"\n"
"-8 --utf-8\n"
"       Generate a parser that supports UTF-8. The generated code can deal with\n"
"       any valid Unicode character up to 0x10FFFF. In this mode, re2c  assumes\n"
"       an input character size of 1 byte. This switch is incompatible with -e,\n"
"       -w, -x, and -u.\n"
"\n"
"--case-insensitive\n"
"       Makes all strings case insensitive.  This  makes  \"-quoted  expressions\n"
"       behave as '-quoted expressions.\n"
"\n"
"--case-inverted\n"
"       Invert  the  meaning  of  single  and  double quoted strings. With this\n"
"       switch, single quotes are case sensitive and  double  quotes  are  case\n"
"       insensitive.\n"
"\n"
"--no-generation-date\n"
"       Suppress date output in the generated file.\n"
"\n"
"--no-version\n"
"       Suppress version output in the generated file.\n"
"\n"
"--no-generation-date\n"
"       Suppress version output in the generated file.\n"
"\n"
"--encoding-policy POLICY\n"
"       Specify  how  re2c  must treat Unicode surrogates. POLICY can be one of\n"
"       the following: fail (abort with an error when a  surrogate  is  encoun\xe2\x80\x90\n"
"       tered),  substitute  (silently  replace  surrogates with the error code\n"
"       point 0xFFFD), ignore (treat surrogates  as  normal  code  points).  By\n"
"       default, re2c ignores surrogates (for backward compatibility). The Uni\xe2\x80\x90\n"
"       code standard says that standalone surrogates are invalid code  points,\n"
"       but different libraries and programs treat them differently.\n"
"\n"
"--input INPUT\n"
"       Specify re2c's input API. INPUT can be either default or custom.\n"
"\n"
"-S --skeleton\n"
"       Instead  of embedding re2c-generated code into C/C++ source, generate a\n"
"       self-contained program for the same DFA. Most  useful  for  correctness\n"
"       and performance testing.\n"
"\n"
"--empty-class POLICY\n"
"       What to do if the user uses an empty character class. POLICY can be one\n"
"       of the following: match-empty (match empty input: pretty illogical, but\n"
"       this  is  the  default for backwards compatibility reasons), match-none\n"
"       (fail to match on any input),  error  (compilation  error).  Note  that\n"
"       there  are  various  ways  to  construct  an  empty  class,  e.g.,  [],\n"
"       [^\\x00-\\xFF], [\\x00-\\xFF][\\x00-\\xFF].\n"
"\n"
"--dfa-minimization <table | moore>\n"
"       The internal algorithm used by re2c to minimize the  DFA  (defaults  to\n"
"       moore).   Both  the  table  filling  algorithm  and the Moore algorithm\n"
"       should produce the same DFA (up to states relabeling).  The table fill\xe2\x80\x90\n"
"       ing  algorithm  is  much  simpler  and slower; it serves as a reference\n"
"       implementation.\n"
"\n"
"-1 --single-pass\n"
"       Deprecated. Does nothing (single pass is the default now).\n"
"\n"
"-W     Turn on all warnings.\n"
"\n"
"-Werror\n"
"       Turn warnings into errors. Note that this option alone doesn't turn  on\n"
"       any  warnings  at  all;  it  only affects those warnings that have been\n"
"       turned on so far or those that will be turned on later.\n"
"\n"
"-W<warning>\n"
"       Turn on a warning.\n"
"\n"
"-Wno-<warning>\n"
"       Turn off a warning.\n"
"\n"
"-Werror-<warning>\n"
"       Turn on a warning and treat it as an error (this implies -W<warning>).\n"
"\n"
"-Wno-error-<warning>\n"
"       Don't treat this particular warning as an error. This doesn't turn  off\n"
"       the warning itself.\n"
"\n"
"-Wcondition-order\n"
"       Warn  if  the generated program makes implicit assumptions about condi\xe2\x80\x90\n"
"       tion numbering. You should use either the -t, --type-header  option  or\n"
"       the  /*!types:re2c*/ directive to generate a mapping of condition names\n"
"       to numbers and then use the autogenerated condition names.\n"
"\n"
"-Wempty-character-class\n"
"       Warn if a regular expression contains an empty character class.  Ratio\xe2\x80\x90\n"
"       nally,  trying  to  match  an  empty character class makes no sense: it\n"
"       should always fail. However, for backwards compatibility reasons,  re2c\n"
"       allows  empty  character  classes and treats them as empty strings. Use\n"
"       the --empty-class option to change the default behavior.\n"
"\n"
"-Wmatch-empty-string\n"
"       Warn if a regular expression in a rule is nullable  (matches  an  empty\n"
"       string).  If the DFA runs in a loop and an empty match is unintentional\n"
"       (the input position in not advanced manually), the lexer may get  stuck\n"
"       in an infinite loop.\n"
"\n"
"-Wswapped-range\n"
"       Warn if the lower bound of a range is greater than its upper bound. The\n"
"       default behavior is to silently swap the range bounds.\n"
"\n"
"-Wundefined-control-flow\n"
"       Warn if some input strings cause undefined control flow  in  the  lexer\n"
"       (the faulty patterns are reported). This is the most dangerous and most\n"
"       common mistake. It can be easily fixed by adding the default  rule  (*)\n"
"       (this rule has the lowest priority, matches any code unit, and consumes\n"
"       exactly one code unit).\n"
"\n"
"-Wunreachable-rules\n"
"       Warn about rules that are shadowed by other rules and will never match.\n"
"\n"
"-Wuseless-escape\n"
"       Warn if a symbol is escaped when it shouldn't  be.   By  default,  re2c\n"
"       silently  ignores such escapes, but this may as well indicate a typo or\n"
"       error in the escape sequence.\n"
"\n"
""
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
	vernum.resize(6, '0');

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
