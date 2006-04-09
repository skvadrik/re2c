#define	NULL		((char*) 0)
#define	YYCTYPE		char
#define	YYCURSOR	p
#define	YYLIMIT		p
#define	YYMARKER	q
#define	YYFILL(n)

char *scan(char *p)
{
	char *q;
/*!re2c
	re2c:indent:top = 1;
*/
/*!getstate:re2c */

	// after getstate

/*!re2c
	re2c:state:abort = 0;
	re2c:state:nextlabel = 0;
	[0-9]+		{ return YYCURSOR; }
	[\000-\377]	{ return NULL; }
*/
}
