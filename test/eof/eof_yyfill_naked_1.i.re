// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:eof = 0;
*/

/*!re2c
    re2c:define:YYFILL = "fill() == 0";
    re2c:define:YYFILL:naked = 1;
    re2c:yyfill:parameter = 1;
    *   { return FAIL; }
    $   { return EOF; }
    [a] { return OK; }
*/

/*!re2c
    re2c:define:YYFILL = "fill() == 0";
    re2c:define:YYFILL:naked = 1;
    re2c:yyfill:parameter = 0;
    *   { return FAIL; }
    $   { return EOF; }
    [a] { return OK; }
*/

/*!re2c
    re2c:define:YYFILL = "fill";
    re2c:define:YYFILL:naked = 0;
    re2c:yyfill:parameter = 1;
    *   { return FAIL; }
    $   { return EOF; }
    [a] { return OK; }
*/

/*!re2c
    re2c:define:YYFILL = "fill()";
    re2c:define:YYFILL:naked = 0;
    re2c:yyfill:parameter = 0;
    *   { return FAIL; }
    $   { return EOF; }
    [a] { return OK; }
*/
