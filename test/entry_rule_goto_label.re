// re2c $INPUT -o $OUTPUT -ci

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
