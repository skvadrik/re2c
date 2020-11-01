// re2c $INPUT -o $OUTPUT --stadfa --tags -i

/*!re2c
    re2c:eof = 0;

    "" { return 1; }
    $  { return 0; }
    [a]* ([b] @x [a]* @y)? [\n] {}
*/
