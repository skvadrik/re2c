#define	NULL		((char*) 0)

const unsigned char *scan(const unsigned char *p, unsigned int len, int *state)
{
	unsigned char c;
	const unsigned char *q;
	const unsigned char * const e = p + len;
/*!re2c
re2c:variable:yych           = c;
re2c:indent:top              = 1;
re2c:state:abort             = 0;
re2c:state:nextlabel         = 0;
re2c:define:YYCTYPE          = char;
re2c:define:YYCURSOR         = p;
re2c:define:YYLIMIT          = e;
re2c:define:YYMARKER         = q;
re2c:yyfill:check            = 0;
re2c:define:YYFILL:naked     = 1;
re2c:define:YYFILL           = "if (p >= e) {\n\t\treturn NULL;\n\t}";
re2c:define:YYSETSTATE       = "*state = @;";
re2c:define:YYSETSTATE:naked = 1;
re2c:define:YYSETSTATE@state = "@";
re2c:define:YYGETSTATE       = "*state";
re2c:define:YYGETSTATE:naked = 1;
*/
/*!getstate:re2c */
/*!re2c
	[0-9]+		{ return p; }
	[\000-\377]	{ return NULL; }
*/
}
