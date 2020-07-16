// re2c $INPUT -o $OUTPUT -cs
enum cond_t : int;

int main ()
{
	cond_t cond;
	char * YYCURSOR;
#define YYGETCONDITION() cond
/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = "unsigned char";
	re2c:define:YYCONDTYPE = "cond_t : int";
	<a> "a" {}
	<b> "b" {}
*/
	return 0;
}

/*!types:re2c*/
