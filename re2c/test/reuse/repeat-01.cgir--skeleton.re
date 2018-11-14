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






*/
}

void scan(unsigned short* in)
{
/*!use:re2c






*/
}

void scan(unsigned int* in)
{
/*!use:re2c






*/
}

