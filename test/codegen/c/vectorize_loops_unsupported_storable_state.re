// re2c $INPUT -o $OUTPUT -i --vectorize-loops --storable-state
// Storable state restores execution at YYFILL points; the vector loop has none.
// The combination is rejected as an error.
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
