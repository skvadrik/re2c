// re2c $INPUT -o $OUTPUT -i

// ok, name 'x' is defined in the scope of block 'xa'
/*!rules:re2c:xa
    x = [a];
*/

// ok, name 'x' is defined in the scope of block 'xb'
/*!rules:re2c:xb
    x = [b];
*/

// ok, name 'x' is pulled into global scope
/*!re2c
    !use:xa;
*/

// error, name 'x' is alredy defined
/*!re2c
    x = [x];
*/
