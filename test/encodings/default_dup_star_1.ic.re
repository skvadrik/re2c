// re2c $INPUT -o $OUTPUT -ic
/*!re2c
	<c1> *	{ return DEFAULT-1; }
	<c2> *	{ return DEFAULT-2; }
	<c3> ""	{ return C3; }
	<*> *	{ return DEFAULT-*; }
*/
