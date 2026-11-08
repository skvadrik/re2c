// re2c $INPUT -o $OUTPUT -i --vectorize-loops
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
