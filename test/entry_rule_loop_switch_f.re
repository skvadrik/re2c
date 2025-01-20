// re2c $INPUT -o $OUTPUT -cfi --loop-switch

/*!re2c:x
    [a]*   { return a; }
    !entry { /* init ... */ }
*/

/*!conditions:re2c*/
/*!re2c:y
    <a> [a]*   { return a; }
    <b> [b]*   { return b; }
    <*> !entry { /* init * ... */ }
    <a> !entry { /* init a ... */ }
*/
