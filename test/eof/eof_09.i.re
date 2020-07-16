// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:eof = 0;

    *   { return FAIL; }
    $   { return EOF; }
    [a] { return OK; }
*/

/*!re2c
    re2c:eof = -1;

    *   { return FAIL; }
    [a] { return OK; }
*/

/*!re2c
    re2c:eof = 42;

    *   { return FAIL; }
    $   { return EOF; }
    [b] { return OK; }
*/

/*!re2c
    re2c:eof = -1;

    *   { return FAIL; }
    [b] { return OK; }
*/
