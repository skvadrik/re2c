// re2c --lang go $INPUT -o $OUTPUT
/*!re2c
    re2c:api = simple;
    re2c:vectorize:linear = 1;
    re2c:YYCTYPE = rune;
    re2c:yyfill:enable = 0;
    "abcdefgh" { return 1 }
    * { return 0 }
*/
