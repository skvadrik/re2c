// re2c --vectorize-linear -u -Werror $INPUT -o $OUTPUT
/*!re2c
    "abcdefgh" { return 1; }
    * { return 0; }
*/
