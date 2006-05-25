#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RET(n) return n

size_t scan(const char *s, int l, char *r)
{
	const char *p = s;
	const char *q;
	#define YYCTYPE         char
	#define YYCURSOR        p
	#define YYLIMIT         (s+l)
	#define YYMARKER        q
	#define YYFILL(n)

	while(1)
	{
/*!re2c
	ALNUM = [0-9a-zA-Z];
	ANY = [\001-\377]\"?";
	EOF = '\000';
	
	"?!" ALNUM* {
		*r++ = '1';
		continue;
	}
	
	"?" ALNUM+ {
		*r++ = '2';
		continue;
	}
	
	EOF {
		*r++ = '3';
		*r++ = '\0';
		return p - s;
	}
	
	ANY* {
		*r++ = '0';
		*r++ = '\0';
		return p - s;
	}
*/
	}
}

void _do_scan(const char * str, size_t str_len, size_t scn_len, const char * exp, size_t exp_len)
{
	char res[32], sp[32];
	size_t res_len, inp_len;

	inp_len = scan(str, str_len, res);
	res_len = strlen(res);
	
	memset(sp, ' ', sizeof(sp));
	sp[15 - str_len] = '\0';

	printf("[%s](%2d/%2d)%s: %8s(%d) %s %8s(%d)\n", str, inp_len, scn_len, sp, 
			res, res_len, 
			inp_len != scn_len || exp_len != res_len || strncmp(exp, res, exp_len) ? "!=" : "==", 
			exp, exp_len);
}

#define do_scan(str, scn_len, exp) _do_scan(str, sizeof(str) - 1, scn_len, exp, sizeof(exp) - 1)

main()
{
	do_scan("?1??",         2, "20");
	do_scan("#",            1, "0");
	do_scan("##",           2, "0");
	do_scan("##?",          2, "0");
	do_scan("##|",          3, "0");
	do_scan("?!|",          3, "10");
	do_scan("?!?1|",        5, "120");
	do_scan("?!?a+",        5, "120");
	do_scan("?2!1?2??",     4, "20");
	do_scan("?1?2!1?2??",   6, "220");
	do_scan("?1?2?!1?2??",  9, "22120");
	do_scan("?1?2?!1?2?!", 12, "221213");
	do_scan("?1?123?45??",  9, "2220");
	do_scan("?1?123?45?!", 12, "22213");
}
