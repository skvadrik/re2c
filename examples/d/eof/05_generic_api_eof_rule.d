/* Generated by re2c 3.0 on Sun Jan  8 12:47:48 2023 */
#line 1 "05_generic_api_eof_rule.re"
// re2d $INPUT -o $OUTPUT
module generic_api_eof_rule05;

import core.stdc.stdlib;
import core.stdc.string;

int lex(in string str, ulong len) {
    // For the sake of example create a string without terminating null.
    char *buf = cast(char*) malloc(len);
    memcpy(buf, cast(const(void*)) str, len);

    const(char) * cur = buf, lim = buf + len, mar;
    int count = 0;

    for (;;) {
    
#line 20 "05_generic_api_eof_rule.d"
{
	char yych;
	yych = cur < lim ? *cur : 0;
	if (yych <= ' ') {
		if (yych <= 0x0000) {
			if (cur >= lim) goto yy9;
			goto yy1;
		}
		if (yych >= ' ') goto yy3;
	} else {
		if (yych == '\'') goto yy5;
	}
yy1:
	++cur;
yy2:
#line 30 "05_generic_api_eof_rule.re"
	{ count = -1; break; }
#line 38 "05_generic_api_eof_rule.d"
yy3:
	++cur;
	yych = cur < lim ? *cur : 0;
	if (yych <= 0x0000) goto yy4;
	if (yych == ' ') goto yy3;
yy4:
#line 33 "05_generic_api_eof_rule.re"
	{ continue; }
#line 47 "05_generic_api_eof_rule.d"
yy5:
	++cur;
	mar = cur;
	yych = cur < lim ? *cur : 0;
	if (yych >= 0x0001) goto yy7;
	if (cur >= lim) goto yy2;
yy6:
	++cur;
	yych = cur < lim ? *cur : 0;
yy7:
	if (yych <= '\'') {
		if (yych <= 0x0000) {
			if (cur >= lim) goto yy10;
			goto yy6;
		}
		if (yych <= '&') goto yy6;
	} else {
		if (yych == '\\') goto yy8;
		goto yy6;
	}
	++cur;
#line 32 "05_generic_api_eof_rule.re"
	{ ++count; continue; }
#line 71 "05_generic_api_eof_rule.d"
yy8:
	++cur;
	yych = cur < lim ? *cur : 0;
	if (yych <= 0x0000) {
		if (cur >= lim) goto yy10;
		goto yy6;
	}
	goto yy6;
yy9:
#line 31 "05_generic_api_eof_rule.re"
	{ break;{} }
#line 83 "05_generic_api_eof_rule.d"
yy10:
	cur = mar;
	goto yy2;
}
#line 34 "05_generic_api_eof_rule.re"

    }

    free(buf);
    return count;
}

void TEST(immutable char[] s, int r){
    assert(lex(s,s.length)==r);
}

unittest{
    TEST("", 0);
    TEST("'qu\0tes' 'are' 'fine: \\'' ", 3);
    TEST("'unterminated\\'", -1);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}