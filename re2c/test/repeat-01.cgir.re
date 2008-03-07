// multiple scanners

/*!types:re2c */

void scan(unsigned char* in)
{
/*!re2c

re2c:define:YYCTYPE  = 'unsigned char';




<*>		"1"	{ return "1"; }
<*>		"2"	{ return "2"; }
<r1>	"a" { return "a"; }
<r1,r2>	"b" { return "b"; }

*/
}

void scan(unsigned short* in)
{
/*!repeat:re2c






*/
}

void scan(unsigned int* in)
{
/*!repeat:re2c






*/
}

