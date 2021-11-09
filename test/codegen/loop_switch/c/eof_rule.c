/* Generated by re2c */
// re2c $INPUT -o $OUTPUT --loop-switch -i
#include <assert.h>

// expect a null-terminated string
static int lex(const char *str, unsigned int len)
{
    const char *YYCURSOR = str, *YYLIMIT = str + len, *YYMARKER;
    int count = 0;

loop:
    
{
	char yych;
	unsigned int yystate = 1;
	for (;;) {
		switch (yystate) {
		case 1:
			yych = *YYCURSOR;
			switch (yych) {
			case ' ':
				++YYCURSOR;
				yystate = 4;
				continue;
			case '\'':
				++YYCURSOR;
				yystate = 7;
				continue;
			default:
				if (YYLIMIT <= YYCURSOR) {
					yystate = 13;
					continue;
				}
				++YYCURSOR;
				yystate = 2;
				continue;
			}
		case 2:
			yystate = 3;
			continue;
		case 3:
			{ return -1; }
		case 4:
			yych = *YYCURSOR;
			yystate = 5;
			continue;
		case 5:
			switch (yych) {
			case ' ':
				++YYCURSOR;
				yystate = 4;
				continue;
			default:
				yystate = 6;
				continue;
			}
		case 6:
			{ goto loop; }
		case 7:
			YYMARKER = YYCURSOR;
			yych = *YYCURSOR;
			if (yych >= 0x01) {
				yystate = 9;
				continue;
			}
			if (YYLIMIT <= YYCURSOR) {
				yystate = 3;
				continue;
			}
			++YYCURSOR;
			yystate = 8;
			continue;
		case 8:
			yych = *YYCURSOR;
			yystate = 9;
			continue;
		case 9:
			switch (yych) {
			case '\'':
				++YYCURSOR;
				yystate = 10;
				continue;
			case '\\':
				++YYCURSOR;
				yystate = 12;
				continue;
			default:
				if (YYLIMIT <= YYCURSOR) {
					yystate = 14;
					continue;
				}
				++YYCURSOR;
				yystate = 8;
				continue;
			}
		case 10:
			yystate = 11;
			continue;
		case 11:
			{ ++count; goto loop; }
		case 12:
			yych = *YYCURSOR;
			if (yych <= 0x00) {
				if (YYLIMIT <= YYCURSOR) {
					yystate = 14;
					continue;
				}
				++YYCURSOR;
				yystate = 8;
				continue;
			}
			++YYCURSOR;
			yystate = 8;
			continue;
		case 13:
			{ return count; }
		case 14:
			YYCURSOR = YYMARKER;
			yystate = 3;
			continue;
		}
	}
}

}

#define TEST(s, r) assert(lex(s, sizeof(s) - 1) == r)
int main()
{
    TEST("", 0);
    TEST("'qu\0tes' 'are' 'fine: \\'' ", 3);
    TEST("'unterminated\\'", -1);
    return 0;
}
