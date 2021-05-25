// re2c $INPUT -o $OUTPUT -gi
// multiple scanners, additional rules, char width change, default rule

void scan(unsigned char* in)
{
/*!rules:re2c

"a" := return "a";
"b" := return "b";
"c" := return "c";
"d" := return "d";
*   := return "DEFAULT";

re2c:indent:top = 1;

*//*!use:re2c

re2c:flags:u = 0;
re2c:flags:w = 0;

re2c:define:YYCTYPE  = 'unsigned char';
re2c:define:YYFILL   = 'fill1';
re2c:define:YYCURSOR = 'cursor1';
re2c:define:YYLIMIT  = 'limit1';

"1"	:= return "1";
.   := return ".";

*/
}

void scan(unsigned short* in)
{
/*!use:re2c

re2c:flags:u = 0;
re2c:flags:w = 1;

re2c:define:YYCTYPE  = 'unsigned short';
re2c:define:YYFILL   = 'fill2';
re2c:define:YYCURSOR = 'cursor2';
re2c:define:YYLIMIT  = 'limit2';

"2"	:= return "2";
.   := return ".";

*/
}

void scan(unsigned int* in)
{
/*!use:re2c

re2c:flags:w = 0;
re2c:flags:u = 1;

re2c:define:YYCTYPE  = 'unsigned int';
re2c:define:YYFILL   = 'fill3';
re2c:define:YYCURSOR = 'cursor3';
re2c:define:YYLIMIT  = 'limit3';

"3"	:= return "3";
.   := return ".";

*/
}
