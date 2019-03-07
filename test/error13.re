/*!max:re2c */

/*!re2c
	"ABC"		{ return 1; }
	"ABD"		{ return 2; }
	[^]			{ return 0; }
*/
