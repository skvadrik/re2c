// multiple scanners, error

/*!types:re2c */

void scan(unsigned char* in)
{
/*!rules:re2c

<*>		"1"	{ return "1"; }
<*>		"2"	{ return "2"; }
<r1>	"a" { return "a"; }
<r1,r2>	"b" { return "b"; }

*/
}

void scan(unsigned short* in)
{
/*!use:re2c

<r1>	"c" { return "c"; }

*/
}
