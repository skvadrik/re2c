// re2c $INPUT -o $OUTPUT -i --arch bad --vectorize-loops
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
