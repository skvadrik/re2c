/*!re2c
	[\x00-\x7f]		{ return 0; }
	[\x80-\u07ff]		{ return 1; }
	[\u0800-\u0fff]		{ return 2; }
	[\u1000-\uffff]		{ return 3; }
	[\U00010000-\U0003ffff]	{ return 4; }
	[\U00040000-\U000fffff]	{ return 5; }
	[\U00100000-\U0010ffff]	{ return 6; }
*/
