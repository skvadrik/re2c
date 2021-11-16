//go:generate re2go -f $INPUT -o $OUTPUT --loop-switch -i

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
