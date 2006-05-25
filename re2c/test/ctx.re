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

#define	YYCTYPE		char
#define	YYCURSOR	s.cur
#define	YYLIMIT		s.lim
#define	YYMARKER	s.ptr
#define	YYCTXMARKER	s.ctx
#define	YYFILL(n)	

enum What
{
	UNEXPECTED,
	KEYWORD,
	NUMBER,
	EOI
};

char * tokens[] = { "UNEXPECTED", "KEYWORD", "NUMBER", "EOI" };


int scan(Scanner &s)
{
	YYCTYPE *cursor = s.cur;

	if(cursor == s.lim)
		return EOI;
	
std:
	s.tok = cursor;

/*!re2c

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

/*!max:re2c */

int main(int,char**)
{
	Scanner s("a77 a1 b8 b1");
	
	int t, n = 0;
	while ((t = scan(s)) != EOI)
	{
		std::cout << (++n) << ": " << tokens[t] << " = \""; std::cout.write(s.tok, s.cur-s.tok); std::cout << "\"" << std::endl;
	}
}
