// multiple scanners

/*!types:re2c */

void scan(unsigned char* in)
{
/*!rules:re2c

<*>		"a"	{ return "a"; }
<*>		.	{ return "."; }
<r1>	"b" { return "b"; }
<r1,r2>	"c" { return "c"; }

*//*!use:re2c

<r1>	"1" { return "1"; }

*/

}

void scan(unsigned short* in)
{
/*!use:re2c

<r1>	"2" { return "2"; }

*/
}
