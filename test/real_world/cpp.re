// re2c $INPUT -o $OUTPUT -i
/*
 * This lexer was written for unifdef, which is a kind of C/C++
 * preprocessor. It supports some recent C and C++ features.
 *
 * It lexes comments and whitespace as separate tokens, partly for the
 * preprocessor's whitespace-sensitivity, and partly because unifdef
 * aims to preserve them. Backslash-newline escapes are allowed anywhere.
 *
 * It does not lex tokens that the preprocessor does not need to care
 * about, such as keywords for statements and types, or operators for
 * assignment and member access. Preprocessor directives are treated
 * as keywords.
 *
 * Floating point numbers are treated as pp-numbers. Integer length
 * suffixes do not result in different tokens. Supported character and
 * integer constants are lexed relatively precisely, whereas
 * unsupported ones are lexed enough to be passed through unevaluated.
 *
 * Written by Tony Finch <dot@dotat.at>
 * You may do anything with this. It has no warranty.
 * <https://creativecommons.org/publicdomain/zero/1.0/>
 * SPDX-License-Identifier: CC0-1.0
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

typedef enum Token {
	ERROR, COMMENT, CTRL, HASH, HEADER, IDENT, NEWLINE, NOMORE,
	OTHER, PLACEMARKER, PPNUM, REST, SPACE, STRING, CHARACTER,
	CH_byte_u, CH_byte_x, CH_esc_s, CH_esc_u, CH_hex_s, CH_hex_u,
	CH_hex_x, CH_oct_s, CH_oct_u, CH_oct_x, CH_utf2_s, CH_utf2_u,
	CH_utf3_s, CH_utf3_u, CH_utf4_s, CH_utf4_u, INTb2s, INTb2u,
	INT_8s, INT_8u, INT_10s, INT_10u, INTx16s, INTx16u, K_va_args,
	K_va_opt, K_defined, K_false, K_true, K_compl, K_not, K_not_eq,
	K_bitand, K_xor, K_bitor, K_and, K_or, K_and_eq, K_or_eq,
	K_xor_eq, K_define, K_defval, K_elif, K_else, K_endif, K_if,
	K_ifdef, K_ifndef, K_import, K_include, K_include_next,
	K_undef, CLOSE, OPEN, DEC, INC, COMPL, NOT, DIV, MOD, MUL, ADD,
	SUB, SHL, SHR, GE, GT, LE, LT, EQ, NOT_EQ, BITAND, XOR, BITOR,
	AND, OR, QUERY, COLON, ASSIGN, COMMA, PASTE,
} Token;

typedef struct Position {
	const byte *start;
	const byte *spelling;
	const byte *cursor;
	const byte *limit;
	Token tok;
	unsigned line, next;
} Position;

static Token lex(Position *here);

static Position
lex_start(const byte *ptr, size_t len) {
	Position here = { .start = ptr,
			  .spelling = ptr,
			  .cursor = ptr,
			  .limit = ptr + len,
			  .tok = ERROR,
			  .line = 0,
			  .next = 1 };
	return(here);
}

static const byte *
backslash_newline(const byte *p) {
	for(;;) {
		if(p[0] == '\\' && p[1] == '\r' && p[2] == '\n') {
			p += 3;
			continue;
		}
		if(p[0] == '\\' && p[1] == '\r') {
			p += 2;
			continue;
		}
		if(p[0] == '\\' && p[1] == '\n') {
			p += 2;
			continue;
		}
		return(p);
	}
}

static unsigned
count_lines(const byte *p, const byte *end) {
	unsigned n = 0;
	while(p < end) {
		if(p[0] == '\r' && p[1] == '\n') {
			n += 1, p += 2;
			continue;
		}
		if(p[0] == '\r' || p[0] == '\n') {
			n += 1, p += 1;
			continue;
		}
		p += 1;
		continue;
	}
	return(n);
}

static Token
lex_return(Position *here, Token tok, const byte *cursor) {
	here->tok = tok;
	here->spelling = here->cursor;
	here->cursor = cursor;
	here->line = here->next;
	here->next += count_lines(here->spelling, here->cursor);
	return(tok);
}

static Token
raw_string(Position *here, const byte *cursor) {
	const byte *start = here->cursor;
	const byte *limit = here->limit;
	assert(start < cursor && cursor <= limit);
	size_t toklen = (size_t)(cursor - start);
	const byte *qq = memchr(start, '"', toklen);
	const byte *lp = memchr(start, '(', toklen);
	assert(qq != NULL && lp != NULL && lp > qq);
	const byte *ds = qq + 1; // delimiter string
	size_t dlen = (size_t)(lp - ds);
	// in case of backslash-newline shenanigans
	if(memchr(ds, '\\', dlen)) goto error;
	// enough space for right delimiter )dlen"
	const byte *dlimit = limit - dlen - 2;
	const byte *rp = lp;
	for(;;) {
		if(rp > dlimit) goto error;
		size_t rlen = (size_t)(dlimit - rp);
		rp = memchr(rp, ')', rlen);
		if(rp == NULL) goto error; else rp++;
		if(memcmp(rp, ds, dlen) == 0 && rp[dlen] == '"')
			break;
	}
	return(lex_return(here, STRING, rp + dlen + 1));
error:	// just return the encoding prefix as an identifier
	return(lex_return(here, IDENT, qq));
}

/*!re2c	re2c:flags:input = custom;
	re2c:yyfill:enable = 0;
	re2c:eof = 0;
*/

#define YYCTYPE		byte
#define YYPEEK()	*(YYCURSOR = backslash_newline(YYCURSOR))
#define YYSKIP()	++YYCURSOR
#define YYLESSTHAN(n)	(YYLIMIT - YYCURSOR < n)
#define YYBACKUP()	YYMARKER = YYCURSOR
#define YYRESTORE()	YYCURSOR = YYMARKER

#define rettok(tok)	return(lex_return(here, tok, YYCURSOR))

static Token
lex(Position *here) {
	const byte *YYCURSOR = here->cursor;
	const byte *YYLIMIT  = here->limit;
	const byte *YYMARKER = NULL;
%{

$					{ rettok(NOMORE);		}

'\r\n' | [\r\n]				{ rettok(NEWLINE);		}

[ \t\v\f]+				{ rettok(SPACE);		}

*					{ rettok(OTHER);		}
[\x00-\x1F\x7F]				{ rettok(CTRL);			}

"//"[^\r\n]*				{ rettok(COMMENT);		}
"/*"([^*]*[*]+[^*/])*[^*]*[*]+[/]	{ rettok(COMMENT);		}

'#'					{ rettok(HASH);			}
"%:"					{ rettok(HASH);			}
'##'					{ rettok(PASTE);		}
"%:%:"					{ rettok(PASTE);		}
'...'					{ rettok(REST);			}

'('					{ rettok(OPEN);			} // -32
')'					{ rettok(CLOSE);		} // -32
'--'					{ rettok(DEC);			} // -30
'++'					{ rettok(INC);			} // -30
'~'					{ rettok(COMPL);		} // -28
'!'					{ rettok(NOT);			} // -28
'/'					{ rettok(DIV);			} // +26
'%'					{ rettok(MOD);			} // +26
'*'					{ rettok(MUL);			} // +26
'+'					{ rettok(ADD);			} // +24
'-'					{ rettok(SUB);			} // +24
'<<'					{ rettok(SHL);			} //  22
'>>'					{ rettok(SHR);			} //  22
'>='					{ rettok(GE);			} // +20
'>'					{ rettok(GT);			} // +20
'<='					{ rettok(LE);			} // +20
'<'					{ rettok(LT);			} // +20
'=='					{ rettok(EQ);			} // +18
'!='					{ rettok(NOT_EQ);		} // +18
'&'					{ rettok(BITAND);		} // +16
'^'					{ rettok(XOR);			} // +14
'|'					{ rettok(BITOR);		} // +12
'&&'					{ rettok(AND);			} //  10
'||'					{ rettok(OR);			} //   8
'?'					{ rettok(QUERY);		} //   6
':'					{ rettok(COLON);		} //  -5
'='					{ rettok(ASSIGN);		} //  -4
','					{ rettok(COMMA);		} //  -2

"__VA_ARGS__"				{ rettok(K_va_args);		}
"__VA_OPT__"				{ rettok(K_va_opt);		}
"defined"				{ rettok(K_defined);		}
"false"					{ rettok(K_false);		}
"true"					{ rettok(K_true);		}
"compl"					{ rettok(K_compl);		}
"not"					{ rettok(K_not);		}
"not_eq"				{ rettok(K_not_eq);		}
"bitand"				{ rettok(K_bitand);		}
"xor"					{ rettok(K_xor);		}
"bitor"					{ rettok(K_bitor);		}
"and"					{ rettok(K_and);		}
"or"					{ rettok(K_or);			}
"and_eq"				{ rettok(K_and_eq);		}
"or_eq"					{ rettok(K_or_eq);		}
"xor_eq"				{ rettok(K_xor_eq);		}
"define"				{ rettok(K_define);		}
"defval"				{ rettok(K_defval);		}
"elif"					{ rettok(K_elif);		}
"else"					{ rettok(K_else);		}
"endif"					{ rettok(K_endif);		}
"if"					{ rettok(K_if);			}
"ifdef"					{ rettok(K_ifdef);		}
"ifndef"				{ rettok(K_ifndef);		}
"import"				{ rettok(K_import);		}
"include"				{ rettok(K_include);		}
"include_next"				{ rettok(K_include_next);	}
"undef"					{ rettok(K_undef);		}

hex	= [0-9a-fA-F]							;

ucn4	= "\\u" hex{4}							;
ucn8	= "\\U" hex{8}							;
ucn	= ucn4 | ucn8							;

nodigit	= [a-zA-Z_$\x80-\xFF]						;
id	=  nodigit | ucn | [0-9]					;
ident	= (nodigit | ucn) id*						;

ident					{ rettok(IDENT);		}

length	= ("l"|"ll"|"L"|"LL")						;
unsign	= length[uU]|[uU]|[uU]length					;

[0][bB][01]* length?			{ rettok(INTb2s);		}
[0][bB][01]* unsign			{ rettok(INTb2u);		}
[0][0-7]* length?			{ rettok(INT_8s);		}
[0][0-7]* unsign			{ rettok(INT_8u);		}
[1-9][0-9]* length?			{ rettok(INT_10s);		}
[1-9][0-9]* unsign			{ rettok(INT_10u);		}
[0][xX]hex* length?			{ rettok(INTx16s);		}
[0][xX]hex* unsign			{ rettok(INTx16u);		}

[.]?[0-9]( id | [eEpP][+-] | [.'] )*	{ rettok(PPNUM);		} // '

esc	= [\\]('"'|"'"|[\\?abefnrtv])					;

oct7	= [\\][0-1]?[0-7]?[0-7]						;
oct8	= [\\][0-3]?[0-7]?[0-7]						;
oct9	= [\\][0-7]?[0-7]?[0-7]						;

hex2	= [\\][x]hex{1,2}						;
hex4	= [\\][x]hex{1,4}						;
hex8	= [\\][x]hex{1,8}						;
hexX	= [\\][x]hex{1,}						;

ansi_x	= [\x20-\x7E\x80-\xFF]						;
ascii	= [\x20-\x7E]							;
utfcont	= [\x80-\xBF]							;
utf2	= [\xC0-\xDF] utfcont						;
utf3	= [\xE0-\xEF] utfcont utfcont					;
utf4	= [\xF0-\xF7] utfcont utfcont utfcont				;

"L"?['] esc  [']			{ rettok(CH_esc_s);		}
[uU]['] esc  [']			{ rettok(CH_esc_u);		}
"u8"['] esc  [']			{ rettok(CH_esc_u);		}

    ['] oct8 [']			{ rettok(CH_oct_x);		}
"L" ['] oct9 [']			{ rettok(CH_oct_s);		}
[uU]['] oct9 [']			{ rettok(CH_oct_u);		}
"u8"['] oct7 [']			{ rettok(CH_oct_u);		}

    ['] hex2 [']			{ rettok(CH_hex_x);		}
    ['] ucn  [']			{ rettok(CH_hex_s);		}
"L" ['] hex8 [']			{ rettok(CH_hex_s);		}
"L" ['] ucn  [']			{ rettok(CH_hex_s);		}
"u" ['] hex4 [']			{ rettok(CH_hex_u);		}
"u" ['] ucn4 [']			{ rettok(CH_hex_u);		}
"U" ['] hex8 [']			{ rettok(CH_hex_u);		}
"U" ['] ucn  [']			{ rettok(CH_hex_u);		}
"u'\\U"  [0]{4} hex{4} "'"		{ rettok(CH_hex_u);		}
"u8'\\x"        [0-7]? hex "'"		{ rettok(CH_hex_u);		}
"u8'\\u" [0]{2} [0-7]  hex "'"		{ rettok(CH_hex_u);		}
"u8'\\U" [0]{6} [0-7]  hex "'"		{ rettok(CH_hex_u);		}

"L"?['] ansi_x [']			{ rettok(CH_byte_x);		}
[uU]['] ansi_x [']			{ rettok(CH_byte_u);		}
"u8"['] ascii [']			{ rettok(CH_byte_u);		}
"L"?['] utf2 [']			{ rettok(CH_utf2_s);		}
[uU]['] utf2 [']			{ rettok(CH_utf2_u);		}
"L"?['] utf3 [']			{ rettok(CH_utf3_s);		}
[uU]['] utf3 [']			{ rettok(CH_utf3_u);		}
"L"?['] utf4 [']			{ rettok(CH_utf4_s);		}
[U] ['] utf4 [']			{ rettok(CH_utf4_u);		}

enc	= ("u8" | [uUL])?						;
seq	= esc | oct9 | hexX | ucn					;

enc '"' (seq | [^"\\\r\n])* ["]		{ rettok(STRING);		}
enc "'" (seq | [^'\\\r\n])+ [']		{ rettok(CHARACTER);		}

d_char	= [a-zA-Z0-9!#%&*+,./:;<=>?^_{|}~-] |'['|']'|'"'|"'"		;

enc [R]'"' d_char{0,16} '('	{ return(raw_string(here, YYCURSOR));	}

%}
}

int main(void) {
	byte *buffer = NULL;
	size_t length = 0;
	size_t bufsiz = 1024;
	while(!feof(stdin)) {
		bufsiz *= 2;
		buffer = realloc(buffer, bufsiz);
		assert(buffer != NULL);
		length += fread(buffer + length, 1, bufsiz - length - 1, stdin);
		assert(!ferror(stdin));
	}
	buffer[length] = '\0'; // sentinel
	Position there = lex_start(buffer, length);
	Position *here = &there;
	Token tok;
	while((tok = lex(here)) != NOMORE) {
		printf("%3d %.*s\n", tok,
		       (int)(here->cursor - here->spelling), here->spelling);
	}
	return(0);
}
