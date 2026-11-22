// re2c --vectorize-linear -Werror $INPUT -o $OUTPUT
/*!re2c
    re2c:eof = 0;
    "abcdefgh" { return 1; }
    * { return 0; }
    $ { return 2; }
*/
