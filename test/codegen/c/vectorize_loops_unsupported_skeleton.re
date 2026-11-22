// re2c $INPUT -o $OUTPUT -i --skeleton --arch x86 --vectorize-loops
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
