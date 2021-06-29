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

// match a (does not add 'x' in the global scope)
/*!local:re2c
    !use:xa;
    x {}
*/

// match b (does not add 'x' in the global scope)
/*!local:re2c
    !use:xb;
    x {}
*/

// match c (does not add 'x' in the global scope)
/*!local:re2c
    x = [c];
    x {}
    * {}
*/

// match d (adds 'x' in the global scope)
/*!re2c
    x = [d];
    x {}
    * {}
*/

// match d
/*!re2c
    x {}
    * {}
*/
