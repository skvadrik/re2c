// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:flags:x = 1; // set UTF-16
    [^] {}
*/

/*!re2c
    re2c:flags:w = 0; // don't reset, still UTF-16
    [^] {}
*/

/*!re2c
    re2c:flags:x = 0; // reset, ASCII
    [^] {}
*/
