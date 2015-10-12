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

	conf_assign = space* "=" space*;
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
					if (opts->rFlag)
					{
						fatal("found standard 're2c' block while using -r flag");
					}
					if (opts->target == opt_t::CODE)
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
					if (opts->rFlag)
					{
						opts.reset_mapCodeName ();
					}
					else
					{
						fatal("found 'rules:re2c' block without -r flag");
					}
					tok = cur;
					return Rules;
				}
	"/*!use:re2c"	{
					if (!opts->rFlag)
					{
						fatal("found 'use:re2c' block without -r flag");
					}
					reuse();
					if (opts->target == opt_t::CODE)
					{
						const size_t lexeme_len = sizeof ("/*!use:re2c") - 1;
						out.write(tok, tok_len () - lexeme_len);
					}
					tok = cur;
					return Reuse;
				}
	"/*!max:re2c" {
					if (opts->target != opt_t::DOT)
					{
						out.insert_yymaxfill ();
					}
					tok = pos = cur;
					ignore_eoc = true;
					goto echo;
				}
	"/*!getstate:re2c" {
					tok = pos = cur;
					out.insert_state_goto (opts->topIndent);
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
					if (opts->target != opt_t::DOT)
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
					else if (opts->target == opt_t::CODE)
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
					else if (opts->target == opt_t::CODE)
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
					else if (opts->target == opt_t::CODE)
					{
						out.write(tok, tok_len ());
					}
					tok = pos = cur;
					cline++;
					goto echo;
				}
	zero		{
					if (!ignore_eoc && opts->target == opt_t::CODE)
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
		yylval.regexp = cpoint_string (cpoints, opts->bCaseInsensitive || !opts->bCaseInverted);
		return REGEXP;
	}
	"\""
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints ('"', cpoints);
		yylval.regexp = cpoint_string (cpoints, opts->bCaseInsensitive || opts->bCaseInverted);
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
					if (!opts->FFlag) {
						fatal("curly braces for names only allowed with -F switch");
					}
					yylval.str = new std::string (tok + 1, tok_len () - 2); // -2 to omit braces
					return ID;
				}

	"re2c:" { goto conf; }

	name / (space+ [^=>,])	{
					yylval.str = new std::string (tok, tok_len ());
					if (opts->FFlag)
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
					if (!opts->FFlag) {
						yylval.str = new std::string (tok, tok_len ());
						return ID;
					} else {
						std::vector<uint32_t> cpoints;
						for (char * p = tok; p < cur; ++p)
						{
							cpoints.push_back (static_cast<uint8_t> (*p));
						}
						yylval.regexp = cpoint_string (cpoints, opts->bCaseInsensitive || opts->bCaseInverted);
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
/*!re2c
	* { fatal ((tok - pos) - tchar, "unrecognized configuration"); }

	"condprefix"                  { opts.set_condPrefix       (lex_conf_string ()); return CONF; }
	"condenumprefix"              { opts.set_condEnumPrefix   (lex_conf_string ()); return CONF; }
	"cond:divider"                { opts.set_condDivider      (lex_conf_string ()); return CONF; }
	"cond:divider@cond"           { opts.set_condDividerParam (lex_conf_string ()); return CONF; }
	"cond:goto"                   { opts.set_condGoto         (lex_conf_string ()); return CONF; }
	"cond:goto@cond"              { opts.set_condGotoParam    (lex_conf_string ()); return CONF; }
	"cgoto:threshold"
	{
		const int32_t n = lex_conf_number ();
		if (n < 0)
		{
			fatal ("configuration 'cgoto:threshold' must be nonnegative");
		}
		opts.set_cGotoThreshold (static_cast<uint32_t> (n));
		return CONF;
	}
	"define:YYBACKUP"             { opts.set_yybackup         (lex_conf_string ()); return CONF; }
	"define:YYBACKUPCTX"          { opts.set_yybackupctx      (lex_conf_string ()); return CONF; }
	"define:YYCONDTYPE"           { opts.set_yycondtype       (lex_conf_string ()); return CONF; }
	"define:YYCTXMARKER"          { opts.set_yyctxmarker      (lex_conf_string ()); return CONF; }
	"define:YYCTYPE"              { opts.set_yyctype          (lex_conf_string ()); return CONF; }
	"define:YYCURSOR"             { opts.set_yycursor         (lex_conf_string ()); return CONF; }
	"define:YYDEBUG"              { opts.set_yydebug          (lex_conf_string ()); return CONF; }
	"define:YYFILL"               { opts.set_fill             (lex_conf_string ()); return CONF; }
	"define:YYFILL:naked"         { opts.set_fill_naked       (lex_conf_number () != 0); return CONF; }
	"define:YYFILL@len"           { opts.set_fill_arg         (lex_conf_string ()); return CONF; }
	"define:YYGETCONDITION"       { opts.set_cond_get         (lex_conf_string ()); return CONF; }
	"define:YYGETCONDITION:naked" { opts.set_cond_get_naked   (lex_conf_number () != 0); return CONF; }
	"define:YYGETSTATE"           { opts.set_state_get        (lex_conf_string ()); return CONF; }
	"define:YYGETSTATE:naked"     { opts.set_state_get_naked  (lex_conf_number () != 0); return CONF; }
	"define:YYLESSTHAN"           { opts.set_yylessthan       (lex_conf_string ()); return CONF; }
	"define:YYLIMIT"              { opts.set_yylimit          (lex_conf_string ()); return CONF; }
	"define:YYMARKER"             { opts.set_yymarker         (lex_conf_string ()); return CONF; }
	"define:YYPEEK"               { opts.set_yypeek           (lex_conf_string ()); return CONF; }
	"define:YYRESTORE"            { opts.set_yyrestore        (lex_conf_string ()); return CONF; }
	"define:YYRESTORECTX"         { opts.set_yyrestorectx     (lex_conf_string ()); return CONF; }
	"define:YYSETCONDITION"       { opts.set_cond_set         (lex_conf_string ()); return CONF; }
	"define:YYSETCONDITION@cond"  { opts.set_cond_set_arg     (lex_conf_string ()); return CONF; }
	"define:YYSETCONDITION:naked" { opts.set_cond_set_naked   (lex_conf_number () != 0); return CONF; }
	"define:YYSETSTATE"           { opts.set_state_set        (lex_conf_string ()); return CONF; }
	"define:YYSETSTATE:naked"     { opts.set_state_set_naked  (lex_conf_number () != 0); return CONF; }
	"define:YYSETSTATE@state"     { opts.set_state_set_arg    (lex_conf_string ()); return CONF; }
	"define:YYSKIP"               { opts.set_yyskip           (lex_conf_string ()); return CONF; }
	"flags:" [ewxu8]
	{
		Enc::type_t enc = Enc::ASCII;
		switch (YYCURSOR[-1])
		{
			case 'e': enc = Enc::EBCDIC; break;
			case 'w': enc = Enc::UCS2;   break;
			case 'x': enc = Enc::UTF16;  break;
			case 'u': enc = Enc::UTF32;  break;
			case '8': enc = Enc::UTF8;   break;
		}
		const int32_t n = lex_conf_number ();
		if (n == 0)
		{
			opts.unset_encoding (enc);
		}
		else if (!opts.set_encoding (enc))
		{
			fatalf ("Cannot set %s encoding: please reset %s encoding first"
				, Enc::name (enc)
				, Enc::name (opts->encoding.type ()));
		}
		return CONF;
	}
	"indent:string"               { opts.set_indString        (lex_conf_string ()); return CONF; }
	"indent:top"
	{
		const int32_t n = lex_conf_number ();
		if (n < 0)
		{
			fatal ("configuration 'indent:top' must be nonnegative");
		}
		opts.set_topIndent (static_cast<uint32_t> (n));
		return CONF;
	}
	"label:yyFillLabel"           { opts.set_yyfilllabel      (lex_conf_string ()); return CONF; }
	"label:yyNext"                { opts.set_yynext           (lex_conf_string ()); return CONF; }
	"labelprefix"                 { opts.set_labelPrefix      (lex_conf_string ()); return CONF; }
	"state:abort"                 { opts.set_bUseStateAbort   (lex_conf_number () != 0); return CONF; }
	"state:nextlabel"             { opts.set_bUseStateNext    (lex_conf_number () != 0); return CONF; }
	"variable:yyaccept"           { opts.set_yyaccept         (lex_conf_string ()); return CONF; }
	"variable:yybm"               { opts.set_yybm             (lex_conf_string ()); return CONF; }
	"variable:yych"               { opts.set_yych             (lex_conf_string ()); return CONF; }
	"variable:yyctable"           { opts.set_yyctable         (lex_conf_string ()); return CONF; }
	"variable:yystable"           { lex_conf_string (); return CONF; } // deprecated
	"variable:yytarget"           { opts.set_yytarget         (lex_conf_string ()); return CONF; }
	"yybm:hex"                    { opts.set_yybmHexTable     (lex_conf_number () != 0); return CONF; }
	"yych:conversion"             { opts.set_yychConversion   (lex_conf_number () != 0); return CONF; }
	"yych:emit"                   { opts.set_bEmitYYCh        (lex_conf_number () != 0); return CONF; }
	"yyfill:check"                { opts.set_fill_check       (lex_conf_number () != 0); return CONF; }
	"yyfill:enable"               { opts.set_fill_use         (lex_conf_number () != 0); return CONF; }
	"yyfill:parameter"            { opts.set_fill_arg_use     (lex_conf_number () != 0); return CONF; }

	// try to lex number first, otherwize it would be lexed as a naked string
	"startlabel" / conf_assign number { out.set_force_start_label (lex_conf_number () != 0); return CONF; }
	"startlabel"                      { out.set_user_start_label (lex_conf_string ()); return CONF; }
*/
}

void Scanner::lex_conf_assign ()
{
/*!re2c
	*           { fatal ("missing '=' in configuration"); }
	conf_assign { return; }
*/
}

void Scanner::lex_conf_semicolon ()
{
/*!re2c
	*          { fatal ("missing ending ';' in configuration"); }
	space* ";" { return; }
*/
}

int32_t Scanner::lex_conf_number ()
{
	lex_conf_assign ();
	tok = cur;
/*!re2c
	number
	{
		int32_t n = 0;
		if (!s_to_i32_unsafe (tok, cur, n))
		{
			fatal ("configuration value overflow");
		}
		lex_conf_semicolon ();
		return n;
	}
*/
}

std::string Scanner::lex_conf_string ()
{
	lex_conf_assign ();
	std::string s;
	tok = cur;
/*!re2c
	['"]
	{
		std::vector<uint32_t> cpoints;
		lex_cpoints (tok[0], cpoints);
		s = cpoint_conf (cpoints);
		goto end;
	}
	naked
	{
		s = std::string (tok, tok_len ());
		goto end;
	}
*/
end:
	lex_conf_semicolon ();
	return s;
}

std::string Scanner::cpoint_conf (const std::vector<uint32_t> & cs) const
{
	const size_t n = cs.size ();
	std::string s;
	for (size_t i = 0; i < n; ++i)
	{
		const uint32_t c = cs[i];
		if (c > 0xFF)
		{
			fatalf ("multibyte character in configuration string: 0x%X", c);
		}
		else
		{
			s += static_cast<char> (c);
		}
	}
	return s;
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
