/* $Id$ */
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "scanner.h"
#include "parser.h"
#include "y.tab.h"
#include "globals.h"
#include "dfa.h"

extern YYSTYPE yylval;

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define	YYCTYPE		unsigned char
#define	YYCURSOR	cursor
#define	YYLIMIT		lim
#define	YYMARKER	ptr
#define	YYCTXMARKER ctx
#define	YYFILL(n)	{cursor = fill(cursor, n);}

#define	RETURN(i)	{cur = cursor; return i;}

namespace re2c
{

/*!re2c
zero    = "\000";
any     = [\000-\377];
dot     = any \ [\n];
esc     = dot \ [\\];
istring = "[" "^" ((esc \ [\]]) | "\\" dot)* "]" ;
cstring = "["     ((esc \ [\]]) | "\\" dot)* "]" ;
dstring = "\""    ((esc \ ["] ) | "\\" dot)* "\"";
sstring = "'"     ((esc \ ['] ) | "\\" dot)* "'" ;
letter  = [a-zA-Z];
digit   = [0-9];
lineno  = [1-9] digit*;
number  = "0" | ("-"? [1-9] digit*);
name    = (letter|"_") (letter|digit|"_")*;
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
	char *cursor = cur;
	bool ignore_eoc = false;
	int  ignore_cnt = 0;

	if (eof && cursor == eof) // Catch EOF
	{
		return Stop;
	}

	tok = cursor;
echo:
/*!re2c
	"/*!re2c"	{
					if (rFlag)
					{
						fatal("found standard 're2c' block while using -r flag");
					}
					if (bUsedYYMaxFill && bSinglePass)
					{
						fatal("found scanner block after YYMAXFILL declaration");
					}
					if (!DFlag)
					{
						out.write((const char*)(tok), (const char*)(&cursor[-7]) - (const char*)(tok));
					}
					tok = cursor;
					RETURN(Parse);
				}
	"/*!rules:re2c"	{
					if (rFlag)
					{
						mapCodeName.clear();
					}
					else
					{
						fatal("found 'reules:re2c' block without -r flag");
					}
					if (bUsedYYMaxFill && bSinglePass)
					{
						fatal("found scanner block after YYMAXFILL declaration");
					}
					tok = cursor;
					RETURN(Rules);
				}
	"/*!use:re2c"	{
					if (!rFlag)
					{
						fatal("found 'use:re2c' block without -r flag");
					}
					reuse();
					if (bUsedYYMaxFill && bSinglePass)
					{
						fatal("found scanner block after YYMAXFILL declaration");
					}
					if (!DFlag)
					{
						out.write((const char*)(tok), (const char*)(&cursor[-11]) - (const char*)(tok));
					}
					tok = cursor;
					RETURN(Reuse);
				}
	"/*!max:re2c" {
					if (bUsedYYMaxFill)
					{
						fatal("cannot generate YYMAXFILL twice");
					}
					if (!DFlag)
					{
						out << "#define YYMAXFILL " << maxFill << std::endl;
					}
					tok = pos = cursor;
					ignore_eoc = true;
					bUsedYYMaxFill = true;
					goto echo;
				}
	"/*!getstate:re2c" {
					tok = pos = cursor;
					genGetStateGoto(out, topIndent, 0);
					ignore_eoc = true;
					goto echo;
				}
	"/*!ignore:re2c" {
					tok = pos = cursor;
					ignore_eoc = true;
					goto echo;
				}
	"/*!types:re2c" {
					if (bSinglePass)
					{
						fatal("cannot generate types inline in single pass mode");
					}
					tok = pos = cursor;
					ignore_eoc = true;
					if (bLastPass && !DFlag)
					{
						out << outputFileInfo;
						out << "\n";
						out << typesInline;
						out << "\n";
						out << sourceFileInfo;
					}
					goto echo;
				}
	"*" "/"	"\r"? "\n"	{
					cline++;
					if (ignore_eoc)
					{
						if (ignore_cnt)
						{
							out << sourceFileInfo;
						}
						ignore_eoc = false;
						ignore_cnt = 0;
					}
					else if (!DFlag)
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					goto echo;
				}
	"*" "/"		{
					if (ignore_eoc)
					{
						if (ignore_cnt)
						{
							out << "\n" << sourceFileInfo;
						}
						ignore_eoc = false;
						ignore_cnt = 0;
					}
					else if (!DFlag)
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					goto echo;
				}
	"\n" space* "#" space* "line" space+ / lineinf {
					set_sourceline(cursor);
					goto echo;
				}
	"\n"		{
					if (ignore_eoc)
					{
						ignore_cnt++;
					}
					else if (!DFlag)
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok));
					}
					tok = pos = cursor;
					cline++;
					goto echo;
				}
	zero		{
					if (!ignore_eoc && !DFlag)
					{
						out.write((const char*)(tok), (const char*)(cursor) - (const char*)(tok) - 1);
						// -1 so we don't write out the \0
					}
					if(cursor == eof)
					{
						RETURN(Stop);
					}
				}
	any			{
					goto echo;
				}
*/
}

int Scanner::scan()
{
	char *cursor = cur;
	uint depth;

scan:
	tchar = cursor - pos;
	tline = cline;
	tok = cursor;
	if (iscfg == 1)
	{
		goto config;
	}
	else if (iscfg == 2)
	{
		goto value;
	}
/*!re2c
	"{"			{
					depth = 1;
					goto code;
				}

	":" / "=>"	{
					RETURN(*tok);
				}

	":="		{
					cur = cursor;
					tok += 2; /* skip ":=" */
					depth = 0;
					goto code;
				}

	"/*"		{
					depth = 1;
					goto comment;
				}

	"*/"		{
					tok = cursor;
					RETURN(0);
				}

	dstring		{
					cur = cursor;
					if (bCaseInsensitive || bCaseInverted)
					{
						yylval.regexp = strToCaseInsensitiveRE(token());
					}
					else
					{
						yylval.regexp = strToRE(token());
					}
					return STRING;
				}

	sstring		{
					cur = cursor;
					if (bCaseInverted)
					{
						yylval.regexp = strToRE(token());
					}
					else
					{
						yylval.regexp = strToCaseInsensitiveRE(token());
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
					cur = cursor;
					yylval.regexp = invToRE(token());
					return RANGE;
				}

	cstring		{
					cur = cursor;
					yylval.regexp = ranToRE(token());
					return RANGE;
				}

	"["			{
					fatal("unterminated range (missing ])");
				}

	"<>" / (space* ("{" | "=>" | ":=")) {
					RETURN(NOCOND);
				}
	"<!"		{
					RETURN(SETUP);
				}
	[<>,()|=;/\\]	{
					RETURN(*tok);
				}

	"*"			{
					yylval.op = *tok;
					RETURN(STAR);
				}
	[+?]		{
					yylval.op = *tok;
					RETURN(CLOSE);
				}

	"{0,}"		{
					yylval.op = '*';
					RETURN(CLOSE);
				}

	"{" [0-9]+ "}"	{
					yylval.extop.minsize = atoi((char *)tok+1);
					yylval.extop.maxsize = atoi((char *)tok+1);
					RETURN(CLOSESIZE);
				}

	"{" [0-9]+ "," [0-9]+ "}"	{
					yylval.extop.minsize = atoi((char *)tok+1);
					yylval.extop.maxsize = MAX(yylval.extop.minsize,atoi(strchr((char *)tok, ',')+1));
					RETURN(CLOSESIZE);
				}

	"{" [0-9]+ ",}"		{
					yylval.extop.minsize = atoi((char *)tok+1);
					yylval.extop.maxsize = -1;
					RETURN(CLOSESIZE);
				}

	"{" [0-9]* ","		{
					fatal("illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers");
				}

	"{" name "}"	{
					if (!FFlag) {
						fatal("curly braces for names only allowed with -F switch");
					}
					cur = cursor;
					yylval.symbol = Symbol::find(token(1, cur - tok - 2));
					return ID;
				}

	config		{
					cur = cursor;
					tok += 5; /* skip "re2c:" */
					iscfg = 1;
					yylval.str = new Str(token());
					return CONFIG;
				}

	name / (space+ [^=>,])	{
					cur = ptr > tok ? ptr - 1 : cursor;
					yylval.symbol = Symbol::find(token());
					return FFlag ? FID : ID;
				}

	name / (space* [=>,])	{
					cur = ptr > tok ? ptr - 1 : cursor;
					yylval.symbol = Symbol::find(token());
					return ID;
				}

	name / [^]	{
					if (!FFlag) {
						cur = cursor;
						yylval.symbol = Symbol::find(token());
						return ID;
					} else {
						/* Add one char in front and one behind instead of 's or "s */
						cur = cursor;
						if (bCaseInsensitive || bCaseInverted)
						{
							yylval.regexp = strToCaseInsensitiveRE(raw_token("\""));
						}
						else
						{
							yylval.regexp = strToRE(raw_token("\""));
						}
						return STRING;
					}
				}

	"."			{
					cur = cursor;
					yylval.regexp = mkDot();
					return RANGE;
				}

	space+		{
					goto scan;
				}

	eol space* "#" space* "line" space+ / lineinf {
					set_sourceline(cursor);
					goto scan;
				}

	eol			{
					if (cursor == eof) RETURN(0);
					pos = cursor;
					cline++;
					goto scan;
				}

	any			{
					std::ostringstream msg;
					msg << "unexpected character: ";
					prtChOrHex(msg, *tok);
					fatal(msg.str().c_str());
					goto scan;
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
						cur = cursor;
						yylval.token = new Token(token(), sourceFileInfo.fname, tline);
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
					set_sourceline(cursor);
					goto code;
				}
	"\n" /  ws	{
					if (depth == 0)
					{
						goto code;
					}
					else if (cursor == eof)
					{
						fatal("missing '}'");
					}
					pos = cursor;
					cline++;
					goto code;
				}
	"\n"		{
					if (depth == 0)
					{
						cur = cursor;
						tok += strspn(tok, " \t\r\n");
						while (cur > tok && strchr(" \t\r\n", cur[-1]))
						{
							--cur;
						}
						yylval.token = new Token(token(), sourceFileInfo.fname, tline);
						return CODE;
					}
					else if (cursor == eof)
					{
						fatal("missing '}'");
					}
					pos = cursor;
					cline++;
					goto code;
				}
	zero		{
					if (cursor == eof)
					{
						if (depth)
						{
							fatal("missing '}'");
						}
						RETURN(0);
					}
					goto code;
				}
	dstring | sstring | any	{
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
					set_sourceline(cursor);
					goto comment;
				}
	"\n"		{
					if (cursor == eof)
					{
						RETURN(0);
					}
					tok = pos = cursor;
					cline++;
					goto comment;
				}
	any			{
					if (cursor == eof)
					{
						RETURN(0);
					}
					goto comment;
				}
*/

config:
/*!re2c
	space+		{
					goto config;
				}
	"=" space*	{
					iscfg = 2;
					cur = cursor;
					RETURN('=');
				}
	any			{
					fatal("missing '='");
				}
*/

value:
/*!re2c
	number		{
					cur = cursor;
					yylval.number = atoi(token().to_string().c_str());
					iscfg = 0;
					return NUMBER;
				}
	value		{
					cur = cursor;
					yylval.str = new Str(token());
					iscfg = 0;
					return VALUE;
				}
*/
}

void Scanner::set_sourceline(char *& cursor) 
{
sourceline:
	tok = cursor;
/*!re2c	
	lineno		{
					cur = cursor;
					cline = atoi(token().to_string().c_str());
					goto sourceline; 
				}
	dstring		{
					cur = cursor;
					sourceFileInfo.set_fname(token(1, cur - tok - 2).to_string());
			  		goto sourceline; 
				}
	"\n"			{
  					if (cursor == eof)
  					{
						--cursor; 
					}
			  		else
			  		{
			  			pos = cursor; 
			  		}
			  		tok = cursor;
			  		return; 
				}
	any			{
  					goto sourceline;
  				}
*/
}

} // end namespace re2c
