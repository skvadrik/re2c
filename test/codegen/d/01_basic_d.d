/* Generated by re2d */
#line 1 "codegen/d/01_basic_d.re"
// re2d $INPUT -o $OUTPUT -d
module main;

import core.stdc.stdio;

bool lex(const char *s) {
    size_t cursor;
    
#line 12 "codegen/d/01_basic_d.d"
{
	char yych;
	yych = s[cursor];
	debug{printf("lex1: char '%c' at state %u\n", yych, 0);}
	switch (yych) {
		case '1': .. case '9': goto yy2;
		default: goto yy1;
	}
yy1:
	debug{printf("lex1: char '%c' at state %u\n", yych, 1);}
	++cursor;
#line 19 "codegen/d/01_basic_d.re"
	{ return false; }
#line 26 "codegen/d/01_basic_d.d"
yy2:
	debug{printf("lex1: char '%c' at state %u\n", yych, 2);}
	++cursor;
	yych = s[cursor];
	switch (yych) {
		case '0': .. case '9': goto yy2;
		default: goto yy3;
	}
yy3:
	debug{printf("lex1: char '%c' at state %u\n", yych, 3);}
#line 18 "codegen/d/01_basic_d.re"
	{ return true; }
#line 39 "codegen/d/01_basic_d.d"
}
#line 20 "codegen/d/01_basic_d.re"

}

void main() {
    assert(lex("1234"));
}