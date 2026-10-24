// re2c --lang go --vectorize-linear $INPUT -o $OUTPUT
/*!re2c
    re2c:api = simple;
    re2c:YYCTYPE = uint16;
    re2c:yyfill:enable = 0;
    "abcdefgh" { return 1 }
    * { return 0 }
*/
