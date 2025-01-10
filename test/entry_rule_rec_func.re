// re2c $INPUT -o $OUTPUT -ci --recursive-functions

/*!re2c
    re2c:YYFN = ["lex;int"];
*/

/*!re2c:x
    [a]* { return a; }
    ^    { /* init ... */ }
*/

/*!conditions:re2c*/
/*!re2c:y
    <a> [a]* { return a; }
    <b> [b]* { return b; }
    <*> ^    { /* init * ... */ }
    <a> ^    { /* init a ... */ }
*/
