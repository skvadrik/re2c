// re2c $INPUT -o $OUTPUT -i

/*!re2c
    re2c:eof = 0;
    re2c:yyfill:enable = 0;
*/

/*!re2c
    [^][^] { r1 }
    $      { eof }
*/

/*!re2c
    [^][^] { r1 }
    ""     { empty }
    $      { eof }
*/
