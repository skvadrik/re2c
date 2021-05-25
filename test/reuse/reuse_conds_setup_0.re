// re2c $INPUT -o $OUTPUT -cgi

/*!rules:re2c
	<*>	"a"	{ return "a"; }
	<*>	.	{ return "."; }
	<r1>	"b"	{ return "b"; }
	<r1,r2>	"c"	{ return "c"; }
*/

/*!use:re2c
	<!r1>		{ return "SETUP - r1"; }
	<r1>	"1"	{ return "1"; }
*/

/*!use:re2c
	<!r2>		{ return "SETUP - r2"; }
	<r1>	"2"	{ return "2"; }
*/
