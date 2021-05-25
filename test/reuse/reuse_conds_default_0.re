// re2c $INPUT -o $OUTPUT -cgi
// This test currently fails with error
// 're2c: error: line 13, column 9: code to default rule 'r1' is already defined'
// This must be fixed later

/*!rules:re2c
	<*>	"a"	{ return "a"; }
	<*>	.	{ return "."; }
	<r1>	"b"	{ return "b"; }
	<r1,r2>	"c"	{ return "c"; }
*/

/*!use:re2c
	<r1>	*	{ return "DEFAULT - r1"; }
	<r1>	"1"	{ return "1"; }
*/

/*!use:re2c
	<r2>	*	{ return "DEFAULT - r2"; }
	<r1>	"2"	{ return "2"; }
*/
