#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include "src/ir/dfa/dfa.h"
#include "src/globals.h"
#include "src/parse/extop.h"
#include "src/parse/parser.h"
#include "src/parse/scanner.h"
#include "src/parse/unescape.h"
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
dstring = "\"" ((. \ [\\"] ) | "\\" .)* "\"";
sstring = "'"  ((. \ [\\'] ) | "\\" .)* "'" ;
letter  = [a-zA-Z];
digit   = [0-9];
lineno  = [1-9] digit*;
number  = "0" | ("-"? [1-9] digit*);
name    = (letter|digit|"_")+;
space   = [ \t];
ws      = (space | [\r\n]);
eol     = ("\r\n" | "\n");
lineinf = lineno (space+ dstring)? eol;

	esc = "\\";
	hex_digit = [0-9a-fA-F];
	esc_hex = esc ("x" hex_digit{2} | [uX] hex_digit{4} | "U" hex_digit{8});
	esc_oct = esc [0-3] [0-7]{2}; // max 1-byte octal value is '\377'
	esc_simple = esc [abfnrtv\\];

	naked_char = . \ (space | [;]);
	naked      = "" | (naked_char \ ['"]) naked_char*;
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
					if (opts.rFlag)
					{
						fatal("found standard 're2c' block while using -r flag");
					}
					if (!(opts.DFlag || opts.flag_skeleton))
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
					if (opts.rFlag)
					{
						opts.mapCodeName.clear();
					}
					else
					{
						fatal("found 'rules:re2c' block without -r flag");
					}
					tok = cur;
					return Rules;
				}
	"/*!use:re2c"	{
					if (!opts.rFlag)
					{
						fatal("found 'use:re2c' block without -r flag");
					}
					reuse();
					if (!(opts.DFlag || opts.flag_skeleton))
					{
						const size_t lexeme_len = sizeof ("/*!use:re2c") - 1;
						out.write(tok, tok_len () - lexeme_len);
					}
					tok = cur;
					return Reuse;
				}
	"/*!max:re2c" {
					if (!opts.DFlag)
					{
						out.insert_yymaxfill ();
					}
					tok = pos = cur;
					ignore_eoc = true;
					goto echo;
				}
	"/*!getstate:re2c" {
					tok = pos = cur;
					out.insert_state_goto (opts.topIndent);
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
					if (!opts.DFlag)
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
					else if (!(opts.DFlag || opts.flag_skeleton))
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
					else if (!(opts.DFlag || opts.flag_skeleton))
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
					else if (!(opts.DFlag || opts.flag_skeleton))
					{
						out.write(tok, tok_len ());
					}
					tok = pos = cur;
					cline++;
					goto echo;
				}
	zero		{
					if (!(ignore_eoc || opts.DFlag || opts.flag_skeleton))
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
		case LEX_NORMAL:    goto start;
		case LEX_CONF:      goto conf_eq;
		case LEX_FLEX_NAME: goto flex_name;
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

	"'"
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints ('\'', cpoints);
		yylval.regexp = cpoint_string (cpoints, opts.bCaseInsensitive || !opts.bCaseInverted);
		return REGEXP;
	}
	"\""
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints ('"', cpoints);
		yylval.regexp = cpoint_string (cpoints, opts.bCaseInsensitive || opts.bCaseInverted);
		return REGEXP;
	}
	"["
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints (']', cpoints);
		yylval.regexp = cpoint_class (cpoints, false);
		return REGEXP;
	}
	"[^"
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints (']', cpoints);
		yylval.regexp = cpoint_class (cpoints, true);
		return REGEXP;
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
					if (!opts.FFlag) {
						fatal("curly braces for names only allowed with -F switch");
					}
					yylval.str = new std::string (tok + 1, tok_len () - 2); // -2 to omit braces
					return ID;
				}

	"re2c:" { goto conf; }

	name / (space+ [^=>,])	{
					yylval.str = new std::string (tok, tok_len ());
					if (opts.FFlag)
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
					if (!opts.FFlag) {
						yylval.str = new std::string (tok, tok_len ());
						return ID;
					} else {
						std::vector<uint32_t> cpoints;
						for (char * p = tok; p < cur; ++p)
						{
							cpoints.push_back (static_cast<uint8_t> (*p));
						}
						yylval.regexp = cpoint_string (cpoints, opts.bCaseInsensitive || opts.bCaseInverted);
						return REGEXP;
					}
				}

	"."			{
					yylval.regexp = mkDot();
					return REGEXP;
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

conf:
	tok = cur;
	lexer_state = LEX_CONF;
/*!re2c
	* { fatal ((tok - pos) - tchar, "unrecognized configuration"); }

	"define:"
		( "YYBACKUP"
		| "YYBACKUPCTX"
		| "YYCONDTYPE"
		| "YYCTXMARKER"
		| "YYCTYPE"
		| "YYCURSOR"
		| "YYDEBUG"
		| "YYFILL"
		| "YYGETCONDITION"
		| "YYGETSTATE"
		| "YYLESSTHAN"
		| "YYLIMIT"
		| "YYMARKER"
		| "YYPEEK"
		| "YYRESTORE"
		| "YYRESTORECTX"
		| "YYSETCONDITION"
		| "YYSETSTATE"
		| "YYSKIP"
		)
	{
		tok += sizeof "define:" - 1;
		yylval.str = new std::string (tok, tok_len ());
		return CONF;
	}

	"label:"
		( "yyFillLabel"
		| "yyNext"
		)
	{
		tok += sizeof "label:" - 1;
		yylval.str = new std::string (tok, tok_len ());
		return CONF;
	}

	"variable:"
		( "yyaccept"
		| "yybm"
		| "yych"
		| "yyctable"
		| "yystable"
		| "yytarget"
		)
	{
		tok += sizeof "variable:" - 1;
		yylval.str = new std::string (tok, tok_len ());
		return CONF;
	}

	"condprefix"                  { return CONF_CONDPREFIX; }
	"condenumprefix"              { return CONF_CONDENUMPREFIX; }
	"cond:divider"                { return CONF_COND_DIVIDER; }
	"cond:divider@cond"           { return CONF_COND_DIVIDER_COND; }
	"cond:goto"                   { return CONF_COND_GOTO; }
	"cond:goto@cond"              { return CONF_COND_GOTO_COND; }
	"cgoto:threshold"             { return CONF_CGOTO_THRESHOLD; }
	"define:YYFILL:naked"         { return CONF_DEFINE_YYFILL_NAKED; }
	"define:YYFILL@len"           { return CONF_DEFINE_YYFILL_LEN; }
	"define:YYGETCONDITION:naked" { return CONF_DEFINE_YYGETCONDITION_NAKED; }
	"define:YYGETSTATE:naked"     { return CONF_DEFINE_YYGETSTATE_NAKED; }
	"define:YYSETCONDITION@cond"  { return CONF_DEFINE_YYSETCONDITION_COND; }
	"define:YYSETSTATE:naked"     { return CONF_DEFINE_YYSETSTATE_NAKED; }
	"define:YYSETSTATE@state"     { return CONF_DEFINE_YYSETSTATE_STATE; }
	"flags:" [ewxu8]
	{
		switch (YYCURSOR[-1])
		{
			case 'e': yylval.enc = Enc::EBCDIC; break;
			case 'w': yylval.enc = Enc::UCS2;   break;
			case 'x': yylval.enc = Enc::UTF16;  break;
			case 'u': yylval.enc = Enc::UTF32;  break;
			case '8': yylval.enc = Enc::UTF8;   break;
		}
		return CONF_FLAGS;
	}
	"indent:string"               { return CONF_INDENT_STRING; }
	"indent:top"                  { return CONF_INDENT_TOP; }
	"labelprefix"                 { return CONF_LABELPREFIX; }
	"startlabel"                  { return CONF_STARTLABEL; }
	"state:abort"                 { return CONF_STATE_ABORT; }
	"state:nextlabel"             { return CONF_STATE_NEXTLABEL; }
	"yybm:hex"                    { return CONF_YYBM_HEX; }
	"yych:conversion"             { return CONF_YYCH_CONVERSION; }
	"yych:emit"                   { return CONF_YYCH_EMIT; }
	"yyfill:check"                { return CONF_YYFILL_CHECK; }
	"yyfill:enable"               { return CONF_YYFILL_ENABLE; }
	"yyfill:parameter"            { return CONF_YYFILL_PARAMETER; }
*/

conf_eq:
/*!re2c
	* { fatal ("missing '=' in configuration"); }
	space* "=" space* { goto conf_val; }
*/

conf_val:
	tok = cur;
	lexer_state = LEX_NORMAL;
/*!re2c
	number
	{
		if (!s_to_i32_unsafe (tok, cur, yylval.num))
		{
			fatal ("configuration value overflow");
		}
		return NUM;
	}
	['"]
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints (tok[0], cpoints);
		yylval.str = cpoint_conf (cpoints);
		return STRING;
	}
	naked
	{
		yylval.str = new std::string (tok, tok_len ());
		return STRING;
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

void Scanner::lex_cpoints (char quote, std::vector<uint32_t> & cs)
{
	for (;;)
	{
		tok = cur;
	/*!re2c
		*          { fatal ((tok - pos) - tchar, "syntax error"); }
		esc [xXuU] { fatal ((tok - pos) - tchar, "syntax error in hexadecimal escape sequence"); }
		esc [0-7]  { fatal ((tok - pos) - tchar, "syntax error in octal escape sequence"); }
		esc        { fatal ((tok - pos) - tchar, "syntax error in escape sequence"); }

		esc_hex    { cs.push_back (unesc_hex (tok, cur)); continue; }
		esc_oct    { cs.push_back (unesc_oct (tok, cur)); continue; }
		esc_simple { cs.push_back (unesc_simple (tok));   continue; }
		esc .
		{
			const char c = tok[1];
			if (c != quote)
			{
				warn.useless_escape (tline, tok - pos, c);
			}
			cs.push_back (static_cast<uint8_t> (c));
			continue;
		}
		. \ esc
		{
			const char c = tok[0];
			if (c == quote)
			{
				return;
			}
			else
			{
				cs.push_back (static_cast<uint8_t> (c));
				continue;
			}
		}
	*/
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
