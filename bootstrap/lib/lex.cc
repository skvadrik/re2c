/* Generated by re2c 3.0 */
#line 1 "../lib/lex.re"
#include <stdint.h>
#include <stdio.h>

#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/parse/ast.h"
#include "src/util/range.h"
#include "src/util/string_utils.h"
#include "parse.h"
#include "lib/lex.h"



namespace re2c {

static int32_t lex_cls_chr(const uint8_t*&, uint32_t&);

#line 27 "../lib/lex.re"


int lex(YYSTYPE* yylval, const uint8_t*& cur, Ast& ast) {
    
#line 26 "lib/lex.cc"
const uint8_t* yyt1;const uint8_t* yyt2;
#line 30 "../lib/lex.re"

    const uint8_t* mar, *x, *y;
    bool neg = false;
    uint32_t l, u;


#line 35 "lib/lex.cc"
{
	uint8_t yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *cur;
	if (yych <= '>') {
		if (yych <= '\'') {
			if (yych <= 0x00) goto yy1;
			if (yych == '$') goto yy4;
			goto yy2;
		} else {
			if (yych <= '+') goto yy5;
			if (yych == '.') goto yy6;
			goto yy2;
		}
	} else {
		if (yych <= ']') {
			if (yych <= '?') goto yy5;
			if (yych == '[') goto yy7;
			goto yy2;
		} else {
			if (yych <= 'z') {
				if (yych <= '^') goto yy4;
				goto yy2;
			} else {
				if (yych <= '{') goto yy8;
				if (yych <= '|') goto yy5;
				goto yy2;
			}
		}
	}
yy1:
	++cur;
#line 38 "../lib/lex.re"
	{ return 0; }
#line 103 "lib/lex.cc"
yy2:
	++cur;
yy3:
#line 73 "../lib/lex.re"
	{
        ast.temp_chars.push_back({cur[-1], NOWHERE});
        yylval->regexp = ast.str(NOWHERE, false);
        return TOKEN_REGEXP;
    }
#line 113 "lib/lex.cc"
yy4:
	++cur;
#line 42 "../lib/lex.re"
	{
        error("anchors are not supported");
        return TOKEN_ERROR;
    }
#line 121 "lib/lex.cc"
yy5:
	++cur;
#line 40 "../lib/lex.re"
	{ return cur[-1]; }
#line 126 "lib/lex.cc"
yy6:
	++cur;
#line 68 "../lib/lex.re"
	{
        yylval->regexp = ast.dot(NOWHERE);
        return TOKEN_REGEXP;
    }
#line 134 "lib/lex.cc"
yy7:
	yych = *++cur;
	if (yych == '^') goto yy9;
#line 48 "../lib/lex.re"
	{ goto cls; }
#line 140 "lib/lex.cc"
yy8:
	yych = *(mar = ++cur);
	if (yych <= '/') goto yy3;
	if (yych <= '9') {
		yyt1 = cur;
		goto yy10;
	}
	goto yy3;
yy9:
	++cur;
#line 47 "../lib/lex.re"
	{ neg = true; goto cls; }
#line 153 "lib/lex.cc"
yy10:
	yych = *++cur;
	if (yybm[0+yych] & 128) {
		goto yy10;
	}
	if (yych == ',') goto yy12;
	if (yych == '}') goto yy13;
yy11:
	cur = mar;
	goto yy3;
yy12:
	yych = *++cur;
	if (yych <= '/') goto yy11;
	if (yych <= '9') {
		yyt2 = cur;
		goto yy14;
	}
	if (yych == '}') goto yy15;
	goto yy11;
yy13:
	++cur;
	x = yyt1;
#line 50 "../lib/lex.re"
	{
        if (!s_to_u32_unsafe(x, cur - 1, yylval->bounds.min)) goto err_cnt;
        yylval->bounds.max = yylval->bounds.min;
        return TOKEN_COUNT;
    }
#line 182 "lib/lex.cc"
yy14:
	yych = *++cur;
	if (yych <= '/') goto yy11;
	if (yych <= '9') goto yy14;
	if (yych == '}') goto yy16;
	goto yy11;
yy15:
	++cur;
	x = yyt1;
#line 62 "../lib/lex.re"
	{
        if (!s_to_u32_unsafe(x, cur - 2, yylval->bounds.min)) goto err_cnt;
        yylval->bounds.max = Ast::MANY;
        return TOKEN_COUNT;
    }
#line 198 "lib/lex.cc"
yy16:
	++cur;
	x = yyt1;
	y = yyt2;
#line 56 "../lib/lex.re"
	{
        if (!s_to_u32_unsafe(x, y - 1, yylval->bounds.min)
            || !s_to_u32_unsafe(y, cur - 1, yylval->bounds.max)) goto err_cnt;
        return TOKEN_COUNT;
    }
#line 209 "lib/lex.cc"
}
#line 78 "../lib/lex.re"


cls:
    if (lex_cls_chr(cur, l) != 0) goto err;

#line 217 "lib/lex.cc"
{
	uint8_t yych;
	yych = *(mar = cur);
	if (yych == '-') goto yy19;
yy18:
#line 83 "../lib/lex.re"
	{ u = l; goto add; }
#line 225 "lib/lex.cc"
yy19:
	yych = *++cur;
	if (yych != ']') goto yy20;
	cur = mar;
	goto yy18;
yy20:
	++cur;
	cur -= 1;
#line 84 "../lib/lex.re"
	{ if (lex_cls_chr(cur, u) != 0) goto err; goto add; }
#line 236 "lib/lex.cc"
}
#line 85 "../lib/lex.re"

add:
    if (l > u) goto err;
    ast.temp_ranges.push_back(AstRange(l, u, NOWHERE));

#line 244 "lib/lex.cc"
{
	uint8_t yych;
	yych = *cur;
	if (yych == ']') goto yy22;
#line 90 "../lib/lex.re"
	{ goto cls; }
#line 251 "lib/lex.cc"
yy22:
	++cur;
#line 91 "../lib/lex.re"
	{
        yylval->regexp = ast.cls(NOWHERE, neg);
        return TOKEN_REGEXP;
    }
#line 259 "lib/lex.cc"
}
#line 95 "../lib/lex.re"


err:
    error("syntax error: %s\n", cur);
    return TOKEN_ERROR;

err_cnt:
    error("repetition count overflow");
    return TOKEN_ERROR;
}

int32_t lex_cls_chr(const uint8_t*& cur, uint32_t& c) {
    const uint8_t* mar, *p = cur;

#line 276 "lib/lex.cc"
{
	uint8_t yych;
	yych = *cur;
	if (yych <= 0x00) goto yy24;
	if (yych <= 'Z') goto yy25;
	if (yych <= '[') goto yy27;
	if (yych <= '\\') goto yy28;
	goto yy25;
yy24:
	++cur;
#line 109 "../lib/lex.re"
	{ return 1; }
#line 289 "lib/lex.cc"
yy25:
	++cur;
yy26:
#line 127 "../lib/lex.re"
	{ c = cur[-1]; return 0; }
#line 295 "lib/lex.cc"
yy27:
	yych = *++cur;
	if (yych <= '9') {
		if (yych == '.') goto yy30;
		goto yy26;
	} else {
		if (yych <= ':') goto yy31;
		if (yych == '=') goto yy32;
		goto yy26;
	}
yy28:
	yych = *(mar = ++cur);
	switch (yych) {
		case '\\': goto yy33;
		case ']': goto yy34;
		case 'a': goto yy35;
		case 'b': goto yy36;
		case 'f': goto yy37;
		case 'n': goto yy38;
		case 'r': goto yy39;
		case 't': goto yy40;
		case 'v': goto yy41;
		case 'x': goto yy42;
		default: goto yy29;
	}
yy29:
#line 116 "../lib/lex.re"
	{ c = '\\'_u8; return 0; }
#line 324 "lib/lex.cc"
yy30:
	++cur;
#line 110 "../lib/lex.re"
	{ error("collating characters not supported"); return 1; }
#line 329 "lib/lex.cc"
yy31:
	++cur;
#line 111 "../lib/lex.re"
	{ error("character classes not supported");    return 1; }
#line 334 "lib/lex.cc"
yy32:
	++cur;
#line 112 "../lib/lex.re"
	{ error("equivalence classes not supported");  return 1; }
#line 339 "lib/lex.cc"
yy33:
	++cur;
#line 124 "../lib/lex.re"
	{ c = '\\'_u8; return 0; }
#line 344 "lib/lex.cc"
yy34:
	++cur;
#line 125 "../lib/lex.re"
	{ c = ']'_u8;  return 0; }
#line 349 "lib/lex.cc"
yy35:
	++cur;
#line 117 "../lib/lex.re"
	{ c = '\a'_u8; return 0; }
#line 354 "lib/lex.cc"
yy36:
	++cur;
#line 118 "../lib/lex.re"
	{ c = '\b'_u8; return 0; }
#line 359 "lib/lex.cc"
yy37:
	++cur;
#line 119 "../lib/lex.re"
	{ c = '\f'_u8; return 0; }
#line 364 "lib/lex.cc"
yy38:
	++cur;
#line 120 "../lib/lex.re"
	{ c = '\n'_u8; return 0; }
#line 369 "lib/lex.cc"
yy39:
	++cur;
#line 121 "../lib/lex.re"
	{ c = '\r'_u8; return 0; }
#line 374 "lib/lex.cc"
yy40:
	++cur;
#line 122 "../lib/lex.re"
	{ c = '\t'_u8; return 0; }
#line 379 "lib/lex.cc"
yy41:
	++cur;
#line 123 "../lib/lex.re"
	{ c = '\v'_u8; return 0; }
#line 384 "lib/lex.cc"
yy42:
	yych = *++cur;
	if (yych <= '@') {
		if (yych <= '/') goto yy43;
		if (yych <= '9') goto yy44;
	} else {
		if (yych <= 'F') goto yy44;
		if (yych <= '`') goto yy43;
		if (yych <= 'f') goto yy44;
	}
yy43:
	cur = mar;
	goto yy29;
yy44:
	yych = *++cur;
	if (yych <= '@') {
		if (yych <= '/') goto yy43;
		if (yych >= ':') goto yy43;
	} else {
		if (yych <= 'F') goto yy45;
		if (yych <= '`') goto yy43;
		if (yych >= 'g') goto yy43;
	}
yy45:
	++cur;
#line 114 "../lib/lex.re"
	{ c = unesc_hex(p, cur); return 0; }
#line 412 "lib/lex.cc"
}
#line 128 "../lib/lex.re"

}

} // namespace re2c
