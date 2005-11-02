#include <string.h>
#include <stdlib.h>
#include <iostream>

struct Scanner
{
	Scanner(char *_inp)
		: inp(_inp), buf(NULL), ptr(NULL), len(0), siz(strlen(_inp)), line(0)
	{
		fill(0);
		cur = buf;
	}
	
	void fill(size_t n)
	{
		n++;
		buf = (char*)realloc(buf, len + n + 1);
		if ((len += n) > siz)
		{
			len = siz;
		}
		memcpy(buf, inp, len);
		buf[len] = '\0';
		lim = buf + len;
		eof = buf + siz - 1;
	}

	char    *inp;
	char    *cur;
	char    *buf;
	char    *ptr;
	char    *lim;
	char    *eof;
	size_t  len;
	size_t  siz;
	size_t  line;
};

enum What
{
	UNEXPECTED,
	FCON,
	EOI
};

#define	YYCTYPE		char
#define	YYCURSOR	s.cur
#define	YYLIMIT		s.lim
#define	YYMARKER	s.ptr
#define	YYFILL(n)	s.fill(n)
#define RET(n)      return (n)

int scan(Scanner &s)
{
std:

/*!re2c

("0"* "." "e"? "L"?) |
("0"+ "." "e"? "L"?)
	{
		RET(FCON);
	}

"\n"
	{
		s.line++;
		if(1||s.cur == s.eof) RET(EOI);
		goto std;
	}


.
	{
		RET(UNEXPECTED);
	}
*/
}

int main(int,char**)
{
	Scanner s("\n0.eL\n00.eL\n");
	
	std::cout << "RES(2): " << scan(s) << std::endl;
	std::cout << "RES(1): " << scan(s) << std::endl;
	std::cout << "RES(2): " << scan(s) << std::endl;
	std::cout << "RES(1): " << scan(s) << std::endl;
	std::cout << "RES(2): " << scan(s) << std::endl;
	std::cout << "RES(0): " << scan(s) << std::endl;
}
