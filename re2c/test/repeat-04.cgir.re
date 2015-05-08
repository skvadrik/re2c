// multiple scanners, error

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
/* Next block is not possible */
/*!rules:re2c
*/
}
 