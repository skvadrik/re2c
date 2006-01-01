#define	NULL		((char*) 0)
#define	YYCTYPE		char
#define	YYCURSOR	p
#define	YYLIMIT		p
#define	YYMARKER	q
#define	YYFILL(n)

char *scan0(char *p)
{
	char *q;
/*!re2c
	re2c:indent:top = 0;
	[0-9]+		{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}

char *scan1(char *p)
{
	char *q;
/*!re2c
	re2c:indent:top = 1;
	[0-9]+		{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}

char *scan(char *p)
{
	char *q;
/*!re2c
	[0-9]+		{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}
