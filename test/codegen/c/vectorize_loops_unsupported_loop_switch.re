// re2c $INPUT -o $OUTPUT -i --vectorize-loops --loop-switch
// The vector loop falls through to the scalar dispatcher of a labelled state; other
// code models are rejected as an error.
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
