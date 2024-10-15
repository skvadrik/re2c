// re2c $INPUT -o $OUTPUT -fi --recursive-functions

/*!re2c
    re2c:define:YYFN = ["lex_x;void", "x;X"];
    [a] { a }
    *   { * }
*/

/*!re2c
    re2c:define:YYFN = ["lex_y;void", "y;Y"];
    re2c:eof = 0;
    [b] { b }
    $   { $ }
    *   { * }
*/
