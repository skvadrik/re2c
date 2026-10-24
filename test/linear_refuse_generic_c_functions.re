// re2c --vectorize-linear $INPUT -o $OUTPUT
/*!re2c
    re2c:api = generic;
    re2c:api:style = functions;
    "abcdefgh" { return 1; }
    * { return 0; }
*/
