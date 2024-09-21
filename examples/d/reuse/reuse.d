/* Generated by re2d */
#line 1 "d/reuse/reuse.re"
// re2d $INPUT -o $OUTPUT --input-encoding utf8
module main;

import std.stdint;

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
#line 14 "d/reuse/reuse.re"


private int lex_utf8(const(uint8_t)* s) {
    const(uint8_t)* yycursor = s, yymarker;
    
#line 18 "d/reuse/reuse.d"
{
	uint8_t yych;
	yych = *yycursor;
	switch (yych) {
		case 0xE2: goto yy3;
		default: goto yy1;
	}
yy1:
	++yycursor;
yy2:
#line 13 "d/reuse/reuse.re"
	{ return 1; }
#line 31 "d/reuse/reuse.d"
yy3:
	yych = *(yymarker = ++yycursor);
	switch (yych) {
		case 0x88: goto yy4;
		default: goto yy2;
	}
yy4:
	yych = *++yycursor;
	switch (yych) {
		case 0x80: goto yy6;
		default: goto yy5;
	}
yy5:
	yycursor = yymarker;
	goto yy2;
yy6:
	yych = *++yycursor;
	switch (yych) {
		case 'x': goto yy7;
		default: goto yy5;
	}
yy7:
	yych = *++yycursor;
	switch (yych) {
		case ' ': goto yy8;
		default: goto yy5;
	}
yy8:
	yych = *++yycursor;
	switch (yych) {
		case 0xE2: goto yy9;
		default: goto yy5;
	}
yy9:
	yych = *++yycursor;
	switch (yych) {
		case 0x88: goto yy10;
		default: goto yy5;
	}
yy10:
	yych = *++yycursor;
	switch (yych) {
		case 0x83: goto yy11;
		default: goto yy5;
	}
yy11:
	yych = *++yycursor;
	switch (yych) {
		case 'y': goto yy12;
		default: goto yy5;
	}
yy12:
	++yycursor;
#line 12 "d/reuse/reuse.re"
	{ return 0; }
#line 87 "d/reuse/reuse.d"
}
#line 21 "d/reuse/reuse.re"

}

private int lex_utf32(const(uint32_t)* s) {
    const(uint32_t)* yycursor = s, yymarker;
    
#line 96 "d/reuse/reuse.d"
{
	uint32_t yych;
	yych = *yycursor;
	if (yych == 0x00002200) goto yy15;
	++yycursor;
yy14:
#line 13 "d/reuse/reuse.re"
	{ return 1; }
#line 105 "d/reuse/reuse.d"
yy15:
	yych = *(yymarker = ++yycursor);
	if (yych != 'x') goto yy14;
	yych = *++yycursor;
	if (yych == ' ') goto yy17;
yy16:
	yycursor = yymarker;
	goto yy14;
yy17:
	yych = *++yycursor;
	if (yych != 0x00002203) goto yy16;
	yych = *++yycursor;
	if (yych != 'y') goto yy16;
	++yycursor;
#line 12 "d/reuse/reuse.re"
	{ return 0; }
#line 122 "d/reuse/reuse.d"
}
#line 29 "d/reuse/reuse.re"

}

void main() {
    immutable uint8_t[] s8 = // UTF-8
        [ 0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79 ];

    immutable uint32_t[] s32 = // UTF32
        [ 0x00002200, 0x00000078, 0x00000020, 0x00002203, 0x00000079 ];

    assert(lex_utf8(cast(const(uint8_t)*)s8) == 0);
    assert(lex_utf32(cast(const(uint32_t)*)s32) == 0);
}