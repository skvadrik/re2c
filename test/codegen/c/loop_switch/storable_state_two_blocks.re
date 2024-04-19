// re2c $INPUT -o $OUTPUT -fi --loop-switch

/*!re2c
    [a] { a }
    *   { * }
*/

/*!re2c
    re2c:eof = 0;
    [b] { b }
    $   { $ }
    *   { * }
*/
