// re2c $INPUT -o $OUTPUT -i

// ok, name 'x' is defined in the scope of block 'xa'
/*!rules:re2c:xa
    x = [a];
*/

// ok, name 'x' is defined in the scope of block 'xb'
/*!rules:re2c:xb
    x = [b];
*/

// ok, name 'x' is defined in global scope
/*!re2c
    x = [x];
*/

// error, name 'x' is alredy defined
/*!re2c
    !use:xa;
*/
