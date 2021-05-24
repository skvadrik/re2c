// re2c $INPUT -o $OUTPUT -cgi
/*!types:re2c */

void scan(unsigned char* in)
{
/*!rules:re2c

<r1>		*	{ return "DEFAULT-r1"; }
<*>		"a"	{ return "a"; }
<*>		.	{ return "."; }
<r1>	"b" { return "b"; }
<r1,r2>	"c" { return "c"; }

*//*!use:re2c

<r1>	"1" { return "1"; }
<r2>	*		{ return "DEFAULT-r2"; }

*/

}

void scan(unsigned short* in)
{
/*!use:re2c

<r1>	"2" { return "2"; }

*/
}
