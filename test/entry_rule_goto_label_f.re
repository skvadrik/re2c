// re2c $INPUT -o $OUTPUT -cfi

/*!re2c:x
    [a]*   { return a; }
    !entry { /* init ... */ }
*/

/*!getstate:re2c:x*/

/*!conditions:re2c*/
/*!re2c:y
    <a> [a]*   { return a; }
    <b> [b]*   { return b; }
    <*> !entry { /* init * ... */ }
    <a> !entry { /* init a ... */ }
*/

/*!getstate:re2c:y*/
