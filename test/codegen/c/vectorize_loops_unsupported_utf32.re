// re2c $INPUT -o $OUTPUT -i --vectorize-loops -u
// Encodings with code units wider than one byte are rejected as an error: the vector
// block compares bytes.
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
