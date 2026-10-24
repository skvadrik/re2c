// re2c $INPUT -o $OUTPUT -i --vectorize-loops
// The length guard of the vector loop is derived from YYFILL bounds checking; with
// YYFILL disabled the combination is rejected as an error.
/*!re2c
    re2c:yyfill:enable = 0;
    [a-z]+ { return 1; }
    *      { return 0; }
*/
