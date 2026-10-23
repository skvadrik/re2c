// re2c $INPUT -o $OUTPUT -i --vectorize-loops --eager-skip
// Eager skip moves the cursor increment onto transitions; the vector loop relies on
// the lazy skip of the loop state. The combination is rejected as an error.
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
