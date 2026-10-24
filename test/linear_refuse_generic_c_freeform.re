// re2c $INPUT -o $OUTPUT
/*!re2c
    re2c:vectorize:linear = 1;
    re2c:api = generic;
    re2c:api:style = free-form;
    "abcdefgh" { return 1; }
    * { return 0; }
*/
