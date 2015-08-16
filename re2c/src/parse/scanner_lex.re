#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include "src/ir/dfa/dfa.h"
#include "src/globals.h"
#include "src/parse/extop.h"
#include "src/parse/parser.h"
#include "src/parse/scanner.h"
#include "y.tab.h"
#include "src/util/s_to_n32_unsafe.h"

extern YYSTYPE yylval;

#define	YYCTYPE		unsigned char
#define	YYCURSOR	cur
#define	YYLIMIT		lim
#define	YYMARKER	ptr
#define	YYCTXMARKER ctx
#define	YYFILL(n)	{ fill (n); }

namespace re2c
{

// source code is in ASCII: pointers have type 'char *'
// but re2c makes an implicit assumption that YYCTYPE is unsigned
// when it generates comparisons
/*!re2c
	re2c:yych:conversion = 1;
*/

/*!re2c
zero    = "\000";
dot     = .;
esc     = dot \ [\\];
istring = "[" "^" ((esc \ [\]]) | "\\" dot)* "]" ;
cstring = "["     ((esc \ [\]]) | "\\" dot)* "]" ;
dstring = "\""    ((esc \ ["] ) | "\\" dot)* "\"";
sstring = "'"     ((esc \ ['] ) | "\\" dot)* "'" ;
letter  = [a-zA-Z];
digit   = [0-9];
lineno  = [1-9] digit*;
number  = "0" | ("-"? [1-9] digit*);
name    = (letter|digit|"_")+;
cname   = ":" name;
space   = [ \t];
ws      = (space | [\r\n]);
eol     = ("\r\n" | "\n");
config  = "re2c" cname+ ("@" name)?;
value   = [^\r\n; \t]* | dstring | sstring;
lineinf = lineno (space+ dstring)? eol;
*/

Scanner::ParseMode Scanner::echo()
{
	bool ignore_eoc = false;
	int  ignore_cnt = 0;

	if (eof && cur == eof) // Catch EOF
	{
		return Stop;
	}

	tok = cur;
echo:
/*!re2c
   beginRE     =  "%{" | "/*!re2c";
   beginRE     {
					if (rFlag)
					{
						fatal("found standard 're2c' block while using -r flag");
					}
					if (!(DFlag || flag_skeleton))
					{
						const size_t lexeme_len = cur[-1] == '{'
							? sizeof ("%{") - 1
							: sizeof ("/*!re2c") - 1;
						out.write(tok, tok_len () - lexeme_len);
					}
					tok = cur;
					return Parse;
				}
	"/*!rules:re2c"	{
					if (rFlag)
					{
						mapCodeName.clear();
					}
					else
					{
						fatal("found 'rules:re2c' block without -r flag");
					}
					tok = cur;
					return Rules;
				}
	"/*!use:re2c"	{
					if (!rFlag)
					{
						fatal("found 'use:re2c' block without -r flag");
					}
					reuse();
					if (!(DFlag || flag_skeleton))
					{
						const size_t lexeme_len = sizeof ("/*!use:re2c") - 1;
						out.write(tok, tok_len () - lexeme_len);
					}
					tok = cur;
					return Reuse;
				}
	"/*!max:re2c" {
					if (!DFlag)
					{
						out.insert_yymaxfill ();
					}
					tok = pos = cur;
					ignore_eoc = true;
					goto echo;
				}
	"/*!getstate:re2c" {
					tok = pos = cur;
					out.insert_state_goto (topIndent);
					ignore_eoc = true;
					goto echo;
				}
	"/*!ignore:re2c" {
					tok = pos = cur;
					ignore_eoc = true;
					goto echo;
				}
	"/*!types:re2c" {
					tok = pos = cur;
					ignore_eoc = true;
					if (!DFlag)
					{
						out.insert_line_info ();
						out << "\n";
						out.insert_types ();
						out << "\n";
						out.write_line_info (cline, get_fname ().c_str ());
					}
					goto echo;
				}
	"*" "/"	"\r"? "\n"	{
					cline++;
					if (ignore_eoc)
					{
						if (ignore_cnt)
						{
							out.write_line_info (cline, get_fname ().c_str ());
						}
						ignore_eoc = false;
						ignore_cnt = 0;
					}
					else if (!(DFlag || flag_skeleton))
					{
						out.write(tok, tok_len ());
					}
					tok = pos = cur;
					goto echo;
				}
	"*" "/"		{
					if (ignore_eoc)
					{
						if (ignore_cnt)
						{
							out << "\n";
							out.write_line_info (cline, get_fname ().c_str ());
						}
						ignore_eoc = false;
						ignore_cnt = 0;
					}
					else if (!(DFlag || flag_skeleton))
					{
						out.write(tok, tok_len ());
					}
					tok = pos = cur;
					goto echo;
				}
	"\n" space* "#" space* "line" space+ / lineinf {
					set_sourceline ();
					goto echo;
				}
	"\n"		{
					if (ignore_eoc)
					{
						ignore_cnt++;
					}
					else if (!(DFlag || flag_skeleton))
					{
						out.write(tok, tok_len ());
					}
					tok = pos = cur;
					cline++;
					goto echo;
				}
	zero		{
					if (!(ignore_eoc || DFlag || flag_skeleton))
					{
						out.write(tok, tok_len () - 1);
						// -1 so we don't write out the \0
					}
					if(cur == eof)
					{
						return Stop;
					}
				}
	*			{
					goto echo;
				}
*/
}

int Scanner::scan()
{
	uint32_t depth;

scan:
	tchar = cur - pos;
	tline = cline;
	tok = cur;
	switch (lexer_state)
	{
		case LEX_NORMAL:       goto start;
		case LEX_CONFIG:       goto config;
		case LEX_CONFIG_VALUE: goto value;
		case LEX_FLEX_NAME:    goto flex_name;
	}

start:
/*!re2c
	"{"			{
					depth = 1;
					goto code;
				}

	":" / "=>"	{
					return *tok;
				}

	":="		{
					tok += 2; /* skip ":=" */
					depth = 0;
					goto code;
				}

        "//"            {
				goto nextLine;
			}
	"/*"		{
					depth = 1;
					goto comment;
				}

   endRE    =  "%}" | "*/";
   endRE    {
					tok = cur;
					return 0;
				}

	dstring		{
					SubStr s (tok + 1, tok_len () - 2); // -2 to omit quotes
					if (bCaseInsensitive || bCaseInverted)
					{
						yylval.regexp = strToCaseInsensitiveRE (s);
					}
					else
					{
						yylval.regexp = strToRE (s);
					}
					return STRING;
				}

	sstring		{
					SubStr s (tok + 1, tok_len () - 2); // -2 to omit quotes
					if (bCaseInverted)
					{
						yylval.regexp = strToRE (s);
					}
					else
					{
						yylval.regexp = strToCaseInsensitiveRE (s);
					}
					return STRING;
				}

	"\""		{
					fatal("unterminated string constant (missing \")");
				}
	"'"			{
					fatal("unterminated string constant (missing ')");
				}

	istring		{
					SubStr s (tok, tok_len ());
					yylval.regexp = invToRE (s);
					return RANGE;
				}

	cstring		{
					SubStr s (tok, tok_len ());
					yylval.regexp = ranToRE (s);
					return RANGE;
				}

	"["			{
					fatal("unterminated range (missing ])");
				}

	"<>" / (space* ("{" | "=>" | ":=")) {
					return NOCOND;
				}
	"<!"		{
					return SETUP;
				}
	[<>,()|=;/\\]	{
					return *tok;
				}

	"*"			{
					yylval.op = *tok;
					return STAR;
				}
	[+?]		{
					yylval.op = *tok;
					return CLOSE;
				}

	"{0,}"		{
					yylval.op = '*';
					return CLOSE;
				}

	"{" [0-9]+ "}"	{
					if (!s_to_u32_unsafe (tok + 1, cur - 1, yylval.extop.min))
					{
						fatal ("repetition count overflow");
					}
					yylval.extop.max = yylval.extop.min;
					return CLOSESIZE;
				}

	"{" [0-9]+ "," [0-9]+ "}"	{
					const char * p = strchr (tok, ',');
					if (!s_to_u32_unsafe (tok + 1, p, yylval.extop.min))
					{
						fatal ("repetition lower bound overflow");
					}
					if (!s_to_u32_unsafe (p + 1, cur - 1, yylval.extop.max))
					{
						fatal ("repetition upper bound overflow");
					}
					return CLOSESIZE;
				}

	"{" [0-9]+ ",}"		{
					if (!s_to_u32_unsafe (tok + 1, cur - 2, yylval.extop.min))
					{
						fatal ("repetition lower bound overflow");
					}
					yylval.extop.max = UINT32_MAX;
					return CLOSESIZE;
				}

	"{" [0-9]* ","		{
					fatal("illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers");
				}

	"{" name "}"	{
					if (!FFlag) {
						fatal("curly braces for names only allowed with -F switch");
					}
					yylval.str = new std::string (tok + 1, tok_len () - 2); // -2 to omit braces
					return ID;
				}

	config		{
					tok += 5; /* skip "re2c:" */
					lexer_state = LEX_CONFIG;
					yylval.str = new std::string (tok, tok_len ());
					return CONFIG;
				}

	name / (space+ [^=>,])	{
					yylval.str = new std::string (tok, tok_len ());
					if (FFlag)
					{
						lexer_state = LEX_FLEX_NAME;
						return FID;
					}
					else
					{
						return ID;
					}
				}

	name / (space* [=>,])	{
					yylval.str = new std::string (tok, tok_len ());
					return ID;
				}

	name / [^]	{
					if (!FFlag) {
						yylval.str = new std::string (tok, tok_len ());
						return ID;
					} else {
						/* Add one char in front and one behind instead of 's or "s */
						SubStr s (tok, tok_len ());
						if (bCaseInsensitive || bCaseInverted)
						{
							yylval.regexp = strToCaseInsensitiveRE (s);
						}
						else
						{
							yylval.regexp = strToRE (s);
						}
						return STRING;
					}
				}

	"."			{
					yylval.regexp = mkDot();
					return RANGE;
				}

	space+		{
					goto scan;
				}

	eol space* "#" space* "line" space+ / lineinf {
					set_sourceline ();
					goto scan;
				}

	eol			{
					if (cur == eof) return 0;
					pos = cur;
					cline++;
					goto scan;
				}

	*			{
					fatalf("unexpected character: '%c'", *tok);
					goto scan;
				}
*/

flex_name:
/*!re2c
	eol
	{
		YYCURSOR = tok;
		lexer_state = LEX_NORMAL;
		return FID_END;
	}
	*
	{
		YYCURSOR = tok;
		goto start;
	}
*/

code:
/*!re2c
	"}"			{
					if (depth == 0)
					{
						fatal("Curly braces are not allowed after ':='");
					}
					else if (--depth == 0)
					{
						yylval.code = new Code (tok, tok_len (), get_fname (), tline);
						return CODE;
					}
					goto code;
				}
	"{"			{
					if (depth == 0)
					{
						fatal("Curly braces are not allowed after ':='");
					}
					else
					{
						++depth;
					}
					goto code;
				}
	"\n" space* "#" space* "line" space+ / lineinf {
					set_sourceline ();
					goto code;
				}
	"\n" /  ws	{
					if (depth == 0)
					{
						goto code;
					}
					else if (cur == eof)
					{
						fatal("missing '}'");
					}
					pos = cur;
					cline++;
					goto code;
				}
	"\n"		{
					if (depth == 0)
					{
						tok += strspn(tok, " \t\r\n");
						while (cur > tok && strchr(" \t\r\n", cur[-1]))
						{
							--cur;
						}
						yylval.code = new Code (tok, tok_len (), get_fname (), tline);
						return CODE;
					}
					else if (cur == eof)
					{
						fatal("missing '}'");
					}
					pos = cur;
					cline++;
					goto code;
				}
	zero		{
					if (cur == eof)
					{
						if (depth)
						{
							fatal("missing '}'");
						}
						return 0;
					}
					goto code;
				}
	dstring | sstring	{
					goto code;
				}
	*			{
					goto code;
				}
*/

comment:
/*!re2c
	"*/"		{
					if (--depth == 0)
					{
						goto scan;
					}
					else
					{
						goto comment;
					}
				}
	"/*"		{
					++depth;
					fatal("ambiguous /* found");
					goto comment;
				}
	"\n" space* "#" space* "line" space+ / lineinf {
					set_sourceline ();
					goto comment;
				}
	"\n"		{
					if (cur == eof)
					{
						return 0;
					}
					tok = pos = cur;
					cline++;
					goto comment;
				}
	*			{
					if (cur == eof)
					{
						return 0;
					}
					goto comment;
				}
*/

nextLine:
/*!re2c                                  /* resync emacs */
   "\n"     { if(cur == eof) {
                  return 0;
               }
               tok = pos = cur;
               cline++;
               goto scan;
            }
   *        {  if(cur == eof) {
                  return 0;
               }
               goto nextLine;
            }
*/

config:
/*!re2c
	space+		{
					goto config;
				}
	"=" space*	{
					lexer_state = LEX_CONFIG_VALUE;
					return '=';
				}
	*			{
					fatal("missing '='");
				}
*/

value:
/*!re2c
	number		{
					if (!s_to_i32_unsafe (tok, cur, yylval.number))
					{
						fatal ("configuration value overflow");
					}
					lexer_state = LEX_NORMAL;
					return NUMBER;
				}
	value		{
					yylval.str = new std::string (tok, tok_len ());
					lexer_state = LEX_NORMAL;
					return VALUE;
				}
*/
}

static void escape (std::string & dest, const std::string & src)
{
	dest = src;
	size_t l = dest.length();
	for (size_t p = 0; p < l; ++p)
	{
		if (dest[p] == '\\')
		{
			dest.insert(++p, "\\");
			++l;
		}
	}
}

void Scanner::set_sourceline ()
{
sourceline:
	tok = cur;
/*!re2c	
	lineno		{
					if (!s_to_u32_unsafe (tok, cur, cline))
					{
						fatal ("line number overflow");
					}
					goto sourceline; 
				}
	dstring		{
					escape (in.file_name, std::string (tok + 1, tok_len () - 2)); // -2 to omit quotes
			  		goto sourceline; 
				}
	"\n"			{
  					if (cur == eof)
  					{
						--cur; 
					}
			  		else
			  		{
			  			pos = cur; 
			  		}
			  		tok = cur;
			  		return; 
				}
	*			{
  					goto sourceline;
  				}
*/
}

} // end namespace re2c
