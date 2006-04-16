/*!re2c

DEF1	= ("a"|"b")/[1] ;
DEF2	= ("a"|"b")/[0-9]+ ;

DEF1    { return KEYWORD; }
DEF2	{ return KEYWORD; }
[0-9]+	{ return NUMBER;  }

[^]		{ return UNEXPECTED; }

*/
