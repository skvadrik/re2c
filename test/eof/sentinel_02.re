// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:yyfill:enable = 0;
    re2c:sentinel = 256;

    str = ['] [^']* ['];

    str {}
    * {}
*/
