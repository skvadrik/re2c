// multiple scanners

/*!types:re2c */

void scan(unsigned char* in)
{
/*!rules:re2c

<*>		"1"	{ return "1"; }
<*>		"2"	{ return "2"; }
<r1>	"a" { return "a"; }
<r1,r2>	"b" { return "b"; }
*//*!use:re2c

re2c:define:YYCTYPE  = 'unsigned char';
re2c:define:YYFILL   = 'fill1';
re2c:define:YYCURSOR = 'cursor1';
re2c:define:YYLIMIT  = 'limit1';

*/
}

void scan(unsigned short* in)
{
/*!use:re2c

re2c:define:YYCTYPE  = 'unsigned short';
re2c:define:YYFILL   = 'fill2';
re2c:define:YYCURSOR = 'cursor2';
re2c:define:YYLIMIT  = 'limit2';

*/
}

void scan(unsigned int* in)
{
/*!use:re2c

re2c:define:YYCTYPE  = 'unsigned int';
re2c:define:YYFILL   = 'fill3';
re2c:define:YYCURSOR = 'cursor3';
re2c:define:YYLIMIT  = 'limit3';

*/
}

