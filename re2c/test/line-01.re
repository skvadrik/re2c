const char* scan(unsigned char* in)
{
/*!re2c

#line 1 "a"
"a" {
		return "a";
	}
#line 2 "b"
"b" {
		return "b";
	}
"c" {
		return "c";
	}
#line 1 "d"

"d" {
		return "d";
	}

.   {
		return ".";
	}
#line 1 "e"
*/
}
