// re2c $INPUT -o $OUTPUT -i
// rules block disables YYFILL
/*!rules:re2c
    re2c:yyfill:enable = 0;
*/

// use block has no YYFILL
/*!use:re2c
    "a" { a }
    *   { xa }
*/

// normal block still has YYFILL
/*!re2c
    "b" { b }
    *   { xb }
*/
