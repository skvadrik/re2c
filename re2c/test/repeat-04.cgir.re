// multiple scanners, error

/*!types:re2c */

void scan(unsigned char* in)
{
/*!re2c
re2c:define:YYCTYPE  = 'unsigned char';
*/

/*!re2c

<*>		"1"	{ return "1"; }
<*>		"2"	{ return "2"; }
<r1>	"a" { return "a"; }
<r1,r2>	"b" { return "b"; }

*/
/* Next block is not possible */
/*!re2c
*/
}
 