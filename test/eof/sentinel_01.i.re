// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:yyfill:enable = 0;
    str = ['] [^'\xFE]* ['];
*/

/*!re2c
    str {}
    * {}
*/

/*!re2c
    re2c:sentinel = 0;
    str {}
    * {}
*/

/*!re2c
    re2c:sentinel = -1;
    str {}
    * {}
*/

/*!re2c
    re2c:sentinel = 39; // single quote
    str {}
    * {}
*/

/*!re2c
    re2c:sentinel = 254; // \xFE
    str {}
    * {}
*/

/*!re2c
    re2c:sentinel = 255;
    str {}
    * {}
*/
