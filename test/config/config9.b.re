#include <cstring>
#include <iostream>

struct Scanner
{
	Scanner(char *txt)
		: cur(txt), lim(txt + strlen(txt))
	{
	}
	
	char    *cur;
	char    *lim;
	char	*ptr;
	char	*ctx;
	char    *tok;
};

enum What
{
	UNEXPECTED,
	KEYWORD,
	NUMBER,
	EOI
};

char * tokens[] = { "UNEXPECTED", "KEYWORD", "NUMBER", "EOI" };

void fill(int)
{
}

int scan(Scanner &s)
{
	char *cursor = s.cur;

	if(cursor == s.lim)
		return EOI;
	
std:
	s.tok = cursor;

/*!re2c

re2c:define:YYCTYPE		= "unsigned char";
re2c:define:YYCURSOR	= s.cur;
re2c:define:YYLIMIT		= s.lim;
re2c:define:YYMARKER	= s.ptr;
re2c:define:YYCTXMARKER	= s.ctx;
re2c:define:YYFILL      = fill;

re2c:variable:yych      = curr;
re2c:labelprefix        = xx;

re2c:yych:conversion    = 1;

("a"|"b")/[1]    { return KEYWORD; }
("a"|"b")/[0-9]+ { return KEYWORD; }
[0-9]+           { return NUMBER;  }

[ \t\n]
	{
		if(s.cur == s.lim)
			return EOI;
		cursor = s.cur;
		goto std;
	}
.
	{
		return UNEXPECTED;
	}
*/
}

int main(int,char**)
{
	Scanner s("a77 a1 b8 b1");
	
	int t, n = 0;
	while ((t = scan(s)) != EOI)
	{
		std::cout << (++n) << ": " << tokens[t] << " = \""; std::cout.write(s.tok, s.cur-s.tok); std::cout << "\"" << std::endl;
	}
}
