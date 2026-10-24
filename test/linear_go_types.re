// re2c --lang go $INPUT -o $OUTPUT
/*!local:re2c
    re2c:api = simple;
    re2c:YYCTYPE = byte;
    re2c:vectorize:linear = 1;
*/
/*!local:re2c
    re2c:api = simple;
    re2c:YYCTYPE = uint8;
    re2c:vectorize:linear = 1;
*/
/*!local:re2c
    re2c:api = simple;
    re2c:YYCTYPE = rune;
    re2c:vectorize:linear = 0;
*/
