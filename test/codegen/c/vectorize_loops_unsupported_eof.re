// re2c $INPUT -o $OUTPUT -i --vectorize-loops
// The end-of-input rule checks for the sentinel at every position; the vector loop
// skips positions, so the combination is rejected as an error.
/*!re2c
    re2c:eof = 0;
    [a-z]+ { return 1; }
    $      { return 2; }
    *      { return 0; }
*/
