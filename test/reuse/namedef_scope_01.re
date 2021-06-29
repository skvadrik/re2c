// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:yyfill:enable = 0;
    re2c:flags:s = 1;
*/

/*!rules:re2c:xa
    x = [a];
    * {}
*/

/*!rules:re2c:xb
    x = [b];
    * {}
*/

// match a
/*!use:re2c:xa
    x {}
*/

// match b
/*!use:re2c:xb
    x {}
*/

// match c
/*!re2c
    x = [c];
    x {}
    * {}
*/

// match c
/*!re2c
    x {}
    * {}
*/
