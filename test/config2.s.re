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
	re2c:indent:string = "   ";
	[a]			{ return YYCURSOR; }
	[b]			{ return YYCURSOR; }
	[c]			{ return YYCURSOR; }
	[d]			{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}

char *scan1(char *p)
{
	char *q;
/*!re2c
	re2c:indent:string = "\t";
	[a]			{ return YYCURSOR; }
	[b]			{ return YYCURSOR; }
	[c]			{ return YYCURSOR; }
	[d]			{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}

char *scan(char *p)
{
	char *q;
/*!re2c
	re2c:indent:string = "";
	[a]			{ return YYCURSOR; }
	[b]			{ return YYCURSOR; }
	[c]			{ return YYCURSOR; }
	[d]			{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}
